/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: DrvAsmCtrl.c
*
*    Author: linjianjun
*
*   Created: 2014-10-10
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* Included header files
*******************************************************************************/
#include "CfgGlobal.h"
#include "CfgAutoTune.h"

#include "DrvSysCtrl.h"
#include "DrvAfe.h"
//#include "DrvAsmCtrl.h"
//#include "DrvMonDet.h"

#include "LibDrv.h"

//#include "AppDataStruct.h"
//#include "AppAfeCtrl.h"


#include "DrvAsm.h"

/*******************************************************************************
* Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* Static variables
*******************************************************************************/

/*******************************************************************************
* Global variable or extern global variabls/functions
*******************************************************************************/
ST_AsmRegisters * XRAM pAsmRegs = (volatile ST_AsmRegisters *)ASM_REG_BASE_ADDR;
UINT16 XRAM g_ucLcdBusyCnt = 0;


extern volatile UINT8 XRAM g_ucFrameEndFlag;
extern volatile UINT8 XRAM g_ucAramReadyFlag;  
extern volatile UINT16 XRAM g_usAsmIntFlag0;
extern volatile UINT16 XRAM g_usAsmIntFlag1;
extern volatile UINT8 XRAM g_ucLcdSyncMissFlag;   
extern volatile UINT16 XRAM g_ucIntCount;
extern volatile UINT8 XRAM g_ucTimeOutFlag;  // hw mon time out
extern volatile UINT8 XRAM g_ucTchDetFlag;  // tch det

extern UINT8 XRAM ucAfeRunMode;
extern UINT8 XRAM g_ucAfeScanMode;

/*******************************************************************************
* Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: Asm_Config_Init
*  Brief: Afe scan���ò�����ʼ��
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Asm_Config_Init(void)
{     
    //REG_14    
    pAsmRegs->usAsmScanCfg0 =   ((0<<BIT_MONITOR_MODE)         // [15]Ӳ���������ģʽ: 1: �ǣ�      0:��   
                                +(0<<BIT_CB_ADJUST_MODE)       // [14]CBУ��ģʽ:       1:У��ģʽ   0:����ģʽ           
                                +(0<<BIT_AFE_CLKGATE_EN)       // [12]�Զ��ſ�AFEʱ��:  1:�Զ��ſ� 0:���Զ��ſ� 
                                +(0<<BIT_SCAN_START_STORE_EN)  // [10]1:���棬�Զ�������һ��ɨ�裬0:�����棬���Զ������´�ɨ�衣          
                                +(1<<BIT_LCD_FRAME_HEAD_ALIGN) // [9]��0֡������ʱ��ѡ��:0:��ǰLCD֡��ʼʣ���ɨ��; 1:���ID,��LCD֡��ʼɨ��      
                                +(0<<BIT_VBLANK_EDGE_SEL)      // [8]busy_id�����ź�ѡ��: 0:������ ��1: �½���  
                                +(0<<BIT_VSTART_EDGE_SEL)      // [7]busy_id�����ź�ѡ��: 0:������ ��1: �½���      
                                +(0<<BIT_VMID_EDGE_SEL)        // [6]busy_id�����ź�ѡ��: 0:������ ��1: �½��� 
                                +(0<<BIT_VEND_EDGE_SEL)        // [5]busy_id�����ź�ѡ��: 0:������ ��1: �½��� 
                                +(0<<BIT_CLR_BUSY_ID_SEL)      // [4:3] �����ź�ѡ��: 0:vstart; 1:vmid 2:vend 3:vblank
                                +(0<<BIT_TP_FRAME_NUM));       // [2:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡  

    pAsmRegs->usAsmScanCfg0 |= (0<<BIT_SCAN_START_STORE_EN);      // 1:���棬�Զ�������һ��ɨ��

    pAsmRegs->usAsmScanCfg0 |= (1<<BIT_LCD_FRAME_HEAD_ALIGN);     // 1:���ID,��LCD֡��ʼɨ�� 
#if TEST_CUR_LEFT_SCAN
    pAsmRegs->usAsmScanCfg0&=~(1<<BIT_LCD_FRAME_HEAD_ALIGN);      // 0:��ǰLCD֡��ʼʣ���ɨ��;  
#endif
    DBG_FLOW("\n  13 pAsmRegs->usAsmScanCfg0: %04x",pAsmRegs->usAsmScanCfg0);
    
    //REG_15         
    pAsmRegs->usAsmScanCfg1 =   ((1<<BIT_LCD_RUN_INTPHASE)     // [15] LCD RUN�жϵ�ƽѡ��         0:�͵�ƽ��1:���ߵ�ƽ                       
                                +(1<<BIT_LCD_DSTB_INTPHASE)    // [14] LCD Deep Standby�жϵ�ƽѡ��0:�͵�ƽ��1:���ߵ�ƽ                       
                                +(0<<BIT_LPF_MODE_TP_TURBO_REQ)// [9] ����: 0:������  1:����
                                +(0<<BIT_VB_MODE_REQ)          // [8] ����: 0:С��    1:��� 
                                +(1<<BIT_TP_END_SEL)           // [5] ֡����λ��ѡ��. 0:tp_frame_end. 1:aram rdy(��ϵ������ɨ����֡����λ��)
                                +(DAT_TP_STANDBY_ENABLE<<BIT_STB_EN)               // [4] Ԥ�ȼ��ز�������CB shiftʹ��: 1:ʹ�� ��lcd busyǰ�Ĵ�����tab,�ٶȿ졣ֻ֧��С��        
                                +(0<<BIT_HW_MONITOR_EN)        // [3] Ӳ��Monitorʹ�ܣ�           1: ʹ�� 
                                +(0<<BIT_VBLANK_INV));         // [1] Vblank��Ч��ƽѡ�������ж�, 0:�ߵ�ƽ��1:�͵�ƽ   
                          
    //REG_16 
    pAsmRegs->usAsmTpFrameCfg0 =  ((0<<BIT_TAB_ID1)            // [14]��1��TP֡�õ�Table���  
                                  +(0<<BIT_BUSY_ID1)           // [8] ��1��TP֡��ʼ�Ӻ�        
                                  +(0<<BIT_TAB_ID0)            // [6] ��0��TP֡�õ�Table���     
                                  +(0<<BIT_BUSY_ID0));         // [0] ��0��TP֡��ʼ�Ӻ� 

    //REG_17 
    pAsmRegs->usAsmTpFrameCfg1 =  ((0<<BIT_TAB_ID3)            // [14]��3��TP֡�õ�Table���  
                                  +(0<<BIT_BUSY_ID3)           // [8] ��3��TP֡��ʼ�Ӻ�        
                                  +(0<<BIT_TAB_ID2)            // [6] ��2��TP֡�õ�Table���     
                                  +(0<<BIT_BUSY_ID2));         // [0] ��2��TP֡��ʼ�Ӻ� 

    //REG_18 
    pAsmRegs->usAsmTpFrameCfg2 =  ((0<<BIT_BUSY_ID5)           // [8] ��5��TP֡��ʼ�Ӻ�        
                                  +(0<<BIT_BUSY_ID4));         // [0] ��4��TP֡��ʼ�Ӻ� 

    //REG_19 
    pAsmRegs->usAsmTpFrameCfg3 =  ((0<<BIT_BUSY_ID7)           // [8] ��7��TP֡��ʼ�Ӻ�        
                                  +(0<<BIT_BUSY_ID6));         // [0] ��6��TP֡��ʼ�Ӻ� 

    //REG_20   
    pAsmRegs->usAsmScanDly =   ((0<<BIT_TAB_EN3)               // [13] Tab3��ʹ��: 1:ʹ��  �Ѿ�ɾ�� 
                               +(0<<BIT_TAB_EN2)               // [12] Tab2��ʹ��: 1:ʹ��  �Ѿ�ɾ�� 
                               +(0<<BIT_TAB_EN1)               // [11] Tab1��ʹ��: 1:ʹ��  �Ѿ�ɾ�� 
                               +(0<<BIT_TAB_EN0)               // [10] Tab0��ʹ��: 1:ʹ��  �Ѿ�ɾ�� 
                               +(0<<BIT_SCAN_DELAY));          // [9:0]LCD RUN�½��ص�ɨ�迪ʼ����ʱ

    //REG_21 
    pAsmRegs->usAsmStbMaseL =  (0xffff<<BIT_STB_MASK_L);       // [15:0]STB_TICK�ж��������õ�λ

    //REG_22  
    pAsmRegs->usAsmStbMaseH =  (0xffff<<BIT_STB_MASK_H);       // [15:0]STB_TICK�ж��������ø�λ

    //REG_23 24 25   
    pAsmRegs->usAsmAramBaseL   = 0;
    pAsmRegs->usAsmAramBaseR   = CH_ORDER_MAX;
    pAsmRegs->usAsmAramBaseKey = 2*CH_ORDER_MAX;

    //REG_26 27 28   
    pAsmRegs->usAsmAramCBL     = 0;
    pAsmRegs->usAsmAramCBR     = CH_ORDER_MAX;  
    pAsmRegs->usAsmAramCBKey   = 2*CH_ORDER_MAX;

    //REG_04
    pAsmRegs->usAsmIntEn0 = 0; 
    DBG_FLOW("\n pAsmRegs->usAsmIntEn0 : %04x",pAsmRegs->usAsmIntEn0);
//    while(1);

    pAsmRegs->usAsmIntEn0 =  ((0<<BIT_LCD_BUSY_FALL_EN0)            //15
                             +(0<<BIT_LCD_BUSY_RISE_EN0)            //14
                             +(0<<BIT_LCD_PANEL_CONFLICT_EN0)       //13
                             +(0<<BIT_LCD_DSTB_FAIL_EN0)            //12
                             +(0<<BIT_LCD_DSTB_RISE_EN0)            //11 
                             +(0<<BIT_LCD_SYNC_MISS_FALL_EN0)       //10
                             +(0<<BIT_LCD_SYNC_MISS_RISE_EN0)       //9
                             +(0<<BIT_LCD_ARAM_RDY_EN0)             //8
                             +(0<<BIT_LCD_FRAME_END_EN0)            //7
                             +(0<<BIT_LCD_TCH_DET_EN0)              //6
                             +(0<<BIT_LCD_VSTART_EN0)               //5
                             +(0<<BIT_LCD_VMID_EN0)                 //4
                             +(0<<BIT_LCD_VEND_EN0)                 //3
                             +(0<<BIT_LCD_VBLANK_EN0)               //2
                             +(0<<BIT_LCD_RUN_FALL_EN0)             //1 
                             +(0<<BIT_LCD_RUN_RISE_EN0));           //0
    

    //REG_05
    pAsmRegs->usAsmIntEn1 = 0; 
    pAsmRegs->usAsmIntEn1 = ((0<<BIT_HW_MON_TIMEOUT_EN1)             //14
                            +(0<<BIT_LCD_LPF_MODE_EN_FALL_EN1)      //13
                            +(0<<BIT_LCD_LPF_MODE_EN_RISE_EN1)      //12
                            +(0<<BIT_LCD_STB_TICK_EN1)              //11
                            +(0<<BIT_LCD_ODD_EVEN_FALL_EN1)         //10
                            +(0<<BIT_LCD_ODD_EVEN_RISE_EN1)         //9
                            +(0<<BIT_LCD_VDO_MODE_FALL_EN1)         //8
                            +(0<<BIT_LCD_VDO_MODE_RISE_EN1)         //7  
                            +(0<<BIT_LCD_IDLE_MODE_FALL_EN1)        //6  
                            +(0<<BIT_LCD_IDLE_MODE_RISE_EN1)        //5
                            +(0<<BIT_LCD_3D_MODE_FALL_EN1)          //4
                            +(0<<BIT_LCD_3D_MODE_RISE_EN1)          //3
                            +(0<<BIT_LCD_RUN_EN1)                   //2
                            +(0<<BIT_LCD_DSTB_EN1));                //1
                         
                                                                             
// Test Wake Up    
     //REG_06
     pAsmRegs->usAsmIntWakeEn0 = 0;
     pAsmRegs->usAsmIntWakeEn0 = ((0<<BIT_LCD_BUSY_FALL_WAKE_EN0)       //15
                                 +(0<<BIT_LCD_BUSY_RISE_WAKE_EN0)       //14
                                 +(0<<BIT_LCD_PANEL_CONFLICT_WAKE_EN0)  //13
                                 +(0<<BIT_LCD_DSTB_FAIL_WAKE_EN0)       //12
                                 +(0<<BIT_LCD_DSTB_RISE_WAKE_EN0)       //11
                                 +(0<<BIT_LCD_SYNC_MISS_FALL_WAKE_EN0)  //10
                                 +(0<<BIT_LCD_SYNC_MISS_RISE_WAKE_EN0)  //9
                                 +(0<<BIT_LCD_ARAM_RDY_WAKE_EN0)        //8
                                 +(0<<BIT_LCD_FRAME_END_WAKE_EN0)       //7
                                 +(0<<BIT_LCD_TCH_DET_WAKE_EN0)         //6
                                 +(0<<BIT_LCD_VSTART_WAKE_EN0)          //5
                                 +(0<<BIT_LCD_VMID_WAKE_EN0)            //4
                                 +(0<<BIT_LCD_VEND_WAKE_EN0)            //3
                                 +(0<<BIT_LCD_VBLANK_WAKE_EN0)          //2
                                 +(0<<BIT_LCD_RUN_FALL_WAKE_EN0)        //1
                                 +(0<<BIT_LCD_RUN_RISE_WAKE_EN0));      //0  
     //REG_07
     pAsmRegs->usAsmIntWakeEn1 = 0;
     pAsmRegs->usAsmIntWakeEn1 = ((0<<BIT_LCD_STB_TICK_WAKE_EN1)        //11  
                                 +(0<<BIT_LCD_ODD_EVEN_FALL_WAKE_EN1)   //10
                                 +(0<<BIT_LCD_ODD_EVEN_RISE_WAKE_EN1)   //9
                                 +(0<<BIT_LCD_VDO_MODE_FALL_WAKE_EN1)   //8
                                 +(0<<BIT_LCD_VDO_MODE_RISE_WAKE_EN1)   //7 
                                 +(0<<BIT_LCD_IDLE_MODE_FALL_WAKE_EN1)  //6 
                                 +(0<<BIT_LCD_IDLE_MODE_RISE_WAKE_EN1)  //5
                                 +(0<<BIT_LCD_3D_MODE_FALL_WAKE_EN1)    //4
                                 +(0<<BIT_LCD_3D_MODE_RISE_WAKE_EN1));  //3     

#if TEST_STANDBY_WAKEUP_ALL
    pAsmRegs->usAsmIntWakeEn0 = 0xFFFF;
    pAsmRegs->usAsmIntWakeEn1 = 0xFFFF;
#endif
                                          
     DBG_FLOW("\n 6usAsmIntWakeEn0: %04x",pAsmRegs->usAsmIntWakeEn0);
     DBG_FLOW("\n 7usAsmIntWakeEn1: %04x",pAsmRegs->usAsmIntWakeEn1);     


#if 0// LCD RELOAD FLASH WAKE UP  interrupt 0
    LCD_RELOAD_FLASH_WKEN = 1;    
#endif

#if TEST_LCD_LVD_WAKEUP// LCD LVD WAKE UP interrupt 0
    LCD_LVD_PHASE = 1;  // 1:���ߵ�ƽ
    LCD_LVD_WKEN = 1;            
#endif

#if TEST_LCD_ESD_WAKEUP// LCD ESD WAKE UP interrupt 0    
    LCD_ESD_PHASE = 1;  // 1:���ߵ�ƽ
    LCD_ESD_WKEN = 1;       
#endif

#if TEST_LCD_RUN_WAKEUP//LCD RUN WAKE UP interrupt 0   
    pAsmRegs->usAsmScanCfg1|=(1<<BIT_LCD_RUN_INTPHASE);     //[15] LCD RUN�жϵ�ƽѡ��.1:���ߵ�ƽ                       
    LCD_TIM_WKEN = 1;  
    pAsmRegs->usAsmIntEn1|=(1<<BIT_LCD_RUN_EN1);            // LCD RUN �ж�ʹ��  interrupt 4    
#endif

#if TEST_LCD_DSTB_WAKEUP//LCD_DSTB WAKE UP interrupt 0 
    pAsmRegs->usAsmScanCfg1|=(1<<BIT_LCD_DSTB_INTPHASE);    //[15] LCD DSTB�жϵ�ƽѡ��.1:���ߵ�ƽ  
    LCD_TIM_WKEN = 1;
    pAsmRegs->usAsmIntEn1|=(1<<BIT_LCD_DSTB_EN1);           // LCD DEEP STANDBY �ж�ʹ��   interrupt 4                  
#endif

    //REG_2 3  
    pAsmRegs->usAsmIntClr0  = 0xFFFF;
    pAsmRegs->usAsmIntClr1  = 0xFFFF; 
     
    ASM_EI  = 1;  /* asm int */
    EX0 = 1;  /* int0 wake up */ 
    
    EA = 1;
}

