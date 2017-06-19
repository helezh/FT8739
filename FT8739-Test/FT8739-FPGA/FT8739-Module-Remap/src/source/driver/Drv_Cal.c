/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Drv_Cal.c
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
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Drv_Cal.h"
#include <string.h>


#if _TEST_CAL_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
/* DMA unit default value */
#define DMA_LEN        1            //除了Amove之外其他算法的DmaLength 1~31
#define DMA_LENA       1            //Amove的DmaLength                 1~31
#define DMALENGTH     ((DMA_LENA << 5) + DMA_LEN)


/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
//ST_CalRegisters * XRAM pCalRegs = (volatile ST_CalRegisters *)CAL_REG_BASE_ADDR;
ST_CalRegisters *pCalRegs = (volatile ST_CalRegisters *)CAL_REG_BASE_ADDR;

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
BOOLEAN g_bCalResumeFlag;

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: DrvCal_Init
*  Brief: Config DMALENGTH,TxNum/RxNum and CalMask/AmoveMask for Cal-modules
*  Input:TxNum,RxNum,CalMask,AmoveMask
* Output:
* Return: None
*******************************************************************************/
void DrvCal_Init(UINT8 ucTxNum, UINT8 ucRxNum, UINT16 usDmask, UINT16 usDmaskA)

{
    CALCKEN = 1;

    pCalRegs->rDmaLen = DMALENGTH;
    
    pCalRegs->rTxRxNum = (ucTxNum << 8) + ucRxNum;       //CAL长度
    pCalRegs->rTxRxNumAm = (ucTxNum << 8)+ ucRxNum;      //Amove长度

    /* 运行时中断可打断源配置 */
    pCalRegs->rDmask = usDmask;//CAL的Mask
    pCalRegs->rDmaskA = usDmaskA;//Amove的Mask

    CALCKEN = 0;
}

/*******************************************************************************
*   Name: DrvCal_Cmd
*  Brief: Set cmd to cal_module and wait for finishing.
*  Input: cmd
* Output:
* Return: None
*******************************************************************************/
void DrvCal_Cmd(UINT16 cmd)
{
    pCalRegs->rCmd &= 0xFF0F;                                  
    pCalRegs->rCmd |= (cmd|CAL_CMD_START);                       

    /* mcu hold ... cal run */
    while((pCalRegs->rInt&CAL_CMD_INT) != CAL_CMD_INT)           
    {
        //DBG_CAL("\nCALINT:%d ",pCalRegs->rInt); 
        
        /* if cal madule is resumed,start again */
        if((pCalRegs->rCmd&CAL_CMD_SUSPEND) == CAL_CMD_SUSPEND)  
        {    
            DBG_CAL("\n\rSUSPEND=%d\n",CAL_CMD_INT);
            pCalRegs->rCmd |= CAL_CMD_RESUME;                    
            g_bCalResumeFlag = TRUE;
        }
    }
    pCalRegs->rCmd |= CAL_CMD_INT_CLR;
    pCalRegs->rCmd  = 0;                                        
}

