/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: AppSysCtrl.c
*
*    Author: lisen
*
*   Created: 2016-12-26
*
*  Abstract: System Control functions and variables
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* Included header files
*******************************************************************************/
#include "AppSysCtrl.h"
#include "DrvSysCtrl.h"
#include "AppHostComm.h"
#include "AppSysCtrl.h"
#include "LibDrv.h"

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

/*******************************************************************************
*   Name: AppSysInit
*  Brief: Initialize system just after powering up and before entering into flow
*         control.
*  Input: None
* Output: None
* Return: None
*******************************************************************************/


/*******************************************************************************
*   Name: DrvLcdRunInit
*  Brief: lcd run
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvLcdRunInit(void)
{
//    LCD_RUN = 1;
    ES = 1;
}

void DrvPowerInit(void)
{

}

void AppSysInit(void)
{
    DrvPowerInit();

    DrvSysClkInit(MAIN_CLK); 
    
    DrvSysPortInit(); 
    
    AppHostCommInit();
    
    DrvUartInit();
    
    DrvCal_Init(TX_NUM_LOCAL, RX_NUM_LOCAL, 0x55ef);// mask 0x000F  

    DrvLcdRunInit();

    DrvIntPriority();    

    DrvSysIntEnable();  

    Drv_XsiInit();
	
	Drv_XbusInit();

}

