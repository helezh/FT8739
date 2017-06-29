/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Drv_XSI.h
*
*    Author: xinkunpeng
*
*   Created: 2014-05-14
*
*  Abstract:
*
* Reference:
*
*   Version:
*******************************************************************************/
#ifndef __DRV_XSI_H__
#define __DRV_XSI_H__

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"
#include "FT8835_Reg.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define AFE_REG          0
#define XSI_S_REG        1
#define XSI_WDATA_DUMMY  0

/* Bit defined of Afe_en reg */
#define XSI_WDATA_ADDR    0
#define XSI_WDATA_SEL    11
#define XSI_WDATA_WR     15

#define LCD_PAGE_SEL     8
#define XSI_LCD_ECC      0
#define XSI_LCD_PAGE0    1
#define XSI_LCD_PAGE1    2
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern ST_XSIRegisters * XRAM pXSI0Regs;
extern ST_XSIRegisters * XRAM pXSI1Regs;

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void Drv_XsiInit();
UINT16 Drv_XsiReadReg(ST_XSIRegisters *pXSIRegs, UINT16 addr, UINT8 flag);
void Drv_XsiWriteReg(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 usData,UINT8 flag);
void Drv_XsiRead(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 *pBuf, UINT16 len, UINT8 flag);
void Drv_XsiWrite(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 *pBuf, UINT16 len, UINT8 flag);

#if _TEST_XSI_EN
void Test_Xsi();
#else
#define  Test_Xsi   /##/
#endif

#endif

