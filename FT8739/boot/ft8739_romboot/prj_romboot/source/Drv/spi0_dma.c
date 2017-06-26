/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_spi0_dma.c
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
#include <intrins.h>
#include "CfgGlobal.h"
#include "SPI0_dma.h"

#if _TEST_SPI0_DMA_EN


/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/







/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

volatile ST_Spi0DmaRegisters * pSpi0_DMA1 = (ST_Spi0DmaRegisters *)SPI0_REG_BASE_ADDR;
volatile ST_Spi0DmaRegisters * pSpi0_DMA2= (ST_Spi0DmaRegisters *)SPI0_DMA2_BASE_ADDR;

volatile ST_Spi0DmaConfig Spi0RxDmaConfig,Spi0TxDmaConfig;
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


/*******************************************************************************
*   Name: SPI0_DMA_Init
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI0_DMA_Init(void)
{
    SPI0_32K_EN =1;
    AFEACKEN = 1;
    ARAM_SEL = 1;   /* ARAM_SEL: 1: Mcu write and read; 0: others */




    SPI0_DMA_SetAddr(pSpi0_DMA2,(UINT32)DRAM8K_DMA_TX_ADDRESS,1+DUMMY_LEN,DMA_MEM_DRAM8K);    
    SPI0_DMA_SetAddr(pSpi0_DMA1,(UINT32)g_ucpSpi0RxBuf,1032,dma_rx_mem_sel);   
    SPI0_DMA_Enable(pSpi0_DMA2,0xff,DMA_TX_CONFIG);
    SPI0_DMA_Enable(pSpi0_DMA1,0xff,DMA_RX_CONFIG);

             
   
    
 
    
    DBG_SPI("\n dma_ctrl=%04x ",pSpi0_DMA1->dma_srcr);
    DBG_SPI("\n dma_ctrl=%04x ",pSpi0_DMA1->dma_ctrl);
    DBG_SPI("\n dma_crc =%04x ",pSpi0_DMA1->dma_crc);
    DBG_SPI("\n dma_timeout=%04x ",pSpi0_DMA1->timeout_ctrl);
    DBG_SPI("\n start_addr_h=%04x ",pSpi0_DMA1->addr_h);
    DBG_SPI("\n start_addr_l=%04x ",pSpi0_DMA1->start_addr_l);
    DBG_SPI("\n end_addr_l=%04x ",pSpi0_DMA1->end_addr_l);
    
}

/******************************************************************************
*
*   Name: SPI0_DMA_SetAddr
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
******************************************************************************/
void SPI0_DMA_SetAddr(ST_Spi0DmaRegisters *ptr,UINT32 start_addr,UINT32 len,UINT16 mem_sel)
{    
    UINT16 start_addr_h,end_addr_h;
    UINT32 end_addr;



        DBG_SPI("\n2 start_addr =%04x ",start_addr);
        DBG_SPI("\n2 len=%04x ",len);
        DBG_SPI("\n2 mem_sel=%04x ",mem_sel);
    
    end_addr        =start_addr+len-1;

    start_addr_h    =(start_addr>>16)&0x03;
    end_addr_h      =(end_addr  >>16)&0x03;

    mem_sel &= 0xC000;    
    
    ptr->addr_h=mem_sel|(start_addr_h<<8)|end_addr_h;  
    
    ptr->start_addr_l=start_addr&0xffff;
    ptr->end_addr_l=end_addr&0xffff;
    
}

/******************************************************************************
*
*   Name: SPI0_DMA_config
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
******************************************************************************/
void SPI0_DMA_Enable(ST_Spi0DmaRegisters *ptr,UINT8 time_out,UINT16 reg)
{
    
    UINT8  dma_errdr=0xec;

    ptr->dma_srcr=0x000f;
        
    ptr->timeout_ctrl=((UINT16)time_out<<8)|dma_errdr;

    ptr->dma_ctrl=reg;
    
}






#endif//if _SPI0_DMA_EN





