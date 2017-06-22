/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
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
#define PWR_EN             1    //0:关闭上下电时序控制;1:开启上下电时序控制
#define SC_CLB_TIMES       8    // 校准次数 不能超过32次
#define CB_AFE_SCAN_MODE   0    //CB校正扫描方式
#define TEST_MCAP_CB       0    //测试mcap cb校正
#define TEST_MCAP_HWMON    1    //测试mcap hw mon
#define TEST_SAMP_INT      0    //调整mcap采集ADC数据初始相位.


//0x01 
#define  DAT_PANEL_MUX3_GROUPB_SEL    0x02    //[14:12] mux3 group b选择的列数: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:无效                            
#define  DAT_PANEL_MUX3_GROUPA_SEL    0x02    //[11:10] mux3 group a选择的列数: 0:G1; 1:G2 2:G3 3:G4 ,other:无效 
#define  DAT_PANEL_MUX2_GROUPB_SEL    0x03    //[09:07] mux2 group b选择的列数: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:无效   
#define  DAT_PANEL_MUX2_GROUPA_SEL    0x01    //[06:05] mux2 group a选择的列数: 0:G1; 1:G2 2:G3 3:G4 ,other:无效 
#define  DAT_PANEL_MUX1_GROUPB_SEL    0x04    //[04:02] mux1 group b选择的列数: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:无效 
#define  DAT_PANEL_MUX1_GROUPA_SEL    0x00    //[01:00] mux1 group a选择的列数: 0:G1; 1:G2 2:G3 3:G4 ,other:无效 
#define  rPANEL_MODE_CFG0             ((DAT_PANEL_MUX3_GROUPB_SEL<<12)\                           
                                      +(DAT_PANEL_MUX3_GROUPA_SEL<<10)\
                                      +(DAT_PANEL_MUX2_GROUPB_SEL<<7)\
                                      +(DAT_PANEL_MUX2_GROUPA_SEL<<5)\
                                      +(DAT_PANEL_MUX1_GROUPB_SEL<<2)\
                                      +(DAT_PANEL_MUX1_GROUPA_SEL<<0))

//0x02
#define  DAT_PANEL_MUX5_GROUPB_SEL    0x00    //[10:08] mux5 group b选择的列数: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:无效   
#define  DAT_PANEL_MUX5_GROUPA_SEL    0x04    //[07:05] mux5 group a选择的列数: 0:G1; 1:G2 2:G3 3:G4 4:不接屏
#define  DAT_PANEL_MUX4_GROUPB_SEL    0x01    //[04:02] mux4 group b选择的列数: 0:G5; 1:G6 2:G7 3:G8 4:G9, other:无效 
#define  DAT_PANEL_MUX4_GROUPA_SEL    0x03    //[01:00] mux4 group a选择的列数: 0:G1; 1:G2 2:G3 3:G4 ,other:无效 
#define  rPANEL_MODE_CFG1             ((DAT_PANEL_MUX5_GROUPB_SEL<<8)\                                  
                                      +(DAT_PANEL_MUX5_GROUPA_SEL<<5)\
                                      +(DAT_PANEL_MUX4_GROUPB_SEL<<2)\
                                      +(DAT_PANEL_MUX4_GROUPA_SEL<<0))

//0x03
#define  DAT_PANEL_MUX4_KEY_SEL      0x03    //[7:6] mux4 key键选择信号 
#define  DAT_PANEL_MUX3_KEY_SEL      0x02    //[5:4] mux3 key键选择信号 
#define  DAT_PANEL_MUX2_KEY_SEL      0x01    //[3:2] mux2 key键选择信号 
#define  DAT_PANEL_MUX1_KEY_SEL      0x00    //[1:0] mux1 key键选择信号 
#define  rPANEL_MODE_CFG2            ((DAT_PANEL_MUX4_KEY_SEL<<6)\                                  
                                     +(DAT_PANEL_MUX3_KEY_SEL<<4)\
                                     +(DAT_PANEL_MUX2_KEY_SEL<<2)\
                                     +(DAT_PANEL_MUX1_KEY_SEL<<0))

