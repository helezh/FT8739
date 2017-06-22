/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: AppHostComm.h
*
*    Author:
*
*   Created: 2013-12-31
*
*  Abstract: Please describe the interface in detail for this module
*
* Reference:
*
*******************************************************************************/

#ifndef _APP_HOST_COMM_H_
#define _APP_HOST_COMM_H_

/* Conditional Compiler Options */

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include <string.h>
#include "CfgSystem.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define g_RegHead               g_unPanelParam.reg.RegHead
#define g_DeviceMode            g_RegHead.bits.ucDeviceMode

/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/
typedef union
{
    UINT8 ucData;
    struct
    {
        UINT8 ucSoftReset     : 1;  // 1 = software reset
        UINT8 ucDeepSleep     : 1;  // 1 = enter deep sleep state, 0 = quit sleep
        UINT8 ucLowPower      : 1;  // 1 = enable low power, 0 = disable
        UINT8 ucReserved1     : 1;
        UINT8 ucDeviceMode    : 3;  // device mode
        UINT8 ucDataReadToggle: 1;  //
    } bits;
} UNION_RegisterHeader;

typedef enum
{
    DEVICE_MODE_NORMAL = 0,     // Normal operating mode
    DEVICE_MODE_INFO   = 1,     // system information mode
    DEVICE_MODE_TEST   = 4,     // test mode - filtered raw counts
    DEVICE_MODE_MAX             // other value - reserved
} ENUM_DeviceMode;