void DrvAsmWakeEnable0(UINT16 usWakeMode)
{
    //REG_06
    pAsmRegs->usAsmIntWakeEn0 |=(1<<usWakeMode);       
}

void DrvAsmWakeEnable1(UINT16 usWakeMode)
{
    //REG_07
    pAsmRegs->usAsmIntWakeEn1 |=(1<<usWakeMode);       
}

void DrvAsmWakeDisable0(UINT16 usWakeMode)
{
    //REG_06
    pAsmRegs->usAsmIntWakeEn0&=~(1<<usWakeMode);       
}

void DrvAsmWakeDisable1(UINT16 usWakeMode)
{
    //REG_07
    pAsmRegs->usAsmIntWakeEn1&=~(1<<usWakeMode);       
}

void DrvAsmInterEnableAll(void)
{
    //REG_04
    pAsmRegs->usAsmIntEn0 = 0xFFFF; //�����ж�ʹ��
    //REG_05
    pAsmRegs->usAsmIntEn1 = 0xFFFF; //�����ж�ʹ��

    //DBG_FLOW("\npAsmRegs->usAsmIntEn0: %04x",pAsmRegs->usAsmIntEn0);          
}

void DrvAsmInterDisableAll(void)
{
    //REG_04
    pAsmRegs->usAsmIntEn0 = 0x0; //�ر��ж�ʹ��
    //REG_05
    pAsmRegs->usAsmIntEn1 = 0x0; //�ر��ж�ʹ��

    //DBG_FLOW("\npAsmRegs->usAsmIntEn0: %04x",pAsmRegs->usAsmIntEn0);          
}

void DrvAsmInterEnable0(UINT16 usInterMode)
{
    //REG_04
    pAsmRegs->usAsmIntEn0|=(TRUE<<usInterMode); //�����ж�ʹ��
    //DBG_FLOW("\npAsmRegs->usAsmIntEn0: %04x",pAsmRegs->usAsmIntEn0);          
}

void DrvAsmInterDisable0(UINT16 usInterMode)
{
    //REG_04
    pAsmRegs->usAsmIntEn0&=~(TRUE<<usInterMode); //�ر��ж�ʹ��
}

void DrvAsmInterEnable1(UINT16 usInterMode)
{
    //REG_05
    pAsmRegs->usAsmIntEn1|=(TRUE<<usInterMode); //�����ж�ʹ��
}

