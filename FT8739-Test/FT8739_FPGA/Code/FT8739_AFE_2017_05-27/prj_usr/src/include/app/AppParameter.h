/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: AppParameter.h
*
*    Author: linjianjun
*
*   Created: 2013-07-01
*
*  Abstract:
*  1.参数设置及其相关函数
*
* Reference:
*
* Version:
*
*******************************************************************************/

#ifndef _APP_PARAMETER_H_
#define _APP_PARAMETER_H_

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"
#include "CfgAutoTune.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
/* 工作模式寄存器总数 */
#define SYS_PARAM_LEN           64

#define REG_OUTPUT_ADDR_FIRST   0x01
#define REG_OUTPUT_ADDR_LAST    0x5E
#define REG_PARAM_ADDR_FIRST    0x80
#define REG_PARAM_ADDR_LAST     (REG_PARAM_ADDR_FIRST + ID_G_MAX)

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

// System Parameter Offsets and Normal Work Register Map
typedef enum
{
    ID_G_MC_THGROUP             =  0x00,
    ID_G_MC_THPEAK,             // 0x01
    ID_G_SC_THGROUP,            // 0x02
    ID_G_SC_TXTHPEAK,           // 0x03
    ID_G_SC_RXTHPEAK,           // 0x04
    ID_G_THDIFF,                // 0x05
    ID_G_PWR_CTRL,              // 0x06  Active and monitor ctrl en
    ID_G_TIMEENTERMONITOR,      // 0x07
    ID_G_PERIODACTIVE,          // 0x08
    ID_G_PERIODMONITOR,         // 0x09
    ID_G_CHARGER_STATE          =  0x0b,

    ID_G_LIB_VERSION_H          =  0x21,
    ID_G_LIB_VERSION_L,         // 0x22
    ID_G_CHIPER,                // 0x23
    ID_G_INT_MODE,              // 0x24
    ID_G_PMODE,                 // 0x25  //active monitor ... mode
    ID_G_FIRMID,                // 0x26
    ID_G_STATE,                 // 0x27
    ID_G_VENDORID,              // 0x28
    ID_G_DRVLIB_VER_H           =  0x29,
    ID_G_DRVLIB_VER_L           =  0x2a,
    ID_G_RELEASE_CODE_ID        =  0x2f,

    ID_G_FACE_DEC_MODE          =  0x30,
    ID_G_IC_VERSION,            // 0x31
    ID_G_PRESIZE_EN,            // 0x32
    ID_G_HOVER_MODE,            // 0x33
    ID_G_SCAN_STATUS            =  0x3e,

    ID_G_HIGH_SENSITIVITY_EN    =  0x40, // 高灵敏度模式
    ID_G_PEN_SUPPORT_EN         =  0x41, // 被动笔模式

    ID_G_SPEC_GESTURE_EN        =  0x50, // 特殊手势模式 1:开 0:关
    ID_G_SPEC_GESTURE_CH_CONFIG =  0x51,
    ID_G_SPEC_GESTURE_CH_EN     =  0x52,
    ID_G_SPEC_GESTURE_COOR      =  0x53,
    ID_G_SPEC_GESTURE_COOR1     =  0x54,
    ID_G_MAX                    =  0x5F
} ENUM_SysParamRegmap;

/*******************************************************************************
Name:                  E_PMode
DataType:              enum
Description:
1. 系统功耗模式
2. 功耗从高到低依次排列
*******************************************************************************/
typedef enum
{
    P_ACTIVE = 0,                                       //工作模式
    P_MONITOR,                                          //省电模式
    P_STANDBY,                                          //待机模式--实际不用
    P_HIBERNATE                                         //休眠模式
} E_PMode;

/* Normal system running parameters accessed by host via communication port */
typedef struct
{
    UINT8 McThGroup;              // 0x00,
    UINT8 McThPeak;               // 0x01
    UINT8 ScThGroup;              // 0x02
    UINT8 ScTxThPeak;             // 0x03
    UINT8 ScRxThPeak;             // 0x04
    UINT8 ucMoveThdDiff;          // 0x05
    ST_HOST_REG reg;
} ST_FlowReg;

typedef union
{
    ST_FlowReg Params;
    UINT8 Offset[sizeof(ST_FlowReg)];  // System Parameter Values
} UNION_SystemParameter;

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern UNION_SystemParameter XRAM g_stSysParam; 

#define g_State       g_stSysParam.Params.reg.ucState // 0xA7 System State
#define g_PMode       g_stSysParam.Params.reg.ucPMode // 0xA5 Power Mode

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
#endif //_APP_PARAMETER_H_ 

