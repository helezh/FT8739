/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
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
#define EX_OP_CMP              (0x07<<4)//FT8836 新加
#define EX_OP_MUL3             (0x08<<4)//FT8836 新加

#define TX_LOCAL_NUM    18//18 // 总的大小
#define RX_LOCAL_NUM    36//30 // 16//28

#define CAL_TEST_TX     18//18//16 // 测试局部
#define CAL_TEST_RX     36//30//28 //16//28


#define TX_ARAM_NUM    TX_LOCAL_NUM
#define RX_ARAM_NUM    RX_LOCAL_NUM

#define CAL_ARAM_TX     18//18//16 // 测试局部
#define CAL_ARAM_RX     36//30//28 //16//28


#define CAL_MDS_TX_POINT    11
#define CAL_MDS_RX_POINT    11
#define CAL_DATA_SIZE       (TX_LOCAL_NUM*RX_LOCAL_NUM)
#define ID_POS_DATA_SIZE    10
#define MAX_POINT           ID_POS_DATA_SIZE
#define MAX_PEAK            (MAX_POINT*3 )


// CRC数据源片区
#define CRC_SRC_DRAM            0   // 00
#define CRC_SRC_FC_ZONE         1   // FC:0000 -- FC:FFFF
#define CRC_SRC_FD_ZONE         2   // FD:0000 -- FD:FFFF
#define CRC_SRC_FE_ZONE         3   // FE:0000 -- FE:FFFF
#define CRC_SRC_FF_ZONE         4   // FF:0000 -- FF:0000

#define CRC_MOD_XOR             1   // 异或求和
#define CRC_MOD_CRC             0   // CRC8方式

#define SUB_MOD_0               0   // sign 加减 sign = sign
#define SUB_MOD_1               1   // unsign 加减 unsign = unsign

#define MOV_CFG_0               0   // 不转置
#define MOV_CFG_1               1   // 转置

#define SIGN_MOD_0              0   // sign 加减 sign = sign
#define SIGN_MOD_1              1   // unsign 加减 unsign = unsign

#define MUL2_CFG_0              0   // mul2按列乘固定常数
#define MUL2_CFG_1              1   // mul2按行乘固定常数

#define MUL2_MODE_0             0   //MUL2选择1维数组乘以2维数组的方式
#define MUL2_MODE_1             1   //MUL2选择2维数组乘以2维数组的方式

#define MAC_MOD_0               0   // original positive value
#define MAC_MOD_1               1   // absolute value

#define MAC_CFG_0               0   // sub-region of frame data
#define MAC_CFG_1               1   // re-pack data

#define COM_CFG_0           0   // com旧算法
#define COM_CFG_1           1   // com新算法: 行列补偿算法

#define EX_MOD_TX           0   // 扩展命令avg/min/max按行计算
#define EX_MOD_RX           1   // 扩展命令avg/min/max按列计算

#define EX_CFG_ORG          0   // 扩展命令avg/min/max按原始数据计算
#define EX_CFG_ABS          1   // 扩展命令avg/min/max按绝对值计算

#define CMP_CFG_0            0 //求最大值
#define CMP_CFG_1            1//求最小值

#define AVG_MODE_0         0//超过阈值的数据用阈值代替
#define AVG_MODE_1         1//超过阈值的数据直接丢弃


#define MAC_TX_START         2 //mac子区域模式tx起始地址
#define MAC_RX_START         2//mac子区域模式rx起始地址
#define MAC_TX_LEN           5//mac算法tx运算长度
#define MAC_RX_LEN           5//mac算法rx运算长度


/* CAL COM运算相关参数配置 */
#define COMPENSATION_MODE           0      // 0:normal(full screen) 1:single point
#define NO_COMPENSATION_TX_LENGTH   8      // bit7:4 in pCalRegs->rPThd
#define NO_COMPENSATION_RX_LENGTH   3      // bit3:0 in pCalRegs->rPThd
#define NO_COMPENSATION_TX_START    0      // bit[15:8] in pCalRegs->rPar
#define NO_COMPENSATION_RX_START    0      // bit[7:0] in pCalRegs->Par

/* CAL MAC运算噪声阈值 */
// length for calculate output
// DrvCal_Mac: need 6
// DrvCal_McPeak:need MC_MAX_PEAK
// DrvCal_KmID:need 11*11
// DrvCal_MatrixMul: need 28*3 (3 buffers)
#define CAL_COMMON_SIZE         (11*11)  //It is the max size of above case

/* Frame Data */
/* 增加子元素时，16位必须在前面，保证cal运算是偶地址运算 */
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
/* CAL矩阵运算参数 */
typedef struct
{
    UINT8 ucTxLen;           // 矩阵操作行数
    UINT8 ucRxLen;           // 矩阵操作列数
    UINT8 ucShift;           // 结果右移个数
    UINT8 ucCfg;            // 配置参数
    UINT8 ucDataType;       // 扩展命令avg/min/max运算数据: 原值or绝对值
    UINT8 ucLineCfg;        // 扩展命令avg/min/max运算数据: 按行计算or按列计算
    UINT16 usSrc1Addr;       // 操作数1的内存开始地址
    UINT16 usSrc2Addr;       // 操作数2的内存开始地址
    UINT16 usDstAddr;        // 运算结果的内存开始地址
    UINT16 usCalCmd;         // 运算符号    
} ST_CalMcMatrixParam;

/* 查找peak结果信息 */
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

/* 查找peak运算参数 */
typedef struct
{
    UINT8 ucRxLen;           // Rx Length
    UINT8 ucTxLen;           // Tx Length
    UINT8 ucMaxPeakNum;      // 最大peak数量
    UINT8 ucSearchMod;       // 0: 十字;  1: 米字

    UINT16 usDiffAddr;       // Diff内存的开始地址
    UINT16 usCalOutAddr;     // 正peak内存的开始地址
    UINT16 usNegOutAddr;     // 负peak内存的开始地址

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
    UINT8 aucMcPeakValid[(MAX_PEAK >> 3) + 1];  //互电容PEAK 有效性标识，每个PEAK 用一个bit 标识其有效性
    UINT8 ucMcPosPeakNum;                         //互电容正PEAK 数量
    UINT8 ucMcNegPeakNum;                         //互电容负PEAK 数量
    UINT8 ucCurrPeakNum;                          //上一帧实际点数
    UINT8 ucLastPeakNum;                          //上一帧实际点数
    UINT16 ucMcPosAreaChNum;                       //互电容超过AREA TH CH 数量
    UINT16 ucMcNegAreaChNum;                       //互电容超过AREA TH CH 数量    
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

/* ID运算参数 */
typedef struct
{
    UINT8  ucLastPoint;      // 上一帧点数
    UINT8  ucCurrPoint;      // 当前帧点数
    UINT16 usLastIdPosAddr;  // 上一帧点信息所在内存的开始地址
    UINT16 usCurrIdPosAddr;  // 当前帧点信息所在内存的开始地址
    UINT16 usCalOut;         // ID匹配结果所在内存的开始地址
} ST_CalKmIdParam;

/* AMOV运算参数 */
typedef struct
{
    UINT8 ucS1TxLen;      // 矩阵S1的TxLen
    UINT8 ucS1RxLen;      // 矩阵S1的RxLen
    UINT16 usSrc1Addr;    // 操作数S1的内存开始地址
    UINT16 usDstAddr;     // 运算结果的内存开始地址
    UINT16 usDmaMask;     // 扩展命令avg/min/max运算数据: 原值or绝对值
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