void DrvAsmInterDisable1(UINT16 usInterMode)
{
    //REG_05
    pAsmRegs->usAsmIntEn1&=~(TRUE<<usInterMode); //�ر��ж�ʹ��
}

void DrvAsmInterClear0(UINT16 usClearMode)
{
    pAsmRegs->usAsmIntClr0|=(TRUE<<usClearMode); //����ж� 
}

UINT16 DrvAsmGetSta(void)
{
    //REG8
    return pAsmRegs->usAsmIntSta;
}

UINT16 DrvAsmGetSta1(void)
{
    //REG10
    return pAsmRegs->usAsmScanSta1;
}

void DrvAsmSetIDReset(void)
{
    //REG13
    pAsmRegs->usAsmScanCtrl|= (1<<1);
}

void DrvAsmSetPhase(void)
{
    //REG15
    pAsmRegs->usAsmScanCfg1|=((1<<BIT_LCD_RUN_INTPHASE)     // [15] LCD RUN�жϵ�ƽѡ��         0:�͵�ƽ��1:���ߵ�ƽ                       
                             +(1<<BIT_LCD_DSTB_INTPHASE));   // [14] LCD Deep Standby�жϵ�ƽѡ��0:�͵�ƽ��1:���ߵ�ƽ                           
}

void DrvAsmSeStbtMask(UINT16 usMask)
{
    //REG21
    pAsmRegs->usAsmStbMaseL = (usMask<<BIT_STB_MASK_L);       // [15:0]STB_TICK�ж��������õ�λ
}

void DebugReadAsmReg(void)
{
    DBG_FLOW("\npAsmReg0: %04x",pAsmRegs->usAsmIntFlag0);          // 00  RO
    DBG_FLOW("\npAsmReg1: %04x",pAsmRegs->usAsmIntFlag1);          // 01  RO
    DBG_FLOW("\npAsmReg2: %04x",pAsmRegs->usAsmIntClr0);           // 02  WO
    DBG_FLOW("\npAsmReg3: %04x",pAsmRegs->usAsmIntClr1);           // 03  WO
    DBG_FLOW("\npAsmReg4: %04x",pAsmRegs->usAsmIntEn0);            // 04
    DBG_FLOW("\npAsmReg5: %04x",pAsmRegs->usAsmIntEn1);            // 05
    DBG_FLOW("\npAsmReg6: %04x",pAsmRegs->usAsmIntWakeEn0);        // 06
    DBG_FLOW("\npAsmReg7: %04x",pAsmRegs->usAsmIntWakeEn1);        // 07
    DBG_FLOW("\npAsmReg8: %04x",pAsmRegs->usAsmIntSta);            // 08  RO
    DBG_FLOW("\npAsmReg9: %04x",pAsmRegs->usAsmScanSta0);          // 09  RO
    DBG_FLOW("\npAsmReg10: %04x",pAsmRegs->usAsmScanSta1);         // 10  RO
    DBG_FLOW("\npAsmReg11: %04x",pAsmRegs->usAsmScanSta2);         // 11  RO
    DBG_FLOW("\npAsmReg12: %04x",pAsmRegs->usAsmScanSta3);         // 12  RO    
    DBG_FLOW("\npAsmReg13: %04x",pAsmRegs->usAsmScanCtrl);         // 13  WO
    DBG_FLOW("\npAsmReg14: %04x",pAsmRegs->usAsmScanCfg0);         // 14
    DBG_FLOW("\npAsmReg15: %04x",pAsmRegs->usAsmScanCfg1);         // 15
    DBG_FLOW("\npAsmReg16: %04x",pAsmRegs->usAsmTpFrameCfg0);      // 16
    DBG_FLOW("\npAsmReg17: %04x",pAsmRegs->usAsmTpFrameCfg1);      // 17
    DBG_FLOW("\npAsmReg18: %04x",pAsmRegs->usAsmTpFrameCfg2);      // 18
    DBG_FLOW("\npAsmReg19: %04x",pAsmRegs->usAsmTpFrameCfg3);      // 19
    DBG_FLOW("\npAsmReg20: %04x",pAsmRegs->usAsmScanDly);          // 20
    DBG_FLOW("\npAsmReg21: %04x",pAsmRegs->usAsmStbMaseL);         // 21
    DBG_FLOW("\npAsmReg22: %04x",pAsmRegs->usAsmStbMaseH);         // 22  
    DBG_FLOW("\npAsmReg23: %04x",pAsmRegs->usAsmAramBaseL);        // 23
    DBG_FLOW("\npAsmReg24: %04x",pAsmRegs->usAsmAramBaseR);        // 24
    DBG_FLOW("\npAsmReg25: %04x",pAsmRegs->usAsmAramBaseKey);      // 25    
    DBG_FLOW("\npAsmReg26: %04x",pAsmRegs->usAsmAramCBL);          // 26
    DBG_FLOW("\npAsmReg27: %04x",pAsmRegs->usAsmAramCBR);          // 27
    DBG_FLOW("\npAsmReg28: %04x",pAsmRegs->usAsmAramCBKey);        // 28
}

void AppGetAsmState(void)
{
    DBG_FLOW("\n8usAsmIntSta: %04x",pAsmRegs->usAsmIntSta);            // 08  RO
    DBG_FLOW("\n9usAsmScanSta0: %04x busy_id:0x%x",pAsmRegs->usAsmScanSta0,pAsmRegs->usAsmScanSta0&0x3F);          // 09  RO
    DBG_FLOW("\n10usAsmScanSta1: %04x lcd_busy:0x%x",pAsmRegs->usAsmScanSta1,(pAsmRegs->usAsmScanSta1>>10)&0x1);         // 10  RO
    DBG_FLOW("\n11usAsmScanSta2: stb_id:0x%04x stb_tick_id:0x%x",pAsmRegs->usAsmScanSta2>>6,pAsmRegs->usAsmScanSta2&0x3F);     // 11  RO
    DBG_FLOW("\n12usAsmScanSta3: max:0x%04x min:0x%04x",pAsmRegs->usAsmScanSta3>>6,pAsmRegs->usAsmScanSta3&0x3F);         // 12  RO  
}

/*******************************************************************************
*   Name: DrvAsmCloseTable
*  Brief: 
*  Input:
* Output:  
* Return:  
*******************************************************************************/
void DrvAsmCloseTable(void)
{
    //REG_19   
    pAsmRegs->usAsmScanDly&=~(0xF<<10);
}

