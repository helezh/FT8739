/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Task_main.h
*
*    Author: tangsujun
*
*   Created: 2016-12-22
*
*  Abstract:
*
* Reference:
*
* Version:
*
*******************************************************************************/

#ifndef __TASK_MAIN_H__
#define __TASK_MAIN_H__


/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"
#include "spi_flash.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
//��λ����
#define RST_POR      0x01
#define RST_UPGRADE  0x02  //������λ��־ upgrade
#define RST_PIN      0x03
#define RST_SOFT     0x04

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern UINT8 g_nRSTtype;           //�����λorӲ����λ
extern BOOLEAN g_bTime20ms_Flag;  // Host��������ʱ��
extern UINT8 g_ucFlashMode;  // ����flashѡ��
#if _TEST_FLASH_LOAD_EN
extern volatile UINT32 far *load_ok;
extern volatile UINT32 far *load_err;
extern volatile UINT32 far *load_cnt;
#endif
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void task_send_int();


void main_task_flash(void);


#endif


