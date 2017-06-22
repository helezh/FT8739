/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: main.c
*
*    Author: xinkunpeng
*
*   Created: 2013-11-11
*
*  Abstract:
*
* Reference:
*
* Version: 0.2: Transplant from FT5412 by linjianjun
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define DRAM data     // data can be mapped directly to the 251 data space
#define XRAM near     // xdata uses MOVX or MOV @DR56, use 251 near instead
#define PRAM near     // pdata uses MOVX Ri, use 251 near instead
#define CROM code     // code uses MOVC A, use 251 const instead

typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned long  UINT32;

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

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
#define XRAM_START_ADDRESS    0x0080
#define DRAM_START_ADDRESS    0x0000
#define DRAM_END_ADDRESS      0xA000//0xA000
#define DRAM_LENGTH_BYTE      (120 - 8)//定义数组没法定义到0x0000的，最前面只能定义到0x0008
#define XRAM_LENGTH_BYTE      (DRAM_END_ADDRESS-XRAM_START_ADDRESS)
#define XRAM_LENGTH_WORD      (XRAM_LENGTH_BYTE >> 1)
#define XRAM_LENGTH_DWORD     (XRAM_LENGTH_BYTE >> 2)

#define _TEST_DRAM              0
#define _TEST_XRAM_BYTE         0
#define _TEST_XRAM_WORD         0
#define _TEST_XRAM_DWORD        1

#define TEST_PATTERN1         0x55
#define TEST_PATTERN2         0xAA
#define TEST_PATTERN3         0x55AA
#define TEST_PATTERN4         0xAA55
#define TEST_PATTERN5         0x12345678//0x55AA55AA
#define TEST_PATTERN6         0xAA55AA55

#if _TEST_DRAM
UINT8 XRAM ReadBackUINT8;
UINT8 DRAM g_ReadDramUINT8[DRAM_LENGTH_BYTE];  // DRAM test
#endif

#if _TEST_XRAM_BYTE
UINT8 XRAM ReadBackUINT8;
UINT8 *g_ReadXramUINT8;  // XRAM test
#endif

#if _TEST_XRAM_WORD
UINT16 XRAM ReadBackUINT16;
UINT16 * g_ReadXramUINT16;  // XRAM test
#endif

#if _TEST_XRAM_DWORD
UINT32 XRAM ReadBackUINT32;
//UINT32 XRAM g_ReadDramUINT32[XRAM_LENGTH_DWORD];  // XRAM test
UINT32 * g_ReadXramUINT32;
#endif


/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
* Name: main
* Brief:
* Input:
* Output:
* Return:
* Note:不要使用函数嵌套，此时需要用到堆栈，堆栈分配在XRAM中，遍历XRAM的时候必定会
        对堆栈中的内容操作.使用函数嵌套，可能会在调用函数后出栈时找不到进入函数时
        的寄存器配置，导致系统跑飞。
*******************************************************************************/

