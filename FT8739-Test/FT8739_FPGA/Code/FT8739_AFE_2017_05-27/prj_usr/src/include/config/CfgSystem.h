/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: CfgSystem.h
*
*    Author: 
*
*   Created: 2013-02-01
*
*  Abstract: System Common Definition and typedefs
*
* Reference:
*
*******************************************************************************/

#ifndef _CFG_SYSTEM_H_
#define _CFG_SYSTEM_H_

/* Conditional Compiler Options */

/*******************************************************************************
* Included files
*******************************************************************************/
#include "CfgGlobal.h"
#include "flowfactory.h"
/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#define PWR_EN             1    //0:�ر����µ�ʱ�����;1:�������µ�ʱ�����
#define SC_CLB_TIMES       8    // У׼���� ���ܳ���32��
#define CB_AFE_SCAN_MODE   0    //CBУ��ɨ�跽ʽ
#define TEST_MCAP_CB       0    //����mcap cbУ��
#define TEST_MCAP_HWMON    1    //����mcap hw mon
#define TEST_SAMP_INT      0    //����mcap�ɼ�ADC���ݳ�ʼ��λ.


//0x01 
#define  DAT_PANEL_MUX3_GROUPB_SEL    0x02    //[14:12] mux3 group bѡ�������: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:��Ч                            
#define  DAT_PANEL_MUX3_GROUPA_SEL    0x02    //[11:10] mux3 group aѡ�������: 0:G1; 1:G2 2:G3 3:G4 ,other:��Ч 
#define  DAT_PANEL_MUX2_GROUPB_SEL    0x03    //[09:07] mux2 group bѡ�������: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:��Ч   
#define  DAT_PANEL_MUX2_GROUPA_SEL    0x01    //[06:05] mux2 group aѡ�������: 0:G1; 1:G2 2:G3 3:G4 ,other:��Ч 
#define  DAT_PANEL_MUX1_GROUPB_SEL    0x04    //[04:02] mux1 group bѡ�������: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:��Ч 
#define  DAT_PANEL_MUX1_GROUPA_SEL    0x00    //[01:00] mux1 group aѡ�������: 0:G1; 1:G2 2:G3 3:G4 ,other:��Ч 
#define  rPANEL_MODE_CFG0             ((DAT_PANEL_MUX3_GROUPB_SEL<<12)\                           
                                      +(DAT_PANEL_MUX3_GROUPA_SEL<<10)\
                                      +(DAT_PANEL_MUX2_GROUPB_SEL<<7)\
                                      +(DAT_PANEL_MUX2_GROUPA_SEL<<5)\
                                      +(DAT_PANEL_MUX1_GROUPB_SEL<<2)\
                                      +(DAT_PANEL_MUX1_GROUPA_SEL<<0))

//0x02
#define  DAT_PANEL_MUX5_GROUPB_SEL    0x00    //[10:08] mux5 group bѡ�������: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:��Ч   
#define  DAT_PANEL_MUX5_GROUPA_SEL    0x04    //[07:05] mux5 group aѡ�������: 0:G1; 1:G2 2:G3 3:G4 4:������
#define  DAT_PANEL_MUX4_GROUPB_SEL    0x01    //[04:02] mux4 group bѡ�������: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:��Ч 
#define  DAT_PANEL_MUX4_GROUPA_SEL    0x03    //[01:00] mux4 group aѡ�������: 0:G1; 1:G2 2:G3 3:G4 ,other:��Ч 
#define  rPANEL_MODE_CFG1             ((DAT_PANEL_MUX5_GROUPB_SEL<<8)\                                  
                                      +(DAT_PANEL_MUX5_GROUPA_SEL<<5)\
                                      +(DAT_PANEL_MUX4_GROUPB_SEL<<2)\
                                      +(DAT_PANEL_MUX4_GROUPA_SEL<<0))

//0x03
#define  DAT_PANEL_MUX4_KEY_SEL      0x03    //[7:6] mux4 key��ѡ���ź� 
#define  DAT_PANEL_MUX3_KEY_SEL      0x02    //[5:4] mux3 key��ѡ���ź� 
#define  DAT_PANEL_MUX2_KEY_SEL      0x01    //[3:2] mux2 key��ѡ���ź� 
#define  DAT_PANEL_MUX1_KEY_SEL      0x00    //[1:0] mux1 key��ѡ���ź� 
#define  rPANEL_MODE_CFG2            ((DAT_PANEL_MUX4_KEY_SEL<<6)\                                  
                                     +(DAT_PANEL_MUX3_KEY_SEL<<4)\
                                     +(DAT_PANEL_MUX2_KEY_SEL<<2)\
                                     +(DAT_PANEL_MUX1_KEY_SEL<<0))

//0x04
#define  DAT_ADC_SHIFT_CLK_DIV       0x00  //[15:14] adc_shift_clk��Ƶ�ȣ������afe_clk: 0:2��Ƶ��1:3��Ƶ; 2:4��Ƶ                                   
#define  DAT_ADC_CLK_DIV             0x00  //[13:11] adc_clk��Ƶ�ȣ������afe_clk: 0-7: 2,4,6,8,10,12,14,16��Ƶ
#define  DAT_KEY_CB_ADJUST_DIR       0x00  //[10] key��У������ 0:˳ʱ��; 1:��ʱ��
#define  DAT_TP_CB_ADJUST_DIR        0x00  //[9]  tp_chУ������ 0:˳ʱ��; 1:��ʱ��
#define  DAT_AFE_EN_MODE             0x00  //[8]  ʹ��stb_en,��afe_enλ��.1'b0:��scan_start���;1'b1:��stb_start���
#define  DAT_KEY_ENABLE              0x0F  //[7:4]4��key��ʹ�ܣ���bitλ��Ӧ��1:ʹ��       
#define  DAT_SHORT_TEST_ENABLE       0x00  //[3] short test����ʹ��: 1:ʹ��
#define  DAT_PANEL_SHRINK_ENABLE     0x00  //[2] ��Ļ��Сʹ��: 0:��ʹ��,��������mux5����; 1:ʹ�ܣ���Ļ����mux4����
#define  DAT_DISCONNECT_MODE         0x00  //[1] ������ʹ��: 0:��ʹ��; 1:ʹ��(������ģʽ��Ч)
#define  DAT_AFE_WORK_MODE           0x01  //[0] ����ģʽ:   0: test mode; 1: normal scan mode                                    
#define  rAFE_SYS_CFG0               ((DAT_ADC_SHIFT_CLK_DIV<<14)\                                          
                                     +(DAT_ADC_CLK_DIV<<11)\
                                     +(DAT_KEY_CB_ADJUST_DIR<<10)\
                                     +(DAT_TP_CB_ADJUST_DIR<<9)\
                                     +(DAT_AFE_EN_MODE<<8)\
                                     +(DAT_KEY_ENABLE<<4)\
                                     +(DAT_SHORT_TEST_ENABLE<<3)\
                                     +(DAT_PANEL_SHRINK_ENABLE<<2)\
                                     +(DAT_DISCONNECT_MODE<<1)\
                                     +(DAT_AFE_WORK_MODE<<0))

