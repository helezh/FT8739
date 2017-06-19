/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Test_spi.h
*
*    Author: tangsujun
*
*   Created: 2016-12-26
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/
#ifndef _TEST_SPI_H__
#define _TEST_SPI_H__

/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#if _TEST_SPI_EN
/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void Test_SPI_Flash();
void SPI_Init(void);
BOOLEAN SPIFlash_FastRead(UINT32 addr, UINT8 far *pBuf, UINT32 len);
#else
#define Test_SPI_Flash() /##/
#define SPI_Init(void)   /##/
#endif

#endif