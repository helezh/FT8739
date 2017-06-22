/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: DrvTimer.h
*
*    Author: tangsujun
*
*   Created: 2016-12-22
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/

#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__
/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define TM0_SINGLE_MODE          0x01
#define TM0_REPEAT_MODE          0x02
#define DrvTimer0Stop()          TMOD &= 0xFC
#define DrvTimer0SetMs(x)        TH0 = x; TL0 = 0; //TLH*1ms
#define DrvTimer0SetUs(x)        TH0 = 0; TL0 = x; //TL0*4us
#define DrvTimer0_Trigger()      TR0 = 1

#define DrvTimer0Set200Us()      DrvTimer0SetUs(50)
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern  UINT16 gLcdLoadTime;
extern  UINT16 g_TimeOver;
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void DrvTimer0Init();
#endif