//0x04
#define  DAT_ADC_SHIFT_CLK_DIV       0x00  //[15:14] adc_shift_clk分频比，相对于afe_clk: 0:2分频；1:3分频; 2:4分频                                   
#define  DAT_ADC_CLK_DIV             0x00  //[13:11] adc_clk分频比，相对于afe_clk: 0-7: 2,4,6,8,10,12,14,16分频
#define  DAT_KEY_CB_ADJUST_DIR       0x00  //[10] key键校正方向 0:顺时针; 1:逆时针
#define  DAT_TP_CB_ADJUST_DIR        0x00  //[9]  tp_ch校正方向 0:顺时针; 1:逆时针
#define  DAT_AFE_EN_MODE             0x00  //[8]  使能stb_en,打开afe_en位置.1'b0:在scan_start后打开;1'b1:在stb_start后打开
#define  DAT_KEY_ENABLE              0x0F  //[7:4]4个key键使能，按bit位对应，1:使能       
#define  DAT_SHORT_TEST_ENABLE       0x00  //[3] short test功能使能: 1:使能
#define  DAT_PANEL_SHRINK_ENABLE     0x00  //[2] 屏幕缩小使能: 0:不使能,半屏采样mux5划分; 1:使能，屏幕采样mux4划分
#define  DAT_DISCONNECT_MODE         0x00  //[1] 不接屏使能: 0:不使能; 1:使能(不接屏模式有效)
#define  DAT_AFE_WORK_MODE           0x01  //[0] 工作模式:   0: test mode; 1: normal scan mode                                    
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
#define  DAT_ADC_DUMMY_SCAN_EN       0x01  //[15] Dummy扫描，ADC是否使能: 1:使能
#define  DAT_TP_STANDBY_ENABLE       0x01  //[14] tp_standby信号使能. 1:使能，使能后在该信号到来后进行CB shift操作 ,freerun固定为0，亮屏建议为0.                                 
#define  DAT_SSI_CLK_SEL             0x00  //[13:11] SSI时钟48M分频: 0:12M; 1:8M; 2:6M; 3:4.8M; 4:4M; 5:3.4M 6:3M
#define  DAT_ACC_ASR                 0x00  //[10:7] 累和结果右移bit数. 0:不移动; 1:右移1bit; ...9:右移9bit
#define  DAT_MEMORY_DATASEG          0x00  //[6:5]  mcu访问memory数据位宽: 0:0~15bit; 1:16~31bit; 2:32~47bit;3:48~63bit
#define  DAT_MEMORY_SEL              0x00  //[4:3]  mcu访问memory选择: 0: Tab Ram; 1: Acc Ram 2:Rpt Ram
#define  DAT_RPT_INFO_ENABLE         0x01  //[2]  上报info使能.            1:使能
#define  DAT_RPT_DIFF_NOISE_MAX_EN   0x01  //[1]  上报diffNoiseMax使能.    1:使能
#define  DAT_NOISE_DETECT_ENABLE     0x01  //[0]  diff noise 检测功能使能. 1:使能                                     
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
#define  DAT_AFE_SCAN_TIMES          0x06  //[10:3]  每个mux扫描次数，实际值为配置值加1
#define  DAT_AFE_SCAN_MODE           0x00  //[2:0]: Afe扫描方式:
                                           //0: 方式1: 单个坑内只扫描1个1/5屏的通道
                                           //1: 方式2: 单个坑内只扫描2或1个1/5屏的通道
                                           //2: 方式3: 单个坑内只扫描3或2个1/5屏的通道
                                           //3: 方式4: 单个坑内只扫描2或3个1/5屏的通道
                                           //4: 方式5: 单个大坑内只扫描5个1/5屏的通道
                                           //5: 方式6: 单个坑内只扫描5个1/5屏的通道，且多坑累加，段式
                                           //6: 方式7: 单个坑内只扫描2或1个mux,即mux9模式
                                           //7: 方式8: 仅扫描1个Mux,即Monitor,5个SX相连模式
#define  rAFE_SCAN_CFG0              ((DAT_KEY_SAMPL_INTERVAL_6_H<<11)\
                                     +(DAT_AFE_SCAN_TIMES<<3)\                                          
                                     +(DAT_AFE_SCAN_MODE<<0))
                                     
//0x07
#define  DAT_KEY_SAMPL_INTERVAL_6_L  0x00  //[15:11] key_sampl_interval_6[5:1]
#define  DAT_DOU_SAMPLE_MODE         0x00  //[10:9] 采样模式: 0:双边采样，模拟相减; 1:负边采样; 2:正边采样; 3:双边采样，数字相减                                   
#define  DAT_AFE_SIN_DOU_SCAN_SEL    0x00  //[8] SX扫描方式:  0:双边扫描(4种采样mode); 1: 单边扫描(仅1种单边采样)
#define  DAT_AFE_SCAN_SEG_NUM        0x04  //[0] 方式6，扫描段数
#define  rAFE_SCAN_CFG1              ((DAT_KEY_SAMPL_INTERVAL_6_L<<11)\
                                     +(DAT_DOU_SAMPLE_MODE<<9)\                                          
                                     +(DAT_AFE_SIN_DOU_SCAN_SEL<<8)\
                                     +(DAT_AFE_SCAN_SEG_NUM<<0))
//0x08
#define  DAT_SAMPLE_INTERVAL_6_LSB   0x00  //[15] key_sampl_interval_6[0]
#define  DAT_SCAN_MUX_DUMMY_NUM      0x00  //[14:10]Mux切换之间Dummy次数                                   
#define  DAT_SECTION_DUMMY_NUM       0x00  //[9:5]坑前Dummy次数
#define  DAT_SCAN_FRAME_DUMMY_NUM    0x00  //[4:0]Tp帧前Dummy次数                                     
#define  rAFE_DUMMY_SCAN_CFG         ((DAT_SAMPLE_INTERVAL_6_LSB<<15)\
                                     +(DAT_SCAN_MUX_DUMMY_NUM<<10)\                                          
                                     +(DAT_SECTION_DUMMY_NUM<<5)\
                                     +(DAT_SCAN_FRAME_DUMMY_NUM<<0))

//0x09     
#define  DAT_ADC_SAMPLE_POINT        0x00  //[15:10]ADC数据采样点
#define  DAT_BASE_TRACK_STEP         0x00  //[9:2]Monitor模式，Base跟踪，步进跟踪步长                                      
#define  DAT_BASE_TRACK_MODE         0x01  //[1] Monitor模式，Base跟踪方式: 0:步进跟踪; 1:原值跟踪
#define  DAT_BASE_TRACK_ENABLE       0x01  //[0] Montior模式，Base跟踪使能，1:使能                                     
#define  rAFE_BASE_TRACK_CFG         ((DAT_ADC_SAMPLE_POINT<<10)\
                                     +(DAT_BASE_TRACK_STEP<<2)\                                          
                                     +(DAT_BASE_TRACK_MODE<<1)\
                                     +(DAT_BASE_TRACK_ENABLE<<0))
//0x0A  10
#define  DAT_ACC_OFFSET              0x0000  //[15:0] ADC数据累加偏移量,基础值
#define  rACC_OFFSET                 (DAT_ACC_OFFSET<<0)

//0x0B  11
#define  DAT_TP_MONITOR_THERSHOLD    0x0000  //[15:0] 触摸检测时，TP通道的触摸阈值
#define  rTP_MONITOR_THRESHOLD       (DAT_TP_MONITOR_THERSHOLD<<0)

