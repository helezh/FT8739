/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Typedef.h
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
#ifndef __DATATYPE_H__
#define __DATATYPE_H__


/*******************************************************************************
* 1.Included files
*******************************************************************************/


/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
/*Data Types(Compiler Specific) in C251*/
typedef bit  BOOLEAN;
typedef unsigned char  UINT8;
typedef signed   char  SINT8;
typedef unsigned short UINT16;
typedef signed   short SINT16;
typedef unsigned long  UINT32;
typedef signed   long  SINT32;
typedef float          FP32;
typedef double         FP64;

/* This is the header file CONV51.H */
#ifdef __C251__     // __C251__ is a define of C251
#define DRAM data     // data can be mapped directly to the 251 data space
#define IRAM near     // idata uses MOV Ri, use 251 near instead
#define XRAM near     // xdata uses MOVX or MOV @DR56, use 251 near instead
#define PRAM near     // pdata uses MOVX Ri, use 251 near instead
#define CROM code     // code uses MOVC A, use 251 const instead
#else
#define DRAM data     // if you compile with C51 the memory spaces are
#define IRAM idata     // mapped to the previous definitions
#define XRAM xdata
#define PRAM pdata
#define CROM code
#endif

#define SFR         sfr
#define SBIT        sbit

#define VALID       1
#define INVALID     0

#define TRUE        1
#define FALSE       0

#define ENABLE      1
#define DISABLE     0

#define BITn(n)     ((UINT16)1<<(n))
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

#endif