/*******************************************************************************
*   Name: DrvCal_MatrixProc
*  Brief: Let hardware do ADD/DEC/MOV matrix calculation.
*         ADD/DEC: pCalRegs->rOutAddr = (pCalRegs->rS1Addr +/- pCalRegs->rS2Addr)>>ucShift
*         MOV:     pCalRegs->rOutAddr = pCalRegs->rS1Addr
*  Input: ST_CalMcMatrixParam *pMcMP =>
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixProc(ST_CalMcMatrixParam *pMcMP)
{
    CALCKEN = TRUE;
   
    g_bCalResumeFlag = FALSE;

    pCalRegs->rS1Addr  = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr  = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;
    pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rPThd = pMcMP->ucShift;
    // run
    pCalRegs->rCmd  = ((pMcMP->ucCfg & 0x01)<<8);
    DrvCal_Cmd(pMcMP->usCalCmd);
       
    CALCKEN = FALSE;
}

/*******************************************************************************
*   Name: DrvCal_MatrixAmp
*  Brief: Let hardware do AMP matrix calculation.
*         AMP: pCalRegs->rOutAddr = (pCalRegs->rS1Addr * mul)>>ucShift
*  Input: ST_CalMcMatrixParam *pMcMP =>
*         UINT8 mul
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixAmp(ST_CalMcMatrixParam *pMcMP, SINT16 mul)
{
    CALCKEN = TRUE;
    
    pCalRegs->rS1Addr  = pMcMP->usSrc1Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;    
    pCalRegs->rSize    = (pMcMP->ucTxLen << 8) + pMcMP->ucRxLen;
    pCalRegs->rPThd = pMcMP->ucShift;
    pCalRegs->rPar  = mul;

    // run
    pCalRegs->rCmd = 0;
    DrvCal_Cmd(pMcMP->usCalCmd);
   
    CALCKEN = FALSE;
}

/*******************************************************************************
*   Name: DrvCal_MatrixDiv
*  Brief: Let hardware do AMP matrix calculation.
*         AMP: pCalRegs->rOutAddr = pCalRegs->rS1Addr/div
*  Input: ST_CalMcMatrixParam *pMcMP =>
*         UINT8 div
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixDiv(ST_CalMcMatrixParam *pMcMP, UINT8 div)
{
    CALCKEN = TRUE;
    
    pCalRegs->rS1Addr  = pMcMP->usSrc1Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;
	pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rPar  = div;
    // run
    pCalRegs->rCmd = 0;
    DrvCal_Cmd(pMcMP->usCalCmd);
   
    CALCKEN = FALSE;
}

/*******************************************************************************
*   Name: DrvCal_MatrixMul
*  Brief: M1 : M*K
*         M2 : K*N
*         OUT: M*N
*         Out[i][j] = sum(S1[i][0...(K-1)]*S2[0...(k-1)[j]])
*  Input: ST_CalMcMatrixParam *pMcMP =>
*
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixMul(ST_CalMcMatrixParam *pMcMP, UINT8 K_Num)
{
    //clk
    CALCKEN = TRUE;
    
    // Address
    pCalRegs->rS1Addr  = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr  = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;
	pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rPThd   = pMcMP->ucShift;
    pCalRegs->rNThd   = K_Num;

    pCalRegs->rCmd  = 0;
    DrvCal_Cmd(pMcMP->usCalCmd);
   
    CALCKEN = FALSE;
}


/*******************************************************************************
*   Name: DrvCal_McPeak
*  Brief: Let hardware Search positive/negative peaks
*  Input: ST_CalMcPeakDetectParam *pMcPDP => MC Peak Detect Parameters Struct
*         ST_CalMcPeakInfo *pMcPI => MC Peak Information Struct
* Output: g_stFrmData.CalOut => Calculate Output of Global Frame Data
* Return: None
*******************************************************************************/
#define TX_START      0  //从左上角开始
void DrvCal_McPeak(ST_CalMcPeakDetectParam *pMcPDP, ST_CalMcPeakInfo *pMcPI)
{
    CALCKEN = 1;
    
    pCalRegs->rS1Addr = pMcPDP->usDiffAddr;
    pCalRegs->rS2Addr = pMcPDP->usNegOutAddr;//;
    pCalRegs->rOutAddr  = pMcPDP->usCalOutAddr;
    pCalRegs->rSize   = (pMcPDP->ucTxLen<<8) + pMcPDP->ucRxLen;
    pCalRegs->rPar    = (TX_START<<8) + pMcPDP->ucMaxPeakNum;

    pCalRegs->rPThd   = pMcPDP->usPosThd;
    pCalRegs->rNThd   = pMcPDP->usNegThd;
    pCalRegs->rAThd   = pMcPDP->usAreaThd;
    pCalRegs->rNaThd  = pMcPDP->usNegAreaThd;

    // cmd
    pCalRegs->rCmd = pMcPDP->ucSearchMod<<8;
    DrvCal_Cmd(OP_PKS);

    // Get results
    pMcPI->ucMcPosPeakNum = pCalRegs->rPsCnt;
    pMcPI->ucMcNegPeakNum = pCalRegs->rNsCnt;
    pMcPI->ucMcPosAreaChNum = pCalRegs->rPaCnt;
    pMcPI->ucMcNegAreaChNum = pCalRegs->rNaCnt;

    pMcPI->usMCminValue = pCalRegs->rMinV;
    pMcPI->usMCminPos   = pCalRegs->rMinPos;
    pMcPI->usMCmaxValue = pCalRegs->rMaxV;
    pMcPI->usMCmaxPos   = pCalRegs->rMaxPos;
    
    CALCKEN = 0;
}

