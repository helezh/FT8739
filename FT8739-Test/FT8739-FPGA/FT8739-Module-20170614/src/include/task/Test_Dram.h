/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_Dram.h
*
*    Author: xinkunpeng
*
*   Created: 2014-04-22
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/
#ifndef _TEST_DRAM_H__
#define _TEST_DRAM_H__

/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgGlobal.h"

#if _TEST_DRAM_EN
/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#define TEST_PATTERN1         0x5A
#define TEST_PATTERN2         0xA5
#define TEST_PATTERN3         0x55AA
#define TEST_PATTERN4         0xAA55
#define TEST_PATTERN5         0x12345678//0x55AA55AA
#define TEST_PATTERN6         0x11223344//0xAA55AA55

/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/
extern UINT8  XRAM ucReadBack;
extern UINT16 XRAM usReadBack;
extern UINT32 XRAM ulReadBack;

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void Test_Dram(void);
#else
#define Test_Dram()  /##/
#endif

#endif
