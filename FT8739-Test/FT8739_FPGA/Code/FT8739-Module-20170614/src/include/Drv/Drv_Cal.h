/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Drv_mcu.h
*
*    Author: xinkunpeng
*
*   Created: 2014-05-07
*
*  Abstract:
*
* Reference:
*
*   Version:
*******************************************************************************/
#ifndef __DRV_CAL_H__
#define __DRV_CAL_H__


/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"
#include "FT8835_Reg.h"


#if _TEST_CAL_EN
/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
// pCalCmd BIT DEFINITION
#define CAL_CMD_START          BITn(0)
#define CAL_CMD_RUNNING        BITn(1)
#define CAL_CMD_RESUME         BITn(2)
#define CAL_CMD_SUSPEND        BITn(3)
#define CAL_CMD_OP_CFG0        BITn(8)
#define CAL_CMD_OP_CFG1        BITn(9)
#define CAL_CMD_OP_CFG2        BITn(10)
#define CAL_CMD_DMA_OFF        BITn(11)
#define CAL_CMD_EXT_RESUME_EN  BITn(12)
#define CAL_CMD_MUL2_EN        BITn(13)
#define CAL_CMD_INT_CLR        BITn(14)
#define CAL_CMD_MOD_EXTEND     BITn(15)
#define CAL_OP_MASK            0x00F0

//CALINT
#define CAL_CMD_AMOV_START     BITn(0)
#define CAL_CMD_AMOV_RESUME    BITn(1)
#define CAL_CMD_AMOV_INT_CLR   BITn(2)
#define CAL_CMD_AMOV_MODE      BITn(3)
#define CAL_CMD_AMOV_EN        BITn(4)
#define CAL_CMD_AMOV_SUSPEND   BITn(5)
#define CAL_CMD_AMOV_RUNNING   BITn(6)
#define CAL_CMD_AMOV_INT       BITn(7)
#define CAL_FUNC_SEL           BITn(14)
#define CAL_CMD_INT            BITn(15)

//CALSEL
#define CAL_AMOV_CFG           BITn(14)
#if 0
#define CAL_DSEL_AMOV_DRAM     (0x00<<12)
#define CAL_DSEL_AMOV_ARAM     (0x01<<12)
#define CAL_DSEL_AMOV_PRAM     (0x02<<12)
#define CAL_S2SEL_AMOV_DRAM    (0x00<<10)
#define CAL_S2SEL_AMOV_ARAM    (0x01<<10)
#define CAL_S2SEL_AMOV_PRAM    (0x02<<10)
#define CAL_S1SEL_AMOV_DRAM    (0x00<<8)
#define CAL_S1SEL_AMOV_ARAM    (0x01<<8)
#define CAL_S1SEL_AMOV_PRAM    (0x02<<8)
#define CAL_DSEL_DRAM          (0x00<<4)
#define CAL_DSEL_ARAM          (0x01<<4)
#define CAL_DSEL_PRAM          (0x02<<4)
#define CAL_S2SEL_DRAM         (0x00<<2)
#define CAL_S2SEL_ARAM         (0x01<<2)
#define CAL_S2SEL_PRAM         (0x02<<2)
#define CAL_S1SEL_DRAM         (0x00<<0)
#define CAL_S1SEL_ARAM         (0x01<<0)
#define CAL_S1SEL_PRAM         (0x02<<0)
#endif

// CAL_OP_MOD DEFINITION
#define OP_SUB                 (0x00<<4)
#define OP_ADD                 (0x01<<4)
#define OP_MOV                 (0x02<<4)
#define OP_COM                 (0x03<<4)
#define OP_AMP                 (0x04<<4)
//#define OP_FLT                 (0x05<<4)
#define OP_MDS                 (0x06<<4)
#define OP_LDS                 (0x07<<4)
#define OP_CHK                 (0x08<<4)
#define OP_CRC                 (0x09<<4)
#define OP_PKS                 (0x0A<<4)
//#define OP_MUL                 (0x0B<<4)
#define OP_MAC                 (0x0C<<4)
#define OP_KM                  (0x0D<<4)
#define OP_MUL2                (0x0E<<4)
#define OP_DIV                 (0x0F<<4)

