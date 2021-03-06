
/*******************************************************************************
* Copyright (C) 2017-2019, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: test_XBUS.c
*
*    Author: tangsujun
*
*   Created: 2017-03-22
*
*  Abstract:
*
* Reference:
*
*   Version:CRC 0X020304 0305
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "CfgGlobal.h"
#include "FT8835_Reg.h"
#include "Drv_XBUS.h"
#include "Test_Xbus.h"
#if _TEST_XBUS_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define WRITERREAD  1
#define READONLY    0
/* lcd wrap base addr */
#define LCD_WRAP_START_ADDR     0xBC00
//对lcd reg操作，小心操作
#define LCD_REG_BASE_ADDR      0x020000
#define Xbus_ADDR8(n)    (*((UINT8 far *)(LCD_REG_BASE_ADDR + n)))
#define Xbus_ADDR16(n)   (*((UINT16 far *)(LCD_REG_BASE_ADDR + n)))

#define LCD_REG_GET_CRC_ADDR        0x0304
#define LCD_REG_SET_RELOAD_ADDR     0xfb30  // 0xfb30(0.5US)  0xfb10(2.6MS)
#define LCD_REG_SET_RELOAD_VALUE    0x00

#define LCD_OTP_REG_ADDR            0xf300
#define LCD_XBUS_REG_ADDR           0xCA80

#define RELOAD_END_H        pLcdWrapRegs->xbus_cmd |=  BITn(1)
#define RELOAD_END_L        pLcdWrapRegs->xbus_cmd &=~ BITn(1)

#define RELOAD_ABORT_H      pLcdWrapRegs->xbus_cmd |=  BITn(0)
#define RELOAD_ABORT_L      pLcdWrapRegs->xbus_cmd &=~ BITn(0)
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
//ST_LcdWrapRegisters *XRAM pLcdWrapRegs = (volatile ST_LcdWrapRegisters *)XBUS_REG_BASE_ADDR;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

UINT8 XRAM ucLcdCrcbuf[0X1000];
UINT8 XRAM ucLcdintialcode[0X1000]={0x00,0x0e,0x00,0x00,0XFF,0XE0,0X01,0X5A,\
    0XA4,0X80,0X03,0Xe7,0X22,0x55,0XFF,0XE0,0X01,0X00,0x11,0XFF};

UINT16 ucLcdCrclen=0;
UINT16 intialcodelen=0;
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
// ---------------- POPULAR POLYNOMIALS ----------------
//  CCITT:      x^16 + x^12 + x^5 + x^0                 (0x1021)
//  CRC-16:     x^16 + x^15 + x^2 + x^0                 (0x8005)
//  CCITT Kermit:     x^16 + x^12 + x^5 + x^0           (0x8408)
#define         CRC_16_POLYNOMIALS      0x8408
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


#define     GRAB_BIT(x,y)       ((x&(0x0001<<y))>>y)

/****************************************************************************/



