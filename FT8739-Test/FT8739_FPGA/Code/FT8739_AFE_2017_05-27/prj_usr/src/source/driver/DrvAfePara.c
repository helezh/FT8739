/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)��All Rights Reserved.
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
*   Name: DrvAFEGroupSelReg1
*  Brief: 5��Mux, GroupA,GroupBѡ��
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
*  Brief: 5��Mux, GroupA,GroupBѡ��
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
*  Brief: ��ַ: 0-323: Tpͨ����Key���ϱ�Rawdata�����Order
*         ��ַ  324-325: key diff Noise max, TP diff Noise max.
*         ��ַ: 326-653: Tpͨ����Key�� Rawdata/Base
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
*  Brief:  AFE��λ�߼�  
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
*  Brief:  ɨ����������ϱ�ԭʼADC������ģ�����ÿ�α�2�����ݡ�
*           DAT_TEST_MODE_KEY_NUM       0x00    //[11:10]����ģʽ��ѡ��key����                                    
*           DAT_TEST_MODE_TP_CH_NUM             0x000   //[9:1]  ����ģʽ��ѡ��tpͨ����
*           DAT_TEST_MODE_TP_KEY_SEL            0x0     //[0], ͨ��ѡ��, 0:tp; 1:key
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
*  Brief: Monitorģʽ��Base�������� 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeSetBaseTrack(UINT8 ucBaseMode,UINT8 ucStep)
{
    UINT16 XRAM usBaseTrackReg;
                                 
    usBaseTrackReg = ((ucStep<<BIT_BASE_TRACK_STEP)          //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
                     +(ucBaseMode<<BIT_BASE_TRACK_MODE)      //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
                     +(1<<BIT_BASE_TRACK_ENABLE));           //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_BASE_TRACK_CFG, usBaseTrackReg, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_BASE_TRACK_CFG, usBaseTrackReg, AFE_REG);               
}


