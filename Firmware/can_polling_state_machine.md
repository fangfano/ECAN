# CAN 按需收发 + 学习式路由方案（修订版）

## Context

原方案的"7 电机轮询、发一个等一个回复"模型被用户否定。新需求：

1. **总线可能不满 7 个电机**：可能只接 3 个，分布在 1/3/6 号槽位。其他槽位 CAN ID 字段为 0（主机不填）。
2. **TX 按需**：主机更新哪个槽位 → 就发那个槽位的 CANFD。槽位 CAN ID 为 0（主机未填）→ 跳过不送。
3. **TX/RX 不互相等待**：发送不需要等接收，接收不需要等发送。让 CAN 总线自己仲裁，程序上不做时序限制。
4. **RX 路由由 TX 学习**：每个槽位的 CAN ID 不是预定义的，而是从该槽位 TxPDO 内容的前 2 字节读取。一旦某槽位被 TX 过，其 CAN ID 就被"学习"记下。后续 RX 收到同 ID 的帧，路由到该槽位的 RxPDO 槽。
5. **从未 TX 过 → RX 丢弃**：如果某 CAN ID 从未被任何槽位 TX 过，对应 RX 帧直接丢弃（无法确定路由目标）。
6. **4 路独立并发**：4 个 CAN 通道互不阻塞，独立收发。

与原方案的差异：取消 POLL_TX_SEND / POLL_WAIT_RX 状态机、取消 5ms 超时、取消 `s_motor_can_ids` 预定义 ID 表（CAN ID 改由 TxPDO 内容学习）。

## 实现方案

### 1. 数据结构（`can_app.c` 新增）

```c
typedef struct {
    bool active;              /* 本槽位至少被 TX 过一次 */
    uint16_t last_can_id;    /* 最近一次 TX 时从该槽位 TxPDO 学到的 CAN ID */
} slot_state_t;

static slot_state_t s_slot_state[4][7];   /* [bus][slot] - RX 路由学习表 */
static volatile bool s_bus_tx_pending[4];  /* 主机写 PDO 后由 trigger 设置 */

/* RxPDO/TxPDO 7 个槽位的指针表（替代原 4-case switch） */
static CHAR *const s_rx_pdo_ptrs[4][7] = {
    { RxCanGroup110x6000, RxCanGroup120x600B, RxCanGroup130x6016, RxCanGroup140x6021,
      RxCanGroup150x602C, RxCanGroup160x6037, RxCanGroup170x6042 },
    { RxCanGroup210x604D, RxCanGroup220x6058, RxCanGroup230x6063, RxCanGroup240x606E,
      RxCanGroup250x6079, RxCanGroup260x6084, RxCanGroup270x608F },
    { RxCanGroup310x609A, RxCanGroup320x60A5, RxCanGroup330x60B0, RxCanGroup340x60BB,
      RxCanGroup350x60C6, RxCanGroup360x60D1, RxCanGroup370x60DC },
    { RxCanGroup410x60E7, RxCanGroup420x60F2, RxCanGroup430x60FD, RxCanGroup440x6108,
      RxCanGroup450x6113, RxCanGroup460x611E, RxCanGroup470x6129 },
};
static CHAR *const s_tx_pdo_ptrs[4][7] = {
    { TxCanGroup110x7000, TxCanGroup120x700B, TxCanGroup130x7016, TxCanGroup140x7021,
      TxCanGroup150x702C, TxCanGroup160x7037, TxCanGroup170x7042 },
    /* ... bus 1/2/3 同理，参考 can_app.c 现有 can_app_read_tx_pdo 的 4-case 实现 ... */
};
```

### 2. PDO 存取辅助（重构现有 4-case switch 为循环）