//0x05
#define  DAT_ADC_DUMMY_SCAN_EN       0x01  //[15] Dummyɨ�裬ADC�Ƿ�ʹ��: 1:ʹ��
#define  DAT_TP_STANDBY_ENABLE       0x01  //[14] tp_standby�ź�ʹ��. 1:ʹ�ܣ�ʹ�ܺ��ڸ��źŵ��������CB shift���� ,freerun�̶�Ϊ0����������Ϊ0.                                 
#define  DAT_SSI_CLK_SEL             0x00  //[13:11] SSIʱ��48M��Ƶ: 0:12M; 1:8M; 2:6M; 3:4.8M; 4:4M; 5:3.4M 6:3M
#define  DAT_ACC_ASR                 0x00  //[10:7] �ۺͽ������bit��. 0:���ƶ�; 1:����1bit; ...9:����9bit
#define  DAT_MEMORY_DATASEG          0x00  //[6:5]  mcu����memory����λ��: 0:0~15bit; 1:16~31bit; 2:32~47bit;3:48~63bit
#define  DAT_MEMORY_SEL              0x00  //[4:3]  mcu����memoryѡ��: 0: Tab Ram; 1: Acc Ram 2:Rpt Ram
#define  DAT_RPT_INFO_ENABLE         0x01  //[2]  �ϱ�infoʹ��.            1:ʹ��
#define  DAT_RPT_DIFF_NOISE_MAX_EN   0x01  //[1]  �ϱ�diffNoiseMaxʹ��.    1:ʹ��
#define  DAT_NOISE_DETECT_ENABLE     0x01  //[0]  diff noise ��⹦��ʹ��. 1:ʹ��                                     
#define  rAFE_SYS_CFG1               ((DAT_ADC_DUMMY_SCAN_EN<<15)\   
                                     +(DAT_TP_STANDBY_ENABLE<<14)\                                          
                                     +(DAT_SSI_CLK_SEL<<11)\
                                     +(DAT_ACC_ASR<<7)\
                                     +(DAT_MEMORY_DATASEG<<5)\
                                     +(DAT_MEMORY_SEL<<3)\
                                     +(DAT_RPT_INFO_ENABLE<<2)\
                                     +(DAT_RPT_DIFF_NOISE_MAX_EN<<1)\
                                     +(DAT_NOISE_DETECT_ENABLE<<0))

//0x06        
#define  DAT_KEY_SAMPL_INTERVAL_6_H  0x00  //[15:11] key_sampl_interval_6[10:6]
#define  DAT_AFE_SCAN_TIMES          0x06  //[10:3]  ÿ��muxɨ�������ʵ��ֵΪ����ֵ��1
#define  DAT_AFE_SCAN_MODE           0x00  //[2:0]: Afeɨ�跽ʽ:
                                           //0: ��ʽ1: ��������ֻɨ��1��1/5����ͨ��
                                           //1: ��ʽ2: ��������ֻɨ��2��1��1/5����ͨ��
                                           //2: ��ʽ3: ��������ֻɨ��3��2��1/5����ͨ��
                                           //3: ��ʽ4: ��������ֻɨ��2��3��1/5����ͨ��
                                           //4: ��ʽ5: ���������ֻɨ��5��1/5����ͨ��
                                           //5: ��ʽ6: ��������ֻɨ��5��1/5����ͨ�����Ҷ���ۼӣ���ʽ
                                           //6: ��ʽ7: ��������ֻɨ��2��1��mux,��mux9ģʽ
                                           //7: ��ʽ8: ��ɨ��1��Mux,��Monitor,5��SX����ģʽ
#define  rAFE_SCAN_CFG0              ((DAT_KEY_SAMPL_INTERVAL_6_H<<11)\
                                     +(DAT_AFE_SCAN_TIMES<<3)\                                          
                                     +(DAT_AFE_SCAN_MODE<<0))
                                     
//0x07
#define  DAT_KEY_SAMPL_INTERVAL_6_L  0x00  //[15:11] key_sampl_interval_6[5:1]
#define  DAT_DOU_SAMPLE_MODE         0x00  //[10:9] ����ģʽ: 0:˫�߲�����ģ�����; 1:���߲���; 2:���߲���; 3:˫�߲������������                                   
#define  DAT_AFE_SIN_DOU_SCAN_SEL    0x00  //[8] SXɨ�跽ʽ:  0:˫��ɨ��(4�ֲ���mode); 1: ����ɨ��(��1�ֵ��߲���)
#define  DAT_AFE_SCAN_SEG_NUM        0x04  //[0] ��ʽ6��ɨ�����
#define  rAFE_SCAN_CFG1              ((DAT_KEY_SAMPL_INTERVAL_6_L<<11)\
                                     +(DAT_DOU_SAMPLE_MODE<<9)\                                          
                                     +(DAT_AFE_SIN_DOU_SCAN_SEL<<8)\
                                     +(DAT_AFE_SCAN_SEG_NUM<<0))
//0x08
#define  DAT_SAMPLE_INTERVAL_6_LSB   0x00  //[15] key_sampl_interval_6[0]
#define  DAT_SCAN_MUX_DUMMY_NUM      0x00  //[14:10]Mux�л�֮��Dummy����                                   
#define  DAT_SECTION_DUMMY_NUM       0x00  //[9:5]��ǰDummy����
#define  DAT_SCAN_FRAME_DUMMY_NUM    0x00  //[4:0]Tp֡ǰDummy����                                     
#define  rAFE_DUMMY_SCAN_CFG         ((DAT_SAMPLE_INTERVAL_6_LSB<<15)\
                                     +(DAT_SCAN_MUX_DUMMY_NUM<<10)\                                          
                                     +(DAT_SECTION_DUMMY_NUM<<5)\
                                     +(DAT_SCAN_FRAME_DUMMY_NUM<<0))

//0x09     
#define  DAT_ADC_SAMPLE_POINT        0x00  //[15:10]ADC���ݲ�����
#define  DAT_BASE_TRACK_STEP         0x00  //[9:2]Monitorģʽ��Base���٣��������ٲ���                                      
#define  DAT_BASE_TRACK_MODE         0x01  //[1] Monitorģʽ��Base���ٷ�ʽ: 0:��������; 1:ԭֵ����
#define  DAT_BASE_TRACK_ENABLE       0x01  //[0] Montiorģʽ��Base����ʹ�ܣ�1:ʹ��                                     
#define  rAFE_BASE_TRACK_CFG         ((DAT_ADC_SAMPLE_POINT<<10)\
                                     +(DAT_BASE_TRACK_STEP<<2)\                                          
                                     +(DAT_BASE_TRACK_MODE<<1)\
                                     +(DAT_BASE_TRACK_ENABLE<<0))
//0x0A  10
#define  DAT_ACC_OFFSET              0x0000  //[15:0] ADC�����ۼ�ƫ����,����ֵ
#define  rACC_OFFSET                 (DAT_ACC_OFFSET<<0)

//0x0B  11
#define  DAT_TP_MONITOR_THERSHOLD    0x0000  //[15:0] �������ʱ��TPͨ���Ĵ�����ֵ
#define  rTP_MONITOR_THRESHOLD       (DAT_TP_MONITOR_THERSHOLD<<0)

//0x0C  12
#define  DAT_KEY_MONITOR_THERSHOLD   0x0000  //[15:0] �������ʱ��KEYͨ���Ĵ�����ֵ
#define  rKEY_MONITOR_THRESHOLD      (DAT_KEY_MONITOR_THERSHOLD<<0)

//0x0D  13
#define  DAT_AFE_ANA_GEN_CFG0        0xC2    //[10:0] K1: CA_P1�ߵ�ƽ��ȣ�ʵ��ֵΪ����ֵ��1.
#define  rAFE_ANA_K1_CFG0           (DAT_AFE_ANA_GEN_CFG0<<0)

//0x0E  14
#define  DAT_AFE_ANA_GEN_CFG1        0x2E    //[10:0] K2: CA_P1�͵�ƽ��ȣ�ʵ��ֵΪ����ֵ��1.
#define  rAFE_ANA_K2_CFG1           (DAT_AFE_ANA_GEN_CFG1<<0)

//0x0F  15
#define  DAT_T3                      0x01    //[11:8] T3ʱ���ȣ�Allʵ��ֵΪ����ֵ��1.
#define  DAT_T2                      0x01    //[7:4]  T2ʱ����
#define  DAT_T1                      0x01    //[3:0]  T1ʱ����
#define  rAFE_ANA_CA_CFG0            ((DAT_T3<<8)\                                          
                                     +(DAT_T2<<4)\
                                     +(DAT_T1<<0))
                                     
