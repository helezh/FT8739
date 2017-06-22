/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)??All Rights Reserved.
*
* File Name: FT8836_Reg.h
*
*    Author: 
*
*   Created: 2016-07-11
*
*  Abstract: Define FT8836 Sram registers and their bits
*
* Reference:
*
*******************************************************************************/

#ifndef _FT8836_REG_H_
#define _FT8836_REG_H_

/* Conditional Compiler Options */

/*******************************************************************************
* Included files
*******************************************************************************/
#include "FT8836.h"

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/


#define ARAM_DATA_BASE_ADDR    0xA000

/* CAL reg Start Addr */
#define CAL_REG_BASE_ADDR      0xB000

#define ASM_REG_BASE_ADDR      0xB100

/* XSI0 reg start addr */
#define XSI0_REG_BASE_ADDR     0xB400

#define XSI0_WDATA_LOC         REG16(XSI0_REG_BASE_ADDR+(0x00<<1))
#define XSI0_RDATA_LOC         REG16(XSI0_REG_BASE_ADDR+(0x01<<1))
#define XSI0_CLK_SEL           REG16(XSI0_REG_BASE_ADDR+(0x02<<1))
#define XSI0_STOP              REG16(XSI0_REG_BASE_ADDR+(0x03<<1))
#define XSI0_TX_INT            REG16(XSI0_REG_BASE_ADDR+(0x04<<1))

/* XSI1 reg start addr */
#define XSI1_REG_BASE_ADDR     0xB800

#define XSI1_WDATA_LOC         REG16(XSI1_REG_BASE_ADDR+(0x00<<1))
#define XSI1_RDATA_LOC         REG16(XSI1_REG_BASE_ADDR+(0x01<<1))
#define XSI1_CLK_SEL           REG16(XSI1_REG_BASE_ADDR+(0x02<<1))
#define XSI1_STOP              REG16(XSI1_REG_BASE_ADDR+(0x03<<1))
#define XSI1_TX_INT            REG16(XSI1_REG_BASE_ADDR+(0x04<<1))

/* XBUS reg start addr */
#define XBUS_REG_BASE_ADDR     0xBC00

#define XBUS_RDATA_LO_BYTE     REG16(XBUS_REG_BASE_ADDR+(0x00<<1))
#define XBUS_RDATA_HO_BYTE     REG16(XBUS_REG_BASE_ADDR+(0x01<<1))
#define XBUS_REGFILE_CTRL      REG16(XBUS_REG_BASE_ADDR+(0x02<<1))
#define XBUS_TRIM_VALUE        REG16(XBUS_REG_BASE_ADDR+(0x03<<1))


/* lcd wrap base addr */
#define LCD_WRAP_START_ADDR    0xBC00




// pCalCmd BIT DEFINITION
#define CAL_CMD_START          BITn(0)
#define CAL_CMD_RUNNING        BITn(1)
#define CAL_CMD_RESUME         BITn(2)
#define CAL_CMD_SUSPEND        BITn(3)
#define CAL_CMD_OP_CFG0        BITn(8)
#define CAL_CMD_OP_CFG1        BITn(9)
#define CAL_CMD_OP_CFG2        BITn(10)
#define CAL_CMD_DMA_OFF        BITn(11)
#define CAL_CMD_EXT_RESUME_EN  BITn(12)
#define CAL_CMD_MUL2_EN        BITn(13)
#define CAL_CMD_INT_CLR        BITn(14)
#define CAL_CMD_MOD_EXTEND     BITn(15)
#define CAL_OP_MASK            0x00F0

//CALINT
#define CAL_CMD_AMOV_START     BITn(0)
#define CAL_CMD_AMOV_RESUME    BITn(1)
#define CAL_CMD_AMOV_INT_CLR   BITn(2)
#define CAL_CMD_AMOV_MODE      BITn(3)
#define CAL_CMD_AMOV_EN        BITn(4)
#define CAL_CMD_AMOV_SUSPEND   BITn(5)
#define CAL_CMD_AMOV_RUNNING   BITn(6)
#define CAL_CMD_AMOV_INT       BITn(7)
#define CAL_CMD_INT            BITn(15)

