/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: SPI-flash.c
*
*    Author: Tangsujun
*
*   Created: 2016-12-12
*
*  Abstract:
*
* Reference:
*
* Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "CfgGlobal.h"
#include "SPI_Flash.h"


#if _SPI_FLASH_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define SPI_DUAL    0
#define SPI_QUAD    0
/******************************************************************************/
// ������ȫ�ֱ�������
/******************************************************************************/


#define SPI_FLASH_LEN   256


#define SPI1_MODE_STD       ((UINT8) 0)
#define SPI1_MODE_DUAL       ((UINT8) 1)
#define SPI1_MODE_QUAD       ((UINT8) 2)

#define SPI1_IO_OUTPUT       ((UINT8) 0)
#define SPI1_IO_INPUT       ((UINT8) 1)


#define CLK_SELECT_SUM      0xAB     // ���ֽںͣ�У����
#define SYS_CLK_48          0x48     // 48Mʱ��


/*SPI CON1  */
#define BIT_TI   7
#define BIT_RI   6
#define BIT_DIV  4
#define BIT_MOD  2
#define BIT_MAS  1
#define BIT_CS   0
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef enum
{
    SPI_CLK_DIV4  = 0x04,  //4��Ƶ��־
    SPI_CLK_DIV8  = 0x08,  //8��Ƶ��־
    SPI_CLK_DIV16 = 0x16,  //16��Ƶ��־
    SPI_CLK_DIV32 = 0x32   //32��Ƶ��־
} ENUM_SPI_FLG;

typedef enum
{
    SPI_DIV_4  = 0,  //24/4 = 6M
    SPI_DIV_8  = 1,  //24/8 = 3M
    SPI_DIV_16 = 2,  //24/16 = 1.5M
    SPI_DIV_32 = 3   //24/32 = 0.75M
} ENUM_SPI_DIV;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

UINT8 SPI_RW_Byte(UINT8 val);

#define SPI_WriteData(n)  SPI_RW_Byte(n)
#define SPI_ReadData(void)  SPI_RW_Byte(0)
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


#if 1
void SPI1_Mode_Sel(UINT8 mode)
{
    if(mode==1)
    {
        SPI1MODE_SELH   =0;
        SPI1MODE_SELL   =1;
    }
    else if(mode==2)
    {
        SPI1MODE_SELH   =1;
        SPI1MODE_SELL   =0;
    }
    else
    {
        SPI1MODE_SELH   =0;
        SPI1MODE_SELL   =0;     
    }

}

void SPI1_IO_Set(UINT8 mode)
{
    if(mode==1)
    {
        SPI1_SW_IO_ENH=0;
        SPI1_SW_IO_ENL=1;

    }
    else if(mode==2)
    {   

        SPI1_SW_IO_ENH=1;
        SPI1_SW_IO_ENL=1;


    }
    else
    {  

        P1MOD = 0x0f;
        SPI1_SW_IO_ENH=0;
        SPI1_SW_IO_ENL=0;

    }
}


void SPI1_IO_Switch(UINT8 time,UINT8 dir)
{
    
        
        SW_1BYTE_LATER  =time&0x01;
         
        SPI1_SW_DIR        =dir&0x01;

        SPI1_SW_EN          =1;

}
#endif
/*******************************************************************************
*   Name: SPI_Init
*  Brief:
*         1.��ʼ��spiʱ�ӷ�Ƶ
*         2.��ʼ��spi�ӿ�
*         3.spi����
*
* 00��4��Ƶ
* 01��8��Ƶ
* 10��16��Ƶ
* 11��32��Ƶ
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI_Init(void)
{

    SPI1CKEN = 1;
    
    SPI1CON  =0X0f;
    SPI1CON2 =0X46;
    SPI1CON3 =0;
    SPI1CON4 =0X11;

    /* IO����: P10-->P13 */
    P1MOD = 0x9f;
    P1SEL = 0xff;    

    
    SPI1_EI = 0;
#if 0
    SPI1MAS = 1;                 // 1��maste mode;
    SPI1_SLVSLELEN  = 1;    // 1��master ģʽ��slvselo��SPI0CON2[2]����

    SPI1PH = 1;
    SPI1PO = 1;

    //SPI��Ƶ����
    SPI1CKH  = 0;
    SPI1CKM  = 0;
    SPI1CKL   = 0;                // 00��4��Ƶ 00��6��Ƶ 10��8��Ƶ

    //�жϱ�־ʹ��
    SPI1RI_EN = 1;
    SPI1TI_EN = 0;


     SPI1_SW_IO_ENH=0;
     SPI1_SW_IO_ENL=0;
     

    SPI1RX_AUTO_CLR =1;
    SPI1TX_AUTO_CLR =0;



    DBG_SPI("\n SPI1CON1=%02x ",SPI1CON);
    DBG_SPI("\n SPI1CON2=%02x ",SPI1CON2);
    DBG_SPI("\n SPI1CON3=%02x ",SPI1CON3);
    DBG_SPI("\n SPI1CON4=%02x ",SPI1CON4);
