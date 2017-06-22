/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)，All Rights Reserved.
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
#define ARAM_DATA_BASE_ADDR   0xA000

/* SPI0 reg Start Addr */
#define SPI0_REG_BASE_ADDR               0xB200

#define SPI0_DMA_CTRL                    REG16(SPI0_REG_BASE_ADDR+(0x00<<1))
#define SPI0_DMA_ERR_TIMEOUT_CTRL        REG16(SPI0_REG_BASE_ADDR+(0x01<<1))
#define SPI0_DMA_ADDR_H                  REG16(SPI0_REG_BASE_ADDR+(0x02<<1))
#define SPI0_DMA_START_ADDR_L            REG16(SPI0_REG_BASE_ADDR+(0x03<<1))            
#define SPI0_DMA_END_ADDR_L              REG16(SPI0_REG_BASE_ADDR+(0x04<<1))         
#define SPI0_DMA_CRC                     REG16(SPI0_REG_BASE_ADDR+(0x05<<1))
#define SPI0_DMA_SRCR                    REG16(SPI0_REG_BASE_ADDR+(0x06<<1))
/* XSI reg 控制区 */

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
#define XBUS_CMD               REG16(XBUS_REG_BASE_ADDR+(0x03<<1))
#define XBUS_RLD_DATA          REG16(XBUS_REG_BASE_ADDR+(0x04<<1))

/* reload dma base addr */
//#define RELOAD_DMA_START_ADDR  0x9D00
/******************************************************************************/
/******************************************************************************/
/* CAL reg Start Addr */
#define CAL_REG_BASE_ADDR       0xB000

/* ASM reg Start Addr */
#define ASM_REG_BASE_ADDR       0xB100


/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/
/*************************************************************/
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

/*************************************************************/
// cal
typedef struct
{
    UINT16 rCmd;           // (0x00<<1)
    UINT16 rDmaLen;        // (0x01<<1)
    UINT16 rS1Addr;        // (0x02<<1)
    UINT16 rS2Addr;        // (0x03<<1)
    UINT16 rOutAddr;       // (0x04<<1)
    UINT16 rPar;           // (0x05<<1)
    UINT16 rSize;          // (0x06<<1)
    UINT16 rPThd;          // (0x07<<1)
    UINT16 rNThd;          // (0x08<<1)
    UINT16 rAThd;          // (0x09<<1)
    UINT16 rDmask;         // (0x0A<<1)
    UINT16 rPaCnt;         // (0x0B<<1)
    UINT16 rNaCnt;         // (0x0C<<1)
    UINT16 rPsCnt;         // (0x0D<<1)
    UINT16 rNsCnt;         // (0x0E<<1)
    UINT16 rMaxV;          // (0x0F<<1)
    UINT16 rMaxPos;        // (0x10<<1)
    UINT16 rMinV;          // (0x11<<1)
    UINT16 rMinPos;        // (0x12<<1)
    UINT16 rID0;           // (0x13<<1)
    UINT16 rID1;           // (0x14<<1)
    UINT16 rID2;           // (0x15<<1)
    UINT16 rCrc;           // (0x16<<1)
    UINT16 rChk;           // (0x17<<1)
    UINT16 rNaThd;         // (0x18<<1)
    UINT16 rTxRxNum;       // (0x19<<1)
    UINT16 rDivShift;      // (0x1a<<1)
    UINT16 rSubabsMax;     // (0x1b<<1)
    UINT16 rInt;           // (0x1c<<1)
    UINT16 rCntNum;        // (0x1d<<1)
    UINT16 rDmaskA;        // (0x1e<<1)
    UINT16 rTxRxNumAm;     // (0x1f<<1)
    UINT16 rTxRxNumAs;     // (0x20<<1)
    UINT16 rSizeAm;        // (0x21<<1)
    UINT16 rSizeAs;        // (0x22<<1)
    UINT16 rS1AddrA;       // (0x23<<1)
    UINT16 rS2AddrA;       // (0x24<<1)
    UINT16 rOutAddrA;      // (0x25<<1)
    UINT16 rSel;           // (0x26<<1)
} ST_CalRegisters;