void main(void)
{
    UINT16 XRAM i_tmp;

    CGUCON4 = 0x00;

    P0MOD   = 0x00;
    P0DIR   = 0xFF;
    P0SEL   = 0xFF;
    P0BUF   = 0x00;

    P1MOD   = 0x00;
    P1DIR   = 0xFF;
    P1SEL   = 0xFF;
    P1BUF   = 0xFF;
#if 0

    while(1)
    {
        //P0_2 = 1;
        #if 1
        
        for(i_tmp = 0;i_tmp < XRAM_LENGTH_BYTE; i_tmp++);
            
        P0_7 = ~P0_7;
        #else
        P0_5 = 1;
        P0_5 = 0;
        #endif
    }

#else    
    while(1)
   {

#if _TEST_DRAM
    for (i_tmp = 0; i_tmp < DRAM_LENGTH_BYTE; i_tmp++)
    {
        if (!(i_tmp&0x01))
        {
            g_ReadDramUINT8[i_tmp] = TEST_PATTERN1;
        }
        else
        {
            g_ReadDramUINT8[i_tmp] = TEST_PATTERN2;
        }
    }
    for (i_tmp = 0; i_tmp < DRAM_LENGTH_BYTE; i_tmp++)
    {
        ReadBackUINT8 = g_ReadDramUINT8[i_tmp];

        if (!(i_tmp&0x01))  //奇地址校验
        {
            if (ReadBackUINT8 ==  TEST_PATTERN1)
            {
                P0_0 = ~P0_0;
            }
            else 
            {
                P0_0 = 0;
                P0_1 = 1;
                P0_6 = 1;
                while(1);
            }
        }
        else  //偶地址校验
        {
            if (ReadBackUINT8 ==  TEST_PATTERN2)
            {
                P0_1 = ~P0_1;
            }
            else
            {
                P0_0 = 1;
                P0_1 = 0;
                P0_6 = 1;
                while(1);
            }
        }
    }
#endif

#if _TEST_XRAM_BYTE
    g_ReadXramUINT8 = XRAM_START_ADDRESS;
    for (i_tmp = 0; i_tmp < XRAM_LENGTH_BYTE; i_tmp++)
    {
        if (!(i_tmp&0x01))
        {
            g_ReadXramUINT8[i_tmp] = TEST_PATTERN1;
        }
        else
        {
            g_ReadXramUINT8[i_tmp] = TEST_PATTERN2;
        }
    }
    g_ReadXramUINT8 = XRAM_START_ADDRESS;
    for (i_tmp = 0; i_tmp < XRAM_LENGTH_BYTE; i_tmp++)
    {
        ReadBackUINT8 = g_ReadXramUINT8[i_tmp];
        if (!(i_tmp&0x01))
        {
            if (ReadBackUINT8 ==  TEST_PATTERN1)
            {
                P0_0 = ~ P0_0;
            }
            else 
            {
                P0_0 = 0;
                P0_1 = 1;
                P0_6 = 1;
                while(1);
            }
        }
        else
        {
            if (ReadBackUINT8 ==  TEST_PATTERN2)
            {
                P0_1 = ~P0_1;
            }
            else 
            {
                P0_0 = 1;
                P0_1 = 0;
                P0_6 = 1;                
                while(1);
            }
        }
    }

#endif
#if _TEST_XRAM_WORD
    g_ReadXramUINT16 = XRAM_START_ADDRESS;
    for (i_tmp = 0; i_tmp < XRAM_LENGTH_WORD; i_tmp++)
    {
        if (!(i_tmp&0x01))
        {
            g_ReadXramUINT16[i_tmp] = TEST_PATTERN3;
        }
        else
        {
            g_ReadXramUINT16[i_tmp] = TEST_PATTERN4;
        }
    }
    
    g_ReadXramUINT16 = XRAM_START_ADDRESS;    
    for (i_tmp = 0; i_tmp < XRAM_LENGTH_WORD; i_tmp++)
    {
        ReadBackUINT16 = g_ReadXramUINT16[i_tmp];

        if (!(i_tmp&0x01))
        {
            if (ReadBackUINT16 ==  TEST_PATTERN3)
            {
                P0_0 = ~P0_0;
            }
            else 
            {
                P0_0 = 0;
                P0_1 = 1;
                P0_6 = 1;                
                while(1);
            }
        }
        else
        {
            if (ReadBackUINT16 ==  TEST_PATTERN4)
            {
                P0_1 = ~P0_1;
            }
            else 
            {
                P0_0 = 1;
                P0_1 = 0;
                P0_6 = 1;                
                while(1);
            }
        }
    }
#endif
#if _TEST_XRAM_DWORD
    g_ReadXramUINT32 = XRAM_START_ADDRESS;
    for (i_tmp = 0; i_tmp < XRAM_LENGTH_DWORD; i_tmp++)
    {
        if (!(i_tmp&0x01))
        {
            g_ReadXramUINT32[i_tmp] = TEST_PATTERN5;
        }
        else
        {
            g_ReadXramUINT32[i_tmp] = TEST_PATTERN6;
        }
    }
    
    g_ReadXramUINT32 = XRAM_START_ADDRESS;    
    for (i_tmp = 0; i_tmp < XRAM_LENGTH_DWORD; i_tmp++)
    {
        ReadBackUINT32 = g_ReadXramUINT32[i_tmp];

        if (!(i_tmp&0x01))
        {
            if (ReadBackUINT32 ==  TEST_PATTERN5)
            {
                P0_0 = ~P0_0;
            }
            else 
            {
                P0_0 = 0;
                P0_1 = 1;
                P0_6 = 1;                
                while(1);
            }
        }
        else
        {
            if (ReadBackUINT32 ==  TEST_PATTERN6)
            {
                P0_1 = ~P0_1;
            }
            else 
            {
                P0_0 = 1;
                P0_1 = 0;
                P0_6 = 1;                
                while(1);
            }
        }
    }
#endif

    P0_7 = ~ P0_7;
    }
#endif

}

