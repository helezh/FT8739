/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: uart.h
*
*    Author: xinkunpeng
*
*   Created: 2014-05-27
*
*  Abstract: DBG_������ܻ��в���            
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

#define UART_RECEIVE_OPEN     0  // ����ʹ�ܺ�


/************** ģ������� ***************/
//module
#define DBG_FACTORY       /##/printf       // ����ģʽ
#define DBG_INT           printf        // ASM�ж�
#define DBG_INT1          printf             
#define DBG_FLOW          printf    
#define DBG_ID            /##/printf
#define DBG_EVENT         /##/printf       // �����¼�
#define DBG_MAPPING       /##/printf
#define DBG_PALM          /##/printf       // �����
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
#define DBG_COORD         /##/printf       // �������
#define DBG_SC_CLB        /##/printf       // Sc У��
#define DBG_MC_RAW        /##/printf       // Mc Raw��һ��Ϣ
#define DBG_MC_CFG        /##/printf       // Mc����
#define DBG_SC_CFG        /##/printf       // Sc����
#define DBG_SC_CFG        /##/printf       // Sc����
#define DBG_SC_FILTER     /##/printf       // Sc�˲�
#define DBG_FIR           /##/printf       // Fir��任   
#define DBG_PEAK          /##/printf       // Peak ��Ϣ
#define DBG_PWR_FILTER    /##/printf       // ��Դ�˲�
#define DBG_APP_MC_NOISE  /##/printf       // �����������
#define DBG_FRE_HOPPING   /##/printf       // ������Ƶ
#define DBG_SC_NOISE      /##/printf       // ��������
#define DBG_HP            /##/printf       // ��ѹ
#define DBG_BASE_TRACE    /##/printf       // base����
#define DBG_WATER         /##/printf       // ˮ
#define DBG_MC_FRE_POL    /##/printf       // ɨƵ
#define DBG_SW_MON        /##/printf       // ��Դ����monitor����
#define DBG_FRM_TIME      /##/printf       // ֡ʱ����ʾ
#define DBG_AFE_DRV       /##/printf       // ģ���ʼ��
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
#define DBG_FACTORY       /##/     // ����ģʽ    
#define DBG_INT           /##/     // ASM�ж�
#define DBG_INT1          /##/     
#define DBG_FLOW          /##/                                                                            
#define DBG_ID            /##/                                                                              
#define DBG_EVENT         /##/     // �����¼�                                                            
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
#define DBG_COORD         /##/       // �������                                                            
#define DBG_SC_CLB        /##/       // Sc У��                                                             
#define DBG_MC_RAW        /##/       // Mc Raw��һ?
#define DBG_MC_CFG        /##/       // Mc����     
#define DBG_SC_CFG        /##/       // Sc����                                                              
#define DBG_SC_FILTER     /##/       // Sc�˲�                                                              
#define DBG_FIR           /##/       // Fir��任                                                           
#define DBG_PEAK          /##/       // Peak ��Ϣ                                                           
#define DBG_PWR_FILTER    /##/       // ��Դ�˲�                                                            
#define DBG_APP_MC_NOISE  /##/       // ����������?
#define DBG_FRE_HOPPING   /##/       // ������Ƶ   
#define DBG_SC_NOISE      /##/       // ��������
#define DBG_HP            /##/       // ��ѹ
#define DBG_BASE_TRACE    /##/       // base����
#define DBG_WATER         /##/       // ˮ
#define DBG_MC_FRE_POL    /##/       // ɨƵ
#define DBG_SW_MON        /##/       // ��Դ����monitor����
#define DBG_FRM_TIME      /##/       // ֡ʱ����ʾ
                                                                                                            
#define DBG_AFE_DRV       /##/       // ģ���ʼ��   
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

