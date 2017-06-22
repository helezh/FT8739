/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: main.c
*
*    Author:
*
*   Created: 2016-12-06
*
*  Abstract: lisen
*
* Reference: 
*
*******************************************************************************/

/*******************************************************************************
* Included header files
*******************************************************************************/
#include "AppSysCtrl.h"
#include "AppParameter.h"
#include "FlowWork.h"
#include "FlowFactory.h"
#include "FlowUpgrade.h"
#include "DrvSysCtrl.h"
/*******************************************************************************
* Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* Static variables
*******************************************************************************/
//#define APP_VERIF_LEN  0x20
//#define APP_VERIF_ADDR 0x100

#define BASE_ADDR         0xFEE800
#define APP_VERIF_ADDR    (BASE_ADDR + 0x100)   //0xFEE900   Verification Info
#define APP_VERIF_LEN     0x20

#define FW_CFG_TOTAL_SIZE         0x80


/*******************************************************************************
* Global variable or extern global variabls/functions
*******************************************************************************/

//UINT8 CROM g_aucVerfication[APP_VERIF_LEN] _at_ APP_VERIF_ADDR;
UINT8 ecode g_aucVerfication[APP_VERIF_LEN+FW_CFG_TOTAL_SIZE] _at_ APP_VERIF_ADDR;

/*******************************************************************************
* Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: main
*  Brief: Main Entrance on Embedded Platform
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void main(void)
{
    // 1.system hardware initialization
    AppSysInit();

    g_State = SS_FACTORY; 

    DBG_ALEN("\nKeil version:%d",__C251__);
    DBG_FLOW("\nFT8836 AFE:%s",__DATE__);
    DBG_FLOW("\nFlow Select:%x",g_State);   

	//TestUart();

    while(1)
    {
        switch (g_State) 
        {
            case SS_WORK:
                FlowWork();     // Normal work mode
                break;

            case SS_FACTORY:
                FlowFactory();  // Factory test mode
                break;

            case SS_UPGRADE1:
            case SS_UPGRADE2:
                FlowUpgrade();  // Upgrade checking mode
                break;

            default:
                break;
        }
    }
}


