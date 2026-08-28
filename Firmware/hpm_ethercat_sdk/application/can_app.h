/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef CAN_APP_H
#define CAN_APP_H

#include "hpm_common.h"
#include "hpm_mcan_drv.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CAN LED blink period in microseconds
 */
#define CAN_LED_BLINK_PERIOD_US  (100000)  /* LED blink period: 100ms */

/**
 * @brief CAN LED activity timeout in milliseconds
 */
#define CAN_LED_ACTIVITY_TIMEOUT_MS (100)   /* Timeout to stop blinking: 100ms */

/**
 * @brief Initialize CAN application (LEDs, timer, CAN channels)
 */
void can_app_init(void);

/**
 * @brief Initialize CANx for continuous receive mode (ch0/1: CANFD, ch2/3: classic)
 */
hpm_stat_t can_app_init_can0_receive(void);
hpm_stat_t can_app_init_can1_receive(void);
hpm_stat_t can_app_init_can2_receive(void);
hpm_stat_t can_app_init_can3_receive(void);

/**
 * @brief Initialize CANx for transmit mode (ch0/1: CANFD, ch2/3: classic)
 */
hpm_stat_t can_app_init_can0_transmit(void);
hpm_stat_t can_app_init_can1_transmit(void);
hpm_stat_t can_app_init_can2_transmit(void);
hpm_stat_t can_app_init_can3_transmit(void);

/**
 * @brief Trigger a bus to scan its TxPDO and send non-zero-ID slots.
 *
 * Called from APPL_OutputMapping after the master writes the PDO region.
 * Sets a per-bus pending flag; can_app_process_bus consumes it.
 */
void can_app_trigger_transmit(void);
void can_app_trigger_can1_transmit(void);
void can_app_trigger_can2_transmit(void);
void can_app_trigger_can3_transmit(void);

/**
 * @brief Unified per-bus TX+RX processor.
 *
 * TX: if triggered this iteration, scan 7 slots and send each slot whose
 *     CAN ID (bytes 0..1 of the 11-byte entry) is non-zero. Slots with
 *     CAN ID == 0 are skipped but their previously learned CAN ID is
 *     preserved so RX routing keeps working.
 *
 * RX: drain the FIFO. For each frame, find the slot whose last TX used
 *     that CAN ID and write the 11-byte status into that slot's RxPDO.
 *     Frames whose CAN ID was never TX-ed by any slot are discarded.
 *
 * Call once per main-loop iteration for each of the 4 buses; they are
 * independent and effectively concurrent.
 *
 * @param ch CAN channel index (0..3)
 */
void can_app_process_bus(uint32_t ch);

/**
 * @brief TX Completed interrupt handler entry point.
 *
 * Called from the MCANx_IRQHandler in hpm_can.c. Drains pending frames
 * from the pipeline by feeding them into the TX FIFO until it is full
 * or all frames have been sent.
 *
 * @param ch CAN channel index (0..3)
 */
void can_app_on_tx_complete(uint32_t ch);

#ifdef __cplusplus
}
#endif

#endif /* CAN_APP_H */