//0x0C  12
#define  DAT_KEY_MONITOR_THERSHOLD   0x0000  //[15:0] 触摸检测时，KEY通道的触摸阈值
#define  rKEY_MONITOR_THRESHOLD      (DAT_KEY_MONITOR_THERSHOLD<<0)

//0x0D  13
#define  DAT_AFE_ANA_GEN_CFG0        0xC2    //[10:0] K1: CA_P1高电平宽度，实际值为配置值加1.
#define  rAFE_ANA_K1_CFG0           (DAT_AFE_ANA_GEN_CFG0<<0)

//0x0E  14
#define  DAT_AFE_ANA_GEN_CFG1        0x2E    //[10:0] K2: CA_P1低电平宽度，实际值为配置值加1.
#define  rAFE_ANA_K2_CFG1           (DAT_AFE_ANA_GEN_CFG1<<0)

//0x0F  15
#define  DAT_T3                      0x01    //[11:8] T3时间宽度，All实际值为配置值加1.
#define  DAT_T2                      0x01    //[7:4]  T2时间宽度
#define  DAT_T1                      0x01    //[3:0]  T1时间宽度
#define  rAFE_ANA_CA_CFG0            ((DAT_T3<<8)\                                          
                                     +(DAT_T2<<4)\
                                     +(DAT_T1<<0))
                                     
//0x10  16
#define  DAT_T5                      0x28    //[15:7] T5时间宽度
#define  DAT_T4                      0x01    //[6:0]  T4时间宽度
#define  rAFE_ANA_CA_CFG1            ((DAT_T5<<8)\                                          
                                     +(DAT_T4<<0))

//0x11  17
#define  DAT_CB_DAC_ONE_STEP_W       0x1 // 0x2     //[11:8] cb_dac每一阶宽度，实际值为配置值加1. 
#define  DAT_CB_JUMP_STEP_EN         0x0     //[7] 0:32阶； 1:16阶
#define  DAT_T6                      0x06    //[6:0]  T6时间宽度
#define  rAFE_ANA_CA_CFG2            ((DAT_CB_DAC_ONE_STEP_W<<8)\                                          
                                     +(DAT_CB_JUMP_STEP_EN<<7)\
                                     +(DAT_T6<<0))
//0x12  18
#define  DAT_AFE_LOAD_DELAY_H        0x00    //[15:10] afe load cb finish delay high bits;
#define  DAT_T7_SX                   0x000   //[9:0]  SX/VCOM_OPT T7时间宽度
#define  rAFE_ANA_P1_P2_CFG0         ((DAT_AFE_LOAD_DELAY_H<<10)\
                                     +(DAT_T7_SX<<0))

//0x13  19
#define  DAT_AFE_LOAD_DELAY_M        0x00    //[15:10] afe load cb finish delay middle bits;
#define  DAT_T8_SX                   0x000   //[9:0]  SX/VCOM_OPT T8时间宽度
#define  rAFE_ANA_P1_P2_CFG1         ((DAT_AFE_LOAD_DELAY_M<<10)\
                                     +(DAT_T8_SX<<0))

//0x14  20
#define  DAT_AFE_LOAD_DELAY_L        0x00    //[15:10] afe load cb finish delay low bits;
#define  DAT_T7_GIP                  0x000   //[9:0]  GIPH/GIPL T7时间宽度
#define  rAFE_ANA_P1_P2_CFG2         ((DAT_AFE_LOAD_DELAY_M<<10)\
                                     +(DAT_T7_GIP<<0))

//0x15  21                           
#define  DAT_T8_GIP                  0x000   //[9:0]  GIPH/GIPL T8时间宽度
#define  rAFE_ANA_P1_P2_CFG3         (DAT_T8_GIP<<0)

//0x16  22                           
#define  DAT_T7_SD                   0x000   //[9:0]  SOURCE T7时间宽度
#define  rAFE_ANA_P1_P2_CFG4         (DAT_T7_SD<<0)

//0x17  23                           
#define  DAT_T8_SD                   0x000   //[9:0]  SOURCE T8时间宽度
#define  rAFE_ANA_P1_P2_CFG5         (DAT_T8_SD<<0)

//0x18  24
#define  DAT_GIPL_P1P2_DLY           0x00   //[15:12] gipl p1/p2 delay时间                                     
#define  DAT_GIPH_P1P2_DLY           0x00   //[11:8]  giph p1/p2 delay时间  
#define  DAT_SX_DLY                  0x00   //[7:4] sx p1/p2 delay时间
#define  DAT_CA_DLY                  0x00   //[3:0] ca delay时间
#define  rAFE_P1_P2_DLY_CFG0         ((DAT_GIPL_P1P2_DLY<<12)\                                          
                                     +(DAT_GIPH_P1P2_DLY<<8)\
                                     +(DAT_SX_DLY<<4)\
                                     +(DAT_CA_DLY<<0))
//0x19  25
#define  DAT_VCOM_DLY                0x00   //[7:4] vcom p1/p2 delay时间
#define  DAT_SD_DLY                  0x00   //[3:0] source p1/p2 delay时间
#define  rAFE_P1_P2_DLY_CFG1         ((DAT_VCOM_DLY<<4)\                                          
                                     +(DAT_SD_DLY<<0))

//0x1A  26
#define  DAT_SCAN_START_0_WITDH      0x00 //[13:10]每1个tp帧,第1个scan_start的长度,RO
#define  DAT_T10                     0x21 // 0x011  //[9:0] T10 时间宽度
#define  rAFE_ANA_SH_CFG0            ((DAT_SCAN_START_0_WITDH<<10)\
                                     +(DAT_T10<<0))