//0x10  16
#define  DAT_T5                      0x28    //[15:7] T5ʱ����
#define  DAT_T4                      0x01    //[6:0]  T4ʱ����
#define  rAFE_ANA_CA_CFG1            ((DAT_T5<<8)\                                          
                                     +(DAT_T4<<0))

//0x11  17
#define  DAT_CB_DAC_ONE_STEP_W       0x1 // 0x2     //[11:8] cb_dacÿһ�׿�ȣ�ʵ��ֵΪ����ֵ��1. 
#define  DAT_CB_JUMP_STEP_EN         0x0     //[7] 0:32�ף� 1:16��
#define  DAT_T6                      0x06    //[6:0]  T6ʱ����
#define  rAFE_ANA_CA_CFG2            ((DAT_CB_DAC_ONE_STEP_W<<8)\                                          
                                     +(DAT_CB_JUMP_STEP_EN<<7)\
                                     +(DAT_T6<<0))
//0x12  18
#define  DAT_AFE_LOAD_DELAY_H        0x00    //[15:10] afe load cb finish delay high bits;
#define  DAT_T7_SX                   0x000   //[9:0]  SX/VCOM_OPT T7ʱ����
#define  rAFE_ANA_P1_P2_CFG0         ((DAT_AFE_LOAD_DELAY_H<<10)\
                                     +(DAT_T7_SX<<0))

//0x13  19
#define  DAT_AFE_LOAD_DELAY_M        0x00    //[15:10] afe load cb finish delay middle bits;
#define  DAT_T8_SX                   0x000   //[9:0]  SX/VCOM_OPT T8ʱ����
#define  rAFE_ANA_P1_P2_CFG1         ((DAT_AFE_LOAD_DELAY_M<<10)\
                                     +(DAT_T8_SX<<0))

//0x14  20
#define  DAT_AFE_LOAD_DELAY_L        0x00    //[15:10] afe load cb finish delay low bits;
#define  DAT_T7_GIP                  0x000   //[9:0]  GIPH/GIPL T7ʱ����
#define  rAFE_ANA_P1_P2_CFG2         ((DAT_AFE_LOAD_DELAY_M<<10)\
                                     +(DAT_T7_GIP<<0))

//0x15  21                           
#define  DAT_T8_GIP                  0x000   //[9:0]  GIPH/GIPL T8ʱ����
#define  rAFE_ANA_P1_P2_CFG3         (DAT_T8_GIP<<0)

//0x16  22                           
#define  DAT_T7_SD                   0x000   //[9:0]  SOURCE T7ʱ����
#define  rAFE_ANA_P1_P2_CFG4         (DAT_T7_SD<<0)

//0x17  23                           
#define  DAT_T8_SD                   0x000   //[9:0]  SOURCE T8ʱ����
#define  rAFE_ANA_P1_P2_CFG5         (DAT_T8_SD<<0)

//0x18  24
#define  DAT_GIPL_P1P2_DLY           0x00   //[15:12] gipl p1/p2 delayʱ��                                     
#define  DAT_GIPH_P1P2_DLY           0x00   //[11:8]  giph p1/p2 delayʱ��  
#define  DAT_SX_DLY                  0x00   //[7:4] sx p1/p2 delayʱ��
#define  DAT_CA_DLY                  0x00   //[3:0] ca delayʱ��
#define  rAFE_P1_P2_DLY_CFG0         ((DAT_GIPL_P1P2_DLY<<12)\                                          
                                     +(DAT_GIPH_P1P2_DLY<<8)\
                                     +(DAT_SX_DLY<<4)\
                                     +(DAT_CA_DLY<<0))
//0x19  25
#define  DAT_VCOM_DLY                0x00   //[7:4] vcom p1/p2 delayʱ��
#define  DAT_SD_DLY                  0x00   //[3:0] source p1/p2 delayʱ��
#define  rAFE_P1_P2_DLY_CFG1         ((DAT_VCOM_DLY<<4)\                                          
                                     +(DAT_SD_DLY<<0))

//0x1A  26
#define  DAT_SCAN_START_0_WITDH      0x00 //[13:10]ÿ1��tp֡,��1��scan_start�ĳ���,RO
#define  DAT_T10                     0x21 // 0x011  //[9:0] T10 ʱ����
#define  rAFE_ANA_SH_CFG0            ((DAT_SCAN_START_0_WITDH<<10)\
                                     +(DAT_T10<<0))

//0x1B  27
#define  DAT_START_OTHER_MAX_WITDH   0x00 //[12:10]ÿ1��tp֡,����scan_start����󳤶ȣ�RO
#define  DAT_T11                     0x21 //0x011  //[9:0] T11 ʱ����
#define  rAFE_ANA_SH_CFG1            ((DAT_START_OTHER_MAX_WITDH<<10)\
                                     +(DAT_T11<<0))

//0x1C  28
#define  DAT_START_OTHER_MIN_WITDH   0x00 //[12:10]ÿ1��tp֡,����scan_start����С���ȣ�RO
#define  DAT_T12                     0x001  //[9:0] T12 ʱ����
#define  rAFE_ANA_SH_CFG2            ((DAT_START_OTHER_MIN_WITDH<<10)\
                                     +(DAT_T11<<0))

//0x1D  29
#define  DAT_T13                     0x001  //[9:0] T13 ʱ����
#define  rAFE_ANA_SH_CFG3            (DAT_T13<<0)

//0x1E  30
#define  DAT_T14                     0x011  //[9:0] T14 ʱ����
#define  rAFE_ANA_SH_CFG4            (DAT_T14<<0)

//0x1F  31
#define  DAT_FRM_START_WITDH         0x8    //[12:9] frame_start_���ѡ��ֻ������6,7,8
#define  DAT_T15                     0x001  //[9:0] T15 ʱ����
#define  rAFE_ANA_SH_CFG5            ((DAT_FRM_START_WITDH<<9)\
                                     +(DAT_T15<<0))

//0x20  32
#define  DAT_SEC_START_WITDH         0x4   //[14:12] section_start���ѡ��,ֻ������3,4,5
#define  DAT_SH_DLY_SEL              0x01  //[11]sh cap control delay 45ns  1:delay 0: no delay
#define  DAT_T17                     0x03  //[10:6] T17 ʱ����
#define  DAT_T16                     0x11  //[5:0]  T16 ʱ����
#define  rAFE_ANA_SH_CFG6            ((DAT_SEC_START_WITDH<<12)\
                                     +(DAT_SH_DLY_SEL<<11)\
                                     +(DAT_T17<<6)\
                                     +(DAT_T16<<0))

//0x21  33
#define  DAT_T22                     0x3F  //[15:8] T22 ʱ����
#define  DAT_T20                     0x07  //[7:0]  T20 ʱ����
#define  rAFE_ANA_ADC_CFG0           ((DAT_T22<<8)\
                                     +(DAT_T20<<0))

//0x22  34
#define  DAT_ADC_CLK_GATE_EN         0x01  //[14]tp channel adc clk gating enable
#define  DAT_KEY_ADC_SAMPLE_SEL      0x00  //[13]key��ADC������ѡ��;1'b0:adc_clk�����ز���;1'b1:adc_clk��������1�Ĳ���
#define  DAT_T25                     0x01  //[12:9] T25 ʱ����
#define  DAT_T21                     0x07  //[8:0]  T21 ʱ����
#define  rAFE_ANA_ADC_CFG1           ((DAT_ADC_CLK_GATE_EN<<14)\
                                     +(DAT_KEY_ADC_SAMPLE_SEL<<13)\
                                     +(DAT_T25<<9)\
                                     +(DAT_T21<<0))

//0x23  35
#define  DAT_T26                     0x01  //[12:9] T22 ʱ����
#define  DAT_T23                     0x01  //[8:0]  T20 ʱ����
#define  rAFE_ANA_ADC_CFG2           ((DAT_T26<<9)\
                                     +(DAT_T23<<0))

