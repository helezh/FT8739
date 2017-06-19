#include "Test_Xbus.h"

#if _TEST_XBUS_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define WRITERREAD  1
#define READONLY    0
/* lcd wrap base addr */
#define LCD_WRAP_START_ADDR     0x9C00
//对lcd reg操作，小心操作
#define LCD_REG_BASE_ADDR      0x020000
#define Xbus_ADDR8(n)    (*((UINT8 far *)(LCD_REG_BASE_ADDR + n)))
#define Xbus_ADDR16(n)   (*((UINT16 far *)(LCD_REG_BASE_ADDR + n)))
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/


/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
//ST_LcdWrapRegisters *XRAM pLcdWrapRegs = (volatile ST_LcdWrapRegisters *)LCD_WRAP_START_ADDR;
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
#if 0
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
#endif

void Test_Xbus(void)
{
    UINT16 count;
    UINT16 usReadBack = 0xff;
    UINT8  MyusReadBack = 0xff;
    UINT16 tempAddr = 0xA480;
    UINT8 WriteData = 0x27;
    volatile UINT8 temp2;
    DBG_FLOW("\n\rTest_Xbus start ");
#if 1
    XBUSCKEN = 1;
#if WRITERREAD
    while(1)
    {
        DBG_FLOW("\n\r***Single Start===================================***");
        pRlDmaRegs->CtrlReg = (pRlDmaRegs->CtrlReg | 0x0004);
        DelayMs(10);
        while (((pRlDmaRegs->CtrlReg)&0x0002) == 1)
        {
            DBG_FLOW("\n\rstart sing\n\r");     

        }
        WriteData++;
        if(WriteData > 0xF5)
        {
            WriteData = 0;
        }
        tempAddr++;
        if(tempAddr > 0xA48F)
        {
             tempAddr = 0xA480;
        }
        
        DBG_FLOW("\n\r ======adr = %04x",tempAddr);
        DBG_FLOW("\n\r ======Data= %02x",WriteData);
        P0_6 = 0;
        while(((pLcdWrapRegs->lcd_regfile_ctrl) & 0x0002) == 0)
        {
            DBG_FLOW("\n\r[0] %04x",(pLcdWrapRegs->lcd_regfile_ctrl));
        }
        DelayMs(10);
        P0_6 = 1;
        Xbus_ADDR8(tempAddr) = WriteData;
        P0_6 = 0;
        while (((pLcdWrapRegs->lcd_regfile_ctrl)&0x0002) == 0)
        {
            DBG_FLOW("\n\r[1] %04x",(pLcdWrapRegs->lcd_regfile_ctrl));
        }
        P0_6 = 1;
        temp2 = Xbus_ADDR8(tempAddr);
             
        while(((pLcdWrapRegs->lcd_regfile_ctrl) & 0x0001) == 0);
        {
            //DBG_FLOW("\n[2] %04x",pLcdWrapRegs->LcdRegCtrl);
            DBG_FLOW("\n\rRd wating");
            //DelayMs(100);
        }

        DBG_FLOW("\n[3] %04x",(pLcdWrapRegs->lcd_regfile_ctrl));
        if(tempAddr % 2 == 0)
        {
            MyusReadBack = pLcdWrapRegs->rdata_lo_byte;
        }
        else
        {
            MyusReadBack = pLcdWrapRegs->rdata_ho_byte;
        }
       // usReadBack = (UINT16)((pLcdWrapRegs->rdata_ho_byte << 8) + (pLcdWrapRegs->rdata_lo_byte & 0x00ff));
        DBG_FLOW("\n\r ======usReadBack= %02x",MyusReadBack);
        DBG_FLOW("\n\r***Single end====================================***");
        DelayMs(2000);
    }
#endif
#if READONLY
    while(1)
    {
        DBG_FLOW("\n\r***Single Start===================================***");
        pRlDmaRegs->CtrlReg = ((pRlDmaRegs->CtrlReg) | 0x0004);
        while(pRlDmaRegs->CtrlReg & 0x0002 == 1);
        tempAddr++;
        if(tempAddr > 0xA48F)
        {
             tempAddr = 0xA480;
        }
        while (((pRlDmaRegs->CtrlReg)&0x0002) == 1);
        temp2 = Xbus_ADDR8(tempAddr);
        while(((pLcdWrapRegs->lcd_regfile_ctrl) & 0x0001) == 0);
        if(tempAddr % 2 == 0)
        {
            MyusReadBack = pLcdWrapRegs->rdata_lo_byte;
        }
        else
        {
            MyusReadBack = pLcdWrapRegs->rdata_ho_byte;
        }
        DBG_FLOW("\n\r ======usReadBack= %02x",MyusReadBack);
        DBG_FLOW("\n\r ======adr = %04x",tempAddr);
        DBG_FLOW("\n\r***Single End  ===================================***");
        DelayMs(2000);
    }
#endif


    XBUSCKEN = 0;
    #endif
}
#endif

