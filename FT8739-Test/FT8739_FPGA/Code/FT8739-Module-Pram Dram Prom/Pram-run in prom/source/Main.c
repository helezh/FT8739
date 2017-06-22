/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: main.c
*
*    Author: tangzhewei
*
*   Created: 2015-03-16
*
*  Abstract:
*
* Reference:
*
* Version:
* 0.1: Transplant from FT5412 by linjianjun
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "CfgGlobal.h"
#include "Drv_mcu.h"


/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define TEST_PRAM8      1
#define TEST_PRAM16     0
#define TEST_PRAM32     0
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
UINT8 temp = 0;
volatile UINT8 far  *ptr8 = 0;
volatile UINT16 far *ptr16 = 0;
volatile UINT32 far *ptr32 = 0;
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
/*******************************************************************************
*   Name: init_mcu
*  Brief:
* 功能:
*  Input:
* Output:
* Return:
*******************************************************************************/
void init_mcu(void)
{    
    EA = 0;
    
    // 1.IO口初始化
    DrvIOInit();

    DrvUartInit();

    EA = 1;

    DBG_FLOW("\n ROMMBOOT REMAP =%02x ",REMAP);
}
/*******************************************************************************
*   Name: main
*  Brief:
* 功能:
*  Input:
* Output:
* Return:
*******************************************************************************/
void main(void)
{
    UINT8 i; 
    UINT32 j=0,k=0;
    UINT32 cnt_err=0,cnt_ok=0;
    UINT32 cnt_err16=0,cnt_ok16=0;
    UINT32 cnt_err32=0,cnt_ok32=0;
    UINT32 test_data=0;
    

    init_mcu();
    
    while (1)
    {
        test_data++;
        if (test_data == 0xffffffff)
        {
            test_data=0;
        }

#if TEST_PRAM8

    for(k=0; k<1; k++)
    {

        temp =0;
        test_data &=0xff;
        for(j=0; j<(1024ul*70ul); j++)
        {
            PRAM_ADDR8(j) = test_data;
        }

        for(j=0; j<(1024ul*70ul); j++)
        {
            if(PRAM_ADDR8(j)  != test_data) 
            {
                temp=5;
                break;
            }
            else
            {
                P0_2 = !P0_2;
            }
        }

        if(temp ==5)
            cnt_err++;
        else
            cnt_ok++;

        DBG_FLOW("\n PRAM08 OK=%lx,ERR=%lx,test_data=%lx",cnt_ok,cnt_err,test_data);
    }
#endif
#if TEST_PRAM16

    for(k=0; k<1; k++)
    {
        test_data &=0xffff;
        temp =0;
        ptr16 = (volatile UINT16 *)0xfce800;
        for(j=0; j<(512UL*70); j++)
        {
            *ptr16  =test_data;
            ptr16 ++;

        }

        ptr16 = (volatile UINT16 *)0xfce800;
        for(j=0; j<(512UL*70); j++)
        {
            if(*ptr16  !=test_data) 
            {
                temp=5;
                break;
            }
            ptr16 ++;
        }

        if(temp ==5)
            cnt_err16++;
        else
            cnt_ok16++;

        DBG_FLOW("\n PRAM16 OK=%lx,ERR=%lx,j=%lx",cnt_ok16,cnt_err16,test_data);

    }

#endif
#if TEST_PRAM32

    for(k=0; k<1; k++)
    {

        temp =0;
        ptr32 = (volatile UINT32 *)0xfce800;
        for(j=0; j<(128UL*70); j++)
        {
        *ptr32  =test_data;	

        ptr32 ++;

        }

        ptr32 = (volatile UINT32 *)0xfce800;
        for(j=0; j<(128UL*70); j++)
        {
        if(*ptr32  !=test_data) 
        {
            temp=5;
            break;
        }


        ptr32 ++;

        }

        if(temp ==5)
        cnt_err32++;
        else
        cnt_ok32++;

        DBG_FLOW("\n PRAM32 OK=%lx,ERR=%lx,j=%lx",cnt_ok32,cnt_err32,test_data);

    }

#endif
    }    

}