//0x24  36
#define  DAT_SADC_OSDET              0x0   //[15] SADC offset test control: 1:enable
#define  DAT_ADC_KEY_VRSEL           0x0   //[14] 1:enable
#define  DAT_TP_CH_VRSEL             0x0   //[13] 1:enable
#define  DAT_ADC_SH_DELAY            0x01  //[12:5] adc sh delayʱ�䣬������λΪadc_clk;
#define  DAT_ADC_SH_WIDTH            0x03  //[4:0]  adc sh ��ȣ�������λΪadc_clk;
#define  rAFE_ANA_ADC_CFG3           ((DAT_SADC_OSDET<<15)\
                                     +(DAT_ADC_KEY_VRSEL<<14)\
                                     +(DAT_TP_CH_VRSEL<<13)\
                                     +(DAT_ADC_SH_DELAY<<5)\
                                     +(DAT_ADC_SH_WIDTH<<0))

//0x25  37
#define  DAT_GIPH_PHASE3             0x00  //[11:10] giph display off phase3�׶�p1/p2����ֵ(0:ȫ����1:Hiz; 2:GND)
#define  DAT_GIPH_PHASE2             0x00  //[9:8] giph display off phase2�׶�p1/p2����ֵ(0:ȫ����1:Hiz; 2:GND)
#define  DAT_GIPH_PHASE1             0x00  //[7:6] giph display off phase1�׶�p1/p2����ֵ
#define  DAT_GIPH_PHASE0             0x00  //[5:4] giph display off phase0�׶�p1/p2����ֵ
#define  DAT_GIPH_DPON_NO_SCAN       0x00  //[3:2] giph display on no scan�׶�p1/p2����ֵ
#define  DAT_GIPH_DPON_SCAN          0x00  //[1:0] giph display on scan�׶�p1/p2����ֵ
#define  rAFE_GIPH_P1_P2_CFG         ((DAT_GIPH_PHASE3<<10)\ 
                                     +(DAT_GIPH_PHASE2<<8)\                                          
                                     +(DAT_GIPH_PHASE1<<6)\
                                     +(DAT_GIPH_PHASE0<<4)\
                                     +(DAT_GIPH_DPON_NO_SCAN<<2)\
                                     +(DAT_GIPH_DPON_SCAN<<0))
//0x26  38
#define  DAT_GIPL_PHASE3             0x00  //[11:10] gipl display off phase3�׶�p1/p2����ֵ(0:ȫ����1:Hiz; 2:GND)
#define  DAT_GIPL_PHASE2             0x00  //[9:8] gipl display off phase2�׶�p1/p2����ֵ(0:ȫ����1:Hiz; 2:GND)
#define  DAT_GIPL_PHASE1             0x00  //[7:6] gipl display off phase1�׶�p1/p2����ֵ
#define  DAT_GIPL_PHASE0             0x00  //[5:4] gipl display off phase0�׶�p1/p2����ֵ
#define  DAT_GIPL_DPON_NO_SCAN       0x00  //[3:2] gipl display on no scan�׶�p1/p2����ֵ
#define  DAT_GIPL_DPON_SCAN          0x00  //[1:0] gipl display on scan�׶�p1/p2����ֵ
#define  rAFE_GIPL_P1_P2_CFG         ((DAT_GIPL_PHASE3<<10)\  
                                     +(DAT_GIPL_PHASE2<<8)\
                                     +(DAT_GIPL_PHASE1<<6)\
                                     +(DAT_GIPL_PHASE0<<4)\
                                     +(DAT_GIPL_DPON_NO_SCAN<<2)\
                                     +(DAT_GIPL_DPON_SCAN<<0))  



//0x27  39
#define  DAT_VOM_DPOFF_NO_SCAN       0x00  //[15:14] vom opt display off no scan�׶�p1/p2����ֵ
#define  DAT_VOM_DPOFF_SCAN          0x00  //[13:12] vom opt display off scan�׶�p1/p2����ֵ
#define  DAT_VOM_DPON_NO_SCAN        0x00  //[11:10] vom opt display on no scan�׶�p1/p2����ֵ
#define  DAT_VOM_DPON_SCAN           0x00  //[9:8]   vom opt display on scan�׶�p1/p2����ֵ
#define  DAT_SD_DPOFF_NO_SCAN        0x00  //[7:6] source display off no scan�׶�p1/p2����ֵ
#define  DAT_SD_DPOFF_SCAN           0x00  //[5:4] source display off scan�׶�p1/p2����ֵ
#define  DAT_SD_DPON_NO_SCAN         0x00  //[3:2] source display on no scan�׶�p1/p2����ֵ
#define  DAT_SD_DPON_SCAN            0x00  //[1:0] source display on scan�׶�p1/p2����ֵ
#define  rAFE_SD_VOM_OPT_P1_P2_CFG   ((DAT_VOM_DPOFF_NO_SCAN<<14)\
                                     +(DAT_VOM_DPOFF_SCAN<<12)\
                                     +(DAT_VOM_DPON_NO_SCAN<<10)\
                                     +(DAT_VOM_DPON_SCAN<<8)\
                                     +(DAT_SD_DPOFF_NO_SCAN<<6)\
                                     +(DAT_SD_DPOFF_SCAN<<4)\
                                     +(DAT_SD_DPON_NO_SCAN<<2)\
                                     +(DAT_SD_DPON_SCAN<<0))  
                                     
//0x28  40
#define  DAT_SX_DPOFF_NO_SCAN        0x00  //[7:6]sx display off no scan�׶�p1/p2����ֵ
#define  DAT_SX_DPOFF_SCAN           0x00  //[5:4]sx display off scan�׶�p1/p2����ֵ
#define  DAT_SX_DPON_NO_SCAN         0x00  //[3:2]sx display on no scan�׶�p1/p2����ֵ
#define  DAT_SX_DPON_SCAN            0x00  //[1:0]sx display on scan�׶�p1/p2����ֵ
#define  rAFE_SX_P1_P2_CFG           ((DAT_SX_DPOFF_NO_SCAN<<6)\                                          
                                     +(DAT_SX_DPOFF_SCAN<<4)\
                                     +(DAT_SX_DPON_NO_SCAN<<2)\
                                     +(DAT_SX_DPON_SCAN<<0))  
//0x29  41
#define  DAT_MOUT_GIPH_PHASE3_CFG    0x00  //[11:10]mout vgho display off phase3 config
#define  DAT_MOUT_GIPH_PHASE2_CFG    0x00  //[9:8]mout vgho display off phase3 config
#define  DAT_MOUT_GIPH_PHASE1_CFG    0x00  //[7:6]mout vgho display off phase3 config
#define  DAT_MOUT_GIPH_PHASE0_CFG    0x00  //[5-4]mout vgho display off phase3 config
#define  DAT_MOUT_GIPH_DPON_NO_SCAN_CFG   0x00  //[3-2]mout vgho display on no scan config
#define  DAT_MOUT_GIPH_DPON_SCAN_CFG      0x00  //[1-0]mout vgho display on scan config
#define  rAFE_MOUT_GIPH_CFG          ((DAT_MOUT_GIPH_PHASE3_CFG<<10)\   
                                     +(DAT_MOUT_GIPH_PHASE2_CFG<<8)\
                                     +(DAT_MOUT_GIPH_PHASE1_CFG<<6)\
                                     +(DAT_MOUT_GIPH_PHASE0_CFG<<4)\
                                     +(DAT_MOUT_GIPH_DPON_NO_SCAN_CFG<<2)\
                                     +(DAT_MOUT_GIPH_DPON_SCAN_CFG<<0))  

