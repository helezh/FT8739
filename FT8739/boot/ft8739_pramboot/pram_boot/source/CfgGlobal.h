/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: CfgGlobal.h
*
*    Author: tangsujun
*
*   Created: 2017-01-20
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/
#ifndef __GLOBAL_CONFIG_H__
#define __GLOBAL_CONFIG_H__

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "Typedef.h"
#include "FT8836.h"
#include "uart.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
/* main clk */
#define DIV_CLK_48M             0
#define DIV_CLK_24M             1
#define MAIN_CLK                DIV_CLK_48M

#define _FLASH_SLAVE_EN         0     /* flash¶ÁslaveµØÖ·Ê¹ÄÜ */
#define _LCD_XSI2_EN            0

#define _8707U_FLOW_EN          0 /* 8707 Ver.U flow */
#define _8707D_FLOW_EN          0 /* 8707 Ver.B,Ver.D flow */
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

#endif //GLOBAL_CONFIG_H
