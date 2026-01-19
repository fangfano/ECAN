/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_can.h"
#include "hpm_mcan_drv.h"
#include "board.h"

#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
ATTR_PLACE_AT(".ahb_sram") uint32_t mcan0_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS];
ATTR_PLACE_AT(".ahb_sram") uint32_t mcan1_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS];
ATTR_PLACE_AT(".ahb_sram") uint32_t mcan2_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS];
ATTR_PLACE_AT(".ahb_sram") uint32_t mcan3_msg_buf[MCAN_MSG_BUF_SIZE_IN_WORDS];
#endif

typedef struct {
    MCAN_Type *can_base;
    uint32_t clock_freq;
    uint32_t irq_num;
#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
    uint32_t ram_base;
    uint32_t ram_size;
#endif
} can_info_t;

static can_info_t s_can_info[] = {
#if defined(HPM_MCAN0)
    {
        .can_base = HPM_MCAN0,
        .irq_num = IRQn_MCAN0,
#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
        .ram_base = (uint32_t) &mcan0_msg_buf,
        .ram_size = sizeof(mcan0_msg_buf),
#endif
    },
#endif
#if defined(HPM_MCAN1)
    {
        .can_base = HPM_MCAN1,
        .irq_num = IRQn_MCAN1,
#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
        .ram_base = (uint32_t) &mcan1_msg_buf,
        .ram_size = sizeof(mcan1_msg_buf),
#endif
    },
#endif
#if defined(HPM_MCAN2)
    {
        .can_base = HPM_MCAN2,
        .irq_num = IRQn_MCAN2,
#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
        .ram_base = (uint32_t) &mcan2_msg_buf,
        .ram_size = sizeof(mcan2_msg_buf),
#endif
    },
#endif
#if defined(HPM_MCAN3)
    {
        .can_base = HPM_MCAN3,
        .irq_num = IRQn_MCAN3,
#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
        .ram_base = (uint32_t) &mcan3_msg_buf,
        .ram_size = sizeof(mcan3_msg_buf),
#endif
    },
#endif
};

hpm_stat_t hpm_can_init_all_channels(void)
{
    hpm_stat_t status = status_success;

    for (uint32_t i = 0; i < ARRAY_SIZE(s_can_info); i++) {
        can_info_t *info = &s_can_info[i];
        board_init_can(info->can_base);
        info->clock_freq = board_init_can_clock(info->can_base);

#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
        mcan_msg_buf_attr_t attr = { info->ram_base, info->ram_size };
        status = mcan_set_msg_buf_attr(info->can_base, &attr);
        if (status != status_success) {
            printf("Error was detected during setting message buffer attribute, please check the arguments\n");
            return status;
        }
#endif
    }

    return status;
}

hpm_stat_t hpm_can_init_channel(uint32_t channel, mcan_config_t *config)
{
    hpm_stat_t status;
    can_info_t *info;

    if (channel >= ARRAY_SIZE(s_can_info)) {
        return status_invalid_argument;
    }

    info = &s_can_info[channel];

#if defined(MCAN_SOC_MSG_BUF_IN_AHB_RAM) && (MCAN_SOC_MSG_BUF_IN_AHB_RAM == 1)
    mcan_msg_buf_attr_t attr = { info->ram_base, info->ram_size };
    status = mcan_set_msg_buf_attr(info->can_base, &attr);
    if (status != status_success) {
        printf("Error was detected during setting message buffer attribute, please check the arguments\n");
        return status;
    }
#endif

    status = mcan_init(info->can_base, config, info->clock_freq);
    if (status != status_success) {
        printf("CAN%d initialization failed, error code: %d\n", channel, status);
        return status;
    }

    return status_success;
}

hpm_stat_t hpm_can_deinit_channel(uint32_t channel)
{
    can_info_t *info;

    if (channel >= ARRAY_SIZE(s_can_info)) {
        return status_invalid_argument;
    }

    info = &s_can_info[channel];
    mcan_deinit(info->can_base);

    return status_success;
}

hpm_stat_t hpm_can_get_default_config(mcan_config_t *config, bool enable_canfd)
{
    mcan_get_default_config(s_can_info[0].can_base, config);

    if (enable_canfd) {
        config->baudrate = 1000000; /* 1Mbps */
        config->baudrate_fd = 5000000; /* 5Mbps for data phase */
        config->enable_canfd = true;
        config->mode = mcan_mode_normal;
        config->enable_tdc = true; /* Enable Transmitter Delay Compensation for 5Mbps */
        mcan_get_default_ram_config(s_can_info[0].can_base, &config->ram_config, true);
    } else {
        config->baudrate = 1000000; /* 1Mbps */
        config->mode = mcan_mode_normal;
    }

    return status_success;
}

hpm_stat_t hpm_can_transmit(uint32_t channel, mcan_tx_frame_t *tx_frame)
{
    can_info_t *info;

    if (channel >= ARRAY_SIZE(s_can_info)) {
        return status_invalid_argument;
    }

    info = &s_can_info[channel];
    return mcan_transmit_blocking(info->can_base, tx_frame);
}

hpm_stat_t hpm_can_receive(uint32_t channel, mcan_rx_message_t *rx_msg)
{
    can_info_t *info;

    if (channel >= ARRAY_SIZE(s_can_info)) {
        return status_invalid_argument;
    }

    info = &s_can_info[channel];
    return mcan_receive_from_fifo_blocking(info->can_base, 0, rx_msg);
}

MCAN_Type *hpm_can_get_base(uint32_t channel)
{
    if (channel >= ARRAY_SIZE(s_can_info)) {
        return NULL;
    }

    return s_can_info[channel].can_base;
}

uint32_t hpm_can_get_channel_count(void)
{
    return ARRAY_SIZE(s_can_info);
}
