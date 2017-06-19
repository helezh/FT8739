/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_RomEcc.c
*
*    Author: tangsujun
*
*   Created: 2017-05-05
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
#define PROM_START_ADDRESS      0xFD0000   //Prom start address
#define PROM_PTR16(n)   ((UINT16 far *)(PROM_START_ADDRESS + (n)))
#define PROM_LENGTH             ((1024*3)>>1)  //0x80
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

typedef union
{
    UINT16 ucData;
    
    struct
    {
        UINT16 r16   : 1;
        UINT16 r17   : 1;
        UINT16 r18   : 1;
        UINT16 r19   : 1;
        UINT16 r20   : 1;
        UINT16 r21   : 1;
        UINT16 r22   : 1;
        UINT16 r23   : 1;
        UINT16 r24   : 1;
        UINT16 r25   : 1;
        UINT16 r26  : 1;
        UINT16 r27  : 1;
        UINT16 r28  : 1;
        UINT16 r29  : 1;
        UINT16 r30  : 1;
        UINT16 r31  : 1;
    } bits;
} UNION_resultH;
#endif
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
static UNION_result XRAM result_out;
static UNION_result XRAM result_tmp;
static UNION_result XRAM rom_data;

static UNION_resultH XRAM resultH_out;
static UNION_resultH XRAM resultH_tmp;

static UINT16 XRAM ucRomTestBuf[PROM_LENGTH];
static UINT16 XRAM usRead_data;


static void Drv_RomCRC32(void);
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


/******************************************************************************
*   Name: Test_RomEcc
*  Brief: 
*  Input:
* Output:
* Return:
******************************************************************************/
void Test_RomEcc(void)
{
    UINT16 i;    
    UINT16 far *pRom;


    DBG_PROM("\n Test_RomEcc");
   
    pRom = PROM_PTR16(0);
    for (i = 0; i < PROM_LENGTH; i++)
    {
        //*pRom = i;//0xffff;
       ucRomTestBuf[i] = *pRom++;
    }
    #if 0
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
    resultH_out.ucData = 0;
    result_out.ucData  = 0;
    
    resultH_tmp.ucData = 0x9570;//CRC 初始值，高16bit
    result_tmp.ucData  = 0xA7F1;//CRC 初始值，低16bit
  
    
    rom_data.ucData = ucRomTestBuf[0];//membits电路设计原因
    Drv_RomCRC32();
    
    for(i=0;i< PROM_LENGTH;i++)//顺序计算
    {  
        rom_data.ucData = ucRomTestBuf[i];
        Drv_RomCRC32();  
    }
    
    for(i=PROM_LENGTH;i>0;i--)//逆序计算
    {
        rom_data.ucData = ucRomTestBuf[i-1];
        Drv_RomCRC32();        
    }  
    DBG_MODE("\n\rresult_out =0x%04X%04X ",resultH_out.ucData,result_out.ucData);
}


/******************************************************************************
*   Name: Drv_RomCRC32
*  Brief: 
*  Input:
* Output:
* Return:
******************************************************************************/
static void Drv_RomCRC32(void)
{
    resultH_out.bits.r31 = resultH_tmp.bits.r30^resultH_tmp.bits.r31;
    resultH_out.bits.r30 = resultH_tmp.bits.r29^resultH_tmp.bits.r31;

    resultH_out.bits.r29 = resultH_tmp.bits.r28;

    resultH_out.bits.r28 = resultH_tmp.bits.r27^resultH_tmp.bits.r31;
    resultH_out.bits.r27 = resultH_tmp.bits.r26^resultH_tmp.bits.r31;

    resultH_out.bits.r26 = resultH_tmp.bits.r25;

    resultH_out.bits.r25 = resultH_tmp.bits.r24^resultH_tmp.bits.r31;
    resultH_out.bits.r24 = resultH_tmp.bits.r23^resultH_tmp.bits.r31;

    resultH_out.bits.r23 = resultH_tmp.bits.r22;

    resultH_out.bits.r22 = resultH_tmp.bits.r21^resultH_tmp.bits.r31;
    resultH_out.bits.r21 = resultH_tmp.bits.r20^resultH_tmp.bits.r31;
    resultH_out.bits.r20 = resultH_tmp.bits.r19^resultH_tmp.bits.r31;

    resultH_out.bits.r19 = resultH_tmp.bits.r18;
    resultH_out.bits.r18 = resultH_tmp.bits.r17;
    resultH_out.bits.r17 = resultH_tmp.bits.r16;

    resultH_out.bits.r16 = result_tmp.bits.r15^resultH_tmp.bits.r31^rom_data.bits.r15;


    result_out.bits.r15 = result_tmp.bits.r14^rom_data.bits.r14;
    result_out.bits.r14 = result_tmp.bits.r13^rom_data.bits.r13;
    result_out.bits.r13 = result_tmp.bits.r12^rom_data.bits.r12;
    result_out.bits.r12 = result_tmp.bits.r11^rom_data.bits.r11;
    result_out.bits.r11 = result_tmp.bits.r10^rom_data.bits.r10;
    result_out.bits.r10 = result_tmp.bits.r9^rom_data.bits.r9^resultH_tmp.bits.r31;
    result_out.bits.r9  = result_tmp.bits.r8^rom_data.bits.r8^resultH_tmp.bits.r31;
    result_out.bits.r8  = result_tmp.bits.r7^rom_data.bits.r7;
    result_out.bits.r7  = result_tmp.bits.r6^rom_data.bits.r6;
    result_out.bits.r6  = result_tmp.bits.r5^rom_data.bits.r5^resultH_tmp.bits.r31;
    result_out.bits.r5  = result_tmp.bits.r4^rom_data.bits.r4;
    result_out.bits.r4  = result_tmp.bits.r3^rom_data.bits.r3;
    result_out.bits.r3  = result_tmp.bits.r2^rom_data.bits.r2;
    result_out.bits.r2  = result_tmp.bits.r1^rom_data.bits.r1;
    result_out.bits.r1  = result_tmp.bits.r0^rom_data.bits.r0;
    result_out.bits.r0  = resultH_tmp.bits.r31;

    resultH_tmp.ucData = resultH_out.ucData;
    result_tmp.ucData  = result_out.ucData;
}






#endif//_TEST_ROMECC_EN





