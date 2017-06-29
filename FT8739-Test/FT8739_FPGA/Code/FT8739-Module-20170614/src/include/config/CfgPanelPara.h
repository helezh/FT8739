/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: CfgPanelPara.h
*
*    Author: linjianjun
*
*   Created: 2013-12-01
*
*  Abstract: Please describe the interface in detail for this module
*
*  ֻ��CfgAutoTune.c�����ܰ������ļ�
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
/* 1. ���ò��� */
/******************************************************************************/
#define CFG_PROJECT_CODE        "FT8835"  /* �ַ������Ȳ�����31���ֽ� "FTS8835P001"  */
#define CFG_CUSTOMER_CODE       "COB"     /* �ַ������Ȳ�����15���ֽ� "0123456789123" "001" */
#define RV_G_FIRMID             0x8a          /* ��ʽ����Ϊʮ������ (0x00)   ��ȡ�Ĵ��� 0xA6, �ͻ�Firmware�汾��Ϣ��ÿ����һ��Firmware�汾��+1 */

/* ��ʽ����Ϊʮ������ (0x01)   ��ȡ�Ĵ��� 0xAD, ��������Խ׶ε� Firmware�汾��Ϣ��ÿ����һ��Firmware�汾��+1 �������ڵ��Խ׶ν��а汾��¼*/
#define RV_G_FIRM_DEBUG_ID      0x01

#define RV_G_LIB_VERSION_H      0x00    /* App Lib version high */
#define RV_G_LIB_VERSION_L      0x01    /* App Lib version low ---ͬһ��Ŀ��ÿ���һ�μ�1 */

/******************************************************************************/
// 2. ͨ������
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
#else//ȫͨ������
#define CH_X_NUM_S0             8     // S0����������
#define CH_X_NUM_S1             8     // S1����������

#define CH_X_NUM_LOCAL          16    // (CH_X_NUM_S0 + CH_X_NUM_S1) Xͨ����������
#define CH_Y_NUM_LOCAL          28    // Yͨ��������
#define CH_X_NUM_VA             CH_X_NUM_LOCAL
#define CH_Y_NUM_VA             CH_Y_NUM_LOCAL

#define RV_CH_VALID_S0          224    // (CH_X_NUM_S0*CH_Y_NUM_LOCAL) S0 ��Чͨ����
#define RV_CH_VALID_S1          224    // (CH_X_NUM_S1*CH_Y_NUM_LOCAL) S1 ��Чͨ����

#define RV_CH_START_S0          3      // S0������Сͨ�����
#define RV_CH_NUM_S0            224    // (CH_X_NUM_S0*CH_Y_NUM_LOCAL) S0������ͨ���� 
#define RV_CH_START_S1          3     // S1������Сͨ�����
#define RV_CH_NUM_S1            224    // (CH_X_NUM_S1*CH_Y_NUM_LOCAL) S1������ͨ���� 

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
// 3. ϵͳ����
/******************************************************************************/
#define IO_LEVEL_SELECTION      0       /* 0:1.8V; 1:3.3V */
#define I2C_SLAVE_ADDR          0x70

#define SYS_MAX_POINT           5       /* ֧�ֵı������ */

#define SYS_PEAK_NOISE          140      /* Diff��Ҫ��ȥ������ */

/* ���Ź���λʱ��--��λms */
#define WDT_OVER_TIME_CLB       3500    //3500 ms
#define WDT_OVER_TIME_FLOW      200     //200 ms

/******************************************************************************/
// 4. ɨ��ģʽ����
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
/* FreeRunģʽ ���� */
#define MOD_FREE_SYNC_NUM       SNUM02           /* 0---15; ��ʾN+1��С������ */
#define MOD_FREE_SEG_CYCLE      5//15               /* 0:��ʾ1,ÿ�ε�ɨ����� */

//------------------------------------------------------------------------------
/* Monitor ���� */
#define MOD_M_SYNC_NUM          SNUM01           /* 0---15; ��ʾN+1��С������ */
#define MOD_M_SEG_CYCLE         6                /* 0:��ʾ1,ÿ�ε�ɨ����� */

