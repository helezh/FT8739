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
/*SPI0_DMA init*/
typedef struct
{
    volatile  UINT32 start_addr;
    volatile  UINT16 len;
    volatile  UINT16 mem_sel;    
    volatile  UINT8  time_out;
    volatile  UINT8  dma_ctrl;
    
}ST_Spi0DmaConfig;
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




/*DMA_CTRL REG*/
#define DMA_CRC_FH               ((UINT16)1<<10)  
#define DMA_CRC_FL               ((UINT16)0<<10)

#define DMA_TIMEOUT_DL           ((UINT16)2<<8)  
#define DMA_TIMEOUT_D2           ((UINT16)1<<8)  
#define DMA_TIMEOUT_D1           ((UINT16)0<<8)

#define DMA_DUAL_EN              ((UINT16)1<<7)  
#define DMA_DUAL_DIS             ((UINT16)0<<7) 

#define DMA_TIMEOUT_EN           ((UINT16)1<<6)  
#define DMA_TIMEOUT_DIS          ((UINT16)0<<6)  

#define DMA_TRANS_ERR_EN         ((UINT16)1<<5)  /*timerout或dma结束后host继续发送sck是否要发送dma_err_dat.0:不发送;1:发送*/
#define DMA_TRANS_ERR_DIS        ((UINT16)0<<5)

#define DMA_CRC_EN               ((UINT16)1<<4)  /*dma接收/发送数据是否需要接收/发送crc. 0: no crc;1:crc*/
#define DMA_CRC_DIS              ((UINT16)0<<4)

#define DMA_WD                   ((UINT16)1<<3)  /*dma对ram进行读操作还是写操作.0:读;1:写*/
#define DMA_RD                   ((UINT16)0<<3) 

#define DMA_CLR_RI_EN            ((UINT16)1<<2)
#define DMA_CLR_RI_DIS           ((UINT16)0<<2)

#define DMA_CLR_TI_EN            ((UINT16)1<<1)
#define DMA_CLR_TI_DIS           ((UINT16)0<<1)

#define DMA_EN                   ((UINT16)1<<0)

/*DMA_ADDR_H REG*/
#define DMA_MEM_DRAM8K           ((UINT16)3<<14)
#define DMA_MEM_PRAM             ((UINT16)2<<14)/*dma访问的ram选择. 2'b00:aram;2'b01:dram;2'b1x:pram*/
#define DMA_MEM_DRAM             ((UINT16)1<<14)/*dma访问的ram选择. 2'b00:aram;2'b01:dram;2'b1x:pram*/
#define DMA_MEM_ARAM             ((UINT16)0<<14) /*dma访问的ram选择. 2'b00:aram;2'b01:dram;2'b1x:pram*/



#define DMA_RX0_CONFIG   (DMA_TIMEOUT_DIS|DMA_TRANS_ERR_DIS|DMA_CRC_EN|DMA_WD|\
            DMA_CLR_RI_EN|DMA_CLR_TI_DIS|DMA_EN)
#define DMA_RX_CONFIG   (DMA_DUAL_EN|DMA_TIMEOUT_DIS|DMA_TRANS_ERR_EN|DMA_CRC_EN|DMA_WD|\
            DMA_CLR_RI_EN|DMA_CLR_TI_DIS|DMA_EN)

#define DMA_TX_CONFIG   (DMA_DUAL_EN|DMA_TIMEOUT_DIS|DMA_TRANS_ERR_EN|DMA_CRC_EN|DMA_RD|\
            DMA_CLR_RI_EN|DMA_CLR_TI_DIS|DMA_EN)

#define ARAM_START_ADDRESS   0xA000
#define ARAM_END_ADDRESS     0xA500
#define ARAM_LENGTH          0x500

#define DRAM8K_START_ADDRESS   0x8000
#define DRAM8K_END_ADDRESS     0xA000
#define DRAM8K_LENGTH          0x2000

#define DRAM8K_DMA_TX_ADDRESS   (DRAM8K_START_ADDRESS+0X1000)


extern volatile ST_Spi0DmaConfig Spi0RxDmaConfig,Spi0TxDmaConfig;
extern volatile ST_Spi0DmaRegisters * pSpi0_DMA1;
extern volatile ST_Spi0DmaRegisters * pSpi0_DMA2;
/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void SPI0_DMA_Init(void);
void SPI0_DMA_ClrStatus(UINT8 *val);
void SPI0_DMA_Wait_Done(void);

void SPI0_DMA_SetAddr(ST_Spi0DmaRegisters *ptr,UINT32 start_addr,UINT32 len,UINT16 mem_sel);// reentrant;
void SPI0_DMA_Enable(ST_Spi0DmaRegisters *ptr,UINT8 time_out,UINT16 reg);
//void Test_DMA(void);
#else
#define SPI0_DMA_Init       /##/
#define SPI0_DMA_ClrStatus  /##/
#define SPI0_DMA_Wait_Done  /##/
#define SPI0_DMA_SetAddr    /##/
#define SPI0_DMA_Enable     /##/
#define Test_DMA            /##/

#endif

#endif
