/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
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
    UINT8  usErrFlg;              //通道扫描是否正常结束标志
    UINT8  usErrSta;              //看哪个通道错了
    UINT8  usDoneFlg;             //mcap扫描是否结束
    UINT8  usOvfEn;               //ADC饱和检测设置
    UINT8  usOvfFlg;              //ADC溢出标志
    UINT8  usOvfClrEn;            //使能溢出消除检测设置
    UINT8  usOvfClrFlg;           //ADC溢出标志清除标志
    UINT8  usGainEn ;             //对RAWDATA进行增益处理
    UINT8  usGainCof;             //增益系数
    UINT8  usRawShiftCof;         //
    UINT8  usDiffSet;             // 2b'0x:不计算diff_max;2b'10:对ADC数据进行diff_max运算;2b'11:对mixer数据进行diff_max运算
    UINT8  usHbFirEn;             //半带滤波开启
    UINT8  usLpFirEn;             //低通滤波开启
    UINT8  usLpFirTap;            //低通滤波阶数，默认14
    UINT8  usLpFirStart;          //低通滤波累积起始点,不小于usLpFirStart
    UINT8  usSampl_6;             //采样倍数         
    UINT8  usScanNum;             //扫描次数
    UINT8  usScanMode;            //afe扫描方式
    UINT8  usSxMode;              //sx扫描方式
    UINT8  usFrmDummy;            //TP帧前扫描dummy次数
    UINT8  usSecDummy;            //坑前扫描dummy次数 
    UINT8  usMuxDummy;            //mux前扫描dummy次数
    UINT16 usSampl_Init;          //扫描起始点
    UINT16 usK1;                  //K1
    UINT16 usK2;                  //K2
    UINT16 usLpFirSumNum;         //累积次数
    UINT16 usLpFirCof0;           //LpFir系数0
    UINT16 usLpFirCof1;           //LpFir系数1
    UINT16 usLpFirCof2;           //LpFir系数2
    UINT16 usLpFirCof3;           //LpFir系数3
    UINT16 usLpFirCof4;           //LpFir系数4
    UINT16 usLpFirCof5;           //LpFir系数5
    UINT16 usLpFirCof6;           //LpFir系数6
    UINT16 usLpFirCof7;           //LpFir系数7    
    UINT16 usOvfTh;               //adc数据溢出上限阈值
    UINT16 usUdwTh;               //adc数据溢出下限阈值
    UINT16 usOvfUpBound;          //定义落在溢出范围有多少个点记为一个溢出点
    UINT16 usOvfPointFrm;         //当溢出点超过该值以后，产生溢出标志
    UINT16 usNormalUpTh;          //数据溢出消除上限阈值
    UINT16 usNormalDwTh;          //数据溢出消除下限阈值
    UINT16 usOvfClrFrmNum;        //当连续超过该值的数据在正常范围,产生溢出清除标志
    UINT32 usRawdataOffset;       //ADC增益处理，rawdata统一减去该值
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
