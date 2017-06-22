/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)��All Rights Reserved.
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
/* CAL����������� */
typedef struct
{
    UINT8 ucTxNum;          // ��������
    UINT8 ucRxNum;          // ��������    
    UINT8 ucShift;          // ������Ƹ���
    UINT8 ucCfg;            // ���ò���
    ADDR  usSrc1Addr;       // ������1���ڴ濪ʼ��ַ
    ADDR  usSrc2Addr;       // ������2���ڴ濪ʼ��ַ
    ADDR  usDstAddr;        // ���������ڴ濪ʼ��ַ
    ADDR  usCalcmd;         // �������
} ST_CalMcMatrixParam;

/* AMOV������� */
typedef struct
{
    UINT8 ucS1TxNum;      // ����S1��TxNum
    UINT8 ucS1RxNum;      // ����S1��RxNum
    UINT8 ucS2TxNum;      // ����S2��TxNum
    UINT8 ucS2RxNum;      // ����S2��RxNum
    UINT8 ucS1TxLen;      // ����S1��TxLen
    UINT8 ucS1RxLen;      // ����S1��RxLen
    UINT8 ucS2TxLen;      // ����S2��TxLen
    UINT8 ucS2RxLen;      // ����S2��RxLen
    UINT16 usSrc1Addr;    // ������S1���ڴ濪ʼ��ַ
    UINT16 usSrc2Addr;    // ������S2���ڴ濪ʼ��ַ
    UINT16 usDstAddr;     // ���������ڴ濪ʼ��ַ
    UINT16 usCalSel;      // ѡ��dram,aram,pram
    UINT16 usDmaMask;     // ��չ����avg/min/max��������: ԭֵor����ֵ
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

