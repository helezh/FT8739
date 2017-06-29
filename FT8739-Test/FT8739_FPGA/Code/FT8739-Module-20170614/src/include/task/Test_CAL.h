/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
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
/* 可以一起测试模块 */
#if 0
#define  TEST_CAL_ADD_EN        0   // 加法
#define  TEST_CAL_SUB_EN        0   // 减法
#define  TEST_CAL_AMP_EN        0   // 乘法
#define  TEST_CAL_DIV_EN        0   // 除法  
#define  TEST_CAL_MOV_EN        0   // 不转置搬移
#define  TEST_CAL_MOV2_EN       0   // 转置搬移(矩阵转置搬移时最好TxNum,RxNum与TxLen,RxLen相等)  
#define  TEST_CAL_MUL2_1_EN     0   // 一维矩阵乘法      (Tx,Rx均必须<=18)       
#define  TEST_CAL_MUL2_2_EN     0   // 二维矩阵乘法
#define  TEST_CAL_COM_1_EN      0   // 旧的补偿运算  
#define  TEST_CAL_COM_2_EN      0   // 新的补偿运算 
#define  TEST_CAL_LDS_EN        0   // 矩阵点对应距离运算
#define  TEST_CAL_MDS_EN        0   // 两列点的矩阵运算  (Tx,Rx均必须<=11)
#define  TEST_CAL_CHK_EN        0   // 均匀度检查
#define  TEST_CAL_CRC_EN        1   // CRC校验
#define  TEST_CAL_XORSUM_EN     0   // xor异或校验
#define  TEST_CAL_AMOV_EN       0   // AMOV    (以下为扩展算法)
#define  TEST_CAL_AVG_TX_EN     0   // 行均值算法 
#define  TEST_CAL_AVG_RX_EN     0   // 列均值算法
#define  TEST_CAL_AVG2_TX_EN    0   // 去掉范围外的值后行均值算法
#define  TEST_CAL_AVG2_RX_EN    0   // 去掉范围外的值后列均值算法
#define  TEST_CAL_AVG_ARAM_EN   0
#define  TEST_CAL_MIN_TX_EN     0   // 行最小值算法
#define  TEST_CAL_MIN_RX_EN     0   // 列最小值算法
#define  TEST_CAL_MAX_TX_EN     0   // 行最大值算法
#define  TEST_CAL_MAX_RX_EN     0   // 列最大值算法
#define  TEST_CAL_COUNT_EN      0   // 矩阵处于某个区间的个数[max,min]
#define  TEST_CAL_SUBCONST_EN   0   // 计算每行(Tx)或者每列(Rx)的减去一个常数
#define  TEST_CAL_MAC_1_EN      0   // 子区域模式MAC
#define  TEST_CAL_MAC_2_EN      0   // 重构模式MAC
#define  TEST_CAL_ID_EN         0   // ID匹配
#define  TEST_CAL_PKS_EN        0   // Peak Search


#else//Auto
#define  TEST_CAL_ADD_EN        1   // 加法
#define  TEST_CAL_SUB_EN        1   // 减法
#define  TEST_CAL_AMP_EN        1   // 乘法
#define  TEST_CAL_DIV_EN        1   // 除法
#define  TEST_CAL_MOV_EN        1   // 不转置搬移
#define  TEST_CAL_MOV2_EN       1   // 转置搬移(矩阵转置搬移时最好TxNum,RxNum与TxLen,RxLen相等)
#define  TEST_CAL_MUL2_1_EN     1   // 一维矩阵乘法      
#define  TEST_CAL_MUL2_2_EN     1   // 二维矩阵乘法
#define  TEST_CAL_COM_1_EN      1   // 旧的补偿运算
#define  TEST_CAL_COM_2_EN      1   // 新的补偿运算 
#define  TEST_CAL_LDS_EN        1   // 矩阵点对应距离运算
#define  TEST_CAL_MDS_EN        1   // 两列点的矩阵运算 
#define  TEST_CAL_CHK_EN        1   // 均匀度检查
#define  TEST_CAL_CRC_EN        1   // CRC校验
#define  TEST_CAL_XORSUM_EN     1   // xor异或校验

#define  TEST_CAL_AMOV_EN       1   // AMOV    (以下为扩展算法)
#define  TEST_CAL_AVG_TX_EN     1   // 行均值算法 
#define  TEST_CAL_AVG_RX_EN     1   // 列均值算法
#define  TEST_CAL_AVG2_TX_EN    1   // 去掉范围外的值后行均值算法
#define  TEST_CAL_AVG2_RX_EN    1   // 去掉范围外的值后列均值算法
#define  TEST_CAL_AVG_ARAM_EN   1
#define  TEST_CAL_MIN_TX_EN     1   // 行最小值算法
#define  TEST_CAL_MIN_RX_EN     1   // 列最小值算法
#define  TEST_CAL_MAX_TX_EN     1   // 行最大值算法
#define  TEST_CAL_MAX_RX_EN     1   // 列最大值算法
#define  TEST_CAL_COUNT_EN      1   // 矩阵处于某个区间的个数[max,min]
#define  TEST_CAL_SUBCONST_EN   1   // 计算每行(Tx)或者每列(Rx)的减去一个常数 
#define  TEST_CAL_MAC_1_EN      1  // 子区域模式MAC
#define  TEST_CAL_MAC_2_EN      1  // 重构模式MAC
#define  TEST_CAL_ID_EN         1  // ID匹配
#define  TEST_CAL_PKS_EN        1  // Peak Search
#endif

#if 1//8836新增模块
/* 单独测试模块 */

#define TEST_CAL_CMP_EN         1  //矩阵比较算法
#define TEST_CAL_MUL3_EN        1  //数组两两相乘算法
#else
/* 单独测试模块 */
#define TEST_CAL_CMP_EN         0   //矩阵比较算法
#define TEST_CAL_MUL3_EN        0   //数组两两相乘算法

#endif

#define  TEST_AMOVE_RTC_INT_EN  1   /* Cal模块中断打断测试,RTC打断,在rtc中断中调用amove */
#define  TEST_SPI0_CAL_INT_EN   0   /* Cal模块中断打断测试,SPI0打断 */
#define  TEST_SPI0_DMA_INT_EN   0   /* Cal模块中断打断测试,启动SPI0 DMA,必须打开TEST_SPI0_CAL_INT_EN */
#define  TEST_IIC_CAL_INT       1   /* Cal模块中断打断测试,iic打断 */



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