/*******************************************************************************
*   Name: DrvAfeSetBaseTrack
*  Brief: Monitorģʽ��Base�������� 
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
                                 
    usBaseTrackReg |= ((ucStep<<BIT_BASE_TRACK_STEP)          //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
                     +(ucBaseMode<<BIT_BASE_TRACK_MODE)      //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
                     +(1<<BIT_BASE_TRACK_ENABLE));           //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 


    Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucId+4,usBaseTrackReg,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*ucId+4,usBaseTrackReg,AFE_REG);
}


/*******************************************************************************
*   Name: DrvAfeSetHCBTarget
*  Brief: Ӳ��CBУ����Ŀ��ֵ
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
*  Brief:  �������tp,key����
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
#if TEMP_CLOSE_KEY 
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0;      //4������:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0;
#else
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0100;      //4������:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0100;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0100;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0100;
#endif    
    Drv_XsiWrite(pXSI0Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
#if TEST_KEY_DET
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0;      //4������:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0;
    Drv_XsiWrite(pXSI0Regs,256+ucTabID*TAB_RAM_LEN+TAB_TP_KEY_CB_START_ADDR,&aus_tabbuf[TAB_TP_KEY_CB_START_ADDR],TAB_RAM_LEN,AFE_REG);
#endif
}




/*******************************************************************************
*  Brief: ����0���á�һ����4������ , FreeRun ����
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

//    usReg0 = rAFE_SYS_CFG1|(1<<7);  //DAT_ACC_ASR �����ۺ�����
    usReg0 = rAFE_SYS_CFG1|(0<<7);  //DAT_ACC_ASR
    
    usReg1 = rAFE_SCAN_CFG0;
    usReg1 =((1<<BIT_AFE_SCAN_TIMES) +(4<<BIT_AFE_SCAN_MODE));  //��ʽ5 ��������ɨ��5��1/5,ɨ�������ʵ��ֵΪ����ֵ��1; ������ݴ�������1.��: ����Ϊ1��ʵ��ɨ��2�Σ�����ֻ��1�Ρ���0��ɨ��1�Σ���ֵ����� 
//    usReg1 =((1<<BIT_AFE_SCAN_TIMES) +(7<<BIT_AFE_SCAN_MODE));  //��ʽ8 5����һ��,����ͨ����һ��mux1ѡ���������:mux1:G1,G9, ��G1,G9���ݣ�����������λ�ÿɽ�DET�жϡ� 
                      
#if TEST_ONE_CHANNEL_ADC
    usReg1 =((5<<BIT_AFE_SCAN_TIMES)             //ɨ�������ʵ��ֵΪ����ֵ��1; ������ݴ�������1.��: ����Ϊ1��ʵ��ɨ��2�Σ�����ֻ��1�Ρ���0��ɨ��1�Σ���ֵ����� ����ֻ��һ��mux.
            +(4<<BIT_AFE_SCAN_MODE));             //��ʽ5 ��������ɨ��5��1/5
#endif
    
    usReg2 = rAFE_SCAN_CFG1;
    usReg2 =((0<<9)               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������      
            +(0<<8)               //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
            +(4<<0));             //[0] ��ʽ6��ɨ�����  

#if 1 //˫��3��ģʽ
#if TEST_2SAMPLE_ANA_SUB
     usReg2 =((0<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����;     [8]˫��ɨ��
#endif
#if TEST_2SAMPLE_POSITIVE
     usReg2 =((1<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 1:���߲���;     [8]˫��ɨ��
#endif
#if TEST_2SAMPLE_NEGATIVE
     usReg2 =((2<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 2:���߲���;     [8]˫��ɨ��
#endif
     usReg8 = rAFE_ANA_K1_CFG0;
     usReg9 = rAFE_ANA_K2_CFG1;
#endif     
          
    usReg3 = rAFE_DUMMY_SCAN_CFG;
    usReg3 =((1<<10)               //[14:10]Mux�л�֮��Dummy����    
            +(0<<5)                //[9:5]��ǰDummy����
            +(2<<0));              //[4:0]Tp֡ǰDummy����    
            
    usReg4 = rAFE_BASE_TRACK_CFG;
    usReg4 = ((80<<BIT_BASE_TRACK_STEP)             //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
             +(0<<BIT_BASE_TRACK_MODE)              //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
             +(1<<BIT_BASE_TRACK_ENABLE));          //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 

    usReg5 = 0x100; //rACC_OFFSET;        //����ACC Offsetֵ 
#if IS_4_MUX_MODE
    usReg5 = 256;                //keyֻ֧���������������ֵΪ0��Ҫ��Offset.
#endif
    
#if TEST_2SAMPLE_DIG_SUB //˫��ɨ��, ˫�߲������������   
    usReg2 =((3<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 3:˫�߲������������   [8]˫��ɨ��
    usReg5 = 256;       //����ACC Offsetֵ
    usReg8 = rAFE_ANA_K1_CFG0*2;
    usReg9 = rAFE_ANA_K2_CFG1*3;
#endif    

    usReg6 = rTP_MONITOR_THRESHOLD;
    usReg7 = rKEY_MONITOR_THRESHOLD;

#if TEST_1SAMPLE //����ɨ��,���߲���
    usReg2 =((0<<9)+(1<<8)+(4<<0));               //[8]����ɨ��(��1�ֵ��߲���)  

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
*  Brief: ����1���á�һ����4������ , 120hz ����
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

    ucScanMode = SCAN_MODE_1;   //����ɨ�跽ʽ

#if TEST_MUX_ABC_SACN    
    ucScanMode = SCAN_MODE_2;   //����ɨ�跽ʽ2_2_1
#endif

#if TEST_MUX_ABCD_SACN    
    ucScanMode = SCAN_MODE_3;   //����ɨ�跽ʽ3_2
#endif

#if TEST_60HZ_SCAN_MODE
    ucScanMode = SCAN_MODE_5;   //����ɨ�跽ʽ
#endif


    usReg0 = rAFE_SYS_CFG1;
    
    usReg1 = rAFE_SCAN_CFG0;

    usReg2 = rAFE_SCAN_CFG1;
    usReg2 =((0<<9)               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������      
            +(0<<8)               //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
            +(4<<0));             //[0] ��ʽ6��ɨ�����  
//   usReg2 =((0<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����;     [8]˫��ɨ��
//   usReg2 =((1<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 1:���߲���;     [8]˫��ɨ��
//   usReg2 =((2<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 2:���߲���;    [8]˫��ɨ��
//   usReg2 =((3<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 3:˫�߲������������   [8]˫��ɨ��
//   usReg2 =((0<<9)+(1<<8)+(4<<0));               //[8]����ɨ��(��1�ֵ��߲���) 

    switch(ucScanMode)
    {
        case SCAN_MODE_1:
            usReg1 =((1<<BIT_AFE_SCAN_TIMES)+(0<<BIT_AFE_SCAN_MODE));       //��ʽ1: ��������ֻɨ��1��1/5����ͨ��
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                    +(2<<5)                //[9:5]��ǰDummy����
                    +(0<<0));              //[4:0]Tp֡ǰDummy����   
            break;
        case SCAN_MODE_2:
            usReg1 =((4<<BIT_AFE_SCAN_TIMES)+(1<<BIT_AFE_SCAN_MODE));     //��ʽ2: ��������ֻɨ��2��1��1/5����ͨ�� ��:A:2_2_1+B:2_2_1
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                    +(2<<5)                //[9:5]��ǰDummy����
                    +(0<<0));              //[4:0]Tp֡ǰDummy����   
            break;
        case SCAN_MODE_3:
            usReg1 =((2<<BIT_AFE_SCAN_TIMES)+(2<<BIT_AFE_SCAN_MODE));     //��ʽ3: ��������ֻɨ��3��2��1/5����ͨ�� ��:A:3_2+B:3_2
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                    +(1<<5)                //[9:5]��ǰDummy����
                    +(1<<0));              //[4:0]Tp֡ǰDummy����   
            break;
        case SCAN_MODE_4:
            usReg1 =((2<<BIT_AFE_SCAN_TIMES)+(3<<BIT_AFE_SCAN_MODE));     //��ʽ4: ��������ֻɨ��2��3��1/5����ͨ�� ��:A:2_3+B:2_3
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                   +(2<<5)                 //[9:5]��ǰDummy����
                   +(0<<0));               //[4:0]Tp֡ǰDummy����   
            break;
        case SCAN_MODE_5:
            usReg1 =((1<<BIT_AFE_SCAN_TIMES)+(4<<BIT_AFE_SCAN_MODE));     //��ʽ5: 
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                    +(0<<5)                //[9:5]��ǰDummy����
                    +(0<<0));              //[4:0]Tp֡ǰDummy����   
            break;
        case SCAN_MODE_6:
            usReg1 =((1<<BIT_AFE_SCAN_TIMES)+(5<<BIT_AFE_SCAN_MODE));     //��ʽ6: ��������ֻɨ��5��1/5����ͨ�����Ҷ���ۼӣ���ʽ 
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                    +(0<<5)                //[9:5]��ǰDummy����
                    +(0<<0));              //[4:0]Tp֡ǰDummy����   
            usReg2 =((0<<9)                //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������      
                    +(0<<8)                //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
                    +(4<<0));              //[0] ��ʽ6��ɨ�����                     
            break;
        case SCAN_MODE_7:
           usReg1 =((1<<BIT_AFE_SCAN_TIMES)+(6<<BIT_AFE_SCAN_MODE));     //��ʽ7: ��������ֻɨ��2��1��mux,��mux9ģʽ��:A:2_2_2_2_1+B:2_2_2_2_1
           usReg3 = rAFE_DUMMY_SCAN_CFG;                                 //9��mux����ɨ�裬9��mux�����ȫ��ɨ�衣
           usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                   +(2<<5)                //[9:5]��ǰDummy����
                   +(0<<0));              //[4:0]Tp֡ǰDummy����   
            break;
        case SCAN_MODE_8:
           usReg1 =((2<<BIT_AFE_SCAN_TIMES)+(7<<BIT_AFE_SCAN_MODE));     //��ʽ8: ��ɨ��1��Mux,���ȫ��ɨ�裬��Monitor,5��SX����ģʽ��G1234 G56789, 
           usReg3 = rAFE_DUMMY_SCAN_CFG;                                 //ֻ��mux1 G1G9���ݻᷢ���仯��Ӧ���ڴ������ѡ�
           usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                   +(2<<5)                //[9:5]��ǰDummy����
                   +(0<<0));              //[4:0]Tp֡ǰDummy����   
            break;
        default:
            break;
    }
                                        
    usReg4 = rAFE_BASE_TRACK_CFG;
    usReg4 = ((80<<BIT_BASE_TRACK_STEP)             //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
              +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
              +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 
    
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
*  Brief: ����2���á�һ����4������ ,  monitor ����
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
    usReg1 =((1<<BIT_AFE_SCAN_TIMES)                //ɨ�������ʵ��ֵΪ����ֵ��1;  
            +(4<<BIT_AFE_SCAN_MODE));               //��ʽ5

    usReg3 = rAFE_DUMMY_SCAN_CFG;
    usReg3 =((1<<10)                                //[11:8]Mux�л�֮��Dummy����    
            +(0<<5)                                 //[7:4]��ǰDummy����
            +(2<<0));                               //[3:0]Tp֡ǰDummy����    

    //���ô������ʱ��TP,keyͨ���Ĵ�����ֵ     
    usReg6 = 100; //rTP_MONITOR_THRESHOLD;
    usReg7 = 2000; //rKEY_MONITOR_THRESHOLD;          //����keyֻ���������ģʽ
#endif

#if TEST_120HZ_MONTIOR// normal 120hz  
    usReg1 = rAFE_SCAN_CFG0;
    usReg1 =((1<<BIT_AFE_SCAN_TIMES)               //ɨ�������ʵ��ֵΪ����ֵ��1;  
            +(0<<BIT_AFE_SCAN_MODE));              //��ʽ1

    usReg3 = rAFE_DUMMY_SCAN_CFG;
    usReg3 =((1<<10)               //[11:8]Mux�л�֮��Dummy����    
            +(0<<5)               //[7:4]��ǰDummy����
            +(2<<0));             //[3:0]Tp֡ǰDummy����  
    //���ô������ʱ��TP,keyͨ���Ĵ�����ֵ     
    usReg6 = 18; //rTP_MONITOR_THRESHOLD;
    usReg7 = 18; //rKEY_MONITOR_THRESHOLD;
#endif

            
    usReg2 = rAFE_SCAN_CFG1; 
    usReg2 =((0<<9)               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������      
            +(0<<8)               //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
            +(4<<0));             //[0] ��ʽ6��ɨ�����             

    //���óɲ�������,    ���ٲ���32(0x20)        
    usReg4 = rAFE_BASE_TRACK_CFG;
    usReg4 = ((32<<BIT_BASE_TRACK_STEP)             //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
             // +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 
              +(1<<BIT_BASE_TRACK_MODE)             //[1] Monitorģʽ��Base���ٷ�ʽ:   1:ԭֵ����
              +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 
              
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
*  Brief: ����3���á�һ����4������ , Ӳ��CBУ�� ����
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
    usReg1 =((2<<BIT_AFE_SCAN_TIMES)               //ɨ�������ʵ��ֵΪ����ֵ��1;  
            +(4<<BIT_AFE_SCAN_MODE));             //��ʽ0
            
    usReg2 = rAFE_SCAN_CFG1;
    usReg2 =((0<<9)               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������      
            +(0<<8)               //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
            +(4<<0));             //[0] ��ʽ6��ɨ�����  
            
    usReg3 = rAFE_DUMMY_SCAN_CFG;
    usReg3 =((1<<10)               //[14:10]Mux�л�֮��Dummy����    
            +(0<<5)               //[9:5]��ǰDummy����
            +(2<<0));             //[4:0]Tp֡ǰDummy����   
            
    usReg4 = rAFE_BASE_TRACK_CFG;
    usReg4 = ((80<<BIT_BASE_TRACK_STEP)             //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
              +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
              +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 
              
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
*  Brief: ����3���á�һ����4������ , Ӳ��CBУ�� ����
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


            usReg1 =(((usScanNum)<<BIT_AFE_SCAN_TIMES)                   //ɨ�������ʵ��ֵΪ����ֵ��1;  
                    +(ucScanMode<<BIT_AFE_SCAN_MODE));                   //ɨ�跽ʽ

            usReg2 = rAFE_SCAN_CFG1;
            usReg2 =((0<<9)               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������      
                    +(0<<8)               //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
                    +(4<<0));             //[0] ��ʽ6��ɨ�����  
                    
            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((1<<10)               //[14:10]Mux�л�֮��Dummy����    
                    +(0<<5)               //[9:5]��ǰDummy����
                    +(2<<0));             //[4:0]Tp֡ǰDummy����   
                    
            usReg4 = rAFE_BASE_TRACK_CFG;
            usReg4 = ((80<<BIT_BASE_TRACK_STEP)             //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
                      +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
                      +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 
                      
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
            usReg1 =(((usScanNum)<<BIT_AFE_SCAN_TIMES)      //ɨ�������ʵ��ֵΪ����ֵ��1;  
                    +(ucScanMode<<BIT_AFE_SCAN_MODE));      //ɨ�跽ʽ


            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((1<<10)                                //[11:8]Mux�л�֮��Dummy����    
                    +(0<<5)                                 //[7:4]��ǰDummy����
                    +(2<<0));                               //[3:0]Tp֡ǰDummy����    

            //���ô������ʱ��TP,keyͨ���Ĵ�����ֵ     
            usReg6 = 20; //rTP_MONITOR_THRESHOLD;
            usReg7 = 20; //rKEY_MONITOR_THRESHOLD;  

                    
            usReg2 = rAFE_SCAN_CFG1; 
            usReg2 =((0<<9)               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������      
                    +(0<<8)               //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
                    +(4<<0));             //[0] ��ʽ6��ɨ�����             

            //���óɲ�������,    ���ٲ���32(0x20)        
            usReg4 = rAFE_BASE_TRACK_CFG;
            usReg4 = ((32<<BIT_BASE_TRACK_STEP)             //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
                     // +(0<<BIT_BASE_TRACK_MODE)             //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 
                      +(1<<BIT_BASE_TRACK_MODE)             //[1] Monitorģʽ��Base���ٷ�ʽ:   1:ԭֵ����
                      +(1<<BIT_BASE_TRACK_ENABLE));         //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 
                      
            usReg5 = rACC_OFFSET;
            
            
            usReg8 = rAFE_ANA_K1_CFG0;
            usReg9 = rAFE_ANA_K2_CFG1;            
            
            break;
        }

        case 2:           //mcap
        {
            usReg0 = rAFE_SYS_CFG1|(0<<7);  //DAT_ACC_ASR
            usReg1 =((usScanNum<<BIT_AFE_SCAN_TIMES)        //ɨ�������ʵ��ֵΪ����ֵ��1,����1��tx�̶�Ϊdummy;  
                    +(ucScanMode<<BIT_AFE_SCAN_MODE));      //ɨ�跽ʽ

            
            usReg2 =((0<<9)+(0<<8)+(4<<0));               //[10:9] ����ģʽ: 0:˫�߲�����ģ�����;     [8]˫��ɨ��

            usReg3 = rAFE_DUMMY_SCAN_CFG;
            usReg3 =((0<<10)               //[14:10]Mux�л�֮��Dummy����    
                    +(0<<5)                //[9:5]��ǰDummy����
                    +(0<<0));              //[4:0]Tp֡ǰDummy����  

            usReg4 = rAFE_BASE_TRACK_CFG;
            usReg4 = ((0<<BIT_BASE_TRACK_STEP)             //[9:2]Monitorģʽ��Base���٣��������ٲ���                                                 
                     +(0<<BIT_BASE_TRACK_MODE)              //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
                     +(1<<BIT_BASE_TRACK_ENABLE));          //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 

            usReg5 = rACC_OFFSET;        //����ACC Offsetֵ             

            usReg6 = rTP_MONITOR_THRESHOLD;
            usReg7 = rKEY_MONITOR_THRESHOLD;

			/*˫��ɨ��ʱ���ɨ��Ƶ����120KHz,���߲������ɨ��Ƶ����60KHz*/

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
*  Brief: ���ݰ����������� 
*  Input: ucModeEn  0:�رջ��ݰ���;1:�������ݰ���
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetMode(UINT8 ucModeEn)
{
    UINT16 XRAM Reg64 = 0;

    Reg64 = Drv_XsiReadReg(pXSIREG,Addr_MCAP_SCAN_CFG,AFE_REG);
    Reg64 &= ~(1<<15);
    if(ucModeEn)           //�������ݰ��� 
    {
        Reg64 |= (1<<15);             
    }

    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);    
}

