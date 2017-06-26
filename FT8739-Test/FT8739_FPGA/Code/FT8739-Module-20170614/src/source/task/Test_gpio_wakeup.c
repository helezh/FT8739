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
#include <intrins.h>

#if _TEST_GPIO_WK_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*     1. 中断0必须设成低电平触发，边沿不能唤醒无效
*     2. stop standby必须把中断0的优先级设为最高
*     3. INT0_P06固定低电平唤醒
*******************************************************************************/

#define INT0_P06_WK_EN          0
#define INT0_P07_WK_EN          0
#define INT0_LCD_ESD_WK_EN      0
#define INT0_LCD_LVD_WK_EN      0
#define INT0_LCD_RELOAD_WK_EN   0
#define INT0_ASM_WK_EN          0
#define INT0_LCD_WK_EN          1

#define INT0_LCD_BUSY_FALL           BITn(15)
#define INT0_LCD_BUSY_RISE           BITn(14)
#define INT0_LCD_PANEL_CONFLICT      BITn(13)
#define INT0_LCD_DSTB_FALL           BITn(12)
#define INT0_LCD_DSTB_RISE           BITn(11)
#define INT0_LCD_SYNC_MISS_FALL      BITn(10)
#define INT0_LCD_SYNC_MISS_RISE      BITn(9)
#define INT0_LCD_ARAM_RDY            BITn(8)
#define INT0_LCD_FRAME_END           BITn(7)
#define INT0_LCD_TCH_DET             BITn(6)
#define INT0_LCD_VSTART              BITn(5)
#define INT0_LCD_VMID                BITn(4)
#define INT0_LCD_VEND                BITn(3)
#define INT0_LCD_VBLANK              BITn(2)
#define INT0_LCD_RUN_FALL            BITn(1)
#define INT0_LCD_RUN_RISE            BITn(0)

#define INT1_HW_MON_TIMEOUT          BITn(14)
#define INT1_LCD_LPF_MODE_EN_FALL    BITn(13)
#define INT1_LCD_LPF_MODE_EN_RISE    BITn(12)
#define INT1_LCD_STB_TICK            BITn(11)
#define INT1_LCD_ODD_EVEN_FALL       BITn(10)
#define INT1_LCD_ODD_EVEN_RISE       BITn(9)
#define INT1_LCD_VDO_MODE_FALL       BITn(8)
#define INT1_LCD_VDO_MODE_RISE       BITn(7)
#define INT1_LCD_IDLE_MODE_FALL      BITn(6)
#define INT1_LCD_IDLE_MODE_RISE      BITn(5)
#define INT1_LCD_3D_MODE_FALL        BITn(4)
#define INT1_LCD_3D_MODE_RISE        BITn(3)
#define INT1_LCD_RUN                 BITn(2)
#define INT1_LCD_DSTB                BITn(1)

#define LCD_RUN_INTPHASE             BITn(15)
#define LCD_DSTB_INTPHASE            BITn(14)


#define INT0_ASM_SRC0                INT0_LCD_VSTART
#define INT0_ASM_SRC1                INT1_LCD_3D_MODE_FALL

#define INT0_LCD_SRC                 INT1_LCD_RUN//INT1_LCD_DSTB

#if 1//(INT0_LCD_SRC == INT1_LCD_RUN)
#define INT0_LCD_PHASE  LCD_RUN_INTPHASE
#elif (INT0_LCD_SRC == INT1_LCD_DSTB)
#define INT0_LCD_PHASE  LCD_DSTB_INTPHASE
#endif

#define SLEEPOUT                     DrvXbus_WriteLcd8(0x1100,0x00)
#define SLEEPIN                      DrvXbus_WriteLcd8(0x1000,0x00)


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
ST_AsmRegisters * XRAM pAsmRegs = (volatile ST_AsmRegisters *)ASM_REG_BASE_ADDR;

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
    CGUCON5 = 0;
    
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

