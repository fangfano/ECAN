/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "can_app.h"
#include "hpm_can.h"
#include "board.h"
#include "digital_io.h"

/***********************************************************************************************************************
 *
 *  Definitions
 *
 **********************************************************************************************************************/

typedef struct {
    volatile bool tx_active;      /* TX activity detected */
    volatile bool rx_active;      /* RX activity detected */
    volatile bool channel_initialized;  /* Channel initialized status */
    volatile uint32_t tx_last_tick;  /* Last TX activity timestamp */
    volatile uint32_t rx_last_tick;  /* Last RX activity timestamp */
} can_led_state_t;

/* Per-slot TX learning entry: which CAN ID was last sent on this slot.
 * RX frames are routed back to the slot whose learned CAN ID matches. */
typedef struct {
    bool active;              /* true once this slot has been TX-ed at least once */
    uint16_t last_can_id;     /* CAN ID learned from the most recent non-zero TX */
} slot_state_t;

/***********************************************************************************************************************
 *
 *  Constants
 *
 **********************************************************************************************************************/

#define MOTOR_FRAME_COUNT       7
#define MOTOR_FRAME_SIZE        16
#define SLOTS_PER_BUS           7    /* 7 motors per bus (no info slot) */
#define CAN_BUS_COUNT           4
#define PDO_BUFFER_SIZE         (SLOTS_PER_BUS * MOTOR_FRAME_SIZE)  /* 112 */

/* 16-byte PDO entry layout */
#define CAN_ID_HI_OFFSET        0
#define CAN_ID_LO_OFFSET        1
#define FRAME_TYPE_OFFSET       2
#define FRAME_LEN_OFFSET        3   /* actual data byte count to send/receive */
#define FRAME_DATA_OFFSET       4   /* data field starts at byte 4 */
#define FRAME_DATA_MAX_LEN      12  /* 16 - 4 = 12 bytes max payload in one entry */

#define MOTOR_FRAME_TYPE_CAN        0
#define MOTOR_FRAME_TYPE_CANFD      1
#define MOTOR_FRAME_TYPE_CANFD_BRS  2

/***********************************************************************************************************************
 *
 *  Variables
 *
 **********************************************************************************************************************/

static can_led_state_t s_can_led_state[4] = {0};
static volatile uint32_t s_timer_tick = 0;

/* TX learning table: per bus, per slot. Drives RX reverse-routing. */
static slot_state_t s_slot_state[CAN_BUS_COUNT][SLOTS_PER_BUS] = {0};

/* Bus-level TX pending flag, set by APPL_OutputMapping via trigger functions. */
static volatile bool s_bus_tx_pending[CAN_BUS_COUNT] = {false};

/* Per-channel init flags (kept for re-init guard). */
static bool s_can_initialized[CAN_BUS_COUNT] = {false};

/* 记录每个通道初始化时是否启用了 CANFD（用于 TX 路径对 classic CAN 做 8 字节截断） */
static bool s_canfd_enabled[CAN_BUS_COUNT] = {false};

/* PDO slot pointer tables. Each entry points to the 16-byte RxCan/TxCan object. */
static CHAR *const s_rx_pdo_ptrs[CAN_BUS_COUNT][SLOTS_PER_BUS] = {
    { RxCanGroup110x6000, RxCanGroup120x6010, RxCanGroup130x6020, RxCanGroup140x6030,
      RxCanGroup150x6040, RxCanGroup160x6050, RxCanGroup170x6060 },
    { RxCanGroup210x6070, RxCanGroup220x6080, RxCanGroup230x6090, RxCanGroup240x60A0,
      RxCanGroup250x60B0, RxCanGroup260x60C0, RxCanGroup270x60D0 },
    { RxCanGroup310x60E0, RxCanGroup320x60F0, RxCanGroup330x6100, RxCanGroup340x6110,
      RxCanGroup350x6120, RxCanGroup360x6130, RxCanGroup370x6140 },
    { RxCanGroup410x6150, RxCanGroup420x6160, RxCanGroup430x6170, RxCanGroup440x6180,
      RxCanGroup450x6190, RxCanGroup460x61A0, RxCanGroup470x61B0 },
};

