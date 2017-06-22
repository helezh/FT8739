/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: CommHost.h
*
*    Author: Wu Bo Zhong (Michael)
*
*   Created: 2013-02-21
*
*  Abstract: Just provide an interface for high layer of flow to initialize
*            the module communicated with host.
*
* Reference: 
*
*******************************************************************************/

#ifndef _DRV_SYS_CTRL_H_
#define _DRV_SYS_CTRL_H_

/* Conditional Compiler Options */
#define _DELAY_MS_EN            1

/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgSystem.h"

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
/* mcu clk = 48M/(MAIN_CLK + 1) */
#define MAIN_CLK                0   

#define SYS_PWR_IDLE            0
#define SYS_PWR_STOP            1
#define SYS_PWR_STANDBY         2

#define DrvSysPowerIdle()       DrvSysPwrSel(SYS_PWR_IDLE)
#define DrvSysPowerStop()       DrvSysPwrSel(SYS_PWR_STOP)
#define DrvSysPowerStandby()    DrvSysPwrSel(SYS_PWR_STANDBY)   //enter the standby mode 
 
#define DrvSysIntEnable()       EA = 1
#define DrvSysIntDisable()      EA = 0

#define RV_G_VDD5              0x0F  // 4.5V FT8626 : 0-15档可设 ,1.5V-4.5V, 0.2V/step; 
#define RV_G_VREF              0x0A  // 4.1V FT8626 : 0-15档可设 ,1.5V-4.5V, 0.2V/step;

/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/
 
/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void DrvSysClkInit(UINT8 ucDiv);
void DrvSysPwrSel(UINT8 pmode);

void DrvSysPortInit(void);
 
void DrvIntPriority(void);

void Drv_Rtc_Init(UINT8 ucMode);

 
#if _DELAY_MS_EN
void DelayUs(UINT8 ucDlyCnt);
void DelayMs(UINT16 ucDlyCnt);
#endif

#endif // _DRV_SYS_CTRL_H_

