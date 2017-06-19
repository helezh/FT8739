/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: test_gpio_wakeup.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-25
*
*  Abstract:
*
* Reference:
*   Version: 0.2
*
*******************************************************************************/
/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "test_gpio_wakeup.h"

#if _TEST_GPIO_WK_EN//得重新写
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*     1. 中断0必须设成低电平触发，边沿不能唤醒无效
*     2. stop standby必须把中断0的优先级设为最高
*     3. INT0_P06固定低电平唤醒
*******************************************************************************/
//#define INT0_P06_WK_EN       1
//#define INT0_INCELL0_WK_EN   0
//#define INT0_INCELL1_WK_EN   0
//#define INT0_INCELL2_WK_EN   0
//#define INT0_RELOAD_WK_EN    0

#define INT0_P06_WK_EN       1
#define INT0_P07_WK_EN       0
#define INT0_LCD_ESD_WK_EN   0
#define INT0_LCD_LVD_WK_EN   0
#define INT0_LCD_RELOAD_WK_EN   0

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
//UINT8 CROM gpio_56K_code[40960+6000+1024*4+52-7*16];
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT8   g_nWKsrc   = 0;
UINT16  g_nINT0cnt  = 0;
BOOLEAN g_bInt0Flag = 0;
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

#if 0//INT0_LCD_ESD_WK_EN
/*******************************************************************************
*   Name: DrvIncell0Init
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvIncell0Init(void)
{
    LCD_SYNC_MISS = 1;
    LCD_SYNC_MISS_IF = 0;
    LCD_SYNC_MISS_EI = 1;
}
#else 
#define DrvIncell0Init  /##/
#endif

#if 0//INT0_LCD_LVD_WK_EN
/*******************************************************************************
*   Name: DrvIncell1Init
*  Brief: lcd sync 60Hz
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvIncell1Init(void)
{
    LCD_SYNC_60HZ = 1;
    LCD_SYNC_60HZ_IF = 0;
    LCD_SYNC_60HZ_EI = 1;

    TP_120HZ_REQ = 0x01; // 向lcd请求120Hz mode
}
#else 
#define DrvIncell1Init  /##/
#endif

#if 0//INT0_INCELL2_WK_EN
/*******************************************************************************
*   Name: DrvIncell2Init
*  Brief: lcd run
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvIncell2Init(void)
{
    INCELL2 = 1;
    ES = 1;
}
#else 
#define DrvIncell2Init  /##/
#endif

#if 0//INT0_RELOAD_WK_EN
/*******************************************************************************
*   Name: DrvLcdReloadFlashInit
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvLcdReloadFlashInit(void)
{
    LCD_RELOAD_FLASH_IF = 0;
    LCD_RELOAD_FLASH_EI = 1;
}
#else 
#define DrvLcdReloadFlashInit  /##/
#endif

/*******************************************************************************
*   Name: ExternInt0Init()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void ExternInt0Init(void)
{
#if INT0_P06_WK_EN
    P0MOD |= BITn(6);
    GPIO_WKEN = 1;
    GPIO_INT_SEL = 0;
#endif

#if INT0_P07_WK_EN
    P0MOD |= BITn(7);
    GPIO_WKEN = 1;
    GPIO_INT_SEL = 1;
#endif

#if 0//INT0_INCELL0_WK_EN
    LCD_SYNC_MISS_WKEN = 1;
#endif

#if 0//INT0_INCELL1_WK_EN
    LCD_SYNC_60HZ_WKEN = 1;
#endif

#if 0//INT0_INCELL2_WK_EN
    LCD_RUN_WKEN = 1;
#endif

    IT0   = 0;    // 0:low level triggered 1:falling edge

    IPL0  = 0;
    IPH0  = 0;

    IPLX0 = 1;
    IPHX0 = 1;    // 中断0优先级必须最高

    EX0 = 1;
    EA  = 1;
}
/*******************************************************************************
*   Name: Test_Int0Wakeup()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Int0Wakeup(void)
{
    DrvIncell0Init();
    DrvIncell1Init();
    DrvIncell2Init();
    DrvLcdReloadFlashInit();
    ExternInt0Init();

    while (1)
    {
        DBG_GPIOWK("\nstart...");
        DelayMs(100);
        EA = 0;

#if 0        
    #if INT0_P06_WK_EN
        //P06PHASE = 1;
        GPIO_WKEN = 1;
    #endif
    #if INT0_INCELL0_WK_EN
        LCD_SYNC_MISS_WKEN = 1;
    #endif
    #if INT0_INCELL1_WK_EN
        LCD_SYNC_60HZ_WKEN = 1;
    #endif
    #if INT0_INCELL2_WK_EN
        LCD_RUN_WKEN = 1;
    #endif
#endif

#if INT0_P06_WK_EN || INT0_P07_WK_EN
        GPIO_WKEN = 1;
#endif

#if INT0_LCD_ESD_WK_EN
        LCD_ESD_WKEN = 1;
#endif
#if INT0_LCD_LVD_WK_EN
        LCD_LVD_WKEN = 0;
#endif
#if INT0_LCD_RELOAD_WK_EN
        LCD_RELOAD_FLASH_WKEN = 1;
#endif
        g_bInt0Flag = FALSE;
        DrvSysPowerIdle();
        //DrvSysPowerStandby();
        //DrvSysPowerStop();
        DBG_GPIOWK("\nexit Power");
        while (!g_bInt0Flag);
        DBG_GPIOWK("\nWK src:%X,cnt=%d",g_nWKsrc,g_nINT0cnt);
        g_nWKsrc = 0x00;
        DelayMs(1000);
    }
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
	g_nWKsrc  = IWKSTA;
    g_bInt0Flag = TRUE;
    #if INT0_P06_WK_EN|INT0_P07_WK_EN
        GPIO_WKEN = 0;
    #endif
    #if 0//INT0_INCELL0_WK_EN
        LCD_SYNC_MISS_WKEN = 0;
    #endif
    #if 0//INT0_INCELL1_WK_EN
        LCD_SYNC_60HZ_WKEN = 0;
    #endif
    #if 0//INT0_INCELL2_WK_EN
        LCD_RUN_WKEN = 0;
    #endif
    g_nINT0cnt++;
    DBG_GPIOWK("\nint0");
}

#if 0//INT0_INCELL0_WK_EN
/*******************************************************************************
*   Name: LCD_SYNC_MISS_IRQHandler
*  Brief: lcd sync miss
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void LCD_SYNC_MISS_IRQHandler(void) interrupt  13
{
    LCD_SYNC_MISS_IF = 0;

    if (LCD_SYNC_MISS)
    {
        LCD_SYNC_MISS = 0;
        DBG_FLOW("\nlcd sync miss in");
    }
    else
    {
        LCD_SYNC_MISS = 1;
        DBG_FLOW("\nlcd sync miss out");
    }
}
#endif

#if 0//INT0_INCELL1_WK_EN
/*******************************************************************************
*   Name: LCD_SYNC_60HZ_IRQHandler
*  Brief: lcd sync 60Hz
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void LCD_SYNC_60HZ_IRQHandler(void) interrupt  9
{
    LCD_SYNC_60HZ_IF = 0;

    if (LCD_SYNC_60HZ == 0)
    {
        DBG_FLOW("\nlcd sync 60Hz");
    }
    LCD_SYNC_60HZ = ~LCD_SYNC_60HZ;
}
#endif

#if 0//INT0_INCELL2_WK_EN
/*******************************************************************************
*   Name: INCELL2_IRQHandler
*  Brief: lcd run
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void INCELL2_IRQHandler(void) interrupt  4
{
    if (INCELL2)
    {
        INCELL2 = 0;
        DBG_FLOW("\nINCELL2_High");
    }
    else
    {
        INCELL2 = 1;
        DBG_FLOW("\nINCELL2_low");
    }
}
#endif

#if 0//INT0_RELOAD_WK_EN
/*******************************************************************************
*   Name: LcdReloadFlash_IRQHandler
*  Brief: lcd run
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void LcdReloadFlash_IRQHandler(void) interrupt  11
{
    LCD_RELOAD_FLASH_IF = 0;

    if (LCD_RELOAD_INT)
    {
        DBG_FLOW("\nlcd reloadflash");
    }
}
#endif

#endif
