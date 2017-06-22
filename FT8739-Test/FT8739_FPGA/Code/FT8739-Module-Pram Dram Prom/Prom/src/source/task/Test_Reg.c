/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_Reg.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-24
*
*  Abstract:
*
* Reference: Transplant from FT5412 by linjianjun
*
*   Version: 0.2
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <string.h>
#include "Test_Reg.h"
#include "Test_spi.h"
#include "Test_Xbus.h"

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#if _TEST_LCD_REG_EN

#define LCD_REG_MAX_SIZE      0x780
// flash
#define LCD_FLASH_ADDR_START        0x0000
#define LCD_INITCODE_LENGTH_ADDR    (LCD_FLASH_ADDR_START+0)
#define LCD_INITCODE_CRC_ADDR       (LCD_FLASH_ADDR_START+2)
#define LCD_INITCODE_DATA_ADDR      (LCD_FLASH_ADDR_START+4)
#define LCD_INITCODE_REG_ADDR       (LCD_FLASH_ADDR_START+8)

// 数据缓冲区
typedef union
{
    UINT16 Buf16[LCD_REG_MAX_SIZE/2];
    UINT8  Buf8[LCD_REG_MAX_SIZE];
} UNION_LcdRegBuf;

typedef union
{
    UINT16 Buf16;
    UINT8  Buf8[2];
} UNION_LcdLenInfo;

UNION_LcdRegBuf XRAM g_unLcdBuf;
UNION_LcdLenInfo g_unLcdLen;
UNION_LcdLenInfo g_LcdEcc;