// CAL_EXTEND_MOD DEFINITION
#define EX_OP_AVG              (0x00<<4)
#define EX_OP_MIN              (0x01<<4)
#define EX_OP_MAX              (0x02<<4)
#define EX_OP_SUBCONST         (0x03<<4)
#define EX_OP_COUNT            (0x04<<4)
#define EX_OP_AMOV             (0x05<<4)
#define EX_OP_CMP              (0x07<<4)//FT8836 �¼�
#define EX_OP_MUL3             (0x08<<4)//FT8836 �¼�

#define TX_LOCAL_NUM    18//18 // �ܵĴ�С
#define RX_LOCAL_NUM    36//30 // 16//28

#define CAL_TEST_TX     18//18//16 // ���Ծֲ�
#define CAL_TEST_RX     36//30//28 //16//28


#define TX_ARAM_NUM    TX_LOCAL_NUM
#define RX_ARAM_NUM    RX_LOCAL_NUM

#define CAL_ARAM_TX     18//18//16 // ���Ծֲ�
#define CAL_ARAM_RX     36//30//28 //16//28


#define CAL_MDS_TX_POINT    11
#define CAL_MDS_RX_POINT    11
#define CAL_DATA_SIZE       (TX_LOCAL_NUM*RX_LOCAL_NUM)
#define ID_POS_DATA_SIZE    10
#define MAX_POINT           ID_POS_DATA_SIZE
#define MAX_PEAK            (MAX_POINT*3 )


// CRC����ԴƬ��
#define CRC_SRC_DRAM            0   // 00
#define CRC_SRC_FC_ZONE         1   // FC:0000 -- FC:FFFF
#define CRC_SRC_FD_ZONE         2   // FD:0000 -- FD:FFFF
#define CRC_SRC_FE_ZONE         3   // FE:0000 -- FE:FFFF
#define CRC_SRC_FF_ZONE         4   // FF:0000 -- FF:0000

#define CRC_MOD_XOR             1   // ������
#define CRC_MOD_CRC             0   // CRC8��ʽ

#define SUB_MOD_0               0   // sign �Ӽ� sign = sign
#define SUB_MOD_1               1   // unsign �Ӽ� unsign = unsign

#define MOV_CFG_0               0   // ��ת��
#define MOV_CFG_1               1   // ת��

#define SIGN_MOD_0              0   // sign �Ӽ� sign = sign
#define SIGN_MOD_1              1   // unsign �Ӽ� unsign = unsign

#define MUL2_CFG_0              0   // mul2���г˹̶�����
#define MUL2_CFG_1              1   // mul2���г˹̶�����

#define MUL2_MODE_0             0   //MUL2ѡ��1ά�������2ά����ķ�ʽ
#define MUL2_MODE_1             1   //MUL2ѡ��2ά�������2ά����ķ�ʽ

#define MAC_MOD_0               0   // original positive value
#define MAC_MOD_1               1   // absolute value

#define MAC_CFG_0               0   // sub-region of frame data
#define MAC_CFG_1               1   // re-pack data

#define COM_CFG_0           0   // com���㷨
#define COM_CFG_1           1   // com���㷨: ���в����㷨

#define EX_MOD_TX           0   // ��չ����avg/min/max���м���
#define EX_MOD_RX           1   // ��չ����avg/min/max���м���

#define EX_CFG_ORG          0   // ��չ����avg/min/max��ԭʼ���ݼ���
#define EX_CFG_ABS          1   // ��չ����avg/min/max������ֵ����

#define CMP_CFG_0            0 //�����ֵ
#define CMP_CFG_1            1//����Сֵ

#define AVG_MODE_0         0//������ֵ����������ֵ����
#define AVG_MODE_1         1//������ֵ������ֱ�Ӷ���


#define MAC_TX_START         2 //mac������ģʽtx��ʼ��ַ
#define MAC_RX_START         2//mac������ģʽrx��ʼ��ַ
#define MAC_TX_LEN           5//mac�㷨tx���㳤��
#define MAC_RX_LEN           5//mac�㷨rx���㳤��


/* CAL COM������ز������� */
#define COMPENSATION_MODE           0      // 0:normal(full screen) 1:single point
#define NO_COMPENSATION_TX_LENGTH   8      // bit7:4 in pCalRegs->rPThd
#define NO_COMPENSATION_RX_LENGTH   3      // bit3:0 in pCalRegs->rPThd
#define NO_COMPENSATION_TX_START    0      // bit[15:8] in pCalRegs->rPar
#define NO_COMPENSATION_RX_START    0      // bit[7:0] in pCalRegs->Par

