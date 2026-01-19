/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
\addtogroup digital_io digital_io
@{
*/

/**
\file digital_io.c
\brief Implementation
 Created with SSC Tool application parser 1.6.4.0
\version 0.0.0.1
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "applInterface.h"

#define _DIGITAL_IO_ 1
#include "digital_io.h"
#undef _DIGITAL_IO_

#include "ecat_config.h"
#include "hpm_gpio_drv.h"
#include "applInterface.h"
#include "can_app.h"


UINT32 APPL_GetDipSw(void);
void APPL_SetLed(UINT32 value,UINT32 value1);

static UINT32 timer_500ms_counter = 0;
static UINT32 timer_500ms_flag = 0;

/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/


/**
 \brief    The function is called when an error state was acknowledged by the master
*/

void    APPL_AckErrorInd(UINT16 stateTrans)
{

}


/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
             all general settings were checked to start the mailbox handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case this function will be called cyclically
            until a value unequal NOERROR_INWORK is returned

*/

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
             to stop the mailbox handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*/

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                       register (0x204) when this function is succeeded. The event mask can be adapted
                       in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
           all general settings were checked to start the input handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete
           the transition by calling ECAT_StateChange.
*/

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    return ALSTATUSCODE_NOERROR;
}

/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*/

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete
           the transition by calling ECAT_StateChange.
*/

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*/

UINT16 APPL_StopOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*/

