/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
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

//UINT16 XRAM ucRomTestBuf[PROM_LENGTH];

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
    UINT8 t = 0;
    UINT8  ucLoopValue;
    UINT16 usLoopValue;
    UINT32 ulLoopValue;
    UINT8 far *pRom;
    UINT8 far *ucpRom;
    UINT16 far *uspRom;
    UINT32 far *ulpRom;    

    DBG_MODE("\nprom test is start");

    //I2C_DEBUG往PROM写数据，然后Pram程序打印Prom中的内容比较
    pRom = PROM_START_ADDRESS;
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
    DBG_MODE("\n\rprom test is end\n");

    //Pram程序往Prom中写数据，用I2C_DEBUG读出来比较
    pRom = PROM_START_ADDRESS;
    for (i = 0; i < PROM_LENGTH; i++)
    {
        *(pRom+i) = 0x5a;
    }

    #if 0
    //Pram程序往Prom中写数据，烤机测试
    while (1)
    {
        //one byte write and read
        for (ucLoopValue = 0; ucLoopValue < 0xff; ucLoopValue++)
        {
            ucpRom = PROM_START_ADDRESS;
            for (i = 0; i < PROM_LENGTH; i++)
            {
                *ucpRom++ = ucLoopValue;
            }
            ucpRom = PROM_START_ADDRESS;
            for (i = 0; i < PROM_LENGTH; i++)
            {
                if (*ucpRom++ == ucLoopValue)
                {
                    P0_2 = !P0_2;
                }
                else
                {
                    P0_2 = 0;
                    DBG_ERROR("uci=%04x",i);                    
                    while (1);
                }
            }
        }
        ucpRom = PROM_START_ADDRESS;
        for (i = 0; i < PROM_LENGTH; i++)
        {
            *ucpRom++ = 0xff;
        }
        ucpRom = PROM_START_ADDRESS;
        for (i = 0; i < PROM_LENGTH; i++)
        {
            if (*ucpRom++ == 0xff)
            {
                P0_2 = !P0_2;
            }
            else
            {
                P0_2 = 0;
                DBG_ERROR("uci=%04x",i);                    
                while (1);
            }
        }        

        //two bytes write and read
        for (usLoopValue = 0; usLoopValue < 0xffff; usLoopValue++)
        {
            uspRom = PROM_START_ADDRESS;
            for (i = 0; i < (PROM_LENGTH >> 1); i++)
            {
                *uspRom++ = usLoopValue;
            }
            uspRom = PROM_START_ADDRESS;
            for (i = 0; i < (PROM_LENGTH >> 1); i++)
            {
                if (*uspRom++ == usLoopValue)
                {
                    P0_3 = !P0_3;
                    if ((*uspRom == 0x1234) && (i == 5))
                    {
                        DBG_PROM("*uspRom = %04x",*uspRom);
                    }
                }
                else
                {
                    P0_3 = 0;
                    DBG_ERROR("usi=%04x",i);
                    while (1);
                }
            }
        }  
        uspRom = PROM_START_ADDRESS;
        for (i = 0; i < (PROM_LENGTH >> 1); i++)
        {
            *uspRom++ = 0xffff;
        }
        uspRom = PROM_START_ADDRESS;
        for (i = 0; i < (PROM_LENGTH >> 1); i++)
        {
            if (*uspRom++ == 0xffff)
            {
                P0_3 = !P0_3;
            }
            else
            {
                P0_3 = 0;
                DBG_ERROR("usi=%04x",i);
                while (1);
            }
        }

        //four bytes write and read
        for (ulLoopValue = 0; ulLoopValue < 0xffffffff; ulLoopValue++)
        {
            ulpRom = (UINT32 *)PROM_START_ADDRESS;
            for (i = 0; i < (PROM_LENGTH >> 2); i++)
            {
                *ulpRom++ = ulLoopValue;
            }
            ulpRom = (UINT32 *)PROM_START_ADDRESS;
            for (i = 0; i < (PROM_LENGTH >> 2); i++)
            {
                if (*ulpRom++ == ulLoopValue)
                {
                    P0_4 = !P0_4;
                    if ((*uspRom == 0x12345678) && (i == 5))
                    {
                        DBG_PROM("*ulpRom = %08x",*ulpRom);
                    }
                }
                else
                {
                    P0_4 = 0;
                    DBG_ERROR("uli=%04x",i);
                    while (1);
                }
            }           
        }  
        ulpRom = (UINT32 *)PROM_START_ADDRESS;
        for (i = 0; i < (PROM_LENGTH >> 2); i++)
        {
            *ulpRom++ = 0xffffffff;
        }
        for (i = 0; i < (PROM_LENGTH >> 2); i++)
        {
            if (*ulpRom++ == 0xffffffff)
            {
                P0_4 = !P0_4;
            }
            else
            {
                P0_4 = 0;
                DBG_ERROR("uli=%04x",i);
                while (1);
            }
        }         
    } 
    #endif
}
#endif