#if INT0_LCD_RELOAD_WK_EN
    XBUSCKEN = 1;
#endif

#if INT0_ASM_WK_EN
    //DrvXbus_WriteInitCode();//写initial code,需要用lcd联调版本.
    AFEACKEN = 1;    
    AFECKEN  = 1;   
    AFESCKEN = 1;
    pAsmRegs ->usAsmIntClr0 = 0xFFFF;
    pAsmRegs ->usAsmIntClr1 = 0xFFFF;    
    pAsmRegs ->usAsmIntWakeEn0 = INT0_ASM_SRC0;
    pAsmRegs ->usAsmIntWakeEn1 = INT0_ASM_SRC1;
#endif

#if INT0_LCD_WK_EN
    AFEACKEN = 1;    
    AFECKEN  = 1;   
    AFESCKEN = 1;
    pAsmRegs ->usAsmIntClr1 = 0xFFFF;
    pAsmRegs ->usAsmIntEn1 = INT0_LCD_SRC;
    pAsmRegs->usAsmScanCfg1|= INT0_LCD_PHASE;//检测高电平
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
        //EA = 0;
#if INT0_LCD_RELOAD_WK_EN
        DrvXbus_WriteLcd8(0xfb30,0x00);
        LCD_RELOAD_FLASH_WKEN = 1;
#endif
        g_bInt0Flag = FALSE;
#if INT0_ASM_WK_EN
        ASM_MON_WKEN = 1;
#endif

#if INT0_P06_WK_EN || INT0_P07_WK_EN
        GPIO_WKEN = 1;
#endif

#if INT0_LCD_WK_EN
        LCD_TIM_WKEN = 1;
#endif
        EA = 1;
        //DrvSysPowerIdle();
        //DrvSysPowerStandby();
        DrvSysPowerStop();
        DBG_GPIOWK("\nexit Power");
        while (!g_bInt0Flag);
        DBG_GPIOWK("\nWK src:%X,cnt=%d",g_nWKsrc,g_nINT0cnt);
        
#if INT0_ASM_WK_EN
        if(g_nINT0cnt == 5)
        {
            SLEEPIN;
            DelayMs(5000);
            g_nINT0cnt = 0;
            SLEEPOUT;
        }
#endif

        DelayMs(5000);
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

    if(LCD_RELOAD_FLASH)
    {
       LCD_RELOAD_FLASH_WKEN = 0;
    }

    if(LCD_ESD_WK_INT)
    {
        ESD_INT_CLR = 1;
    }

    if(LCD_LVD_WK_INT)
    {
        LVD_INT_CLR =1;
    }

    if(ASM_MON_INT)
    {
        if((pAsmRegs->usAsmIntFlag0)&&INT0_ASM_SRC0)
        {
            pAsmRegs->usAsmIntClr0 |= 0xFFFF;//INT0_ASM_SRC0;
            
        }
        if((pAsmRegs->usAsmIntFlag1)&&INT0_ASM_SRC1)
        {
            pAsmRegs->usAsmIntClr1 |= 0xFFFF;//INT0_ASM_SRC1;
        }
        ASM_MON_WKEN = 0;
    }


    if(LCD_GPIO_WK_INT)
    {
        if ((pAsmRegs->usAsmIntFlag1)&INT0_LCD_SRC)
        {
            /* 检测高电平 */
            if(pAsmRegs->usAsmScanCfg1&INT0_LCD_PHASE) 
            {
                pAsmRegs->usAsmScanCfg1 &= (~INT0_LCD_PHASE);          // 检测低电平，                               
            }
            else
            {
                pAsmRegs->usAsmScanCfg1|= INT0_LCD_PHASE;              // 检测高电平 
            }

            pAsmRegs->usAsmIntClr1 |= INT0_LCD_SRC;
        }

        LCD_TIM_WKEN = 0;           
    }
    g_nINT0cnt++;

}

#endif
