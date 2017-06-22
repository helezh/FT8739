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
#define RTC_N_MS     (RTC_MS*100)//100ms

/*
 * Normal   :此时CPU启动RTC，RTC产生一次定时中断，计时时间与计数Counter相关
 * Slot     :此时CPU启动RTC，若打开wake_sub_en，则RTC会产生slot_num+1个中断给CPU Cancel
 * Auto     :此时CPU启动一次RTC，产生一次RTC中断给CPU，产生无限次中断给ASM，
             直到CPU CLR RTC
 * LCD Start:此时RTC会根据LCD信号启动，在Counter中间会自动屏蔽LCD的start
             信号
*/

//RTC MODE 0-Normal,(1-Slot),2-Auto,3-Lcd Start
#define RTC_MODE    0

/* time0 */
#define T0MODE                            0x02    //高四位为T1,低四位为T0
#define IRQTIME0_VALUE                    1       //(MS)
//#define IRQTIME0_LOAD()                   TMOD|=T0MODE;TH0=IRQTIME0_VALUE;TL0=0 old
#define IRQTIME0_LOAD()                   TMOD|=T0MODE;TH0=IRQTIME0_VALUE;TL0=0

#define TEST_RTC_WK                       0//0:不测试rtc wk；1 测试rtc wk
#define INT1_TRI_MODE                     0// 0:LOW level triggered 1:falling edge

//#define AUTO_MODE                         1//0:不开启Auto_mode  1:开启Auto_Mode
#define RTC_SLOT_NUM                      9
#define RTC_SLOT_NUM_NONE                 0
#define TEST_WAKE_EN_SUB                  0

//设置LCD Start信号源--0--Vstart,1--Vmid;2--Vend;3--Vblank
#define LCD_START_SRC   0

//以下三种模式最多只能进入一种
#define IDLE_MODE                         0//0:不进入idle   1:进入idle
#define STANDBY_MODE                      0//0:不进入standy 1:进入standy
#define STOP_MODE                         0//0:不进入stop   1:进入stop

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

    // clear rtc
    RTC_WP  = 1;
    RTC_CLR = 1;
    //DelayMs(100);

    // 设置RTC计数时间
    RTCIVH  = RTC_N_MS>>8;
    RTCIVL  = RTC_N_MS;

    //Normal mode
    #if (RTC_MODE == 0)
    RTC_AUTO_MODE = 0;
    LCD_START_EN  = 0;
    #endif

#if 0
    //Slot mode
    #if (RTC_MODE == 1)
//    RTCSLN          = RTC_SLOT_NUM;
    RTC_AUTO_MODE   = 0;
    LCD_START_EN    = 0;
    #endif
#endif

    //Auto mode
    #if (RTC_MODE == 2)
    RTC_AUTO_MODE   = 1;
    LCD_START_EN    = 0;
    #endif

    //LCD Start mode
    #if (RTC_MODE == 3)
    #if (LCD_START_SRC == 0)
    RTCCON1 |= 0x00;
    #elif (LCD_START_SRC == 1)
    RTCCON1 |= 0x02;
    #elif (LCD_START_SRC == 2)
    RTCCON1 |= 0x04;
    #elif (LCD_START_SRC == 3)
    RTCCON1 |= 0x06;
    #endif
    RTC_AUTO_MODE = 0;
    LCD_START_EN = 1;
    #endif

    #if TEST_RTC_WK
    RTC_CNT_WKEN = 1;  // RTC wake en  
    #endif

    //RTC中断使能
    RTC_INT_EN_CPU = 1;

#if 0
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
#endif
 
    DBG_RTC("\nRTC Interval:%dms",RTC_N_MS/RTC_MS);         // 1.8ms@115200bps total 19 character 100us per character
    DBG_RTC("\nRTC_IVH:%02X,RTC_IVL:%02X",RTCIVH,RTCIVL);
    DBG_RTC("\ninit RTC OK!");
    DelayMs(10);

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
        RTC_CNT_WKEN = 0;
        DBG_FLOW("\n\rrtc int0");
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
    P0_2 = 0;
    //如果是在AUTO模式，则不清rtc，否则一定要清RTC，不然会一直在中断中出不去
#if !(RTC_MODE == 2)
    while(RTC_START_STA == 0);
    RTC_WP  = 1;
    RTC_CLR = 1;
#endif

    DBG_FLOW("\n\rrtc int1");

    g_bRtcFlag = TRUE;

#if TEST_RTC_WK
    RTC_CNT_WKEN = 1;
#endif
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
    DrvSysTimer0_Init();
    DrvRTCInit();
    ExternInt1Init();

    #if TEST_RTC_WK
    ExternInt0Init();
    #endif

    // clear rtc
    RTC_WP  = 1;
    RTC_CLR = 1;  

    // RTC Start
    RTC_WP    = 1;
    RTC_START = 1;

    P0_2 = 1;

    while (1)
    {      
        g_bRtcFlag = FALSE;
        g_bWKsrcOut = 1;
        m_usCnt = 0;
        // RTC Start
        //RTC_WP    = 1;
        //RTC_START = 1;
        
        #if 0
        if(m_usCnt = 10)
        {
            LCD_START_EN = 0;
        }
        else if(m_usCnt = 20)
        {
            LCD_START_EN = 1;
        }
        #endif

        //idle_mode
        #if  IDLE_MODE
        DBG_RTC("\n\rjoin in Idle");
        DelayMs(50);
        DrvSysPowerIdle();
        DBG_RTC("\n\rexit Idle");        
        #endif

        //standby_mode
        #if STANDBY_MODE
        DBG_RTC("\n\rjoin in Standby");
        DelayMs(50);    
        DrvSysPowerStandby();
        DBG_RTC("\n\rexit Standby");
        #endif
        
        //stop_mode
        #if STOP_MODE
        DBG_RTC("\n\rjoin in Stop");
        DelayMs(50);        
        DrvSysPowerStop();
        DBG_RTC("\n\rexit Stop");        
        #endif
        
        while (!g_bRtcFlag);
        DBG_RTC("\nm_usCnt=%dms",m_usCnt);   
        DelayMs(10);
        
        if (g_bRtcFlag && g_bWKsrcOut == FALSE)
        {
            DBG_RTC("\n\rWK src:%x",g_nWKsrc);
        }
    }
}
#endif



