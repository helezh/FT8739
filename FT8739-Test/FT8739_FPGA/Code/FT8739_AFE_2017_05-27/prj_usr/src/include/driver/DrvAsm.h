/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: DrvAsm.h
*
*    Author: lisen
*
*   Created: 2016-12-27
*
*  Abstract:
*
* Reference:
*
* Version:
* 0.1:
*
*******************************************************************************/
#ifndef __DRV_ASM_H_
#define __DRV_ASM_H_

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
/* Asm int */
#define LCD_BUSY_FALL_INT0          BITn(15)
#define LCD_BUSY_RISE_INT0          BITn(14)
#define LCD_PANEL_CONFLICT_INT0     BITn(13)
#define LCD_DSTB_FAIL_INT0          BITn(12)
#define LCD_DSTB_RISE_INT0          BITn(11)
#define LCD_SYNC_MISS_FALL_INT0     BITn(10)
#define LCD_SYNC_MISS_RISE_INT0     BITn(9)
#define ARAM_READY_INT0             BITn(8)
#define FRAME_END_INT0              BITn(7)
#define AFE_DET_INT0                BITn(6)
#define LCD_VSTART_INT0             BITn(5)
#define LCD_VMID_INT0               BITn(4)
#define LCD_VEND_INT0               BITn(3)
#define LCD_VBLANK_INT0             BITn(2)
#define LCD_RUN_FALL_INT0           BITn(1)
#define LCD_RUN_RISE_INT0           BITn(0)

#define LCD_HW_MON_TIMEOUT_INT1     BITn(14) 
#define LCD_LPF_MODE_EN_FALL_INT1   BITn(13)
#define LCD_LPF_MODE_EN_RISE_INT1   BITn(12)
#define LCD_STB_TICK_INT1           BITn(11)
#define LCD_ODD_EVEN_FALL_INT1      BITn(10)
#define LCD_ODD_EVEN_RISE_INT1      BITn(9)
#define LCD_VDO_MODE_FALL_INT1      BITn(8)
#define LCD_VDO_MODE_RISE_INT1      BITn(7)  
#define LCD_IDLE_MODE_FALL_INT1     BITn(6)  
#define LCD_IDLE_MODE_RISE_INT1     BITn(5)
#define LCD_3D_MODE_FALL_INT1       BITn(4)
#define LCD_3D_MODE_RISE_INT1       BITn(3)
#define LCD_RUN_INT1                BITn(2)
#define LCD_DSTB_INT1               BITn(1)


/* Asm Sta */
#define LCD_PANEL_CONFLICT_STA      BITn(14)
#define LCD_DSTB_STA                BITn(13)
#define LCD_SYNC_MISS_STA           BITn(12)
#define LCD_FRAME_END_STA           BITn(11)
#define LCD_TCH_DET_STA             BITn(10)
#define LCD_STB_TICK_STA            BITn(9)
#define LCD_VSTART_STA              BITn(8)
#define LCD_VMID_STA                BITn(7)
#define LCD_VEND_STA                BITn(6)
#define LCD_VBLANK_STA              BITn(5)
#define LCD_ODD_EVEN_STA            BITn(4)
#define LCD_VDO_MODE_STA            BITn(3)
#define LCD_IDLE_MODE_STA           BITn(2)
#define LCD_3D_MODE_STA             BITn(1)
#define LCD_RUN_STA                 BITn(0)

/*Scan Sta1*/
#define TP_BUSY_STA                 BITn(11) // [11]  RO: TP busy的实时状态
#define LCD_BUSY_STA                BITn(10) // [10]  RO: LCD busy的实时状态   

/*Scan Sta2*/
#define LPF_MODE_TP_TURBO_ACK       BITn(13) // [13]  RO: 0:不开坑  1:开坑
#define VB_MODE_ACK                 BITn(12) // [12]  RO: 0:小坑    1:大坑 

