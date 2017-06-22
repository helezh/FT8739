/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_Afe.c
*
*    Author: xinkunpeng
*
*   Created: 2014-05-15
*
*  Abstract:
*
* Reference:
*
*   Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_Afe.h"
#include "Drv_Cal.h"
#include "Drv_XSI.h"

/*得重新修改*/
#if 0//_TEST_AFE_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
UINT16 XRAM dma_data[456] _at_ 0x0400;

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef enum
{
    SCAN_FREE_RUN,
    SCAN_SERIAL_RUN,
    SCAN_Parallel_RUN,
    SCAN_ARAM_BUSY,
    TP_60HZ_RUN,
    SCAN_FREE_RUN5,
} ENUM_TEST_MODE;

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT8 g_ucIntFlag0      = 0x00;
UINT8 g_Flag            = 0x55;

UINT8 g_ucTpmodeFlag    = 0x00;
UINT8 g_ucAramReadyFlag = 0x00;
UINT8 g_ucLcdStopFlag   = 0x00;
UINT8 g_ucLcdBusyFlag   = 0x00;

UINT8 g_ucLcdStartFlag  = 0x00;

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: Afe_Read_Dram
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Afe_Read_Dram()
{
    UINT16 i;
    ST_CalMcMatrixParam XRAM CalParam;

    UINT16 * XRAM abuf_ptr;
    UINT16 * XRAM ram_ptr;

    ARAM_SEL = 1;

    abuf_ptr = (UINT16)ARAM_DATA_BASE_ADDR;
    ram_ptr  = (UINT16)dma_data;

    CalParam.usSrc1Addr = (UINT16)abuf_ptr;
    CalParam.usDstAddr  = (UINT16)ram_ptr;
    CalParam.ucTxNum    = 24;
    CalParam.ucRxNum    = 19;
    CalParam.usCalcmd   = OP_MOV;
    CalParam.ucCfg      = 0;

    DrvCal_Init(24, 19, 0x0000);
    DrvCal_MatrixProc(&CalParam);

    DBG_FLOW("\n\rDram");
    for (i = 0; i < 227; i++)
    {
        if (i%23 == 0)
        {
            DBG_AFE("\n\r");
        }
        DBG_AFE("0x%04x ",ram_ptr[i]);
    }
    ARAM_SEL = 0;
}

/*******************************************************************************
*   Name: ExternInt0Init()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void ExternInt0Init(void)
{
    //SCAN_MON_WKEN = 1;
    IT0   = 0;
    IPL0  = 0;
    IPH0  = 0;

    IPLX0 = 1;
    IPHX0 = 1;    // 中断0优先级必须最高

    EX0 = 1;
}

/*******************************************************************************
*   Name: Afe_Clk_Init
*  Brief: Afe时钟初始化
*  Input:
* Output:
* Return:
*******************************************************************************/
void Afe_Clk_Init(void)
{
    XSI0CKEN = 1;
    XSI1CKEN = 1;
    //XSI2CKEN = 1;
    AFEACKEN = 1;
    //AFELCKEN = 1;
    //AFERCKEN = 1;
    AFESCKEN = 1;
    //SSICKEN  = 1;
    ASMCKEN = 1;
    //XSI2CKEN = 1;

    ExternInt0Init();
}

/*******************************************************************************
*   Name: Afe_Order_Init
*  Brief: 重排序表初始化
*  Input:
* Output:
* Return:
*******************************************************************************/
void Afe_Order_Init(void)
{
    UINT8 i;
    UINT8 len;
    UINT16 XRAM Buf[112];

    len = 112;
    for (i = 0; i < len; i++)
    {
        Buf[i] = i*2 + ((i*2+1)<<8);
    }
    Drv_XsiWrite(pXSI0Regs,256,Buf,len,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256,Buf,len,AFE_REG);
}
/*******************************************************************************
*   Name: Afe_Config_Init
*  Brief: Afe配置参数初始化
*  Input:
* Output:
* Return:
*******************************************************************************/
void Afe_Config_Init(void)
{
    Drv_XsiWriteReg(pXSI0Regs,6,  0x3080,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,6,  0x3080,AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs,24, 0x0022,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,24, 0x0022,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,25, 0x0200,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,25, 0x0200,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,26, 0x0200,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,26, 0x0200,AFE_REG);

    /* XSI_S Reg Init */
    Drv_XsiWriteReg(pXSI0Regs,0,1,XSI_S_REG);
    Drv_XsiWriteReg(pXSI1Regs,0,1,XSI_S_REG);

}

