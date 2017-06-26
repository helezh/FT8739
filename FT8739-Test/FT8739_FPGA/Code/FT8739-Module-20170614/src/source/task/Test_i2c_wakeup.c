/*******************************************************************************
* Copyright (c) 2013~2014 Focaltech (Shenzhen) Inc.
* All right reserved.
*
* Project:     FT8836
* File:        I2C唤醒
*
* VERSION        DATE              AUTHOR
* V0.1           2014-04-29        xinkunpeng
*
* Reference: test i2c wake up introduction:
*            g_ucTestCmd :  0x01 : idle wake up
*                           0x02 : standby wake up
*                           0x03 : stop wake up
*                           0x04 : i2c slave addr + 2
*                           0x05 : i2c slave addr - 2
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_i2c_wakeup.h"
#include "Drv_mcu.h"

#if _TEST_I2C_WK_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define TEST_INIT_CMD 0x00

UINT8 g_ucI2Ccmd  = 0x00;
UINT8 g_ucI2cAddr = 0x70;
UINT8 g_wkup_stop = 0;
UINT8 g_CMDbuff[5];
/******************R*************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef enum
{
    I2CWakeup_NOP,
    I2CWakeup_Idle,
    I2CWakeup_Standby,
    I2CWakeup_Stop,
    I2CWakeup_AddrUp,
    I2CWakeup_AddrDown,
} ENUM_I2CWakeup;
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
*   Name: DrvHostI2cInit
*  Brief: I2C接口配置与初始化
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvHostI2cInit(void)
{
    I2CCKEN = 1;
    
    I2CBUF = 0;
    I2CRI  = 0;
    I2CTI  = 0;

    I2CADDR = I2C_SLAVE_ADDR&0xFE;
    //I2CADDR = I2C_SLAVE_ADDR|0x01;
    
    ISP_STOP_EI = 1;
    I2C_STOP_IF = 0;
    
    I2C_IPH = 0;
    I2C_IPL = 1;

    Uart_IPH = 0;
    Uart_IPL = 0;

    I2C_MON_CFG = 0;    // 0:i2c工作,1:i2c monitor工作
    I2C_WKEN = 0;
    ISP_MON_WKEN = 1;
    I2C_DEGLITCH_EN = 0; 

    ADDR_NACK = 0;
    DATA_NACK = 0;

    ET2 = 1;
}

/*******************************************************************************
*   Name: Test_I2CWakeup
*  Brief:
         1.cmd 02: idle mode wake up
         2.cmd 03: standby mode wake up
         3.cmd 04: stop mode wake up
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_I2CWakeup(void)
{
    DrvHostI2cInit();
    ExternInt0Init();
    P0_2 = 0;
    DBG_I2CWK("\nI2C wakeup Start");
 
    g_ucI2Ccmd = I2CWakeup_NOP;
    while (1)
    {
        if (g_ucI2Ccmd == I2CWakeup_Idle)
        {
            DBG_I2CWK("\nStart I2C wakeup...Idle");
            DelayMs(100);
            //配置中断0的中断源
            ISP_MON_WKEN = 1;       //monitor and iic wakeup switch
            I2C_WKEN     = 1;       //i2c wakeup
            ISP_STOP_EI  = 1;
            DelayMs(1);
            DrvSysPowerIdle();
            DelayMs(1);
            DBG_I2CWK("\nWake up in idle");
            g_ucI2Ccmd = 0;
        }
        if (g_ucI2Ccmd == I2CWakeup_Standby)
        {
            DBG_I2CWK("\nStart I2C wakeup...Standby");
            DelayMs(100);
            //配置中断0的中断源
            ISP_MON_WKEN = 1;       //monitor and iic wakeup switch    
            I2C_WKEN     = 1;       //i2c wakeup
            ISP_STOP_EI  = 1;            
            DelayMs(1);
            DrvSysPowerStandby();
            DelayMs(1);
            DBG_I2CWK("\nWake up in standby");
            g_ucI2Ccmd = 0;
        }
        if (g_ucI2Ccmd == I2CWakeup_Stop)
        {
            DBG_I2CWK("\nStart I2C wakeup...Stop");
            DelayMs(100);
            //配置中断0的中断源
            ISP_MON_WKEN = 1;       //monitor and iic wakeup switch 
            I2C_WKEN     = 1;       //i2c wakeup
            ISP_STOP_EI  = 1;            
            DelayMs(1);
            g_wkup_stop = 0;

            DrvSysPowerStop();
            DelayMs(100);
            if(g_wkup_stop == 1)
            {
                DBG_I2CWK("\n\rI2C_STATE = %02x",g_CMDbuff[0]);
                DBG_I2CWK("\n\rI2C_CMD0 = %02x",g_CMDbuff[1]);
                DBG_I2CWK("\n\rI2C_CMD1 = %02x",g_CMDbuff[2]);
                DBG_I2CWK("\n\rI2C_CMD2 = %02x",g_CMDbuff[3]);
                DBG_I2CWK("\n\rI2C_CMD3 = %02x",g_CMDbuff[4]);
                DBG_I2CWK("\nWake up in stop");               
            }
            g_ucI2Ccmd = 0;
            
        }
        if (g_ucI2Ccmd == I2CWakeup_AddrUp)
        {
            g_ucI2Ccmd = 0;
            g_ucI2cAddr += 2;
            I2CADDR =  g_ucI2cAddr;
            DBG_I2CWK("\nSalve:%02X",I2CADDR);
        }
        if (g_ucI2Ccmd == I2CWakeup_AddrDown)
        {
            g_ucI2Ccmd = 0;
            g_ucI2cAddr -= 2;
            I2CADDR =  g_ucI2cAddr;
            DBG_I2CWK("\nSalve:%02X",I2CADDR);
        }
        DelayMs(1000);
        //DBG_I2CWK("\ng_ucI2Ccmd:%02X",g_ucI2Ccmd);
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
    DBG_I2CWK("\nWK src:%X",IWKSTA);
    //DBG_I2CWK("\nI2C STp:%X",I2C_WK_STOP);
         
    if ((g_ucI2Ccmd > 0)&&(g_ucI2Ccmd < 4))
    {
		ISP_MON_WKEN = 0;        
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
    if (RIFLAG)
    {
        RIFLAG = 0;
        g_ucI2Ccmd = I2CBUF;  //接收命令

        DBG_I2CWK("\nCmd:%02x",g_ucI2Ccmd);
    }

    if (TIFLAG)
    {
        TIFLAG = 0;
        I2CBUF = 0x5a;
    }
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
    
    if(I2C_WK_STOP)
    {
        DBG_I2CWK("\nI2C_WK_STP");
        g_CMDbuff[0] = I2C_STATE;
        g_CMDbuff[1] = I2C_CMD0;
        g_CMDbuff[2] = I2C_CMD1;
        g_CMDbuff[3] = I2C_CMD2;
        g_CMDbuff[4] = I2C_CMD3;
        I2C_WK_STOP = 0;        
        I2C_WKEN = 0;
        g_wkup_stop =1;
    }
}
#endif
