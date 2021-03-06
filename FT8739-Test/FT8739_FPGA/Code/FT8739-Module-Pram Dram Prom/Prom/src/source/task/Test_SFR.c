/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_SFR.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-23
*
*  Abstract:
*
* Reference:
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_SFR.h"

#if _TEST_SFR_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT8 XRAM g_ucSFR[256];

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
UINT8 SFRGetRegMapDataNormal(UINT8 ucAddr)
{
    if (ucAddr < 0x80)
        return 0;
    switch (ucAddr)
    {
        case   0x80:
            return  SFR_80H;
        case   0x81:
            return  SFR_81H;
        case   0x82:
            return  SFR_82H;
        case   0x83:
            return  SFR_83H;
        case   0x84:
            return  SFR_84H;
        case   0x85:
            return  SFR_85H;
        case   0x86:
            return  SFR_86H;
        case   0x87:
            return  SFR_87H;
        case   0x88:
            return  SFR_88H;
        case   0x89:
            return  SFR_89H;
        case   0x8A:
            return  SFR_8AH;
        case   0x8B:
            return  SFR_8BH;
        case   0x8C:
            return  SFR_8CH;
        case   0x8D:
            return  SFR_8DH;
        case   0x8E:
            return  SFR_8EH;
        case   0x8F:
            return  SFR_8FH;
        case   0x90:
            return  SFR_90H;
        case   0x91:
            return  SFR_91H;
        case   0x92:
            return  SFR_92H;
        case   0x93:
            return  SFR_93H;
        case   0x94:
            return  SFR_94H;
        case   0x95:
            return  SFR_95H;
        case   0x96:
            return  SFR_96H;
        case   0x97:
            return  SFR_97H;
        case   0x98:
            return  SFR_98H;
        case   0x99:
            return  SFR_99H;
        case   0x9A:
            return  SFR_9AH;
        case   0x9B:
            return  SFR_9BH;
        case   0x9C:
            return  SFR_9CH;
        case   0x9D:
            return  SFR_9DH;
        case   0x9E:
            return  SFR_9EH;
        case   0x9F:
            return  SFR_9FH;
        case   0xA0:
            return  SFR_A0H;
        case   0xA1:
            return  SFR_A1H;
        case   0xA2:
            return  SFR_A2H;
        case   0xA3:
            return  SFR_A3H;
        case   0xA4:
            return  SFR_A4H;
        case   0xA5:
            return  SFR_A5H;
        case   0xA6:
            return  SFR_A6H;
        case   0xA7:
            return  SFR_A7H;
        case   0xA8:
            return  SFR_A8H;
        case   0xA9:
            return  SFR_A9H;
        case   0xAA:
            return  SFR_AAH;
        case   0xAB:
            return  SFR_ABH;
        case   0xAC:
            return  SFR_ACH;
        case   0xAD:
            return  SFR_ADH;
        case   0xAE:
            return  SFR_AEH;
        case   0xAF:
            return  SFR_AFH;
        case   0xB0:
            return  SFR_B0H;
        case   0xB1:
            return  SFR_B1H;
        case   0xB2:
            return  SFR_B2H;
        case   0xB3:
            return  SFR_B3H;
        case   0xB4:
            return  SFR_B4H;
        case   0xB5:
            return  SFR_B5H;
        case   0xB6:
            return  SFR_B6H;
        case   0xB7:
            return  SFR_B7H;
        case   0xB8:
            return  SFR_B8H;
        case   0xB9:
            return  SFR_B9H;
        case   0xBA:
            return  SFR_BAH;
        case   0xBB:
            return  SFR_BBH;
        case   0xBC:
            return  SFR_BCH;
        case   0xBD:
            return  SFR_BDH;
        case   0xBE:
            return  SFR_BEH;
        case   0xBF:
            return  SFR_BFH;
        case   0xC0:
            return  SFR_C0H;
        case   0xC1:
            return  SFR_C1H;
        case   0xC2:
            return  SFR_C2H;
        case   0xC3:
            return  SFR_C3H;
        case   0xC4:
            return  SFR_C4H;
        case   0xC5:
            return  SFR_C5H;
        case   0xC6:
            return  SFR_C6H;
        case   0xC7:
            return  SFR_C7H;
        case   0xC8:
            return  SFR_C8H;
        case   0xC9:
            return  SFR_C9H;
        case   0xCA:
            return  SFR_CAH;
        case   0xCB:
            return  SFR_CBH;
        case   0xCC:
            return  SFR_CCH;
        case   0xCD:
            return  SFR_CDH;
        case   0xCE:
            return  SFR_CEH;
        case   0xCF:
            return  SFR_CFH;
        case   0xD0:
            return  SFR_D0H;
        case   0xD1:
            return  SFR_D1H;
        case   0xD2:
            return  SFR_D2H;
        case   0xD3:
            return  SFR_D3H;
        case   0xD4:
            return  SFR_D4H;
        case   0xD5:
            return  SFR_D5H;
        case   0xD6:
            return  SFR_D6H;
        case   0xD7:
            return  SFR_D7H;
        case   0xD8:
            return  SFR_D8H;
        case   0xD9:
            return  SFR_D9H;
        case   0xDA:
            return  SFR_DAH;
        case   0xDB:
            return  SFR_DBH;
        case   0xDC:
            return  SFR_DCH;
        case   0xDD:
            return  SFR_DDH;
        case   0xDE:
            return  SFR_DEH;
        case   0xDF:
            return  SFR_DFH;
        case   0xE0:
            return  SFR_E0H;
        case   0xE1:
            return  SFR_E1H;
        case   0xE2:
            return  SFR_E2H;
        case   0xE3:
            return  SFR_E3H;
        case   0xE4:
            return  SFR_E4H;
        case   0xE5:
            return  SFR_E5H;
        case   0xE6:
            return  SFR_E6H;
        case   0xE7:
            return  SFR_E7H;
        case   0xE8:
            return  SFR_E8H;
        case   0xE9:
            return  SFR_E9H;
        case   0xEA:
            return  SFR_EAH;
        case   0xEB:
            return  SFR_EBH;
        case   0xEC:
            return  SFR_ECH;
        case   0xED:
            return  SFR_EDH;
        case   0xEE:
            return  SFR_EEH;
        case   0xEF:
            return  SFR_EFH;
        case   0xF0:
            return  SFR_F0H;
        case   0xF1:
            return  SFR_F1H;
        case   0xF2:
            return  SFR_F2H;
        case   0xF3:
            return  SFR_F3H;
        case   0xF4:
            return  SFR_F4H;
        case   0xF5:
            return  SFR_F5H;
        case   0xF6:
            return  SFR_F6H;
        case   0xF7:
            return  SFR_F7H;
        case   0xF8:
            return  SFR_F8H;
        case   0xF9:
            return  SFR_F9H;
        case   0xFA:
            return  SFR_FAH;
        case   0xFB:
            return  SFR_FBH;
        case   0xFC:
            return  SFR_FCH;
        case   0xFD:
            return  SFR_FDH;
        case   0xFE:
            return  SFR_FEH;
        case   0xFF:
            return  SFR_FFH;
        default:
            return 0;
    }
}


