/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Task_lcd_reload.c
*
*    Author: tangsujun
*
*   Created: 2017-03-22
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/
/******************************************************************************
*
* 1.Included header files
******************************************************************************/
#include "CfgGlobal.h"

#include "Task_lcd_reload.h"

#if _LCD_RELOAD_EN
/******************************************************************************
*
* 2.Private constant and macro definitions using #define
******************************************************************************/


#define WRITERREAD  1
#define READONLY    0
/* lcd wrap base addr */
#define LCD_WRAP_START_ADDR     0xBC00
//对lcd reg操作，小心操作
#define LCD_REG_BASE_ADDR      0x020000
#define Xbus_ADDR8(n)    (*((UINT8 far *)(LCD_REG_BASE_ADDR + n)))
#define Xbus_ADDR16(n)   (*((UINT16 far *)(LCD_REG_BASE_ADDR + n)))

#define LCD_REG_GET_CRC_ADDR        0x0304
#define LCD_REG_SET_RELOAD_ADDR     0xfb30 // 0xfb10 // 0xfb30 
#define LCD_REG_SET_RELOAD_VALUE    0x00

#define RELOAD_END_H        pLcdWrapRegs->xbus_cmd |=  BITn(1)
#define RELOAD_END_L        pLcdWrapRegs->xbus_cmd &=~ BITn(1)

#define RELOAD_ABORT_H      pLcdWrapRegs->xbus_cmd |=  BITn(0)
#define RELOAD_ABORT_L      pLcdWrapRegs->xbus_cmd &=~ BITn(0)



#define FLASH_READ_CRC_ERROR           0xFD
#define FLASH_READ_CHECKSUM_ERROR      0xFE
#define FLASH_RELOAD_ERROR             0xFF
#define FLASH_RELOAD_SUCCESS           0xEE
/******************************************************************************
*
* 3.Private enumerations, structures and unions using typedef
******************************************************************************/
ST_LcdWrapRegisters *XRAM pLcdWrapRegs = (volatile ST_LcdWrapRegisters *)XBUS_REG_BASE_ADDR;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

UINT8 XRAM g_ucLcdBuf[LCDINITCODE_TOTAL_SIZE]  _at_ 0x100;

UINT8 g_ucLcdInitCodeOK = FALSE; 
UINT16 usLcdCrc,g_unLcdLen;
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


/******************************************************************************
*
*   Name: DrvXbus_ReadLcd16
*  Brief: 读lcd数据 16位(双字节对齐)
*  Input:
* Output:
* Return:
******************************************************************************/
UINT16 DrvXbus_ReadLcd16(UINT16 usaddr)
{
    volatile UINT8 Dummy;
    UINT8 delay;
    
    delay=0x20;
    while(((pLcdWrapRegs->lcd_regfile_ctrl & BITn(1))==0)&&delay--);   //wait wr enable    
    Dummy = Xbus_ADDR8(usaddr); 
    
    delay=0x20;
    while(((pLcdWrapRegs->lcd_regfile_ctrl & BITn(0))==0)&&delay--);   //wait rdata redy    
    //return (UINT16)((pLcdWrapRegs->rdata_lo_byte << 8) + (pLcdWrapRegs->rdata_ho_byte & 0x00ff)); //Big-endian
    return (UINT16)(pLcdWrapRegs->rdata_lo_byte);
}

/******************************************************************************
*
*   Name: DrvXbus_WriteLcd8
*  Brief:写lcd数据 8位
*  Input:
* Output:
* Return:
******************************************************************************/
void DrvXbus_WriteLcd8(UINT16 usaddr,UINT8 usdata)
{
    UINT8 delay;
    delay=0x20;
    while(((pLcdWrapRegs->lcd_regfile_ctrl & BITn(1))==0)&&delay--);   //wait wr enable    
    Xbus_ADDR8(usaddr) = usdata;
}

/******************************************************************************
*
*   Name: DrvReadFlashLcdInitCode
*  Brief: 读Flash Lcd Init code
*  Input:
* Output:
* Return:
******************************************************************************/
UINT8 DrvReadFlashLcdInitCode(void)
{

    UINT16 ucBuf[4];
    UINT16 usLen;
    UINT16 usCalCrc;
    UINT16 usFlashCrc;

    SPIFlash_FastRead(LCDINITCODE_START_FLASH_ADDR, (UINT8*)ucBuf,8);

    /* Flash CRC usLen */    
    usLen      = ucBuf[0]-4;//参与FLASH CRC计算的数据长度
    usFlashCrc = ucBuf[1];
    /* Init Code Size:  */
    g_unLcdLen  = usLen -4; //ucBuf[2];
    usLcdCrc    = ucBuf[3];


    //DBG_LCD("\n flashLen=%04x,crc=%04x",usLen,usFlashCrc);
    //DBG_LCD("\n LcdLen=%04x,crc=%04x",g_unLcdLen,usLcdCrc);
    /* 长度加保护 */
    if ((g_unLcdLen >= LCDINITCODE_CODESIZE_MAX)||(g_unLcdLen < 8))
    {
        return FALSE;
    }
#if !_FLASH_TO_LCD

    /* 读LCD Init Code */
    SPIFlash_FastRead(LCDINITCODE_DATA_START_ADDR, (UINT8 *)g_ucLcdBuf,usLen);
    //SPIFlash_ReadToPram(LCDINITCODE_DATA_START_ADDR, (UINT8 *)g_ucLcdBuf,usLen);

#if  _CRC_CAL_EN
    usCalCrc = CAL_Check((UINT16)g_ucLcdBuf,usLen>>1,CRC_TYPE_DRAM);
#else
    usCalCrc = DrvCRC(((UINT32)g_ucLcdBuf),usLen>>1);
#endif

    //DBG_LCD("\nusFlashCrc: %04x-%04x",usCalCrc,usFlashCrc);
    if (usCalCrc != usFlashCrc)
    {     
        return FALSE;
    }    
#endif
    return TRUE;
}