/*******************************************************************************
*   Name: DrvMcapSetFir
*  Brief: ���ݰ������������� 
*  Input: ucMode  0:6��������;1:8��������
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetFir(ST_McapParameter * pMcapPara)
{
    UINT16 XRAM Reg79 = 0,Reg66 = 0;

    //Reg79 = Drv_XsiReadReg(pXSI0Regs,0x4F,AFE_REG);

    //Reg79 &= 0x7FE0;           //���mcap_hbfir_en/mcap_lpfir_en/mcap_lipfir_tap

    if(pMcapPara->usHbFirEn)
    {
        //Reg79 |= (1<<15);        //����mcap_hbfir_en 
        ;
    }
    else
    {
        pMcapPara->usLpFirEn = 0;//�ر�mcap_hbfir_en����ͬʱ�ر�mcap_lpfir_en
    }

#if 0    
    if(pMcapPara->usLpFirEn)
    {
        Reg79 |=(1<<4);         //����mcap_lpfir_en
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
*  Brief: ���ݰ������������� 
*  Input: ucMode  0:6��������;1:8��������
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
        Reg64 |= (1<<4);      //8��������         
    }
    else
    {
        Reg64 &= ~(1<<4);    //6��������

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
*  Brief: ���ݰ���������ʼ������ 
*  Input: ucInit  [9:0] ������ʼ������
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetSampleInit(ST_McapParameter * pMcapPara)
{
    /*������ʼ������mcap_int_sampl_cfg*/
    pMcapPara->usSampl_Init &= 0x03FF;//ֻ�к�10λ��Ч
    if(pMcapPara->usSampl_Init > ((pMcapPara->usK1+pMcapPara->usK2+2)*2))
    {
        pMcapPara->usSampl_Init = (pMcapPara->usK1+pMcapPara->usK2+2)*2;  //����ܳ���(K1+K2+2)*2
    }
    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_INIT_SAMPL_CFG,pMcapPara->usSampl_Init,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_INIT_SAMPL_CFG,pMcapPara->usSampl_Init,AFE_REG);
}