/* ASM_INT_FLAG0 bit信息RO  0x00*/
typedef enum
{
    BIT_LCD_BUSY_FALL_FLAG0          = 15,
    BIT_LCD_BUSY_RISE_FLAG0          = 14,
    BIT_LCD_PANEL_CONFLICT_FLAG0     = 13,
    BIT_LCD_DSTB_FAIL_FLAG0          = 12,
    BIT_LCD_DSTB_RISE_FLAG0          = 11,
    BIT_LCD_SYNC_MISS_FALL_FLAG0     = 10,
    BIT_LCD_SYNC_MISS_RISE_FLAG0     = 9,
    BIT_LCD_ARAM_RDY_FLAG0           = 8,
    BIT_LCD_FRAME_END_FLAG0          = 7,
    BIT_LCD_TCH_DET_FLAG0            = 6,
    BIT_LCD_VSTART_FLAG0             = 5,
    BIT_LCD_VMID_FLAG0               = 4,
    BIT_LCD_VEND_FLAG0               = 3,
    BIT_LCD_VBLANK_FLAG0             = 2,
    BIT_LCD_RUN_FALL_FLAG0           = 1,
    BIT_LCD_RUN_RISE_FLAG0           = 0,          
} ENUM_BIT_ASM_INT_FLAG0;

/* ASM_INT_FLAG1 bit信息RO  0x01*/
typedef enum
{           
    
    BIT_LCD_STB_TICK_FLAG1           = 11,
    BIT_LCD_ODD_EVEN_FALL_FLAG1      = 10,
    BIT_LCD_ODD_EVEN_RISE_FLAG1      = 9,
    BIT_LCD_VDO_MODE_FALL_FLAG1      = 8,
    BIT_LCD_VDO_MODE_RISE_FLAG1      = 7,  
    BIT_LCD_IDLE_MODE_FALL_FLAG1     = 6,  
    BIT_LCD_IDLE_MODE_RISE_FLAG1     = 5,
    BIT_LCD_3D_MODE_FALL_FLAG1       = 4,
    BIT_LCD_3D_MODE_RISE_FLAG1       = 3,
    BIT_LCD_RUN_FLAG1                = 2,
    BIT_LCD_DSTB_FLAG1               = 1,
} ENUM_BIT_ASM_INT_FLAG1;

/* ASM_INT_CLR0 bit信息WO 0x02*/
typedef enum
{
    BIT_LCD_BUSY_FALL_CLR0          = 15,
    BIT_LCD_BUSY_RISE_CLR0          = 14,
    BIT_LCD_PANEL_CONFLICT_CLR0     = 13,
    BIT_LCD_DSTB_FAIL_CLR0          = 12,
    BIT_LCD_DSTB_RISE_CLR0          = 11,
    BIT_LCD_SYNC_MISS_FALL_CLR0     = 10,
    BIT_LCD_SYNC_MISS_RISE_CLR0     = 9,
    BIT_LCD_ARAM_RDY_CLR0           = 8,
    BIT_LCD_FRAME_END_CLR0          = 7,
    BIT_LCD_TCH_DET_CLR0            = 6,
    BIT_LCD_VSTART_CLR0             = 5,
    BIT_LCD_VMID_CLR0               = 4,
    BIT_LCD_VEND_CLR0               = 3,
    BIT_LCD_VBLANK_CLR0             = 2,
    BIT_LCD_RUN_FALL_CLR0           = 1,
    BIT_LCD_RUN_RISE_CLR0           = 0,        
} ENUM_BIT_ASM_INT_CLR0;

/* ASM_INT_CLR1 bit信息WO 0x03*/
typedef enum
{   
    BIT_HW_MON_TIMEOUT_CLR1         = 14,
    BIT_LPF_MODE_EN_FALL_CLR1       = 13,
    BIT_LPF_MODE_EN_RISE_CLR1       = 12,
    BIT_LCD_STB_TICK_CLR1           = 11,    
    BIT_LCD_ODD_EVEN_FALL_CLR1      = 10,
    BIT_LCD_ODD_EVEN_RISE_CLR1      = 9,
    BIT_LCD_VDO_MODE_FALL_CLR1      = 8,
    BIT_LCD_VDO_MODE_RISE_CLR1      = 7,  
    BIT_LCD_IDLE_MODE_FALL_CLR1     = 6,  
    BIT_LCD_IDLE_MODE_RISE_CLR1     = 5,
    BIT_LCD_3D_MODE_FALL_CLR1       = 4,
    BIT_LCD_3D_MODE_RISE_CLR1       = 3,
    BIT_LCD_RUN_CLR1                = 2,
    BIT_LCD_DSTB_CLR1               = 1,   
} ENUM_BIT_ASM_INT_CLR1;