static CHAR *const s_tx_pdo_ptrs[CAN_BUS_COUNT][SLOTS_PER_BUS] = {
    { TxCanGroup110x7000, TxCanGroup120x7010, TxCanGroup130x7020, TxCanGroup140x7030,
      TxCanGroup150x7040, TxCanGroup160x7050, TxCanGroup170x7060 },
    { TxCanGroup210x7070, TxCanGroup220x7080, TxCanGroup230x7090, TxCanGroup240x70A0,
      TxCanGroup250x70B0, TxCanGroup260x70C0, TxCanGroup270x70D0 },
    { TxCanGroup310x70E0, TxCanGroup320x70F0, TxCanGroup330x7100, TxCanGroup340x7110,
      TxCanGroup350x7120, TxCanGroup360x7130, TxCanGroup370x7140 },
    { TxCanGroup410x7150, TxCanGroup420x7160, TxCanGroup430x7170, TxCanGroup440x7180,
      TxCanGroup450x7190, TxCanGroup460x71A0, TxCanGroup470x71B0 },
};

/***********************************************************************************************************************
 *
 *  Triggers (called from APPL_OutputMapping)
 *
 **********************************************************************************************************************/

void can_app_trigger_transmit(void)
{
    s_bus_tx_pending[0] = true;
}

void can_app_trigger_can1_transmit(void)
{
    s_bus_tx_pending[1] = true;
}

void can_app_trigger_can2_transmit(void)
{
    s_bus_tx_pending[2] = true;
}

void can_app_trigger_can3_transmit(void)
{
    s_bus_tx_pending[3] = true;
}

/***********************************************************************************************************************
 *
 *  Internal Functions
 *
 **********************************************************************************************************************/

/* PDO buffer <-> ESC process data. Loops over the pointer tables. */
static void can_app_read_tx_pdo(uint32_t ch, CHAR *buf)
{
    for (uint8_t i = 0; i < SLOTS_PER_BUS; i++) {
        MEMCPY(&buf[i * MOTOR_FRAME_SIZE], s_tx_pdo_ptrs[ch][i], MOTOR_FRAME_SIZE);
    }
}

static void can_app_write_rx_pdo(uint32_t ch, const CHAR *buf)
{
    for (uint8_t i = 0; i < SLOTS_PER_BUS; i++) {
        MEMCPY(s_rx_pdo_ptrs[ch][i], &buf[i * MOTOR_FRAME_SIZE], MOTOR_FRAME_SIZE);
    }
}

static void can_app_clear_tx_pdo(uint32_t ch)
{
    for (uint8_t i = 0; i < SLOTS_PER_BUS; i++) {
        memset(s_tx_pdo_ptrs[ch][i], 0, MOTOR_FRAME_SIZE);
    }
}

/* Write a single 11-byte slot to RxPDO. Used by RX routing on each received frame. */
static void can_app_write_rx_pdo_slot(uint32_t ch, uint8_t slot, const CHAR *data11)
{
    if (ch < CAN_BUS_COUNT && slot < SLOTS_PER_BUS) {
        MEMCPY(s_rx_pdo_ptrs[ch][slot], data11, MOTOR_FRAME_SIZE);
    }
}

/* Unified non-blocking RX FIFO drain. Replaces the 4 channel-specific helpers. */
static hpm_stat_t can_receive_non_blocking(uint32_t ch, mcan_rx_message_t *rx_msg)
{
    MCAN_Type *can_base = hpm_can_get_base(ch);
    if (can_base == NULL) {
        return status_invalid_argument;
    }

    if (can_base->IR & MCAN_INT_RXFIFO0_NEW_MSG) {
        /* Clear the interrupt flag by reading IR */
        volatile uint32_t temp = can_base->IR;
        (void)temp;
        return hpm_can_receive(ch, rx_msg);
    }

    return status_fail;
}

/* CAN DLC (4-bit raw encoding) ↔ actual byte count conversion.
 * Valid CAN/CANFD data lengths: 0-8, 12, 16, 20, 24, 32, 48, 64. */
static uint8_t can_dlc_to_byte_count(uint8_t dlc)
{
    static const uint8_t dlc_table[16] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
    };
    return (dlc < 16) ? dlc_table[dlc] : 0;
}

static uint8_t can_byte_count_to_dlc(uint8_t bytes)
{
    if (bytes <= 8)  return bytes;
    if (bytes <= 12) return 9;
    if (bytes <= 16) return 10;
    if (bytes <= 20) return 11;
    if (bytes <= 24) return 12;
    if (bytes <= 32) return 13;
    if (bytes <= 48) return 14;
    return 15;
}

