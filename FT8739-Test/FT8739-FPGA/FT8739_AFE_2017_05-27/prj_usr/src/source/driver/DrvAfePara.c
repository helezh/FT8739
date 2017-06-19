/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: DrvAfePara.c
*
*    Author: linjianjun
*
*   Created: 2014-10-30
*
*  Abstract:
*
* Reference:
*
* Version:   V0.1
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "CfgGlobal.h"

//#include "DrvAfePara.h"
//#include "DrvAfeCtrl.h"
#include "DrvSysCtrl.h"
//#include "DrvClb.h"

#include "libDrv.h"

//#include "AppAfeCtrl.h"
//#include "AppDataStruct.h"
#include "AppHostComm.h"
//#include "DrvMonDet.h"
#include "DrvAfe.h"
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
ST_McapParameter XRAM g_pMcapData;
ST_McapParameter XRAM *g_pMcapPara = &g_pMcapData;
ST_AfeTabList XRAM g_pAfeTab;
ST_AfeTabList XRAM *g_pAfeTabPara = &g_pAfeTab;
/******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:  DrvAfeSelACCRam
*  Brief:  
*  Input: ucbit:  0:1-15bit;   1:16-31bit   2: 32-47bit  3:48-63bit
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSelACCRam(UINT8 ucbit)
{
    UINT16 XSI0RegValue = 0;
    UINT16 XSI1RegValue = 0;

    XSI0RegValue = Drv_XsiReadReg(pXSI0Regs,ID_AFE_BASE + 0x05,AFE_REG);
    XSI1RegValue = Drv_XsiReadReg(pXSI1Regs,ID_AFE_BASE + 0x05,AFE_REG);
    
    XSI0RegValue = XSI0RegValue&0xFF87;
    XSI1RegValue = XSI1RegValue&0xFF87;
    
    XSI0RegValue|= (1<<3)+(ucbit<<5);  
    XSI1RegValue|= (1<<3)+(ucbit<<5);  
   
    Drv_XsiWriteReg(pXSI0Regs,ID_AFE_BASE + 0x05, XSI0RegValue,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,ID_AFE_BASE + 0x05, XSI1RegValue,AFE_REG);   
}

void DebugReadAFEReg(void)
{
    UINT16 XRAM ReadRegs0;
    UINT16 XRAM ReadRegs1;
    UINT16 XRAM addr;

    for(addr = 0; addr < 75; addr++)
    {
        ReadRegs0 = Drv_XsiReadReg(pXSI0Regs,addr,AFE_REG);
        ReadRegs1 = Drv_XsiReadReg(pXSI1Regs,addr,AFE_REG);
        DBG_FLOW("\nReg%d 0x%x  0x%x ",addr,ReadRegs0,ReadRegs1);
    }
}

UINT16 DebugReadAFEOneReg(UINT16 ucAddr)
{
    UINT16 XRAM ReadRegs0;
    UINT16 XRAM ReadRegs1;

    ReadRegs0 = Drv_XsiReadReg(pXSI0Regs,ucAddr,AFE_REG);
    ReadRegs1 = Drv_XsiReadReg(pXSI1Regs,ucAddr,AFE_REG);

    if(ReadRegs0 == ReadRegs1)
    {
        return ReadRegs0;
    }
    else
    {
        DBG_FLOW("\nReg Error");
        return 0;
    }
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
*   Name: DrvAFEGroupSelReg1
*  Brief: 5组Mux, GroupA,GroupB选择
*  [G1 G2 G3 G4]| [G5 G6 G7 G8 G9]
*     Group A   |    Group B            
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAFEGroupSelReg1(UINT8 ucMux1_GA,UINT8 ucMux1_GB,UINT8 ucMux2_GA,UINT8 ucMux2_GB,UINT8 ucMux3_GA,UINT8 ucMux3_GB)
{
    UINT16 XRAM usPanelMode;

    usPanelMode = ((ucMux3_GB<<BIT_PANEL_MUX3_GROUPB_SEL)   //12                       
                  +(ucMux3_GA<<BIT_PANEL_MUX3_GROUPA_SEL)   //10
                  +(ucMux2_GB<<BIT_PANEL_MUX2_GROUPB_SEL)   //7
                  +(ucMux2_GA<<BIT_PANEL_MUX2_GROUPA_SEL)   //5
                  +(ucMux1_GB<<BIT_PANEL_MUX1_GROUPB_SEL)   //2
                  +(ucMux1_GA<<BIT_PANEL_MUX1_GROUPA_SEL)); //0

    Drv_XsiWriteReg(pXSI0Regs, Addr_PANEL_MODE_CFG0, usPanelMode, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_PANEL_MODE_CFG0, usPanelMode, AFE_REG);
}


/*******************************************************************************
*   Name: DrvAFEGroupSelReg2
*  Brief: 5组Mux, GroupA,GroupB选择
*  [G1 G2 G3 G4]| [G5 G6 G7 G8 G9]
*     Group A   |    Group B            
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAFEGroupSelReg2(UINT8 ucMux4_GA,UINT8 ucMux4_GB,UINT8 ucMux5_GA,UINT8 ucMux5_GB)
{
    UINT16 XRAM usPanelMode;

    usPanelMode = ((ucMux5_GB<<BIT_PANEL_MUX5_GROUPB_SEL)    //8                                  
                  +(ucMux5_GA<<BIT_PANEL_MUX5_GROUPA_SEL)    //5
                  +(ucMux4_GB<<BIT_PANEL_MUX4_GROUPB_SEL)    //2
                  +(ucMux4_GA<<BIT_PANEL_MUX4_GROUPA_SEL));  //0

    Drv_XsiWriteReg(pXSI0Regs, Addr_PANEL_MODE_CFG1, usPanelMode, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_PANEL_MODE_CFG1, usPanelMode, AFE_REG);
}


/*******************************************************************************
*   Name: DrvGetRptRamOrder
*  Brief: 地址: 0-323: Tp通道与Key键上报Rawdata所需的Order
*         地址  324-325: key diff Noise max, TP diff Noise max.
*         地址: 326-653: Tp通道与Key键 Rawdata/Base
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvGetRptRamOrder(void)
{
    UINT16 XRAM j;
    UINT16 XRAM ausBaseBuf[CH_LEN];

    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);
    
    Drv_XsiRead(pXSI0Regs, BASE_RAM_START_ADDR, ausBaseBuf, CH_LEN, AFE_REG); 
    for(j = 0;j < CH_LEN;j++)
    {
        //if(j<10)
        {
            DBG_FLOW("\n[%d] %d ",j,ausBaseBuf[j]);
        }
    }   
}

void DrvInitRptRam(void)
{
    UINT16 XRAM j;

    UINT16 XRAM ausBaseBufL[BASE_RAM_BASE_LEN + BASE_RAM_KEY_LEN]; // Base + 4key
    UINT16 XRAM ausBaseBufR[BASE_RAM_BASE_LEN + BASE_RAM_KEY_LEN]; // Base + 4key

    for(j = 0;j <CH_LEN_MAX;j++)
    {
        ausBaseBufL[j] = 0;
        ausBaseBufR[j] = 0;
    } 

    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);
    
    Drv_XsiWrite(pXSI0Regs, BASE_RAM_START_ADDR + BASE_RAM_TP_RAWBASE_ADDR, ausBaseBufL,CH_LEN_MAX, AFE_REG);  
    Drv_XsiWrite(pXSI1Regs, BASE_RAM_START_ADDR + BASE_RAM_TP_RAWBASE_ADDR, ausBaseBufR,CH_LEN_MAX, AFE_REG);  
}






/*******************************************************************************
*   Name: DrvAfeScanMode
*  Brief:          
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeScanMode(UINT8 ucMode,UINT16 usScantimes)
{
    UINT16 XRAM usScanCfg0;
    
    usScanCfg0 = ((usScantimes<<BIT_AFE_SCAN_TIMES)                                          
                 +(ucMode<<BIT_AFE_SCAN_MODE<<0));
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SCAN_CFG0, usScanCfg0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SCAN_CFG0, usScanCfg0, AFE_REG);
}

/*******************************************************************************
*   Name: DrvAfeSofeReset
*  Brief:  AFE软复位逻辑  
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSofeReset(void)
{
    DBG_FLOW("\nDrvAfeSofeReset: ");  
    AFE_RST = 1;   
    AFE_RST = 0; 
}

void DrvAfeEnCOF(void)
{
    UINT16 XRAM usConfigValue;

    usConfigValue = (rAFE_SYS_CFG0|(1<<8));
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG);

    DBG_FLOW("\nReg4 0x%x ",DebugReadAFEOneReg(4));
//    while(1);
}

void DrvAfeEnRawdataNum(UINT16 ucRptRawdataNum)
{
    Drv_XsiWriteReg(pXSI0Regs, Addr_RPT_RAWDATA_NUM, ucRptRawdataNum, AFE_REG); //rRPT_RAWDATA_NUM
    Drv_XsiWriteReg(pXSI1Regs, Addr_RPT_RAWDATA_NUM, ucRptRawdataNum, AFE_REG);
    DBG_FLOW("\nReg49 0x%x ",DebugReadAFEOneReg(49));
//    while(1);    
}

void DrvAfeEn4mux(void)
{
    UINT16 XRAM usConfigValue;

    usConfigValue = (rAFE_SYS_CFG0|(1<<2));
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG);

    DBG_FLOW("\nReg4 0x%x ",DebugReadAFEOneReg(4));
}

void DrvGetTabRam(void)
{
    UINT8 i;
    UINT8 ucLen;
    UINT16 usAddr;
    UINT16 XRAM Buf[TAB_RAM_LEN];

    usAddr = TAB_RAM_START_ADDR;
    ucLen  = TAB_RAM_LEN;

    XSICKEN = 1;
    
    /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rRam_Tab1[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\rRead Ram_Tab1 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rRam_Tab2[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\rRead Ram_Tab2 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rRam_Tab3[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\rRead Ram_Tab3 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rRam_Tab4[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\rRead Ram_Tab4 is ok!");
}





/*******************************************************************************
*   Name: DrvAfeSetOneChannelTestMode
*  Brief:  扫描次数决定上报原始ADC个数，模拟相减每次报2个数据。
*           DAT_TEST_MODE_KEY_NUM       0x00    //[11:10]测试模式，选择key键号                                    
*           DAT_TEST_MODE_TP_CH_NUM             0x000   //[9:1]  测试模式，选择tp通道号
*           DAT_TEST_MODE_TP_KEY_SEL            0x0     //[0], 通道选择, 0:tp; 1:key
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSetOneChannelTestMode(UINT8 ucKeyNum,UINT16 usTpNum,UINT8 ucTp_Key_Sel)
{
    UINT16 XRAM  Reg;
                                 
    Reg = rAFE_SYS_CFG0&0xFFFE;

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, Reg, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, Reg, AFE_REG);   

    Reg = ((ucKeyNum<<10)|(usTpNum<<1)|(ucTp_Key_Sel<<0));
     
    Drv_XsiWriteReg(pXSI0Regs, Addr_TEST_MODE_FLAG, Reg, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TEST_MODE_FLAG, Reg, AFE_REG);
}


/*******************************************************************************
*   Name: DrvAfeSetBaseTrack
*  Brief: Monitor模式，Base跟踪设置 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSetBaseTrack(UINT8 ucBaseMode,UINT8 ucStep)
{
    UINT16 XRAM usBaseTrackReg;
                                 
    usBaseTrackReg = ((ucStep<<BIT_BASE_TRACK_STEP)          //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
                     +(ucBaseMode<<BIT_BASE_TRACK_MODE)      //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
                     +(1<<BIT_BASE_TRACK_ENABLE));           //[0] Montior模式，Base跟踪使能，1:使能 

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_BASE_TRACK_CFG, usBaseTrackReg, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_BASE_TRACK_CFG, usBaseTrackReg, AFE_REG);               
}


/*******************************************************************************
*   Name: DrvAfeSetBaseTrack
*  Brief: Monitor模式，Base跟踪设置 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSetTabBaseTrack(UINT8 ucBaseMode,UINT8 ucStep,UINT8 ucId)
{
    UINT16 XRAM usBaseTrackReg;

        /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);
        
	usBaseTrackReg = Drv_XsiReadReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucId+4,AFE_REG);
                                 
    usBaseTrackReg |= ((ucStep<<BIT_BASE_TRACK_STEP)          //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
                     +(ucBaseMode<<BIT_BASE_TRACK_MODE)      //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
                     +(1<<BIT_BASE_TRACK_ENABLE));           //[0] Montior模式，Base跟踪使能，1:使能 


    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucId+4,usBaseTrackReg,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*ucId+4,usBaseTrackReg,AFE_REG);
}


/*******************************************************************************
*   Name: DrvAfeSetHCBTarget
*  Brief: 硬件CB校正的目标值
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSetHCBTarget(UINT16 usTpCbTarget,UINT16 usKeyCbTarget)
{                                                              
    Drv_XsiWriteReg(pXSI0Regs,Addr_CB_ADJUST_THLD_TP, usTpCbTarget, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_CB_ADJUST_THLD_TP, usTpCbTarget, AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,Addr_CB_ADJUST_THLD_TP, usKeyCbTarget, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_CB_ADJUST_THLD_TP, usKeyCbTarget, AFE_REG); 	
}

/*******************************************************************************
*   Name:  DrvAfeSetHCBThld
*  Brief:  触摸检测tp,key门限
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSetHCBThld(UINT16 usTpThld,UINT16 usKeyThld)
{                                                              
    Drv_XsiWriteReg(pXSI0Regs,Addr_TP_MONITOR_THRESHOLD,usTpThld, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_TP_MONITOR_THRESHOLD,usTpThld, AFE_REG);   

    Drv_XsiWriteReg(pXSI0Regs,Addr_KEY_MONITOR_THRESHOLD,usKeyThld, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_KEY_MONITOR_THRESHOLD,usKeyThld, AFE_REG);    
}

/*******************************************************************************
*   Name: DrvAfeInitBase
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvAfeInitBase(void)
{
    UINT16 XRAM i;
    UINT16 XRAM usBaseBuff[CH_LEN_MAX];

    DBG_FLOW("\nDrvAfeInitBase begin");
    /* set ram  as  BaseRam */
    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);

