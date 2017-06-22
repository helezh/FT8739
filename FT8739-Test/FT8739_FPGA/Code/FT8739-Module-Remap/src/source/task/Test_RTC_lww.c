/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_RTC.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-18
*
*  Abstract:
*
* Reference:
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_RTC.h"

#if _TEST_RTC_EN
 
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
/* RTC */
#define RTC_MS        32
#define RTC_N_MS     (RTC_MS*10)//100ms

/*
 * Normal   :此时CPU启动RTC，RTC产生一次定时中断，计时时间与计数Counter相关
 * Slot     :此时CPU启动RTC，若打开wake_sub_en，则RTC会产生slot_num+1个中断给CPU
 * Auto     :此时CPU启动一次RTC，产生一次RTC中断给CPU，产生无限次中断给ASM，
             直到CPU CLR RTC
 * LCD Start:此时RTC会根据LCD信号启动，在Counter中间会自动屏蔽LCD的start
             信号
 * 以上模式，CPU都只看到一个中断，所以中断中需要做RTC_CLR
*/
/*
 * 问题点：
 * 1.eint1中不做RTC_CLR也不会导致一直停在eint1中断中不出来，配置成small或者big int均一样
 * 2.RTC打印出来的定时时间与设定时间不一样，设定时间100ms，实际出来时间是66ms
*/
//RTC MODE 0-Normal,1-Slot,2-Auto,3-Lcd Start
#define RTC_MODE    0

/* time0 */
#define T0MODE                            0x02    //高四位为T1,低四位为T0
#define IRQTIME0_VALUE                    1       //(MS)
//#define IRQTIME0_LOAD()                   TMOD|=T0MODE;TH0=IRQTIME0_VALUE;TL0=0 old
#define IRQTIME0_LOAD()                   TMOD|=T0MODE;TH0=IRQTIME0_VALUE;TL0=0

#define TEST_RTC_WK                       0//0:不测试rtc wk；1 测试rtc wk
#define INT1_TRI_MODE                     1// 0:LOW level triggered 1:falling edge

//#define AUTO_MODE                         1//0:不开启Auto_mode  1:开启Auto_Mode
#define RTC_SLOT_NUM                      9
#define RTC_SLOT_NUM_NONE                 0
#define TEST_WAKE_EN_SUB                  0

//以下三种模式最多只能进入一种
#define STANDBY_MODE                      0//0:不进入standy 1:进入standy
#define STOP_MODE                         0// 0:不进入stop   1:进入stop
#define IDLE_MODE                         0//0:不进入idle     1:进入idle

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
UINT8 g_nWKsrc     = 0x00;
BOOLEAN g_bWKsrcOut = 1;
BOOLEAN g_bRtcFlag  = 0;

