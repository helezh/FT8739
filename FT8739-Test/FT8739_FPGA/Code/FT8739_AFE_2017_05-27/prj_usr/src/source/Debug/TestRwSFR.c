/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: TestRwSFR.c
*
*    Author: 
*
*   Created: 2014-05-26
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "TestRwSFR.h"
#include "AppHostComm.h"
#include "DrvSysCtrl.h"


#if _TEST_RW_SFR_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

sfr SFR_80H    =   0x80;      
sfr SFR_81H    =   0x81;  
sfr SFR_82H    =   0x82;   
sfr SFR_83H    =   0x83;   
sfr SFR_84H    =   0x84;    
sfr SFR_85H    =   0x85;    
sfr SFR_86H    =   0x86;
sfr SFR_87H    =   0x87;   
sfr SFR_88H    =   0x88;
sfr SFR_89H    =   0x89;
sfr SFR_8AH    =   0x8A;
sfr SFR_8BH    =   0x8B;
sfr SFR_8CH    =   0x8C;
sfr SFR_8DH    =   0x8D;
sfr SFR_8EH    =   0x8E;
sfr SFR_8FH    =   0x8F;
sfr SFR_90H    =   0x90;
sfr SFR_91H    =   0x91;
sfr SFR_92H    =   0x92;
sfr SFR_93H    =   0x93;
sfr SFR_94H    =   0x94;
sfr SFR_95H    =   0x95;
sfr SFR_96H    =   0x96;
sfr SFR_97H    =   0x97;
sfr SFR_98H    =   0x98;
sfr SFR_99H    =   0x99;
sfr SFR_9AH    =   0x9A;
sfr SFR_9BH    =   0x9B;
sfr SFR_9CH    =   0x9C;
sfr SFR_9DH    =   0x9D;
sfr SFR_9EH    =   0x9E;
sfr SFR_9FH    =   0x9F;
sfr SFR_A0H    =   0xA0;
sfr SFR_A1H    =   0xA1;
sfr SFR_A2H    =   0xA2;
sfr SFR_A3H    =   0xA3;
sfr SFR_A4H    =   0xA4;
sfr SFR_A5H    =   0xA5;
sfr SFR_A6H    =   0xA6;
sfr SFR_A7H    =   0xA7;
sfr SFR_A8H    =   0xA8;
sfr SFR_A9H    =   0xA9;
sfr SFR_AAH    =   0xAA;
sfr SFR_ABH    =   0xAB;
sfr SFR_ACH    =   0xAC;
sfr SFR_ADH    =   0xAD;
sfr SFR_AEH    =   0xAE;
sfr SFR_AFH    =   0xAF;
sfr SFR_B0H    =   0xB0;
sfr SFR_B1H    =   0xB1;
sfr SFR_B2H    =   0xB2;
sfr SFR_B3H    =   0xB3;
sfr SFR_B4H    =   0xB4;
sfr SFR_B5H    =   0xB5;
sfr SFR_B6H    =   0xB6;
sfr SFR_B7H    =   0xB7;
sfr SFR_B8H    =   0xB8;
sfr SFR_B9H    =   0xB9;
sfr SFR_BAH    =   0xBA;
sfr SFR_BBH    =   0xBB;
sfr SFR_BCH    =   0xBC;
sfr SFR_BDH    =   0xBD;
sfr SFR_BEH    =   0xBE;
sfr SFR_BFH    =   0xBF;
sfr SFR_C0H    =   0xC0;
sfr SFR_C1H    =   0xC1;
sfr SFR_C2H    =   0xC2;
sfr SFR_C3H    =   0xC3;
sfr SFR_C4H    =   0xC4;
sfr SFR_C5H    =   0xC5;
sfr SFR_C6H    =   0xC6;
sfr SFR_C7H    =   0xC7;
sfr SFR_C8H    =   0xC8;
sfr SFR_C9H    =   0xC9;
sfr SFR_CAH    =   0xCA;
sfr SFR_CBH    =   0xCB;
sfr SFR_CCH    =   0xCC;
sfr SFR_CDH    =   0xCD;
sfr SFR_CEH    =   0xCE;
sfr SFR_CFH    =   0xCF;
sfr SFR_D0H    =   0xD0;
sfr SFR_D1H    =   0xD1;
sfr SFR_D2H    =   0xD2;
sfr SFR_D3H    =   0xD3;
sfr SFR_D4H    =   0xD4;
sfr SFR_D5H    =   0xD5;
sfr SFR_D6H    =   0xD6;
sfr SFR_D7H    =   0xD7;
sfr SFR_D8H    =   0xD8;
sfr SFR_D9H    =   0xD9;
sfr SFR_DAH    =   0xDA;
sfr SFR_DBH    =   0xDB;
sfr SFR_DCH    =   0xDC;
sfr SFR_DDH    =   0xDD;
sfr SFR_DEH    =   0xDE;
sfr SFR_DFH    =   0xDF;
sfr SFR_E0H    =   0xE0;
sfr SFR_E1H    =   0xE1;
sfr SFR_E2H    =   0xE2;
sfr SFR_E3H    =   0xE3;
sfr SFR_E4H    =   0xE4;
sfr SFR_E5H    =   0xE5;
sfr SFR_E6H    =   0xE6;
sfr SFR_E7H    =   0xE7;
sfr SFR_E8H    =   0xE8;
sfr SFR_E9H    =   0xE9;
sfr SFR_EAH    =   0xEA;
sfr SFR_EBH    =   0xEB;
sfr SFR_ECH    =   0xEC;
sfr SFR_EDH    =   0xED;
sfr SFR_EEH    =   0xEE;
sfr SFR_EFH    =   0xEF;
sfr SFR_F0H    =   0xF0;
sfr SFR_F1H    =   0xF1;
sfr SFR_F2H    =   0xF2;
sfr SFR_F3H    =   0xF3;
sfr SFR_F4H    =   0xF4;
sfr SFR_F5H    =   0xF5;
sfr SFR_F6H    =   0xF6;
sfr SFR_F7H    =   0xF7;
sfr SFR_F8H    =   0xF8;
sfr SFR_F9H    =   0xF9;
sfr SFR_FAH    =   0xFA;
sfr SFR_FBH    =   0xFB;
sfr SFR_FCH    =   0xFC;
sfr SFR_FDH    =   0xFD;
sfr SFR_FEH    =   0xFE;
sfr SFR_FFH    =   0xFF;