//CALSEL
#define CAL_AMOV_CFG           BITn(14)
#define CAL_DSEL_AMOV_DRAM     (0x00<<12)
#define CAL_DSEL_AMOV_ARAM     (0x01<<12)
#define CAL_DSEL_AMOV_PRAM     (0x02<<12)
#define CAL_S2SEL_AMOV_DRAM    (0x00<<10)
#define CAL_S2SEL_AMOV_ARAM    (0x01<<10)
#define CAL_S2SEL_AMOV_PRAM    (0x02<<10)
#define CAL_S1SEL_AMOV_DRAM    (0x00<<8)
#define CAL_S1SEL_AMOV_ARAM    (0x01<<8)
#define CAL_S1SEL_AMOV_PRAM    (0x02<<8)
#define CAL_DSEL_DRAM          (0x00<<4)
#define CAL_DSEL_ARAM          (0x01<<4)
#define CAL_DSEL_PRAM          (0x02<<4)
#define CAL_S2SEL_DRAM         (0x00<<2)
#define CAL_S2SEL_ARAM         (0x01<<2)
#define CAL_S2SEL_PRAM         (0x02<<2)
#define CAL_S1SEL_DRAM         (0x00<<0)
#define CAL_S1SEL_ARAM         (0x01<<0)
#define CAL_S1SEL_PRAM         (0x02<<0)

// CAL_OP_MOD DEFINITION
#define OP_SUB                 (0x00<<4)
#define OP_ADD                 (0x01<<4)
#define OP_MOV                 (0x02<<4)
#define OP_COM                 (0x03<<4)
#define OP_AMP                 (0x04<<4)
#define OP_FLT                 (0x05<<4)
#define OP_MDS                 (0x06<<4)
#define OP_LDS                 (0x07<<4)
#define OP_CHK                 (0x08<<4)
#define OP_CRC                 (0x09<<4)
#define OP_PKS                 (0x0A<<4)
#define OP_MUL                 (0x0B<<4)
#define OP_MAC                 (0x0C<<4)
#define OP_KM                  (0x0D<<4)
#define OP_MUL2                (0x0E<<4)
#define OP_DIV                 (0x0F<<4)

// CAL_EXTEND_MOD DEFINITION
#define EX_OP_AVG              (0x00<<4)
#define EX_OP_MIN              (0x01<<4)
#define EX_OP_MAX              (0x02<<4)
#define EX_OP_SUBCONST         (0x03<<4)
#define EX_OP_COUNT            (0x04<<4)
#define EX_OP_AMOV             (0x05<<4)
#define EX_OP_AVG2             (0x06<<4)


/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/

/* XSI reg */
typedef struct
{
    UINT16 Wdata;        // (0x00<<1)
    UINT16 Rdata;        // (0x01<<1)
    UINT16 Clksel;       // (0x02<<1)
    UINT16 Stop;         // (0x03<<1)
    UINT16 Tx_int;       // (0x04<<1)
} ST_XSIRegisters;

typedef union
{
    ST_XSIRegisters reg;
    UINT16 offset[sizeof(ST_XSIRegisters)>>1];
} Union_XSIReg;

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
    UINT16 NAThd;           // (0x18<<1)
    UINT16 TxRxNum;       //(0x19<<1)
    UINT16 DIYShift;      //(0x1a<<1)
    UINT16 SubAbs;        // (0x1b<<1)//New Add
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
    UINT16 CalSel;
} ST_CalRegisters;

typedef union
{
    ST_CalRegisters reg;
    UINT16 offset[sizeof(ST_CalRegisters)>>1];
} Union_CalReg;



typedef struct
{  
    UINT16 rdata_lo_byte;
    UINT16 rdata_hi_byte;
    UINT16 lcd_regfile_ctrl;
}ST_LcdWrapRegisters;

