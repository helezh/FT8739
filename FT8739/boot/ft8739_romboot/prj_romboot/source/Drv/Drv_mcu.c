/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Drv_mcu.c
*
*    Author: tangsujun
*
*   Created: 2016-12-23
*
*  Abstract:
*
* P07   P04
* 0 1:  I2C--OTP
* 1 0:  I2C--0x72
* 1 1:  I2C--0x70
*
* Reference:
*
* Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/


BOOLEAN g_bHostUpCmd     ;   //Host发升级命令
BOOLEAN g_bLcdReloadCheck ;

UINT8 g_ucAppEcc;
UINT8 g_ucSysState  = S_MCU_INIT; // 系统状态
UINT8 g_ucSysClk    = 0;// sysclk
UINT8 g_ucI2cAddr   = I2C_SLAVE_ADDR;
UINT8 g_ucSPI1_Clk  = 0;//2-8分频,1-6分频,0-4分频
UINT8 g_ucSpi_mode  = 0;
UINT8 g_ucSpi0_phase  = 0X02;

UINT8 g_ucReloadState   = 0;
UINT8 XRAM g_ucFwCfgBuf[32];            // FW配置信息
UINT8 XRAM g_ucFwCfgBkupBuf[32];        // FW配置信息备份
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: DrvIOInit
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvIOInit(void)
{

    //IO init
    P0BUF = 0xFF;   
    //IO结构
    P0SEL = 0xFF;
    P1SEL = 0xFF;

    //IO功能配置
    P0MOD = BITn(1) + BITn(0);
    P1MOD = 0x0F;   // WB模式

    //方向P06为输出口
    P0DIR = BITn(6) + BITn(7);
    P1DIR = BITn(7) + BITn(5) + BITn(4);

    /* WB配置 */
    Flash_WP    = 0;  // P17 = 0
    Flash_HOLD  = 1;  // P14 = 1

}

/*******************************************************************************
*   Name: DrvHostInterfaceInit
*  Brief:
*    1.先根据pad设置默认slave
*    2.如果带flash的，更新flash里的slave地址
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvHostInterfaceInit(void)
{
    
    I2CCON = 0;

    /* 设置设备地址 */
    I2CADDR = I2C_SLAVE_ADDR&0xFE;

    //I2C停止中断
    ISP_STOP_EI = 1;
    ISP_STOP_IF = 0;

    /* ISP STOP优先级设置 */
    ISP_STOP_IPH = 1;
    ISP_STOP_IPL = 0;
    /* I2C优先级设置 */
    I2C_IPH = 1;
    I2C_IPL = 1;
    /* 开启I2C中断 */
    ET2 = 1;

}

/*******************************************************************************
*   Name: DrvClearState
*  Brief: remap之前清标志,关中断
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvClearState(void)
{
    TMOD = 0;
    TCON = 0;
    DelayUs_EX(20);
    
    PRAM_ADDR8(LCD_RELOAD_OFFSET)   = g_ucReloadState;
    PRAM_ADDR8(LCD_RELOAD_OFFSET+1) = ~g_ucReloadState;
    
    /*I2C相关标志清零*/
    I2CCON = 0;
    I2CSTP = 0;

    /*SPI0相关标志清零*/
    SPI0CON5 =0xff;  
    SPI0_DMA_Enable(pSpi0_DMA2,0,0);
    SPI0_DMA_Enable(pSpi0_DMA1,0,0);
    
    IEN0 =0;
    IEN1 =0;
    AIE  =0; 
    XBUSCKEN = 0;

}

/******************************************************************************
*
*   Name: DelayUs
*  Brief:
*  Input:
* Output: None
* Return: None
******************************************************************************/
void DelayUs_EX(UINT16 ucDlyCnt)
{
    UINT8 temp;

    while (ucDlyCnt--)
    {
        temp = 4;
        while (temp--)
        {
           _nop_();//__asm__ volatile ("nop");
        }
    }
}