UINT16 CROM g_usLcdReadBuf[LCD_REG_MAX_SIZE/2] =
{
0x06,0x98,0x99,0x89,0xff,0xe0,0x01,0x5a,0xa4,0x80,0x0f,0x44,0x00,0x00,0x00,0x00,
0x00,0x2e,0x00,0x2e,0x00,0x00,0x00,0xe6,0x01,0x59,0xa5,0x80,0x06,0x11,0x42,0x00,
0x00,0x00,0x00,0xa6,0x80,0x01,0x90,0xb4,0x80,0x05,0x00,0x00,0x40,0x00,0x00,0xb4,
0xd0,0x02,0x00,0x00,0xb6,0xa0,0x01,0x00,0xb6,0xb0,0x05,0x00,0x00,0x07,0x04,0x56,
0xc0,0x80,0x0a,0x00,0xa0,0x00,0x70,0x00,0x18,0x04,0x06,0x05,0x00,0xc0,0x90,0x05,
0x00,0xa0,0x00,0x08,0x08,0xc0,0xa0,0x0f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x10,0x00,0x17,0x00,0x02,0xc0,0xb0,0x03,0x00,0x00,0x00,0xc0,0xc0,0x08,
0x88,0x00,0x00,0x22,0x21,0x06,0x21,0x00,0xc1,0x80,0x07,0x77,0x77,0x00,0x30,0xc2,
0xb0,0x06,0xc1,0x90,0x03,0x22,0x00,0x00,0xc1,0xa0,0x0f,0x00,0x88,0x33,0x00,0x00,
0x00,0x00,0x00,0x20,0x20,0x00,0x8c,0x16,0x00,0x08,0xc1,0xc0,0x09,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xc2,0x80,0x09,0x00,0x00,0xee,0x00,0x00,0xee,0x00,
0x00,0xee,0xc2,0x90,0x09,0x00,0x00,0xee,0x00,0x00,0xee,0x00,0x00,0xee,0xc2,0xa0,
0x09,0x00,0x00,0xee,0x00,0x00,0xee,0x00,0x00,0xee,0xc2,0xb0,0x09,0x00,0x00,0xee,
0x00,0x00,0xee,0x00,0x00,0xee,0xc2,0xc0,0x09,0x00,0x00,0xee,0x00,0x00,0xee,0x00,
0x00,0xee,0xc2,0xd0,0x09,0x00,0x00,0xee,0x00,0x00,0x00,0x00,0x00,0x00,0xc2,0xe0,
0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc2,0xf0,0x0c,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc3,0x80,0x0f,0x00,
0xff,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0xc3,0x90,
0x0f,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0x00,0x00,
0xc3,0xa0,0x0b,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc3,0xb0,
0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x02,0x04,0x06,0xc3,0xc0,0x0d,0x00,
0x00,0x7f,0xff,0x00,0x00,0x00,0x00,0x7f,0xff,0x00,0x00,0x00,0xc4,0x80,0x04,0x50,
0x00,0x06,0x00,0xc4,0x90,0x06,0x00,0x00,0x01,0xc0,0x86,0x86,0xc5,0x80,0x07,0x8b,
0x9b,0x04,0x55,0x55,0x00,0xc0,0xc5,0x90,0x08,0x25,0x25,0x88,0x21,0x4d,0x4d,0x55,
0x55,0xc5,0xb0,0x03,0x20,0x20,0x00,0xc5,0xc0,0x07,0x66,0x01,0x1f,0x84,0x77,0x00,
0x4a,0xc5,0xd0,0x0b,0x20,0x0c,0x11,0x55,0xaa,0xf0,0xf0,0x55,0xaa,0x97,0x97,0xc5,
0xe0,0x01,0xe0,0xc9,0x90,0x07,0xad,0x8d,0x73,0x60,0x53,0x4a,0x43,0xca,0x80,0x0c,
0xd6,0xc4,0xb6,0xab,0xa3,0x9c,0x96,0x90,0x8b,0x88,0x85,0x82,0xca,0x90,0x08,0xff,
0x99,0xff,0x33,0xff,0x99,0xff,0xe0,0xca,0xa0,0x03,0x00,0x00,0x00,0xca,0xb0,0x06,
0x0f,0x0f,0x09,0x03,0xff,0x05,0xcb,0x80,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcb,0x90,0x0f,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcb,0xa0,0x0c,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xcc,0x80,0x0f,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xcc,0x90,0x0f,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xcc,0xa0,0x0e,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xcc,0xb0,
0x0f,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0xcc,0xc0,0x0f,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0xcc,0xd0,0x0e,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0xcc,0xe0,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xcc,0xf0,0x08,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0xcd,0x80,
0x0e,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0x00,0xcd,
0x90,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcd,
0xa0,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcd,
0xb0,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xcd,0xc0,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xcd,0xd0,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xcd,0xe0,0x03,0x00,0x00,0x00,0xce,0x80,0x08,0x08,0x10,
0x00,0x00,0x09,0x00,0x00,0x00,0xce,0x90,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xce,0xa0,0x0d,0x00,0x80,0x00,0x80,0x00,0x00,0x00,0x00,
0x00,0x78,0x00,0x00,0x00,0xce,0xb0,0x07,0x00,0x00,0xa0,0x04,0x06,0x05,0x00,0xce,
0xc0,0x07,0x40,0x00,0xa0,0x04,0x06,0x05,0x00,0xce,0xd0,0x07,0x00,0x00,0xa0,0x04,
0x06,0x05,0x00,0xce,0xe0,0x0f,0x00,0x54,0x0a,0x6b,0x0a,0x6b,0x0a,0x6b,0x0a,0x6b,
0x0a,0x6b,0x00,0x54,0x82,0xce,0xf0,0x0c,0x00,0x02,0x01,0x00,0x18,0x01,0x00,0x00,
0x00,0x0d,0x00,0x80,0xcf,0x80,0x0e,0x00,0x03,0x02,0x01,0x04,0x00,0x00,0x01,0x5b,
0x00,0x00,0x00,0x00,0x07,0xcf,0x90,0x04,0x00,0x00,0x0a,0x0a,0xcf,0xb0,0x0e,0x00,
0x01,0x04,0x00,0xad,0x00,0xad,0x01,0x04,0x00,0xad,0x00,0xad,0x50,0xcf,0xd0,0x03,
0x00,0x00,0x00,0xd7,0x80,0x01,0x1f,0xd7,0x90,0x03,0x03,0x00,0x00,0xd7,0xa0,0x01,
0x06,0xf3,0xc0,0x04,0x00,0x00,0x00,0x00,0xf3,0xd0,0x04,0x00,0x00,0x00,0x00,0xf5,
0x80,0x0b,0x08,0x0f,0x17,0x08,0x1f,0x0f,0x36,0x36,0x00,0x00,0x00,0xf5,0xa0,0x0e,
0x1f,0x0f,0x26,0x66,0x79,0x81,0xae,0x01,0x00,0x04,0x00,0x6e,0x66,0xa9,0xf5,0xb0,
0x05,0xff,0x01,0xff,0xf0,0xfe,0xf5,0xd0,0x07,0x65,0x54,0x55,0x54,0x00,0x54,0x54,
0xf6,0xa0,0x0a,0x0b,0x01,0x23,0x45,0x67,0x89,0xde,0x00,0x00,0xa5,0xff,0x90,0x01,
0x00,0xce,0x80,0x08,0x8a,0x00,0x00,0x00,0x09,0x00,0x00,0x00,0xce,0x90,0x0c,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xce,0xa0,0x0f,0x00,0x80,
0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xce,0xb0,0x07,
0x00,0x00,0x87,0x04,0x06,0x05,0x00,0xce,0xc0,0x07,0x00,0x00,0xa0,0x04,0x06,0x05,
0x00,0xce,0xd0,0x07,0x00,0x00,0xa0,0x04,0x06,0x05,0x00,0xce,0xe0,0x0f,0x00,0x54,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x05,0x00,0x54,0x80,0xce,0xf0,0x0c,
0x00,0x02,0x01,0x00,0x18,0x01,0x00,0x00,0x00,0x0d,0x00,0x80,0xcf,0x90,0x0c,0x05,
0x05,0x03,0x01,0x00,0x00,0x0a,0x0b,0x04,0x04,0x10,0x11,0xcf,0xa0,0x08,0x07,0x07,
0x8a,0x8b,0x07,0x00,0x80,0x00,0xc0,0x91,0x01,0x87,0xc0,0x93,0x01,0x11,0xce,0xc0,
0x03,0x40,0x00,0x87,0xc2,0x80,0x09,0x83,0x84,0x03,0x82,0x83,0x03,0x81,0x82,0x03,
0xc2,0x90,0x09,0x80,0x81,0x03,0x01,0x00,0x03,0x02,0x00,0x03,0xc2,0xa0,0x09,0x03,
0x00,0x03,0x04,0x01,0x03,0x00,0x00,0xee,0xc2,0xb0,0x09,0x00,0x00,0xee,0x00,0x00,
0xee,0x00,0x00,0xee,0xc2,0xc0,0x09,0x00,0x00,0xee,0x00,0x00,0xee,0x00,0x00,0xee,
0xc2,0xd0,0x09,0x00,0x00,0xee,0x70,0x00,0x00,0x00,0x00,0x00,0xc2,0xe0,0x0c,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc2,0xf0,0x0c,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcd,0xb0,0x0f,0x0e,0x06,0x02,
0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcd,0xc0,0x0f,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcd,0xd0,
0x0f,0x00,0x00,0xe0,0x60,0x20,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,
0xcd,0xe0,0x03,0x00,0x00,0x00,0xc3,0x80,0x0f,0x85,0x00,0x00,0x84,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x33,0x00,0x00,0xc3,0x90,0x0f,0x81,0x00,0x00,0x00,0x00,
0x00,0x81,0x00,0x00,0x00,0x00,0x00,0x33,0x33,0x00,0xc3,0xa0,0x0b,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc3,0xb0,0x0b,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x02,0x04,0x06,0xc3,0xc0,0x0d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xcb,0x80,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcb,0x90,0x0f,0x00,0x05,0x05,0x05,0x05,
0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0xcb,0xa0,0x0b,0x05,0x05,0xff,
0xff,0xff,0xff,0x00,0x81,0x00,0x00,0x00,0xcc,0x80,0x0f,0x05,0x06,0x19,0x1a,0x09,
0x0d,0x0a,0x0e,0x0b,0x0f,0x0c,0x10,0x1b,0x1c,0x27,0xcc,0x90,0x0f,0x28,0x01,0x01,
0x2d,0x2e,0x01,0x02,0x03,0x04,0x01,0x01,0x01,0x01,0x01,0x01,0xcc,0xa0,0x0e,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xcc,0xb0,0x0f,
0x1a,0x19,0x06,0x05,0x10,0x0c,0x0f,0x0b,0x0e,0x0a,0x0d,0x09,0x1c,0x1b,0x01,0xcc,
0xc0,0x0f,0x01,0x28,0x27,0x2e,0x2d,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0xcc,0xd0,0x0e,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0xcc,0xf0,0x08,0x00,0x33,0x33,0x85,0x84,0x00,0x00,0x03,0xcc,0xe0,0x0d,
0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x22,0x22,0x22,0x22,0x22,0x22,0xcd,0x80,0x0e,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcd,0x90,
0x0d,0x04,0x38,0x00,0x87,0x03,0xb1,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0xcd,0xa0,
0x0d,0x81,0x83,0x00,0x00,0x00,0x82,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0xc0,0x80,
0x06,0x00,0xbe,0x01,0x30,0x00,0x10,0xcf,0x90,0x04,0x05,0x05,0x03,0x01,0xce,0xf0,
0x02,0x00,0x04,0xce,0xf4,0x01,0xa6,0xd7,0xa0,0x01,0x07,0xb3,0xa1,0x04,0x02,0xd0,
0x05,0x00,0xb3,0xa6,0x01,0x10,0xb3,0xa1,0x04,0x00,0x00,0x02,0xcf,0xb3,0xa1,0x04,
0x00,0x00,0x04,0xff,0x1c,0x00,0x01,0x02,0xff,0xe0,0x01,0x00,                    
};
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

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
* Name: Test_WriteRamReg()
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_WriteRamReg(UINT16 addr,UINT16 mask0,UINT16 mask1)
{
    UINT16 tmp;
    UINT16 cnt_back;
    UINT16 cnt;
    UINT16 Addr_Base;
    UINT16 Addr_Offset;
    UINT16 BackUp;
    BOOLEAN flag;

    flag = TRUE;
    Addr_Base   = (addr&0xff00);
    Addr_Offset = (addr&0x00ff);
    BackUp = REG16(Addr_Base + (Addr_Offset<<1));

    #if 0
    for (cnt = 0; cnt < 0xffff; cnt++)
    {
        cnt_back = cnt;
        cnt &= mask0;
        cnt |= mask1;
        REG16(Addr_Base + (Addr_Offset<<1)) = cnt;
        tmp = REG16(Addr_Base + (Addr_Offset<<1));
        if (tmp != cnt)
        {
            REG16(Addr_Base + (Addr_Offset<<1)) = BackUp;
            DBG_ERROR("\n\rREG_%02X,write:%02X,read:%02X",addr,cnt,tmp);
            flag = 0;
            //break;
        }
        cnt = cnt_back;
    }
    #else

    DBG_FLOW("\n\nreg addr is:0x%04x",Addr_Base + (Addr_Offset<<1));
    
    for(cnt = 0; cnt < 16; cnt++)
    {
        cnt_back = (1<<cnt);
        cnt_back &= mask0;
        cnt_back |= mask1;
        REG16(Addr_Base + (Addr_Offset<<1)) = cnt_back;        
        tmp = REG16(Addr_Base + (Addr_Offset<<1));
        if (tmp != cnt_back)
        {
            REG16(Addr_Base + (Addr_Offset<<1)) = BackUp;

            #if _TEST_ASM_REG_EN
            DBG_ERROR("\n\rREG_%02d,write:%02X,read:%02X",Addr_Offset,cnt_back,tmp);
            #else
            DBG_ERROR("\n\rREG_%02X,write:%02X,read:%02X",Addr_Offset,cnt_back,tmp);
            #endif
            flag = 0;
            //break;
        }        
    }    
    #endif
    if (flag)
    {
        if (_TEST_ASM_REG_EN)
        {
            DBG_XSI_REG("\n\rREG_%02d write ok!",Addr_Offset);
        }
        else
        {
            DBG_CAL_REG("\n\rREG_%02X write ok!",Addr_Offset);
        }
    }
    REG16(Addr_Base + (Addr_Offset<<1)) = BackUp;
}