typedef enum
{
    ID_AFE_BASE  = 0,          
    ID_ORDER_BASE = 256,        
    ID_MON_BASE = 370,           
    ID_TBL1_BASE = 256,         
} ENUM_AFE_BASE;



// ASM
typedef struct
{
    UINT16 usAsmIntFlag0;         // 00  RO
    UINT16 usAsmIntFlag1;         // 01  RO
    UINT16 usAsmIntClr0;          // 02  WO
    UINT16 usAsmIntClr1;          // 03  WO
    UINT16 usAsmIntEn0;           // 04
    UINT16 usAsmIntEn1;           // 05
    UINT16 usAsmIntWakeEn0;       // 06
    UINT16 usAsmIntWakeEn1;       // 07
    UINT16 usAsmIntSta;           // 08  RO
    UINT16 usAsmScanSta0;         // 09  RO
    UINT16 usAsmScanSta1;         // 10  RO
    UINT16 usAsmScanSta2;         // 11  RO
    UINT16 usAsmScanSta3;         // 12  RO
    UINT16 usAsmScanCtrl;         // 13  WO
    UINT16 usAsmScanCfg0;         // 14
    UINT16 usAsmScanCfg1;         // 15
    UINT16 usAsmTpFrameCfg0;      // 16
    UINT16 usAsmTpFrameCfg1;      // 17
    UINT16 usAsmTpFrameCfg2;      // 18
    UINT16 usAsmTpFrameCfg3;      // 19
    UINT16 usAsmScanDly;          // 20
    UINT16 usAsmStbMaseL;         // 21
    UINT16 usAsmStbMaseH;         // 22  
    UINT16 usAsmAramBaseL;        // 23
    UINT16 usAsmAramBaseR;        // 24
    UINT16 usAsmAramBaseKey;      // 25    
    UINT16 usAsmAramCBL;          // 26
    UINT16 usAsmAramCBR;          // 27
    UINT16 usAsmAramCBKey;        // 28
    UINT16 usAsmTailMargin;       // 29 
    UINT16 usAsmReserve1;         // 30 未定义
    UINT16 usAsmReserve2;         // 31 未定义
    UINT16 usAsmPwrCtrl;          // 32
    UINT16 usAsmPwrSta;           // 33
    UINT16 usAsmPwrInterval0;     // 34
    UINT16 usAsmPwrInterval1;     // 35
    UINT16 usAsmPwrInterval2;     // 36
    UINT16 usAsmPwrInterval3;     // 37
    UINT16 usAsmPwrInterval4;     // 38
    UINT16 usAsmHwMonTimer;       // 39
    UINT16 usAsmVreshCfgLcdon;    // 40
} ST_AsmRegisters;


typedef union
{
    ST_AsmRegisters reg;
    UINT16 offset[sizeof(ST_AsmRegisters)>>1];
} Union_AsmReg;

