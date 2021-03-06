/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: main.c
*
*    Author: xinkunpeng
*
*   Created: 2013-11-11
*
*  Abstract:
*
* Reference:
*
* Version: 0.2: Transplant from FT5422 by linjianjun
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

#define APP_INFO_ADDR             0xFEE900  // Verification Info
#define APP_VERIF_LEN             0x20

#define FW_CFG_TOTAL_SIZE         0x80

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
//UINT8 XRAM g_ucTestStack;      // system pram address stack test
//UINT8 CROM g_ucTest[40000];    // use to add the code size to 64K
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
void CRCCCITT(const UINT8* pDataIn, UINT16 iLenIn, UINT16* pCRCOut);

/* 预留给校验码信息的代码区 */
UINT8 ECODE g_aucVerfication[APP_VERIF_LEN+FW_CFG_TOTAL_SIZE] _at_ APP_INFO_ADDR;
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: init_mcu
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void init_mcu(void)
{
    UINT8 XRAM i,cnt;    
    I2CRI  = 0;
    I2CTI  = 0;
    I2CSTP = 0;
    I2CBUF = 0;

#if _TEST_SFR_EN
    for (i = 0x80; i < 0xff; i++)
    {
      g_ucSFR[i]   = SFRGetRegMapDataNormal(i);
    }
    
    g_ucSFR[0xFF] = SFRGetRegMapDataNormal(0xFF);   //LED_H_NUM
    g_ucSFR[0xC0] = SFRGetRegMapDataNormal(0xC0);   //AIF
    P1MOD = 0x00;
    P1DIR = 0xFF;
    P1SEL = 0xFF;
    g_ucSFR[0x94] = SFRGetRegMapDataNormal(0x94);   //P1BUF
#endif
    DrvSysClkInit(MAIN_CLK);
    SEL_32K_SRC = 1;        // select 32K src OSC
    //FlASH_HOLD = 0;         // Flash Hold测试
    DrvIOInit();
    //DelayMs(3000);
    DrvUartInit();
    
    EA = 1;    
  
    DBG_FLOW("\n\rModule test:");
    DBG_FLOW(__DATE__);
    for (i = 0; i < 9; i++)
    {
        DBG_FLOW("\n\rCGU%x: %02x", i, g_ucbuf[i]);
    }
    DBG_FLOW("\n\rSFT_RST: %x", g_ucbuf[9]);
    DBG_FLOW("\n\rPOR_STA: %x", g_ucbuf[10]);
    DBG_FLOW("\n\rRST_STA: %x", g_ucbuf[11]);
    DBG_FLOW("\n\rANACON:%x", g_ucbuf[12]);
    DBG_FLOW("\n\rIWKSTA:%02x",IWKSTA);

    /*若需要使用lvd中断/lvd_cnt/lvd_sta需要开启*/
    LVD_VDDI_EN = 1;
    LVD_AVEE_EN = 1;
    LVD_AVDD_EN = 1;
    
    CNT_MASK = 0;
    cnt = CNT_STA; 
    DBG_FLOW("\n\rPORRST_CNT:%02x",cnt);
    
    CNT_MASK = 1;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rWDTRST_CNT:%02x",cnt);

    CNT_MASK = 2;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rEXTRST_CNT:%02x",cnt);

    CNT_MASK = 3;
    cnt = CNT_STA;      
    DBG_FLOW("\n\rLCDRST_CNT:%02x",cnt);
    
    ESD_RST_EN = 0;  //发生esd，产生复位

    CNT_MASK = 4;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rESDRST_CNT:%02x",cnt);


    CNT_MASK = 5;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rLVDRST_CNT:%02x",cnt);


    CNT_MASK = 0x08;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rCPU_PORRST_CNT:%02x",cnt);


    CNT_MASK = 0x09;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rCPU_WDTRST_CNT:%02x",cnt);
      

    CNT_MASK = 0x0A;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rCPU_EXTRST_CNT:%02x",cnt);

    CNT_MASK = 0x0B;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rCPU_LCDRST_CNT:%02x",cnt);

    CNT_MASK = 0x0C;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rCPU_ESDRST_CNT:%02x",cnt);

    CNT_MASK = 0x0D;
    cnt = CNT_STA;    
    DBG_FLOW("\n\rCPU_LVDRST_CNT:%02x",cnt);
    
    DBG_FLOW("\n\rinit system ok!");
    DelayMs(1000);

#if 0
    // REMAP test
    DelayMs(1000);
    REMAP = 0;
    DelayMs(5);
#endif    

#if 0
	while(1)
	{
		DBG_FLOW("\nLVD_STA:%d",LVD_STA);
		DBG_FLOW("\nESD_STA:%d",ESD_STA);
		DBG_FLOW("\nLVD_FLAG:%d",LVD_FLAG);
		DBG_FLOW("\nESD_FLAG:%d",ESD_FLAG);
		DBG_FLOW("\nLVD_VDDI_STA:%d",LVD_VDDI_STA);
		DBG_FLOW("\nLVD_AVEE_STA:%d",LVD_AVEE_STA);
		DBG_FLOW("\nLVD_AVDD_STA:%d\n",LVD_AVDD_STA);
		DelayMs(1000);
	}
#endif		
}

/*******************************************************************************
*   Name: main
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void main(void)
{
    UINT16 XRAM i = 0;

 #if 0  
    UINT8 buf[8]={0};
    UINT16 crc=0;
    for(i=0;i<8;i++)
    {
        buf[i]=0xa7;
    }
    
    CRCCCITT(buf,6,&crc);
    HOLD;
#endif
    
    init_mcu();

#if 1
    
    Test_UART();
    Test_SFR();
    Test_Dram();
    Test_Prom();
    Test_Aram();
    Test_SPI_Flash();
    Test_Spi0Reg();
    Test_XsiReg();
    Test_XbusReg();
    Test_AsmReg();
    Test_CalReg();
    Test_LcdReg();
    Test_AfeReg(); 
    Test_Afe_Ram();
    Test_DebugOut();    

    Test_LED();
    Test_I2C();

    Test_Reset();
    Test_WDT();
    Test_RTC();
    Test_Counter();
    
    Test_Timer();    
    Test_GPIO();
    Test_I2CWakeup();
    Test_Int0Wakeup();
    Test_int_nest();
    Test_Xsi();
    Test_Afe();
    Test_CAL();

    Test_romboot();
    Test_Xbus();
    Test_RomEcc();
    Test_SPI0();
    Test_DMA();
    Test_SPI0_Wakeup();
    Test_SOFT_RST();

    while (1)
    {
        DBG_FLOW("\nMODULE TEST");
        DelayMs(2000);
    }
 #endif  
}

