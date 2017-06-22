/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: CfgAutoTune.h
*
*    Author: linjianjun
*
*   Created: 2013-02-01
*
*  Abstract: 
*            本文件包含自动调屏的模块结构体
*   注意，结构体作为联合体的成员，不能以数组开头，不然初始化，优先处理offset成员
*   导致过多初始化报错
* Reference:
*
*******************************************************************************/

#ifndef __CFG_AUTO_TUNE_H__
#define __CFG_AUTO_TUNE_H__

/*******************************************************************************
* Conditional Compiler Options
*******************************************************************************/


/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgPlatform.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define TX_NUM_LOCAL         16//24
#define RX_NUM_LOCAL         28//

#define TP_LIFT_CH_NUM       224
#define TP_RIGHT_CH_NUM      224
#define TP_LIFT_CH_OFFSET    0
#define TP_RIGHT_CH_OFFSET   0
#define TP_LIFT_KEY_NUM      3
#define TP_RIGHT_KEY_NUM     3
#define TP_KEY_NUM           (TP_LIFT_KEY_NUM + TP_RIGHT_KEY_NUM)
#define TP_CHANNEL_NUM       (TP_LIFT_CH_NUM + TP_RIGHT_CH_NUM)
#define TP_TOCAL_NUM         (TP_CHANNEL_NUM + TP_KEY_NUM)
#define TP_CH_OFFSET         (TP_LIFT_CH_OFFSET + TP_RIGHT_CH_OFFSET)

#define TP_CH_Y_NUM          16
#define CH_LIFT_Y_NUM        TP_CH_Y_NUM  
#define CH_RIGHT_Y_NUM       TP_CH_Y_NUM   
#define CH_LIFT_X_NUM        (TP_LIFT_CH_NUM - TP_LIFT_CH_OFFSET)/CH_LIFT_Y_NUM   
#define CH_RIGHT_X_NUM       (TP_RIGHT_CH_NUM - TP_RIGHT_CH_OFFSET)/CH_RIGHT_Y_NUM
#define TP_CH_X_NUM          (CH_LIFT_X_NUM + CH_RIGHT_X_NUM)    


// 4. 系统配置
#define IICEN                   /* Only for bin merge tool */
#define I2C_SLAVE_ADDR          0x70
#define I2C_SLAVE_ADDR_NEG      (~I2C_SLAVE_ADDR)

#define IO_LEVEL_SELECTION      IO_LVL_1_8V
#define SYC_IO_VOLTAGE_NEG      (~IO_LEVEL_SELECTION)
#define CFG_PROJECT_CODE        "FTS5822P000"
#define CFG_CUSTOMER_CODE       "001"

/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/
//------------------------------------------------------------------------------
/* 与host通信寄存器 */
typedef struct
{
    /* 以下部分与parameter的寄存器结构体一致，方便统一复制 */
    UINT8 ucPwrCtrl;                   /* 0x86 电源管理开关 */
    UINT8 ucTimeEnterMonitor;          /* 0x87 无触摸时进入monitor的时间 单位s */
    UINT8 ucPeriodActive;              /* 0x88 Active模式一帧的运行时间--index */
    UINT8 ucPeriodMonitor;             /* 0x89 Monitor模式一帧的运行时间 单位ms */
    UINT8 UNUSED_BYTE0;                /* 0x8A */
    UINT8 ucChargerState;              /* 0x8B 充电器插入指示标志（1 - 开，0 - 关）*/
    UINT8 UNUSED_BYTES_0[0x21-0x0C];   /* 0x8C--0xA0 */
    UINT8 ucLibVersionHigh;            /* 0xA1 App库文件版本号高字节 */
    UINT8 ucLibVersionLow;             /* 0xA2 App库文件版本号低字节 */
    UINT8 ucChiper;                    /* 0xA3 Chip type */
    UINT8 ucIntMode;                   /* 0xA4 1:INT trigger模式，0:INT polling模式 */
    UINT8 ucPMode;                     /* 0xA5 Power Mode：0:Active，1:Monitor，2:Sleep */
    UINT8 ucFirmId;                    /* 0xA6 Firmware version number */
    UINT8 ucState;                     /* 0xA7 工作状态（工作模式和工厂模式切换）*/
    UINT8 ucVendorId;                  /* 0xA8 Vendor ID（屏厂）*/
    UINT8 ucDriverVerH;                /* 0xA9 驱动库文件版本号高字节 */
    UINT8 ucDriverVerL;                /* 0xAA 驱动库文件版本号低字节 */
    UINT8 UNUSED_BYTES_1[0x2f-0x2B];   /* 0xAB--AE */
    UINT8 ucReleaseCodeId;             /* 0xAF 公版release code ID */
    UINT8 ucFaceDecMode;               /* 0xB0 近距离感应使能 (1:enable，0:disable)*/
    UINT8 ucIcVersion;                 /* 0xB1 IC version number: 0x01:A, 0x02:B, 0x03:C*/
    UINT8 ucPresizeEn;                 /* 0xB2 */
    UINT8 ucHoverMode;                 /* 0xB3 悬浮模式 (1:enable，0:disable)*/
    UINT8 UNUSED_BYTES_2[0x3e-0x34];   /* 0xB4--BD */
    UINT8 ucScanStatus;                /* 0xBE Scan扫描状态 */
    UINT8 UNUSED_BYTES_4;              /* 0xBF */

    UINT8 ucHighSensity;               /* 0xC0--高灵敏度模式 */
    UINT8 ucPenMode;                   /* 0xC1--笔模式 */
    UINT8 UNUSED_BYTES_5[0x50-0x42];   /* 0xC2--CF */

    UINT8 ucSpecGestureEn;             /* 0xD0 */   // Spec Gesture Mode Enable
    UINT8 ucSpecGestureConfig;         /* 0xD1 */   // Bit0 左滑,Bit1 右滑,Bit2 上滑,Bit3 下滑,Bit4 双击,Bit5 字符;
    UINT8 ucSpecGestureCHEn;           /* 0xD2 */   // Spec Gesture Character Enable,
    UINT8 ucSpecGestureCoor;           /* 0xD3 坐标输出buf0 */
    UINT8 ucSpecGestureCoor1;          /* 0xD4 坐标输出buf1 */
    UINT8 ucSpecGestureConfig1;        /* 0xD5 字符使能1 */
    UINT8 ucSpecGestureConfig2;        /* 0xD6 字符使能2 */
    UINT8 ucSpecGestureConfig3;        /* 0xD7 字符使能3 */
    UINT8 ucSpecGestureConfig4;        /* 0xD8 字符使能4 */
    UINT8 ucSpecGestureConfig5;        /* 0xD9 字符使能5 */
} ST_HOST_REG;

#endif

