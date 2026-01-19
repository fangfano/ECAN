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

typedef struct {
    uint8_t buffer[30];  /* 30 bytes buffer for CAN message data (ECAT process data size) */
    volatile uint32_t new_data_flag;  /* Flag indicating new data available */
    volatile uint32_t message_count;  /* Total received message count */
    volatile uint32_t last_id;  /* Last received CAN ID */
    volatile uint8_t last_dlc;  /* Last received DLC */
    volatile uint32_t overflow_size;  /* Number of bytes that overflowed to next buffer (limited to total 75 bytes) */
} can0_rx_data_t;

/***********************************************************************************************************************
 *
 *  Variables
 *
 **********************************************************************************************************************/

static can_led_state_t s_can_led_state[4] = {0};
static volatile uint32_t s_timer_tick = 0;
static can0_rx_data_t s_can0_rx_data = {0};
static can0_rx_data_t s_can1_rx_data = {0};
static can0_rx_data_t s_can2_rx_data = {0};
static can0_rx_data_t s_can3_rx_data = {0};
static bool s_can0_receive_initialized = false;
static bool s_can0_transmit_initialized = false;
static bool s_can1_receive_initialized = false;
static bool s_can1_transmit_initialized = false;
static bool s_can2_receive_initialized = false;
static bool s_can2_transmit_initialized = false;
static bool s_can3_receive_initialized = false;
static bool s_can3_transmit_initialized = false;
static volatile uint32_t s_txcan0_transmit_pending = 0;
static volatile uint32_t s_txcan1_transmit_pending = 0;
static volatile uint32_t s_txcan2_transmit_pending = 0;
static volatile uint32_t s_txcan3_transmit_pending = 0;

void can_app_trigger_transmit(void)
{
    s_txcan0_transmit_pending = 1;
}

void can_app_trigger_can1_transmit(void)
{
    s_txcan1_transmit_pending = 1;
}

void can_app_trigger_can2_transmit(void)
{
    s_txcan2_transmit_pending = 1;
}

void can_app_trigger_can3_transmit(void)
{
    s_txcan3_transmit_pending = 1;
}

/***********************************************************************************************************************
 *
 *  Internal Functions
 *
 **********************************************************************************************************************/

/**
 * @brief Non-blocking check if CAN0 has data in RX FIFO
 *
 * @param rx_msg Pointer to receive message structure
 * @return hpm_stat_t status_success if data available, status_fail if no data
 */
static hpm_stat_t can0_receive_non_blocking(mcan_rx_message_t *rx_msg)
{
    MCAN_Type *can_base = hpm_can_get_base(0);
    if (can_base == NULL) {
        return status_invalid_argument;
    }

    /* Check RX FIFO 0 status register to see if there are messages */
    uint32_t ir_status = can_base->IR;

    /* Check if there's a new message in RX FIFO 0 */
    if (ir_status & MCAN_INT_RXFIFO0_NEW_MSG) {
        /* Clear the interrupt flag by reading IR */
        volatile uint32_t temp = can_base->IR;
        (void)temp;

        /* Now try to receive the message */
        return hpm_can_receive(0, rx_msg);
    }

    return status_fail;
}

static hpm_stat_t can1_receive_non_blocking(mcan_rx_message_t *rx_msg)
{
    MCAN_Type *can_base = hpm_can_get_base(1);
    if (can_base == NULL) {
        return status_invalid_argument;
    }

    /* Check RX FIFO 0 status register to see if there are messages */
    uint32_t ir_status = can_base->IR;

    /* Check if there's a new message in RX FIFO 0 */
    if (ir_status & MCAN_INT_RXFIFO0_NEW_MSG) {
        /* Clear the interrupt flag by reading IR */
        volatile uint32_t temp = can_base->IR;
        (void)temp;

        /* Now try to receive the message */
        return hpm_can_receive(1, rx_msg);
    }

    return status_fail;
}

static hpm_stat_t can2_receive_non_blocking(mcan_rx_message_t *rx_msg)
{
    MCAN_Type *can_base = hpm_can_get_base(2);
    if (can_base == NULL) {
        return status_invalid_argument;
    }

    /* Check RX FIFO 0 status register to see if there are messages */
    uint32_t ir_status = can_base->IR;

    /* Check if there's a new message in RX FIFO 0 */
    if (ir_status & MCAN_INT_RXFIFO0_NEW_MSG) {
        /* Clear the interrupt flag by reading IR */
        volatile uint32_t temp = can_base->IR;
        (void)temp;

        /* Now try to receive the message */
        return hpm_can_receive(2, rx_msg);
    }

    return status_fail;
}

