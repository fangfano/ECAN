/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_can.h"
#include "hpm_mcan_drv.h"
#include "board.h"
#include "hpm_interrupt.h"
/* can_app_on_tx_complete 在 application/can_app.c 中定义，此处前向声明 */
extern void can_app_on_tx_complete(uint32_t ch);

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
    bool irq_enabled;                 /* MCAN IRQ 是否已使能（由 can_app 侧统一触发） */
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

    /* 使能所有 TX Buffer 元素的 TC（Transmission Completed）中断标志生成。
     * MCAN 规定：仅当 TXBTIE 对应 bit=1 时，该 buffer 发送完成才会置位 IR.TC。
     * 若不设置，TC 中断永远不会触发，导致 FIFO 预填后无法继续填充。 */
    info->can_base->TXBTIE = 0xFFFFFFFFU;

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

    /* 初始化后若曾使能过 IRQ，需一并关闭 */
    if (info->irq_enabled) {
        intc_m_disable_irq(info->irq_num);
        info->irq_enabled = false;
    }

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

/***********************************************************************************************************************
 *  Non-blocking TX helpers (for interrupt-driven pipeline)
 **********************************************************************************************************************/

hpm_stat_t hpm_can_transmit_nonblocking(uint32_t channel, mcan_tx_frame_t *tx_frame)
{
    can_info_t *info;
    if (channel >= ARRAY_SIZE(s_can_info) || tx_frame == NULL) {
        return status_invalid_argument;
    }
    info = &s_can_info[channel];
    /* 使用完整非阻塞发送：写 FIFO 缓冲区 + 显式请求发送（TXBAR），
     * 确保 FIFO/Queue 两种模式下均能正确触发硬件发送。 */
    return mcan_transmit_via_txfifo_nonblocking(info->can_base, tx_frame, NULL);
}

void hpm_can_enable_tx_completed_irq(uint32_t channel, bool enable)
{
    can_info_t *info;
    if (channel >= ARRAY_SIZE(s_can_info)) {
        return;
    }
    info = &s_can_info[channel];

    if (enable) {
        if (!info->irq_enabled) {
            /* 首次使能：注册并开启 MCAN 全局 IRQ，优先级与 ESC 持平（level 3） */
            intc_m_enable_irq_with_priority(info->irq_num, 3);
            info->irq_enabled = true;
        }
        /* 使能 TX Completed（TC）中断 */
        info->can_base->IE |= MCAN_IR_TC_MASK;
        info->can_base->ILE  = 1U;
    } else {
        info->can_base->IE &= ~MCAN_IR_TC_MASK;
        /* 注意：不在此处关闭全局 IRQ，防止影响其他通道使能；由 can_app 统一控制 */
    }
}

void hpm_can_disable_all_irq(uint32_t channel)
{
    can_info_t *info;
    if (channel >= ARRAY_SIZE(s_can_info)) {
        return;
    }
    info = &s_can_info[channel];
    info->can_base->IE &= ~MCAN_IR_TC_MASK;
    if (info->irq_enabled) {
        intc_m_disable_irq(info->irq_num);
        info->irq_enabled = false;
    }
}

/* 清除指定通道的 TX Completed 中断标志，需在开中断前调用 */
void hpm_can_clear_tx_completed_flag(uint32_t channel)
{
    can_info_t *info;
    if (channel >= ARRAY_SIZE(s_can_info)) {
        return;
    }
    info = &s_can_info[channel];
    /* 向 IR 寄存器对应位写 1 以清除 TC 中断标志 */
    info->can_base->IR = MCAN_IR_TC_MASK;
}

/* ===== MCAN0~3 中断服务程序 ===== */
SDK_DECLARE_EXT_ISR_M(IRQn_MCAN0, hpm_can0_isr)
SDK_DECLARE_EXT_ISR_M(IRQn_MCAN1, hpm_can1_isr)
SDK_DECLARE_EXT_ISR_M(IRQn_MCAN2, hpm_can2_isr)
SDK_DECLARE_EXT_ISR_M(IRQn_MCAN3, hpm_can3_isr)

void hpm_can0_isr(void) { can_app_on_tx_complete(0); }
void hpm_can1_isr(void) { can_app_on_tx_complete(1); }
void hpm_can2_isr(void) { can_app_on_tx_complete(2); }
void hpm_can3_isr(void) { can_app_on_tx_complete(3); }
