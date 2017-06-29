/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_Prom.c
*
*    Author: xinkunpeng
*
*   Created: 2013-04-22
*
*  Abstract:
*
* Reference: test PROM introduction:
* Version:
* 0.1:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_Prom.h"

#if _TEST_PROM_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define PROM_START_ADDRESS      0xFD0000   //Prom start address
#define PROM_END_ADDRESS        0xFD0FFF   //Prom end address
#define PROM_LENGTH             1024*4     ///2  //0x80


#define TEST_PROM_WRITE         1
#define TEST_PROM_READ          0

//UINT16 far *pRom;
//UINT16 XRAM ucRomTestBuf[PROM_LENGTH];
UINT8 far *pRom;
UINT8 XRAM ucRomTestBuf[PROM_LENGTH];
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Prom(void)
{
    UINT16 i;
    UINT8 t;


    DBG_MODE("\nprom read test is start");
    pRom = PROM_PTR8(0);
    for (i = 0; i < PROM_LENGTH; i++)
    {
        ucRomTestBuf[i] = *pRom++;
    }
    for (i = 0; i < PROM_LENGTH; i++)
    {
        if (t%16 == 0)
        {
            t = 0;
            DBG_PROM("\n\r");
        }
        t++;
        DBG_PROM("%02X ",ucRomTestBuf[i]);
        DelayMs(20);
    }
    DBG_MODE("\n\rprom read test is end\n");



    DBG_MODE("\n\n\n\n\n\n\nprom write test is start");
    pRom = PROM_PTR8(0);
    for (i = 0; i < PROM_LENGTH; i++)
    {
        pRom[i] = ucRomTestBuf[PROM_LENGTH - i - 1];
    }
    for (i = 0; i < PROM_LENGTH; i++)
    {
        if (t%16 == 0)
        {
            t = 0;
            DBG_PROM("\n\r");
        }
        t++;
        DBG_PROM("%02X ",pRom[i]);
        DelayMs(20);
    }
    DBG_MODE("\n\rprom write test is end\n");

}
#endif

