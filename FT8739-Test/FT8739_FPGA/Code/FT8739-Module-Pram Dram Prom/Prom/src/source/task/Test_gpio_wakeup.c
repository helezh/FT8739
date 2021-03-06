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

#if INT0_LCD_ESD_WK_EN
    LCD_ESD_WKEN = 1;
#endif
#if INT0_LCD_LVD_WK_EN
	LVD_VDDI_EN = 1;//只有使能这三个信号，发生LVD才会用LVD中断来
	LVD_AVEE_EN = 1;
	LVD_AVDD_EN = 1;

    LCD_LVD_WKEN = 1;
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
    ExternInt0Init();

    while (1)
    {
        DBG_GPIOWK("\nstart...");
        DelayMs(100);
 

#if INT0_P06_WK_EN || INT0_P07_WK_EN
        GPIO_WKEN = 1;
#endif


#if INT0_LCD_RELOAD_WK_EN
        LCD_RELOAD_FLASH_WKEN = 1;
#endif
        g_bInt0Flag = FALSE;
        //DrvSysPowerIdle();
        //DrvSysPowerStandby();
        DrvSysPowerStop();
        DBG_GPIOWK("\nexit Power");
        while (!g_bInt0Flag);
        DBG_GPIOWK("\nWK src:%X,cnt=%d",g_nWKsrc,g_nINT0cnt);
        DelayMs(1000);
        g_nWKsrc = 0x00;		
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

    DBG_GPIOWK("\nIWKSTA:%02x",IWKSTA);

	
    #if INT0_P06_WK_EN|INT0_P07_WK_EN
        GPIO_WKEN = 0;
    #endif

	if(LCD_ESD_WK_INT)
	{
		ESD_INT_CLR = 1;
		//while(ESD_STA);
	}

	if(LCD_LVD_WK_INT)
	{
		LVD_INT_CLR =1;
	}
	
    g_nINT0cnt++;

}

#endif