/* Factory Test Register Map */
typedef enum
{
    /* system register */
    ID_G_DEVICE_MODE            =  0x00, // RW
    ID_G_RAWDATA_SETCT,         // RW 0x01 The mode of rawdata to be setect
    ID_G_TX_NUM,                // RO 0x02 Actually used TX channel number
    ID_G_RX_NUM,                // RO 0x03 Actually used RX channel number
    ID_G_CLB,                   // RW 0x04 Calibration command & status
    ID_G_MAX_POINT_NUM,         // RW 0x05 The maximum point number supported
    ID_G_DATA_MODE,             // RW 0x06:diff; 0x00:rawdata
    ID_G_LCD_BUSY_NUM,          // RO 0x07 一帧中一帧lcu busy 中断的数量

    ID_G_INT_TEST_EN            = 0x08, // RW 0x08 INT脚测试
    ID_G_RAW_BUF_SEL,           // RW 0x09 工厂模式rawdata buf选择
    ID_G_FREQ_IDX,              // RW 0x0A 工厂模式频率选择

    ID_G_RUN_MODE               = 0x0C, // RO 0x0C 当前扫描模式
    ID_G_P1P2_DELAY,            // RO 0x0D 充放电时间延迟
    ID_G_PARAUP_STATE,          // RO 0x0E 工厂模式下寄存器参数更新状态，0-参数更新完成即空闲， 非零 - 参数更新过程中即忙

    ID_G_NOISE_TEST             = 0x11, //RW 0x11 Noise Test
    ID_G_NOISE_TEST_NUM,        //  RO 0x12 Noise Test 帧数
    ID_G_NOISE_TEST_N,          //  RO 0x13 反馈除数N

    ID_G_FW_BUG_CNT             = 0x17, // RW FW信息buf的偏移量

    /* AFE register */
    ID_G_CB_ADDR_H              = 0x18,
    ID_G_CB_ADDR_L,             // RW 0x19
    ID_G_ORDER_ADDR_H,          // RW 0x1A
    ID_G_ORDER_ADDR_L,          // RW 0x1B
    ID_G_RAW_ADDR_H,            // RW 0x1C
    ID_G_RAW_ADDR_L,            // RW 0x1D
    ID_G_KEY_EN_LEFT,           // RW 0x1E
    ID_G_KEY_EN_RIGHT,          // RW 0x1F

    ID_G_DUMMY_STB              = 0x28,
    ID_G_DUMMY_FRM,             // RW 0x29
    ID_G_DUMMY_SEG,             // RW 0x2A
    ID_G_DROP_FLAG,             // RO 0x2B
    ID_G_RAW_BUF_STA,           // RO 0x2C AB帧标志

    ID_G_SCAN_MODE              = 0x30,
    ID_G_K1_DELAY,              // RW 0x31
    ID_G_K2_DELAY,              // RW 0x32
    ID_G_SYNC_NUM,              // RW 0x33
    ID_G_CF,                    // RW 0x34
    ID_G_TBL,                   // RW 0x35
    ID_G_SUB_BASE1,             // RW 0x36
    ID_G_SUB_BASE0,             // RW 0x37
    ID_G_NUMLIST0               = 0x38, // RW 0x38
    ID_G_NUMLIST1               = 0x3A, // RW 0x3A
    ID_G_NUMLIST2               = 0x3C, // RW 0x3C
    ID_G_NUMLIST3               = 0x3E, // RW 0x3E
    ID_G_NUMLIST4               = 0x40, // RW 0x40
    ID_G_NUMLIST5               = 0x42, // RW 0x42
    ID_G_NUMLIST6               = 0x44, // RW 0x44
    ID_G_NUMLIST7               = 0x46, // RW 0x46
    ID_G_NUMLIST8               = 0x48, // RW 0x48
    ID_G_NUMLIST9               = 0x4A, // RW 0x4A
    ID_G_NUMLIST10              = 0x4C, // RW 0x4C
    ID_G_NUMLIST11              = 0x4E, // RW 0x4E
    ID_G_NUMLIST12              = 0x50, // RW 0x50
    ID_G_NUMLIST13              = 0x52, // RW 0x52
    ID_G_NUMLIST14              = 0x54, // RW 0x54
    ID_G_NUMLIST15              = 0x56, // RW 0x56
    ID_G_RF_NOISE1              = 0x58, // RW 0x58,  /* RF噪声阈值高8位 */
    ID_G_RF_NOISE0,             // RW 0x59,  /* RF噪声阈值低8位 */
    ID_G_DIFF_NOISE1,           // RW 0x5A,  /* 差值噪声阈值高8位 */
    ID_G_DIFF_NOISE0,           // RW 0x5B,  /* 差值噪声阈值低8位 */

    ID_G_RAW_BUF0               = 0x6A,
    ID_G_RAW_BUF1,              // RW 0x6B
    ID_G_ORDER_BUF0,            // RW 0x6C
    ID_G_ORDER_BUF1,            //
    ID_G_CB_BUF0,               // RW 0x6E
    ID_G_CB_BUF1,               //

    ID_FREE_RUN                 = 0x70,  /* RW LCD info内容区开始 */
    ID_PWR_REQ,                 // RW 0x71  //8626del
    ID_120Hz_REQ,               // RW 0x72
    ID_120Hz_STA,               // RO 0x73
    ID_LCD_RUN_STA,             // RO 0x74
    ID_PWR_STA,                 // RO 0x75 TP上电状态 //8626del
    ID_G_LCD_INFO_END           = 0x7F,  /* LCD info内容区结束 */

    ID_G_FW_BUG0                = 0x81, // RW FW信息buf0
    ID_G_FW_BUG1                = 0x82, // RW FW信息buf1--FW地址自锁用
    ID_G_CHANNEL_TEST           = 0x83, // RW 通道检测
    ID_G_CB_INFO                = 0x84, // RW CH检测通道信息
    ID_G_CB_RES                 = 0x85, // RO CH检测状态
    ID_G_VREF                   = 0x86, // RW VREF设置 0:1.3; 1:1.4; 2:VDDA/2; 3:1.6; 4:1.8; 5:2.0; 6:2.2; 7:2.4
    ID_G_VDD5                   = 0x87, // RW VDD5设置 0--15 5v--6.5v stpe:0.1v

    ID_G_WATER_LOT_NUM          = 0x90,

    ID_G_NOISE_TYPE             = 0xE0, // RW 0xE0 扫频噪声类型，RF or Diff
    ID_G_POLL_MODE,             // RW 0xE1 扫频模式，K1 or K2
    ID_G_POLL_STEP,             // RW 0xE2 K1或K2的步长
    ID_G_POLL_NUM,              // RW 0xE3 扫频频点数量
    ID_G_START_K1DELAY,         // RW 0xE4 起始K1
    ID_G_START_K2DELAY,         // RW 0xE5 起始K2
    ID_G_NOISE_THR1,            // RW 0xE6 扫频噪声阈值高8位
    ID_G_NOISE_THR0,            // RW 0xE7 扫频噪声阈值低8位
    ID_G_POLL_STATE,            // RW 0xE8 扫频状态 00:Idl  01:start  02: busy  03: ok 04: fail
    ID_G_CUR_POLL_FREQ,         // RO 0xE9 当前扫频频点
    ID_G_NOISE_FLAG1,           // RO 0xEA 噪声数据buf
    ID_G_NOISE_FLAG0,           // RO 0xEB 噪声数据buf
    ID_G_DATA_POINTER,          // RW 0xEC 噪声数据buf指针

    ID_G_MC_FIR                 = 0xFB,// RW 0xFC 工厂模式开关Fir
    /* I2C Debug */
    ID_G_I2C_DEBUG_LEN          = 0xFD, // RW I2C debug window data len
    ID_G_I2C_DEBUG_DATA         = 0xFF  // RW I2C debug window data value

} ENUM_PanelParamRegMap;