UINT16 m_usCnt = 0;
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:  DrvRTCInit
*  Brief:  RTC初始化
*          1.时钟是固定32K, 1秒32000次，1ms是32次 = 0x20
*          2.计数器为16位，--到0，产生中断
*          3.最大定时时间: t = 0x10000/0x20 = 65536/32 = 2048ms
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvRTCInit(void)
{
    // 32K时钟使能
    CLK_WP = 1;
    EN_32K = 1;
    CKEN_32KRTC = 1;
    
    // rtc clk enable
    RTCCKEN = 1;
//    DBG_RTC("\nRTCCON:%x",RTCCON);
    // clear rtc
    RTC_WP  = 1;
    RTC_CLR = 1;
    //DelayMs(100);

    // 设置RTC计数时间
    RTCIVH  = RTC_N_MS>>8;
    RTCIVL  = RTC_N_MS;

    //Normal mode
    #if (RTC_MODE == 0)
//    RTCSLN        = RTC_SLOT_NUM_NONE;
    RTC_AUTO_MODE = 0;
    LCD_START_EN  = 0;
    #endif

    //Slot mode
    #if (RTC_MODE == 1)
//    RTCSLN          = RTC_SLOT_NUM;
    RTC_AUTO_MODE   = 0;
    LCD_START_EN    = 0;
    #endif

    //Auto mode
    #if (RTC_MODE == 2)
//    RTCSLN          = RTC_SLOT_NUM_NONE;
    RTC_AUTO_MODE   = 1;
    LCD_START_EN    = 0;
    #endif

    //LCD Start mode
    #if (RTC_MODE == 3)
//    RTCSLN = RTC_SLOT_NUM_NONE;
    RTC_AUTO_MODE = 1;
    LCD_START_EN = 1;
    #endif

//    DBG_RTC("\nRTCCON:%x",RTCCON);

    #if TEST_RTC_WK
    RTC_CNT_WKEN = 1;  // RTC wake en  
    #endif

    //RTC中断作为中断0
    #if TEST_WAKE_EN_SUB
    RTC_WKEN_SUB = 1;
    RTC_WKEN     = 0;
    RTCSLN       = RTC_SLOT_NUM;
    #else
    RTC_WKEN     = 1;  // select rtc  
    RTC_WKEN_SUB = 0;
    RTCSLN = RTC_SLOT_NUM_NONE;    
    #endif
 
    DBG_RTC("\nRTC Interval:%dms",RTC_N_MS/RTC_MS);         // 1.8ms@115200bps total 19 character 100us per character
    DBG_RTC("\nRTC_IVH:%02X,RTC_IVL:%02X",RTCIVH,RTCIVL);
    DBG_RTC("\ninit RTC OK!");
    P0_3 = 1;
    DelayMs(200);   
    P0_3 = 0;
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
*   Name: DrvSysTimer0_Init
*  Brief: 定时1ms
*  Input:
* Output:
* Return: timer0 定时器初始化函数
*******************************************************************************/
void DrvSysTimer0_Init(void)
{
    TR0 = 0;     /* Stop Timer Counter */
    IRQTIME0_LOAD();    //1//1ms interval

//    IPHT0 = 1;
//    IPLT0 = 1;
    
    TR0 = 1;
    ET0 = 1;     // enable timer interrupt
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
    IPHX1 = 1;
    IPLX1 = 1;
    EX1   = 1;       
    EA    = 1;
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
    g_bRtcFlag = TRUE;
    if(RTC_CNT_INT)
    {
        //P0_6 = ~P0_6;
        RTC_CNT_WKEN = 0;
        //RTC_WP  = 1;
        //RTC_CLR = 1;        
        //DBG_FLOW("\n\rrtc int0");
        DBG_RTC("\n0");
    }
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: timer0 定时器中断响应函数
*******************************************************************************/
void Timer0_IRQHandler(void) interrupt  1
{
    m_usCnt++;
    #if 1
    P0_7 = 1;
    DelayUs(5);
    P0_7 = 0;
    #else
    DBG_RTC("\n1");
    #endif
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT1中断响应函数.
*******************************************************************************/
void Exint1_IRQHandler(void) interrupt 2
{   
    #if 0
    P0_7 = 1;
//    DelayMs(1);
    P0_7 = 0;
    #endif
    //if(RTC_CNT_INT)//不能用RTC_CNT_INT判断，进入int0用该标志判断了，进入int1时该标志已经为0
    {
        //P0_7 = ~ P0_7;
        
        //清rtc
//        #if !AUTO_MODE//AUTO MODE不能写CLR。因为写CLR时会关闭RTC内部的gating，没法重复进入RTC中断。
        RTC_WP  = 1;
        RTC_CLR = 1;
//        #endif
        
        #if !INT1_TRI_MODE//如果是低电平触发模式，需要等待RTC_CNT_INT清0，否则会进入几次中断，该标志持续时间为1个RTC CLK
        while(RTC_CNT_INT);
        #endif
        
        //DBG_FLOW("\n\rrtc int1");
        DBG_RTC("\n2");
        g_bRtcFlag = TRUE;

        #if TEST_RTC_WK
            RTC_CNT_WKEN = 1;
        #endif
    }
}


/*******************************************************************************
*   Name: Test_RTC
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_RTC(void)
{
    P0_3 = 0;
    IPL0  = 0;
    IPH0  = 0;
    DrvRTCInit();
    ExternInt1Init();
    DrvSysTimer0_Init();
    
    #if TEST_RTC_WK
    ExternInt0Init();
    #endif
    
    // clear rtc
//    RTC_WP  = 1;
//    RTC_CLR = 1;    

    // RTC Start
    RTC_WP    = 1;
    RTC_START = 1;

    g_bRtcFlag  = FALSE;
    
    #if 1
//    P0_7 = 1;
//    DelayUs(1);
    P0_7 = 0;
    #endif

    while (1)
    {     
        #if TEST_RTC_WK
        RTC_CNT_WKEN = 1;  // RTC wake en  
        #endif 
      
        g_bWKsrcOut = 1;
//        DBG_RTC("\n\rRTC init time=%dms",m_usCnt);  

        //idle_mode
        #if  IDLE_MODE
        DBG_RTC("\nj");
        DelayMs(1);
        DrvSysPowerIdle();
        DBG_RTC("\ne");        
        #endif

        //standby_mode
        #if STANDBY_MODE
        DBG_RTC("\njoin in Standby");
        //DelayMs(50);    
        DrvSysPowerStandby();
        DBG_RTC("\n exit power");
        #endif
        
        //stop_mode
        #if STOP_MODE
        DBG_RTC("\njoin in Stop");
        //DelayMs(50);        
        DrvSysPowerStop();
        DBG_RTC("\nexit power");        
        #endif
        
        while (!g_bRtcFlag)
        {
            P0_2 = 1;
            P0_2 = 0;
        }
        DBG_RTC("\n=%dms",m_usCnt);   
        m_usCnt = 0;
//        RTC_WP    = 1;
//        RTC_START = 1;
//        DelayMs(5);
//        m_usCnt = 0;
        if (g_bRtcFlag && g_bWKsrcOut == FALSE)
        {
            DBG_RTC("\n\rWK src:%x",g_nWKsrc);
        }
    //DelayMs(2000);
    }
}
#endif



