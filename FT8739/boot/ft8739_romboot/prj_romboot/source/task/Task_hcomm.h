/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Task_hcomm.h
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

#ifndef __TASK_HCOMM_H__
#define __TASK_HCOMM_H__


/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define BOOT_CODE_FLAG     0xEF
#define LCD_RELOAD_FLAG    0xED

#define ROMBOOT_VERSION    0x0C
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern BOOLEAN g_bWriteFlag;      // 写时，需要返回值给host标志
extern BOOLEAN hcomm_end_flag;
extern UINT16 g_ucHostIdx   ;          // Host每次通讯RW的字节序号
extern UINT8 g_ucHostCmdNow  ;          // Host--发来的第一个字节，即命令头

extern volatile UINT32 g_usAppStartAddr;// 数据包开始地址

extern UINT8 *pAppAddr ;
extern volatile UINT16 g_ucAppLen;        // 接收数据包大小，

extern UINT8 g_ucChipId[2];
extern UINT8 XRAM g_ucDataBuf[16];             // 长命令缓冲区
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

#endif