/* ASM_INT_EN0 bit信息0x04 */
typedef enum
{
    BIT_LCD_BUSY_FALL_EN0          = 15,
    BIT_LCD_BUSY_RISE_EN0          = 14,
    BIT_LCD_PANEL_CONFLICT_EN0     = 13,
    BIT_LCD_DSTB_FAIL_EN0          = 12,
    BIT_LCD_DSTB_RISE_EN0          = 11,
    BIT_LCD_SYNC_MISS_FALL_EN0     = 10,
    BIT_LCD_SYNC_MISS_RISE_EN0     = 9,
    BIT_LCD_ARAM_RDY_EN0           = 8,
    BIT_LCD_FRAME_END_EN0          = 7,
    BIT_LCD_TCH_DET_EN0            = 6,
    BIT_LCD_VSTART_EN0             = 5,
    BIT_LCD_VMID_EN0               = 4,
    BIT_LCD_VEND_EN0               = 3,
    BIT_LCD_VBLANK_EN0             = 2,
    BIT_LCD_RUN_FALL_EN0           = 1,
    BIT_LCD_RUN_RISE_EN0           = 0,        
} ENUM_BIT_ASM_INT_EN0;

/* ASM_INT_EN1 bit信息0x05 */
typedef enum
{
    BIT_HW_MON_TIMEOUT_EN1         = 14,
    BIT_LCD_LPF_MODE_EN_FALL_EN1   = 13,
    BIT_LCD_LPF_MODE_EN_RISE_EN1   = 12,
    BIT_LCD_STB_TICK_EN1           = 11,   
    BIT_LCD_ODD_EVEN_FALL_EN1      = 10,
    BIT_LCD_ODD_EVEN_RISE_EN1      = 9,
    BIT_LCD_VDO_MODE_FALL_EN1      = 8,
    BIT_LCD_VDO_MODE_RISE_EN1      = 7,  
    BIT_LCD_IDLE_MODE_FALL_EN1     = 6,  
    BIT_LCD_IDLE_MODE_RISE_EN1     = 5,
    BIT_LCD_3D_MODE_FALL_EN1       = 4,
    BIT_LCD_3D_MODE_RISE_EN1       = 3,
    BIT_LCD_RUN_EN1                = 2,
    BIT_LCD_DSTB_EN1               = 1,
   
} ENUM_BIT_ASM_INT_EN1;

/* ASM_INT_WAKE_EN0 bit信息  06 */
typedef enum
{
    BIT_LCD_BUSY_FALL_WAKE_EN0          = 15,
    BIT_LCD_BUSY_RISE_WAKE_EN0          = 14,
    BIT_LCD_PANEL_CONFLICT_WAKE_EN0     = 13,
    BIT_LCD_DSTB_FAIL_WAKE_EN0          = 12,
    BIT_LCD_DSTB_RISE_WAKE_EN0          = 11,
    BIT_LCD_SYNC_MISS_FALL_WAKE_EN0     = 10,
    BIT_LCD_SYNC_MISS_RISE_WAKE_EN0     = 9,
    BIT_LCD_ARAM_RDY_WAKE_EN0           = 8,
    BIT_LCD_FRAME_END_WAKE_EN0          = 7,
    BIT_LCD_TCH_DET_WAKE_EN0            = 6,
    BIT_LCD_VSTART_WAKE_EN0             = 5,
    BIT_LCD_VMID_WAKE_EN0               = 4,
    BIT_LCD_VEND_WAKE_EN0               = 3,
    BIT_LCD_VBLANK_WAKE_EN0             = 2,
    BIT_LCD_RUN_FALL_WAKE_EN0           = 1,
    BIT_LCD_RUN_RISE_WAKE_EN0           = 0,              
} ENUM_BIT_ASM_WAKE_EN0 ;

