/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R),All Rights Reserved.
*
* File Name: Test_Reg.h
*
*    Author: xinkunpeng
*
*   Created: 2014-04-23
*
*  Abstract: Please describe the interface in detail for this module
*
* Reference:
*
*******************************************************************************/
#ifndef _TEST_REG_H_
#define _TEST_REG_H_

/* Conditional Compiler Options */
/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
#if _TEST_SPI0_REG_EN
void Test_Spi0Reg(void);
#else
#define Test_Spi0Reg    /##/
#endif

#if _TEST_XSI_REG_EN
void Test_XsiReg(void);
#else
#define Test_XsiReg    /##/
#endif

#if _TEST_XBUS_REG_EN
void Test_XbusReg(void);
#else
#define Test_XbusReg   /##/
#endif

#if _TEST_CAL_REG_EN
void Test_CalReg(void);
#else
#define Test_CalReg    /##/
#endif

#if _TEST_AFE_REG_EN
void Test_AfeReg(void);
#else
#define Test_AfeReg    /##/
#endif

#if _TEST_ASM_REG_EN
void Test_AsmReg(void);
#else
#define Test_AsmReg    /##/
#endif
#if _TEST_AFE_RAM_EN
#define  TEST_TAB_RAM_EN          1   // tab ram enble
#define  TEST_RPT_RAM_EN          1   // rpt ram enble
#define  TEST_ACC_RAM4_EN         1   // acc ram4 enble
#define  TEST_ACC_RAM3_EN         1   // acc ram3 enble
#define  TEST_ACC_RAM2_EN         1   // acc ram3 enble
#define  TEST_ACC_RAM1_EN         1   // acc ram2 enble


void Test_Afe_Ram();
#else
#define  Test_Afe_Ram   /##/
#endif

#if _TEST_LCD_REG_EN
void Test_LcdReg(void);
#else
#define Test_LcdReg    /##/
#endif

#endif
