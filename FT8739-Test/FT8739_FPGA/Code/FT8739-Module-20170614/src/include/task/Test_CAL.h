/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Test_CAL.h
*
*    Author: xinkunpeng
*
*   Created: 2014-05-07
*
*  Abstract:
*
* Reference:
*
* Version:
* 0.1:
*
*******************************************************************************/
#ifndef _TEST_CAL_H_
#define _TEST_CAL_H_


/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

#if _TEST_CAL_EN
/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
/* ����һ�����ģ�� */
#if 0
#define  TEST_CAL_ADD_EN        0   // �ӷ�
#define  TEST_CAL_SUB_EN        0   // ����
#define  TEST_CAL_AMP_EN        0   // �˷�
#define  TEST_CAL_DIV_EN        0   // ����  
#define  TEST_CAL_MOV_EN        0   // ��ת�ð���
#define  TEST_CAL_MOV2_EN       0   // ת�ð���(����ת�ð���ʱ���TxNum,RxNum��TxLen,RxLen���)  
#define  TEST_CAL_MUL2_1_EN     0   // һά����˷�      (Tx,Rx������<=18)       
#define  TEST_CAL_MUL2_2_EN     0   // ��ά����˷�
#define  TEST_CAL_COM_1_EN      0   // �ɵĲ�������  
#define  TEST_CAL_COM_2_EN      0   // �µĲ������� 
#define  TEST_CAL_LDS_EN        0   // ������Ӧ��������
#define  TEST_CAL_MDS_EN        0   // ���е�ľ�������  (Tx,Rx������<=11)
#define  TEST_CAL_CHK_EN        0   // ���ȶȼ��
#define  TEST_CAL_CRC_EN        1   // CRCУ��
#define  TEST_CAL_XORSUM_EN     0   // xor���У��
#define  TEST_CAL_AMOV_EN       0   // AMOV    (����Ϊ��չ�㷨)
#define  TEST_CAL_AVG_TX_EN     0   // �о�ֵ�㷨 
#define  TEST_CAL_AVG_RX_EN     0   // �о�ֵ�㷨
#define  TEST_CAL_AVG2_TX_EN    0   // ȥ����Χ���ֵ���о�ֵ�㷨
#define  TEST_CAL_AVG2_RX_EN    0   // ȥ����Χ���ֵ���о�ֵ�㷨
#define  TEST_CAL_AVG_ARAM_EN   0
#define  TEST_CAL_MIN_TX_EN     0   // ����Сֵ�㷨
#define  TEST_CAL_MIN_RX_EN     0   // ����Сֵ�㷨
#define  TEST_CAL_MAX_TX_EN     0   // �����ֵ�㷨
#define  TEST_CAL_MAX_RX_EN     0   // �����ֵ�㷨
#define  TEST_CAL_COUNT_EN      0   // ������ĳ������ĸ���[max,min]
#define  TEST_CAL_SUBCONST_EN   0   // ����ÿ��(Tx)����ÿ��(Rx)�ļ�ȥһ������
#define  TEST_CAL_MAC_1_EN      0   // ������ģʽMAC
#define  TEST_CAL_MAC_2_EN      0   // �ع�ģʽMAC
#define  TEST_CAL_ID_EN         0   // IDƥ��
#define  TEST_CAL_PKS_EN        0   // Peak Search


#else//Auto
#define  TEST_CAL_ADD_EN        1   // �ӷ�
#define  TEST_CAL_SUB_EN        1   // ����
#define  TEST_CAL_AMP_EN        1   // �˷�
#define  TEST_CAL_DIV_EN        1   // ����
#define  TEST_CAL_MOV_EN        1   // ��ת�ð���
#define  TEST_CAL_MOV2_EN       1   // ת�ð���(����ת�ð���ʱ���TxNum,RxNum��TxLen,RxLen���)
#define  TEST_CAL_MUL2_1_EN     1   // һά����˷�      
#define  TEST_CAL_MUL2_2_EN     1   // ��ά����˷�
#define  TEST_CAL_COM_1_EN      1   // �ɵĲ�������
#define  TEST_CAL_COM_2_EN      1   // �µĲ������� 
#define  TEST_CAL_LDS_EN        1   // ������Ӧ��������
#define  TEST_CAL_MDS_EN        1   // ���е�ľ������� 
#define  TEST_CAL_CHK_EN        1   // ���ȶȼ��
#define  TEST_CAL_CRC_EN        1   // CRCУ��
#define  TEST_CAL_XORSUM_EN     1   // xor���У��

#define  TEST_CAL_AMOV_EN       1   // AMOV    (����Ϊ��չ�㷨)
#define  TEST_CAL_AVG_TX_EN     1   // �о�ֵ�㷨 
#define  TEST_CAL_AVG_RX_EN     1   // �о�ֵ�㷨
#define  TEST_CAL_AVG2_TX_EN    1   // ȥ����Χ���ֵ���о�ֵ�㷨
#define  TEST_CAL_AVG2_RX_EN    1   // ȥ����Χ���ֵ���о�ֵ�㷨
#define  TEST_CAL_AVG_ARAM_EN   1
#define  TEST_CAL_MIN_TX_EN     1   // ����Сֵ�㷨
#define  TEST_CAL_MIN_RX_EN     1   // ����Сֵ�㷨
#define  TEST_CAL_MAX_TX_EN     1   // �����ֵ�㷨
#define  TEST_CAL_MAX_RX_EN     1   // �����ֵ�㷨
#define  TEST_CAL_COUNT_EN      1   // ������ĳ������ĸ���[max,min]
#define  TEST_CAL_SUBCONST_EN   1   // ����ÿ��(Tx)����ÿ��(Rx)�ļ�ȥһ������ 
#define  TEST_CAL_MAC_1_EN      1  // ������ģʽMAC
#define  TEST_CAL_MAC_2_EN      1  // �ع�ģʽMAC
#define  TEST_CAL_ID_EN         1  // IDƥ��
#define  TEST_CAL_PKS_EN        1  // Peak Search
#endif

#if 1//8836����ģ��
/* ��������ģ�� */

#define TEST_CAL_CMP_EN         1  //����Ƚ��㷨
#define TEST_CAL_MUL3_EN        1  //������������㷨
#else
/* ��������ģ�� */
#define TEST_CAL_CMP_EN         0   //����Ƚ��㷨
#define TEST_CAL_MUL3_EN        0   //������������㷨

#endif

#define  TEST_AMOVE_RTC_INT_EN  1   /* Calģ���жϴ�ϲ���,RTC���,��rtc�ж��е���amove */
#define  TEST_SPI0_CAL_INT_EN   0   /* Calģ���жϴ�ϲ���,SPI0��� */
#define  TEST_SPI0_DMA_INT_EN   0   /* Calģ���жϴ�ϲ���,����SPI0 DMA,�����TEST_SPI0_CAL_INT_EN */
#define  TEST_IIC_CAL_INT       1   /* Calģ���жϴ�ϲ���,iic��� */



/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
//extern ST_FrameData  *g_stFrmData; // Frame Data

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void Test_CAL(void);
#else
#define Test_CAL /##/
#endif

#endif // _DRV_MC_DATA_COLLECT_H_