// Write Base    
    for (i = 0; i < CH_LEN_MAX; i++)
    {
       usBaseBuff[i] = 1024;     
    }
    
#if TEMP_CLOSE_KEY
    usBaseBuff[CH_LEN_MAX-1] = 0;
    usBaseBuff[CH_LEN_MAX-2] = 0;
    usBaseBuff[CH_LEN_MAX-3] = 0;
    usBaseBuff[CH_LEN_MAX-4] = 0;
#endif
    
    Drv_XsiWrite(pXSI0Regs,BASE_RAM_START_ADDR + BASE_RAM_TP_RAWBASE_ADDR,usBaseBuff,CH_LEN_MAX,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,BASE_RAM_START_ADDR + BASE_RAM_TP_RAWBASE_ADDR,usBaseBuff,CH_LEN_MAX,AFE_REG);
    
// read Base    
    //DrvGetRptRamRawBase();
    DBG_FLOW("\nDrvAfeInitBase finished");
//    while(1);
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
#if TEMP_CLOSE_KEY 
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0;      //4个按键:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0;
#else
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0100;      //4个按键:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0100;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0100;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0100;
#endif    
    Drv_XsiWrite(pXSI0Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
#if TEST_KEY_DET
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0;      //4个按键:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0;
    Drv_XsiWrite(pXSI0Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
#endif
}




/*******************************************************************************
*  Brief: 表项0配置。一共有4个表项 , FreeRun 测试
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Config_Tab0(void)
{
//    UINT16 XRAM i;
//    UINT16 XRAM usTblBaseAddr;
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

//    usReg0 = rAFE_SYS_CFG1|(1<<7);  //DAT_ACC_ASR 测试累和右移
    usReg0 = rAFE_SYS_CFG1|(0<<7);  //DAT_ACC_ASR
    
    usReg1 = rAFE_SCAN_CFG0;
    usReg1 =((1<<BIT_AFE_SCAN_TIMES) +(4<<BIT_AFE_SCAN_MODE));  //方式5 单个坑内扫描5个1/5,扫描次数，实际值为配置值加1; 输出数据次数不加1.即: 配置为1，实际扫描2次，数据只出1次。配0，扫描1次，无值输出。 
//    usReg1 =((1<<BIT_AFE_SCAN_TIMES) +(7<<BIT_AFE_SCAN_MODE));  //方式8 5个接一起,数据通过第一个mux1选择输出，如:mux1:G1,G9, 出G1,G9数据，但触摸任意位置可进DET中断。 
                      
#if TEST_ONE_CHANNEL_ADC
    usReg1 =((5<<BIT_AFE_SCAN_TIMES)             //扫描次数，实际值为配置值加1; 输出数据次数不加1.即: 配置为1，实际扫描2次，数据只出1次。配0，扫描1次，无值输出。 波形只有一个mux.
            +(4<<BIT_AFE_SCAN_MODE));             //方式5 单个坑内扫描5个1/5
#endif
    
    usReg2 = rAFE_SCAN_CFG1;
    usReg2 =((0<<9)               //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减      
            +(0<<8)               //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
            +(4<<0));             //[0] 方式6，扫描段数  

#if 1 //双边3种模式
#if TEST_2SAMPLE_ANA_SUB
     usReg2 =((0<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 0:双边采样，模拟相减;     [8]双边扫描
#endif
#if TEST_2SAMPLE_POSITIVE
     usReg2 =((1<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 1:负边采样;     [8]双边扫描
#endif
#if TEST_2SAMPLE_NEGATIVE
     usReg2 =((2<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 2:正边采样;     [8]双边扫描
#endif
     usReg8 = rAFE_ANA_K1_CFG0;
     usReg9 = rAFE_ANA_K2_CFG1;
#endif     
          
    usReg3 = rAFE_DUMMY_SCAN_CFG;
    usReg3 =((1<<10)               //[14:10]Mux切换之间Dummy次数    
            +(0<<5)                //[9:5]坑前Dummy次数
            +(2<<0));              //[4:0]Tp帧前Dummy次数    
            
    usReg4 = rAFE_BASE_TRACK_CFG;
    usReg4 = ((80<<BIT_BASE_TRACK_STEP)             //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
             +(0<<BIT_BASE_TRACK_MODE)              //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
             +(1<<BIT_BASE_TRACK_ENABLE));          //[0] Montior模式，Base跟踪使能，1:使能 

    usReg5 = 0x100; //rACC_OFFSET;        //测试ACC Offset值 
#if IS_4_MUX_MODE
    usReg5 = 256;                //key只支持数字相减，理论值为0，要加Offset.
#endif
    
#if TEST_2SAMPLE_DIG_SUB //双边扫描, 双边采样，数字相减   
    usReg2 =((3<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 3:双边采样，数字相减   [8]双边扫描
    usReg5 = 256;       //测试ACC Offset值
    usReg8 = rAFE_ANA_K1_CFG0*2;
    usReg9 = rAFE_ANA_K2_CFG1*3;
#endif    

    usReg6 = rTP_MONITOR_THRESHOLD;
    usReg7 = rKEY_MONITOR_THRESHOLD;

#if TEST_1SAMPLE //单边扫描,单边采样
    usReg2 =((0<<9)+(1<<8)+(4<<0));               //[8]单边扫描(仅1种单边采样)  

    usReg8 = rAFE_ANA_K1_CFG0*2;
    usReg9 = rAFE_ANA_K2_CFG1*3;
#endif

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
    
#if 1
    Afe_SetTabCBChEN(0);
#else
//    DrvClbCB(0);
#endif
}

/*******************************************************************************
*  Brief: 表项1配置。一共有4个表项 , 120hz 测试
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Config_Tab1(void)
{
//    UINT16 XRAM i;
    UINT8 XRAM ucScanMode;
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

    ucScanMode = SCAN_MODE_1;   //测试扫描方式

#if TEST_MUX_ABC_SACN    
    ucScanMode = SCAN_MODE_2;   //测试扫描方式2_2_1
#endif

#if TEST_MUX_ABCD_SACN    
    ucScanMode = SCAN_MODE_3;   //测试扫描方式3_2
#endif

#if TEST_60HZ_SCAN_MODE
    ucScanMode = SCAN_MODE_5;   //测试扫描方式
#endif


    usReg0 = rAFE_SYS_CFG1;
    
    usReg1 = rAFE_SCAN_CFG0;

    usReg2 = rAFE_SCAN_CFG1;
    usReg2 =((0<<9)               //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减      
            +(0<<8)               //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
            +(4<<0));             //[0] 方式6，扫描段数  
//   usReg2 =((0<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 0:双边采样，模拟相减;     [8]双边扫描
//   usReg2 =((1<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 1:负边采样;     [8]双边扫描
//   usReg2 =((2<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 2:正边采样;    [8]双边扫描
//   usReg2 =((3<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 3:双边采样，数字相减   [8]双边扫描
//   usReg2 =((0<<9)+(1<<8)+(4<<0));               //[8]单边扫描(仅1种单边采样) 

    switch(ucScanMode)
    {
        case SCAN_MODE_1:
            usReg1 =((1<<BIT_AFE_SCAN_TIMES)+(0<<BIT_AFE_SCAN_MODE));       //方式1: 单个坑内只扫描1个1/5屏的通道
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                    +(2<<5)                //[9:5]坑前Dummy次数
                    +(0<<0));              //[4:0]Tp帧前Dummy次数   
            break;
        case SCAN_MODE_2:
            usReg1 =((4<<BIT_AFE_SCAN_TIMES)+(1<<BIT_AFE_SCAN_MODE));     //方式2: 单个坑内只扫描2或1个1/5屏的通道 即:A:2_2_1+B:2_2_1
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                    +(2<<5)                //[9:5]坑前Dummy次数
                    +(0<<0));              //[4:0]Tp帧前Dummy次数   
            break;
        case SCAN_MODE_3:
            usReg1 =((2<<BIT_AFE_SCAN_TIMES)+(2<<BIT_AFE_SCAN_MODE));     //方式3: 单个坑内只扫描3或2个1/5屏的通道 即:A:3_2+B:3_2
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                    +(1<<5)                //[9:5]坑前Dummy次数
                    +(1<<0));              //[4:0]Tp帧前Dummy次数   
            break;
        case SCAN_MODE_4:
            usReg1 =((2<<BIT_AFE_SCAN_TIMES)+(3<<BIT_AFE_SCAN_MODE));     //方式4: 单个坑内只扫描2或3个1/5屏的通道 即:A:2_3+B:2_3
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                   +(2<<5)                 //[9:5]坑前Dummy次数
                   +(0<<0));               //[4:0]Tp帧前Dummy次数   
            break;
        case SCAN_MODE_5:
            usReg1 =((1<<BIT_AFE_SCAN_TIMES)+(4<<BIT_AFE_SCAN_MODE));     //方式5: 
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                    +(0<<5)                //[9:5]坑前Dummy次数
                    +(0<<0));              //[4:0]Tp帧前Dummy次数   
            break;
        case SCAN_MODE_6:
            usReg1 =((1<<BIT_AFE_SCAN_TIMES)+(5<<BIT_AFE_SCAN_MODE));     //方式6: 单个坑内只扫描5个1/5屏的通道，且多坑累加，段式 
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                    +(0<<5)                //[9:5]坑前Dummy次数
                    +(0<<0));              //[4:0]Tp帧前Dummy次数   
            usReg2 =((0<<9)                //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减      
                    +(0<<8)                //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
                    +(4<<0));              //[0] 方式6，扫描段数                     
            break;
        case SCAN_MODE_7:
           usReg1 =((1<<BIT_AFE_SCAN_TIMES)+(6<<BIT_AFE_SCAN_MODE));     //方式7: 单个坑内只扫描2或1个mux,即mux9模式即:A:2_2_2_2_1+B:2_2_2_2_1
           usReg3 = rAFE_DUMMY_SCAN_CFG;                                 //9个mux依次扫描，9个mux后，完成全屏扫描。
           usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                   +(2<<5)                //[9:5]坑前Dummy次数
                   +(0<<0));              //[4:0]Tp帧前Dummy次数   
            break;
        case SCAN_MODE_8:
           usReg1 =((2<<BIT_AFE_SCAN_TIMES)+(7<<BIT_AFE_SCAN_MODE));     //方式8: 仅扫描1个Mux,完成全屏扫描，即Monitor,5个SX相连模式，G1234 G56789, 
           usReg3 = rAFE_DUMMY_SCAN_CFG;                                 //只有mux1 G1G9数据会发生变化，应用在触摸唤醒。
           usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                   +(2<<5)                //[9:5]坑前Dummy次数
                   +(0<<0));              //[4:0]Tp帧前Dummy次数   
            break;
        default:
            break;
    }
                                        
    usReg4 = rAFE_BASE_TRACK_CFG;
    usReg4 = ((80<<BIT_BASE_TRACK_STEP)             //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
              +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
              +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montior模式，Base跟踪使能，1:使能 
    
    usReg5 = rACC_OFFSET;
    usReg5 = 0x100; 
    usReg6 = 188; //rTP_MONITOR_THRESHOLD;
    usReg7 = 188; //rKEY_MONITOR_THRESHOLD;
    usReg8 = rAFE_ANA_K1_CFG0;
    usReg9 = rAFE_ANA_K2_CFG1;

    /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    //tab 1
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+1,usReg1,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+1,usReg1,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+2,usReg2,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+2,usReg2,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+5,usReg5,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+5,usReg5,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+6,usReg6,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+6,usReg6,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+7,usReg7,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+7,usReg7,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+8,usReg8,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+8,usReg8,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN+9,usReg9,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN+9,usReg9,AFE_REG);
    
#if 1
    Afe_SetTabCBChEN(1);
#else
//    DrvClbCB(0);
#endif
}

/*******************************************************************************
*  Brief: 表项2配置。一共有4个表项 ,  monitor 测试
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Config_Tab2(void)
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

    usReg0 = rAFE_SYS_CFG1;

#if TEST_FREERUN_MONITOR //freerun monitor    
    usReg1 = rAFE_SCAN_CFG0;
    usReg1 =((1<<BIT_AFE_SCAN_TIMES)                //扫描次数，实际值为配置值加1;  
            +(4<<BIT_AFE_SCAN_MODE));               //方式5

    usReg3 = rAFE_DUMMY_SCAN_CFG;
    usReg3 =((1<<10)                                //[11:8]Mux切换之间Dummy次数    
            +(0<<5)                                 //[7:4]坑前Dummy次数
            +(2<<0));                               //[3:0]Tp帧前Dummy次数    

    //设置触摸检测时，TP,key通道的触摸阈值     
    usReg6 = 100; //rTP_MONITOR_THRESHOLD;
    usReg7 = 2000; //rKEY_MONITOR_THRESHOLD;          //自容key只有数字相减模式
#endif

#if TEST_120HZ_MONTIOR// normal 120hz  
    usReg1 = rAFE_SCAN_CFG0;
    usReg1 =((1<<BIT_AFE_SCAN_TIMES)               //扫描次数，实际值为配置值加1;  
            +(0<<BIT_AFE_SCAN_MODE));              //方式1

    usReg3 = rAFE_DUMMY_SCAN_CFG;
    usReg3 =((1<<10)               //[11:8]Mux切换之间Dummy次数    
            +(0<<5)               //[7:4]坑前Dummy次数
            +(2<<0));             //[3:0]Tp帧前Dummy次数  
    //设置触摸检测时，TP,key通道的触摸阈值     
    usReg6 = 18; //rTP_MONITOR_THRESHOLD;
    usReg7 = 18; //rKEY_MONITOR_THRESHOLD;
#endif

            
    usReg2 = rAFE_SCAN_CFG1; 
    usReg2 =((0<<9)               //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减      
            +(0<<8)               //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
            +(4<<0));             //[0] 方式6，扫描段数             

    //设置成步进跟踪,    跟踪步长32(0x20)        
    usReg4 = rAFE_BASE_TRACK_CFG;
    usReg4 = ((32<<BIT_BASE_TRACK_STEP)             //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
             // +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 
              +(1<<BIT_BASE_TRACK_MODE)             //[1] Monitor模式，Base跟踪方式:   1:原值跟踪
              +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montior模式，Base跟踪使能，1:使能 
              
    usReg5 = 100;//rACC_OFFSET;
    
    
    usReg8 = rAFE_ANA_K1_CFG0;
    usReg9 = rAFE_ANA_K2_CFG1;

    /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    //tab 2
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+1,usReg1,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+1,usReg1,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+2,usReg2,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+2,usReg2,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+5,usReg5,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+5,usReg5,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+6,usReg6,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+6,usReg6,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+7,usReg7,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+7,usReg7,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+8,usReg8,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+8,usReg8,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*2+9,usReg9,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*2+9,usReg9,AFE_REG);
    
#if 1
    Afe_SetTabCBChEN(2);
#else
//    DrvClbCB(0);
#endif
}
/*******************************************************************************
*  Brief: 表项3配置。一共有4个表项 , 硬件CB校正 测试
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Config_Tab3(void)
{
//    UINT16 XRAM i;
//    UINT16 XRAM usTblBaseAddr;
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

    usReg0 = rAFE_SYS_CFG1;
    
    usReg1 = rAFE_SCAN_CFG0;
    usReg1 =((2<<BIT_AFE_SCAN_TIMES)               //扫描次数，实际值为配置值加1;  
            +(4<<BIT_AFE_SCAN_MODE));             //方式0
            
    usReg2 = rAFE_SCAN_CFG1;
    usReg2 =((0<<9)               //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减      
            +(0<<8)               //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
            +(4<<0));             //[0] 方式6，扫描段数  
            
    usReg3 = rAFE_DUMMY_SCAN_CFG;
    usReg3 =((1<<10)               //[14:10]Mux切换之间Dummy次数    
            +(0<<5)               //[9:5]坑前Dummy次数
            +(2<<0));             //[4:0]Tp帧前Dummy次数   
            
    usReg4 = rAFE_BASE_TRACK_CFG;
    usReg4 = ((80<<BIT_BASE_TRACK_STEP)             //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
              +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
              +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montior模式，Base跟踪使能，1:使能 
              
    usReg5 = rACC_OFFSET;
    usReg6 = rTP_MONITOR_THRESHOLD;
    usReg7 = rKEY_MONITOR_THRESHOLD;
    usReg8 = rAFE_ANA_K1_CFG0;
    usReg9 = rAFE_ANA_K2_CFG1;

    /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    //tab 3
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+1,usReg1,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+1,usReg1,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+2,usReg2,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+2,usReg2,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+5,usReg5,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+5,usReg5,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+6,usReg6,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+6,usReg6,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+7,usReg7,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+7,usReg7,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+8,usReg8,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+8,usReg8,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+9,usReg9,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+9,usReg9,AFE_REG);
    
#if 1
    Afe_SetTabCBChEN(3);
#else
    DrvClbCB(0);
#endif
}


/*******************************************************************************
*  Brief: 表项3配置。一共有4个表项 , 硬件CB校正 测试
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Change_Tab3(UINT8 ucTestMode,UINT8 ucScanMode,UINT8 usScanNum)
{
//    UINT16 XRAM i;
//    UINT16 XRAM usTblBaseAddr;
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

    switch(ucTestMode)
    {
        case 0:                 //CB
        {
            usReg0 = rAFE_SYS_CFG1;
            
            usReg1 = rAFE_SCAN_CFG0;


            usReg1 =(((usScanNum)<<BIT_AFE_SCAN_TIMES)                   //扫描次数，实际值为配置值加1;  
                    +(ucScanMode<<BIT_AFE_SCAN_MODE));                   //扫描方式

            usReg2 = rAFE_SCAN_CFG1;
            usReg2 =((0<<9)               //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减      
                    +(0<<8)               //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
                    +(4<<0));             //[0] 方式6，扫描段数  
                    
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((1<<10)               //[14:10]Mux切换之间Dummy次数    
                    +(0<<5)               //[9:5]坑前Dummy次数
                    +(2<<0));             //[4:0]Tp帧前Dummy次数   
                    
            usReg4 = rAFE_BASE_TRACK_CFG;
            usReg4 = ((80<<BIT_BASE_TRACK_STEP)             //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
                      +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
                      +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montior模式，Base跟踪使能，1:使能 
                      
            usReg5 = rACC_OFFSET;
            usReg6 = rTP_MONITOR_THRESHOLD;
            usReg7 = rKEY_MONITOR_THRESHOLD;
            usReg8 = rAFE_ANA_K1_CFG0;
            usReg9 = rAFE_ANA_K2_CFG1;            
            break;
        }

        case 1:             // hw monitor
        {
            usReg0 = rAFE_SYS_CFG1;
  
            usReg1 = rAFE_SCAN_CFG0;
            usReg1 =(((usScanNum)<<BIT_AFE_SCAN_TIMES)      //扫描次数，实际值为配置值加1;  
                    +(ucScanMode<<BIT_AFE_SCAN_MODE));      //扫描方式


            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((1<<10)                                //[11:8]Mux切换之间Dummy次数    
                    +(0<<5)                                 //[7:4]坑前Dummy次数
                    +(2<<0));                               //[3:0]Tp帧前Dummy次数    

            //设置触摸检测时，TP,key通道的触摸阈值     
            usReg6 = 20; //rTP_MONITOR_THRESHOLD;
            usReg7 = 20; //rKEY_MONITOR_THRESHOLD;  

                    
            usReg2 = rAFE_SCAN_CFG1; 
            usReg2 =((0<<9)               //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减      
                    +(0<<8)               //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
                    +(4<<0));             //[0] 方式6，扫描段数             

            //设置成步进跟踪,    跟踪步长32(0x20)        
            usReg4 = rAFE_BASE_TRACK_CFG;
            usReg4 = ((32<<BIT_BASE_TRACK_STEP)             //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
                     // +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 
                      +(1<<BIT_BASE_TRACK_MODE)             //[1] Monitor模式，Base跟踪方式:   1:原值跟踪
                      +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montior模式，Base跟踪使能，1:使能 
                      
            usReg5 = rACC_OFFSET;
            
            
            usReg8 = rAFE_ANA_K1_CFG0;
            usReg9 = rAFE_ANA_K2_CFG1;            
            
            break;
        }

        case 2:           //mcap
        {
            usReg0 = rAFE_SYS_CFG1|(0<<7);  //DAT_ACC_ASR
            usReg1 =((usScanNum<<BIT_AFE_SCAN_TIMES)        //扫描次数，实际值为配置值加1,但第1个tx固定为dummy;  
                    +(ucScanMode<<BIT_AFE_SCAN_MODE));      //扫描方式

            
            usReg2 =((0<<9)+(0<<8)+(4<<0));               //[10:9] 采样模式: 0:双边采样，模拟相减;     [8]双边扫描

            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux切换之间Dummy次数    
                    +(0<<5)                //[9:5]坑前Dummy次数
                    +(0<<0));              //[4:0]Tp帧前Dummy次数  

            usReg4 = rAFE_BASE_TRACK_CFG;
            usReg4 = ((0<<BIT_BASE_TRACK_STEP)             //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                                 
                     +(0<<BIT_BASE_TRACK_MODE)              //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
                     +(1<<BIT_BASE_TRACK_ENABLE));          //[0] Montior模式，Base跟踪使能，1:使能 

            usReg5 = rACC_OFFSET;        //测试ACC Offset值             

            usReg6 = rTP_MONITOR_THRESHOLD;
            usReg7 = rKEY_MONITOR_THRESHOLD;

			/*双边扫描时最快扫描频率是120KHz,单边采样最快扫描频率是60KHz*/

#if 1		                 //120khz	
             usReg8 = 0x9B;
             usReg9 = 0x2E;
#elif 1                      //60k
			usReg8 = 0xC2;
			usReg9 = 0xD2;
#else                        //100k
			usReg8 = 0xC2;
			usReg9 = 0x2E;		
#endif
             break;
        }

        default:
            break;
    }


    /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    //tab 3
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+0,usReg0,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+1,usReg1,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+1,usReg1,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+2,usReg2,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+2,usReg2,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+3,usReg3,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+4,usReg4,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+5,usReg5,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+5,usReg5,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+6,usReg6,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+6,usReg6,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+7,usReg7,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+7,usReg7,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+8,usReg8,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+8,usReg8,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*3+9,usReg9,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*3+9,usReg9,AFE_REG);
    
