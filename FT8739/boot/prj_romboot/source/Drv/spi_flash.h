/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: SPI-flash.h
*
*    Author: tangsujun
*
*   Created: 2016-12-22
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

#if _SPI_FLASH_EN
/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define SPI_CON    SPI1CON
#define SPI_CON2   SPI1CON2
#define SPI_BUF    SPI1BUF

//位功能
#define SPI_TI     SPI1TI
#define SPI_RI     SPI1RI
#define SPI1_CSN SPI1SLVELO

// SPI FLASH操作指令定义
#define CMD_WRSR            0x01     // Write Status Register Command
#define CMD_WRITE           0x02     // Write Command
#define CMD_READ            0x03     // Read Command
#define CMD_WRDI            0x04     // Reset Write Enable Latch Command
#define CMD_RDSR            0x05     // Read Status Register Command
#define CMD_RDSR2           0x35     // Read Status Register 2 Command
#define CMD_WREN            0x06     // Set Write Enable Latch Command
#define CMD_FAST_READ       0x0B     // Fast Read Command
#define CMD_RD_JEDEC_ID     0x9F     // Read Manufacturer and Product ID
#define CMD_RDID            0x90     // Read Manufacturer, Memory Type and Capacity
#define CMD_SECTOR_ERASE    0x20     // Erase One Sector in Memory Array
#define CMD_BLOCK_ERASE     0xD8     // Erase One Block in Memory Array
#define CMD_CHIP_ERASE      0x60     // Erase All Sectors in Memory Array
#define CMD_WAKEUP          0xAB     // Release Power_down or Read Device ID according to usage
#define CMD_POWERDOWN       0xB9     // Power down 

#define CMD_READ_DUAL_O       0x3B     // Fast Read Dual Output Command
#define CMD_READ_QUAD_O       0x6B     // Fast Read Quad Output Command
#define CMD_READ_DUAL_IO      0xBB     // Fast Read Dual I/O Command
#define CMD_READ_QUAD_IO      0xEB     // Fast Read Quad I/O Command
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern UINT8 spi_std_dual,spi_cmd ;
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void SPI_Init(void);
void Flash_Init(void);
BOOLEAN SPI_WriteData(UINT8 val);
void SPI_Read(UINT8 far *pBuf, UINT32 len);

/******************************************************************************/
//flash驱动
void SPIFlash_FastRead(UINT32 addr, UINT8 far *pBuf, UINT32 len);
void SPIFlash_DualRead(UINT32 addr, UINT8 far *pBuf, UINT32 len);
void SPIFlash_FastReadAddr(UINT32 addr);
void SPIFlash_ReadToPram(UINT32 addr, UINT32 pramstart, UINT32 len);
void SPI_PRAM_TEST(void);
UINT32 SPIFlash_ReadID(void);

void SPIFlash_ReadToLCD(UINT32 addr,UINT32 len);
#else
#define SPI_Init                /##/
#define Flash_Init              /##/
#define SPI_WriteData           /##/
#define SPI_Read                /##/
#define SPIFlash_FastRead       /##/
#define SPIFlash_ReadToPram     /##/
#define SPIFlash_ReadID         /##/
#endif

#endif