/* ASM_INT_WAKE_EN1 bit信息  07 */
typedef enum
{
    BIT_HW_MON_TIMEOUT_WAKE_EN1         = 14,
    BIT_LCD_LPF_MODE_EN_FALL_WAKE_EN1   = 13,
    BIT_LCD_LPF_MODE_EN_RISE_WAKE_EN1   = 12,
    BIT_LCD_STB_TICK_WAKE_EN1           = 11, 
    BIT_LCD_ODD_EVEN_FALL_WAKE_EN1      = 10,
    BIT_LCD_ODD_EVEN_RISE_WAKE_EN1      = 9,
    BIT_LCD_VDO_MODE_FALL_WAKE_EN1      = 8,
    BIT_LCD_VDO_MODE_RISE_WAKE_EN1      = 7,  
    BIT_LCD_IDLE_MODE_FALL_WAKE_EN1     = 6,  
    BIT_LCD_IDLE_MODE_RISE_WAKE_EN1     = 5,
    BIT_LCD_3D_MODE_FALL_WAKE_EN1       = 4,
    BIT_LCD_3D_MODE_RISE_WAKE_EN1       = 3,
} ENUM_BIT_ASM_WAKE_EN1;

/* ASM_INT_STA0 bit信息  RO  08 */
typedef enum
{
    BIT_LCD_BUSY_STA                = 15,
    BIT_LCD_PANEL_CONFLICT_STA      = 14,
    BIT_LCD_DSTB_STA                = 13,
    BIT_LCD_SYNC_MISS_STA           = 12,
    BIT_LCD_FRAME_END_STA           = 11,
    BIT_LCD_TCH_DET_STA             = 10,
    BIT_LCD_STB_TICK_STA            = 9,
    BIT_LCD_VSTART_STA              = 8,
    BIT_LCD_VMID_STA                = 7,
    BIT_LCD_VEND_STA                = 6,
    BIT_LCD_VBLANK_STA              = 5,
    BIT_LCD_ODD_EVEN_STA            = 4,
    BIT_LCD_VDO_MODE_STA            = 3,
    BIT_LCD_IDLE_MODE_STA           = 2,
    BIT_LCD_3D_MODE_STA             = 1,
    BIT_LCD_RUN_STA                 = 0,
} ENUM_BIT_ASM_INT_STA0;

/* ASM_SCAN_STA0 bit信息  RO  09 */
typedef enum
{
    BIT_CUR_TP_FRAME_ID_STA   = 12,         // [15:12] RO:当前扫描的TP帧号
    //BIT_TPFRM_NUM_DISCARD      = 6,          // [8:6]   RO:1:表示丢帧    
    BIT_BUSY_ID_STA1           = 0,          // [5:0]   RO:坑ID实时状态        
} ENUM_BIT_SCAN_STA0;

/* ASM_SCAN_STA1 bit信息  RO  10 */
typedef enum
{
    BIT_HW_MON_TIMEOUT_STA    = 15,           // [15]  RO: 1:超时
    BIT_LPF_MODE_EN_STA       = 14,           // [14]  RO: 1:skip frame 状态
    BIT_LPF_MODE_TP_TURBO_ACK = 13,           // [13]  RO: 0:不开坑  1:开坑
    BIT_VB_MODE_ACK = 12,                     // [12]  RO: 0:小坑    1:大坑 
    BIT_TP_BUSY     = 11,                     // [11]  RO: TP busy的实时状态
    BIT_LCD_BUSY    = 10,                     // [10]  RO: LCD busy的实时状态                   
    //BIT_TAIL_MARGIN = 0,                      // [9:0] RO: TP每段扫描的尾余量                        
} ENUM_BIT_SCAN_STA1;

/* ASM_SCAN_STA2 bit信息  RO  11 */
typedef enum
{    
    BIT_AFE_WR_ARAM_AVAIL_N  = 12,            // [12]   RO: 1: 当前不可以写ARAM
    BIT_STB_ID       = 6,                     // [11:6] RO:LCD打点计数器的实时状态                  
    BIT_STB_TICK_ID  = 0,                     // [5:0]  RO:LCD打点时，计数器的状态，经过mask后            
} ENUM_BIT_SCAN_STA2;

