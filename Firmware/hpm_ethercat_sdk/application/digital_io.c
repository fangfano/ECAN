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
extern UINT16 aPdInputData[(MAX_PD_INPUT_SIZE>>1)];

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

    if (nPdInputSize >= 112) {
        MEMCPY(&pData8[0],   &RxCanGroup110x6000, 16);
        MEMCPY(&pData8[16],  &RxCanGroup120x6010, 16);
        MEMCPY(&pData8[32],  &RxCanGroup130x6020, 16);
        MEMCPY(&pData8[48],  &RxCanGroup140x6030, 16);
        MEMCPY(&pData8[64],  &RxCanGroup150x6040, 16);
        MEMCPY(&pData8[80],  &RxCanGroup160x6050, 16);
        MEMCPY(&pData8[96],  &RxCanGroup170x6060, 16);
    }

    if (nPdInputSize >= 224) {
        MEMCPY(&pData8[112], &RxCanGroup210x6070, 16);
        MEMCPY(&pData8[128], &RxCanGroup220x6080, 16);
        MEMCPY(&pData8[144], &RxCanGroup230x6090, 16);
        MEMCPY(&pData8[160], &RxCanGroup240x60A0, 16);
        MEMCPY(&pData8[176], &RxCanGroup250x60B0, 16);
        MEMCPY(&pData8[192], &RxCanGroup260x60C0, 16);
        MEMCPY(&pData8[208], &RxCanGroup270x60D0, 16);
    }

    if (nPdInputSize >= 336) {
        MEMCPY(&pData8[224], &RxCanGroup310x60E0, 16);
        MEMCPY(&pData8[240], &RxCanGroup320x60F0, 16);
        MEMCPY(&pData8[256], &RxCanGroup330x6100, 16);
        MEMCPY(&pData8[272], &RxCanGroup340x6110, 16);
        MEMCPY(&pData8[288], &RxCanGroup350x6120, 16);
        MEMCPY(&pData8[304], &RxCanGroup360x6130, 16);
        MEMCPY(&pData8[320], &RxCanGroup370x6140, 16);
    }

    if (nPdInputSize >= 448) {
        MEMCPY(&pData8[336], &RxCanGroup410x6150, 16);
        MEMCPY(&pData8[352], &RxCanGroup420x6160, 16);
        MEMCPY(&pData8[368], &RxCanGroup430x6170, 16);
        MEMCPY(&pData8[384], &RxCanGroup440x6180, 16);
        MEMCPY(&pData8[400], &RxCanGroup450x6190, 16);
        MEMCPY(&pData8[416], &RxCanGroup460x61A0, 16);
        MEMCPY(&pData8[432], &RxCanGroup470x61B0, 16);
    }
}

/**
\param      pData  pointer to output process data
\brief    Copy ESC output data to TxCan objects
*/
void APPL_OutputMapping(UINT16 *pData)
{
    uint8_t *pData8 = (uint8_t *)pData;

    if (nPdOutputSize >= 112) {
        MEMCPY(&TxCanGroup110x7000, &pData8[0],   16);
        MEMCPY(&TxCanGroup120x7010, &pData8[16],  16);
        MEMCPY(&TxCanGroup130x7020, &pData8[32],  16);
        MEMCPY(&TxCanGroup140x7030, &pData8[48],  16);
        MEMCPY(&TxCanGroup150x7040, &pData8[64],  16);
        MEMCPY(&TxCanGroup160x7050, &pData8[80],  16);
        MEMCPY(&TxCanGroup170x7060, &pData8[96],  16);
        can_app_trigger_transmit();
    }

    if (nPdOutputSize >= 224) {
        MEMCPY(&TxCanGroup210x7070, &pData8[112], 16);
        MEMCPY(&TxCanGroup220x7080, &pData8[128], 16);
        MEMCPY(&TxCanGroup230x7090, &pData8[144], 16);
        MEMCPY(&TxCanGroup240x70A0, &pData8[160], 16);
        MEMCPY(&TxCanGroup250x70B0, &pData8[176], 16);
        MEMCPY(&TxCanGroup260x70C0, &pData8[192], 16);
        MEMCPY(&TxCanGroup270x70D0, &pData8[208], 16);
        can_app_trigger_can1_transmit();
    }

    if (nPdOutputSize >= 336) {
        MEMCPY(&TxCanGroup310x70E0, &pData8[224], 16);
        MEMCPY(&TxCanGroup320x70F0, &pData8[240], 16);
        MEMCPY(&TxCanGroup330x7100, &pData8[256], 16);
        MEMCPY(&TxCanGroup340x7110, &pData8[272], 16);
        MEMCPY(&TxCanGroup350x7120, &pData8[288], 16);
        MEMCPY(&TxCanGroup360x7130, &pData8[304], 16);
        MEMCPY(&TxCanGroup370x7140, &pData8[320], 16);
        can_app_trigger_can2_transmit();
    }

    if (nPdOutputSize >= 448) {
        MEMCPY(&TxCanGroup410x7150, &pData8[336], 16);
        MEMCPY(&TxCanGroup420x7160, &pData8[352], 16);
        MEMCPY(&TxCanGroup430x7170, &pData8[368], 16);
        MEMCPY(&TxCanGroup440x7180, &pData8[384], 16);
        MEMCPY(&TxCanGroup450x7190, &pData8[400], 16);
        MEMCPY(&TxCanGroup460x71A0, &pData8[416], 16);
        MEMCPY(&TxCanGroup470x71B0, &pData8[432], 16);
        can_app_trigger_can3_transmit();
    }
}


/**
\brief    Called from synchronization ISR or mainloop
*/
void APPL_Application(void)
{
    APPL_SetLed(0, 0);
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
        if (bEcatInputUpdateRunning && (nEscAddrInputData != 0) && (nPdInputSize != 0)) {
            APPL_InputMapping(aPdInputData);
            HW_EscWriteIsr((MEM_ADDR)aPdInputData, nEscAddrInputData, nPdInputSize);
        }
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

void APPL_SetLed(UINT32 value,UINT32 value1)
{
    UINT8 led0 = ((value & 1) ?  BOARD_ECAT_OUT_ON_LEVEL : !BOARD_ECAT_OUT_ON_LEVEL);
    UINT8 led1 = ((value & 2) ?  BOARD_ECAT_OUT_ON_LEVEL : !BOARD_ECAT_OUT_ON_LEVEL);

    gpio_write_pin(BOARD_ECAT_OUT1_GPIO, BOARD_ECAT_OUT1_GPIO_PORT_INDEX, BOARD_ECAT_OUT1_GPIO_PIN_INDEX, led0);
    gpio_write_pin(BOARD_ECAT_OUT2_GPIO, BOARD_ECAT_OUT2_GPIO_PORT_INDEX, BOARD_ECAT_OUT2_GPIO_PIN_INDEX, led1);
    
    if (bEcatInputUpdateRunning && (nEscAddrInputData != 0) && (nPdInputSize != 0)) {
        APPL_InputMapping(aPdInputData);
        HW_EscWriteIsr((MEM_ADDR)aPdInputData, nEscAddrInputData, nPdInputSize);
    }
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