/******************************************************************************
*
*   Name: GetLcdCrc16
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
unsigned short _xorbit(unsigned char ucStart,unsigned char ucEnd,unsigned short usData,unsigned short usCrcCode)
{
    int j;
    //printf("Input = 0x%04x\n",usData);
    for(j =ucStart ;j < ucEnd; j++)
    {
        //printf("BitAdd = %2d Data =0x%04x Bit = %d ",j,usCrcCode,(GRAB_BIT(usData,j)));
        usCrcCode ^=(GRAB_BIT(usData,j)); 
        //printf("Ans = 0x%04x\n",usCrcCode);
        //getch();
    }
    return usCrcCode;
}
/******************************************************************************
*
*   Name: GetLcdCrc16
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
unsigned short _writebit(unsigned short usCrcCode,unsigned char ucData,unsigned char ucbitaddr)
{
    usCrcCode &= (~(0x0001 << ucbitaddr));
    usCrcCode |= ucData<<ucbitaddr;
    //printf("Bit = %2d CrcCode = 0x%04x\n",ucbitaddr,usCrcCode);

    return usCrcCode;
}

unsigned short _Lcd_crc16_cal(unsigned char *ptr,int length)
{
    unsigned short cFcs = 0;
    unsigned short usCrcTmp = 0x0001;
    unsigned short usDataTmp = 0;
    unsigned short usExeCode = 0xFFFF;
    unsigned short usXorBit = 0;
    unsigned short usCheckSum = 0;
    int i, j;


    usDataTmp = 0;
    for ( i = 0; i < length; i++ )
    {
        //printf("%02x\n ",ptr[i]);
        usDataTmp = 0;
//      usCheckSum += ptr[i];

        usXorBit = (GRAB_BIT(usExeCode,8));
        usXorBit = _xorbit(9,16,usExeCode,usXorBit);
        usXorBit = _xorbit(0,8,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,0);

        //printf("%04x\n ",usDataTmp);

        usXorBit = (GRAB_BIT(usExeCode,9));
        usXorBit = _xorbit(10,16,usExeCode,usXorBit);
        usXorBit = _xorbit(1,8,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,1);

        usXorBit = (GRAB_BIT(usExeCode,8))^(GRAB_BIT(usExeCode,9));
        usXorBit = _xorbit(0,2,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,2);

        usXorBit = (GRAB_BIT(usExeCode,9))^(GRAB_BIT(usExeCode,10));
        usXorBit = _xorbit(1,3,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,3);

        usXorBit = (GRAB_BIT(usExeCode,10))^(GRAB_BIT(usExeCode,11));
        usXorBit = _xorbit(2,4,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,4);

        usXorBit = (GRAB_BIT(usExeCode,11))^(GRAB_BIT(usExeCode,12));
        usXorBit = _xorbit(3,5,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,5);

        usXorBit = (GRAB_BIT(usExeCode,12))^(GRAB_BIT(usExeCode,13));
        usXorBit = _xorbit(4,6,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,6);

        usXorBit = (GRAB_BIT(usExeCode,13))^(GRAB_BIT(usExeCode,14));
        usXorBit = _xorbit(5,7,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,7);

        usXorBit = (GRAB_BIT(usExeCode,0));
        usXorBit = _xorbit(14,16,usExeCode,usXorBit);
        usXorBit = _xorbit(6,8,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,8);

        usXorBit = (GRAB_BIT(usExeCode,1))^(GRAB_BIT(usExeCode,15))^(GRAB_BIT(ptr[i],7));

        usDataTmp = _writebit(usDataTmp,usXorBit,9);

        usDataTmp &= (~(0x0001 << 10));
        usDataTmp |= (GRAB_BIT(usExeCode,2))<<10;

        usDataTmp &= (~(0x0001 << 11));
        usDataTmp |= (GRAB_BIT(usExeCode,3))<<11;

        usDataTmp &= (~(0x0001 << 12));
        usDataTmp |= (GRAB_BIT(usExeCode,4))<<12;

        usDataTmp &= (~(0x0001 << 13));
        usDataTmp |= (GRAB_BIT(usExeCode,5))<<13;

        usDataTmp &= (~(0x0001 << 14));
        usDataTmp |= (GRAB_BIT(usExeCode,6))<<14;

        usXorBit = (GRAB_BIT(usExeCode,7));
        usXorBit = _xorbit(8,16,usExeCode,usXorBit);
        usXorBit = _xorbit(0,8,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,15);

        usExeCode = usDataTmp;
        //printf("0x%04x\n ",usExeCode);
        //getch();
    }

    //printf("0x%04x ",usExeCode);
    //printf("usCheckSum = 0x%04x\n",usCheckSum);
//    g_usLcdCheckSum = usCheckSum;
    return usExeCode;
}

/******************************************************************************
*
*   Name: _get_Lcd_crc16
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
unsigned short _get_Lcd_crc16()
{
    unsigned char ucTemp;
    unsigned short usAddr;
    unsigned char ucAddrH;
    unsigned char ucAddrL;
    unsigned char ucParaOffSet;
    unsigned short usIdx = 0;
    unsigned short usParaNum = 0;

    unsigned long ulCodeLen,i;
    unsigned long g_ulBufLen;
    unsigned long ulBufOffset = 0;
    unsigned char * pucLcdCrcbuf; // for calculate lcd crc
    
    unsigned short usLcd_crc;
    
    unsigned char auc_infoBuf[8];
    //UINT8 ucLcdbuf[12]={/*0XFF,0XE0,0X01,0X5A,*/0XA4,0X80,0X02,0Xe7,0X22,};
    
      
    pucLcdCrcbuf = ucLcdCrcbuf;

    

    //SPIFlash_FastRead(0,auc_infoBuf,8);
    //ulCodeLen = (auc_infoBuf[0] << 8) + auc_infoBuf[1]-4;
    intialcodelen   =(ucLcdintialcode[0] << 8) + ucLcdintialcode[1];
    ulCodeLen       =intialcodelen-4;
    //SPIFlash_FastRead(8,ucLcdbuf,ulCodeLen);

    i=0;
    usIdx = 0;
    while ( i<ulCodeLen)
    {
        ucTemp =ucLcdintialcode[8+i++];

        if (usIdx == 0)
        {
            ucAddrH = ucTemp;
            pucLcdCrcbuf[ulBufOffset++] = ucTemp;
            usIdx = 1;
        }
        else if (usIdx == 1)
        {
            ucAddrL = ucTemp;
            usIdx = 2;
        }
        else if (usIdx == 2)
        {
            usParaNum = ucTemp;
            ucParaOffSet = 0;
            usIdx = 3;
        }
        else if (usIdx == 3)
        {

            pucLcdCrcbuf[ulBufOffset++] = ucTemp + ucAddrL + ucParaOffSet;//参数+偏移地址，只取低八位
            if (ucParaOffSet < usParaNum - 1)
            {
                ucParaOffSet++;
            }
            else
            {
                usIdx = 0;
                ucAddrH = 0;
                ucAddrL = 0;
            }
        }
    }

    if ((usIdx == 1)||(usIdx == 2))    //异常终止去掉地址位
    {
        ulBufOffset --;
    }
    /*DBG_FLOW("\nulBufOffset=%04x",ulBufOffset);
    if(ulBufOffset%2==1)
    {
        pucLcdCrcbuf[ulBufOffset++]=0x00;

    }*/
    
    ucLcdCrclen=ulBufOffset;
    DBG_FLOW("\nucLcdCrclen=%04x",ucLcdCrclen);
    usLcd_crc = _Lcd_crc16_cal(pucLcdCrcbuf,ulBufOffset);
    return usLcd_crc;
}


