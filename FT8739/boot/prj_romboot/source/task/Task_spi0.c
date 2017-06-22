/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_spi.c
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
#include "CfgGlobal.h"

#include "Task_SPI0.h"

#if _TEST_SPI0_EN



/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

#define SPI_VECTOR 10




//位功能




typedef enum
{
    HCMD_NOF          = 0x00,
    HCMD_TOUCH        = 0x01,
    HCMD_RST          = 0x07,
    HCMD_APP_START    = 0x08,
    HCMD_START1       = 0x55,
    HCMD_DATA_R       = 0x85,
    HCMD_DATA_RN      = 0x86,
    HCMD_ID           = 0x90,
    HCMD_VENDOR_ID    = 0xA8,
    HCMD_DATA_WN      = 0xAD,
    HCMD_DATA_W       = 0xAE,
    HCMD_ECC          = 0xCC,
    HCMD_BOOT_STATE   = 0xD0,
    HCMD_ROM_VERSION  = 0xDB,

    HCMD_RST_STA       = 0xE0,
    HCMD_XRST_STA      = 0xE1,
    HCMD_Upgrade_Flg   = 0xE2,
    HCMD_POR_CLR       = 0xE3,
    HCMD_LCDReLoad_STA = 0xE4,

    HCMD_TEST_PRAM     = 0xF0,
    HCMD_TEST_PRAM_STA = 0xF1,
    HCMD_GET_STA       = 0xF2,
} ENUM_RomCmd;


/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/



/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/


/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
/*******************************************************************************
*   Name: SPI0_Init
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI0_Init(void)
{
#if 0
#if _TEST_SPI0_DMA_EN
    INTOUT=0;

    SPI0_DMA_SetAddr(PRAM_PTR8(g_usAppStartAddr),g_ucAppLen,DMA_MEM_PRAM);
    SPI0_DMA_Enable(0xff,(DMA_TIMEOUT_DIS|DMA_TRANS_ERR_DIS|DMA_CRC_DIS|DMA_WD|
    DMA_CLR_RI_EN|DMA_CLR_TI_EN));
    SPI0_DMA_ClrStatus();

    INTOUT=1;
#endif 
#endif 
    SPI0CKEN = 1;
    SPI0CON5 =0xff;
    SPI0CON2 =0xc2;
    SPI0CON3 =0;
    SPI0CON4 =0X00;
    
    //SPI0_EDGE_SEL =1;
    
    /* IO配置: P05-->P02  MOSI MISO CLK CS */
    P0MOD |= BITn(5) + BITn(4)+BITn(3) + BITn(2);
    P0SEL |= BITn(5) + BITn(4)+BITn(3) + BITn(2);
    
    P0DIR |= BITn(4)+BITn(3) + BITn(2);
    P0DIR &= ~ BITn(5);



    SPI0_IPH = 1;
    SPI0_IPL = 1;
    SPI0_EI  = 1;
    

#if 0


    //中断标志使能
    SPI0RI_EN = 1;
    SPI0TI_EN = 0;
     

    SPI0RX_AUTO_CLR =1;
    SPI0TX_AUTO_CLR =1;

#endif

    DBG_SPI("\n SPI0CON1=%02x ",SPI0CON);
    DBG_SPI("\n SPI0CON2=%02x ",SPI0CON2);
    DBG_SPI("\n SPI0CON3=%02x ",SPI0CON3);
    DBG_SPI("\n SPI0CON4=%02x ",SPI0CON4);

                    
#if _TEST_SPI0_DMA_EN
    SPI0_DMA_Init();
#endif    
    
}