//0x2A  42
#define  DAT_MOUT_GIPL_PHASE3_CFG    0x00  //[11:10]mout vgho display off phase3 config
#define  DAT_MOUT_GIPL_PHASE2_CFG    0x00  //[9:8]mout vgho display off phase3 config
#define  DAT_MOUT_GIPL_PHASE1_CFG    0x00  //[7:6]mout vgho display off phase3 config
#define  DAT_MOUT_GIPL_PHASE0_CFG    0x00  //[5-4]mout vgho display off phase3 config
#define  DAT_MOUT_GIPL_DPON_NO_SCAN_CFG   0x00  //[3-2]mout vgho display on no scan config
#define  DAT_MOUT_GIPL_DPON_SCAN_CFG      0x00  //[1-0]mout vgho display on scan config
#define  rAFE_MOUT_GIPL_CFG          ((DAT_MOUT_GIPL_PHASE3_CFG<<10)\   
                                     +(DAT_MOUT_GIPL_PHASE2_CFG<<8)\
                                     +(DAT_MOUT_GIPL_PHASE1_CFG<<6)\
                                     +(DAT_MOUT_GIPL_PHASE0_CFG<<4)\
                                     +(DAT_MOUT_GIPL_DPON_NO_SCAN_CFG<<2)\
                                     +(DAT_MOUT_GIPL_DPON_SCAN_CFG<<0)) 

//0x2B  43
#define  DAT_GOUT_GIPH_PHASE3_CFG    0x00  //[11:10]gout vgho display off phase3 config
#define  DAT_GOUT_GIPH_PHASE2_CFG    0x00  //[9:8]gout vgho display off phase3 config
#define  DAT_GOUT_GIPH_PHASE1_CFG    0x00  //[7:6]gout vgho display off phase3 config
#define  DAT_GOUT_GIPH_PHASE0_CFG    0x00  //[5-4]gout vgho display off phase3 config
#define  DAT_GOUT_GIPH_DPON_NO_SCAN_CFG   0x00  //[3-2]gout vgho display on no scan config
#define  DAT_GOUT_GIPH_DPON_SCAN_CFG      0x00  //[1-0]gout vgho display on scan config
#define  rAFE_GOUT_GIPH_CFG          ((DAT_GOUT_GIPH_PHASE3_CFG<<10)\   
                                     +(DAT_GOUT_GIPH_PHASE2_CFG<<8)\
                                     +(DAT_GOUT_GIPH_PHASE1_CFG<<6)\
                                     +(DAT_GOUT_GIPH_PHASE0_CFG<<4)\
                                     +(DAT_GOUT_GIPH_DPON_NO_SCAN_CFG<<2)\
                                     +(DAT_GOUT_GIPH_DPON_SCAN_CFG<<0))  

//0x2C  44
#define  DAT_GOUT_GIPL_PHASE3_CFG    0x00  //[11:10]gout vgho display off phase3 config
#define  DAT_GOUT_GIPL_PHASE2_CFG    0x00  //[9:8]gout vgho display off phase3 config
#define  DAT_GOUT_GIPL_PHASE1_CFG    0x00  //[7:6]gout vgho display off phase3 config
#define  DAT_GOUT_GIPL_PHASE0_CFG    0x00  //[5-4]gout vgho display off phase3 config
#define  DAT_GOUT_GIPL_DPON_NO_SCAN_CFG   0x00  //[3-2]gout vgho display on no scan config
#define  DAT_GOUT_GIPL_DPON_SCAN_CFG      0x00  //[1-0]gout vgho display on scan config
#define  rAFE_GOUT_GIPL_CFG          ((DAT_GOUT_GIPL_PHASE3_CFG<<10)\   
                                     +(DAT_GOUT_GIPL_PHASE2_CFG<<8)\
                                     +(DAT_GOUT_GIPL_PHASE1_CFG<<6)\
                                     +(DAT_GOUT_GIPL_PHASE0_CFG<<4)\
                                     +(DAT_GOUT_GIPL_DPON_NO_SCAN_CFG<<2)\
                                     +(DAT_GOUT_GIPL_DPON_SCAN_CFG<<0)) 
                                     
//0x2D  45                                     
#define  DAT_ALL_GATE_ON_L_CFG       0x0000  //[15:0] allgate on ��16bit����ֵ
#define  rALL_GATE_ON_L_CFG          (DAT_ALL_GATE_ON_L_CFG<<0)

//0x2E  46 
#define  DAT_ALL_GATE_OFF_L_CFG      0x0000  //[15:0] allgate off ��16bit����ֵ
#define  rALL_GATE_OFF_L_CFG         (DAT_ALL_GATE_OFF_L_CFG<<0)

//0x2F  47
#define  DAT_ALL_GATE_STOP_L_CFG     0x0000  //[15:0] allgate stop ��16bit����ֵ
#define  rALL_GATE_STOP_L_CFG        (DAT_ALL_GATE_STOP_L_CFG<<0)

//0x30  48
#define  DAT_ALL_GATE_ON_H_CFG       0x0000  //[5:4] allgate on   ��2bit����ֵ
#define  DAT_ALL_GATE_OFF_H_CFG      0x0000  //[3:2] allgate off  ��2bit����ֵ
#define  DAT_ALL_GATE_STOP_H_CFG     0x0000  //[1:0] allgate stop ��2bit����ֵ

#define  rALL_GATE_H_CFG             ((DAT_ALL_GATE_ON_H_CFG<<4)\                                          
                                     +(DAT_ALL_GATE_OFF_H_CFG<<2)\
                                     +(DAT_ALL_GATE_STOP_H_CFG<<0)) 

//0x31  49
#define  DAT_RPT_RAWDATA_NUM         0x120  //[9:0] �ϱ�Rawdata�ĸ���
#define  rRPT_RAWDATA_NUM            (DAT_RPT_RAWDATA_NUM<<0)                                      

//0x32  50
#define  DAT_CB_ADJUST_THLD_TP        0x0000 //[15:0] Ӳ��CBУ����ֵ��Ŀ��ֵ��
#define  rCB_ADJUST_THLD_TP          (DAT_CB_ADJUST_THLD_TP<<0)

//0x33  51
#define  DAT_TEST_MODE_KEY_NUM       0x00    //[11:10]����ģʽ��ѡ��key����                                    
#define  DAT_TEST_MODE_TP_CH_NUM     0x000   //[9:1]  ����ģʽ��ѡ��tpͨ����
#define  DAT_TEST_MODE_TP_KEY_SEL    0x0     //[0], ͨ��ѡ��, 0:tp; 1:key
#define  rTEST_MODE_FLAG             ((DAT_TEST_MODE_KEY_NUM<<10)\                                          
                                     +(DAT_TEST_MODE_TP_CH_NUM<<1)\
                                     +(DAT_TEST_MODE_TP_KEY_SEL<<0)) 
//0x34  52
#define  DAT_PRESCAN_TIME            0x0000  //[15:0] ����Ԥɨ��ʱ��
#define  rPRESCAN_TIME               DAT_PRESCAN_TIME

//0x35  53
#define  DAT_DISCHARGE_TIME          0x0000  //[15:0] ����ɨ���ŵ�ʱ��
#define  rDISCHARGE_TIME             DAT_DISCHARGE_TIME

//0x36  54 
#define  DAT_SADC_DLY_CRL            0x0     //[15] SADC Comparator delay control, 1:enable   0:disable
#define  DAT_KEY_RF_SEL              0x3     //[14:13] Key Rf resistance sel, 0:210K  1:140K  2:70K   3:off
#define  DAT_RF_SEL                  0x3     //[12:11] Rf resistance sel,     0:210K  1:140K  2:70K   3:off
#define  DAT_RIN_RF_SEL              0x3     //[10:09] Rin Rf resistance sel, 0:210K  1:140K  2:70K   3:off 
#define  DAT_RX_AFD                  0x0     //[8] pad state when channel disable@ AFD, 0:HZ or PL  1:AFD
#define  DAT_RX_HZ                   0x0     //[7] pad state when channel disable@ HZ,  0:low  1:high
#define  DAT_BIAS_CURRENT            0x1     //[6:5] afe bias current adjust, 0:2.5u 1:5.0u 2:7.5u  3:10u
#define  DAT_TEST_EN                 0x0     //[4:0] test enable
#define  rANA_STATIC_CFG0           ((DAT_SADC_DLY_CRL<<15)\           
                                    +(DAT_KEY_RF_SEL<<13)\                
                                    +(DAT_RF_SEL<<11)\                    
                                    +(DAT_RIN_RF_SEL<<9)\                 
                                    +(DAT_RX_AFD<<8)\                    
                                    +(DAT_RX_HZ<<7)\                     
                                    +(DAT_BIAS_CURRENT<<5)\
                                    +(DAT_TEST_EN<<0))
                                                      