//0x1B  27
#define  DAT_START_OTHER_MAX_WITDH   0x00 //[12:10]每1个tp帧,其它scan_start的最大长度，RO
#define  DAT_T11                     0x21 //0x011  //[9:0] T11 时间宽度
#define  rAFE_ANA_SH_CFG1            ((DAT_START_OTHER_MAX_WITDH<<10)\
                                     +(DAT_T11<<0))

//0x1C  28
#define  DAT_START_OTHER_MIN_WITDH   0x00 //[12:10]每1个tp帧,其它scan_start的最小长度，RO
#define  DAT_T12                     0x001  //[9:0] T12 时间宽度
#define  rAFE_ANA_SH_CFG2            ((DAT_START_OTHER_MIN_WITDH<<10)\
                                     +(DAT_T11<<0))

//0x1D  29
#define  DAT_T13                     0x001  //[9:0] T13 时间宽度
#define  rAFE_ANA_SH_CFG3            (DAT_T13<<0)

//0x1E  30
#define  DAT_T14                     0x011  //[9:0] T14 时间宽度
#define  rAFE_ANA_SH_CFG4            (DAT_T14<<0)

//0x1F  31
#define  DAT_FRM_START_WITDH         0x8    //[12:9] frame_start_宽度选择，只允许配6,7,8
#define  DAT_T15                     0x001  //[9:0] T15 时间宽度
#define  rAFE_ANA_SH_CFG5            ((DAT_FRM_START_WITDH<<9)\
                                     +(DAT_T15<<0))

//0x20  32
#define  DAT_SEC_START_WITDH         0x4   //[14:12] section_start宽度选择,只允许配3,4,5
#define  DAT_SH_DLY_SEL              0x01  //[11]sh cap control delay 45ns  1:delay 0: no delay
#define  DAT_T17                     0x03  //[10:6] T17 时间宽度
#define  DAT_T16                     0x11  //[5:0]  T16 时间宽度
#define  rAFE_ANA_SH_CFG6            ((DAT_SEC_START_WITDH<<12)\
                                     +(DAT_SH_DLY_SEL<<11)\
                                     +(DAT_T17<<6)\
                                     +(DAT_T16<<0))

//0x21  33
#define  DAT_T22                     0x3F  //[15:8] T22 时间宽度
#define  DAT_T20                     0x07  //[7:0]  T20 时间宽度
#define  rAFE_ANA_ADC_CFG0           ((DAT_T22<<8)\
                                     +(DAT_T20<<0))

//0x22  34
#define  DAT_ADC_CLK_GATE_EN         0x01  //[14]tp channel adc clk gating enable
#define  DAT_KEY_ADC_SAMPLE_SEL      0x00  //[13]key键ADC采样点选择;1'b0:adc_clk上升沿采样;1'b1:adc_clk上升沿下1拍采样
#define  DAT_T25                     0x01  //[12:9] T25 时间宽度
#define  DAT_T21                     0x07  //[8:0]  T21 时间宽度
#define  rAFE_ANA_ADC_CFG1           ((DAT_ADC_CLK_GATE_EN<<14)\
                                     +(DAT_KEY_ADC_SAMPLE_SEL<<13)\
                                     +(DAT_T25<<9)\
                                     +(DAT_T21<<0))

//0x23  35
#define  DAT_T26                     0x01  //[12:9] T22 时间宽度
#define  DAT_T23                     0x01  //[8:0]  T20 时间宽度
#define  rAFE_ANA_ADC_CFG2           ((DAT_T26<<9)\
                                     +(DAT_T23<<0))

//0x24  36
#define  DAT_SADC_OSDET              0x0   //[15] SADC offset test control: 1:enable
#define  DAT_ADC_KEY_VRSEL           0x0   //[14] 1:enable
#define  DAT_TP_CH_VRSEL             0x0   //[13] 1:enable
#define  DAT_ADC_SH_DELAY            0x01  //[12:5] adc sh delay时间，调整单位为adc_clk;
#define  DAT_ADC_SH_WIDTH            0x03  //[4:0]  adc sh 宽度，调整单位为adc_clk;
#define  rAFE_ANA_ADC_CFG3           ((DAT_SADC_OSDET<<15)\
                                     +(DAT_ADC_KEY_VRSEL<<14)\
                                     +(DAT_TP_CH_VRSEL<<13)\
                                     +(DAT_ADC_SH_DELAY<<5)\
                                     +(DAT_ADC_SH_WIDTH<<0))

//0x25  37
#define  DAT_GIPH_PHASE3             0x00  //[11:10] giph display off phase3阶段p1/p2配置值(0:全驱；1:Hiz; 2:GND)
#define  DAT_GIPH_PHASE2             0x00  //[9:8] giph display off phase2阶段p1/p2配置值(0:全驱；1:Hiz; 2:GND)
#define  DAT_GIPH_PHASE1             0x00  //[7:6] giph display off phase1阶段p1/p2配置值
#define  DAT_GIPH_PHASE0             0x00  //[5:4] giph display off phase0阶段p1/p2配置值
#define  DAT_GIPH_DPON_NO_SCAN       0x00  //[3:2] giph display on no scan阶段p1/p2配置值
#define  DAT_GIPH_DPON_SCAN          0x00  //[1:0] giph display on scan阶段p1/p2配置值
#define  rAFE_GIPH_P1_P2_CFG         ((DAT_GIPH_PHASE3<<10)\ 
                                     +(DAT_GIPH_PHASE2<<8)\                                          
                                     +(DAT_GIPH_PHASE1<<6)\
                                     +(DAT_GIPH_PHASE0<<4)\
                                     +(DAT_GIPH_DPON_NO_SCAN<<2)\
                                     +(DAT_GIPH_DPON_SCAN<<0))