/* Factory test parameters accessed by host via communication port */
typedef struct
{
    /* System Register */
    UNION_RegisterHeader RegHead;  //0x00 RW
    UINT8 ucRawSel;        // RW 0x01 Rawdata mode setect: Mc/ScNomal/ScWater
    UINT8 ucTxNum;         // RO 0x02 Actually used TX channel number
    UINT8 ucRxNum;         // RO 0x03 Actually used RX channel number
    UINT8 ucClbCmd;        // RW 0x04 Calibration status, W Calibration command
    UINT8 ucPointNumMax;   // RW 0x05 The maximum point number supported
    UINT8 ucDataMode;      // RW 0x06 数据格式
    UINT8 ucLcdBusyNum;    // RW 0x07 一帧lcu busy 中断的数量
    UINT8 ucTestIntPin;    // RW 0x08 INT pin Test

    UINT8 ucRawBufSel;     // RW 0x09 0:A帧，1:B帧，2:交替
    UINT8 ucFreIdx;        // RW 0x0A
    UINT8 Reserved_0B;     // RW 0x0B

    UINT8 ucRunMode;       // RO 0x0C 当前扫描模式
    UINT8 ucD12Delay;      // RO 0x0D 充放电时间延迟
    UINT8 ucParaUpState;   // RO 0x0E 工厂模式下寄存器参数更新状态，0-参数更新完成即空闲， 非零 - 参数更新过程中即忙

    UINT8 Reserved_0F;
    UINT8 Reserved_10;
    UINT8 ucNoiseTest;      //  RW 0x11 Noise Test
    UINT8 ucNoiseTestNum;   //  RW 0x12 Noise Test测试帧数
    UINT8 ucNoiseTestN;     //  RO 0x13 反馈除数N,  ucNoiseTestN <= ucNoiseTestNum
    UINT8 Reserved_14;
    UINT8 Reserved_15;
    UINT8 Reserved_16;
    UINT8 FwInfoCnt;       // RW 0x17 FW info指针位置

    /* Mc Register */
    UINT8 ucCbAddrH;       // RW 0x18
    UINT8 ucCbAddrL;       // RW 0x19
    UINT8 ucOrderAddrH;    // RW 0x1A
    UINT8 ucOrderAddrL;    // RW 0x1B
    UINT8 ucRawAddrH;      // RW 0x1C
    UINT8 ucRawAddrL;      // RW 0x1D
    UINT8 ucKeyEnLeft;     // RW 0x1E
    UINT8 ucKeyEnRight;    // RW 0x1F

    UINT8 Reserved_20;
    UINT8 Reserved_21;
    UINT8 Reserved_22;
    UINT8 Reserved_23;
    UINT8 Reserved_24;
    UINT8 Reserved_25;
    UINT8 Reserved_26;
    UINT8 Reserved_27;

    UINT8 ucDummyStb;      // RW 0x28
    UINT8 ucDummyFrm;      // RW 0x29
    UINT8 ucDummySeg;      // RW 0x2A
    UINT8 ucDropFlag;      // RW 0x2B
    UINT8 ucRawBufSta;     // RO 0x2C AB帧标志

    UINT8 Reserved_2D;
    UINT8 Reserved_2E;
    UINT8 Reserved_2F;

    UINT8 ucScanMode;      // RW 0x30
    UINT8 ucK1Delay;       // RW 0x31
    UINT8 ucK2Delay;       // RW 0x32
    UINT8 ucSyncNum;       // RW 0x33
    UINT8 ucCf;            // RW 0x34
    UINT8 ucTbl;           // RW 0x35
    UINT16 usSubBase;      // RW 0x36--0x37
    UINT16 usNumList[16];   // RW 0x38--0x57
    UINT16 usRfNoiseThr;    // RW 0x58--0x59         /* RF噪声检测阈值，低10位有效，即一个段内受到干扰的扫描次数 */
    UINT16 usDiffNoiseThr;  // RW 0x5a--0x5b         /* 差值噪声检测阈值 */
} ST_FactoryReg;

typedef union
{
    ST_FactoryReg reg;
    UINT8 Offset[sizeof(ST_FactoryReg)];
} UNION_PanelParameter;


/*******************************************************************************
* 3.Global variable extern declarations
*******************************************************************************/
/* Touch Panel Parameters */
extern UNION_PanelParameter XRAM g_unPanelParam;
extern UINT8 XRAM g_ucLastState;   /* 升级及复位命令状态标志 */
extern UINT8 DRAM g_ucI2cDataAddr;

/*******************************************************************************
* 4.Global function prototypes
*******************************************************************************/
void AppHostCommInit(void);
void AppHostUpdateHeadState(UINT8 NewRegHeader);
void AppParamUpdatePost(void);

UINT8 AppHostRegRead(UINT8 addr);
void AppHostRegWrite(UINT8 addr,UINT8 ch);
#endif // _APP_HOST_COMM_H_