/*******************************************************************************
*   Name: DrvCal_Mac
*  Brief: Let hardware do center of gravity calculation
*         pCalRegs->rS1Addr : Data to be computed
*         pCalRegs->rOutAddr  : Result output, sum(c_tx), sum(tx), sum(c_rx), sum(rx)
*  Input: ST_CalMcMacParam *pMcMParm => MC Mac Parameters Struct
* Output: g_stFrmData.CalOut => Calculate Output of Global Frame Data
* Return: None
*******************************************************************************/
void DrvCal_Mac(ST_CalMcMacParam *pMacParm)
{
    CALCKEN = 1;
    
    pCalRegs->rS1Addr = pMacParm->usDiffAddr;
    pCalRegs->rOutAddr  = pMacParm->usCalOutAddr;

    pCalRegs->rSize = (pMacParm->ucTxLen<<8) + pMacParm->ucRxLen;
    pCalRegs->rPar  = (pMacParm->ucTxStart<<8) + pMacParm->ucRxStart;
    pCalRegs->rPThd = pMacParm->ucNoise;

    pCalRegs->rCmd  = (pMacParm->ucMode & 0x03) << 8;

    DrvCal_Cmd(OP_MAC);
    
    CALCKEN = 0;
}

/*******************************************************************************
*   Name: DrvCalcID
*  Brief: Match IDs
*         pCalRegs->rS1Addr: Last ID Position
*         pCalRegs->rS2Addr: Current ID Position
*  Input: UINT16 LastIdPosAddr => Last ID Position Information
*         UINT16 CurrIdPosAddr => Current ID Position Information
*         UINT8 MaxPoint => Maximum Point Number supported
* Output: None
* Return: UINT16 IDs
*******************************************************************************/
void DrvCal_KmID(ST_CalKmIdParam *pKmIDParm)
{
    UINT8 i,j;
    UINT8 MaxPoint;

    MaxPoint = pKmIDParm->ucLastPoint;
    if (MaxPoint < pKmIDParm->ucCurrPoint)
    {
        MaxPoint = pKmIDParm->ucCurrPoint;
    }

    memset((UINT16*)pKmIDParm->usCalOut, 0xFF, 121<<1);

    //clk
    CALCKEN = 1;
   
    // 1.测试 MDS 先求各点的相互距离
    pCalRegs->rS1Addr = pKmIDParm->usLastIdPosAddr;
    pCalRegs->rS2Addr = pKmIDParm->usCurrIdPosAddr;
    pCalRegs->rOutAddr = pKmIDParm->usCalOut;
    pCalRegs->rSize    = (pKmIDParm->ucLastPoint << 8) + pKmIDParm->ucCurrPoint;

    //cmd
    pCalRegs->rCmd = 0;
    DrvCal_Cmd(OP_MDS);

    for (i = 0; i < pKmIDParm->ucLastPoint; i++)
    {
        for (j = 0; j < pKmIDParm->ucCurrPoint; j++)
        {
            *(UINT16*)(pKmIDParm->usCalOut+(i*11 + j)*2) = ~(*(UINT16*)(pKmIDParm->usCalOut+(i*11 + j)*2));
        }
    }

    // 2.再cal ID号
    pCalRegs->rS1Addr = pKmIDParm->usCalOut;
    pCalRegs->rSize   = (MaxPoint<<8) + MaxPoint;

    //cmd
    pCalRegs->rCmd  = 0;
    DrvCal_Cmd(OP_KM);

    /* 解析硬件CalID 计算的结果 */
    for (i = 0; i < 11; i++)
    {
        // Get ID
        if (i < 4)
        {
            *(UINT16*)(pKmIDParm->usCalOut + i*2) = ( pCalRegs->rID0 >> (4*i) ) % 0x10;
        }
        else if (i < 8)
        {
            *(UINT16*)(pKmIDParm->usCalOut + i*2) = ( pCalRegs->rID1 >> (4*(i-4)) ) % 0x10;
        }
        else
        {
            *(UINT16*)(pKmIDParm->usCalOut + i*2) = ( pCalRegs->rID2 >> (4*(i-8)) ) % 0x10;
        }
    }
          
    CALCKEN = 0;
  
}

