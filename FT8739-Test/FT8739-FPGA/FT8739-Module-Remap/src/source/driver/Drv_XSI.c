/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Drv_XSI.c
*
*    Author: xinkunpeng
*
*   Created: 2014-05-14
*
*  Abstract:
*
* Reference:
*
*   Version:
*
*******************************************************************************/
#include "Drv_XSI.h"
#include "FT8836_Reg.h"

/*******************************************************************************
* 1.Included header files
*******************************************************************************/

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
ST_XSIRegisters * XRAM pXSI0Regs = (volatile ST_XSIRegisters *)XSI0_REG_BASE_ADDR;
ST_XSIRegisters * XRAM pXSI1Regs = (volatile ST_XSIRegisters *)XSI1_REG_BASE_ADDR;

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
*   Name: Drv_Xsi0Init
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Drv_XsiInit()
{
    AFECKEN  = 1;
    XSICKEN = 1;

    //XSI_SEL = 0; //CPU·ÃÎÊXSI

    // clk sel
    pXSI0Regs->Clksel = 1;
    pXSI1Regs->Clksel = 1;
   // pXSI2Regs->Clksel = 3;

    //LCD_XSI_CLKEN = 0; 
    //LCD_XSI_CLKEN = 0x5A;

   /* while(LCD_XSI_CLKEN!=1)
    {
        DBG_FLOW("\n\rLCD_XSI_CLKEN = %x",LCD_XSI_CLKEN);
    }*/
}

/*******************************************************************************
*   Name: Drv_XsiReadReg
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT16 Drv_XsiReadReg(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT8 flag)
{
    UINT16 tmp;
    XSI_SEL = 0;

    //pXSIRegs->Stop = 1;
    //while (pXSIRegs->Stop);  

    pXSIRegs->Wdata  = (0<<XSI_WDATA_WR) + (flag<<XSI_WDATA_SEL) + usAddr;
    while (!pXSIRegs->Tx_int);

    pXSIRegs->Wdata = XSI_WDATA_DUMMY; // dummy
    while (!pXSIRegs->Tx_int);

    tmp = pXSIRegs->Rdata;
    pXSIRegs->Stop = 1;
    while (pXSIRegs->Stop);
    XSI_SEL = 1;

    return tmp;
}

/*******************************************************************************
*   Name: Drv_XsiWriteReg
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Drv_XsiWriteReg(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 usData,UINT8 flag)
{
    XSI_SEL = 0;
    //pXSIRegs->Stop = 1;
    //while (pXSIRegs->Stop);    

    pXSIRegs->Wdata = (1<<XSI_WDATA_WR) + (flag<<XSI_WDATA_SEL) + usAddr;
    while (!pXSIRegs->Tx_int);

    pXSIRegs->Wdata = usData;
    while (!pXSIRegs->Tx_int);
    pXSIRegs->Stop = 1;
    while (pXSIRegs->Stop);
    XSI_SEL = 1;
}

/*******************************************************************************
*   Name: Drv_XsiRead
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Drv_XsiRead(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 *pBuf, UINT16 len, UINT8 flag)
{
    UINT8 i;

    XSI_SEL = 0;
    //pXSIRegs->Stop = 1;
    //while (pXSIRegs->Stop);      

    pXSIRegs->Wdata  = (0<<XSI_WDATA_WR) + (flag<<XSI_WDATA_SEL) + usAddr;
    while (!pXSIRegs->Tx_int);

    for (i = 0; i < len; i++)
    {
        pXSIRegs->Wdata = XSI_WDATA_DUMMY;   // dummy
        while (!pXSIRegs->Tx_int);

        *pBuf++ = pXSIRegs->Rdata;
    }
    
    pXSIRegs->Stop = 1;
    while (pXSIRegs->Stop);
    XSI_SEL = 1;
}

/*******************************************************************************
*   Name: Drv_XsiWrite
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Drv_XsiWrite(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 *pBuf, UINT8 len, UINT8 flag)
{
    UINT8 i;
    XSI_SEL = 0;

    //pXSIRegs->Stop = 1;
    //while (pXSIRegs->Stop);      

    pXSIRegs->Wdata = (1<<XSI_WDATA_WR) + (flag<<XSI_WDATA_SEL) + usAddr;
    while (!pXSIRegs->Tx_int);

    for (i = 0; i < len; i++)
    {
        pXSIRegs->Wdata = *pBuf++;
        while (!pXSIRegs->Tx_int);
    }
    pXSIRegs->Stop = 1;
    while (pXSIRegs->Stop);
    XSI_SEL = 1;    
}

#if _TEST_XSI_EN
/*******************************************************************************
*   Name: Test_Xsi()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Xsi()
{
    UINT8 i,j;
    UINT8 len;
    UINT16 k = 0;
    UINT16 XRAM Buf1[200];
    UINT16 XRAM Buf2[200];
    UINT16 XRAM Buf3[200];

    DBG_MODE("\n\rXSI test is start");
    Drv_XsiInit();
    len = 200;
    for (i = 0; i < len; i++)
    {
        Buf3[i] = 5 + i;
    }
    
    while (1)
    {
        for (j = 0; j < 200; j++)
        {
            for (i = 0; i < len; i++)
           {
                Buf1[i] = i + Buf3[j];
           }
            Drv_XsiWrite(pXSI0Regs,256,Buf1,len,XSI_S_REG);
            Drv_XsiRead(pXSI0Regs,256,Buf2,len,XSI_S_REG);
            for (i = 0; i < len; i++)
            {
                if (Buf1[i] != Buf2[i])                
                {
                    DBG_ERROR("\n\rBuf1[%02d]: %04x,Buf2[%02d]: %04x",i,Buf1[i],i,Buf2[i]);
                    break;
                }
            }
            DelayMs(10);
        }
        k++;
        DBG_XSI("\n\rCounter: %06d",k);
    }
    DBG_MODE("\n\rXSI test is end");
}
#endif