/*******************************************************************************
*   Name: DrvLoadTabSingle
*  Brief: ���±��� ,һ������ ɨ��1��TP֡
*  Input: ucTabId:��Ҫ���µı�ID, ucBusyID ��0��TP֡��ʼ�Ӻ� 
* Output:  
* Return:  
*******************************************************************************/
void DrvLoadTabSingle(UINT8 ucTabId,UINT8 ucBusyID)
{
    //REG_20   
    pAsmRegs->usAsmScanDly|=   ((1<<BIT_TAB_EN3)              // [13] Tab3��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN2)              // [12] Tab2��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN1)              // [11] Tab1��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN0));            // [10] Tab0��ʹ��: 1:ʹ�� 
//    DBG_FLOW("\n17pAsmRegs->usAsmScanDly: %04x",pAsmRegs->usAsmScanDly);         

    //REG_14    
    pAsmRegs->usAsmScanCfg0&=~(0x7<<BIT_TP_FRAME_NUM);      
    pAsmRegs->usAsmScanCfg0|=(0<<BIT_TP_FRAME_NUM);         // [1:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡ 
    
    //REG_16 
    pAsmRegs->usAsmTpFrameCfg0|= ((ucTabId<<BIT_TAB_ID0)      // [1] ��0��TP֡�õ�Table���     
                                 +(ucBusyID<<BIT_BUSY_ID0));  // [0] ��0��TP֡��ʼ�Ӻ� 
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
    pAsmRegs->usAsmScanDly|=   ((1<<BIT_TAB_EN3)               // [13] Tab3��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN2)               // [12] Tab2��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN1)               // [11] Tab1��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN0));             // [10] Tab0��ʹ��: 1:ʹ�� 

    //REG_14    
    pAsmRegs->usAsmScanCfg0&=~(0x7<<BIT_TP_FRAME_NUM);      
    pAsmRegs->usAsmScanCfg0|=(ucScanMul<<BIT_TP_FRAME_NUM);   // [1:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡                                
                               
    //REG_16 
    pAsmRegs->usAsmTpFrameCfg0 = ((ucF1TabId<<BIT_TAB_ID1)     // [3] ��1��TP֡�õ�Table���  
                                  +(ucBusyId1<<BIT_BUSY_ID1)   // [2] ��1��TP֡��ʼ�Ӻ�        
                                  +(ucF0TabId<<BIT_TAB_ID0)    // [1] ��0��TP֡�õ�Table���     
                                  +(ucBusyId0<<BIT_BUSY_ID0)); // [0] ��0��TP֡��ʼ�Ӻ� 

    //REG_17 
    pAsmRegs->usAsmTpFrameCfg1 = ((ucF3TabId<<BIT_TAB_ID3)     // [3] ��3��TP֡�õ�Table���  
                                  +(ucBusyId3<<BIT_BUSY_ID3)   // [2] ��3��TP֡��ʼ�Ӻ�        
                                  +(ucF2TabId<<BIT_TAB_ID2)    // [1] ��2��TP֡�õ�Table���     
                                  +(ucBusyId2<<BIT_BUSY_ID2)); // [0] ��2��TP֡��ʼ�Ӻ� 
                         
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
    pAsmRegs->usAsmScanCtrl|=(1<<BIT_SCAN_START);   // [0] WO: ����ɨ��  
    //DBG_FLOW("\nStart"); 
}

/*******************************************************************************
*   Name: DrvAsmSetMonitorMode
*  Brief: Ӳ���������ģʽ: 1: �ǣ�      0:��   
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmSetMonitorMode(UINT8 ucModeEn)
{
    //REG_14   
    pAsmRegs->usAsmScanCfg0&=~(1<<BIT_MONITOR_MODE);
    pAsmRegs->usAsmScanCfg0|=(ucModeEn<<BIT_MONITOR_MODE);     // [15]Ӳ���������ģʽ: 1: �ǣ�      0:��   
    // Ӳ���������ģʽ�£���ARAM READY�жϣ�����frame_end ֡�����ж����ж�ɨ�����
    pAsmRegs->usAsmScanCfg1&=~(1<<BIT_TP_END_SEL);           // [5] ֡����λ��ѡ��. 0:tp_frame_end. 1:aram rdy(��ϵ������ɨ����֡����λ��)
}

/*******************************************************************************
*   Name: DrvAsmSetCBAdjustMode
*  Brief: CBУ��ģʽ:       1:У��ģʽ   0:����ģʽ   
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmSetCBAdjustMode(UINT8 ucModeEn)
{
    //REG_14    
    pAsmRegs->usAsmScanCfg0&=~(1<<BIT_CB_ADJUST_MODE);
    pAsmRegs->usAsmScanCfg0|=(ucModeEn<<BIT_CB_ADJUST_MODE);   // [14]CBУ��ģʽ:       1:У��ģʽ   0:����ģʽ   
}


/*******************************************************************************
*   Name: DrvGetAramCb
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvGetAramCb(void)
{
    UINT16 XRAM i;
    UINT16 XRAM ausCbBuff;
    UINT16 XRAM ausCbBase;

    ARAM_SEL = 1;
   
    DBG_FLOW("\nRead CB from Aram");

    ausCbBase = pAsmRegs->usAsmAramCBL;
    DBG_FLOW("\nAFE_L CB  BASE ADDR:%04x",ausCbBase);  
    for(i = 0; i < CH_ORDER_MAX>>1; i++)
    {   
        if((i%18) == 0)
            DBG_FLOW("\n");
        
        ausCbBuff = ARAM_ADDR16((ausCbBase<<1)+(i<<1));        
        DBG_FLOW("%04x  ",ausCbBuff); 
    }
    
    DBG_FLOW("\n\n");

    ausCbBase = pAsmRegs->usAsmAramCBR;
    DBG_FLOW("\nAFE_R CB  BASE ADDR:%04x",ausCbBase);  
    for(i = 0; i < CH_ORDER_MAX>>1; i++)
    {   
        if((i%18) == 0)
            DBG_FLOW("\n");
        
        ausCbBuff = ARAM_ADDR16((ausCbBase<<1)+(i<<1));      
        DBG_FLOW("%04x  ",ausCbBuff); 
    }  

    DBG_FLOW("\n\n");

    /*����AFE_KEY��CBУ��ֵ*/
    ausCbBase = pAsmRegs->usAsmAramCBKey;
    DBG_FLOW("\nAFE_KEY CB  BASE ADDR:%04x\n",ausCbBase);    
    for(i = 0; i < 8; i++)
    {
        ausCbBuff = ARAM_ADDR16((ausCbBase<<1)+(i<<1));
        DBG_FLOW("%04x  ",ausCbBuff);
    }     
    
    ARAM_SEL = 0;
}

/*******************************************************************************
*   Name: DrvGetAramRawData
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvGetAramRawData(void)
{
    UINT16 XRAM i;
    UINT16 XRAM ausDataBuff[CH_ORDER_MAX*2+14];
    UINT16 XRAM ausDataBase;

    ARAM_SEL = 1;

    /*����AFE_L��RawData*/
    ausDataBase = pAsmRegs->usAsmAramBaseL;
    for(i = 0; i < CH_ORDER_MAX; i++)
    {
        ausDataBuff[i] = ARAM_ADDR16((ausDataBase<<1)+(i<<1));
    }

    /*����AFE_R��RawData*/
    ausDataBase = pAsmRegs->usAsmAramBaseR;   
    for(i = 0; i < CH_ORDER_MAX; i++)
    {
        ausDataBuff[CH_ORDER_MAX + i] = ARAM_ADDR16((ausDataBase<<1)+(i<<1));
    }

    /*����AFE_KEY��RawData*/
    ausDataBase = pAsmRegs->usAsmAramBaseKey;
   
    for(i = 0; i < 14; i++)
    {
        ausDataBuff[CH_ORDER_MAX*2 + i] = ARAM_ADDR16((ausDataBase<<1)+(i<<1));
    }
	
    DBG_FLOW("\nAFE_L RawData:");
    for(i = 0; i < CH_ORDER_MAX; i++)
	{
		if(i%18 == 0)
		{
			DBG_FLOW("\n");
		}
		DBG_FLOW("%04x  ",ausDataBuff[i]);
	}

    DBG_FLOW("\nAFE_R RawData:");
    for(i = 0; i < CH_ORDER_MAX; i++)
	{
		if(i%18 == 0)
		{
			DBG_FLOW("\n");
		}
		DBG_FLOW("%04x  ",ausDataBuff[CH_ORDER_MAX + i]);
	}
	
    DBG_FLOW("\nAFE_Key RawData:\n"); 
    for(i = 0; i < 8; i++)
    {
		DBG_FLOW("%04x ",ausDataBuff[CH_ORDER_MAX*2 + i]);    
    }

    DBG_FLOW("\nAFE Info:");
    DBG_FLOW("%04x  ",ausDataBuff[CH_ORDER_MAX*2 + 8]);
    DBG_FLOW("%04x  ",ausDataBuff[CH_ORDER_MAX*2 + 11]);

    DBG_FLOW("\nAFE Tp Diff Max:");
    DBG_FLOW("%04x  ",ausDataBuff[CH_ORDER_MAX*2 + 9]);
    DBG_FLOW("%04x  ",ausDataBuff[CH_ORDER_MAX*2 + 12]);

    DBG_FLOW("\nAFE Key Diff Max:");
    DBG_FLOW("%04x  ",ausDataBuff[CH_ORDER_MAX*2 + 10]);
    DBG_FLOW("%04x  ",ausDataBuff[CH_ORDER_MAX*2 + 13]);    
    ARAM_SEL = 0; 
}



/*******************************************************************************
*   Name: DrvGetAdcData
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvGetAdcData(UINT16 ucLen)
{
    UINT16 XRAM i;
    UINT16 XRAM ausDataBuff;
    UINT16 XRAM ausDataBase;

    ARAM_SEL = 1;

    /*����AFE_L��RawData*/
    ausDataBase = pAsmRegs->usAsmAramBaseL;
    DBG_FLOW("\nAFE_L Adc Data:");
    for(i = 0; i < ucLen; i++)
    {
        ausDataBuff = ARAM_ADDR16((ausDataBase<<1)+(i<<1));
        if((i%24) == 0)
        { 
            DBG_FLOW("\n");
        }
        DBG_FLOW("%04x ",ausDataBuff);
        }
#if 0
    /*����AFE_R��RawData*/
    ausDataBase = pAsmRegs->usAsmAramBaseR;
    DBG_FLOW("\nAFE_R RawData:");    
    for(i = 0; i < ucLen; i++)
    {
        ausDataBuff = ARAM_ADDR16((ausDataBase<<1)+(i<<1));
        if((i%18) == 0)
        {
            DBG_FLOW("\n");
        }
        DBG_FLOW("%04x  ",ausDataBuff);
    }
#endif

    
    ARAM_SEL = 0; 
}