//0x26  38
#define  DAT_GIPL_PHASE3             0x00  //[11:10] gipl display off phase3阶段p1/p2配置值(0:全驱；1:Hiz; 2:GND)
#define  DAT_GIPL_PHASE2             0x00  //[9:8] gipl display off phase2阶段p1/p2配置值(0:全驱；1:Hiz; 2:GND)
#define  DAT_GIPL_PHASE1             0x00  //[7:6] gipl display off phase1阶段p1/p2配置值
#define  DAT_GIPL_PHASE0             0x00  //[5:4] gipl display off phase0阶段p1/p2配置值
#define  DAT_GIPL_DPON_NO_SCAN       0x00  //[3:2] gipl display on no scan阶段p1/p2配置值
#define  DAT_GIPL_DPON_SCAN          0x00  //[1:0] gipl display on scan阶段p1/p2配置值
#define  rAFE_GIPL_P1_P2_CFG         ((DAT_GIPL_PHASE3<<10)\  
                                     +(DAT_GIPL_PHASE2<<8)\
                                     +(DAT_GIPL_PHASE1<<6)\
                                     +(DAT_GIPL_PHASE0<<4)\
                                     +(DAT_GIPL_DPON_NO_SCAN<<2)\
                                     +(DAT_GIPL_DPON_SCAN<<0))  



//0x27  39
#define  DAT_VOM_DPOFF_NO_SCAN       0x00  //[15:14] vom opt display off no scan阶段p1/p2配置值
#define  DAT_VOM_DPOFF_SCAN          0x00  //[13:12] vom opt display off scan阶段p1/p2配置值
#define  DAT_VOM_DPON_NO_SCAN        0x00  //[11:10] vom opt display on no scan阶段p1/p2配置值
#define  DAT_VOM_DPON_SCAN           0x00  //[9:8]   vom opt display on scan阶段p1/p2配置值
#define  DAT_SD_DPOFF_NO_SCAN        0x00  //[7:6] source display off no scan阶段p1/p2配置值
#define  DAT_SD_DPOFF_SCAN           0x00  //[5:4] source display off scan阶段p1/p2配置值
#define  DAT_SD_DPON_NO_SCAN         0x00  //[3:2] source display on no scan阶段p1/p2配置值
#define  DAT_SD_DPON_SCAN            0x00  //[1:0] source display on scan阶段p1/p2配置值
#define  rAFE_SD_VOM_OPT_P1_P2_CFG   ((DAT_VOM_DPOFF_NO_SCAN<<14)\
                                     +(DAT_VOM_DPOFF_SCAN<<12)\
                                     +(DAT_VOM_DPON_NO_SCAN<<10)\
                                     +(DAT_VOM_DPON_SCAN<<8)\
                                     +(DAT_SD_DPOFF_NO_SCAN<<6)\
                                     +(DAT_SD_DPOFF_SCAN<<4)\
                                     +(DAT_SD_DPON_NO_SCAN<<2)\
                                     +(DAT_SD_DPON_SCAN<<0))  
                                     
//0x28  40
#define  DAT_SX_DPOFF_NO_SCAN        0x00  //[7:6]sx display off no scan阶段p1/p2配置值
#define  DAT_SX_DPOFF_SCAN           0x00  //[5:4]sx display off scan阶段p1/p2配置值
#define  DAT_SX_DPON_NO_SCAN         0x00  //[3:2]sx display on no scan阶段p1/p2配置值
#define  DAT_SX_DPON_SCAN            0x00  //[1:0]sx display on scan阶段p1/p2配置值
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
#define  DAT_ALL_GATE_ON_L_CFG       0x0000  //[15:0] allgate on 低16bit配置值
#define  rALL_GATE_ON_L_CFG          (DAT_ALL_GATE_ON_L_CFG<<0)

//0x2E  46 
#define  DAT_ALL_GATE_OFF_L_CFG      0x0000  //[15:0] allgate off 低16bit配置值
#define  rALL_GATE_OFF_L_CFG         (DAT_ALL_GATE_OFF_L_CFG<<0)

//0x2F  47
#define  DAT_ALL_GATE_STOP_L_CFG     0x0000  //[15:0] allgate stop 低16bit配置值
#define  rALL_GATE_STOP_L_CFG        (DAT_ALL_GATE_STOP_L_CFG<<0)

//0x30  48
#define  DAT_ALL_GATE_ON_H_CFG       0x0000  //[5:4] allgate on   高2bit配置值
#define  DAT_ALL_GATE_OFF_H_CFG      0x0000  //[3:2] allgate off  高2bit配置值
#define  DAT_ALL_GATE_STOP_H_CFG     0x0000  //[1:0] allgate stop 高2bit配置值

#define  rALL_GATE_H_CFG             ((DAT_ALL_GATE_ON_H_CFG<<4)\                                          
                                     +(DAT_ALL_GATE_OFF_H_CFG<<2)\
                                     +(DAT_ALL_GATE_STOP_H_CFG<<0)) 

//0x31  49
#define  DAT_RPT_RAWDATA_NUM         0x120  //[9:0] 上报Rawdata的个数
#define  rRPT_RAWDATA_NUM            (DAT_RPT_RAWDATA_NUM<<0)                                      

//0x32  50
#define  DAT_CB_ADJUST_THLD_TP        0x0000 //[15:0] 硬件CB校正阈值，目标值。
#define  rCB_ADJUST_THLD_TP          (DAT_CB_ADJUST_THLD_TP<<0)

//0x33  51
#define  DAT_TEST_MODE_KEY_NUM       0x00    //[11:10]测试模式，选择key键号                                    
#define  DAT_TEST_MODE_TP_CH_NUM     0x000   //[9:1]  测试模式，选择tp通道号
#define  DAT_TEST_MODE_TP_KEY_SEL    0x0     //[0], 通道选择, 0:tp; 1:key
#define  rTEST_MODE_FLAG             ((DAT_TEST_MODE_KEY_NUM<<10)\                                          
                                     +(DAT_TEST_MODE_TP_CH_NUM<<1)\
                                     +(DAT_TEST_MODE_TP_KEY_SEL<<0)) 
