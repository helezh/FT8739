/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: CommHost.c
*
*    Author: Wu Bo Zhong (Michael)
*
*   Created: 2013-01-01
*
*  Abstract: Just provide an interface for high layer of flow to initialize
*            the module communicats with host.
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* Included header files
*******************************************************************************/
#include <intrins.h>
//#include "FT8836.h"
#include "DrvSysCtrl.h"
#include "FT8836_Reg.h"
#include "FlowFactory.h"

#if 1
/*******************************************************************************
* Private constant and macro definitions using #define
*******************************************************************************/
#if _PRAM_UPGRADE_EN
/* upgrade flag */
#define UPGRADE_FLAGA           0x66
#define UPGRADE_FLAGB           0xbb
#endif
#define RTC_MS        32
#define RTC_N_MS     (RTC_MS*14)
/*******************************************************************************
* Private enumerations, structures and unions using typedef
*******************************************************************************/


/*******************************************************************************
* Static variables
*******************************************************************************/

/*******************************************************************************
* Global variable or extern global variabls/functions
*******************************************************************************/
UINT8 XRAM g_ucSysClk = 0;              /* 系统时钟，ms加一次 */
UINT8 XRAM g_ucFramTime = 100;          /* 一帧的工作时间 */
UINT8 XRAM g_ucFramCnt  = 0;            /* monitor-->active,后的帧计数 */
BOOLEAN g_bRtcTimeFlg = FALSE;          /* RTC 计时到标志 */

/* Test */
UINT8  XRAM g_ucINT0src  = 0;

/*******************************************************************************
* Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: DrvSysClkInit
*  Brief: Initialize system clock based on ucflag
*  Input: UINT8 ucflag
* Output: None
* Return: None
*******************************************************************************/
void DrvSysClkInit(UINT8 ucDiv)
{
    if (ucDiv < 8)
    {
        /* main clk = 48M/(div+1) */     
        CGUCON4 =  ucDiv;
    }    

    //OSC48M_EN = 1;	   //该寄存器已删
    SYSCKEN = 1;
 
    /*WDT,CNT,TIMER会用到*/
    CLKEN_500K = 1; 
    WDT_500K_EN = 1;
}

/*******************************************************************************
*   Name: DrvSysPowerMode
*  Brief: Select system power saving mode
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvSysPwrSel(UINT8 pmode)
{    
    /* IDLE mode */
    if (pmode == 0)
    {
        CORE_IDLE = 1;
        EA = 1;
    }
    
    /* Stop mode */
    if (pmode == 1)
    {
        CLK_WP = 1;
        STANDBY = 0;
        CORE_STOP = 1;
        EA = 1;
    }
    
    /* Standby mode */
    if (pmode == 2)
    {            
        CLK_WP = 1;
        STANDBY = 1;
        CORE_STOP = 1;
        EA = 1;
    }
    _nop_();
    _nop_();
    _nop_();
    _nop_();        
}

/*******************************************************************************
*   Name: DrvSysPortInit
*  Brief: Initialize system GPIO Port
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvSysPortInit(void)
{

#if 0
    P0MOD &= 0x7F;
    P0DIR &= 0x7F;
    P0SEL |= 0x80;
    P0DIR |= BITn(6);
    P0SEL |= BITn(6); 
#else
    P0MOD = 0x00;
    P0DIR = 0xFF;
    P0SEL = 0xFF;
    P1MOD = 0x00;
    P1DIR = 0xFF;
    P1SEL = 0xFF;
#endif
}

#if _PRAM_UPGRADE_EN
/*******************************************************************************
*   Name: DrvGoToUpgrade
*  Brief: Wirte Upgarade Flag into RST_STA,then software reset to upgrade firware
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvGoToUpgrade(void)
{
    RST_STA = RST_VALUE_UPGRADE;
    SFTRST  = 0xff;
}

#endif //_PRAM_UPGRADE_EN

/*******************************************************************************
*   Name: DrvSwReset
*  Brief: Software reset.
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvSwReset(void)
{
    SFTRST  = 0xff;
}

#if _DELAY_MS_EN
/*******************************************************************************
*   Name: DelayUs
*  Brief: delay some us, internal NOP number varies related with main clock
*  1.不同主频不一样，如果时间要求严，需要示波器测试
*  Input: UINT8 ucDlyCnt => maximum delay is 255 us
* Output: None
* Return: None
*******************************************************************************/
void DelayUs(UINT8 ucDlyCnt)
{
#if !_BLK_DBG_EN
    return;
#endif

    while (ucDlyCnt--)
    {
    #if _COMPILE_PLATFORM == PLATFORM_251
        _nop_();
        _nop_();
        _nop_();
        _nop_();

        _nop_();
        _nop_();
        _nop_();
        _nop_();

        _nop_();
        _nop_();
        _nop_();
        _nop_(); 

        _nop_();
        _nop_();
        _nop_();        
    #endif
    }
}