/*******************************************************************************
*   Name: DrvAsmSetSTBTickMask
*  Brief: STB_TICK�ж��������� 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmSetSTBTickMask(UINT16 usMaskL,UINT16 usMaskH)
{
    //REG_21  
    pAsmRegs->usAsmStbMaseL = (usMaskL<<BIT_STB_MASK_L);       // [15:0]STB_TICK�ж��������õ�λ

    //REG_22  
    pAsmRegs->usAsmStbMaseH = (usMaskH<<BIT_STB_MASK_H);       // [15:0]STB_TICK�ж��������ø�λ
}

/*******************************************************************************
*   Name: DrvAsmMonitoModeInit
*  Brief: Ӳ���������ģʽ 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmMonitoModeInit(void)
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

#if TEST_FREERUN_MONITOR
	usReg1 = rAFE_SCAN_CFG0;
	usReg1 =((1<<BIT_AFE_SCAN_TIMES)			   //ɨ�������ʵ��ֵΪ����ֵ��1;  
			+(4<<BIT_AFE_SCAN_MODE));			  //��ʽ5
#else
	usReg1 = rAFE_SCAN_CFG0;
	usReg1 =((1<<BIT_AFE_SCAN_TIMES)			   //ɨ�������ʵ��ֵΪ����ֵ��1;  
			+(0<<BIT_AFE_SCAN_MODE));			  //��ʽ1


	//REG_14	
	pAsmRegs->usAsmScanCfg0&=~(0x7<<BIT_TP_FRAME_NUM);		
	pAsmRegs->usAsmScanCfg0|=(0<<BIT_TP_FRAME_NUM);   // [1:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡								 
							   
	//REG_16 
	pAsmRegs->usAsmTpFrameCfg0 = ((2<<BIT_TAB_ID1)	   // [3] ��1��TP֡�õ�Table���  
								  +(0<<BIT_BUSY_ID1)   // [2] ��1��TP֡��ʼ�Ӻ� 	   
								  +(2<<BIT_TAB_ID0)    // [1] ��0��TP֡�õ�Table���	 
								  +(1<<BIT_BUSY_ID0)); // [0] ��0��TP֡��ʼ�Ӻ� 

	//REG_17 
	pAsmRegs->usAsmTpFrameCfg1 = ((2<<BIT_TAB_ID3)	   // [3] ��3��TP֡�õ�Table���  
								  +(0<<BIT_BUSY_ID3)   // [2] ��3��TP֡��ʼ�Ӻ� 	   
								  +(2<<BIT_TAB_ID2)    // [1] ��2��TP֡�õ�Table���	 
								  +(0<<BIT_BUSY_ID2)); // [0] ��2��TP֡��ʼ�Ӻ� 

			
#endif

	usReg3 = rAFE_DUMMY_SCAN_CFG;
	usReg3 =((1<<10)			   //[11:8]Mux�л�֮��Dummy����    
			+(0<<5) 			  //[7:4]��ǰDummy����
			+(2<<0));			  //[3:0]Tp֡ǰDummy����			 
		   
	usReg2 = rAFE_SCAN_CFG1; 
	usReg2 =((0<<9) 			  //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������ 	 
			+(0<<8) 			  //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
			+(4<<0));			  //[0] ��ʽ6��ɨ����� 			
		   
	usReg4 = rAFE_BASE_TRACK_CFG;
	usReg4 = ((32<<BIT_BASE_TRACK_STEP) 			//[9:2]Monitorģʽ��Base���٣��������ٲ���												   
			  +(1<<BIT_BASE_TRACK_MODE) 			//[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
			  +(1<<BIT_BASE_TRACK_ENABLE)); 		//[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ�� 
			  
	usReg5 = rACC_OFFSET;
	usReg6 = rTP_MONITOR_THRESHOLD;
	usReg7 = rKEY_MONITOR_THRESHOLD;
	usReg8 = rAFE_ANA_K1_CFG0;
	usReg9 = rAFE_ANA_K2_CFG1;

	DrvAsmCloseTable(); // ������Tab����,ֱ���üĴ�������
	
	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG1, usReg0, AFE_REG); //5
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG1, usReg0, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SCAN_CFG0, usReg1, AFE_REG); //6
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SCAN_CFG0, usReg1, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SCAN_CFG1, usReg2, AFE_REG); //7
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SCAN_CFG1, usReg2, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_DUMMY_SCAN_CFG, usReg3, AFE_REG); //8
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_DUMMY_SCAN_CFG, usReg3, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_BASE_TRACK_CFG, usReg4, AFE_REG); //9 Base���ٷ�ʽ:   1:ԭֵ����
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_BASE_TRACK_CFG, usReg4, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_ACC_OFFSET, usReg5, AFE_REG); //10
	Drv_XsiWriteReg(pXSI1Regs, Addr_ACC_OFFSET, usReg5, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_TP_MONITOR_THRESHOLD, usReg6, AFE_REG); //11
	Drv_XsiWriteReg(pXSI1Regs, Addr_TP_MONITOR_THRESHOLD, usReg6, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_KEY_MONITOR_THRESHOLD, usReg7, AFE_REG); //12
	Drv_XsiWriteReg(pXSI1Regs, Addr_KEY_MONITOR_THRESHOLD, usReg7, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_K1_CFG0, usReg8, AFE_REG); //13
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_K1_CFG0, usReg8, AFE_REG);

	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_K2_CFG1, usReg9, AFE_REG); //14
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_K2_CFG1, usReg9, AFE_REG);

		  
	// Ӳ���������ģʽ�£���ARAM READY�жϣ�����frame_end ֡�����ж����ж�ɨ�����
	pAsmRegs->usAsmIntEn0|=(TRUE<<BIT_LCD_FRAME_END_EN0); 
	DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
	// �ر�ARAM ,Tch Det�ж�
	pAsmRegs->usAsmIntEn0&=~(TRUE<<BIT_LCD_ARAM_RDY_EN0);	 
	pAsmRegs->usAsmIntEn0&=~(TRUE<<BIT_LCD_TCH_DET_EN0);		  
   
	//����ԭֵ���٣�ɨ���ȡbase,ʹ��base����
	DrvAsmSetMonitorMode(TRUE); 			  //1:�������ģʽ
	
	pAsmRegs->usAsmIntEn0|=(TRUE<<BIT_LCD_ARAM_RDY_EN0);   // ���￪AramReady,�����Ƿ��AramReady�ж�  
	DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);

	DrvAfeSetBaseTrack(1,0);				  //ʹ��base���٣�1:ԭֵ����   Step: 0
	DBG_FLOW("\npAsmRegs->usAsmIntEn0:0x%x",pAsmRegs->usAsmIntEn0);

	g_ucFrameEndFlag = 0;
	DrvAsmScanStart();						  // ������һ��ɨ�裬��֤BaseRAM�����ݣ������ٿ���DET�жϡ�
	DBG_FLOW("\nAsmMonitoMode ScanStart");
	
	while(!g_ucFrameEndFlag);
	
//	  DrvGetRptRamRawBase();					// Monitorģʽ���ϱ����ݵ�ARAM,ͨ��RptRam�ϱ���

	DrvAfeInitBase();

	DrvAfeSetHCBTarget(8000,8000);				  //����Ӳ��CBУ����Ŀ��ֵ

	//ʹ�ܴ��������ж�
	pAsmRegs->usAsmIntWakeEn0|=(TRUE<<BIT_LCD_TCH_DET_WAKE_EN0);	 
		
	//ʹ�ܴ�������ж�
//	  pAsmRegs->usAsmIntEn0|=(TRUE<<BIT_LCD_TCH_DET_EN0);  
}


void DrvAsmReq120hz_Small_LcdBusy(void)
{
    //REG_15    
    pAsmRegs->usAsmScanCfg1&=~(1<<BIT_VB_MODE_REQ);    // [8] ����: 0:С��     
}                              

void DrvAsmReq60hz_Big_LcdBusy(void)
{
    //REG_15    
    pAsmRegs->usAsmScanCfg1|=(1<<BIT_VB_MODE_REQ);     // [8] ����: 1:��� 
}

void DrvAsmSkipFramNoLcdBusy(void)
{
    //REG_15    
    pAsmRegs->usAsmScanCfg1&=~(1<<BIT_LPF_MODE_TP_TURBO_REQ);    // [9]:Tp����LCD��skip frameʱ���Ƿ񿪿ӡ�0:������ 
}                              

void DrvAsmSkipFramHaveLcdBusy(void)
{
    //REG_15    
    pAsmRegs->usAsmScanCfg1|=(1<<BIT_LPF_MODE_TP_TURBO_REQ);     // [9]:Tp����LCD��skip frameʱ���Ƿ񿪿ӡ� 1:���ӡ�
}

/*******************************************************************************
*   Name: DrvLoadTabCB
*  Brief: ���±��� ,����cbУ��ģʽ,����busyid
*  Input: 
* Output:  
* Return:  
*******************************************************************************/
void DrvLoadTabCB(UINT8 ucTabId,ENUM_AFE_MODE ucCbMode)
{
      
    //REG_19   
    pAsmRegs->usAsmScanDly|=   ((1<<BIT_TAB_EN3)               // [13] Tab3��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN2)               // [12] Tab2��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN1)               // [11] Tab1��ʹ��: 1:ʹ�� 
                               +(1<<BIT_TAB_EN0));             // [10] Tab0��ʹ��: 1:ʹ�� 

    switch(ucCbMode)
    {
        case AFE_120HZ_MODE:
        {
            pAsmRegs->usAsmScanCfg0&=~(0x7<<BIT_TP_FRAME_NUM);
            pAsmRegs->usAsmScanCfg0|=(CB_TP_FRAME_NUM<<BIT_TP_FRAME_NUM);          // [1:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡     
            
            pAsmRegs->usAsmTpFrameCfg0|= ((ucTabId<<BIT_TAB_ID0)                   // [1] ��0��TP֡�õ�Table���
                                       + (CB_BUSY_ID0<<BIT_BUSY_ID0)               // [0] ��0��TP֡��ʼ�Ӻ� 
                                       + (ucTabId<<BIT_TAB_ID1)                    // ��1��TP֡�õ�Table���
                                       + (CB_BUSY_ID1<<BIT_BUSY_ID1));             // ��1��TP֡��ʼ�Ӻ�

            pAsmRegs->usAsmTpFrameCfg1|= ((ucTabId<<BIT_TAB_ID2)                   // [1] ��2��TP֡�õ�Table���
                                       + (CB_BUSY_ID2<<BIT_BUSY_ID2)               // [0] ��2��TP֡��ʼ�Ӻ� 
                                       + (ucTabId<<BIT_TAB_ID3)                    // ��3��TP֡�õ�Table���
                                       + (CB_BUSY_ID3<<BIT_BUSY_ID3));             // ��3��TP֡��ʼ�Ӻ�                               

            pAsmRegs->usAsmTpFrameCfg2|= ((CB_BUSY_ID4<<BIT_BUSY_ID4)              // [0] ��4��TP֡��ʼ�Ӻ�            
                                       + (CB_BUSY_ID5<<BIT_BUSY_ID5));             // ��5��TP֡��ʼ�Ӻ�                                                         

            pAsmRegs->usAsmTpFrameCfg3|= ((CB_BUSY_ID6<<BIT_BUSY_ID6)              // [0] ��4��TP֡��ʼ�Ӻ�            
                                       + (CB_BUSY_ID7<<BIT_BUSY_ID7));             // ��5��TP֡��ʼ�Ӻ�
            break;
        }

        case AFE_60HZ_MODE:
        {
            pAsmRegs->usAsmScanCfg0&=~(0x7<<BIT_TP_FRAME_NUM);
            pAsmRegs->usAsmScanCfg0|=(0<<BIT_TP_FRAME_NUM);                        // [1:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡     
            
            pAsmRegs->usAsmTpFrameCfg0|= ((ucTabId<<BIT_TAB_ID0)                   // [1] ��0��TP֡�õ�Table���
                                       + (1<<BIT_BUSY_ID0)                         // [0] ��0��TP֡��ʼ�Ӻ� 
                                       + (ucTabId<<BIT_TAB_ID1)                    // ��1��TP֡�õ�Table���
                                       + (1<<BIT_BUSY_ID1));                       // ��1��TP֡��ʼ�Ӻ�

            pAsmRegs->usAsmTpFrameCfg1|= ((ucTabId<<BIT_TAB_ID2)                   // [1] ��2��TP֡�õ�Table���
                                       + (1<<BIT_BUSY_ID2)                         // [0] ��2��TP֡��ʼ�Ӻ� 
                                       + (ucTabId<<BIT_TAB_ID3)                    // ��3��TP֡�õ�Table���
                                       + (1<<BIT_BUSY_ID3));                       // ��3��TP֡��ʼ�Ӻ�                               

            pAsmRegs->usAsmTpFrameCfg2|= ((1<<BIT_BUSY_ID4)                        // [0] ��4��TP֡��ʼ�Ӻ�            
                                       + (1<<BIT_BUSY_ID5));                       // ��5��TP֡��ʼ�Ӻ�                                                         

            pAsmRegs->usAsmTpFrameCfg3|= ((1<<BIT_BUSY_ID6)                        // [0] ��4��TP֡��ʼ�Ӻ�            
                                       + (1<<BIT_BUSY_ID7));                       // ��5��TP֡��ʼ�Ӻ�
            break;
        }

        case AFE_FREERUN_MODE:
        {
            pAsmRegs->usAsmScanCfg0&=~(0x7<<BIT_TP_FRAME_NUM);
            pAsmRegs->usAsmScanCfg0|=(7<<BIT_TP_FRAME_NUM);                        // [1:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡     

            pAsmRegs->usAsmTpFrameCfg0|= (ucTabId<<BIT_TAB_ID0);                  // [1] ��0��TP֡�õ�Table���
            break;
        }
        
        default:
            break;
    }
}