typedef union
{
    ST_CalRegisters reg;
    UINT16 offset[sizeof(ST_CalRegisters)>>1];
} Union_CalReg;

/*************************************************************/
/*XBUS reg*/
typedef struct
{  
    UINT16 rdata_lo_byte;
    UINT16 rdata_ho_byte;
    UINT16 lcd_regfile_ctrl;
    UINT16 xbus_cmd;//bit1 reload_end;bit0 reload_abort
    UINT16 xbus_rld_data;//reload_data
}ST_LcdWrapRegisters;

typedef union
{
    ST_LcdWrapRegisters reg;
    UINT16 offset[sizeof(ST_LcdWrapRegisters)>>1];
}Union_LcdReg;

/*************************************************************/
/*SPI0_DMA reg*/
typedef struct
{
    UINT16 dma_ctrl;
    UINT16 timeout_ctrl;
    UINT16 addr_h;
    UINT16 start_addr_l;
    UINT16 end_addr_l;
    UINT16 dma_crc;
    UINT16 dma_srcr;
    
}ST_Spi0DmaRegisters;

typedef union
{
    ST_Spi0DmaRegisters reg;
    UINT16 offset[sizeof(ST_Spi0DmaRegisters)>>1];
}Union_Spi0Reg;

/*************************************************************/
/* ASM reg */
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
    UINT16 usAsmReserve0;         // 29 未定义
    UINT16 usAsmReserve1;         // 30 未定义
    UINT16 usAsmReserve2;         // 31 未定义
    UINT16 usAsmHwMonCrtl0;       // 32
    UINT16 usAsmHwMonCtrl1;       // 33
    UINT16 usAsmHwMonCfg0;        // 34
    UINT16 usAsmHwMonCfg1;        // 35
    UINT16 usAsmHwMonCfg2;        // 36
    UINT16 usAsmHwMonCfg3;        // 37
    UINT16 usAsmHwMonCfg4;        // 38
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
    UINT16 usAfeAsmCfg;              // 0x00
    UINT16 usAfePanelCfg0;           // 0x01
    UINT16 usAfePanelCfg1;           // 0x02
    UINT16 usAfePanelCfg2;           // 0x03
    UINT16 usAfeSysCfg0;             // 0x04
    UINT16 usAfeSysCfg1;             // 0x05
    UINT16 usAfeScanCfg0;            // 0x06
    UINT16 usAfeScanCfg1;            // 0x07
    UINT16 usAfeDummyScanCfg;        // 0x08
    UINT16 usAfeBaseTrackCfg;        // 0x09
    UINT16 usAfeAcc_Offset;          // 0x0A
    UINT16 usAfeTpMonTh;             // 0x0B
    UINT16 usAfeKeyMonTh;            // 0x0C
    UINT16 usAfeAnaGenCfg0;          // 0x0D
    UINT16 usAfeAnaGenCfg1;          // 0x0E
    UINT16 usAfeAnaCaCfg0;           // 0x0F
    UINT16 usAfeAnaCaCfg1;           // 0x10
    UINT16 usAfeAnaCaCfg2;           // 0x11
    UINT16 usAfeAnaP1P2Cfg0;         // 0x12
    UINT16 usAfeAnaP1P2Cfg1;         // 0x13
    UINT16 usAfeAnaP1P2Cfg2;         // 0x14 
    UINT16 usAfeAnaP1P2Cfg3;         // 0x15    
    UINT16 usAfeAnaP1P2Cfg4;         // 0x16
    UINT16 usAfeAnaP1P2Cfg5;         // 0x17
    UINT16 usAfeP1P2DlyCfg0;         // 0x18
    UINT16 usAfeP1P2DlyCfg1;         // 0x19
    UINT16 usAfeAnaShcfg0;           // 0x1A
    UINT16 usAfeAnaShcfg1;           // 0x1B
    UINT16 usAfeAnaShcfg2;           // 0x1C
    UINT16 usAfeAnaShcfg3;           // 0x1D
    UINT16 usAfeAnaShcfg4;           // 0x1E
    UINT16 usAfeAnaShcfg5;           // 0x1F
    UINT16 usAfeAnaShcfg6;           // 0x20
    UINT16 usAfeAnaAdcCfg0;          // 0x21
    UINT16 usAfeAnaAdcCfg1;          // 0x22 
    UINT16 usAfeAnaAdcCfg2;          // 0x23
    UINT16 usAfeAnaAdcCfg3;          // 0x24
    UINT16 usAfeGiphP1P2Cfg;         // 0x25
    UINT16 usAfeGiplP1P2Cfg;         // 0x26
    UINT16 usAfeSdVcomCfg;           // 0x27
    UINT16 usAfeSxP1P2Cfg;           // 0x28
    UINT16 usAllGateOnLCfg;          // 0x29
    UINT16 usAllGateOffLCfg;         // 0x2A
    UINT16 usAllGateStopLCfg;        // 0x2B
    UINT16 usAllGateHCfg;            // 0x2C
    UINT16 usRptRawdataNum;          // 0x2D
    UINT16 usCbAdjustTh;             // 0x2E
    UINT16 usTestModeCfg;            // 0x2F
    UINT16 usPrescanTime;            // 0x30
    UINT16 usDischargeTime;          // 0x31
    UINT16 usAfeAnaStaticCfg0;       // 0x32
    UINT16 usAfeAnaStaticCfg1;       // 0x33
    UINT16 usAfeAnaStaticCfg2;       // 0x34
    UINT16 usAfeAnaStaticCfg3;       // 0x35
    UINT16 usAfeTestPin0Cfg0;        // 0x36
    UINT16 usAfeTestPin0Cfg1;        // 0x37
    UINT16 usAfeTestPin0Cfg2;        // 0x38
    UINT16 usAfeTestPin1Cfg0;        // 0x39
    UINT16 usAfeTestPin1Cfg1;        // 0x3A
    UINT16 usAfeTestPin1Cfg2;        // 0x3B
    UINT16 usReserveZone1;           // 0x3C
    UINT16 usReserveZone2;           // 0x3D
    UINT16 usReserveZone3;           // 0x3E
    UINT16 usReserveZone4;           // 0x3F    
    UINT16 usMcapScanCfg;            // 0x40
    UINT16 usMcapScanSr;             // 0x41
    UINT16 usMcapKeyInterVal6;       // 0x42
    UINT16 usMcapDummyScanNum;       // 0x43
    UINT16 usMcapRawShiftCof;        // 0x44
    UINT16 usMcapRawOffSetL;         // 0x45
    UINT16 usMcapAdcCfg;             // 0x46
    UINT16 usMcapAdcDat0;            // 0x47
    UINT16 usMcapInitSamplCfg;       // 0x48
    UINT16 usMcapOverFlowThr;        // 0x49
    UINT16 usMcapUnderFlowThr;       // 0x4A
    UINT16 usMcapOverFlowUpBound;    // 0x4B
    UINT16 usMcapOverFlowPointFrame; // 0x4C
    UINT16 usMcapNormalSignalUpThr;  // 0x4D
    UINT16 usMcapNormalSignalDwThr;  // 0x4E
    UINT16 usMcapOverFlowClrFrameNum;// 0x4F
    UINT16 usMcapLpfirCfg;           // 0x50
    UINT16 usMcapLpFirCfg0;          // 0x51
    UINT16 usMcapLpFirCfg1;          // 0x52
    UINT16 usMcapLpFirCfg2;          // 0x53
    UINT16 usMcapLpFirCfg3;          // 0x54
    UINT16 usMcapLpFirCfg4;          // 0x55  
    UINT16 usMcapLpFirCfg5;          // 0x56
    UINT16 usMcapLpFirCfg6;          // 0x57
    UINT16 usMcapLpFirCfg7;          // 0x58
   
} ST_AfeRegList;



/*******************************************************************************/
/* Afe table reg */

/*******************************************************************************/


/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/

#endif //_FT8836_REG_H_
