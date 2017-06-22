/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_spi0_wakeup.c
*
*    Author: tangsujun
*
*   Created: 2017-03-10
*
*  Abstract: 
*
* Reference: test spi0 wake up introduction:
*            g_ucTestCmd :  0x01 : idle wake up
*                           0x02 : standby wake up
*                           0x03 : stop wake up
*******************************************************************************/
/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_spi0_wakeup.h"
#include "Drv_mcu.h"

#if _TEST_SPI0_WK_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define TEST_INIT_CMD 0x00

UINT8 g_ucSPI0cmd  = 0x00;
UINT8 g_wkup_stop = 0;
UINT8 g_CMDbuff[5];
/******************R*************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef enum
{
    SPI0Wakeup_NOP,
    SPI0Wakeup_Idle,
    SPI0Wakeup_Standby,
    SPI0Wakeup_Stop,
} ENUM_SPI0Wakeup;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
*   Name: ExternInt0Init
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void ExternInt0Init(void)
{
    IT0   = 0;

    IPL0  = 0;  /* interruption priority */
    IPH0  = 0;  /* interruption priority */
      /* Int0优先级设置为3---唤醒要求 */
    IPLX0 = 1;
    IPHX0 = 1;

    //Uart_IPL = 1;

    EX0 = 1;

    EA  = 1;
    
}

/*******************************************************************************
*   Name: DrvHostSpi0Init
*  Brief: SPI0接口配置与初始化
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvHostSpi0Init(void)
{
    
    SPI0CKEN = 1;
    SPI0CON5 =0xff;
    SPI0CON2 =0x00;
    SPI0CON3 =0;
    SPI0CON4 =0X00;
    /* IO配置: P05-->P02  MOSI MISO CLK CS */
    P0MOD |= BITn(5) + BITn(4)+BITn(3) + BITn(2);
    P0SEL |= BITn(5) + BITn(4)+BITn(3) + BITn(2);
    
    P0DIR |= BITn(4)+BITn(3) + BITn(2);
    P0DIR &= ~ BITn(5);
    
    SPI0_EI = 0;
    




    //中断标志使能
    SPI0RI_EN = 1;
    SPI0TI_EN = 0;

    SPI0RX_AUTO_CLR =1;
    SPI0TX_AUTO_CLR =1;


    SPI0_STOP_IE = 1;    
    SPI0_STOP_EN = 1;
    SPI0_STOP_CLR= 1;
    
    SPI0_IPH = 0;
    SPI0_IPL = 1;

    Uart_IPH = 1;
    Uart_IPL = 1;

    I2C_MON_WKEN=0;
    SPI0_WKEN = 0;

    SPI0_EI = 1;
}

/*******************************************************************************
*   Name: Test_SPI0_Wakeup
*  Brief:
         1.cmd 02: idle mode wake up
         2.cmd 03: standby mode wake up
         3.cmd 04: stop mode wake up
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_SPI0_Wakeup(void)
{
    DrvHostSpi0Init();
    ExternInt0Init();
    
    DBG_SPI0WK("\nSPI0 wakeup Start");
 
    g_ucSPI0cmd = SPI0Wakeup_NOP;
    while (1)
    {
        if (g_ucSPI0cmd == SPI0Wakeup_Idle)
        {
            DBG_SPI0WK("\nStart SPI0 wakeup...Idle");
            DelayMs(100);
            //配置中断0的中断源
            I2C_MON_WKEN  = 1; 
            SPI0_WKEN     = 1;
            
            DelayMs(1);
            DrvSysPowerIdle();
            DBG_SPI0WK("\nWake up in idle");
       
            g_ucSPI0cmd = 0;
        }
        if (g_ucSPI0cmd == SPI0Wakeup_Standby)
        {
            DBG_SPI0WK("\nStart SPI0 wakeup...Standby");
            DelayMs(100);
            //配置中断0的中断源
            I2C_MON_WKEN  = 1;
            SPI0_WKEN     = 1;
                    
            DelayMs(1);
            DrvSysPowerStandby();
            DBG_SPI0WK("\nWake up in standby");
            g_ucSPI0cmd = 0;
        }
        if (g_ucSPI0cmd == SPI0Wakeup_Stop)
        {
            DBG_SPI0WK("\nStart SPI0 wakeup...Stop");
            DelayMs(100);
            //配置中断0的中断源
            I2C_MON_WKEN  = 1;
            SPI0_WKEN     = 1;  

            
            DelayMs(1);
            g_wkup_stop = 0;

            DrvSysPowerStop();
            DBG_SPI0WK("\nWake up in Stop");
            DelayMs(100);
            if(g_wkup_stop == 1)
            {
                DBG_SPI0WK("\n\rSPI0_STATE = %02x",g_CMDbuff[0]);
                DBG_SPI0WK("\n\rSPI0_CMD0 = %02x",g_CMDbuff[1]);
                DBG_SPI0WK("\n\rSPI0_CMD1 = %02x",g_CMDbuff[2]);
                DBG_SPI0WK("\n\rSPI0_CMD2 = %02x",g_CMDbuff[3]);
                DBG_SPI0WK("\n\rSPI0_CMD3 = %02x",g_CMDbuff[4]);
                DBG_SPI0WK("\nWake up in stop");               
            }
            g_ucSPI0cmd = 0;
            g_ucSPI0cmd = SPI0Wakeup_NOP;
            
        }
        
        DelayMs(1000);
        //DBG_SPI0WK("\ng_ucSPI0cmd:%02X",g_ucSPI0cmd);
    }
}

/*******************************************************************************
*   Name: isr0
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void isr0(void) interrupt 0
{
    DBG_SPI0WK("\nWK src:%X",IWKSTA);
    //DBG_SPI0WK("\nSPI0 STp:%X",SPI0_WK_STOP);

         
    if ((g_ucSPI0cmd > 0)&&(g_ucSPI0cmd < 4))
    {
            I2C_MON_WKEN  = 0;        
    }
}

/*******************************************************************************
*   Name: SPI0_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI0_IRQHandler(void) interrupt 11
{
    if (SPI0RI)
    {
        SPI0RI_CLR= 1;
        g_ucSPI0cmd = SPI0BUF;  //接收命令

    //    DBG_SPI0WK("\nCmd:%02x",g_ucSPI0cmd);
    }

}

/*******************************************************************************
*   Name: SPI0Stop_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI0Stop_IRQHandler(void) interrupt 8
{    
    
    if(SPI0_STOP)
    {
        DBG_SPI0WK("\n%02x",SPI0CON5);
        DBG_SPI0WK("\nSPI0_WK_STP");
     
        SPI0_STOP_CLR = 1; 
        g_wkup_stop =1;
        SPI0CON5    =0Xff;
    }
}
#endif
