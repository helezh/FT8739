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

/* Conditional Compiler Options */
#define _BLK_DBG_EN      1

#if _BLK_DBG_EN
/*******************************************************************************
* Included files
*******************************************************************************/
#include <STDIO.H>
#include "FT8836.h"
#include "CfgGlobal.h"
/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#define BAUD_RATE 115200
#define _UART_RECEIVE_EN   0  // 接收使能宏
/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void  DrvUartInit(void);
SINT8 putchar(SINT8 c);

#define DBG_FLOW          printf
#define DBG_HOST          printf
#define DBG_I2C           /##/printf
#define DBG_TEST          /##/printf
#define DBG_5003          /##/printf
#define DBG_SPI           printf
#define DGB_CHAR          /##/putchar
#define DBG_FLASH_ECC			/##/printf
#else
#define DrvUartInit(x)    /##/

//module
#define DBG_FLOW          /##/
#define DBG_HOST          /##/
#define DBG_I2C           /##/
#define DBG_TEST          /##/
#define DBG_5003          /##/
#define DBG_SPI           /##/
#define DGB_CHAR          /##/

#endif

#endif