#if 1
    Afe_SetTabCBChEN(3);
#else
//    DrvClbCB(0);
#endif
}



/*******************************************************************************
*   Name: DrvSetCbDir
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvSetCbDir(UINT8 ucTpDir,UINT8 ucKeyDir)
{
    UINT16 XRAM Reg4;
    Reg4 = Drv_XsiReadReg(pXSI0Regs, Addr_AFE_SYS_CFG0, AFE_REG);

    Reg4 &= 0xF9FF;
	Reg4 |= (ucKeyDir<<10)|(ucTpDir<<9);
	
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, Reg4, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, Reg4, AFE_REG);    
}


/*******************************************************************************
*   Name: DrvGetTabRamCb
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvGetTabRamCb(void)
{
    UINT16 XRAM i;
    UINT16 XRAM aus_tabbuf[TAB_RAM_LEN - 10];

    DBG_FLOW("\nRead CB from TabRam");
    DBG_FLOW("\nAFE_L CB:");
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);
    Drv_XsiRead(pXSI0Regs,TAB_RAM_START_ADDR+3*TAB_RAM_LEN + 10,aus_tabbuf,TAB_RAM_LEN - 10,AFE_REG);

    for(i = 4; i < TAB_RAM_LEN - 10;i++)
    {
        if((i%18) == 4)
        {
            DBG_FLOW("\n");
        }
        
        DBG_FLOW("%04x  ",aus_tabbuf[i]);    
    }
    
    DBG_FLOW("\n\n");
    DBG_FLOW("\nAFE_R CB:");    
    Drv_XsiRead(pXSI1Regs,TAB_RAM_START_ADDR+3*TAB_RAM_LEN + 10,aus_tabbuf,TAB_RAM_LEN - 10,AFE_REG);
    for(i = 4; i < TAB_RAM_LEN - 10;i++)
    {    
        if((i%18) == 4)
        {
            DBG_FLOW("\n");
        }        
        DBG_FLOW("%04x  ",aus_tabbuf[i]);     
    }

    DBG_FLOW("\n\n");
    DBG_FLOW("AFE_KEY CB:\n");
    Drv_XsiRead(pXSI0Regs,TAB_RAM_START_ADDR+3*TAB_RAM_LEN + 10,aus_tabbuf,4,AFE_REG); 
    for(i = 0; i < 4; i++)
    {
        DBG_FLOW("%04x  ",aus_tabbuf[i]); 
    }
    Drv_XsiRead(pXSI1Regs,TAB_RAM_START_ADDR+3*TAB_RAM_LEN + 10,aus_tabbuf,4,AFE_REG); 
    for(i = 0; i < 4; i++)
    {
        DBG_FLOW("%04x  ",aus_tabbuf[i]); 
    }    
}



/*******************************************************************************
*   Name: DrvSetTabMonThr
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvSetTabMonThr(UINT16 usTpMonThr,UINT16 usKeyMonThr,UINT8 usTabId)
{
        /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);
        
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*usTabId+6,usTpMonThr,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*usTabId+6,usTpMonThr,AFE_REG);
    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*usTabId+7,usKeyMonThr,AFE_REG); 
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*usTabId+7,usKeyMonThr,AFE_REG);
}

/*******************************************************************************
*   Name: DrvMcapSetMode
*  Brief: 互容按键启动设置 
*  Input: ucModeEn  0:关闭互容按键;1:开启互容按键
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetMode(UINT8 ucModeEn)
{
    UINT16 XRAM Reg64 = 0;

    Reg64 = Drv_XsiReadReg(pXSIREG,Addr_MCAP_SCAN_CFG,AFE_REG);
    Reg64 &= ~(1<<15);
    if(ucModeEn)           //开启互容按键 
    {
        Reg64 |= (1<<15);             
    }

    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);    
}

/*******************************************************************************
*   Name: DrvMcapSetFir
*  Brief: 互容按键采样率配置 
*  Input: ucMode  0:6倍采样率;1:8倍采样率
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetFir(ST_McapParameter * pMcapPara)
{
    UINT16 XRAM Reg79 = 0,Reg66 = 0;

    //Reg79 = Drv_XsiReadReg(pXSI0Regs,0x4F,AFE_REG);

    //Reg79 &= 0x7FE0;           //清除mcap_hbfir_en/mcap_lpfir_en/mcap_lipfir_tap

    if(pMcapPara->usHbFirEn)
    {
        //Reg79 |= (1<<15);        //开启mcap_hbfir_en 
        ;
    }
    else
    {
        pMcapPara->usLpFirEn = 0;//关闭mcap_hbfir_en，需同时关闭mcap_lpfir_en
    }

#if 0    
    if(pMcapPara->usLpFirEn)
    {
        Reg79 |=(1<<4);         //开启mcap_lpfir_en
    }
#endif

    //Reg79 |=(0x0F&pMcapPara->usLpFirTap);   //mcap_lpfir_tap

    DBG_FLOW("\nLpFirTap:%d",pMcapPara->usLpFirTap);
    DBG_FLOW("\nLpFirStart:%d",pMcapPara->usLpFirStart);

    if(pMcapPara->usLpFirTap > pMcapPara->usLpFirStart)
    {
        DBG_FLOW("\nLpFirStart should be not smaller than LpFirTap");
        //pMcapPara->usLpFirStart = pMcapPara->usLpFirTap;
    }
#if 0
    Reg79 |= (((0x1F&pMcapPara->usLpFirStart)<<10)\         
          +  ((pMcapPara->usHbFirEn)<<15)\
          +  ((pMcapPara->usLpFirEn)<<4)\
          +  (0x0F&pMcapPara->usLpFirTap)\                  
          +  ((0x1F&pMcapPara->usLpFirSumNum)<<5));         
#else
    Reg79 = (((0x1F&pMcapPara->usLpFirStart)<<10)\         
          +  ((pMcapPara->usHbFirEn)<<15)\
          +  ((pMcapPara->usLpFirEn)<<4)\
          +  (0x0F&pMcapPara->usLpFirTap));

    Reg66 = (0x1FF&pMcapPara->usLpFirSumNum);
    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_LPFIR_SUM_NUM,Reg66,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_LPFIR_SUM_NUM,Reg66,AFE_REG);

#endif
    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_LPFIR_CFG,Reg79,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_LPFIR_CFG,Reg79,AFE_REG);     


#if 0        
    Drv_XsiWriteReg(pXSI0Regs,0x50,pMcapPara->usLpFirCof0,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,0x50,pMcapPara->usLpFirCof0,AFE_REG); 

    Drv_XsiWriteReg(pXSI0Regs,0x51,pMcapPara->usLpFirCof1,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,0x51,pMcapPara->usLpFirCof1,AFE_REG); 

    Drv_XsiWriteReg(pXSI0Regs,0x52,pMcapPara->usLpFirCof2,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,0x52,pMcapPara->usLpFirCof2,AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs,0x53,pMcapPara->usLpFirCof3,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,0x53,pMcapPara->usLpFirCof3,AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs,0x54,pMcapPara->usLpFirCof4,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,0x54,pMcapPara->usLpFirCof4,AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs,0x55,pMcapPara->usLpFirCof5,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,0x55,pMcapPara->usLpFirCof5,AFE_REG); 

    Drv_XsiWriteReg(pXSI0Regs,0x56,pMcapPara->usLpFirCof6,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,0x56,pMcapPara->usLpFirCof6,AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs,0x57,pMcapPara->usLpFirCof7,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,0x57,pMcapPara->usLpFirCof7,AFE_REG);
#endif    
}



/*******************************************************************************
*   Name: DrvMcapSetSampleRate
*  Brief: 互容按键采样率配置 
*  Input: ucMode  0:6倍采样率;1:8倍采样率
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetSampleRate(ST_McapParameter * pMcapPara,ST_AfeTabList * pAfeTabPara,UINT8 ucTabId)
{
    UINT16 XRAM Reg1 = pAfeTabPara->usScanCfg0;
    UINT16 XRAM Reg2 = pAfeTabPara->usScanCfg1;
    UINT16 XRAM Reg3 = pAfeTabPara->usDummyScanCfg;
    UINT16 XRAM Reg64 = 0;
    UINT16 XRAM ucTemp;
    
    Reg64 = Drv_XsiReadReg(pXSIREG,Addr_MCAP_SCAN_CFG,AFE_REG);

    if(pMcapPara->usSampl_6 == 0)
    {
        Reg64 |= (1<<4);      //8倍采样率         
    }
    else
    {
        Reg64 &= ~(1<<4);    //6倍采样率

        ucTemp = (pMcapPara->usK1+pMcapPara->usK2+2)/3;

        DBG_FLOW("\nkey_sampl_6:%04x",ucTemp);

        DrvAfeSelTaborRepRam(AREA_TBL_RAM);

        Reg1 |= (((ucTemp&0x07C0) >>6)<<11);  //key_sampl_interval_6[10:6]        
        Reg2 |= (((ucTemp&0x003E) >>1)<<11);  //key_sampl_interval_6[5:1]
        Reg3 |= (((ucTemp&0x0001) >>0)<<15);  //key_sampl_interval_6[0]

        DBG_FLOW("\nReg1:%04x",Reg1);
        DBG_FLOW("\nReg2:%04x",Reg2);
        DBG_FLOW("\nReg3:%04x",Reg3);

        Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+1,Reg1,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+1,Reg1,AFE_REG);
        Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+2,Reg2,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+2,Reg2,AFE_REG); 
        Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+3,Reg3,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+3,Reg3,AFE_REG); 
        pAfeTabPara->usScanCfg0 = Reg1;
        pAfeTabPara->usScanCfg1 = Reg2;
        pAfeTabPara->usDummyScanCfg =Reg3;
       
    }
    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);        
}


/*******************************************************************************
*   Name: DrvMcapSetSampleInit
*  Brief: 互容按键采样起始点设置 
*  Input: ucInit  [9:0] 采样起始点配置
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetSampleInit(ST_McapParameter * pMcapPara)
{
    /*采样起始点配置mcap_int_sampl_cfg*/
    pMcapPara->usSampl_Init &= 0x03FF;//只有后10位有效
    if(pMcapPara->usSampl_Init > ((pMcapPara->usK1+pMcapPara->usK2+2)*2))
    {
        pMcapPara->usSampl_Init = (pMcapPara->usK1+pMcapPara->usK2+2)*2;  //最大不能超过(K1+K2+2)*2
    }
    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_INIT_SAMPL_CFG,pMcapPara->usSampl_Init,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_INIT_SAMPL_CFG,pMcapPara->usSampl_Init,AFE_REG);
}

