/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: CfgPanelPara.h
*
*    Author: linjianjun
*
*   Created: 2013-12-01
*
*  Abstract: Please describe the interface in detail for this module
*
*  只有CfgAutoTune.c，才能包含此文件
*
* Reference:
*
*******************************************************************************/
#ifndef _CFG_PANEL_PARA_H_
#define _CFG_PANEL_PARA_H_

#ifdef __CFG_AUTO_TUNE_C__

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "CfgSystem.h"
#include "AppDataStruct.h"

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

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/******************************************************************************/
/* 1. 常用参数 */
/******************************************************************************/
#define CFG_PROJECT_CODE        "FT8835"  /* 字符串长度不大于31个字节 "FTS8835P001"  */
#define CFG_CUSTOMER_CODE       "COB"     /* 字符串长度不大于15个字节 "0123456789123" "001" */
#define RV_G_FIRMID             0x8a          /* 格式必须为十六进制 (0x00)   读取寄存器 0xA6, 客户Firmware版本信息，每更新一次Firmware版本号+1 */

/* 格式必须为十六进制 (0x01)   读取寄存器 0xAD, 开发或调试阶段的 Firmware版本信息，每更新一次Firmware版本号+1 ，便于在调试阶段进行版本记录*/
#define RV_G_FIRM_DEBUG_ID      0x01

#define RV_G_LIB_VERSION_H      0x00    /* App Lib version high */
#define RV_G_LIB_VERSION_L      0x01    /* App Lib version low ---同一项目，每打包一次加1 */

/******************************************************************************/
// 2. 通道配置
/******************************************************************************/
#if 0
#define CH_X_NUM_S0             7
#define CH_X_NUM_S1             8
#define CH_X_NUM_LOCAL          (CH_X_NUM_S0 + CH_X_NUM_S1)
#define CH_Y_NUM_LOCAL          26
#define CH_X_NUM_VA             CH_X_NUM_LOCAL
#define CH_Y_NUM_VA             CH_Y_NUM_LOCAL

#define RV_CH_VALID_S0          (CH_X_NUM_S0*CH_Y_NUM_LOCAL)
#define RV_CH_VALID_S1          (CH_X_NUM_S1*CH_Y_NUM_LOCAL)

#define RV_CH_START_S0          6
#define RV_CH_NUM_S0            (CH_X_NUM_S0*CH_Y_NUM_LOCAL)

#define RV_CH_START_S1          8
#define RV_CH_NUM_S1            (CH_X_NUM_S1*CH_Y_NUM_LOCAL)

#define AREA_S0_AS_AFE1         0  /* 0:means S0 as AFE0, 1:means S0 as AFE1 */

#define RV_CH_ORDER  {\
     31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,\
     57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32,\
     83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58,\
    109,108,107,106,105,104,103,102,101,100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84,\
    135,134,133,132,131,130,129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,\
    161,160,159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144,143,142,141,140,139,138,137,136,\
    187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171,170,169,168,167,166,165,164,163,162,\
    \
    190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,\
    164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,\
    138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,\
    112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,\
     86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,\
     60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,\
     34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,\
      3,  5,  6, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,\
}
#else//全通道排列
#define CH_X_NUM_S0             8     // S0半屏的列数
#define CH_X_NUM_S1             8     // S1半屏的列数

#define CH_X_NUM_LOCAL          16    // (CH_X_NUM_S0 + CH_X_NUM_S1) X通道的总列数
#define CH_Y_NUM_LOCAL          28    // Y通道的行数
#define CH_X_NUM_VA             CH_X_NUM_LOCAL
#define CH_Y_NUM_VA             CH_Y_NUM_LOCAL

#define RV_CH_VALID_S0          224    // (CH_X_NUM_S0*CH_Y_NUM_LOCAL) S0 有效通道数
#define RV_CH_VALID_S1          224    // (CH_X_NUM_S1*CH_Y_NUM_LOCAL) S1 有效通道数

