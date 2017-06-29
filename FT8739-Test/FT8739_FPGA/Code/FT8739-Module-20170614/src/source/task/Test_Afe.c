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
#include <string.h>

#if _TEST_AFE_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define CH_ORDER_MAX         (324)               
#define TAB_TP_KEY_CB_START_ADDR  10
#define TAB_START_ADDR            256
#define TAB_RAM_LEN          176
#define TAB_RAM_START_ADDR   256
#define ACC_RAM_LEN          324
#define ACC_RAM_START_ADDR   256
#define RPT_RAM_LEN          652
#define RPT_RAM_START_ADDR   256

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef enum
{
    ID_AFE_BASE  = 0,      
    ID_ORDER_BASE = 256,    
    ID_MON_BASE = 370,   
    ID_TBL1_BASE = 256, 
} ENUM_AFE_BASE;

/* ram表项选择 */
typedef enum
{
    AREA_TBL_RAM,
    AREA_BASE_ORDER,
    AREA_BASE_ACC,
} ENUM_RAM_SEL;

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
ST_AsmRegisters * XRAM pAsmRegs = (volatile ST_AsmRegisters *)ASM_REG_BASE_ADDR;
UINT16 XRAM  g_ucOrderBuf[CH_ORDER_MAX<<1];  // 

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
/*Name: Afe_Clk_Init
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Clk_Init(void)
{  
    AFEACKEN = 1;    
    AFECKEN  = 1;   
    AFESCKEN = 1;
    ARAM_SEL = 0;  //0: afe控制aram     
}

/*******************************************************************************
*   Name: DrvAfeSelTaborRepRam
*  Brief: MCU选择要访问的Memory
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSelTaborRepRam(UINT8 RamSelect)
{
    UINT16 XSI0RegValue = 0;
    UINT16 XSI1RegValue = 0;

    XSI0RegValue = Drv_XsiReadReg(pXSI0Regs,ID_AFE_BASE + 0x05,AFE_REG);
    XSI1RegValue = Drv_XsiReadReg(pXSI1Regs,ID_AFE_BASE + 0x05,AFE_REG);
    
    XSI0RegValue = XSI0RegValue&0xFF87;
    XSI1RegValue = XSI1RegValue&0xFF87;
    
    if(RamSelect == AREA_TBL_RAM)
    {
        XSI0RegValue|= (0<<3);  
        XSI1RegValue|= (0<<3);  
    }
    else if(RamSelect == AREA_BASE_ORDER) //RPT Memory
    {
        XSI0RegValue|= (2<<3);  
        XSI1RegValue|= (2<<3);  
    }
    else if(RamSelect == AREA_BASE_ACC)
    {
        XSI0RegValue|= (1<<3);  
        XSI1RegValue|= (1<<3);  
    }

    Drv_XsiWriteReg(pXSI0Regs,ID_AFE_BASE + 0x05, XSI0RegValue,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,ID_AFE_BASE + 0x05, XSI1RegValue,AFE_REG);   
}

/*******************************************************************************
*  Brief: 在Tab表中，设置CB初值，通道使能
*  Input: ucTabID: 0表示第1个表; 3表示第4个表。
* Output: 
* Return: 
*******************************************************************************/
void Afe_SetTabCBChEN(UINT8 ucTabID)
{
    UINT16 XRAM i;
    UINT16 XRAM aus_tabbuf[TAB_RAM_LEN];
    
    memset(aus_tabbuf, 0, TAB_RAM_LEN*2);

    /* set Ch enable, set CB 0*/ 
    for(i = TAB_TP_KEY_CB_START_ADDR ;i<TAB_RAM_LEN;i++)
    {
        aus_tabbuf[i] = 0x4040;   // [6]:EN  [5:0]:CB
    }

    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0100;      //4个按键:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0100;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0100;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0100;
    
    Drv_XsiWrite(pXSI0Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
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

    SINT16 i;
    UINT16 len;
    UINT16 XRAM Buf[CH_ORDER_MAX];

    //左半屏Order
    for(i = 0; i< CH_ORDER_MAX; i++)
    {
       g_ucOrderBuf[i] = i; //0- 287/323
    }

    //右半屏Order
    for(i = 0; i < CH_ORDER_MAX; i++)
    {
       g_ucOrderBuf[i+CH_ORDER_MAX] = ((CH_ORDER_MAX-1)-i); // 287/323 -0
    }
    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);

    //按照Order Ram字节配置
    len = CH_ORDER_MAX;
    for (i = 0; i < len; i++)
    {
       Buf[i] = g_ucOrderBuf[i];  //  值: 04_03;06_05...226_225...290_289		 
    }
    Drv_XsiWrite(pXSI0Regs,256,Buf,len,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256,Buf,len,AFE_REG);		//左右同序
   
}

