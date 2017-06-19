/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: uart.h
*
*    Author: linjianjun
*
*   Created: 2013-06-05
*
*  Abstract: DBG_输出不能换行操作
*
* Reference:
*
*******************************************************************************/
#ifndef  __UART_H__
#define  __UART_H__

/*******************************************************************************
* 1.Included files
*******************************************************************************/

#include "CfgGlobal.h"
#include <STDIO.H>

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define _BLK_DBG_EN     1 /* Uart Debug */
#define _PRAM_DBG_EN    1  /* pram指定位置 Debug */

#define DBG_INFO_0      0xF000
#if _BLK_DBG_EN

#define BAUD_RATE          115200
#define _UART_RECEIVE_EN   0  // 接收使能宏
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/


/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void  DrvUartInit(void);
SINT8 putchar(SINT8 c);

#define DBG_FLOW       printf
#define DBG_SPI        /##/printf
#define DBG_RST        /##/printf
#define DBG_I2C        /##/printf
#define DGB_INT        /##/printf
#define DGB_ECC        /##/printf
#define DBG_BOOT       /##/printf
#else
#define DrvUartInit(x) /##/

//module
#define DBG_FLOW       /##/
#define DBG_SPI        /##/
#define DBG_RST        /##/
#define DBG_I2C        /##/
#define DGB_INT        /##/
#define DGB_ECC        /##/
#define DBG_BOOT       /##/
#endif
//------------------------------------------------------------------------------
#if _PRAM_DBG_EN
#define DEBUG_PRAM(addr)  /##/PRAM_ADDR8(addr)
#else
#define DEBUG_PRAM(addr)  /##/
#endif

#endif
