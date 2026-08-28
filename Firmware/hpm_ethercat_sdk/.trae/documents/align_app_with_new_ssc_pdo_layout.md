# 让 application 代码对齐新生成的 SSC 对象字典布局

## Context（背景）

用 SSC Tool 重新生成的 `SSC/Src/digital_ioObjects.h` 已经把 CAN 应用的对象字典从原来的"每条 CAN 3 个 PDO 变量、30+30+20=80 字节"布局，改成"每条 CAN 8 个 PDO 变量、1 info + 7 motor 各 11 字节 = 88 字节、共 4 条 CAN 总线 352 字节"的新布局。新对象字典同时定义了 PDO 分配对象 `sRxPDOassign`/`sTxPDOassign`（0x1C12/0x1C13）、`OutputMapping00x1600`/`InputMapping00x1A00` 以及 `ApplicationObjDic[]`，已自洽。

但 `application/digital_io.c` 和 `application/can_app.c` 仍引用旧变量名（`RxCan00x6000`、`TxCan00x7000` 等）和旧的 80 字节内部缓冲布局，导致编译失败。本次任务是把这两个 application 文件改造为完全匹配新 SSC 布局。

## 设计决策（已与用户确认）

1. **info slot 编码**：用 8-bit 位掩码转 2 字符 hex 字符串 + null。bit i (0..6) 置 1 表示电机 (i+1) 在线/被寻址。
   - "7F" = 0x7F = 电机 1-7 全在
   - "15" = 0x15 = 电机 1/3/5 在
   - "00" = 无电机
   - 占用 3 字节（11 字节槽内剩余 8 字节填 0）

2. **方向语义（与 SSC 配置一致）**：
   - **RxCanGroup (0x6000 系, TxPDO 方向, slave→master)**：slave 从 CAN 收到电机数据后填充 motor 槽 + 刷新 info hex（本周期内哪些电机有响应），master 读取
   - **TxCanGroup (0x7000 系, RxPDO 方向, master→slave)**：master 把指令写进 motor 槽 + 在 info hex 中列出要寻址的电机，slave 解析 info hex 后只对名单中的电机发 CAN 帧

## 新 SSC 变量命名表（每条 CAN 8 个槽 × 11 字节）

| CAN | 槽 | 对象索引 | RxPDO 变量名 | TxPDO 变量名 |
|-----|----|---------|-------------|-------------|
| 1 | info | 0x6000/0x7000 | `RxCanGroup10x6000` | `TxCanGroup10x7000` |
| 1 | m1 | 0x600B/0x700B | `RxCanGroup110x600B` | `TxCanGroup110x700B` |
| 1 | m2 | 0x6016/0x7016 | `RxCanGroup120x6016` | `TxCanGroup120x7016` |
| 1 | m3 | 0x6021/0x7021 | `RxCanGroup130x6021` | `TxCanGroup130x7021` |
| 1 | m4 | 0x602C/0x702C | `RxCanGroup140x602C` | `TxCanGroup140x702C` |
| 1 | m5 | 0x6037/0x7037 | `RxCanGroup150x6037` | `TxCanGroup150x7037` |
| 1 | m6 | 0x6042/0x7042 | `RxCanGroup160x6042` | `TxCanGroup160x7042` |
| 1 | m7 | 0x604D/0x704D | `RxCanGroup170x604D` | `TxCanGroup170x704D` |
| 2 | info | 0x6058/0x7058 | `RxCanGroup20x6058` | `TxCanGroup20x7058` |
| 2 | m1..m7 | 0x6063..0x60A5 / 0x7063..0x70A5 | `RxCanGroup2{M}0xXXXX` | `TxCanGroup2{M}0xXXXX` |
| 3 | info | 0x60B0/0x70B0 | `RxCanGroup30x60B0` | `TxCanGroup30x70B0` |
| 3 | m1..m7 | 0x60BB..0x60FD / 0x70BB..0x70FD | `RxCanGroup3{M}0xXXXX` | `TxCanGroup3{M}0xXXXX` |
| 4 | info | 0x6108/0x7108 | `RxCanGroup40x6108` | `TxCanGroup40x7108` |
| 4 | m1..m7 | 0x6113..0x6155 / 0x7113..0x7155 | `RxCanGroup4{M}0xXXXX` | `TxCanGroup4{M}0xXXXX` |