/*******************************************************************************
*   Name: DrvMcapSetAnaTiming
*  Brief: 互容按键模拟时序配置 
*  Input: ucDataInv/ucMsbInv
* Output: 
* Return: 
*******************************************************************************/
UINT8 DrvMcapSetAnaTiming(ST_McapParameter * pMcapPara,UINT8 ucScanMode)   
{
    UINT8 XRAM ucDummyNum;
    UINT8 XRAM flag = 0;

    /* 单个mux用到的最大dummy数 */
    switch(ucScanMode)
    {
        case 0://扫描方式1
        case 1://扫描方式2
        case 2://扫描方式3
        case 3://扫描方式4
        case 6://扫描方式7
        case 7:
        {
            if(pMcapPara->usFrmDummy > pMcapPara->usMuxDummy)
            {
                ucDummyNum = pMcapPara->usFrmDummy + pMcapPara->usSecDummy;
            }
            else
            {
                ucDummyNum = pMcapPara->usMuxDummy + pMcapPara->usSecDummy;
            }
            break;
        }
                
        case 4://扫描方式5
        {
            if((pMcapPara->usFrmDummy + pMcapPara->usSecDummy) > pMcapPara->usMuxDummy)
            {
                ucDummyNum = pMcapPara->usFrmDummy + pMcapPara->usSecDummy;
            }
            else
            {
                ucDummyNum = pMcapPara->usMuxDummy;
            }
            break;
        }

        case 5://扫描方式6
        {
            DBG_FLOW("\nMcap is nont supported to scan mode six!!!");
            DBG_FLOW("\nChange to Scap!!!");
            DrvMcapSetMode(FALSE);
            return 0;
        }

        default:
        {
            DBG_FLOW("\nInput Scan Mode Err");
            return 0;
        }       
    }

    if(pMcapPara->usLpFirTap == 14)//14阶
    {
        if((pMcapPara->usLpFirEn)&&(pMcapPara->usHbFirEn))
        {
            if((pMcapPara->usSxMode == 0)&&(pMcapPara->usSampl_6 == 1))//双边扫描,6倍采样
            {
                if(pMcapPara->usScanNum < (ucDummyNum + 13))
                {
                    flag = 1;
                    DBG_FLOW("\nScanNum is not large enough1!");
                    DBG_FLOW("\nlast ScanNum:%d,new ScanNum:%d",pMcapPara->usScanNum,ucDummyNum + 13);
                    pMcapPara->usScanNum = ucDummyNum + 13;
                } 
            }

            if((pMcapPara->usSxMode == 1)&&(pMcapPara->usSampl_6 == 1))//单边扫描,6倍采样
            {
                if(pMcapPara->usScanNum < (ucDummyNum + 13)*2)
                {
                    flag = 1;
                    DBG_FLOW("\nScanNum is not large enough2!");
                    DBG_FLOW("\nlast ScanNum:%d,new ScanNum:%d",pMcapPara->usScanNum,(ucDummyNum + 13)*2);
                    pMcapPara->usScanNum = (ucDummyNum + 13)*2;
                } 
            }

            if((pMcapPara->usSxMode == 0)&&(pMcapPara->usSampl_6 == 0))//双边扫描,8倍采样
            {
                if(pMcapPara->usScanNum < (ucDummyNum + 11))
                {
                    flag = 1;
                    DBG_FLOW("\nScanNum is not large enough3!");
                    DBG_FLOW("\nlast ScanNum:%d,new ScanNum:%d",pMcapPara->usScanNum,(ucDummyNum + 11));
                    pMcapPara->usScanNum = (ucDummyNum + 11);
                } 
            }

            if((pMcapPara->usSxMode == 1)&&(pMcapPara->usSampl_6 == 0))//单边扫描,8倍采样
            {
                if(pMcapPara->usScanNum < (ucDummyNum + 11)*2)
                {
                    flag = 1;
                    DBG_FLOW("\nScanNum is not large enough4!");
                    DBG_FLOW("\nlast ScanNum:%d,new ScanNum:%d",pMcapPara->usScanNum,(ucDummyNum + 13)*2);
                    pMcapPara->usScanNum = (ucDummyNum + 11)*2;
                }  
            }
        }
    }
    return flag;
}