/* ASM_SCAN_STA2 bit信息  RO  12 */
typedef enum
{    
    BIT_BUSY_ID_MAX  = 6,                     // [11:6] RO:最大坑号               
    BIT_BUSY_ID_MIN  = 0,                     // [5:0]  RO:最小坑号         
} ENUM_BIT_SCAN_STA3;

/* ASM_SCAN_CTRL bit信息 WO 13*/
typedef enum
{             
    BIT_AFE_WR_ARAM_AVAIL_N_CLR = 2,          // [2] WO: 1:可以操作ARAM
    BIT_BUSY_ID_MAX_RESET   = 1,              // [1] WO: 坑统计计数器最大值复位，写1复位            
    BIT_SCAN_START          = 0,              // [0] WO: 启动扫描                       
} ENUM_BIT_ASM_SCAN_CTRL;

/* ASM_SCAN_CFG0 bit信息 14 */
typedef enum
{
    BIT_MONITOR_MODE         = 15,              // [15]硬件触摸检测模式: 1: 是；      0:否   
    BIT_CB_ADJUST_MODE       = 14,              // [14]CB校正模式:       1:校正模式   0:正常模式           
    BIT_AFE_CLKGATE_EN       = 12,              // [12]自动门控AFE时钟:  1:自动门控 0:不自动门控 
    BIT_SCAN_START_STORE_EN  = 10,              // [10]1:保存，自动启动下一次扫描，0:不保存，不自动启动下次扫描。        
    BIT_LCD_FRAME_HEAD_ALIGN = 9,               // [9]第0帧的启动时刻选择:0:当前LCD帧开始剩余坑扫描; 1:错过ID,下LCD帧开始扫描    
    BIT_VBLANK_EDGE_SEL      = 8,               // [8]busy_id清零信号选择: 0:上升沿 ；1: 下降沿  
    BIT_VSTART_EDGE_SEL      = 7,               // [7]busy_id清零信号选择: 0:上升沿 ；1: 下降沿      
    BIT_VMID_EDGE_SEL        = 6,               // [6]busy_id清零信号选择: 0:上升沿 ；1: 下降沿 
    BIT_VEND_EDGE_SEL        = 5,               // [5]busy_id清零信号选择: 0:上升沿 ；1: 下降沿 
    BIT_CLR_BUSY_ID_SEL      = 3,               // [4:3] 清零信号选择: 0:vstart; 1:vmid 2:vend 3:vblank
    BIT_TP_FRAME_NUM         = 0,               // [2:0]多帧扫描的总帧数 0-3: 扫描1-4个TP帧   CB:4-7 扫描5-8个TP帧  
} ENUM_BIT_ASM_SCAN_CFG0;

/* ASM_SCAN_CFG1 bit信息 15*/
typedef enum
{
    BIT_LCD_RUN_INTPHASE     = 15,              // [15] LCD RUN 中断电平选择，0:低电平，1:高电平  
    BIT_LCD_DSTB_INTPHASE    = 14,              // [14] LCD Deep Standby中断电平选择，0:低电平，1:高电平  
    BIT_LPF_MODE_TP_TURBO_REQ= 9,               // [9]:Tp请求LCD在skip frame时，是否开坑。0:不开坑，1:开坑。 
    BIT_VB_MODE_REQ          = 8,               // [8]:Tp请求LCD切换大小坑.               0:小坑(120hz)，  1:大坑(60hz)。
    BIT_TP_END_SEL           = 5,               // [5] TP帧结束标志选择. 0:tp frane end;  1:aram ready
    BIT_STB_EN               = 4,               // [4] 预先加载参数，如CB shift使能: 1:使能         
    BIT_HW_MONITOR_EN        = 3,               // [3] 硬件Monitor使能；           1: 使能 
    BIT_VBLANK_INV           = 1,               // [1] Vblank有效电平选择，用于中断, 0:高电平，1:低电平   
} ENUM_BIT_ASM_SCAN_CFG1;

