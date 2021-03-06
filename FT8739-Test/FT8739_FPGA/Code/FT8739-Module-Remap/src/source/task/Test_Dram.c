/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_Dram.c
*
* Author: xinkunpeng
*
* Created: 2014-04-22
*
* Abstract: 只是选取60Byte DRAM和4000Byte XRAM进行测试，如果全部测试请使用FT8836_dram文件进行测试
*
* Reference:
* Version:
* 0.1:
*
*******************************************************************************

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_Dram.h"

#if _TEST_DRAM_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define _TEST_DRAM            1
#define _TEST_XRAM_BYTE       0
#define _TEST_XRAM_WORD       0
#define _TEST_XRAM_DWORD      1

#define DRAM_START_ADDRESS    0x0000
#define DRAM_END_ADDRESS      0x8FFF
#define DRAM_LENGTH_BYTE      60
#define XRAM_LENGTH_BYTE      0x4000
#define XRAM_LENGTH_WORD      XRAM_LENGTH_BYTE>>1
#define XRAM_LENGTH_DWORD     XRAM_LENGTH_BYTE>>2

#if _TEST_DRAM
/* dram最大为128 Byte */
UINT8 DRAM g_ucReadDram[DRAM_LENGTH_BYTE];   // DRAM test
#endif

#if _TEST_XRAM_BYTE
/* xram大小为(0x5800 - 0x80) Byte */
UINT8 XRAM g_ucReadXram[XRAM_LENGTH_BYTE];   // XRAM test
#endif

#if _TEST_XRAM_WORD
UINT16 XRAM g_usReadXram[XRAM_LENGTH_WORD];  // XRAM test
#endif

#if _TEST_XRAM_DWORD
UINT32 XRAM g_ulReadXram[XRAM_LENGTH_DWORD]; // XRAM test
#endif

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT8  XRAM ucReadBack;
UINT16 XRAM usReadBack;
UINT32 XRAM ulReadBack;
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
void Test_Dram(void)
{
    UINT16 i;
#if _TEST_DRAM
    DBG_MODE("\n\rread DRAM start");
    for (i = 0; i < DRAM_LENGTH_BYTE; i++)
    {
        if (!(i&0x01))
        {
            g_ucReadDram[i] = TEST_PATTERN1;
        }
        else
        {
            g_ucReadDram[i] = TEST_PATTERN2;
        }
    }
    for (i = 0; i < DRAM_LENGTH_BYTE; i++)
    {
        ucReadBack = g_ucReadDram[i];

        if (!(i&0x01))
        {
            if (ucReadBack !=  TEST_PATTERN1)
            {
                DBG_ERROR("%02x ",ucReadBack);
                break;
            }
        }
        else
        {
            if (ucReadBack !=  TEST_PATTERN2)
            {
                DBG_ERROR("%02x ",ucReadBack);
                break;
            }
        }
    }
    DBG_MODE("\n\rread DRAM is end");
#endif

#if _TEST_XRAM_BYTE
    DBG_MODE("\n\rread XRAM by byte start: ");
    for (i = 0; i < XRAM_LENGTH_BYTE; i++)
    {
        if (!(i&0x01))
        {
            g_ucReadXram[i] = TEST_PATTERN1;
        }
        else
        {
            g_ucReadXram[i] = TEST_PATTERN2;
        }
    }
    for (i = 0; i < XRAM_LENGTH_BYTE; i++)
    {
        ucReadBack = g_ucReadXram[i];

        if (!(i&0x01))
        {
            if (ucReadBack !=  TEST_PATTERN1)
            {
                DBG_ERROR("%02x ",ucReadBack);
                DBG_ERROR("\n\r i= %02x ",i);
                break;
            }
        }
        else
        {
            if (ucReadBack !=  TEST_PATTERN2)
            {
                DBG_ERROR("%02x ",ucReadBack);
                DBG_ERROR("\n\r i= %02x ",i);
                break;
            }
        }
    }
    DBG_MODE("\n\rread XRAM by byte is end");
#endif

#if _TEST_XRAM_WORD
    DBG_MODE("\n\rread DRAM by word start");
    for (i = 0; i < XRAM_LENGTH_WORD; i++)
    {
        if (!(i&0x01))
        {
            g_usReadXram[i] = TEST_PATTERN3;
        }
        else
        {
            g_usReadXram[i] = TEST_PATTERN4;
        }
    }
    for (i = 0; i < XRAM_LENGTH_WORD; i++)
    {
        usReadBack = g_usReadXram[i];

        if (!(i&0x01))
        {
            if (usReadBack !=  TEST_PATTERN3)
            {
                DBG_ERROR("%04x ",usReadBack);
                break;
            }
        }
        else
        {
            if (usReadBack !=  TEST_PATTERN4)
            {
                DBG_ERROR("%04x ",usReadBack);
                break;
            }
        }
    }
    DBG_MODE("\n\rread DRAM by word is ok");
#endif

#if _TEST_XRAM_DWORD
    DBG_MODE("\n\rread DRAM by double word start");
    for (i = 0; i < XRAM_LENGTH_DWORD; i++)
    {
        if (!(i&0x01))
        {
            g_ulReadXram[i] = TEST_PATTERN5;
        }
        else
        {
            g_ulReadXram[i] = TEST_PATTERN6;
        }
    }
    for (i = 0; i < XRAM_LENGTH_DWORD; i++)
    {
        UINT16 temp_H,temp_L;
        
        ulReadBack = g_ulReadXram[i];

        if (!(i&0x01))
        {
            if (ulReadBack !=  TEST_PATTERN5)
            {
                temp_H = ulReadBack>>16;
                temp_L = ulReadBack&0x0000FFFF;
                DBG_ERROR("\n\r0x%04x%04x Error",temp_H,temp_L);
                break;
            }
        }
        else
        {
            if (ulReadBack !=  TEST_PATTERN6)
            {
                temp_H = ulReadBack>>16;
                temp_L = ulReadBack&0x0000FFFF;
                DBG_ERROR("\n\r0x%04x%04x Error",temp_H,temp_L);
                break;
            }
        }
    }
    DBG_MODE("\n\rread DRAM by double word is ok\n");
#endif
}

#endif
