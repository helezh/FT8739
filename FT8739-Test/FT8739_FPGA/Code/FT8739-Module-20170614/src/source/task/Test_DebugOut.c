/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_DebugOut.c
*
*    Author: 
*
*   Created: 2017-04-18
*
*  Abstract:
*
* Reference: :
* Version:
* 0.1:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_DebugOut.h"

#if _TEST_DEBUGOUT_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
typedef enum
{
	TEST_AFE_TEST_OUT_L0   = 0x00,
	TEST_AFE_TEST_OUT_L1   = 0x01,
	TEST_AFE_TEST_OUT_R0   = 0x02,
	TEST_AFE_TEST_OUT_R1   = 0x03,
	TEST_AFE_SCAN_START    = 0x04,
	TEST_AFE_STB_START     = 0x05,
	TEST_AFE_ARAM_RDY      = 0x06,
	TEST_AFE_FRAME_END_R   = 0x07,
	TEST_AFE_TP_BUSY_R     = 0x08,
	TEST_AFE_MON_DET_R     = 0x09,
	TEST_AFE_FRAME_END_L   = 0x0A,
	TEST_AFE_TP_BUSY_L     = 0x0B,
	TEST_AFE_MON_DET_L     = 0x0C,
	TEST_LCD_VSTART        = 0x0D,
	TEST_LCD_VMIN          = 0x0E,
	TEST_LCD_VEND          = 0x0F,
	TEST_LCD_VBLANK        = 0x10,
	TEST_LCD_TCON_L_VBP    = 0x11,
	TEST_LCD_TP_STANDBY    = 0x12,
	TEST_LCD_RUN           = 0x13,
	TEST_LCD_BUSY          = 0x14,
	TEST_LCD_SYNC_MISS     = 0x15,
	TEST_LCD_VDO_MODE      = 0x16,
	TEST_LCD_IDLE_MODE     = 0x17,
	TEST_LCD_3BDITHER_MODE = 0x18,
	TEST_LCD_FR_ODD_EVEN   = 0x19,
	TEST_TP_VB_MODE_REQ    = 0x1A,
	TEST_LCD_VB_MODE_ACK   = 0x1B,
	TEST_LCD_LPF_MODE_EN   = 0x1C,
	TEST_TP_LPF_MODE_REQ   = 0x1D,
	TEST_LCD_LPF_MODE_ACK  = 0x1E,
	TEST_LCD_WR_ENABLE     = 0x1F,
	TEST_TP_XBUS_AEN       = 0x20,
	TEST_TP_XBUS_REN       = 0x21,
	TEST_TP_XBUS_DEN       = 0x22,
	TEST_LCD_RELOAD_START  = 0x23,
	TEST_TP_RELOAD_END     = 0x24,
	TEST_TP_RELOAD_ABORT   = 0x25,
	TEST_LCD_DSTB          = 0x26,
	TEST_LVD_MASK          = 0x27,
	TEST_BGP_MASK          = 0x28,
	TEST_VDD_TP_MASK_N1    = 0x29,
	TEST_VDD_TP_MASK_N2    = 0x2A,
	TEST_VDD_TP_MASK_N3    = 0x2B,
	TEST_AFE_POWERGATING_L = 0x2C,
	TEST_VREFBG_EN_L       = 0x2D,
	TEST_VREFTP_EDTOP_EN_L = 0x2E,
	TEST_VREFTP_BUF_EN_L   = 0x2F,
	TEST_VREFTP_SH_L       = 0x30,
	TEST_VREFTP_SRCTRL_L   = 0x31,
	TEST_VDD5_SETOP_EN_L   = 0x32,
	TEST_VDD5_BUF_EN_L     = 0x33,
	TEST_VDD5_SRCTRL_L     = 0x34,
	TEST_AFE_POWERGATING_R = 0x35,
	TEST_VREFBG_EN_R       = 0x36,
	TEST_VREFTP_EDTOP_EN_R = 0x37,
	TEST_VREFTP_BUF_EN_R   = 0x38,
	TEST_VREFTP_SH_R       = 0x39,
	TEST_VREFTP_SRCTRL_R   = 0x3A,
	TEST_VDD5_SETOP_EN_R   = 0x3B,
	TEST_VDD5_BUF_EN_R     = 0x3C,
	TEST_VDD5_SRCTRL_R     = 0x3D,
	TEST_OSC48M_SSCG0      = 0x3E,
	TEST_OSC48M_SSCG1      = 0x3F,
	TEST_OSC48M_SSCG2      = 0x40,
	TEST_TP_R_L_SEL        = 0x41,
	TEST_VCOM_OPT_SEL      = 0x42,
	TEST_VREFTP_SRCTRL     = 0x43,
	TEST_VREFTP_SH         = 0x44,
	TEST_VREFTP_BUF_EN     = 0x45,
	TEST_VREFTP_SETOP_EN   = 0x46,
	TEST_ARAM_ERRMAP       = 0x47,
	TEST_DRAM2_ERRMAP      = 0x48,
	TEST_DRAM1_ERRMAP      = 0x49,
	TEST_DRAM0_ERRMAP      = 0x4A,
	TEST_PRAM4_ERRMAP      = 0x4B,
	TEST_PRAM3_ERRMAP      = 0x4C,
	TEST_PRAM2_ERRMAP      = 0x4D,
	TEST_PRAM1_ERRMAP      = 0x4E,
	TEST_PRAM0_ERRMAP      = 0x4F,
	TEST_TABRAM_ERRMAP_L   = 0x50,
	TEST_RPTRAM_ERRMAP_L   = 0x51,
	TEST_ACCRAM_ERRMAP_L   = 0x52,
	TEST_TABRAM_ERRMAP_R   = 0x53,
	TEST_RPTRAM_ERRMAP_R   = 0x54,
	TEST_ACCRAM_ERRMAP_R   = 0x55,
	TEST_SPI0_TEST_OUT0    = 0x56,
	TEST_SPI0_TEST_OUT1    = 0x57,
	TEST_SPI0_TEST_OUT2    = 0x58,
	TEST_SPI0_TEST_OUT3    = 0x59,
	TEST_SPI0_TEST_OUT4    = 0x5A,
	TEST_SPI0_TEST_OUT5    = 0x5B,
	TEST_SPI0_TEST_OUT6    = 0x5C,
	TEST_SPI0_TEST_OUT7    = 0x5D,
	TEST_SPI0_TEST_OUT8    = 0x5E,
	TEST_SPI0_TEST_OUT9    = 0x5F,
	TEST_SPI0_TEST_OUT10   = 0x60,
	TEST_SPI0_TEST_OUT11   = 0x61
}ENUM_TEST_CON;

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CLk48M(void)
{
	UINT8 ucDiv = 5;
    #if _UART_OUT_GPIO2
        DBG_DEBUGOUT("\nP0_6 is used to be UART TX pad!");
        return;
    #endif
	
	if((UART_INH == 0)&&(UART_INL == 1))
	{
        DBG_DEBUGOUT("\nP0_6 is used to be UART RX pad and now is changed to be CLK Test Pin!");
		UART_INH = 0;
		UART_INL = 0;
	}
    P0MOD |= BITn(6);
    TEST_OUT3_EN = 0;
    GPIO_INT_SEL = 1;//将唤醒脚选为p0_7
    TEST_CLK_EN = 1;

    CGUCON7 = ucDiv;   //osc_test_div

    DBG_DEBUGOUT("\nP0MOD:%02x",P0MOD);
    DBG_DEBUGOUT("\nTESTCON3:%02x",TESTCON3);
    DBG_DEBUGOUT("\nANACON:%02x",ANACON);
    DBG_DEBUGOUT("\nFT_EN_REG:%02x",FT_EN_REG);
    DBG_DEBUGOUT("\nCUGCON7:%02x",CGUCON7);    
    DBG_DEBUGOUT("\nTest Clk 48M");
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CLk32K(void)
{
	UINT8 ucDiv = 0;//分频系数.0,1,2为2分频;其他按实际配置分频
	UINT8 ucSrc = 2;//3:32k_from_1m;2:32k_dig;1:32k osc;0:48m
	
    #if _UART_OUT_GPIO2
        DBG_DEBUGOUT("\nP0_6 is used to be UART TX pad!");
        return;
    #endif

	if((UART_INH == 0)&&(UART_INL == 1))
	{
        DBG_DEBUGOUT("\nP0_6 is used to be UART RX pad and now is changed to be CLK Test Pin!");
		UART_INH = 0;
		UART_INL = 0;
	}	
	
    P0MOD |= BITn(6);
    TEST_OUT3_EN = 0;
    GPIO_INT_SEL = 1;            //将唤醒脚选为p0_7
    TEST_CLK_EN = 1;

	if(ucSrc == 1)
	{
		SEL_32K_SRC = 1;         //写1可以发出,写0不行
	}
	else if(ucSrc == 2)
	{
		PROBE32K_DIG_EN = 1;		
	}
	else if(ucSrc == 3)
	{
		PROBE32K_FROM1M_EN = 1;
		SEL_32K_SRC = 0;         //fpga目前写1或者写0都可以发出
	}
	
	CGUCON7 = (ucSrc << 6)|(ucDiv);

    DBG_DEBUGOUT("\nP0MOD:%02x",P0MOD);
	DBG_DEBUGOUT("\nDSVCON:%02x",DSV_CON);
    DBG_DEBUGOUT("\nTESTCON3:%02x",TESTCON3);
    DBG_DEBUGOUT("\nSYSCON:%02x",SYSCON);
    DBG_DEBUGOUT("\nFT_EN_REG:%02x",FT_EN_REG);
    DBG_DEBUGOUT("\nCUGCON7:%02x",CGUCON7);    
    DBG_DEBUGOUT("\nTest Clk 32K");
}

/*******************************************************************************
*   Name:Test_CON0
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CON0(ENUM_TEST_CON ucSignal)
{
	TEST_OUT0_EN = 1;
    
	TESTCON0 |= ucSignal;	
}

/*******************************************************************************
*   Name:Test_CON1
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CON1(ENUM_TEST_CON ucSignal)
{
	TEST_OUT1_EN = 1;
    
	TESTCON1 |= ucSignal;	
}

/*******************************************************************************
*   Name:Test_CON2
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CON2(ENUM_TEST_CON ucSignal)
{
    if(BUS_SEL == 1)//spi0
    {
        P1MOD |= BITn(2);//p1_2;
    }
    else
    {
        SPI_REPLACE_EN = 0;
        P0MOD |= BITn(2);//P0_2;
    }

	TEST_OUT2_EN = 1;
    
	TESTCON2 |= ucSignal;	
}

/*******************************************************************************
*   Name:Test_CON3
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CON3(ENUM_TEST_CON ucSignal)
{

    P0MOD |= BITn(6);

	TEST_OUT3_EN = 1;
    
	TESTCON3 |= ucSignal;	
}


/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_DebugOut(void)//AFE相关信号的测试放在AFE测试代码里面
{

#if 0
    while(1)
    {
        P0_6 = !P0_6;
        DelayMs(10);
    }
#endif
    Test_CON0(TEST_LCD_BUSY);   //从tp2pad_dsv_en6出信号
    //Test_CON1(TEST_LCD_RUN);    //从led_pwm[0]出信号
    Test_CON2(TEST_LCD_VSTART); //当用SPI0时,从P0_0出信号,当用IIC时，从p0_2出信号

#if 0    
    Test_CON3(TEST_TP_BUSY);   //从p0_6出信号
#elif 0
    Test_CLk48M();              //从p0_6出信号
#else
    Test_CLk32K();              //从p0_6出信号
#endif

}
#endif

