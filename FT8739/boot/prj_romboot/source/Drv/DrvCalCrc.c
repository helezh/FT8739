/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: DrvCalCrc.c
*
*    Author: tangsujun
*
*   Created: 2016-12-22
*
*  Abstract: Calculate crc module
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* Included header files
*******************************************************************************/
#include "FT8836.h"
#include "Typedef.h"
#include "DrvCalCrc.h"

/*******************************************************************************
* Private constant and macro definitions using #define
*******************************************************************************/
//CAL_CMD BIT DEFINITION
#define CAL_CMD_START          0x0001
#define CAL_CMD_RESUME         0x0004
#define CAL_CMD_SUSPEND        0x0008
#define CAL_CMD_INT_CLR        0x4000

//CAL_OP_MOD DEFINITION
#define OP_CRC                 (0x09<<4)
#define CRC_PRAM_TYPE          BITn(8)
#define CAL_CMD_INT            BITn(15)

#if _CRC_CAL_EN
#define DMALENGTH              1
/*******************************************************************************
* Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* Static variables
*******************************************************************************/
ST_CalRegisters *pCalRegs = (volatile ST_CalRegisters *)CAL_REG_BASE_ADDR;

/*******************************************************************************
* Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: DrvCal_CRC16
*  Brief:
*  Input: UINT16 usSrc1Addr:0--32K
*         UINT16 usLen: 0--32K
*         UINT8  Area:  0:Dram; 1:00K--64K; 3:64K--128K
*
* Output: None
* Return: CRC8 result
*******************************************************************************/
UINT16 CAL_Check(UINT16 usSrc1Addr, UINT16 usLen, UINT8 mem)
{
    UINT16 value;
    //clk
    CALCKEN = 1;

    #if 1//TBD 只跟打断有关系，若无打断，可以删掉这条语句
    pCalRegs->rDmaLen = DMALENGTH;
    /* 运行时中断可打断源配置 */
    pCalRegs->rDmask = BITn(11)|BITn(5);  //表示CAL可以被IIC/SPI0打断
    #endif
    
    //cfg
    pCalRegs->rS1Addr = usSrc1Addr;
    pCalRegs->rSize   = usLen;   
    
    
    pCalRegs->rInt &= ~(1<<8); //第三个选项，0标志地址是FC:0000-FC:FFFF;1:FD:0000-FD:FFFF
    // memory area
    pCalRegs->rCmd = (mem<<8)|(OP_CRC|CAL_CMD_START);
   


    /* mcu hold ... cal run */
    while((pCalRegs->rInt&CAL_CMD_INT) != CAL_CMD_INT)
    {

        /* if cal madule is resumed,start again */
        if((pCalRegs->rCmd&CAL_CMD_SUSPEND) == CAL_CMD_SUSPEND)
        {  
         //   DBG_FLOW("\n CAL_CMD_SUSPEND=%02x",pCalRegs->rCmd&CAL_CMD_SUSPEND);
         //   wait_printf_done();
            INTOUT =0;
            INTOUT =1;
            pCalRegs->rCmd |= CAL_CMD_RESUME;
        }
    }
    pCalRegs->rCmd |= CAL_CMD_INT_CLR;    

    value = pCalRegs->rCrc;
      
    CALCKEN = 0;
    return value;
}

#else
#define AL2_FCS_COEF                     ((1 << 15) + (1 << 10) + (1 << 3))
/******************************************************************************
*
*   Name: GetCrc16
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
UINT16 DrvCRC(UINT32 addr,UINT16 length)
{
    UINT16 cFcs = 0,*ptr16;
    UINT16 i, j;
    
    ptr16   =(UINT16 far  *)addr;
        
    for ( i = 0; i < length; i++ )
    {

        cFcs ^= *ptr16++;    
        
        for (j = 0; j < 16; j ++)
        {
            if (cFcs & 0x01)
            {
                cFcs = (UINT16)((cFcs >> 1) ^ AL2_FCS_COEF);
            }
            else
            {
                cFcs >>= 1;
            }
        }
    }
    return cFcs;
} 
#endif

