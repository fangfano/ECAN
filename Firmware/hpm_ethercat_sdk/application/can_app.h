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
 * @brief Initialize CAN application
 */
void can_app_init(void);



/**
 * @brief Initialize CAN0 for continuous receive mode
 *
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t can_app_init_can0_receive(void);

/**
 * @brief Check and process CAN0 received messages
 *
 * This function should be called periodically to check for new CAN messages
 * and update the receive buffer.
 */
void can_app_process_can0_receive(void);

/**
 * @brief Get pointer to CAN0 receive buffer
 *
 * @return uint8_t* Pointer to receive buffer (30 bytes for CAN data)
 */
uint8_t *can_app_get_can0_rx_buffer(void);

/**
 * @brief Get pointer to CAN1 receive buffer (used for overflow from CAN0)
 *
 * @return uint8_t* Pointer to receive buffer (30 bytes for CAN data)
 */
uint8_t *can_app_get_can1_rx_buffer(void);

/**
 * @brief Get pointer to CAN2 receive buffer (used for overflow from CAN1)
 *
 * @return uint8_t* Pointer to receive buffer (30 bytes for CAN data)
 */
uint8_t *can_app_get_can2_rx_buffer(void);

/**
 * @brief Get pointer to CAN3 receive buffer (used for overflow from CAN2)
 *
 * @return uint8_t* Pointer to receive buffer (30 bytes for CAN data)
 */
uint8_t *can_app_get_can3_rx_buffer(void);

/**
 * @brief Get CAN0 message status flags
 *
 * @return uint32_t Status flags (bit 0: new data available)
 */
uint32_t can_app_get_can0_status(void);

/**
 * @brief Clear CAN0 new data flag
 */
void can_app_clear_can0_new_data_flag(void);

/**
 * @brief Initialize CAN0 for transmit mode
 *
 * @return hpm_stat_t Status of operation
 */
hpm_stat_t can_app_init_can0_transmit(void);

/**
 * @brief Process and transmit TxCan0 data to CAN0
 *
 * This function reads data from the TxCan0 buffer and sends it as a CAN FD frame
 */
void can_app_process_txcan_transmit(void);

/**
 * @brief Trigger CAN0 transmit pending flag
 *
 * This function should be called when new TxCan0 data is available
 */
void can_app_trigger_transmit(void);

/**
 * @brief Initialize CAN1 for continuous receive mode
 *
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t can_app_init_can1_receive(void);

/**
 * @brief Check and process CAN1 received messages
 *
 * This function should be called periodically to check for new CAN messages
 * and update the receive buffer.
 */
void can_app_process_can1_receive(void);

/**
 * @brief Initialize CAN1 for transmit mode
 *
 * @return hpm_stat_t Status of operation
 */
hpm_stat_t can_app_init_can1_transmit(void);

/**
 * @brief Process and transmit TxCan4 data to CAN1
 *
 * This function reads data from the TxCan4/5/6 buffers and sends it as a CAN FD frame
 */
void can_app_process_txcan1_transmit(void);

/**
 * @brief Trigger CAN1 transmit pending flag
 *
 * This function should be called when new TxCan4 data is available
 */
void can_app_trigger_can1_transmit(void);

/**
 * @brief Initialize CAN2 for continuous receive mode
 *
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t can_app_init_can2_receive(void);

/**
 * @brief Check and process CAN2 received messages
 *
 * This function should be called periodically to check for new CAN messages
 * and update the receive buffer.
 */
void can_app_process_can2_receive(void);

/**
 * @brief Initialize CAN2 for transmit mode
 *
 * @return hpm_stat_t Status of operation
 */
hpm_stat_t can_app_init_can2_transmit(void);

/**
 * @brief Process and transmit TxCan7 data to CAN2
 *
 * This function reads data from the TxCan7/8/9 buffers and sends it as a CAN FD frame
 */
void can_app_process_txcan2_transmit(void);

/**
 * @brief Trigger CAN2 transmit pending flag
 *
 * This function should be called when new TxCan7 data is available
 */
void can_app_trigger_can2_transmit(void);

/**
 * @brief Initialize CAN3 for continuous receive mode
 *
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t can_app_init_can3_receive(void);

/**
 * @brief Check and process CAN3 received messages
 *
 * This function should be called periodically to check for new CAN messages
 * and update the receive buffer.
 */
void can_app_process_can3_receive(void);

/**
 * @brief Initialize CAN3 for transmit mode
 *
 * @return hpm_stat_t Status of operation
 */
hpm_stat_t can_app_init_can3_transmit(void);

/**
 * @brief Process and transmit TxCan10 data to CAN3
 *
 * This function reads data from the TxCan10/11/12 buffers and sends it as a CAN FD frame
 */
void can_app_process_txcan3_transmit(void);

/**
 * @brief Trigger CAN3 transmit pending flag
 *
 * This function should be called when new TxCan10 data is available
 */
void can_app_trigger_can3_transmit(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_APP_H */