#define RV_CH_START_S0          3      // S0半屏最小通道编号
#define RV_CH_NUM_S0            224    // (CH_X_NUM_S0*CH_Y_NUM_LOCAL) S0半屏总通道数 
#define RV_CH_START_S1          3     // S1半屏最小通道编号
#define RV_CH_NUM_S1            224    // (CH_X_NUM_S1*CH_Y_NUM_LOCAL) S1半屏总通道数 

#define AREA_S0_AS_AFE1         0      /* 0:means S0 as AFE0, 1:means S0 as AFE1 */

#define RV_CH_ORDER  {\
  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14,  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,\
  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,  32,  31,\
  86,  85,  84,  83,  82,  81,  80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,  65,  64,  63,  62,  61,  60,  59,\
 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100,  99,  98,  97,  96,  95,  94,  93,  92,  91,  90,  89,  88,  87,\
 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115,\
 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143,\
 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171,\
 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199,\
\
 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226,\
 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198,\
 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,\
 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,\
  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,\
  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,\
  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,\
   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,\
}

#endif
/******************************************************************************/
// 3. 系统配置
/******************************************************************************/
#define IO_LEVEL_SELECTION      0       /* 0:1.8V; 1:3.3V */
#define I2C_SLAVE_ADDR          0x70

#define SYS_MAX_POINT           5       /* 支持的报点点数 */

#define SYS_PEAK_NOISE          140      /* Diff需要减去的噪声 */

/* 看门狗复位时间--单位ms */
#define WDT_OVER_TIME_CLB       3500    //3500 ms
#define WDT_OVER_TIME_FLOW      200     //200 ms

/******************************************************************************/
// 4. 扫描模式配置
/******************************************************************************/
#define K1_DELAY                30
#define K2_DELAY                15
#define SCAN_CF                 5
#define SCAN_KEY_CF             5
#if (SYS_KEY_DRV_MODE == KEY_DRV_MODE_MUTI)
#define KEY_MODE_SEL            KEY_DRV_MODE_MUTI
#else
#define KEY_MODE_SEL            KEY_DRV_MODE_SELF
#endif
//------------------------------------------------------------------------------
/* FreeRun模式 参数 */
#define MOD_FREE_SYNC_NUM       SNUM02           /* 0---15; 表示N+1个小段数量 */
#define MOD_FREE_SEG_CYCLE      5//15               /* 0:表示1,每段的扫描次数 */

//------------------------------------------------------------------------------
/* Monitor 参数 */
#define MOD_M_SYNC_NUM          SNUM01           /* 0---15; 表示N+1个小段数量 */
#define MOD_M_SEG_CYCLE         6                /* 0:表示1,每段的扫描次数 */

//------------------------------------------------------------------------------
/* Active Normal模式 参数 */
#if (SYS_PANEL_TYPE  == PANEL_TYPE_120HZ_NORMAL)
#define MOD_NORMAL_SYNC_NUM     SNUM03           /* 0---15; 表示N+1个小段数量 */
#define MOD_NORMAL_SEG_CYCLE    4                /* 0:表示1,每段的扫描次数 */
#elif (SYS_PANEL_TYPE  == PANEL_TYPE_120HZ_CBT)
#define MOD_NORMAL_SYNC_NUM     SNUM01           /* 0---15; 表示N+1个小段数量 */
#define MOD_NORMAL_SEG_CYCLE    7                /* 0:表示1,每段的扫描次数 */
#else
#define MOD_NORMAL_SYNC_NUM     SNUM01           /* 0---15; 表示N+1个小段数量 */
#define MOD_NORMAL_SEG_CYCLE    5               /* 0:表示1,每段的扫描次数 */
#endif

//------------------------------------------------------------------------------
/* Active Special模式 参数 */
#define MOD_SPEC_SYNC_NUM       SNUM09           /* 0---15; 表示N+1个小段数量 */
#define MOD_SPEC_SEG_CYCLE      0                /* 0:表示1,每段的扫描次数 */

