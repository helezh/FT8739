/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: task_hcomm.c
*
*    Author: tangsujun
*
*   Created: 2016-12-22
*
*  Abstract: 主机通讯模块
*
* Reference:
*
* Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "CfgGlobal.h"
#include "Task_hcomm.h"



/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

/*
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
    HCMD_DATA_W       = 0xAE,
    HCMD_ECC          = 0xCC,
    HCMD_BOOT_STATE   = 0xD0,
    HCMD_ROM_VERSION  = 0xDB,

    HCMD_RST_STA       = 0xE0,
    HCMD_XRST_STA      = 0xE1,
    HCMD_Upgrade_Flg   = 0xE2,
    HCMD_POR_CLR       = 0xE3,
    HCMD_LCDReLoad_STA = 0xE4,
} ENUM_RomCmd;*/

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

BOOLEAN g_bWriteFlag ;      // 写时，需要返回值给host标志
BOOLEAN hcomm_end_flag= TRUE;
UINT16 g_ucHostIdx  ;          // Host每次通讯RW的字节序号
UINT8 g_ucHostCmdNow;          // Host--发来的第一个字节，即命令头

volatile UINT32 g_usAppStartAddr ;//_at_ 0x60;//__attribute__((aligned (4)));     // 数据包开始地址

UINT8 *pAppAddr = (UINT8 *)&g_usAppStartAddr;
UINT16 g_ucAppLen  ;        // 接收数据包大小，这里只接收不处理

UINT8 g_ucChipId[2] = {CHIP_ID_H,CHIP_ID_L};
UINT8 XRAM g_ucDataBuf[16];             // 长命令缓冲区

#if  _TEST_I2C_EN 
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
#if 0//!_TEST_SPI0_EN
/*******************************************************************************
*   Name: DrvRomRegRead
*  Brief:
*    1.g_ucHostCmdNow 作为全局变量，不再传送，节省代码
*    2.idx: 0--->255
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT8 DrvRomRegRead(UINT16 idx)
{
    UINT8 ch = BOOT_CODE_FLAG;

    switch (g_ucHostCmdNow)
    {
        // xx xx (cmd = 0x90)
        case HCMD_ID:
        {

            if (idx < 2)
            {
                ch = g_ucChipId[idx];
            }
            
            break;
        }

        // xx (cmd = 0x85)
        case HCMD_DATA_R:
        {
           
          ch = PRAM_ADDR8(g_usAppStartAddr + idx);        
 
            break;
        }

        // xx (cmd = 0xCC)
        case HCMD_ECC:
        {
            ch = g_ucAppEcc;
            break;
        }

        // xx (cmd = 0xD0)
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
        default:  //HCMD_TOUCH
        {
            break;
        }
    }
    return ch;
}

/*******************************************************************************
*   Name: DrvRomRegWrite
*  Brief:

    1.idx: 0-->255
    2.调用时先写再加

*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvRomRegWrite(UINT16 idx,UINT8 ucData)
{
    UINT32 temp=0;
    g_bWriteFlag  = FALSE;

    switch (g_ucHostCmdNow)
    {
        // 55 AA
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
            if (idx < 4)
            {
                g_ucAppEcc = 0x00;
                g_ucDataBuf[idx] = ucData;
            }

            if (idx == 0)
            {
                g_bWriteFlag = TRUE;
            }
            break;
        }

        //AE AH AM AL LH LL D0 D1 ... Dn
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
                    //g_ucAppLen = ((UINT16)ucData<<8);
                    break;
                }
                case 5:
                {
                    //g_ucAppLen += ucData;
                    break;
                }
                // 6-->255
                default:
                {
                 //   g_ucAppEcc ^= ucData;
                    PRAM_ADDR8(g_usAppStartAddr + idx - 6) = ucData;
                    break;
                }
            }

            break;
        }

        //85 AH AM AL  --> set read address
        case HCMD_DATA_R:
        {
            switch (idx)
            {           
                case 3:
                    g_bWriteFlag = TRUE;
                case 1:
                case 2:
                {
                    pAppAddr[idx] = ucData;
                    break;
                }
                case 0:
                default:
                {
                    break;
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
        //01 --- touch point
        case HCMD_TOUCH:
        case HCMD_ECC:
        case HCMD_BOOT_STATE:
        case HCMD_VENDOR_ID:
        {
            g_bWriteFlag = TRUE;
            break;
        }

        default:
        {
            break;
        }
    }
}

/*******************************************************************************
*   Name: I2C_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2C_IRQHandler(void) interrupt 5
{
    UINT8 ch = 0;
    //P0_7 =0;
    if (RIFLAG)
    {
        RIFLAG = 0;

        ch = DATABUFF;        

        /* 接收 Host 写的第一个数据，保存为cmd */
        if (g_ucHostIdx ==  0)
        {
            g_ucHostCmdNow = ch;
        }

        // idx 先调用，后++
        DrvRomRegWrite(g_ucHostIdx,ch);
        g_ucHostIdx++;

        if (g_bWriteFlag)
        {
            DATABUFF = DrvRomRegRead(0x00);
        }
    }

    //--------------------------------------------------------------------------
    //每一帧读的第一个数据，总是提前准备，因此中断来后的index是从1开始的
    if (TIFLAG)
    {
        TIFLAG = 0;
        g_ucHostIdx++;
        DATABUFF = DrvRomRegRead(g_ucHostIdx); //place next byte
    }
    //P0_7 =1;
}

