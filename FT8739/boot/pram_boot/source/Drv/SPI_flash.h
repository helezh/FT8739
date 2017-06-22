/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: SPI_flash.h
*
*    Author: tangsujun
*
*   Created: 2017-01-20
*
*  Abstract:
*
* Reference:
*
* Version:
*
*******************************************************************************/
#ifndef _SPI_FLASH_H__
#define _SPI_FLASH_H__

/* Conditional Compiler Options */
/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/

//flash信息宏
#define PAGE_SIZE           0x80     // 定义页大小
#define SECTOR_SIZE         0x1000   // 定义扇区大小
#define BLOCK_SIZE          0x10000  // 定义块区大小
#define PAGE_WRITE_TIME     100      // ms
#define SECTOR_ERASE_TIME   500      // ms
#define BLOCK_ERASE_TIME    4000     // ms
#define CHIP_ERASE_TIME     8000     // ms
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void SPI_Init(void);
BOOLEAN SPI_WriteData(UINT8 val);
BOOLEAN SPI_Write(UINT8 *pBuf, UINT16 len);
UINT8 SPI_ReadData(void);
void SPI_Read(UINT8 *pBuf, UINT16 len);

void SPIFlashSoftWpInit();
BOOLEAN SPIFlash_FastRead(UINT32 addr, UINT8 *pBuf, UINT16 len);
BOOLEAN SPIFlash_Write(UINT32 addr, UINT8 *pBuf,UINT16 len);

void SPIFlash_EraseSector(UINT8 sector);
void SPIFlash_EraseBlock(UINT8 block);
void SPIFlash_EraseChip(void);
UINT32 SPIFlash_ReadID(void);
void test_flash_to_pram(void);
#endif  // _SPI_FLASH_EN