/* ASM TP FRAME CFG0 bit信息 16*/
typedef enum
{
    BIT_TAB_ID1              = 14,              // [14] 第1个TP帧用的Table表号  
    BIT_BUSY_ID1             = 8,               // [8] 第1个TP帧起始坑号        
    BIT_TAB_ID0              = 6,               // [6] 第0个TP帧用的Table表号     
    BIT_BUSY_ID0             = 0,               // [0] 第0个TP帧起始坑号 
} ENUM_BIT_ASM_TP_FRAME_CFG0;

/* ASM TP FRAME CFG1 bit信息 17*/
typedef enum
{
    BIT_TAB_ID3              = 14,              // [14] 第3个TP帧用的Table表号  
    BIT_BUSY_ID3             = 8,               // [8] 第3个TP帧起始坑号        
    BIT_TAB_ID2              = 6,               // [6] 第2个TP帧用的Table表号     
    BIT_BUSY_ID2             = 0,               // [0] 第2个TP帧起始坑号 
} ENUM_BIT_ASM_TP_FRAME_CFG1;

/* ASM TP FRAME CFG2 bit信息 18*/
typedef enum
{
    BIT_BUSY_ID5             = 8,               // [8] 第5个TP帧起始坑号        
    BIT_BUSY_ID4             = 0,               // [0] 第4个TP帧起始坑号 
} ENUM_BIT_ASM_TP_FRAME_CFG2;

/* ASM TP FRAME CFG3 bit信息 19*/
typedef enum
{
    BIT_BUSY_ID7             = 8,               // [8] 第7个TP帧起始坑号        
    BIT_BUSY_ID6             = 0,               // [0] 第6个TP帧起始坑号 
} ENUM_BIT_ASM_TP_FRAME_CFG3;

/*ASM_ SCAN_DELAY  bit信息 20 */
typedef enum
{
    BIT_TAB_EN3             = 13,               // [13] Tab3表使能: 1:使能 
    BIT_TAB_EN2             = 12,               // [12] Tab2表使能: 1:使能 
    BIT_TAB_EN1             = 11,               // [11] Tab1表使能: 1:使能 
    BIT_TAB_EN0             = 10,               // [10] Tab0表使能: 1:使能 
    BIT_SCAN_DELAY          = 0,                // [9:0]LCD RUN下降沿到扫描开始的延时
}ENUM_BIT_ASM_SCAN_DELAY;

/*ASM STB MASK L   bit信息 21 */
typedef enum
{
    BIT_STB_MASK_L          = 0,                // [15:0]STB_TICK中断屏蔽设置低位
}ENUM_BIT_STB_MASK_L;

/*ASM STB MASK H   bit信息 22 */
typedef enum
{
    BIT_STB_MASK_H          = 0,                // [15:0]STB_TICK中断屏蔽设置高位
}ENUM_BIT_STB_MASK_H;

/*ASM ARAM BASE L  bit信息 23 */
typedef enum
{
    BIT_ARAM_BASE_L         = 0,                // [9:0]左AFE数据在ARAM中存放的基地址
}ENUM_BIT_ARAM_BASE_L; 

/*ASM ARAM BASE R  bit信息 24*/
typedef enum
{
    BIT_ARAM_BASE_R         = 0,                // [9:0]右AFE数据在ARAM中存放的基地址
}ENUM_BIT_ARAM_BASE_R;

/*ASM ARAM BASE KEY bit信息 25*/
typedef enum
{
    BIT_ARAM_BASE_KEY       = 0,                // [9:0]KEY数据在ARAM中存放的基地址
}ENUM_BIT_ARAM_BASE_KEY; 

/*ASM CB BASE L  bit信息 26 */
typedef enum
{
    BIT_CB_BASE_L           = 0,                // [9:0]左CB数据在ARAM中存放的基地址
}ENUM_BIT_CB_BASE_L;

/*ASM CB BASE R  bit信息 27 */
typedef enum
{
    BIT_CB_BASE_R           = 0,                // [9:0]右CB数据在ARAM中存放的基地址
}ENUM_BIT_CB_BASE_R;