//0x37  55
#define  DAT_SADC_RES_VREF_GND_SEL   0x3    //[15:13] res-array sel: 0:72/90vref 1:74/90vref 2:76/90vref 3:78/90vref
                                            //                       4:80/90vref 5:82/90vref 6:84/90vref 7:86/90vref
#define  DAT_SADC_RES_VREF_POW_SEL   0x4    //[12:10] res-array sel: 0:72/90vref 1:74/90vref 2:76/90vref 3:78/90vref
                                            //                       4:80/90vref 5:82/90vref 6:84/90vref 7:86/90vref
#define  DAT_CB_OFFSET               0x000  //[9:7] CB offset
#define  DAT_KEY_CF_SEL              0x5    //[6:3] Key freeback cap sel, 0:1.8p 1:2.4p 2:3.0p 3:3.6p 4:4.2p 5:4.8p 6:5.4p 7:6.0p
#define  DAT_CF_SEL                  0x5    //[2:0] CF freeback cap sel, 0:1.8p 1:2.4p 2:3.0p 3:3.6p 4:4.2p 5:4.8p 6:5.4p 7:6.0p
#define  rANA_STATIC_CFG1            ((DAT_SADC_RES_VREF_GND_SEL<<13)\                               
                                     +(DAT_SADC_RES_VREF_POW_SEL<<10)\  
                                     +(DAT_CB_OFFSET<<7)\               
                                     +(DAT_KEY_CF_SEL<<3)\              
                                     +(DAT_CF_SEL<<0))                  
//0x38  56
#define  DAT_ABSEL_AFE               0x01   //[9:8]afe bias current sel: 0:x0.5; 1:x1(default 5uA); 2:x1.5; 3:x2
#define  DAT_IBSEL_ADC               0x01   //[7:6]sadc bias current sel:0:x0.5; 1:x1(default 5uA); 2:x1.5; 3:x2
#define  DAT_IBSEL_VREFTP            0x01   //[5:4]vref/cdd5/halfvref bias current sel:0:x0.5; 1:x1(default 5uA); 2:x1.5; 3:x2
#define  DAT_IZTAT_SEL               0x06   //[3:0]ztat bias current sel: 0:0.875uA; 1:0.9375uA; 2:1uA 3:1.0625uA 4:1.125uA;5:1.1875uA
                                            // 6:1.25uA(default); 7:1.3125uA; 8:1.375uA; 9:1.4375uA 10:1.5uA
                                            // 11:1.5625uA; 12:1.625uA; 13:1.6875uA; 14:1.75uA; 15:1.8125uA
#define  rANA_STATIC_CFG2            ((DAT_ABSEL_AFE<<8)\                               
                                     +(DAT_IBSEL_ADC<<6)\  
                                     +(DAT_IBSEL_VREFTP<<4)\               
                                     +(DAT_IZTAT_SEL<<0))   
//0x39  57
//#define  DAT_EN_TXSLR                0x0   //[12]1:enable TX slew rate control function
#define  DAT_TXSLR                   0x00  //[11:10]0,1,2,3:Risi/falling time 80ns,120ns,160ns,200ns
#define  DAT_HALFVERF_SEL            0x7   //[9:6]halfvref valtage sel: 0:0.7v 1:0.85v 2:1v 3:1.1.5v 4:1.3v
                                           // 5:1.45v 6:1.6v 7:1.75v(default) 8:1.9v 9:2.05v 10:2.2v 11:2.35v
                                           // 12:2.5v 13:2.65v 14:2.8v 15:2.95v
#define  DAT_VDD5_SEL                0x5   //[5:3]VDD5  voltage: 0:2v 1:2.5v 2:3V 3:3.5v 4:4v 5:4.5v(default)6:5v 7:.5.5v
#define  DAT_VREF_TP_SEL             0x3   //[2:0]Vref_TP  voltage: 0:2v 1:2.5v 2:3V 3:3.5v(default) 4:4v 5:4.5v6:5v 7:.5.5v                                           
#define  rANA_STATIC_CFG3            ((DAT_TXSLR<<10)\  
                                     +(DAT_VDD5_SEL<<6)\
                                     +(DAT_VREF_TP_SEL<<3)\  
                                     +(DAT_VREF_TP_SEL<<0))   

//0x3a  58
#define  DAT_P0_SORT2_SEL            0x0  //[]15:12�ź�ѡ��
                                          //0:sh_s0  1:sh_s1 2:sh_s2 3:sh_rst
#define  DAT_P0_SORT1_SEL            0x0  //[11:8]�ź�ѡ��
                                          //0:ca_rst 1:ca_p1 2:ca_p4 3:ca_p6 4:ca_p7 5:ca_p10 
                                          //6:cb_dac0 7:cb_dac1 8:cb_dac2 9:cb_dac3 10:cb_dac4
#define  DAT_P0_SORT0_SEL            0x0  //[7:4]�ź�ѡ��:
                                          //0:lvd_det 1:lcd_run 2:lcd_busy 3:stb_start 4:scan_start
                                          //5:tp_scan 6:tp_busy 7:frame end 8:aram_ready 9:mon_det 
#define  DAT_P0_SORT_SEL             0x0  //[3:0]����ѡ��
#define  rTEST_P0_CFG0               ((DAT_P0_SORT2_SEL<<12)\                               
                                     +(DAT_P0_SORT1_SEL<<8)\  
                                     +(DAT_P0_SORT0_SEL<<4)\
                                     +(DAT_P0_SORT_SEL<<0))  
//0x3b  59
#define  DAT_P0_SORT6_SEL            0x0  //[]15:12�ź�ѡ��                                     
#define  DAT_P0_SORT5_SEL            0x0  //[11:8]�ź�ѡ��
#define  DAT_P0_SORT4_SEL            0x0  //[7:4]�ź�ѡ��
#define  DAT_P0_SORT3_SEL            0x0  //[3:0]�ź�ѡ��
#define  rTEST_P0_CFG1               ((DAT_P0_SORT6_SEL<<12)\                               
                                     +(DAT_P0_SORT5_SEL<<8)\  
                                     +(DAT_P0_SORT4_SEL<<4)\
                                     +(DAT_P0_SORT3_SEL<<0))  

//0x3c  60            
#define  DAT_TEST_PIN0_SORTA_SEL     0x0000 //[15:12]�ź�ѡ��
#define  DAT_P0_SORT9_SEL            0x0  //[11:8]�ź�ѡ��
#define  DAT_P0_SORT8_SEL            0x0  //[7:4]�ź�ѡ��
#define  DAT_P0_SORT7_SEL            0x0  //[3:0]�ź�ѡ��
#define  rTEST_P0_CFG2               ((DAT_TEST_PIN0_SORTA_SEL<<8)\
                                     +(DAT_P0_SORT9_SEL<<8)\  
                                     +(DAT_P0_SORT8_SEL<<4)\
                                     +(DAT_P0_SORT7_SEL<<0))  

