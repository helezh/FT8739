/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: FlowFactory.h
*
*    Author: 
*
*   Created: 2014-01-01
*
*  Abstract: Please describe the interface in detail for this module
*
* Reference:
*
*******************************************************************************/

#ifndef _FLOW_FACTORY_H_
#define _FLOW_FACTORY_H_

/* Conditional Compiler Options */

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgSystem.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define TEST_60HZ_SCAN_MODE             1   //0表示测试freerun and 120HZ
#define IS_4_MUX_MODE                   0   //mux4模式，key,tp输出P4比mux5少一组，输出4组。__0_0_0_0____

#define TEST_GROUP_SEL1                 0   //Config:   MUX1: G1 G5  MUX2: G2  G6  MUX3: G3 G7  MUX4: G4 G8  MUX5: X G9
#define TEST_GROUP_SEL2                 0   //Config:   MUX1: G4 G5  MUX2: G3  G6  MUX3: G2 G7  MUX4: G1 G8  MUX5: X G9
#define COF_MODE
//#define TEST_MUL_SCAN                     //连续多次扫描

#define TEST_SCAN_START_IN_VSTART_INT   1   //VStart 中断在坑前
#define TEST_MUX_ABC_SACN               0   //亮屏连续扫描3tp帧
#define TEST_MUX_ABCD_SACN              0   //亮屏连续扫描4tp帧
#define TEST_FREERUN_MONITOR            0   //测试Base跟踪，触摸检测
#define TEST_120HZ_MONTIOR              0   //亮屏触摸检测
#define TEST_LCD_CHANGED                0   //亮灭屏测试，及中断测试。
#define TEST_CUR_LEFT_SCAN              0   //LCD剩余坑扫描，启动扫描时机错过坑。

//-------------ASM唤醒Stop测试---------------------------------------------------------
#define TEST_LCD_LVDESD_WAKEUP          0   //唤醒Stop测试
#define TEST_LCD_LVD_WAKEUP             0   //二级宏
#define TEST_LCD_ESD_WAKEUP             0   //二级宏
#define TEST_LCD_RUN_WAKEUP             0   //唤醒Stop测试
#define TEST_LCD_DSTB_WAKEUP            0   //唤醒Stop测试
//-------------------------------------------------------------------------------------

//------------LCD中，能够唤醒StandBy测试-----------------------------------------------
#define TEST_STANDBY_WAKEUP_ALL         0   //开启所有唤醒源,测试唤醒Standby
#define TEST_ASM_FRAME_END_WAKEUP       0
#define TEST_ASM_ARAM_READY_WAKEUP      0
#define TEST_120_ARAM_READY_WAKEUP      0   // 120hz亮屏AramReady唤醒Standby.

#define TEST_LCD_WAKE_UP_STANDBY        0   //一级宏,控制下列二级宏。
#define TEST_LCD_RUN_FALL_WAKEUP        0   //二级宏，外部key模拟时，default低，按下高。  
#define TEST_LCD_RUN_RISE_WAKEUP        0
#define TEST_LCD_DSTB_FAIL_WAKEUP       0
#define TEST_LCD_DSTB_RISE_WAKEUP       0
#define TEST_LCD_VDO_MODE_FALL_WAKEUP   0   //外部key模拟时，default低，按下高。                             
#define TEST_LCD_VDO_MODE_RISE_WAKEUP   0
#define TEST_LCD_IDLE_MODE_FALL_WAKEUP  0 
#define TEST_LCD_IDLE_MODE_RISE_WAKEUP  0
#define TEST_LCD_3D_MODE_FALL_WAKEUP    0 
#define TEST_LCD_3D_MODE_RISE_WAKEUP    0
//--------------------------------------------------------------------------------------


//-------------------扫描模式，采样模式------------------------------------
#define TEST_2SAMPLE_ANA_SUB            1 
#define TEST_2SAMPLE_POSITIVE           0 
#define TEST_2SAMPLE_NEGATIVE           0
#define TEST_2SAMPLE_DIG_SUB            0
#define TEST_1SAMPLE                    0 
//-------------------------------------------------------------------------


//单个通道输出原始ADC测试
#define TEST_ONE_CHANNEL_ADC            0 



