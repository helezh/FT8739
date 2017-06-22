/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: test_pram1.c
*
*    Author: xinkunpeng
*
*   Created: 2017-01-23
*
*  Abstract:
*
* Reference:
*
* Version: 0.2: Transplant from FT5412 by linjianjun
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "global.h"
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
* Name: test_pram1
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void test_pram1(void)
{
    UINT16 i = 0;
    UINT32 src_addr;
    UINT32 dest_addr;

    src_addr = PRAM1_START_ADDR - 0xFEE800;
    dest_addr = PRAM1_COPY_ADDR - 0xFEE800;

    P0_6 = 0;
    P0_7 = 0;
    /*先把pram1中的代码段搬运到pram2中*/
    for(i = 0; i < PRAM1_CODE_LEN ; i++)
    {
        PRAM_ADDR8(dest_addr + i) = PRAM_ADDR8(src_addr + i);
    }

    /* pram1 test*/
    for(i = 0; i < PRAM1_TEST_LEN; i++)
    {
        PRAM_ADDR8(src_addr + i) = TEST_PATTERN1;
    }

    for(i = 0; i < PRAM1_CODE_LEN; i++)
    {
        if(PRAM_ADDR8(src_addr + i) != TEST_PATTERN1)
        {
            P0_0 = 0;
            P0_1 = 1;
            while(1);
        }
        else
        {
            P0_0 = ~ P0_0;
        }
    }



    for(i = 0; i < PRAM1_TEST_LEN; i++)
    {
        PRAM_ADDR8(src_addr + i) = TEST_PATTERN2;
    }

    for(i = 0; i < PRAM1_CODE_LEN; i++)
    {
        if(PRAM_ADDR8(src_addr + i) != TEST_PATTERN2)
        {
            P0_0 = 1;
            P0_1 = 0;
            while(1);
        }
        else
        {
            P0_0 = ~ P0_0;
        }        
    }
  
    /* 把原来pram1的代码段搬回来 */
    for(i = 0; i < PRAM1_CODE_LEN ; i++)
    {
        PRAM_ADDR8(src_addr + i) = PRAM_ADDR8(dest_addr + i);
    }
   
}