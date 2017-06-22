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
#include "Test_WDT.h"

#if _TEST_WDT_EN
/******************************************************************************
*
* 2.Private constant and macro definitions using #define
*******************************************************************************/
//time0
#define T0MODE                            0x02    //高四位为T1,低四位为T0
#define IRQTIME0_VALUE                    1       //(MS)
#define IRQTIME0_LOAD()                   do{TMOD |= T0MODE;TH0 = IRQTIME0_VALUE;TL0 = 0;}while(0)

#define PRESCALE_24                       0       // 1:24个cycle计数一次;0:384个cycle计数一次

//WDT 定时数 110ms、400ms、25.2S
#define CNT_WDT_MS  110

#if PRESCALE_24
#define WDT_MS(n)  ((0x7FFC-(UINT32)(n)*1000/48)&0x00FF) > 0x0080?(((0x7FFC-(UINT32)(n)*1000/48)>>8)+1):((0x7FFC-(UINT32)(n)*1000/48)>>8)
#else
#define WDT_MS(n)  ((0x7FFC-(UINT32)(n)*1000/768)&0x00FF) > 0x0080?(((0x7FFC-(UINT32)(n)*1000/768)>>8)+1):((0x7FFC-(UINT32)(n)*1000/768)>>8)
#endif

// TEST_POWER_MANAGE:0-Idle;1-Standby;2-Stop;3-none
#define TEST_POWER_MANAGE   2
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
UINT16 m_usCnt = 0;

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

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
* Name: DrvSysTimerInit
* Brief:  系统定时器初始化
* Input:
* Output:
* Return:
*******************************************************************************/
void DrvSysTimer0_Init(void)
{
    TR0 = 0;
    IRQTIME0_LOAD();        //1
    TR0 = 1;
    ET0 = 1;
}

/*******************************************************************************
* Name: WDT_int
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void WDT_int(void)
{
    WDT_INT_IF = 0;
    WDT_INT_EI = 1;
}

/*******************************************************************************
* Name:WDT_Init
* Input:
* Output:
* function:
*  1.WTD时钟默认为 fclk = 500KHZ固定，一个时间周期是2us
*  2.溢出时间 (0x7FFC - 0xXX00)*2*12*2us
*  3.最小最大值12.096ms(0xFC*2*12*2us)~25.2S(0x7FFC*2*12*2us*16)
********************************************************************************/
void WDT_Init(void)
{
    WDT_500K_EN = 1; //wdt clk
    WDTSTARTEN = 1;     //start en = 1

    /* 时钟计数: 只配置高7位，低8位固定为0 
    wdtrel[7]  1: 每384  个cycle  计数一次
               0: 每  24  个cycle  计数一次*/

#if 0	
    //WDTREL = 0x5E;//0x77;
    WDTREL = 0x60;//0x7E;
    /* 16倍分频器使能 */
    WDTREL |= 0x00;
#else
    WDTREL = WDT_MS(CNT_WDT_MS);
#if PRESCALE_24
    WDTREL &= 0x7F;
    DBG_WDT("\nReal WDT time:%dms",(UINT32)(0x7FFC - (WDTREL<<8))*48/1000);
#else
    WDTREL |= 0x80;
    DBG_WDT("\nReal WDT time:%dms",(UINT32)(0x7FFC - ((WDTREL&0x7F)<<8))*768/1000);
#endif
    DBG_WDT("\nWDTREL:%02x",WDTREL);
#endif
    WDT  = 1;           //刷新计数器值
    SWDT = 1;           //启动wdt计数

    WDT_int();
}

/*******************************************************************************
* Name:WDT_Feed
* Input:
* Output:
* function:
********************************************************************************/
void WDT_Feed(void)
{
    WDT  = 1;  //刷新计数器值
    SWDT = 1;  //启动wtd计数
}

/*******************************************************************************
* Name:WDT_Stop
* Input:
* Output:
* function:
********************************************************************************/
void WDT_Stop(void)
{
    WDTSTOPEN = 1;  //stop en = 1
    SWDT = 0;       //停止wdt计数
}

/*******************************************************************************
* Name:Task_WDT
* Input:
* Output:
* function:
*********************************************************************************/
void Test_WDT(void)
{
    UINT8  i = 0;
#if 0
    DBG_MODE("\n\rWDT Test is start");
    DelayMs(2000);
#else    
    DrvSysTimer0_Init();

#endif
    WDT_Init();
    m_usCnt = 0;

    while (1)
    {

        if (WDTACT)
        {
            DBG_WDT("\n\rWDT run");
            DelayMs(10);
        }
        else
        {
            DBG_WDT("\n\rWDT not run");
            DelayMs(10);        
        }    
        #if TEST_POWER_MANAGE < 3
        DBG_MODE("\n\rPWR in");
        DelayMs(100);
        #if TEST_POWER_MANAGE == 0
        DrvSysPowerIdle();
        #elif TEST_POWER_MANAGE == 1
        DrvSysPowerStandby();
        #elif TEST_POWER_MANAGE == 2
        DrvSysPowerStop();
        #endif
        DBG_MODE("\n\rPWR out");
        DelayMs(10);
        #else
        DBG_MODE("\n\rwhile running");
        DelayMs(10);
        #endif
        DelayMs(5000);
    }
    DBG_MODE("\n\rWDT Test is end");
}

/*******************************************************************************
* Name      : WDT_IRQHandler
* Input     :
* Output    :
* function  : WDT 中断响应函数
********************************************************************************/
void WDT_IRQHandler(void) interrupt  12
{

    WDT_Feed();
    //DBG_WDT("\n\rWDT %dms",m_usCnt);
    m_usCnt = 0;
//    WDT_Stop();
}

#endif

