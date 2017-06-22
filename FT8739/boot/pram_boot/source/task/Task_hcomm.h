/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Task_hcomm.h
*
*    Author: tangsujun
*
*   Created: 2017-01-20
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
#define BOOT_CODE_FLAG           0xEF

#define FLASH_STATUS_NOP         0x0000  // 初始状态 
#define FLASH_STATUS_ECC_OK      0xF055  // Flash校验完成标志
#define FLASH_STATUS_ERASE_OK    0xF0AA  // Flash擦除完成标志
#define FLASH_STATUS_WRITE_OK    0x1000  // Flash写入完成标志 

#define BOOT_DOWNLOAD_FLAG       0x0A   // Download 升级标志
#define BOOT_UPGRADE_FLAG        0x0B   // Upgrade 升级标志
#define BOOT_INT_FLAG            0x0C   // int中断使能标志
#define BOOT_ERASE_PAGE_ADDR     0x80   // 指定Page擦除起始Page










/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/
typedef enum
{
    MTASK_NOF         = 0x00,
    MTASK_FLASH_READ  = 0x01,
    MTASK_FLASH_WRITE = 0x02,
    MTASK_FLASH_ECC   = 0x03,
    MTASK_FLASH_ERASE = 0x04,
} ENUM_mTask;

typedef struct
{
    UINT32 usStartAddr;
    UINT16 usLen;
    UINT16 usPos;
    UINT8  pBuf[260];
} ST_BuffInfo;

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern BOOLEAN g_bHostI2C;
extern BOOLEAN g_bRstFlag;

extern ST_BuffInfo *g_pstBufMainTask;
extern ENUM_mTask  g_nMainTask;
extern UINT8 g_ucDownloadMode;
extern UINT8 g_ucErasePageLen;
extern UINT16 g_usFlashOperationFlag;
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void task_send_int();
void CheckFlash(UINT32 start, UINT16 len, UINT8 *ecc);

#endif

