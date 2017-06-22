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
#ifndef _GLOBAL_CONFIG_H_
#define _GLOBAL_CONFIG_H_

/* release�汾 */
#define RELEASE_VISION  0
#define _SPI_FLASH_EN   0

#if  RELEASE_VISION
#define _CRC_CAL_EN     1         // Ӳ��������check mem
#define _FLASH_SLAVE_EN 1         // flash��slave
#define _OTP_SLAVE_EN   0         // �Ƿ��LCD�ж�ȡOTP��ַ
#else
#define _CRC_CAL_EN     0         // Ӳ��������check mem,�ص��ɽ�ʡ����
#define _FLASH_SLAVE_EN 0         // flash��slave,�ص��ɽ�ʡ����
#define _OTP_SLAVE_EN   0         // �Ƿ��LCD�ж�ȡOTP��ַ
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