/*******************************************************************************
*  Brief: 表项0配置。一共有4个表项 , FreeRun 测试
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Config_Tab0(void)
{
    UINT16 XRAM usReg0;
    UINT16 XRAM usReg1;
    UINT16 XRAM usReg2;
    UINT16 XRAM usReg3;
    UINT16 XRAM usReg4;
    UINT16 XRAM usReg5;
    UINT16 XRAM usReg6;
    UINT16 XRAM usReg7;
    UINT16 XRAM usReg8;
    UINT16 XRAM usReg9; 
    UINT16 XRAM i,usReg;
    XSICKEN = 1;
    usReg0 = (15<<1)|(14<<1)|(0<<11)|(0<<7)|(0<<5)|(0<<3)|(1<<2)|(1<<1)|(1<<0);  //DAT_ACC_ASR

    usReg1 =((1<<3) +(4<<0));  //方式5 单个坑内扫描5个1/5,扫描次数，实际值为配置值加1; 输出数据次数不加1.即: 配置为1，实际扫描2次，数据只出1次。配0，扫描1次，无值输出。 

    usReg2 =((0<<9)               //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减      
            +(0<<8)               //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
            +(4<<0));             //[0] 方式6，扫描段数  
             
    usReg3 =((1<<10)               //[14:10]Mux切换之间Dummy次数    
            +(0<<5)                //[9:5]坑前Dummy次数
            +(2<<0));              //[4:0]Tp帧前Dummy次数    
            

    usReg4 = ((80<<2)             //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
             +(0<<1)              //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
             +(1<<0));          //[0] Montior模式，Base跟踪使能，1:使能 

    usReg5 = 0x100; //rACC_OFFSET;        //测试ACC Offset值 

   
    usReg6 = 0;
    usReg7 = 0;

    usReg8 = 0xC2;
    usReg9 = 0x2E;

    /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    //tab 0
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+1,usReg1,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+1,usReg1,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+2,usReg2,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+2,usReg2,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+5,usReg5,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+5,usReg5,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+6,usReg6,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+6,usReg6,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+7,usReg7,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+7,usReg7,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+8,usReg8,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+8,usReg8,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+9,usReg9,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+9,usReg9,AFE_REG);

    for(i = 0; i < 10; i++)
    {
        usReg = Drv_XsiReadReg(pXSI0Regs,TAB_START_ADDR+i,AFE_REG);
        DBG_FLOW("\n%04x",usReg);
    }

    Afe_SetTabCBChEN(0);
    
}

void AfeInit(void)
{
    Drv_XsiInit();
    Afe_Clk_Init();
    Afe_Order_Init();
    Afe_Config_Tab0();
}


void DrvAsmInterEnable0(UINT16 usInterMode)
{
    pAsmRegs->usAsmIntEn0|=(TRUE<<usInterMode); //开启中断使能         
}

void DrvAsmInterEnable1(UINT16 usInterMode)
{
    pAsmRegs->usAsmIntEn1|=(TRUE<<usInterMode); //开启中断使能         
}

/*******************************************************************************
*   Name: DrvLoadTabMultiple
*  Brief: 更新表项 ,一次启动 多TP帧扫描
*  Input: ucBusyId0-3,LCD_BUSY启动扫描坑号， ucScanMul: 多少次TP扫描 
* Output:  
* Return:  
*******************************************************************************/
void DrvLoadTabMultiple(UINT8 ucBusyId0,UINT8 ucBusyId1,UINT8 ucBusyId2,UINT8 ucBusyId3,UINT8 ucScanMul,UINT8 ucTab)
{
    UINT8 ucF0TabId;
    UINT8 ucF1TabId;
    UINT8 ucF2TabId;
    UINT8 ucF3TabId;
    
    ucF0TabId = ucTab; // TAB表ID
    ucF1TabId = ucTab;
    ucF2TabId = ucTab;
    ucF3TabId = ucTab;
   
    //REG_20   
    pAsmRegs->usAsmScanDly|=   ((1<<13)               // [13] Tab3表使能: 1:使能 
                               +(1<<12)               // [12] Tab2表使能: 1:使能 
                               +(1<<11)               // [11] Tab1表使能: 1:使能 
                               +(1<<10));             // [10] Tab0表使能: 1:使能 

    //REG_14    
    pAsmRegs->usAsmScanCfg0&=~(0x7<<0);      
    pAsmRegs->usAsmScanCfg0|=(ucScanMul<<0);   // [1:0]多帧扫描的总帧数 0-3: 扫描1-4个TP帧                                
                               
    //REG_16 
    pAsmRegs->usAsmTpFrameCfg0 = ((ucF1TabId<<14)     // [3] 第1个TP帧用的Table表号  
                                  +(ucBusyId1<<8)   // [2] 第1个TP帧起始坑号        
                                  +(ucF0TabId<<6)    // [1] 第0个TP帧用的Table表号     
                                  +(ucBusyId0<<0)); // [0] 第0个TP帧起始坑号 

    //REG_17 
    pAsmRegs->usAsmTpFrameCfg1 = ((ucF3TabId<<14)     // [3] 第3个TP帧用的Table表号  
                                  +(ucBusyId3<<8)   // [2] 第3个TP帧起始坑号        
                                  +(ucF2TabId<<6)    // [1] 第2个TP帧用的Table表号     
                                  +(ucBusyId2<<0)); // [0] 第2个TP帧起始坑号 
                         
}


