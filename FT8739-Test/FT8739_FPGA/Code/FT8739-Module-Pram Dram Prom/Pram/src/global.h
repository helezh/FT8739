/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R),All Rights Reserved.
*
* File Name: Test_Afe.h
*
*    Author: xinkunpeng
*
*   Created: 2014-05-15
*
*  Abstract:
*
* Reference:
*
*   Version:
*******************************************************************************/
#ifndef __GLOBAL_H__
#define __GLOBAL_H___

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include <intrins.h>

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
sfr CGUCON4 = 0xCC;
sfr P0BUF   = 0x80;
sfr P0DIR   = 0xAC;
sfr P0MOD   = 0xEB;
sfr P0SEL   = 0xEC;
sfr P1BUF   = 0x94;   /*P1Buf*/
sfr P1DIR   = 0xAD;   /*P1口方向配置，1:输出, 0:输入*/
sfr P1MOD   = 0xED;   /*0:P1 use as gpio;1:p1 use as function define*/
sfr P1SEL   = 0xEE;   /*0:P1 as OD port; 1:P1 as PUSH-PULL port*/


sbit P0_0 = P0BUF^0;
sbit P0_1 = P0BUF^1;
sbit P0_2 = P0BUF^2;
sbit P0_3 = P0BUF^3;
sbit P0_4 = P0BUF^4;
sbit P0_5 = P0BUF^5;
sbit P0_6 = P0BUF^6;
sbit P0_7 = P0BUF^7;

sbit P1_0 = P1BUF^0;
sbit P1_1 = P1BUF^1;
sbit P1_2 = P1BUF^2;
sbit P1_3 = P1BUF^3;
sbit P1_4 = P1BUF^4;
sbit P1_5 = P1BUF^5;
sbit P1_6 = P1BUF^6;
sbit P1_7 = P1BUF^7;


#define DRAM  data     // data can be mapped directly to the 251 data space
#define XRAM  near     // xdata uses MOVX or MOV @DR56, use 251 near instead
#define PRAM  near     // pdata uses MOVX Ri, use 251 near instead
#define CROM  code     // code uses MOVC A, use 251 const instead
#define ECODE ecode

/*APP info*/
#define APP_VERIF_ADDR         0xFEE900  // Verification Info
#define APP_VERIF_LEN          0x20
#define FW_CFG_TOTAL_SIZE      0x80

/* test pram setting */
#define PRAM1_START_ADDR       (UINT32)0xFEE800
#define PRAM2_START_ADDR       (UINT32)0xFF0000

#define PRAM1_CODE_LEN         0x300    //PRAM1中要搬运代码的长度
#define PRAM2_CODE_LEN         0x200    //PRAM2中要搬运代码的长度

#define PRAM1_COPY_ADDR        (UINT32)0xFF2000  //PRAM1中的代码放到PRAM2中的指定起始位置
#define PRAM2_COPY_ADDR        (UINT32)0xFEF000  //PRAM2中的代码放到PRAM1中的指定位置

#define PRAM1_TEST_LEN         (PRAM2_START_ADDR - PRAM1_START_ADDR)
#define PRAM2_TEST_LEN         (0xFFFFFF - PRAM2_START_ADDR)

#define PRAM_ADDR8(n)          (*((UINT8 far *)((UINT32)0xFEE800 + n)))
#define PRAM_ADDR16(n)         (*((UINT16 far *)((UINT32)0xFEE800 + n)))

#define TEST_PATTERN1          0x55
#define TEST_PATTERN2          0xAA
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned long  UINT32;

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void test_pram1(void);
void test_pram2(void);
#endif