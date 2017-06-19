/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Test_LED.h
*
*    Author: xinkunpeng
*
*   Created: 2014-06-06
*
*  Abstract:
*
* Reference:
*
* Version:
* 0.1:
*
*******************************************************************************/
#ifndef __TEST_LED__
#define __TEST_LED__

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

#if _TEST_LED_EN
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
void Test_LED(void);
#else
#define Test_LED  /##/
#endif

#endif
