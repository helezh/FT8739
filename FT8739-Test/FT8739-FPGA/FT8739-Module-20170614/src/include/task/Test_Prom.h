/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Test_Prom.h
*
*    Author: xinkunpeng
*
*   Created: 2014-04-24
*
*  Abstract: Please describe the interface in detail for this module
*
* Reference:
*
*******************************************************************************/
#ifndef _TEST_PROM_H__
#define _TEST_PROM_H__

/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/

#if _TEST_PROM_EN
/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void Test_Prom(void);
#else
#define Test_Prom()  /##/
#endif

#endif