/*******************************************************************************
*  Name: DrvCal_CRC16
*  Brief: 
*  1. if Area == 0 Calculat CRC for Dram
*  2. if Area == 1 CRC start Address is 0xFC:xxxx
*  3. if Area == 2 CRC start Address is 0xFD:xxxx
*  4. if Area == 3 CRC Start Address is 0xFE:xxxx
*  5. if Area == 4 CRC start Address is 0xFF:xxxx
*  6. usLen:0 ~ 70k
*  
*  for example:
*  1.if want to calculat CRC Result for the zone (0xFE:E800 ~ 0xFF:FFFF),
*  set Area = 3,usSrc1Addr = 0xE800, uslen = 35*1024(70k)
*  2.if want to calculat CRC Result for the zone (0xFF:0000 ~ 0xFF:FFFF),
*  set Area = 4,usSrc1Addr = 0x0000, uslen = 32*1024(64k)
*  3.if want to calculat CRC Result for the zone (0xFC:E800 ~ 0xFC:FFFF),
*  set Area = 1,usSrc1Addr = 0xE800, uslen = 3*1024(6k)
*
* Input:  usSrc1Addr,usLen,Area,type,AddrH
* Output: None
* Return: CRC16 result
*******************************************************************************/
UINT16 DrvCal_CRC16(UINT16 usSrc1Addr, UINT16 usLen, UINT8 Area, BOOLEAN type)
{
    UINT16 value;
    //clk
    CALCKEN = 1;
          
    //cfg
    pCalRegs->rS1Addr = usSrc1Addr;
    pCalRegs->rSize   = usLen;

    //启动
    pCalRegs->rCmd = (UINT16)type << 10;     //set xorsum function

    switch(Area)
    {
        case CRC_SRC_DRAM:
            pCalRegs->rCmd |= (0x00<<8);
            pCalRegs->rInt &= ~(1<<8);
            break;

        case CRC_SRC_FC_ZONE:
            pCalRegs->rCmd |= (0x01<<8);
            pCalRegs->rInt &= ~(1<<8);
            break;
            
        case CRC_SRC_FD_ZONE:
            pCalRegs->rCmd |= (0x01<<8);
            pCalRegs->rInt |= (1<<8); 
            break;

        case CRC_SRC_FE_ZONE:
            pCalRegs->rCmd |= (0x03<<8);
            pCalRegs->rInt &= ~(1<<8); 
            break;
            
        case CRC_SRC_FF_ZONE:
            pCalRegs->rCmd |= (0x03<<8);
            pCalRegs->rInt |= (1<<8); 
            break;
        default :
            break;            
    }
    
    DrvCal_Cmd(OP_CRC);

    value = pCalRegs->rCrc;
      
    CALCKEN = 0;
    return value;
}


#if 0
/*******************************************************************************
*   Name: Test_CAL_MaxtixMul_PtoP1
*  Brief: M1 : M*N
*         M2 : 1*N
*         OUT: M*N
*         Out[i][j] = M2[1][j]*M1[i][j];
*  Input: ST_CalMcMatrixParam *pMcMP =>
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixMul_PtoP1(ST_CalMcMatrixParam *pMcMP)
{
    //clk
    CALCKEN = TRUE;
          
    // Address
    pCalRegs->rS1Addr  = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr  = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;
    pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rPThd   = pMcMP->ucShift;
    
    pCalRegs->rInt &=(~(1<<13));
    pCalRegs->rInt |= (pMcMP->ucCfg<<13);
    
    pCalRegs->rCmd &= (~CAL_CMD_MUL2_EN);    // 1*2矩阵

    DrvCal_Cmd(pMcMP->usCalCmd);
          
    CALCKEN = FALSE;
}

/*******************************************************************************
*   Name: DrvCal_MatrixMul_PtoP2
*  Brief: M1 : M*N
*         M2 : M*N
*         OUT: M*N
*         Out[i][j] = M1[i][j]*M2[i][j];
*  Input: ST_CalMcMatrixParam *pMcMP =>
*
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixMul_PtoP2(ST_CalMcMatrixParam *pMcMP)
{
    //clk
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr  = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr  = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;
    pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rPThd   = pMcMP->ucShift;

    pCalRegs->rCmd |= CAL_CMD_MUL2_EN;       // 2*2矩阵

    DrvCal_Cmd(pMcMP->usCalCmd);
          
    CALCKEN = FALSE;
}
#endif
/*******************************************************************************
*  Name: DrvCal_MatrixMul2
*  Brief:
*         if CalReg->cmd.bit13 == 1:          // 2*2矩阵运算
*         {
*            S1 : M*N
*            S2 : M*N
*            OUT: M*N
*            Out[i][j] = S1[i][j]*S2[i][j];
*         }
*
*         if  CalReg->Cmd.bit13 == 0:         // 1*2矩阵运算
*         {
*           if CalReg->Int.bit13 == 1:        //按行乘固定数
*           {
*              S1 : M*N
*              S2 : 1*N
*              OUT: M*N
*              Out[i][j] = S2[1][j]*S1[i][j]
*           }
*           if CalReg->Int.bit13 == 0:        //按列乘固定数
*           {
*              S1 : M*N
*              S2 : M*1
*              OUT: M*N
*              Out[i][j] = S2[i][1]*S1[i][j]
*           }                        
*         }
*
*  Input: ST_CalMcMatrixParam *pMcMP =>
*  Output: None
*  Return: None
*******************************************************************************/
void DrvCal_MatrixMul2(ST_CalMcMatrixParam *pMcMP,BOOLEAN MulMode)
{
    //clk
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr  = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr  = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;
    pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rPThd   = pMcMP->ucShift;

    if(MulMode == MUL2_MODE_1)                   // 2*2矩阵  
    {
        pCalRegs->rCmd |= CAL_CMD_MUL2_EN;       // 2*2方式   
    }
    else if(MulMode == MUL2_MODE_0)              // 1*2矩阵 
    {
        pCalRegs->rInt &=(~(1<<13));
        pCalRegs->rInt |= (pMcMP->ucCfg<<13);    // 按行乘或者按列乘    
        pCalRegs->rCmd &= (~CAL_CMD_MUL2_EN);    // 1*2方式            
    }

    DrvCal_Cmd(pMcMP->usCalCmd);
          
    CALCKEN = FALSE;
}

