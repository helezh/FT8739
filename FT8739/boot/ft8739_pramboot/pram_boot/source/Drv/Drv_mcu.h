/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Drv_mcu.h
*
*    Author: xinkunpeng
*
*   Created: 2014-10-22
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/
#ifndef __DRV_MCU_H__
#define __DRV_MCU_H__

/* Conditional Compiler Options */
/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define I2C_SLAVE_ADDR 0x70

#define DATABUFF       I2CBUF
#define RIFLAG         I2CRI
#define TIFLAG         I2CTI
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern UINT8  g_ucAppEcc;
extern UINT16 g_usTimerCnt;
extern UINT8 g_ucICVersion;

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void DrvSysInit(void);
void DrvHostI2cInit(void);
void DelayUs(UINT16 cnt);
void DrvSysTimer0Init();

#if _LCD_XSI2_EN
void DrvGetICVersion(void);
#else
#define DrvGetICVersion()   /##/
#endif
#endif //_DRV_MCU_H_