void DrvAsmReq120hz_Small_LcdBusy(void)
{
    //REG_15    
    pAsmRegs->usAsmScanCfg1&=~(1<<8);    // [8] 请求: 0:小坑     
}   

/*******************************************************************************
*   Name: Afe_120Hz_Run
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_120Hz_Run(void)
{

    UINT16 XRAM usConfigValue;
    static XRAM FristStart = 1;

    ASM_EI = 1;

    AfeInit();
#if 1     
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG); // sx全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);

    DrvLoadTabMultiple(1,6,0,0,0,0);    // 120hz表1  启动扫描后，每次连续扫描2帧，第1次启动从1坑开始，第2次启动从6坑开始，

    DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);   //开启LCD_VSTART中断使能  
                                        
    DrvAsmReq120hz_Small_LcdBusy(); //请求120h
#endif  
    
}

/*******************************************************************************
*   Name:  DrvAsmAramAvail
*  Brief:  启动一次，多次扫描，Aram在第一次扫描后，取走后，可以进行下次扫描。
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmAramAvail(void)
{
    //REG_13  
    pAsmRegs->usAsmScanCtrl|=(1<<2); // [2] WO: 1:可以操作ARAM
}

/*******************************************************************************
*   Name: DrvAsmScanStart
*  Brief: 启动扫描
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmScanStart(void)
{
    pAsmRegs->usAsmScanCtrl|=(1<<0);   // [0] WO: 启动扫描  
    //DBG_FLOW("\nStart"); 
}

#endif //_TEST_AFE_EN


