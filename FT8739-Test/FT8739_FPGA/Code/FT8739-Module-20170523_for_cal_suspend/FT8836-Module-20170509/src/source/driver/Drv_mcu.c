/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Drv_mcu.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-24
*
*  Abstract:
*
* Reference: Transplant from FT5412 by linjianjun
*
*   Version: 0.2
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "Drv_mcu.h"
#include "uart.h"

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
UINT8 XRAM g_ucbuf[16];

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: DrvSysClkInit
*  Brief: Initialize system clock based on ucflag
*  Input: UINT8 ucflag
* Output: None
* Return: None
*******************************************************************************/
void DrvSysClkInit(UINT8 ucDiv)
{
    if (ucDiv < 4)
    {
        CGUCON4 = ucDiv;
    }
        
    CLKEN_500K = 1;      // 500kÊ±ÖÓ¿ªÆô 
}

/*******************************************************************************
*   Name: DrvIOInit
*  Brief:
*  Input:
* Output: None
* Return: None
*******************************************************************************/
void DrvIOInit(void)
{
    g_ucbuf[0]  = CGUCON0;
    g_ucbuf[1]  = CGUCON1;
    g_ucbuf[2]  = CGUCON2;
    g_ucbuf[3]  = CGUCON3;
    g_ucbuf[4]  = CGUCON4;
    g_ucbuf[5]  = CGUCON5;
    g_ucbuf[6]  = CGUCON6;
    g_ucbuf[8]  = SFTRST;
    g_ucbuf[9]  = POR_STA;
    g_ucbuf[10] = RST_STA;
    g_ucbuf[11] = ANACON;

    POR_STA = 0x00;
    RST_STA = 0x66;

    SYSCKEN = 1;
    P0SEL = 0xff;
    P1SEL = 0xff;
    
    P1MOD = 0x00;
    
    P0MOD = BITn(1) + BITn(0);      //P0_0 SCL;P0_1 SDA

    P0DIR = 0xff;
    P1DIR = 0xff;


}

/*******************************************************************************
*   Name: DelayUs
*  Brief:
*  Input:
* Output: None
* Return: None
*******************************************************************************/
void DelayUs(UINT8 ucDlyCnt)
{
#if _FOR_RD
	return;
#else
    while (ucDlyCnt--)
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
#endif	
}

/*******************************************************************************
*   Name: DelayMs
*  Brief:
*  Input:
* Output: None
* Return: None
*******************************************************************************/
void DelayMs(UINT16 ucDlyCnt)
{
    while (ucDlyCnt--)
    {
        DelayUs(250);
        DelayUs(250);
        DelayUs(250);
        DelayUs(250);
    }
}

/*******************************************************************************
*   Name: DrvSysPowerMode
*  Brief: Select system power saving mode
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvSysPowerMode(UINT8 pmode)
{
    /* IDLE mode */
    if (pmode == 0)
    {  
        CORE_STOP = 0;
        CORE_IDLE = 1;
        EA = 1;
    }
    /* Stop mode */
    if (pmode == 1)
    {
        CLK_WP = 1;
        STANDBY = 0;
        CORE_STOP = 1;
        EA = 1;
    }

    /* Standby mode */
    if (pmode == 2)
    {
        CLK_WP = 1;
        STANDBY = 1;
        CORE_STOP = 1;
        EA = 1;
    }

    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

