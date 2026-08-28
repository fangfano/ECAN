/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_CAN_H
#define HPM_CAN_H

#include "hpm_common.h"
#include "hpm_mcan_drv.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize all CAN channels with default settings
 *
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t hpm_can_init_all_channels(void);

/**
 * @brief Initialize a specific CAN channel with custom configuration
 *
 * @param channel CAN channel index (0-3)
 * @param config Pointer to MCAN configuration structure
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t hpm_can_init_channel(uint32_t channel, mcan_config_t *config);

/**
 * @brief Deinitialize a specific CAN channel
 *
 * @param channel CAN channel index (0-3)
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t hpm_can_deinit_channel(uint32_t channel);

/**
 * @brief Get default CAN configuration
 *
 * @param config Pointer to store the default configuration
 * @param enable_canfd Enable CAN FD mode
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t hpm_can_get_default_config(mcan_config_t *config, bool enable_canfd);

/**
 * @brief Transmit a CAN message on specified channel
 *
 * @param channel CAN channel index (0-3)
 * @param tx_frame Pointer to transmit frame structure
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t hpm_can_transmit(uint32_t channel, mcan_tx_frame_t *tx_frame);

/**
 * @brief Receive a CAN message from specified channel
 *
 * @param channel CAN channel index (0-3)
 * @param rx_msg Pointer to store received message
 * @return hpm_stat_t Status of the operation
 */
hpm_stat_t hpm_can_receive(uint32_t channel, mcan_rx_message_t *rx_msg);

/**
 * @brief Get CAN base address for specified channel
 *
 * @param channel CAN channel index (0-3)
 * @return MCAN_Type* Pointer to MCAN peripheral or NULL if invalid channel
 */
MCAN_Type *hpm_can_get_base(uint32_t channel);

/**
 * @brief Get total number of CAN channels
 *
 * @return uint32_t Number of available CAN channels
 */
uint32_t hpm_can_get_channel_count(void);

/**
 * @brief Non-blocking transmit: write frame into TX FIFO if space is available.
 *        Returns status_fail when the TX FIFO is full.
 */
hpm_stat_t hpm_can_transmit_nonblocking(uint32_t channel, mcan_tx_frame_t *tx_frame);

/**
 * @brief Enable or disable the TX Completed (TC) interrupt for a channel.
 *        The MCAN global IRQ is enabled on first call and stays enabled until
 *        hpm_can_disable_all_irq() is called.
 */
void hpm_can_enable_tx_completed_irq(uint32_t channel, bool enable);

/**
 * @brief Fully disable TX Completed interrupt and the MCAN global IRQ.
 */
void hpm_can_disable_all_irq(uint32_t channel);

/**
 * @brief Clear the TC interrupt flag before enabling the TC interrupt to
 *        avoid an immediate spurious interrupt.
 */
void hpm_can_clear_tx_completed_flag(uint32_t channel);

#ifdef __cplusplus
}
#endif

#endif /* HPM_CAN_H */
