/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: CfgAutoTune.h
*
*    Author: linjianjun
*
*   Created: 2013-02-01
*
*  Abstract: 
*            ���ļ������Զ�������ģ��ṹ��
*   ע�⣬�ṹ����Ϊ������ĳ�Ա�����������鿪ͷ����Ȼ��ʼ�������ȴ���offset��Ա
*   ���¹����ʼ������
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


// 4. ϵͳ����
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
/* ��hostͨ�żĴ��� */
typedef struct
{
    /* ���²�����parameter�ļĴ����ṹ��һ�£�����ͳһ���� */
    UINT8 ucPwrCtrl;                   /* 0x86 ��Դ������ */
    UINT8 ucTimeEnterMonitor;          /* 0x87 �޴���ʱ����monitor��ʱ�� ��λs */
    UINT8 ucPeriodActive;              /* 0x88 Activeģʽһ֡������ʱ��--index */
    UINT8 ucPeriodMonitor;             /* 0x89 Monitorģʽһ֡������ʱ�� ��λms */
    UINT8 UNUSED_BYTE0;                /* 0x8A */
    UINT8 ucChargerState;              /* 0x8B ���������ָʾ��־��1 - ����0 - �أ�*/
    UINT8 UNUSED_BYTES_0[0x21-0x0C];   /* 0x8C--0xA0 */
    UINT8 ucLibVersionHigh;            /* 0xA1 App���ļ��汾�Ÿ��ֽ� */
    UINT8 ucLibVersionLow;             /* 0xA2 App���ļ��汾�ŵ��ֽ� */
    UINT8 ucChiper;                    /* 0xA3 Chip type */
    UINT8 ucIntMode;                   /* 0xA4 1:INT triggerģʽ��0:INT pollingģʽ */
    UINT8 ucPMode;                     /* 0xA5 Power Mode��0:Active��1:Monitor��2:Sleep */
    UINT8 ucFirmId;                    /* 0xA6 Firmware version number */
    UINT8 ucState;                     /* 0xA7 ����״̬������ģʽ�͹���ģʽ�л���*/
    UINT8 ucVendorId;                  /* 0xA8 Vendor ID��������*/
    UINT8 ucDriverVerH;                /* 0xA9 �������ļ��汾�Ÿ��ֽ� */
    UINT8 ucDriverVerL;                /* 0xAA �������ļ��汾�ŵ��ֽ� */
    UINT8 UNUSED_BYTES_1[0x2f-0x2B];   /* 0xAB--AE */
    UINT8 ucReleaseCodeId;             /* 0xAF ����release code ID */
    UINT8 ucFaceDecMode;               /* 0xB0 �������Ӧʹ�� (1:enable��0:disable)*/
    UINT8 ucIcVersion;                 /* 0xB1 IC version number: 0x01:A, 0x02:B, 0x03:C*/
    UINT8 ucPresizeEn;                 /* 0xB2 */
    UINT8 ucHoverMode;                 /* 0xB3 ����ģʽ (1:enable��0:disable)*/
    UINT8 UNUSED_BYTES_2[0x3e-0x34];   /* 0xB4--BD */
    UINT8 ucScanStatus;                /* 0xBE Scanɨ��״̬ */
    UINT8 UNUSED_BYTES_4;              /* 0xBF */

    UINT8 ucHighSensity;               /* 0xC0--��������ģʽ */
    UINT8 ucPenMode;                   /* 0xC1--��ģʽ */
    UINT8 UNUSED_BYTES_5[0x50-0x42];   /* 0xC2--CF */

    UINT8 ucSpecGestureEn;             /* 0xD0 */   // Spec Gesture Mode Enable
    UINT8 ucSpecGestureConfig;         /* 0xD1 */   // Bit0 ��,Bit1 �һ�,Bit2 �ϻ�,Bit3 �»�,Bit4 ˫��,Bit5 �ַ�;
    UINT8 ucSpecGestureCHEn;           /* 0xD2 */   // Spec Gesture Character Enable,
    UINT8 ucSpecGestureCoor;           /* 0xD3 �������buf0 */
    UINT8 ucSpecGestureCoor1;          /* 0xD4 �������buf1 */
    UINT8 ucSpecGestureConfig1;        /* 0xD5 �ַ�ʹ��1 */
    UINT8 ucSpecGestureConfig2;        /* 0xD6 �ַ�ʹ��2 */
    UINT8 ucSpecGestureConfig3;        /* 0xD7 �ַ�ʹ��3 */
    UINT8 ucSpecGestureConfig4;        /* 0xD8 �ַ�ʹ��4 */
    UINT8 ucSpecGestureConfig5;        /* 0xD9 �ַ�ʹ��5 */
} ST_HOST_REG;

#endif