//------------------------------------------------------------------------------
/* Active Normalģʽ ���� */
#if (SYS_PANEL_TYPE  == PANEL_TYPE_120HZ_NORMAL)
#define MOD_NORMAL_SYNC_NUM     SNUM03           /* 0---15; ��ʾN+1��С������ */
#define MOD_NORMAL_SEG_CYCLE    4                /* 0:��ʾ1,ÿ�ε�ɨ����� */
#elif (SYS_PANEL_TYPE  == PANEL_TYPE_120HZ_CBT)
#define MOD_NORMAL_SYNC_NUM     SNUM01           /* 0---15; ��ʾN+1��С������ */
#define MOD_NORMAL_SEG_CYCLE    7                /* 0:��ʾ1,ÿ�ε�ɨ����� */
#else
#define MOD_NORMAL_SYNC_NUM     SNUM01           /* 0---15; ��ʾN+1��С������ */
#define MOD_NORMAL_SEG_CYCLE    5               /* 0:��ʾ1,ÿ�ε�ɨ����� */
#endif

//------------------------------------------------------------------------------
/* Active Specialģʽ ���� */
#define MOD_SPEC_SYNC_NUM       SNUM09           /* 0---15; ��ʾN+1��С������ */
#define MOD_SPEC_SEG_CYCLE      0                /* 0:��ʾ1,ÿ�ε�ɨ����� */

/* 60Hz����У������, ����SC_60HZ_FAST_CLBʱ�ò�����Ч
   ������60Hzģʽ�£��ϵ�ʱ���л���120Hz���ģʽ����CBУ׼���Լӿ�CBУ׼�ٶ� */
#define MOD_60HZ_CLB_SYNC_NUM   SNUM01           /* 0---15; ��ʾN+1��С������ */
#define MOD_60HZ_CLB_SEG_CYCLE  0                /* 0:��ʾ1,ÿ�ε�ɨ����� */
/******************************************************************************/
// 5.��ֵ����
/******************************************************************************/
#define RV_G_VA_GROUP_THR       900//350//230//600//350//250                  /* VA����������������ֵ */
#define RV_G_VA_PEAK_THR        700//200//300//200//500//300//200             /* VA������������PEAK������ֵ */
#define RV_G_VA_PEAK_THR_NEG    700//300//200//500//300//200                  /* VA������������PEAK������ֵ */
#define RV_G_VK_TOUCH_THR       1500                 /* ��������������������ֵ */
#define RV_G_VK_PEAK_THR        1200                 /* ����������������PEAK������ֵ */
#define RV_G_VK_PEAK_THR_NEG    1200                 /* ����������������PEAK������ֵ */
#define RV_G_AREA_THR           600                  /* �����ͳ����PEAK������ֵ */
#define RV_G_AREA_THR_NEG       600                  /* �����ͳ�Ƹ�PEAK������ֵ */

/******************************************************************************/
// 6. ��Ƶ���
/******************************************************************************/
#define RV_FREQ_LIST            {K1_DELAY, 15, 20} /* ��ƵƵ�ʱ�,����ʱ�豣֤���Ƶ�������п��ܵ�ģʽ�²��ᷢ��scan drop */
#define RV_SW_NOISE_THR         (RV_G_VA_GROUP_THR*2)       /* ��������������ֵ */
#define RV_SW_DC_NOISE_THR      (RV_G_VA_GROUP_THR)         /* ��Ӳ����ж�ʱ�����������ֵ */
#define RV_SW_NOISE_HIGH_THR    (RV_G_VA_GROUP_THR*4)       /* ��������������ֵ */
#define RV_HW_NOISE_THR         80                          /* Ӳ�����������ֵ */
#define RV_POLLING_TIMES        4                           /* �������������� */

/******************************************************************************/
// 7.LCD mapping
/******************************************************************************/
#define X_CHANNEL               USE_TX_AS_X_CHANNEL     /*0 :X ������õ� TXӳ��, 1: X ������õ� RXӳ��*/

#define MAPPING_MAX_X            720  /* X����Mapping������ظ��� */
#define MAPPING_MAX_Y           1280  /* Y����Mapping������ظ��� */

#define VA_X_LEFT                448  /* X��������������ԭʼ����+1 */
#define VA_Y_UP                  576  /* Y�����ϰ��������ԭʼ����+1 */

#define LCD_X_L_MAPPING          339  /* X�����������������ظ��� */
#define LCD_Y_U_MAPPING          431  /* Y�����ϰ�����������ظ��� */

/* ����_Mapping���������������Ĳ���ֵ, ���ܸ���ʵ�������Ҫ΢�� */

#define LCD_X_L_EDGE              45//43  /* X�������ԵMapping���ظ��� */
#define LCD_X_R_EDGE              42  /* X�����ұ�ԵMapping���ظ��� */