/*******************************************************************************/
/* AFE reg */
typedef struct
{
    UINT16 usAfeAsmCfg;              // 0
    UINT16 usAfePanelCfg0;           // 1
    UINT16 usAfePanelCfg1;           // 2
    UINT16 usAfePanelCfg2;           // 3
    UINT16 usAfeSysCfg0;             // 4
    UINT16 usAfeSysCfg1;             // 5
    UINT16 usAfeScanCfg0;            // 6
    UINT16 usAfeScanCfg1;            // 7
    UINT16 usAfeDummyScanCfg;        // 8
    UINT16 usAfeBaseTrackCfg;        // 9
    UINT16 usAfeAcc_Offset;          // 10
    UINT16 usAfeTpMonTh;             // 11
    UINT16 usAfeKeyMonTh;            // 12
    UINT16 usAfeAnaGenCfg0;          // 13
    UINT16 usAfeAnaGenCfg1;          // 14
    UINT16 usAfeAnaCaCfg0;           // 15
    UINT16 usAfeAnaCaCfg1;           // 16
    UINT16 usAfeAnaCaCfg2;           // 17
    UINT16 usAfeAnaP1P2Cfg0;         // 18
    UINT16 usAfeAnaP1P2Cfg1;         // 19
    UINT16 usAfeAnaP1P2Cfg2;         // 20 
    UINT16 usAfeAnaP1P2Cfg3;         // 21    
    UINT16 usAfeAnaP1P2Cfg4;         // 22
    UINT16 usAfeAnaP1P2Cfg5;         // 23
    UINT16 usAfeP1P2DlyCfg0;         // 24
    UINT16 usAfeP1P2DlyCfg1;         // 25
    UINT16 usAfeAnaShcfg0;           // 26
    UINT16 usAfeAnaShcfg1;           // 27 
    UINT16 usAfeAnaShcfg2;           // 28
    UINT16 usAfeAnaShcfg3;           // 29
    UINT16 usAfeAnaShcfg4;           // 30
    UINT16 usAfeAnaShcfg5;           // 31
    UINT16 usAfeAnaShcfg6;           // 32
    UINT16 usAfeAnaAdcCfg0;          // 33
    UINT16 usAfeAnaAdcCfg1;          // 34 
    UINT16 usAfeAnaAdcCfg2;          // 35
    UINT16 usAfeAnaAdcCfg3;          // 36
    UINT16 usAfeGiphP1P2Cfg;         // 37
    UINT16 usAfeGiplP1P2Cfg;         // 38
    UINT16 usAfeSdVcomCfg;           // 39
    UINT16 usAfeSxP1P2Cfg;           // 40
    UINT16 usAllGateOnLCfg;          // 41
    UINT16 usAllGateOffLCfg;         // 42
    UINT16 usAllGateStopLCfg;        // 43
    UINT16 usAllGateHCfg;            // 44
    UINT16 usMcapScanCfg;            // 48
    UINT16 usMcapScanSr;             // 49
    UINT16 usMcapKeyInterVal6;       // 50
    UINT16 usMcapDummyScanNum;       // 51
    UINT16 usMcapRawShiftCof;        // 52
    UINT16 usMcapRawOffSetL;         // 53
    UINT16 usMcapAdcCfg;             // 54
    UINT16 usMcapAdcDat0;            // 55
    UINT16 usMcapInitSamplCfg;       // 56
    UINT16 usMcapOverFlowThr;        // 59
    UINT16 usMcapUnderFlowThr;       // 60
    UINT16 usMcapOverFlowUpBound;    // 61
    UINT16 usMcapOverFlowPointFrame; // 62
    UINT16 usMcapNormalSignalUpThr;  // 63
    UINT16 usMcapNormalSignalDwThr;  // 64
    UINT16 usMcapOverFlowClrFrameNum;// 65
    UINT16 usMcapLpfirCfg;           // 66
    UINT16 usMcapLpFirCfg0;          // 67
    UINT16 usMcapLpFirCfg1;          // 68
    UINT16 usMcapLpFirCfg2;          // 69
    UINT16 usMcapLpFirCfg3;          // 70
    UINT16 usMcapLpFirCfg4;          // 71  
    UINT16 usMcapLpFirCfg5;          // 72
    UINT16 usMcapLpFirCfg6;          // 73
    UINT16 usMcapLpFirCfg7;          // 74
   
} ST_AfeRegList;

/*******************************************************************************/
/* Afe table reg */

/*******************************************************************************/
typedef struct
{
    UINT16 usSysCfg1;
    UINT16 usScanCfg0;
    UINT16 usScanCfg1;
    UINT16 usDummyScanCfg;
    UINT16 usBAseTrackCfg;
    UINT16 usAccOffset;
    UINT16 usTpMonThr;
    UINT16 usKeyMonThr;
    UINT16 usAnaGenCfg0;
    UINT16 usAnaGenCfg1;
}ST_AfeTabList;

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/

#endif //_FT8836_REG_H_