#define TEMP_CLOSE_KEY      0//1    
#define KEY_R_L             0//0:KEY键接在左边AFE;1:KEY键接在右边AFE
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

typedef enum
{
    TP_FREE_RUN_MODE,
    TP_60HZ_RUN_MODE,
    TP_120HZ_RUN_MODE,
    TP_GLANCE_RUN_MODE,
    TP_OTHER_RUN_MODE,
} ENUM_TEST_MODE;

typedef enum
{
    Addr_PANEL_MODE_CFG0 =1, 
    Addr_PANEL_MODE_CFG1 =2,
    Addr_PANEL_MODE_CFG2 =3, 
    Addr_AFE_SYS_CFG0 =4, 
    Addr_AFE_SYS_CFG1 =5, 
    Addr_AFE_SCAN_CFG0 =6, 
    Addr_AFE_SCAN_CFG1 =7, 
    Addr_AFE_DUMMY_SCAN_CFG =8, 
    Addr_AFE_BASE_TRACK_CFG =9, 
    Addr_ACC_OFFSET =10, 
    Addr_TP_MONITOR_THRESHOLD =11,
    Addr_KEY_MONITOR_THRESHOLD =12, 
    Addr_AFE_ANA_K1_CFG0 =13,
    Addr_AFE_ANA_K2_CFG1 =14,
    Addr_AFE_ANA_CA_CFG0 =15, 
    Addr_AFE_ANA_CA_CFG1 =16, 
    Addr_AFE_ANA_CA_CFG2 =17,
    Addr_AFE_ANA_P1_P2_CFG0 =18, 
    Addr_AFE_ANA_P1_P2_CFG1 =19,
    Addr_AFE_ANA_P1_P2_CFG2 =20, 
    Addr_AFE_ANA_P1_P2_CFG3 =21,
    Addr_AFE_ANA_P1_P2_CFG4 =22, 
    Addr_AFE_ANA_P1_P2_CFG5 =23, 
    Addr_AFE_P1_P2_DLY_CFG0 =24, 
    Addr_AFE_P1_P2_DLY_CFG1 =25, 
    Addr_AFE_ANA_SH_CFG0 =26,
    Addr_AFE_ANA_SH_CFG1 =27, 
    Addr_AFE_ANA_SH_CFG2 =28, 
    Addr_AFE_ANA_SH_CFG3 =29, 
    Addr_AFE_ANA_SH_CFG4 =30, 
    Addr_AFE_ANA_SH_CFG5 =31,
    Addr_AFE_ANA_SH_CFG6 =32, 
    Addr_AFE_ANA_ADC_CFG0 =33, 
    Addr_AFE_ANA_ADC_CFG1 =34, 
    Addr_AFE_ANA_ADC_CFG2 =35, 
    Addr_AFE_ANA_ADC_CFG3 =36, 
    Addr_AFE_GIPH_P1_P2_CFG =37, 
    Addr_AFE_GIPL_P1_P2_CFG =38, 
    Addr_AFE_SD_VOM_OPT_P1_P2_CFG =39,
    Addr_AFE_SX_P1_P2_CFG =40, 
    Addr_AFE_MOUT_GIPH_CFG = 41,
    Addr_AFE_MOUT_GIPL_CFG = 42,
    Addr_AFE_GOUT_GIPH_CFG = 43,
    Addr_AFE_GOUT_GIPL_CFG = 44,
   
    Addr_ALL_GATE_ON_L_CFG =45, 
    Addr_ALL_GATE_OFF_L_CFG =46,
    Addr_ALL_GATE_STOP_L_CFG =47, 
    Addr_ALL_GATE_H_CFG =48,                              
    Addr_RPT_RAWDATA_NUM =49,                             
    Addr_CB_ADJUST_THLD_TP =50,                                
    Addr_TEST_MODE_FLAG =51,                              
    Addr_PRESCAN_TIME =52,                                 
    Addr_DISCHARGE_TIME =53,                               
    Addr_ANA_STATIC_CFG0 =54,                              
    Addr_ANA_STATIC_CFG1 =55,                               
    Addr_ANA_STATIC_CFG2 =56,                              
    Addr_ANA_STATIC_CFG3 =57,                            
    Addr_TEST_P0_CFG0 =58,                               
    Addr_TEST_P0_CFG1 =59,                               
    Addr_TEST_P0_CFG2 =60,                                 
    Addr_TEST_P1_CFG0 =61,                               
    Addr_TEST_P1_CFG1 =62,                                
    Addr_TEST_P1_CFG2 =63,                                 
                                                                 
                                                                 
                                   
    Addr_MCAP_SCAN_CFG =64,                                
    Addr_MCAP_SCANSR =65,                                  
    Addr_MCAP_LPFIR_SUM_NUM =66,                     
    Addr_RAWSHIFTCAF =67,                                
    Addr_RAWDATA_OFFSET_L =68,                           
    Addr_ADC_CFG =69,                                      
    Addr_ADC_DATA0 =70,                                   
    Addr_MCAP_INIT_SAMPL_CFG =71,                         
    Addr_OVERFLOW_THR =72,                                 
    Addr_UNDERFLOW_THR =73,                                
    Addr_OVERFLOW_UPBOUND =74,                            
    Addr_OVER_POINT_FRAME =75,                             
    Addr_NORMAL_SIGNAL_UPTHR =76,                          
    Addr_NORMAL_SIGNAL_DWTHR =77,                        
    Addr_OVERFLOW_CLR_FRAMENUM =78,                       
    Addr_MCAP_LPFIR_CFG =79,                               
    Addr_MCAP_LPFIR_COF0 =80,                              
    Addr_MCAP_LPFIR_COF1 =81,                              
    Addr_MCAP_LPFIR_COF2 =82,                             
    Addr_MCAP_LPFIR_COF3 =83,                              
    Addr_MCAP_LPFIR_COF4 =84,                              
    Addr_MCAP_LPFIR_COF5 =85,                            
    Addr_MCAP_LPFIR_COF6 =86,                             
    Addr_MCAP_LPFIR_COF7 =87,
    Addr_CB_ADJUST_THLD_KEY = 88,
}ENUM_AFE_ADDR;