static hpm_stat_t can3_receive_non_blocking(mcan_rx_message_t *rx_msg)
{
    MCAN_Type *can_base = hpm_can_get_base(3);
    if (can_base == NULL) {
        return status_invalid_argument;
    }

    /* Check RX FIFO 0 status register to see if there are messages */
    uint32_t ir_status = can_base->IR;

    /* Check if there's a new message in RX FIFO 0 */
    if (ir_status & MCAN_INT_RXFIFO0_NEW_MSG) {
        /* Clear the interrupt flag by reading IR */
        volatile uint32_t temp = can_base->IR;
        (void)temp;

        /* Now try to receive the message */
        return hpm_can_receive(3, rx_msg);
    }

    return status_fail;
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







hpm_stat_t can_app_init_can0_receive(void)
{
    mcan_config_t can_config;
    hpm_stat_t status;
    mcan_filter_elem_t std_id_filter;
    mcan_filter_elem_t ext_id_filter;

    if (s_can0_receive_initialized) {
        printf("CAN0 already initialized for receive mode\n");
        return status_success;
    }

    printf("Initializing CAN0 for continuous receive...\n");

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

    hpm_can_get_default_config(&can_config, true);

    printf("CAN0 baudrate: %u bps\n", can_config.baudrate);
    printf("CAN0 FD mode: %s\n", can_config.enable_canfd ? "enabled" : "disabled");

    can_config.all_filters_config.std_id_filter_list.filter_elem_list = &std_id_filter;
    can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.ext_id_filter_list.filter_elem_list = &ext_id_filter;
    can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
    can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;

    printf("CAN0 filters configured to accept all messages\n");

    status = hpm_can_init_channel(0, &can_config);
    if (status != status_success) {
        printf("CAN0 initialization failed, error code: %d\n", status);
        return status;
    }

    s_can_led_state[0].channel_initialized = true;
    s_can0_receive_initialized = true;
    memset(&s_can0_rx_data, 0, sizeof(s_can0_rx_data));

    printf("CAN0 initialized successfully for continuous receive\n");
    printf("Waiting for CAN messages on CAN0...\n");
    return status_success;
}

void can_app_process_can0_receive(void)
{
    mcan_rx_message_t rx_msg;
    hpm_stat_t status;

    if (!s_can0_receive_initialized) {
        return;
    }

    status = can0_receive_non_blocking(&rx_msg);

    if (status == status_success) {
        s_can_led_state[0].rx_active = true;
        s_can_led_state[0].rx_last_tick = s_timer_tick;

        s_can0_rx_data.message_count++;

        uint32_t can_id;
        if (rx_msg.use_ext_id) {
            s_can0_rx_data.last_id = rx_msg.ext_id;
            can_id = rx_msg.ext_id;
        } else {
            s_can0_rx_data.last_id = rx_msg.std_id;
            can_id = rx_msg.std_id;
        }
        s_can0_rx_data.last_dlc = rx_msg.dlc;

        extern CHAR RxCan00x6000[30];
        extern CHAR RxCan10x601E[30];
        extern CHAR RxCan20x603C[30];

        /* Clear RxCan0 completely */
        memset(&RxCan00x6000, 0, sizeof(RxCan00x6000));
        memset(&RxCan10x601E, 0, sizeof(RxCan10x601E));
        memset(&RxCan20x603C[0], 0, 15);

        /* Layout: [0-3]=ID, [4]=DLC, [5-29]=data (25 bytes) in RxCan0 */
        RxCan00x6000[0] = (can_id >> 24) & 0xFF;
        RxCan00x6000[1] = (can_id >> 16) & 0xFF;
        RxCan00x6000[2] = (can_id >> 8) & 0xFF;
        RxCan00x6000[3] = can_id & 0xFF;
        RxCan00x6000[4] = rx_msg.dlc;

        uint32_t msg_len = mcan_get_message_size_from_dlc(rx_msg.dlc);
        uint32_t data_available_in_rxcan0 = 25; /* Bytes 5-29 in RxCan0 */

        uint32_t copy_len_0 = (msg_len > data_available_in_rxcan0) ? data_available_in_rxcan0 : msg_len;
        for (uint32_t i = 0; i < copy_len_0; i++) {
            RxCan00x6000[5 + i] = rx_msg.data_8[i];
        }

        if (msg_len > data_available_in_rxcan0) {
            uint32_t overflow_len_0 = msg_len - data_available_in_rxcan0;
            s_can0_rx_data.overflow_size = overflow_len_0;

            /* Copy remaining data to RxCan1 (30 bytes) */
            uint32_t copy_len_1 = (overflow_len_0 > 30) ? 30 : overflow_len_0;
            for (uint32_t i = 0; i < copy_len_1; i++) {
                RxCan10x601E[i] = rx_msg.data_8[data_available_in_rxcan0 + i];
            }

            if (overflow_len_0 > 30) {
                uint32_t overflow_len_1 = overflow_len_0 - 30;

                /* Copy remaining data to RxCan2[0-14] (15 bytes) */
                uint32_t copy_len_2 = (overflow_len_1 > 15) ? 15 : overflow_len_1;
                for (uint32_t i = 0; i < copy_len_2; i++) {
                    RxCan20x603C[i] = rx_msg.data_8[data_available_in_rxcan0 + 30 + i];
                }

                /* Remaining overflow beyond 75 bytes is discarded */
                if (overflow_len_1 > 15) {
                    uint32_t discard_len = overflow_len_1 - 15;
                    (void)discard_len;
                }
            }
        }


        if (msg_len > 30) {
            uint32_t overflow_len_0 = msg_len - 30;
            s_can0_rx_data.overflow_size = overflow_len_0;

            /* Clear RxCan1 based on actual data that will be written */
            uint32_t copy_len_1 = (overflow_len_0 > 30) ? 30 : overflow_len_0;
            memset(&RxCan10x601E[0], 0, copy_len_1);
            for (uint32_t i = 0; i < copy_len_1; i++) {
                RxCan10x601E[i] = rx_msg.data_8[30 + i];
            }
            s_can1_rx_data.new_data_flag = 1;
            s_can1_rx_data.overflow_size = overflow_len_0 - copy_len_1;

            if (overflow_len_0 > 30) {
                uint32_t overflow_len_1 = overflow_len_0 - 30;

                /* Limit to 15 bytes for RxCan2 (total: 30 + 30 + 15 = 75 bytes) */
                uint32_t copy_len_2 = (overflow_len_1 > 15) ? 15 : overflow_len_1;
                /* Clear RxCan2[0-14] based on actual data that will be written */
                memset(&RxCan20x603C[0], 0, copy_len_2);
                for (uint32_t i = 0; i < copy_len_2; i++) {
                    RxCan20x603C[i] = rx_msg.data_8[60 + i];
                }
                s_can2_rx_data.new_data_flag = 1;
                s_can2_rx_data.overflow_size = overflow_len_1 - copy_len_2;

                /* Remaining overflow beyond 75 bytes is discarded */
                if (overflow_len_1 > 15) {
                    /* Discard data beyond 75 bytes (30 + 30 + 15) */
                    uint32_t discard_len = overflow_len_1 - 15;
                    (void)discard_len;
                }
            }
        }

        s_can0_rx_data.new_data_flag = 1;
    }
}

uint8_t *can_app_get_can0_rx_buffer(void)
{
    return s_can0_rx_data.buffer;
}

uint8_t *can_app_get_can1_rx_buffer(void)
{
    return s_can1_rx_data.buffer;
}

uint8_t *can_app_get_can2_rx_buffer(void)
{
    return s_can2_rx_data.buffer;
}

uint8_t *can_app_get_can3_rx_buffer(void)
{
    return s_can3_rx_data.buffer;
}

uint32_t can_app_get_can0_status(void)
{
    return (s_can0_rx_data.new_data_flag << 0) |
           (s_can0_rx_data.message_count << 1) |
           (s_can0_rx_data.last_id << 16);
}

void can_app_clear_can0_new_data_flag(void)
{
    s_can0_rx_data.new_data_flag = 0;
}


hpm_stat_t can_app_init_can0_transmit(void)
{
    mcan_config_t can_config;
    hpm_stat_t status;

    if (s_can0_transmit_initialized) {
        printf("CAN0 already initialized for transmit mode\n");
        return status_success;
    }

    printf("Initializing CAN0 for transmit mode (TxCan0 -> CAN0)...\n");

    hpm_can_get_default_config(&can_config, true);

    printf("CAN0 baudrate: %u bps\n", can_config.baudrate);
    printf("CAN0 FD mode: %s\n", can_config.enable_canfd ? "enabled" : "disabled");
    printf("CAN0 FD data baudrate: %u bps\n", can_config.baudrate_fd);

    status = hpm_can_init_channel(0, &can_config);
    if (status != status_success) {
        printf("CAN0 initialization failed for transmit mode, error code: %d\n", status);
        return status;
    }

    s_can_led_state[0].channel_initialized = true;
    s_can0_transmit_initialized = true;
    
    /* Initialize TxCan0, TxCan1, and TxCan2[0-14] (used by CAN0) */
    extern CHAR TxCan00x7000[30];
    extern CHAR TxCan10x701E[30];
    extern CHAR TxCan20x703C[30];
    memset(&TxCan00x7000, 0, sizeof(TxCan00x7000));
    memset(&TxCan10x701E, 0, sizeof(TxCan10x701E));
    memset(&TxCan20x703C[0], 0, 15);  // Only clear first 15 bytes, TxCan2[15-29] used by CAN1

    printf("CAN0 initialized successfully for transmit mode\n");
    printf("Ready to send TxCan0 data as CAN FD frames...\n");
    return status_success;
}

void can_app_process_txcan_transmit(void)
{
    mcan_tx_frame_t tx_frame;
    hpm_stat_t status;

    if (!s_can0_transmit_initialized) {
        return;
    }

    if (s_txcan0_transmit_pending == 0) {
        return;
    }

    s_txcan0_transmit_pending = 0;

    memset(&tx_frame, 0, sizeof(tx_frame));

    extern CHAR TxCan00x7000[30];
    extern CHAR TxCan10x701E[30];
    extern CHAR TxCan20x703C[30];

    /* Extract CAN ID from TxCan0[0-3] */
    uint32_t can_id = TxCan00x7000[0] |
                     ((uint32_t)TxCan00x7000[1] << 8) |
                     ((uint32_t)TxCan00x7000[2] << 16) |
                     ((uint32_t)TxCan00x7000[3] << 24);

    /* Extract DLC from TxCan0[4], limit to 15 (0x0F) */
    uint8_t dlc = TxCan00x7000[4];
    if (dlc > 15) {
        dlc = 15;
    }

    /* Determine if it's an extended frame (ID > 0x7FF) */
    if (can_id > 0x7FF) {
        tx_frame.ext_id = can_id;
        tx_frame.use_ext_id = 1;
    } else {
        tx_frame.std_id = can_id;
        tx_frame.use_ext_id = 0;
    }
    tx_frame.dlc = dlc;
    tx_frame.canfd_frame = 1;
    tx_frame.bitrate_switch = 1;

    /* Layout: [0-3]=ID, [4]=DLC, [5-29]=data (25 bytes) in TxCan0 */
    /* Combine data from TxCan0[5-29] (25 bytes) + TxCan1 (30 bytes) + TxCan2[0-14] (15 bytes) */
    memcpy(&tx_frame.data_8[0], &TxCan00x7000[5], 25);
    memcpy(&tx_frame.data_8[25], TxCan10x701E, 30);
    memcpy(&tx_frame.data_8[55], &TxCan20x703C[0], 15);

    status = hpm_can_transmit(0, &tx_frame);
    if (status == status_success) {
        s_can_led_state[0].tx_active = true;
        s_can_led_state[0].tx_last_tick = s_timer_tick;
    } else {
        printf("Failed to transmit CAN FD frame on CAN0, status: %d\n", status);
    }
}

hpm_stat_t can_app_init_can1_receive(void)
{
    mcan_config_t can_config;
    hpm_stat_t status;
    mcan_filter_elem_t std_id_filter;
    mcan_filter_elem_t ext_id_filter;

    if (s_can1_receive_initialized) {
        printf("CAN1 already initialized for receive mode\n");
        return status_success;
    }

    printf("Initializing CAN1 for continuous receive...\n");

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

    hpm_can_get_default_config(&can_config, true);

    printf("CAN1 baudrate: %u bps\n", can_config.baudrate);
    printf("CAN1 FD mode: %s\n", can_config.enable_canfd ? "enabled" : "disabled");

    can_config.all_filters_config.std_id_filter_list.filter_elem_list = &std_id_filter;
    can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.ext_id_filter_list.filter_elem_list = &ext_id_filter;
    can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
    can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;

    printf("CAN1 filters configured to accept all messages\n");

    status = hpm_can_init_channel(1, &can_config);
    if (status != status_success) {
        printf("CAN1 initialization failed, error code: %d\n", status);
        return status;
    }

    s_can_led_state[1].channel_initialized = true;
    s_can1_receive_initialized = true;

    printf("CAN1 initialized successfully for continuous receive\n");
    printf("Waiting for CAN messages on CAN1...\n");
    return status_success;
}

void can_app_process_can1_receive(void)
{
    mcan_rx_message_t rx_msg;
    hpm_stat_t status;

    if (!s_can1_receive_initialized) {
        return;
    }

    status = can1_receive_non_blocking(&rx_msg);

    if (status == status_success) {
        s_can_led_state[1].rx_active = true;
        s_can_led_state[1].rx_last_tick = s_timer_tick;

        extern CHAR RxCan20x603C[30];
        extern CHAR RxCan30x605A[30];
        extern CHAR RxCan40x6078[30];

        /* Clear RxCan2[15-29], RxCan3, RxCan4 */
        memset(&RxCan20x603C[15], 0, 15);
        memset(&RxCan30x605A, 0, sizeof(RxCan30x605A));
        memset(&RxCan40x6078, 0, sizeof(RxCan40x6078));

        uint32_t can_id;
        if (rx_msg.use_ext_id) {
            can_id = rx_msg.ext_id;
        } else {
            can_id = rx_msg.std_id;
        }

        /* Layout for CAN1: RxCan2[15-18]=ID, [19]=DLC, [20-29]=data (10 bytes), RxCan3[30], RxCan4[30] */
        RxCan20x603C[15] = (can_id >> 24) & 0xFF;
        RxCan20x603C[16] = (can_id >> 16) & 0xFF;
        RxCan20x603C[17] = (can_id >> 8) & 0xFF;
        RxCan20x603C[18] = can_id & 0xFF;
        RxCan20x603C[19] = rx_msg.dlc;

        uint32_t msg_len = mcan_get_message_size_from_dlc(rx_msg.dlc);
        uint32_t data_available_in_rxcan2 = 10; /* Bytes 20-29 in RxCan2 */

        uint32_t copy_len_0 = (msg_len > data_available_in_rxcan2) ? data_available_in_rxcan2 : msg_len;
        for (uint32_t i = 0; i < copy_len_0; i++) {
            RxCan20x603C[20 + i] = rx_msg.data_8[i];
        }

        if (msg_len > data_available_in_rxcan2) {
            uint32_t overflow_len_0 = msg_len - data_available_in_rxcan2;

            /* Copy remaining data to RxCan3 (30 bytes) */
            uint32_t copy_len_1 = (overflow_len_0 > 30) ? 30 : overflow_len_0;
            for (uint32_t i = 0; i < copy_len_1; i++) {
                RxCan30x605A[i] = rx_msg.data_8[data_available_in_rxcan2 + i];
            }

            if (overflow_len_0 > 30) {
                uint32_t overflow_len_1 = overflow_len_0 - 30;

                /* Copy remaining data to RxCan4 (30 bytes) */
                uint32_t copy_len_2 = (overflow_len_1 > 30) ? 30 : overflow_len_1;
                for (uint32_t i = 0; i < copy_len_2; i++) {
                    RxCan40x6078[i] = rx_msg.data_8[data_available_in_rxcan2 + 30 + i];
                }

                /* Remaining overflow beyond 75 bytes is discarded */
                if (overflow_len_1 > 30) {
                    uint32_t discard_len = overflow_len_1 - 30;
                    (void)discard_len;
                }
            }
        }
    }
}

hpm_stat_t can_app_init_can1_transmit(void)
{
    mcan_config_t can_config;
    hpm_stat_t status;

    if (s_can1_transmit_initialized) {
        printf("CAN1 already initialized for transmit mode\n");
        return status_success;
    }

    printf("Initializing CAN1 for transmit mode (TxCan4 -> CAN1)...\n");

    hpm_can_get_default_config(&can_config, true);

    printf("CAN1 baudrate: %u bps\n", can_config.baudrate);
    printf("CAN1 FD mode: %s\n", can_config.enable_canfd ? "enabled" : "disabled");
    printf("CAN1 FD data baudrate: %u bps\n", can_config.baudrate_fd);

    status = hpm_can_init_channel(1, &can_config);
    if (status != status_success) {
        printf("CAN1 initialization failed for transmit mode, error code: %d\n", status);
        return status;
    }

    s_can_led_state[1].channel_initialized = true;
    s_can1_transmit_initialized = true;

    /* Initialize TxCan2[15-29], TxCan3, and TxCan4 (used by CAN1) */
    extern CHAR TxCan20x703C[30];
    extern CHAR TxCan30x705A[30];
    extern CHAR TxCan40x7078[30];
    memset(&TxCan20x703C[15], 0, 15);  // Only clear last 15 bytes, TxCan2[0-14] used by CAN0
    memset(&TxCan30x705A, 0, sizeof(TxCan30x705A));
    memset(&TxCan40x7078, 0, sizeof(TxCan40x7078));

    printf("CAN1 initialized successfully for transmit mode\n");
    printf("Ready to send TxCan4 data as CAN FD frames...\n");
    return status_success;
}

void can_app_process_txcan1_transmit(void)
{
    mcan_tx_frame_t tx_frame;
    hpm_stat_t status;

    if (!s_can1_transmit_initialized) {
        return;
    }

    if (s_txcan1_transmit_pending == 0) {
        return;
    }

    s_txcan1_transmit_pending = 0;

    memset(&tx_frame, 0, sizeof(tx_frame));

    extern CHAR TxCan20x703C[30];
    extern CHAR TxCan30x705A[30];
    extern CHAR TxCan40x7078[30];

    /* Extract CAN ID from TxCan2[15-18] */
    uint32_t can_id = TxCan20x703C[15] |
                     ((uint32_t)TxCan20x703C[16] << 8) |
                     ((uint32_t)TxCan20x703C[17] << 16) |
                     ((uint32_t)TxCan20x703C[18] << 24);

    /* Extract DLC from TxCan2[19], limit to 15 (0x0F) */
    uint8_t dlc = TxCan20x703C[19];
    if (dlc > 15) {
        dlc = 15;
    }

    /* Determine if it's an extended frame (ID > 0x7FF) */
    if (can_id > 0x7FF) {
        tx_frame.ext_id = can_id;
        tx_frame.use_ext_id = 1;
    } else {
        tx_frame.std_id = can_id;
        tx_frame.use_ext_id = 0;
    }
    tx_frame.dlc = dlc;
    tx_frame.canfd_frame = 1;
    tx_frame.bitrate_switch = 1;

    /* Layout: TxCan2[15-18]=ID, [19]=DLC, [20-29]=data (10 bytes), TxCan3 (30), TxCan4 (30) */
    memcpy(&tx_frame.data_8[0], &TxCan20x703C[20], 10);
    memcpy(&tx_frame.data_8[10], TxCan30x705A, 30);
    memcpy(&tx_frame.data_8[40], TxCan40x7078, 30);

    status = hpm_can_transmit(1, &tx_frame);
    if (status == status_success) {
        s_can_led_state[1].tx_active = true;
        s_can_led_state[1].tx_last_tick = s_timer_tick;
    } else {
        printf("Failed to transmit CAN FD frame on CAN1, status: %d\n", status);
    }
}

hpm_stat_t can_app_init_can2_receive(void)
{
    mcan_config_t can_config;
    hpm_stat_t status;
    mcan_filter_elem_t std_id_filter;
    mcan_filter_elem_t ext_id_filter;

    if (s_can2_receive_initialized) {
        printf("CAN2 already initialized for receive mode\n");
        return status_success;
    }

    printf("Initializing CAN2 for continuous receive...\n");

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

    hpm_can_get_default_config(&can_config, true);

    printf("CAN2 baudrate: %u bps\n", can_config.baudrate);
    printf("CAN2 FD mode: %s\n", can_config.enable_canfd ? "enabled" : "disabled");

    can_config.all_filters_config.std_id_filter_list.filter_elem_list = &std_id_filter;
    can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.ext_id_filter_list.filter_elem_list = &ext_id_filter;
    can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
    can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;

    printf("CAN2 filters configured to accept all messages\n");

    status = hpm_can_init_channel(2, &can_config);
    if (status != status_success) {
        printf("CAN2 initialization failed, error code: %d\n", status);
        return status;
    }

    s_can_led_state[2].channel_initialized = true;
    s_can2_receive_initialized = true;

    printf("CAN2 initialized successfully for continuous receive\n");
    printf("Waiting for CAN messages on CAN2...\n");
    return status_success;
}

void can_app_process_can2_receive(void)
{
    mcan_rx_message_t rx_msg;
    hpm_stat_t status;

    if (!s_can2_receive_initialized) {
        return;
    }

    status = can2_receive_non_blocking(&rx_msg);

    if (status == status_success) {
        s_can_led_state[2].rx_active = true;
        s_can_led_state[2].rx_last_tick = s_timer_tick;

        extern CHAR RxCan50x6096[30];
        extern CHAR RxCan60x60B4[30];
        extern CHAR RxCan70x60D2[30];

        /* Clear RxCan5, RxCan6, RxCan7[0-14] */
        memset(&RxCan50x6096, 0, sizeof(RxCan50x6096));
        memset(&RxCan60x60B4, 0, sizeof(RxCan60x60B4));
        memset(&RxCan70x60D2[0], 0, 15);

        uint32_t can_id;
        if (rx_msg.use_ext_id) {
            can_id = rx_msg.ext_id;
        } else {
            can_id = rx_msg.std_id;
        }

        /* Layout for CAN2: RxCan5[0-3]=ID, [4]=DLC, [5-29]=data (25 bytes), RxCan6 (30), RxCan7[0-14] (15) */
        RxCan50x6096[0] = (can_id >> 24) & 0xFF;
        RxCan50x6096[1] = (can_id >> 16) & 0xFF;
        RxCan50x6096[2] = (can_id >> 8) & 0xFF;
        RxCan50x6096[3] = can_id & 0xFF;
        RxCan50x6096[4] = rx_msg.dlc;

        uint32_t msg_len = mcan_get_message_size_from_dlc(rx_msg.dlc);
        uint32_t data_available_in_rxcan5 = 25; /* Bytes 5-29 in RxCan5 */

        uint32_t copy_len_0 = (msg_len > data_available_in_rxcan5) ? data_available_in_rxcan5 : msg_len;
        for (uint32_t i = 0; i < copy_len_0; i++) {
            RxCan50x6096[5 + i] = rx_msg.data_8[i];
        }

        if (msg_len > data_available_in_rxcan5) {
            uint32_t overflow_len_0 = msg_len - data_available_in_rxcan5;

            /* Copy remaining data to RxCan6 (30 bytes) */
            uint32_t copy_len_1 = (overflow_len_0 > 30) ? 30 : overflow_len_0;
            for (uint32_t i = 0; i < copy_len_1; i++) {
                RxCan60x60B4[i] = rx_msg.data_8[data_available_in_rxcan5 + i];
            }

            if (overflow_len_0 > 30) {
                uint32_t overflow_len_1 = overflow_len_0 - 30;

                /* Copy remaining data to RxCan7[0-14] (15 bytes) */
                uint32_t copy_len_2 = (overflow_len_1 > 15) ? 15 : overflow_len_1;
                for (uint32_t i = 0; i < copy_len_2; i++) {
                    RxCan70x60D2[i] = rx_msg.data_8[data_available_in_rxcan5 + 30 + i];
                }

                /* Remaining overflow beyond 75 bytes is discarded */
                if (overflow_len_1 > 15) {
                    uint32_t discard_len = overflow_len_1 - 15;
                    (void)discard_len;
                }
            }
        }
    }
}

hpm_stat_t can_app_init_can2_transmit(void)
{
    mcan_config_t can_config;
    hpm_stat_t status;

    if (s_can2_transmit_initialized) {
        printf("CAN2 already initialized for transmit mode\n");
        return status_success;
    }

    printf("Initializing CAN2 for transmit mode (TxCan7 -> CAN2)...\n");

    hpm_can_get_default_config(&can_config, true);

    printf("CAN2 baudrate: %u bps\n", can_config.baudrate);
    printf("CAN2 FD mode: %s\n", can_config.enable_canfd ? "enabled" : "disabled");
    printf("CAN2 FD data baudrate: %u bps\n", can_config.baudrate_fd);

    status = hpm_can_init_channel(2, &can_config);
    if (status != status_success) {
        printf("CAN2 initialization failed for transmit mode, error code: %d\n", status);
        return status;
    }

    s_can_led_state[2].channel_initialized = true;
    s_can2_transmit_initialized = true;

    /* Initialize TxCan5, TxCan6, and TxCan7[0-14] (used by CAN2) */
    extern CHAR TxCan50x7096[30];
    extern CHAR TxCan60x70B4[30];
    extern CHAR TxCan70x70D2[30];
    memset(&TxCan50x7096, 0, sizeof(TxCan50x7096));
    memset(&TxCan60x70B4, 0, sizeof(TxCan60x70B4));
    memset(&TxCan70x70D2[0], 0, 15);  // Only clear first 15 bytes, TxCan7[15-29] used by CAN3

    printf("CAN2 initialized successfully for transmit mode\n");
    printf("Ready to send TxCan7 data as CAN FD frames...\n");
    return status_success;
}

void can_app_process_txcan2_transmit(void)
{
    mcan_tx_frame_t tx_frame;
    hpm_stat_t status;

    if (!s_can2_transmit_initialized) {
        return;
    }

    if (s_txcan2_transmit_pending == 0) {
        return;
    }

    s_txcan2_transmit_pending = 0;

    memset(&tx_frame, 0, sizeof(tx_frame));

    extern CHAR TxCan50x7096[30];
    extern CHAR TxCan60x70B4[30];
    extern CHAR TxCan70x70D2[30];

    /* Extract CAN ID from TxCan5[0-3] */
    uint32_t can_id = TxCan50x7096[0] |
                     ((uint32_t)TxCan50x7096[1] << 8) |
                     ((uint32_t)TxCan50x7096[2] << 16) |
                     ((uint32_t)TxCan50x7096[3] << 24);

    /* Extract DLC from TxCan5[4], limit to 15 (0x0F) */
    uint8_t dlc = TxCan50x7096[4];
    if (dlc > 15) {
        dlc = 15;
    }

    /* Determine if it's an extended frame (ID > 0x7FF) */
    if (can_id > 0x7FF) {
        tx_frame.ext_id = can_id;
        tx_frame.use_ext_id = 1;
    } else {
        tx_frame.std_id = can_id;
        tx_frame.use_ext_id = 0;
    }
    tx_frame.dlc = dlc;
    tx_frame.canfd_frame = 1;
    tx_frame.bitrate_switch = 1;

    /* Layout: TxCan5[0-3]=ID, [4]=DLC, [5-29]=data (25 bytes), TxCan6 (30), TxCan7[0-14] (15) */
    memcpy(&tx_frame.data_8[0], &TxCan50x7096[5], 25);
    memcpy(&tx_frame.data_8[25], TxCan60x70B4, 30);
    memcpy(&tx_frame.data_8[55], &TxCan70x70D2[0], 15);

    status = hpm_can_transmit(2, &tx_frame);
    if (status == status_success) {
        s_can_led_state[2].tx_active = true;
        s_can_led_state[2].tx_last_tick = s_timer_tick;
    } else {
        printf("Failed to transmit CAN FD frame on CAN2, status: %d\n", status);
    }
}

hpm_stat_t can_app_init_can3_receive(void)
{
    mcan_config_t can_config;
    hpm_stat_t status;
    mcan_filter_elem_t std_id_filter;
    mcan_filter_elem_t ext_id_filter;

    if (s_can3_receive_initialized) {
        printf("CAN3 already initialized for receive mode\n");
        return status_success;
    }

    printf("Initializing CAN3 for continuous receive...\n");

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

    hpm_can_get_default_config(&can_config, true);

    printf("CAN3 baudrate: %u bps\n", can_config.baudrate);
    printf("CAN3 FD mode: %s\n", can_config.enable_canfd ? "enabled" : "disabled");

    can_config.all_filters_config.std_id_filter_list.filter_elem_list = &std_id_filter;
    can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.ext_id_filter_list.filter_elem_list = &ext_id_filter;
    can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count = 1;
    can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
    can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option =
        MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;

    printf("CAN3 filters configured to accept all messages\n");

    status = hpm_can_init_channel(3, &can_config);
    if (status != status_success) {
        printf("CAN3 initialization failed, error code: %d\n", status);
        return status;
    }

    s_can_led_state[3].channel_initialized = true;
    s_can3_receive_initialized = true;

    printf("CAN3 initialized successfully for continuous receive\n");
    printf("Waiting for CAN messages on CAN3...\n");
    return status_success;
}

void can_app_process_can3_receive(void)
{
    mcan_rx_message_t rx_msg;
    hpm_stat_t status;

    if (!s_can3_receive_initialized) {
        return;
    }

    status = can3_receive_non_blocking(&rx_msg);

    if (status == status_success) {
        s_can_led_state[3].rx_active = true;
        s_can_led_state[3].rx_last_tick = s_timer_tick;

        extern CHAR RxCan70x60D2[30];
        extern CHAR RxCan80x60F0[30];
        extern CHAR RxCan90x610E[30];

        /* Clear RxCan7[15-29], RxCan8, RxCan9 */
        memset(&RxCan70x60D2[15], 0, 15);
        memset(&RxCan80x60F0, 0, sizeof(RxCan80x60F0));
        memset(&RxCan90x610E, 0, sizeof(RxCan90x610E));

        uint32_t can_id;
        if (rx_msg.use_ext_id) {
            can_id = rx_msg.ext_id;
        } else {
            can_id = rx_msg.std_id;
        }

        /* Layout for CAN3: RxCan7[15-18]=ID, [19]=DLC, [20-29]=data (10 bytes), RxCan8 (30), RxCan9 (30) */
        RxCan70x60D2[15] = (can_id >> 24) & 0xFF;
        RxCan70x60D2[16] = (can_id >> 16) & 0xFF;
        RxCan70x60D2[17] = (can_id >> 8) & 0xFF;
        RxCan70x60D2[18] = can_id & 0xFF;
        RxCan70x60D2[19] = rx_msg.dlc;

        uint32_t msg_len = mcan_get_message_size_from_dlc(rx_msg.dlc);
        uint32_t data_available_in_rxcan7 = 10; /* Bytes 20-29 in RxCan7 */

        uint32_t copy_len_0 = (msg_len > data_available_in_rxcan7) ? data_available_in_rxcan7 : msg_len;
        for (uint32_t i = 0; i < copy_len_0; i++) {
            RxCan70x60D2[20 + i] = rx_msg.data_8[i];
        }

        if (msg_len > data_available_in_rxcan7) {
            uint32_t overflow_len_0 = msg_len - data_available_in_rxcan7;

            /* Copy remaining data to RxCan8 (30 bytes) */
            uint32_t copy_len_1 = (overflow_len_0 > 30) ? 30 : overflow_len_0;
            for (uint32_t i = 0; i < copy_len_1; i++) {
                RxCan80x60F0[i] = rx_msg.data_8[data_available_in_rxcan7 + i];
            }

            if (overflow_len_0 > 30) {
                uint32_t overflow_len_1 = overflow_len_0 - 30;

                /* Copy remaining data to RxCan9 (30 bytes) */
                uint32_t copy_len_2 = (overflow_len_1 > 30) ? 30 : overflow_len_1;
                for (uint32_t i = 0; i < copy_len_2; i++) {
                    RxCan90x610E[i] = rx_msg.data_8[data_available_in_rxcan7 + 30 + i];
                }

                /* Remaining overflow beyond 75 bytes is discarded */
                if (overflow_len_1 > 30) {
                    uint32_t discard_len = overflow_len_1 - 30;
                    (void)discard_len;
                }
            }
        }
    }
}

hpm_stat_t can_app_init_can3_transmit(void)
{
    mcan_config_t can_config;
    hpm_stat_t status;

    if (s_can3_transmit_initialized) {
        printf("CAN3 already initialized for transmit mode\n");
        return status_success;
    }

    printf("Initializing CAN3 for transmit mode (TxCan10 -> CAN3)...\n");

    hpm_can_get_default_config(&can_config, true);

    printf("CAN3 baudrate: %u bps\n", can_config.baudrate);
    printf("CAN3 FD mode: %s\n", can_config.enable_canfd ? "enabled" : "disabled");
    printf("CAN3 FD data baudrate: %u bps\n", can_config.baudrate_fd);

    status = hpm_can_init_channel(3, &can_config);
    if (status != status_success) {
        printf("CAN3 initialization failed for transmit mode, error code: %d\n", status);
        return status;
    }

    s_can_led_state[3].channel_initialized = true;
    s_can3_transmit_initialized = true;

    /* Initialize TxCan7[15-29], TxCan8, and TxCan9 (used by CAN3) */
    extern CHAR TxCan70x70D2[30];
    extern CHAR TxCan80x70F0[30];
    extern CHAR TxCan90x710E[30];
    memset(&TxCan70x70D2[15], 0, 15);  // Only clear last 15 bytes, TxCan7[0-14] used by CAN2
    memset(&TxCan80x70F0, 0, sizeof(TxCan80x70F0));
    memset(&TxCan90x710E, 0, sizeof(TxCan90x710E));

    printf("CAN3 initialized successfully for transmit mode\n");
    return status_success;
}

void can_app_process_txcan3_transmit(void)
{
    mcan_tx_frame_t tx_frame;
    hpm_stat_t status;

    if (!s_can3_transmit_initialized) {
        return;
    }

    if (s_txcan3_transmit_pending == 0) {
        return;
    }

    s_txcan3_transmit_pending = 0;

    memset(&tx_frame, 0, sizeof(tx_frame));

    extern CHAR TxCan70x70D2[30];
    extern CHAR TxCan80x70F0[30];
    extern CHAR TxCan90x710E[30];

    /* Extract CAN ID from TxCan7[15-18] */
    uint32_t can_id = TxCan70x70D2[15] |
                     ((uint32_t)TxCan70x70D2[16] << 8) |
                     ((uint32_t)TxCan70x70D2[17] << 16) |
                     ((uint32_t)TxCan70x70D2[18] << 24);

    /* Extract DLC from TxCan7[19], limit to 15 (0x0F) */
    uint8_t dlc = TxCan70x70D2[19];
    if (dlc > 15) {
        dlc = 15;
    }

    /* Determine if it's an extended frame (ID > 0x7FF) */
    if (can_id > 0x7FF) {
        tx_frame.ext_id = can_id;
        tx_frame.use_ext_id = 1;
    } else {
        tx_frame.std_id = can_id;
        tx_frame.use_ext_id = 0;
    }
    tx_frame.dlc = dlc;
    tx_frame.canfd_frame = 1;
    tx_frame.bitrate_switch = 1;

    /* Layout: TxCan7[15-18]=ID, [19]=DLC, [20-29]=data (10 bytes), TxCan8 (30), TxCan9 (30) */
    memcpy(&tx_frame.data_8[0], &TxCan70x70D2[20], 10);
    memcpy(&tx_frame.data_8[10], TxCan80x70F0, 30);
    memcpy(&tx_frame.data_8[40], TxCan90x710E, 30);

    status = hpm_can_transmit(3, &tx_frame);
    if (status == status_success) {
        s_can_led_state[3].tx_active = true;
        s_can_led_state[3].tx_last_tick = s_timer_tick;
    } else {
        printf("Failed to transmit CAN FD frame on CAN3, status: %d\n", status);
    }
}