#if 0
/*******************************************************************************
*   Name: DrvCal_MatrixCompensation_1
*  Brief:
*  Input: ST_CalMcMatrixParam *pMcMP =>
*         UINT8 Thr: Threshold
*         UINT8 step: Step
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixCompensation_1(ST_CalMcMatrixParam *pMcMP, UINT8 Thr, UINT8 step)
{
    // CLK
    CALCKEN = TRUE;

    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr  = pMcMP->usDstAddr;

    // 矩阵长度设置
    pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;

    // com新旧模式选择
    if(pMcMP->ucCfg == COM_CFG_0)
    {
        pCalRegs->rInt&=(~(1<<14));
    }
    else if(pMcMP->ucCfg == COM_CFG_1) 
    {
        pCalRegs->rInt|=(1<<14);
    }

    // Mode
    pCalRegs->rPThd = (COMPENSATION_MODE<<8);

    // Step and threshold
    pCalRegs->rNThd = ((Thr<<8)|(step));

    // 不补偿区域设置
    pCalRegs->rPThd |= ((NO_COMPENSATION_TX_LENGTH<<4) | (NO_COMPENSATION_RX_LENGTH));
    pCalRegs->rPar  = ((NO_COMPENSATION_TX_START <<8) | (NO_COMPENSATION_RX_START));


    //启动
    pCalRegs->rCmd  = 0;
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}
/*******************************************************************************
*   Name: DrvCal_MatrixCompensation_2
*  Brief:
*  Input: ST_CalMcMatrixParam *pMcMP =>
*         UINT8 Thr: Threshold
*         UINT8 step: Step
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixCompensation_2(ST_CalMcMatrixParam *pMcMP, UINT8 Thr, UINT8 mode)
{
    // CLK
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr  = pMcMP->usDstAddr;
    
    // 矩阵长度设置
    pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;

    // Mode
    pCalRegs->rPThd = (COMPENSATION_MODE<<8);

    // com新旧模式选择
    if(pMcMP->ucCfg == COM_CFG_0)
    {
        pCalRegs->rInt&=(~(1<<14));
    }
    else if(pMcMP->ucCfg == COM_CFG_1) 
    {
        pCalRegs->rInt|=(1<<14);      
    }

    // Step and threshold
    pCalRegs->rNThd = Thr;

    // 不补偿区域设置
    pCalRegs->rPThd |= ((NO_COMPENSATION_TX_LENGTH<<4) | (NO_COMPENSATION_RX_LENGTH));
    pCalRegs->rPar  = ((NO_COMPENSATION_TX_START <<8) | (NO_COMPENSATION_RX_START));

    pCalRegs->rCmd  = 0;
    // com新模式按行列计算选择: 0: 按行计算, 1: 按列计算
    pCalRegs->rCmd |= (mode<<10);  
    //启动
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}
#endif
/*******************************************************************************
*  Name: DrvCal_MatrixCompensation
*  Brief: 1.旧补偿算法:若矩阵1的数据(diff)大于阈值正值,将矩阵2(base)对应位置的数
*           据加上补偿值以后放到结果矩阵对应位置.若小于阈值负值，将矩阵2(base)对
*           应位置的数据减去补偿值以后放到结果矩阵对应位置.其他值不变
*
*         2.新补偿算法:若矩阵1的数据(rawdata)大于阈值正值，则将该数据减去补偿值
*           以后放到结果矩阵，若小于阈值负值，则将该数据加上补偿值以后放到结果
*           矩阵。其他值不变(各行或各列的补偿值不一样，矩阵2为补偿值)
*  Input: ST_CalMcMatrixParam *pMcMP =>
*         UINT8 Thr: Threshold
*         UINT8 step: Step
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixCompensation(ST_CalMcMatrixParam *pMcMP, UINT8 Thr, UINT8 Cfg)
{
    // CLK
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr  = pMcMP->usDstAddr;
    
    // 矩阵长度设置
    pCalRegs->rSize = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;

    pCalRegs->rCmd  = 0;
    // com新旧模式选择
    if(pMcMP->ucCfg == COM_CFG_0)
    {
        pCalRegs->rInt&=(~CAL_FUNC_SEL);            //旧算法(根据 diff 值调整 base)

        // Step and threshold
        pCalRegs->rNThd = ((Thr<<8)|(Cfg));         //thr:补偿的threshold;Cfg:补偿值        
    }
    else if(pMcMP->ucCfg == COM_CFG_1) 
    {
        pCalRegs->rInt|= CAL_FUNC_SEL;              //新算法(linefilter)

        // Step and threshold
        pCalRegs->rNThd = Thr;                      //阈值的绝对值
        
        // com新模式按行列计算选择: 0: 按行计算, 1: 按列计算
        pCalRegs->rCmd |= (Cfg<<10);        
    }

    // Mode
    pCalRegs->rPThd = (COMPENSATION_MODE << 8); //0:全屏补偿;1:有不补偿区域    
    // 不补偿区域设置
    pCalRegs->rPThd |= ((NO_COMPENSATION_TX_LENGTH<<4) | (NO_COMPENSATION_RX_LENGTH));
    pCalRegs->rPar  = ((NO_COMPENSATION_TX_START <<8) | (NO_COMPENSATION_RX_START));

    //启动
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}

/*******************************************************************************
*  Name: DrvCal_LDS
*  Brief: 
*         S1[M][N]  (S1的一个元素为16bit(x,y)。x与y都为8bits)
*         S2[M][N]
*         OUT[i][j] = sqrt((S1[i][j].x-S2[i][j].x)^2+(S1[i][j].y-S2[i][j].y)^2)
*  Input: ST_CalMcMatrixParam *pMcMP
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_LDS(ST_CalMcMatrixParam *pMcMP)
{
    // Clk
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr  = pMcMP->usDstAddr;
    pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;

    //启动
    pCalRegs->rCmd  = 0;
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}

/*******************************************************************************
*   Name: DrvCal_MDS
*  Brief: 用于产生两列座标间的距离point to point
*         S1[M]  (S1的一个元素为16bit(x,y)。x与y都为8bits)
*         S2[N]
*         OUT[i][j] = sqrt((S1[i].x-S2[j].x)^2+(S1[i].y-S2[j].y)^2)
*  Input: ST_CalMcMatrixParam *pMcMP =>
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MDS(ST_CalMcMatrixParam *pMcMP)
{
    // Clk
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr  = pMcMP->usDstAddr;
	pCalRegs->rSize    = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;

    //启动
    pCalRegs->rCmd  = 0;
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}

/*******************************************************************************
*   Name: DrvCal_Noise
*  Brief:
*         1.一列数据 差值 = 最大值 - 最小值
*         2.所有列的差值中求最大值 max = max(差值)
*  Input: UINT16 usSrc1Addr
*         UINT8  Tx
*         UINT8  Rx
* Output: None
* Return: Get Max of value,which is sub value of max-min in the same column
*******************************************************************************/
UINT16 DrvCal_Noise(UINT16 usSrc1Addr,UINT8 Tx_Len, UINT8 Rx_Len)
{
    UINT16 Noise;
    //clk
    CALCKEN = TRUE;

    // Cfg
    pCalRegs->rS1Addr = usSrc1Addr;
    pCalRegs->rSize    = (Tx_Len<<8) + Rx_Len;

    pCalRegs->rCmd  = 0;
    DrvCal_Cmd(OP_CHK);

    Noise = pCalRegs->rChk;
      
    CALCKEN = FALSE;
    return Noise;
}