#define LCD_Y_U_EDGE              41  /* Y�����ϱ�ԵMapping���ظ��� */
#define LCD_Y_D_EDGE              50  /* Y�����±�ԵMapping���ظ��� */

#define K_X_MID_LEFT             (195)//(193)  /* X�������������Mappingϵ�� */
#define K_X_MID_RIGHT            (192)  /* X���������Ұ���Mappingϵ�� */

#define K_Y_MID_UP               (192+1)  /* Y���������ϰ���Mappingϵ�� */
#define K_Y_MID_DOWN             (199+1)  /* Y���������°���Mappingϵ�� */

#define K_X_L_EDGE               (496-70)  /* X�������ԵMappingϵ�� */
#define K_X_R_EDGE               (515-60)  /* X�����ұ�ԵMappingϵ�� */

#define K_Y_U_EDGE               (440+0)  /* Y�����ϱ�ԵMappingϵ�� */
#define K_Y_D_EDGE               (440+0)  /* Y�����±�ԵMappingϵ�� */

/******************************************************************************/
// 8. ���ⰴ��
/******************************************************************************/
#define RV_KEY_EN_A0            (KS1_01|KS1_02|KS1_03)            /* 000 -- 111, ��AFE����ʹ��λ����3λ��Ч */
#define RV_KEY_EN_A1            (KS1_01|KS1_02|KS1_03)            /* 000 -- 111, ��AFE����ʹ��λ����3λ��Ч */

/* ���ⰴ���������--��HostԼ�� */
#define TOUCH_KEY_POS_X_OUT     {180,360,540}            /* ���ⰴ��X�������� */
#define TOUCH_KEY_POS_Y_OUT     1350                     /* ���ⰴ��Y�������� */

/******************************************************************************/
// 9.�Ĵ�������
/******************************************************************************/
/* ��һ�ΰ���ʱ�Ĵ�����ֵ����ֹ��������---һ�������ֵ */
#define RV_G_THG_TOUCHDOW       (RV_G_VA_GROUP_THR + (RV_G_VA_GROUP_THR>>2))

#define RV_G_MOVE_THDIFF        2560        /* ���ƶ��˲��� ����diffֵ */

#define RV_G_TIME_ENTER_MONITOR 2           /* ����Monitor״̬ʱ�� ��λs */
#define RV_G_FREE_ACTIVE_RPT    6           /* Free Run: Active period time 1:10Hz,2:20Hz,... */
#define RV_G_FREE_MONITOR_TIME  33          /* Free Run: Monitor period time  monitor 33Hz���� */

#define RV_G_LCD_VSYC_HZ        60          /* LCD��ʾ��֡�� */
#define RV_G_RTC_DEVI           20          /* RTC ��ʱ��ƫ��ϵ����24Ϊ��ƫ�С��24ΪRTC��ʱ��ʵ���жϼ������1ms������24ΪRTC��ʱ��ʵ���жϼ��С��1ms */

#define RV_G_PMODE              PM_ACTIVE   /* Default mode */
#define RV_G_INT_MODE           1           /* �жϷ�ʽ */
#define RV_G_STATE              SS_WORK     /* ����״̬ */

#define RV_G_IC_TYPE            0x01        /* IC���� */
#define RV_G_FIRMID_NEG         (~RV_G_FIRMID)
#define RV_G_VENDORID           0x86        /* ����ID�����ֿͻ��Ĳ�ͬ���� */
#define RV_G_VENDORID_NEG       (~RV_G_VENDORID)
#define RV_G_CHIPER_HIGH        0x86        /* Chip ID: FT8606��оƬID�����ڲ�ͬ�ͺ�оƬ�����֣�оƬID�벻Ҫ�޸� */
#define RV_G_CHIPER_LOW         0x06
#define RV_G_CUS_HW_ID          0x01        /* customer hw id */
#define RV_G_VENDORPANEL_ID     0x01        /* verdor panel hw id */
#define RV_G_LCDINITCODE_ID     0x01        /* lcd initcode id */

#define RV_G_RELEASE_ID_H       0x01        /* ��ʽ����Ϊʮ������ (0x00)  Firmware����汾ID_H����������Firmware����Ĳ�ͬ�汾 */
#define RV_G_RELEASE_ID_L       0x01        /* ��ʽ����Ϊʮ������ (0x00)  Firmware����汾ID_L����������Firmware����Ĳ�ͬ�汾 */

