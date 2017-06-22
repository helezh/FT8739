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
#define CH_ORDER_MAX          288                /* 一边的通道最多数量 288(SX) */
#define CH_LEN_MAX            (CH_ORDER_MAX+4)   /* 一边的通道最多数量 288(TX)+3(key) + 1(dummy) */
#define CH_EN_LEN             (CH_LEN_MAX>>4) + 1/* 一边的通道enable数量 */
#define CH_CB_LEN_MAX         155 //未确定               /* 一边的通道存储CB的reg数量 */
#define GROUP_LEN_MAX         5   //未确定               /* 一边的通道最多的Group数量 */
#define TBL_LEN_MAX           205 //未确定               /* Tbl的寄存器数量 */



#define ARAM_DATA_BASE_ADDR   0xA000

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
#define XBUS_TRIM_VALUE        REG16(XBUS_REG_BASE_ADDR+(0x03<<1))

/* reload dma base addr */
//#define RELOAD_DMA_START_ADDR  0x9D00
/******************************************************************************/
/******************************************************************************/
/* CAL reg Start Addr */
#define CAL_REG_BASE_ADDR       0xB000

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

#if 0
typedef struct
{
    UINT16 Reserved[4];
    UINT16 DesAddr1;
    UINT16 DesAddr0;
    UINT16 CtrlReg;
    UINT16 FlashCmd;
    UINT16 FlashAddr1;
    UINT16 FlashAddr0;
    UINT16 FlashLen;
}ST_RlDmaRegisters;
#endif

typedef struct
{  
    UINT16 rdata_lo_byte;
    UINT16 rdata_ho_byte;
    UINT16 lcd_regfile_ctrl;
}ST_LcdWrapRegisters;


/* ASM reg */
typedef struct
{
    UINT16 usAsmIntFlag0;     // (0x00<<1)
    UINT16 usAsmIntFlag1;     //(0x01<<1)
    UINT16 usAsmIntClr0;      // (0x02<<1)
    UINT16 usAsmIntClr1;      //(0x03<<1)
    UINT16 usAsmIntEn0;       // (0x04<<1)
    UINT16 usAsmIntEn1;       //(0x05<<1)
    UINT16 usAsmWakeEn0;      //(0x06<<1)
    UINT16 usAsmWakeEn1;      //(0x07<<1)
    UINT16 usAsmIntSta;      // (0x08<<1)
    UINT16 usAsmScanSta0;    //(0x09<<1)
    UINT16 usAsmScanSta1;    //(0x0a<<1)
    UINT16 usAsmScanCtrl;    //(0x0b<<1)
    UINT16 usAsmScanCfg;     //(0x0c<<1)
    UINT16 usAsmFrameCfg0;   //(0x0d<<1)
    UINT16 usAsmFrameCfg1;   //(0x0e<<1)
    UINT16 usAsmScanDelay;   //(0x0f<<1)
    UINT16 usAsmStbMaskL;   // (0x10<<1)
    UINT16 usAsmStbMaskH;    // (0x11<<1)
    UINT16 usAsmIntCfg;      //(0x12<<1)
    UINT16 usAsmAramBaseL;   // (0x13<<1)
    UINT16 usAsmAramBaseR;   // (0x14<<1)    
} ST_AsmRegisters;

typedef union
{
    ST_AsmRegisters reg;
    UINT16 offset[sizeof(ST_AsmRegisters)>>1];
} Union_AsmReg;

#if 0
/*******************************************************************************/
/* Thermo reg */
typedef struct
{
    UINT16 usThermoCtrl;
    UINT16 usThermoTrim;
    UINT16 usThermoDbg1;
    UINT16 usThermoOutput;
    UINT16 usThermoDbg2;
    UINT16 usThermoCfg;
} ST_ThermoRegisters;

typedef union
{
    ST_ThermoRegisters reg;
    UINT16 offset[sizeof(ST_ThermoRegisters)>>1];
} Union_ThermoReg;

#endif
/*******************************************************************************/
/* AFE reg */

