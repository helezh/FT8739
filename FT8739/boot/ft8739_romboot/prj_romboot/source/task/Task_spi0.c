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





 
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

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
    
    HCMD_GET_REG_SPI0  = 0xF0,
    HCMD_SET_REG_SPI0  = 0xF1,
    HCMD_GET_STA       = 0xF2,
} ENUM_RomCmd;

/*************************************************************/
typedef union
{
    UINT8 reg;
    struct
    {
        UINT8 cmd_len       :4;        
        UINT8 time_out_en   :1;
        UINT8 crc_en        :1;
        UINT8 data_rw       :1;
        UINT8 pack_type     :1;

    }bits;
}UNION_INFO;

/*SPI0_CMD_HEAD*/
typedef struct
{
    UINT8       head;
    UNION_INFO  info;
    UINT8       cmd;
    UINT8       buf[15];
    
}ST_Spi0Cmdhead;
/*SPI0_status*/
typedef union
{
    UINT8 reg;
    struct
    {
        UINT8 crc_err   :1;
        UINT8 revbit0   :1;
        UINT8 err       :1;
        UINT8 revbit1   :1;
        
        UINT8 revbit3   :3;
        UINT8 busy      :1;
                
        
    }bits;
}UNION_SPI0_STA;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/



/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
volatile ST_Spi0Cmdhead  far * pCmdhead;
volatile UINT16 IRAM dma_config=0,dma2_config;
volatile UINT16 IRAM dma_rx_mem_sel;

volatile UINT8 far * IRAM g_ucpSpi0RxBuf;
volatile UINT8 far * IRAM g_ucpSpi0TxBuf;
volatile UINT8 far * IRAM ptrdata;

volatile UINT8 IRAM g_ucRxbufSel=0;

UINT8 IRAM data_mode=0;
UINT8 IRAM crc_info =0;
volatile UNION_SPI0_STA IRAM UNION_SpiSta;
UINT16 IRAM g_ulSpi0cnt=0;
//volatile UINT8 IRAM g_ucRxDone=0;
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

    
    SPI0CKEN = 1;
    SPI0CON5 =0xff;
    SPI0CON2 =0xc9;
    SPI0CON3 =0X60;
    SPI0CON4 =0X00;

    SPI0_PHASE =1;
    
    //SPI0_EDGE_SEL =1;
    
    /* IO配置: P05-->P02  MOSI MISO CLK CS */
    P0MOD |= BITn(5) + BITn(4)+BITn(3) + BITn(2);
    P0SEL |= BITn(5) + BITn(4)+BITn(3) + BITn(2);
    
    P0DIR |= BITn(4)+BITn(3) + BITn(2);
    P0DIR &= ~ BITn(5);


    //interruption priority
    SPI0_IPH = 1;
    SPI0_IPL = 1;       
    
    //AIE 
    SPI0_EI     = 0;     
    ISP_STOP_EI = 1;


#if 0


    //中断标志使能
    SPI0RI_EN = 0;
    SPI0TI_EN = 1;
    SPI0_STOP_EN=1; 

    SPI0RX_AUTO_CLR =1;
    SPI0TX_AUTO_CLR =1;
    
    SPI0_CS_DEGLITCH_EN =1;
    SPI0_PHASE =1;
#endif

    DBG_SPI("\n SPI0CON1=%02x ",SPI0CON);
    DBG_SPI("\n SPI0CON2=%02x ",SPI0CON2);
    DBG_SPI("\n SPI0CON3=%02x ",SPI0CON3);
    DBG_SPI("\n SPI0CON4=%02x ",SPI0CON4);

                    
#if _TEST_SPI0_DMA_EN
    #if 0
    g_ucRxbufSel  =0;
    dma_rx_mem_sel   = DMA_MEM_ARAM;
    g_ucpSpi0RxBuf=ARAM_START_ADDRESS; 
    #else    
    g_ucRxbufSel  =1;
    dma_rx_mem_sel   = DMA_MEM_DRAM8K;
    g_ucpSpi0RxBuf   = DRAM8K_START_ADDRESS; 
    #endif
    g_ucpSpi0RxBuf[0]=0;
    g_ucpSpi0RxBuf[1]=0;
    g_ucpSpi0RxBuf[2]=0;

    g_ucpSpi0TxBuf=DRAM8K_DMA_TX_ADDRESS;

    pCmdhead    =g_ucpSpi0RxBuf;
    
    SPI0_DMA_Init();

    