/* 60Hz快速校正参数, 开启SC_60HZ_FAST_CLB时该参数有效
   开启后，60Hz模式下，上电时会切换到120Hz多段模式进行CB校准，以加快CB校准速度 */
#define MOD_60HZ_CLB_SYNC_NUM   SNUM01           /* 0---15; 表示N+1个小段数量 */
#define MOD_60HZ_CLB_SEG_CYCLE  0                /* 0:表示1,每段的扫描次数 */
/******************************************************************************/
// 5.阈值设置
/******************************************************************************/
#define RV_G_VA_GROUP_THR       900//350//230//600//350//250                  /* VA区正常触摸触摸阈值 */
#define RV_G_VA_PEAK_THR        700//200//300//200//500//300//200             /* VA区正常触摸正PEAK计算阈值 */
#define RV_G_VA_PEAK_THR_NEG    700//300//200//500//300//200                  /* VA区正常触摸负PEAK计算阈值 */
#define RV_G_VK_TOUCH_THR       1500                 /* 按键区正常触摸触摸阈值 */
#define RV_G_VK_PEAK_THR        1200                 /* 按键区正常触摸正PEAK计算阈值 */
#define RV_G_VK_PEAK_THR_NEG    1200                 /* 按键区正常触摸负PEAK计算阈值 */
#define RV_G_AREA_THR           600                  /* 大面积统计正PEAK计算阈值 */
#define RV_G_AREA_THR_NEG       600                  /* 大面积统计负PEAK计算阈值 */

/******************************************************************************/
// 6. 跳频相关
/******************************************************************************/
#define RV_FREQ_LIST            {K1_DELAY, 15, 20} /* 跳频频率表,调屏时需保证最低频率在所有可能的模式下不会发生scan drop */
#define RV_SW_NOISE_THR         (RV_G_VA_GROUP_THR*2)       /* 纯软件噪声检测阈值 */
#define RV_SW_DC_NOISE_THR      (RV_G_VA_GROUP_THR)         /* 软硬结合判断时的软件噪声阈值 */
#define RV_SW_NOISE_HIGH_THR    (RV_G_VA_GROUP_THR*4)       /* 软件大噪声检测阈值 */
#define RV_HW_NOISE_THR         80                          /* 硬件噪声检测阈值 */
#define RV_POLLING_TIMES        4                           /* 噪声检测的周期数 */

/******************************************************************************/
// 7.LCD mapping
/******************************************************************************/
#define X_CHANNEL               USE_TX_AS_X_CHANNEL     /*0 :X 坐标采用的 TX映射, 1: X 坐标采用的 RX映射*/

#define MAPPING_MAX_X            720  /* X方向Mapping最大像素个数 */
#define MAPPING_MAX_Y           1280  /* Y方向Mapping最大像素个数 */

#define VA_X_LEFT                448  /* X方向左半区域最大原始坐标+1 */
#define VA_Y_UP                  576  /* Y方向上半区域最大原始坐标+1 */

#define LCD_X_L_MAPPING          339  /* X方向左半区域最大像素个数 */
#define LCD_Y_U_MAPPING          431  /* Y方向上半区域最大像素个数 */

/* 根据_Mapping参数计算表格计算出的参数值, 可能根据实际情况需要微调 */

#define LCD_X_L_EDGE              45//43  /* X方向左边缘Mapping像素个数 */
#define LCD_X_R_EDGE              42  /* X方向右边缘Mapping像素个数 */

#define LCD_Y_U_EDGE              41  /* Y方向上边缘Mapping像素个数 */
#define LCD_Y_D_EDGE              50  /* Y方向下边缘Mapping像素个数 */

#define K_X_MID_LEFT             (195)//(193)  /* X方向中央左半区Mapping系数 */
#define K_X_MID_RIGHT            (192)  /* X方向中央右半区Mapping系数 */

#define K_Y_MID_UP               (192+1)  /* Y方向中央上半区Mapping系数 */
#define K_Y_MID_DOWN             (199+1)  /* Y方向中央下半区Mapping系数 */