/*ASM CB BASE KEY bit信息 28 */
typedef enum
{
    BIT_CB_BASE_KEY         = 0,                // [9:0]KEY CB数据在ARAM中存放的基地址
}ENUM_BIT_CB_BASE_KEY; 

/* ASM TAIL MARGIN bit信息 29 */
typedef enum
{
	BIT_TAIL_MARGIN         = 0,                // [9:0]RO tp每段扫描的尾余量.
}ENUM_BIT_TAIL_MARGIN;

/*ASM PWR CTRL bit信息 32*/
typedef enum
{
    BIT_PWROFF_AUTO           = 3,             //[3]是否在扫描完成后自动下电,该寄存器对hw mon模式不起作用.0:否;1:是
    BIT_HWMON_PWR_EN          = 2,             //[2]是否在hw mon模式下控制上下电时序.0:不控制;1:控制
    BIT_PWROFF_START          = 1,             //[1]写1开始下电时序，硬件自动清零，读出为0
    BIT_PWRON_START           = 0,             //[0]写1开始上电时序，硬件自动清零，读出为0
}ENUM_BIT_PWR_CTRL;

/*ASM PWR STA bit信息 33*/
typedef enum
{
    BIT_PWR_STA               = 0,             //[0]指示自动上下电模块的上电和下电状态.0:当前为下电完成状态;1:当前为上电完成状态
}ENUM_BIT_PWR_STA;


/*ASM PWR INTERVAL0 bit信息 34*/
typedef enum
{
    BIT_T1_DSVR_BGPR          = 8,             //[15:8]DSV_EN上升沿后到NVDD2_MASK,VDD_TP_MASK_N1和BGP_MASK上升沿的时钟个数(rtc clk)=t1+1               
    BIT_T2_BGPR_REFBGR        = 4,             //[7:4] NVDD2_MASK,VDD_TP_MASK_N1上升沿到VDD_TP_MASK[3:2]和REFBG_EN上升沿的时钟个数 =t2+1
    BIT_T3_REFBGR_REFOPR      = 0,             //[3:0]VDD_TP_MASK[3:2]和REFBG_EN上升沿到VREFTP_SETOP_EN上升沿的时钟个数=t3+1
}ENUM_BIT_PWR_INTERVAL0;

/*ASM PWR INTERVAL1 bit信息 35*/
typedef enum
{
    BIT_T4_REFOPR_REFBUFR     = 12,            //[15:12]VREFTP_SETOP_EN上升沿到VREFTP_BUF_EN上升沿的rtc时钟个数=t4
    BIT_T5_REFOPR_REFSHR      = 8,             //[11:8]VREFTP_SETOP_EN上升沿到VREFTP_SH上升沿的时钟个数=t5
    BIT_T6_REFSH_WIDTH        = 0,             //[7:0] VREFTP_SH宽度RTC时钟个数=t6
}ENUM_BIT_PWR_INTERVAL1;

/*ASM PWR INTERVAL2 bit信息 36*/
typedef enum
{
    BIT_T7_REFBUFR_REFSRR     = 8,              //[15:8] VREFTP_BUF上升沿到VREFTP_SR_CTRL上升沿的时钟个数=t7+1
    BIT_T8_SRCTRLR_PWRON      = 0,              //[7:0]  VREFTP_SRCTRL和VDD5_SRCTRL最晚的上升沿到power稳定可以做扫描的上升沿的时钟个数=t8+1
}ENUM_BIT_PWR_INTERVAL2;

/*ASM PWR INTERVAL3 bit信息 37*/
typedef enum
{
    T9_REFBUFR_VDD5SRR        = 8,              //[15:8]VREFTP_BUF上升沿到VDD5_SRCTRL上升沿的时钟个数=t9+1
    T10_TPBUSYF_REFBGF        = 4,              //[7:4] TP_BUSY下降沿到REFBG_EN下降沿的时钟个数=t10+1
    T11_REFBGF_BGPF           = 0,              //[3:0] REFBG_E下降沿到BGP_MASK下降沿的rtc时钟个数=t11+1
}ENUM_BIT_PWR_INTERVAL3;