/******************************************************************************
*
*   Name: DrvPrepareLcdInitCode
*  Brief: 准备LCD Init Code数据
*  Input:
* Output:
* Return:
******************************************************************************/
void DrvPrepareLcdInitCode(void)
{
    UINT8 i;

    for(i =0; i < 3; i++)
    {
        g_ucLcdInitCodeOK = DrvReadFlashLcdInitCode();  
        if (g_ucLcdInitCodeOK !=0) break;
    }
    //DBG_LCD("\nInitCodeOK=%02x",g_ucLcdInitCodeOK);
}
#if !_FLASH_TO_LCD
/******************************************************************************
*
*   Name: AppLcdInitCodeReload
*  Brief: TP导入lcd init code到LCD中
*  Input:
* Output:
* Return:
******************************************************************************/
void AppLcdInitCodeReload(void)
{
    static UINT8 ReloadCnt=0;
    UINT8 delay;   
    UINT16 i,lcd_ecc=0,*ptr16=0;
    
    
    DBG_LCD("\n1 LCD_RELOAD =%02x ",LCD_RELOAD_FLASH);
    //DBG_LCD("\n1 g_unLcdLen =%04x ",g_unLcdLen);
    if(g_ucLcdInitCodeOK)
    {
        //do{
        ptr16 =(UINT16*)&g_ucLcdBuf[4];
        
        for(i=0;i<(g_unLcdLen);i+=2)
        {
            pLcdWrapRegs->xbus_rld_data=*ptr16;
            //DBG_LCD("\nrld=%04x",*ptr16);
            //wait_printf_done();
            ptr16++;
        }  
    
        RELOAD_END_H;// 
        delay=0x20;
        while(LCD_RELOAD_FLASH&&delay--);
        
        RELOAD_END_L;
        
        lcd_ecc=DrvXbus_ReadLcd16(LCD_REG_GET_CRC_ADDR);            
        

        if(lcd_ecc != usLcdCrc)
        {
            ReloadCnt++;
            if(ReloadCnt< 3)
            {
                DrvXbus_WriteLcd8(LCD_REG_SET_RELOAD_ADDR,LCD_REG_SET_RELOAD_VALUE);
                //while(LCD_RELOAD_FLASH == 0);  //wait LCD_RELOAD_INT rise 2.45MS
            }
            g_ucReloadState= FLASH_RELOAD_ERROR;
           
        } 
        else
        {
            g_ucReloadState= FLASH_RELOAD_SUCCESS;  
            
        }
        //}while((ReloadCnt<3)&&(g_ucReloadState != FLASH_RELOAD_SUCCESS));
        
        
    } 
    else
    {
        RELOAD_ABORT_H;// 
        delay=0x20;
        while(LCD_RELOAD_FLASH&&delay--);
        RELOAD_ABORT_L;
        g_ucReloadState= FLASH_READ_CRC_ERROR;  

    }
    //DBG_LCD("\ncrc=%04x",lcd_ecc);
    
    wait_printf_done();
    
    
  //  GPIO3 =1;
}
#else
void AppLcdInitCodeReload(void)
{
    static UINT8 ReloadCnt=0;
    UINT8 delay;   
    UINT16 i,lcd_ecc=0,*ptr16=0;
    
    
    DBG_LCD("\n1 LCD_RELOAD =%02x ",LCD_RELOAD_FLASH);
    
       

        
        g_unLcdLen=0x0704;
        SPIFlash_ReadToLCD(8,g_unLcdLen); 
        
    
        RELOAD_END_H;// 
        delay=0x20;
        while(LCD_RELOAD_FLASH&&delay--);
        
        RELOAD_END_L;
        
        lcd_ecc=DrvXbus_ReadLcd16(LCD_REG_GET_CRC_ADDR);            
        

        if(lcd_ecc != usLcdCrc)
        {
            ReloadCnt++;
            if(ReloadCnt< 3)
            {
                DrvXbus_WriteLcd8(LCD_REG_SET_RELOAD_ADDR,LCD_REG_SET_RELOAD_VALUE);
                //while(LCD_RELOAD_FLASH == 0);  //wait LCD_RELOAD_INT rise 2.45MS
            }
            g_ucReloadState= FLASH_RELOAD_ERROR;
           
        } 
        else
        {
            g_ucReloadState= FLASH_RELOAD_SUCCESS;  
            
        }
        
        

    DBG_LCD("\ncrc=%04x",lcd_ecc);
    
    wait_printf_done();
    
    
  //  GPIO3 =1;
}

#endif
#if _OTP_SLAVE_EN
/******************************************************************************
*
*   Name: Read_Lcd_OTP
*  Brief: 读LCD OTP 中FW CONFIG信息
*  Input:
* Output:
* Return:
******************************************************************************/
void Read_Lcd_OTP(UINT16 *ptr16,UINT8 len)
{
    UINT8 i=0;
    
    
    for(i=0;i<len;i+=2)
    {
        *ptr16++=DrvXbus_ReadLcd16(i+0XF300);
    }
    
    
}
#endif





#endif