```c
static void can_app_read_tx_pdo(uint32_t ch, CHAR *buf) {
    for (uint8_t i = 0; i < 7; i++) MEMCPY(&buf[i*11], s_tx_pdo_ptrs[ch][i], 11);
}
static void can_app_write_rx_pdo(uint32_t ch, const CHAR *buf) {
    for (uint8_t i = 0; i < 7; i++) MEMCPY(s_rx_pdo_ptrs[ch][i], &buf[i*11], 11);
}
static void can_app_clear_tx_pdo(uint32_t ch) {
    for (uint8_t i = 0; i < 7; i++) memset(s_tx_pdo_ptrs[ch][i], 0, 11);
}
/* 新增：单槽位 RX 直写（避免一次 RX 事件就写整路 77 字节） */
static void can_app_write_rx_pdo_slot(uint32_t ch, uint8_t slot, const CHAR *data11) {
    if (ch < 4 && slot < 7) MEMCPY(s_rx_pdo_ptrs[ch][slot], data11, 11);
}
```

### 3. 统一 RX 非阻塞接收

把现有 4 个 `canN_receive_non_blocking` 合并为 1 个：
```c
static hpm_stat_t can_receive_non_blocking(uint32_t ch, mcan_rx_message_t *rx_msg) {
    MCAN_Type *base = hpm_can_get_base(ch);
    if (base == NULL) return status_invalid_argument;
    if (base->IR & MCAN_INT_RXFIFO0_NEW_MSG) {
        volatile uint32_t tmp = base->IR; (void)tmp;
        return hpm_can_receive(ch, rx_msg);
    }
    return status_fail;
}
```

### 4. 主循环统一处理函数（核心）

```c
void can_app_process_bus(uint32_t ch) {
    /* === TX: 主机写 PDO 触发，扫描 7 槽，发非零 ID 的 === */
    if (s_bus_tx_pending[ch]) {
        s_bus_tx_pending[ch] = false;
        CHAR tx_buf[77];
        can_app_read_tx_pdo(ch, tx_buf);
        for (uint8_t slot = 0; slot < 7; slot++) {
            uint32_t off = slot * 11;
            uint16_t can_id = ((uint16_t)(uint8_t)tx_buf[off] << 8) |
                              ((uint16_t)(uint8_t)tx_buf[off+1]);
            if (can_id == 0) continue;            /* 主机未填，跳过 */

            uint8_t frame_type = (uint8_t)tx_buf[off+2];
            mcan_tx_frame_t f = {0};
            f.std_id = can_id & 0x7FF;
            f.use_ext_id = 0;
            f.dlc = 8;
            if (frame_type == MOTOR_FRAME_TYPE_CAN)         { f.canfd_frame=0; f.bitrate_switch=0; }
            else if (frame_type == MOTOR_FRAME_TYPE_CANFD) { f.canfd_frame=1; f.bitrate_switch=0; }
            else                                            { f.canfd_frame=1; f.bitrate_switch=1; }
            memcpy(f.data_8, &tx_buf[off+3], 8);
            hpm_can_transmit(ch, &f);

            /* 学习该槽位的 CAN ID，供 RX 反向路由 */
            s_slot_state[ch][slot].active = true;
            s_slot_state[ch][slot].last_can_id = can_id;

            s_can_led_state[ch].tx_active = true;
            s_can_led_state[ch].tx_last_tick = s_timer_tick;
        }
    }

    /* === RX: 排空 FIFO，按学到的 CAN ID 反向路由到对应槽位 === */
    mcan_rx_message_t rx_msg;
    while (can_receive_non_blocking(ch, &rx_msg) == status_success) {
        uint16_t can_id = rx_msg.use_ext_id
                          ? (uint16_t)(rx_msg.ext_id & 0x7FF)
                          : (uint16_t)(rx_msg.std_id & 0x7FF);

        int8_t slot = -1;
        for (uint8_t i = 0; i < 7; i++) {
            if (s_slot_state[ch][i].active && s_slot_state[ch][i].last_can_id == can_id) {
                slot = (int8_t)i;
                break;
            }
        }
        if (slot < 0) continue;  /* 从未 TX 过此 ID，丢弃 */

        /* 组装 11 字节并直写到对应 RxPDO 槽 */
        CHAR data11[11];
        data11[0] = (CHAR)((can_id >> 8) & 0xFF);
        data11[1] = (CHAR)(can_id & 0xFF);
        data11[2] = (CHAR)(rx_msg.canfd_frame
                           ? (rx_msg.bitrate_switch ? MOTOR_FRAME_TYPE_CANFD_BRS : MOTOR_FRAME_TYPE_CANFD)
                           : MOTOR_FRAME_TYPE_CAN);
        memcpy(&data11[3], rx_msg.data_8, 8);
        can_app_write_rx_pdo_slot(ch, (uint8_t)slot, data11);

        s_can_led_state[ch].rx_active = true;
        s_can_led_state[ch].rx_last_tick = s_timer_tick;
    }
}
```