/* CAL MAC����������ֵ */
// length for calculate output
// DrvCal_Mac: need 6
// DrvCal_McPeak:need MC_MAX_PEAK
// DrvCal_KmID:need 11*11
// DrvCal_MatrixMul: need 28*3 (3 buffers)
#define CAL_COMMON_SIZE         (11*11)  //It is the max size of above case

/* Frame Data */
/* ������Ԫ��ʱ��16λ������ǰ�棬��֤cal������ż��ַ���� */
typedef struct
{
    UINT16 CalBaseAddr[CAL_DATA_SIZE];      // cal base data buffer
    UINT16 CalBaseAddr1[CAL_DATA_SIZE];      // cal base data buffer
    UINT16 CalBaseAddr2[CAL_DATA_SIZE];      // cal base data buffer
    SINT16 ScDiff[CAL_DATA_SIZE];           // sc diff data buffer
    UINT16 LastIdPos[ID_POS_DATA_SIZE<<1];  // (x,y)
    UINT16 CurrIdPos[ID_POS_DATA_SIZE<<1];  // (x,y)
    SINT16 CalOut[CAL_COMMON_SIZE];         // hardware calculating output
} ST_FrameData;
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/
/* CAL����������� */
typedef struct
{
    UINT8 ucTxLen;           // �����������
    UINT8 ucRxLen;           // �����������
    UINT8 ucShift;           // ������Ƹ���
    UINT8 ucCfg;            // ���ò���
    UINT8 ucDataType;       // ��չ����avg/min/max��������: ԭֵor����ֵ
    UINT8 ucLineCfg;        // ��չ����avg/min/max��������: ���м���or���м���
    UINT16 usSrc1Addr;       // ������1���ڴ濪ʼ��ַ
    UINT16 usSrc2Addr;       // ������2���ڴ濪ʼ��ַ
    UINT16 usDstAddr;        // ���������ڴ濪ʼ��ַ
    UINT16 usCalCmd;         // �������    
} ST_CalMcMatrixParam;

/* ����peak�����Ϣ */
typedef struct
{
    UINT8 ucMcPosPeakNum;     // Positvie Peak Number
    UINT8 ucMcNegPeakNum;     // Negative Peak Number
    UINT16 ucMcPosAreaChNum;  // Positive Area Peak Number
    UINT16 ucMcNegAreaChNum;  // Negative Area Peak Number
    UINT16 usMCminValue;      // min-peak diff value
    UINT16 usMCminPos;        // min-peak pos, B15--B8:Y,B7--B0:X
    UINT16 usMCmaxValue;      // max-peak diff value
    UINT16 usMCmaxPos;        // max-peak pos, B15--B8:Y,B7--B0:X
} ST_CalMcPeakInfo;

/* ����peak������� */
typedef struct
{
    UINT8 ucRxLen;           // Rx Length
    UINT8 ucTxLen;           // Tx Length
    UINT8 ucMaxPeakNum;      // ���peak����
    UINT8 ucSearchMod;       // 0: ʮ��;  1: ����

    UINT16 usDiffAddr;       // Diff�ڴ�Ŀ�ʼ��ַ
    UINT16 usCalOutAddr;     // ��peak�ڴ�Ŀ�ʼ��ַ
    UINT16 usNegOutAddr;     // ��peak�ڴ�Ŀ�ʼ��ַ

    SINT16 usPosThd;         // Positive Peak Threshold
    SINT16 usNegThd;         // Negative Peak Threshold
    UINT16 usAreaThd;        // Area Peak Threshold
    SINT16 usNegAreaThd;     // Area Peak Threshold
} ST_CalMcPeakDetectParam;

/* Peak Data */
typedef struct
{
    UINT8 aucMcPosPeak[MAX_PEAK][2];            //[P][0]:TX,  [P][1]:RX
    UINT8 aucMcNegPeak[MAX_PEAK][2];            //[P][0]:TX,  [P][1]:RX
    UINT8 aucMcPeakValid[(MAX_PEAK >> 3) + 1];  //������PEAK ��Ч�Ա�ʶ��ÿ��PEAK ��һ��bit ��ʶ����Ч��
    UINT8 ucMcPosPeakNum;                         //��������PEAK ����
    UINT8 ucMcNegPeakNum;                         //�����ݸ�PEAK ����
    UINT8 ucCurrPeakNum;                          //��һ֡ʵ�ʵ���
    UINT8 ucLastPeakNum;                          //��һ֡ʵ�ʵ���
    UINT16 ucMcPosAreaChNum;                       //�����ݳ���AREA TH CH ����
    UINT16 ucMcNegAreaChNum;                       //�����ݳ���AREA TH CH ����    
} ST_PeakData;