#define RV_G_UCTHPREFACTOR      4           /* for touch pressure, default value is 7, stand for 127 */
#define RV_G_USTHTOUCHSIZE      100

#define RV_G_IC_VERSION         0x01        /* IC version 0x01:A  0x02:B  0x03:C  and so forth */
#define RV_G_CHARGER_STATE      0           /* 1: Charger in   0: charger out, �����״̬ */

/******************************************************************************/
// 10. CFG Globalȫ�ֹ���ģ��ʹ������, ��CfgGlobal.h�е��������岻һ����
// ��CfgGlobal.h ����Ӧ��ģ��ʹ��֮����������ò������壬��������ý��ģ�����
// ֮���ò��õ����⣬��Ҫ���ڹ��߲���������
/******************************************************************************/
#define RV_G_LED_MODULE_EN              0   /* Led��ʹ�� */
#define RV_G_NOISE_COLLECT_EN           1   /* ��Ӳ�������ռ�ʹ��, ��Ƶ��ɨƵ����ʱ���뿪�� */
#define RV_G_PRESSURESIZE_VALID_EN      0   /* ����ѹ���������������ʹ�ܣ��Ĵ���ʹ�� */
#define RV_G_REPORT_EVEN_NUM_EN         0   /* ֻ���¼���ʹ�� */
#define RV_G_GESTURE_EN                 1   /* ��ͨ����ʹ��: �Ŵ���С, �������� */
#define RV_G_VIRTUAL_KEY_EN             1   /* ���ⰴ��ʹ�� */
#define RV_G_POS_MAPPING_EN             1   /* ����ӳ��ʹ�� */
#define RV_G_BASE_COMPENSATE_EN         1   /* Base���ٴ���ʹ�� */
#define RV_G_POINT_ID_PROC_EN           1   /* ID��ƥ��ʹ�� */

#define RV_G_PEAK_MERGE_PROCESS_EN      1   /* Peak�ϲ�ʹ�� */
#define RV_G_FLYING_LINE_PROC_EN        1   /* ��ָ�����û����ߴ���ʹ�� */
#define RV_G_POINT_TOUCH_FIILTER_EN     1   /* ����ƽ������ʹ�� */

#define RV_G_LINE_NOISE_FLT_EN          1   /* ����̧���˲�ʹ�� */
#define RV_G_COL_NOISE_FLT_EN           1   /* ����̧���˲����� */
#define RV_G_POINTS_STABLE_HANDLE_EN    1   /* ���ȶ�����ʹ�� */
#define RV_G_DEFER_FILTER_EN            1   /* �������ӳٱ���ʹ�� */
#define RV_G_LIFT_UP_FILTER_EN          1   /* ̧���ӳ�һ֡��̧���¼�ʹ�� */
#define RV_G_PWR_FILTER_EN              1   /* ��Դ�����˲�ʹ�� */
#define RB_G_FRAME_FILTER_EN            1   /* ֡�˲�ʹ�� */
#define RV_G_ESD_NOISE_HANDLE_EN        1   /* ESD����ʹ�� */
#define RV_G_HP_PROCESS_EN              1   /* ��ѹʹ�� */

#define RV_G_PWR_MANAGER_EN             1   /* ��Դ���Ĺ���ʹ�ܣ��Ĵ���ʹ�� */
#define RV_G_MONITOR_DET_EN             1   /* Ӳ���������ʹ��, ������, _PWR_MANAGER_EN����ʱ��Ч */
#define RV_G_PALM_REJECTION_EN          1   /* �����Ƽ��ʹ�� */
#define RV_G_SC_FREQ_HOPPING_EN         1   /* ��Ƶʹ�� */
#define RV_G_SPEC_GESTURE_EN            0   /* ��������ʹ��, �Ĵ���ʹ�� */
#define RV_G_LCD_PROCESS_EN             1   /* LCD������������diff�������˵��ٵ�ʹ�� */
#define RV_G_RF_PROC_EN                 1   /* ��RF���Ŵ����ܿ��� */

// TBD.
#define RV_G_FACE_DEC_MODE              0   /* �ӽ���Ӧ */
#define RV_G_HOVER_MODE                 0   /* Ƥ�� */
#define RV_G_GLOVE_MODE_EN              0   /* ����֧�� */
#define RV_G_PEN_MODE_EN                0   /* ������ */

