/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: TestRwSFR.h
*
*    Author: 
*
*   Created: 2013-05-27
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/
#ifndef _TEST_RW_SFR_H__
#define _TEST_RW_SFR_H__

/*******************************************************************************
* 1.Included files
*******************************************************************************/

#include "CfgGlobal.h"

#if _TEST_RW_SFR_EN
/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/



/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/
typedef enum
{
    ID_G_DEVICE_ID              =  0x00,
    ID_G_SFR_80                 =  0x80,
    ID_G_SFR_FF                 =  0xFF
} ENUM_TestSFR;

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void  AppWriteSFR(UINT8 ucAddr, UINT8 ucData);
UINT8 AppReadSFR(UINT8 ucAddr);
#else
#define AppWriteSFR(x)  /##/
#define AppReadSFR(x)   /##/

#endif


#endif

