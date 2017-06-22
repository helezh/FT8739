/*******************************************************************************
* Copyright (C) 2017-2019, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Drv_XBUS.c
*
*    Author: tangsujun
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
#include "Drv_XBUS.h"
#include "FT8836_Reg.h"

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


/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
ST_LcdWrapRegisters *XRAM pLcdWrapRegs = (volatile ST_LcdWrapRegisters *)XBUS_REG_BASE_ADDR;
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
*   Name: Drv_XbusInit
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Drv_XbusInit(void)
{
    XBUSCKEN = 1;//
    LCD_RELOAD_FLASH_WKEN =1;

}


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
*******************************************************************************/
void DrvXbus_WriteLcd8(UINT16 usaddr,UINT8 usdata)
{
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(1))) == 0); //wait wr enable
    Xbus_ADDR8(usaddr) = usdata;
}

/******************************************************************************
*
*   Name: DrvXbus_WriteLcd16
*  Brief:写lcd数据 16位
*  Input:
* Output:
* Return:
*******************************************************************************/
/*void DrvXbus_WriteLcd16(UINT16 usaddr,UINT16 usdata)
{
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(1))) == 0); //wait wr enable
    Xbus_ADDR16(usaddr) = usdata;
}*/


