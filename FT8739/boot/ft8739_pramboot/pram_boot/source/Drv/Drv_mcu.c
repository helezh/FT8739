/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Drv_mcu.c
*
*    Author: tangsujun
*
*   Created: 2017-01-20
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "Drv_mcu.h"
#include "spi_flash.h"
#include "Task_hcomm.h"
#include "uart.h"
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
/* XSI2 reg start addr */
#define XSI2_REG_BASE_ADDR           0x9C00

#define LCD_REG_IC_VERSION_LEN       0x02
#define LCD_REG_IC_VERSION_ADDR      0xF4D8

#define DrvXsi2_LcdAccessEn()        (pXSI2Regs->lcd_regfile_ctrl |= 0x0200)
#define DrvXsi2_LcdAccessDis()       (pXSI2Regs->lcd_regfile_ctrl &=  0xFDFF)
#define DrvXsi2_LcdWriteEn()         (pXSI2Regs->lcd_regfile_ctrl &= 0xFEFF)
#define DrvXsi2_LcdReadEn()          (pXSI2Regs->lcd_regfile_ctrl |= 0x0100)
#define DrvXsi2_LcdReady()           ((pXSI2Regs->lcd_regfile_ctrl) & 0x0001)
#define DrvDma_CheckWriteFinish()    (pXSI2Regs->reload_dma_ctrl&0x0002)
#define DrvCheckLcdStandby()         ((pXSI2Regs->lcd_regfile_ctrl)&0x02)

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
// XSI
typedef struct
{
    UINT16 Wdata;             // (0x00<<1)
    UINT16 Rdata;             // (0x01<<1)
    UINT16 Clksel;            // (0x02<<1)
    UINT16 Stop;              // (0x03<<1)
    UINT16 Tx_int;            // (0x04<<1)
    UINT16 lcd_regfile_ctrl;  // (0x05<<1)
    UINT16 reload_dma_ctrl;   // (0x06<<1)
    UINT16 dma_flash_cmd;     // (0x07<<1)
    UINT16 dma_flash_addr1;   // (0x08<<1)
    UINT16 dma_flash_addr0;   // (0x09<<1)
    UINT16 dma_flash_length;  // (0x0A<<1)
} ST_XSIRegisters;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT8  g_ucAppEcc    = 0x00;       // Ĭ��0x00
UINT16 g_usTimerCnt  = 0;          // Timer0����
UINT8 g_ucICVersion  = 0;          // 0 : A , 1 : B

ST_XSIRegisters * XRAM pXSI2Regs = (volatile ST_XSIRegisters *)XSI2_REG_BASE_ADDR;
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:  DrvSysInit
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvSysInit(void)
{
    SYSCKEN = 1;
    CGUCON4 = MAIN_CLK;


#if 1
    //IO�ṹ
    P0SEL = 0xFF;
    P1SEL = 0xFF;

    //IO��������
    P0MOD = BITn(1) + BITn(0);
    P1MOD = 0x0F;   // WBģʽ

    //����P06Ϊ�����
    P0DIR = BITn(6) ;
    P1DIR = BITn(7) + BITn(5) + BITn(4);

    /* WB���� */
    Flash_WP    = 1;  // P17 = 0
    Flash_HOLD  = 1;  // P14 = 1
#else
    // IO�ṹ
    P0SEL = 0xFF;
    P1SEL = 0xFF;

    P0MOD = BITn(1) + BITn(0);
    P0DIR = BITn(7) + BITn(6);

    /* WinBond���� */
    
    P1MOD = 0x0F;                        // ����Winbond�ӿ�����P1�ڹ���
    P1DIR = BITn(7) + BITn(5) + BITn(4); // P1�ڷ�������
    Flash_WP   = 1;                      // �ر�Winbondд����
    Flash_HOLD = 1;                      // ��ֹHold
#endif
}

/*******************************************************************************
*   Name: DrvHostI2cInit
*  Brief:
* 1.�ȸ���pad����Ĭ��slave
* 2.�����flash�ģ�����flash���slave��ַ
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvHostI2cInit(void)
{
    UINT8 pBuf[2];
    UINT8 ucSlvAddr;

    ucSlvAddr = I2C_SLAVE_ADDR;

    I2CBUF = 0;
    I2CRI  = 0;
    I2CTI  = 0;

#if _FLASH_SLAVE_EN
    // ��flash�������slave��ַ
    SPIFlash_FastRead(FW_CFG_BKUP_START_FLASH_ADDR, pBuf,2);
    if ((pBuf[0] != 0xFF)&&(pBuf[0] != 0x00))
    {
        if (pBuf[0] + pBuf[1] == 0xFF)
        {
            ucSlvAddr = pBuf[0];
        }
    }
#endif
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
*   Name:  DelayUs
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DelayUs(UINT16 cnt)
{
    while (cnt--)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();

        _nop_();
        _nop_();
        _nop_();
        _nop_();

        _nop_();
        _nop_();
        _nop_();
        _nop_();

        _nop_();
        _nop_();
        _nop_();
        _nop_();

        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}

/*******************************************************************************
*   Name: DrvSysTimer0Init
*  Brief: Initialize system timer
*         1.Single Mode
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvSysTimer0Init()
{
    g_usTimerCnt = 0;

    TR0 = 0;       // Stop Timer Counter
    TF0 = 0;

    TMOD |= 0x02;  // ��������ģʽ
    TH0 = 1;       // 1ms
    TL0 = 0x00;

    TR0 = 1;
    ET0 = 1; // enable timer interrupt
}

/******************************************************************************
*
*   Name: ISR_Timer0
*  Brief: Interrupt Service Routine (ISR) for timer 0
*         1.incell ɨ������
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void ISR_Timer0(void) interrupt  1
{
    TF0 = 0;
    g_usTimerCnt++;
}