#define K_X_L_EDGE               (496-70)  /* X方向左边缘Mapping系数 */
#define K_X_R_EDGE               (515-60)  /* X方向右边缘Mapping系数 */

#define K_Y_U_EDGE               (440+0)  /* Y方向上边缘Mapping系数 */
#define K_Y_D_EDGE               (440+0)  /* Y方向下边缘Mapping系数 */

/******************************************************************************/
// 8. 虚拟按键
/******************************************************************************/
#define RV_KEY_EN_A0            (KS1_01|KS1_02|KS1_03)            /* 000 -- 111, 左AFE按键使能位，低3位有效 */
#define RV_KEY_EN_A1            (KS1_01|KS1_02|KS1_03)            /* 000 -- 111, 右AFE按键使能位，低3位有效 */

/* 虚拟按键输出坐标--与Host约定 */
#define TOUCH_KEY_POS_X_OUT     {180,360,540}            /* 虚拟按键X报点坐标 */
#define TOUCH_KEY_POS_Y_OUT     1350                     /* 虚拟按键Y报点坐标 */

/******************************************************************************/
// 9.寄存器参数
/******************************************************************************/
/* 第一次按下时的触摸阈值，防止触摸抖动---一般大于阈值 */
#define RV_G_THG_TOUCHDOW       (RV_G_VA_GROUP_THR + (RV_G_VA_GROUP_THR>>2))

#define RV_G_MOVE_THDIFF        2560        /* 点移动滤波的 距离diff值 */

#define RV_G_TIME_ENTER_MONITOR 2           /* 进入Monitor状态时间 单位s */
#define RV_G_FREE_ACTIVE_RPT    6           /* Free Run: Active period time 1:10Hz,2:20Hz,... */
#define RV_G_FREE_MONITOR_TIME  33          /* Free Run: Monitor period time  monitor 33Hz报点 */

#define RV_G_LCD_VSYC_HZ        60          /* LCD显示的帧率 */
#define RV_G_RTC_DEVI           20          /* RTC 定时器偏差系数，24为无偏差，小于24为RTC定时器实际中断间隔大于1ms，大于24为RTC定时器实际中断间隔小于1ms */

#define RV_G_PMODE              PM_ACTIVE   /* Default mode */
#define RV_G_INT_MODE           1           /* 中断方式 */
#define RV_G_STATE              SS_WORK     /* 运行状态 */

#define RV_G_IC_TYPE            0x01        /* IC名称 */
#define RV_G_FIRMID_NEG         (~RV_G_FIRMID)
#define RV_G_VENDORID           0x86        /* 屏厂ID，区分客户的不同屏厂 */
#define RV_G_VENDORID_NEG       (~RV_G_VENDORID)
#define RV_G_CHIPER_HIGH        0x86        /* Chip ID: FT8606的芯片ID，用于不同型号芯片的区分，芯片ID请不要修改 */
#define RV_G_CHIPER_LOW         0x06
#define RV_G_CUS_HW_ID          0x01        /* customer hw id */
#define RV_G_VENDORPANEL_ID     0x01        /* verdor panel hw id */
#define RV_G_LCDINITCODE_ID     0x01        /* lcd initcode id */

#define RV_G_RELEASE_ID_H       0x01        /* 格式必须为十六进制 (0x00)  Firmware公版版本ID_H，用于区分Firmware公版的不同版本 */
#define RV_G_RELEASE_ID_L       0x01        /* 格式必须为十六进制 (0x00)  Firmware公版版本ID_L，用于区分Firmware公版的不同版本 */

#define RV_G_UCTHPREFACTOR      4           /* for touch pressure, default value is 7, stand for 127 */
#define RV_G_USTHTOUCHSIZE      100

#define RV_G_IC_VERSION         0x01        /* IC version 0x01:A  0x02:B  0x03:C  and so forth */
#define RV_G_CHARGER_STATE      0           /* 1: Charger in   0: charger out, 充电器状态 */

