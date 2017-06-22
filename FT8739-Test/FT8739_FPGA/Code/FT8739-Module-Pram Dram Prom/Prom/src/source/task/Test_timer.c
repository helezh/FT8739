/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_timer.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-24
*
*  Abstract: Calculate coordinate of points
*
* Reference: test timer introduction:
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_timer.h"

#if _TEST_TIMER_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

//选择定时器0 or 1
#define TIMER_TEST  0

//暂停停止测试
#define INT_HOLD          0//在定时中断中，暂停计数
#define INT_STOP          1//在定时中断中，停止计数,该stop为串口的stop模式,不是低功耗的stop模式
#define MAIN_HOLD         0//主程序中，直接暂停
#define RUN_MODE          1 //0:single mode   1:repeat mode

//中断唤醒测试
#define TEST_IDLE          0//在定时中断中，暂停计数
#define TEST_STANDBY       0//在定时中断中，停止计数
#define TEST_STOP          0//主程序中，直接暂停，低功耗的stop模式

#define TEST_SW_CLR_INT   0 // 1:软件清中断标志 0:硬件清中断标志位

#define MODE0 0x00  //stop
#define MODE1 0X01  //16 bit counter single mode
#define MODE2 0x02  //16 bit counter repeat mode
#define MODE3 0x03  //halt timer暂停工作，如果复原到之前的模式，timer将继续工作

#define TMAXTH 0x7f //TH0[7]必须为0，所以最长时间为127ms
#define TMAXTL 0xf9 //计数时间为TL0[7:0]X4us,最大值不能超过1ms也就是说最大值为8'hF9,大于此值时将强制为8'hF9.

#define TIMER_MS    1 //timer最大的时间设置为127ms，不能超过
#define TIMER_4US   0    //4//timer 4us最大的时间设置为249，即996us，不能超过
//----------------------------------------------------------------------------------------------
//宏常量
#if TIMER_TEST
#define MODE0_SEL  (MODE0<<4)
#define MODE1_SEL  (MODE1<<4)
#define MODE2_SEL  (MODE2<<4)
#define MODE3_SEL  (MODE3<<4)
#define TR_SEL     TR1
#define TH_SEL     TH1
#define TL_SEL     TL1
#define TF_SEL     TF1
#define ET_SEL     ET1
#define INT_SEL    3
#define TDIV_SET   0x80
#define TDIV_CLR   0x20
#define IPLT       IPLT1
#define IPHT       IPHT1

#else
#define MODE0_SEL  MODE0
#define MODE1_SEL  MODE1
#define MODE2_SEL  MODE2
#define MODE3_SEL  MODE3
#define TR_SEL     TR0
#define TH_SEL     TH0
#define TL_SEL     TL0
#define TF_SEL     TF0
#define ET_SEL     ET0
#define INT_SEL    1
#define TDIV_SET   0x40
#define TDIV_CLR   0x10
#define IPLT       IPLT0
#define IPHT       IPHT0
#endif
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
UINT8 m_nTimeState = 0;  //定时器状态

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
* Name:
* Brief:
* Input:
* Output: t = TH0*1ms + TL0*4us  TH0 <= 0x7F; TL0 <= 0xF9
*         Tmax = 127*1ms + 249*4us = 127.996ms
* Return:
*******************************************************************************/
void TimerInit(void)
{
    TIMERCKEN = 1;       // clk
    TIMER_500K_EN = 1;

#if 0
	CLOSE_500K_EN = 0;   //standby不关闭500k
	CLOSE_TIMER_EN = 0;  //standby不关闭timer_clk
#else
	CLOSE_500K_EN = 1;	 //standby关闭500k
	CLOSE_TIMER_EN = 1;  //standby关闭timer_clk
#endif
    
#if RUN_MODE
    TMOD = MODE2_SEL;       // repeat mode
    DBG_TIMER("\n\rTest Timer%d Repeat Mode",TIMER_TEST);
#else    
    TMOD = MODE1_SEL;       //single mode
    DBG_TIMER("\n\rTest Timer%d Single Mode",TIMER_TEST);    
#endif    

#if TEST_SW_CLR_INT
    TDIV |= TDIV_SET;
#endif

    //定时时间设置
    TH_SEL = TIMER_MS;
    TL_SEL = TIMER_4US;

    TF_SEL = 0;

    // run the timer0
    TR_SEL = 1;

    IPLT= 1;
    IPHT = 0;

    // interrupt enable
    ET_SEL = 1;
    EA  = 1;
    DBG_TIMER("\n\rinit Timer");
}