/*******************************************************************************
*   Name: DrvCal_MatrixAMov
*  Brief: 
*    1.Amov可嵌套CAL运算,当启动Amov时可打断当前CAL运算进行AMov运算
*    2.该运算用于在中断中搬移Aram中rawdata到dram
* input : 
* Return: None
*******************************************************************************/
void DrvCal_MatrixAMov(ST_CalMatrixAMov *pMcMP)
{
    UINT8 CALCKEN_BAK = CALCKEN;
    CALCKEN = 1;//clk
          
    pCalRegs->rSizeAm = (pMcMP->ucS1TxLen << 8) + pMcMP->ucS1RxLen;  //  21 TxRxLen
    pCalRegs->rS1AddrA = pMcMP->usSrc1Addr; // SrcAddr
    pCalRegs->rOutAddrA = pMcMP->usDstAddr;   // DstAddr
    pCalRegs->rInt &= 0xFF00;
    pCalRegs->rInt |= (0<<3);//不支持合并aMove Mode Select 03
    pCalRegs->rInt |= CAL_CMD_AMOV_EN;//启用aMove  04
    pCalRegs->rInt |= CAL_CMD_AMOV_START;//aMoveStart 0
     /* mcu hold ... cal run */
    while ((pCalRegs->rInt&CAL_CMD_AMOV_INT) != CAL_CMD_AMOV_INT)
    {
        DBG_CAL("\nwaiting...int");
        /* if cal madule is resumed,start again */
        if ((pCalRegs->rInt&CAL_CMD_AMOV_SUSPEND) == CAL_CMD_AMOV_SUSPEND)
        {
            pCalRegs->rInt |= CAL_CMD_AMOV_RESUME;
            g_bCalResumeFlag = TRUE;
        }
    }    
    pCalRegs->rInt |= CAL_CMD_AMOV_INT_CLR;
    pCalRegs->rInt &= 0xFF00;
    
    //有可能在ASM中断中调用了AMOVE,然后ASM中断打断了其他CAL算法，退出Amove算法时,假如关掉了
    //CALCKEN，则被打断的CAL算法会没法执行下去，导致系统卡死.因此，需要在调用AMOVE的时候，把
    //进来之前的CALCKEN保存下来，退出的时候恢复成原样.
    CALCKEN = CALCKEN_BAK;   
}