/*******************************************************************************
*   Name: DelayUs
*  Brief: delay some ms
*  Input: UINT8 ucDlyCnt => maximum delay is 255 ms
* Output: None
* Return: None
*******************************************************************************/
void DelayMs(UINT16 ucDlyCnt)
{
    while (ucDlyCnt--)
    {
        DelayUs(250);
        DelayUs(250);
        DelayUs(250);
        DelayUs(250);
    }
}
#endif

/*******************************************************************************
*   Name: DrvIntPriority
*  Brief: Config priority of interrupts
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvIntPriority(void)
{

    //优先级--先清0
    IPH0 = 0x00;
    IPL0 = 0x00;
    AIPH = 0x00;
    AIPL = 0x00;     

    /* Int0优先级设置为3---唤醒要求 */ 
    IPHX0 = 1;
    IPLX0 = 1; 

    /* 通信优先 设置为2 */    
    I2C_IPH = 0;
    I2C_IPL = 1; 

    I2C_STOP_IPH = 1;
    I2C_STOP_IPL = 0;      

    // Time0优先级设置为2---incell方案时需要考虑
    IPHT0 = 0;
    IPLT0 = 1;  

    ET2 = 1;

#if _BLK_DBG_EN    
    // uart优先级设置为2--低优先级中断中不能使用串口
    Uart_IPH = 1;
    Uart_IPL = 1; 
#else
    Uart_IPH = 0;
    Uart_IPL = 0;
#endif
}


void Drv_Rtc_Init(UINT8 ucMode)
{
    // 32K时钟使能
    
    CLK_WP = 1;
    EN_32K = 1;
    RTC_32K_EN = 1;
  
    // rtc clk enable
    RTCCKEN = 1;
    
    // clear rtc
    RTC_WP  = 1;
    RTC_CLR = 1;

    // 设置RTC计数时间
    RTCIVH  = RTC_N_MS/256;
    RTCIVL  = RTC_N_MS%256;

    if(ucMode == 0)
    {
        RTC_AUTO_MODE = 1;
        LCD_START_EN = 0;
    }
    else
    {
        RTC_AUTO_MODE = 0;
        LCD_SRC_SEL_H = 0;//vstart
        LCD_SRC_SEL_L = 0;
    }
    
    
    //RTC中断作为中断0
    RTC_INT_EN_ASM = 1;      // select rtc
    RTC_INT_EN_CPU = 1;
    
    //int1 init
    IT1 = 0;   // 0:LOW level triggered 1:falling edge

    IPHX1 = 1;
    IPLX1 = 1;    
    EX1 = 1;
  
#if 0
    Uart_IPL = 0;
    Uart_IPH = 0;
#endif

    EA = 1;    
}



/*******************************************************************************
*   Name: Exint0_IRQHandler()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Exint0_IRQHandler(void) interrupt 0
{
    g_ucState0 = IWKSTA;

    if (ASM_MON_WKEN)
    {
        if (ASM_MON_INT)
        {
            DBG_INT("\nASM WKEN");
            g_ucState0 = IWKSTA;
            ASM_MON_WKEN = 0;
        }
    }

    if (LCD_RELOAD_FLASH_WKEN)
    {
        if (LCD_RELOAD_FLASH)
        {
            g_ucState0 = IWKSTA;
            LCD_RELOAD_FLASH_WKEN = 0;
        }
    }

    if (RTC_CNT_WKEN)
    {
        if (RTC_CNT_INT)
        {
            RTC_CNT_WKEN = 0;
        }
    }

    if (I2C_MON_WKEN)
    {
        if (I2C_MON_INT)
        {
            I2C_MON_WKEN = 0;
        }
    }
    if (LCD_ESD_WKEN)
    {
        if (LCD_ESD_WK_INT)
        {
           
//            LCD_ESD_WKEN = 0;
            g_ucAbnormalFlag |= 0x01;
            
            //DBG_FLOW("\nESD %d",LCD_ESD_PHASE);//该寄存器已删除
            //LCD_ESD_PHASE =~LCD_ESD_PHASE;     //该寄存器已删除
            
        }
    }
    if (LCD_LVD_WKEN)
    {
        if (LCD_LVD_WK_INT)
        {
            //LCD_LVD_WKEN = 0;
            g_ucAbnormalFlag |= 0x02;
            
            //DBG_FLOW("\nLVD %d",LCD_LVD_PHASE);  //该寄存器已删除
            //LCD_LVD_PHASE =~LCD_LVD_PHASE;	   //该寄存器已删除
        }
    }

    if (LCD_TIM_WKEN)
    {
        if (LCD_GPIO_WK_INT)
        {
            LCD_TIM_WKEN = 0;
            DBG_FLOW("\nLCD TIM");
        }
    }
    DBG_FLOW("\nint0:%x",IWKSTA);
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
    while(RTC_START_STA == 0);
    //清rtc
    RTC_WP  = 1;
    RTC_CLR = 1;
    //RTC_START = 1;

    DBG_FLOW("\nint1");
}
#endif