/**
 * @brief Timer callback for LED blinking
 */
static void led_blink_timer_callback(void)
{
    s_timer_tick++;

    /* Update TX LEDs */
    for (uint32_t i = 0; i < 4; i++) {
        if (s_can_led_state[i].tx_active) {
            if ((s_timer_tick - s_can_led_state[i].tx_last_tick) > CAN_LED_ACTIVITY_TIMEOUT_MS) {
                s_can_led_state[i].tx_active = false;
            }
        }

        if (s_can_led_state[i].tx_active) {
            bool led_state = ((s_timer_tick % (CAN_LED_BLINK_PERIOD_US / 1000)) < (CAN_LED_BLINK_PERIOD_US / 2000));
            if (led_state) {
                board_can_tx_led_on(i);
            } else {
                board_can_tx_led_off(i);
            }
        } else if (s_can_led_state[i].channel_initialized) {
            board_can_tx_led_on(i);
        } else {
            board_can_tx_led_off(i);
        }
    }

    /* Update RX LEDs */
    for (uint32_t i = 0; i < 4; i++) {
        if (s_can_led_state[i].rx_active) {
            if ((s_timer_tick - s_can_led_state[i].rx_last_tick) > CAN_LED_ACTIVITY_TIMEOUT_MS) {
                s_can_led_state[i].rx_active = false;
            }
        }

        if (s_can_led_state[i].rx_active) {
            bool led_state = ((s_timer_tick % (CAN_LED_BLINK_PERIOD_US / 1000)) < (CAN_LED_BLINK_PERIOD_US / 2000));
            if (led_state) {
                board_can_rx_led_on(i);
            } else {
                board_can_rx_led_off(i);
            }
        } else {
            if (s_can_led_state[i].channel_initialized) {
                board_can_rx_led_off(i);
            } else {
                board_can_rx_led_on(i);
            }
        }
    }
}

/***********************************************************************************************************************
 *
 *  Public Functions
 *
 **********************************************************************************************************************/

void can_app_init(void)
{
    board_init_can_led_pins();
    board_timer_create(1, led_blink_timer_callback);
    hpm_can_init_all_channels();
}

/* Common RX-channel initializer. ch0/1 enable CANFD, ch2/3 disable. */
static hpm_stat_t can_app_init_receive_common(uint32_t ch, bool enable_canfd)
{
    mcan_config_t can_config;
    hpm_stat_t status;
    mcan_filter_elem_t std_id_filter;
    mcan_filter_elem_t ext_id_filter;

    if (s_can_initialized[ch]) {
        printf("CAN%u already initialized\n", ch);
        return status_success;
    }

    printf("Initializing CAN%u for continuous receive...\n", ch);

    std_id_filter.filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER;
    std_id_filter.filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    std_id_filter.can_id_type = MCAN_CAN_ID_TYPE_STANDARD;
    std_id_filter.filter_id = 0;
    std_id_filter.filter_mask = 0x7FF;

    ext_id_filter.filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER;
    ext_id_filter.filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
    ext_id_filter.can_id_type = MCAN_CAN_ID_TYPE_EXTENDED;
    ext_id_filter.filter_id = 0;
    ext_id_filter.filter_mask = 0x1FFFFFFF;

    hpm_can_get_default_config(&can_config, enable_canfd);

    printf("CAN%u baudrate: %u bps\n", ch, can_config.baudrate);
    printf("CAN%u FD mode: %s\n", ch, can_config.enable_canfd ? "enabled" : "disabled");

    can_config.all_filters_config.std_id_filter_list.filter_elem_list = &std_id_filter;
    can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.ext_id_filter_list.filter_elem_list = &ext_id_filter;
    can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
    can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;

    printf("CAN%u filters configured to accept all messages\n", ch);

    status = hpm_can_init_channel(ch, &can_config);
    if (status != status_success) {
        printf("CAN%u initialization failed, error code: %d\n", ch, status);
        return status;
    }

    s_can_led_state[ch].channel_initialized = true;
    s_can_initialized[ch] = true;
    s_canfd_enabled[ch] = enable_canfd;       /* 记录 CANFD 模式供 TX 路径使用
                                               * 必须在此设置：transmit_common 会因
                                               * s_can_initialized 已置位而提前返回，
                                               * 导致此处遗漏会使 TX 路径误将 CANFD
                                               * 帧截断到 8 字节 */

    CHAR init_buf[PDO_BUFFER_SIZE] = {0};
    can_app_write_rx_pdo(ch, init_buf);

    printf("CAN%u initialized successfully for continuous receive\n", ch);
    printf("Waiting for CAN messages on CAN%u...\n", ch);
    return status;
}