#define RV_G_EDGE_FILETER_COOR_LEFT     2   /* ��Ե������ر����귶Χ */
#define RV_G_EDGE_FILETER_COOR_RIGHT    2   /* ��Ե�����ҽر����귶Χ */

/******************************************************************************/
// 11. base����
/******************************************************************************/
#define FRAME_STABLE_TH                 300 /* ����������������Χ */ /* ֡�ȶ�ֵ��������ֵ��һ�����ң�Ҫ���Ǽ������� */
#define BIG_AREA_SUM_TH                 ((CH_X_NUM_LOCAL * CH_Y_NUM_LOCAL) >> 3)
#define BASE_TRACE_STEP                 2   /* ÿ��BASE���ٲ��� */
#define BASE_TRACE_CNT                  1   /* ���ٴθ���һ��BASE */
#define BASE_REFRESH_CNT                5   /* ���ٴ�ˢ��һ��BASE */

/******************************************************************************/
// 12. ֡�˲�
/******************************************************************************/
#define FRAME_FILETR_MODE_EN            1   /* ģ��ʹ�� */
#define FRAME_FILTER_SUB_MAX_THR        2   /* �����������֡�� */
#define FRAME_FILTER_ADD_MAX_THR        2   /* �����������֡�� */
#define FRAME_FILTER_SUB_MAX_THR_NOISE  4
#define FRAME_FILTER_ADD_MAX_THR_NOISE  4
#define FRAME_FILTER_SKIP_START_FRAME   6   /* ����ͷN֡������֡���� */
#define FRAME_FILTER_BAND_WIDTH         128 /* ����֡����Ŀռ���� 2*PITCH */

/******************************************************************************/
// 13. ��ѹ
/******************************************************************************/
#define HP_RANGE_MIN                    200     /* ��ѹ�������diff��Χ--min */
#define HP_RANGE_MAX                    5000    /* ��ѹ�������diff��Χ--max */

/* ֵС��Խ�����ж�Ϊ��ѹ */
#define HP_NUM_PERPEAK                  8       /* ÿ��Peak��Χ�仯��������ѹ�����㷶Χ�ļ������ */
#define HP_MIN_PEAK_NUM                 5       /* ȫ��Peak����Ĭ��ֵ����Peak����С�ڸ���ֵʱ��������ֵ�� */

/* Peak 33����ĺ���Peak�ı�ֵ��������ֵʱ������Ϊ����ѹ�Ŀ�����Խ�󣬸�ֵԽС��Խ�����ж�Ϊ��ѹ */
#define HP_AROUND_RATIO                 6       /* Peak��Χ�ĺ�(����Peak����)��Peak����ı�ֵ��ֵ */
#define HP_LAST_TIME                    300     /* ��ѹ�α�ָ�ʱ�䣬��λms */

#define HP_SMALL_PEAK_THR               600//500     /* ��ѹ״̬�µ�ʶ��СPeak����ֵ */
#define HP_FIRST_ENTER_THR              800    /* �״ν�����ѹʱ���diff������ڸ�ֵ */
#define HP_OVERFLOW_THR                 8000    /* ȫ������仯���������仯��������ֵʱ��Ϊѹ�����أ������� */

/******************************************************************************/
// 14. ��������㴦��
/******************************************************************************/
#define BIGAREA_PEAK_CNT                45      /* peak ��Χ��diff����ָ����ֵ������������ֵ����Ϊ�Ǵ���� */
#define BIGAREA_PEAK_THR                500     /* �����Diff��ֵ,����ͳ��peak��Χ���ڴ���ֵ�Ľڵ��� */
#define BIGAREA_RECT_THR                700     /* ����������������ֵ, �ڴ������ڵ�peakҪ���㴦��*/
#define BIGAREA_RETAINING_TIMEOUT       20      /* ������˳�delay֡��*/

/******************************************************************************/
// 15. ���ƴ���
/******************************************************************************/
/*��Ӧ���Ƶ���Ч��Χ*/
#define SPEC_GESTURE_MARGIN_LEFT                   32//������д�Ľر߹��,����
#define SPEC_GESTURE_MARGIN_TOP                    0 //������д�Ľر߹��,����
#define SPEC_GESTURE_MARGIN_RIGHT               (MAPPING_MAX_X - SPEC_GESTURE_MARGIN_LEFT)
#define SPEC_GESTURE_MARGIN_BOTTOM              (MAPPING_MAX_Y- SPEC_GESTURE_MARGIN_TOP)