/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
extern void AppHostUpdateHeadState(UINT8 NewRegHeader);

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


/*******************************************************************************
*   Name: SFR_Read
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
UINT8 SFR_Read(UINT8 ucAddr)
{     
    if(ucAddr < 0x80)
    {
        return 0;
    }

    switch(ucAddr)
    {
        case   0x80:   return  SFR_80H;  
        case   0x81:   return  SFR_81H;  
        case   0x82:   return  SFR_82H;  
        case   0x83:   return  SFR_83H;  
        case   0x84:   return  SFR_84H;  
        case   0x85:   return  SFR_85H;  
        case   0x86:   return  SFR_86H;  
        case   0x87:   return  SFR_87H;  
        case   0x88:   return  SFR_88H;  
        case   0x89:   return  SFR_89H;  
        case   0x8A:   return  SFR_8AH;  
        case   0x8B:   return  SFR_8BH;  
        case   0x8C:   return  SFR_8CH;  
        case   0x8D:   return  SFR_8DH;  
        case   0x8E:   return  SFR_8EH;  
        case   0x8F:   return  SFR_8FH;  
        case   0x90:   return  SFR_90H;  
        case   0x91:   return  SFR_91H;  
        case   0x92:   return  SFR_92H;  
        case   0x93:   return  SFR_93H;  
        case   0x94:   return  SFR_94H;  
        case   0x95:   return  SFR_95H;  
        case   0x96:   return  SFR_96H;  
        case   0x97:   return  SFR_97H;  
        case   0x98:   return  SFR_98H;  
        case   0x99:   return  SFR_99H;  
        case   0x9A:   return  SFR_9AH;  
        case   0x9B:   return  SFR_9BH;  
        case   0x9C:   return  SFR_9CH;  
        case   0x9D:   return  SFR_9DH;  
        case   0x9E:   return  SFR_9EH;  
        case   0x9F:   return  SFR_9FH;  
        case   0xA0:   return  SFR_A0H;  
        case   0xA1:   return  SFR_A1H;  
        case   0xA2:   return  SFR_A2H;  
        case   0xA3:   return  SFR_A3H;  
        case   0xA4:   return  SFR_A4H;  
        case   0xA5:   return  SFR_A5H;  
        case   0xA6:   return  SFR_A6H;  
        case   0xA7:   return  SFR_A7H;  
        case   0xA8:   return  SFR_A8H;  
        case   0xA9:   return  SFR_A9H;  
        case   0xAA:   return  SFR_AAH;  
        case   0xAB:   return  SFR_ABH;  
        case   0xAC:   return  SFR_ACH;  
        case   0xAD:   return  SFR_ADH;  
        case   0xAE:   return  SFR_AEH;  
        case   0xAF:   return  SFR_AFH;  
        case   0xB0:   return  SFR_B0H;  
        case   0xB1:   return  SFR_B1H;  
        case   0xB2:   return  SFR_B2H;  
        case   0xB3:   return  SFR_B3H;  
        case   0xB4:   return  SFR_B4H;  
        case   0xB5:   return  SFR_B5H;  
        case   0xB6:   return  SFR_B6H;  
        case   0xB7:   return  SFR_B7H;  
        case   0xB8:   return  SFR_B8H;  
        case   0xB9:   return  SFR_B9H;  
        case   0xBA:   return  SFR_BAH;  
        case   0xBB:   return  SFR_BBH;  
        case   0xBC:   return  SFR_BCH;  
        case   0xBD:   return  SFR_BDH;  
        case   0xBE:   return  SFR_BEH;  
        case   0xBF:   return  SFR_BFH;  
        case   0xC0:   return  SFR_C0H;  
        case   0xC1:   return  SFR_C1H;  
        case   0xC2:   return  SFR_C2H;  
        case   0xC3:   return  SFR_C3H;  
        case   0xC4:   return  SFR_C4H;  
        case   0xC5:   return  SFR_C5H;  
        case   0xC6:   return  SFR_C6H;  
        case   0xC7:   return  SFR_C7H;  
        case   0xC8:   return  SFR_C8H;  
        case   0xC9:   return  SFR_C9H;  
        case   0xCA:   return  SFR_CAH;  
        case   0xCB:   return  SFR_CBH;  
        case   0xCC:   return  SFR_CCH;  
        case   0xCD:   return  SFR_CDH;  
        case   0xCE:   return  SFR_CEH;  
        case   0xCF:   return  SFR_CFH;  
        case   0xD0:   return  SFR_D0H;  
        case   0xD1:   return  SFR_D1H;  
        case   0xD2:   return  SFR_D2H;  
        case   0xD3:   return  SFR_D3H;  
        case   0xD4:   return  SFR_D4H;  
        case   0xD5:   return  SFR_D5H;  
        case   0xD6:   return  SFR_D6H;  
        case   0xD7:   return  SFR_D7H;  
        case   0xD8:   return  SFR_D8H;  
        case   0xD9:   return  SFR_D9H;  
        case   0xDA:   return  SFR_DAH;  
        case   0xDB:   return  SFR_DBH;  
        case   0xDC:   return  SFR_DCH;  
        case   0xDD:   return  SFR_DDH;  
        case   0xDE:   return  SFR_DEH;  
        case   0xDF:   return  SFR_DFH;  
        case   0xE0:   return  SFR_E0H;  
        case   0xE1:   return  SFR_E1H;  
        case   0xE2:   return  SFR_E2H;  
        case   0xE3:   return  SFR_E3H;  
        case   0xE4:   return  SFR_E4H;  
        case   0xE5:   return  SFR_E5H;  
        case   0xE6:   return  SFR_E6H;  
        case   0xE7:   return  SFR_E7H;  
        case   0xE8:   return  SFR_E8H;  
        case   0xE9:   return  SFR_E9H;  
        case   0xEA:   return  SFR_EAH;  
        case   0xEB:   return  SFR_EBH;  
        case   0xEC:   return  SFR_ECH;  
        case   0xED:   return  SFR_EDH;  
        case   0xEE:   return  SFR_EEH;  
        case   0xEF:   return  SFR_EFH;  
        case   0xF0:   return  SFR_F0H;  
        case   0xF1:   return  SFR_F1H;  
        case   0xF2:   return  SFR_F2H;  
        case   0xF3:   return  SFR_F3H;  
        case   0xF4:   return  SFR_F4H;  
        case   0xF5:   return  SFR_F5H;  
        case   0xF6:   return  SFR_F6H;  
        case   0xF7:   return  SFR_F7H;  
        case   0xF8:   return  SFR_F8H;  
        case   0xF9:   return  SFR_F9H;  
        case   0xFA:   return  SFR_FAH;  
        case   0xFB:   return  SFR_FBH;  
        case   0xFC:   return  SFR_FCH;  
        case   0xFD:   return  SFR_FDH;  
        case   0xFE:   return  SFR_FEH;  
        case   0xFF:   return  SFR_FFH;  
        default:
        return 0;
    }    
}


/*******************************************************************************
*   Name: SFR_Write
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void SFR_Write(UINT8 ucAddr,  UINT8 ucData)
{
    if(ucAddr < 0x80)
    {
        return;
    }
    
    switch(ucAddr)
    {
        case 0x80:     SFR_80H = ucData; break;    
        case 0x81:     SFR_81H = ucData; break;    
        case 0x82:     SFR_82H = ucData; break;    
        case 0x83:     SFR_83H = ucData; break;    
        case 0x84:     SFR_84H = ucData; break;    
        case 0x85:     SFR_85H = ucData; break;    
        case 0x86:     SFR_86H = ucData; break;    
        case 0x87:     SFR_87H = ucData; break;    
        case 0x88:     SFR_88H = ucData; break;    
        case 0x89:     SFR_89H = ucData; break;    
        case 0x8A:     SFR_8AH = ucData; break;    
        case 0x8B:     SFR_8BH = ucData; break;    
        case 0x8C:     SFR_8CH = ucData; break;    
        case 0x8D:     SFR_8DH = ucData; break;    
        case 0x8E:     SFR_8EH = ucData; break;    
        case 0x8F:     SFR_8FH = ucData; break;    
        case 0x90:     SFR_90H = ucData; break;    
        case 0x91:     SFR_91H = ucData; break;    
        case 0x92:     SFR_92H = ucData; break;    
        case 0x93:     SFR_93H = ucData; break;    
        case 0x94:     SFR_94H = ucData; break;    
        case 0x95:     SFR_95H = ucData; break;    
        case 0x96:     SFR_96H = ucData; break;    
        case 0x97:     SFR_97H = ucData; break;    
        case 0x98:     SFR_98H = ucData; break;    
        case 0x99:     SFR_99H = ucData; break;    
        case 0x9A:     SFR_9AH = ucData; break;    
        case 0x9B:     SFR_9BH = ucData; break;    
        case 0x9C:     SFR_9CH = ucData; break;    
        case 0x9D:     SFR_9DH = ucData; break;    
        case 0x9E:     SFR_9EH = ucData; break;    
        case 0x9F:     SFR_9FH = ucData; break;    
        case 0xA0:     SFR_A0H = ucData; break;    
        case 0xA1:     SFR_A1H = ucData; break;    
        case 0xA2:     SFR_A2H = ucData; break;    
        case 0xA3:     SFR_A3H = ucData; break;    
        case 0xA4:     SFR_A4H = ucData; break;    
        case 0xA5:     SFR_A5H = ucData; break;    
        case 0xA6:     SFR_A6H = ucData; break;    
        case 0xA7:     SFR_A7H = ucData; break;    
        case 0xA8:     SFR_A8H = ucData; break;    
        case 0xA9:     SFR_A9H = ucData; break;    
        case 0xAA:     SFR_AAH = ucData; break;    
        case 0xAB:     SFR_ABH = ucData; break;    
        case 0xAC:     SFR_ACH = ucData; break;    
        case 0xAD:     SFR_ADH = ucData; break;    
        case 0xAE:     SFR_AEH = ucData; break;    
        case 0xAF:     SFR_AFH = ucData; break;    
        case 0xB0:     SFR_B0H = ucData; break;    
        case 0xB1:     SFR_B1H = ucData; break;    
        case 0xB2:     SFR_B2H = ucData; break;    
        case 0xB3:     SFR_B3H = ucData; break;    
        case 0xB4:     SFR_B4H = ucData; break;    
        case 0xB5:     SFR_B5H = ucData; break;    
        case 0xB6:     SFR_B6H = ucData; break;    
        case 0xB7:     SFR_B7H = ucData; break;    
        case 0xB8:     SFR_B8H = ucData; break;    
        case 0xB9:     SFR_B9H = ucData; break;    
        case 0xBA:     SFR_BAH = ucData; break;    
        case 0xBB:     SFR_BBH = ucData; break;    
        case 0xBC:     SFR_BCH = ucData; break;    
        case 0xBD:     SFR_BDH = ucData; break;    
        case 0xBE:     SFR_BEH = ucData; break;    
        case 0xBF:     SFR_BFH = ucData; break;    
        case 0xC0:     SFR_C0H = ucData; break;    
        case 0xC1:     SFR_C1H = ucData; break;    
        case 0xC2:     SFR_C2H = ucData; break;    
        case 0xC3:     SFR_C3H = ucData; break;    
        case 0xC4:     SFR_C4H = ucData; break;    
        case 0xC5:     SFR_C5H = ucData; break;    
        case 0xC6:     SFR_C6H = ucData; break;    
        case 0xC7:     SFR_C7H = ucData; break;    
        case 0xC8:     SFR_C8H = ucData; break;    
        case 0xC9:     SFR_C9H = ucData; break;    
        case 0xCA:     SFR_CAH = ucData; break;    
        case 0xCB:     SFR_CBH = ucData; break;    
        case 0xCC:     SFR_CCH = ucData; break;    
        case 0xCD:     SFR_CDH = ucData; break;    
        case 0xCE:     SFR_CEH = ucData; break;    
        case 0xCF:     SFR_CFH = ucData; break;    
        case 0xD0:     SFR_D0H = ucData; break;    
        case 0xD1:     SFR_D1H = ucData; break;    
        case 0xD2:     SFR_D2H = ucData; break;    
        case 0xD3:     SFR_D3H = ucData; break;    
        case 0xD4:     SFR_D4H = ucData; break;    
        case 0xD5:     SFR_D5H = ucData; break;    
        case 0xD6:     SFR_D6H = ucData; break;    
        case 0xD7:     SFR_D7H = ucData; break;    
        case 0xD8:     SFR_D8H = ucData; break;    
        case 0xD9:     SFR_D9H = ucData; break;    
        case 0xDA:     SFR_DAH = ucData; break;    
        case 0xDB:     SFR_DBH = ucData; break;    
        case 0xDC:     SFR_DCH = ucData; break;    
        case 0xDD:     SFR_DDH = ucData; break;    
        case 0xDE:     SFR_DEH = ucData; break;    
        case 0xDF:     SFR_DFH = ucData; break;    
        case 0xE0:     SFR_E0H = ucData; break;    
        case 0xE1:     SFR_E1H = ucData; break;    
        case 0xE2:     SFR_E2H = ucData; break;    
        case 0xE3:     SFR_E3H = ucData; break;    
        case 0xE4:     SFR_E4H = ucData; break;    
        case 0xE5:     SFR_E5H = ucData; break;    
        case 0xE6:     SFR_E6H = ucData; break;    
        case 0xE7:     SFR_E7H = ucData; break;    
        case 0xE8:     SFR_E8H = ucData; break;    
        case 0xE9:     SFR_E9H = ucData; break;    
        case 0xEA:     SFR_EAH = ucData; break;    
        case 0xEB:     SFR_EBH = ucData; break;    
        case 0xEC:     SFR_ECH = ucData; break;    
        case 0xED:     SFR_EDH = ucData; break;    
        case 0xEE:     SFR_EEH = ucData; break;    
        case 0xEF:     SFR_EFH = ucData; break;    
        case 0xF0:     SFR_F0H = ucData; break;    
        case 0xF1:     SFR_F1H = ucData; break;    
        case 0xF2:     SFR_F2H = ucData; break;    
        case 0xF3:     SFR_F3H = ucData; break;    
        case 0xF4:     SFR_F4H = ucData; break;    
        case 0xF5:     SFR_F5H = ucData; break;    
        case 0xF6:     SFR_F6H = ucData; break;    
        case 0xF7:     SFR_F7H = ucData; break;    
        case 0xF8:     SFR_F8H = ucData; break;    
        case 0xF9:     SFR_F9H = ucData; break;    
        case 0xFA:     SFR_FAH = ucData; break;    
        case 0xFB:     SFR_FBH = ucData; break;    
        case 0xFC:     SFR_FCH = ucData; break;    
        case 0xFD:     SFR_FDH = ucData; break;    
        case 0xFE:     SFR_FEH = ucData; break;    
        case 0xFF:     SFR_FFH = ucData; break;    
        default: break;
    }
}

/*******************************************************************************
*   Name: AppWriteSFR
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void AppWriteSFR(UINT8 ucAddr, UINT8 ucData)
{
    if (ucAddr == 0x00)
    {
        AppHostUpdateHeadState(ucData);
    }
    else if (ucAddr >= ID_G_SFR_80)
    {
        SFR_Write(ucAddr,ucData);
    } 

    DBG_SFR("\nREG:%02x", ucData);    
}

/*******************************************************************************
*   Name: AppReadSFR
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
UINT8 AppReadSFR(UINT8 ucAddr)
{
    UINT8 ch = 0xFF;

    if (ucAddr == 0x00)
    {
        return g_RegHead.byte;
    }
    else if (ucAddr >= ID_G_SFR_80)
    {
        ch = SFR_Read(ucAddr);
    }

    DBG_SFR("\nREG readr:%02x", ucAddr);
    
    return ch;
}

#endif

