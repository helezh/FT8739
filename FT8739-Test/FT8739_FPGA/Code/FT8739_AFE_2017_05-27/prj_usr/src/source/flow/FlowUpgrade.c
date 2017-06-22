/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: FlowUpgrade.c
*
*    Author: 
*
*   Created: 2013-02-01
*
*  Abstract: Please describe what the module complete, what relationship with
*            other modules, etc.
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* Included header files
*******************************************************************************/
//#include "FlowUpgrade.h"
#include "AppHostComm.h"
#include "DrvSysCtrl.h"
#include "AppSysCtrl.h"

/*******************************************************************************
* Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* Static variables
*******************************************************************************/

/*******************************************************************************
* Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* Static function prototypes
*******************************************************************************/

#if _PRAM_UPGRADE_EN
/*******************************************************************************
*   Name: FlowUpgrade
*  Brief: Upgrad firmware flow, check if entering legal upgrade steps, then goto 
*         internal bootloader.
*         1. App will enter into SS_UPGRADE1 state when host send 0xaa to
*         register 0xFC.
*         2. App will enter into SS_UPGRADE2 state when host send 0x55 to
*         register 0xFC. After that, if last state is S_UPGRADE1, system
*         goes to upgrade firware.
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void FlowUpgrade(void)
{
    static UINT8 XRAM g_LastState = SS_WORK;

    if (g_State == SS_UPGRADE1)
    {
        g_LastState = SS_UPGRADE1;
    }
    else if (g_State == SS_UPGRADE2)
    {
        DBG_FLOW("\nUpgrade2");    
        if (g_LastState == SS_UPGRADE1)
        {
            g_LastState = SS_UPGRADE2;
            /* Delay a short time for sending ack */
            DelayMs(1);
            DrvGoToUpgrade();
        }
        else
        {
            g_LastState = SS_WORK;
        }
    }
    else if (g_State == SS_SW_RESET)
    {
        if (g_LastState == SS_UPGRADE1)
        {
            g_LastState = SS_SW_RESET;
            /* Delay a short time for sending ack */
            DelayMs(1);
            DrvSwReset();
        }
    }
    else
    {
        g_LastState = SS_WORK;
    }
}
#endif