/*******************************************************************************
*   Name: Afe_Scan_Config_Init
*  Brief: Afe scan配置参数初始化
*  Input:
* Output:
* Return:
*******************************************************************************/
void Afe_Scan_Config_Init(void)
{
    AFE_CLK_EN = 0x3F;
    SSI_EN_ID  = 0x03;
    SSI_SADDR0 = 0x00;
    SSI_SADDR1 = 227;

    INT_MASK0  = 0x33;
    INT_MASK1  = 0x0B;
    MON_MASK0  = 0x00;
    MON_MASK1  = 0x04;

    SCAN_CFG   = 0;
    INT_FLAG0 = 0xFF;
    INT_FLAG1 = 0xFF;
    SCAN_INT_EI = 1;

    EA = 1;
}
/*******************************************************************************
*   Name: Afe_Init
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Afe_Init(void)
{
    Afe_Clk_Init();
    Afe_Order_Init();
    Afe_Config_Init();
    Afe_Scan_Config_Init();

    DBG_FLOW("\n\rAfe Init is OK");
}

/*******************************************************************************
*   Name: Afe_60Hz_Run
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Afe_60Hz_Run(void)
{

    TP_120HZ_REQ = 0x00;

    while ((TP_RUN_MODE_STA == 0)&&(LCD_RUN_STA==1))
    {
        SCAN_MON_WKEN = 1;
        EA = 0;

        SCAN_EN = 0;
        SCAN_EN = 1;
        SCAN_EN = 0;
        DrvSysPowerStop();

        while ((g_ucAramReadyFlag==0)&&(g_ucLcdStopFlag==0));

        SSI_DATA_RD = 1;
        TP_FREE_RUN = 0;
        g_ucAramReadyFlag = 0;
        if (g_ucLcdStopFlag)
        {
            g_ucLcdStopFlag = 0;
        }
        DelayMs(40);
    }
}

/*******************************************************************************
*   Name: Afe_Free_Run
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Afe_Free_Run(void)
{
    SCAN_EN = 0;
    SCAN_EN = 1;
    SCAN_EN = 0;
    while (SSI_DATA_RD == 0);
    //Afe_Read_Dram();
    SSI_DATA_RD = 1;
    DelayMs(40);
}
/*******************************************************************************
*   Name: Test_Afe
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Afe()
{
    Afe_Init();
    while (1)
    {
        while (LCD_RUN_STA == 1)
        {
            DBG_FLOW("\nAfe_60Hz_Run");
            Afe_60Hz_Run();
        }
        while (LCD_RUN_STA == 0)
        {
            DBG_FLOW("\nAfe_free_Run");
            Afe_Free_Run();
        }
    }
}

/*******************************************************************************
*   Name: DrvScanCtrl_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvScanCtrl_IRQHandler(void) interrupt 14
{
    if (MON_DET_1_FLAG)
    {
        g_ucIntFlag0 |= 0x80;
        INT_FLAG0    = 0x80;
    }
    if (MON_DET_0_FLAG)
    {
        g_ucIntFlag0 |= 0x40;
        INT_FLAG0    = 0x40;
    }
    if (CVT_END_1_FLAG)
    {
        g_ucIntFlag0 |= 0x08;
        INT_FLAG0    = 0x08;
    }
    if (CVT_END_0_FLAG)
    {
        g_ucIntFlag0 |= 0x04;
        g_Flag = 0xAA;
        INT_FLAG0    = 0x04;
    }

    if (FME_END_1_FLAG)
    {
        g_ucIntFlag0 |= 0x20;
        INT_FLAG0    = 0x20;
    }
    if (FME_END_0_FLAG)
    {
        g_ucIntFlag0 |= 0x10;
        INT_FLAG0    = 0x10;
    }
    if (SA_END_1_FLAG)
    {
        g_ucIntFlag0 |= 0x02;
        INT_FLAG0    = 0x02;
    }
    if (SA_END_0_FLAG)
    {
        g_ucIntFlag0 |= 0x01;
        INT_FLAG0    = 0x01;
    }

    if (TP_RUN_MODE_FLAG_FALL)
    {
        g_ucTpmodeFlag = 0;
        INT_FLAG1    = 0x20;
    }
    if (TP_RUN_MODE_FLAG)
    {
        g_ucTpmodeFlag = 1;
        INT_FLAG1    = 0x10;
    }
    if (ARAM_RDY_FLAG)
    {
        g_ucAramReadyFlag = 1;
        INT_FLAG1    = 0x08;
    }
    if (LCD_BUSY_FLAG)
    {
        g_ucLcdBusyFlag = 1;
        INT_FLAG1    = 0x04;
    }

    if (LCD_RUN_FLAG_FALL)
    {
        g_ucLcdStopFlag = 1;
        INT_FLAG1    = 0x02;
    }
    if (LCD_RUN_FLAG)
    {
        g_ucLcdStartFlag = 1;
        INT_FLAG1    = 0x01;
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
    if (SCAN_MON_INT)
    {
        DBG_FLOW("\nwake up");
    }
    SCAN_MON_WKEN = 0;
}

#endif