typedef struct
{
    UINT8 ucRxStart;
    UINT8 ucTxStart;
    UINT8 ucRxLen;
    UINT8 ucTxLen;
    UINT8 ucNoise;
    UINT8 ucMode;      //0:FILTER_ORG  1:FILTER_ABS
    UINT16 usDiffAddr;
    UINT16 usCalOutAddr;
} ST_CalMcMacParam;

/* ID������� */
typedef struct
{
    UINT8  ucLastPoint;      // ��һ֡����
    UINT8  ucCurrPoint;      // ��ǰ֡����
    UINT16 usLastIdPosAddr;  // ��һ֡����Ϣ�����ڴ�Ŀ�ʼ��ַ
    UINT16 usCurrIdPosAddr;  // ��ǰ֡����Ϣ�����ڴ�Ŀ�ʼ��ַ
    UINT16 usCalOut;         // IDƥ���������ڴ�Ŀ�ʼ��ַ
} ST_CalKmIdParam;

/* AMOV������� */
typedef struct
{
    UINT8 ucS1TxLen;      // ����S1��TxLen
    UINT8 ucS1RxLen;      // ����S1��RxLen
    UINT16 usSrc1Addr;    // ������S1���ڴ濪ʼ��ַ
    UINT16 usDstAddr;     // ���������ڴ濪ʼ��ַ
    UINT16 usDmaMask;     // ��չ����avg/min/max��������: ԭֵor����ֵ
} ST_CalMatrixAMov;

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern BOOLEAN g_bCalResumeFlag;
extern ST_CalRegisters *pCalRegs;
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void DrvCal_Init(UINT8 ucTxNum, UINT8 ucRxNum, UINT16 usDmask,UINT16 usDmaskA);
void DrvCal_Cmd(UINT16 cmd);
void DrvCal_MatrixProc(ST_CalMcMatrixParam *pMcMP);
void DrvCal_MatrixAmp(ST_CalMcMatrixParam *pMcMP, SINT16 mul);
void DrvCal_MatrixDiv(ST_CalMcMatrixParam *pMcMP, UINT8 div);
void DrvCal_MatrixMul(ST_CalMcMatrixParam *pMcMP, UINT8 K_Num);
void DrvCal_McPeak(ST_CalMcPeakDetectParam *pMcPDP, ST_CalMcPeakInfo *pMcPI);
void DrvCal_Mac(ST_CalMcMacParam *pMacParm);
void DrvCal_KmID(ST_CalKmIdParam *pKmIDParm);
UINT16 DrvCal_CRC16(UINT16 usSrc1Addr, UINT16 usLen, UINT8 Area, BOOLEAN type);
void DrvCal_MatrixMul2(ST_CalMcMatrixParam *pMcMP,BOOLEAN MulMode);
void DrvCal_MatrixCompensation(ST_CalMcMatrixParam *pMcMP, UINT8 Thr, UINT8 Cfg);
void DrvCal_LDS(ST_CalMcMatrixParam *pMcMP);
void DrvCal_MDS(ST_CalMcMatrixParam *pMcMP);
UINT16 DrvCal_Noise(UINT16 usSrc1Addr,UINT8 Tx_Len, UINT8 Rx_Len);
void DrvCal_MatrixAMov(ST_CalMatrixAMov *pMcMP);
void DrvCal_MatrixAvg(ST_CalMcMatrixParam *pMcMP,UINT8 usAvgMode);
void DrvCal_MatrixMaxMin(ST_CalMcMatrixParam *pMcMP);
UINT16 DrvCal_MatrixCount(ST_CalMcMatrixParam *pMcMP, SINT16 ssMin,SINT16 ssMax);
void DrvCal_MatrixSubConst(ST_CalMcMatrixParam *pMcMP);
void DrvCal_MatrixCMP(ST_CalMcMatrixParam *pMcMP);
void DrvCal_MatrixMul3(ST_CalMcMatrixParam *pMcMP);
#endif
#endif


