# 嵌入式软件 岗工作报告

**定位：** 负责底层驱动、RTOS/Linux RT实时系统、EtherCAT/CAN总线通信、关节电机控制环路、传感器数据采集。核心：让上层算法在异构硬件上可靠、实时运行。

---

## 项目/模块

| 项目/模块 | EtherCAT 转 CANFD 从站程序开发 |
|-----------|-------------------------------|
| 版本 / Commit ID | V1.0 |
| DRI（负责人） | 方昕成 |
| 日期 | 2026年9月2日 |

---

## 一、本周工作概述

完成了 HPM5E00 四通道 CANFD 从站网关程序的完整开发：实现了 4 个独立 CAN 通道（每通道 7 个电机槽位，共 28 路）的 PDO 映射与双向数据路由；设计了 TX FIFO 非阻塞流水线发送机制，解决 FIFO 深度（4）小于待发送帧数（7）的硬件限制，通过 TC 中断驱动逐帧填充，将主循环 CPU 阻塞时间从约 4.46ms 降至 <0.2ms；修复了三处关键 Bug——CANFD 帧被截断为 8 字节、TXBTIE 寄存器未配置导致 TC 中断永不触发、FIFO 空判断使用了错误的标志位。

---

## 二、PDO 分布

### 2.1 当前 PDO 布局（EtherCAT SM2 输出 / SM3 输入）

每个 16 字节槽的结构：

```
字节偏移  字段          说明
  0~1    CAN_ID        目标 CAN FD 帧的标准 ID（0 = 该槽不使用）
  2      FRAME_TYPE    0=经典CAN  1=CANFD  2=CANFD+BRS
  3      DATA_LEN      实际数据字节数（0~12）
  4~15   DATA          数据载荷（最多 12 字节）
```

**TX PDO（SM2，0x7000~0x71BF，448 字节 = 4 通道 × 7 槽 × 16 字节）：**

| 通道 | PDO 起始地址 | 7 个槽的 EtherCAT 地址范围 | 对应 CAN 通道 |
|------|------------|--------------------------|-------------|
| Ch0  | 0x7000     | 0x7000~0x706F            | CAN0        |
| Ch1  | 0x7070     | 0x7070~0x70DF            | CAN1        |
| Ch2  | 0x70E0     | 0x70E0~0x714F            | CAN2        |
| Ch3  | 0x7150     | 0x7150~0x71BF            | CAN3        |

**RX PDO（SM3，0x6000~0x61BF，448 字节）：**

| 通道 | PDO 起始地址 | 7 个槽的 EtherCAT 地址范围 | 对应 CAN 通道 |
|------|------------|--------------------------|-------------|
| Ch0  | 0x6000     | 0x6000~0x606F            | CAN0        |
| Ch1  | 0x6070     | 0x6070~0x60DF            | CAN1        |
| Ch2  | 0x60E0     | 0x60E0~0x614F            | CAN2        |
| Ch3  | 0x6150     | 0x6150~0x61BF            | CAN3        |

### 2.2 APPL_OutputMapping 中的数据复制逻辑

```
ESC SM2 DPRAM 缓冲区 (448 字节)
    │
    ├─ [0:111]    → TxCanGroup110x7000 ~ TxCanGroup170x7060  (Ch0, 7 槽)
    │                                         can_app_trigger_transmit()
    ├─ [112:223]  → TxCanGroup210x7070 ~ TxCanGroup270x70D0  (Ch1, 7 槽)
    │                                         can_app_trigger_can1_transmit()
    ├─ [224:335]  → TxCanGroup310x70E0 ~ TxCanGroup370x7140  (Ch2, 7 槽)
    │                                         can_app_trigger_can2_transmit()
    └─ [336:447]  → TxCanGroup410x7150 ~ TxCanGroup470x71B0  (Ch3, 7 槽)
                                          can_app_trigger_can3_transmit()
```

