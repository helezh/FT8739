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
#ifndef  __UART1_H__
#define  __UART1_H__

/* Conditional Compiler Options */
#define _BLK_DBG_EN      1

#if _BLK_DBG_EN
/*******************************************************************************
* Included files
*******************************************************************************/
#include <STDIO.H>
#include <REG251S.H>
#include "CfgGlobal.h"

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#define BAUD_RATE 115200
//#define BAUD_RATE 57600
//#define BAUD_RATE 38400
//#define BAUD_RATE 19200
//#define BAUD_RATE 9600
#define _UART_RECEIVE_EN   0  // 接收使能宏


#define _UART_OUT_GPIO2    0    //P0.6
#define _UART_OUT_GPIO3    1    //default P0.7
#define _UART_OUT_GPIO4    0    //P0.3 or P1.7

#define _FOR_RD            0    //用来取消打印和delay

/************** 模块输出宏 ***************/
/* module */
#if _FOR_RD
#define DBG_FLOW        /##/
#define DBG_SFR         /##/
#define DBG_DRAM        /##/
#define DBG_PROM        /##/
#define DBG_ARAM        /##/
#define DBG_SPI0_REG    /##/
#define DBG_XSI_REG     /##/
#define DBG_XBUS_REG    /##/
#define DBG_ASM_REG     /##/
#define DBG_CAL_REG     /##/
#define DBG_LCD_REG     /##/
#define DBG_AFE_REG     /##/
#define DBG_AFE_RAM     /##/
#define DBG_SPI         /##/
#define DBG_LED         /##/
#define DBG_I2C         /##/

#define DBG_WDT         /##/
#define DBG_RTC         /##/
#define DBG_CNT         /##/
#define DBG_GPIO        /##/
#define DBG_TIMER       /##/
#define DBG_INT         /##/
#define DBG_GPIOWK      /##/
#define DBG_I2CWK       /##/
#define DBG_XSI         /##/
#define DBG_CAL         /##/
#define DBG_CAL_DATA    /##/
#define DBG_AFE         /##/
#define DBG_MODE        /##/
#define DBG_ERROR       /##/
#define DBG_UART        /##/
#define DBG_SPI0WK      /##/
#define DBG_DEBUGOUT    /##/

#else
#define DBG_FLOW        printf       //printf in main.c
#define DBG_SFR         printf
#define DBG_DRAM        printf
#define DBG_PROM        printf
#define DBG_ARAM        printf
#define DBG_SPI0_REG    printf
#define DBG_XSI_REG     printf
#define DBG_XBUS_REG    printf
#define DBG_ASM_REG     printf
#define DBG_CAL_REG     printf
#define DBG_LCD_REG     printf
#define DBG_AFE_REG     printf
#define DBG_AFE_RAM     printf
#define DBG_SPI         printf
#define DBG_LED         printf
#define DBG_I2C         printf

#define DBG_WDT         printf
#define DBG_RTC         printf
#define DBG_CNT         printf
#define DBG_GPIO        printf
#define DBG_TIMER       printf
#define DBG_INT         printf
#define DBG_GPIOWK      printf
#define DBG_I2CWK       printf
#define DBG_XSI         printf
#define DBG_CAL         printf
#define DBG_CAL_DATA    printf
#define DBG_AFE         printf
#define DBG_MODE        printf
#define DBG_ERROR       printf
#define DBG_XBUS        printf
#define DBG_ECC         printf
#define DBG_UART        printf
#define DBG_SPI0WK      printf
#define DBG_DEBUGOUT    printf
#endif

void  DrvUartInit(void);
SINT8 putchar(SINT8 c);
UINT8 CLK_DIV(UINT8 div);
void wait_printf_done(void);

extern volatile UINT8 XRAM s_ucUartTxLen;
#else
#define DrvUartInit()        /##/
#define CLK_DIV()            /##/
#define wait_printf_done()   /##/ 
/************** 模块输出宏 ***************/
/* module */
#define DBG_FLOW        /##/
#define DBG_SFR         /##/
#define DBG_DRAM        /##/
#define DBG_PROM        /##/
#define DBG_ARAM        /##/
#define DBG_SPI0_REG    /##/
#define DBG_XSI_REG     /##/
#define DBG_XBUS_REG    /##/
#define DBG_ASM_REG     /##/
#define DBG_CAL_REG     /##/
#define DBG_LCD_REG     /##/
#define DBG_AFE_REG     /##/
#define DBG_AFE_RAM     /##/
#define DBG_SPI         /##/
#define DBG_LED         /##/
#define DBG_I2C         /##/

#define DBG_WDT         /##/
#define DBG_RTC         /##/
#define DBG_CNT         /##/
#define DBG_GPIO        /##/
#define DBG_TIMER       /##/
#define DBG_INT         /##/
#define DBG_GPIOWK      /##/
#define DBG_I2CWK       /##/
#define DBG_XSI         /##/
#define DBG_CAL         /##/
#define DBG_CAL_DATA    /##/
#define DBG_AFE         /##/
#define DBG_MODE        /##/
#define DBG_ERROR       /##/
#define DBG_UART        /##/
#define DBG_SPI0WK      /##/
#define DBG_DEBUGOUT    /##/

#endif
/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/

#endif

