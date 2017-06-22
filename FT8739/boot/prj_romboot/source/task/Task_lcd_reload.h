/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Task_lcd_reload.h
*
*    Author:
*
*   Created: 2017-03-22
*
*  Abstract: Please describe the interface in detail for this module
*
* Reference:
*
*******************************************************************************/
#ifndef _TASK_LCD_RELOAD_H__
#define _TASK_LCD_RELOAD_H__

/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#if _LCD_RELOAD_EN
/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/
extern ST_LcdWrapRegisters *XRAM pLcdWrapRegs;
/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/
extern UINT8 XRAM g_ucLcdBuf[LCDINITCODE_TOTAL_SIZE];

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void DrvPrepareLcdInitCode(void);
void AppLcdInitCodeReload(void);
void Read_Lcd_OTP(UINT16 *ptr16,UINT8 len);
#else
#define DrvPrepareLcdInitCode /##/
#define AppLcdInitCodeReload  /##/
#define Read_Lcd_OTP         /##/       
#endif

#endif