UINT16 APPL_GenerateMapping(UINT16 *pInputSize, UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM *pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;

#if MAX_PD_OUTPUT_SIZE > 0
    /*Scan object 0x1C12 RXPDO assign*/
    for (PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++) {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if (pPDO != NULL) {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for (PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++) {
                pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1), pPDO)>>4));    /* goto PDO entry */
                /* we increment the expected output size depending on the mapped Entry */
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
            }
        } else {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;
#endif

#if MAX_PD_INPUT_SIZE > 0
    if (result == 0) {
        /*Scan Object 0x1C13 TXPDO assign*/
        for (PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++) {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if (pPDO != NULL) {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for (PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++) {
                    pPDOEntry = (UINT32 *)(((UINT16 *)pPDO->pVarPtr) + (OBJ_GetEntryOffset((PDOEntryCnt+1), pPDO)>>4));    /* goto PDO entry */
                    /* we increment the expected output size depending on the mapped Entry */
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                }
            } else {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;
#endif

#else
#if _WIN32
    #pragma message ("Warning: Define 'InputSize' and 'OutputSize'.")
#else
    #warning "Define 'InputSize' and 'OutputSize'."
#endif
#endif

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}

/**
\param      pData  pointer to input process data
\brief      Copy CAN data to ESC input process data
*/
void APPL_InputMapping(UINT16 *pData)
{
    uint8_t *pData8 = (uint8_t *)pData;

    /* Copy CAN0 RxCan objects to ESC input process data (75 bytes total, offset 0) */
    if (SIZEOF(RxCan00x6000) > 0) {
        MEMCPY(&pData8[0], &RxCan00x6000, SIZEOF(RxCan00x6000));
    }
    if (SIZEOF(RxCan10x601E) > 0 && nPdInputSize >= 60) {
        MEMCPY(&pData8[30], &RxCan10x601E, SIZEOF(RxCan10x601E));
    }
    if (SIZEOF(RxCan20x603C) > 0 && nPdInputSize >= 75) {
        MEMCPY(&pData8[60], &RxCan20x603C, 15);
    }

    /* Copy CAN1 RxCan objects to ESC input process data (75 bytes total, offset 75) */
    /* RxCan2[15-29] (15 bytes) already copied above, now copy from offset 75 */
    if (SIZEOF(RxCan20x603C) > 0 && nPdInputSize >= 90) {
        MEMCPY(&pData8[75], &RxCan20x603C[15], 15);
    }
    if (SIZEOF(RxCan30x605A) > 0 && nPdInputSize >= 120) {
        MEMCPY(&pData8[90], &RxCan30x605A, SIZEOF(RxCan30x605A));
    }
    if (SIZEOF(RxCan40x6078) > 0 && nPdInputSize >= 150) {
        MEMCPY(&pData8[120], &RxCan40x6078, SIZEOF(RxCan40x6078));
    }

    /* Copy CAN2 RxCan objects to ESC input process data (75 bytes total, offset 150) */
    if (SIZEOF(RxCan50x6096) > 0 && nPdInputSize >= 180) {
        MEMCPY(&pData8[150], &RxCan50x6096, SIZEOF(RxCan50x6096));
    }
    if (SIZEOF(RxCan60x60B4) > 0 && nPdInputSize >= 210) {
        MEMCPY(&pData8[180], &RxCan60x60B4, SIZEOF(RxCan60x60B4));
    }
    if (SIZEOF(RxCan70x60D2) > 0 && nPdInputSize >= 225) {
        MEMCPY(&pData8[210], &RxCan70x60D2, 15);
    }

    /* Copy CAN3 RxCan objects to ESC input process data (75 bytes total, offset 225) */
    /* RxCan7[15-29] (15 bytes) already copied above, now copy from offset 225 */
    if (SIZEOF(RxCan70x60D2) > 0 && nPdInputSize >= 240) {
        MEMCPY(&pData8[225], &RxCan70x60D2[15], 15);
    }
    if (SIZEOF(RxCan80x60F0) > 0 && nPdInputSize >= 270) {
        MEMCPY(&pData8[240], &RxCan80x60F0, SIZEOF(RxCan80x60F0));
    }
    if (SIZEOF(RxCan90x610E) > 0 && nPdInputSize >= 300) {
        MEMCPY(&pData8[270], &RxCan90x610E, SIZEOF(RxCan90x610E));
    }
}

/**
\param      pData  pointer to output process data
\brief    Copy ESC output data to TxCan objects
*/
void APPL_OutputMapping(UINT16 *pData)
{
    uint8_t *pData8 = (uint8_t *)pData;

    /* Copy to CAN0 TxCan objects (75 bytes total, offset 0) */
    MEMCPY(&TxCan00x7000, &pData8[0], SIZEOF(TxCan00x7000));
    MEMCPY(&TxCan10x701E, &pData8[30], SIZEOF(TxCan10x701E));
    MEMCPY(&TxCan20x703C, &pData8[60], 15);
    can_app_trigger_transmit();

    /* Copy to CAN1 TxCan objects (75 bytes total, offset 75) */
    if (nPdOutputSize >= 90) {
        MEMCPY(&TxCan20x703C[15], &pData8[75], 15);
    }
    if (nPdOutputSize >= 120) {
        MEMCPY(&TxCan30x705A, &pData8[90], SIZEOF(TxCan30x705A));
    }
    if (nPdOutputSize >= 150) {
        MEMCPY(&TxCan40x7078, &pData8[120], SIZEOF(TxCan40x7078));
    }
    can_app_trigger_can1_transmit();

    /* Copy to CAN2 TxCan objects (75 bytes total, offset 150) */
    if (nPdOutputSize >= 180) {
        MEMCPY(&TxCan50x7096, &pData8[150], SIZEOF(TxCan50x7096));
    }
    if (nPdOutputSize >= 210) {
        MEMCPY(&TxCan60x70B4, &pData8[180], SIZEOF(TxCan60x70B4));
    }
    if (nPdOutputSize >= 225) {
        MEMCPY(&TxCan70x70D2, &pData8[210], 15);
    }
    can_app_trigger_can2_transmit();

    /* Copy to CAN3 TxCan objects (75 bytes total, offset 225) */
    if (nPdOutputSize >= 240) {
        MEMCPY(&TxCan70x70D2[15], &pData8[225], 15);
    }
    if (nPdOutputSize >= 270) {
        MEMCPY(&TxCan80x70F0, &pData8[240], SIZEOF(TxCan80x70F0));
    }
    if (nPdOutputSize >= 300) {
        MEMCPY(&TxCan90x710E, &pData8[270], SIZEOF(TxCan90x710E));
    }
    can_app_trigger_can3_transmit();
}

/**
\brief    Called from synchronization ISR or mainloop
*/
void APPL_Application(void)
{
    APPL_SetLed((UINT32)(TxCan00x7000[0] & 0xFFFFFFFF),(UINT32)(TxCan00x7000[1] & 0xFFFFFFFF));
}

/**
\brief    Called in ecat_time_ms_isr to handle 500ms timer
*/
void APPL_Timer500ms_Handler(void)
{
    timer_500ms_counter++;
    if (timer_500ms_counter >= 500) {
        timer_500ms_counter = 0;
        timer_500ms_flag = 1;
    }
}

/**
\brief    Called in mainloop to check 500ms timer flag
*/
void APPL_CheckTimer500ms(void)
{
    if (timer_500ms_flag) {
        timer_500ms_flag = 0;
        HW_EscWriteIsr(((MEM_ADDR)&RxCan00x6000), nEscAddrInputData, nPdInputSize);
    }
}

#if EXPLICIT_DEVICE_ID

/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Read the Explicit Device ID (from an external ID switch)
*/
UINT16 APPL_GetDeviceID(void)
{
    /* Explicit Device 5 is expected by Explicit Device ID conformance tests*/
    return 0x5;
}
#endif

extern UINT16 aPdInputData[(MAX_PD_INPUT_SIZE>>1)];
void APPL_SetLed(UINT32 value,UINT32 value1)
{
    UINT8 led0 = ((value & 1) ?  BOARD_ECAT_OUT_ON_LEVEL : !BOARD_ECAT_OUT_ON_LEVEL);
    UINT8 led1 = ((value & 2) ?  BOARD_ECAT_OUT_ON_LEVEL : !BOARD_ECAT_OUT_ON_LEVEL);

    gpio_write_pin(BOARD_ECAT_OUT1_GPIO, BOARD_ECAT_OUT1_GPIO_PORT_INDEX, BOARD_ECAT_OUT1_GPIO_PIN_INDEX, led0);
    gpio_write_pin(BOARD_ECAT_OUT2_GPIO, BOARD_ECAT_OUT2_GPIO_PORT_INDEX, BOARD_ECAT_OUT2_GPIO_PIN_INDEX, led1);
    
    HW_EscWriteIsr(((MEM_ADDR )&RxCan00x6000), nEscAddrInputData, nPdInputSize );
}

UINT32 APPL_GetDipSw(void)
{
    UINT8 pin0_level = gpio_read_pin(BOARD_ECAT_IN1_GPIO, BOARD_ECAT_IN1_GPIO_PORT_INDEX, BOARD_ECAT_IN1_GPIO_PIN_INDEX);
    UINT8 pin1_level = gpio_read_pin(BOARD_ECAT_IN2_GPIO, BOARD_ECAT_IN2_GPIO_PORT_INDEX, BOARD_ECAT_IN2_GPIO_PIN_INDEX);

    UINT32 val = pin0_level << 0 | pin1_level << 1;

    return val;
}

#if USE_DEFAULT_MAIN

/**

 \brief    This is the main function

*/
#if _PIC24 && EL9800_HW
int main(void)
#elif _WIN32
int main(int argc, char *argv[])
#else
void main(void)
#endif
{
    /* initialize the Hardware and the EtherCAT Slave Controller */
#if FC1100_HW
#if _WIN32
    u16FcInstance = 0;
    if (argc > 1) {
        u16FcInstance = atoi(argv[1]);
    }
#endif
    if (HW_Init()) {
        HW_Release();
        return;
    }
#else
    HW_Init();
#endif
    MainInit();

    bRunApplication = TRUE;
    do {
        MainLoop();
    } while (bRunApplication == TRUE);

    HW_Release();
#if _PIC24
    return 0;
#endif
}
#endif /* #if USE_DEFAULT_MAIN */
/** @} */

