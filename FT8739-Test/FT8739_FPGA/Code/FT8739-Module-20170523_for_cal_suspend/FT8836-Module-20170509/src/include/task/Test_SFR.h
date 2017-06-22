/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_SFR.h
*
*    Author: xinkunpeng
*
*   Created: 2014-04-23
*
*  Abstract: Please describe the interface in detail for this module
*
* Reference:
*
*******************************************************************************/
#ifndef _TEST_SFR_H__
#define _TEST_SFR_H__

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

#if _TEST_SFR_EN
/*******************************************************************************
* 2.Global constant and macro definitions using #define
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
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern UINT8 XRAM g_ucSFR[256];

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
UINT8 SFRGetRegMapDataNormal(UINT8 ucAddr);
void Test_SFR();
#else
#define Test_SFR /##/
#define SFRGetRegMapDataNormal(x)  /##/
#endif

#endif

