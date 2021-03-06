/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Test_RTC.h
*
*    Author: xinkunpeng
*
*   Created: 2014-04-18
*
*  Abstract:
*
* Reference:
*
* Version:
* 0.1:
*
*******************************************************************************/
#ifndef __TEST_SOFT_RST__
#define __TEST_SOFT_RST__

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

#if _TEST_SOFT_RST_EN

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
void Test_SOFT_RST(void);
#else
#define Test_SOFT_RST  /##/
#endif

#endif
