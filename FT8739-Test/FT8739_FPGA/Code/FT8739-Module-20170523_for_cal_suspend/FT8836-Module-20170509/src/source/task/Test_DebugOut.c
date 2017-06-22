/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_DebugOut.c
*
*    Author: 
*
*   Created: 2017-04-18
*
*  Abstract:
*
* Reference: :
* Version:
* 0.1:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_DebugOut.h"

#if _TEST_DEBUGOUT_EN
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
void Test_CLk48M(void)
{
    #if _UART_OUT_GPIO2
        DBG_DEBUGOUT("\nP0_6 is used to be UART TX pad!");
        return;
    #endif
    P0MOD |= BITn(6);
    TEST_OUT3_EN = 0;
    GPIO_INT_SEL = 1;//将唤醒脚选为p0_7
    TEST_CLK_EN = 1;

    OSC_TEST_SEL = 0;  //48M
    CGUCON7 = 0x04;   //osc_test_div

    DBG_DEBUGOUT("\nP0MOD:%02x",P0MOD);
    DBG_DEBUGOUT("\nTESTCON3:%02x",TESTCON3);
    DBG_DEBUGOUT("\nANACON:%02x",ANACON);
    DBG_DEBUGOUT("\nFT_EN_REG:%02x",FT_EN_REG);
    DBG_DEBUGOUT("\nCUGCON7:%02x",CGUCON7);    
    DBG_DEBUGOUT("\nTest Clk 48M");
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CLk32K(void)
{
    #if _UART_OUT_GPIO2
        DBG_DEBUGOUT("\nP0_6 is used to be UART TX pad!");
        return;
    #endif
    P0MOD |= BITn(6);
    TEST_OUT3_EN = 0;
    GPIO_INT_SEL = 1;//将唤醒脚选为p0_7
    TEST_CLK_EN = 1;

    OSC_TEST_SEL = 1;  //32K
    CGUCON7 |= 0x03;//0x03;   //osc_test_div

    DBG_DEBUGOUT("\nP0MOD:%02x",P0MOD);
    DBG_DEBUGOUT("\nTESTCON3:%02x",TESTCON3);
    DBG_DEBUGOUT("\nANACON:%02x",ANACON);
    DBG_DEBUGOUT("\nFT_EN_REG:%02x",FT_EN_REG);
    DBG_DEBUGOUT("\nCUGCON7:%02x",CGUCON7);    
    DBG_DEBUGOUT("\nTest Clk 32K");
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_DebugOut(void)//AFE相关信号的测试放在AFE测试代码里面
{
#if 0
    while(1)
    {
        P0_6 = !P0_6;
        DelayMs(10);
    }
#endif    
    Test_CLk48M();
    //Test_CLk32K();

}
#endif