/******************************************************************************
*   Name: DrvFlashCfgValid
*  Brief: 检查Flash数据的有效性
*  Input:
* Output:
* Return:
******************************************************************************/
UINT8 DrvFlashCfgValid(UINT8 *pbuf, UINT8 *pCfg)
{
    if ((pbuf[0] + pbuf[1]) == 0xFF)
    {
        *pCfg =pbuf[0];
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************
*
*   Name: DrvFlashCfg
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
void DrvFlashCfg(UINT8 ucOffset, UINT8 *pCfg)
{
    UINT8 ucFlashDataValid;

    /* 检查master i2c addr有效性 */
    ucFlashDataValid = DrvFlashCfgValid(&g_ucFwCfgBuf[ucOffset],pCfg);
    
    if (ucFlashDataValid==0)
    {
        DrvFlashCfgValid(&g_ucFwCfgBkupBuf[ucOffset],pCfg);
    }
}

/******************************************************************************
*
*   Name: DrvFwConfigInit
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
void DrvFwConfigInit(void)
{
    UINT8 temp;
    

        if (g_ucFlashMode)
        {
            /* 读FW配置信息中master i2c addr */
            SPIFlash_FastRead(FW_CFG_START_FLASH_ADDR, &g_ucFwCfgBuf[FW_CFG_I2C_OFFSET],FW_CFG_INFO_SIZE);

            /* 读FW配置信息备份中master i2c addr */
            SPIFlash_FastRead(FW_CFG_BKUP_START_FLASH_ADDR,&g_ucFwCfgBkupBuf[FW_CFG_I2C_OFFSET],FW_CFG_INFO_SIZE);            
        }
        else
        {
        #if _OTP_SLAVE_EN
            /* 读LCD OTP 中FW CONFIG信息 */
            Read_Lcd_OTP((UINT16 *)g_ucFwCfgBuf,FW_CFG_INFO_SIZE);
            
        #endif
        }

        /* 检查Sys Clk 有效性 */
        DrvFlashCfg(FW_CFG_SYS_CLK_OFFSET,&g_ucSysClk); 
        if(g_ucSysClk==0x24)
        {
            CGUCON4 =1;//24M
        }
        else
        {
            CGUCON4 =0;//48M
        }
        DBG_FLOW("\n CGUCON4 =%02x ",CGUCON4);
        
        /* 检查master i2c addr有效性 */
        DrvFlashCfg(FW_CFG_I2C_OFFSET,&g_ucI2cAddr);
        /* 设置设备地址 */
        if((g_ucI2cAddr>=0x02)&&(g_ucI2cAddr<=0xFE))
        I2CADDR = g_ucI2cAddr&0xFE;
        
            
        /* 检查Spi1 Clk 有效性 */
        DrvFlashCfg(FW_CFG_SPI_CLK_OFFSET,&g_ucSPI1_Clk);         
        SPI1CON &= 0xcf;
        SPI1CON |= (g_ucSPI1_Clk&0x03)<<4;//4 6 8 12分频
        DBG_FLOW("\n g_ucSPI1_Clk =%02x ",g_ucSPI1_Clk);

        
        /* 检查Spi1 MODE 有效性 */
        DrvFlashCfg(FW_CFG_SPI_IOMODE_OFFSET,&g_ucSpi_mode); 
        DBG_FLOW("\n g_ucSpi_mode =%02x ",g_ucSpi_mode);

        /* 检查Spi0 PHASE 有效性 */
        DrvFlashCfg(FW_CFG_SPI0_PHASE_OFFSET,&g_ucSpi0_phase); 
        DBG_FLOW("\n g_ucSpi0_phase =%02x ",g_ucSpi0_phase);
        SPI0_PHASE=g_ucSpi0_phase&0X02;
        
        /* 检查LcdReloadCnt有效性 */
        DrvFlashCfg(FW_CFG_LCD_CNT_OFFSET,&temp); 
        if(temp==0x5a)
        {
            LcdReloadCnt=3;
        }
        DBG_FLOW("\n LcdReloadCnt =%02x ",LcdReloadCnt);    
        
   
}


