/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: LibDrv.h
*
*    Author: xinkunpeng
*
*   Created: 2014-05-28
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/
#ifndef _FT8607_LIB_H_
#define _FT8607_LIB_H_

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgPlatform.h"
#include "FT8836.h"
#include "FT8836_Reg.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
/* Driver Lib version */
#define  RV_G_DRVLIB_VER_H   0x01
#define  RV_G_DRVLIB_VER_L   0x02

#define AFE_REG          0 
#define XSI_S_REG        1 
#define XSI_WDATA_DUMMY  0 

/* Bit defined of Afe_en reg */ 
#define XSI_WDATA_ADDR  0
#define XSI_WDATA_SEL   11
#define XSI_WDATA_WR    15

#define XSI_PAGE_SEL    8
#define XSI_LCD_PAGE0   1
#define XSI_LCD_PAGE1   2

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/
/* CAL矩阵运算参数 */
typedef struct
{
    UINT8 ucTxNum;          // 矩阵行数
    UINT8 ucRxNum;          // 矩阵列数    
    UINT8 ucShift;          // 结果右移个数
    UINT8 ucCfg;            // 配置参数
    ADDR  usSrc1Addr;       // 操作数1的内存开始地址
    ADDR  usSrc2Addr;       // 操作数2的内存开始地址
    ADDR  usDstAddr;        // 运算结果的内存开始地址
    ADDR  usCalcmd;         // 运算符号
} ST_CalMcMatrixParam;

/* AMOV运算参数 */
typedef struct
{
    UINT8 ucS1TxNum;      // 矩阵S1的TxNum
    UINT8 ucS1RxNum;      // 矩阵S1的RxNum
    UINT8 ucS2TxNum;      // 矩阵S2的TxNum
    UINT8 ucS2RxNum;      // 矩阵S2的RxNum
    UINT8 ucS1TxLen;      // 矩阵S1的TxLen
    UINT8 ucS1RxLen;      // 矩阵S1的RxLen
    UINT8 ucS2TxLen;      // 矩阵S2的TxLen
    UINT8 ucS2RxLen;      // 矩阵S2的RxLen
    UINT16 usSrc1Addr;    // 操作数S1的内存开始地址
    UINT16 usSrc2Addr;    // 操作数S2的内存开始地址
    UINT16 usDstAddr;     // 运算结果的内存开始地址
    UINT16 usCalSel;      // 选择dram,aram,pram
    UINT16 usDmaMask;     // 扩展命令avg/min/max运算数据: 原值or绝对值
} ST_CalMatrixAMov;
/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern BOOLEAN g_bCalResumeFlag;
extern ST_XSIRegisters * XRAM pXSI0Regs;
extern ST_XSIRegisters * XRAM pXSI1Regs;
extern ST_XSIRegisters * XRAM pXSI2Regs;
extern ST_CalRegisters * XRAM pCalRegs;

extern ST_LcdWrapRegisters * XRAM pLcdWrapRegs;
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
/******************************************************************************/
//Xsi module
void Drv_XsiInit();
UINT16 Drv_XsiReadReg(ST_XSIRegisters *pXSIRegs, UINT16 addr, UINT8 flag);
void Drv_XsiWriteReg(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 usData,UINT8 flag);
void Drv_XsiRead(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 *pBuf, UINT16 len, UINT8 flag);
void Drv_XsiWrite(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 *pBuf, UINT16 len, UINT8 flag);
void Drv_LcdRegWrite(ST_LcdWrapRegisters *pLcdWrapRegs,UINT16 usAddr,UINT8 ucdata);
UINT8 Drv_LcdRegRead(ST_LcdWrapRegisters *pLcdWrapRegs,UINT16 usAddr);
void DrvXsi0_WriteN(UINT16 usAddr, UINT16 *pBuf, UINT16 usLen);
void DrvXsi1_WriteN(UINT16 usAddr, UINT16 *pBuf, UINT16 usLen);


void DrvXbus_WriteLcdReg(UINT16 usAddr,UINT8 ucData);
UINT8 DrvXbus_ReadLcdReg(UINT16 usAddr);


void Drv_XbusInit(void);
UINT16 DrvXbus_ReadLcd16(UINT16 usaddr);
void DrvXbus_WriteLcd8(UINT16 usaddr,UINT8 usdata);
void DrvXbus_WriteInitCode(void);


/******************************************************************************/
//Cal module
void DrvCal_Init(UINT8 ucTxNum, UINT8 ucRxNum, UINT16 usDmask);
void DrvCal_Cmd(UINT16 cmd);
void DrvCal_MatrixProc(ST_CalMcMatrixParam *pMcMP);
void DrvCal_MatrixAmp(ST_CalMcMatrixParam *pMcMP, SINT16 mul);
void DrvCal_MatrixMul(ST_CalMcMatrixParam *pMcMP, UINT8 K_Num);

#endif

