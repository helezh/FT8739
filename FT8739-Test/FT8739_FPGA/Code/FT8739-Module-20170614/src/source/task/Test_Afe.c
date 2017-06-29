/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)��All Rights Reserved.
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

/* ram����ѡ�� */
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
    ARAM_SEL = 0;  //0: afe����aram     
}

/*******************************************************************************
*   Name: DrvAfeSelTaborRepRam
*  Brief: MCUѡ��Ҫ���ʵ�Memory
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
*  Brief: ��Tab���У�����CB��ֵ��ͨ��ʹ��
*  Input: ucTabID: 0��ʾ��1����; 3��ʾ��4����
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

    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0100;      //4������:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0100;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0100;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0100;
    
    Drv_XsiWrite(pXSI0Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
}

/*******************************************************************************
*   Name: Afe_Order_Init
*  Brief: ��������ʼ��
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Order_Init(void)
{

    SINT16 i;
    UINT16 len;
    UINT16 XRAM Buf[CH_ORDER_MAX];

    //�����Order
    for(i = 0; i< CH_ORDER_MAX; i++)
    {
       g_ucOrderBuf[i] = i; //0- 287/323
    }

    //�Ұ���Order
    for(i = 0; i < CH_ORDER_MAX; i++)
    {
       g_ucOrderBuf[i+CH_ORDER_MAX] = ((CH_ORDER_MAX-1)-i); // 287/323 -0
    }
    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);

    //����Order Ram�ֽ�����
    len = CH_ORDER_MAX;
    for (i = 0; i < len; i++)
    {
       Buf[i] = g_ucOrderBuf[i];  //  ֵ: 04_03;06_05...226_225...290_289		 
    }
    Drv_XsiWrite(pXSI0Regs,256,Buf,len,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256,Buf,len,AFE_REG);		//����ͬ��
   
}

/*******************************************************************************
*  Brief: ����0���á�һ����4������ , FreeRun ����
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

    usReg1 =((1<<3) +(4<<0));  //��ʽ5 ��������ɨ��5��1/5,ɨ�������ʵ��ֵΪ����ֵ��1; ������ݴ�������1.��: ����Ϊ1��ʵ��ɨ��2�Σ�����ֻ��1�Ρ���0��ɨ��1�Σ���ֵ����� 

    usReg2 =((0<<9)               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������      
            +(0<<8)               //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
            +(4<<0));             //[0] ��ʽ6��ɨ�����  
             
    usReg3 =((1<<10)               //[14:10]Mux�л�֮��Dummy����    
            +(0<<5)                //[9:5]��ǰDummy����
            +(2<<0));              //[4:0]Tp֡ǰDummy����    
            

    usReg4 = ((80<<2)             //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
             +(0<<1)              //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
             +(1<<0));          //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 

    usReg5 = 0x100; //rACC_OFFSET;        //����ACC Offsetֵ 

   
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
    pAsmRegs->usAsmIntEn0|=(TRUE<<usInterMode); //�����ж�ʹ��         
}

void DrvAsmInterEnable1(UINT16 usInterMode)
{
    pAsmRegs->usAsmIntEn1|=(TRUE<<usInterMode); //�����ж�ʹ��         
}

/*******************************************************************************
*   Name: DrvLoadTabMultiple
*  Brief: ���±��� ,һ������ ��TP֡ɨ��
*  Input: ucBusyId0-3,LCD_BUSY����ɨ��Ӻţ� ucScanMul: ���ٴ�TPɨ�� 
* Output:  
* Return:  
*******************************************************************************/
void DrvLoadTabMultiple(UINT8 ucBusyId0,UINT8 ucBusyId1,UINT8 ucBusyId2,UINT8 ucBusyId3,UINT8 ucScanMul,UINT8 ucTab)
{
    UINT8 ucF0TabId;
    UINT8 ucF1TabId;
    UINT8 ucF2TabId;
    UINT8 ucF3TabId;
    
    ucF0TabId = ucTab; // TAB��ID
    ucF1TabId = ucTab;
    ucF2TabId = ucTab;
    ucF3TabId = ucTab;
   
    //REG_20   
    pAsmRegs->usAsmScanDly|=   ((1<<13)               // [13] Tab3��ʹ��: 1:ʹ�� 
                               +(1<<12)               // [12] Tab2��ʹ��: 1:ʹ�� 
                               +(1<<11)               // [11] Tab1��ʹ��: 1:ʹ�� 
                               +(1<<10));             // [10] Tab0��ʹ��: 1:ʹ�� 

    //REG_14    
    pAsmRegs->usAsmScanCfg0&=~(0x7<<0);      
    pAsmRegs->usAsmScanCfg0|=(ucScanMul<<0);   // [1:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡                                
                               
    //REG_16 
    pAsmRegs->usAsmTpFrameCfg0 = ((ucF1TabId<<14)     // [3] ��1��TP֡�õ�Table���  
                                  +(ucBusyId1<<8)   // [2] ��1��TP֡��ʼ�Ӻ�        
                                  +(ucF0TabId<<6)    // [1] ��0��TP֡�õ�Table���     
                                  +(ucBusyId0<<0)); // [0] ��0��TP֡��ʼ�Ӻ� 

    //REG_17 
    pAsmRegs->usAsmTpFrameCfg1 = ((ucF3TabId<<14)     // [3] ��3��TP֡�õ�Table���  
                                  +(ucBusyId3<<8)   // [2] ��3��TP֡��ʼ�Ӻ�        
                                  +(ucF2TabId<<6)    // [1] ��2��TP֡�õ�Table���     
                                  +(ucBusyId2<<0)); // [0] ��2��TP֡��ʼ�Ӻ� 
                         
}


void DrvAsmReq120hz_Small_LcdBusy(void)
{
    //REG_15    
    pAsmRegs->usAsmScanCfg1&=~(1<<8);    // [8] ����: 0:С��     
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
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG); // sxȫ��
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);

    DrvLoadTabMultiple(1,6,0,0,0,0);    // 120hz��1  ����ɨ���ÿ������ɨ��2֡����1��������1�ӿ�ʼ����2��������6�ӿ�ʼ��

    DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);   //����LCD_VSTART�ж�ʹ��  
                                        
    DrvAsmReq120hz_Small_LcdBusy(); //����120h
#endif  
    
}

/*******************************************************************************
*   Name:  DrvAsmAramAvail
*  Brief:  ����һ�Σ����ɨ�裬Aram�ڵ�һ��ɨ���ȡ�ߺ󣬿��Խ����´�ɨ�衣
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmAramAvail(void)
{
    //REG_13  
    pAsmRegs->usAsmScanCtrl|=(1<<2); // [2] WO: 1:���Բ���ARAM
}

/*******************************************************************************
*   Name: DrvAsmScanStart
*  Brief: ����ɨ��
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmScanStart(void)
{
    pAsmRegs->usAsmScanCtrl|=(1<<0);   // [0] WO: ����ɨ��  
    //DBG_FLOW("\nStart"); 
}

#endif //_TEST_AFE_EN