/* 01寄存器命令 */
typedef enum
{
    R01_ARAM      = 0xAA, /* 指向互容数据区 */
    R01_CNT_CLEAR = 0xAD, /* 地址计数清0 */
    R01_CNT_KEY   = 0xAE, /* 指定KEY地址 */
} ENUM_R01_CMD;

/* ram表项选择 */
typedef enum
{
    AREA_TBL_RAM,
    AREA_BASE_ORDER,
    AREA_BASE_ACC,
} ENUM_RAM_SEL;


typedef enum
{
    BIT_PANEL_MUX3_GROUPB_SEL = 12,                          
    BIT_PANEL_MUX3_GROUPA_SEL = 10,
    BIT_PANEL_MUX2_GROUPB_SEL = 7,
    BIT_PANEL_MUX2_GROUPA_SEL = 5,
    BIT_PANEL_MUX1_GROUPB_SEL = 2,
    BIT_PANEL_MUX1_GROUPA_SEL = 0,
} ENUM_GROUP_SEL1;

typedef enum
{
    BIT_PANEL_MUX5_GROUPB_SEL = 8,                                  
    BIT_PANEL_MUX5_GROUPA_SEL = 5,
    BIT_PANEL_MUX4_GROUPB_SEL = 2,
    BIT_PANEL_MUX4_GROUPA_SEL = 0,
} ENUM_GROUP_SEL2;

typedef enum
{
    BIT_AFE_SCAN_TIMES = 3,                                       
    BIT_AFE_SCAN_MODE = 0,
} ENUM_MODE;

typedef enum
{	
    BIT_BASE_TRACK_STEP = 2,                                        
    BIT_BASE_TRACK_MODE = 1,
    BIT_BASE_TRACK_ENABLE = 0,
} ENUM_BASE_MODE;

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

#define AFE_REG_LEN   0x57 //87

#define USE_LEFT_KEY  1                        /* default used to left key*/

#define TX_NUM  (9*2)
 