//0x34  52
#define  DAT_PRESCAN_TIME            0x0000  //[15:0] 黑屏预扫描时间
#define  rPRESCAN_TIME               DAT_PRESCAN_TIME

//0x35  53
#define  DAT_DISCHARGE_TIME          0x0000  //[15:0] 黑屏扫描后放电时间
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
#define  DAT_P0_SORT2_SEL            0x0  //[]15:12信号选择
                                          //0:sh_s0  1:sh_s1 2:sh_s2 3:sh_rst
#define  DAT_P0_SORT1_SEL            0x0  //[11:8]信号选择
                                          //0:ca_rst 1:ca_p1 2:ca_p4 3:ca_p6 4:ca_p7 5:ca_p10 
                                          //6:cb_dac0 7:cb_dac1 8:cb_dac2 9:cb_dac3 10:cb_dac4
#define  DAT_P0_SORT0_SEL            0x0  //[7:4]信号选择:
                                          //0:lvd_det 1:lcd_run 2:lcd_busy 3:stb_start 4:scan_start
                                          //5:tp_scan 6:tp_busy 7:frame end 8:aram_ready 9:mon_det 
#define  DAT_P0_SORT_SEL             0x0  //[3:0]种类选择
#define  rTEST_P0_CFG0               ((DAT_P0_SORT2_SEL<<12)\                               
                                     +(DAT_P0_SORT1_SEL<<8)\  
                                     +(DAT_P0_SORT0_SEL<<4)\
                                     +(DAT_P0_SORT_SEL<<0))  
//0x3b  59
#define  DAT_P0_SORT6_SEL            0x0  //[]15:12信号选择                                     
#define  DAT_P0_SORT5_SEL            0x0  //[11:8]信号选择
#define  DAT_P0_SORT4_SEL            0x0  //[7:4]信号选择
#define  DAT_P0_SORT3_SEL            0x0  //[3:0]信号选择
#define  rTEST_P0_CFG1               ((DAT_P0_SORT6_SEL<<12)\                               
                                     +(DAT_P0_SORT5_SEL<<8)\  
                                     +(DAT_P0_SORT4_SEL<<4)\
                                     +(DAT_P0_SORT3_SEL<<0))  

//0x3c  60            
#define  DAT_TEST_PIN0_SORTA_SEL     0x0000 //[15:12]信号选择
#define  DAT_P0_SORT9_SEL            0x0  //[11:8]信号选择
#define  DAT_P0_SORT8_SEL            0x0  //[7:4]信号选择
#define  DAT_P0_SORT7_SEL            0x0  //[3:0]信号选择
#define  rTEST_P0_CFG2               ((DAT_TEST_PIN0_SORTA_SEL<<8)\
                                     +(DAT_P0_SORT9_SEL<<8)\  
                                     +(DAT_P0_SORT8_SEL<<4)\
                                     +(DAT_P0_SORT7_SEL<<0))  

//0x3d  61
#define  DAT_P1_SORT2_SEL            0x0  //[]15:12信号选择
#define  DAT_P1_SORT1_SEL            0x0  //[11:8]信号选择                                         
#define  DAT_P1_SORT0_SEL            0x0  //[7:4]信号选择:
#define  DAT_P1_SORT_SEL             0x0  //[3:0]种类选择
#define  rTEST_P1_CFG0               ((DAT_P1_SORT2_SEL<<12)\                               
                                     +(DAT_P1_SORT1_SEL<<8)\  
                                     +(DAT_P1_SORT0_SEL<<4)\
                                     +(DAT_P1_SORT_SEL<<0))  

//0x3e  62
#define  DAT_P1_SORT6_SEL            0x0  //[]15:12信号选择                                     
#define  DAT_P1_SORT5_SEL            0x0  //[11:8]信号选择
#define  DAT_P1_SORT4_SEL            0x0  //[7:4]信号选择
#define  DAT_P1_SORT3_SEL            0x0  //[3:0]信号选择
#define  rTEST_P1_CFG1               ((DAT_P1_SORT6_SEL<<12)\                               
                                     +(DAT_P1_SORT5_SEL<<8)\  
                                     +(DAT_P1_SORT4_SEL<<4)\
                                     +(DAT_P1_SORT3_SEL<<0))  

//0x3f  63   
#define  DAT_PIN1_SORTA_SEL          0x0000 //[15:12]信号选择
#define  DAT_P1_SORT9_SEL            0x0  //[11:8]信号选择
#define  DAT_P1_SORT8_SEL            0x0  //[7:4]信号选择
#define  DAT_P1_SORT7_SEL            0x0  //[3:0]信号选择
#define  rTEST_P1_CFG2               ((DAT_PIN1_SORTA_SEL<<12)\  
                                     +(DAT_P1_SORT9_SEL<<8)\ 
                                     +(DAT_P1_SORT8_SEL<<4)\
                                     +(DAT_P1_SORT7_SEL<<0))  


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//0x40  64  
#define  DAT_SCAN_EN                 0x0    //[15] 0:关闭; 1: key通道开启互容模式;                             
#define  DAT_ADC_DIFF_EN             0x0    //[14] 0:不计算adc diff max; 1:开启mcap diff模块，结合mcap_diff_mode
//#define  DAT_DATAPROC_MODE           0x1    //[13] 0:关闭mixer以后，sum之前的数据处理单元; 1:正常处理   
#define  DAT_MIX_LEN_MODE            0x1    //[4]  0:6点正交; 1:8点正交；算法建议TX_clk大于175K,采样6倍过采样率
//#define  DAT_BASE_EN                 0x0    //[3]  0:关闭key减Base功能; 1:开启  已删除
#define  DAT_RAW_GAIN_EN             0x0    //[2]  0:不增益; 1:进行增益处理
#define  DAT_OVERFLOW_CLR_EN         0x0    //[1]  0:不使能; 1:溢出检测使能
#define  DAT_OVERFLOW_EN             0x0    //[0]  0:溢出检测使能                        
#define  rMCAP_SCAN_CFG              ((DAT_SCAN_EN<<15)\  
                                     +(DAT_ADC_DIFF_EN<<14)\
                                     +(DAT_MIX_LEN_MODE<<4)\
                                     +(DAT_RAW_GAIN_EN<<2)\
                                     +(DAT_OVERFLOW_CLR_EN<<1)\
                                     +(DAT_OVERFLOW_EN<<0))  