/* 寄存器子项偏移量 */
typedef enum
{
    ID_AFE_PANEL_CFG0 = 0x00,         // 0
    ID_AFE_PANEL_CFG1,
    ID_AFE_PANEL_CFG2,
    ID_AFE_SYS_CFG0,                 // 3
    ID_AFE_SYS_CFG1,
    ID_AFE_SCAN_CFG0,               //5
    ID_AFE_SCAN_CFG1,   
    ID_AFE_ACC_OFFSET,              //7
    ID_AFE_TP_MON_TH,               //8
    ID_AFE_KEY_MON_TH, 
    ID_AFE_ANA_GEN_CFG0,           //10
    ID_AFE_ANA_GEN_CFG1,
    ID_AFE_ANA_CA_CFG0,            //12
    ID_AFE_ANA_CA_CFG1,
    ID_AFE_ANA_CA_CFG2,
    ID_AFE_ANA_P1_P2_CFG0,        //15
    ID_AFE_ANA_P1_P2_CFG1,
    ID_AFE_ANA_P1_P2_CFG2,
    ID_AFE_ANA_P1_P2_CFG3,
    ID_AFE_ANA_P1_P2_CFG4,
    ID_AFE_ANA_P1_P2_CFG5,
    ID_AFE_ANA_P2_DLY_CFG0,       //21
    ID_AFE_ANA_P2_DLY_CFG1,
    ID_AFE_ANA_SH_CFG0,           //23
    ID_AFE_ANA_SH_CFG1,
    ID_AFE_ANA_SH_CFG2,
    ID_AFE_ANA_SH_CFG3,
    ID_AFE_ANA_SH_CFG4,
    ID_AFE_ANA_SH_CFG5,
    ID_AFE_ANA_SH_CFG6,
    ID_AFE_ANA_ADC_CFG0,         //30
    ID_AFE_ANA_ADC_CFG1,
    ID_AFE_ANA_ADC_CFG2,
    ID_AFE_ANA_ADC_CFG3
} ENUM_AFE_REG_OFFSET;

typedef struct
{
    UINT16 usAfePanelCfg0;           //0
    UINT16 usAfePanelCfg1;           // 1
    UINT16 usAfePanelCfg2;           // 2
    UINT16 usAfeSysCfg0;             // 3
    UINT16 usAfeSysCfg1;             // 4
    UINT16 usAfeScanCfg0;            // 5
    UINT16 usAfeScanCfg1;            // 6
    UINT16 usAfeAcc_Offset;          //7
    UINT16 usAfeTpMonTh;             //8
    UINT16 usAfeKeyMonTh;            //9
    UINT16 usAfeAnaGenCfg0;          //10
    UINT16 usAfeAnaGenCfg1;          //11
    UINT16 usAfeAnaCaCfg0;           //12
    UINT16 usAfeAnaCaCfg1;           //13
    UINT16 usAfeAnaCaCfg2;           //14
    UINT16 usAfeAnaP1P2Cfg0;         //15 
    UINT16 usAfeAnaP1P2Cfg1;         //16
    UINT16 usAfeAnaP1P2Cfg2;         //17 
    UINT16 usAfeAnaP1P2Cfg3;         //18     
    UINT16 usAfeAnaP1P2Cfg4;         //19
    UINT16 usAfeAnaP1P2Cfg5;         //20 
    UINT16 usAfeP1P2DlyCfg0;         //21
    UINT16 usAfeP1P2DlyCfg1;         //22
    UINT16 usAfeAnaShcfg0;           //23
    UINT16 usAfeAnaShcfg1;           //24  
    UINT16 usAfeAnaShcfg2;           //25
    UINT16 usAfeAnaShcfg3;           //26
    UINT16 usAfeAnaShcfg4;           //27
    UINT16 usAfeAnaShcfg5;           //28
    UINT16 usAfeAnaShcfg6;           //29
    UINT16 usAfeAnaAdcCfg0;          //30
    UINT16 usAfeAnaAdcCfg1;          //31  
    UINT16 usAfeAnaAdcCfg2;          //32
    UINT16 usAfeAnaAdcCfg3;          //33
} ST_AfeRegList;

/*******************************************************************************/
/* Afe table reg */