//0x3d  61
#define  DAT_P1_SORT2_SEL            0x0  //[]15:12�ź�ѡ��
#define  DAT_P1_SORT1_SEL            0x0  //[11:8]�ź�ѡ��                                         
#define  DAT_P1_SORT0_SEL            0x0  //[7:4]�ź�ѡ��:
#define  DAT_P1_SORT_SEL             0x0  //[3:0]����ѡ��
#define  rTEST_P1_CFG0               ((DAT_P1_SORT2_SEL<<12)\                               
                                     +(DAT_P1_SORT1_SEL<<8)\  
                                     +(DAT_P1_SORT0_SEL<<4)\
                                     +(DAT_P1_SORT_SEL<<0))  

//0x3e  62
#define  DAT_P1_SORT6_SEL            0x0  //[]15:12�ź�ѡ��                                     
#define  DAT_P1_SORT5_SEL            0x0  //[11:8]�ź�ѡ��
#define  DAT_P1_SORT4_SEL            0x0  //[7:4]�ź�ѡ��
#define  DAT_P1_SORT3_SEL            0x0  //[3:0]�ź�ѡ��
#define  rTEST_P1_CFG1               ((DAT_P1_SORT6_SEL<<12)\                               
                                     +(DAT_P1_SORT5_SEL<<8)\  
                                     +(DAT_P1_SORT4_SEL<<4)\
                                     +(DAT_P1_SORT3_SEL<<0))  

//0x3f  63   
#define  DAT_PIN1_SORTA_SEL          0x0000 //[15:12]�ź�ѡ��
#define  DAT_P1_SORT9_SEL            0x0  //[11:8]�ź�ѡ��
#define  DAT_P1_SORT8_SEL            0x0  //[7:4]�ź�ѡ��
#define  DAT_P1_SORT7_SEL            0x0  //[3:0]�ź�ѡ��
#define  rTEST_P1_CFG2               ((DAT_PIN1_SORTA_SEL<<12)\  
                                     +(DAT_P1_SORT9_SEL<<8)\ 
                                     +(DAT_P1_SORT8_SEL<<4)\
                                     +(DAT_P1_SORT7_SEL<<0))  


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//0x40  64  
#define  DAT_SCAN_EN                 0x0    //[15] 0:�ر�; 1: keyͨ����������ģʽ;                             
#define  DAT_ADC_DIFF_EN             0x0    //[14] 0:������adc diff max; 1:����mcap diffģ�飬���mcap_diff_mode
//#define  DAT_DATAPROC_MODE           0x1    //[13] 0:�ر�mixer�Ժ�sum֮ǰ�����ݴ���Ԫ; 1:��������   
#define  DAT_MIX_LEN_MODE            0x1    //[4]  0:6������; 1:8���������㷨����TX_clk����175K,����6����������
//#define  DAT_BASE_EN                 0x0    //[3]  0:�ر�key��Base����; 1:����  ��ɾ��
#define  DAT_RAW_GAIN_EN             0x0    //[2]  0:������; 1:�������洦��
#define  DAT_OVERFLOW_CLR_EN         0x0    //[1]  0:��ʹ��; 1:������ʹ��
#define  DAT_OVERFLOW_EN             0x0    //[0]  0:������ʹ��                        
#define  rMCAP_SCAN_CFG              ((DAT_SCAN_EN<<15)\  
                                     +(DAT_ADC_DIFF_EN<<14)\
                                     +(DAT_MIX_LEN_MODE<<4)\
                                     +(DAT_RAW_GAIN_EN<<2)\
                                     +(DAT_OVERFLOW_CLR_EN<<1)\
                                     +(DAT_OVERFLOW_EN<<0))  

//0x41  65  
#define  DAT_KEY_NUM_ERROR_FLAG      0x0  //[8:5]RO: 3;2;1;0 :key1;2;3;4ɨ�������������
#define  DAT_KEY_ERROR_FLAG          0x0  //[4]RO: �ӵĳ���С�ڻ����㷨Ҫ����1����
#define  DAT_MCAP_DIFF_MODE          0x0  //[3]0:adc�������ݾ���diff����; 1:����mixer�ٽ���diff����
#define  DAT_MCAP_OVERFLOW_CLR_FLAG  0x0  //[2]������ʱ,����������
#define  DAT_MCAP_OVERFLOW_FLAG      0x0  //[1]������ʱ,��ǰ֡�����
#define  DAT_MCAP_DONE               0x0  //[0]�����ã�д1���                
#define  rMCAP_SCANSR                ((DAT_KEY_NUM_ERROR_FLAG<<5)\  
                                     +(DAT_KEY_ERROR_FLAG<<4)\
                                     +(DAT_MCAP_DIFF_MODE<<3)\
                                     +(DAT_MCAP_OVERFLOW_CLR_FLAG<<2)\
                                     +(DAT_MCAP_OVERFLOW_FLAG<<1)\
                                     +(DAT_MCAP_DONE<<0))  

//0x42 66
#define  DAT_MCAP_LPFIR_SUM_NUM      0x0001  //[9:5]����ģʽ:num = �ز�����x����������/4-FIRϵ�����ȣ�Freerun������16;�رյ�ͨ�˲�������˲�ʱ����������256
#define  rMCAP_LPFIR_SUM_NUM         (DAT_MCAP_LPFIR_SUM_NUM<<0)
                                     
//0x43 67
#define  DAT_GAIN_COF                0x1  //[15:8]raw_gain_en��Чʱ��rawdata����rawdata*gaincof>>raw_shif_cof����
#define  DAT_RAW_SHIFT_COF           0x0  //[7:0] raw_gain_en��Чʱ��rawdata����rawdata*gaincof>>raw_shif_cof����
#define  rRAWSHIFTCAF                ((DAT_GAIN_COF<<8)\  
                                     +(DAT_RAW_SHIFT_COF<<0))   

//0x44 68
#define  DAT_RAWDATA_OFFSET_L        0x0  //[15:0]rawdata��ֵͳһ��ȥ��ֵ�����rawdata���ڸ�offset,��Ϊ0.
#define  rRAWDATA_OFFSET_L           (DAT_RAWDATA_OFFSET_L<<0)

//0x45 69
#define  DAT_MACP_DIFF_SHIFT_COF     0x00 //[7:4]����key diff_noise��shift����
//#define  DAT_RAWDATA_OFFSET_H        0x0  //[3]offset��λ
//#define  DAT_DATA_INV                0x0  //[2]1:���ط���
//#define  DAT_ADC_DUMMY_SHUF          0x0  //[1]1:��dummy�ڼ䣬������ADCʱ��0:����
//#define  DAT_ADC_MSB_INV             0x1  //[0]1:��λȡ��
#define  rADC_CFG                    (DAT_MACP_DIFF_SHIFT_COF<<4)

//0x46 70  �Ĵ�����Ч
#define  DAT_ADC_DATA_VLD0           0x0  //[12]1:�ɼ���Ч; 0:�ɼ���Ч
#define  DAT_ADC_DATA0               0x0  //[11:0]ͨ��0 ADC DATA,����һ�����ݲɼ������ݻ���¡�
#define  rADC_DATA0                  ((DAT_ADC_DATA_VLD0<<12)\  
                                     +(DAT_ADC_DATA0<<0))    

//0x47 71
#define  DAT_MCAP_INIT_SAMPLE        0x0  //[9:0]����TX_clk��ʼλ�ã�������λ
#define  rMCAP_INIT_SAMPL_CFG        (DAT_MCAP_INIT_SAMPLE<<0)

//0x48 72
#define  DAT_OVERFLOW_THR            0x3E0  //[11:0] ADC�����������ֵ 
#define  rOVERFLOW_THR               (DAT_OVERFLOW_THR<<0)

//0x49 73
#define  DAT_UNDERFLOW_THR           0x0  //[11:0] ADC�����������ֵ 
#define  rUNDERFLOW_THR              (DAT_UNDERFLOW_THR<<0)

//0x4A 74
#define  DAT_OVERFLOW_UPBOUND        0xA  //[11:0] ���������Χ����Ϊһ�������
#define  rOVERFLOW_UPBOUND           (DAT_OVERFLOW_UPBOUND<<0)

