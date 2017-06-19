/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_UART.c
*
*    Author: 
*
*   Created: 2016-11-29
*
*  Abstract:
*
* Reference:
*
*   Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_Uart.h"

#if _TEST_UART_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define TEST_BAUD_RATE  115200

#define UART_9BIT

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
*   Name: Uart_Set_RaudRate
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Uart_Set_RaudRate(UINT32 Rate, UINT8 main_clk)
{
    UINT16 cnt;
    
    cnt = (0x400 - (main_clk*1000000/16)/Rate);  //波特率设置
    UART_RELH = cnt>>8;
    UART_RELL = cnt;
}

/*******************************************************************************
*   Name: Test_Uart
*  Brief: 测试uart在不同分频系数下能否正常打印
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_UART(void)
{
    UINT8 Div,i,main_clk = 48;

    DBG_UART("\nTest Uart Start"); 
    
    for(Div = 0 ; Div < 2; Div ++)
    {
        DrvSysClkInit(Div);

        main_clk = 48/CLK_DIV(Div);

        #if 0
        if(Div == 0)
        {
            main_clk = 48;
        }
        else
        {
            main_clk = 48/(Div+Div%2);
        }
        #endif
        Uart_Set_RaudRate(BAUD_RATE,main_clk);
        DelayMs(1000);

        DBG_UART("\nmain clk is %dM",main_clk);

#if 0        
        for(i = 0;i < 100; i++)
        {
            DBG_UART("\n%x",0x55);
            DBG_UART("\n%x",0xAA);            
        }
#endif        
        DelayMs(1000);//延时，以保证打印以后uart的配置才会发生改变
    }


    DrvSysClkInit(MAIN_CLK); //切回原来状态 
    Uart_Set_RaudRate(BAUD_RATE,48);

    DelayMs(1000);
    DBG_UART("\n%x",0x55);
    DBG_UART("\n%x",0xAA);

    /*测试发送大量数据*/
    for(i = 0; i < 0xFF; i++ )
    {
        DBG_UART("\nTest Sending large number of data");
        DBG_UART("\nThe %d Test",i);
     }
    
    DBG_UART("\nTest Uart End");  
    
}
#endif