/******************************************************************************/
// 10. CFG Global全局功能模块使能配置, 与CfgGlobal.h中的配置意义不一样，
// 在CfgGlobal.h 中相应的模块使能之后，这里的配置才有意义，这里的配置解决模块包含
// 之后用不用的问题，主要用于工具参数化调屏
/******************************************************************************/
#define RV_G_LED_MODULE_EN              0   /* Led灯使能 */
#define RV_G_NOISE_COLLECT_EN           1   /* 软硬件噪声收集使能, 跳频或扫频开启时必须开启 */
#define RV_G_PRESSURESIZE_VALID_EN      0   /* 触摸压力及触摸面积处理使能，寄存器使能 */
#define RV_G_REPORT_EVEN_NUM_EN         0   /* 只报事件数使能 */
#define RV_G_GESTURE_EN                 1   /* 普通手势使能: 放大，缩小, 上下左右 */
#define RV_G_VIRTUAL_KEY_EN             1   /* 虚拟按键使能 */
#define RV_G_POS_MAPPING_EN             1   /* 坐标映射使能 */
#define RV_G_BASE_COMPENSATE_EN         1   /* Base跟踪处理使能 */
#define RV_G_POINT_ID_PROC_EN           1   /* ID号匹配使能 */

#define RV_G_PEAK_MERGE_PROCESS_EN      1   /* Peak合并使能 */
#define RV_G_FLYING_LINE_PROC_EN        1   /* 多指快速敲击连线处理使能 */
#define RV_G_POINT_TOUCH_FIILTER_EN     1   /* 坐标平滑处理使能 */

#define RV_G_LINE_NOISE_FLT_EN          1   /* 整行抬起滤波使能 */
#define RV_G_COL_NOISE_FLT_EN           1   /* 整列抬起滤波开关 */
#define RV_G_POINTS_STABLE_HANDLE_EN    1   /* 点稳定处理使能 */
#define RV_G_DEFER_FILTER_EN            1   /* 新增点延迟报点使能 */
#define RV_G_LIFT_UP_FILTER_EN          1   /* 抬手延迟一帧报抬起事件使能 */
#define RV_G_PWR_FILTER_EN              1   /* 电源干扰滤波使能 */
#define RB_G_FRAME_FILTER_EN            1   /* 帧滤波使能 */
#define RV_G_ESD_NOISE_HANDLE_EN        1   /* ESD处理使能 */
#define RV_G_HP_PROCESS_EN              1   /* 重压使能 */

#define RV_G_PWR_MANAGER_EN             1   /* 电源功耗管理使能，寄存器使能 */
#define RV_G_MONITOR_DET_EN             1   /* 硬件触摸检测使能, 降功耗, _PWR_MANAGER_EN开启时有效 */
#define RV_G_PALM_REJECTION_EN          1   /* 大手掌检测使能 */
#define RV_G_SC_FREQ_HOPPING_EN         1   /* 跳频使能 */
#define RV_G_SPEC_GESTURE_EN            0   /* 特殊手势使能, 寄存器使能 */
#define RV_G_LCD_PROCESS_EN             1   /* LCD噪声特征进行diff修正，滤掉假点使能 */
#define RV_G_RF_PROC_EN                 1   /* 抗RF干扰处理功能开关 */

// TBD.
#define RV_G_FACE_DEC_MODE              0   /* 接近感应 */
#define RV_G_HOVER_MODE                 0   /* 皮套 */
#define RV_G_GLOVE_MODE_EN              0   /* 手套支持 */
#define RV_G_PEN_MODE_EN                0   /* 被动笔 */

#define RV_G_EDGE_FILETER_COOR_LEFT     2   /* 边缘抑制左截边坐标范围 */
#define RV_G_EDGE_FILETER_COOR_RIGHT    2   /* 边缘抑制右截边坐标范围 */

