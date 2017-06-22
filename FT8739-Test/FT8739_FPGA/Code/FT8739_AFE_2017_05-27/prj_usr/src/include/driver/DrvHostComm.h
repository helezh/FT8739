/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: DrvHostComm.h
*
*    Author: Wu Bo Zhong (Michael)
*
*   Created: 2013-01-01
*
*  Abstract: Please describe the interface in detail for this module
*
* Reference:
*
*******************************************************************************/

#ifndef _DRV_HOST_COMM_H_
#define _DRV_HOST_COMM_H_

/* Conditional Compiler Options */

/*******************************************************************************
* 1.Included files
*******************************************************************************/
//#include "FT8836.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
#define DATA_BUF                I2CBUF
#define RI_FLAG                 I2CRI
#define TI_FLAG                 I2CTI

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void DrvHostCommInit(void);

#endif // _DRV_HOST_COMM_H_

