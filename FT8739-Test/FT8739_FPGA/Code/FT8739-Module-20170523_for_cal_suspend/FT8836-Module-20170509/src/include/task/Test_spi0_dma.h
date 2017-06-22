/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_spi0_dma.h
*
*    Author: tangsujun
*
*   Created: 2017-03-03
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/
#ifndef _TEST_SPI0_DMA_H__
#define _TEST_SPI0_DMA_H__

/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#if _TEST_SPI0_DMA_EN
/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/
/*DMA_SRCR REG*/
#define BIT_DMA_NOT_FINISH_FLAG      BITn(11) /*cs拉高时，dma没有完成设置DMA数据包数据传输，会置1,需要软件清0*/
#define BIT_DMA_TIMEOUT_FLAG         BITn(10) /*dma数据传输时发生timeout,会置1,需要软件清0.只包括占用总线时,不包括传输CRC时间*/
#define BIT_DMA_SCK_OVERTRANS_FLAG   BITn(9) /*DMA数据包传输结束后host继续发送sck，会置1，需要软件清0*/
#define BIT_DMA_CRC_ERROR_FLAG       BITn(8) /*当处于dma写模式时，当接收到数据计算出的crc与接收到的crc不一致时，置1，软件清0*/

#define BIT_DMA_NOT_FINISH_CLR       BITn(3) /*写1清dma_not_finish_flag*/
#define BIT_DMA_TIMEOUT_CLR          BITn(2) /*写1清dma_timeout_flag*/
#define BIT_DMA_SCK_OVERTRANS_CLR    BITn(1)  /*写1清dma_sck_overtrans_flag*/
#define BIT_DMA_CRC_ERROR_CLR        BITn(0)  /*写1清dma_crc_error_flag*/
/*DMA_CTRL REG*/

#define BIT_DMA_TIMEOUT_EN           BITn(6)  /*timeout功能使能:0:disable;1:enable*/
#define BIT_DMA_TRANS_ERR_EN         BITn(5)  /*timerout或dma结束后host继续发送sck是否要发送dma_err_dat.0:不发送;1:发送*/
#define BIT_DMA_CRC_EN               BITn(4)  /*dma接收/发送数据是否需要接收/发送crc. 0: no crc;1:crc*/
#define BIT_DMA_RW                   BITn(3)  /*dma对ram进行读操作还是写操作.0:读;1:写*/
//#define BIT_DMA_RAM_SEL              (BITn(2)|BITn(1))  /*dma访问的ram选择. 2'b00:aram;2'b01:dram;2'b1x:pram*/
#define BIT_DMA_EN                   BITn(0)  /*dma功能使能hw auto clr after exit dma. 0:disbale;1:enable*/


/*DMA_ERR_TIMEOUT_CTRL REG*/
#define BIT_DMA_TIMEOUT_NUM          BITn(8) /*dma timeout时间设置,以32k时钟为单位*/
#define BIT_DMA_ERR_DAT              BITn(0) /*err byte:当timeout或者dma结束后，如果host继续发送sck，spi0向host发送error byte*/

/*DMA_ADDR_H REG*/
#define BIT_DMA_START_ADDR_H         BITn(8) /*dma的起始地址[16]*/
#define BIT_DMA_END_ADDR_H           BITn(0) /*dma的结束地址[16]*/

/*DMA_START_ADDR_L REG*/
#define BIT_DMA_START_ADDR_L         BITn(0) /*dma的起始地址[15:0]*/

/*DMA_END_ADDR_L REG*/
#define BIT_DMA_END_ADDR_L           BITn(0) /*dma的结束地址[15:0]*/

/*DMA_CRC REG*/
#define BIT_DMA_CRC                  BITn(0) /*dma传输数据的crc值*/
/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void SPI0_DMA_Init(void);
void SPI0_DMA_ClrStatus(void);
void SPI0_DMA_Wait_Done(void);
void SPI0_DMA_SetAddr(UINT32 start_addr,UINT32 len,UINT16 mem_sel);
void SPI0_DMA_Enable(UINT8 time_out,UINT8 reg);
void Test_DMA(void);
#else
#define SPI0_DMA_Init       /##/
#define SPI0_DMA_ClrStatus  /##/
#define SPI0_DMA_Wait_Done  /##/
#define SPI0_DMA_SetAddr    /##/
#define SPI0_DMA_Enable     /##/
#define Test_DMA            /##/

#endif

#endif