/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Drv_mcu.h
*
*    Author: tangsujun
*
*   Created: 2016-12-23
*
*  Abstract:
*
* Reference:
*
* Version:
*
*******************************************************************************/

#ifndef __DRV_MCU_H__
#define __DRV_MCU_H__


/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define SYSTEM_FLASH       1    // 带flash系统
#define SYSTEM_PRAM        0    // 只有pram系统


#define SYS_CLK_48M        0    // sysclk as 48M
#define SYS_CLK_24M        1    // sysclk as 24M

/* main clk */
#define MAIN_CLK              SYS_CLK_48M

#define I2C_SLAVE_ADDR        0x70  // 

//状态
#define S_MCU_INIT            0x00  //初始状态
#define S_PRAM_OK             0x06  //pram有效
#define S_NEED_LOAD           0x01  //pram无效
#define S_MCU_WAIT            0x02  //等待主机命令
#define S_FLASH_NOF           0x03  //flash空
#define S_FLASH_ERR           0x04  //flash数据错
#define S_FLASH_OK            0x07  //flash APP 导入OK



#define DATABUFF  I2CBUF
#define RIFLAG    I2CRI
#define TIFLAG    I2CTI

#define OTP_REG_I2C_ADDR      0xF381
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/


/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
//extern ST_XSIRegisters * XRAM pXSI2Regs;
extern BOOLEAN g_bHostUpCmd;                             //Host发升级命令

extern UINT16 g_usLcdLoadTime;
extern UINT16 g_TimeOver;

extern UINT8 g_ucAppEcc;
extern UINT8 g_ucSysState; //系统状态
extern UINT8 g_ucXbusClk;
extern UINT8 g_ucSysClk;
extern UINT8 g_ucSpi_mode;

extern UINT8 XRAM g_ucFwCfgBuf[32];  // info信息
extern UINT8 g_ucSelLcdReloadMode;
extern UINT8 g_ucReloadState;

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void DrvIOInit(void);
void DrvHostInterfaceInit(void);
UINT8 DrvReadPram8(UINT32 addr);
UINT16 DrvReadPram16(UINT32 addr);
BOOLEAN DrvPramIfValid(UINT16 addr);
void DrvClearState(void);
void DelayUs_EX(UINT16 ucDlyCnt);
void DrvFwConfigInit(void);



#endif //_DRV_HOST_COMM_H_

