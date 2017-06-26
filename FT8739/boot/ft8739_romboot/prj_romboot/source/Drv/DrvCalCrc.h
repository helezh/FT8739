/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: DrvCalCrc.h
*
*    Author: tangsujun
*
*   Created: 2016-12-22
*
*  Abstract: Calculate crc module
*
* Reference:
*
*******************************************************************************/
#ifndef __DRV_CAL_CRC_H__
#define __DRV_CAL_CRC_H__

/*******************************************************************************
* Included header files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* Private constant and macro definitions using #define
*******************************************************************************/
#define CRC_TYPE_DRAM  0
#define CRC_TYPE_PRAM  1

/* CAL reg Start Addr */
#define CAL_REG_BASE_ADDR       0xB000

#if _CRC_CAL_EN
#define CRC_TYPE        0     // 0:crc16,1:xorsum

// CRC数据源片区
#define CRC_SRC_DRAM            0   // 00
#define CRC_SRC_PAL             1   // 01, FC:0000 -- FD:FFFF
#define CRC_SRC_PAH             3   // 11, FE:0000 -- FF:FFFF

#define OP_CRC                 (0x09<<4)

/*******************************************************************************
* Private enumerations, structures and unions using typedef
*******************************************************************************/
#if 0
// cal
typedef struct
{
    UINT16 cmd;           // (0x00<<1)
    UINT16 DmaLen;        // (0x01<<1)
    UINT16 S1Addr;        // (0x02<<1)
    UINT16 S2Addr;        // (0x03<<1)
    UINT16 OutAddr;       // (0x04<<1)
    UINT16 Par;           // (0x05<<1)
    UINT16 Size;          // (0x06<<1)
    UINT16 PThd;          // (0x07<<1)
    UINT16 NThd;          // (0x08<<1)
    UINT16 AThd;          // (0x09<<1)
    UINT16 Dmask;         // (0x0A<<1)
    UINT16 PaCnt;         // (0x0B<<1)
    UINT16 NaCnt;         // (0x0C<<1)
    UINT16 PsCnt;         // (0x0D<<1)
    UINT16 NsCnt;         // (0x0E<<1)
    UINT16 MaxV;          // (0x0F<<1)
    UINT16 MaxPos;        // (0x10<<1)
    UINT16 MinV;          // (0x11<<1)
    UINT16 MinPos;        // (0x12<<1)
    UINT16 ID0;           // (0x13<<1)
    UINT16 ID1;           // (0x14<<1)
    UINT16 ID2;           // (0x15<<1)
    UINT16 Crc;           // (0x16<<1)
    UINT16 Chk;           // (0x17<<1)
    UINT16 NAThd;         // (0x18<<1)
    UINT16 TxRxNum;       // (0x19<<1)
    UINT16 DIYShift;      // (0x1a<<1)
    UINT16 SubAbs;        // (0x1b<<1)
    UINT16 Int;           // (0x1c<<1)
    UINT16 CountNum;      // (0x1d<<1)
    UINT16 DmaSka;        // (0x1e<<1)
    UINT16 Trna;          // (0x1f<<1)
    UINT16 Trnas;         // (0x20<<1)
    UINT16 SizeA;         // (0x21<<1)
    UINT16 SizeAs;        // (0x22<<1)
    UINT16 S1BaseEa;      // (0x23<<1)
    UINT16 S2BaseEa;      // (0x24<<1)
    UINT16 DBaseEa;       // (0x25<<1)
    UINT16 CalSel;        // (0x26<<1)
} ST_CalRegisters;

typedef union
{
    ST_CalRegisters reg;
    UINT16 offset[sizeof(ST_CalRegisters)>>1];
} Union_CalReg;
#endif
/*******************************************************************************
* Global variable or extern global variabls/functions
*******************************************************************************/
UINT16 CAL_Check(UINT16 usSrc1Addr, UINT16 usLen, UINT8 mem);
#else
UINT16 DrvCRC(UINT32 addr,UINT16 length);
#endif

#endif