#endif    
    
}
/******************************************************************************
*
*   Name: SPI0_Get_Byte_Num
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
******************************************************************************/
#if 1
UINT32 SPI0_Get_Byte_Num(void)
{

    UINT16 byte_num_h,byte_num_m,byte_num_l;
    UINT32 byte_num;
    
    SPI0CON4 =0x00<<6;
    byte_num_h  =SPI0CON4&0x3f;
    SPI0CON4 =0x01<<6;
    byte_num_m  =SPI0CON4&0x3f;
    SPI0CON4 =0x02<<6;
    byte_num_l  =SPI0CON4&0x3f;

    byte_num    =(byte_num_h<<12)|(byte_num_m<<6)|(byte_num_l);
    return  byte_num;
    
}
#else
UINT16 SPI0_Get_Byte_Num(void)
{
    UINT16 byte_num_m,byte_num_l;
    UINT32 byte_num;
    

    SPI0CON4 =0x01<<6;
    byte_num_m  =SPI0CON4&0x3f;
    SPI0CON4 =0x02<<6;
    byte_num_l  =SPI0CON4&0x3f;
 
    byte_num    =(byte_num_m<<6)|(byte_num_l);

    return  byte_num;    
}
#endif
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
            if(g_ucSysState == S_MCU_WAIT)
            {
                
                g_ucAppEcc = 0x00;
                #if _TEST_SPI0_DMA_EN       
                if(Bus_I2C_SPI0)//if(BUS_SEL)
                {
                    if (idx == 3)
                    {
                        ptrdata =DRAM_PTR8(g_ucChipId);
                        g_ucAppLen=2;
                    }
                    
                }
                else
                #endif            
                {
                    if ((idx == 3)||(idx ==4))
                    {
                        ch = g_ucChipId[idx-3];
                    }
                   
                }
                
            }
            break;
        }

        //AE AH AM AL LH LL D0 D1 ... Dn
     //   case HCMD_DATA_WN:            
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
                        ptrdata =PRAM_PTR8(g_usAppStartAddr);                        
                    }
                    #endif         

                    break;
                }
                // 6-->0xffff
                default:
                {
                    
                    #if _TEST_SPI0_DMA_EN
                    if(Bus_I2C_SPI0==0)//if(!BUS_SEL)    
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
        // FW DEBUG USE
        case HCMD_GET_STA:             
        //85 AH AM AL  --> set read address
        case HCMD_DATA_R:
        {
            
            if((idx>0)&&(idx<4))
            {
                pAppAddr[idx] = ucData;
            }
           

            #if _TEST_SPI0_DMA_EN            
            if(Bus_I2C_SPI0)//if(BUS_SEL)
            { 
                if(idx == 3)
                {
                    if(g_ucHostCmdNow == HCMD_GET_STA)
                    {
                        ptrdata =DRAM_PTR8(g_usAppStartAddr);
                    }
                    else
                    {
                        ptrdata =PRAM_PTR8(g_usAppStartAddr);
                    }
                    g_ucAppLen=0X100;//MAX 4095

                }
                else if(idx==4)
                {                    
                    g_ucAppLen=ucData;
                }
                else if(idx==5)
                {
                    g_ucAppLen<<=8;
                    g_ucAppLen|=ucData;
                }
            }
            else
            #endif//_TEST_SPI0_DMA_EN                     
            {
                if(idx >= 3)//3-->0x400
                {
                    ch = PRAM_ADDR8(g_usAppStartAddr + idx -3);  
                }
            }
            break;    

        }        
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
 
        case HCMD_GET_REG_SPI0:
        {
            ch = SPI0CON2 & BIT8(5);// ch = SPI0_EDGE_SEL;
            break;
        }
        
        case HCMD_SET_REG_SPI0:
        {   
            if(idx==1)
            {
                SPI0_EDGE_SEL=ucData & BIT8(5);
            }
            break;
        }
      
       
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

    SPI0CON5 =0xf3;//不清 CS 及DMA flag 
    SPI0BUF =UNION_SpiSta.reg; 
//    INTOUT ^=1;
//    INTOUT ^=1;
}
/******************************************************************************
*   Name: SPI0_DMA_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
#if _TEST_SPI0_DMA_EN
void SPI0_DMA_IRQHandler(void)
{
 
    UINT16 i,len;
    volatile UINT8 far *ptr8_src;
    volatile UINT8 far *ptr8_dest;
    volatile UINT16 far *ptr16_src;
    volatile UINT16 far *ptr16_dest;
    
 
    g_ulSpi0cnt=SPI0_Get_Byte_Num();

    if(g_ulSpi0cnt>=2)
    {
        if((pCmdhead->head==0xc0)||(pCmdhead->head==0xc3))//命令包 or 数据包
        { 
                            
            UNION_SpiSta.reg=0x80;//UNION_SpiSta.bits.busy =1;          
            SPI0BUF =UNION_SpiSta.reg;
            //INTOUT ^=1;
            SPI0_DMA_SetAddr(pSpi0_DMA2,(UINT32)DRAM8K_DMA_TX_ADDRESS,1+DUMMY_LEN,DMA_MEM_DRAM8K);                
            SPI0_DMA_SetAddr(pSpi0_DMA1,(UINT32)g_ucpSpi0RxBuf,4096,dma_rx_mem_sel);    
            
            
            //INTOUT ^=1;
         }
        
         if(pCmdhead->head==0xc0)//命令包
         {
                         
            data_mode =pCmdhead->info.bits.data_rw;
            crc_info  =pCmdhead->info.bits.crc_en;
            if(crc_info)//if include CRC 
            {
                if(0 != pSpi0_DMA1->dma_crc)
                {
                    UNION_SpiSta.bits.crc_err=1;
                }
                 
            } 
            
            
            if(UNION_SpiSta.bits.crc_err==0)
            {  
                g_ucAppLen=1;
                ptr8_src = g_ucpSpi0RxBuf+2;
                g_ucHostCmdNow=*ptr8_src; 
                ptr8_dest = g_ucpSpi0TxBuf+DUMMY_LEN;
                len = pCmdhead->info.bits.cmd_len;
                for(i=0; i<len;i++)
                {
                    *ptr8_dest++= DrvRomRegWR(i,*ptr8_src++);
                }
                if(data_mode>0)//读操作，提前准备数据
                {
                    ptr16_dest = g_ucpSpi0TxBuf+DUMMY_LEN;                        
                    ptr16_src  = ptrdata;
                    if((g_ucAppLen>1)&&(g_ucAppLen<=4094))
                    {
                        len = (g_ucAppLen+1)>>1;
                   //     INTOUT ^=1;
                        for(i=0; i<len;i++)
                        {  
                           *ptr16_dest++ = *ptr16_src++;
                           //DelayUs_EX(12);
                           
                        }
                   //     INTOUT ^=1;
                    }
                    
                    SPI0_DMA_SetAddr(pSpi0_DMA2,(UINT32)DRAM8K_DMA_TX_ADDRESS,g_ucAppLen+DUMMY_LEN,DMA_MEM_DRAM8K);
                }
                
                
            } 
       
        
        }
        else if(pCmdhead->head==0xc3)//数据包
        {             
            
            if(data_mode==0)
            {          
                if(crc_info)//if include CRC 
                {
                    if(0 != pSpi0_DMA1->dma_crc)
                    {
                        UNION_SpiSta.bits.crc_err=1;
                    }     
                }
                
                    
                if(UNION_SpiSta.bits.crc_err==0)
                {
                    if(g_ucHostCmdNow==HCMD_DATA_W)
                    {
                        ptr16_dest =ptrdata;
                        ptr16_src= g_ucpSpi0RxBuf+DUMMY_LEN;                        
                        len  = (g_ucAppLen<=4094)?g_ucAppLen:0;
                        len =(len+1)>>1;
                        
                    //    INTOUT ^=1;
                        for(i=0; i<len;i++)
                        {                            
                            *ptr16_dest++ = *ptr16_src++;
                        } 
                    //    INTOUT ^=1;
                    } 
                }

            }
            else
            {
                data_mode=0;
                if(pSpi0_DMA2->dma_srcr&(BIT_DMA_NOT_FINISH_FLAG|BIT_DMA_SCK_OVERTRANS_FLAG))
                {
                    UNION_SpiSta.bits.err=1;
                }                
            }
            g_ucHostCmdNow=0;
            

         
        }
        else
        {
            UNION_SpiSta.bits.err=1;
        }
        
    }
    else
    {
       
        if(pCmdhead->head!=0x05)//状态包
        {                    
           UNION_SpiSta.bits.err=1;
        }
             
    }
    
    g_ucpSpi0RxBuf[0]=0;
    g_ucpSpi0RxBuf[1]=0;
    g_ucpSpi0RxBuf[2]=0; 
    UNION_SpiSta.bits.busy =0; 
    g_ucpSpi0TxBuf[0]=UNION_SpiSta.reg;   
    SPI0BUF          =UNION_SpiSta.reg;
    SPI0_DMA_Enable(pSpi0_DMA2,0xff,DMA_TX_CONFIG);
    SPI0_DMA_Enable(pSpi0_DMA1,0xff,DMA_RX_CONFIG); 
    
   
    INTOUT = 0;
    
}
#endif





#endif