#ifdef  COF_MODE
#define CH_ORDER_MAX         (324)               /* 一边的通道最多数量 324(Tp) 9x36 */
#define CH_LEN               (324*2)             /* 通道总数，不包含key */ 
#define CH_LEN_MAX           (CH_ORDER_MAX+4)    /* 一边的通道最多数量 324(Tp)+4(key) */
#define RX_NUM  36  
#else
#define CH_ORDER_MAX         (288)               /* 一边的通道最多数量 288(Tp) 9x32 */
#define CH_LEN               (288*2)             /* 通道总数，不包含key */ 
#define CH_LEN_MAX           (CH_ORDER_MAX+4)    /* 一边的通道最多数量 288(Tp)+4(key) */
#define RX_NUM  32  
#endif
#define KEY_ADDR_OFFSET      4                   /*左边key offset=0; 右边key offset = 4*/

#define TAB_START_ADDR            256
#define TAB_TP_KEY_CB_START_ADDR  10 
#define TAB_RAM_LEN               176            /*ADDR: 0-9     Tab1 config  10-175:  TP and KEY CB EN*/ 
                                                 /*ADDR: 176-185 Tab2 config  185-351: TP and KEY CB EN*/
                                                 /*ADDR: 352-361 Tab3 config  362-527: TP and KEY CB EN*/  
                                                 /*ADDR: 528-537 Tab4 config  537-703: TP and KEY CB EN*/ 
#define TAB_RAM_START_ADDR   256

#define ACC_RAM_LEN          324
#define ACC_RAM_START_ADDR   256

#define BASE_RAM_LEN         652
#define BASE_RAM_START_ADDR  256
#define BASE_RAM_ORDER_LEN         CH_ORDER_MAX   // 288 or 324
#define BASE_RAM_TP_RAWBASE_ADDR   CH_ORDER_MAX   // 288 or 324
#define BASE_RAM_KEY_RAWBASE_ADDR  (BASE_RAM_ORDER_LEN+BASE_RAM_TP_RAWBASE_ADDR)
#define BASE_RAM_BASE_LEN    324   // Base ram Base存放大小324
#define BASE_RAM_KEY_LEN     4     // Base ram Key存放大小4


#define TEST_ACC_H_RAM_EN    1   // acc_h ram enble
#define TEST_ACC_M_RAM_EN    1   // acc_m ram enble
#define TEST_ACC_M2_RAM_EN   1   // acc_m2 ram enble
#define TEST_ACC_L_RAM_EN    1   // acc_l ram enble


#define KEY_NUM_MAX         4    /* IC支持的最大按键数量 */

#define ARAM_INFO_BASE_ADDR        (324*2+8)
#define KEY_R_DIFF_NOISE_MAX_ADDR   5
#define TP_R_DIFF_NOISE_MAX_ADDR    4
#define ARAM_INFO_R_ADDR            3 
#define KEY_L_DIFF_NOISE_MAX_ADDR   2
#define TP_L_DIFF_NOISE_MAX_ADDR    1
#define ARAM_INFO_L_ADDR            0 

#define SCAN_MODE_1     1
#define SCAN_MODE_2     2
#define SCAN_MODE_3     3
#define SCAN_MODE_4     4
#define SCAN_MODE_5     5
#define SCAN_MODE_6     6
#define SCAN_MODE_7     7
#define SCAN_MODE_8     8

extern volatile UINT8 XRAM g_ucAbnormalFlag;
extern volatile UINT8 XRAM g_ucState0;
extern volatile UINT8 XRAM g_ucState1;

#if KEY_R_L
#define pXSIREG pXSI0Regs
#else
#define pXSIREG pXSI1Regs
#endif

/*******************************************************************************
* Global function prototypes
*******************************************************************************/ 
void AppWriteRegMapDataTest(UINT8 ucAddr, UINT8 ucData);
UINT8 AppReadRegMapDataTest(UINT8 ucAddr);
void FlowFactory(void);
void TestXbus(void);
void Afe_Clk_Init(void);
void DrvAfeSetBaseTrack(UINT8 ucBaseMode,UINT8 ucStep);
void DrvAfeInitBase(void);
void DrvAfeSetHCBTarget(UINT16 usTpCbTarget,UINT16 usKeyCbTarget);
void DrvGetAramData(void);
void DrvGetRptRamRawBase(void);
void DrvAsmInterEnableAll(void);

#endif 