/*******************************************************************************
*  Name: DrvCal_MatrixAvg
*  Brief: 
*  1.按行按列求取源矩阵的平均值，Src1Addr存放的是源数据矩阵，Src2Addr存放的是各行
*    或各列的阈值(各行或各列都有自己单独的阈值)，结果放在OutAddr中。
*  2.usAvgMode = 0，若源数据超过阈值,则用该行或该列的阈值代替源数据参与计算
*  3.usAvgMode = 1，若源数据超过阈值,则将该数据丢弃，计算该行或该列剩余的平均值
*  input:   
*    ucCfg: 0: 操作数是有符号数;  1:操作数是无符号数
*    ucLineCfg: 0: 按行计算; 1: 按列计算
*    ucDataType: 0: 原始数据; 1: 数据先求绝对值 
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixAvg(ST_CalMcMatrixParam *pMcMP,UINT8 usAvgMode)
{
    //clk
    CALCKEN = TRUE;
             
    // Address
    pCalRegs->rS1Addr   = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr   = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr  = pMcMP->usDstAddr;
    pCalRegs->rSize     = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen; // 6

    pCalRegs->rInt &=(~(1<<14));
    pCalRegs->rInt |=(usAvgMode<<14);    
    pCalRegs->rCmd  = (pMcMP->ucLineCfg<<10)|(pMcMP->ucDataType<<9)|(pMcMP->ucCfg<<8);
    pCalRegs->rCmd |= CAL_CMD_MOD_EXTEND;
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}

/*******************************************************************************
*  Name: DrvCal_MatrixMaxMin
*  Brief: 
*  input:   
*        ucCfg: 0: 操作数是有符号数;  1:操作数是无符号数
*    ucLineCfg: 0: 按行计算; 1: 按列计算
*   ucDataType: 0: 原始数据; 1: 数据先求绝对值 
* Output: None
* Return: None
*******************************************************************************/
void DrvCal_MatrixMaxMin(ST_CalMcMatrixParam *pMcMP)
{
    //clk
    CALCKEN = TRUE;
            
    // Address
    pCalRegs->rS1Addr   = pMcMP->usSrc1Addr;
    pCalRegs->rOutAddr  = pMcMP->usDstAddr;  
    pCalRegs->rSize   = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rCmd= (pMcMP->ucLineCfg<<10)|(pMcMP->ucDataType<<9)|(pMcMP->ucCfg<<8); //00   
    pCalRegs->rCmd |= CAL_CMD_MOD_EXTEND;//
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}

