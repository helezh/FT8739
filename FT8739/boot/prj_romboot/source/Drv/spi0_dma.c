/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
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


/*DMA_CTRL REG*/
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


#define ARAM_START_ADDRESS   0xA000
#define ARAM_END_ADDRESS     0xA500
#define ARAM_LENGTH          0x500
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/







/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

volatile ST_Spi0DmaRegisters *XRAM pSpi0_DmaRegs = (ST_Spi0DmaRegisters *)SPI0_REG_BASE_ADDR;


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
    CLKEN_32K4SPI0 =1;
    AFEACKEN = 1;
    ARAM_SEL = 1;   /* ARAM_SEL: 1: Mcu write and read; 0: others */
#if 1   
    pSpi0_DmaRegs->dma_ctrl=0;
    pSpi0_DmaRegs->timeout_ctrl=0;
    pSpi0_DmaRegs->addr_h=0;
    pSpi0_DmaRegs->start_addr_l=0;
    pSpi0_DmaRegs->end_addr_l=0;
    pSpi0_DmaRegs->dma_srcr=0x000f;
#else
    SPI0_DMA_SetAddr(0,0,0);
    SPI0_DMA_Enable(0,0);
#endif
    
    
    DBG_SPI("\n dma_ctrl=%04x ",pSpi0_DmaRegs->dma_srcr);
    DBG_SPI("\n dma_ctrl=%04x ",pSpi0_DmaRegs->dma_ctrl);
    DBG_SPI("\n dma_crc =%04x ",pSpi0_DmaRegs->dma_crc);
    DBG_SPI("\n dma_timeout=%04x ",pSpi0_DmaRegs->timeout_ctrl);
    DBG_SPI("\n start_addr_h=%04x ",pSpi0_DmaRegs->addr_h);
    DBG_SPI("\n start_addr_l=%04x ",pSpi0_DmaRegs->start_addr_l);
    DBG_SPI("\n end_addr_l=%04x ",pSpi0_DmaRegs->end_addr_l);
    
}
/*******************************************************************************
*   Name: SPI0_DMA_ClrStatus
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI0_DMA_ClrStatus(UINT8 *val)
{  
    if(pSpi0_DmaRegs->dma_srcr==0)
    {
        *val='k';
    }
    else
    {
        *val='e';
    }    
    pSpi0_DmaRegs->dma_srcr=0x000f;    
}
#if 0
/*******************************************************************************
*   Name: SPI0_DMA_Wait_Done
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI0_DMA_Wait_Done(void)
{    
    while(pSpi0_DmaRegs->dma_ctrl & BIT_DMA_EN);    
}
#endif
/*******************************************************************************
*   Name: SPI0_DMA_SetAddr
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI0_DMA_SetAddr(UINT32 start_addr,UINT32 len,UINT16 mem_sel) //reentrant
{    
    UINT16 start_addr_h,end_addr_h;
    UINT32 end_addr;
    
    end_addr        =start_addr+len-1;
    start_addr_h    =(start_addr>>16)&0x03;
    end_addr_h      =(end_addr  >>16)&0x03;

    mem_sel &= 0xC000;    
    
    pSpi0_DmaRegs->addr_h=mem_sel|(start_addr_h<<8)|end_addr_h;  
    
    pSpi0_DmaRegs->start_addr_l=start_addr;
    pSpi0_DmaRegs->end_addr_l=end_addr;
    
}

/*******************************************************************************
*   Name: SPI0_DMA_config
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI0_DMA_Enable(UINT8 time_out,UINT8 reg)
{
    
    UINT8  dma_errdr=0xea;

    pSpi0_DmaRegs->dma_srcr=0x000f;
        
    pSpi0_DmaRegs->timeout_ctrl=((UINT16)time_out<<8)|dma_errdr;

    pSpi0_DmaRegs->dma_ctrl=reg;
    
}
#if 0
volatile UINT8  XRAM DRAMBUF[16];
/*******************************************************************************
*   Name: Test_DMA
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_DMA(void)
{
    volatile UINT8  far *ucpAsmram;
    UINT16 i=0,j=0;
    UINT8  reg=0,temp=10;

    //SPI0_Init();
    //SPI0_EI = 0;

    ucpAsmram=PRAM_PTR8(0);
    //ucpAsmram =&DRAMBUF[0];//&BUF[0];
    //ucpAsmram =ARAM_START_ADDRESS;
    
    AFEACKEN = 1;
    ARAM_SEL = 1;   /* ARAM_SEL: 1: Mcu write and read; 0: others */

   
        for (i = 0; i < 16; i++)
        {
         //   if (!(i&0x01))
                *(ucpAsmram+i) = temp;
         //   else
         //       *(ucpAsmram+i) = 0xa5;
        }
        for (i = 0; i < 16; i++)
        {
            if (i%16 == 0)
            {
                DBG_SPI("\n");
            }
            DBG_SPI("%02x ",*(ucpAsmram+i));

        }
        temp++;
 
    
    SPI0_DMA_Init();
    SPI0_DMA_SetAddr(ucpAsmram,6,DMA_MEM_PRAM);
    

    
    while(1)
    {
        DBG_SPI("\n1  ARAM_SEL=%02x ",ARAM_SEL);
#if _BLK_DBG_EN
        wait_printf_done();
#endif
        
        SPI0_DMA_Enable(0xff,(DMA_TIMEOUT_DIS|DMA_TRANS_ERR_DIS|DMA_CRC_DIS|DMA_WD|
        DMA_CLR_RI_EN|DMA_CLR_TI_EN|DMA_EN));

        SPI0_DMA_Wait_Done();


        DelayUs_EX(100);
        DBG_SPI("\n dma_srcr=%04x ",pSpi0_DmaRegs->dma_srcr);
        DBG_SPI("\n dma_ctrl=%04x ",pSpi0_DmaRegs->dma_ctrl);
        DBG_SPI("\n dma_crc =%04x ",pSpi0_DmaRegs->dma_crc);
        DBG_SPI("\n dma_timeout=%04x ",pSpi0_DmaRegs->timeout_ctrl);
        DBG_SPI("\n start_addr_h=%04x ",pSpi0_DmaRegs->addr_h);
        DBG_SPI("\n start_addr_l=%04x ",pSpi0_DmaRegs->start_addr_l);
        DBG_SPI("\n end_addr_l=%04x ",pSpi0_DmaRegs->end_addr_l);

        DBG_SPI("\n2  ARAM_SEL=%02x ",ARAM_SEL);
        //HOLD;
        for (i = 0; i < 16; i++)
        {
            if (i%16 == 0)
            {
                DBG_SPI("\n");
            }
            DBG_SPI("%02x ",*(ucpAsmram+i));
            
            *(ucpAsmram+i)=0x5a;
        }
        
       // DelayMs(1000);
    }
    
}

#endif











#endif//if _SPI0_DMA_EN