/*******************************************************************************
*   Name: DrvMcapSetDiffMax
*  Brief: 互容按键是否计算key通道的diff_max
*  Input: ucEn/ucMode
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetDiffMax(ST_McapParameter* pMcapPara)                       
{
    UINT16 XRAM Reg64,Reg65;

    Reg64 = Drv_XsiReadReg(pXSIREG,0x40,AFE_REG);

    Reg64 &= ~(1<<14);                                  //不进行diff max计算

    if((pMcapPara->usDiffSet)&0x02) 
    {
        Reg64 |= (1<<14);                                  //进行diff max计算
        Reg65 = Drv_XsiReadReg(pXSIREG,0x41,AFE_REG);
        Reg65 &= ~(1<<3);                                 //对ADC数据进行diff_max运算
        if(pMcapPara->usDiffSet == 0x03)
        {
            Reg65 |= (1<<3);                              //对解调后的数据,即mixer数据进行diff_max运算         
        
        Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCANSR,Reg65,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCANSR,Reg65,AFE_REG);  
    }

    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);    
    }
}
/*******************************************************************************
*   Name: DrvMcapSetRawGain
*  Brief: 互容按键是否对RAWDATA进行增益处理
*  Input: ucEn
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetRawGain(ST_McapParameter* pMcapPara)                         
{
    UINT16 XRAM Reg64,Reg67,Reg68;
#if 0
	UINT16 Reg69;
#endif  
    Reg64 = Drv_XsiReadReg(pXSIREG,Addr_MCAP_SCAN_CFG,AFE_REG);

    Reg64 &= ~(1<<2);                                  //不对RAWDATA进行增益处理

    Reg68 = (pMcapPara->usRawdataOffset)&0x0000FFFF;

    Drv_XsiWriteReg(pXSI0Regs,Addr_RAWDATA_OFFSET_L,Reg68,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_RAWDATA_OFFSET_L,Reg68,AFE_REG); 
    
    if(pMcapPara->usGainEn)
    {
        Reg64 |= (1<<2);                                  //对RAWDATA进行增益处理
        Reg67 = (pMcapPara->usGainCof<<8) + pMcapPara->usRawShiftCof;
        Drv_XsiWriteReg(pXSI0Regs,Addr_RAWSHIFTCAF,Reg67,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_RAWSHIFTCAF,Reg67,AFE_REG); 
        
#if 0
        Reg69 = Drv_XsiReadReg(pXSIREG,0x45,AFE_REG);
        Reg69 &= 0xFFF7;
        Reg69 |= ((pMcapPara->usRawdataOffset)&0x10000)>>13;
      
        Drv_XsiWriteReg(pXSI0Regs,0x45,Reg69,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,0x45,Reg69,AFE_REG); 
#endif          
    }

    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);    
}

/*******************************************************************************
*   Name: DrvMcapSetOverflow
*  Brief: 互容按键是否对ADC数据进行饱和检测
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetOverflow(ST_McapParameter * pMcapPara)                        
{
    UINT16 XRAM Reg64,Reg72,Reg73,Reg74,Reg75,Reg76,Reg77,Reg78;
  
    Reg64 = Drv_XsiReadReg(pXSIREG,Addr_MCAP_SCAN_CFG,AFE_REG);
    Reg64 &= 0xFFFE;                             //清除overflow_en
    if(pMcapPara->usOvfEn)
    {
        Reg64 |= 0x0001;

        Reg72 = (pMcapPara->usOvfTh)&0x0FFF;
        Reg73 = (pMcapPara->usUdwTh)&0x0FFF;
        Reg74 = (pMcapPara->usOvfUpBound)&0x0FFF;
        Reg75 = (pMcapPara->usOvfPointFrm)&0x0FFF;

        Reg64 &= 0xFFFD;                        //清除overflow_clr_en
        if(pMcapPara->usOvfClrEn)
        {
            Reg64 |= 0x0002;
            DBG_FLOW("\nReg64:%04x",Reg64);
            Reg76 = (pMcapPara->usNormalUpTh)&0x0FFF;
            Reg77 = (pMcapPara->usNormalDwTh)&0x0FFF;
            Reg78 = (pMcapPara->usOvfClrFrmNum)&0x0FFF;
            
            Drv_XsiWriteReg(pXSI0Regs,Addr_NORMAL_SIGNAL_UPTHR,Reg76,AFE_REG);
            Drv_XsiWriteReg(pXSI1Regs,Addr_NORMAL_SIGNAL_UPTHR,Reg76,AFE_REG); 

            Drv_XsiWriteReg(pXSI0Regs,Addr_NORMAL_SIGNAL_DWTHR,Reg77,AFE_REG);
            Drv_XsiWriteReg(pXSI1Regs,Addr_NORMAL_SIGNAL_DWTHR,Reg77,AFE_REG);

            Drv_XsiWriteReg(pXSI0Regs,Addr_OVERFLOW_CLR_FRAMENUM,Reg78,AFE_REG);
            Drv_XsiWriteReg(pXSI1Regs,Addr_OVERFLOW_CLR_FRAMENUM,Reg78,AFE_REG);             
        }


        Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG); 

        DBG_FLOW("\nREG72:%04x",Reg72);

        Drv_XsiWriteReg(pXSI0Regs,Addr_OVERFLOW_THR,Reg72,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_OVERFLOW_THR,Reg72,AFE_REG); 

        Drv_XsiWriteReg(pXSI0Regs,Addr_UNDERFLOW_THR,Reg73,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_UNDERFLOW_THR,Reg73,AFE_REG);

        Drv_XsiWriteReg(pXSI0Regs,Addr_OVERFLOW_UPBOUND,Reg74,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_OVERFLOW_UPBOUND,Reg74,AFE_REG);

        Drv_XsiWriteReg(pXSI0Regs,Addr_OVER_POINT_FRAME,Reg75,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_OVER_POINT_FRAME,Reg75,AFE_REG);         
    }

}

/*******************************************************************************
*   Name: DrvMcapSetOverflowEn
*  Brief: 互容按键是否对ADC数据进行饱和检测
*  Input: ucEn
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetPara(ST_McapParameter * pMcapPara,ST_AfeTabList * pAfeTab,UINT8 ucTabId)                         //未写全
{
    UINT16 XRAM ucReg;

    /*切换到TblRam*/
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    /*获取使用tab表的k1,k2*/    
    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+8,AFE_REG);
    pAfeTab ->usAnaGenCfg0 = ucReg;
    pMcapPara->usK1= ucReg&0x07FF;

    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+9,AFE_REG);
    pAfeTab ->usAnaGenCfg1 = ucReg;    
    pMcapPara->usK2 = ucReg&0x07FF;

    /*扫描次数*/
    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+1,AFE_REG);
    pAfeTab ->usScanCfg0= ucReg;
    pMcapPara->usScanNum = (ucReg&0x07F8)>>3;
    pMcapPara->usScanMode = ucReg&0x0007;

    /*sx扫描方式*/
    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+2,AFE_REG);
    pAfeTab ->usScanCfg1 = ucReg;
    pMcapPara->usSxMode = (ucReg&0x0100)>>8; //0:双边扫描; 1:单边扫描

    /*获取dummy_num配置*/
    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+3,AFE_REG);
    pAfeTab ->usDummyScanCfg = ucReg;
    pMcapPara->usFrmDummy = ucReg&0x001F;
    pMcapPara->usSecDummy = (ucReg&0x03E0)>>5;    
    pMcapPara->usMuxDummy = (ucReg&&0x7C00)>>10;

    /*半带滤波，低通滤波设置*/
    pMcapPara->usLpFirEn     = 1;
    pMcapPara->usHbFirEn     = 1;
    pMcapPara->usLpFirTap    = 14;
    pMcapPara->usLpFirStart  = 14;
    pMcapPara->usLpFirSumNum = 1;//16;     //这个得请教要怎么配 亮屏下要怎么配,若滤波器全关的话,这个参数应该是扫描次数*采样倍数
    pMcapPara->usLpFirCof0   = 0x0104;
    pMcapPara->usLpFirCof1   = 0x0296;
    pMcapPara->usLpFirCof2   = 0x04e5;
    pMcapPara->usLpFirCof3   = 0x07c3;
    pMcapPara->usLpFirCof4   = 0x0acd;
    pMcapPara->usLpFirCof5   = 0x0d84; 
    pMcapPara->usLpFirCof6   = 0x0f65;
    pMcapPara->usLpFirCof7   = 0x1011;
    
    /*采样率配置*/
    pMcapPara->usSampl_6 = 0;         //1:表示6倍采样，0表示8倍采样

    /*采样起始点配置*/
    pMcapPara->usSampl_Init = 0;//0x42;  //对采集到的ADC影响很大,可以通过改变这个值，看哪个值对应的rawdata最大来判断是不是设置正确.

    /*Diff_max设置*/
    pMcapPara->usDiffSet = 0x2;     //2b'0x:不计算diff_max;2b'10:对ADC数据进行diff_max运算;2b'11:对mixer数据进行diff_max运算

    /*增益处理注意事项*/
    /*当开增益处理时rawdata = ((sum_data - offset) * gaincof>>shiftCof)<<1 */
    /*当关增益处理时rawdata = sum_data << 1.  sum_data为计算出来的结果 */
    /*则若没开增益处理时,rawdata = 0x170;开了增益处理时,若shiftcof = 0,gaincof = 1,offset = 0x10,则rawdata应为0x150左右 */

    /*增益处理设置*/
    pMcapPara->usGainEn = 0;         //不开启增益处理
    pMcapPara->usGainCof = 1;        //增益系数
    pMcapPara->usRawShiftCof = 0;
    pMcapPara->usRawdataOffset = 0x0;

    /*ADC饱和检测设置*/
    pMcapPara->usOvfEn = 0;
    pMcapPara->usOvfFlg = 0;
    pMcapPara->usOvfTh  = 0xfff;//0x03e8;
    pMcapPara->usUdwTh  = 0;
    pMcapPara->usOvfUpBound = 0x04;//0x0A;
    pMcapPara->usOvfPointFrm = 0x2;//0x20;

    /*ADC饱和检测清除标志设置*/
    pMcapPara->usOvfClrEn = 0;
    pMcapPara->usNormalDwTh = 0x0;//0x190;
    pMcapPara->usNormalUpTh = 0xfff;//0xfff;//0x258;
    pMcapPara->usOvfClrFrmNum = 0x02;//0x64;

    /*结束标志初始化*/
    pMcapPara->usErrFlg = 0;
    pMcapPara->usErrSta = 0;
    pMcapPara->usDoneFlg = 0;
    
}