//0x4B 75
#define  DAT_OVER_POINT_FRAME        0x20  //[11:0] ��������ĵ���ڸ�ֵʱ�����������־
#define  rOVER_POINT_FRAME           (DAT_OVER_POINT_FRAME<<0)

//0x4C 76
#define  DAT_NORMAL_SIGNAL_UPTHR     0x258 //[11:0]����������ֵ
#define  rNORMAL_SIGNAL_UPTHR        (DAT_NORMAL_SIGNAL_UPTHR<<0)

//0x4D 77
#define  DAT_NORMAL_SIGNAL_DWTHR     0x190 //[11:0]����������ֵ
#define  rNORMAL_SIGNAL_DWTHR        (DAT_NORMAL_SIGNAL_DWTHR<<0)

//0x4E 78
#define  DAT_OVERFLOW_CLR_FRAMENUM   0x64   //[7:0] �������������ĵ���ڸ�ֵʱ��������������־
#define  rOVERFLOW_CLR_FRAMENUM     (DAT_OVERFLOW_CLR_FRAMENUM<<0)

//0x4F 79
#define  DAT_MCAP_HBFIR_EN           0x01  //[15]mcap hb firʹ���ź�.0:�ر�;1:����
#define  DAT_MCAP_LPFIR_SUM_START    0x0E  //[14:10]Sum_Start = FIR������0��ʼ��ʵ��ֵΪ����ֵ��1
//#define  DAT_MCAP_LPFIR_SUM_NUM      0x06  //[9:5]����ģʽ:num = �ز�����x����������/4-FIRϵ�����ȣ�Freerun������16
#define  DAT_MCAP_LPFIR_EN           0x1   //[4] 1:ʹ��
#define  DAT_MCAP_LPFIR_TOP          0xE   //[3:0] LP FIR����
#define  rMCAP_LPFIR_CFG             ((DAT_MCAP_LPFIR_SUM_START<<10)\  
                                     +(DAT_MCAP_LPFIR_EN<<4)\
                                     +(DAT_MCAP_LPFIR_TOP<<0))  

//0x50 80
#define  DAT_MCAP_LPFIR_COF0        0x104  //[15:0] LP FIR ϵ��0  
#define  rMCAP_LPFIR_COF0           (DAT_MCAP_LPFIR_COF0<<0)

//0x51 81
#define  DAT_MCAP_LPFIR_COF1        0x296  //[15:0] LP FIR ϵ��1  
#define  rMCAP_LPFIR_COF1           (DAT_MCAP_LPFIR_COF1<<0)

//0x52 82
#define  DAT_MCAP_LPFIR_COF2        0x4E5  //[15:0] LP FIR ϵ��2  
#define  rMCAP_LPFIR_COF2           (DAT_MCAP_LPFIR_COF2<<0)

//0x53 83
#define  DAT_MCAP_LPFIR_COF3        0x7C3  //[15:0] LP FIR ϵ��3  
#define  rMCAP_LPFIR_COF3           (DAT_MCAP_LPFIR_COF3<<0)

//0x54 84
#define  DAT_MCAP_LPFIR_COF4        0xACD  //[15:0] LP FIR ϵ��4
#define  rMCAP_LPFIR_COF4           (DAT_MCAP_LPFIR_COF4<<0)

//0x55 85
#define  DAT_MCAP_LPFIR_COF5        0xD84  //[15:0] LP FIR ϵ��5 
#define  rMCAP_LPFIR_COF5           (DAT_MCAP_LPFIR_COF5<<0)

//0x56 86
#define  DAT_MCAP_LPFIR_COF6        0xF65  //[15:0] LP FIR ϵ��6  
#define  rMCAP_LPFIR_COF6           (DAT_MCAP_LPFIR_COF6<<0)

//0x57 87
#define  DAT_MCAP_LPFIR_COF7        0x1011 //[15:0] LP FIR ϵ��7  
#define  rMCAP_LPFIR_COF7           (DAT_MCAP_LPFIR_COF7<<0)

//0x58  88
#define  DAT_CB_ADJUST_THLD_KEY     0x0000 //[15:0] Ӳ��CBУ��key��ֵ��Ŀ��ֵ��
#define  rCB_ADJUST_THLD_KEY        (DAT_CB_ADJUST_THLD_KEY<<0)

typedef enum
{
    SS_WORK = 1,    // SS: System State
    SS_FACTORY  = 3,
    SS_UPGRADE1 = 5,
    SS_UPGRADE2 = 6,
    SS_SW_RESET = 7,
    SS_MAX
} ENUM_SysState;
    
#if CB_AFE_SCAN_MODE == 0            //ɨ�跽ʽ1
#define DAT_TP_FRAME_NUM   1
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       6
#define DAT_BUSY_ID2       1
#define DAT_BUSY_ID3       6
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       6
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       6
    
#elif CB_AFE_SCAN_MODE == 1          //ɨ�跽ʽ2
#define DAT_TP_FRAME_NUM   2
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       4
#define DAT_BUSY_ID2       7
#define DAT_BUSY_ID3       1
#define DAT_BUSY_ID4       4
#define DAT_BUSY_ID5       7
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       4
    
#elif CB_AFE_SCAN_MODE == 2          //ɨ�跽ʽ3
#define DAT_TP_FRAME_NUM   3
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       3
#define DAT_BUSY_ID2       5
#define DAT_BUSY_ID3       7
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       3
#define DAT_BUSY_ID6       5
#define DAT_BUSY_ID7       7
    
#elif CB_AFE_SCAN_MODE == 3          //ɨ�跽ʽ4
#define DAT_TP_FRAME_NUM   3
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       3
#define DAT_BUSY_ID2       5
#define DAT_BUSY_ID3       7
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       3
#define DAT_BUSY_ID6       5
#define DAT_BUSY_ID7       7
    
    
#elif CB_AFE_SCAN_MODE == 4          //ɨ�跽ʽ5
#define DAT_TP_FRAME_NUM   1
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       2
#define DAT_BUSY_ID2       1
#define DAT_BUSY_ID3       2
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       2
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       2
    
#elif CB_AFE_SCAN_MODE == 5          //ɨ�跽ʽ6
#define DAT_TP_FRAME_NUM   1
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       6
#define DAT_BUSY_ID2       1
#define DAT_BUSY_ID3       6
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       6
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       6
 
#elif CB_AFE_SCAN_MODE == 6          //ɨ�跽ʽ7
#define DAT_TP_FRAME_NUM   1
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       6
#define DAT_BUSY_ID2       1
#define DAT_BUSY_ID3       6
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       6
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       6 

#elif CB_AFE_SCAN_MODE == 7          //ɨ�跽ʽ8
#define DAT_TP_FRAME_NUM   7
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       2
#define DAT_BUSY_ID2       3
#define DAT_BUSY_ID3       4
#define DAT_BUSY_ID4       5
#define DAT_BUSY_ID5       6
#define DAT_BUSY_ID6       7
#define DAT_BUSY_ID7       8 
    
#endif
    
#define CB_TP_FRAME_NUM     DAT_TP_FRAME_NUM
#define CB_BUSY_ID0         DAT_BUSY_ID0
#define CB_BUSY_ID1         DAT_BUSY_ID1
#define CB_BUSY_ID2         DAT_BUSY_ID2
#define CB_BUSY_ID3         DAT_BUSY_ID3
#define CB_BUSY_ID4         DAT_BUSY_ID4
#define CB_BUSY_ID5         DAT_BUSY_ID5
#define CB_BUSY_ID6         DAT_BUSY_ID6
#define CB_BUSY_ID7         DAT_BUSY_ID7

typedef enum
{
    AFE_120HZ_MODE    = 0,    
    AFE_60HZ_MODE     = 1,
    AFE_FREERUN_MODE = 2
} ENUM_AFE_MODE;





/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/


/*******************************************************************************
* Global function prototypes
*******************************************************************************/

#endif // _CFG_SYSTEM_H_

