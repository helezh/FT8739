/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_romboot.c
*
*    Author: xinkunpeng
*
*   Created: 2014-05-07
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_romboot.h"

#if _TEST_ROMBOOT_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
volatile UINT32 far *load_ok  =   ((UINT32 *)(0xFFFFFF-0X03));
volatile UINT32 far *load_err =   ((UINT32 *)(0xFFFFFF-0X07));
volatile UINT32 far *load_cnt =   ((UINT32 *)(0xFFFFFF-0X0B));
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
*   Name: TestClrMemEccRun()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestClrMemEccRun()
{
    //clear app-ecc
    PRAM_ADDR16(ADDR_PART1_ECC) = 0x00;
    PRAM_ADDR16(ADDR_PART2_ECC) = 0x00;
    while (1);
}

/*******************************************************************************
*   Name: TestClrMemEccSoftRST()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestClrMemEccSoftRST()
{
    //clear app-ecc
    PRAM_ADDR16(ADDR_PART1_ECC) = 0x00;
    PRAM_ADDR16(ADDR_PART2_ECC) = 0x00;
    DelayMs(1000);
    //reset
    SFTRST = 0xFF;
}

/*******************************************************************************
*   Name: TestClrMemEccWDTRST()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestClrMemEccWDTRST()
{
    //clear app-ecc
    PRAM_ADDR16(ADDR_PART1_ECC) = 0x00;
    PRAM_ADDR16(ADDR_PART2_ECC) = 0x00;
    //DelayMs(1000);
    WDTREL     = 0x3B;   
    WDTSTARTEN = 1;
    WDT  = 1;
    SWDT = 1;
    while (1);
}

/*******************************************************************************
*   Name: TestOnlyClrMemEcc()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestOnlyClrMemEcc()
{
    //clear app-ecc
    PRAM_ADDR16(ADDR_PART1_ECC) = 0x00;
    PRAM_ADDR16(ADDR_PART2_ECC) = 0x00;
}

/*******************************************************************************
*   Name: TestSoftRST()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestSoftRST()
{
    DelayMs(2000);
    SFTRST = 0xFF;
}

/*******************************************************************************
*   Name: TestWDTRST()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestWDTRST()
{
    DelayMs(2000);
    WDTREL     = 0x7B;  // Over time = 12.096 + (0x7F-0x2F)*12.288 = 955.136ms
    WDTSTARTEN = 1;
    WDT  = 1;
    SWDT = 1;
    while (1);
}

/*******************************************************************************
*   Name: TestUpdateRST()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestUpdateRST()
{
    DelayMs(2000);
    RST_STA = RST_VALUE_UPGRADE;
    SFTRST  = 0xFF;
}


/*******************************************************************************
*   Name: TestChangeEcc1()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestChangeEcc1()
{
    DelayMs(2000);
    PRAM_ADDR16(ADDR_PART1_ECC) += 1;
    PRAM_ADDR16(ADDR_PART1_ECC_NE) -= 1;
    SFTRST  = 0xFF;
}


/*******************************************************************************
*   Name: TestChangeEcc2()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestChangeEcc2()
{
    DelayMs(2000);
    PRAM_ADDR16(ADDR_PART2_ECC) += 1;
    PRAM_ADDR16(ADDR_PART2_ECC_NE) -= 1;
    SFTRST  = 0xFF;
}


/*******************************************************************************
*   Name: TestChangeLenL()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestClrLen()
{
    DelayMs(2000);
    PRAM_ADDR16(ADDR_APP_LEN) = 0;
    PRAM_ADDR16(ADDR_APP_NE_LEN) = 0xFFFF;    
    PRAM_ADDR16(ADDR_APP_LEN_H) = 0;
    PRAM_ADDR16(ADDR_APP_LEN_H) = 0xFFFF;   
    SFTRST  = 0xFF;
}

/*******************************************************************************
*   Name: TestMaxLen()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestMaxLen()
{
    DelayMs(2000);
    PRAM_ADDR16(ADDR_APP_LEN) = 0;
    PRAM_ADDR16(ADDR_APP_NE_LEN) = 0xFFFF;    
    PRAM_ADDR16(ADDR_APP_LEN_H) = 2;
    PRAM_ADDR16(ADDR_APP_LEN_H) = 0xFFFD;  
    SFTRST  = 0xFF;
}


/*******************************************************************************
*   Name: TestMaxLen()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestChangeLen()
{
    DelayMs(2000);
    PRAM_ADDR16(ADDR_APP_LEN) -= 1;
    PRAM_ADDR16(ADDR_APP_NE_LEN) += 1;    
    SFTRST  = 0xFF;
}
/*******************************************************************************
*   Name: TestLoadCnt()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestLoadCnt()
{
    DBG_FLOW("\nload_ok:0x%lx",*load_ok);
    DBG_FLOW("\nload_err:0x%lx",*load_err);    
    DBG_FLOW("\nload_cnt:0x%lx",*load_cnt);
    DelayMs(2000);
    PRAM_ADDR16(ADDR_PART1_ECC) = 0x00;
    PRAM_ADDR16(ADDR_PART2_ECC) = 0x00;    
    SFTRST  = 0xFF;
    
}


/*******************************************************************************
*   Name: Test_romboot()
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_romboot()
{
    UINT8 g_ucRomboot;

    DBG_FLOW("\nTest_romboot\n");
    DelayMs(500);
    g_ucRomboot = 0x05;//5;// 2;
    switch (g_ucRomboot)
    {
        case 0x01:
        {
            TestClrMemEccRun();
            break;
        }
        case 0x02:
        {
            TestClrMemEccSoftRST();
            break;
        }
        case 0x03:
        {
            TestClrMemEccWDTRST();
            break;
        }
        case 0x04:
        {
            TestOnlyClrMemEcc();
            break;
        }
        case 0x05:
        {
            TestSoftRST();
            break;
        }
        case 0x06:
        {
            TestWDTRST();
            break;
        }
        case 0x07:
        {
            TestUpdateRST();
            break;
        }

        case 0x08:
        {
            TestChangeEcc1();
            break;
        }
        case 0x09:
        {
            TestChangeEcc2();
            break;
        }
        case 0x0A:
        {
            TestClrLen();
            break;
        }
        case 0x0B:
        {
            TestMaxLen();
            break;
        }
        case 0x0C:
        {
            TestChangeLen();
            break;
        }
        case 0x0D:
        {
            TestLoadCnt();
            break;
        }
        default:
            break;
    }
}
#endif