/* Common TX-channel initializer. ch0/1 enable CANFD, ch2/3 disable. */
static hpm_stat_t can_app_init_transmit_common(uint32_t ch, bool enable_canfd)
{
    mcan_config_t can_config;
    hpm_stat_t status;

    if (s_can_initialized[ch]) {
        printf("CAN%u already initialized for transmit mode\n", ch);
        return status_success;
    }

    printf("Initializing CAN%u for transmit mode...\n", ch);

    hpm_can_get_default_config(&can_config, enable_canfd);

    printf("CAN%u baudrate: %u bps\n", ch, can_config.baudrate);
    printf("CAN%u FD mode: %s\n", ch, can_config.enable_canfd ? "enabled" : "disabled");
    printf("CAN%u FD data baudrate: %u bps\n", ch, can_config.baudrate_fd);

    status = hpm_can_init_channel(ch, &can_config);
    if (status != status_success) {
        printf("CAN%u initialization failed for transmit mode, error code: %d\n", ch, status);
        return status;
    }

    s_can_led_state[ch].channel_initialized = true;
    s_can_initialized[ch] = true;
    s_canfd_enabled[ch] = enable_canfd;       /* 记录 CANFD 模式供 TX 路径使用 */

    can_app_clear_tx_pdo(ch);

    printf("CAN%u initialized successfully for transmit mode\n", ch);
    return status_success;
}

hpm_stat_t can_app_init_can0_receive(void)  { return can_app_init_receive_common(0, true);  }
hpm_stat_t can_app_init_can1_receive(void)  { return can_app_init_receive_common(1, true);  }
hpm_stat_t can_app_init_can2_receive(void)  { return can_app_init_receive_common(2, true); }
hpm_stat_t can_app_init_can3_receive(void)  { return can_app_init_receive_common(3, true); }

hpm_stat_t can_app_init_can0_transmit(void) { return can_app_init_transmit_common(0, true);  }
hpm_stat_t can_app_init_can1_transmit(void) { return can_app_init_transmit_common(1, true);  }
hpm_stat_t can_app_init_can2_transmit(void) { return can_app_init_transmit_common(2, true); }
hpm_stat_t can_app_init_can3_transmit(void) { return can_app_init_transmit_common(3, true); }

/**
 * @brief Unified per-bus TX+RX processor.
 *
 * TX: When APPL_OutputMapping triggers this bus, scan all 7 slots. For each
 *     slot whose CAN ID field (first 2 bytes of the 11-byte entry) is non-zero,
 *     send the CANFD frame and remember the slot->CAN_ID mapping. Slots with
 *     CAN ID == 0 are skipped WITHOUT clearing the learned CAN ID, so RX
 *     routing for previously-commanded motors keeps working.
 *
 * RX: Drain the FIFO. For each received frame, look up the slot whose learned
 *     CAN ID matches and write the 11-byte status into that slot's RxPDO. If
 *     no slot has ever been TX-ed with that CAN ID, discard the frame.
 *
 * The 4 CAN channels are independent; calling this for ch=0..3 each main-loop
 * iteration gives concurrent TX/RX across buses.
 */