/*ASM PWR INTERVAL4 bit信息 38*/
typedef enum
{
    T12_BGPF_DSVF            = 12,             //[15:12]BGP_MASK下降沿到DSV_EN下降沿的时钟个数=t12+1
    T_OPENAFECLK_TPSCAN      = 0,              //[4:0]  打开AFE时钟可启动扫描的rtc时钟个数=t+1
}ENMU_BIT_PWR_INTERVAL4;


/*ASM HW MON TIMER bit信息 39*/
typedef enum
{
    BIT_HW_MON_TIMER          = 0             // [11:0] 用于rtc硬件monitor模式,当RTC_INT中断次数达到hw_mon_timer+1,
                                              //        会产生timeout中断(若使能中断) .此时AFE只扫描hw_mon_tiemr次 
}ENUM_BIT_HW_MON_TIMER;

/*ASM VREFSH CFG LCDON bit信息 40*/
typedef enum
{
    BIT_VREFSH_REFSEL_LCDON   = 12,           // [12] 亮屏下TP2XTP_VREFTP_SH上升沿参考信号选择
                                              //      0:vbp信号上升沿;1:lcd_vend信号上升沿
    BIT_VREFSH_DLY_LCDON      = 8,            // [11:8] 亮屏下TP2XTP_VREFTP_SH延时，以250khz计数
    BIT_VREFSH_WIDTH_LCDON    = 0             // [7:0]  亮屏下TP2XTP_VREFTP_SH宽度，以250khz计数
}ENUM_BIT_VREFSH_CFG_LCDON;

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern volatile UINT16 XRAM g_usAsmIntSta;
extern ST_AsmRegisters * XRAM pAsmRegs;
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void DrvAsmSetPhase(void);
void Asm_Config_Init(void);
void DrvLoadTabSingle(UINT8 ucTabId,UINT8 ucBusyID);
void DrvLoadTabMultiple(UINT8 ucBusyId0,UINT8 ucBusyId1,UINT8 ucBusyId2,UINT8 ucBusyId3,UINT8 ucScanMul,UINT8 ucTab);

void DrvAsmInterEnable0(UINT16 usInterMode);
void DrvAsmInterDisable0(UINT16 usInterMode);
void DrvAsmInterEnable1(UINT16 usInterMode);
void DrvAsmInterDisable1(UINT16 usInterMode);
void DrvAsmInterClear0(UINT16 usClearMode);
UINT16 DrvAsmGetSta(void);
UINT16 DrvAsmGetSta1(void);
void DrvAsmSetIDReset(void);
void DrvAsmSetPhase(void);
void DrvAsmSeStbtMask(UINT16 usMask);
void DrvAsmScanStart(void);
void DrvAsmAramAvail(void);
void DrvAsmMonitoModeInit(void);
void DrvAsmReq60hz_Big_LcdBusy(void);
void DrvAsmReq120hz_Small_LcdBusy(void);
void AppGetAsmState(void);
void DrvAsmWakeEnable0(UINT16 usWakeMode);
void DrvAsmWakeEnable1(UINT16 usWakeMode);
void DrvAsmSetCBAdjustMode(UINT8 ucModeEn);
void DrvLoadTabCB(UINT8 ucTabId,ENUM_AFE_MODE ucCbMode);
void DrvGetAramCb(void);
void DrvGetAramRawData(void);
void DrvAsmSetRtcMonitorMode(UINT8 ucModeEn);
void DrvAsmSetRtcMonitorTimer(UINT16 ucTimer);
void DrvAsmSetHwMonPwrEn(UINT8 ucEn);
void DrvAsmSetRTCMoniroMode(UINT8 ucModeEn);
void DrvAsmRtcMonitoModeInit(void);
void DrvAsmClrInt(void);
void DrvAsmSetPwrOn(void);
void DrvAsmSetPwrOff(void);
void DrvGetAdcData(UINT16 ucLen);
void DrvAsmWakeDisable0(UINT16 usWakeMode);
void DrvAsmWakeDisable1(UINT16 usWakeMode);
void DrvAsmInterDisableAll(void);
void DrvAsmAfeClkGateEn(void);

#endif
