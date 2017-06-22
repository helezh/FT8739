/*******************************************************************************
* Copyright (C) 2017-2019, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Drv_XBUS.h
*
*    Author: tangsujun
*   Created: 2017-03-22
*
*  Abstract:
*
* Reference:
*
*   Version:CRC 0X020304 0305
*
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
void Drv_XbusInit(void);
UINT16 DrvXbus_ReadLcd16(UINT16 usaddr);
void DrvXbus_WriteLcd8(UINT16 usaddr,UINT8 usdata);
void DrvXbus_WriteLcd16(UINT16 usaddr,UINT16 usdata);
#if _TEST_XBUS_EN
void Test_Xbus(void);
#else
#define Test_Xbus  /##/
#endif

#endif

