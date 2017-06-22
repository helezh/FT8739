
/*******************************************************************************
* Copyright (C) 2017-2019, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Drv_CRC.c
*
*    Author: tangsujun
*
*   Created: 2017-03-22
*
*  Abstract:
*
* Reference:
*
*   Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "CfgGlobal.h"


/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef struct
{
    UINT16 poly;
    UINT16 init;
    UINT8  refin;
    UINT8  refout;
    UINT16 xorout;
    
}ST_CRC_MODE_Init;

typedef enum
{
     CRC16_IBM_M,
     CRC16_MAXIM_M,
     CRC16_USB_M,
     CRC16_MODBUS_M,
     CRC16_LCD_M,
     CRC16_SPI0_M,    
     CRC16_CCITT_M,
    
}ST_CRC_TYPE;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
ST_CRC_MODE_Init Crc_mode;
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




/****************************************************************************/

static  UINT16 XRAM wCRCTable[] = {
0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

UINT16 CRC16 (const UINT8 *nData, UINT16 wLength)
{

    UINT8 nTemp;
    UINT16 wCRCWord = 0;//xFFFF;

   while (wLength--)
   {
      nTemp = *nData++ ^ wCRCWord;
      wCRCWord >>= 8;
      wCRCWord ^= wCRCTable[nTemp];
   }
   return wCRCWord;

}

UINT8 InvertUint8(UINT8 val)
{
    UINT8 temp=0,c=0x80,i;  
   
    for(i=0;i<8;i++)
    {
        if(val&c)
        temp|=0x01<<i;
        c>>=1;
    }
   
    return temp;
}

UINT16 InvertUint16(UINT16 val)
{
    UINT8 temph,templ;
    
    temph   =val&0xff;
    templ   =val>>8;
    temph=InvertUint8(temph);
    templ=InvertUint8(templ);

    return ((UINT16)temph<<8|templ);

}

/*******************************************************************************
*   Name: CRC16_mode_init
*  Brief: CRC16_mode_init
*  Input:
* Output:
* Return:
*******************************************************************************/
void CRC16_mode_init(ST_CRC_TYPE val,ST_CRC_MODE_Init *pCrcInit) 
{

    switch(val)
    {
        case CRC16_IBM_M:
                        pCrcInit->init=0;
                        pCrcInit->poly=0X8005;
                        pCrcInit->refin=1;
                        pCrcInit->refout=1;
                        pCrcInit->xorout=0X0000;
        break;
        case CRC16_MAXIM_M:
                        pCrcInit->init=0;
                        pCrcInit->poly=0X8005;
                        pCrcInit->refin=1;
                        pCrcInit->refout=1;
                        pCrcInit->xorout=0XFFFF;            
        break;
        case CRC16_USB_M:
                        pCrcInit->init=0XFFFF;
                        pCrcInit->poly=0X8005;
                        pCrcInit->refin=1;
                        pCrcInit->refout=1;
                        pCrcInit->xorout=0XFFFF;           
        break;
        case CRC16_MODBUS_M:
                        pCrcInit->init=0XFFFF;
                        pCrcInit->poly=0X8005;
                        pCrcInit->refin=1;
                        pCrcInit->refout=1;
                        pCrcInit->xorout=0X0000;           
        break;
        
        case CRC16_LCD_M:
                        pCrcInit->init=0XFFFF;
                        pCrcInit->poly=0X8005;
                        pCrcInit->refin=0;
                        pCrcInit->refout=0;
                        pCrcInit->xorout=0X0000;           
        break;

        case CRC16_SPI0_M:
                        pCrcInit->init=0XFFFF;
                        pCrcInit->poly=0X1021;//0X8048
                        pCrcInit->refin=1;
                        pCrcInit->refout=1;
                        pCrcInit->xorout=0X0000;           
        break;
        case CRC16_CCITT_M:
                        pCrcInit->init=0x0000;
                        pCrcInit->poly=0X1021;
                        pCrcInit->refin=1;
                        pCrcInit->refout=1;
                        pCrcInit->xorout=0X0000;           
        break;

        
        default:
            break;
    }

}
/*******************************************************************************
*   Name: CRC16_fun
*  Brief: CRC16_fun
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT16 CRC16_fun(UINT8 *puchMsg, UINT16 usDataLen,ST_CRC_MODE_Init Crc_mode)  
{  
  UINT16 wCRCin  = Crc_mode.init;  
  UINT16 wCPoly  = Crc_mode.poly;
  UINT16 wXorOut = Crc_mode.xorout;
  UINT8  wChar = 0,i;  
#if 0    
  while (usDataLen--)     
  {  
        wChar = *puchMsg++; 
        
        if(Crc_mode.refin==1)
        wChar=InvertUint8(wChar); 
        
        wCRCin ^= (wChar << 8);  
        for(i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }
  
  if(Crc_mode.refin==1)
  wCRCin=InvertUint16(wCRCin);    
  
#else
  wCPoly=InvertUint16(wCPoly);
  while (usDataLen--)     
  {  
        wChar = *puchMsg++; 
        //DBG_FLOW("\nwChar=%02x",wChar);
        
        if(Crc_mode.refin==0)
        wChar=InvertUint8(wChar); 
        
        wCRCin ^= wChar;  
        for(i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x01)  
            wCRCin = (wCRCin >> 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin >> 1;  
        }  
  }
  
  if(Crc_mode.refin==0)
  wCRCin=InvertUint16(wCRCin);  
#endif

    return (wCRCin^wXorOut) ; 

}
/*******************************************************************************
*   Name: CRCKERMIT
*  Brief: SPI0_DMA CRC算法(CRCKERMIT变种)
*  Input:
* Output:
* Return:
*******************************************************************************/
void CRCKERMIT(const UINT8* pDataIn, UINT16 iLenIn, UINT16* pCRCOut)     
{     
    UINT16 wTemp = 0,i=0,j=0,c=0;      
    UINT16 wCRC = 0xffff;      //原始为0，
  
    for( i = 0; i < iLenIn; i++)      
    {  
        wCRC ^=pDataIn[i];
        
        for(j = 0; j < 8; j++)      
        {      
            if(wCRC&0x01) wCRC=(wCRC>>1)^0X8408;
            else          wCRC=(wCRC>>1);
    
        }      
    }  

    *pCRCOut = wCRC;     //高低交换，原始要交换
}



/*******************************************************************************
*   Name: CRC16_LCD
*  Brief: LCD CRC算法(CRC_USB变种)
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT16 CRC16_LCD(UINT8 *puchMsg, UINT16 usDataLen)  
{  
  UINT16 wCRCin = 0xFFFF;  
  UINT16 wCPoly = 0x8005;  
  UINT8  wChar = 0,i;  
    
  while (usDataLen--)     
  {  
        wChar = *(puchMsg++);  
        wCRCin ^= (wChar << 8);  
        for(i = 0;i < 8;i++)  
        {  
          if(wCRCin & 0x8000)  
            wCRCin = (wCRCin << 1) ^ wCPoly;  
          else  
            wCRCin = wCRCin << 1;  
        }  
  }  

  return wCRCin;

}  

/*******************************************************************************
*   Name: crc_sick
*  Brief: crc_sick
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT16 crc_sick( const unsigned char *input_str, UINT16 num_bytes )
{

    UINT16 crc;
    UINT16 low_byte;
    UINT16 high_byte;
    UINT16 short_c;
    UINT16 short_p;
    const UINT8 *ptr;
    UINT16 a;

    crc     = 0;
    ptr     = input_str;
    short_p = 0;

    if ( ptr != NULL ) 
        for (a=0; a<num_bytes; a++) 
        {

            short_c = 0x00ff & (UINT16) *ptr;

            if ( crc & 0x8000 ) crc = ( crc << 1 ) ^ CRC_POLY_16;
            else                crc =   crc << 1;

            crc    ^= ( short_c | short_p );
            short_p = short_c << 8;

            ptr++;
        }

    low_byte  = (crc & 0xff00) >> 8;
    high_byte = (crc & 0x00ff) << 8;
    crc       = low_byte | high_byte;

    return crc;

}  /* crc_sick */

/******************************************************************************
*
*   Name: Drv_CRC16
*  Brief: 
*  Input:
* Output:
* Return:
******************************************************************************/
static UINT8 Drv_CRC16(void)
{
    UINT8 k=0,buf[16]={0XFF,0XE0,0X01,0X5A,0XA4,0X80,0X02,0Xe7,0X22,0X00,0X44,0X55};
    UINT16 i,len=5,temp=0,lcd_ecc,*ptr16=0;
    UINT8 Lbuf[8]={0XA4,0X67,0xA3,0xd7,0xff,0xe0};
    
    len=6;
    CRC16_mode_init(CRC16_IBM_M,&Crc_mode);    
    lcd_ecc=CRC16_fun(Lbuf,len,Crc_mode);
    DBG_FLOW("\nCRC16_IBM=%04x",lcd_ecc);

    CRC16_mode_init(CRC16_MAXIM_M,&Crc_mode);    
    lcd_ecc=CRC16_fun(Lbuf,len,Crc_mode);
    DBG_FLOW("\nCRC16_MAXIM_M=%04x",lcd_ecc);

    CRC16_mode_init(CRC16_USB_M,&Crc_mode);    
    lcd_ecc=CRC16_fun(Lbuf,len,Crc_mode);
    DBG_FLOW("\nCRC16_USB_M=%04x",lcd_ecc);

    CRC16_mode_init(CRC16_MODBUS_M,&Crc_mode);    
    lcd_ecc=CRC16_fun(Lbuf,len,Crc_mode);
    DBG_FLOW("\nCRC16_MODBUS_M=%04x",lcd_ecc);


    CRC16_mode_init(CRC16_LCD_M,&Crc_mode);    
    lcd_ecc=CRC16_fun(Lbuf,len,Crc_mode);
    DBG_FLOW("\nCRC16_LCD_M=%04x",lcd_ecc);

    CRC16_mode_init(CRC16_SPI0_M,&Crc_mode);    
    lcd_ecc=CRC16_fun(Lbuf,len,Crc_mode);
    DBG_FLOW("\nCRC16_SPI0_M=%04x",lcd_ecc);

    CRC16_mode_init(CRC16_CCITT_M,&Crc_mode);    
    lcd_ecc=CRC16_fun(Lbuf,len,Crc_mode);
    DBG_FLOW("\nCRC16_CCITT_M=%04x",lcd_ecc);
    
    lcd_ecc=crc_sick(Lbuf,len);
    DBG_FLOW("\nsickcrc[2]=%04x",lcd_ecc);



    lcd_ecc=CRC16(Lbuf,len);
    DBG_FLOW("\ncrc16[4]=%04x",lcd_ecc);
    


    CRCKERMIT(Lbuf,len,&lcd_ecc);   
    DBG_FLOW("\nCRCKERMIT=%04x",lcd_ecc);



    return 1;
}


/*******************************************************************************
*   Name: Test_Xbus()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_CRC(void)
{
    UINT8 test_cnt=1;   

    while(test_cnt--)
    {
        Drv_CRC16();
    }
    //HOLD;
}



