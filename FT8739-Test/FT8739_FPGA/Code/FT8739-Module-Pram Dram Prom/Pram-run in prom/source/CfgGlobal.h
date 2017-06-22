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
#ifndef _GLOBAL_CONFIG_H_
#define _GLOBAL_CONFIG_H_

/* release版本 */
#define RELEASE_VISION  0
#define _SPI_FLASH_EN   0

#if  RELEASE_VISION
#define _CRC_CAL_EN     1         // 硬件加速求check mem
#define _FLASH_SLAVE_EN 1         // flash读slave
#define _OTP_SLAVE_EN   0         // 是否从LCD中读取OTP地址
#else
#define _CRC_CAL_EN     0         // 硬件加速求check mem,关掉可节省代码
#define _FLASH_SLAVE_EN 0         // flash读slave,关掉可节省代码
#define _OTP_SLAVE_EN   0         // 是否从LCD中读取OTP地址
#endif

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include <intrins.h>
#include "Typedef.h"
#include "FT8836.h"
#include "uart.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/

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
