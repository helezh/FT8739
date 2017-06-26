/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_spi.h
*
*    Author:
*
*   Created: 2016-12-20
*
*  Abstract: Please describe the interface in detail for this module
*
* Reference:
*
*******************************************************************************/
#ifndef _TEST_SPI0_H__
#define _TEST_SPI0_H__

/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgGlobal.h"

#if _TEST_SPI0_EN
/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#define DUMMY_LEN  1

/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/
extern volatile UINT8 far *IRAM g_ucpSpi0RxBuf;
extern volatile UINT8 far *IRAM g_ucpSpi0TxBuf;
extern volatile UINT16     IRAM dma_rx_mem_sel;
extern volatile UINT8      IRAM g_ucRxbufSel;
//extern volatile UINT8      IRAM g_ucRxDone;
/*******************************************************************************
* Global function prototypes
*******************************************************************************/

void SPI0_Init(void);
UINT8 DrvRomRegWR(UINT16 idx,UINT8 ucData);
void SPI0_DMA_IRQHandler(void);
void write_pram_task(void);
#else
#define Test_SPI0(void)     /##/
#define SPI0_Init(void)     /##/

#endif

#endif