/*******************************************************************************
*   Name: DrvAsmClrInt
*  Brief:    
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmClrInt(void)
{
    pAsmRegs->usAsmIntClr0 = 0xFFFF;
    pAsmRegs->usAsmIntClr1 = 0xFFFF;
}

/*******************************************************************************
*   Name: DrvAsmSetHwMonitorMode
*  Brief: Ӳ��Monitorģʽ: 1: �ǣ�      0:��   
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmSetRtcMonitorMode(UINT8 ucModeEn)
{
    //REG_14   
    pAsmRegs->usAsmScanCfg0&=~(1<<BIT_MONITOR_MODE);
    pAsmRegs->usAsmScanCfg0|=(ucModeEn<<BIT_MONITOR_MODE);     // [15]Ӳ���������ģʽ: 1: �ǣ�      0:�� 


    pAsmRegs->usAsmScanCfg1&=~(1<<BIT_HW_MONITOR_EN);
    pAsmRegs->usAsmScanCfg1|=(ucModeEn<<BIT_HW_MONITOR_EN);  // [3]Ӳ��monitorʹ��. 1:��. 0:��

    if(ucModeEn)
    {
        // Ӳ���������ģʽ�£���ARAM READY�жϣ�����frame_end ֡�����ж����ж�ɨ�����
        pAsmRegs->usAsmScanCfg1&=~(1<<BIT_TP_END_SEL);           // [5] ֡����λ��ѡ��. 0:tp_frame_end. 1:aram rdy(��ϵ������ɨ����֡����λ��)
    }
    else
    {
        // Ӳ���������ģʽ�£���ARAM READY�жϣ�����frame_end ֡�����ж����ж�ɨ�����
        pAsmRegs->usAsmScanCfg1 |=(1<<BIT_TP_END_SEL);           // [5] ֡����λ��ѡ��. 0:tp_frame_end. 1:aram rdy(��ϵ������ɨ����֡����λ��)        
    }
}
/*******************************************************************************
*   Name: DrvAsmSetRtcMonitorTimer
*  Brief: Ӳ��Monitor timer����
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmSetRtcMonitorTimer(UINT16 ucTimer)
{
    //REG_39   
    pAsmRegs->usAsmHwMonTimer = ucTimer&0x0FFF;
    DBG_FLOW("\nASM REG_39:%04x",pAsmRegs->usAsmHwMonTimer);
}  

/*******************************************************************************
*   Name: DrvAsmSetHwMonPwrEn(UINT8 ucEn)
*  Brief: Ӳ��Monitor �������µ�ʱ������
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmSetHwMonPwrEn(UINT8 ucEn)
{
    //REG_33
    if(ucEn == 0)
    {
        pAsmRegs->usAsmPwrCtrl&= (~ BITn(2));
    }
    else
    {
        pAsmRegs->usAsmPwrCtrl |=  BITn(2);

        
    }
    DBG_FLOW("\nASM REG_33:%04x",pAsmRegs->usAsmPwrCtrl);
} 

/*******************************************************************************
*   Name: DrvAfeClkGateEn(UINT8 ucEn)
*  Brief: Asm�Ƿ��Զ�����afe clk�ſ�
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAfeClkGateEn(UINT8 ucEn)
{
    if(ucEn == 0)
    {
        pAsmRegs->usAsmScanCfg0&= (~ BITn(12));
    }
    else
    {
        pAsmRegs->usAsmScanCfg0 |=  BITn(12);        
    }

}


/*******************************************************************************
*   Name: DrvAsmMonitoModeInit
*  Brief: Ӳ���������ģʽ 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmRtcMonitoModeInit(void)
{
	//ASM�Զ��ſ�afe clk
	DrvAfeClkGateEn(1);

    DrvAfeSetTabBaseTrack(1,0,3);                  //ʹ��base���٣�1:ԭֵ����   Step: 0	
	
    /* ����Tab��*/
    //DrvLoadTabMultiple(1,0,0,0,0,3);
    DrvLoadTabSingle(3,1);

#if 1                                       //ˢһ֡base

    // Ӳ���������ģʽ�£���ARAM READY�жϣ�����frame_end ֡�����ж����ж�ɨ�����
    pAsmRegs->usAsmIntEn0|=(TRUE<<BIT_LCD_FRAME_END_EN0); 
    
    // �ر�ARAM ,Tch Det�ж�
    pAsmRegs->usAsmIntEn0&=~(TRUE<<BIT_LCD_ARAM_RDY_EN0);    
    pAsmRegs->usAsmIntEn0&=~(TRUE<<BIT_LCD_TCH_DET_EN0);          
       
     
    g_ucFrameEndFlag = 0;
    DrvAsmScanStart();                        // ������һ��ɨ�裬��֤BaseRAM�����ݣ������ٿ���DET�жϡ�
    DBG_FLOW("\nAsmMonitoMode ScanStart");
    
    while(!g_ucFrameEndFlag);
    
    DrvGetRptRamRawBase();                    // Monitorģʽ���ϱ����ݵ�ARAM,ͨ��RptRam�ϱ���
#endif

    DelayMs(10);

    DrvAsmSetRtcMonitorTimer(1000);                           //���ò������ٴ�rtc�ж��Ժ���û��touch det������timeout�ж�


#if 0
    pAsmRegs->usAsmIntClr0 |= ((1<<BIT_LCD_TCH_DET_CLR0)
                            + (1<<BIT_LCD_FRAME_END_CLR0));//��Ҫ�������־λ����������tch det�ж�
    pAsmRegs->usAsmIntClr1 |= (1<<BIT_HW_MON_TIMEOUT_CLR1);//���timeout��־
#else
    pAsmRegs->usAsmIntClr0 = 0xFFFF;
    pAsmRegs->usAsmIntClr1 = 0xFFFF;
#endif

	DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
	DrvAsmInterEnable0(BIT_LCD_TCH_DET_EN0);
	DrvAsmInterEnable1(BIT_HW_MON_TIMEOUT_EN1);

	DrvAsmWakeEnable0(BIT_LCD_TCH_DET_WAKE_EN0);
	DrvAsmWakeEnable1(BIT_HW_MON_TIMEOUT_WAKE_EN1);


#if 1   
    DBG_FLOW("\npAsmRegs->usAsmIntEn0:0x%04x",pAsmRegs->usAsmIntEn0);
    DBG_FLOW("\npAsmRegs->usAsmIntEn1:0x%04x",pAsmRegs->usAsmIntEn1);
    DBG_FLOW("\npAsmRegs->usAsmIntWakeEn0:0x%04x",pAsmRegs->usAsmIntWakeEn0);
    DBG_FLOW("\npAsmRegs->usAsmIntWakeEn1:0x%04x",pAsmRegs->usAsmIntWakeEn1);
#endif

#if 0     //��ӡasm����
    for(i = 0;i < 41; i++)
    {
        DBG_FLOW("\nReg[%d]:%04x",i,*(UINT16 *)(ASM_REG_BASE_ADDR + 2*i));
    }
#endif 

}

