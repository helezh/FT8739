/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_RTC.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-18
*
*  Abstract:
*
* Reference:
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_RomEcc.h"

#if _TEST_ROMECC_EN   
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define PROM_START_ADDRESS      0xFE0000   //Prom start address
#define Proom_ADDR16(n)   (*((UINT16 far *)(PROM_START_ADDRESS + n)))
#define PROM_LENGTH             1024*3/2  //0x80
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
#if 1
typedef union
{
    UINT16 ucData;
    struct
    {
        UINT16 r0   : 1;
        UINT16 r1   : 1;
        UINT16 r2   : 1;
        UINT16 r3   : 1;
        UINT16 r4   : 1;
        UINT16 r5   : 1;
        UINT16 r6   : 1;
        UINT16 r7   : 1;
        UINT16 r8   : 1;
        UINT16 r9   : 1;
        UINT16 r10  : 1;
        UINT16 r11  : 1;
        UINT16 r12  : 1;
        UINT16 r13  : 1;
        UINT16 r14  : 1;
        UINT16 r15  : 1;
    } bits;
} UNION_result;
#endif
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UNION_result XRAM bist_result_out;
UNION_result XRAM bist_result_out_tmp;
UNION_result XRAM bist_ron_data;

UINT16 XRAM ucRomTestBuf[PROM_LENGTH];
UINT16 XRAM usRead_data;
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
void Test_RomEcc(void)
{
    UINT16 i;
    UINT8 t;
    UINT16 far *pRom;
    #if 1
    pRom = PROM_START_ADDRESS;
    for (i = 0; i < PROM_LENGTH; i++)
    {
        //*pRom = i;//0xffff;
       ucRomTestBuf[i] = *pRom++;
    }
    
    for (i = 0; i < PROM_LENGTH; i++)
    {
        //if(ucRomTestBuf[i] != 0xffff)
        {
            if (t%16 == 0)
            {
                t = 0;
                DBG_PROM("\n\r");
            }
            t++;
            DBG_PROM("%04X ",ucRomTestBuf[i]);
            DelayMs(10);
        }
    }
    #endif
    bist_result_out.ucData = 0;
    bist_result_out_tmp.ucData = 0x9570;

    bist_ron_data.ucData = ucRomTestBuf[0];

    for(i=0;i< PROM_LENGTH+1;i++)
    {
        bist_result_out.bits.r15 = bist_result_out_tmp.bits.r14^bist_ron_data.bits.r14;
        bist_result_out.bits.r14 = bist_result_out_tmp.bits.r13^bist_result_out_tmp.bits.r15^bist_ron_data.bits.r13;
        bist_result_out.bits.r13 = bist_result_out_tmp.bits.r12^bist_ron_data.bits.r12;
        bist_result_out.bits.r12 = bist_result_out_tmp.bits.r11^bist_ron_data.bits.r11;
        bist_result_out.bits.r11 = bist_result_out_tmp.bits.r10^bist_ron_data.bits.r10;
        bist_result_out.bits.r10 = bist_result_out_tmp.bits.r9^bist_ron_data.bits.r9;
        bist_result_out.bits.r9  = bist_result_out_tmp.bits.r8^bist_ron_data.bits.r8;
        bist_result_out.bits.r8  = bist_result_out_tmp.bits.r7^bist_ron_data.bits.r7;
        bist_result_out.bits.r7  = bist_result_out_tmp.bits.r6^bist_ron_data.bits.r6;
        bist_result_out.bits.r6  = bist_result_out_tmp.bits.r5^bist_ron_data.bits.r5;
        bist_result_out.bits.r5  = bist_result_out_tmp.bits.r4^bist_ron_data.bits.r4;
        bist_result_out.bits.r4  = bist_result_out_tmp.bits.r3^bist_ron_data.bits.r3;
        bist_result_out.bits.r3  = bist_result_out_tmp.bits.r2^bist_ron_data.bits.r2;
        bist_result_out.bits.r2  = bist_result_out_tmp.bits.r1^bist_ron_data.bits.r1;
        bist_result_out.bits.r1  = bist_result_out_tmp.bits.r0^bist_result_out_tmp.bits.r15^bist_ron_data.bits.r0;
        bist_result_out.bits.r0  = bist_result_out_tmp.bits.r15;
        bist_result_out_tmp.ucData = bist_result_out.ucData;
        bist_ron_data.ucData = ucRomTestBuf[i];
    }

    for(i=0;i< PROM_LENGTH;i++)
    {
        bist_ron_data.ucData = ucRomTestBuf[PROM_LENGTH - 1- i];

        bist_result_out.bits.r15 = bist_result_out_tmp.bits.r14^bist_ron_data.bits.r14;
        bist_result_out.bits.r14 = bist_result_out_tmp.bits.r13^bist_result_out_tmp.bits.r15^bist_ron_data.bits.r13;
        bist_result_out.bits.r13 = bist_result_out_tmp.bits.r12^bist_ron_data.bits.r12;
        bist_result_out.bits.r12 = (bist_result_out_tmp.bits.r11)^(bist_ron_data.bits.r11);
        bist_result_out.bits.r11 = bist_result_out_tmp.bits.r10^bist_ron_data.bits.r10;
        bist_result_out.bits.r10 = bist_result_out_tmp.bits.r9^bist_ron_data.bits.r9;
        bist_result_out.bits.r9  = bist_result_out_tmp.bits.r8^bist_ron_data.bits.r8;
        bist_result_out.bits.r8  = bist_result_out_tmp.bits.r7^bist_ron_data.bits.r7;
        bist_result_out.bits.r7  = bist_result_out_tmp.bits.r6^bist_ron_data.bits.r6;
        bist_result_out.bits.r6  = bist_result_out_tmp.bits.r5^bist_ron_data.bits.r5;
        bist_result_out.bits.r5  = bist_result_out_tmp.bits.r4^bist_ron_data.bits.r4;
        bist_result_out.bits.r4  = bist_result_out_tmp.bits.r3^bist_ron_data.bits.r3;
        bist_result_out.bits.r3  = bist_result_out_tmp.bits.r2^bist_ron_data.bits.r2;
        bist_result_out.bits.r2  = bist_result_out_tmp.bits.r1^bist_ron_data.bits.r1;
        bist_result_out.bits.r1  = bist_result_out_tmp.bits.r0^bist_result_out_tmp.bits.r15^bist_ron_data.bits.r0;
        bist_result_out.bits.r0  = bist_result_out_tmp.bits.r15;

        bist_result_out_tmp.ucData = bist_result_out.ucData;
    }  
    DBG_MODE("\n\rbist_result_out = %04X ",bist_result_out.ucData);
}
#endif