#endif
//    SPIFlash_ReadID();
//    SPI_PRAM_TEST();
}

/******************************************************************************
*
*   Name: SPI_WriteReadData
*  Brief: ��1������
*  Input:
* Output:
* Return:
******************************************************************************/
UINT8 SPI_RW_Byte(UINT8 val)
{
    SPI_BUF = val;                        // Dummy write to output serial clock
    while (!SPI1RI);                    // Wait for the value to be read
    //SPI1RI  = 0;    
    return SPI_BUF;
}
/*******************************************************************************
*   Name: SPI_Read
*  Brief: ��n������
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI_Read(UINT8 far *pBuf, UINT32 len)
{
    UINT32 i;

#if 0
    for (i = 0; i < len; i++)
    {
        SPI_BUF  = 0;
        while (!SPI1RI);
       // SPI1RI = 0;
        *pBuf++ = SPI_BUF;
    }

#else
    if(len==0) return;    
    SPI_BUF  = 0;
    len = len - 1;
    for (i = 0; i < (len); i++)
    {
        
        while (!SPI1RI);
        SPI_BUF  = 0;
   //    SPI1RI = 0;
        *pBuf++ = SPI_BUF;
    }
    while (!SPI1RI);
    *pBuf = SPI_BUF;
    
#endif
}

/******************************************************************************/
//flash�������

/*******************************************************************************
*   Name: SPIFlash_FastReadAddr
*  Brief:
* 1.��N���ֽ�
* 2.���ٶ�����
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_FastReadAddr(UINT32 addr)
{
   
    SPI1_CSN = 0;                        // ʹ��оƬ����
    SPI_WriteData(CMD_FAST_READ);          // ��ָ��
    SPI_WriteData((UINT8)(addr>>16) );                 // д��ַ
    SPI_WriteData((UINT8)(addr>>8) );                 // д��ַ
    SPI_WriteData((UINT8)addr );                 // д��ַ
    SPI_WriteData(0x00);                   // dummy data to insert 8 dummy clocks

}
/******************************************************************************
*
*   Name: SPIFlash_DUALAddr
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
void SPIFlash_DUALAddr(UINT32 addr,UINT8 cmd)
{    
    
    SPI1_Mode_Sel(SPI1_MODE_STD);
    SPI1_IO_Set(SPI1_MODE_DUAL);  
    
    
    SPI1_CSN = 0;                        // ʹ��оƬ����
    if(cmd !=0)  //0xbb
    {
        SPI_WriteData(CMD_READ_DUAL_IO);          // ��ָ��
        SPI1_Mode_Sel(SPI1_MODE_DUAL);    
        SPI1_IO_Switch(0, SPI1_IO_OUTPUT);
    }
    else    //0x3b
    {
        SPI_WriteData(CMD_READ_DUAL_O);          // ��ָ��
    }
    SPI_WriteData((UINT8)(addr>>16) );                 // д��ַ
    SPI_WriteData((UINT8)(addr>>8) );                 // д��ַ
    SPI_WriteData((UINT8)addr );                 // д��ַ

    
    SPI1_IO_Switch(1, SPI1_IO_INPUT);
    
    SPI_WriteData(0x00);                   // dummy data to insert 8 dummy clocks
    if(cmd==0)  //0x3b
    {
        SPI1_Mode_Sel(SPI1_MODE_DUAL); 
    }

}
/*******************************************************************************
*   Name: SPIFlash_FastReadAddr
*  Brief:
* 1.��N���ֽ�
* 2.���ٶ�����
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_FastRead(UINT32 addr, UINT8 far *pBuf, UINT32 len)
{
  
    SPIFlash_FastReadAddr(addr);
    SPI_Read(pBuf,len);                     // ������
    SPI1_CSN = 1;                         // ��ֹоƬ����
    
}
/*******************************************************************************
*   Name: SPIFlash_DualRead
*  Brief:
* 1.��N���ֽ�
* 2.���ٶ�����
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_DualRead(UINT32 addr, UINT8 far *pBuf, UINT32 len)
{

    //SPIFlash_DUALAddr(addr,spi_std_dual&0x01);// 
    SPIFlash_DUALAddr(addr,g_ucSpi_mode&0x80);// 
    SPI_Read(pBuf,len);                     // ������
   
    SPI1_CSN = 1;                         // ��ֹоƬ����
    SPI1_Mode_Sel(SPI1_MODE_STD);
    SPI1_IO_Set(SPI1_MODE_STD);  
}
/*******************************************************************************
*   Name: SPIFlash_ReadToPram
*  Brief:
* 1.��N���ֽ�
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_ReadToPram(UINT32 addr, UINT32 pramstart, UINT32 len)
{
    UINT8 far * ptr=0;

    ptr= (UINT8 far  *)pramstart; 

    if((g_ucSpi_mode==CMD_READ_DUAL_O)||(g_ucSpi_mode==CMD_READ_DUAL_IO))//if((spi_std_dual&0x02))
    {
        SPIFlash_DualRead(addr, ptr, len);//
    }
    else
    {
         SPIFlash_FastRead(addr, ptr, len);
    }

}



#endif