/*******************************************************************************
*   Name: DrvMcapInit
*  Brief: 互容按键初始化 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapModeInit(UINT8 ucModeEn,UINT8 ucTabId)
{
    UINT8 XRAM ucScanMode;
    UINT8 XRAM i;
    UINT16 XRAM ucTalReg1,ucReg;
    if(ucModeEn == 0)//关闭互容按键
    {
        DrvMcapSetMode(0);
        return;
    }
    else
    {
        /*参数设置*/
        DrvMcapSetPara(g_pMcapPara,g_pAfeTabPara,ucTabId);
    
        DrvMcapSetMode(1);//开启互容按键
    }

#if 1    
    /*设置低通滤波、半带滤波*/
    DrvMcapSetFir(g_pMcapPara);

    /*采样率设置*/
    DrvMcapSetSampleRate(g_pMcapPara,g_pAfeTabPara,ucTabId);

    /*采样初始点设置*/
    DrvMcapSetSampleInit(g_pMcapPara);   

    /*ANA时序检查*/
    ucScanMode = g_pMcapPara->usScanMode;
    if(DrvMcapSetAnaTiming(g_pMcapPara,ucScanMode) == 1)//tx_clk是否满足要求
    {
        ucTalReg1 = (g_pAfeTabPara->usScanCfg0)&0xF807;
        ucTalReg1 |= ((g_pMcapPara->usScanNum)<<3);
        DBG_FLOW("\nReg1:%04x",ucTalReg1);
        Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+1,ucTalReg1,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+1,ucTalReg1,AFE_REG);        
    }

    /*设置互容按键是否计算diff_max*/
    DrvMcapSetDiffMax(g_pMcapPara);

    /*RAWDATA增益处理设置*/
    DrvMcapSetRawGain(g_pMcapPara);

    /*ADC数据饱和检测设置*/
    DrvMcapSetOverflow(g_pMcapPara);

    DBG_FLOW("\nScanMode:%d",g_pMcapPara->usScanMode);
#endif

