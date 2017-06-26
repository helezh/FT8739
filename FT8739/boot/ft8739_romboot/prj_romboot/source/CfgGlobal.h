/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: CfgGlobal.h
*
*    Author: xinkunpeng
*
*   Created: 2013-07-21
*
*  Abstract:
*
* Reference:
*
* Version:
*
*******************************************************************************/
#include "Typedef.h"
#include "FT8836.h"
#include "FT8836_Reg.h"
#include "Uart.h"
#include "DrvCalCrc.h" 
#include "DrvTimer.h"
#include "Task_main.h"
#include "Drv_mcu.h"
#include "Task_hcomm.h"
#include "Spi_flash.h"
#include "Spi0_dma.h"
#include "Task_SPI0.h"
#include "Task_lcd_reload.h"
/******************************************************************************/
#ifndef _GLOBAL_CONFIG_H_
#define _GLOBAL_CONFIG_H_

#define CHIP_ID_H     0x88
#define CHIP_ID_L     0x35


/* release版本 */
#define RELEASE_VISION  0

#define _SPI_FLASH_EN       1
#define _LCD_RELOAD_EN      1 // 从Flash导入LCD_config


#define _TEST_SPI0_EN       1
#define _TEST_SPI0_DMA_EN   1
#define _TEST_I2C_EN        1

#if  RELEASE_VISION
#define _CRC_CAL_EN     1         // 硬件加速求check mem
#define _OTP_SLAVE_EN   1         // 是否从LCD中读取OTP地址
#define _TEST_FLASH_LOAD_EN   0   // 测试FLASH_LOAD 
#define _TEST_PRAM_EN         0   // 测试 PRAM 
#else
#define _CRC_CAL_EN     1         // 硬件加速求check mem,关掉可节省代码
#define _OTP_SLAVE_EN   1         // 是否从LCD中读取OTP地址
#define _TEST_FLASH_LOAD_EN   0   // 测试FLASH_LOAD 
#define _TEST_PRAM_EN         0   // 测试 PRAM 
#endif

/* 每个包的大小，改大会提高效率 Winbond最大只能是0x100 */
#define PACK_MAX                        0x100  //256byte--->0.56ms

// IO口电压设置
#define IO_VCC_33        1    // 0 --1.8v  1 -- 3.3V

#define INT_EN           0
#define INT_DIS          1

#define DIR_OUT          1
#define DIR_IN           0

#define G_USAGE          0
#define S_USAGE          1

#define DM_PP            1
#define DM_OD            0

#define ON               1
#define OFF              0
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern UINT8 Bus_I2C_SPI0;  //0 I2C 1 SPI0
extern UINT8 g_ucFlashMode; // 有无flash选择








/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

/* Release/debug version select */

#endif //GLOBAL_CONFIG_H