## 改造范围

### 文件 1：`application/can_app.c`

**A. 常量与内部缓冲（开头部分）**

- 保留 `MOTOR_FRAME_COUNT=7`、`MOTOR_FRAME_SIZE=11`
- 新增 `INFO_SLOT_SIZE=11`、`SLOTS_PER_BUS=8`（1 info + 7 motors）、`CAN_BUS_COUNT=4`
- 把所有 `static CHAR canX_rx_buf[80]` / `CHAR tx_buf[80]` / `CHAR init_buf[80]` 改为 `[88]`
- `s_canX_rx_data.buffer[30]` 这种结构里跟 ECAT 直接对接的字段如果只是历史调试用，可保持不动；只需保证对接 PDO 的 88 字节布局正确

**B. `can_app_store_rx_frame(channel, buf, rx_msg)`（line 169）**

把 slot offset 从 `2 + slot*11` 改为 `11 + slot*11`（前 11 字节留给 info slot）。其余逻辑（写 `[id_hi, id_lo, frame_type, data[0..7]]`）不变。

写入 motor slot 后，同步更新 info hex：
1. 解析 `buf[0..1]` 为 hex → bitmask（用 `sscanf` 或手写 hex 解析）
2. `bitmask |= (1 << slot)`
3. 重新编码为 2 字符 hex 写回 `buf[0..1]`，剩余 9 字节填 0

**C. `can_app_write_rx_pdo(channel, buf)`（line 205）**

把原来 3 路 MEMCPY（30+30+20）改成 8 路 MEMCPY，每路 11 字节，目标改为新变量名。channel 0..3 对应 CAN1..CAN4：
- ch0: `RxCanGroup10x6000` ← `buf[0..10]`，`RxCanGroup110x600B` ← `buf[11..21]`，... `RxCanGroup170x604D` ← `buf[77..87]`
- ch1: `RxCanGroup20x6058` ... `RxCanGroup270x60A5`
- ch2: `RxCanGroup30x60B0` ... `RxCanGroup370x60FD`
- ch3: `RxCanGroup40x6108` ... `RxCanGroup470x6155`

用 `switch(channel)` + 显式列出 8 个 MEMCPY 的形式（与现有代码风格一致）。

**D. `can_app_read_tx_pdo(channel, buf)`（line 230）**

镜像 write_rx_pdo，方向相反：从 8 个 `TxCanGroup{N}{M?}0xXXXX` 变量 MEMCPY 到 `buf`。

**E. `can_app_clear_tx_pdo(channel)`（line 256）**

把 3 路 memset 改为 8 路 memset，每路 11 字节，对 8 个 `TxCanGroup{N}{M?}0xXXXX` 变量清零。info 槽清为 `"00"` 字符串（即 `'0','0',0,...`）。

**F. `can_app_send_motor_frames(channel, buf)`（line 112）**

不再用 `buf[0]=frame_count` 循环 7 次。改为：
1. 解析 `buf[0..1]` hex → bitmask
2. 对 i=0..6，若 `bitmask & (1<<i)`：offset = 11 + i*11，从 `buf[offset..offset+10]` 取 `[id_hi, id_lo, frame_type, data[0..7]]`，调用 `hpm_can_transmit` 发出
3. 不在 bitmask 中的电机跳过

**G. 各 `can_app_init_canX_receive` / `can_app_init_canX_transmit` 的 init_buf 初始化**

原来用 `init_buf[0] = MOTOR_FRAME_COUNT;`（即 7）。新布局下 init_buf 前 2 字节应是 info hex：
- receive 方向：init 时认为没电机响应，info = `"00"`
- transmit 方向：init 时认为没电机要发，info = `"00"`

把 `init_buf[0] = MOTOR_FRAME_COUNT;` 替换为 `init_buf[0] = '0'; init_buf[1] = '0'; init_buf[2] = 0;`（其余已是 0）。

### 文件 2：`application/digital_io.c`

**A. `APPL_InputMapping(UINT16 *pData)`（line 264）**