/*******************************************************************************/
/* AFE table偏移地址 */
typedef struct
{
    UINT16 usAfe_EN;                  // 00
    UINT16 usP1_WIDTH;                // 01
    UINT16 usP2_WIDTH;                // 02
    UINT16 usAfe_TpThld;              // 03
    UINT16 usAfe_KeyThld;             // 04
    UINT16 usAfe_BaseStep;            // 05
    UINT16 usAfe_ScanNum[8];          // 06-->13
    UINT16 usAfe_Tim0a;               // 14
    UINT16 usAfe_Tim0b;               // 15
    UINT16 usAfe_TIM[3];              // 16-->18
    UINT16 usAfe_Mt0;                 // 19
    UINT16 usAfe_Mt1;                 // 20
    UINT16 usAfe_TIM4[6];             // 21-->26
    UINT16 usAfe_Mt2;                 // 27
    UINT16 usAfe_Mt3;                 // 28
    UINT16 usAfe_Mt4;                 // 29
} ST_AfeTbl;

/*还未确定*/
/* 表的子项偏移量 */
typedef enum
{
    ID_TBL_AFE_EN = 0,              // 00
    ID_TBL_P1_WIDTH,                // 01
    ID_TBL_P2_WIDTH,                // 02
    ID_TBL_AFE_TpThld,              // 03
    ID_TBL_AFE_KeyThld,             // 04
    ID_TBL_AFE_BaseStep,            // 05
    ID_TBL_AFE_ScanNum0,            // 06
    ID_TBL_AFE_ScanNum1,            // 07
    ID_TBL_AFE_ScanNum2,            // 08
    ID_TBL_AFE_ScanNum3,            // 09
    ID_TBL_AFE_ScanNum4,            // 10
    ID_TBL_AFE_ScanNum5,            // 11
    ID_TBL_AFE_ScanNum6,            // 12
    ID_TBL_AFE_ScanNum7,            // 13
    ID_TBL_AFE_TIM0A,               // 14
    ID_TBL_AFE_TIM0B,               // 15
    ID_TBL_AFE_TIM1 = 16,           // 16
    ID_TBL_AFE_MT0  = 19,           // 19
    ID_TBL_AFE_TIM4 = 21,           // 21
    ID_TBL_AFE_MT2  = 27,           // 27
    ID_TBL_AFE_CH_EN0    = 30,      // 30
    ID_TBL_AFE_CB_ADJ0   = 50,      // 50
    ID_TBL_AFE_CB_ADJ154 = 204,     // 204
} ENUM_AFE_TBL_OFFSET;

/*还未确定*/
/* 表的基址*/
typedef enum
{
    ID_AFE_BASE   = 0,                          /* AFE寄存器基址 */
    ID_ORDER_BASE = 256,                        /* KEY通道顺序基址 */
    ID_BASE_RAM   = ID_ORDER_BASE+305,          /* 通道Rawdata基址 */
    ID_TBL1_BASE  = 256,                        /* 表1基址 */
    ID_TBL2_BASE  = ID_TBL1_BASE+TBL_LEN_MAX,   /* 表2基址 */
    ID_TBL3_BASE  = ID_TBL2_BASE+TBL_LEN_MAX,   /* 表3基址 */
    ID_TBL4_BASE  = ID_TBL3_BASE+TBL_LEN_MAX,   /* 表4基址 */
} ENUM_AFE_BASE;

/*还未确定*/
// CB组合，2通道共用一个半字; CB0~CB284; TAB:24~186
typedef struct
{
    UINT8 aucCbRegL[CH_LEN_MAX];      /* 当前模式的左AFE通道寄存器CB */
    UINT8 aucCbRegR[CH_LEN_MAX];      /* 当前模式的右AFE通道寄存器CB */
} ST_AfeCB;

// 通道使能，每个bit代表1个通道;AFE_CHEN0~17; TAB:26~43
typedef struct
{
    UINT16 ausChEnL[CH_EN_LEN];      /* 当前模式的左AFE通道使能 */
    UINT16 ausChEnR[CH_EN_LEN];      /* 当前模式的右AFE通道使能 */
} ST_AfeChEn;

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/

#endif //_FT8836_REG_H_