/*******************************************************************************
*   Name: I2CStop_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2CStop_IRQHandler(void) interrupt 8
{
    I2CSTP = 0;
    g_ucHostIdx = 0;
}





#else




/*******************************************************************************
*   Name: DrvRomRegWR
*  Brief:

    1.idx: 0-->65535
    2.调用时先写再加

*  Input:
* Output:
* Return:
*******************************************************************************/
#if 0//!_TEST_SPI0_EN
UINT8 DrvRomRegWR(UINT16 idx,UINT8 ucData)
{
    
    UINT8 ch = BOOT_CODE_FLAG;
    
    switch (g_ucHostCmdNow)
    {
        // 55 AA
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

            if (idx == 0)
            {
                //g_ucAppEcc = 0x00;
                //g_bWriteFlag = TRUE;
            }
            break;
        }

        //AE AH AM AL LH LL D0 D1 ... Dn
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
                    break;
                }
                // 6-->255
                default:
                {
                 //   g_ucAppEcc ^= ucData;
                    PRAM_ADDR8(g_usAppStartAddr + idx - 6) = ucData;
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
            if(idx >= 3)
            {
                ch = PRAM_ADDR8(g_usAppStartAddr + idx -3); 
                
            }
            break;    

        }
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
                ch = PRAM_ADDR8(g_usAppStartAddr + idx -5); 
                
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
        //01 --- touch point
        case HCMD_TOUCH:
        default:
        {
            break;
        }
    }
    
    return ch;
}
#endif
/*******************************************************************************
*   Name: I2C_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2C_IRQHandler(void) interrupt 5
{
    UINT8 ch = 0;
    //GPIO3   =INT_EN;
    if (RIFLAG)
    {
        RIFLAG = 0;

        ch = DATABUFF; 
        /* 接收 Host 写的第一个数据，保存为cmd */
        if(hcomm_end_flag)
        {
            hcomm_end_flag=FALSE;
            g_ucHostIdx=0;
            g_ucHostCmdNow = ch;
        }

        // idx 先调用，后++
        DATABUFF=DrvRomRegWR(g_ucHostIdx,ch);         
    }

    //--------------------------------------------------------------------------
    
    if (TIFLAG)
    {
        TIFLAG = 0;        
        DATABUFF = DrvRomRegWR(g_ucHostIdx,0); //place next byte        
    }
    g_ucHostIdx++;
    //GPIO3   =INT_DIS;
}

/*******************************************************************************
*   Name: I2CStop_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2CStop_IRQHandler(void) interrupt 8
{
    I2CSTP = 0;
    hcomm_end_flag=TRUE;
}


#endif














/*******************end***********************************/
#endif

