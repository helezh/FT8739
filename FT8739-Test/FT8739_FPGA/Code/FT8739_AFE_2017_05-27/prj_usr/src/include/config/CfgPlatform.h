/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: CfgPlatform.h
*
*    Author: 
*
*   Created: 2014-05-27
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/

#ifndef _CFG_PLATFORM_H_
#define _CFG_PLATFORM_H_

/*******************************************************************************
* Conditional Compiler Options
*******************************************************************************/

/* Platform Configurations */
#define PLATFORM_251        1
#define PLATFORM_51         2
#define PLATFORM_M0         3
#define PLATFORM_PC         4

#ifdef __C251__ // A predefined of version number of the C251 compiler (401 = V4.01)
#define _COMPILE_PLATFORM   PLATFORM_251
#endif

#ifdef __C51__  // A predefined of version number of the C51 compiler (701 = V7.01)
#define _COMPILE_PLATFORM   PLATFORM_51
#endif

#ifdef __ARM_M0__ // this macro is pre-defined by compiler in keil ARM project file
#define _COMPILE_PLATFORM   PLATFORM_M0
#endif

#ifdef WIN32    // this macro is pre-defined by VC compiler
#define _COMPILE_PLATFORM   PLATFORM_PC
#endif

#if _COMPILE_PLATFORM == PLATFORM_PC
#define PLATFORM_PC_MFC

#if (defined PLATFORM_PC_MFC)
#include "stdafx.h"
#endif
#endif
/*******************************************************************************
* Included files
*******************************************************************************/

/*******************************************************************************
* Global constant and macro definitions using #define
*******************************************************************************/
// Common Macro
#ifndef NULL
#define NULL                ((void *)0)
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef SUCCESS
#define SUCCESS             0
#endif

#ifndef FAIL
#define FAIL                1
#endif

#ifndef ENABLE
#define ENABLE              1
#endif

#ifndef DISABLE
#define DISABLE             0
#endif

#ifndef VALID
#define VALID               1
#endif

#ifndef INVALID
#define INVALID             0
#endif

#ifndef ON  
#define ON                  1
#endif

#ifndef OFF
#define OFF                 0
#endif

#if _COMPILE_PLATFORM == PLATFORM_251
#define BIT                 bit
#define SFR                 sfr
#define SBIT                sbit

#ifndef BOOLEAN
#define BOOLEAN             bit
#endif

#define FRAM                far
#define DRAM                data  // data can be mapped directly to the 251 data space
#define IRAM                near  // idata uses MOV Ri, use 251 near instead
#define XRAM                near  // xdata uses MOVX or MOV @DR56, use 251 near instead
#define PRAM                near  // pdata uses MOVX Ri, use 251 near instead
#define CROM                code  // (const) code uses MOVC A, use 251 const instead
#define VOLATILE            volatile

/* basic data type */
typedef signed char         SINT8;
typedef signed short        SINT16;
typedef signed long         SINT32;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16,ADDR;
typedef unsigned long       UINT32;
typedef float               FP32;
typedef double              FP64;

#elif _COMPILE_PLATFORM == PLATFORM_51
#define BIT                 bit
#define SFR                 sfr
#define SBIT                sbit

#ifndef BOOLEAN
#define BOOLEAN             bit
#endif

#define DRAM                data  // if you compile with C51 the memory spaces are
#define IRAM                idata // mapped to the previous definitions
#define XRAM                xdata
#define PRAM                pdata
#define CROM                code

/*******************************************************************************
* Global structures, unions and enumerations using typedef
*******************************************************************************/
/* basic data type */
typedef signed char         SINT8;
typedef signed short        SINT16;
typedef signed long         SINT32;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;
typedef float               FP32;
typedef double              FP64;

#elif _COMPILE_PLATFORM == PLATFORM_M0
#define BIT                 bit
#define SFR                 sfr
#define SBIT                sbit

#define DRAM
#define IRAM
#define XRAM
#define PRAM
#define CROM

/* basic data type */
typedef signed char         SINT8;
typedef signed short        SINT16;
typedef signed long         SINT32;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;
typedef float               FP32;
typedef double              FP64;

#endif // _COMPILE_PLATFORM == ???

#define BITn(n)  ((UINT16)1<<(n))

/*******************************************************************************
* Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* Global function prototypes
*******************************************************************************/

#endif // _CFG_PLATFORM_H_