/*******************************************************************************
*   Name: DrvCal_MatrixCount
*  Brief:
*     IN: M*N矩阵  
*    OUT: 处于[min max]之间的矩阵元素个数
* Return:
*******************************************************************************/
UINT16 DrvCal_MatrixCount(ST_CalMcMatrixParam *pMcMP, SINT16 ssMin,SINT16 ssMax)
{
    UINT16 usNum = 0;
    //clk
	CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;   
    pCalRegs->rSize   = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rPThd     = ssMax;
    pCalRegs->rNThd     = ssMin;

    pCalRegs->rCmd = 0; 
    pCalRegs->rCmd |= CAL_CMD_MOD_EXTEND;
    DrvCal_Cmd(pMcMP->usCalCmd);

    usNum = pCalRegs->rCntNum;
          
	CALCKEN = FALSE;
    return usNum;
}

/*******************************************************************************
*   Name: DrvCal_SubConst
*  Brief:
*     IN: M*N  1*N
*    OUT: M*N
* input : usCfgLineCol: 0: 按行计算;  1: 按列计算
* Return: None
*******************************************************************************/
void DrvCal_MatrixSubConst(ST_CalMcMatrixParam *pMcMP)
{
    //clk
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;   
    pCalRegs->rSize   = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;

    pCalRegs->rCmd = (pMcMP->ucLineCfg<<10)+(pMcMP->ucCfg<<8);
    pCalRegs->rCmd |= CAL_CMD_MOD_EXTEND;
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}

/*******************************************************************************
*  Name: DrvCal_MatrixCMP
*  Brief:
*   IN: S1[M][N],S2[M][N]  
*   OUT:1. if pCalRegs->rInt  bit14 = 1, OUT[i][j] = MAX(S1[i][j],S2[i][j])
*       2. if pCalRegs->rInt  bit14 = 0, OUT[i][j] = MIN(S1[i][j],S2[i][j])
* input : pMcMP
* Return: None
*******************************************************************************/
void DrvCal_MatrixCMP(ST_CalMcMatrixParam *pMcMP)
{
    //clk
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;   
    pCalRegs->rSize   = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rInt &= (~(1<<14));
    pCalRegs->rInt |= (pMcMP->ucDataType<<14);                                //ucDataType配置是取最大值还是最小值

    pCalRegs->rCmd &= (~(1<<8));    
    pCalRegs->rCmd |= CAL_CMD_MOD_EXTEND + ((pMcMP->ucCfg & 0x01)<<8);        //ucCfg配置有无符号

    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}

/*******************************************************************************
*  Name: DrvCal_MatrixMul3
*  Brief:
*  Brief: S1 : M*1
*         S2 : N*1
*         OUT: M*N
*         Out[i][j] = S1[i][1]*S2[j][1];
* input : pMcMP
* Return: None
*******************************************************************************/
void DrvCal_MatrixMul3(ST_CalMcMatrixParam *pMcMP)
{
    //clk
    CALCKEN = TRUE;
      
    // Address
    pCalRegs->rS1Addr = pMcMP->usSrc1Addr;
    pCalRegs->rS2Addr = pMcMP->usSrc2Addr;
    pCalRegs->rOutAddr = pMcMP->usDstAddr;     
    pCalRegs->rSize   = (pMcMP->ucTxLen<<8) + pMcMP->ucRxLen;
    pCalRegs->rPThd = pMcMP->ucShift;
    pCalRegs->rCmd |= CAL_CMD_MOD_EXTEND;
    DrvCal_Cmd(pMcMP->usCalCmd);
      
    CALCKEN = FALSE;
}
#endif


