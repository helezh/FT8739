/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: DrvTimer.c
*
*    Author: tangsujun
*
*   Created: 2016-12-22
*
*  Abstract:
*
* Reference:
*
* Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "CfgGlobal.h"

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

UINT16 g_TimeOver ;
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: DrvTimer0Init
*  Brief:Initial timer0
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvTimer0Init()
{
    g_TimeOver = 0;    

    TIMERCKEN = 1;
    TMOD = TM0_REPEAT_MODE;
    TF0 = 0;

    DrvTimer0Set200Us();
    DrvTimer0_Trigger();

    // interrupt enable
    ET0 =1;
}
/*******************************************************************************
*   Name: ISR_Timer0
*  Brief: Timer interrupt handler
*  Input:
* Output:
* Return:
*******************************************************************************/
void ISR_Timer0(void) interrupt  1
{  
    g_TimeOver++;
    if(g_TimeOver>100)
    {
        g_bTime20ms_Flag=1;
        
    }

}
