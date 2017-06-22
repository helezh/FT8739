/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)��All Rights Reserved.
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


/* release�汾 */
#define RELEASE_VISION  0

#define _SPI_FLASH_EN       1
#define _LCD_RELOAD_EN      1 // APP��Flash����LCD_config


#define _TEST_SPI0_EN       1
#define _TEST_SPI0_DMA_EN   1
#define _TEST_I2C_EN        1

#if  RELEASE_VISION
#define _CRC_CAL_EN     1         // Ӳ��������check mem
#define _OTP_SLAVE_EN   1         // �Ƿ��LCD�ж�ȡOTP��ַ
#define _TEST_FLASH_LOAD_EN   0   // ����FLASH_LOAD 
#define _TEST_PRAM_EN         0   // ���� PRAM 
#else
#define _CRC_CAL_EN     1         // Ӳ��������check mem,�ص��ɽ�ʡ����
#define _OTP_SLAVE_EN   1         // �Ƿ��LCD�ж�ȡOTP��ַ
#define _TEST_FLASH_LOAD_EN   0   // ����FLASH_LOAD 
#define _TEST_PRAM_EN         0   // ���� PRAM 
#define _FLASH_TO_LCD         0  
#endif

/* ÿ�����Ĵ�С���Ĵ�����Ч�� Winbond���ֻ����0x100 */
#define PACK_MAX                        0x100  //256byte--->0.56ms
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern UINT8 Bus_I2C_SPI0;  //0 I2C 1 SPI0
extern UINT8 g_ucFlashMode; // ����flashѡ��








/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

/* Release/debug version select */

#endif //GLOBAL_CONFIG_H
