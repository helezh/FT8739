/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: DrvAfe.h
*
*    Author: lisen
*
*   Created: 2017-04-10
*
*  Abstract:
*
* Reference:
*
* Version:
* 0.1:
*
*******************************************************************************/
#ifndef __DRV_AFE_H_
#define __DRV_AFE_H_

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef struct
{
    UINT8  usErrFlg;              //ͨ��ɨ���Ƿ�����������־
    UINT8  usErrSta;              //���ĸ�ͨ������
    UINT8  usDoneFlg;             //mcapɨ���Ƿ����
    UINT8  usOvfEn;               //ADC���ͼ������
    UINT8  usOvfFlg;              //ADC�����־
    UINT8  usOvfClrEn;            //ʹ����������������
    UINT8  usOvfClrFlg;           //ADC�����־�����־
    UINT8  usGainEn ;             //��RAWDATA�������洦��
    UINT8  usGainCof;             //����ϵ��
    UINT8  usRawShiftCof;         //
    UINT8  usDiffSet;             // 2b'0x:������diff_max;2b'10:��ADC���ݽ���diff_max����;2b'11:��mixer���ݽ���diff_max����
    UINT8  usHbFirEn;             //����˲�����
    UINT8  usLpFirEn;             //��ͨ�˲�����
    UINT8  usLpFirTap;            //��ͨ�˲�������Ĭ��14
    UINT8  usLpFirStart;          //��ͨ�˲��ۻ���ʼ��,��С��usLpFirStart
    UINT8  usSampl_6;             //��������         
    UINT8  usScanNum;             //ɨ�����
    UINT8  usScanMode;            //afeɨ�跽ʽ
    UINT8  usSxMode;              //sxɨ�跽ʽ
    UINT8  usFrmDummy;            //TP֡ǰɨ��dummy����
    UINT8  usSecDummy;            //��ǰɨ��dummy���� 
    UINT8  usMuxDummy;            //muxǰɨ��dummy����
    UINT16 usSampl_Init;          //ɨ����ʼ��
    UINT16 usK1;                  //K1
    UINT16 usK2;                  //K2
    UINT16 usLpFirSumNum;         //�ۻ�����
    UINT16 usLpFirCof0;           //LpFirϵ��0
    UINT16 usLpFirCof1;           //LpFirϵ��1
    UINT16 usLpFirCof2;           //LpFirϵ��2
    UINT16 usLpFirCof3;           //LpFirϵ��3
    UINT16 usLpFirCof4;           //LpFirϵ��4
    UINT16 usLpFirCof5;           //LpFirϵ��5
    UINT16 usLpFirCof6;           //LpFirϵ��6
    UINT16 usLpFirCof7;           //LpFirϵ��7    
    UINT16 usOvfTh;               //adc�������������ֵ
    UINT16 usUdwTh;               //adc�������������ֵ
    UINT16 usOvfUpBound;          //�������������Χ�ж��ٸ����Ϊһ�������
    UINT16 usOvfPointFrm;         //������㳬����ֵ�Ժ󣬲��������־
    UINT16 usNormalUpTh;          //�����������������ֵ
    UINT16 usNormalDwTh;          //�����������������ֵ
    UINT16 usOvfClrFrmNum;        //������������ֵ��������������Χ,������������־
    UINT32 usRawdataOffset;       //ADC���洦��rawdataͳһ��ȥ��ֵ
} ST_McapParameter;


/*******************************************************************************
* 3.Global variable or extern global variabls/functions
*******************************************************************************/
extern ST_McapParameter XRAM g_pMcapData;
extern ST_McapParameter XRAM *g_pMcapPara;


/*******************************************************************************
* 4.Global function prototypes
*******************************************************************************/
void DrvAfeSelACCRam(UINT8 ucbit);
void DebugReadAFEReg(void);
UINT16 DebugReadAFEOneReg(UINT16 ucAddr);
void DrvAfeSelTaborRepRam(UINT8 RamSelect);
void DrvAFEGroupSelReg1(UINT8 ucMux1_GA,UINT8 ucMux1_GB,UINT8 ucMux2_GA,UINT8 ucMux2_GB,UINT8 ucMux3_GA,UINT8 ucMux3_GB);
void DrvAFEGroupSelReg2(UINT8 ucMux4_GA,UINT8 ucMux4_GB,UINT8 ucMux5_GA,UINT8 ucMux5_GB);
void DrvGetRptRamOrder(void);
void DrvInitRptRam(void);
void DrvAfeScanMode(UINT8 ucMode,UINT16 usScantimes);
void DrvAfeSofeReset(void);
void DrvAfeEnCOF(void);
void DrvAfeEnRawdataNum(UINT16 ucRptRawdataNum);
void DrvAfeEn4mux(void);
void DrvGetTabRam(void);

void DrvAfeSetOneChannelTestMode(UINT8 ucKeyNum,UINT16 usTpNum,UINT8 ucTp_Key_Sel);
void DrvAfeSetBaseTrack(UINT8 ucBaseMode,UINT8 ucStep);
void DrvAfeSetHCBThld(UINT16 usTpThld,UINT16 usKeyThld);
void DrvAfeInitBase(void);
void Afe_SetTabCBChEN(UINT8 ucTabID);
void Afe_Config_Tab0(void);
void Afe_Config_Tab1(void);
void Afe_Config_Tab2(void);
void Afe_Config_Tab3(void);
//void DrvGetRptRamRawBase(void);
void DrvSetCbDir(UINT8 ucTpDir,UINT8 ucKeyDir);
void DrvSetTabMonThr(UINT16 usTpMonThr,UINT16 usKeyMonThr,UINT8 usTabId);
void DrvGetTabRamCb(void);
void Afe_Change_Tab3(UINT8 ucTestMode,UINT8 ucScanMode,UINT8 ucScanNum);
void DrvMcapModeInit(UINT8 ucModeEn,UINT8 ucTabId);
void DrvMcapReadSta(ST_McapParameter * pMcapPara);
void DrvMcapSetTestMode(UINT8 ucMode,UINT8 ucKeyNum);
void Test_DebugOut(void);
void DrvAfeSetTabBaseTrack(UINT8 ucBaseMode,UINT8 ucStep,UINT8 ucId);

#endif