/*******************************************************************************
*   Name: DrvMcapSetAnaTiming
*  Brief: ���ݰ���ģ��ʱ������ 
*  Input: ucDataInv/ucMsbInv
* Output: 
* Return: 
*******************************************************************************/
UINT8 DrvMcapSetAnaTiming(ST_McapParameter * pMcapPara,UINT8 ucScanMode)   
{
    UINT8 XRAM ucDummyNum;
    UINT8 XRAM flag = 0;

    /* ����mux�õ������dummy�� */
    switch(ucScanMode)
    {
        case 0://ɨ�跽ʽ1
        case 1://ɨ�跽ʽ2
        case 2://ɨ�跽ʽ3
        case 3://ɨ�跽ʽ4
        case 6://ɨ�跽ʽ7
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
                
        case 4://ɨ�跽ʽ5
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

        case 5://ɨ�跽ʽ6
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

    if(pMcapPara->usLpFirTap == 14)//14��
    {
        if((pMcapPara->usLpFirEn)&&(pMcapPara->usHbFirEn))
        {
            if((pMcapPara->usSxMode == 0)&&(pMcapPara->usSampl_6 == 1))//˫��ɨ��,6������
            {
                if(pMcapPara->usScanNum < (ucDummyNum + 13))
                {
                    flag = 1;
                    DBG_FLOW("\nScanNum is not large enough1!");
                    DBG_FLOW("\nlast ScanNum:%d,new ScanNum:%d",pMcapPara->usScanNum,ucDummyNum + 13);
                    pMcapPara->usScanNum = ucDummyNum + 13;
                } 
            }

            if((pMcapPara->usSxMode == 1)&&(pMcapPara->usSampl_6 == 1))//����ɨ��,6������
            {
                if(pMcapPara->usScanNum < (ucDummyNum + 13)*2)
                {
                    flag = 1;
                    DBG_FLOW("\nScanNum is not large enough2!");
                    DBG_FLOW("\nlast ScanNum:%d,new ScanNum:%d",pMcapPara->usScanNum,(ucDummyNum + 13)*2);
                    pMcapPara->usScanNum = (ucDummyNum + 13)*2;
                } 
            }

            if((pMcapPara->usSxMode == 0)&&(pMcapPara->usSampl_6 == 0))//˫��ɨ��,8������
            {
                if(pMcapPara->usScanNum < (ucDummyNum + 11))
                {
                    flag = 1;
                    DBG_FLOW("\nScanNum is not large enough3!");
                    DBG_FLOW("\nlast ScanNum:%d,new ScanNum:%d",pMcapPara->usScanNum,(ucDummyNum + 11));
                    pMcapPara->usScanNum = (ucDummyNum + 11);
                } 
            }

            if((pMcapPara->usSxMode == 1)&&(pMcapPara->usSampl_6 == 0))//����ɨ��,8������
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
*  Brief: ���ݰ����Ƿ����keyͨ����diff_max
*  Input: ucEn/ucMode
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetDiffMax(ST_McapParameter* pMcapPara)                       
{
    UINT16 XRAM Reg64,Reg65;

    Reg64 = Drv_XsiReadReg(pXSIREG,0x40,AFE_REG);

    Reg64 &= ~(1<<14);                                  //������diff max����

    if((pMcapPara->usDiffSet)&0x02) 
    {
        Reg64 |= (1<<14);                                  //����diff max����
        Reg65 = Drv_XsiReadReg(pXSIREG,0x41,AFE_REG);
        Reg65 &= ~(1<<3);                                 //��ADC���ݽ���diff_max����
        if(pMcapPara->usDiffSet == 0x03)
        {
            Reg65 |= (1<<3);                              //�Խ���������,��mixer���ݽ���diff_max����         
        
        Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCANSR,Reg65,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCANSR,Reg65,AFE_REG);  
    }

    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_SCAN_CFG,Reg64,AFE_REG);    
    }
}
/*******************************************************************************
*   Name: DrvMcapSetRawGain
*  Brief: ���ݰ����Ƿ��RAWDATA�������洦��
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

    Reg64 &= ~(1<<2);                                  //����RAWDATA�������洦��

    Reg68 = (pMcapPara->usRawdataOffset)&0x0000FFFF;

    Drv_XsiWriteReg(pXSI0Regs,Addr_RAWDATA_OFFSET_L,Reg68,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_RAWDATA_OFFSET_L,Reg68,AFE_REG); 
    
    if(pMcapPara->usGainEn)
    {
        Reg64 |= (1<<2);                                  //��RAWDATA�������洦��
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
*  Brief: ���ݰ����Ƿ��ADC���ݽ��б��ͼ��
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetOverflow(ST_McapParameter * pMcapPara)                        
{
    UINT16 XRAM Reg64,Reg72,Reg73,Reg74,Reg75,Reg76,Reg77,Reg78;
  
    Reg64 = Drv_XsiReadReg(pXSIREG,Addr_MCAP_SCAN_CFG,AFE_REG);
    Reg64 &= 0xFFFE;                             //���overflow_en
    if(pMcapPara->usOvfEn)
    {
        Reg64 |= 0x0001;

        Reg72 = (pMcapPara->usOvfTh)&0x0FFF;
        Reg73 = (pMcapPara->usUdwTh)&0x0FFF;
        Reg74 = (pMcapPara->usOvfUpBound)&0x0FFF;
        Reg75 = (pMcapPara->usOvfPointFrm)&0x0FFF;

        Reg64 &= 0xFFFD;                        //���overflow_clr_en
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
*  Brief: ���ݰ����Ƿ��ADC���ݽ��б��ͼ��
*  Input: ucEn
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetPara(ST_McapParameter * pMcapPara,ST_AfeTabList * pAfeTab,UINT8 ucTabId)                         //δдȫ
{
    UINT16 XRAM ucReg;

    /*�л���TblRam*/
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    /*��ȡʹ��tab���k1,k2*/    
    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+8,AFE_REG);
    pAfeTab ->usAnaGenCfg0 = ucReg;
    pMcapPara->usK1= ucReg&0x07FF;

    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+9,AFE_REG);
    pAfeTab ->usAnaGenCfg1 = ucReg;    
    pMcapPara->usK2 = ucReg&0x07FF;

    /*ɨ�����*/
    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+1,AFE_REG);
    pAfeTab ->usScanCfg0= ucReg;
    pMcapPara->usScanNum = (ucReg&0x07F8)>>3;
    pMcapPara->usScanMode = ucReg&0x0007;

    /*sxɨ�跽ʽ*/
    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+2,AFE_REG);
    pAfeTab ->usScanCfg1 = ucReg;
    pMcapPara->usSxMode = (ucReg&0x0100)>>8; //0:˫��ɨ��; 1:����ɨ��

    /*��ȡdummy_num����*/
    ucReg = Drv_XsiReadReg(pXSIREG,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+3,AFE_REG);
    pAfeTab ->usDummyScanCfg = ucReg;
    pMcapPara->usFrmDummy = ucReg&0x001F;
    pMcapPara->usSecDummy = (ucReg&0x03E0)>>5;    
    pMcapPara->usMuxDummy = (ucReg&&0x7C00)>>10;

    /*����˲�����ͨ�˲�����*/
    pMcapPara->usLpFirEn     = 1;
    pMcapPara->usHbFirEn     = 1;
    pMcapPara->usLpFirTap    = 14;
    pMcapPara->usLpFirStart  = 14;
    pMcapPara->usLpFirSumNum = 1;//16;     //��������Ҫ��ô�� ������Ҫ��ô��,���˲���ȫ�صĻ�,�������Ӧ����ɨ�����*��������
    pMcapPara->usLpFirCof0   = 0x0104;
    pMcapPara->usLpFirCof1   = 0x0296;
    pMcapPara->usLpFirCof2   = 0x04e5;
    pMcapPara->usLpFirCof3   = 0x07c3;
    pMcapPara->usLpFirCof4   = 0x0acd;
    pMcapPara->usLpFirCof5   = 0x0d84; 
    pMcapPara->usLpFirCof6   = 0x0f65;
    pMcapPara->usLpFirCof7   = 0x1011;
    
    /*����������*/
    pMcapPara->usSampl_6 = 0;         //1:��ʾ6��������0��ʾ8������

    /*������ʼ������*/
    pMcapPara->usSampl_Init = 0;//0x42;  //�Բɼ�����ADCӰ��ܴ�,����ͨ���ı����ֵ�����ĸ�ֵ��Ӧ��rawdata������ж��ǲ���������ȷ.

    /*Diff_max����*/
    pMcapPara->usDiffSet = 0x2;     //2b'0x:������diff_max;2b'10:��ADC���ݽ���diff_max����;2b'11:��mixer���ݽ���diff_max����

    /*���洦��ע������*/
    /*�������洦��ʱrawdata = ((sum_data - offset) * gaincof>>shiftCof)<<1 */
    /*�������洦��ʱrawdata = sum_data << 1.  sum_dataΪ��������Ľ�� */
    /*����û�����洦��ʱ,rawdata = 0x170;�������洦��ʱ,��shiftcof = 0,gaincof = 1,offset = 0x10,��rawdataӦΪ0x150���� */

    /*���洦������*/
    pMcapPara->usGainEn = 0;         //���������洦��
    pMcapPara->usGainCof = 1;        //����ϵ��
    pMcapPara->usRawShiftCof = 0;
    pMcapPara->usRawdataOffset = 0x0;

    /*ADC���ͼ������*/
    pMcapPara->usOvfEn = 0;
    pMcapPara->usOvfFlg = 0;
    pMcapPara->usOvfTh  = 0xfff;//0x03e8;
    pMcapPara->usUdwTh  = 0;
    pMcapPara->usOvfUpBound = 0x04;//0x0A;
    pMcapPara->usOvfPointFrm = 0x2;//0x20;

    /*ADC���ͼ�������־����*/
    pMcapPara->usOvfClrEn = 0;
    pMcapPara->usNormalDwTh = 0x0;//0x190;
    pMcapPara->usNormalUpTh = 0xfff;//0xfff;//0x258;
    pMcapPara->usOvfClrFrmNum = 0x02;//0x64;

    /*������־��ʼ��*/
    pMcapPara->usErrFlg = 0;
    pMcapPara->usErrSta = 0;
    pMcapPara->usDoneFlg = 0;
    
}


