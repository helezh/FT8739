/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Drv_mcu.h
*
*    Author: xinkunpeng
*
*   Created: 2014-04-24
*
*  Abstract:
*
* Reference: Transplant from FT5412 by linjianjun
*
*   Version: 0.2
*******************************************************************************/
#ifndef __DRV_MCU_H__
#define __DRV_MCU_H__


/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define I2C_SLAVE_ADDR 0x70


#define DATABUFF     I2CBUF
#define RIFLAG       I2CRI
#define TIFLAG       I2CTI


#define DrvSysPowerIdle()               DrvSysPowerMode(0)          //enter the idle mode 
#define DrvSysPowerStop()               DrvSysPowerMode(1)          //enter the stop mode 
#define DrvSysPowerStandby()            DrvSysPowerMode(2)          //enter the standby mode 
#define DrvSysPowerHibernate()          DrvSysPowerMode(1)          //enter the hibernate mode 

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern UINT8 XRAM g_ucbuf[16];

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

void DrvSysPowerMode(UINT8 pmode);
void DrvSysClkInit(UINT8 ucDiv);
void DrvIOInit(void);
void DelayUs(UINT8 ucDlyCnt);
void DelayMs(UINT16 ucDlyCnt);
#endif