/*ʱ�����*/
/*1S=87 500MS=43 1500MS=130 2S=170*/
#define SPEC_GESTURE_TIMEOUT_1500MS                5000//1500 �Զ�������ʱ��ϳ�,Ĭ��Ϊ5s
#define SPEC_GESTURE_TIMEOUT_ONETIME               SPEC_GESTURE_TIMEOUT_1500MS//87//������д�����ʱ��

/*ֱ�����ƵĲ���*/
#define SPEC_GESTURE_LINE_DELTA                    (MAPPING_MAX_X/CH_X_NUM_LOCAL)   //ֱ�߶������Χ
#define SPEC_GESTURE_TRACE_CURVATURE               30//ֱ�����Ƶ�����
#define SPEC_GESTURE_TRACE_CURVATURE_STEP          128//ֱ�����Ƶ����ʼ��㲽��
#define SPEC_GESTURE_TRACE_DISTX_Y                 300//��˫�����Ƶ���д��С���꣬
#define SPEC_GESTURE_TRACE_MINCOUNT                10//��˫�����Ƶ���д��С������
#define SPEC_GESTURE_TRACE_X_WIDTH_MIN             160//��˫�����Ƶ���д������Сֵ��
#define SPEC_GESTURE_TRACE_Y_WIDTH_MIN          160
#define SPEC_GESTURE_DIST_START_TO_END_CLOSETO     100//��ʼ��ͽ�����ӽ����жϱ�׼
#define SPEC_GESTURE_VERT_LINE_Y_MIN               (MAPPING_MAX_Y>>2)//�������Ƶĳ��ȹ��
#define SPEC_GESTURE_VERT_LINE_X_MAX               (MAPPING_MAX_X>>3)//�������ƵĿ�ȹ��
#define SPEC_GESTURE_HORIZ_LINE_X_MIN              (MAPPING_MAX_X>>2)//�������ƵĹ��
#define SPEC_GESTURE_HORIZ_LINE_Y_MAX           (MAPPING_MAX_Y>>3)

#define SPEC_GESTURE_VERT_LINE_TIMEOUT_1000MS      1000 //�������Ƶ������дʱ��
#define SPEC_GESTURE_VERT_LINE_TIMEOUT_60MS        60//�������Ƶ���С��дʱ��
#define SPEC_GESTURE_HORIZ_LINE_TIMEOUT_1000MS  1000
#define SPEC_GESTURE_HORIZ_LINE_TIMEOUT_60MS    60

/*˫�����ƵĲ���*/

#define SPEC_GESTURE_DBLCLICK_DIST_10MM            10 //˫������ľ�����,�ڲ���x8
#define SPEC_GESTURE_DBLCLICK_STABLE_3MM           5 //˫��������ȶ�����ֹ�ϵ����,�ڲ���x8

#define SPEC_GESTURE_DBLCLICK_MARGIN_LEFT          80//˫���Ľر�Ҫ�� 720pixel=6.0cm
#define SPEC_GESTURE_DBLCLICK_MARGIN_TOP           80//1280pixel=10.5cm
#define SPEC_GESTURE_DBLCLICK_MARGIN_RIGHT         (MAPPING_MAX_X - SPEC_GESTURE_DBLCLICK_MARGIN_LEFT)//720pixel=6.0cm
#define SPEC_GESTURE_DBLCLICK_MARGIN_BOTTOM        (MAPPING_MAX_Y - SPEC_GESTURE_DBLCLICK_MARGIN_TOP)//1280pixel=10.5cm

#define CLICK_TIME_OUT_500MS                       500 //˫������ĵ��ʱ����
#define DBLCLICK_TIME_OUT_800MS                    800 //˫����ʱ����
#define DBLCLICK_TAIL_TIME_OUT_300MS               300 //˫����ʱ����
#define DOUBLE_CLICK_INTERVAL_50MS                 50  //˫�������ʱ�������
#define DOUBLE_CLICK_INTERVAL_500MS             CLICK_TIME_OUT_500MS
#define DOUBLE_CLICK_SECONDUP_300MS                300 //˫���ڶ���̧���ʱ����
#define DOUBLE_CLICK_NOPOINT_200MS                 200 //˫���ڶ���̧���û�е㴥����ʱ����

#else // __CFG_AUTO_TUNE_C__
#warning  "[warning]: CfgPanelPara.h should not be included except CfgAutoTune.c"
#endif // __CFG_AUTO_TUNE_C__

#endif // _CFG_PANEL_PARA_H_