/*******************************************************************************
*   Name:  DrvAsmSetPwrOn
*  Brief:  �ϵ�ʱ��
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmSetPwrOn(void)
{
    if(((pAsmRegs->usAsmPwrSta)&0x0001) == 0)                   //��ǰΪ�µ�״̬
    {
        pAsmRegs->usAsmPwrCtrl |= (1<<BIT_PWRON_START);         //�����ϵ�ʱ��
        while(((pAsmRegs->usAsmPwrSta)&0x0001) == 0);           //�ȴ��ϵ����
    }
}


/*******************************************************************************
*   Name:  DrvAsmSetPwrOff
*  Brief:  �ϵ�ʱ��
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmSetPwrOff(void)
{
    if(((pAsmRegs->usAsmPwrSta)&0x0001) == 1)                   //��ǰΪ�ϵ�״̬
    {
        pAsmRegs->usAsmPwrCtrl |= (1<<BIT_PWROFF_START);        //�����µ�ʱ��
        while(((pAsmRegs->usAsmPwrSta)&0x0001) == 1);           //�ȴ��µ����
    }
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
    pAsmRegs->usAsmScanCtrl|=(1<<BIT_AFE_WR_ARAM_AVAIL_N_CLR); // [2] WO: 1:���Բ���ARAM
}

/*******************************************************************************
*   Name:  DrvAsmAfeClkGateEn
*  Brief:  1,�Զ��ſأ�����AFEģ��ʱ���Զ�������
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvAsmAfeClkGateEn(void)
{
    //REG_14    
    pAsmRegs->usAsmScanCfg0|=(1<<BIT_AFE_CLKGATE_EN);       // [12]�Զ��ſ�AFEʱ��:  1:�Զ��ſ� 0:���Զ��ſ� 
}

/*******************************************************************************
*   Name: ISR_LcdRun
*  Brief: lcd run
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void ISR_LcdRun_IRQHandler(void) interrupt  4
{
    UINT16 usAsmIntEn0,usAsmIntEn1;
    UINT16 usAsmIntFlag0,usAsmIntFlag1;

    usAsmIntEn0   = pAsmRegs->usAsmIntEn0;
    usAsmIntEn1   = pAsmRegs->usAsmIntEn1;

    usAsmIntFlag0 = pAsmRegs->usAsmIntFlag0;
    usAsmIntFlag1 = pAsmRegs->usAsmIntFlag1;

    /* LCD RUN int */
    if (usAsmIntEn1&LCD_RUN_INT1)
    {
        if (usAsmIntFlag1&LCD_RUN_INT1)
        {
            /* lcd_run�������� 1: ���� */
            if(pAsmRegs->usAsmScanCfg1&BITn(BIT_LCD_RUN_INTPHASE)) 
            {
               pAsmRegs->usAsmScanCfg1&=~(1<<BIT_LCD_RUN_INTPHASE);     // [15] LCD RUN�жϵ�ƽѡ��                               
               DBG_FLOW("\nRun INTPHAS 1");
            }
            else
            {
               pAsmRegs->usAsmScanCfg1|=(1<<BIT_LCD_RUN_INTPHASE);     // [15] LCD RUN�жϵ�ƽѡ��                               
               DBG_FLOW("\nRun INTPHAS 2");
            }
       
            pAsmRegs->usAsmIntClr1 |=LCD_RUN_INT1;
            g_usAsmIntFlag1 |=LCD_RUN_INT1;
            //DBG_FLOW("\nLCD RUN int");
        }
    }

    /* lcd Deep StandBy int */
    if (usAsmIntEn1&LCD_DSTB_INT1)
    {
        if (usAsmIntFlag1&LCD_DSTB_INT1)
        {
            /* lcd_dstb��������1: ���� */
            if(pAsmRegs->usAsmScanCfg1&BITn(BIT_LCD_DSTB_INTPHASE)) 
            {
               pAsmRegs->usAsmScanCfg1&=~(1<<BIT_LCD_DSTB_INTPHASE);     // [15] LCD DSTB�жϵ�ƽѡ��                              
               DBG_FLOW("\nLCD DSTB_INTPHASE 1");
            }
            else
            {
               pAsmRegs->usAsmScanCfg1|=(1<<BIT_LCD_DSTB_INTPHASE);     // [15] LCD DSTB�жϵ�ƽѡ��                           
               DBG_FLOW("\nLCD DSTB_INTPHASE 2");
            }
            
            pAsmRegs->usAsmIntClr1 |=LCD_DSTB_INT1;
            g_usAsmIntFlag1 |=LCD_DSTB_INT1;
            //DBG_FLOW("\nlcd Deep StandBy int");
        }
    }       
//    DBG_FLOW("\nISR_LcdRun");
}

/*******************************************************************************
*   Name: DrvScanCtrl_IRQHandler
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvScanCtrl_IRQHandler(void) interrupt 9
{
    UINT16 usAsmIntEn0,usAsmIntEn1;
    UINT16 usAsmIntFlag0,usAsmIntFlag1;

    usAsmIntEn0   = pAsmRegs->usAsmIntEn0;
    usAsmIntEn1   = pAsmRegs->usAsmIntEn1;

    usAsmIntFlag0 = pAsmRegs->usAsmIntFlag0;
    usAsmIntFlag1 = pAsmRegs->usAsmIntFlag1;

//    DBG_FLOW("\nint9 0x%x 0x%x",pAsmRegs->usAsmIntFlag0,pAsmRegs->usAsmIntFlag1);
    g_usAsmIntSta = DrvAsmGetSta();  

    /* lcd busy fall int */
    if (usAsmIntEn0&LCD_BUSY_FALL_INT0)
    {
        if (usAsmIntFlag0&LCD_BUSY_FALL_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_BUSY_FALL_INT0;   /* д1��0 */
            g_usAsmIntFlag0 |= LCD_BUSY_FALL_INT0;
            //DBG_FLOW("\nlcd busy fall: %04x",pAsmRegs->usAsmScanSta0);
            if(g_ucLcdBusyCnt<64)
            {
                g_ucLcdBusyCnt++;
#if TEST_CUR_LEFT_SCAN               
                if(g_ucLcdBusyCnt == 3)
                {
                     DrvAsmScanStart();
                }
#endif                
                //DBG_FLOW("\nlcd busy %04x",g_ucLcdBusyCnt);
            }
        }
    }

    
    /* lcd busy rise int */
    if (usAsmIntEn0&LCD_BUSY_RISE_INT0)
    {
        if (usAsmIntFlag0&LCD_BUSY_RISE_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_BUSY_RISE_INT0;   /* д1��0 */
            g_usAsmIntFlag0 |= LCD_BUSY_RISE_INT0;
            DBG_INT("\nint busy rise");
            //DBG_FLOW("\nlcd_busy: %04x tp_busy: %04x",(pAsmRegs->usAsmScanSta1>>10)&0x1,(pAsmRegs->usAsmScanSta1>>11)&0x1);
            //DBG_FLOW("\ntail_margin: %04x",pAsmRegs->usAsmTailMargin);
        }
    }

    /* lcd dstb int */
    if (usAsmIntEn0&LCD_DSTB_RISE_INT0)
    {
        if (usAsmIntFlag0&LCD_DSTB_RISE_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_DSTB_RISE_INT0;   /* д1��0 */
            g_usAsmIntFlag0 |= LCD_DSTB_RISE_INT0;
            DBG_INT("\nint lcd dstb int: %04x",pAsmRegs->usAsmIntSta);
        }
    }

    /* lcd sync miss fall int */
    if (usAsmIntEn0&LCD_SYNC_MISS_FALL_INT0)
    {
        if (usAsmIntFlag0&LCD_SYNC_MISS_FALL_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_SYNC_MISS_FALL_INT0;   /* д1��0 */
            g_usAsmIntFlag0 |= LCD_SYNC_MISS_FALL_INT0;
            DBG_FLOW("\nint lcd sync miss fall");

            //AFE_RST = 1;
            //AFE_RST = 0;
            g_ucLcdSyncMissFlag = 1;
            //while(1);
        }
    }

    /* lcd sync miss rise int */
    if (usAsmIntEn0&LCD_SYNC_MISS_RISE_INT0)
    {
        if (usAsmIntFlag0&LCD_SYNC_MISS_RISE_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_SYNC_MISS_RISE_INT0;
            g_usAsmIntFlag0 |= LCD_SYNC_MISS_RISE_INT0;
            AFE_RST = 1;
            AFE_RST = 0;

            g_ucLcdSyncMissFlag = 1;
            DBG_FLOW("\nint lcd sync miss rise");
        }
    }

    /* aram ready int */
    if (usAsmIntEn0&ARAM_READY_INT0)
    {
        if (usAsmIntFlag0&ARAM_READY_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= ARAM_READY_INT0;
            g_usAsmIntFlag0 |= ARAM_READY_INT0;
            g_ucAramReadyFlag = 1;
#if TEST_CUR_LEFT_SCAN                          
//            DBG_FLOW("\nARAM_READY: %04x",pAsmRegs->usAsmScanSta0);//Aram ready�жϺ�Ӳ���õ�֡id.
//            DBG_FLOW("\nA lcd_busy: %04x tp_busy: %04x",(pAsmRegs->usAsmScanSta1>>10)&0x1,(pAsmRegs->usAsmScanSta1>>11)&0x1);
#endif           
            g_ucIntCount++;
            if(g_ucIntCount>=12)
            {
                g_ucIntCount = 0;
            }
    
#if TEST_SCAN_START_IN_VSTART_INT                     
            DrvGetAramData();
            if(ucAfeRunMode == TP_FREE_RUN_MODE)  
            {

            }
            else
            {
                DrvAsmAramAvail(); // realse aram:  Asm������Aramд��һ��tp֡����, ����AramReady�ж�
            }
#endif  
            //DBG_INT("\nint Aram");
        }
    }

    /* panel conflict int */
    if (usAsmIntEn0&LCD_PANEL_CONFLICT_INT0)
    {
        if (usAsmIntFlag0&LCD_PANEL_CONFLICT_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_PANEL_CONFLICT_INT0;
            g_usAsmIntFlag0 |= LCD_PANEL_CONFLICT_INT0;
            DBG_FLOW("\n xx int panel conflict xx");
        }
    }

    /* frame end int */
    if (usAsmIntEn0&FRAME_END_INT0)
    {
        if (usAsmIntFlag0&FRAME_END_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= FRAME_END_INT0;
            g_usAsmIntFlag0 |= FRAME_END_INT0;
            g_ucFrameEndFlag = 1;
            DBG_FLOW("\nint frame end");
        }
    }

    /* afe det int */
    if (usAsmIntEn0&AFE_DET_INT0)
    {
        if (usAsmIntFlag0&AFE_DET_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= AFE_DET_INT0;
            g_usAsmIntFlag0 |= AFE_DET_INT0;
            g_ucTchDetFlag = 1;
            DBG_FLOW("\n============int tch det");
        }
    }

    /*hw mon timeout int*/
    if(usAsmIntEn1&LCD_HW_MON_TIMEOUT_INT1)
    {
        if(usAsmIntFlag1&LCD_HW_MON_TIMEOUT_INT1)
        {       
            pAsmRegs->usAsmIntClr1 |= LCD_HW_MON_TIMEOUT_INT1;
            g_usAsmIntFlag1 |= LCD_HW_MON_TIMEOUT_INT1;
            g_ucTimeOutFlag = 1;
            DBG_INT("\nint hw mon timeout");
        }
    }    

    /* lcd vstart int */
    if (usAsmIntEn0&LCD_VSTART_INT0)
    {
        if (usAsmIntFlag0&LCD_VSTART_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_VSTART_INT0;
            g_usAsmIntFlag0 |= LCD_VSTART_INT0;
            //DBG_INT("\nint vstart");

#if TEST_CUR_LEFT_SCAN
            return;
#endif
#if TEST_120_ARAM_READY_WAKEUP
            return;
#endif 
            DrvAsmScanStart();         
        }
    }

    /* lcd vmid int */
    if (usAsmIntEn0&LCD_VMID_INT0)
    {
        if (usAsmIntFlag0&LCD_VMID_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_VMID_INT0;
            g_usAsmIntFlag0 |= LCD_VMID_INT0;
            DBG_INT("\nint vmid");
        }
    }

    /* lcd vend int */
    if (usAsmIntEn0&LCD_VEND_INT0)
    {
        if (usAsmIntFlag0&LCD_VEND_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_VEND_INT0;
            g_usAsmIntFlag0 |= LCD_VEND_INT0;
            DBG_INT("\nint vend");
        }
    }

    /* lcd vblank int */
    if (usAsmIntEn0&LCD_VBLANK_INT0)
    {
        if (usAsmIntFlag0&LCD_VBLANK_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_VBLANK_INT0;
            g_usAsmIntFlag0 |= LCD_VBLANK_INT0;
            g_ucLcdBusyCnt = 0;
            DBG_INT("\nint vblank");
            //DBG_FLOW("\nint VBLANK max:0x%x min:0x%x",(pAsmRegs->usAsmScanSta3>>6),(pAsmRegs->usAsmScanSta3&0x1F));
        }
    }

