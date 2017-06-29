/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_RAM.c
*
*    Author: tangsujun
*
*   Created: 2017-04-28
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/
#include "Test_RAM.h"

#if _TEST_RAM_EN

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

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
void ( far * test_pram)(UINT8 far *ptr8,UINT32 len, UINT8 test_cnt);

/******************************************************************************
* Name:void Test_SPI0(void)
* Brief:
* Input:
* Output:
* Return:
******************************************************************************/
void Test_RAM_IN_PROM(void)
{
    unsigned char i=0;
    volatile UINT8 far * ptr8;


    ptr8 = PROM_PTR8(0x0202);
    
    for(i=0;i<0x80;i++)
    {        
        if (i%16 == 0)
        {
            DBG_FLOW("\n");
        }
        DBG_FLOW("%02x ",*(ptr8+i));

    }    
    wait_printf_done();
#if 0   
    /********test pram*****************/
    EA =0;
    test_pram =PROM_PTR8(0x0226);
    (*test_pram)(PRAM2_PTR8(0),0x400,32);
    EA =1;
#endif

#if 1 
    /********test dram*****************/
    EA =0;
    test_pram =PROM_PTR8(0x0202);
    (*test_pram)(DRAM_PTR8(0x8000),0x400,4);
    EA =1;
#endif  
    DBG_FLOW("Test_RAM_IN_PROM DONE");
    while(1)
    {
        DelayMs(10);
       // INTOUT ^=1;
    }  




}



#endif//_TEST_RAM_EN