/******************************************************************************/
// 11. base跟踪
/******************************************************************************/
#define FRAME_STABLE_TH                 300 /* 正常的噪声抖动范围 */ /* 帧稳定值，正常阈值的一半左右，要考虑极限噪声 */
#define BIG_AREA_SUM_TH                 ((CH_X_NUM_LOCAL * CH_Y_NUM_LOCAL) >> 3)
#define BASE_TRACE_STEP                 2   /* 每次BASE跟踪步长 */
#define BASE_TRACE_CNT                  1   /* 多少次跟踪一次BASE */
#define BASE_REFRESH_CNT                5   /* 多少次刷新一次BASE */

/******************************************************************************/
// 12. 帧滤波
/******************************************************************************/
#define FRAME_FILETR_MODE_EN            1   /* 模块使能 */
#define FRAME_FILTER_SUB_MAX_THR        2   /* 最多连续消点帧数 */
#define FRAME_FILTER_ADD_MAX_THR        2   /* 最多连续补点帧数 */
#define FRAME_FILTER_SUB_MAX_THR_NOISE  4
#define FRAME_FILTER_ADD_MAX_THR_NOISE  4
#define FRAME_FILTER_SKIP_START_FRAME   6   /* 触摸头N帧不做滤帧操作 */
#define FRAME_FILTER_BAND_WIDTH         128 /* 做滤帧处理的空间带宽 2*PITCH */

/******************************************************************************/
// 13. 重压
/******************************************************************************/
#define HP_RANGE_MIN                    200     /* 重压特征点的diff范围--min */
#define HP_RANGE_MAX                    5000    /* 重压特征点的diff范围--max */

/* 值小，越容易判断为重压 */
#define HP_NUM_PERPEAK                  8       /* 每个Peak周围变化量处于重压特征点范围的计算个数 */
#define HP_MIN_PEAK_NUM                 5       /* 全屏Peak个数默认值，当Peak个数小于该阈值时，按此阈值算 */

/* Peak 33区域的和与Peak的比值超过该阈值时，则认为是重压的可能性越大，该值越小，越容易判断为重压 */
#define HP_AROUND_RATIO                 6       /* Peak周围的和(不含Peak本身)与Peak本身的比值阈值 */
#define HP_LAST_TIME                    300     /* 重压形变恢复时间，单位ms */

#define HP_SMALL_PEAK_THR               600//500     /* 重压状态下的识别小Peak的阈值 */
#define HP_FIRST_ENTER_THR              800    /* 首次进入重压时最大diff必需大于该值 */
#define HP_OVERFLOW_THR                 8000    /* 全屏溢出变化量，当最大变化量超过该值时认为压力过重，不报点 */

/******************************************************************************/
// 14. 大面积消点处理
/******************************************************************************/
#define BIGAREA_PEAK_CNT                45      /* peak 周围点diff大于指定阈值计数，超过此值，认为是大面积 */
#define BIGAREA_PEAK_THR                500     /* 大面积Diff阈值,用来统计peak周围大于此阈值的节点数 */
#define BIGAREA_RECT_THR                700     /* 大面积矩形区域的阈值, 在此区域内的peak要消点处理*/
#define BIGAREA_RETAINING_TIMEOUT       20      /* 大面积退出delay帧数*/

/******************************************************************************/
// 15. 手势处理
/******************************************************************************/
/*响应手势的有效范围*/
#define SPEC_GESTURE_MARGIN_LEFT                   32//手势书写的截边规格,左右
#define SPEC_GESTURE_MARGIN_TOP                    0 //手势书写的截边规格,上下
#define SPEC_GESTURE_MARGIN_RIGHT               (MAPPING_MAX_X - SPEC_GESTURE_MARGIN_LEFT)
#define SPEC_GESTURE_MARGIN_BOTTOM              (MAPPING_MAX_Y- SPEC_GESTURE_MARGIN_TOP)

/*时间相关*/
/*1S=87 500MS=43 1500MS=130 2S=170*/
#define SPEC_GESTURE_TIMEOUT_1500MS                5000//1500 自定义手势时间较长,默认为5s
#define SPEC_GESTURE_TIMEOUT_ONETIME               SPEC_GESTURE_TIMEOUT_1500MS//87//手势书写的最大时间