/*******************************************************************************
*   Name: DrvRomRegWR
*  Brief:

    1.idx: 0-->65535
    2.调用时先写再加

*  Input:
* Output:
* Return:
*******************************************************************************/
UINT8 DrvRomRegWR(UINT16 idx,UINT8 ucData)
{
    UINT8 ch = BOOT_CODE_FLAG;
    volatile UINT8 dma_config;
    
    switch (g_ucHostCmdNow)
    {
        // 55 
        case HCMD_START1:
        {
            /* 收到正确命令，说明主机有向rom发请求 */
            if(g_ucSysState != S_MCU_WAIT)
            {
                RST_STA = RST_VALUE_UPGRADE;
                DelayUs_EX(100);
                SFTRST  = 0xFF;
            }
            break;
        }

        // 90 xx xx xx
        case HCMD_ID:
        {
            if ((idx >= 3)&&(idx < 5))
            {
                g_ucAppEcc = 0x00;
                ch = g_ucChipId[idx-3];
            }

            break;
        }

        //AE AH AM AL LH LL D0 D1 ... Dn
        case HCMD_DATA_WN:            
        case HCMD_DATA_W:
        {            
            switch (idx)
            {
                case 0:
                {
                    if(g_ucSysState != S_MCU_WAIT)
                    {
                        g_ucHostCmdNow = HCMD_NOF;
                    }
                    break;
                }
             
                case 1:
                case 2:
                case 3:
                {
                    pAppAddr[idx] = ucData;
                    break;
                }
              
                case 4:
                {
                    g_ucAppLen = ((UINT16)ucData<<8);
                    break;
                }
                case 5:
                {
                    g_ucAppLen += ucData;

#if _TEST_SPI0_DMA_EN
                    if(Bus_I2C_SPI0)//if(BUS_SEL)
                    {
                        if(g_ucHostCmdNow==HCMD_DATA_WN)//0xad指令开启CRC,0xae指令禁止CRC
                        {
                            dma_config=(DMA_TIMEOUT_DIS|DMA_TRANS_ERR_DIS|DMA_CRC_EN|DMA_WD|
                                        DMA_CLR_RI_EN|DMA_CLR_TI_EN|DMA_EN);
                        }
                        else
                        {
                            dma_config=(DMA_TIMEOUT_DIS|DMA_TRANS_ERR_DIS|DMA_CRC_DIS|DMA_WD|
                                        DMA_CLR_RI_EN|DMA_CLR_TI_EN|DMA_EN);
                        }
                        SPI0_DMA_SetAddr(PRAM_PTR8(g_usAppStartAddr),g_ucAppLen,DMA_MEM_PRAM);
                        SPI0_DMA_Enable(0xff,dma_config);
                        SPI0_DMA_ClrStatus(&g_ucAppEcc);                    
                    }
#endif         

                    break;
                }
                // 6-->0xffff
                default:
                {
                    
#if _TEST_SPI0_DMA_EN
                    if(!Bus_I2C_SPI0)//if(!BUS_SEL)    
#endif
                    {
                        PRAM_ADDR8(g_usAppStartAddr + idx - 6) = ucData;
                        g_ucAppEcc ^=ucData;
                    }
                    break;
                }
            }

            break;
        }

        //85 AH AM AL  --> set read address
        case HCMD_DATA_R:
        {
            
            if((idx>0)&&(idx<4))
            {
                pAppAddr[idx] = ucData;
            }
            if(idx >= 3)//3-->0xffff
            {

#if _TEST_SPI0_DMA_EN
                g_ucAppLen=0XFFFF;

                if(Bus_I2C_SPI0)//if(BUS_SEL)
                { 
                    dma_config=(DMA_TIMEOUT_DIS|DMA_TRANS_ERR_DIS|DMA_CRC_DIS|DMA_RD|
                                    DMA_CLR_RI_EN|DMA_CLR_TI_EN|DMA_EN);
                    SPI0_DMA_SetAddr(PRAM_PTR8(g_usAppStartAddr),g_ucAppLen,DMA_MEM_PRAM);
                    SPI0_DMA_Enable(0xff,dma_config);
                    SPI0_DMA_ClrStatus(&g_ucAppEcc);                      
                }
                else
#endif//_TEST_SPI0_DMA_EN                     
                
                ch = PRAM_ADDR8(g_usAppStartAddr + idx -3);   
            }
            break;    

        }
#if  1       
        //86 AH AM AL LH LL --> set read address read len
        case HCMD_DATA_RN:
        {
          
            if((idx>0)&&(idx<4))
            {
                pAppAddr[idx] = ucData; 
                g_ucAppLen =0;
            }
            if((idx>3)&&(idx<6))
            {
                g_ucAppLen<<=8;
                g_ucAppLen|=ucData;                

            }
           
            if(idx >= 5)
            {
#if _TEST_SPI0_DMA_EN
                if(Bus_I2C_SPI0)//if(BUS_SEL)
                {
                    dma_config=(DMA_TIMEOUT_DIS|DMA_TRANS_ERR_DIS|DMA_CRC_EN|DMA_RD|
                                DMA_CLR_RI_EN|DMA_CLR_TI_EN|DMA_EN);
                    SPI0_DMA_SetAddr(PRAM_PTR8(g_usAppStartAddr),g_ucAppLen,DMA_MEM_PRAM);
                    SPI0_DMA_Enable(0xff,dma_config);
                    SPI0_DMA_ClrStatus(&g_ucAppEcc); 
                }
                else
#endif            
                ch = PRAM_ADDR8(g_usAppStartAddr + idx -5);                
                
            }
            break;    

        }
#endif
        //07
        //08
        case HCMD_APP_START:
        case HCMD_RST:
        {
            SFTRST  = 0xFF;
            break;
        }
    #if 0
        //08
        case HCMD_APP_START:
        {
            DrvClearState();
            REMAP = 1;
            break;
        }
    #endif
        
        case HCMD_ECC:
        {
            ch = g_ucAppEcc;
            break;
        }
        case HCMD_BOOT_STATE:
        {
            ch = g_ucSysState;
            
            break;
        }
        case HCMD_VENDOR_ID:
        {
            ch = g_ucFwCfgBuf[FW_CFG_VENDOR_OFFSET];
            break;
        }
#if 1        
        case HCMD_GET_STA:
        {
            if((idx>0)&&(idx<4))
            {
                pAppAddr[idx] = ucData;                 
            }
            /*if((idx==4))
            {                
                g_ucAppLen=ucData;                

            }*/
            if(idx >= 5)
            {
                ch = DRAM_ADDR8(g_usAppStartAddr + idx -5);  
            }
            break;    
        } 
#endif        
       
        //01 --- touch point
        //case HCMD_TOUCH:
        default:
        {
            break;
        }
    }
 
    return ch;
}


/******************************************************************************
*
*   Name: SPI0_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
void SPI0_IRQHandler(void) interrupt 11
{
    UINT8 ch = 0;  

 
    if (SPI0RI)
    {    
        ch = SPI0BUF;  

        if(SPI0_START)
        {        
            SPI0_START_CLR=1;
            
            g_ucHostIdx =0;
            /* 接收 Host 写的第一个数据，保存为cmd */
            g_ucHostCmdNow = ch;
        }


        // idx 先调用，后++
        SPI0BUF=DrvRomRegWR(g_ucHostIdx,ch);        
        g_ucHostIdx++;
        
    }   

    SPI0CON5 =0xff;

}



#endif