//0x41  65  
#define  DAT_KEY_NUM_ERROR_FLAG      0x0  //[8:5]RO: 3;2;1;0 :key1;2;3;4扫描非正常结束；
#define  DAT_KEY_ERROR_FLAG          0x0  //[4]RO: 坑的长度小于互容算法要求，置1报错
#define  DAT_MCAP_DIFF_MODE          0x0  //[3]0:adc采样数据经过diff计算; 1:经过mixer再进行diff计算
#define  DAT_MCAP_OVERFLOW_CLR_FLAG  0x0  //[2]被设置时,软件可以清除
#define  DAT_MCAP_OVERFLOW_FLAG      0x0  //[1]被设置时,当前帧有溢出
#define  DAT_MCAP_DONE               0x0  //[0]被设置，写1清除                
#define  rMCAP_SCANSR                ((DAT_KEY_NUM_ERROR_FLAG<<5)\  
                                     +(DAT_KEY_ERROR_FLAG<<4)\
                                     +(DAT_MCAP_DIFF_MODE<<3)\
                                     +(DAT_MCAP_OVERFLOW_CLR_FLAG<<2)\
                                     +(DAT_MCAP_OVERFLOW_FLAG<<1)\
                                     +(DAT_MCAP_DONE<<0))  

//0x42 66
#define  DAT_MCAP_LPFIR_SUM_NUM      0x0001  //[9:5]正常模式:num = 载波周期x过采样倍率/4-FIR系数长度，Freerun建议配16;关闭低通滤波跟半带滤波时，最大次数是256
#define  rMCAP_LPFIR_SUM_NUM         (DAT_MCAP_LPFIR_SUM_NUM<<0)
                                     
//0x43 67
#define  DAT_GAIN_COF                0x1  //[15:8]raw_gain_en有效时，rawdata进行rawdata*gaincof>>raw_shif_cof运算
#define  DAT_RAW_SHIFT_COF           0x0  //[7:0] raw_gain_en有效时，rawdata进行rawdata*gaincof>>raw_shif_cof运算
#define  rRAWSHIFTCAF                ((DAT_GAIN_COF<<8)\  
                                     +(DAT_RAW_SHIFT_COF<<0))   

//0x44 68
#define  DAT_RAWDATA_OFFSET_L        0x0  //[15:0]rawdata的值统一减去该值，如果rawdata大于该offset,可为0.
#define  rRAWDATA_OFFSET_L           (DAT_RAWDATA_OFFSET_L<<0)

//0x45 69
#define  DAT_MACP_DIFF_SHIFT_COF     0x00 //[7:4]互容key diff_noise的shift参数
//#define  DAT_RAWDATA_OFFSET_H        0x0  //[3]offset高位
//#define  DAT_DATA_INV                0x0  //[2]1:比特反向
//#define  DAT_ADC_DUMMY_SHUF          0x0  //[1]1:在dummy期间，不发送ADC时序。0:发送
//#define  DAT_ADC_MSB_INV             0x1  //[0]1:高位取反
#define  rADC_CFG                    (DAT_MACP_DIFF_SHIFT_COF<<4)

//0x46 70  寄存器无效
#define  DAT_ADC_DATA_VLD0           0x0  //[12]1:采集有效; 0:采集无效
#define  DAT_ADC_DATA0               0x0  //[11:0]通道0 ADC DATA,当下一个数据采集，数据会更新。
#define  rADC_DATA0                  ((DAT_ADC_DATA_VLD0<<12)\  
                                     +(DAT_ADC_DATA0<<0))    

//0x47 71
#define  DAT_MCAP_INIT_SAMPLE        0x0  //[9:0]配置TX_clk初始位置，对齐相位
#define  rMCAP_INIT_SAMPL_CFG        (DAT_MCAP_INIT_SAMPLE<<0)

//0x48 72
#define  DAT_OVERFLOW_THR            0x3E0  //[11:0] ADC数据溢出上限值 
#define  rOVERFLOW_THR               (DAT_OVERFLOW_THR<<0)

//0x49 73
#define  DAT_UNDERFLOW_THR           0x0  //[11:0] ADC数据溢出下限值 
#define  rUNDERFLOW_THR              (DAT_UNDERFLOW_THR<<0)

//0x4A 74
#define  DAT_OVERFLOW_UPBOUND        0xA  //[11:0] 符合溢出范围，计为一个溢出点
#define  rOVERFLOW_UPBOUND           (DAT_OVERFLOW_UPBOUND<<0)

//0x4B 75
#define  DAT_OVER_POINT_FRAME        0x20  //[11:0] 发送溢出的点大于该值时，产生溢出标志
#define  rOVER_POINT_FRAME           (DAT_OVER_POINT_FRAME<<0)

//0x4C 76
#define  DAT_NORMAL_SIGNAL_UPTHR     0x258 //[11:0]溢出清除上限值
#define  rNORMAL_SIGNAL_UPTHR        (DAT_NORMAL_SIGNAL_UPTHR<<0)