/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void SFRWriteRegMapDataNormal(UINT8 ucAddr,  UINT8 ucData)
{
    if (ucAddr < 0x80)
        return;
    switch (ucAddr)
    {
        case 0x80:
            SFR_80H = ucData;
            break;
        case 0x81:
            SFR_81H = ucData;
            break;
        case 0x82:
            SFR_82H = ucData;
            break;
        case 0x83:
            SFR_83H = ucData;
            break;
        case 0x84:
            SFR_84H = ucData;
            break;
        case 0x85:
            SFR_85H = ucData;
            break;
        case 0x86:
            SFR_86H = ucData;
            break;
        case 0x87:
            SFR_87H = ucData;
            break;
        case 0x88:
            SFR_88H = ucData;
            break;
        case 0x89:
            SFR_89H = ucData;
            break;
        case 0x8A:
            SFR_8AH = ucData;
            break;
        case 0x8B:
            SFR_8BH = ucData;
            break;
        case 0x8C:
            SFR_8CH = ucData;
            break;
        case 0x8D:
            SFR_8DH = ucData;
            break;
        case 0x8E:
            SFR_8EH = ucData;
            break;
        case 0x8F:
            SFR_8FH = ucData;
            break;
        case 0x90:
            SFR_90H = ucData;
            break;
        case 0x91:
            SFR_91H = ucData;
            break;
        case 0x92:
            SFR_92H = ucData;
            break;
        case 0x93:
            SFR_93H = ucData;
            break;
        case 0x94:
            SFR_94H = ucData;
            break;
        case 0x95:
            SFR_95H = ucData;
            break;
        case 0x96:
            SFR_96H = ucData;
            break;
        case 0x97:
            SFR_97H = ucData;
            break;
        case 0x98:
            SFR_98H = ucData;
            break;
        case 0x99:
            SFR_99H = ucData;
            break;
        case 0x9A:
            SFR_9AH = ucData;
            break;
        case 0x9B:
            SFR_9BH = ucData;
            break;
        case 0x9C:
            SFR_9CH = ucData;
            break;
        case 0x9D:
            SFR_9DH = ucData;
            break;
        case 0x9E:
            SFR_9EH = ucData;
            break;
        case 0x9F:
            SFR_9FH = ucData;
            break;
        case 0xA0:
            SFR_A0H = ucData;
            break;
        case 0xA1:
            SFR_A1H = ucData;
            break;
        case 0xA2:
            SFR_A2H = ucData;
            break;
        case 0xA3:
            SFR_A3H = ucData;
            break;
        case 0xA4:
            SFR_A4H = ucData;
            break;
        case 0xA5:
            SFR_A5H = ucData;
            break;
        case 0xA6:
            SFR_A6H = ucData;
            break;
        case 0xA7:
            SFR_A7H = ucData;
            break;
        case 0xA8:
            SFR_A8H = ucData;
            break;
        case 0xA9:
            SFR_A9H = ucData;
            break;
        case 0xAA:
            SFR_AAH = ucData;
            break;
        case 0xAB:
            SFR_ABH = ucData;
            break;
        case 0xAC:
            SFR_ACH = ucData;
            break;
        case 0xAD:
            SFR_ADH = ucData;
            break;
        case 0xAE:
            SFR_AEH = ucData;
            break;
        case 0xAF:
            SFR_AFH = ucData;
            break;
        case 0xB0:
            SFR_B0H = ucData;
            break;
        case 0xB1:
            SFR_B1H = ucData;
            break;
        case 0xB2:
            SFR_B2H = ucData;
            break;
        case 0xB3:
            SFR_B3H = ucData;
            break;
        case 0xB4:
            SFR_B4H = ucData;
            break;
        case 0xB5:
            SFR_B5H = ucData;
            break;
        case 0xB6:
            SFR_B6H = ucData;
            break;
        case 0xB7:
            SFR_B7H = ucData;
            break;
        case 0xB8:
            SFR_B8H = ucData;
            break;
        case 0xB9:
            SFR_B9H = ucData;
            break;
        case 0xBA:
            SFR_BAH = ucData;
            break;
        case 0xBB:
            SFR_BBH = ucData;
            break;
        case 0xBC:
            SFR_BCH = ucData;
            break;
        case 0xBD:
            SFR_BDH = ucData;
            break;
        case 0xBE:
            SFR_BEH = ucData;
            break;
        case 0xBF:
            SFR_BFH = ucData;
            break;
        case 0xC0:
            SFR_C0H = ucData;
            break;
        case 0xC1:
            SFR_C1H = ucData;
            break;
        case 0xC2:
            SFR_C2H = ucData;
            break;
        case 0xC3:
            SFR_C3H = ucData;
            break;
        case 0xC4:
            SFR_C4H = ucData;
            break;
        case 0xC5:
            SFR_C5H = ucData;
            break;
        case 0xC6:
            SFR_C6H = ucData;
            break;
        case 0xC7:
            SFR_C7H = ucData;
            break;
        case 0xC8:
            SFR_C8H = ucData;
            break;
        case 0xC9:
            SFR_C9H = ucData;
            break;
        case 0xCA:
            SFR_CAH = ucData;
            break;
        case 0xCB:
            SFR_CBH = ucData;
            break;
        case 0xCC:
            SFR_CCH = ucData;
            break;
        case 0xCD:
            SFR_CDH = ucData;
            break;
        case 0xCE:
            SFR_CEH = ucData;
            break;
        case 0xCF:
            SFR_CFH = ucData;
            break;
        case 0xD0:
            SFR_D0H = ucData;
            break;
        case 0xD1:
            SFR_D1H = ucData;
            break;
        case 0xD2:
            SFR_D2H = ucData;
            break;
        case 0xD3:
            SFR_D3H = ucData;
            break;
        case 0xD4:
            SFR_D4H = ucData;
            break;
        case 0xD5:
            SFR_D5H = ucData;
            break;
        case 0xD6:
            SFR_D6H = ucData;
            break;
        case 0xD7:
            SFR_D7H = ucData;
            break;
        case 0xD8:
            SFR_D8H = ucData;
            break;
        case 0xD9:
            SFR_D9H = ucData;
            break;
        case 0xDA:
            SFR_DAH = ucData;
            break;
        case 0xDB:
            SFR_DBH = ucData;
            break;
        case 0xDC:
            SFR_DCH = ucData;
            break;
        case 0xDD:
            SFR_DDH = ucData;
            break;
        case 0xDE:
            SFR_DEH = ucData;
            break;
        case 0xDF:
            SFR_DFH = ucData;
            break;
        case 0xE0:
            SFR_E0H = ucData;
            break;
        case 0xE1:
            SFR_E1H = ucData;
            break;
        case 0xE2:
            SFR_E2H = ucData;
            break;
        case 0xE3:
            SFR_E3H = ucData;
            break;
        case 0xE4:
            SFR_E4H = ucData;
            break;
        case 0xE5:
            SFR_E5H = ucData;
            break;
        case 0xE6:
            SFR_E6H = ucData;
            break;
        case 0xE7:
            SFR_E7H = ucData;
            break;
        case 0xE8:
            SFR_E8H = ucData;
            break;
        case 0xE9:
            SFR_E9H = ucData;
            break;
        case 0xEA:
            SFR_EAH = ucData;
            break;
        case 0xEB:
            SFR_EBH = ucData;
            break;
        case 0xEC:
            SFR_ECH = ucData;
            break;
        case 0xED:
            SFR_EDH = ucData;
            break;
        case 0xEE:
            SFR_EEH = ucData;
            break;
        case 0xEF:
            SFR_EFH = ucData;
            break;
        case 0xF0:
            SFR_F0H = ucData;
            break;
        case 0xF1:
            SFR_F1H = ucData;
            break;
        case 0xF2:
            SFR_F2H = ucData;
            break;
        case 0xF3:
            SFR_F3H = ucData;
            break;
        case 0xF4:
            SFR_F4H = ucData;
            break;
        case 0xF5:
            SFR_F5H = ucData;
            break;
        case 0xF6:
            SFR_F6H = ucData;
            break;
        case 0xF7:
            SFR_F7H = ucData;
            break;
        case 0xF8:
            SFR_F8H = ucData;
            break;
        case 0xF9:
            SFR_F9H = ucData;
            break;
        case 0xFA:
            SFR_FAH = ucData;
            break;
        case 0xFB:
            SFR_FBH = ucData;
            break;
        case 0xFC:
            SFR_FCH = ucData;
            break;
        case 0xFD:
            SFR_FDH = ucData;
            break;
        case 0xFE:
            SFR_FEH = ucData;
            break;
        case 0xFF:
            SFR_FFH = ucData;
            break;
        default:
            break;
    }
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_WriteSFR(UINT8 addr,UINT8 mask0,UINT8 mask1)
{
    UINT8 tmp;
    UINT8 cnt_back;
    UINT16 cnt;
    UINT8 BackUp;
    BOOLEAN flag;
    flag = 1;
    BackUp = SFRGetRegMapDataNormal(addr);
    for (cnt = 0; cnt < 0x100; cnt++)
    {
        cnt_back = cnt;
        cnt &= mask0;
        cnt |= mask1;

        SFRWriteRegMapDataNormal(addr,(UINT8)cnt);
        tmp = SFRGetRegMapDataNormal(addr);
        if (tmp != cnt)
        {
            SFRWriteRegMapDataNormal(addr,BackUp);
            DelayMs(10);
            DBG_ERROR("\n\rSFR_%02X,write:%02X,read:%02X",addr,cnt,tmp);
            flag = 0;
            break;
        }
        cnt = cnt_back;
    }
    SFRWriteRegMapDataNormal(addr,BackUp);
    if (flag)
    {
        DelayMs(10);
        DBG_SFR("\n\rSFR_%02X write ok!",addr);
    }
    DelayMs(10);
}


/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_WriteCGU0(UINT8 addr,UINT8 mask0,UINT8 mask1)
{
    UINT8 tmp;
    UINT8 cnt_back;
    UINT16 cnt;
    UINT8 BackUp;
    BOOLEAN flag;
    flag = 1;
    BackUp = SFRGetRegMapDataNormal(0xC9);
    for (cnt = 0; cnt < 0x100; cnt++)
    {
        cnt_back = cnt;
        cnt &= mask0;
        cnt |= mask1;
        CLK_WP = 1;
        SFRWriteRegMapDataNormal(0xC9,(UINT8)cnt);
        tmp = SFRGetRegMapDataNormal(0xC9);
        if (tmp != cnt)
        {
            SFRWriteRegMapDataNormal(0xC9,BackUp);
            DelayMs(10);
            DBG_ERROR("\n\rSFR_%02X,write:%02X,read:%02X",0xC9,cnt,tmp);
            flag = 0;
            break;
        }
        cnt = cnt_back;
    }
    SFRWriteRegMapDataNormal(0xC9,BackUp);
    if (flag)
    {
        DelayMs(10);
        DBG_SFR("\n\rSFR_%02X write ok!",0xC9);
    }
    DelayMs(10);
}


/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_SFR()
{
    UINT8 i;
    //read default value
    DBG_MODE("\n\rSFR read test");
    for (i = 0x80; i < 0xff; i++)
    {
        DBG_SFR("\n\rSFR_%02X = %02X",i,g_ucSFR[i]);
    }
    DBG_SFR("\n\rSFR_%02X = %02X",0xFF,g_ucSFR[0xFF]);
    
    DelayMs(100);
    DBG_MODE("\n\rSFR Write test");

    DBG_SFR("\n\r\n\rSSCG:");
    Test_WriteSFR(0xF5,0x33,0x00);//SSCGCON
    Test_WriteSFR(0xF6,0xFF,0x00);//SSCGCON1  

    DBG_SFR("\n\r\n\rSPI0:");
    Test_WriteSFR(0xA3,0xEF,0x00);//SPI0CON2
    Test_WriteSFR(0xA5,0xCF,0x00);//SPI0CON3
    Test_WriteSFR(0xA6,0xFF,0x00);//SPI0CON4
    
    DBG_SFR("\n\r\n\rSPI1:");
    Test_WriteSFR(0xB3,0x3F,0x00);//SPI1CON
    Test_WriteSFR(0xB4,0xDF,0x00);//SPI1CON2
    //Test_WriteSFR(0xB5,0xFF,0x00);//SPIBUF
    Test_WriteSFR(0xB1,0xF6,0x00);//SPICON3
    Test_WriteSFR(0xB2,0x17,0x00);//SPICON4

    DBG_SFR("\n\r\n\rUart:");
    Test_WriteSFR(0xA9,0xBC,0x00);//UARTCON
    Test_WriteSFR(0xAB,0xFF,0x00);//UARTRELH
    Test_WriteSFR(0xAE,0x03,0x00);//UARTRELH
    Test_WriteSFR(0xAF,0xFF,0x00);//UARTSDA

    DBG_SFR("\n\r\n\rRTC:");
    Test_WriteSFR(0x9C,0xFF,0x00);//RTCIVL
    Test_WriteSFR(0x9D,0xFF,0x00);//RTCIVH        
    Test_WriteSFR(0x9E,0x47,0x00);//RTCCON
    Test_WriteSFR(0xB6,0x07,0x00);//RTCCON1
    
    DBG_SFR("\n\nSystem:");
    Test_WriteSFR(0x98,0xCC,0x80);//SYS_CON
    Test_WriteSFR(0xE6,0xFF,0x00);//PORSTA
    Test_WriteSFR(0xE7,0xFF,0x00);//RSTSTA
    //Test_WriteSFR(0xE9,0xF0,0x0F);//SFTRST   
    Test_WriteSFR(0xEA,0xFF,0x00);//ANA_CON
    Test_WriteSFR(0xEB,0xFF,0x00);//POMOD
    Test_WriteSFR(0xEC,0xFF,0x00);//P0DIR
    Test_WriteSFR(0xED,0xFF,0x00);//P1MOD
    Test_WriteSFR(0xEE,0xFF,0x00);//P1DIR
    //Test_WriteSFR(0xEF,0xFF,0x00);//XDP_STA      RO    
    Test_WriteSFR(0xE1,0xFF,0x00);//Test_Con0
    Test_WriteSFR(0xE2,0xFF,0x00);//Test_Con1    
    Test_WriteSFR(0xE3,0xFF,0x00);//Test_Con2
    Test_WriteSFR(0xE4,0xFF,0x00);//Test_Con3
    Test_WriteSFR(0xDA,0x6D,0x00);//dsv_con
    Test_WriteSFR(0xBD,0x3C,0x00);//FT_EN_REG   


    DBG_SFR("\n\r\n\rP0 and P1:");
    Test_WriteSFR(0xAC,0xFF,0x80);//
    Test_WriteSFR(0xAD,0xFF,0x00);
    P0MOD = 0x80;
    P0DIR = 0xFF;
    P1MOD = 0x00;
    P1DIR = 0xFF;
    Test_WriteSFR(0x80,0xFF,0x00);
    Test_WriteSFR(0x94,0xFF,0x00);
    
    DBG_SFR("\n\r\n\rANA_CTRL:");
    Test_WriteSFR(0xC1,0xFF,0x00);//ANACON1
    Test_WriteSFR(0xC2,0xFF,0x00);//ANACON2
    Test_WriteSFR(0xC3,0xFF,0x00);//ANACON3
    Test_WriteSFR(0xC4,0xFF,0x00);//ANACON4
    Test_WriteSFR(0xC5,0xFF,0x00);//ANACON5
    Test_WriteSFR(0xC6,0x7F,0x00);//ANACON6
    Test_WriteSFR(0xC7,0xFF,0x00);//ANACON7 
    Test_WriteSFR(0xA0,0xFF,0x00);//ANACON8
    Test_WriteSFR(0xB0,0xFF,0x00);//ANACON9
    Test_WriteSFR(0xF3,0x07,0x00);//ANACON10    

    DBG_SFR("\n\r\n\rCGU:");
    Test_WriteSFR(0xC8,0xFF,0x00);//CGUCON1

    Test_WriteCGU0(0xC9,0xBF,0x00);//CGUCON0
   
    Test_WriteSFR(0xCA,0xFF,0x00);//CGUCON2
    Test_WriteSFR(0xCB,0xFF,0x00);//CGUCON3
    Test_WriteSFR(0xCC,0xDB,0x01);//CGUCON4
    Test_WriteSFR(0xCD,0xFF,0x00);//CGUCON5
    Test_WriteSFR(0xCE,0x01,0x00);//CGUCON6
    Test_WriteSFR(0xCF,0xFF,0x00);//CGUCON7
    Test_WriteSFR(0xBF,0xFF,0x00);//CGUCON8    
    

    DBG_SFR("\n\r\n\rIIC");
    Test_WriteSFR(0x90,0x33,0x00);//I2CCON
    //Test_WriteSFR(0x92,0xFE,0x00);//I2CADDR  I2CADDR写进去以后读出来是0
    Test_WriteSFR(0x93,0xF7,0x00);//I2CSTOP
    Test_WriteSFR(0x95,0x10,0x00);//I2CSEL
    
    DBG_SFR("\n\r\n\rWDT");
    Test_WriteSFR(0x99,0x03,0x00);//WDTCON    
    Test_WriteSFR(0x9A,0xFF,0x00);//WDTREL

    DBG_SFR("\n\r\n\rTIMER");
    Test_WriteSFR(0x88,0x05,0x00);//TCON    
    Test_WriteSFR(0x89,0x5F,0x00);//TMOD
    //Test_WriteSFR(0x8C,0xFF,0x00);//TH0
    //Test_WriteSFR(0x8A,0xFF,0x00);//TL0     
    //Test_WriteSFR(0x8D,0xFF,0x00);//TH1
    //Test_WriteSFR(0x8B,0xFF,0x00);//TL1
    Test_WriteSFR(0x97,0x07,0x00);//MMCON
    Test_WriteSFR(0x9B,0xC0,0x00);//TDIV    

    //DBG_SFR("\n\r\n\rCOUNTER");
    //Test_WriteSFR(0xBA,0xFF,0x00);//CNTIVL
    //Test_WriteSFR(0xBB,0xFF,0x00);//CNTIVM
    //Test_WriteSFR(0xBC,0xFF,0x00);//CNTIVH

    DBG_SFR("\n\r\n\rLED:");
    Test_WriteSFR(0xFE,0x3F,0x00);//LED_EN_SFR
    Test_WriteSFR(0xFF,0x3F,0x00);//LED_H_NUM_SFR

    DBG_SFR("\n\r\n\rMEMBIST");
    Test_WriteSFR(0xD2,0xFF,0x00);//MEMBIST_EN_ID1
    Test_WriteSFR(0xD3,0x0F,0x00);//MEMBIST_EN_ID2

    DBG_SFR("\n\r\n\rOTHER");
    Test_WriteSFR(0xF8,0x3F,0x00);//AIPL    
    Test_WriteSFR(0xF7,0x3F,0x00);//AIPH
    Test_WriteSFR(0xE8,0x3F,0x00);//AIE   
    //Test_WriteSFR(0xC0,0x3F,0x00);//AIF
    Test_WriteSFR(0xB8,0x3F,0x00);//IPL0
    //Test_WriteSFR(0xBE,0x3F,0x00);//SPH    
    Test_WriteSFR(0xB7,0x3F,0x00);//IPH0  
    Test_WriteSFR(0xA8,0xFF,0x00);//IEN0

    DBG_MODE("\n\rSFR write and read is end!\n");
}
#endif