/*******************************************************************************
*   Name: DrvMcapInit
*  Brief: ���ݰ�����ʼ�� 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapModeInit(UINT8 ucModeEn,UINT8 ucTabId)
{
    UINT8 XRAM ucScanMode;
    UINT8 XRAM i;
    UINT16 XRAM ucTalReg1,ucReg;
    if(ucModeEn == 0)//�رջ��ݰ���
    {
        DrvMcapSetMode(0);
        return;
    }
    else
    {
        /*��������*/
        DrvMcapSetPara(g_pMcapPara,g_pAfeTabPara,ucTabId);
    
        DrvMcapSetMode(1);//�������ݰ���
    }

#if 1    
    /*���õ�ͨ�˲�������˲�*/
    DrvMcapSetFir(g_pMcapPara);

    /*����������*/
    DrvMcapSetSampleRate(g_pMcapPara,g_pAfeTabPara,ucTabId);

    /*������ʼ������*/
    DrvMcapSetSampleInit(g_pMcapPara);   

    /*ANAʱ����*/
    ucScanMode = g_pMcapPara->usScanMode;
    if(DrvMcapSetAnaTiming(g_pMcapPara,ucScanMode) == 1)//tx_clk�Ƿ�����Ҫ��
    {
        ucTalReg1 = (g_pAfeTabPara->usScanCfg0)&0xF807;
        ucTalReg1 |= ((g_pMcapPara->usScanNum)<<3);
        DBG_FLOW("\nReg1:%04x",ucTalReg1);
        Drv_XsiWriteReg(pXSI0Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+1,ucTalReg1,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,TAB_START_ADDR+TAB_RAM_LEN*ucTabId+1,ucTalReg1,AFE_REG);        
    }

    /*���û��ݰ����Ƿ����diff_max*/
    DrvMcapSetDiffMax(g_pMcapPara);

    /*RAWDATA���洦������*/
    DrvMcapSetRawGain(g_pMcapPara);

    /*ADC���ݱ��ͼ������*/
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
*  Brief: ��ȡ���ݰ�����״̬ 
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
    //DBG_FLOW("\ndone flag:%04x",pMcapPara->usDoneFlg);           //���û������
    DBG_FLOW("\nover clr flag:%04x",pMcapPara->usOvfClrFlg);

    
}