//0x4D 77
#define  DAT_NORMAL_SIGNAL_DWTHR     0x190 //[11:0]溢出清除下限值
#define  rNORMAL_SIGNAL_DWTHR        (DAT_NORMAL_SIGNAL_DWTHR<<0)

//0x4E 78
#define  DAT_OVERFLOW_CLR_FRAMENUM   0x64   //[7:0] 当发送清除溢出的点大于该值时，产生溢出清除标志
#define  rOVERFLOW_CLR_FRAMENUM     (DAT_OVERFLOW_CLR_FRAMENUM<<0)

//0x4F 79
#define  DAT_MCAP_HBFIR_EN           0x01  //[15]mcap hb fir使能信号.0:关闭;1:开启
#define  DAT_MCAP_LPFIR_SUM_START    0x0E  //[14:10]Sum_Start = FIR阶数，0开始，实际值为配置值加1
//#define  DAT_MCAP_LPFIR_SUM_NUM      0x06  //[9:5]正常模式:num = 载波周期x过采样倍率/4-FIR系数长度，Freerun建议配16
#define  DAT_MCAP_LPFIR_EN           0x1   //[4] 1:使能
#define  DAT_MCAP_LPFIR_TOP          0xE   //[3:0] LP FIR阶数
#define  rMCAP_LPFIR_CFG             ((DAT_MCAP_LPFIR_SUM_START<<10)\  
                                     +(DAT_MCAP_LPFIR_EN<<4)\
                                     +(DAT_MCAP_LPFIR_TOP<<0))  

//0x50 80
#define  DAT_MCAP_LPFIR_COF0        0x104  //[15:0] LP FIR 系数0  
#define  rMCAP_LPFIR_COF0           (DAT_MCAP_LPFIR_COF0<<0)

//0x51 81
#define  DAT_MCAP_LPFIR_COF1        0x296  //[15:0] LP FIR 系数1  
#define  rMCAP_LPFIR_COF1           (DAT_MCAP_LPFIR_COF1<<0)

//0x52 82
#define  DAT_MCAP_LPFIR_COF2        0x4E5  //[15:0] LP FIR 系数2  
#define  rMCAP_LPFIR_COF2           (DAT_MCAP_LPFIR_COF2<<0)

//0x53 83
#define  DAT_MCAP_LPFIR_COF3        0x7C3  //[15:0] LP FIR 系数3  
#define  rMCAP_LPFIR_COF3           (DAT_MCAP_LPFIR_COF3<<0)

//0x54 84
#define  DAT_MCAP_LPFIR_COF4        0xACD  //[15:0] LP FIR 系数4
#define  rMCAP_LPFIR_COF4           (DAT_MCAP_LPFIR_COF4<<0)

//0x55 85
#define  DAT_MCAP_LPFIR_COF5        0xD84  //[15:0] LP FIR 系数5 
#define  rMCAP_LPFIR_COF5           (DAT_MCAP_LPFIR_COF5<<0)

//0x56 86
#define  DAT_MCAP_LPFIR_COF6        0xF65  //[15:0] LP FIR 系数6  
#define  rMCAP_LPFIR_COF6           (DAT_MCAP_LPFIR_COF6<<0)

//0x57 87
#define  DAT_MCAP_LPFIR_COF7        0x1011 //[15:0] LP FIR 系数7  
#define  rMCAP_LPFIR_COF7           (DAT_MCAP_LPFIR_COF7<<0)

//0x58  88
#define  DAT_CB_ADJUST_THLD_KEY     0x0000 //[15:0] 硬件CB校正key阈值，目标值。
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
    
#if CB_AFE_SCAN_MODE == 0            //扫描方式1
#define DAT_TP_FRAME_NUM   1
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       6
#define DAT_BUSY_ID2       1
#define DAT_BUSY_ID3       6
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       6
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       6
    
#elif CB_AFE_SCAN_MODE == 1          //扫描方式2
#define DAT_TP_FRAME_NUM   2
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       4
#define DAT_BUSY_ID2       7
#define DAT_BUSY_ID3       1
#define DAT_BUSY_ID4       4
#define DAT_BUSY_ID5       7
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       4
    
#elif CB_AFE_SCAN_MODE == 2          //扫描方式3
#define DAT_TP_FRAME_NUM   3
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       3
#define DAT_BUSY_ID2       5
#define DAT_BUSY_ID3       7
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       3
#define DAT_BUSY_ID6       5
#define DAT_BUSY_ID7       7
    
#elif CB_AFE_SCAN_MODE == 3          //扫描方式4
#define DAT_TP_FRAME_NUM   3
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       3
#define DAT_BUSY_ID2       5
#define DAT_BUSY_ID3       7
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       3
#define DAT_BUSY_ID6       5
#define DAT_BUSY_ID7       7
    
    
#elif CB_AFE_SCAN_MODE == 4          //扫描方式5
#define DAT_TP_FRAME_NUM   1
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       2
#define DAT_BUSY_ID2       1
#define DAT_BUSY_ID3       2
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       2
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       2
    
#elif CB_AFE_SCAN_MODE == 5          //扫描方式6
#define DAT_TP_FRAME_NUM   1
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       6
#define DAT_BUSY_ID2       1
#define DAT_BUSY_ID3       6
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       6
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       6
 
#elif CB_AFE_SCAN_MODE == 6          //扫描方式7
#define DAT_TP_FRAME_NUM   1
#define DAT_BUSY_ID0       1
#define DAT_BUSY_ID1       6
#define DAT_BUSY_ID2       1
#define DAT_BUSY_ID3       6
#define DAT_BUSY_ID4       1
#define DAT_BUSY_ID5       6
#define DAT_BUSY_ID6       1
#define DAT_BUSY_ID7       6 

#elif CB_AFE_SCAN_MODE == 7          //扫描方式8
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

