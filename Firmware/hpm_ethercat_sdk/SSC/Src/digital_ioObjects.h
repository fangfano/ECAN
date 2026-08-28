/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
* \addtogroup digital_io digital_io
* @{
*/

/**
\file digital_ioObjects
\author ET9300Utilities.ApplicationHandler (Version 1.6.3.0) | EthercatSSC@beckhoff.com

\brief digital_io specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : Output mapping 0
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | Output mapping 0
* @{
* \brief Object 0x1600 (Output mapping 0) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.0<br>
* SubIndex 2 - Reference to 0x7010.0<br>
* SubIndex 3 - Reference to 0x7020.0<br>
* SubIndex 4 - Reference to 0x7030.0<br>
* SubIndex 5 - Reference to 0x7040.0<br>
* SubIndex 6 - Reference to 0x7050.0<br>
* SubIndex 7 - Reference to 0x7060.0<br>
* SubIndex 8 - Reference to 0x7070.0<br>
* SubIndex 9 - Reference to 0x7080.0<br>
* SubIndex 10 - Reference to 0x7090.0<br>
* SubIndex 11 - Reference to 0x70A0.0<br>
* SubIndex 12 - Reference to 0x70B0.0<br>
* SubIndex 13 - Reference to 0x70C0.0<br>
* SubIndex 14 - Reference to 0x70D0.0<br>
* SubIndex 15 - Reference to 0x70E0.0<br>
* SubIndex 16 - Reference to 0x70F0.0<br>
* SubIndex 17 - Reference to 0x7100.0<br>
* SubIndex 18 - Reference to 0x7110.0<br>
* SubIndex 19 - Reference to 0x7120.0<br>
* SubIndex 20 - Reference to 0x7130.0<br>
* SubIndex 21 - Reference to 0x7140.0<br>
* SubIndex 22 - Reference to 0x7150.0<br>
* SubIndex 23 - Reference to 0x7160.0<br>
* SubIndex 24 - Reference to 0x7170.0<br>
* SubIndex 25 - Reference to 0x7180.0<br>
* SubIndex 26 - Reference to 0x7190.0<br>
* SubIndex 27 - Reference to 0x71A0.0<br>
* SubIndex 28 - Reference to 0x71B0.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7000.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7010.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7020.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x7030.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x7040.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x7050.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 - Reference to 0x7060.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 - Reference to 0x7070.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex9 - Reference to 0x7080.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex10 - Reference to 0x7090.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex11 - Reference to 0x70A0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex12 - Reference to 0x70B0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex13 - Reference to 0x70C0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex14 - Reference to 0x70D0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex15 - Reference to 0x70E0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex16 - Reference to 0x70F0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex17 - Reference to 0x7100.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex18 - Reference to 0x7110.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex19 - Reference to 0x7120.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex20 - Reference to 0x7130.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex21 - Reference to 0x7140.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex22 - Reference to 0x7150.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex23 - Reference to 0x7160.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex24 - Reference to 0x7170.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex25 - Reference to 0x7180.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex26 - Reference to 0x7190.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex27 - Reference to 0x71A0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex28 - Reference to 0x71B0.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "Output mapping 0\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000"
"SubIndex 010\000"
"SubIndex 011\000"
"SubIndex 012\000"
"SubIndex 013\000"
"SubIndex 014\000"
"SubIndex 015\000"
"SubIndex 016\000"
"SubIndex 017\000"
"SubIndex 018\000"
"SubIndex 019\000"
"SubIndex 020\000"
"SubIndex 021\000"
"SubIndex 022\000"
"SubIndex 023\000"
"SubIndex 024\000"
"SubIndex 025\000"
"SubIndex 026\000"
"SubIndex 027\000"
"SubIndex 028\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.0 */
UINT32 SI2; /* Subindex2 - Reference to 0x7010.0 */
UINT32 SI3; /* Subindex3 - Reference to 0x7020.0 */
UINT32 SI4; /* Subindex4 - Reference to 0x7030.0 */
UINT32 SI5; /* Subindex5 - Reference to 0x7040.0 */
UINT32 SI6; /* Subindex6 - Reference to 0x7050.0 */
UINT32 SI7; /* Subindex7 - Reference to 0x7060.0 */
UINT32 SI8; /* Subindex8 - Reference to 0x7070.0 */
UINT32 SI9; /* Subindex9 - Reference to 0x7080.0 */
UINT32 SI10; /* Subindex10 - Reference to 0x7090.0 */
UINT32 SI11; /* Subindex11 - Reference to 0x70A0.0 */
UINT32 SI12; /* Subindex12 - Reference to 0x70B0.0 */
UINT32 SI13; /* Subindex13 - Reference to 0x70C0.0 */
UINT32 SI14; /* Subindex14 - Reference to 0x70D0.0 */
UINT32 SI15; /* Subindex15 - Reference to 0x70E0.0 */
UINT32 SI16; /* Subindex16 - Reference to 0x70F0.0 */
UINT32 SI17; /* Subindex17 - Reference to 0x7100.0 */
UINT32 SI18; /* Subindex18 - Reference to 0x7110.0 */
UINT32 SI19; /* Subindex19 - Reference to 0x7120.0 */
UINT32 SI20; /* Subindex20 - Reference to 0x7130.0 */
UINT32 SI21; /* Subindex21 - Reference to 0x7140.0 */
UINT32 SI22; /* Subindex22 - Reference to 0x7150.0 */
UINT32 SI23; /* Subindex23 - Reference to 0x7160.0 */
UINT32 SI24; /* Subindex24 - Reference to 0x7170.0 */
UINT32 SI25; /* Subindex25 - Reference to 0x7180.0 */
UINT32 SI26; /* Subindex26 - Reference to 0x7190.0 */
UINT32 SI27; /* Subindex27 - Reference to 0x71A0.0 */
UINT32 SI28; /* Subindex28 - Reference to 0x71B0.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 OutputMapping00x1600
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={28,0x70000080,0x70100080,0x70200080,0x70300080,0x70400080,0x70500080,0x70600080,0x70700080,0x70800080,0x70900080,0x70A00080,0x70B00080,0x70C00080,0x70D00080,0x70E00080,0x70F00080,0x71000080,0x71100080,0x71200080,0x71300080,0x71400080,0x71500080,0x71600080,0x71700080,0x71800080,0x71900080,0x71A00080,0x71B00080}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : Input mapping 0
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | Input mapping 0
* @{
* \brief Object 0x1A00 (Input mapping 0) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6000.0<br>
* SubIndex 2 - Reference to 0x6010.0<br>
* SubIndex 3 - Reference to 0x6020.0<br>
* SubIndex 4 - Reference to 0x6030.0<br>
* SubIndex 5 - Reference to 0x6040.0<br>
* SubIndex 6 - Reference to 0x6050.0<br>
* SubIndex 7 - Reference to 0x6060.0<br>
* SubIndex 8 - Reference to 0x6070.0<br>
* SubIndex 9 - Reference to 0x6080.0<br>
* SubIndex 10 - Reference to 0x6090.0<br>
* SubIndex 11 - Reference to 0x60A0.0<br>
* SubIndex 12 - Reference to 0x60B0.0<br>
* SubIndex 13 - Reference to 0x60C0.0<br>
* SubIndex 14 - Reference to 0x60D0.0<br>
* SubIndex 15 - Reference to 0x60E0.0<br>
* SubIndex 16 - Reference to 0x60F0.0<br>
* SubIndex 17 - Reference to 0x6100.0<br>
* SubIndex 18 - Reference to 0x6110.0<br>
* SubIndex 19 - Reference to 0x6120.0<br>
* SubIndex 20 - Reference to 0x6130.0<br>
* SubIndex 21 - Reference to 0x6140.0<br>
* SubIndex 22 - Reference to 0x6150.0<br>
* SubIndex 23 - Reference to 0x6160.0<br>
* SubIndex 24 - Reference to 0x6170.0<br>
* SubIndex 25 - Reference to 0x6180.0<br>
* SubIndex 26 - Reference to 0x6190.0<br>
* SubIndex 27 - Reference to 0x61A0.0<br>
* SubIndex 28 - Reference to 0x61B0.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6000.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6010.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6020.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x6030.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x6040.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x6050.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 - Reference to 0x6060.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 - Reference to 0x6070.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex9 - Reference to 0x6080.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex10 - Reference to 0x6090.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex11 - Reference to 0x60A0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex12 - Reference to 0x60B0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex13 - Reference to 0x60C0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex14 - Reference to 0x60D0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex15 - Reference to 0x60E0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex16 - Reference to 0x60F0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex17 - Reference to 0x6100.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex18 - Reference to 0x6110.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex19 - Reference to 0x6120.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex20 - Reference to 0x6130.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex21 - Reference to 0x6140.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex22 - Reference to 0x6150.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex23 - Reference to 0x6160.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex24 - Reference to 0x6170.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex25 - Reference to 0x6180.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex26 - Reference to 0x6190.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex27 - Reference to 0x61A0.0 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex28 - Reference to 0x61B0.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "Input mapping 0\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000"
"SubIndex 010\000"
"SubIndex 011\000"
"SubIndex 012\000"
"SubIndex 013\000"
"SubIndex 014\000"
"SubIndex 015\000"
"SubIndex 016\000"
"SubIndex 017\000"
"SubIndex 018\000"
"SubIndex 019\000"
"SubIndex 020\000"
"SubIndex 021\000"
"SubIndex 022\000"
"SubIndex 023\000"
"SubIndex 024\000"
"SubIndex 025\000"
"SubIndex 026\000"
"SubIndex 027\000"
"SubIndex 028\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6000.0 */
UINT32 SI2; /* Subindex2 - Reference to 0x6010.0 */
UINT32 SI3; /* Subindex3 - Reference to 0x6020.0 */
UINT32 SI4; /* Subindex4 - Reference to 0x6030.0 */
UINT32 SI5; /* Subindex5 - Reference to 0x6040.0 */
UINT32 SI6; /* Subindex6 - Reference to 0x6050.0 */
UINT32 SI7; /* Subindex7 - Reference to 0x6060.0 */
UINT32 SI8; /* Subindex8 - Reference to 0x6070.0 */
UINT32 SI9; /* Subindex9 - Reference to 0x6080.0 */
UINT32 SI10; /* Subindex10 - Reference to 0x6090.0 */
UINT32 SI11; /* Subindex11 - Reference to 0x60A0.0 */
UINT32 SI12; /* Subindex12 - Reference to 0x60B0.0 */
UINT32 SI13; /* Subindex13 - Reference to 0x60C0.0 */
UINT32 SI14; /* Subindex14 - Reference to 0x60D0.0 */
UINT32 SI15; /* Subindex15 - Reference to 0x60E0.0 */
UINT32 SI16; /* Subindex16 - Reference to 0x60F0.0 */
UINT32 SI17; /* Subindex17 - Reference to 0x6100.0 */
UINT32 SI18; /* Subindex18 - Reference to 0x6110.0 */
UINT32 SI19; /* Subindex19 - Reference to 0x6120.0 */
UINT32 SI20; /* Subindex20 - Reference to 0x6130.0 */
UINT32 SI21; /* Subindex21 - Reference to 0x6140.0 */
UINT32 SI22; /* Subindex22 - Reference to 0x6150.0 */
UINT32 SI23; /* Subindex23 - Reference to 0x6160.0 */
UINT32 SI24; /* Subindex24 - Reference to 0x6170.0 */
UINT32 SI25; /* Subindex25 - Reference to 0x6180.0 */
UINT32 SI26; /* Subindex26 - Reference to 0x6190.0 */
UINT32 SI27; /* Subindex27 - Reference to 0x61A0.0 */
UINT32 SI28; /* Subindex28 - Reference to 0x61B0.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 InputMapping00x1A00
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={28,0x60000080,0x60100080,0x60200080,0x60300080,0x60400080,0x60500080,0x60600080,0x60700080,0x60800080,0x60900080,0x60A00080,0x60B00080,0x60C00080,0x60D00080,0x60E00080,0x60F00080,0x61000080,0x61100080,0x61200080,0x61300080,0x61400080,0x61500080,0x61600080,0x61700080,0x61800080,0x61900080,0x61A00080,0x61B00080}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : SyncManager 2 assignment
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | SyncManager 2 assignment
* @{
* \brief Object 0x1C12 (SyncManager 2 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "SyncManager 2 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,{0x1600}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : SyncManager 3 assignment
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | SyncManager 3 assignment
* @{
* \brief Object 0x1C13 (SyncManager 3 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "SyncManager 3 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,{0x1A00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : RxCanGroup1-1
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | RxCanGroup1-1
* @{
* \brief Object 0x6000 (RxCanGroup1-1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6000 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "RxCanGroup1-1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup110x6000[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6010 : RxCanGroup1-2
******************************************************************************/
/**
* \addtogroup 0x6010 0x6010 | RxCanGroup1-2
* @{
* \brief Object 0x6010 (RxCanGroup1-2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6010 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6010[] = "RxCanGroup1-2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup120x6010[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6020 : RxCanGroup1-3
******************************************************************************/
/**
* \addtogroup 0x6020 0x6020 | RxCanGroup1-3
* @{
* \brief Object 0x6020 (RxCanGroup1-3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6020 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6020[] = "RxCanGroup1-3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup130x6020[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6030 : RxCanGroup1-4
******************************************************************************/
/**
* \addtogroup 0x6030 0x6030 | RxCanGroup1-4
* @{
* \brief Object 0x6030 (RxCanGroup1-4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6030 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6030[] = "RxCanGroup1-4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup140x6030[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6040 : RxCanGroup1-5
******************************************************************************/
/**
* \addtogroup 0x6040 0x6040 | RxCanGroup1-5
* @{
* \brief Object 0x6040 (RxCanGroup1-5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6040 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6040[] = "RxCanGroup1-5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup150x6040[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6050 : RxCanGroup1-6
******************************************************************************/
/**
* \addtogroup 0x6050 0x6050 | RxCanGroup1-6
* @{
* \brief Object 0x6050 (RxCanGroup1-6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6050 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6050[] = "RxCanGroup1-6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup160x6050[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6060 : RxCanGroup1-7
******************************************************************************/
/**
* \addtogroup 0x6060 0x6060 | RxCanGroup1-7
* @{
* \brief Object 0x6060 (RxCanGroup1-7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6060 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6060[] = "RxCanGroup1-7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup170x6060[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6070 : RxCanGroup2-1
******************************************************************************/
/**
* \addtogroup 0x6070 0x6070 | RxCanGroup2-1
* @{
* \brief Object 0x6070 (RxCanGroup2-1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6070 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6070[] = "RxCanGroup2-1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup210x6070[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6080 : RxCanGroup2-2
******************************************************************************/
/**
* \addtogroup 0x6080 0x6080 | RxCanGroup2-2
* @{
* \brief Object 0x6080 (RxCanGroup2-2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6080 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6080[] = "RxCanGroup2-2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup220x6080[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6090 : RxCanGroup2-3
******************************************************************************/
/**
* \addtogroup 0x6090 0x6090 | RxCanGroup2-3
* @{
* \brief Object 0x6090 (RxCanGroup2-3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6090 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6090[] = "RxCanGroup2-3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup230x6090[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60A0 : RxCanGroup2-4
******************************************************************************/
/**
* \addtogroup 0x60A0 0x60A0 | RxCanGroup2-4
* @{
* \brief Object 0x60A0 (RxCanGroup2-4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60A0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60A0[] = "RxCanGroup2-4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup240x60A0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60B0 : RxCanGroup2-5
******************************************************************************/
/**
* \addtogroup 0x60B0 0x60B0 | RxCanGroup2-5
* @{
* \brief Object 0x60B0 (RxCanGroup2-5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60B0[] = "RxCanGroup2-5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup250x60B0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60C0 : RxCanGroup2-6
******************************************************************************/
/**
* \addtogroup 0x60C0 0x60C0 | RxCanGroup2-6
* @{
* \brief Object 0x60C0 (RxCanGroup2-6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60C0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60C0[] = "RxCanGroup2-6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup260x60C0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60D0 : RxCanGroup2-7
******************************************************************************/
/**
* \addtogroup 0x60D0 0x60D0 | RxCanGroup2-7
* @{
* \brief Object 0x60D0 (RxCanGroup2-7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60D0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60D0[] = "RxCanGroup2-7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup270x60D0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60E0 : RxCanGroup3-1
******************************************************************************/
/**
* \addtogroup 0x60E0 0x60E0 | RxCanGroup3-1
* @{
* \brief Object 0x60E0 (RxCanGroup3-1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60E0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60E0[] = "RxCanGroup3-1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup310x60E0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x60F0 : RxCanGroup3-2
******************************************************************************/
/**
* \addtogroup 0x60F0 0x60F0 | RxCanGroup3-2
* @{
* \brief Object 0x60F0 (RxCanGroup3-2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60F0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60F0[] = "RxCanGroup3-2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup320x60F0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6100 : RxCanGroup3-3
******************************************************************************/
/**
* \addtogroup 0x6100 0x6100 | RxCanGroup3-3
* @{
* \brief Object 0x6100 (RxCanGroup3-3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6100 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6100[] = "RxCanGroup3-3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup330x6100[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6110 : RxCanGroup3-4
******************************************************************************/
/**
* \addtogroup 0x6110 0x6110 | RxCanGroup3-4
* @{
* \brief Object 0x6110 (RxCanGroup3-4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6110 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6110[] = "RxCanGroup3-4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup340x6110[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6120 : RxCanGroup3-5
******************************************************************************/
/**
* \addtogroup 0x6120 0x6120 | RxCanGroup3-5
* @{
* \brief Object 0x6120 (RxCanGroup3-5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6120 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6120[] = "RxCanGroup3-5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup350x6120[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6130 : RxCanGroup3-6
******************************************************************************/
/**
* \addtogroup 0x6130 0x6130 | RxCanGroup3-6
* @{
* \brief Object 0x6130 (RxCanGroup3-6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6130 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6130[] = "RxCanGroup3-6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup360x6130[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6140 : RxCanGroup3-7
******************************************************************************/
/**
* \addtogroup 0x6140 0x6140 | RxCanGroup3-7
* @{
* \brief Object 0x6140 (RxCanGroup3-7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6140 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6140[] = "RxCanGroup3-7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup370x6140[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6150 : RxCanGroup4-1
******************************************************************************/
/**
* \addtogroup 0x6150 0x6150 | RxCanGroup4-1
* @{
* \brief Object 0x6150 (RxCanGroup4-1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6150 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6150[] = "RxCanGroup4-1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup410x6150[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6160 : RxCanGroup4-2
******************************************************************************/
/**
* \addtogroup 0x6160 0x6160 | RxCanGroup4-2
* @{
* \brief Object 0x6160 (RxCanGroup4-2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6160 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6160[] = "RxCanGroup4-2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup420x6160[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6170 : RxCanGroup4-3
******************************************************************************/
/**
* \addtogroup 0x6170 0x6170 | RxCanGroup4-3
* @{
* \brief Object 0x6170 (RxCanGroup4-3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6170 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6170[] = "RxCanGroup4-3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup430x6170[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6180 : RxCanGroup4-4
******************************************************************************/
/**
* \addtogroup 0x6180 0x6180 | RxCanGroup4-4
* @{
* \brief Object 0x6180 (RxCanGroup4-4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6180 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6180[] = "RxCanGroup4-4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup440x6180[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6190 : RxCanGroup4-5
******************************************************************************/
/**
* \addtogroup 0x6190 0x6190 | RxCanGroup4-5
* @{
* \brief Object 0x6190 (RxCanGroup4-5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6190 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6190[] = "RxCanGroup4-5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup450x6190[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x61A0 : RxCanGroup4-6
******************************************************************************/
/**
* \addtogroup 0x61A0 0x61A0 | RxCanGroup4-6
* @{
* \brief Object 0x61A0 (RxCanGroup4-6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x61A0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x61A0[] = "RxCanGroup4-6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup460x61A0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x61B0 : RxCanGroup4-7
******************************************************************************/
/**
* \addtogroup 0x61B0 0x61B0 | RxCanGroup4-7
* @{
* \brief Object 0x61B0 (RxCanGroup4-7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x61B0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x61B0[] = "RxCanGroup4-7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCanGroup470x61B0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : TxCanGroup1-1
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | TxCanGroup1-1
* @{
* \brief Object 0x7000 (TxCanGroup1-1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7000 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "TxCanGroup1-1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup110x7000[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7010 : TxCanGroup1-2
******************************************************************************/
/**
* \addtogroup 0x7010 0x7010 | TxCanGroup1-2
* @{
* \brief Object 0x7010 (TxCanGroup1-2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7010 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7010[] = "TxCanGroup1-2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup120x7010[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7020 : TxCanGroup1-3
******************************************************************************/
/**
* \addtogroup 0x7020 0x7020 | TxCanGroup1-3
* @{
* \brief Object 0x7020 (TxCanGroup1-3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7020 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7020[] = "TxCanGroup1-3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup130x7020[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7030 : TxCanGroup1-4
******************************************************************************/
/**
* \addtogroup 0x7030 0x7030 | TxCanGroup1-4
* @{
* \brief Object 0x7030 (TxCanGroup1-4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7030 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7030[] = "TxCanGroup1-4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup140x7030[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7040 : TxCanGroup1-5
******************************************************************************/
/**
* \addtogroup 0x7040 0x7040 | TxCanGroup1-5
* @{
* \brief Object 0x7040 (TxCanGroup1-5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7040 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7040[] = "TxCanGroup1-5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup150x7040[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7050 : TxCanGroup1-6
******************************************************************************/
/**
* \addtogroup 0x7050 0x7050 | TxCanGroup1-6
* @{
* \brief Object 0x7050 (TxCanGroup1-6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7050 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7050[] = "TxCanGroup1-6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup160x7050[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7060 : TxCanGroup1-7
******************************************************************************/
/**
* \addtogroup 0x7060 0x7060 | TxCanGroup1-7
* @{
* \brief Object 0x7060 (TxCanGroup1-7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7060 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7060[] = "TxCanGroup1-7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup170x7060[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7070 : TxCanGroup2-1
******************************************************************************/
/**
* \addtogroup 0x7070 0x7070 | TxCanGroup2-1
* @{
* \brief Object 0x7070 (TxCanGroup2-1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7070 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7070[] = "TxCanGroup2-1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup210x7070[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7080 : TxCanGroup2-2
******************************************************************************/
/**
* \addtogroup 0x7080 0x7080 | TxCanGroup2-2
* @{
* \brief Object 0x7080 (TxCanGroup2-2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7080 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7080[] = "TxCanGroup2-2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup220x7080[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7090 : TxCanGroup2-3
******************************************************************************/
/**
* \addtogroup 0x7090 0x7090 | TxCanGroup2-3
* @{
* \brief Object 0x7090 (TxCanGroup2-3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7090 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7090[] = "TxCanGroup2-3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup230x7090[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x70A0 : TxCanGroup2-4
******************************************************************************/
/**
* \addtogroup 0x70A0 0x70A0 | TxCanGroup2-4
* @{
* \brief Object 0x70A0 (TxCanGroup2-4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70A0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70A0[] = "TxCanGroup2-4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup240x70A0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x70B0 : TxCanGroup2-5
******************************************************************************/
/**
* \addtogroup 0x70B0 0x70B0 | TxCanGroup2-5
* @{
* \brief Object 0x70B0 (TxCanGroup2-5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70B0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70B0[] = "TxCanGroup2-5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup250x70B0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x70C0 : TxCanGroup2-6
******************************************************************************/
/**
* \addtogroup 0x70C0 0x70C0 | TxCanGroup2-6
* @{
* \brief Object 0x70C0 (TxCanGroup2-6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70C0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70C0[] = "TxCanGroup2-6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup260x70C0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x70D0 : TxCanGroup2-7
******************************************************************************/
/**
* \addtogroup 0x70D0 0x70D0 | TxCanGroup2-7
* @{
* \brief Object 0x70D0 (TxCanGroup2-7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70D0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70D0[] = "TxCanGroup2-7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup270x70D0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x70E0 : TxCanGroup3-1
******************************************************************************/
/**
* \addtogroup 0x70E0 0x70E0 | TxCanGroup3-1
* @{
* \brief Object 0x70E0 (TxCanGroup3-1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70E0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70E0[] = "TxCanGroup3-1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup310x70E0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x70F0 : TxCanGroup3-2
******************************************************************************/
/**
* \addtogroup 0x70F0 0x70F0 | TxCanGroup3-2
* @{
* \brief Object 0x70F0 (TxCanGroup3-2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70F0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70F0[] = "TxCanGroup3-2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup320x70F0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7100 : TxCanGroup3-3
******************************************************************************/
/**
* \addtogroup 0x7100 0x7100 | TxCanGroup3-3
* @{
* \brief Object 0x7100 (TxCanGroup3-3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7100 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7100[] = "TxCanGroup3-3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup330x7100[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7110 : TxCanGroup3-4
******************************************************************************/
/**
* \addtogroup 0x7110 0x7110 | TxCanGroup3-4
* @{
* \brief Object 0x7110 (TxCanGroup3-4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7110 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7110[] = "TxCanGroup3-4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup340x7110[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7120 : TxCanGroup3-5
******************************************************************************/
/**
* \addtogroup 0x7120 0x7120 | TxCanGroup3-5
* @{
* \brief Object 0x7120 (TxCanGroup3-5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7120 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7120[] = "TxCanGroup3-5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup350x7120[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7130 : TxCanGroup3-6
******************************************************************************/
/**
* \addtogroup 0x7130 0x7130 | TxCanGroup3-6
* @{
* \brief Object 0x7130 (TxCanGroup3-6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7130 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7130[] = "TxCanGroup3-6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup360x7130[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7140 : TxCanGroup3-7
******************************************************************************/
/**
* \addtogroup 0x7140 0x7140 | TxCanGroup3-7
* @{
* \brief Object 0x7140 (TxCanGroup3-7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7140 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7140[] = "TxCanGroup3-7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup370x7140[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7150 : TxCanGroup4-1
******************************************************************************/
/**
* \addtogroup 0x7150 0x7150 | TxCanGroup4-1
* @{
* \brief Object 0x7150 (TxCanGroup4-1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7150 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7150[] = "TxCanGroup4-1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup410x7150[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7160 : TxCanGroup4-2
******************************************************************************/
/**
* \addtogroup 0x7160 0x7160 | TxCanGroup4-2
* @{
* \brief Object 0x7160 (TxCanGroup4-2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7160 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7160[] = "TxCanGroup4-2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup420x7160[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7170 : TxCanGroup4-3
******************************************************************************/
/**
* \addtogroup 0x7170 0x7170 | TxCanGroup4-3
* @{
* \brief Object 0x7170 (TxCanGroup4-3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7170 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7170[] = "TxCanGroup4-3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup430x7170[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7180 : TxCanGroup4-4
******************************************************************************/
/**
* \addtogroup 0x7180 0x7180 | TxCanGroup4-4
* @{
* \brief Object 0x7180 (TxCanGroup4-4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7180 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7180[] = "TxCanGroup4-4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup440x7180[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7190 : TxCanGroup4-5
******************************************************************************/
/**
* \addtogroup 0x7190 0x7190 | TxCanGroup4-5
* @{
* \brief Object 0x7190 (TxCanGroup4-5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7190 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7190[] = "TxCanGroup4-5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup450x7190[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x71A0 : TxCanGroup4-6
******************************************************************************/
/**
* \addtogroup 0x71A0 0x71A0 | TxCanGroup4-6
* @{
* \brief Object 0x71A0 (TxCanGroup4-6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x71A0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x71A0[] = "TxCanGroup4-6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup460x71A0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x71B0 : TxCanGroup4-7
******************************************************************************/
/**
* \addtogroup 0x71B0 0x71B0 | TxCanGroup4-7
* @{
* \brief Object 0x71B0 (TxCanGroup4-7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x71B0 = { DEFTYPE_VISIBLESTRING , 0x80 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x71B0[] = "TxCanGroup4-7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCanGroup470x71B0[16]
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
= "0"
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0xF000 : Modular Device Profile
******************************************************************************/
/**
* \addtogroup 0xF000 0xF000 | Modular Device Profile
* @{
* \brief Object 0xF000 (Modular Device Profile) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Index distance <br>
* SubIndex 2 - Maximum number of modules <br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex1 - Index distance  */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }}; /* Subindex2 - Maximum number of modules  */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0xF000[] = "Modular Device Profile\000"
"Index distance \000"
"Maximum number of modules \000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IndexDistance; /* Subindex1 - Index distance  */
UINT16 MaximumNumberOfModules; /* Subindex2 - Maximum number of modules  */
} OBJ_STRUCT_PACKED_END
TOBJF000;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJF000 ModularDeviceProfile0xF000
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={2,0x0010,0}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 28 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &OutputMapping00x1600 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 28 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &InputMapping00x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6000 , aName0x6000 , RxCanGroup110x6000 , NULL , NULL , 0x0000 },
/* Object 0x6010 */
{NULL , NULL ,  0x6010 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6010 , aName0x6010 , RxCanGroup120x6010 , NULL , NULL , 0x0000 },
/* Object 0x6020 */
{NULL , NULL ,  0x6020 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6020 , aName0x6020 , RxCanGroup130x6020 , NULL , NULL , 0x0000 },
/* Object 0x6030 */
{NULL , NULL ,  0x6030 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6030 , aName0x6030 , RxCanGroup140x6030 , NULL , NULL , 0x0000 },
/* Object 0x6040 */
{NULL , NULL ,  0x6040 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6040 , aName0x6040 , RxCanGroup150x6040 , NULL , NULL , 0x0000 },
/* Object 0x6050 */
{NULL , NULL ,  0x6050 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6050 , aName0x6050 , RxCanGroup160x6050 , NULL , NULL , 0x0000 },
/* Object 0x6060 */
{NULL , NULL ,  0x6060 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6060 , aName0x6060 , RxCanGroup170x6060 , NULL , NULL , 0x0000 },
/* Object 0x6070 */
{NULL , NULL ,  0x6070 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6070 , aName0x6070 , RxCanGroup210x6070 , NULL , NULL , 0x0000 },
/* Object 0x6080 */
{NULL , NULL ,  0x6080 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6080 , aName0x6080 , RxCanGroup220x6080 , NULL , NULL , 0x0000 },
/* Object 0x6090 */
{NULL , NULL ,  0x6090 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6090 , aName0x6090 , RxCanGroup230x6090 , NULL , NULL , 0x0000 },
/* Object 0x60A0 */
{NULL , NULL ,  0x60A0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60A0 , aName0x60A0 , RxCanGroup240x60A0 , NULL , NULL , 0x0000 },
/* Object 0x60B0 */
{NULL , NULL ,  0x60B0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60B0 , aName0x60B0 , RxCanGroup250x60B0 , NULL , NULL , 0x0000 },
/* Object 0x60C0 */
{NULL , NULL ,  0x60C0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60C0 , aName0x60C0 , RxCanGroup260x60C0 , NULL , NULL , 0x0000 },
/* Object 0x60D0 */
{NULL , NULL ,  0x60D0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60D0 , aName0x60D0 , RxCanGroup270x60D0 , NULL , NULL , 0x0000 },
/* Object 0x60E0 */
{NULL , NULL ,  0x60E0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60E0 , aName0x60E0 , RxCanGroup310x60E0 , NULL , NULL , 0x0000 },
/* Object 0x60F0 */
{NULL , NULL ,  0x60F0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60F0 , aName0x60F0 , RxCanGroup320x60F0 , NULL , NULL , 0x0000 },
/* Object 0x6100 */
{NULL , NULL ,  0x6100 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6100 , aName0x6100 , RxCanGroup330x6100 , NULL , NULL , 0x0000 },
/* Object 0x6110 */
{NULL , NULL ,  0x6110 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6110 , aName0x6110 , RxCanGroup340x6110 , NULL , NULL , 0x0000 },
/* Object 0x6120 */
{NULL , NULL ,  0x6120 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6120 , aName0x6120 , RxCanGroup350x6120 , NULL , NULL , 0x0000 },
/* Object 0x6130 */
{NULL , NULL ,  0x6130 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6130 , aName0x6130 , RxCanGroup360x6130 , NULL , NULL , 0x0000 },
/* Object 0x6140 */
{NULL , NULL ,  0x6140 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6140 , aName0x6140 , RxCanGroup370x6140 , NULL , NULL , 0x0000 },
/* Object 0x6150 */
{NULL , NULL ,  0x6150 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6150 , aName0x6150 , RxCanGroup410x6150 , NULL , NULL , 0x0000 },
/* Object 0x6160 */
{NULL , NULL ,  0x6160 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6160 , aName0x6160 , RxCanGroup420x6160 , NULL , NULL , 0x0000 },
/* Object 0x6170 */
{NULL , NULL ,  0x6170 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6170 , aName0x6170 , RxCanGroup430x6170 , NULL , NULL , 0x0000 },
/* Object 0x6180 */
{NULL , NULL ,  0x6180 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6180 , aName0x6180 , RxCanGroup440x6180 , NULL , NULL , 0x0000 },
/* Object 0x6190 */
{NULL , NULL ,  0x6190 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6190 , aName0x6190 , RxCanGroup450x6190 , NULL , NULL , 0x0000 },
/* Object 0x61A0 */
{NULL , NULL ,  0x61A0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x61A0 , aName0x61A0 , RxCanGroup460x61A0 , NULL , NULL , 0x0000 },
/* Object 0x61B0 */
{NULL , NULL ,  0x61B0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x61B0 , aName0x61B0 , RxCanGroup470x61B0 , NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7000 , aName0x7000 , TxCanGroup110x7000 , NULL , NULL , 0x0000 },
/* Object 0x7010 */
{NULL , NULL ,  0x7010 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7010 , aName0x7010 , TxCanGroup120x7010 , NULL , NULL , 0x0000 },
/* Object 0x7020 */
{NULL , NULL ,  0x7020 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7020 , aName0x7020 , TxCanGroup130x7020 , NULL , NULL , 0x0000 },
/* Object 0x7030 */
{NULL , NULL ,  0x7030 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7030 , aName0x7030 , TxCanGroup140x7030 , NULL , NULL , 0x0000 },
/* Object 0x7040 */
{NULL , NULL ,  0x7040 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7040 , aName0x7040 , TxCanGroup150x7040 , NULL , NULL , 0x0000 },
/* Object 0x7050 */
{NULL , NULL ,  0x7050 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7050 , aName0x7050 , TxCanGroup160x7050 , NULL , NULL , 0x0000 },
/* Object 0x7060 */
{NULL , NULL ,  0x7060 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7060 , aName0x7060 , TxCanGroup170x7060 , NULL , NULL , 0x0000 },
/* Object 0x7070 */
{NULL , NULL ,  0x7070 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7070 , aName0x7070 , TxCanGroup210x7070 , NULL , NULL , 0x0000 },
/* Object 0x7080 */
{NULL , NULL ,  0x7080 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7080 , aName0x7080 , TxCanGroup220x7080 , NULL , NULL , 0x0000 },
/* Object 0x7090 */
{NULL , NULL ,  0x7090 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7090 , aName0x7090 , TxCanGroup230x7090 , NULL , NULL , 0x0000 },
/* Object 0x70A0 */
{NULL , NULL ,  0x70A0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70A0 , aName0x70A0 , TxCanGroup240x70A0 , NULL , NULL , 0x0000 },
/* Object 0x70B0 */
{NULL , NULL ,  0x70B0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70B0 , aName0x70B0 , TxCanGroup250x70B0 , NULL , NULL , 0x0000 },
/* Object 0x70C0 */
{NULL , NULL ,  0x70C0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70C0 , aName0x70C0 , TxCanGroup260x70C0 , NULL , NULL , 0x0000 },
/* Object 0x70D0 */
{NULL , NULL ,  0x70D0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70D0 , aName0x70D0 , TxCanGroup270x70D0 , NULL , NULL , 0x0000 },
/* Object 0x70E0 */
{NULL , NULL ,  0x70E0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70E0 , aName0x70E0 , TxCanGroup310x70E0 , NULL , NULL , 0x0000 },
/* Object 0x70F0 */
{NULL , NULL ,  0x70F0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70F0 , aName0x70F0 , TxCanGroup320x70F0 , NULL , NULL , 0x0000 },
/* Object 0x7100 */
{NULL , NULL ,  0x7100 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7100 , aName0x7100 , TxCanGroup330x7100 , NULL , NULL , 0x0000 },
/* Object 0x7110 */
{NULL , NULL ,  0x7110 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7110 , aName0x7110 , TxCanGroup340x7110 , NULL , NULL , 0x0000 },
/* Object 0x7120 */
{NULL , NULL ,  0x7120 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7120 , aName0x7120 , TxCanGroup350x7120 , NULL , NULL , 0x0000 },
/* Object 0x7130 */
{NULL , NULL ,  0x7130 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7130 , aName0x7130 , TxCanGroup360x7130 , NULL , NULL , 0x0000 },
/* Object 0x7140 */
{NULL , NULL ,  0x7140 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7140 , aName0x7140 , TxCanGroup370x7140 , NULL , NULL , 0x0000 },
/* Object 0x7150 */
{NULL , NULL ,  0x7150 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7150 , aName0x7150 , TxCanGroup410x7150 , NULL , NULL , 0x0000 },
/* Object 0x7160 */
{NULL , NULL ,  0x7160 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7160 , aName0x7160 , TxCanGroup420x7160 , NULL , NULL , 0x0000 },
/* Object 0x7170 */
{NULL , NULL ,  0x7170 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7170 , aName0x7170 , TxCanGroup430x7170 , NULL , NULL , 0x0000 },
/* Object 0x7180 */
{NULL , NULL ,  0x7180 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7180 , aName0x7180 , TxCanGroup440x7180 , NULL , NULL , 0x0000 },
/* Object 0x7190 */
{NULL , NULL ,  0x7190 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7190 , aName0x7190 , TxCanGroup450x7190 , NULL , NULL , 0x0000 },
/* Object 0x71A0 */
{NULL , NULL ,  0x71A0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x71A0 , aName0x71A0 , TxCanGroup460x71A0 , NULL , NULL , 0x0000 },
/* Object 0x71B0 */
{NULL , NULL ,  0x71B0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x71B0 , aName0x71B0 , TxCanGroup470x71B0 , NULL , NULL , 0x0000 },
/* Object 0xF000 */
{NULL , NULL ,  0xF000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0xF000 , aName0xF000 , &ModularDeviceProfile0xF000 , NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_

#undef PROTO

/** @}*/
#define _DIGITAL_IO_OBJECTS_H_
