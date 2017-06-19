/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_i2c.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-25
*
*  Abstract:
*
* Reference:
*
* Version:
* 0.1:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_i2c.h"

#if _TEST_I2C_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define I2C_MON_Wakeup_Standby  0x01

#define I2C_MON_WAKEUP   1
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT8 g_nWKsrc    = 0x00;
UINT8 g_ucI2Ccmd  = 0x00;

UINT8   g_ucI2cIdx;
UINT8   g_ucI2cLen;                     // 数据长度不能超过256
UINT8   g_ucHostIdx = 0;                // Host每次通讯RW的字节序号
UINT8 XRAM g_ucDataBuf[256];
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvI2cInit(void)
{
    I2CCKEN = 1;

    I2CBUF = 0;
    I2CRI  = 0;
    I2CTI  = 0;

    /* 设置设备地址 */
    I2CADDR = I2C_SLAVE_ADDR&0xFE;
    //I2CADDR = I2C_SLAVE_ADDR|0x01;

    /* 广播地址 */
    //I2CADDR |= 0x01;

    I2C_STOP_EI = 1;        //Set to enable Additional Interrupt 0
    I2C_STOP_IF = 0;

    I2C_IPH = 0;
    I2C_IPL = 1;

    Uart_IPH = 0;
    Uart_IPL = 0;

    DBG_MODE("\nI2c test is Start");

#if I2C_MON_WAKEUP
    I2C_MON_CFG  = 1;
    I2C_MON_WKEN = 1;
    I2C_WKEN = 0;
    I2C_WK_RST   = 0;
#endif
    ET2 = 1;                 //I2C Interrupt Enable
}

/*******************************************************************************
*   Name: ExternInt0Init
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void ExternInt0Init(void)
{
    IT0 = 0;

    IPL0  = 0;
    IPH0  = 0;

    IPLX0 = 1;
    IPHX0 = 1;

    EX0 = 1;
    EA  = 1;
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_I2C(void)
{
    ExternInt0Init();
    DrvI2cInit();
#if I2C_MON_WAKEUP
    DBG_I2CWK("\nStart I2C monitor wakeup...");
    DelayMs(100);
    //DrvSysPowerIdle();
    DrvSysPowerStandby();
    //DrvSysPowerStop();
    DBG_I2CWK("\n\rWK src:%x",g_nWKsrc);
    DBG_I2CWK("\nStart I2C monitor wakeup..ok.");
#endif

    while (1)
    {
        if (g_ucI2Ccmd == I2C_MON_Wakeup_Standby)
        {
            DBG_I2CWK("\n first cmd is ok");
            g_ucI2Ccmd = 0;
        }
        DelayMs(1000);
    }
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2C_ISR(void) interrupt 5
{
    UINT8 ch = 0;

    DBG_I2CWK("\nint5");

    if (RIFLAG)
    {
        RIFLAG = 0;
        ch = DATABUFF;
        g_ucHostIdx ++;

        /* 接收 Host 写的第一个数据，保存为cmd */
        switch (g_ucHostIdx)
        {
            case 0x01:
            {
                g_ucI2Ccmd = ch;
                break;
            }
            case 0x02:
            {
                g_ucI2cLen   = ch;
                g_ucI2cIdx   = 0;
                break;
            }
            case 0x03:
            {
                g_ucDataBuf[g_ucI2cIdx] = ch;
                g_ucI2cIdx++;
                if (g_ucI2cIdx >= g_ucI2cLen)
                {
                    g_ucHostIdx  = 0x00;
                    DATABUFF = g_ucDataBuf[0x00];
                }
                break;
            }
            /* I2C_DATA */
            default:
            {
                g_ucDataBuf[g_ucI2cIdx] = ch;
                g_ucI2cIdx++;
                if (g_ucI2cIdx >= g_ucI2cLen)
                {
                    g_ucHostIdx  = 0x00;
                    DATABUFF = g_ucDataBuf[0x00];
                }
                break;
            }

        }
    }
    //每一帧读的第一个数据，总是提前准备，因此中断来后的index是从1开始的
    if (TIFLAG)
    {
        TIFLAG = 0;
        g_ucHostIdx++;
        DATABUFF = g_ucDataBuf[g_ucHostIdx]; //place next byte
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
#if I2C_MON_WAKEUP
    DBG_I2CWK("\nint0");
    g_nWKsrc = IWKSTA;	
    //if (I2CMON_INT)
    {
        I2C_WK_RST = 1;
        I2C_WK_RST = 0;
    }
#endif

}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2C_STOP_ISR(void) interrupt 8
{
    g_ucHostIdx = 0;
    I2CSTP = 0;
}
#endif

