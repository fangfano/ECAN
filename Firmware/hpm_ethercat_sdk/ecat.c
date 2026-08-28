/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include "board.h"
#include "ecat_def.h"
#include "ecatappl.h"
#include "ecatslv.h"
#include "applInterface.h"
#include "digital_io.h"
#include "hpm_ecat_hw.h"
#include "hpm_l1c_drv.h"
#include "can_app.h"

extern void APPL_CheckTimer500ms(void);


int main(void)
{
    hpm_stat_t stat;
    board_init();
    board_init_ethercat(HPM_ESC); /* init ESC function pins */
    board_init_switch_led();      /* init switch and led for ECAT display */
    printf("EtherCAT IO sample\n");

    /* hardware init */
    stat = ecat_hardware_init(HPM_ESC);
    if (stat != status_success) {
        printf("Init ESC peripheral and related devices(EEPROM/PHY) failed!\n");
        return 0;
    }

    /* CAN initialization */
    printf("Initializing CAN...\n");
    can_app_init();
    printf("CAN initialized!\n");

    /* Initialize CAN0 for continuous receive mode */
    printf("Initializing CAN0 for ECAT RX bridge...\n");
    hpm_stat_t can0_status = can_app_init_can0_receive();
    if (can0_status != status_success) {
        printf("WARNING: CAN0 initialization failed, CAN->ECAT bridge may not work\n");
    } else {
        printf("CAN0 ECAT RX bridge initialized successfully!\n");
    }

    /* Initialize CAN0 for transmit mode (ECAT TX -> CAN) */
    printf("Initializing CAN0 for ECAT TX bridge...\n");
    hpm_stat_t can0_tx_status = can_app_init_can0_transmit();
    if (can0_tx_status != status_success) {
        printf("WARNING: CAN0 transmit initialization failed, ECAT->CAN bridge may not work\n");
    } else {
        printf("CAN0 ECAT TX bridge initialized successfully!\n");
    }

    /* Initialize CAN1 for continuous receive mode */
    printf("Initializing CAN1 for ECAT RX bridge...\n");
    hpm_stat_t can1_status = can_app_init_can1_receive();
    if (can1_status != status_success) {
        printf("WARNING: CAN1 initialization failed, CAN->ECAT bridge may not work\n");
    } else {
        printf("CAN1 ECAT RX bridge initialized successfully!\n");
    }

    /* Initialize CAN1 for transmit mode (ECAT TX -> CAN) */
    printf("Initializing CAN1 for ECAT TX bridge...\n");
    hpm_stat_t can1_tx_status = can_app_init_can1_transmit();
    if (can1_tx_status != status_success) {
        printf("WARNING: CAN1 transmit initialization failed, ECAT->CAN bridge may not work\n");
    } else {
        printf("CAN1 ECAT TX bridge initialized successfully!\n");
    }

    /* Initialize CAN2 for continuous receive mode */
    printf("Initializing CAN2 for ECAT RX bridge...\n");
    hpm_stat_t can2_status = can_app_init_can2_receive();
    if (can2_status != status_success) {
        printf("WARNING: CAN2 initialization failed, CAN->ECAT bridge may not work\n");
    } else {
        printf("CAN2 ECAT RX bridge initialized successfully!\n");
    }

    /* Initialize CAN2 for transmit mode (ECAT TX -> CAN) */
    printf("Initializing CAN2 for ECAT TX bridge...\n");
    hpm_stat_t can2_tx_status = can_app_init_can2_transmit();
    if (can2_tx_status != status_success) {
        printf("WARNING: CAN2 transmit initialization failed, ECAT->CAN bridge may not work\n");
    } else {
        printf("CAN2 ECAT TX bridge initialized successfully!\n");
    }

    /* Initialize CAN3 for continuous receive mode */
    printf("Initializing CAN3 for ECAT RX bridge...\n");
    hpm_stat_t can3_status = can_app_init_can3_receive();
    if (can3_status != status_success) {
        printf("WARNING: CAN3 initialization failed, CAN->ECAT bridge may not work\n");
    } else {
        printf("CAN3 ECAT RX bridge initialized successfully!\n");
    }

    /* Initialize CAN3 for transmit mode (ECAT TX -> CAN) */
    printf("Initializing CAN3 for ECAT TX bridge...\n");
    hpm_stat_t can3_tx_status = can_app_init_can3_transmit();
    if (can3_tx_status != status_success) {
        printf("WARNING: CAN3 transmit initialization failed, ECAT->CAN bridge may not work\n");
    } else {
        printf("CAN3 ECAT TX bridge initialized successfully!\n");
    }

    MainInit(); /* SSC Initilize the stack */

#if defined(ESC_EEPROM_EMULATION) && ESC_EEPROM_EMULATION
    pAPPL_EEPROM_Read  = ecat_eeprom_emulation_read;
    pAPPL_EEPROM_Write = ecat_eeprom_emulation_write;
    pAPPL_EEPROM_Reload = ecat_eeprom_emulation_reload;
    pAPPL_EEPROM_Store  = ecat_eeprom_emulation_store;
#endif

    /* Create basic mapping */
    APPL_GenerateMapping(&nPdInputSize, &nPdOutputSize);

    /* Set stack run flag */
    bRunApplication = TRUE;
    /* Execute the stack */
    while (bRunApplication == TRUE) {
        /* Process all 4 CAN buses: TX (if triggered) + RX (FIFO drain + route) */
        can_app_process_bus(0);
        can_app_process_bus(1);
        can_app_process_bus(2);
        can_app_process_bus(3);

        /* Run EtherCAT stack main loop */
        MainLoop();

        /* Check timer for periodic tasks */
        APPL_CheckTimer500ms();
    }

    /* hardware deinit */

    return 0;
}