void can_app_process_bus(uint32_t ch)
{
    if (ch >= CAN_BUS_COUNT) {
        return;
    }
    if (!s_can_initialized[ch]) {
        return;
    }

    /* === TX: trigger-driven scan of non-zero-ID slots === */
    if (s_bus_tx_pending[ch]) {
        s_bus_tx_pending[ch] = false;

        CHAR tx_buf[PDO_BUFFER_SIZE];
        can_app_read_tx_pdo(ch, tx_buf);

        for (uint8_t slot = 0; slot < SLOTS_PER_BUS; slot++) {
            uint32_t off = slot * MOTOR_FRAME_SIZE;
            uint16_t can_id = ((uint16_t)(uint8_t)tx_buf[off + 0] << 8) |
                              ((uint16_t)(uint8_t)tx_buf[off + 1]);

            if (can_id == 0) {
                /* Master didn't populate this slot. Skip TX but PRESERVE the
                 * previously learned CAN ID so RX routing for that motor keeps
                 * working across cycles where the master writes 0 here. */
                continue;
            }

            uint8_t frame_type = (uint8_t)tx_buf[off + FRAME_TYPE_OFFSET];
            uint8_t data_len   = (uint8_t)tx_buf[off + FRAME_LEN_OFFSET];

            if (data_len > FRAME_DATA_MAX_LEN) {
                data_len = FRAME_DATA_MAX_LEN;
            }
            /* Classic CAN 通道（未启用 CANFD）单帧最多 8 字节数据，
             * 超过会被硬件拒绝；此处截断到 8 字节以保证发送成功。 */
            if (!s_canfd_enabled[ch] && data_len > 8) {
                data_len = 8;
            }

            mcan_tx_frame_t tx_frame;
            memset(&tx_frame, 0, sizeof(tx_frame));
            tx_frame.std_id = can_id & 0x7FF;
            tx_frame.use_ext_id = 0;
            tx_frame.dlc = can_byte_count_to_dlc(data_len);

            if (frame_type == MOTOR_FRAME_TYPE_CAN) {
                tx_frame.canfd_frame = 0;
                tx_frame.bitrate_switch = 0;
            } else if (frame_type == MOTOR_FRAME_TYPE_CANFD) {
                tx_frame.canfd_frame = 1;
                tx_frame.bitrate_switch = 0;
            } else {
                tx_frame.canfd_frame = 1;
                tx_frame.bitrate_switch = 1;
            }

            if (data_len > 0) {
                memcpy(tx_frame.data_8, &tx_buf[off + FRAME_DATA_OFFSET], data_len);
            }
            hpm_can_transmit(ch, &tx_frame);

            /* Learn slot -> CAN ID for RX reverse-routing. */
            s_slot_state[ch][slot].active = true;
            s_slot_state[ch][slot].last_can_id = can_id;

            s_can_led_state[ch].tx_active = true;
            s_can_led_state[ch].tx_last_tick = s_timer_tick;
        }
    }

    /* === RX: drain FIFO, route each frame by learned CAN ID === */
    mcan_rx_message_t rx_msg;
    while (can_receive_non_blocking(ch, &rx_msg) == status_success) {
        uint16_t can_id = rx_msg.use_ext_id
                          ? (uint16_t)(rx_msg.ext_id & 0x7FF)
                          : (uint16_t)(rx_msg.std_id & 0x7FF);

        /* Find the slot whose last TX used this CAN ID. */
        int8_t slot = -1;
        for (uint8_t i = 0; i < SLOTS_PER_BUS; i++) {
            if (s_slot_state[ch][i].active && s_slot_state[ch][i].last_can_id == can_id) {
                slot = (int8_t)i;
                break;
            }
        }

        if (slot < 0) {
            /* No slot has ever been TX-ed with this ID: discard (no routing target). */
            continue;
        }

        uint8_t frame_type = MOTOR_FRAME_TYPE_CAN;
        if (rx_msg.canfd_frame) {
            frame_type = rx_msg.bitrate_switch ? MOTOR_FRAME_TYPE_CANFD_BRS : MOTOR_FRAME_TYPE_CANFD;
        }

        uint8_t data_len = can_dlc_to_byte_count((uint8_t)rx_msg.dlc);
        if (data_len > FRAME_DATA_MAX_LEN) {
            data_len = FRAME_DATA_MAX_LEN;
        }

        CHAR data16[MOTOR_FRAME_SIZE];
        memset(data16, 0, sizeof(data16));
        data16[CAN_ID_HI_OFFSET]  = (CHAR)((can_id >> 8) & 0xFF);
        data16[CAN_ID_LO_OFFSET]  = (CHAR)(can_id & 0xFF);
        data16[FRAME_TYPE_OFFSET] = (CHAR)frame_type;
        data16[FRAME_LEN_OFFSET]  = (CHAR)data_len;
        if (data_len > 0) {
            memcpy(&data16[FRAME_DATA_OFFSET], rx_msg.data_8, data_len);
        }

        can_app_write_rx_pdo_slot(ch, (uint8_t)slot, data16);

        s_can_led_state[ch].rx_active = true;
        s_can_led_state[ch].rx_last_tick = s_timer_tick;
    }
}
