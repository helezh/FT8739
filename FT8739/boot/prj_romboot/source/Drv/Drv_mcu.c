/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
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
/* XSI2 reg start addr */
#define XSI2_REG_BASE_ADDR    0x9C00
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/


BOOLEAN g_bHostUpCmd     ;   //Host����������
BOOLEAN g_bLcdReloadCheck ;

UINT8 g_ucAppEcc;
UINT8 g_ucSysState  = S_MCU_INIT; // ϵͳ״̬
UINT8 g_ucSysClk    = 1;// sysclk
UINT8 g_ucI2cAddr   = I2C_SLAVE_ADDR;
UINT8 g_ucSPI1_Clk  = 0;
UINT8 g_ucSpi_mode  = 0;


UINT8 g_ucReloadState   = 0;
UINT8 XRAM g_ucFwCfgBuf[32];            // FW������Ϣ
UINT8 XRAM g_ucFwCfgBkupBuf[32];        // FW������Ϣ����
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
#if 1
    //IO init
    P0BUF = 0xFF;   
    //IO�ṹ
    P0SEL = 0xFF;
    P1SEL = 0xFF;

    //IO��������
    P0MOD = BITn(1) + BITn(0);
    P1MOD = 0x0F;   // WBģʽ

    //����P06Ϊ�����
    P0DIR = BITn(6) + BITn(7);
    P1DIR = BITn(7) + BITn(5) + BITn(4);

    /* WB���� */
    Flash_WP    = 0;  // P17 = 0
    Flash_HOLD  = 1;  // P14 = 1
#else
    POR_STA = 0x00;
    RST_STA = 0x66;

    SYSCKEN = 1;
    P0SEL = 0xff;
    P1SEL = 0xff;
    
    P1MOD = 0x00;
    
    P0MOD = BITn(1) + BITn(0);

    P0DIR = 0xff;
    P1DIR = 0xff;

#endif
}

/*******************************************************************************
*   Name: DrvHostInterfaceInit
*  Brief:
*    1.�ȸ���pad����Ĭ��slave
*    2.�����flash�ģ�����flash���slave��ַ
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvHostInterfaceInit(void)
{
    UINT8 ucSlvAddr;
    UINT8 ucFlashAdrValid = 0;

    ucSlvAddr = I2C_SLAVE_ADDR;

    I2CBUF = 0;
    //I2CRI  = 0;
    //I2CTI  = 0;
    I2CCON = 0;

    /* �����豸��ַ */
    I2CADDR = ucSlvAddr&0xFE;

    //I2Cֹͣ�ж�
    I2C_STOP_EI = 1;
    I2C_STOP_IF = 0;

    /* I2C���ȼ����� */
    I2C_IPH = 1;
    I2C_IPL = 1;
    /* ����I2C�ж� */
    ET2 = 1;

}

/*******************************************************************************
*   Name: DrvClearState
*  Brief: remap֮ǰ���־,���ж�
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
    
    /*I2C��ر�־����*/
    //I2CRI  = 0;
    //I2CTI  = 0;
    I2CCON = 0;
    I2CSTP = 0;
    I2CBUF = 0;

    /*SPI0��ر�־����*/
    SPI0CON5 =0xff;    
    
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
*  Brief: ���Flash���ݵ���Ч��
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

    /* ���master i2c addr��Ч�� */
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
 
    

        if (g_ucFlashMode)
        {
            /* ��FW������Ϣ��master i2c addr */
            SPIFlash_FastRead(FW_CFG_START_FLASH_ADDR, &g_ucFwCfgBuf[FW_CFG_I2C_OFFSET],FW_CFG_INFO_SIZE);

            /* ��FW������Ϣ������master i2c addr */
            SPIFlash_FastRead(FW_CFG_BKUP_START_FLASH_ADDR,&g_ucFwCfgBkupBuf[FW_CFG_I2C_OFFSET],FW_CFG_INFO_SIZE);            
        }
        else
        {
        #if _OTP_SLAVE_EN
            /* ��LCD OTP ��FW CONFIG��Ϣ */
            Read_Lcd_OTP((UINT16 *)g_ucFwCfgBuf,FW_CFG_INFO_SIZE);
            
        #endif
        }

        /* ���Sys Clk ��Ч�� */
        DrvFlashCfg(FW_CFG_SYS_CLK_OFFSET,&g_ucSysClk); 
        if(g_ucSysClk==0)
        CGUCON4 =0;
        DBG_FLOW("\n CGUCON4 =%02x ",CGUCON4);
        
        /* ���master i2c addr��Ч�� */
        DrvFlashCfg(FW_CFG_I2C_OFFSET,&g_ucI2cAddr);
        /* �����豸��ַ */
        if((g_ucI2cAddr>=0x10)&&(g_ucI2cAddr<=0x7a))
        I2CADDR = g_ucI2cAddr&0xFE;
        
            
        /* ���Spi1 Clk ��Ч�� */
        DrvFlashCfg(FW_CFG_SPI_CLK_OFFSET,&g_ucSPI1_Clk);         
        SPI1CON &= 0xcf;
        SPI1CON |= (g_ucSPI1_Clk&0x03)<<4;//4 6 8 12��Ƶ
        DBG_FLOW("\n g_ucSPI1_Clk =%02x ",g_ucSPI1_Clk);

        
        /* ���Spi1 MODE ��Ч�� */
        DrvFlashCfg(FW_CFG_SPI_IOMODE_OFFSET,&g_ucSpi_mode); 
        DBG_FLOW("\n g_ucSpi_mode =%02x ",g_ucSpi_mode);

        
   
}


