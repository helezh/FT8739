/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: uart.h
*
*    Author: xinkunpeng
*
*   Created: 2014-05-27
*
*  Abstract: DBG_输出不能换行操作            
*
* Reference:
*
*******************************************************************************/
#ifndef  __UART_H__
#define  __UART_H__

#include "CfgPlatform.h"

/* Conditional Compiler Options */
#define _BLK_DBG_EN           1

#if _BLK_DBG_EN
/*******************************************************************************
* Included files
*******************************************************************************/
#include <STDIO.H>
#include "FT8836.h"
#include "CfgPlatform.h"
#include <stdlib.h>
#include <ctype.h>

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
#define BAUD_RATE 115200

#define UART_RECEIVE_OPEN     0  // 接收使能宏


/************** 模块输出宏 ***************/
//module
#define DBG_FACTORY       /##/printf       // 工厂模式
#define DBG_INT           printf        // ASM中断
#define DBG_INT1          printf             
#define DBG_FLOW          printf    
#define DBG_ID            /##/printf
#define DBG_EVENT         /##/printf       // 触摸事件
#define DBG_MAPPING       /##/printf
#define DBG_PALM          /##/printf       // 大面积
#define DBG_FH            /##/printf
#define DBG_LIFT_UP       /##/printf
#define DBG_FLYING        /##/printf
#define DBG_POINT_FILTE   /##/printf
#define DBG_REGFILIE      /##/printf
#define DBG_MC_NOISE_INIT /##/printf
#define DBG_TEST_NOISE    /##/printf
#define DBG_HOST          /##/printf
#define DBG_POWER         /##/printf
#define DBG_SFR           /##/printf
#define DBG_MC_BASE       /##/printf
#define DBG_SC_BASE       /##/printf
#define DBG_SC_BASE       /##/printf
#define DBG_COORD         /##/printf       // 坐标计算
#define DBG_SC_CLB        /##/printf       // Sc 校正
#define DBG_MC_RAW        /##/printf       // Mc Raw归一信息
#define DBG_MC_CFG        /##/printf       // Mc配置
#define DBG_SC_CFG        /##/printf       // Sc配置
#define DBG_SC_CFG        /##/printf       // Sc配置
#define DBG_SC_FILTER     /##/printf       // Sc滤波
#define DBG_FIR           /##/printf       // Fir逆变换   
#define DBG_PEAK          /##/printf       // Peak 信息
#define DBG_PWR_FILTER    /##/printf       // 电源滤波
#define DBG_APP_MC_NOISE  /##/printf       // 互容噪声检测
#define DBG_FRE_HOPPING   /##/printf       // 互容跳频
#define DBG_SC_NOISE      /##/printf       // 自容噪声
#define DBG_HP            /##/printf       // 重压
#define DBG_BASE_TRACE    /##/printf       // base跟踪
#define DBG_WATER         /##/printf       // 水
#define DBG_MC_FRE_POL    /##/printf       // 扫频
#define DBG_SW_MON        /##/printf       // 电源管理monitor流程
#define DBG_FRM_TIME      /##/printf       // 帧时间显示
#define DBG_AFE_DRV       /##/printf       // 模拟初始化
#define DBG_SC_SCAN       /##/printf

#define DBG_ALEN          /##/printf

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
void  DrvUartInit(void);
SINT8 putchar(SINT8 c);
void TestUart();

#else
#define DrvUartInit(x)    /##/

//module
#define putchar           /##/
#define DBG_FACTORY       /##/     // 工厂模式    
#define DBG_INT           /##/     // ASM中断
#define DBG_INT1          /##/     
#define DBG_FLOW          /##/                                                                            
#define DBG_ID            /##/                                                                              
#define DBG_EVENT         /##/     // 触摸事件                                                            
#define DBG_MAPPING       /##/                                                                              
#define DBG_PALM          /##/                                                                              
#define DBG_FH            /##/                                                                              
#define DBG_LIFT_UP       /##/                                                                              
#define DBG_FLYING        /##/                                                                              
#define DBG_POINT_FILTE   /##/                                                                              
#define DBG_REGFILIE      /##/                                                                              
#define DBG_MC_NOISE_INIT /##/                                                                              
#define DBG_TEST_NOISE    /##/                                                                              
#define DBG_HOST          /##/                                                                              
#define DBG_POWER         /##/                                                                              
#define DBG_SFR           /##/                                                                              
#define DBG_MC_BASE       /##/                                                                              
#define DBG_SC_BASE       /##/                                                                              
#define DBG_COORD         /##/       // 坐标计算                                                            
#define DBG_SC_CLB        /##/       // Sc 校正                                                             
#define DBG_MC_RAW        /##/       // Mc Raw归一?
#define DBG_MC_CFG        /##/       // Mc配置     
#define DBG_SC_CFG        /##/       // Sc配置                                                              
#define DBG_SC_FILTER     /##/       // Sc滤波                                                              
#define DBG_FIR           /##/       // Fir逆变换                                                           
#define DBG_PEAK          /##/       // Peak 信息                                                           
#define DBG_PWR_FILTER    /##/       // 电源滤波                                                            
#define DBG_APP_MC_NOISE  /##/       // 互容噪声检?
#define DBG_FRE_HOPPING   /##/       // 互容跳频   
#define DBG_SC_NOISE      /##/       // 自容噪声
#define DBG_HP            /##/       // 重压
#define DBG_BASE_TRACE    /##/       // base跟踪
#define DBG_WATER         /##/       // 水
#define DBG_MC_FRE_POL    /##/       // 扫频
#define DBG_SW_MON        /##/       // 电源管理monitor流程
#define DBG_FRM_TIME      /##/       // 帧时间显示
                                                                                                            
#define DBG_AFE_DRV       /##/       // 模拟初始化   
#define DBG_ALEN          /##/                                                       

//------------------------------------------------------------------------------
// For test
#define DBG_SPI0_SLAVE    /##/

#define DBG_SC_SCAN       /##/

// module
#define DBG_MODULE_DATA   /##/
#define DBG_MODULE_INFO   /##/
#endif


#endif