#if 1
    DBG_FLOW("\n\nAFE REG:");
    for(i = 0x00; i < 0x58; i++)
    {
        ucReg = Drv_XsiReadReg(pXSI0Regs,i,AFE_REG);
        DBG_FLOW("\nReg[%x] = %04x",i,ucReg);
        ucReg = Drv_XsiReadReg(pXSI1Regs,i,AFE_REG);
        DBG_FLOW("\nReg[%x] = %04x",i,ucReg);        
    }

    DBG_FLOW("\n\nAFE TAB REG");
    for(i = 0x00; i < 0x0A; i++)
    {  
        ucReg = Drv_XsiReadReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+i,AFE_REG);
        DBG_FLOW("\nTabReg[%x] = %04x",i,ucReg);
        ucReg = Drv_XsiReadReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+i,AFE_REG);
        DBG_FLOW("\nTabReg[%x] = %04x",i,ucReg);        
    }    
#endif    
}


/*******************************************************************************
*   Name: DrvMcapReadSta
*  Brief: 读取互容按键的状态 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapReadSta(ST_McapParameter * pMcapPara)
{
    UINT16 XRAM Reg65;


    Reg65 = Drv_XsiReadReg(pXSIREG,Addr_MCAP_SCANSR,AFE_REG);
    pMcapPara->usErrSta = (Reg65&0x01E0)>>5;
    pMcapPara->usErrFlg = (Reg65&0x0010)>>4;
    pMcapPara->usOvfClrFlg = (Reg65&0x0004)>>2;
    pMcapPara->usOvfFlg = (Reg65&0x0002)>>1;
    pMcapPara->usDoneFlg = (Reg65&0x0001);

    DBG_FLOW("\nover flag:%04x",pMcapPara->usOvfFlg);
    //DBG_FLOW("\ndone flag:%04x",pMcapPara->usDoneFlg);           //软件没法读到
    DBG_FLOW("\nover clr flag:%04x",pMcapPara->usOvfClrFlg);

    
}

/*******************************************************************************
*   Name: DrvMcapReadSta
*  Brief: 进入测试模式 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetTestMode(UINT8 ucMode,UINT8 ucKeyNum)
{
    UINT16 XRAM ucReg04,ucReg51;
    ucReg04 = Drv_XsiReadReg(pXSIREG,0x04,AFE_REG);

    ucReg04 &= 0xFFFE;     //测试模式
    if(ucMode)
    {
        ucReg04 |=0x0001;  //普通模式
    }
    Drv_XsiWriteReg(pXSI0Regs,Addr_AFE_SYS_CFG0,ucReg04,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_AFE_SYS_CFG0,ucReg04,AFE_REG);

    ucReg51 = (ucKeyNum<<10) + 1;

    Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_MODE_FLAG,ucReg51,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_MODE_FLAG,ucReg51,AFE_REG);    
}


/*******************************************************************************
*   Name:Test_CLk48M
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CLk48M(UINT8 ucDiv)
{
    if((SYSCON&0x0C)==0x04)
    {
        DBG_FLOW("\nP0_6 is used to be UART TX pad!");
        return;
    }
	
	if((UART_INH == 0)&&(UART_INL == 1))
	{
        DBG_FLOW("\nP0_6 is used to be UART RX pad and now is changed to be CLK Test Pin!");
		UART_INH = 0;
		UART_INL = 0;
	}
    P0MOD |= BITn(6);
    TEST_OUT3_EN = 0;
    GPIO_INT_SEL = 1;//将唤醒脚选为p0_7
    TEST_CLK_EN = 1;

    CGUCON7 = ucDiv;   //osc_test_div

    DBG_FLOW("\nP0MOD:%02x",P0MOD);
    DBG_FLOW("\nTESTCON3:%02x",TESTCON3);
    DBG_FLOW("\nANACON:%02x",ANACON);
    DBG_FLOW("\nFT_EN_REG:%02x",FT_EN_REG);
    DBG_FLOW("\nCUGCON7:%02x",CGUCON7);    
    DBG_FLOW("\nTest Clk 48M");

}

/*******************************************************************************
*   Name:Test_CLk32K
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CLk32K(UINT8 ucDiv)
{
	UINT8 ucSrc = 3;//3:32k_from_1m;2:32k_dig;1:32k osc;0:48m


    if((SYSCON&0x0C)==0x04)
    {
        DBG_FLOW("\nP0_6 is used to be UART TX pad!");
        return;
    }

	if((UART_INH == 0)&&(UART_INL == 1))
	{
        DBG_FLOW("\nP0_6 is used to be UART RX pad and now is changed to be CLK Test Pin!");
		UART_INH = 0;
		UART_INL = 0;
	}	
	
    P0MOD |= BITn(6);
    TEST_OUT3_EN = 0;
    GPIO_INT_SEL = 1;//将唤醒脚选为p0_7
    TEST_CLK_EN = 1;

	if(ucSrc == 1)
	{
		SEL_32K_SRC = 1;         //写1可以发出,
	}
	else if(ucSrc == 2)
	{
		PROBE32K_DIG_EN = 1;		
	}
	else if(ucSrc == 3)
	{
		PROBE32K_FROM1M_EN = 1;
		SEL_32K_SRC = 0;         //FPGA写1或者写0都可以发出
	}
	
	CGUCON7 = (ucSrc << 6)|(ucDiv);

    DBG_FLOW("\nP0MOD:%02x",P0MOD);
	DBG_FLOW("\nDSVCON:%02x",DSV_CON);
    DBG_FLOW("\nTESTCON3:%02x",TESTCON3);
    DBG_FLOW("\nSYSCON:%02x",SYSCON);
    DBG_FLOW("\nFT_EN_REG:%02x",FT_EN_REG);
    DBG_FLOW("\nCUGCON7:%02x",CGUCON7);    
    DBG_FLOW("\nTest Clk 32K");

}


/*******************************************************************************
*   Name:Test_Ca_P1
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Ca_P1(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig;
    ucConfig = (0x1<<8) + 0x1;//ca_p1,afe与ca信号

    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x81;
    }
    
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("CA_P1");
}


/*******************************************************************************
*   Name:Test_Ca_P4
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Ca_P4(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig;
    ucConfig = (0x2<<8) + 0x1;//ca_p4,afe与ca信号

    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    } 
    DBG_FLOW("CA_P4");    
}

/*******************************************************************************
*   Name:Test_Ca_Rst
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Ca_Rst(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig;
    ucConfig = (0x0<<8) + 0x1;//ca_rst,afe与ca信号

    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("CA_RST");    
}

/*******************************************************************************
*   Name:Test_Lcd_Run
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Lcd_Run(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig;
    ucConfig = (0x1<<4) + 0x0;//lcd_run,afe与soc信号

    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("LCD_RUN");    
}

/*******************************************************************************
*   Name:Test_Lcd_Busy
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Lcd_Busy(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig;
    ucConfig = (0x2<<4) + 0x0;//lcd_Busy,afe与soc信号

    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("LCD_BUSY");
	DBG_FLOW("\nReg[%x]:%04x",Addr_TEST_P1_CFG0,Drv_XsiReadReg(pXSI0Regs,Addr_TEST_P1_CFG0,AFE_REG));
}

/*******************************************************************************
*   Name:Test_Tp_Scan
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Tp_Scan(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig;
    ucConfig = (0x5<<4) + 0x0;//Tp_Scan,afe与soc信号

    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("TP_SCAN");    
}

/*******************************************************************************
*   Name:Test_Tp_Busy
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Tp_Busy(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig;
    ucConfig = (0x6<<4) + 0x0;//Tp_Busy,afe与soc信号

    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig,AFE_REG);
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("TP_BUSY");     
}

/*******************************************************************************
*   Name:Test_Tx_Clk
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Tx_Clk(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig0;
    UINT16 XRAM ucConfig1;
    ucConfig0 = 0x4;      //afe与mcap信号
    ucConfig1 = (0x5<<4); //tx_clk
    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig0,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig0,AFE_REG);
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG1,ucConfig1,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG1,ucConfig1,AFE_REG);        
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig0,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig0,AFE_REG);
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG1,ucConfig1,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG1,ucConfig1,AFE_REG);  
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("Tx_Clk"); 
}


/*******************************************************************************
*   Name:Test_MCAP_DONE
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_MCAP_DONE(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig0;
    UINT16 XRAM ucConfig1;
    ucConfig0 = 0xA;      //afe与mcap信号
    //ucConfig1 = (0x1<<12); //macp_done
    //ucConfig1 = (0x3<<12); //MIXER_VLD
    ucConfig1 = (0x1<<12); //MIXER_VLD    
    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig0,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig0,AFE_REG);
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG2,ucConfig1,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG2,ucConfig1,AFE_REG);        
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig0,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig0,AFE_REG);
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG2,ucConfig1,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG2,ucConfig1,AFE_REG);  
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("mcap_done"); 
}


/*******************************************************************************
*   Name:Test_MCAP_ADC_DATA_VLD
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_MCAP_ADC_DATA_VLD(UINT8 ucPin,UINT8 ucAfePin)
{
    UINT8 XRAM ucSfrCon;
    UINT16 XRAM ucConfig0;
    UINT16 XRAM ucConfig1;
    ucConfig0 = 0xA;      //afe与mcap信号
    //ucConfig1 = (0x2<<12); //macp_done
    ucConfig1 = (0x6<<12); //macp_done    
    if(ucAfePin == 0)// pin0
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG0,ucConfig0,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG0,ucConfig0,AFE_REG);
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P0_CFG2,ucConfig1,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P0_CFG2,ucConfig1,AFE_REG);        
        ucSfrCon = 0x80;
    }
    else            //pin1
    {
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG0,ucConfig0,AFE_REG);  //p1
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG0,ucConfig0,AFE_REG);
        Drv_XsiWriteReg(pXSI0Regs,Addr_TEST_P1_CFG2,ucConfig1,AFE_REG);  //p0
        Drv_XsiWriteReg(pXSI1Regs,Addr_TEST_P1_CFG2,ucConfig1,AFE_REG);  
        ucSfrCon = 0x81;
    }
    if(ucPin == 0)
    {
        TESTCON0 = ucSfrCon;
    }
    else if(ucPin == 1)
    {
        TESTCON1 = ucSfrCon;
    }
    else if(ucPin == 2)
    {
        TESTCON2 = ucSfrCon;
    }
    else if(ucPin == 3)
    {
        TESTCON3 = ucSfrCon;
    }
    DBG_FLOW("mcap_done"); 
}


/*******************************************************************************
*   Name:Test_Debug0
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Debug0(void)
{
    TEST_OUT0_EN = 1;

    DBG_FLOW("\nTest_Debug0:");

    //下面只能选择打开一个函数
    //Test_Ca_P1(2,0);
    //Test_Ca_P4(2,0);
    //Test_Ca_Rst(2,0);
    Test_Lcd_Run(2,0);
    //Test_Lcd_Busy(2,0);
    //Test_Tp_Scan(2,0);
    //Test_Tp_Busy(2,0);
    //Test_Tx_Clk(2,0);
    //Test_MCAP_DONE(2,0);
    //Test_MCAP_ADC_DATA_VLD(2,0);	
}


/*******************************************************************************
*   Name:Test_Debug3
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Debug1(void)
{
    TEST_OUT1_EN = 1;
    
    DBG_FLOW("\nTest_Debug1:");

    //下面只能选择打开一个函数
    Test_Ca_P1(3,1);
    //Test_Ca_P4(3,1);
    //Test_Ca_Rst(3,1);
    //Test_Lcd_Run(3,1);
    //Test_Lcd_Busy(3,1);
    //Test_Tp_Scan(3,1);
    //Test_Tp_Busy(3,1);
    Test_Tx_Clk(3,1);
}




/*******************************************************************************
*   Name:Test_Debug2
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Debug2(void)
{
    if(BUS_SEL == 1)//spi0
    {
        P0MOD |= BITn(0);//p0_0;
    }
    else
    {
        P0MOD |= BITn(2);//P0_2;
    }

    TEST_OUT2_EN = 1;

    DBG_FLOW("\nTest_Debug2:");

    //下面只能选择打开一个函数
    Test_Ca_P1(2,0);
    //Test_Ca_P4(2,0);
    //Test_Ca_Rst(2,0);
    //Test_Lcd_Run(2,0);
    //Test_Lcd_Busy(2,0);
    //Test_Tp_Scan(2,0);
    //Test_Tp_Busy(2,0);
    //Test_Tx_Clk(2,0);
}


/*******************************************************************************
*   Name:Test_Debug3
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Debug3(void)
{
    P0MOD |= BITn(6);

    TEST_OUT3_EN = 1;
    
    DBG_FLOW("\nTest_Debug3:");

    //下面只能选择打开一个函数
    //Test_Ca_P1(3,1);
    //Test_Ca_P4(3,1);
    //Test_Ca_Rst(3,1);
    //Test_Lcd_Run(3,1);
    Test_Lcd_Busy(3,1);
    //Test_Tp_Scan(3,1);
    //Test_Tp_Busy(3,1);
    //Test_Tx_Clk(3,1);
    //Test_MCAP_DONE(3,1);    
    //Test_MCAP_ADC_DATA_VLD(3,1);    
}




/*******************************************************************************
*   Name: Test_DebugOut
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_DebugOut(void)
{
    //测试48M/32K/Test_Debug3只能同时开一个,共用p0_6

        
    //Test_CLk32K(0);  //从p0_6出信号 
    //Test_CLk48M(0);  //从P0_6出信号

	//目前代码里面pin0配置在debug0与debug2,两组只能开1个;pin1配置在debug1与debug3,两者也只能开1个.
    Test_Debug0();     //从tp2pad_dsv_en6出信号
	//Test_Debug1();     //从led_pwm[0]出信号
    //Test_Debug2();     //当用SPI0时,从P0_0出信号,当用IIC时，从p0_2出信号
    Test_Debug3();     //从p0_6出信号
    
}


#if 0 // 软件CB校正
/*******************************************************************************
*   Name: DrvPara_WriteCB
*  Brief:
*         1.更新CB到寄存器表中
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvPara_WriteCB(UINT8 Tbl_ID)
{
    UINT8 i;
    UINT8 ucOrder;
    UINT8 ucLenS0;  /* S0半屏 有效通道数 */
    UINT8 ucLenS1;  /* S1半屏 有效通道数 */

    UINT8 ucTbl;   /* 该模式对应的表号 */

    UINT16 XRAM usTblBaseAddr;
    UINT16 XRAM usAddr;
    UINT16 XRAM ausCbValue[(CH_LEN_MAX+1)>>1];
    UINT8 XRAM aucCbRegL[CH_LEN_MAX+1];
    UINT8 XRAM aucCbRegR[CH_LEN_MAX+1];

        ucTbl = Tbl_ID;
        usTblBaseAddr = ID_TBL1_BASE + ucTbl*TBL_LEN_MAX + 22;

        /* 将地址切换到 Tbl区 */
        DrvAfeSelTaborRepRam(AREA_TBL_RAM);
        
        ucLenS0 = 224;
        ucLenS1 = 224;

        /* 左AFE */
        for (i = 0; i < ucLenS0; i++)
        {
            ucOrder = g_ucOrderBuf[i];
            aucCbRegL[ucOrder+1] = 1 | (ucCbValue[i]<<1);
        }

        /* 右AFE */
        for (i = 0; i < ucLenS1; i++)
        {
            usAddr = ucLenS0 + i;
            ucOrder = g_ucOrderBuf[usAddr];
            aucCbRegR[ucOrder+1] = 1 | (ucCbValue[usAddr] << 1);
        }
  
        /* 左 key */
        usAddr = ucLenS0 + ucLenS1;
        /*tbl Ram CB0的高八位存放Key0-2的高2位*/

        /* Key1有效时，赋值 */
        if (1)
        {
            aucCbRegL[0] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegL[1] = (aucCbRegL[1]&0xFC)
                                    + ((ucCbValue[usAddr]&0xC0) >> 6);
        }
        usAddr++;
        /* Key2有效时，赋值 */
        if (1)
        {
            aucCbRegL[2] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegL[1] = (aucCbRegL[1]&0xF3)
                                    + ((ucCbValue[usAddr]&0xC0) >> 4);
        }
        usAddr++;

        /* Key3有效时，赋值 */
        if (1)
        {
            aucCbRegL[3] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegL[1] = (aucCbRegL[1]&0xCF)
                                    + ((ucCbValue[usAddr]&0xC0) >> 2);
        }
        usAddr++;
        /*  */

        /* 右Key4有效时，赋值 */
        if (1)
        {
            aucCbRegR[0] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegR[1] = (aucCbRegR[1]&0xFC)
                                    + ((ucCbValue[usAddr]&0xC0) >> 6);
        }
        usAddr++;

        /* 右Key5有效时，赋值 */
        if (1)
        {
            aucCbRegR[2] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegR[1] = (aucCbRegR[1]&0xF3)
                                    + ((ucCbValue[usAddr]&0xC0) >> 4);
        }
        usAddr++;
        /* 右Key6有效时，赋值 */
        if (1)
        {
            aucCbRegR[3] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegR[1] = (aucCbRegR[1]&0xCF)
                                    + ((ucCbValue[usAddr]&0xC0) >> 2);
        }
        usAddr++;


        for (i = 0; i<CH_LEN_MAX; i+=2)
        {
            ausCbValue[i>>1] = ((UINT16)aucCbRegL[i+1]<<8) + aucCbRegL[i];
        }