/*直线手势的参数*/
#define SPEC_GESTURE_LINE_DELTA                    (MAPPING_MAX_X/CH_X_NUM_LOCAL)   //直线抖动最大范围
#define SPEC_GESTURE_TRACE_CURVATURE               30//直线手势的曲率
#define SPEC_GESTURE_TRACE_CURVATURE_STEP          128//直线手势的曲率计算步长
#define SPEC_GESTURE_TRACE_DISTX_Y                 300//非双击手势的书写最小坐标，
#define SPEC_GESTURE_TRACE_MINCOUNT                10//非双击手势的书写最小点数，
#define SPEC_GESTURE_TRACE_X_WIDTH_MIN             160//非双击手势的书写区域最小值，
#define SPEC_GESTURE_TRACE_Y_WIDTH_MIN          160
#define SPEC_GESTURE_DIST_START_TO_END_CLOSETO     100//开始点和结束点接近的判断标准
#define SPEC_GESTURE_VERT_LINE_Y_MIN               (MAPPING_MAX_Y>>2)//竖线手势的长度规格
#define SPEC_GESTURE_VERT_LINE_X_MAX               (MAPPING_MAX_X>>3)//竖线手势的宽度规格
#define SPEC_GESTURE_HORIZ_LINE_X_MIN              (MAPPING_MAX_X>>2)//横线手势的规格
#define SPEC_GESTURE_HORIZ_LINE_Y_MAX           (MAPPING_MAX_Y>>3)

#define SPEC_GESTURE_VERT_LINE_TIMEOUT_1000MS      1000 //竖线手势的最大书写时间
#define SPEC_GESTURE_VERT_LINE_TIMEOUT_60MS        60//竖线手势的最小书写时间
#define SPEC_GESTURE_HORIZ_LINE_TIMEOUT_1000MS  1000
#define SPEC_GESTURE_HORIZ_LINE_TIMEOUT_60MS    60

/*双击手势的参数*/

#define SPEC_GESTURE_DBLCLICK_DIST_10MM            10 //双击两点的距离规格,内部有x8
#define SPEC_GESTURE_DBLCLICK_STABLE_3MM           5 //双击单点的稳定，防止拖点成线,内部有x8

#define SPEC_GESTURE_DBLCLICK_MARGIN_LEFT          80//双击的截边要求 720pixel=6.0cm
#define SPEC_GESTURE_DBLCLICK_MARGIN_TOP           80//1280pixel=10.5cm
#define SPEC_GESTURE_DBLCLICK_MARGIN_RIGHT         (MAPPING_MAX_X - SPEC_GESTURE_DBLCLICK_MARGIN_LEFT)//720pixel=6.0cm
#define SPEC_GESTURE_DBLCLICK_MARGIN_BOTTOM        (MAPPING_MAX_Y - SPEC_GESTURE_DBLCLICK_MARGIN_TOP)//1280pixel=10.5cm

#define CLICK_TIME_OUT_500MS                       500 //双击单点的点击时间规格
#define DBLCLICK_TIME_OUT_800MS                    800 //双击的时间规格
#define DBLCLICK_TAIL_TIME_OUT_300MS               300 //双击的时间规格
#define DOUBLE_CLICK_INTERVAL_50MS                 50  //双击两点的时间间隔规格
#define DOUBLE_CLICK_INTERVAL_500MS             CLICK_TIME_OUT_500MS
#define DOUBLE_CLICK_SECONDUP_300MS                300 //双击第二次抬起的时间规格
#define DOUBLE_CLICK_NOPOINT_200MS                 200 //双击第二次抬起后没有点触摸的时间规格

#else // __CFG_AUTO_TUNE_C__
#warning  "[warning]: CfgPanelPara.h should not be included except CfgAutoTune.c"
#endif // __CFG_AUTO_TUNE_C__

#endif // _CFG_PANEL_PARA_H_