#if 0
    /* lcd glance fall int */
    if (usAsmIntEn&LCD_GLANCE_FALL_INT)
    {
        if (usAsmIntFlag&LCD_GLANCE_FALL_INT)
        {
            pAsmRegs->usAsmIntClr |= LCD_GLANCE_FALL_INT;
            g_usAsmIntFlag |= LCD_GLANCE_FALL_INT;
            if ((pAsmRegs->usAsmIntSta&LCD_GLANCE_STA) == 0)
            {
                if (pAsmRegs->usAsmIntSta&LCD_RUN_STA)
                {
                    g_ucAfeScanMode = TP_NOMAL_MODE;
                }
                else
                {
                    g_ucAfeScanMode = TP_FREE_RUN_MODE;
                }
                AFE_RST = 1;
                AFE_RST = 0;
                DBG_INT("\nglance mode fall");
            }           
        }
    }

    /* lcd glance rise int */
    if (usAsmIntEn&LCD_GLANCE_RISE_INT)
    {
        if (usAsmIntFlag&LCD_GLANCE_RISE_INT)
        {
            pAsmRegs->usAsmIntClr |= LCD_GLANCE_RISE_INT;
            g_usAsmIntFlag |= LCD_GLANCE_RISE_INT;
            if (pAsmRegs->usAsmIntSta&LCD_GLANCE_STA)
            {
                g_ucAfeScanMode = TP_GLANCE_MODE;
                AFE_RST = 1;
                AFE_RST = 0;
                DBG_INT("\nglance mode rise");
            }
        }
    }

#endif

    /* lcd run fall int */
    if (usAsmIntEn0&LCD_RUN_FALL_INT0)
    {
        if (usAsmIntFlag0&LCD_RUN_FALL_INT0)
        {
            pAsmRegs->usAsmIntClr0 |= LCD_RUN_FALL_INT0;
            if ((pAsmRegs->usAsmIntSta&LCD_RUN_STA) == 0)
            {
                g_usAsmIntFlag0 |= LCD_RUN_FALL_INT0;
                ucAfeRunMode = TP_FREE_RUN_MODE;
                AFE_RST = 1;
                AFE_RST = 0;
                DBG_FLOW("\nint free");
            }
        }
    }

    /* lcd run rise int */
    if (usAsmIntEn0&LCD_RUN_RISE_INT0)       
    {
        if (usAsmIntFlag0&LCD_RUN_RISE_INT0)
        {
            if (pAsmRegs->usAsmIntSta&LCD_RUN_STA)
            {
                g_usAsmIntFlag0 |= LCD_RUN_RISE_INT0;   
                if (g_ucAfeScanMode == TP_60HZ_RUN_MODE)
                {
                    ucAfeRunMode = TP_60HZ_RUN_MODE;
                    DBG_FLOW("\nint 60HZ ");
                }
                else
                {
                    ucAfeRunMode = TP_120HZ_RUN_MODE;
                    DBG_FLOW("\nint 120Hz ");
                }
                pAsmRegs->usAsmIntClr0 |= LCD_RUN_RISE_INT0;

                AFE_RST = 1;
                AFE_RST = 0;
                DBG_INT("\nint nomal");
            }
        }
    }
    
//  Enable1  
    /* lcd STB tick int */
    if (usAsmIntEn1&LCD_STB_TICK_INT1)
    {
        if (usAsmIntFlag1&LCD_STB_TICK_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_STB_TICK_INT1 ;
            g_usAsmIntFlag1 |=LCD_STB_TICK_INT1;
            //DBG_FLOW("\nint STB tick %d 0x%x,0x%x",g_ucLcdBusyCnt,(pAsmRegs->usAsmScanSta2>>6),(pAsmRegs->usAsmScanSta2&0x1F));
        }
    }
    
    /* lcd odd even fall int */
    if (usAsmIntEn1&LCD_ODD_EVEN_FALL_INT1)
    {
        if (usAsmIntFlag1&LCD_ODD_EVEN_FALL_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_ODD_EVEN_FALL_INT1 ;
            g_usAsmIntFlag1 |= LCD_ODD_EVEN_FALL_INT1;
            DBG_INT1("\nint odd even fall");
        }
    }

    /* lcd odd even rise int */
    if (usAsmIntEn1&LCD_ODD_EVEN_RISE_INT1)
    {
        if (usAsmIntFlag1&LCD_ODD_EVEN_RISE_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_ODD_EVEN_RISE_INT1 ;
            g_usAsmIntFlag1 |= LCD_ODD_EVEN_RISE_INT1;
            DBG_INT1("\nint odd even rise");
        }
    }

    /* lcd VDO node fall int */
    if (usAsmIntEn1&LCD_VDO_MODE_FALL_INT1)
    {
        if (usAsmIntFlag1&LCD_VDO_MODE_FALL_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_VDO_MODE_FALL_INT1 ;
            g_usAsmIntFlag1 |=LCD_VDO_MODE_FALL_INT1 ;
            DBG_INT1("\nint VDO mode fall");
        }
    }

    /* lcd VDO node rise int */
    if (usAsmIntEn1&LCD_VDO_MODE_RISE_INT1)
    {
        if (usAsmIntFlag1&LCD_VDO_MODE_RISE_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_VDO_MODE_RISE_INT1 ;
            g_usAsmIntFlag1 |=LCD_VDO_MODE_RISE_INT1 ;
            DBG_INT1("\nint VDO mode rise");
        }
    }
    
    /* lcd IDLE node fall int */
    if (usAsmIntEn1&LCD_IDLE_MODE_FALL_INT1)
    {
        if (usAsmIntFlag1&LCD_IDLE_MODE_FALL_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_IDLE_MODE_FALL_INT1 ;
            g_usAsmIntFlag1 |=LCD_IDLE_MODE_FALL_INT1 ;
            DBG_INT1("\nint IDLE mode fall");
        }
    }

    /* lcd IDLE node rise int */
    if (usAsmIntEn1&LCD_IDLE_MODE_RISE_INT1)
    {
        if (usAsmIntFlag1&LCD_IDLE_MODE_RISE_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_IDLE_MODE_RISE_INT1 ;
            g_usAsmIntFlag1 |=LCD_IDLE_MODE_RISE_INT1 ;
            DBG_INT1("\nint IDLE mode rise");
        }
    }

    /* lcd 3D node fall int */
    if (usAsmIntEn1&LCD_3D_MODE_FALL_INT1)
    {
        if (usAsmIntFlag1&LCD_3D_MODE_FALL_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_3D_MODE_FALL_INT1 ;
            g_usAsmIntFlag1 |=LCD_3D_MODE_FALL_INT1 ;
            DBG_INT1("\nint 3D mode fall");
        }
    }

    /* lcd 3D node rise int */
    if (usAsmIntEn1&LCD_3D_MODE_RISE_INT1)
    {
        if (usAsmIntFlag1&LCD_3D_MODE_RISE_INT1)
        {
            pAsmRegs->usAsmIntClr1 |=LCD_3D_MODE_RISE_INT1 ;
            g_usAsmIntFlag1 |=LCD_3D_MODE_RISE_INT1 ;
            DBG_INT1("\nint 3D mode rise");
        }
    }
}



