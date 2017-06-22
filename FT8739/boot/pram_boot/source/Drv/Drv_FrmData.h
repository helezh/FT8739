/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Drv_FrmData.h
*
*    Author: linjianjun
*
*   Created: 2013-02-01
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/
#ifndef __DRV_FRMDATA_H__
#define __DRV_FRMDATA_H__

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/
#pragma pack(1)     /* 以下结构体对齐为1个字节 */


/* CFG 版本配置信息 */
typedef struct
{
    UINT8 aucDateCode[16];
    UINT8 aucProjectCode[16];
} ST_CFG_PARA;

#pragma pack()
/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

#endif