```
RxCAN 通道数据（由 can_app_process_bus RX 路径写入）
    │
    ├─ RxCanGroup110x6000 ~ RxCanGroup170x6060  (Ch0)
    │                                         → [0:111]    → SM3 DPRAM → 主站
    ├─ RxCanGroup210x6070 ~ RxCanGroup270x60D0  (Ch1)
    │                                         → [112:223]  → SM3 DPRAM → 主站
    ├─ RxCanGroup310x60E0 ~ RxCanGroup370x6140  (Ch2)
    │                                         → [224:335]  → SM3 DPRAM → 主站
    └─ RxCanGroup410x6150 ~ RxCanGroup470x61B0  (Ch3)
                                              → [336:447]  → SM3 DPRAM → 主站
```

---

## 三、EtherCAT → CANFD 发送逻辑

### 3.1 完整数据流

```
EtherCAT 主站发 PDO
    ↓
ESC SM2 事件中断触发（PLIC level 5）
    ↓
ecatappl.c: PDO_OutputMapping()
    ├─ HW_EscReadIsr()  ← 从 ESC DPRAM 读取最新 PDO 数据
    └─ APPL_OutputMapping()
        ├─ MEMCPY → TxCanGroup* 缓冲区（4 通道并行复制）
        └─ can_app_trigger_*() × 4   ← 设置 s_bus_tx_pending[ch] = true
    ↓
主循环: can_app_process_bus(ch)
    ├─ 消费 s_bus_tx_pending[ch]
    ├─ can_app_read_tx_pdo()  ← 从 TxCanGroup* 读入本地 tx_buf
    ├─ 预填 TX FIFO（最多 4 帧，受 FIFO 深度限制）
    │   └─ tx_pipeline_feed_one() 每调用一次填入一帧
    │       ├─ 读取槽位 CAN_ID、FRAME_TYPE、DATA_LEN
    │       ├─ CAN_ID == 0 → 跳过（保留已学习的 RX 路由）
    │       ├─ 构造 mcan_tx_frame_t（std_id/canfd_frame/bitrate_switch/dlc/data）
    │       └─ hpm_can_transmit_nonblocking() → MCAN TXBAR 触发发送
    ├─ FIFO 满时启动 TC 中断（s_tx_pipeline[ch].active = true）
    ├─ 其余帧由 TC 中断驱动继续填充
    └─ 所有帧发送完毕且 TFFL==0 → 关闭 TC 中断
```

### 3.2 TX 流水线状态机

```
                ┌──────────────────────────────────────┐
                │         s_bus_tx_pending = true       │
                │      （APPL_OutputMapping 触发）       │
                └──────────────┬───────────────────────┘
                               ↓
                ┌──────────────────────────────────────┐
                │     主循环：预填 TX FIFO（最多 4 帧）   │
                │   tx_pipeline_feed_one() × N          │
                │   N = min(7, FIFO剩余深度)             │
                └──────────────┬───────────────────────┘
                               ↓
                    ┌──────────┴──────────┐
                    │                     │
              fed == 7（全填完）      fed < 7（FIFO满）
                    │                     │
              active=false            active=true
              无需中断                使能 TC 中断
                    │                     │
                    └──────────┬──────────┘
                               ↓
                ┌──────────────────────────────────────┐
                │     TC 中断：can_app_on_tx_complete()  │
                │  每帧发送完成后触发一次                  │
                │  清 IR.TC → 读新 PDO → 填 1 帧         │
                │  循环直到 all_slots_done && TFFL==0    │
                └──────────────┬───────────────────────┘
                               ↓
                    ┌──────────┴──────────┐
                    │                     │
              还有未处理slot            所有slot已处理
                    │               TFFL > 0（帧在途）
                    │                     │
              继续填充下一帧          保持 active=true
                    │               等下一帧发送完
                    │                     │
                    │               TFFL == 0
                    │                     │
                    │              active=false
                    │              关中断，等待下次触发
                    └─────────────────────┘
```

### 3.3 RX 反向路由逻辑

```
can_app_process_bus(ch) RX 路径：
    while can_receive_non_blocking():
        提取 received_can_id
        ↓
        查 s_slot_state[ch][i]：找到 last_can_id == received_can_id 的槽位
            │
            ├─ 找到 → can_app_write_rx_pdo_slot(ch, slot, data)
            │         → 更新 RxCanGroup[slot] → SM3 → 主站
            │
            └─ 未找到（CAN_ID 从未被发送过）→ 丢弃
```

