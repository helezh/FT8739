/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: main.c
*
*    Author: tangsujun
*
*   Created: 2016-12-22
*
*  Abstract:
*
* Reference:
*
* Version: 0.1
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "CfgGlobal.h"
#include "Drv_mcu.h"
#include "DrvCalCrc.h"

#include "SPI_flash.h"
#include "Task_main.h"
#include "Task_hcomm.h"
#include "Task_spi0.h" 
#include "DrvTimer.h"
#include "uart.h"
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

void test_pram(UINT8 far *ptr8,UINT32 len, UINT8 test_cnt);

/*************************************************************/

UINT8 Bus_I2C_SPI0;//0 I2C 1 SPI0

UINT8 g_ucFlashMode;  // 有无flash选择

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
/******************************************************************************
*
*   Name: ExternInt0Init
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
void ExternInt0Init(void)
{
    IT0   = 0;

    //IPL0  = 0;  /* interruption priority */
    //IPH0  = 0;  /* interruption priority */
      /* Int0优先级设置为3---唤醒要求 */
    //IPLX0 = 0;
    //IPHX0 = 1;

    //Uart_IPL = 1;
    XBUSCKEN = 1;
    LCD_RELOAD_FLASH_WKEN =1;
    EX0 = 1;


    
}
/*******************************************************************************
*   Name: GetRSTstate
*  Brief:
* 功能:获得复位状态
*      1. 上电复位
*      2. pin脚复位
*      3. soft复位/wtd复位
*      4. 升级标志
*  Input:
* Output:
* Return:
*******************************************************************************/
void GetRSTstate()
{
    //复位类型
    if (POR_STA == 0x01)
    {
        g_nRSTtype  = RST_POR; //;1硬件复位，0软件复位
        DBG_RST("\nRST_POR");
        #if _TEST_FLASH_LOAD_EN
            (*load_cnt)  = 0;
            (*load_ok)   = 0;
            (*load_err)  = 0;
        #endif
    }
    else
    {
        //pin 脚复位
        if (RST_STA == 0x00)
        {
            g_nRSTtype  = RST_PIN;
            DBG_RST("\nRST_PIN");
            
        #if _TEST_FLASH_LOAD_EN
            (*load_cnt)  = 0;
            (*load_ok)   = 0;
            (*load_err)  = 0;
        #endif
            
        }
        //app\HOST修改，用于识别升级命令
        else if (RST_STA == RST_VALUE_UPGRADE)
        {
            g_nRSTtype   = RST_UPGRADE;
            g_ucSysState = S_MCU_WAIT;
            DBG_RST("\nRST_UPGRADE");
        }
        //软件复位
        else
        {
            g_nRSTtype  = RST_SOFT;
            DBG_RST("\nRST_SOFT");
        }
    }
    //--------------------------------------------------------------------------
    RST_STA = 0xAA;  // 系统运行过程，寄存器值
    POR_STA = 0;
}

/*******************************************************************************
*   Name: init_mcu
*  Brief:
* 功能:
*  Input:
* Output:
* Return:
*******************************************************************************/
void init_mcu(void)
{

    IEN0 =0;
    AIE  =0;
    SYSCKEN = 1;
    //CGUCON4 =0;
    CLKEN_TP4_500k = 1;    
    CLKEN_500K = 1;      // 500k时钟开启 
    
    
    
    // 1.IO口初始化
    DrvIOInit();

    // 2.获得复位状态
    GetRSTstate();
    
    DrvUartInit();
    Bus_I2C_SPI0=BUS_SEL;
   
    /* Initial I2C as slave */
    DrvHostInterfaceInit();   
    SPI0_Init();
    DrvTimer0Init();
    
    
    g_ucFlashMode =! P1_6;//
    
    // SPI接口初始化
    SPI_Init();    
    DrvFwConfigInit(); 
    EA = 1;

    //while(0)
    //{
    //    CAL_Check((UINT16)APP_ADDR_PART1_START,0x7fff,CRC_TYPE_PRAM);    
    //}
    
    if(g_ucFlashMode)
    {
        
        DrvPrepareLcdInitCode();
        
    }
    
    
    
    
    
    DBG_FLOW("\ng_nRSTtype =%02x ",g_nRSTtype);
    DBG_FLOW("\n g_ucFlashMode =%02x ",g_ucFlashMode);
    //DBG_FLOW("\n g_usAppStartAddr =%lx ",g_usAppStartAddr);
    //g_usAppStartAddr=0xffccddee;

    wait_printf_done();
    ExternInt0Init();
}
/*******************************************************************************
*   Name: main
*  Brief:
* 功能:
*  Input:
* Output:
* Return:
*******************************************************************************/
void main(void)
{
    UINT8 k=0;
    init_mcu();  

    #if _TEST_FLASH_LOAD_EN
    test_pram();
    #endif
    main_task_flash();
    DBG_FLOW("\nWAIT\n");
    while (1)
    {
        #if  _TEST_PRAM_EN
    //    test_pram(0x20,8,0);
        #endif
    }
}

/*******************************************************************************
*   Name: INT0_IRQHandler
*  Brief:
* 功能:
*  Input:
* Output:
* Return:
******************************************************************************/
void INT0_IRQHandler(void) interrupt 0
{

    if(LCD_RELOAD_FLASH)
    {     
        LCD_RELOAD_FLASH_WKEN =0;
        AppLcdInitCodeReload();
        LCD_RELOAD_FLASH_WKEN =1;
    }
}
    
/*******************************************************************************
*   Name: test_pram
*  Brief:
* 功能:
*  Input:
* Output:
* Return:
******************************************************************************/
#if  _TEST_PRAM_EN
void test_pram(UINT8 far *psrc,UINT32 len,UINT8 test_cnt)//55byte
{
    UINT8 far *ptr8=0;    
    UINT8  temp=0x5a;
    UINT8  k=0;
    UINT32 j=0; 
    
    
    for(k=0; k<test_cnt; k++)
    {
        INTOUT ^=1;
        ptr8 =  psrc;    
        temp^=0xff;
        for(j=0; j<(len); j++)
        {
            *ptr8=temp;
            if(*ptr8++  !=temp)
            {    
                INTOUT =0;
                HOLD;
            }                
        }
        
    }
    INTOUT =1;
    //HOLD;

}

#endif





