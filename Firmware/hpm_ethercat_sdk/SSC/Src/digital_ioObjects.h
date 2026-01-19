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
\author ET9300Utilities.ApplicationHandler (Version 1.5.0.0) | EthercatSSC@beckhoff.com

\brief digital_io specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : TxCan0 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | TxCan0 process data mapping
* @{
* \brief Object 0x1600 (TxCan0 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x7000.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "TxCan0 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 TxCan0ProcessDataMapping0x1600
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x700000F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1601 : TxCan1 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1601 0x1601 | TxCan1 process data mapping
* @{
* \brief Object 0x1601 (TxCan1 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x701E.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1601[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x701E.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1601[] = "TxCan1 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x701E.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1601;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1601 TxCan1ProcessDataMapping0x1601
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x701E00F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1603 : TxCan2 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1603 0x1603 | TxCan2 process data mapping
* @{
* \brief Object 0x1603 (TxCan2 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x703C.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1603[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x703C.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1603[] = "TxCan2 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x703C.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1603;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1603 TxCan2ProcessDataMapping0x1603
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x703C00F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1605 : TxCan3 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1605 0x1605 | TxCan3 process data mapping
* @{
* \brief Object 0x1605 (TxCan3 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x705A.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1605[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x705A.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1605[] = "TxCan3 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x705A.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1605;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1605 TxCan3ProcessDataMapping0x1605
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x705A00F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1607 : TxCan4 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1607 0x1607 | TxCan4 process data mapping
* @{
* \brief Object 0x1607 (TxCan4 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7078.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1607[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x7078.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1607[] = "TxCan4 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7078.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1607;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1607 TxCan4ProcessDataMapping0x1607
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x707800F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1609 : TxCan5 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1609 0x1609 | TxCan5 process data mapping
* @{
* \brief Object 0x1609 (TxCan5 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7096.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1609[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x7096.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1609[] = "TxCan5 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7096.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1609;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1609 TxCan5ProcessDataMapping0x1609
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x709600F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x160B : TxCan6 process data mapping
******************************************************************************/
/**
* \addtogroup 0x160B 0x160B | TxCan6 process data mapping
* @{
* \brief Object 0x160B (TxCan6 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x70B4.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x160B[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x70B4.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x160B[] = "TxCan6 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x70B4.0 */
} OBJ_STRUCT_PACKED_END
TOBJ160B;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ160B TxCan6ProcessDataMapping0x160B
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x70B400F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x160D : TxCan7 process data mapping
******************************************************************************/
/**
* \addtogroup 0x160D 0x160D | TxCan7 process data mapping
* @{
* \brief Object 0x160D (TxCan7 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x70D2.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x160D[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x70D2.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x160D[] = "TxCan7 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x70D2.0 */
} OBJ_STRUCT_PACKED_END
TOBJ160D;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ160D TxCan7ProcessDataMapping0x160D
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x70D200F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x160F : TxCan8 process data mapping
******************************************************************************/
/**
* \addtogroup 0x160F 0x160F | TxCan8 process data mapping
* @{
* \brief Object 0x160F (TxCan8 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x70F0.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x160F[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x70F0.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x160F[] = "TxCan8 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x70F0.0 */
} OBJ_STRUCT_PACKED_END
TOBJ160F;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ160F TxCan8ProcessDataMapping0x160F
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x70F000F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1610 : TxCan9 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1610 0x1610 | TxCan9 process data mapping
* @{
* \brief Object 0x1610 (TxCan9 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x710E.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1610[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x710E.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1610[] = "TxCan9 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x710E.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1610;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1610 TxCan9ProcessDataMapping0x1610
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x710E00F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : RxCan0 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | RxCan0 process data mapping
* @{
* \brief Object 0x1A00 (RxCan0 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6000.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x6000.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "RxCan0 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6000.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 RxCan0ProcessDataMapping0x1A00
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x600000F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A01 : RxCan1 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A01 0x1A01 | RxCan1 process data mapping
* @{
* \brief Object 0x1A01 (RxCan1 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x601E.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A01[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x601E.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A01[] = "RxCan1 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x601E.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A01;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A01 RxCan1ProcessDataMapping0x1A01
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x601E00F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A03 : RxCan2 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A03 0x1A03 | RxCan2 process data mapping
* @{
* \brief Object 0x1A03 (RxCan2 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x603C.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A03[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x603C.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A03[] = "RxCan2 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x603C.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A03;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A03 RxCan2ProcessDataMapping0x1A03
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x603C00F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A05 : RxCan3 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A05 0x1A05 | RxCan3 process data mapping
* @{
* \brief Object 0x1A05 (RxCan3 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x605A.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A05[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x605A.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A05[] = "RxCan3 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x605A.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A05;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A05 RxCan3ProcessDataMapping0x1A05
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x605A00F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A07 : RxCan4 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A07 0x1A07 | RxCan4 process data mapping
* @{
* \brief Object 0x1A07 (RxCan4 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6078.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A07[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x6078.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A07[] = "RxCan4 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6078.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A07;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A07 RxCan4ProcessDataMapping0x1A07
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x607800F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A09 : RxCan5 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A09 0x1A09 | RxCan5 process data mapping
* @{
* \brief Object 0x1A09 (RxCan5 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6096.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A09[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x6096.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A09[] = "RxCan5 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6096.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A09;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A09 RxCan5ProcessDataMapping0x1A09
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x609600F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A0B : RxCan6 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A0B 0x1A0B | RxCan6 process data mapping
* @{
* \brief Object 0x1A0B (RxCan6 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x60B4.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A0B[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x60B4.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A0B[] = "RxCan6 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x60B4.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A0B;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A0B RxCan6ProcessDataMapping0x1A0B
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x60B400F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A0D : RxCan7 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A0D 0x1A0D | RxCan7 process data mapping
* @{
* \brief Object 0x1A0D (RxCan7 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x60D2.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A0D[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x60D2.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A0D[] = "RxCan7 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x60D2.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A0D;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A0D RxCan7ProcessDataMapping0x1A0D
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x60D200F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A0F : RxCan8 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A0F 0x1A0F | RxCan8 process data mapping
* @{
* \brief Object 0x1A0F (RxCan8 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x60F0.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A0F[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x60F0.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A0F[] = "RxCan8 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x60F0.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A0F;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A0F RxCan8ProcessDataMapping0x1A0F
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x60F000F0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A10 : RxCan9 process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A10 0x1A10 | RxCan9 process data mapping
* @{
* \brief Object 0x1A10 (RxCan9 process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x610E.0<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A10[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 - Reference to 0x610E.0 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A10[] = "RxCan9 process data mapping\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _DIGITAL_IO_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x610E.0 */
} OBJ_STRUCT_PACKED_END
TOBJ1A10;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A10 RxCan9ProcessDataMapping0x1A10
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={1,0x610E00F0}
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
UINT16 aEntries[10];  /**< \brief Subindex 1 - 10 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={10,{0x1600,0x1601,0x1603,0x1605,0x1607,0x1609,0x160B,0x160D,0x160F,0x1610}}
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
UINT16 aEntries[10];  /**< \brief Subindex 1 - 10 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _DIGITAL_IO_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_DIGITAL_IO_) && (_DIGITAL_IO_ == 1)
={10,{0x1A00,0x1A01,0x1A03,0x1A05,0x1A07,0x1A09,0x1A0B,0x1A0D,0x1A0F,0x1A10}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : RxCan0
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | RxCan0
* @{
* \brief Object 0x6000 (RxCan0) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6000 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "RxCan0\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan00x6000[30];
/** @}*/



/******************************************************************************
*                    Object 0x601E : RxCan1
******************************************************************************/
/**
* \addtogroup 0x601E 0x601E | RxCan1
* @{
* \brief Object 0x601E (RxCan1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x601E = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x601E[] = "RxCan1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan10x601E[30];
/** @}*/



/******************************************************************************
*                    Object 0x603C : RxCan2
******************************************************************************/
/**
* \addtogroup 0x603C 0x603C | RxCan2
* @{
* \brief Object 0x603C (RxCan2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x603C = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x603C[] = "RxCan2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan20x603C[30];
/** @}*/



/******************************************************************************
*                    Object 0x605A : RxCan3
******************************************************************************/
/**
* \addtogroup 0x605A 0x605A | RxCan3
* @{
* \brief Object 0x605A (RxCan3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x605A = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x605A[] = "RxCan3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan30x605A[30];
/** @}*/



/******************************************************************************
*                    Object 0x6078 : RxCan4
******************************************************************************/
/**
* \addtogroup 0x6078 0x6078 | RxCan4
* @{
* \brief Object 0x6078 (RxCan4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6078 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6078[] = "RxCan4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan40x6078[30];
/** @}*/



/******************************************************************************
*                    Object 0x6096 : RxCan5
******************************************************************************/
/**
* \addtogroup 0x6096 0x6096 | RxCan5
* @{
* \brief Object 0x6096 (RxCan5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x6096 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x6096[] = "RxCan5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan50x6096[30];
/** @}*/



/******************************************************************************
*                    Object 0x60B4 : RxCan6
******************************************************************************/
/**
* \addtogroup 0x60B4 0x60B4 | RxCan6
* @{
* \brief Object 0x60B4 (RxCan6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60B4 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60B4[] = "RxCan6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan60x60B4[30];
/** @}*/



/******************************************************************************
*                    Object 0x60D2 : RxCan7
******************************************************************************/
/**
* \addtogroup 0x60D2 0x60D2 | RxCan7
* @{
* \brief Object 0x60D2 (RxCan7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60D2 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60D2[] = "RxCan7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan70x60D2[30];
/** @}*/



/******************************************************************************
*                    Object 0x60F0 : RxCan8
******************************************************************************/
/**
* \addtogroup 0x60F0 0x60F0 | RxCan8
* @{
* \brief Object 0x60F0 (RxCan8) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x60F0 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x60F0[] = "RxCan8\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan80x60F0[30];
/** @}*/



/******************************************************************************
*                    Object 0x610E : RxCan9
******************************************************************************/
/**
* \addtogroup 0x610E 0x610E | RxCan9
* @{
* \brief Object 0x610E (RxCan9) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x610E = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x610E[] = "RxCan9\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR RxCan90x610E[30];
/** @}*/



/******************************************************************************
*                    Object 0x7000 : TxCan0
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | TxCan0
* @{
* \brief Object 0x7000 (TxCan0) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7000 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "TxCan0\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan00x7000[30];
/** @}*/



/******************************************************************************
*                    Object 0x701E : TxCan1
******************************************************************************/
/**
* \addtogroup 0x701E 0x701E | TxCan1
* @{
* \brief Object 0x701E (TxCan1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x701E = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x701E[] = "TxCan1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan10x701E[30];
/** @}*/



/******************************************************************************
*                    Object 0x703C : TxCan2
******************************************************************************/
/**
* \addtogroup 0x703C 0x703C | TxCan2
* @{
* \brief Object 0x703C (TxCan2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x703C = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x703C[] = "TxCan2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan20x703C[30];
/** @}*/



/******************************************************************************
*                    Object 0x705A : TxCan3
******************************************************************************/
/**
* \addtogroup 0x705A 0x705A | TxCan3
* @{
* \brief Object 0x705A (TxCan3) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x705A = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x705A[] = "TxCan3\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan30x705A[30];
/** @}*/



/******************************************************************************
*                    Object 0x7078 : TxCan4
******************************************************************************/
/**
* \addtogroup 0x7078 0x7078 | TxCan4
* @{
* \brief Object 0x7078 (TxCan4) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7078 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7078[] = "TxCan4\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan40x7078[30];
/** @}*/



/******************************************************************************
*                    Object 0x7096 : TxCan5
******************************************************************************/
/**
* \addtogroup 0x7096 0x7096 | TxCan5
* @{
* \brief Object 0x7096 (TxCan5) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x7096 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x7096[] = "TxCan5\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan50x7096[30];
/** @}*/



/******************************************************************************
*                    Object 0x70B4 : TxCan6
******************************************************************************/
/**
* \addtogroup 0x70B4 0x70B4 | TxCan6
* @{
* \brief Object 0x70B4 (TxCan6) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70B4 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70B4[] = "TxCan6\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan60x70B4[30];
/** @}*/



/******************************************************************************
*                    Object 0x70D2 : TxCan7
******************************************************************************/
/**
* \addtogroup 0x70D2 0x70D2 | TxCan7
* @{
* \brief Object 0x70D2 (TxCan7) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70D2 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70D2[] = "TxCan7\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan70x70D2[30];
/** @}*/



/******************************************************************************
*                    Object 0x70F0 : TxCan8
******************************************************************************/
/**
* \addtogroup 0x70F0 0x70F0 | TxCan8
* @{
* \brief Object 0x70F0 (TxCan8) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x70F0 = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x70F0[] = "TxCan8\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan80x70F0[30];
/** @}*/



/******************************************************************************
*                    Object 0x710E : TxCan9
******************************************************************************/
/**
* \addtogroup 0x710E 0x710E | TxCan9
* @{
* \brief Object 0x710E (TxCan9) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x710E = { DEFTYPE_VISIBLESTRING , 0xF0 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x710E[] = "TxCan9\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO CHAR TxCan90x710E[30];
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
={2,0,0}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &TxCan0ProcessDataMapping0x1600 , NULL , NULL , 0x0000 },
/* Object 0x1601 */
{NULL , NULL ,  0x1601 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1601 , aName0x1601 , &TxCan1ProcessDataMapping0x1601 , NULL , NULL , 0x0000 },
/* Object 0x1603 */
{NULL , NULL ,  0x1603 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1603 , aName0x1603 , &TxCan2ProcessDataMapping0x1603 , NULL , NULL , 0x0000 },
/* Object 0x1605 */
{NULL , NULL ,  0x1605 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1605 , aName0x1605 , &TxCan3ProcessDataMapping0x1605 , NULL , NULL , 0x0000 },
/* Object 0x1607 */
{NULL , NULL ,  0x1607 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1607 , aName0x1607 , &TxCan4ProcessDataMapping0x1607 , NULL , NULL , 0x0000 },
/* Object 0x1609 */
{NULL , NULL ,  0x1609 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1609 , aName0x1609 , &TxCan5ProcessDataMapping0x1609 , NULL , NULL , 0x0000 },
/* Object 0x160B */
{NULL , NULL ,  0x160B , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x160B , aName0x160B , &TxCan6ProcessDataMapping0x160B , NULL , NULL , 0x0000 },
/* Object 0x160D */
{NULL , NULL ,  0x160D , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x160D , aName0x160D , &TxCan7ProcessDataMapping0x160D , NULL , NULL , 0x0000 },
/* Object 0x160F */
{NULL , NULL ,  0x160F , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x160F , aName0x160F , &TxCan8ProcessDataMapping0x160F , NULL , NULL , 0x0000 },
/* Object 0x1610 */
{NULL , NULL ,  0x1610 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1610 , aName0x1610 , &TxCan9ProcessDataMapping0x1610 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &RxCan0ProcessDataMapping0x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1A01 */
{NULL , NULL ,  0x1A01 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A01 , aName0x1A01 , &RxCan1ProcessDataMapping0x1A01 , NULL , NULL , 0x0000 },
/* Object 0x1A03 */
{NULL , NULL ,  0x1A03 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A03 , aName0x1A03 , &RxCan2ProcessDataMapping0x1A03 , NULL , NULL , 0x0000 },
/* Object 0x1A05 */
{NULL , NULL ,  0x1A05 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A05 , aName0x1A05 , &RxCan3ProcessDataMapping0x1A05 , NULL , NULL , 0x0000 },
/* Object 0x1A07 */
{NULL , NULL ,  0x1A07 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A07 , aName0x1A07 , &RxCan4ProcessDataMapping0x1A07 , NULL , NULL , 0x0000 },
/* Object 0x1A09 */
{NULL , NULL ,  0x1A09 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A09 , aName0x1A09 , &RxCan5ProcessDataMapping0x1A09 , NULL , NULL , 0x0000 },
/* Object 0x1A0B */
{NULL , NULL ,  0x1A0B , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A0B , aName0x1A0B , &RxCan6ProcessDataMapping0x1A0B , NULL , NULL , 0x0000 },
/* Object 0x1A0D */
{NULL , NULL ,  0x1A0D , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A0D , aName0x1A0D , &RxCan7ProcessDataMapping0x1A0D , NULL , NULL , 0x0000 },
/* Object 0x1A0F */
{NULL , NULL ,  0x1A0F , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A0F , aName0x1A0F , &RxCan8ProcessDataMapping0x1A0F , NULL , NULL , 0x0000 },
/* Object 0x1A10 */
{NULL , NULL ,  0x1A10 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1A10 , aName0x1A10 , &RxCan9ProcessDataMapping0x1A10 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 10 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 10 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6000 , aName0x6000 , &RxCan00x6000 , NULL , NULL , 0x0000 },
/* Object 0x601E */
{NULL , NULL ,  0x601E , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x601E , aName0x601E , &RxCan10x601E , NULL , NULL , 0x0000 },
/* Object 0x603C */
{NULL , NULL ,  0x603C , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x603C , aName0x603C , &RxCan20x603C , NULL , NULL , 0x0000 },
/* Object 0x605A */
{NULL , NULL ,  0x605A , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x605A , aName0x605A , &RxCan30x605A , NULL , NULL , 0x0000 },
/* Object 0x6078 */
{NULL , NULL ,  0x6078 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6078 , aName0x6078 , &RxCan40x6078 , NULL , NULL , 0x0000 },
/* Object 0x6096 */
{NULL , NULL ,  0x6096 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x6096 , aName0x6096 , &RxCan50x6096 , NULL , NULL , 0x0000 },
/* Object 0x60B4 */
{NULL , NULL ,  0x60B4 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60B4 , aName0x60B4 , &RxCan60x60B4 , NULL , NULL , 0x0000 },
/* Object 0x60D2 */
{NULL , NULL ,  0x60D2 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60D2 , aName0x60D2 , &RxCan70x60D2 , NULL , NULL , 0x0000 },
/* Object 0x60F0 */
{NULL , NULL ,  0x60F0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x60F0 , aName0x60F0 , &RxCan80x60F0 , NULL , NULL , 0x0000 },
/* Object 0x610E */
{NULL , NULL ,  0x610E , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x610E , aName0x610E , &RxCan90x610E , NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7000 , aName0x7000 , &TxCan00x7000 , NULL , NULL , 0x0000 },
/* Object 0x701E */
{NULL , NULL ,  0x701E , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x701E , aName0x701E , &TxCan10x701E , NULL , NULL , 0x0000 },
/* Object 0x703C */
{NULL , NULL ,  0x703C , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x703C , aName0x703C , &TxCan20x703C , NULL , NULL , 0x0000 },
/* Object 0x705A */
{NULL , NULL ,  0x705A , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x705A , aName0x705A , &TxCan30x705A , NULL , NULL , 0x0000 },
/* Object 0x7078 */
{NULL , NULL ,  0x7078 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7078 , aName0x7078 , &TxCan40x7078 , NULL , NULL , 0x0000 },
/* Object 0x7096 */
{NULL , NULL ,  0x7096 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x7096 , aName0x7096 , &TxCan50x7096 , NULL , NULL , 0x0000 },
/* Object 0x70B4 */
{NULL , NULL ,  0x70B4 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70B4 , aName0x70B4 , &TxCan60x70B4 , NULL , NULL , 0x0000 },
/* Object 0x70D2 */
{NULL , NULL ,  0x70D2 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70D2 , aName0x70D2 , &TxCan70x70D2 , NULL , NULL , 0x0000 },
/* Object 0x70F0 */
{NULL , NULL ,  0x70F0 , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x70F0 , aName0x70F0 , &TxCan80x70F0 , NULL , NULL , 0x0000 },
/* Object 0x710E */
{NULL , NULL ,  0x710E , {DEFTYPE_VISIBLESTRING , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x710E , aName0x710E , &TxCan90x710E , NULL , NULL , 0x0000 },
/* Object 0xF000 */
{NULL , NULL ,  0xF000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0xF000 , aName0xF000 , &ModularDeviceProfile0xF000 , NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _DIGITAL_IO_OBJECTS_H_