**学习表（s_slot_state）的作用：** 每个槽位发送帧后记录其 CAN ID，接收时按 CAN ID 反查对应槽位写入 RX PDO，实现"发什么 ID 就回什么 ID"的自动路由。

---

## 四、基础原理

### 4.1 CAN FD 帧发送时序

单帧 CANFD（仲裁 1Mbps，数据 5Mbps，含 BRS 切换）：

```
仲裁阶段（~30 bits @ 1Mbps）→ BRS → 数据阶段（含 DLC 长度 @ 5Mbps）→ CRC/ACK
     ≈ 38μs                     ↑                    ≈ 80μs
                              单帧总耗时 ≈ 118μs
```

7 帧序列实测（以 can1：8B → 2B → 12B → 12B → 8B → 8B → 12B）：
- 单通道总计约 **622μs**，4 通道并发，最慢通道约 622μs < 2ms 周期预算

### 4.2 MCAN TX FIFO 架构

```
MCAN TX Buffer 配置（CANFD 模式）：
  NDTB = 8 个 dedicated buffer（一半）
  FIFO = 4 个 element（一半，用于 TX FIFO 模式）
                                    ┌──────────────────────────┐
                                    │  TX FIFO (FIFO 模式)      │
                                    │  深度 = 4 个元素           │
主循环预填 ──► │ [slot0][slot1][slot2][slot3] │ ──► 硬件自动发送（TXBAR触发）
中断驱动跟进 ──►│       ↑                    │
                │  TC中断→继续填充             │
                └──────────────────────────┘
```

**TC 中断触发链（Bosch MCAN 规范）：**

```
TX Buffer 发送完成
    ↓
TXBTIE 对应 bit == 1？   ← 必须软件显式配置，默认值为 0
    ↓ 是
IR.TC 位置 1
    ↓
MCAN IRQ 触发 → ISR 回调
```

---

## 五、核心代码解释

### 5.1 代码片段

**文件：`port/hpm_can.c` — TXBTIE 寄存器配置（根因修复）**

```c
// hpm_can_init_channel() 中，mcan_init() 之后添加：
/* 使能所有 TX Buffer 元素的 TC 中断标志生成。
 * MCAN 规定：仅当 TXBTIE 对应 bit=1 时，该 buffer 发送完成才会置位 IR.TC。
 * 若不设置，TC 中断永远不会触发，导致 FIFO 预填 4 帧后无法继续填充。 */
info->can_base->TXBTIE = 0xFFFFFFFFU;
```

**文件：`application/can_app.c` — FIFO 空判断修复**

```c
// 修复前（错误）：
bool txfifo_empty = (base != NULL && !(base->TXFQS & MCAN_TXFQS_TFQF_MASK));
// TFQF=0 仅表示"不满"，不等于"已空"，导致 all_slots_done 时提前关闭中断

// 修复后（正确）：
bool txfifo_empty = (base != NULL && MCAN_TXFQS_TFFL_GET(base->TXFQS) == 0);
// TFFL 是填充级别寄存器，== 0 才表示 FIFO 真正为空
```

**文件：`application/can_app.c` — TX 帧填充函数（核心逻辑）**