### 5. Trigger 函数（实现改写）

```c
void can_app_trigger_transmit(void)    { s_bus_tx_pending[0] = true; }
void can_app_trigger_can1_transmit(void) { s_bus_tx_pending[1] = true; }
void can_app_trigger_can2_transmit(void) { s_bus_tx_pending[2] = true; }
void can_app_trigger_can3_transmit(void) { s_bus_tx_pending[3] = true; }
```

`digital_io.c::APPL_OutputMapping` 的调用点不动（仍按 77/154/231/308 阈值分别调 4 个 trigger）。

### 6. Init 函数微调

`can_app_init_canN_receive()`：
- 保留过滤器配置、`hpm_can_init_channel`、`s_canN_receive_initialized`、LED 标志
- 删除 `s_canN_rx_data` 相关 memset
- 保留 `can_app_write_rx_pdo(N, zero_buf)` 初始化为全零（用栈上 zero_buf 即可）
- 不再初始化 `s_slot_state[N]`（静态变量默认零，`active=false` 即可）

`can_app_init_canN_transmit()`：保留 `can_app_clear_tx_pdo(N)`，其余不变。



## 关键文件

- [application/can_app.c](file:///c:/Users/Fano/Desktop/ECAN/kh-ethercat-canfdx4-op-fang/Firmware/hpm_ethercat_sdk/application/can_app.c) — 主重构
- [application/can_app.h](file:///c:/Users/Fano/Desktop/ECAN/kh-ethercat-canfdx4-op-fang/Firmware/hpm_ethercat_sdk/application/can_app.h) — API 同步
- [ecat.c](file:///c:/Users/Fano/Desktop/ECAN/kh-ethercat-canfdx4-op-fang/Firmware/hpm_ethercat_sdk/ecat.c) — 主循环 8 行 process 调用 → 4 行 `can_app_process_bus(0..3)`

## 复用的现有工具

- `hpm_can_get_base` / `hpm_can_transmit` / `hpm_can_receive` / `MCAN_INT_RXFIFO0_NEW_MSG` — HPM CAN HAL
- `MEMCPY` 宏（SSC 提供）— PDO 字节搬运
- `s_timer_tick` + `led_blink_timer_callback`（[can_app.c:423](file:///c:/Users/Fano/Desktop/ECAN/kh-ethercat-canfdx4-op-fang/Firmware/hpm_ethercat_sdk/application/can_app.c#L423)）— 1ms tick，LED 共用
- `s_can_led_state[4]` — TX/RX LED 状态机

## 验证

1. `cmake --build build --target demo.elf` — 编译通过，无新增 warning。
2. 烧录后用 `ethercat pdos` 确认 SM2/SM3 DefaultSize 仍为 308。
3. 主机只写 CAN0 的 1/3/6 号槽位（其余槽位 CAN ID 字段为 0），CAN 抓包应观察到：
   - 每次主机写 PDO 后，CAN0 上**只发 3 帧**（不是 7 帧）；
   - 3 个电机的回复到来后，RxPDO 的 1/3/6 号槽位（`RxCanGroup110x6000` / `RxCanGroup130x6016` / `RxCanGroup160x6037`）被填充；其余槽位保持零。
4. 主机不写某路 PDO（如 CAN2），CAN2 上无任何自发 TX；若 CAN2 上有外来帧（无匹配学习 ID），全部丢弃，RxPDO CAN2 段保持零。
5. 4 路 CAN 在时间轴上互相重叠（并发），互不阻塞。
6. LED：每次 `hpm_can_transmit` 后 TX LED 亮 100ms；每次有效路由 RX 后 RX LED 亮 100ms。

## 不在本次范围

- `digital_io.xml` SM DefaultSize（仍 352，需改 308）和 `eeprom.h` 重生成 — 上一轮已提示。
- RevisionNo 递增 — 同上。