#if 0
    DBG_FLOW("\n write CB Tab_L %d\n",ucTbl);
    for (i = 0;i < 10 ;i++)
    {
        DBG_FLOW("%04x  ",ausCbValue[i]);
    }
#endif
        DrvXsi0_WriteN(usTblBaseAddr, ausCbValue, (CH_LEN_MAX+1)>>1);

        for (i = 0; i<CH_LEN_MAX; i+=2)
        {
           ausCbValue[i>>1] = ((UINT16)aucCbRegR[i+1]<<8) + aucCbRegR[i];
        }
#if 0
    DBG_FLOW("\n write CB Tab_R %d\n",ucTbl);
    for (i = 0;i < 10 ;i++)
    {
        DBG_FLOW("%04x  ",ausCbValue[i]);
    }
#endif
        DrvXsi1_WriteN(usTblBaseAddr, ausCbValue, (CH_LEN_MAX+1)>>1);
}

/*******************************************************************************
*   Name: DrvClbCB
*  Brief:
*         1.CB自动校正,CF校正时，配置成最大
*         2.CB从00-->0x7F,  高位-->低位，逐位逼近
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvClbCB(UINT8 ucTabID)
{
    SINT8 scCnt;                // 校准次数计数器
    UINT8 ucDataMask;           // 临时设置的CB值
    UINT8 ucKeyMask;            // 临时设置的Key CB值:软件校准低两位不校
    UINT16 i;
    UINT16 usChNum;             // 需要校准的所有通道总数
    UINT16 usChVaNum;           // 需要校准的va通道总数
    UINT16 usRawTargeNormal;    // 正常模式 校准目标值


    /* +6个按键通道 */
    usChVaNum = CH_LEN;  /* 有效通道总长度, 不含按键 */
    usChNum = usChVaNum + KEY_NUM_MAX;
    /* 清零所有通道CB值 */
    memset(ucCbValue, 0x00, usChNum);
   
    // RAWDATA目标值设置，OutPutRaw = (1CycleRaw * CycleSum)>>AccShift
    usRawTargeNormal = 8192;

    /* 连续进行7次完整扫描，逐次逼近方式校准CB值 */
    for (scCnt = (SC_CLB_TIMES - 1); scCnt >= 0; scCnt--)
    {
        /* 预设CB值 */
        if (scCnt > 1)
        {
            ucDataMask = (0x01 << (scCnt-2)); /*va区只校准6位*/
        }
        else
        {
            ucDataMask = 0x00;
        }
#if 1
        if (scCnt > 1)
        {
            ucKeyMask = (0x01 << (scCnt-2)); /*Key高2位不起作用*/
        }
        else
        {
            ucKeyMask = 0x00;
        }
#else
        ucKeyMask = (0x01 << scCnt);
#endif

        /* VA通道此次校正位置 */
        for (i = 0; i < usChVaNum; i++)
        {
            ucCbValue[i] |= ucDataMask;
        }
        /* Key通道此次校正位置 */
        for (i = 0; i < KEY_NUM_MAX; i++)
        {
            ucCbValue[usChVaNum+i] |= ucKeyMask;
        }

        /* CB参数写入寄存器 */
        DrvPara_WriteCB(ucTabID);
        
        g_ucAramReadyFlag = 0;
        /* 加载Tab表 */
        DrvLoadTabSingle(ucTabID,0);
        /* scan start */
        DrvAsmScanStart();

        /* wait end　*/
        while(!g_ucAramReadyFlag);

        /* 当前帧数据,AFE ARAM READY中断完成数据搬运到RawBuf中 */
#if 1
        DBG_FLOW("\nRaw time %d \n",scCnt);
        DrvGetRawdata();
#endif
        /* 对所有通道进行校正 */
        for (i = 0; i < usChNum; i++)
        {
            /* 如果RAWDATA小于目标值，将预设的值清除，如果大于目标值，保持当前预设值 */
            if (g_usRawdataBuf[i] < usRawTargeNormal)
            {
                ucCbValue[i] &= ~ucDataMask;
            }
        }

    }
    
    /* CB参数写入寄存器 */
    DrvPara_WriteCB(ucTabID);
}
#endif