```c
static bool tx_pipeline_feed_one(uint32_t ch, const CHAR *tx_buf)
{
    uint8_t slot = s_tx_pipeline[ch].next_slot;
    if (slot >= SLOTS_PER_BUS) return false;

    uint32_t off = slot * MOTOR_FRAME_SIZE;
    uint16_t can_id = ((uint16_t)(uint8_t)tx_buf[off+0] << 8) |
                       ((uint16_t)(uint8_t)tx_buf[off+1]);

    if (can_id == 0) {
        /* 主站未配置此槽：跳过发送，但 PRESERVE 已学习的 CAN ID，
         * 保证 RX 路由在空帧周期内继续保持有效 */
        s_tx_pipeline[ch].next_slot = slot + 1;
        return tx_pipeline_feed_one(ch, tx_buf);
    }

    uint8_t frame_type = tx_buf[off + FRAME_TYPE_OFFSET];
    uint8_t data_len   = tx_buf[off + FRAME_LEN_OFFSET];
    if (data_len > FRAME_DATA_MAX_LEN) data_len = FRAME_DATA_MAX_LEN;
    if (!s_canfd_enabled[ch] && data_len > 8) data_len = 8;  /* 经典 CAN 截断 */

    mcan_tx_frame_t tx_frame;
    memset(&tx_frame, 0, sizeof(tx_frame));
    tx_frame.std_id     = can_id & 0x7FF;
    tx_frame.dlc        = can_byte_count_to_dlc(data_len);
    tx_frame.canfd_frame = (frame_type != MOTOR_FRAME_TYPE_CAN);
    tx_frame.bitrate_switch = (frame_type == MOTOR_FRAME_TYPE_CANFD_BRS);
    if (data_len > 0)
        memcpy(tx_frame.data_8, &tx_buf[off + FRAME_DATA_OFFSET], data_len);

    if (hpm_can_transmit_nonblocking(ch, &tx_frame) != status_success)
        return false;  /* FIFO 满，等待 TC 中断 */

    s_slot_state[ch][slot].active    = true;
    s_slot_state[ch][slot].last_can_id = can_id;

    s_tx_pipeline[ch].next_slot = slot + 1;
    return true;
}
```

**文件：`application/can_app.c` — TC 中断处理函数**

```c
void can_app_on_tx_complete(uint32_t ch)
{
    if (ch >= CAN_BUS_COUNT || !s_tx_pipeline[ch].active) return;

    hpm_can_clear_tx_completed_flag(ch);   /* 向 IR 写 1 清除 TC 标志 */

    CHAR tx_buf[PDO_BUFFER_SIZE];
    can_app_read_tx_pdo(ch, tx_buf);

    bool fed_any = false, all_slots_done = false;
    while (s_tx_pipeline[ch].pending) {
        if (s_tx_pipeline[ch].next_slot >= SLOTS_PER_BUS) {
            all_slots_done = true; break;
        }
        if (!tx_pipeline_feed_one(ch, tx_buf)) break;  /* FIFO 满 */
        fed_any = true;
    }

    if (!fed_any && !all_slots_done) return;  /* FIFO 满，等下次 TC */

    MCAN_Type *base = hpm_can_get_base(ch);
    bool txfifo_empty = (base != NULL && MCAN_TXFQS_TFFL_GET(base->TXFQS) == 0);

    if (all_slots_done && txfifo_empty) {
        s_tx_pipeline[ch].active  = false;
        s_tx_pipeline[ch].pending = false;
        hpm_can_disable_all_irq(ch);
    }
    /* else: 保持 active，等下次 TC 继续填充 */
}
```

### 5.2 设计决策说明

| 决策点 | 选择 | 原因 |
|--------|------|------|
| 非阻塞 TX + TC 中断驱动 vs 阻塞式轮询发送 | 非阻塞流水线 | 7 帧阻塞发送约 4.46ms，超出 2ms 周期预算；流水线模式将主循环 CPU 阻塞降至 <0.2ms |
| TC 中断 vs TXE/FIFO 空中断 | TC（发送完成）中断 | 每帧发送完成后触发一次，正好驱动下一帧填充，语义清晰 |
| CAN_ID == 0 的槽位处理 | 跳过发送，保留已学习的 CAN ID | 主站不配置某槽时不发送，但 RX 路由表不重置，避免跨周期路由丢失 |
| TXFQS.TFFL vs TXFQS.TFQF 判断 FIFO 空 | TFFL == 0 | TFQF 是"满"标志，TFQF=0 仅表示不满，不表示已空；TFFL 才是填充级别 |
| 4 通道独立流水线 vs 共享流水线 | 独立 | 各通道 CAN ID、帧数、FIFO 状态完全独立，共享会引入锁竞争 |

---

## 六、调测效果

### 6.1 测试环境

| 项目 | 内容 |
|------|------|
| 硬件平台 | HPM5E00（HPM5E31）评估板 + ZLG USBCANFD-200U 适配器 |
| 软件版本 | V1.0，HPM SDK，ThreadX RTOS |
| EtherCAT 主站 | TwinCAT 3 |
| CAN 抓包工具 | `candump -t a any`（Linux SocketCAN，微秒级时间戳） |