/*******************************************************************************
*   Name: DrvMcapReadSta
*  Brief: �������ģʽ 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvMcapSetTestMode(UINT8 ucMode,UINT8 ucKeyNum)
{
    UINT16 XRAM ucReg04,ucReg51;
    ucReg04 = Drv_XsiReadReg(pXSIREG,0x04,AFE_REG);

    ucReg04 &= 0xFFFE;     //����ģʽ
    if(ucMode)
    {
        ucReg04 |=0x0001;  //��ͨģʽ
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
    GPIO_INT_SEL = 1;//�����ѽ�ѡΪp0_7
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
    GPIO_INT_SEL = 1;//�����ѽ�ѡΪp0_7
    TEST_CLK_EN = 1;

	if(ucSrc == 1)
	{
		SEL_32K_SRC = 1;         //д1���Է���,
	}
	else if(ucSrc == 2)
	{
		PROBE32K_DIG_EN = 1;		
	}
	else if(ucSrc == 3)
	{
		PROBE32K_FROM1M_EN = 1;
		SEL_32K_SRC = 0;         //FPGAд1����д0�����Է���
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
    ucConfig = (0x1<<8) + 0x1;//ca_p1,afe��ca�ź�

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
    ucConfig = (0x2<<8) + 0x1;//ca_p4,afe��ca�ź�

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
    ucConfig = (0x0<<8) + 0x1;//ca_rst,afe��ca�ź�

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
    ucConfig = (0x1<<4) + 0x0;//lcd_run,afe��soc�ź�

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
    ucConfig = (0x2<<4) + 0x0;//lcd_Busy,afe��soc�ź�

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
    ucConfig = (0x5<<4) + 0x0;//Tp_Scan,afe��soc�ź�

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
    ucConfig = (0x6<<4) + 0x0;//Tp_Busy,afe��soc�ź�

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
    ucConfig0 = 0x4;      //afe��mcap�ź�
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
    ucConfig0 = 0xA;      //afe��mcap�ź�
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
    ucConfig0 = 0xA;      //afe��mcap�ź�
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

    //����ֻ��ѡ���һ������
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

    //����ֻ��ѡ���һ������
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

    //����ֻ��ѡ���һ������
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

    //����ֻ��ѡ���һ������
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
    //����48M/32K/Test_Debug3ֻ��ͬʱ��һ��,����p0_6

        
    //Test_CLk32K(0);  //��p0_6���ź� 
    //Test_CLk48M(0);  //��P0_6���ź�

	//Ŀǰ��������pin0������debug0��debug2,����ֻ�ܿ�1��;pin1������debug1��debug3,����Ҳֻ�ܿ�1��.
    Test_Debug0();     //��tp2pad_dsv_en6���ź�
	//Test_Debug1();     //��led_pwm[0]���ź�
    //Test_Debug2();     //����SPI0ʱ,��P0_0���ź�,����IICʱ����p0_2���ź�
    Test_Debug3();     //��p0_6���ź�
    
}


#if 0 // ���CBУ��
/*******************************************************************************
*   Name: DrvPara_WriteCB
*  Brief:
*         1.����CB���Ĵ�������
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvPara_WriteCB(UINT8 Tbl_ID)
{
    UINT8 i;
    UINT8 ucOrder;
    UINT8 ucLenS0;  /* S0���� ��Чͨ���� */
    UINT8 ucLenS1;  /* S1���� ��Чͨ���� */

    UINT8 ucTbl;   /* ��ģʽ��Ӧ�ı�� */

    UINT16 XRAM usTblBaseAddr;
    UINT16 XRAM usAddr;
    UINT16 XRAM ausCbValue[(CH_LEN_MAX+1)>>1];
    UINT8 XRAM aucCbRegL[CH_LEN_MAX+1];
    UINT8 XRAM aucCbRegR[CH_LEN_MAX+1];

        ucTbl = Tbl_ID;
        usTblBaseAddr = ID_TBL1_BASE + ucTbl*TBL_LEN_MAX + 22;

        /* ����ַ�л��� Tbl�� */
        DrvAfeSelTaborRepRam(AREA_TBL_RAM);
        
        ucLenS0 = 224;
        ucLenS1 = 224;

        /* ��AFE */
        for (i = 0; i < ucLenS0; i++)
        {
            ucOrder = g_ucOrderBuf[i];
            aucCbRegL[ucOrder+1] = 1 | (ucCbValue[i]<<1);
        }

        /* ��AFE */
        for (i = 0; i < ucLenS1; i++)
        {
            usAddr = ucLenS0 + i;
            ucOrder = g_ucOrderBuf[usAddr];
            aucCbRegR[ucOrder+1] = 1 | (ucCbValue[usAddr] << 1);
        }
  
        /* �� key */
        usAddr = ucLenS0 + ucLenS1;
        /*tbl Ram CB0�ĸ߰�λ���Key0-2�ĸ�2λ*/

        /* Key1��Чʱ����ֵ */
        if (1)
        {
            aucCbRegL[0] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegL[1] = (aucCbRegL[1]&0xFC)
                                    + ((ucCbValue[usAddr]&0xC0) >> 6);
        }
        usAddr++;
        /* Key2��Чʱ����ֵ */
        if (1)
        {
            aucCbRegL[2] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegL[1] = (aucCbRegL[1]&0xF3)
                                    + ((ucCbValue[usAddr]&0xC0) >> 4);
        }
        usAddr++;

        /* Key3��Чʱ����ֵ */
        if (1)
        {
            aucCbRegL[3] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegL[1] = (aucCbRegL[1]&0xCF)
                                    + ((ucCbValue[usAddr]&0xC0) >> 2);
        }
        usAddr++;
        /*  */

        /* ��Key4��Чʱ����ֵ */
        if (1)
        {
            aucCbRegR[0] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegR[1] = (aucCbRegR[1]&0xFC)
                                    + ((ucCbValue[usAddr]&0xC0) >> 6);
        }
        usAddr++;

        /* ��Key5��Чʱ����ֵ */
        if (1)
        {
            aucCbRegR[2] = 1 | ((ucCbValue[usAddr]&0x3F) << 1);
            aucCbRegR[1] = (aucCbRegR[1]&0xF3)
                                    + ((ucCbValue[usAddr]&0xC0) >> 4);
        }
        usAddr++;
        /* ��Key6��Чʱ����ֵ */
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
*         1.CB�Զ�У��,CFУ��ʱ�����ó����
*         2.CB��00-->0x7F,  ��λ-->��λ����λ�ƽ�
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvClbCB(UINT8 ucTabID)
{
    SINT8 scCnt;                // У׼����������
    UINT8 ucDataMask;           // ��ʱ���õ�CBֵ
    UINT8 ucKeyMask;            // ��ʱ���õ�Key CBֵ:���У׼����λ��У
    UINT16 i;
    UINT16 usChNum;             // ��ҪУ׼������ͨ������
    UINT16 usChVaNum;           // ��ҪУ׼��vaͨ������
    UINT16 usRawTargeNormal;    // ����ģʽ У׼Ŀ��ֵ


    /* +6������ͨ�� */
    usChVaNum = CH_LEN;  /* ��Чͨ���ܳ���, �������� */
    usChNum = usChVaNum + KEY_NUM_MAX;
    /* ��������ͨ��CBֵ */
    memset(ucCbValue, 0x00, usChNum);
   
    // RAWDATAĿ��ֵ���ã�OutPutRaw = (1CycleRaw * CycleSum)>>AccShift
    usRawTargeNormal = 8192;

    /* ��������7������ɨ�裬��αƽ���ʽУ׼CBֵ */
    for (scCnt = (SC_CLB_TIMES - 1); scCnt >= 0; scCnt--)
    {
        /* Ԥ��CBֵ */
        if (scCnt > 1)
        {
            ucDataMask = (0x01 << (scCnt-2)); /*va��ֻУ׼6λ*/
        }
        else
        {
            ucDataMask = 0x00;
        }
#if 1
        if (scCnt > 1)
        {
            ucKeyMask = (0x01 << (scCnt-2)); /*Key��2λ��������*/
        }
        else
        {
            ucKeyMask = 0x00;
        }
#else
        ucKeyMask = (0x01 << scCnt);
#endif

        /* VAͨ���˴�У��λ�� */
        for (i = 0; i < usChVaNum; i++)
        {
            ucCbValue[i] |= ucDataMask;
        }
        /* Keyͨ���˴�У��λ�� */
        for (i = 0; i < KEY_NUM_MAX; i++)
        {
            ucCbValue[usChVaNum+i] |= ucKeyMask;
        }

        /* CB����д��Ĵ��� */
        DrvPara_WriteCB(ucTabID);
        
        g_ucAramReadyFlag = 0;
        /* ����Tab�� */
        DrvLoadTabSingle(ucTabID,0);
        /* scan start */
        DrvAsmScanStart();

        /* wait end��*/
        while(!g_ucAramReadyFlag);

        /* ��ǰ֡����,AFE ARAM READY�ж�������ݰ��˵�RawBuf�� */
#if 1
        DBG_FLOW("\nRaw time %d \n",scCnt);
        DrvGetRawdata();
#endif
        /* ������ͨ������У�� */
        for (i = 0; i < usChNum; i++)
        {
            /* ���RAWDATAС��Ŀ��ֵ����Ԥ���ֵ������������Ŀ��ֵ�����ֵ�ǰԤ��ֵ */
            if (g_usRawdataBuf[i] < usRawTargeNormal)
            {
                ucCbValue[i] &= ~ucDataMask;
            }
        }

    }
    
    /* CB����д��Ĵ��� */
    DrvPara_WriteCB(ucTabID);
}
#endif