/*******************************************************************************
* Name: Test_AfeRegWrite
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_AfeRegWrite(ST_XSIRegisters *pXSIRegs,UINT16 addr,UINT16 mask0,UINT16 mask1)
{
    UINT16 tmp;
    UINT16 cnt_back;
    UINT16 cnt;
    UINT16 BackUp;
    BOOLEAN flag;

    flag = TRUE;
    BackUp = Drv_XsiReadReg(pXSIRegs,addr,AFE_REG);

    #if 0
    for (cnt = 0; cnt < 0xffff; cnt++)
    {
        cnt_back = cnt;
        cnt &= mask0;
        cnt |= mask1;

        Drv_XsiWriteReg(pXSIRegs,addr,cnt,AFE_REG);
        tmp = Drv_XsiReadReg(pXSIRegs,addr,AFE_REG);
        if (tmp != cnt)
        {
            Drv_XsiWriteReg(pXSIRegs,addr,BackUp,AFE_REG);
            DBG_ERROR("\n\rREG_%02x,write:%04x,read:%04x",addr,cnt,tmp);
            DelayMs(10);
            flag = 0;
            break;
            //HOLD;
        }
        cnt = cnt_back;
    }
    #else
    for (cnt = 0; cnt < 0x10; cnt++)
    {
        cnt_back = (1 << cnt);
        cnt_back &= mask0;
        cnt_back |= mask1;

        Drv_XsiWriteReg(pXSIRegs,addr,cnt_back,AFE_REG);
        tmp = Drv_XsiReadReg(pXSIRegs,addr,AFE_REG);
        if (tmp != cnt_back)
        {
            Drv_XsiWriteReg(pXSIRegs,addr,BackUp,AFE_REG);
            DBG_ERROR("\n\rREG_%02x,write:%04x,read:%04x",addr,cnt_back,tmp);
            DelayMs(10);
            flag = 0;
        }
    }    
    #endif
    if (flag)
    {
        if (_TEST_AFE_REG_EN)
        {
            DBG_AFE_REG("\n\rREG_%02x write ok!",addr);
        }
        else
        {
            DBG_AFE_RAM("\n\rREG_%02x write ok!",addr);
        }
    }
    Drv_XsiWriteReg(pXSIRegs,addr,BackUp,AFE_REG);
}

/******************************************************************************/
/* XSI寄存器遍历 */
#if _TEST_SPI0_REG_EN
/*******************************************************************************
* Name: Test_XsiReg
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_Spi0Reg(void)
{
    UINT8 i;
    UINT16 XRAM buf[10];

    SPI0CKEN = 1;
    SPI0_32K_EN = 1;

    DBG_MODE("\n\rSPI0 Reg Test is start:");
    buf[0]  = SPI0_DMA_CTRL;
    buf[1]  = SPI0_DMA_ERR_TIMEOUT_CTRL;
    buf[2]  = SPI0_DMA_ADDR_H;
    buf[3]  = SPI0_DMA_START_ADDR_L;
    buf[4]  = SPI0_DMA_END_ADDR_L;
    buf[5]  = SPI0_DMA_CRC;

    DBG_SPI0_REG("\n\rSPI0 Reg init value:");
    for (i = 0; i < 6; i++)
    {
        DBG_SPI0_REG("\n\rbuf[%02d]=%04X",i,buf[i]);
    }
    DBG_SPI0_REG("\n\rSPI0 Reg write test");
    Test_WriteRamReg(0xB200,0x007f,0x0000);
    Test_WriteRamReg(0xB201,0xffff,0x0000);
    Test_WriteRamReg(0xB202,0x0101,0x0000);
    Test_WriteRamReg(0xB203,0xffff,0x0000);
    Test_WriteRamReg(0xB204,0xffff,0x0000);
    Test_WriteRamReg(0xB205,0xffff,0x0000);     
    DBG_MODE("\n\rSPI0 reg write OK\n\r");
    SPI0CKEN = 0;
    SPI0_32K_EN = 0;
}
#endif



/******************************************************************************/
/* XSI寄存器遍历 */
#if _TEST_XSI_REG_EN
/*******************************************************************************
* Name: Test_XsiReg
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_XsiReg(void)
{
    UINT8 i;
    UINT16 XRAM buf[10];

    XSICKEN = 1;

    DBG_MODE("\n\rXSI Reg Test is start:");
    buf[0]  = XSI0_WDATA_LOC;
    buf[1]  = XSI0_RDATA_LOC;
    buf[2]  = XSI0_CLK_SEL;
    buf[3]  = XSI0_STOP;
    buf[4]  = XSI0_TX_INT;
    buf[5]  = XSI1_WDATA_LOC;
    buf[6]  = XSI1_RDATA_LOC;
    buf[7]  = XSI1_CLK_SEL;
    buf[8]  = XSI1_STOP;
    buf[9]  = XSI1_TX_INT;

    DBG_XSI_REG("\n\rXSI Reg init value:");
    for (i = 0; i < 10; i++)
    {
        DBG_XSI_REG("\n\rbuf[%02d]=%04X",i,buf[i]);
    }
    DBG_XSI_REG("\n\rXSI Reg write test");
    Test_WriteRamReg(0xB400,0xffff,0x0000);
    Test_WriteRamReg(0xB402,0x0003,0x0000);
    Test_WriteRamReg(0xB800,0xffff,0x0000);
    Test_WriteRamReg(0xB802,0x0003,0x0000);
    DBG_MODE("\n\rXSI reg write OK\n\r");
    XSICKEN = 0;    
}
#endif

/******************************************************************************/
/* XBUS寄存器遍历 */
#if _TEST_XBUS_REG_EN
/*******************************************************************************
* Name: Test_XbusReg
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_XbusReg(void)
{
    UINT8 i;
    UINT16 XRAM buf[5];

    XBUSCKEN = 1;

    DBG_MODE("\n\rXBUS Reg Test is start:");
    buf[0]  = XBUS_RDATA_LO_BYTE;
    buf[1]  = XBUS_RDATA_HO_BYTE;
    buf[2]  = XBUS_REGFILE_CTRL;
    buf[3]  = XBUS_CMD;
    buf[4]  = XBUS_RLD_DATA;

    DBG_XBUS_REG("\n\rXBUS Reg init value:");
    for (i = 0; i < 5; i++)
    {
        DBG_XBUS_REG("\n\rbuf[%02d]=%04X",i,buf[i]);
    }
    DBG_XBUS_REG("\n\rXBUS Reg write test");
    Test_WriteRamReg(0xBC00,0x00ff,0x0000);
    Test_WriteRamReg(0xBC01,0x00ff,0x0000);
    Test_WriteRamReg(0xBC03,0x0003,0x0000);
    Test_WriteRamReg(0xBC04,0xffff,0x0000);
    DBG_MODE("\n\rXBUS reg write OK\n\r");
    XBUSCKEN = 0;    
}
#endif

#if _TEST_ASM_REG_EN
/*******************************************************************************
* Name: Test_AsmReg
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_AsmReg(void)
{
    UINT16 i;
    UINT16 XRAM buf;
    AFEACKEN = 1;
    AFESCKEN = 1;
    DBG_MODE("\n\rAsm Reg Test is start:");
    DBG_ASM_REG("\n\rAsm Reg init value:");    
    for(i = 0; i < 41; i++)
    {
        buf = REG16(ASM_REG_BASE_ADDR +(i << 1));
        DBG_ASM_REG("\n\rAsmReg[%2d] = %04x addr= %04x",i,buf,ASM_REG_BASE_ADDR+(i << 1));
    }
    DBG_ASM_REG("\n\rAsm Reg write test");
    Test_WriteRamReg(0xB104,0xFFFF,0x0000);//int_en0 
    Test_WriteRamReg(0xB105,0x7FFE,0x0000);//int_en1
    Test_WriteRamReg(0xB106,0xFFFF,0x0000);//wk_en0
    Test_WriteRamReg(0xB107,0x7FF8,0x0000);//wk_en1
    Test_WriteRamReg(0xB10E,0xDFFF,0x0000);//scan_cfg0
    Test_WriteRamReg(0xB10F,0xC33A,0x0000);//scan_cfg1    
    Test_WriteRamReg(0xB110,0xFFFF,0x0000);//tp_frame_cfg0
    Test_WriteRamReg(0xB111,0xFFFF,0x0000);//tp_frame_cfg1
    Test_WriteRamReg(0xB112,0x3F3F,0x0000);//tp_frame_cfg2
    Test_WriteRamReg(0xB113,0x3F3F,0x0000);//tp_frame_cfg3
    Test_WriteRamReg(0xB114,0x3FFF,0x0000);//scan_delay
    Test_WriteRamReg(0xB115,0xFFFF,0xFFFF);//stb_mask_l
    Test_WriteRamReg(0xB116,0xFFFF,0xFFFF);//stb_mask_h
    
    for(i = 0xB117; i < 0xB11D; i++)
    {
        Test_WriteRamReg(i,0x03FF,0x0000);   
    }

    Test_WriteRamReg(0xB120,0xFFFF,0x0000);//hw_mon_ctr0
    Test_WriteRamReg(0xB121,0xDFFF,0x0000);//hw_mon_ctr1    
    Test_WriteRamReg(0xB122,0xFFFF,0x0000);//hw_mon_cfg0
    Test_WriteRamReg(0xB123,0xFFFF,0x0000);//hw_mon_cfg1
    Test_WriteRamReg(0xB124,0xFFFF,0x0000);//hw_mon_cfg2
    Test_WriteRamReg(0xB125,0xFFFF,0x0000);//hw_mon_cfg3
    Test_WriteRamReg(0xB126,0xF0FF,0x0000);//hw_mon_cfg4
    Test_WriteRamReg(0xB127,0x0FFF,0x0000);//hw_mon_tiemr
    Test_WriteRamReg(0xB128,0x1FFF,0x0000);//vrefsh_cfg_lcdon

    DBG_MODE("\n\rAsm reg write OK\n\r");
    AFESCKEN = 0;
    AFEACKEN = 0;
}
#endif

/******************************************************************************/
/* CAL寄存器读写测试 */
#if _TEST_CAL_REG_EN
/*******************************************************************************
*   Name: Test_CalReg
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CalReg(void)
{
    UINT8 i;
    UINT16 Addr;

    CALCKEN = 1;

    DBG_MODE("\n\rCal reg test is start");
    DBG_CAL_REG("\n\rCal reg init value.");
    for (i = 0; i <= 0x26; i++)
    {
        DBG_CAL_REG("\n\rreg%02X=%04X",i,REG16(CAL_REG_BASE_ADDR + (i<<1)));
    }
    DBG_CAL_REG("\n\r\n\rCal reg write test");

    // 0x0B -- 0x17 为只读，不需要测试
    Test_WriteRamReg(0xB000,0xA7F0,0x0000);
    Test_WriteRamReg(0xB001,0x001f,0x0000);
    for (Addr = 0xB002; Addr < 0xB00B; Addr++)
    {
        Test_WriteRamReg(Addr,0xffff,0x0000);
    }
    Test_WriteRamReg(0xB018,0xffff,0x0000);
    Test_WriteRamReg(0xB019,0xffff,0x0000);
    //Test_WriteRamReg(0xB01a,0x000f,0x0000);
    
    // 0x1B为只读，不需要测试
    Test_WriteRamReg(0xB01c,0x6118,0x0000);//bit2-bit0为WO，读该位MCU会挂掉
    // 0x1D为只读，不需要测试

    for(Addr = 0xB01e; Addr < 0xB026; Addr++)
    {
        Test_WriteRamReg(Addr,0xffff,0x0000);
    }
    
    CALCKEN = 0;
    DBG_MODE("\n\rCal reg write ok\n\r");
}
#endif

/******************************************************************************/
/* AFE寄存器读写测试 */
#if _TEST_AFE_REG_EN
#define AFE_REG_LEN  0x58
/*******************************************************************************
*   Name: Test_AfeReg
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_AfeReg(void)
{
    UINT8 i;
    UINT16 XRAM Buf[AFE_REG_LEN];

    DBG_MODE("\n\rafe Reg Test is start");
    Drv_XsiInit();

    /* AFE_REG Read and Write Test */
    DBG_AFE_REG("\n\rAfe Reg read and write:XSI0");
    Drv_XsiRead(pXSI0Regs,0,Buf,AFE_REG_LEN,AFE_REG);
    for (i = 0; i < AFE_REG_LEN; i++)
    {
        DBG_AFE_REG("\n\rreg[%02X] = 0x%04x",i,Buf[i]);
    }
    for(i = 0; i < 0x1A; i++)
    {
        Test_AfeRegWrite(pXSI0Regs,i,0xFFFF,0x0000);
    }
    Test_AfeRegWrite(pXSI0Regs,0x1A,0x03FF,0x0000);
    Test_AfeRegWrite(pXSI0Regs,0x1B,0x03FF,0x0000);
    Test_AfeRegWrite(pXSI0Regs,0x1C,0x01FF,0x0000);
    Test_AfeRegWrite(pXSI0Regs,0x1D,0x01FF,0x0000); 
    Test_AfeRegWrite(pXSI0Regs,0x1E,0x03FF,0x0000);      
    for(i = 0x1F; i < 0x3F; i++)
    {
        Test_AfeRegWrite(pXSI0Regs,i,0xFFFF,0x0000);
    }

    
    Test_AfeRegWrite(pXSI0Regs,0x40,0xFFFF,0x0000);
    Test_AfeRegWrite(pXSI0Regs,0x41,0x0008,0x0000);
    //Test_AfeRegWrite(3,0xFFFF,0x0000);
    Test_AfeRegWrite(pXSI0Regs,0x42,0xFFFF,0x0000);
    for(i = 0x43; i < 0x46;i++)
    {
        Test_AfeRegWrite(pXSI0Regs,i,0xFFFF,0x0000);
    }            
    //Test_AfeRegWrite(pXSI0Regs,0x46,0xC000,0x0000);
    for(i = 0x47; i < 0x58; i++)
    {
       Test_AfeRegWrite(pXSI0Regs,i,0xFFFF,0x0000); 
    }
    

    DBG_AFE_REG("\n\n\n\n\rAfe Reg read and write:XSI1");
    Drv_XsiRead(pXSI1Regs,0,Buf,AFE_REG_LEN,AFE_REG);
    for (i = 0; i < AFE_REG_LEN; i++)
    {
        DBG_AFE_REG("\n\rreg[%02X] = 0x%04x",i,Buf[i]);
    }
    for(i = 0; i < 0x1A; i++)
    {
        Test_AfeRegWrite(pXSI1Regs,i,0xFFFF,0x0000);
    }
    Test_AfeRegWrite(pXSI1Regs,0x1A,0x03FF,0x0000);
    Test_AfeRegWrite(pXSI1Regs,0x1B,0x03FF,0x0000);
    Test_AfeRegWrite(pXSI1Regs,0x1C,0x01FF,0x0000);
    Test_AfeRegWrite(pXSI1Regs,0x1D,0x01FF,0x0000); 
    Test_AfeRegWrite(pXSI1Regs,0x1E,0x03FF,0x0000);      
    for(i = 0x1F; i < 0x3F; i++)
    {
        Test_AfeRegWrite(pXSI0Regs,i,0xFFFF,0x0000);
    }
    Test_AfeRegWrite(pXSI1Regs,0x40,0xFFFF,0x0000);
    Test_AfeRegWrite(pXSI1Regs,0x41,0x0008,0x0000);
    //Test_AfeRegWrite(3,0xFFFF,0x0000);
    Test_AfeRegWrite(pXSI1Regs,0x42,0xFFFF,0x0000);
    for(i = 0x43; i < 0x46;i++)
    {
        Test_AfeRegWrite(pXSI1Regs,i,0xFFFF,0x0000);
    }            
    //Test_AfeRegWrite(pXSI1Regs,0x46,0xC000,0x0000);

    for(i = 0x47; i < 0x58; i++)
    {
       Test_AfeRegWrite(pXSI1Regs,i,0xFFFF,0x0000); 
    }    
    
    DBG_MODE("\n\rAFE_Reg read and write is OK!\n\r");
}
#endif