/******************************************************************************
*
*   Name: DrvWriteLcdInitCode
*  Brief: 导入数据到LCD中
*  Input:
* Output:
* Return:
******************************************************************************/
static UINT8 DrvWriteLcdInitCode(void)
{
    UINT8 k=0,buf[16]={0XFF,0XE0,0X01,0X5A,0XA4,0X80,0X02,0Xe7,0X22,0X00,0X44,0X55};
    UINT16 i,len=7,temp=0,lcd_ecc,*ptr16=0;
    UINT8 Lbuf[8]={0XA4,0X67,0xA3,0xff};
    ptr16 =(UINT16)&ucLcdintialcode[4];

#if 1
    lcd_ecc =_get_Lcd_crc16();
    DBG_FLOW("\nlcdcrc[0]=%04x",lcd_ecc);

    for(i=0;i<ucLcdCrclen ;i++)
    {
        DBG_FLOW("\nLcdCrcbuf[%02x]=%02x",i,ucLcdCrcbuf[i]);
        
    }



#endif
    DBG_FLOW("\na LCD_RELOAD =%02x ",LCD_RELOAD_FLASH);
    if(!LCD_RELOAD_FLASH)
    {
        DrvXbus_WriteLcd8(LCD_REG_SET_RELOAD_ADDR,LCD_REG_SET_RELOAD_VALUE);    
        while(LCD_RELOAD_FLASH == 0);  //wait LCD_RELOAD_INT rise 2.45MS
        DBG_FLOW("\n LCD_RELOAD =%02x ",LCD_RELOAD_FLASH);
    }
    DBG_FLOW("\nb LCD_RELOAD =%02x ",LCD_RELOAD_FLASH);
    for(k=0;k<3;k++)
    {
            for(i=0;i<((intialcodelen+1)>>1);i++)
            {
                pLcdWrapRegs->xbus_rld_data=*ptr16;//g_ucLcdBuf[i];
                DBG_FLOW("\nrld=%04x",*ptr16);
                wait_printf_done();
                ptr16++;
            }
            INTOUT=0;
            RELOAD_END_H;//                
            while(LCD_RELOAD_FLASH);
            RELOAD_END_L;
            INTOUT=1;
            
            temp=DrvXbus_ReadLcd16(LCD_REG_GET_CRC_ADDR);
            DBG_FLOW("\ncrc[%02x]=%04x",k,lcd_ecc);
            
            
            if(lcd_ecc == temp) break;
           
            DrvXbus_WriteLcd8(LCD_REG_SET_RELOAD_ADDR,LCD_REG_SET_RELOAD_VALUE);
            INTOUT=0;
            while(LCD_RELOAD_FLASH == 0);  //wait LCD_RELOAD_INT rise 2.45MS
            INTOUT=1;
                      
    }    

    return 1;
}
/*******************************************************************************
*   Name: Test_Xbus_reg()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Xbus_reg()
{  
    UINT8 i,FWconfig[16]={0x70,0x8f,0x00,0xff,0,0,\
                        0x01,0xfe,0x01,0xfe,0x01,0xfe,0,0xff};
    UINT16 temp=0;
    //Drv_XbusInit();
    DBG_FLOW("\n LCD_RELOAD =%02x ",LCD_RELOAD_FLASH);
    if(LCD_RELOAD_FLASH)
    {
        RELOAD_ABORT_H;//                
        while(LCD_RELOAD_FLASH);
        RELOAD_ABORT_L;
    }
    DBG_FLOW("\n LCD_RELOAD =%02x ",LCD_RELOAD_FLASH);
    DBG_FLOW("\nWriteLcd");
    for(i=0;i<8;i+=2)
    {
        DrvXbus_WriteLcd8(i+LCD_XBUS_REG_ADDR,0x55);
        DrvXbus_WriteLcd8(i+1+LCD_XBUS_REG_ADDR,0xAA);
        //DrvXbus_WriteLcd16(i+LCD_XBUS_REG_ADDR,0x55AA);
        temp=DrvXbus_ReadLcd16(LCD_XBUS_REG_ADDR+i);
        DBG_FLOW("\nXbus[%02x]=%lx\n",i,temp);
        if(temp!=0x55aa)
        {
            DBG_FLOW("\ntest Xbus_reg err1=%lx\n",i);
            HOLD;
        }
    }

    DBG_FLOW("\nWriteLcd");
    for(i=0;i<8;i+=2)
    {
        DrvXbus_WriteLcd8(i+LCD_XBUS_REG_ADDR,0xAA);
        DrvXbus_WriteLcd8(i+1+LCD_XBUS_REG_ADDR,0x55);
        
        temp=DrvXbus_ReadLcd16(LCD_XBUS_REG_ADDR+i);
        DBG_FLOW("\nXbus[%02x]=%lx\n",i,temp);
        if(temp!=0xaa55)
        {
            DBG_FLOW("\ntest Xbus_reg err2=%lx\n",i);
            HOLD;
        }
    }
    DBG_FLOW("\nTest Lcd OTP");
    for(i=0;i<16;i++)
    {
        DrvXbus_WriteLcd8(i+LCD_OTP_REG_ADDR,FWconfig[i]);        
    }
    
    for(i=0;i<8;i+=2)
    {        
        temp=DrvXbus_ReadLcd16(LCD_OTP_REG_ADDR+i);
        DBG_FLOW("\nXbus[%02x]=%04x\n",i,temp);        
    }
    
}
#if _TEST_XBUS_EN
/*******************************************************************************
*   Name: Test_Xbus()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Xbus()
{
    UINT8 test_cnt=3;
    Drv_XbusInit();
    Test_Xbus_reg();
    while(test_cnt--)
    {
        DrvWriteLcdInitCode();
    }
}
#endif
#endif

