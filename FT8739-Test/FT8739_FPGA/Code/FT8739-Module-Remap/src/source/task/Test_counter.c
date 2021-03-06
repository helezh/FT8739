/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_WDT.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-21
*
*  Abstract: 溢出时间12.096ms~25.2S,步长2us/32us
*
* Reference: test WDT introduction:

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_Counter.h"

#if _TEST_CNT_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
//time0
#define T0MODE                            0x02    //高四位为T1,低四位为T0
#define IRQTIME0_VALUE                    1       //(MS)
#define IRQTIME0_LOAD()                   TMOD|=T0MODE;TH0=IRQTIME0_VALUE;TL0=0

#define INT1_TRI_MODE                     0// 0:LOW level triggered 1:falling edg
#define TEST_CNT_WK                       1//0:不测试CNT WK   1:测试CNT WK
#define COUNT_MS                          100//COUNT溢出时间，ms 

//以下三种模式最多只能进入一种
#define IDLE_MODE                        0//0:不进入idle     1:进入idle
#define STANDBY_MODE                     1//0:不进入standy 1:进入standy
#define STOP_MODE                        0// 0:不进入stop   1:进入stop



/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
UINT16 m_usCnt  = 0;
UINT32 Counter  = 0;
UINT8 g_nWKsrc  = 0x00;
//UINT8 g_nWKsrcH = 0x00;
//UINT8 g_nWKsrcL = 0x00;
BOOLEAN g_bWKsrcOut = 1;
BOOLEAN g_bCntFlag = 0;
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
/*******************************************************************************
* Name: DrvSysTimerInit
* Brief:  系统定时器初始化
* Input:
* Output:
* Return:
*******************************************************************************/
void DrvSysTimer0_Init(void)
{
    TR0 = 0;
    IRQTIME0_LOAD();
    TR0 = 1;
    ET0 = 1;
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT0中断初始化函数
*******************************************************************************/
void ExternInt0Init(void)
{
    IT0   = 0;   // 0:LOW level triggered 1:falling edge

    IPL0  = 0;
    IPH0  = 0;

    IPLX0 = 1;
    IPHX0 = 1;  //中断0优先级必须最高

    EX0   = 1;
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT1中断初始化函数
*******************************************************************************/
void ExternInt1Init(void)
{
    IT1 = INT1_TRI_MODE;   // 0:LOW level triggered 1:falling edge
    EX1 = 1;

    IPLX1 = 1;
    IPLX1 = 1;

    EA = 1;
}

/*******************************************************************************
* Name: Timer_IRQHandler
* Brief:   Timer 中断响应函数
* Input:
* Output:
* Return:
*******************************************************************************/
void Timer0_IRQHandler(void) interrupt  1
{
    m_usCnt++;
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT0中断响应函数
*******************************************************************************/
void Exint0_IRQHandler(void) interrupt 0
{
    if (g_bWKsrcOut)
    {
        g_nWKsrc = IWKSTA;
        g_bWKsrcOut = FALSE;
    }

    if(RTC_CNT_INT)
    {
        DBG_FLOW("\n\rcount int0");
        RTC_CNT_WKEN= 0;
    }
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT1中断响应函数
*******************************************************************************/
void Exint1_IRQHandler(void) interrupt 2
{
    //if(RTC_CNT_INT)//不能用RTC_CNT_INT判断，进入int0用该标志判断了，进入int1时该标志已经为0
    {
      //  RTC_CNT_INT = 0;
        P0_2 = 0;
        // 清cnt
        CNT_CLEAR     = 1;
        //while(RTC_CNT_INT);//等待RTC_CNT_INT为0，大概为一个clk的时间,现在不需要了。硬件改过来了
        CNT_START     = 0;          
        DBG_FLOW("\n\rcnt int1");
        g_bCntFlag = TRUE;
        RTC_CNT_WKEN = 1;
    }
}

/*******************************************************************************
* Name:Test_Counter
* Input:
* Output:
* function:
*********************************************************************************/
void Test_Counter(void)
{
    UINT8 i = 0;
    UINT8 Temp[3];
    UINT32 cnt;
    // cnt clk enable
    CLKEN_500K = 1;    
    CNTCKEN = 1;

    //DrvSysTimer0_Init();
    
    P0_2 = 0;
    DelayMs(200);
    P0_2 = 1;

#if 0
    // 设置CNT计数时间
    CNTIVH = 0x00;
    CNTIVM = 0x00;
    CNTIVL = 0x02;
#else
    // 设置CNT计数时间
    cnt = COUNT_MS*500;//COUNT_MS = cnt *2us/1000
    CNTIVH = cnt>>16;
    CNTIVM = cnt>>8;
    CNTIVL = cnt;

    
#endif

    CNT_WKEN_SEL  = 1; //enable CNT function
    
#if TEST_CNT_WK
    RTC_CNT_WKEN  = 1; //enable wake up (RTC & CNT use same reg)
#endif

    // clear cnt
    //CNT_CLEAR       = 1;
    //CNT_START       = 1;
    
//    DrvSysTimer0_Init();
    
#if TEST_CNT_WK  
    ExternInt0Init();
#endif

    ExternInt1Init();
    DBG_MODE("\n\rCNT test is start");

    //P0_6 = 0;
    //CNT_START = 1;
    while (1)
    {
        CNT_START = 1;    
        m_usCnt = 0;
        g_bCntFlag = 0;
        
#if TEST_CNT_WK        
       RTC_CNT_WKEN  = 1; //enable wake up (RTC & CNT use same reg)
#endif


    #if 0   //打印变了值,在CNT_START = 0的时候测试CNT CLEAR能否清除。

        DelayMs(6);
        CNT_START     = 0;
        Temp[0] = CNTIVH;
        Temp[1] = CNTIVM;
        Temp[2] = CNTIVL;
        DBG_CNT("\n\rCNTIVH=%d",Temp[0]);   
        DBG_CNT("\n\rCNTIVM=%d",Temp[1]);          
        DBG_CNT("\n\rCNTIVL=%d",Temp[2]);
        CNT_CLEAR     = 1;
        DelayMs(7);
        Temp[0] = CNTIVH;
        Temp[1] = CNTIVM;
        Temp[2] = CNTIVL;
        DBG_CNT("\n\rCNTIVH=%d",Temp[0]);   
        DBG_CNT("\n\rCNTIVM=%d",Temp[1]);   
        DBG_CNT("\n\rCNTIVL=%d",Temp[2]);
        DelayMs(7);
        Temp[0] = CNTIVH;
        Temp[1] = CNTIVM;
        Temp[2] = CNTIVL;
        DBG_CNT("\n\rCNTIVH=%d",Temp[0]);   
        DBG_CNT("\n\rCNTIVM=%d",Temp[1]);   
        DBG_CNT("\n\rCNTIVL=%d",Temp[2]);        
    #endif
        
    
#if IDLE_MODE
        DBG_MODE("\njoin idle mode");
        DelayMs(10);
        DrvSysPowerIdle();
        DBG_MODE("\ncount wakeup..ok");
#endif

#if STANDBY_MODE
        DBG_MODE("\njoin standy mode");
        DelayMs(50);
        DrvSysPowerStandby();
        DBG_MODE("\ncount wakeup..ok");
#endif

#if STOP_MODE
        DBG_MODE("\njoin stop mode");
        DelayMs(50);
        DrvSysPowerStop();
        DBG_MODE("\ncount wakeup..ok");
#endif


        while (!g_bCntFlag);
        if (g_bCntFlag)
        {
            DBG_CNT("\n\rWK src:%x",g_nWKsrc);
            DBG_CNT("\n\rCNT time=%dms",m_usCnt);
        }
        DelayMs(1000);
    }
}
#endif