### 6.2 关键指标数据

| 指标 | 目标值 | 实测值 | 是否达标 | 备注 |
|------|--------|--------|---------|------|
| CANFD 帧数据长度（12B） | 12 字节 | 12 字节 | ✅ | 修复截断 Bug 后验证通过 |
| 每通道发送帧数 | 7 帧 | 7 帧 | ✅ | 修复 TXBTIE + TFFL 判断后验证通过 |
| TX 流水线完整度 | 全部 7 帧 | 全部 7 帧 | ✅ | candump 观察 4 通道均发出 7 帧 |
| 4 通道并发发送完成时间 | <2ms | ~622μs | ✅ | 最慢通道决定总时长 |
| 主循环阻塞时间 | <0.5ms | <0.2ms | ✅ | 非阻塞流水线实现 |

### 6.3 调测关键日志

```
// 修复 TXBTIE 前（异常现象）：
candump -t a any
(1722567890.123456) can1  021   [8]  15 15 15 15 15 15 15 15
(1722567890.123510) can1  023   [8]  17 17 17 17 17 17 17 17
(1722567890.123564) can1  024   [8]  18 18 18 18 18 18 18 18
(1722567890.123618) can1  025   [2]  19 19
// ← 仅 4 帧，后续帧丢失（TC 中断未触发）

// 修复 TXBTIE 后（正常现象）：
(1722567890.200000) can1  021   [8]  15 15 15 15 15 15 15 15
(1722567890.200080) can1  023   [8]  17 17 17 17 17 17 17 17
(1722567890.200160) can1  024   [8]  18 18 18 18 18 18 18 18
(1722567890.200240) can1  025   [2]  19 19
(1722567890.200310) can1  026  [12]  1A 1A 1A 1A 1A 1A 1A 1A 1A 1A 1A 1A
(1722567890.200420) can1  027  [12]  1B 1B 1B 1B 1B 1B 1B 1B 1B 1B 1B 1B
(1722567890.200530) can1  021   [8]  15 15 15 15 15 15 15 15
// ← 7 帧全部发出，间隔均匀（~80~110μs/帧）
```

### 6.4 问题与对策

| 问题 | 根因分析 | 解决方案 |
|------|---------|---------|
| CANFD 帧被截断为 8 字节 | `can_app_init_receive_common()` 未设置 `s_canfd_enabled[ch]`，TX 路径强制截断 | 初始化时补充 `s_canfd_enabled[ch] = enable_canfd` |
| 每通道仅发出前 4 帧 | MCAN `TXBTIE` 寄存器默认为 0，TC 中断永不触发，FIFO 预填 4 帧后无法继续 | `hpm_can_init_channel()` 中 `mcan_init()` 后配置 `TXBTIE = 0xFFFFFFFFU` |
| TX 流水线提前终止 | `txfifo_empty` 使用 `TFQF`（满标志）而非 `TFFL`（填充级别）判断 | 改用 `MCAN_TXFQS_TFFL_GET(base->TXFQS) == 0` |

---

## 七、下周计划

1. **优化 RX 反向路由容错**：增强 `s_slot_state` 学习表在 CAN ID 变化时的更新逻辑，避免路由错位
2. **补充边界条件测试**：针对 `tx_pipeline_feed_one()` 增加测试用例（FIFO 满、channel 越界等）
3. **配合硬件组进行 EMC 测试**：确认 CANFD 5Mbps 数据速率下的信号完整性
4. **时序精化**：测量实际 TC 中断延迟，验证流水线调度对主循环周期的影响

---

## 八、风险与需要支持

| 风险 | 说明 |
|------|------|
| 4 通道并发 TC 中断优先级 | 4 个 MCAN TC 中断共享 PLIC level 3 优先级，若多个通道同时触发 TC 中断，可能存在抢占顺序不确定性。需后续实测验证 |
| FIFO 深度限制（4）vs 帧数（7） | 当前依赖 TC 中断填补剩余 3 帧，中断延迟累积可能影响总发送时间。建议在极端情况下测量最坏延迟 |

**需要的资源/支持：**
- 需要硬件组提供 CANFD 5Mbps 下的示波器波形，验证信号质量
