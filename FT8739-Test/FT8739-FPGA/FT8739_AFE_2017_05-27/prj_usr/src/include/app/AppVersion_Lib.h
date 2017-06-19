/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: AppVersion_Lib.h
*
*    Author: linjianjun 
*
*   Created: 2013-08-01
*
*  Abstract: 
*
* Reference:
* 
* Version:
* 0.1: Transplant from FT5336 by linjianjun
*
*******************************************************************************/

#ifndef _APP_LIB_VER_H_
#define _APP_LIB_VER_H_

/* 
Version number description:
    xxxyyyyyy zzzzzzzz  total 16bits
    xxx:        Chip type,3 bits
                000     FT5412D
                001     FT5512F
                010     FT5436D
                011     FT5436W
                100     FT5536J
                101     Reserved
                110
                111     Reserved
    yyyyy:      Major version number, 5 bits
    zzzzzzzz:   Minor version number, 8 bits
*/

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
/*
 * 1. FTXX12  是MID市场
 * 2. FTXX36  是手机市场 
 */
#define FT5822_XXX      (0x00<<13)
#define FT5312_DMK      (0x01<<13)  // 13*22
#define FT5412_DQW      (0x02<<13)  // 19*24
#define FT5512_FQX      (0x03<<13)  // 22*28

#define FT5436_DQY      (0x04<<13)  // 16*27
#define FT5436_WWA      (0x05<<13)  // 20*28
#define FT5536_JHZ      (0x06<<13)  // 35*20

#define FT58X2_VER      FT5822_XXX

#define APP_LIB_VER     0x0101


/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

#define AppGetLibVer() (APP_LIB_VER | FT58X2_VER)

#endif //_APP_LIB_VER_H_ 