把原来 4 段（80/160/240/320 字节阈值、3 路 MEMCPY 30/30/20）改为 4 段（88/176/264/352 字节阈值、每段 8 路 MEMCPY 各 11 字节）：

```c
void APPL_InputMapping(UINT16 *pData) {
    uint8_t *pData8 = (uint8_t *)pData;
    if (nPdInputSize >= 88) {
        MEMCPY(&pData8[0],   &RxCanGroup10x6000,  11);
        MEMCPY(&pData8[11],  &RxCanGroup110x600B, 11);
        MEMCPY(&pData8[22],  &RxCanGroup120x6016, 11);
        MEMCPY(&pData8[33],  &RxCanGroup130x6021, 11);
        MEMCPY(&pData8[44],  &RxCanGroup140x602C, 11);
        MEMCPY(&pData8[55],  &RxCanGroup150x6037, 11);
        MEMCPY(&pData8[66],  &RxCanGroup160x6042, 11);
        MEMCPY(&pData8[77],  &RxCanGroup170x604D, 11);
    }
    if (nPdInputSize >= 176) {
        MEMCPY(&pData8[88],  &RxCanGroup20x6058,  11);
        MEMCPY(&pData8[99],  &RxCanGroup210x6063, 11);
        // ... 6 more ...
        MEMCPY(&pData8[165], &RxCanGroup270x60A5, 11);
    }
    if (nPdInputSize >= 264) { /* CAN3: offsets 176..263 */ }
    if (nPdInputSize >= 352) { /* CAN4: offsets 264..351 */ }
}
```

**B. `APPL_OutputMapping(UINT16 *pData)`（line 297）**

镜像 InputMapping，方向相反：从 `pData8` 读 → 写到 `TxCanGroup{N}{M?}0xXXXX`。每段后调用对应的 `can_app_trigger_canX_transmit()`（ch0→can_app_trigger_transmit, ch1→can_app_trigger_can1_transmit, etc.）。

**C. `APPL_Application(void)`（line 334）**

原来用 `TxCan00x7000[0]` 和 `[1]` 当 LED 值，新布局下 `TxCanGroup10x7000` 是 info hex 字符串，按字节读没意义。改为简单固定值（如 `APPL_SetLed(0, 0);`）或基于 ch0 info bitmask 解码后点亮 LED1/LED2（如有需要再细化）。本次先用 `APPL_SetLed(0, 0);` 占位，并在代码注释标明后续可基于 `TxCanGroup10x7000` hex 解析来驱动。

## 不动的部分

- `APPL_GenerateMapping`（line 189）：用 `sRxPDOassign`/`sTxPDOassign` 遍历 PDO assign，逻辑与新 SSC 完全兼容，**无需修改**
- `application/can_app.h`：公共 API 不变
- `can_app_init_canX_receive` / `can_app_init_canX_transmit` 的 CAN 配置部分（filter、baudrate 等）：与对象字典布局无关，**不动**
- `can0_receive_non_blocking` 等硬件接收函数：**不动**
- `led_blink_timer_callback`、`can_app_get_canX_rx_buffer`、`can_app_get_can0_status` 等辅助函数：**不动**

## 验证

1. **编译验证**：`cd build && ninja`，期望无 error、无 warning
2. **链接验证**：检查 `build/output/demo.map` 中 `RxCanGroup10x6000`、`TxCanGroup10x7000`、`sRxPDOassign`、`sTxPDOassign`、`ApplicationObjDic` 都在 `digital_io.c.obj` 段内
3. **运行时验证（如有硬件）**：
   - 让 CAN1 上 ID=0x001 的电机发一帧 → 用调试器看 `RxCanGroup110x600B` 的 11 字节被填充、`RxCanGroup10x6000` 变成 `"01"`
   - 让 CAN1 上 ID=0x001/0x003/0x005 三台电机各发一帧 → `RxCanGroup10x6000` 变成 `"15"`
   - master 写 `TxCanGroup10x7000="01"`、`TxCanGroup110x700B` 为合法 CAN 帧 → 看 CAN1 总线上出现一帧 ID=0x001 的报文
   - master 写 `TxCanGroup10x7000="00"` → slave 不发任何 CAN 帧
