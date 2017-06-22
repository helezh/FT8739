/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Drv_Xbus.h
*
*    Author: xinkunpeng
*
*   Created: 2016-06-14
*
*  Abstract:
*
* Reference:
*
*   Version:
*******************************************************************************/
#ifndef __DRV_XBUS_H__
#define __DRV_XBUS_H__

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"
#include "FT8836_Reg.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
//extern ST_RlDmaRegisters * XRAM pRlDmaRegs;
extern ST_LcdWrapRegisters *XRAM pLcdWrapRegs;

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void Drv_XbusInit();
UINT16 DrvXbus_ReadLcd16(UINT16 usaddr);
void DrvXbus_WriteLcd8(UINT16 usaddr,UINT8 usdata);

#if _TEST_XBUS_EN
void Test_Xbus(void);
#else
//#define Test_Xbus  /##/
#endif

#endif