/*******************************************************************************
* 功能:定时器中断服务程序
* 1.闪灯
* 2.计数n次，暂停
* 3.计数n次，停止
********************************************************************************/
void Timer_IRQ(void) interrupt INT_SEL
{
    static UINT16 count = 0;
    static UINT8  ledcnt = 0;

#if TEST_SW_CLR_INT
    //TF_SEL = 0;
    TDIV |= TDIV_CLR;
#endif

    m_nTimeState = 0;        
    count++;
    ledcnt++;
    DBG_TIMER("\n\rledcnt:%02x",ledcnt);
    if (ledcnt > 10)
    {
        ledcnt = 0;
    }
    
    //TMOD  = MODE0_SEL;
#if INT_HOLD
    if (count == 20)
    {
        m_nTimeState = 1;
        DelayMs(100);
        TMOD = MODE3_SEL;     //暂停
        count = 0;
    }
#endif

#if INT_STOP
    if (count == 10)
    {
        m_nTimeState = 1;
        TMOD  = MODE0_SEL;
        count = 0;
        m_nTimeState = 1;
    }
#endif
}


/*******************************************************************************
* 功能:Test_Timer
********************************************************************************/
void Test_Timer(void)
{
	UINT8 XRAM ucMode;
    UINT16 i = 0;
	
    TimerInit();
//    DelayMs(50);   
    while (1)
    { 
#ifdef INT_HOLD
        if (m_nTimeState)
        {
            //TMOD = MODE2_SEL;
            DBG_TIMER("\n\rInt Hold");
            DelayMs(2000);
            m_nTimeState = 0;
            DBG_TIMER("\n\rTH_SEL=%02X",TH_SEL);    
            DelayMs(1000);
            DBG_TIMER("\n\rTH_SEL=%02X",TH_SEL);    
            TMOD = MODE2_SEL;    /* 1.复原原来模式，继续启动 2.不用重新启动 TR  */
            DelayMs(1);
            DBG_TIMER("\n\rTH:%02X,TL:%02X",TH_SEL,TL_SEL);
            DelayMs(10);
            DBG_TIMER("\n\rTH:%02X,TL:%02X",TH_SEL,TL_SEL);
            DBG_TIMER("\n\rmode=%02X",TMOD);
        }
#endif//INT_HOLD
        //--------------------------------------------------------------------------------------
#if INT_STOP
        if (m_nTimeState)
        {
            DBG_TIMER("\n\rInt Stop");
            DelayMs(2000);
            m_nTimeState =0 ;
            TMOD = MODE2_SEL;
            TR_SEL  = 1;       //需要重新启动
            DBG_TIMER("\n\rmode=%02X",TMOD);
        }
#endif//INT_STOP 
        //--------------------------------------------------------------------------------------
#if  MAIN_HOLD
		ucMode = TMOD;
        TMOD = MODE3_SEL;      //hold
        DBG_TIMER("\nMain Hold");
        DelayMs(1000);
        TMOD = ucMode;//MODE1_SEL;      //MODE1 MODE2
        DelayMs(2000);
        DBG_TIMER("\nRun");
#endif//MAIN_HOLD
        //--------------------------------------------------------------------------------------
#if    TEST_IDLE
//        TMOD  = MODE2_SEL;
//        TR_SEL = 1;      //需要重新启动
//        DelayMs(1);
        DBG_TIMER("\nIdle Mode in");
        DelayMs(10);
        DrvSysPowerIdle();
        DelayMs(2000);
        DBG_TIMER("\nIdle Mode out");
#endif//TEST_IDLE
        //--------------------------------------------------------------------------------------
#if    TEST_STANDBY
//        TMOD  = MODE1_SEL;
//        TR_SEL = 1;      //需要重新启动
//        DelayMs(1);
        DBG_TIMER("\n\rSTANDBY Mode in");
        DelayMs(80);
        DrvSysPowerStandby();
        DelayMs(2000);
        DBG_TIMER("\n\rSTANDBY Mode Out");
#endif//TEST_STANDBY
        //--------------------------------------------------------------------------------------
#if    TEST_STOP
        //TMOD  = MODE1_SEL;
        //TR_SEL = 1;      //需要重新启动
        DBG_TIMER("\n\rSTOP Mode in");
        DelayMs(80);   //需要延时，保证uart能够输出完毕    
        DrvSysPowerStop();
        DelayMs(2000);
        DBG_TIMER("\n\rSTOP Mode Out");
#endif//TEST_STOP
        //--------------------------------------------------------------------------------------
    }
}
#endif