/******************************************************************************/
/* AFE Ram读写测试 */
#if _TEST_AFE_RAM_EN

#define TAB_RAM_LEN          176
#define TAB_RAM_START_ADDR   256
#define ACC_RAM_LEN          324
#define ACC_RAM_START_ADDR   256
#define RPT_RAM_LEN          652
#define RPT_RAM_START_ADDR   256
#if TEST_TAB_RAM_EN
/*******************************************************************************
* Name: Test_Afe_TabRam
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_Afe_TabRam()
{
    UINT8 i;
    UINT8 ucLen;
    UINT16 usAddr;
    UINT16 XRAM Buf[TAB_RAM_LEN];

    usAddr = TAB_RAM_START_ADDR;
    ucLen  = TAB_RAM_LEN;

    XSICKEN = 1;
    AFECKEN = 1;
    DBG_MODE("\n\rAfe Tab Ram Test is start -XSI0");
    
    /* set ram buf as tab ram: */
    Drv_XsiWriteReg(pXSI0Regs,0x05, 0x0000,AFE_REG);//tabram 16bit
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rRam_Tab1[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\rRead Ram_Tab1 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rRam_Tab2[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\rRead Ram_Tab2 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rRam_Tab3[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\rRead Ram_Tab3 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rRam_Tab4[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\rRead Ram_Tab4 is ok!");
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab is start!");
    usAddr = TAB_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        Test_AfeRegWrite(pXSI0Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab1 is OK!");
    
    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN;
    for (i = 0; i < ucLen; i++)
    {
        Test_AfeRegWrite(pXSI0Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab2 is OK!");

    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN*2;
    for (i = 0; i < ucLen; i++)
    {       
        Test_AfeRegWrite(pXSI0Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab3 is OK!");
    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN*2;
    for (i = 0; i < ucLen; i++)
    {       
        Test_AfeRegWrite(pXSI0Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab4 is OK!");
    DBG_MODE("\n\rAfe Tab Ram Test is start -XSI1");
    Drv_XsiWriteReg(pXSI1Regs,0x05, 0x0020,AFE_REG);//tabram 16bit
    memset(Buf,0xff,TAB_RAM_LEN*2); 
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rRam_Tab1[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\rRead Ram_Tab1 is ok!");
    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI1Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rRam_Tab2[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\rRead Ram_Tab2 is ok!");
    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI1Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rRam_Tab3[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\rRead Ram_Tab3 is ok!");
    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI1Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rRam_Tab4[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\rRead Ram_Tab4 is ok!");
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab is start!");
    usAddr = TAB_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {        
        Test_AfeRegWrite(pXSI1Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab1 is OK!");
    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN;
    for (i = 0; i < ucLen; i++)
    {       
        Test_AfeRegWrite(pXSI1Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab2 is OK!");
    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN*2;
    for (i = 0; i < ucLen; i++)
    {       
        Test_AfeRegWrite(pXSI1Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab3 is OK!");
    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN*2;
    for (i = 0; i < ucLen; i++)
    {       
        Test_AfeRegWrite(pXSI1Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n\r\n\rWrite Ram_Tab4 is OK!");
    DBG_MODE("\n\rAfe Tab Ram is end");
    XSICKEN = 0;
    AFECKEN = 0;
}
#else
#define Test_Afe_TabRam    /##/
#endif

/*******************************************************************************
* Name: Test_Afe_AccRam
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_Afe_AccRam()
{
    UINT8 i;
    UINT8 ucLen;
    UINT16 usAddr;
    UINT16 XRAM Buf[ACC_RAM_LEN];

    XSICKEN = 1;
    AFECKEN = 1;

    DBG_MODE("\n\rAfe Acc Ram Test");
    
    usAddr = ACC_RAM_START_ADDR;
    ucLen  = ACC_RAM_LEN;
    
#if TEST_ACC_RAM4_EN
    /* set ram buf as acc_h ram: testram_dataseg=2*/
    Drv_XsiWriteReg(pXSI0Regs,5, 0x0068,AFE_REG);

    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rAcc_Buf_h[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\r\n\rRead AccRam4 is OK!");

    DBG_AFE_RAM("\n\r\n\rWrite AccRam4 is start!");
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(pXSI0Regs,usAddr,0x007F,0x0000);
    }
    DBG_AFE_RAM("\n\r\n\rWrite AccRam4 is OK!");
#endif

#if TEST_ACC_RAM3_EN
    /* set ram buf as acc_m ram: testram_dataseg = 1 */
    Drv_XsiWriteReg(pXSI0Regs,5, 0x0048,AFE_REG);

    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rAcc_Buf_m[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\r\n\rRead AccRam3 is OK!");

    DBG_AFE_RAM("\n\r\n\rWrite AccRam3 is start!");
    usAddr = ACC_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(pXSI0Regs,usAddr,0xFFFF,0x0000);
    }
    DBG_AFE_RAM("\n\r\n\rWrite AccRam_M is OK!");
#endif

#if TEST_ACC_RAM2_EN
    /* set ram buf as acc_l ram: testram_dataseg = 0 */
    Drv_XsiWriteReg(pXSI0Regs,5, 0x0028,AFE_REG);

    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rAcc_Buf_l[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\r\n\rRead AccRam2 is OK!");

    DBG_AFE_RAM("\n\r\n\rWrite AccRam2 is start!");
    usAddr = ACC_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(pXSI0Regs,usAddr,0xFFFF,0x0000);
    }
    DBG_AFE_RAM("\n\r\n\rWrite AccRam2 is OK!");
#endif
#if TEST_ACC_RAM1_EN
    Drv_XsiWriteReg(pXSI0Regs,5, 0x0008,AFE_REG);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rAcc_Buf_l[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\r\n\rRead AccRam1 is OK!");
    DBG_AFE_RAM("\n\r\n\rWrite AccRam1 is start!");
    usAddr = ACC_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(pXSI0Regs,usAddr,0xFFFF,0x0000);
    }
    DBG_AFE_RAM("\n\r\n\rWrite AccRam1 is OK!");
    DBG_MODE("\n\rAfe acc ram test is end");
#endif
}

#if TEST_RPT_RAM_EN
/*******************************************************************************
* Name: Test_Afe_BaseRam
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_Afe_RptRam()
{
    UINT16 i;
    UINT16 ucLen;
    UINT16 usAddr;
    UINT16 XRAM Buf[RPT_RAM_LEN];
    
    XSICKEN = 1;
    AFECKEN = 1;
    //AFESCKEN = 1;
    DBG_MODE("\n\rAfe Rpt Ram Test is start");

    /* set ram buf as base ram: testram_sel = 0;*/
    Drv_XsiWriteReg(pXSI0Regs,5, 0x0010,AFE_REG);

    ucLen  = RPT_RAM_LEN;
    usAddr = RPT_RAM_START_ADDR;
    DBG_AFE_RAM("\n XSI0");
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rBase_Buf[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    
    DBG_AFE_RAM("\n\r\n\rRead RptRam is OK!");
    DBG_AFE_RAM("\n\r\n\rWrite RptRam is start!");
    ucLen = RPT_RAM_LEN;
    usAddr = RPT_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        Test_AfeRegWrite(pXSI0Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_AFE_RAM("\n XSI1");
    Drv_XsiRead(pXSI1Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_ERROR("\n\rBase_Buf[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_AFE_RAM("\n\r\n\rRead RptRam is OK!");

    DBG_AFE_RAM("\n\r\n\rWrite RptRam is start!");
    ucLen = RPT_RAM_LEN;
    usAddr = RPT_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        Test_AfeRegWrite(pXSI1Regs,usAddr,0xFFFF,0x0000);
        usAddr++;
    }

    XSICKEN = 0;
    AFECKEN = 0;
}
#else
#define Test_Afe_RptRam   /##/
#endif



/*******************************************************************************
*   Name: Test_Afe_Ram
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Afe_Ram()
{
    Test_Afe_TabRam();
    Test_Afe_AccRam();
    Test_Afe_RptRam();

}
#endif

/******************************************************************************/
/* LCD寄存器读写测试 */
#if _TEST_LCD_REG_EN
/******************************************************************************
*
*   Name: DrvXbus_ReadLcd16
*  Brief: 读lcd数据 16位(双字节对齐)
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT16 DrvXbus_ReadLcd16(UINT16 usaddr)
{
    volatile UINT8 Dummy;
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(1))) == 0);   //wait wr enable
    Dummy = Xbus_ADDR8(usaddr);     
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(0))) == 0);   //wait rdata redy
    return (UINT16)((pLcdWrapRegs->rdata_lo_byte << 8) + (pLcdWrapRegs->rdata_ho_byte & 0x00ff)); //Big-endian
}

/******************************************************************************
*
*   Name: DrvXbus_ReadLcd8
*  Brief: 读lcd数据 8位
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT8 DrvXbus_ReadLcd8(UINT16 usaddr)
{
    volatile UINT8 Dummy;
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(1))) == 0);   //wait wr enable
    Dummy = Xbus_ADDR8(usaddr);     
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(0))) == 0);   //wait rdata redy
    if(usaddr % 2 == 0)
    {
        return (UINT8)(pLcdWrapRegs->rdata_lo_byte);
    }
    else
    {
        return (UINT8)(pLcdWrapRegs->rdata_ho_byte);
    }
}

/******************************************************************************
*
*   Name: DrvXbus_WriteLcd8
*  Brief:写lcd数据 8位
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvXbus_WriteLcd8(UINT16 usaddr,UINT8 usdata)
{
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(1))) == 0); //wait wr enable
    Xbus_ADDR8(usaddr) = usdata;
}


/*******************************************************************************
*   Name: DrvReadFlashToLcdReg
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvReadFlashToLcdReg()
{
    UINT16 i;
    UINT16 len;
    UINT16 usPos;
    UINT16 uc_addr;
    UINT8 usLcdRegNum;

    DBG_LCD_REG("\r\nstart..."); 
    SPIFlash_FastRead(LCD_INITCODE_LENGTH_ADDR,g_unLcdLen.Buf8,2);
    SPIFlash_FastRead(LCD_INITCODE_CRC_ADDR,g_LcdEcc.Buf8,2);
    if(g_unLcdLen.Buf16 > 0x780 || g_unLcdLen.Buf16 == 0x0000)//byte
    {
        return;
    }

    DrvAbort_DmaLCD(); 
    //flash init code 前面4byte为dma解锁，这里不需要
    len = g_unLcdLen.Buf16-4;
    SPIFlash_FastRead(LCD_INITCODE_REG_ADDR, g_unLcdBuf.Buf8, len);
    DBG_LCD_REG("\r\n len = %04x ",len);
    if (len > 4) //一组数据最小为4
    {
        usPos = 0;
        while (usPos < len)
        {
            uc_addr = (g_unLcdBuf.Buf8[usPos++] << 8) + (g_unLcdBuf.Buf8[usPos++]);
            //DBG_BOOT("\r\n usPosaddr= %04x ",uc_addr); 
            usLcdRegNum = g_unLcdBuf.Buf8[usPos++];
            // 简单的长度识别
            if ((usLcdRegNum == 0) || (usLcdRegNum > 255))
            {
                DBG_LCD_REG("\r\n usPos1 = %04x ",usPos);
                return;
            }
            for (i = 0; i < usLcdRegNum; i++)
            {

            #if 1
                DBG_LCD_REG("\r\n addr = %04x ",uc_addr+i);
                //DelayMs(10);
                DBG_LCD_REG("\r\n data %02x ",g_unLcdBuf.Buf8[usPos]); 
                //DelayMs(10);
             
                DrvXbus_WriteLcd8(uc_addr+i,g_unLcdBuf.Buf8[usPos++]);

                DBG_LCD_REG("\r\n rddata = %02x ",DrvXbus_ReadLcd8(uc_addr+i));
                //DelayMs(10);
                if(g_unLcdBuf.Buf8[usPos-1] != DrvXbus_ReadLcd8(uc_addr+i))
                {

                    DBG_LCD_REG("\r\n err rddata = %02x ",DrvXbus_ReadLcd8(uc_addr+i));
                }
                DBG_LCD_REG("\r\n rddata = %02x ",DrvXbus_ReadLcd8(uc_addr+i));
             #endif
            }
            //DBG_BOOT("\r\nusPosend= %04x ",usPos); 
        }
        DBG_LCD_REG("\r\n usPos2 = %04x ",usPos);
    } 

}


/******************************************************************************
*
*   Name: DrvAbort_DmaLCD
*  Brief:
* 1.打断DMA，使LCD_RELOAD_INT变低，才能读写xbus
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvAbort_DmaLCD(void)
{
    RLDMACKEN = 1;
    pRlDmaRegs->DesAddr1 = 0x00; 
    pRlDmaRegs->DesAddr1 &= ~BITn(15);    //flash to lcd
    pRlDmaRegs->DesAddr0 = (UINT16)(0x0000);  //双字节对齐 
    pRlDmaRegs->FlashCmd = 0x0303;
    pRlDmaRegs->CtrlReg = ((pRlDmaRegs->CtrlReg) | (BITn(2)));  //abord
    while(LCD_RELOAD_INT == 1);
    RLDMACKEN = 0;
}


/*******************************************************************************
*   Name: Test_LcdReg
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_LcdReg(void)
{
    UINT16 i;
    
    DBG_MODE("\n\rlcd reg read and write is start");
    DBG_LCD_REG("\n\rTotalNum:0x%04x\n\r",g_unLcdLen.Buf16);
    for (i = 0; i < 3; i++)
    {
        if (LCD_RELOAD_FLASH)
        {
            DBG_MODE("\n\rlcd write start");
            DrvReadFlashToLcdReg();
            DBG_MODE("\n\rlcd write end");
        }
        else
        {
            break;
        }
    }
    DBG_MODE("\n\rlcd reg read and write is end\n\r");
}
#endif

