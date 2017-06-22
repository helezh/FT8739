/*******************************************************************************
 * Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
 *
 * File Name: Test_CAL.c
 *
 *    Author: xinkunpeng
 *
 *   Created: 2014-05-07
 *
 *  Abstract:
 *
 * Reference:
 *
 *   Version:
 *
 *******************************************************************************/

/*******************************************************************************
 * 1.Included header files
 *******************************************************************************/
#include <stdlib.h>
#include <math.h>
#include "Test_CAL.h"
#include "Drv_Cal.h"
#include "FT8836_Reg.h"
#include "Test_Afe.h"

#if _TEST_CAL_EN
/*******************************************************************************
 * 2.Private constant and macro definitions using #define
 *******************************************************************************/
ST_FrameData  g_stFrmData _at_ 0x1000;// Frame Data
volatile ST_Spi0DmaRegisters *XRAM pSpi0_DmaRegs = (ST_Spi0DmaRegisters *)SPI0_REG_BASE_ADDR;
#define CAL_TEST_A0  (UINT16)(g_stFrmData.CalBaseAddr)
#define CAL_TEST_A1  (CAL_TEST_A0+(TX_LOCAL_NUM*RX_LOCAL_NUM)*2)
#define CAL_TEST_A2  (CAL_TEST_A1+(TX_LOCAL_NUM*RX_LOCAL_NUM)*2)

#define CAL_TEST_PKS (UINT16)(g_stFrmData.ScDiff)

#define MIN_AVG(a,b)      (((a)<0)?(0):(((a)<(b))?(a):(b)))//若a<0,MIN = 0;若a>0,则MIN为(a)与(b)中的最小值,(b)应该填入无符号数

#define ERROR_HOLD        {DelayMs(100);while(1);}
#define ARAM_CAL_TEST     0

#define DELAY             //DelayUs(10)
#define WATI_CAL_SUSPEND   	  while(((pCalRegs->rCmd&CAL_CMD_SUSPEND) != CAL_CMD_SUSPEND)&&(((pCalRegs->rInt&CAL_CMD_INT) != CAL_CMD_INT))) 
#define WAIT_AMOVE_SUSPEND    while((((pCalRegs->rInt&CAL_CMD_AMOV_SUSPEND) != CAL_CMD_AMOV_SUSPEND))&&(((pCalRegs->rInt&CAL_CMD_AMOV_INT) != CAL_CMD_AMOV_INT))) 
/*******************************************************************************
 * 3.Private enumerations, structures and unions using typedef
 *******************************************************************************/

/************************************************** *****************************
 * 4.Static variables
 *******************************************************************************/

/*******************************************************************************
 * 5.Global variable or extern global variabls/functions
 *******************************************************************************/
SINT16 * XRAM T_tempbuf1;
SINT16 * XRAM T_tempbuf2;
SINT16 * XRAM T_tempbuf3;
SINT16 * XRAM T_tempOut;
SINT16 * XRAM g_pAfeAram = (volatile SINT16*)ARAM_DATA_BASE_ADDR;
UINT32 g_I2cCnt =0;
UINT8 g_ucCalFlag = 0;


/*******************************************************************************
 * 6.Static function prototypes
 *******************************************************************************/

#if TEST_CAL_ADD_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixAdd
 *  Brief: 测试加法运算
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixAdd()
{
    UINT8 i,j;
    UINT8 shift;
    BOOLEAN flag;
    SINT32 temp;
    ST_CalMcMatrixParam XRAM CalParam;
    static UINT8 counter = 0;

    DBG_CAL("\n\nTest: Matrix add");

    if(counter == 4)
        counter = 0;
    
    shift = counter;
    counter ++;
    //for (shift = 0; shift < 4; shift++)
    {
        DBG_CAL("\nShift=%d",shift);
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                *(T_tempbuf1 + i*RX_LOCAL_NUM + j) =  rand()>>1;
                *(T_tempbuf2 + i*RX_LOCAL_NUM + j) =  rand()>>1;
                //g_pAfeAram[i*RX_LOCAL_NUM + j]     = rand()>>1;
            }
        }
        DBG_CAL("\n\rMem-Mem:");
        CalParam.usSrc1Addr = CAL_TEST_A0;
        CalParam.usSrc2Addr = CAL_TEST_A1;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_TEST_TX;
        CalParam.ucRxLen    = CAL_TEST_RX;
        CalParam.ucShift    = shift;
        CalParam.usCalCmd   = OP_ADD;
        CalParam.ucCfg      = SIGN_MOD_0;

        DrvCal_MatrixProc(&CalParam);
        g_ucCalFlag = 0;
        for (i = 0; i < CAL_TEST_TX; i++)
        {
            for (j = 0; j < CAL_TEST_RX; j++)
            {
                temp = (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) + *(T_tempbuf2 + i*RX_LOCAL_NUM + j)) >> shift;
                if (temp > 0x7FFF)
                {   
                    temp = 0x7FFF;
                }
                else if (temp < -32768)
                {
                    temp = 0x8000;
                }
                if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (SINT16)temp)
                {
                    g_ucCalFlag = 1;
                    DBG_ERROR("\n\r%03derror%04X,%04x",(i*RX_LOCAL_NUM + j),*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
                }
                else
                {
                    //DBG_CAL("\n\r%03dok   %04X,%04x",(i*RX_LOCAL_NUM + j),*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
                }
            }
        }
        if (g_ucCalFlag)
        {
            DBG_CAL("\n\rCal Add test is Error");

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }       

            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rCal Add test is OK!");
        }

#if 0        
        DBG_CAL("\nAram-Mem:");

        for (i = 0; i < TX_ARAM_NUM; i++)
        {
            for (j = 0; j < RX_ARAM_NUM; j++)
            {
                *(T_tempbuf1 + i*RX_ARAM_NUM + j) =  rand()>>1;
                g_pAfeAram[i*RX_ARAM_NUM + j]     = rand()>>1;
            }
        }
        
        CalParam.usSrc1Addr = CAL_TEST_A0;
        CalParam.usSrc2Addr = ARAM_DATA_BASE_ADDR;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_ARAM_TX;
        CalParam.ucRxLen    = CAL_ARAM_RX;
        CalParam.ucShift    = shift;
        CalParam.usCalCmd   = OP_ADD;
        CalParam.ucCfg      = SIGN_MOD_0;

        DrvCal_MatrixProc(&CalParam);
        flag = 0;
        
        for (i=0; i<CAL_ARAM_TX; i++)
        {
            for (j=0; j<CAL_ARAM_RX; j++)
            {
                temp = (*(T_tempbuf1 + i*RX_ARAM_NUM + j) + *(g_pAfeAram + i*RX_ARAM_NUM + j)) >> shift;              
                if (temp > 0x7FFF)
                {   
                    temp = 0x7FFF;
                }
                else if (temp < -32768)
                {
                    temp = 0x8000;
                }

                if (*(T_tempOut + i*RX_ARAM_NUM + j) != (SINT16)temp)
                {
                    g_ucCalFlag = 1;
                    DBG_ERROR("\n\r%03derror%04X,%04x",(i*RX_ARAM_NUM + j),*(T_tempOut + i*RX_ARAM_NUM + j),(SINT16)temp);
                }
                else
                {
                    //DBG_CAL("\n\r%03dok   %04X,%04x",(i*RX_LOCAL_NUM + j),*(T_tempbuf2 + i*RX_LOCAL_NUM + j),(SINT16)temp);
                }
            }
        }
        if (g_ucCalFlag)
        {
            DBG_CAL("\nCal Add test is Error");

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }   
            
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\nCal Add test is OK");
        }
#endif        
    }

    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixAdd   /##/
#endif

#if TEST_CAL_SUB_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixSub
 *  Brief: 测试减法运算
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixSub()
{
    UINT8 i,j;
    UINT8 shift;
    UINT16 usSubMax;
    SINT16 temp;
    BOOLEAN flag;
    ST_CalMcMatrixParam XRAM CalParam;
    static UINT8 counter = 0;
    DBG_CAL("\n\nTest: Matrix sub");

    if(counter == 4)
        counter = 0;

    shift = counter;
    counter ++;

    //for (shift = 0; shift < 4; shift++)
    {
        DBG_CAL("\nShift=%d",shift);
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
                T_tempbuf1[i*RX_LOCAL_NUM + j] = rand()>>1;//30000;
                T_tempbuf2[i*RX_LOCAL_NUM + j] = rand()>>1;//;-30000;
                //g_pAfeAram[i*RX_LOCAL_NUM + j] = rand()>>1;
            }
        }

        DBG_CAL("\nMem-Mem:");
        CalParam.usSrc1Addr = CAL_TEST_A0;
        CalParam.usSrc2Addr = CAL_TEST_A1;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_TEST_TX;
        CalParam.ucRxLen    = CAL_TEST_RX;
        CalParam.ucShift    = shift;
        CalParam.usCalCmd   = OP_SUB;
        CalParam.ucCfg      = SIGN_MOD_0;

        DrvCal_MatrixProc(&CalParam);
        g_ucCalFlag = 0;
        usSubMax = 0;
        for (i = 0; i < CAL_TEST_TX; i++)
        {
            for (j = 0; j < CAL_TEST_RX; j++)
            {
                temp = ((SINT16)*(T_tempbuf1 + i*RX_LOCAL_NUM + j) - (SINT16)*(T_tempbuf2 + i*RX_LOCAL_NUM + j)) >> shift;
                if (temp > 32767)
                {   
                    temp = 32767;
                }
                else if (temp < -32768)
                {
                    temp = -32768;
                }
                if (abs((SINT16)temp) > usSubMax)
                {
                    usSubMax = abs((SINT16)temp);
                }
                if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (SINT16)temp)
                {
                    g_ucCalFlag = 1;
                    DBG_ERROR("\n\r%03derror%04X,%04x",(i*RX_LOCAL_NUM + j),*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
                }
                else
                {
                    //DBG_CAL("\n\r%03dok   %04X,%04x",(i*RX_LOCAL_NUM + j),*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
                }
            }
        }
        if (g_ucCalFlag)
        {
            DBG_CAL("\nCal SUB test is ERROR!");
            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }
            
            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            } 

            
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rCal SUB test is OK!");
        }


        for (i=0; i<TX_ARAM_NUM; i++)
        {
            for (j=0; j<RX_ARAM_NUM; j++)
            {
                T_tempbuf1[i*RX_ARAM_NUM + j] = rand()>>1;//30000;
                //T_tempbuf2[i*RX_ARAM_NUM + j] = rand()>>1//;-30000;
                g_pAfeAram[i*RX_ARAM_NUM + j] = rand()>>1;
            }
        }

#if ARAM_CAL_TEST
        DBG_CAL("\n\rAram-Mem:");
        CalParam.usSrc1Addr = CAL_TEST_A0;
        CalParam.usSrc2Addr = ARAM_DATA_BASE_ADDR;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_ARAM_TX;
        CalParam.ucRxLen    = CAL_ARAM_RX;
        CalParam.ucShift    = shift;
        CalParam.usCalCmd   = OP_SUB;
        CalParam.ucCfg      = SIGN_MOD_0;

        DrvCal_MatrixProc(&CalParam);
        CALCKEN = 1;
        g_ucCalFlag = 0;
        usSubMax = 0;
        for (i = 0; i < CAL_ARAM_TX; i++)
        {
            for (j = 0; j < CAL_ARAM_RX; j++)
            {
                temp = ((SINT32)*(T_tempbuf1 + i*RX_ARAM_NUM + j) - (SINT16)*(g_pAfeAram + i*RX_ARAM_NUM + j)) >> shift;
                if (temp > 32767)
                {   
                    temp = 32767;
                }
                else if (temp < -32768)
                {
                    temp = -32768;
                }
                if (abs((SINT16)temp) > usSubMax)
                {
                    usSubMax = abs((SINT16)temp);
                }
                if (*(T_tempOut + i*RX_ARAM_NUM + j) != (SINT16)temp)
                {
                    g_ucCalFlag = 1;
                    DBG_ERROR("\n\r%03derror%04X,%04x",(i*RX_ARAM_NUM + j),*(T_tempOut + i*RX_ARAM_NUM + j),(SINT16)temp);
                }
                else
                {
                    //DBG_CAL("\n\r%03dok   %04X,%04x",(i*RX_LOCAL_NUM + j),*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
                }
            }
        }
              
        if(usSubMax != pCalRegs->rSubabsMax)
        {
            DBG_CAL("\n\rSubMax is Error:%04X,%04x",usSubMax,pCalRegs->rSubabsMax);           
        }
        else
        {
            DBG_CAL("\n\rSubMax is  %04X =%04x",usSubMax,pCalRegs->rSubabsMax);    
        }
        CALCKEN = 0;
        if (g_ucCalFlag)
        {
            DBG_CAL("\nCal SUB test is Error!");
            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }             
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\nCal SUB test is OK!");
        }
#endif		
    }
    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixSub    /##/
#endif

#if TEST_CAL_AMP_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixAmp
 *  Brief: 测试乘法运算
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixAmp()
{
    UINT8 i,j;
    BOOLEAN flag;
    UINT8 shift;
    SINT16 mul;
    SINT32 temp;
    //   SINT16 tmp2;
    ST_CalMcMatrixParam XRAM CalParam;
    static UINT8 counter = 0;
    DBG_CAL("\n\nTest: Matrix amp");

    if(counter == 16)
        counter = 0;
    
    shift = counter;
    counter ++;   
    
    //for (shift = 0; shift < 16; shift++)
    {
        DBG_CAL("\n\rshift:%02d",shift);
        for (mul = -100; mul < 100; mul++)
        {         
            //DBG_CAL_DATA("\n\Mul:%03d,shift:%02d",mul,shift);
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand() >> 4;//400;
                    //g_pAfeAram[i*RX_LOCAL_NUM + j]  = (SINT16)rand() >> 4;
                }
            }

            CalParam.usSrc1Addr = CAL_TEST_A0;
            CalParam.usDstAddr  = CAL_TEST_A1;
            CalParam.ucTxLen    = CAL_TEST_TX;
            CalParam.ucRxLen    = CAL_TEST_RX;
            CalParam.ucShift    = shift;
            CalParam.usCalCmd   = OP_AMP;

            DrvCal_MatrixAmp(&CalParam,mul);
            g_ucCalFlag = 0;
            for (i = 0; i < CAL_TEST_TX; i++)
            {
                for (j = 0; j < CAL_TEST_RX; j++)
                {
                    temp = (SINT16)(*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) * mul;
                    temp >>= shift;
                    if (temp > 32767)
                    {   
                        temp = 32767;
                    }
                    else if (temp < -32768)
                    {
                        temp = -32768;
                    }
                    if (*(T_tempbuf2 + i*RX_LOCAL_NUM + j) != (SINT16)temp )
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\nerror=%04x,%04x,%04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j),(SINT16)temp,*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
                    }
                    else
                    {
                        //DBG_CAL_DATA("\nok=%04x,%04x,%04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j),(SINT16)temp,*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
                    }
                }    
            }
            if (g_ucCalFlag)
            {
                DBG_CAL("\n\r\Mul:%03d,shift:%02d",mul,shift);
                DBG_CAL("\n\rError");
                DBG_CAL("\n");
                for (i = 0; i < TX_LOCAL_NUM; i++)
                {
                    for (j = 0; j < RX_LOCAL_NUM; j++)
                    {
                        DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                    }
                    DBG_CAL("\n");
                }
                
                DBG_CAL("\n");
                ERROR_HOLD;
            }

#if ARAM_CAL_TEST
             for (i = 0; i < TX_ARAM_NUM; i++)
            {
                for (j = 0; j < RX_ARAM_NUM; j++)
                {
                    g_pAfeAram[i*RX_ARAM_NUM + j] = (SINT16)rand() >> 4;
                }
            }           

            CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
            CalParam.usDstAddr  = CAL_TEST_A1;
            CalParam.ucTxLen    = CAL_ARAM_TX;
            CalParam.ucRxLen    = CAL_ARAM_RX;
            CalParam.ucShift    = shift;
            CalParam.usCalCmd   = OP_AMP;

            DrvCal_MatrixAmp(&CalParam,mul);
            g_ucCalFlag = 0;
            for (i = 0; i < CAL_ARAM_TX; i++)
            {
                for (j = 0; j < CAL_ARAM_RX; j++)
                {
                    temp = (SINT16)g_pAfeAram[i*RX_ARAM_NUM + j] * mul;
                    temp >>= shift;
                    if (temp > 32767)
                    {   
                        temp = 32767;
                    }
                    else if (temp < -32768)
                    {
                        temp = -32768;
                    }
                    if (*(T_tempbuf2 + i*RX_ARAM_NUM + j) != (SINT16)temp )
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rerror>>%04x,%04x,%04x",*(T_tempbuf2 + i*RX_ARAM_NUM + j),(SINT16)temp,*(g_pAfeAram + i*RX_ARAM_NUM + j));
                    }
                    else
                    {
                        //DBG_CAL_DATA("\n\rok>>   %04x,%04x,%04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j),(SINT16)temp,*(g_pAfeAram + i*RX_LOCAL_NUM + j));
                    }
                }
            }
            if (g_ucCalFlag)
            {
                DBG_CAL("\n\Mul:%03d,shift:%02d",mul,shift);
                DBG_CAL("\nError");

                
                DBG_CAL("\n");
                for (i = 0; i < TX_LOCAL_NUM; i++)
                {
                    for (j = 0; j < RX_LOCAL_NUM; j++)
                    {
                        DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
                    }
                    DBG_CAL("\n");
                }             
                
                ERROR_HOLD;
            }
			
#endif	

        }  
        DBG_CAL("\nCal AMP test is OK!");
		
    }


    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixAmp    /##/
#endif

#if TEST_CAL_DIV_EN
#define TEST_DIV  25 //除法系数:0~255
/*******************************************************************************
 *   Name: Test_CAL_MaxtixDiv
 *  Brief: 测试除法运算
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixDiv()
{
    UINT8 i,j;
    BOOLEAN flag;
    UINT8 Div;

    ST_CalMcMatrixParam XRAM CalParam;

    DBG_CAL("\n\nTest: Matrix div");

    for (i = 0; i < TX_LOCAL_NUM; i++)
    {
        for (j = 0; j < RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand();//0x555;
        }
    }

    Div = TEST_DIV;
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A1;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;
    CalParam.usCalCmd   = OP_DIV;//OP_AMP;

    DrvCal_MatrixDiv(&CalParam,Div);
    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        for (j = 0; j < CAL_TEST_RX; j++)
        {
            if (*(T_tempbuf2 + i*RX_LOCAL_NUM + j) != (*(T_tempbuf1 + i*RX_LOCAL_NUM + j))/Div )
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\r%03dERROR->Soft:%04X,Cal:%04x ",i*RX_LOCAL_NUM+j,(*(T_tempbuf1 + i*RX_LOCAL_NUM + j))/Div,*(T_tempbuf2 + i*RX_LOCAL_NUM + j));
            }
            else
            {
               // DBG_CAL_DATA("\n\r%03dOK->   Soft:%04X,Cal:%04x ",i*RX_LOCAL_NUM+j,(*(T_tempbuf1 + i*RX_LOCAL_NUM + j))/Div,*(T_tempbuf2 + i*RX_LOCAL_NUM + j));
            }
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\nCal DIV test mem is Error!");
        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }
        
        DBG_CAL("\n");
        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nCal DIV test mem is OK!");
    }
	
#if 0//ARAM_CAL_TEST

    for (i = 0; i < TX_ARAM_NUM; i++)
    {
        for (j = 0; j < RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT16)rand();//0x555;
        }
    }


    Div = TEST_DIV;
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A1;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;
    CalParam.usCalCmd   = OP_DIV;//OP_AMP;

    DrvCal_MatrixDiv(&CalParam,Div);
    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_TX; i++)
    {
        for (j = 0; j < CAL_ARAM_RX; j++)
        {
            if (*(T_tempbuf2 + i*RX_ARAM_NUM + j) != (*(g_pAfeAram + i*RX_ARAM_NUM + j))/Div )
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\r%03dERROR->Soft:%04X,Cal:%04x ",i*RX_LOCAL_NUM+j,(*(g_pAfeAram + i*RX_LOCAL_NUM + j))/Div,*(T_tempbuf2 + i*RX_LOCAL_NUM + j));
            }
            else
            {
                //DBG_CAL_DATA("\n\r%03dOK->   Soft:%04X,Cal:%04x ",i*RX_LOCAL_NUM+j,(*(T_tempbuf1 + i*RX_LOCAL_NUM + j))/Div,*(T_tempbuf2 + i*RX_LOCAL_NUM + j));
            }
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\nCal DIV test aram is Error!");
        
        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }             
        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nCal DIV test aram is OK!");
    }

#endif    
    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixDiv    /##/
#endif

#if TEST_CAL_MOV_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixMov
 *  Brief: 测试矩阵搬移运算
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixMov()
{
    UINT8 i,j;
    BOOLEAN flag = 0;
	
#if TEST_CAL_MOV_INT_EN	
    UINT16 DelayValue;
#endif
	
    ST_CalMcMatrixParam XRAM CalParam;

    DBG_CAL("\n\nTest: Matrix mov");

    for (i = 0; i < TX_LOCAL_NUM; i++)
    {
        for (j = 0; j < RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = rand();
            //*(g_pAfeAram + i*RX_LOCAL_NUM + j) = rand();
        }
    }

    DBG_CAL("\nMem to Mem");
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A1;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;
    CalParam.usCalCmd   = OP_MOV;
    CalParam.ucCfg      = MOV_CFG_0;    /* 0: 不转置，1: 转置 */

    DrvCal_MatrixProc(&CalParam);
    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        for (j = 0; j < CAL_TEST_RX; j++)
        {
            if (*(T_tempbuf2 + i*RX_LOCAL_NUM + j) != *(T_tempbuf1 + i*RX_LOCAL_NUM + j))
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\rERROR->%04x,%04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j),*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK->   %04x,%04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j),*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\nCal MOV test is Error");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nCal MOV test is OK!");
    }
#if ARAM_CAL_TEST

    for (i = 0; i < TX_ARAM_NUM; i++)
    {
        for (j = 0; j < RX_ARAM_NUM; j++)
        {
            //*(T_tempbuf1 + i*RX_LOCAL_NUM + j) = rand();
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = rand();
        }
    }


    DBG_CAL("\n\rAram to Mem");
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;//CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A1;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;
    CalParam.usCalCmd   = OP_MOV;
    CalParam.ucCfg      = MOV_CFG_0;    /* 0: 不转置，1: 转置 */

    DrvCal_MatrixProc(&CalParam);
    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_TX; i++)
    {
        for (j = 0; j < CAL_ARAM_RX; j++)
        {
            if (g_pAfeAram[i*RX_ARAM_NUM + j] != *(T_tempbuf2 + i*RX_ARAM_NUM + j))
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\rERROR->%04x,%04x",*(g_pAfeAram + i*RX_ARAM_NUM + j),*(T_tempbuf2 + i*RX_ARAM_NUM + j));
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK->   %04x,%04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j),*(T_tempbuf2 + i*RX_LOCAL_NUM + j));
            }
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\nCal MOV test is Error!");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nCal MOV test is OK!");
    }
#endif
    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixMov      /##/
#endif

#if TEST_CAL_MOV2_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixMov2
 *  Brief: 测试矩阵转置搬移运算:矩阵转置搬移时最好TxNum,RxNum与TxLen,RxLen相等
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixMov2()
{
    UINT8 i,j;
    BOOLEAN flag = 0;
    ST_CalMcMatrixParam XRAM CalParam;

    DBG_CAL("\n\nTest: Matrix mov2");
    for (i = 0; i < TX_LOCAL_NUM; i++)
    {
        for (j = 0; j < RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = rand();
        }
    }

    DBG_CAL("\n\rMem to Mem");
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A1;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;
    CalParam.usCalCmd   = OP_MOV;
    CalParam.ucCfg      = MOV_CFG_1;    /* 0: 不转置，1: 转置 */

    DrvCal_MatrixProc(&CalParam);

    for (i = 0; i < CAL_TEST_RX; i++)
    {
        for (j = 0; j < CAL_TEST_TX; j++)
        {
            *(T_tempOut+ i*TX_LOCAL_NUM + j) = *(T_tempbuf1 + j*RX_LOCAL_NUM + i);
        }
    }
    g_ucCalFlag = 0;

    for (i = 0; i < CAL_TEST_RX; i++)
    {
        for (j = 0; j < CAL_TEST_TX; j++)
        {
            if (*(T_tempbuf2 + i*TX_LOCAL_NUM + j) != *(T_tempOut + i*TX_LOCAL_NUM + j))
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\rERROR->%04x,%04x",*(T_tempbuf2 + i*TX_LOCAL_NUM + j),*(T_tempOut + i*TX_LOCAL_NUM + j));
            }
            else
            {
               // DBG_CAL_DATA("\n\rOK->   %04x,%04x",*(T_tempbuf2 + i*TX_LOCAL_NUM + j),*(T_tempOut + i*TX_LOCAL_NUM + j));
            }
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\nCal MOV2 test is Error");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nCal MOV2 test is OK!");
    }

#if ARAM_CAL_TEST

    for (i = 0; i < TX_ARAM_NUM; i++)
    {
        for (j = 0; j < RX_ARAM_NUM; j++)
        {
            //*(T_tempbuf1 + i*RX_LOCAL_NUM + j) = rand();
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = 11;//rand();
        }
    }

    DBG_CAL("\nMem-Aram:");
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A1;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;
    CalParam.usCalCmd   = OP_MOV;
    CalParam.ucCfg      = MOV_CFG_1;

    DrvCal_MatrixProc(&CalParam);

    for (i = 0; i < CAL_ARAM_RX; i++)
    {
        for (j = 0; j < CAL_ARAM_TX; j++)
        {
            *(T_tempOut+ i*TX_ARAM_NUM + j) = *(g_pAfeAram + j*RX_ARAM_NUM + i);
        }
    }
    
    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_RX; i++)
    {
        for (j = 0; j < CAL_ARAM_TX; j++)
        {
            if (*(T_tempbuf2 + i*TX_ARAM_NUM + j) != *(T_tempOut + i*TX_ARAM_NUM + j))
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\rERROR->%04x,%04x",*(T_tempbuf2 + i*TX_ARAM_NUM + j),*(T_tempOut + i*TX_ARAM_NUM + j));
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK->   %04x,%04x",*(g_pAfeAram + i*TX_ARAM_NUM + j),*(T_tempOut + i*TX_ARAM_NUM + j));
            }
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\nCal MOV2 test is Error!");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nCal MOV2 test is OK!");
    }
#endif
    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixMov2      /##/
#endif

#if TEST_CAL_MUL2_1_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixMul_PtoP
 *  Brief: M1 : M*N
 *         M2 : 1*N
 *         OUT: M*N
 *         Out[i][j] = M2[1][j]*M1[i][j];
 *  Input: ST_CalMcMatrixParam *pMcMP =>
 * Output: None
 * Return: None
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixMul_PtoP1()
{
    UINT8 i,j;
    UINT8 ucShift;
    SINT16 tmp;
    BOOLEAN flag;
    ST_CalMcMatrixParam XRAM CalParam;
    static UINT8 counter = 0;
    
    DBG_CAL("\n\nTest: Matrix MUL2_1");


    if(counter == 16)
        counter = 0;
    
    ucShift = counter;
    counter ++;    

    DBG_CAL("\nmem-mem");

    for (i=0; i<RX_LOCAL_NUM; i++)
    {
        *(T_tempbuf1 + i) = (SINT8)rand()>>2;//-200
        //DBG_CAL_DATA("\n\r%04x",*(T_tempbuf1 + i));
    }
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf2 + i*RX_LOCAL_NUM + j) = (SINT8)rand()>>2;//200
        }
        //DBG_CAL_DATA("\n\r%04x",*(T_tempbuf2 + i*TX_LOCAL_NUM + j));
    }

    //for (ucShift = 0; ucShift < 16; ucShift++)
    {
        CalParam.usSrc1Addr = CAL_TEST_A0;
        CalParam.usSrc2Addr = CAL_TEST_A1;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_TEST_TX;
        CalParam.ucRxLen    = CAL_TEST_RX;
        CalParam.usCalCmd   = OP_MUL2;
        CalParam.ucShift    = ucShift;
        CalParam.ucCfg      = MUL2_CFG_0;

        DrvCal_MatrixMul2(&CalParam,MUL2_MODE_0);
        //DrvCal_MatrixMul_PtoP1(&CalParam);

        g_ucCalFlag = 0;
        for (i = 0; i < CAL_TEST_TX; i++)
        {
            for (j = 0; j < CAL_TEST_RX; j++)
            {
                tmp = (((SINT16)*(T_tempbuf1 + j)) * ((SINT16)*(T_tempbuf2 + i*RX_LOCAL_NUM + j)));
                tmp >>= ucShift;
                if (tmp > 32767)
                {
                    tmp = 32767;
                }
                else if (tmp < -32768)
                {
                    tmp = -32768;
                }
                if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (SINT16)tmp )
                {
                    DBG_ERROR("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                    g_ucCalFlag = 1;
                }
                else
                {
                    //DBG_ERROR("\n\rOK->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                }
            }
        }

        if (g_ucCalFlag)
        {
            DBG_CAL("\n\rCal MUL2 Rx test %02d is Error!",ucShift);
            DBG_CAL("\n");
            for (i = 0; i < 1; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }             
            
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rCal MUL2 Rx test %02d is OK!",ucShift);
        }
    }
    
#if 1 //每列各点乘以乘以不同的数
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        *(T_tempbuf1 + i) = (SINT8)rand()>>2;
        //DBG_CAL_DATA("\n%04x",*(T_tempbuf1 + i));
    }
    
    //for (ucShift = 0; ucShift < 16; ucShift++)
    {
        CalParam.usSrc1Addr = CAL_TEST_A0;
        CalParam.usSrc2Addr = CAL_TEST_A1;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_TEST_TX;
        CalParam.ucRxLen    = CAL_TEST_RX;
        CalParam.usCalCmd   = OP_MUL2;
        CalParam.ucShift    = ucShift;
        CalParam.ucCfg      = MUL2_CFG_1;
        
        DrvCal_MatrixMul2(&CalParam,MUL2_MODE_0);        
        //DrvCal_MatrixMul_PtoP1(&CalParam);

        g_ucCalFlag = 0;
        for (i = 0; i < CAL_TEST_TX; i++)
        {
            for (j = 0; j < CAL_TEST_RX; j++)
            {
                tmp = (((SINT16)*(T_tempbuf1 + i)) * ((SINT16)*(T_tempbuf2 + i*RX_LOCAL_NUM + j)));
                tmp >>= ucShift;
                if (tmp > 32767)
                {
                    tmp = 32767;
                }
                else if (tmp < -32768)
                {
                    tmp = -32768;
                }
                if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (SINT16)tmp )
                {
                    DBG_ERROR("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                    g_ucCalFlag = 1;
                }
                else
                {
                    //DBG_ERROR("\n\rOK->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                }
            }
        }
        if (g_ucCalFlag)
        {
            DBG_CAL("\n\rCal MUL2 Tx test %02d is Error!",ucShift);
            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < 1; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }             
            
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rCal MUL2 Tx test %02d is OK!",ucShift);
        }
    }
#endif
#if ARAM_CAL_TEST

       DBG_CAL("\naram-mem");
    
        for (i=0; i<RX_ARAM_NUM; i++)
        {
            *(T_tempbuf1 + i) = (SINT8)rand()>>2;
            //DBG_CAL_DATA("\n\r%04x",*(T_tempbuf1 + i));
        }
        for (i=0; i<TX_ARAM_NUM; i++)
        {
            for (j=0; j<RX_ARAM_NUM; j++)
            {
                *(T_tempbuf2 + i*RX_ARAM_NUM + j) = (SINT8)rand()>>2;
                *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT8)rand()>>2;                    
            }
            //DBG_CAL_DATA("\n\r%04x",*(T_tempbuf2 + i*TX_LOCAL_NUM + j));
        }
    
        //for (ucShift = 0; ucShift < 16; ucShift++)
        {
            CalParam.usSrc1Addr = CAL_TEST_A0;
            CalParam.usSrc2Addr = ARAM_DATA_BASE_ADDR;
            CalParam.usDstAddr  = CAL_TEST_A2;
            CalParam.ucTxLen    = CAL_ARAM_TX;
            CalParam.ucRxLen    = CAL_ARAM_RX;
            CalParam.usCalCmd   = OP_MUL2;
            CalParam.ucShift    = ucShift;
            CalParam.ucCfg      = MUL2_CFG_0;
            
            DrvCal_MatrixMul2(&CalParam,MUL2_MODE_0);    
            //DrvCal_MatrixMul_PtoP1(&CalParam);
    
            g_ucCalFlag = 0;
            for (i = 0; i < CAL_ARAM_TX; i++)
            {
                for (j = 0; j < CAL_ARAM_RX; j++)
                {
                    tmp = (((SINT16)*(T_tempbuf1 + j)) * ((SINT16)*(g_pAfeAram + i*RX_ARAM_NUM + j)));
                    tmp >>= ucShift;
                    if (tmp > 32767)
                    {
                        tmp = 32767;
                    }
                    else if (tmp < -32768)
                    {
                        tmp = -32768;
                    }
                    if (*(T_tempOut + i*RX_ARAM_NUM + j) != (SINT16)tmp )
                    {
                        DBG_ERROR("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_ARAM_NUM + j),(SINT16)tmp,i,j);
                        g_ucCalFlag = 1;
                    }
                    else
                    {
                        //DBG_ERROR("\n\rOK->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                    }
                }
            }
    
            if (g_ucCalFlag)
            {
                DBG_CAL("\n\rCal MUL2 Rx test %02d is Error!",ucShift);
                DBG_CAL("\n");
                for (i = 0; i < 1; i++)
                {
                    for (j = 0; j < RX_LOCAL_NUM; j++)
                    {
                        DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                    }
                    DBG_CAL("\n");
                }
                
                DBG_CAL("\n");
                for (i = 0; i < TX_LOCAL_NUM; i++)
                {
                    for (j = 0; j < RX_LOCAL_NUM; j++)
                    {
                        DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
                    }
                    DBG_CAL("\n");
                }             
                
                ERROR_HOLD;
            }
            else
            {
                DBG_CAL("\n\rCal MUL2 Rx test %02d is OK!",ucShift);
            }
        }
        
#if 1 //每列各点乘以乘以不同的数
        for (i=0; i<TX_ARAM_NUM; i++)
        {
            *(g_pAfeAram + i) = (SINT8)rand()>>2;
            //DBG_CAL_DATA("\n%04x",*(T_tempbuf1 + i));
        }
        
        //for (ucShift = 0; ucShift < 16; ucShift++)
        {
            CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
            CalParam.usSrc2Addr = CAL_TEST_A1;
            CalParam.usDstAddr  = CAL_TEST_A2;
            CalParam.ucTxLen    = CAL_ARAM_TX;
            CalParam.ucRxLen    = CAL_ARAM_RX;
            CalParam.usCalCmd   = OP_MUL2;
            CalParam.ucShift    = ucShift;
            CalParam.ucCfg      = MUL2_CFG_1;

            DrvCal_MatrixMul2(&CalParam,MUL2_MODE_0);            
    
            g_ucCalFlag = 0;
            for (i = 0; i < CAL_ARAM_TX; i++)
            {
                for (j = 0; j < CAL_ARAM_RX; j++)
                {
                    tmp = (((SINT16)*(g_pAfeAram + i)) * ((SINT16)*(T_tempbuf2 + i*RX_ARAM_NUM + j)));
                    tmp >>= ucShift;
                    if (tmp > 32767)
                    {
                        tmp = 32767;
                    }
                    else if (tmp < -32768)
                    {
                        tmp = -32768;
                    }
                    if (*(T_tempOut + i*RX_ARAM_NUM + j) != (SINT16)tmp )
                    {
                        DBG_ERROR("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_ARAM_NUM + j),(SINT16)tmp,i,j);
                        g_ucCalFlag = 1;
                    }
                    else
                    {
                        //DBG_ERROR("\n\rOK->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                    }
                }
            }
            if (g_ucCalFlag)
            {
                DBG_CAL("\n\rCal MUL2 Tx test %02d is Error!",ucShift);
                DBG_CAL("\n");
                for (i = 0; i < TX_LOCAL_NUM; i++)
                {
                    for (j = 0; j < 1; j++)
                    {
                        DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                    }
                    DBG_CAL("\n");
                }
                
                DBG_CAL("\n");
                for (i = 0; i < TX_LOCAL_NUM; i++)
                {
                    for (j = 0; j < RX_LOCAL_NUM; j++)
                    {
                        DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
                    }
                    DBG_CAL("\n");
                }             
                
                ERROR_HOLD;
            }
            else
            {
                DBG_CAL("\n\rCal MUL2 Tx test %02d is OK!",ucShift);
            }
        }
#endif

#endif

    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixMul_PtoP1()  /##/
#endif

#if TEST_CAL_MUL2_2_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixMul_PtoP
 *  Brief: M1 : M*N
 *         M2 : M*N
 *         OUT: M*N
 *         Out[i][j] = M1[i][j]*M2[i][j];
 *  Input: ST_CalMcMatrixParam *pMcMP =>
 * Output: None
 * Return: None
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixMul_PtoP2()
{
    UINT8 i,j;
    UINT8 ucShift;
    SINT16 tmp;
    BOOLEAN flag;
    ST_CalMcMatrixParam XRAM CalParam;
    static UINT8 counter = 0;
    
    DBG_CAL("\n\n\rTest: Matrix MUL2");


    if(counter == 16)
        counter = 0;
    
    ucShift = counter;
    counter ++;  



    DBG_CAL("\nmem-men");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT8)rand()>>2;//-200;
            *(T_tempbuf2 + i*RX_LOCAL_NUM + j) = (SINT8)rand()>>2;//200
        }
//      DBG_CAL_DATA("\n\r%04x,%04x",*(T_tempbuf1 + i*CAL_TEST_RX + j),*(T_tempbuf2 + i*CAL_TEST_RX + j));
    }
    
    //for (ucShift = 0; ucShift < 16; ucShift++)
    {
        CalParam.usSrc1Addr = CAL_TEST_A0;
        CalParam.usSrc2Addr = CAL_TEST_A1;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_TEST_TX;
        CalParam.ucRxLen    = CAL_TEST_RX;
        CalParam.usCalCmd   = OP_MUL2;
        CalParam.ucShift    = ucShift;
        
        DrvCal_MatrixMul2(&CalParam,MUL2_MODE_1);
        //DrvCal_MatrixMul_PtoP2(&CalParam);

        g_ucCalFlag = 0;
        for (i=0; i<CAL_TEST_TX; i++)
        {
            for (j=0; j<CAL_TEST_RX; j++)
            {
                tmp = (*(T_tempbuf1 + i*RX_LOCAL_NUM + j)* (((SINT16)*(T_tempbuf2 + i*RX_LOCAL_NUM + j))));
                tmp >>= ucShift;
                if (tmp > 32767)
                {
                    tmp = 32767;
                }
                else if (tmp < -32768)
                {
                    tmp = -32768;
                }
                if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (SINT16)tmp )
                {
                    DBG_ERROR("\n\rERROR->%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),tmp);
                    g_ucCalFlag = 1;
                }
                else
                {
                    //DBG_CAL_DATA("\n\rOK->   %04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),tmp);
                }
            }
        }
        if (g_ucCalFlag)
        {
            DBG_CAL("\n\rCal MUL2 test %d is Error!",ucShift);
            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }             
            
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rCal MUL2 test %d is OK!",ucShift);
        }     
    }

#if ARAM_CAL_TEST

    DBG_CAL("\n aram-men");
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT8)rand()>>2;
            *(T_tempbuf2 + i*RX_ARAM_NUM + j) = (SINT8)rand()>>2;
        }
//      DBG_CAL_DATA("\n\r%04x,%04x",*(T_tempbuf1 + i*CAL_TEST_RX + j),*(T_tempbuf2 + i*CAL_TEST_RX + j));
    }
    //for (ucShift = 0; ucShift < 16; ucShift++)
    {
        CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
        CalParam.usSrc2Addr = CAL_TEST_A1;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_ARAM_TX;
        CalParam.ucRxLen    = CAL_ARAM_RX;
        CalParam.usCalCmd   = OP_MUL2;
        CalParam.ucShift    = ucShift;

        DrvCal_MatrixMul2(&CalParam,MUL2_MODE_1);
        //DrvCal_MatrixMul_PtoP2(&CalParam);

        g_ucCalFlag = 0;
        for (i=0; i<CAL_ARAM_TX; i++)
        {
            for (j=0; j<CAL_ARAM_RX; j++)
            {
                tmp = (*(g_pAfeAram + i*RX_ARAM_NUM + j)* (((SINT16)*(T_tempbuf2 + i*RX_ARAM_NUM + j))));
                tmp >>= ucShift;
                if (tmp > 32767)
                {
                    tmp = 32767;
                }
                else if (tmp < -32768)
                {
                    tmp = -32768;
                }
                if (*(T_tempOut + i*RX_ARAM_NUM + j) != (SINT16)tmp )
                {
                    DBG_ERROR("\n\rERROR->%04x,%04x",*(T_tempOut + i*RX_ARAM_NUM + j),tmp);
                    g_ucCalFlag = 1;
                }
                else
                {
                    //DBG_CAL_DATA("\n\rOK->   %04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),tmp);
                }
            }
        }
        if (g_ucCalFlag)
        {
            DBG_CAL("\n\rCal MUL2 test %d is Error!",ucShift);
            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }

            DBG_CAL("\n");
            for (i = 0; i < TX_LOCAL_NUM; i++)
            {
                for (j = 0; j < RX_LOCAL_NUM; j++)
                {
                    DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
                }
                DBG_CAL("\n");
            }    

            
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rCal MUL2 test %d is OK!",ucShift);
        }     
    }
#endif    
    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixMul_PtoP2()  /##/
#endif


#if TEST_CAL_COM_1_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixCom_1
 *  Brief: 旧的Base补偿运算
 *  Input: ST_CalMcMatrixParam *pMcMP =>
 * Output: None
 * Return: None
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixCom_1()
{
    UINT8 i,j;
    BOOLEAN flag;
    UINT8 step = 50;
    UINT8 Threshlod = 100;
    ST_CalMcMatrixParam XRAM CalParam;

    DBG_CAL("\n\nTest: Matrix Compensation_1");

    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand()>>1;
            *(T_tempbuf2 + i*RX_LOCAL_NUM + j) = rand()>>8;//0x100;
        }
        //DBG_CAL_DATA("\n\r%04x ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;    // diff
    CalParam.usSrc2Addr = CAL_TEST_A1;    // base
    CalParam.usDstAddr  = CAL_TEST_A2;    // out
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;
    CalParam.usCalCmd   = OP_COM;
    CalParam.ucCfg      = COM_CFG_0;

    DrvCal_MatrixCompensation(&CalParam,Threshlod,step);

    g_ucCalFlag = 0;
    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {

#if COMPENSATION_MODE
            if (   (i >= NO_COMPENSATION_TX_START) && (i <= (NO_COMPENSATION_TX_START+ NO_COMPENSATION_TX_LENGTH)) 
                    &&(j >= NO_COMPENSATION_RX_START) && (j <= (NO_COMPENSATION_RX_START+ NO_COMPENSATION_RX_LENGTH)) )
            {
            }
            else
#endif   
            {

                if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) > Threshlod)
                {
                    if (*(T_tempOut + i*RX_LOCAL_NUM + j) != *(T_tempbuf2 + i*RX_LOCAL_NUM + j) + step )
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR->out=%04x,base=%04x,step=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf2 + i*RX_LOCAL_NUM + j),step);
                    }
                    else
                    {
                        //DBG_CAL_DATA("\n\rOK>->  out=%04x,base=%04x,step=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf2 + i*RX_LOCAL_NUM + j),step);
                    }
                }
                else if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) < -Threshlod)
                {
                    if (*(T_tempOut + i*RX_LOCAL_NUM + j) != *(T_tempbuf2 + i*RX_LOCAL_NUM + j) - step )
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR->out=%04x,base=%04x,step=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf2 + i*RX_LOCAL_NUM + j),step);
                    }
                    else
                    {
                        //DBG_CAL_DATA("\n\rOK<->  out=%04x,base=%04x,step=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf2 + i*RX_LOCAL_NUM + j),step);
                    }
                }
                else
                {
                    if (*(T_tempOut + i*RX_LOCAL_NUM + j) != *(T_tempbuf2 + i*RX_LOCAL_NUM + j))
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR->out=%04x,base=%04x,step=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf2 + i*RX_LOCAL_NUM + j),step);
                    }
                    else
                    {
                        //DBG_CAL_DATA("\n\rOK=->  out=%04x,base=%04x,step=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf2 + i*RX_LOCAL_NUM + j),step);
                    }
                }
            }
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal COM_1 test is Error!");
        
        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }
        
        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }    

        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal COM_1 test is OK!");
    }

    return g_ucCalFlag;
}

#else
#define Test_CAL_MaxtixCom_1      /##/
#endif

#if TEST_CAL_COM_2_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixCom_2
 *  Brief: 新的Base补偿运算
 *  Input: ST_CalMcMatrixParam *pMcMP =>
 * Output: None
 * Return: None
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixCom_2()
{
    UINT8 i,j;
    BOOLEAN flag;
    UINT8 mode;
    UINT8 step = 50;
    UINT8 Threshlod = 100;
    ST_CalMcMatrixParam XRAM CalParam;

    DBG_CAL("\n\nTest Matrix Compensation_2 TX");
    for (i = 0; i < TX_LOCAL_NUM; i++)
    {
        for (j = 0; j < RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand()>>1;
        }
    }
    for (i = 0; i < TX_LOCAL_NUM; i++)
    {
        *(T_tempbuf2 + i) = rand()>>8;//i+20;
    }
    mode = 0;
    CalParam.usSrc1Addr = CAL_TEST_A0;    // diff
    CalParam.usSrc2Addr = CAL_TEST_A1;    // base
    CalParam.usDstAddr  = CAL_TEST_A2;    // out
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;
    CalParam.usCalCmd   = OP_COM;
    CalParam.ucCfg      = COM_CFG_1;

    DrvCal_MatrixCompensation(&CalParam,Threshlod,mode);

    g_ucCalFlag = 0;
    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
#if COMPENSATION_MODE
            if (   (i >= NO_COMPENSATION_TX_START) && (i <= (NO_COMPENSATION_TX_START+ NO_COMPENSATION_TX_LENGTH)) 
                    &&(j >= NO_COMPENSATION_RX_START) && (j <= (NO_COMPENSATION_RX_START+ NO_COMPENSATION_RX_LENGTH)) )
            {
            }
            else
#endif   
            {
                //DBG_CAL_DATA("\n\rBefor->out=%04x,%04x----",*(T_tempOut + i*RX_LOCAL_NUM + j),Threshlod);
                if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) > Threshlod)
                {
                    if (*(T_tempOut + i*RX_LOCAL_NUM + j) != *(T_tempbuf1 + i*RX_LOCAL_NUM + j) - (T_tempbuf2[i]))
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR>->out=%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf1+ i*RX_LOCAL_NUM + j) - T_tempbuf2[i],i);
                    }
                }
                else if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) < -Threshlod)
                {
                    if (*(T_tempOut + i*RX_LOCAL_NUM + j) != *(T_tempbuf1 + i*RX_LOCAL_NUM + j) + T_tempbuf2[i])
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR<->out=%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf1+ i*RX_LOCAL_NUM + j) - T_tempbuf2[i],i);
                    }
                    else
                    {
                        //DBG_CAL("\n\rOK<->   out=%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf1+ i*RX_LOCAL_NUM + j) - T_tempbuf2[i],i);
                    }
                }
                else
                {
                    //DBG_CAL_DATA("\n\rKeep");
                    if (*(T_tempOut + i*RX_LOCAL_NUM + j) != *(T_tempbuf1 + i*RX_LOCAL_NUM + j))
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR=->out=%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf1+ i*RX_LOCAL_NUM + j) - T_tempbuf2[i],i);
                    }
                    else
                    {
                        //DBG_CAL("\n\rOK=->   out=%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf1+ i*RX_LOCAL_NUM + j) - T_tempbuf2[i],i);
                    }
                }
            }
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\nCal COM_2 Tx test is Error!");

        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }
        
        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }    
        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nCal COM_2 Tx test is OK!");
    }


    DBG_CAL("\n\nTest  Matrix Compensation_2 Rx");
    for (i = 0; i < TX_LOCAL_NUM; i++)
    {
        for (j = 0; j < RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand()>>1;
        }
    }
    for (i = 0; i < RX_LOCAL_NUM; i++)
    {
        *(T_tempbuf2 + i) = i+20;
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;    // diff
    CalParam.usSrc2Addr = CAL_TEST_A1;    // base
    CalParam.usDstAddr  = CAL_TEST_A2;    // out
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;
    CalParam.usCalCmd   = OP_COM;
    CalParam.ucCfg      = COM_CFG_1;
    mode = 1;
    DrvCal_MatrixCompensation(&CalParam,Threshlod,mode);

    g_ucCalFlag = 0;
    for (i=0; i<CAL_TEST_RX; i++)
    {
        for (j=0; j<CAL_TEST_TX; j++)
        {
#if COMPENSATION_MODE
            if (   (j >= NO_COMPENSATION_TX_START) && (j <= (NO_COMPENSATION_TX_START+ NO_COMPENSATION_TX_LENGTH)) 
                    &&(i >= NO_COMPENSATION_RX_START) && (i <= (NO_COMPENSATION_RX_START+ NO_COMPENSATION_RX_LENGTH)) )
            {
            }
            else
#endif   
            {
                if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) > Threshlod)
                {
                    if (*(T_tempOut + j*RX_LOCAL_NUM + i) != *(T_tempbuf1 + j*RX_LOCAL_NUM + i) - T_tempbuf2[i])
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR->out=%04x,%04x,%04x",*(T_tempOut + j*RX_LOCAL_NUM + i),*(T_tempbuf1+ j*RX_LOCAL_NUM + i) - T_tempbuf2[i],i);
                    }
                    else
                    {
                        //DBG_CAL("\n\rOK->   out=%04x,%04x,%04x",*(T_tempOut + j*TX_LOCAL_NUM + i),*(T_tempbuf1+ j*TX_LOCAL_NUM + i) - T_tempbuf2[i],i);
                    }
                }
                else if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) < -Threshlod)
                {
                    if (*(T_tempOut + j*RX_LOCAL_NUM + i) != *(T_tempbuf1 + j*RX_LOCAL_NUM + i) + T_tempbuf2[i])
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR->out=%04x,%04x,%04x",*(T_tempOut + j*TX_LOCAL_NUM + i),*(T_tempbuf1+ j*TX_LOCAL_NUM + i) - T_tempbuf2[i],i);
                    }
                }
                else
                {
                    if (*(T_tempOut + j*RX_LOCAL_NUM + i) != *(T_tempbuf1 + j*RX_LOCAL_NUM + i))
                    {
                        g_ucCalFlag = 1;
                        DBG_ERROR("\n\rERROR->out=%04x,%04x,%04x",*(T_tempOut + j*RX_LOCAL_NUM + i),*(T_tempbuf1+ j*RX_LOCAL_NUM + i) - T_tempbuf2[i],i);
                    }

                }
            }
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\nCal COM_2 Rx test is Error!");

        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }
        
        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf2 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }    
        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nCal COM_2 Rx test is OK!");
    }
    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixCom_2      /##/
#endif

#if TEST_CAL_LDS_EN
/*******************************************************************************
 *   Name:
 *  Brief: 用于产生两组座标间的距离
 *         resule[n] = sqrt((S1.xn-S2.xn)^2+(S1.yn-S2.yn)^2)
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_LDS()
{
    UINT8 i,j;
    UINT16 x0,x1,y0,y1;
    BOOLEAN flag;

    UINT16 DisSoft;
    UINT16 DisCal;

    ST_CalMcMatrixParam XRAM CalParam;

   // x0 = 100;
   // x1 = 56;

    DBG_CAL("\n\nTest: LDS %d*%d",CAL_TEST_TX,CAL_TEST_RX);
    for (i=0; i<TX_LOCAL_NUM/2; i++)
    {
        for (j=0; j<RX_LOCAL_NUM*2; j++)
        {
            *(T_tempbuf1 + i*2*RX_LOCAL_NUM + j) = (UINT8)rand();
            *(T_tempbuf2 + i*2*RX_LOCAL_NUM + j) = (UINT8)rand();
        }
    }

    //DisSoft = (x0-x1)*(x0-x1)*2;
    //DisSoft = sqrt(DisSoft);

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usSrc2Addr = CAL_TEST_A1;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX/2;
    CalParam.ucRxLen    = CAL_TEST_RX;
    CalParam.usCalCmd   = OP_LDS;

    DrvCal_LDS(&CalParam);


    DBG_CAL("\n\nAfter LDS");
    for (i=0; i<CAL_TEST_TX/2; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
            x0 = *(T_tempbuf1 + i*2*RX_LOCAL_NUM + 2*j);
            y0 = *(T_tempbuf1 + i*2*RX_LOCAL_NUM + 2*j+1);
            x1 = *(T_tempbuf2 + i*2*RX_LOCAL_NUM + 2*j);
            y1 = *(T_tempbuf2 + i*2*RX_LOCAL_NUM + 2*j+1); 
            
            DisSoft = sqrt(((UINT32)x0-x1)*((UINT32)x0-x1)+((UINT32)y0-y1)*((UINT32)y0-y1));
            DisCal = *(T_tempOut + i*RX_LOCAL_NUM + j);
            
            if (DisSoft != DisCal)
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\nLDS error soft:%d,cal:%d",DisSoft,DisCal);
                DBG_ERROR("\nx0=%d,x1=%d,y1=%d,y2=%d",x0,x1,y0,y1);
            }
        }
    }

    if(g_ucCalFlag)
    {
        DBG_CAL("\nLDS ERROR"); 

        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }
        
        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }    
        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nLDS OK");
    }
    return 0;   
}
#else
#define Test_CAL_LDS      /##/
#endif

#if TEST_CAL_MDS_EN
/*******************************************************************************
 *   Name:
 *  Brief: 用于产生两列座标间的距离point to point
 *         resule[M*N] = sqrt((S1.x0-S2.x0)^2+(S1.y0-S2.y0)^2)+...+ sqrt((S1.xn-S2.xn)^2+(S1.yn-S2.yn)^2)
 *        输入宽度为2*Tx与2*Rx的 坐标数组，生产Tx*Rx距离矩阵，CAL模块输出固定为Max = 11，即11*11矩阵
 *        测试代码固定用11*11来测
 *  Input: 
 * Output:
 * Return:
 *******************************************************************************/
#define MDS_TX_LEN 11
#define MDS_RX_LEN 11

BOOLEAN Test_CAL_MDS()
{
#if 0
    UINT8 i,j;
    UINT8 tx_len = 11;
    UINT8 rx_len = 11;
    UINT16 buf0[CAL_MDS_TX_POINT*2];
    UINT16 buf1[CAL_MDS_RX_POINT*2];
    UINT16 buf2[CAL_MDS_TX_POINT*CAL_MDS_RX_POINT];
    UINT16 temp;
    BOOLEAN g_ucCalFlag = 0;
//    UINT16 DisSoft;
//    UINT16 DisCal;
    ST_CalMcMatrixParam XRAM CalParam;


    for (i = 0; i< 22 ;i++)
    {
        buf0[i] = i*2;
        buf1[i] = i*4;
    }
    
    //Cal运算数据初始化
    DBG_CAL("\n\nTest: MDS %d*%d\n",tx_len,rx_len);

    for (i = 0; i<tx_len*2; i++)
    {

            *(T_tempbuf1 + i) = buf0[i];
    }
    for (i = 0; i<rx_len*2; i++)
    {

            *(T_tempbuf2 + i) = buf1[i];
    }

//soft 
    for(i = 0;i < rx_len;i++)
        for(j = 0;j<tx_len;j++)
        {
            temp = (buf0[i*2] - buf1[j*2])*(buf0[i*2] - buf1[j*2]);
            temp += (buf0[i*2+1] - buf1[j*2+1])*(buf0[i*2+1] - buf1[j*2+1]);
            buf2[i*rx_len+j] = sqrt(temp);
        }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usSrc2Addr = CAL_TEST_A1;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxNum    = tx_len;
    CalParam.ucRxNum    = rx_len;
    CalParam.ucTxLen    = tx_len;
    CalParam.ucRxLen    = rx_len;
    CalParam.usCalCmd   = OP_MDS;

    DrvCal_MDS(&CalParam);

    for (i=0; i<tx_len; i++)
    {
        for (j=0; j<rx_len; j++)
        {
//            DBG_CAL("\nsoft data %x,%x :%x ",i,j,buf2[i*CAL_TEST_RX+j]);
//            DBG_CAL("Cal :%x",*(T_tempOut+i*CAL_TEST_RX+j));
            if(buf2[i*rx_len+j] != *(T_tempOut+i*rx_len+j))
            {
                flag = 1;
            }
        }
    }
    if(flag)
    {
        DBG_CAL("\nMDS ERROR");
    }
    else
    {
        DBG_CAL("\nMDS OK");
    }
    return 0;
#else
    UINT8 i,j;
    UINT16 x0,x1,y0,y1;
    BOOLEAN flag;

    UINT16 DisSoft;
    UINT16 DisCal;

    ST_CalMcMatrixParam XRAM CalParam;

   // x0 = 120;
   // x1 = 111;

    DBG_CAL("\n\rTest: MDS %d*%d",CAL_TEST_TX,CAL_TEST_RX);

    for (i=0; i<MDS_TX_LEN*2; i++)
    {
        *(T_tempbuf1 + i) = (UINT8)rand();//x0;
    }

    for (i=0; i<MDS_RX_LEN*2; i++)
    {
        *(T_tempbuf2 + i) = (UINT8)rand();//x0;
    }

    //DisSoft = (x0-x1)*(x0-x1)*2;
    //DisSoft = sqrt(DisSoft);

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usSrc2Addr = CAL_TEST_A1;
    CalParam.usDstAddr  = CAL_TEST_A2;
    //CalParam.ucTxNum    = 11;
    //CalParam.ucRxNum    = 11;
    CalParam.ucTxLen    = MDS_TX_LEN;
    CalParam.ucRxLen    = MDS_RX_LEN;
    CalParam.usCalCmd   = OP_MDS;

    DrvCal_MDS(&CalParam);

    DBG_CAL("\n\nAfter MDS\n");
    for (i=0; i<MDS_TX_LEN; i++)
    {
        for (j=0; j<MDS_RX_LEN; j++)
        {

            x0 = *(T_tempbuf1 + 2*j);
            y0 = *(T_tempbuf1 + 2*j+1);
            x1 = *(T_tempbuf2 + 2*i);
            y1 = *(T_tempbuf2 + 2*i+1); 
            
            DisSoft = sqrt(((UINT32)x0-x1)*((UINT32)x0-x1)+((UINT32)y0-y1)*((UINT32)y0-y1));       
            DisCal = *(T_tempOut + j*11 + i);
            if (DisSoft != DisCal)
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\rMDS ERROR->out:%04x,soft=%04x",DisCal,DisSoft);
                ERROR_HOLD;
                return 1;
            } 
            else
            {
                //DBG_CAL("\n\rMDS OK   ->out:%04x,soft=%04x",DisCal,DisSoft);
            }
        }
    }
    DBG_CAL("\nMDS OK");
    return 0;
#endif    
}
#else
#define Test_CAL_MDS      /##/
#endif

#if TEST_CAL_CHK_EN
/*******************************************************************************
 *   Name: Test_CAL_CHK
 *  Brief: 均匀度检查
 *         1.一列数据 差值 = 最大值 - 最小值
 *         2.所有列的差值中求最大值 max = max(差值)
 *  Input: UINT16 usSrc1Addr
 *         UINT8  Tx
 *         UINT8  Rx
 * Output: None
 * Return: Get Max of value,which is sub value of max-min in the same column
 *******************************************************************************/
BOOLEAN Test_CAL_CHK()
{
    BOOLEAN flag = 0;
    UINT8 i,j;
    UINT16 check;

    UINT16 max;
    UINT16 min;
    UINT16 max_all;
    UINT16 XRAM RxMax[CAL_TEST_RX];
    DBG_CAL("\n");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            T_tempbuf1[i*RX_LOCAL_NUM + j] = (SINT16)rand()>>1;//0x100 + i;
        }
        //DBG_CAL_DATA("%04x ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
    }

    DBG_CAL("\n\nTest: CHK");
    DBG_CAL("\nmen");

    max_all = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        min = 0x7FFF;
        max = 0;
        for (j = 0; j < CAL_TEST_TX; j++)
        {
            if (T_tempbuf1[j*RX_LOCAL_NUM + i] > max)
            {
                max = T_tempbuf1[j*RX_LOCAL_NUM + i];
            }
            if (T_tempbuf1[j*RX_LOCAL_NUM + i] < min)
            {
                min = T_tempbuf1[j*RX_LOCAL_NUM + i];
            }
        }
        RxMax[i] = max - min;
        if (RxMax[i] > max_all)
        {
            max_all = RxMax[i];
        }
    }

    check = DrvCal_Noise(CAL_TEST_A0,CAL_TEST_TX,CAL_TEST_RX);

    if (max_all != check)
    {
        g_ucCalFlag = 1;
    }

    DBG_CAL("\nCHK = 0x%x,soft:0x%x",check,max_all);

    if (g_ucCalFlag)
    {
        DBG_CAL("\nError");
        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(T_tempbuf1 + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }
                
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nOK!");
    }

#if ARAM_CAL_TEST

    #if 1
    DBG_CAL("\naram");

     for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            g_pAfeAram[i*RX_ARAM_NUM + j] = (SINT16)rand()>>1;//0x100 + i;
        }
        //DBG_CAL_DATA("%04x ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
    }   
    
     max_all = 0;
     for (i = 0; i < CAL_ARAM_RX; i++)
     {
         min = 0x7FFF;
         max = 0;
         for (j = 0; j < CAL_ARAM_TX; j++)
         {
             if (g_pAfeAram[j*RX_ARAM_NUM + i] > max)
             {
                 max = g_pAfeAram[j*RX_ARAM_NUM + i];
             }
             if (g_pAfeAram[j*RX_ARAM_NUM + i] < min)
             {
                 min = g_pAfeAram[j*RX_ARAM_NUM + i];
             }
         }
         RxMax[i] = max - min;
         if (RxMax[i] > max_all)
         {
             max_all = RxMax[i];
         }
     }
    
     check = DrvCal_Noise(ARAM_DATA_BASE_ADDR,CAL_ARAM_TX,CAL_ARAM_RX);
    
     if (max_all != check)
     {
         g_ucCalFlag = 1;
     }
    
     DBG_CAL("\nCHK = 0x%x,soft:0x%x",check,max_all);
    
     if (g_ucCalFlag)
     {
         DBG_CAL("\nError");

        DBG_CAL("\n");
        for (i = 0; i < TX_LOCAL_NUM; i++)
        {
            for (j = 0; j < RX_LOCAL_NUM; j++)
            {
                DBG_CAL(" %04x",*(g_pAfeAram + i*RX_LOCAL_NUM + j)); 
            }
            DBG_CAL("\n");
        }         
         ERROR_HOLD;
     }
     else
     {
         DBG_CAL("\nOK!");
     }
    #endif
#endif	
    return g_ucCalFlag;
}

#else
#define Test_CAL_CHK      /##/
#endif

#if TEST_CAL_CRC_EN
#define AL2_FCS_COEF                ((1 << 15) + (1 << 10) + (1 << 3))     //((1 << 7) + (1 << 6) + (1 << 5))
/*******************************************************************************
 *   Name: GetCrc16
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
UINT16 GetCrc16(UINT32 addr,UINT16 length,UINT8 bPram)
{
    UINT16 cFcs = 0;
    UINT32 i, j;
 
    for ( i = 0; i < length; i++ )
    {
        if ((bPram == CRC_SRC_FE_ZONE)||(bPram == CRC_SRC_FF_ZONE))
        {
            #if 0
            if(((UINT32)addr + (i<<1)) < 0x1800)
            {
                 cFcs ^= PRAM_ADDR16((addr+i*2));               
            }
            else
            {          
                j = addr - 0x1800 + (i<<1);           
                cFcs ^= PRAM1_ADDR16(j);     
            }
            #else
            
            cFcs ^= PRAM_ADDR16(addr+i*2);
            #endif
        }
        else if(bPram == CRC_SRC_DRAM)
        {
            cFcs ^= DRAM_ADDR16((addr+i*2));
        }
        else if(bPram == CRC_SRC_FD_ZONE)
        {
            cFcs ^= PROM_ADDR16((addr+i*2));
        }           
        
        for (j = 0; j < 16; j ++)
        {
            if (cFcs & 1)
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
/*******************************************************************************
 *   Name: Test_CAL_CRC
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_CRC()
{
    BOOLEAN flag = 0;

    UINT16 ResultCal;
    UINT16 ResultSoft;

    DBG_CAL("\n\nTest: CRC");

    //--------------------------------------------------------------------------
#if 0
    DBG_CAL("\nDram:");
    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
            *(T_tempbuf1 + i*CAL_TEST_RX + j) = rand(); //0x43;
            //DBG_CAL("\n j = %d, dt = %x",j,*(T_tempbuf1 + i*CAL_TEST_RX + j));
        }
    }

    // 需要设置 CRC_TYPE 0
    ResultCal = DrvCal_CRC16((UINT16)T_tempbuf1,CAL_TEST_TX*CAL_TEST_RX,CRC_SRC_DRAM,CRC_MOD_CRC,0);
    DBG_CAL("\nCal CRC = %x",ResultCal);


    ResultSoft = GetCrc16((UINT16)T_tempbuf1,CAL_TEST_TX*CAL_TEST_RX,0);
    DBG_CAL("\nSoft CRC = %x",ResultSoft);

    if (ResultCal != ResultSoft)
    {
        g_ucCalFlag = 1;
        DBG_CAL("\nError");
        return 1;
    }
    else
    {
        DBG_CAL("\nOK");
    }
#endif

    //--------------------------------------------------------------------------
#if 1
    DBG_CAL("\n\rPram:");

    // 需要设置 CRC_TYPE 0
    ResultCal = DrvCal_CRC16(0xE800,35*1024,CRC_SRC_FE_ZONE,CRC_MOD_CRC);

    DBG_CAL("\n\rCal CRC = %x",ResultCal);
        
    ResultSoft = GetCrc16(0x0000,35*1024,CRC_SRC_FE_ZONE);

    DBG_CAL("\n\rSoft CRC = %x",ResultSoft);

    if (ResultCal != ResultSoft)
    {
        g_ucCalFlag = 1;
        DBG_CAL("\n\rError");
        ERROR_HOLD;
        return 1;
    }
    else
    {
        DBG_CAL("\n\rOK");
    }
#endif

#if 1
    DBG_CAL("\n\rProm:");

    // 需要设置 CRC_TYPE 0
    ResultCal = DrvCal_CRC16(0x00,2*1024,CRC_SRC_FD_ZONE,CRC_MOD_CRC);
    DBG_CAL("\n\rCal CRC = %x",ResultCal);


    ResultSoft = GetCrc16(0x00,2*1024,CRC_SRC_FD_ZONE);
    DBG_CAL("\n\rSoft CRC = %x",ResultSoft);

    if (ResultCal != ResultSoft)
    {
        g_ucCalFlag = 1;
        DBG_CAL("\n\rError");
        ERROR_HOLD;
        return 1;
    }
    else
    {
        DBG_CAL("\n\rOK");
    }    
#endif
    return g_ucCalFlag;
}

#else
#define Test_CAL_CRC      /##/
#endif

#if TEST_CAL_XORSUM_EN
/*******************************************************************************
 *   Name: GetCrc16
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
UINT16 GetXorSum(UINT32 addr,UINT16 length,UINT8 bPram)
{
    UINT16 cFcs = 0;
    UINT32 i,j;
    for ( i = 0; i < length; i++ )
     {
         if ((bPram == CRC_SRC_FF_ZONE)||(bPram == CRC_SRC_FE_ZONE))
         {
         #if 0
             if((addr + (i<<1)) < 0x1800)
             {
                  cFcs ^= PRAM_ADDR16((addr+i*2));               
             }
             else
             {          
                 j = addr - 0x1800 + (i<<1);           
                 cFcs ^= PRAM1_ADDR16(j);     
             }
         #else
             
             cFcs ^= PRAM_ADDR16(addr+i*2);
         #endif
         }
         else if(bPram == CRC_SRC_DRAM)
         {
             cFcs ^= DRAM_ADDR16((addr+i*2));
         }
         else if(bPram == CRC_SRC_FD_ZONE)
         {
             cFcs ^= PROM_ADDR16((addr+i*2));
         }           
         
     }

    return cFcs;
}

/*******************************************************************************
 *   Name: Test_CAL_XORSUM
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
BOOLEAN Test_CAL_XORSUM()
{
    UINT8 i,j;
    BOOLEAN flag = 0;
    UINT16 ResultCal;
    UINT16 ResultSoft;

    DBG_CAL("\n\nTest: XORSUM");

    //--------------------------------------------------------------------------
    DBG_CAL("\nDram:");
    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
            *(T_tempbuf1 + i*CAL_TEST_RX + j) = rand();
        }
    }
    // 需要设置 CRC_TYPE 1    
    ResultCal = DrvCal_CRC16((UINT16)T_tempbuf1,CAL_TEST_TX*CAL_TEST_RX*2,CRC_SRC_DRAM,CRC_MOD_XOR);
    DBG_CAL("\nCal Xorsum = %x",ResultCal);

    ResultSoft = GetXorSum((UINT16)T_tempbuf1,CAL_TEST_TX*CAL_TEST_RX*2,0);
    DBG_CAL("\n\rSoft Xorsum = %x",ResultSoft);

    if (ResultCal != ResultSoft)
    {
        g_ucCalFlag = 1;
        DBG_CAL("\nError");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\nOK");
    }
	
#if 1
    //--------------------------------------------------------------------------
    DBG_CAL("\n\rPram:");

    // 需要设置 CRC_TYPE 1  
    ResultCal = DrvCal_CRC16(0xE800,35*1024,CRC_SRC_FE_ZONE,CRC_MOD_XOR);
    DBG_CAL("\n\rCal Xorsum = %x",ResultCal);

    ResultSoft = GetXorSum(0x0000,35*1024,CRC_SRC_FE_ZONE);
    DBG_CAL("\n\rSoft Xorsum = %x",ResultSoft);

    if (ResultCal != ResultSoft)
    {
        g_ucCalFlag = 1;
        DBG_CAL("\n\rError");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rOK");
    }
#endif


#if 1
        //--------------------------------------------------------------------------
        DBG_CAL("\n\rProm:");
    
        // 需要设置 CRC_TYPE 1  
        ResultCal = DrvCal_CRC16(0x00,2*1024,CRC_SRC_FD_ZONE,CRC_MOD_XOR);
        DBG_CAL("\n\rCal Xorsum = %x",ResultCal);
    
        ResultSoft = GetXorSum(0x0000,2*1024,CRC_SRC_FD_ZONE);
        DBG_CAL("\n\rSoft Xorsum = %x",ResultSoft);
    
        if (ResultCal != ResultSoft)
        {
            g_ucCalFlag = 1;
            DBG_CAL("\n\rError");
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rOK");
        }
#endif

    return g_ucCalFlag;
}

#else
#define Test_CAL_XORSUM      /##/
#endif


#if TEST_CAL_MAC_1_EN
#define MAC_NOISE_THD   0
/*******************************************************************************
 *   Name: Test_CAL_MAC_1
 *  Brief: 子区域模式MAC算法
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/

void Test_CAL_MAC_1()
{
    UINT8 i,j;
    SINT32 ulSum_c  = 0;
    SINT32 ulSum_tx = 0;
    SINT32 ulSum_rx = 0;
    ST_CalMcMacParam XRAM CalParam;

    DBG_CAL("\n\nCal Mac test start\n");

    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = rand();
            *(T_tempbuf2 + i*RX_LOCAL_NUM + j) = 0x00;
        }
    }

    #if 0
    T_tempbuf1[2*RX_LOCAL_NUM + 2] = rand();
    T_tempbuf1[2*RX_LOCAL_NUM + 3] = rand();
    T_tempbuf1[2*RX_LOCAL_NUM + 4] = rand();

    T_tempbuf1[3*RX_LOCAL_NUM + 2] = rand();
    T_tempbuf1[3*RX_LOCAL_NUM + 3] = rand();
    T_tempbuf1[3*RX_LOCAL_NUM + 4] = rand();

    T_tempbuf1[4*RX_LOCAL_NUM + 2] = rand();
    T_tempbuf1[4*RX_LOCAL_NUM + 3] = rand();
    T_tempbuf1[4*RX_LOCAL_NUM + 4] = rand();
    #endif
    

    CalParam.usDiffAddr    = CAL_TEST_A0 + (MAC_TX_START*RX_LOCAL_NUM + MAC_RX_START)*2;  // 子区域模式
    CalParam.usCalOutAddr  = CAL_TEST_A1;    
    CalParam.ucTxStart     = MAC_TX_START;
    CalParam.ucRxStart     = MAC_RX_START;
    CalParam.ucTxLen       = MAC_TX_LEN;
    CalParam.ucRxLen       = MAC_RX_LEN;
    //CalParam.ucTxNum       = TX_LOCAL_NUM;
    //CalParam.ucRxNum       = RX_LOCAL_NUM;    
    CalParam.ucMode        = (MAC_CFG_0<<1) + MAC_MOD_0;
    CalParam.ucNoise       = MAC_NOISE_THD;

    DrvCal_Mac(&CalParam);

    for (i = MAC_TX_START; i<(MAC_TX_START+MAC_TX_LEN); i++)
    {
        for (j = MAC_RX_START; j<(MAC_RX_START+MAC_RX_LEN); j++)
        {
#if 1   // MAC_MOD_0 负值丢弃模式    
            if ((T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD) >= 0)
            {
                ulSum_c  += T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD;
                ulSum_tx += ((T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD)*i);
                ulSum_rx += ((T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD)*j);
            }
#else   // MAC_MOD_1 绝对值>0不丢弃模式  
            if ((T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD) >= 0)
            {   
                ulSum_c  += (T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD);
                ulSum_tx += ((T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD)*i);
                ulSum_rx += ((T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD)*j);
            }
            else if ((0-T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD) >= 0)
            {
                ulSum_c  += (0-T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD);
                ulSum_tx += ((0-T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD)*i);
                ulSum_rx += ((0-T_tempbuf1[i*RX_LOCAL_NUM + j] - MAC_NOISE_THD)*j);
            }
#endif
        }
    }
  
    DBG_CAL("\n\r%08lx %08lx %08lx",ulSum_c,ulSum_tx,ulSum_rx);

    DBG_CAL("\n");
    for (i=0; i<6; i++)
    {
        DBG_CAL("%04x ",*(T_tempbuf2 + i));
    }
    if(((SINT16)(ulSum_c>>16)==T_tempbuf2[0])&&((SINT16)(ulSum_c&0xFFFF) == T_tempbuf2[1])\
      &&((SINT16)(ulSum_tx>>16)==T_tempbuf2[2])&&((SINT16)(ulSum_tx&0xFFFF) == T_tempbuf2[3])\
      &&((SINT16)(ulSum_rx>>16)==T_tempbuf2[4])&&((SINT16)(ulSum_rx&0xFFFF) == T_tempbuf2[5]))

    {
        DBG_CAL("\nMAC_1 OK");
    }
    else
    {
         DBG_CAL("\nMAC_1 ERROR");
         ERROR_HOLD;
    }

    
}
#else
#define Test_CAL_MAC_1      /##/
#endif

#if TEST_CAL_MAC_2_EN
#define MAC_NOISE_THD   0
/*******************************************************************************
 *   Name: Test_CAL_MAC_2
 *  Brief: 重构模式MAC算法
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
void Test_CAL_MAC_2()
{
    UINT8 i,j;
    SINT32 ulSum_c  = 0;
    SINT32 ulSum_tx = 0;
    SINT32 ulSum_rx = 0;
    ST_CalMcMacParam XRAM CalParam;

    DBG_CAL("\n\nCal Mac test start\n");

    #if 1
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = rand();
            *(T_tempbuf2 + i*RX_LOCAL_NUM + j) = 0x00;
        }
    }
    #else
    T_tempbuf1[0] = 0x200;
    T_tempbuf1[1] = 0x200;
    T_tempbuf1[2] = 0x100;

    T_tempbuf1[3] = 0x100;
    T_tempbuf1[4] = 0x100;
    T_tempbuf1[5] = 0x200;

    T_tempbuf1[6] = 0x100;
    T_tempbuf1[7] = 0x200;
    T_tempbuf1[8] = 0x100;
    #endif
    CalParam.usDiffAddr    = CAL_TEST_A0;
    CalParam.usCalOutAddr  = CAL_TEST_A1;
    CalParam.ucTxStart     = 0;
    CalParam.ucRxStart     = 0;
    CalParam.ucTxLen       = MAC_TX_LEN;
    CalParam.ucRxLen       = MAC_RX_LEN;
    CalParam.ucMode        = (MAC_CFG_1<<1) + MAC_MOD_1;
    CalParam.ucNoise       = MAC_NOISE_THD;

    DrvCal_Mac(&CalParam);

    for (i = 0; i<MAC_TX_LEN; i++)
    {
        for (j = 0; j<MAC_RX_LEN; j++)
        {
#if 0   // MAC_MOD_0 负值丢弃模式    
            if ((T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD) >= 0)
            {
                ulSum_c  += T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD;
                ulSum_tx += ((T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD)*i);
                ulSum_rx += ((T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD)*j);
            }
#else   // MAC_MOD_1 绝对值>0不丢弃模式  
            if ((T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD) >= 0)
            {
                ulSum_c  += (T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD);
                ulSum_tx += ((T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD)*i);
                ulSum_rx += ((T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD)*j);
            }
            else if ((0-T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD) >= 0)
            {
                ulSum_c  += (0-T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD);
                ulSum_tx += ((0-T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD)*i);
                ulSum_rx += ((0-T_tempbuf1[i*MAC_RX_LEN + j] - MAC_NOISE_THD)*j);
            }
#endif

        }
    }
    DBG_CAL("\n%08lx %08lx %08lx",ulSum_c,ulSum_tx,ulSum_rx);

    DBG_CAL("\n");
    for (i=0; i<6; i++)
    {
        DBG_CAL("%04x ",*(T_tempbuf2 + i));
    }


if(((SINT16)(ulSum_c>>16)==T_tempbuf2[0])&&((SINT16)(ulSum_c&0xFFFF) == T_tempbuf2[1])\
  &&((SINT16)(ulSum_tx>>16)==T_tempbuf2[2])&&((SINT16)(ulSum_tx&0xFFFF) == T_tempbuf2[3])\
  &&((SINT16)(ulSum_rx>>16)==T_tempbuf2[4])&&((SINT16)(ulSum_rx&0xFFFF) == T_tempbuf2[5]))    
    {
        DBG_CAL("\nMAC_2 OK");
    }
    else
    {
         DBG_CAL("\nMAC_2 ERROR");
         ERROR_HOLD;
    }

}
#else
#define Test_CAL_MAC_2      /##/
#endif

#if TEST_CAL_ID_EN
/*******************************************************************************
 *   Name: Test_CAL_ID
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
void Test_CAL_ID()
{
    UINT8 i;
    UINT8 ucLastNum = 4;
    UINT8 ucCurrNum = 8;
    UINT8 ucMaxNum  = 10;
    ST_CalKmIdParam XRAM stKmIDp;

    DBG_CAL("\n\nCal ID test start");

    /* 将上一帧所有点的原始坐标信息拷贝到LastIDPos中，准备CAL计算输入数据 */
    for (i = 0; i < (ucMaxNum << 1); i++ )
    {
        g_stFrmData.CurrIdPos[i] = 0x7FFF;
        g_stFrmData.LastIdPos[i] = 0x7FFF;
    }

    for (i = 0; i < ucLastNum; i++)
    {
        g_stFrmData.LastIdPos[2*i]   = i*10;
        g_stFrmData.LastIdPos[2*i+1] = i*10;
    }

    for (i = 0; i < ucCurrNum; i++)
    {
        g_stFrmData.CurrIdPos[2*i]   = (ucCurrNum-i)*10 + 1;
        g_stFrmData.CurrIdPos[2*i+1] = (ucCurrNum-i)*10 + 1;
    }

    stKmIDp.usLastIdPosAddr = (UINT16)g_stFrmData.LastIdPos;
    stKmIDp.usCurrIdPosAddr = (UINT16)g_stFrmData.CurrIdPos;
    stKmIDp.usCalOut   = (UINT16)T_tempOut;
    stKmIDp.ucLastPoint = ucLastNum;
    stKmIDp.ucCurrPoint = ucCurrNum;

    DBG_CAL("\n\rFirst ID:L=%d,N=%d",ucLastNum,ucCurrNum);
    DrvCal_KmID(&stKmIDp);

    for (i = 0; i < ucMaxNum; i++)
    {
        UINT8 id;
        id = *(UINT16*)(T_tempOut + i);

        if (id == 0x0F)
        {
            DBG_CAL("\n\rID%x:  %2d--  %4d--XXXX",i,id + 1, g_stFrmData.LastIdPos[i*2]);
        }
        else
        {
            DBG_CAL("\n\rID%x:  %2d--  %4d--  %4d",i,id + 1, g_stFrmData.LastIdPos[i*2], g_stFrmData.CurrIdPos[id*2]);
        }
    }

    if((*(UINT16*)(T_tempOut ) != 7)||(*(UINT16*)(T_tempOut + 1) != 6)||(*(UINT16*)(T_tempOut + 2) != 5)||(*(UINT16*)(T_tempOut + 3) != 4))
    {
        DBG_CAL("\nERROR");
        ERROR_HOLD;
    }

    ucLastNum = 8;
    ucCurrNum = 4;
    stKmIDp.ucLastPoint = ucLastNum;
    stKmIDp.ucCurrPoint = ucCurrNum;

    DBG_CAL("\n\nSecond ID:L=%d,N=%d",ucLastNum,ucCurrNum);

    for (i = 0; i < (ucMaxNum << 1); i++ )
    {
        g_stFrmData.CurrIdPos[i] = 0x7FFF;
        g_stFrmData.LastIdPos[i] = 0x7FFF;
    }

    for (i = 0; i < ucLastNum; i++)
    {
        g_stFrmData.LastIdPos[2*i]   = i*10;
        g_stFrmData.LastIdPos[2*i+1] = i*10;
    }

    for (i = 0; i < ucCurrNum; i++)
    {
        g_stFrmData.CurrIdPos[2*i]   = i*10 + 1;
        g_stFrmData.CurrIdPos[2*i+1] = i*10 + 1;
    }

    DrvCal_KmID(&stKmIDp);

    for (i = 0; i < ucMaxNum; i++)
    {
        UINT8 id;
        id = *(UINT16*)(T_tempOut + i);
        if (id == 0x0F)
        {
            DBG_CAL("\n\rID%x:%2d--%4d--XXXX",i,id + 1, g_stFrmData.LastIdPos[i*2]);
        }
        else
        {
            DBG_CAL("\n\rID%x:%2d--%4d--%4d",i,id + 1, g_stFrmData.LastIdPos[i*2], g_stFrmData.CurrIdPos[id*2]);
        }
    }
    
    if((*(UINT16*)(T_tempOut ) != 0)||(*(UINT16*)(T_tempOut + 1) != 1)||(*(UINT16*)(T_tempOut + 2) != 2)||(*(UINT16*)(T_tempOut + 3) != 3))
    {
        DBG_CAL("\nERROR");
        ERROR_HOLD;
    }

    
}
#else
#define Test_CAL_ID      /##/
#endif

#if TEST_CAL_PKS_EN
/*******************************************************************************
 *   Name: Test_CAL_SearchPeak
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
void Test_CAL_SearchPeak()
{
    UINT8 i,j;
    UINT8 ucPeakValidGroup;
    UINT8 ucPeakValidPos;
    UINT16 XRAM ausNegPeaks[MAX_PEAK + 1];
    UINT16 *pNegPeakBuf;
    ST_CalMcPeakDetectParam XRAM stMcPDP;
    ST_CalMcPeakInfo XRAM stMcPI;
    ST_PeakData  XRAM  g_stPeakData;


    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            T_tempbuf3[i*RX_LOCAL_NUM + j] = 0;
        }
    }
    DBG_CAL("\n\nCal Search Peak test start\n");


    T_tempbuf3[2*RX_LOCAL_NUM + 7] = -400;
    T_tempbuf3[2*RX_LOCAL_NUM + 8] = 100;
    T_tempbuf3[2*RX_LOCAL_NUM + 9] = 100;

    T_tempbuf3[3*RX_LOCAL_NUM + 7] = -250;
    T_tempbuf3[3*RX_LOCAL_NUM + 8] = 800;
    T_tempbuf3[3*RX_LOCAL_NUM + 9] = -200;

    T_tempbuf3[4*RX_LOCAL_NUM + 7] = -200;
    T_tempbuf3[4*RX_LOCAL_NUM + 8] = -200;
    T_tempbuf3[4*RX_LOCAL_NUM + 9] = 100;

    T_tempbuf3[8*RX_LOCAL_NUM + 8] = -1200;
    T_tempbuf3[5*RX_LOCAL_NUM + 9] = 8100;

    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
            DBG_CAL_DATA("%04d ",T_tempbuf3[i*RX_LOCAL_NUM + j]);
        }
        DBG_CAL_DATA("\n");
    }

    //必须偶数
    pNegPeakBuf = (UINT16 *)((UINT16)(ausNegPeaks+1)& 0xFFFE);

    /* step2: DrvCal_McPeak 参数设置 */
    stMcPDP.usDiffAddr = CAL_TEST_PKS;
    stMcPDP.usNegOutAddr = (UINT16)pNegPeakBuf;
    stMcPDP.usCalOutAddr = CAL_TEST_A2;

    stMcPDP.ucTxLen = CAL_TEST_TX;
    stMcPDP.ucRxLen = CAL_TEST_RX;
    stMcPDP.usPosThd     = 200;
    stMcPDP.usNegThd     = -200;
    stMcPDP.usAreaThd    = 50;
    stMcPDP.usNegAreaThd = -50;

    stMcPDP.ucMaxPeakNum = MAX_PEAK - 1;//0表示MaxPeakNum为1，MAX_PEAK-1表示MaxPeakNum为MAX_PEAK
    stMcPDP.ucSearchMod  = 0;//0:十字;1米字 

    /* step3: DrvCal_McPeak */
    DrvCal_McPeak(&stMcPDP, &stMcPI);

    /* step4: 取出DrvCalMCPeak 结果 */
    g_stPeakData.ucMcPosPeakNum = stMcPI.ucMcPosPeakNum;
    g_stPeakData.ucMcNegPeakNum = stMcPI.ucMcNegPeakNum;
    g_stPeakData.ucMcPosAreaChNum = stMcPI.ucMcPosAreaChNum;
    g_stPeakData.ucMcNegAreaChNum = stMcPI.ucMcNegAreaChNum;

    //正peak
    for (i = 0; i < g_stPeakData.ucMcPosPeakNum; i++)
    {
        ucPeakValidGroup = i >> 3;
        ucPeakValidPos = VALID << (i & 0x7);
        g_stPeakData.aucMcPeakValid[ucPeakValidGroup] |= ucPeakValidPos;

        g_stPeakData.aucMcPosPeak[i][0] = T_tempOut[i] >> 8;  //TX 位置
        g_stPeakData.aucMcPosPeak[i][1] = T_tempOut[i] %256;  //RX 位置
    }
    //负peak
    for (i = 0; i < g_stPeakData.ucMcNegPeakNum; i++)
    {
        g_stPeakData.aucMcNegPeak[i][0] = pNegPeakBuf[i] >> 8;   //TX 位置
        g_stPeakData.aucMcNegPeak[i][1] = pNegPeakBuf[i] %256;   //RX 位置
    }

    if (g_stPeakData.ucMcPosPeakNum > 0)
    {
        DBG_CAL("\npeak pos:%x--%x",2,g_stPeakData.ucMcPosPeakNum);
        DBG_CAL("\npeak neg:%x--%x",2,g_stPeakData.ucMcNegPeakNum);
        DBG_CAL("\nArea pos:%x--%x",2,g_stPeakData.ucMcPosAreaChNum);
        DBG_CAL("\nArea Neg:%x--%x",2,g_stPeakData.ucMcNegAreaChNum);

        for (i = 0; i < g_stPeakData.ucMcPosPeakNum; i++)
        {
            DBG_CAL("\npos%x:%x-%x",i,g_stPeakData.aucMcPosPeak[i][0],g_stPeakData.aucMcPosPeak[i][1]);
        }

        for (i = 0; i < g_stPeakData.ucMcNegPeakNum; i++)
        {
            DBG_CAL("\nNeg%x:%x-%x",i,g_stPeakData.aucMcNegPeak[i][0],g_stPeakData.aucMcNegPeak[i][1]);
        }
    }

    if((g_stPeakData.ucMcPosPeakNum != 2)||(g_stPeakData.ucMcNegPeakNum != 4)||(g_stPeakData.ucMcPosAreaChNum != 5)||(g_stPeakData.ucMcNegAreaChNum != 6))
    {
        DBG_CAL("\n Search Peak ERROR");
        ERROR_HOLD;
    }
}
#else
#define Test_CAL_SearchPeak      /##/
#endif

#if TEST_CAL_AMOV_EN
/*******************************************************************************
 *   Name: Test_CAL_AMov
 *  Brief: AMOV搬移
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_AMov(void)
{
    UINT8 i,j;
    BOOLEAN flag;
    ST_CalMatrixAMov CalParam;
  

    DBG_CAL("\n\nTest CAL Amov");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = rand();//i*RX_LOCAL_NUM + j;
            *(g_pAfeAram + i*RX_LOCAL_NUM + j) = rand();//0x2000+i*RX_LOCAL_NUM + j;//rand();
        }
    }
    DBG_CAL("\n\rTest Amov MEM to MEM");

    CalParam.usSrc1Addr = CAL_TEST_A0;//ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    //CalParam.ucS1TxNum  = TX_LOCAL_NUM;
    //CalParam.ucS1RxNum  = RX_LOCAL_NUM;
    CalParam.ucS1TxLen  = CAL_TEST_TX;
    CalParam.ucS1RxLen  = CAL_TEST_RX;
    CalParam.usDmaMask  = 0x0000;

    DrvCal_MatrixAMov(&CalParam);

    #if 0
    DBG_CAL("\n");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            DBG_CAL("%04x ",*(T_tempOut + i*RX_LOCAL_NUM + j));
        }
        DBG_CAL("\n");
    }
    #endif
    g_ucCalFlag = 0;
    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (*(T_tempOut + i*RX_LOCAL_NUM + j) != *(T_tempbuf1 + i*RX_LOCAL_NUM + j))
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\rERROR->out=%04x,vl=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
            else
            {
                //DBG_CAL("\n\rOK->   out=%04x,vl=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rAmov Mem to Mem ERROR");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rAmov Mem to Mem OK");
    }

    DBG_CAL("\n\rTest Amov ARAM to MEM");
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    //CalParam.ucS1TxNum  = TX_ARAM_NUM;
    //CalParam.ucS1RxNum  = RX_ARAM_NUM;
    CalParam.ucS1TxLen  = CAL_ARAM_TX;
    CalParam.ucS1RxLen  = CAL_ARAM_RX;

    DrvCal_MatrixAMov(&CalParam);
    g_ucCalFlag = 0;
    for (i=0; i<CAL_ARAM_TX; i++)
    {
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            if (*(T_tempOut + i*RX_ARAM_NUM + j) != *(g_pAfeAram + i*RX_ARAM_NUM + j))
            {
                g_ucCalFlag = 1;
                DBG_ERROR("\n\rERROR->out=%04x,vl=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
            else
            {
                //DBG_CAL("\n\rOK->   out=%04x,vl=%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rAmov Aram to Mem ERROR");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rAmov Aram to Mem OK");
    }   
}
#else
#define Test_CAL_AMov()         /##/
#endif

#if TEST_CAL_AVG_TX_EN 
/*******************************************************************************
 *   Name: Test_CAL_AVG_TX
 *  Brief: 行均值算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_AVG_TX(void)
{
    UINT8 usAvgMode;
    UINT8 i,j;
    UINT8 flag;
    SINT32 slSumDiff = 0;
    SINT16 ssAvgBuf[CAL_TEST_TX];

    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG AVG Tx Test");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand();
        }          
    }

    for(i = 0;i<TX_LOCAL_NUM;i++)
    {
        *(T_tempbuf2 + i) = (UINT16)rand();//200;                //正阈值
        *(T_tempbuf2 + TX_LOCAL_NUM + i) = ((SINT16)rand()>>1)|0x8000;//-100;//负阈值
    }

    
    CalParam.usSrc1Addr    = CAL_TEST_A0;
    CalParam.usSrc2Addr    = CAL_TEST_A1;    
    CalParam.usDstAddr     = CAL_TEST_A2;
    CalParam.ucTxLen       = CAL_TEST_TX;
    CalParam.ucRxLen       = CAL_TEST_RX;  
    CalParam.usCalCmd      = EX_OP_AVG;
    CalParam.ucCfg         = SIGN_MOD_0;
    CalParam.ucDataType    = EX_CFG_ORG;
    CalParam.ucLineCfg     = EX_MOD_TX;

    usAvgMode = AVG_MODE_0;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);

    for (i=0; i<CAL_TEST_TX; i++)
    {
        slSumDiff = 0; 
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) > *(T_tempbuf2 + i))
            {
                slSumDiff += *(T_tempbuf2 + i);
            }
            else if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) < *(T_tempbuf2 + TX_LOCAL_NUM + i))
            {
                slSumDiff += *(T_tempbuf2 + TX_LOCAL_NUM + i);
            }
            else
            {
                slSumDiff += *(T_tempbuf1 + i*RX_LOCAL_NUM + j);
            }   
        }

        
        ssAvgBuf[i] = (slSumDiff/CAL_TEST_RX);   
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG AVG Tx is ERROR!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<TX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + TX_LOCAL_NUM + i));
            
        }  

        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG AVG Tx is OK!");
    }


    for(i = 0;i<TX_LOCAL_NUM;i++)//abs的下限应该大于等于0
    {
        *(T_tempbuf2 + TX_LOCAL_NUM + i) = MIN_AVG(T_tempbuf2[i]-1000,(UINT8)rand());
    }

   
    DBG_CAL("\n\rCAL ABS AVG Tx Test");
    CalParam.usSrc1Addr    = CAL_TEST_A0;
    CalParam.usSrc2Addr    = CAL_TEST_A1;    
    CalParam.usDstAddr     = CAL_TEST_A2;
    CalParam.ucTxLen       = CAL_TEST_TX;
    CalParam.ucRxLen       = CAL_TEST_RX;  
    CalParam.usCalCmd      = EX_OP_AVG;
    CalParam.ucCfg         = SIGN_MOD_0;
    CalParam.ucDataType    = EX_CFG_ABS;
    CalParam.ucLineCfg     = EX_MOD_TX;
    usAvgMode = AVG_MODE_0;//超过阀值用阀值来代替
    
    DrvCal_MatrixAvg(&CalParam,usAvgMode);
    for (i=0; i<CAL_TEST_TX; i++)
    {
        slSumDiff = 0; 
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) > *(T_tempbuf2 + i))
            {
                slSumDiff += *(T_tempbuf2 + i);
            }
            else if (abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) < *(T_tempbuf2 + TX_LOCAL_NUM + i))
            {
                slSumDiff += *(T_tempbuf2 + TX_LOCAL_NUM + i);
            }
            else
            {
                slSumDiff += abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
          
        }
        ssAvgBuf[i] = slSumDiff/CAL_TEST_RX;   
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_CAL_DATA("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_ERROR("\n\rTest CAL ABS AVG Tx is ERROR!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<TX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + TX_LOCAL_NUM + i));
            
        }  

        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS AVG Tx is OK!");
    }

}
#else
#define Test_CAL_AVG_TX()   /##/
#endif


#if TEST_CAL_AVG_RX_EN
/*******************************************************************************
 *   Name: Test_CAL_AVG_TX
 *  Brief: 行均值算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_AVG_RX(void)
{
    UINT8 usAvgMode;
    UINT8 i,j;
    UINT8 flag;
    SINT32 slSumDiff = 0;
    SINT16 ssAvgBuf[CAL_TEST_RX];

    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG AVG Rx Test");
    //DBG_CAL("\n");    
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand();
            //DBG_CAL("%04d  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
        }
            //DBG_CAL("\n");  
    }

    for(i = 0;i<RX_LOCAL_NUM;i++)
    {
        *(T_tempbuf2 + i) = (UINT16)rand();               //正阈值
        *(T_tempbuf2 + RX_LOCAL_NUM + i) = ((SINT16)rand()>>1)|0x8000;//-100;//负阈值//MIN_AVG(T_tempbuf2[i]-1000,(UINT8)rand());
    }

    
    CalParam.usSrc1Addr    = CAL_TEST_A0;
    CalParam.usSrc2Addr    = CAL_TEST_A1;    
    CalParam.usDstAddr     = CAL_TEST_A2;
    CalParam.ucTxLen       = CAL_TEST_TX;
    CalParam.ucRxLen       = CAL_TEST_RX;  
    CalParam.usCalCmd      = EX_OP_AVG;
    CalParam.ucCfg         = SIGN_MOD_0;//SIGN_MOD_1
    CalParam.ucDataType    = EX_CFG_ORG;
    CalParam.ucLineCfg     = EX_MOD_RX;

    usAvgMode = AVG_MODE_0;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);

    for (i=0; i<CAL_TEST_RX; i++)
    {
        slSumDiff = 0; 
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) > *(T_tempbuf2 + i))
            {
                slSumDiff += *(T_tempbuf2 + i);
            }
            else if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) < *(T_tempbuf2 + RX_LOCAL_NUM + i))
            {
                slSumDiff += *(T_tempbuf2 + RX_LOCAL_NUM + i);
            }
            else
            {
                slSumDiff += *(T_tempbuf1 + j*RX_LOCAL_NUM + i);
            }   
        }

        
        ssAvgBuf[i] = (slSumDiff/CAL_TEST_TX);   
    }


    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG AVG Rx is ERROR!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<RX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + RX_LOCAL_NUM + i));
            
        }  
        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG AVG Rx is OK!");
    }


    for(i = 0;i<RX_LOCAL_NUM;i++)//abs的下限应该大于等于0
    {
        *(T_tempbuf2 + RX_LOCAL_NUM + i) = MIN_AVG(T_tempbuf2[i]-1000,(UINT8)rand());
    }

   
    DBG_CAL("\n\rCAL ABS AVG Rx Test");
    CalParam.usSrc1Addr    = CAL_TEST_A0;
    CalParam.usSrc2Addr    = CAL_TEST_A1;    
    CalParam.usDstAddr     = CAL_TEST_A2;
    CalParam.ucTxLen       = CAL_TEST_TX;
    CalParam.ucRxLen       = CAL_TEST_RX;  
    CalParam.usCalCmd      = EX_OP_AVG;
    CalParam.ucCfg         = SIGN_MOD_0;
    CalParam.ucDataType    = EX_CFG_ABS;
    CalParam.ucLineCfg     = EX_MOD_RX;
    usAvgMode = AVG_MODE_0;//超过阀值用阀值来代替
    
    DrvCal_MatrixAvg(&CalParam,usAvgMode);
    for (i=0; i<CAL_TEST_RX; i++)
    {
        slSumDiff = 0; 
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i)) > *(T_tempbuf2 + i))
            {
                slSumDiff += *(T_tempbuf2 + i);
            }
            else if (abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i)) < *(T_tempbuf2 + RX_LOCAL_NUM + i))
            {
                slSumDiff += *(T_tempbuf2 + RX_LOCAL_NUM + i);
            }
            else
            {
                slSumDiff += abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i));
            }
          
        }
        ssAvgBuf[i] = slSumDiff/CAL_TEST_TX;   
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_CAL_DATA("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<RX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + RX_LOCAL_NUM + i));
            
        }        
        DBG_ERROR("\n\rTest CAL ABS AVG Rx is ERROR!");
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS AVG Rx is OK!");
    }

}
#else
#define Test_CAL_AVG_RX()   /##/
#endif

#if 0
#if TEST_CAL_AVG_RX_EN 
/*******************************************************************************
 *   Name: Test_CAL_AVG_RX
 *  Brief: 列均值算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_AVG_RX(void)
{
    UINT8 usAvgMode;
    UINT8 i,j;
    UINT8 flag;
    SINT32 slSumDiff = 0;
    SINT16 ssAvgBuf[CAL_TEST_RX];
    SINT16 temp0;
    int    temp1,temp2;

    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG AVG Rx Test");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand();
        }          
    }

    for(i = 0;i<RX_LOCAL_NUM;i++)
    {
        *(T_tempbuf2 + i) = (UINT16)rand()>>1;//200;                //正阈值
        *(T_tempbuf2 + RX_LOCAL_NUM + i) = ((SINT16)rand()>>1)|0x8000;//-100;//负阈值
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A1;   
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;  
    CalParam.usCalCmd   = EX_OP_AVG;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_RX;
    usAvgMode = AVG_MODE_0;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);
    for (i=0; i<CAL_TEST_RX; i++)
    {
        slSumDiff = 0; 
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) >  *(T_tempbuf2 + i))
            {
                slSumDiff +=  *(T_tempbuf2 + i);
            }
            else if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) < *(T_tempbuf2 + RX_LOCAL_NUM + i))
            {
                slSumDiff += *(T_tempbuf2 + RX_LOCAL_NUM + i);
            }
            else
            {
                slSumDiff += *(T_tempbuf1 + j*RX_LOCAL_NUM + i);
            }
        }          
        ssAvgBuf[i] = slSumDiff/CAL_TEST_TX;   
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG AVG Rx is ERROR!");
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG AVG Rx is OK!");
    }

    for(i = 0;i<RX_LOCAL_NUM;i++)//abs的下限应该大于等于0
    {
        *(T_tempbuf2 + RX_LOCAL_NUM + i) = MIN_AVG(T_tempbuf2[i]-1000,(UINT8)rand());
    }    


#if 1

    DBG_CAL("\n\rCAL ABS AVG Rx Test");
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A1;   
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX; 
    CalParam.usCalCmd   = EX_OP_AVG;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_RX;
    usAvgMode = AVG_MODE_0;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);
    for (i=0; i<CAL_TEST_RX; i++)
    {
        slSumDiff = 0; 
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i)) > *(T_tempbuf2 + i))
            {
                slSumDiff += *(T_tempbuf2 + i);
            }
            else if (abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i)) < *(T_tempbuf2 + RX_LOCAL_NUM + i))
            {
                slSumDiff += *(T_tempbuf2 + RX_LOCAL_NUM + i);
            }
            else
            {
                slSumDiff += abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i));
            }
        }          
        ssAvgBuf[i] = (SINT16)(slSumDiff/CAL_TEST_TX);   
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS AVG Rx is ERROR!");
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS AVG Rx is OK!");
    }
    #endif
}
#else
#define Test_CAL_AVG_RX()   /##/
#endif
#endif

#if TEST_CAL_AVG2_TX_EN 
/*******************************************************************************
 *   Name: Test_CAL_AVG2_TX
 *  Brief: 去除大于或者小于门限值后行均值算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_AVG2_TX(void)
{
    UINT8 usAvgMode;
    UINT8 i,j;
    UINT8 flag;
    UINT8 removalData;
    SINT32 slSumDiff = 0;
    SINT16 ssAvgBuf[CAL_TEST_TX];

    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG AVG2 Tx Test");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand();
        }          
    }

    for(i = 0;i<TX_LOCAL_NUM;i++)
    {
        *(T_tempbuf2 + i) = (UINT16)rand();//200;                //正阈值
        *(T_tempbuf2 + TX_LOCAL_NUM + i) = ((SINT16)rand())|0x8000;//-100;//负阈值
    }
    
    CalParam.usSrc1Addr    = CAL_TEST_A0;
    CalParam.usSrc2Addr    = CAL_TEST_A1;    
    CalParam.usDstAddr     = CAL_TEST_A2;
    CalParam.ucTxLen       = CAL_TEST_TX;
    CalParam.ucRxLen       = CAL_TEST_RX;  
    CalParam.usCalCmd      = EX_OP_AVG;
    CalParam.ucCfg         = SIGN_MOD_0;
    CalParam.ucDataType    = EX_CFG_ORG;
    CalParam.ucLineCfg     = EX_MOD_TX;
    usAvgMode = AVG_MODE_1;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);

    for (i=0; i<CAL_TEST_TX; i++)
    {
        slSumDiff = 0; 
        removalData = 0;
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) > *(T_tempbuf2 + i))
            {
                removalData++;
                continue;
            }
            else if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) < *(T_tempbuf2 + TX_LOCAL_NUM + i))
            {
                removalData++;
                continue;
            }
            else
            {
                slSumDiff += *(T_tempbuf1 + i*RX_LOCAL_NUM + j);
            }
        }
        if(removalData == CAL_TEST_RX)
            ssAvgBuf[i] = 0x7fff;
        else
            ssAvgBuf[i] = (slSumDiff/(CAL_TEST_RX-removalData));   
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG AVG2 Tx is ERROR!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<TX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + TX_LOCAL_NUM + i));
            
        }  

        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG AVG2 Tx is OK!");
    }

    for(i = 0;i<TX_LOCAL_NUM;i++)//abs的下限应该大于等于0
    {
        *(T_tempbuf2 + TX_LOCAL_NUM + i) = MIN_AVG(T_tempbuf2[i]-1000,(UINT8)rand());
    }


    DBG_CAL("\n\rCAL ABS AVG2 Tx Test");
    CalParam.usSrc1Addr    = CAL_TEST_A0;
    CalParam.usSrc2Addr    = CAL_TEST_A1; 
    CalParam.usDstAddr     = CAL_TEST_A2;
    CalParam.ucTxLen       = CAL_TEST_TX;
    CalParam.ucRxLen       = CAL_TEST_RX; 
    CalParam.usCalCmd      = EX_OP_AVG;
    CalParam.ucCfg         = SIGN_MOD_0;
    CalParam.ucDataType    = EX_CFG_ABS;
    CalParam.ucLineCfg     = EX_MOD_TX;

    usAvgMode = AVG_MODE_1;//超过阀值用阀值来代替
    DrvCal_MatrixAvg(&CalParam,usAvgMode);
    for (i=0; i<CAL_TEST_TX; i++)
    {
        slSumDiff = 0;
        removalData = 0;
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) > *(T_tempbuf2 + i))
            {
                removalData++;
                continue;
            }
            else if (abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) < *(T_tempbuf2 + TX_LOCAL_NUM + i))
            {
                removalData++;
                continue;
            }
            else
            {
                slSumDiff += abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
        }
        if(removalData == CAL_TEST_RX)
            ssAvgBuf[i] = 0x7fff;
        else
            ssAvgBuf[i] = (slSumDiff/(CAL_TEST_RX-removalData));   
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS AVG2 Tx is ERROR!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<TX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + TX_LOCAL_NUM + i));
            
        }  

        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS AVG2 Tx is OK!");
    }
}
#else
#define Test_CAL_AVG2_TX()   /##/
#endif

#if TEST_CAL_AVG2_RX_EN 
/*******************************************************************************
 *   Name: Test_CAL_AVG2_RX
 *  Brief: 列均值算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_AVG2_RX(void)
{
    UINT8 usAvgMode;
    UINT8 i,j;
    UINT8 flag;
    UINT8 removalData;
    SINT32 slSumDiff = 0;
    SINT16 ssAvgBuf[CAL_TEST_RX];

    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG AVG2 Rx Test");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand();
        }          
    }

    for(i = 0;i<RX_LOCAL_NUM;i++)
    {
        *(T_tempbuf2 + i) = (UINT16)rand();//200;                //正阈值
        *(T_tempbuf2 + RX_LOCAL_NUM + i) = ((SINT16)rand())|0x8000;//-100;//负阈值
    }    

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usSrc2Addr = CAL_TEST_A1;    
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX; 
    CalParam.usCalCmd   = EX_OP_AVG;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_RX;

    usAvgMode = AVG_MODE_1;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);
    for (i=0; i<CAL_TEST_RX; i++)
    {
        slSumDiff = 0;
        removalData = 0;
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) > *(T_tempbuf2 + i))
            {
                removalData++;
                continue;
            }
            else if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) < *(T_tempbuf2 + RX_LOCAL_NUM + i))
            {
                removalData++;
                continue;
            }
            else
            {
                slSumDiff += *(T_tempbuf1 + j*RX_LOCAL_NUM + i);
            }
        }
        if(removalData < CAL_TEST_TX)
            ssAvgBuf[i] = (slSumDiff/(CAL_TEST_TX-removalData));   
        else
            ssAvgBuf[i]= 0x7fff;           
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG AVG2 Rx is ERROR!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<RX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + RX_LOCAL_NUM + i));
            
        }  
       
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG AVG2 Rx is OK!");
    }

    for(i = 0;i<RX_LOCAL_NUM;i++)//abs的下限应该大于等于0
    {
        *(T_tempbuf2 + RX_LOCAL_NUM + i) = MIN_AVG(T_tempbuf2[i]-1000,(UINT8)rand());
    }



    DBG_CAL("\n\rCAL ABS AVG2 Rx Test");
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usSrc2Addr = CAL_TEST_A1;   
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;  
    CalParam.usCalCmd   = EX_OP_AVG;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_RX;

    usAvgMode = AVG_MODE_1;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);
    for (i=0; i<CAL_TEST_RX; i++)
    {
        slSumDiff = 0; 
        removalData = 0;
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i)) > *(T_tempbuf2 + i))
            {
                removalData++;
                continue;
            }
            else if (abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i)) < *(T_tempbuf2 + RX_LOCAL_NUM + i))
            {
                removalData++;
                continue;
            }
            else
            {
                slSumDiff += abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i));
            }
        }          
        if(removalData < CAL_TEST_TX)
        {
            ssAvgBuf[i] = (SINT16)(slSumDiff/(CAL_TEST_TX-removalData));  
        }
        else
        {
            ssAvgBuf[i]= 0x7fff;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS AVG2 Rx is ERROR!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<RX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + RX_LOCAL_NUM + i));
            
        }          
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS AVG2 Rx is OK!");
    }
}
#else
#define Test_CAL_AVG2_RX()   /##/
#endif

#if TEST_CAL_AVG_ARAM_EN
/*******************************************************************************
 *   Name: Test_CAL_AVG_ARAM
 *  Brief: Aram 求平均算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_AVG_ARAM(void)
{
    UINT8 usAvgMode;
    UINT8 i,j;
    UINT8 flag;
    UINT8 removalData;    
    SINT32 slSumDiff = 0;
    SINT16 ssAvgBuf[40];


    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG AVG Rx Aram Test");
 
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_LOCAL_NUM + j) = (UINT16)rand();
        }
    }

    for(i = 0;i<RX_ARAM_NUM;i++)
    {
        *(T_tempbuf2 + i) = (UINT16)rand();               //正阈值
        *(T_tempbuf2 + RX_ARAM_NUM + i) = MIN_AVG(T_tempbuf2[i]-1000,(UINT8)rand());
    }

    
    CalParam.usSrc1Addr    = ARAM_DATA_BASE_ADDR;
    CalParam.usSrc2Addr    = CAL_TEST_A1;    
    CalParam.usDstAddr     = CAL_TEST_A2;
    CalParam.ucTxLen       = CAL_ARAM_TX;
    CalParam.ucRxLen       = CAL_ARAM_RX;  
    CalParam.usCalCmd      = EX_OP_AVG;
    CalParam.ucCfg         = SIGN_MOD_1;//SIGN_MOD_1
    CalParam.ucDataType    = EX_CFG_ORG;
    CalParam.ucLineCfg     = EX_MOD_RX;

    usAvgMode = AVG_MODE_0;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);

    for (i=0; i<CAL_ARAM_RX; i++)
    {
        slSumDiff = 0; 
        for (j=0; j<CAL_ARAM_TX; j++)
        {
            if (*(UINT16 *)(g_pAfeAram + j*RX_ARAM_NUM + i) > *(UINT16 *)(T_tempbuf2 + i))
            {
                slSumDiff += *(T_tempbuf2 + i);
            }
            else if (*(UINT16 *)(g_pAfeAram + j*RX_ARAM_NUM + i) < *(UINT16 *)(T_tempbuf2 + RX_ARAM_NUM + i))
            {
                slSumDiff += *(UINT16 *)(T_tempbuf2 + RX_ARAM_NUM + i);
            }
            else
            {
                slSumDiff += *(UINT16 *)(g_pAfeAram + j*RX_ARAM_NUM + i);
            }   
        }

        
        ssAvgBuf[i] = (slSumDiff/CAL_ARAM_TX);   
    }


    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_RX; i++)
    {
        if (*(UINT16 *)(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(UINT16 *)(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(UINT16 *)(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG AVG Rx Aram is ERROR!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<RX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + RX_LOCAL_NUM + i));
            
        }          
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG AVG Rx Aram is OK!");
    }

    DBG_CAL("\n\nCAL ORG AVG2 Tx Aram Test");
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT16)rand();
        }          
    }

    for(i = 0;i<TX_ARAM_NUM;i++)
    {
        *(T_tempbuf2 + i) = (UINT16)rand();//200;                //正阈值
        *(T_tempbuf2 + TX_ARAM_NUM + i) = ((SINT16)rand())|0x8000;//-100;//负阈值
    }

    CalParam.usSrc1Addr    = ARAM_DATA_BASE_ADDR;
    CalParam.usSrc2Addr    = CAL_TEST_A1;    
    CalParam.usDstAddr     = CAL_TEST_A2;
    CalParam.ucTxLen       = CAL_ARAM_TX;
    CalParam.ucRxLen       = CAL_ARAM_RX;  
    CalParam.usCalCmd      = EX_OP_AVG;
    CalParam.ucCfg         = SIGN_MOD_0;
    CalParam.ucDataType    = EX_CFG_ORG;
    CalParam.ucLineCfg     = EX_MOD_TX;
    usAvgMode = AVG_MODE_1;//超过阀值用阀值来代替

    DrvCal_MatrixAvg(&CalParam,usAvgMode);

    for (i=0; i<CAL_ARAM_TX; i++)
    {
        slSumDiff = 0; 
        removalData = 0;
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            if (*(g_pAfeAram + i*RX_ARAM_NUM + j) > *(T_tempbuf2 + i))
            {
                removalData++;
                continue;
            }
            else if (*(g_pAfeAram + i*RX_ARAM_NUM + j) < *(T_tempbuf2 + TX_ARAM_NUM + i))
            {
                removalData++;
                continue;
            }
            else
            {
                slSumDiff += *(g_pAfeAram + i*RX_ARAM_NUM + j);
            }
        }
        if(removalData == CAL_ARAM_RX)
            ssAvgBuf[i] = 0x7fff;
        else
            ssAvgBuf[i] = (slSumDiff/(CAL_ARAM_RX-removalData));   
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_TX; i++)
    {
        if (*(T_tempOut + i) != ssAvgBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
        }
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG AVG2 Tx is ERROR!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }

        for(i = 0;i<TX_LOCAL_NUM;i++)
        {
            DBG_CAL("\n%04d ",*(T_tempbuf2 + i));
            DBG_CAL("%04d ",*(T_tempbuf2 + TX_LOCAL_NUM + i));
            
        }  

        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG AVG2 Tx is OK!");
    }

    
}
#else
#define Test_CAL_AVG_ARAM() /##/
#endif

#if TEST_CAL_MIN_TX_EN 
/*******************************************************************************
 *   Name: Test_CAL_MIN_TX
 *  Brief: 行最小值算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_MIN_TX(void)
{
    UINT8 i,j;
    UINT8 flag;
    SINT16 slTemp;
    SINT16 ssMinBuf[CAL_TEST_TX];

    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG MIN Tx Test");

    DBG_CAL("\n mem");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT8)rand();
        }          
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;  
    CalParam.usCalCmd   = EX_OP_MIN;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_TX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_TEST_TX; i++)
    {
        ssMinBuf[i] = *(T_tempbuf1 + i*RX_LOCAL_NUM + 0); 
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) < ssMinBuf[i])
            {
                ssMinBuf[i] = *(T_tempbuf1 + i*RX_LOCAL_NUM + j);
            }
        }          
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        if (*(T_tempOut + i) != ssMinBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG Min Tx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG Min Tx is OK!");
    }

    DBG_CAL("\n\rCAL ABS MIN Tx Test");
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;   
    CalParam.usCalCmd   = EX_OP_MIN;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_TX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_TEST_TX; i++)
    {
        slTemp = abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + 0)); 
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) < slTemp)
            {
                slTemp = abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
        }
        if (slTemp > 0x7FFF)
        {
            ssMinBuf[i] = 0x7FFF;
        }
        else
        {
            ssMinBuf[i] = slTemp;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        if (*(T_tempOut + i) != ssMinBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS Min Tx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
               
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS Min Tx is OK!");
    }

    DBG_CAL("\naram");
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT8)rand();
        }          
    }
#if ARAM_CAL_TEST

    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;  
    CalParam.usCalCmd   = EX_OP_MIN;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_TX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_ARAM_TX; i++)
    {
        ssMinBuf[i] = *(g_pAfeAram + i*RX_ARAM_NUM + 0); 
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            if (*(g_pAfeAram + i*RX_ARAM_NUM + j) < ssMinBuf[i])
            {
                ssMinBuf[i] = *(g_pAfeAram + i*RX_ARAM_NUM + j);
            }
        }          
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_TX; i++)
    {
        if (*(T_tempOut + i) != ssMinBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG Min Tx is Error!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
                
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG Min Tx is OK!");
    }

    DBG_CAL("\n\rCAL ABS MIN Tx Test");
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
   // CalParam.ucTxNum    = TX_ARAM_NUM;
   // CalParam.ucRxNum    = RX_ARAM_NUM;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;   
    CalParam.usCalCmd   = EX_OP_MIN;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_TX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_ARAM_TX; i++)
    {
        slTemp = abs(*(g_pAfeAram + i*RX_ARAM_NUM + 0)); 
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            if (abs(*(g_pAfeAram + i*RX_ARAM_NUM + j)) < slTemp)
            {
                slTemp = abs(*(g_pAfeAram + i*RX_ARAM_NUM + j));
            }
        }
        if (slTemp > 0x7FFF)
        {
            ssMinBuf[i] = 0x7FFF;
        }
        else
        {
            ssMinBuf[i] = slTemp;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_TX; i++)
    {
        if (*(T_tempOut + i) != ssMinBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS Min Tx is Error!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
                
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS Min Tx is OK!");
    } 
#endif

}
#else
#define Test_CAL_MIN_TX()   /##/
#endif

#if TEST_CAL_MIN_RX_EN 
/*******************************************************************************
 *   Name: Test_CAL_MIN_RX
 *  Brief: 列最小值算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_MIN_RX(void)
{
    UINT8 i,j;
    UINT8 flag;
    SINT32 slTemp;
    SINT16 ssMinBuf[CAL_TEST_RX];

    ST_CalMcMatrixParam CalParam;

    
    DBG_CAL("\n\nCAL ORG MIN Rx Test");

    DBG_CAL("\nmem");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT8)rand();
        }          
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX; 
    CalParam.usCalCmd   = EX_OP_MIN;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_RX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_TEST_RX; i++)
    {
        ssMinBuf[i] = *(T_tempbuf1 + i); 
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) < ssMinBuf[i])
            {
                ssMinBuf[i] = *(T_tempbuf1 + j*RX_LOCAL_NUM + i);
            }
        }          
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssMinBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK->   Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG Min Rx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG Min Rx is OK!");
    }

    DBG_CAL("\n\rCAL ABS MIN Rx Test");
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX; 
    CalParam.usCalCmd   = EX_OP_MIN;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_RX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_TEST_RX; i++)
    {
        slTemp = abs(*(T_tempbuf1 + i)); 
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i)) < slTemp)
            {
                slTemp = abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i));
            }
        }
        if (slTemp > 0x7FFF)
        {
            ssMinBuf[i] = 0x7FFF;
        }
        else
        {
            ssMinBuf[i] = slTemp;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssMinBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS Min Rx is Error!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS Min Rx is OK!");
    }

#if ARAM_CAL_TEST


   DBG_CAL("\naram");
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT8)rand();
        }          
    }

    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX; 
    CalParam.usCalCmd   = EX_OP_MIN;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_RX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_ARAM_RX; i++)
    {
        ssMinBuf[i] = *(g_pAfeAram + i); 
        for (j=0; j<CAL_ARAM_TX; j++)
        {
            if (*(g_pAfeAram + j*RX_ARAM_NUM + i) < ssMinBuf[i])
            {
                ssMinBuf[i] = *(g_pAfeAram + j*RX_ARAM_NUM + i);
            }
        }          
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_RX; i++)
    {
        if (*(T_tempOut + i) != ssMinBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK->   Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG Min Rx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG Min Rx is OK!");
    }

    DBG_CAL("\n\rCAL ABS MIN Rx Test");
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX; 
    CalParam.usCalCmd   = EX_OP_MIN;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_RX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_ARAM_RX; i++)
    {
        slTemp = abs(*(g_pAfeAram + i)); 
        for (j=0; j<CAL_ARAM_TX; j++)
        {
            if (abs(*(g_pAfeAram + j*RX_ARAM_NUM + i)) < slTemp)
            {
                slTemp = abs(*(g_pAfeAram + j*RX_ARAM_NUM + i));
            }
        }
        if (slTemp > 0x7FFF)
        {
            ssMinBuf[i] = 0x7FFF;
        }
        else
        {
            ssMinBuf[i] = slTemp;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_RX; i++)
    {
        if (*(T_tempOut + i) != ssMinBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS Min Rx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS Min Rx is OK!");
    } 
#endif	
}
#else
#define Test_CAL_MIN_RX()   /##/
#endif


#if TEST_CAL_MAX_TX_EN 
/*******************************************************************************
 *   Name: Test_CAL_MAX_TX
 *  Brief: 行最大值算法
 *  Input:
 * Output:
 * Return: none
 *******************************************************************************/
void Test_CAL_MAX_TX(void)
{
    UINT8 i,j;
    UINT8 flag;
    SINT32 slTemp;
    SINT16 ssMaxBuf[CAL_TEST_TX];

    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG Max Tx Test");

    DBG_CAL("\n mem");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT8)rand();
        }          
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX; 
    CalParam.usCalCmd   = EX_OP_MAX;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_TX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_TEST_TX; i++)
    {
        ssMaxBuf[i] = *(T_tempbuf1 + i*RX_LOCAL_NUM + 0); 
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) > ssMaxBuf[i])
            {
                ssMaxBuf[i] = *(T_tempbuf1 + i*RX_LOCAL_NUM + j);
            }
        }          
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        if (*(T_tempOut + i) != ssMaxBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\rOK->   Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
        }

    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG Max Tx is Error!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG Max Tx is OK!");
    }

    DBG_CAL("\n\rCAL ABS Max Tx Test");
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX; 
    CalParam.usCalCmd   = EX_OP_MAX;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_TX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_TEST_TX; i++)
    {        
        slTemp = abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + 0)); 
        for (j=0; j<CAL_TEST_RX; j++)
        {
            if (abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) > slTemp)
            {
                slTemp = abs(*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
        }
        if (slTemp > 0x7FFF)
        {
            ssMaxBuf[i] = 0x7FFF;
        }
        else
        {
            ssMaxBuf[i] = slTemp;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        if (*(T_tempOut + i) != ssMaxBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_ERROR("\n\rOK->   Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS Max Tx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS Max Tx is OK!");
    }

    DBG_CAL("\naram");
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT8)rand();
        }          
    }

#if ARAM_CAL_TEST

    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;  
    CalParam.usCalCmd   = EX_OP_MAX;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_TX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_ARAM_TX; i++)
    {
        ssMaxBuf[i] = *(g_pAfeAram + i*RX_ARAM_NUM + 0); 
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            if (*(g_pAfeAram + i*RX_ARAM_NUM + j) > ssMaxBuf[i])
            {
                ssMaxBuf[i] = *(g_pAfeAram + i*RX_ARAM_NUM + j);
            }
        }          
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_TX; i++)
    {
        if (*(T_tempOut + i) != ssMaxBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG MAX Tx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG MAX Tx is OK!");
    }

    DBG_CAL("\n\rCAL ABS MAX Tx Test");
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;   
    CalParam.usCalCmd   = EX_OP_MAX;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_TX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_ARAM_TX; i++)
    {
        slTemp = abs(*(g_pAfeAram + i*RX_ARAM_NUM + 0)); 
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            if (abs(*(g_pAfeAram + i*RX_ARAM_NUM + j)) > slTemp)
            {
                slTemp = abs(*(g_pAfeAram + i*RX_ARAM_NUM + j));
            }
        }
        if (slTemp > 0x7FFF)
        {
            ssMaxBuf[i] = 0x7FFF;
        }
        else
        {
            ssMaxBuf[i] = slTemp;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_TX; i++)
    {
        if (*(T_tempOut + i) != ssMaxBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS Max Tx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS Max Tx is OK!");
    } 
#endif	
}
#else
#define Test_CAL_MAX_TX()   /##/
#endif

#if TEST_CAL_MAX_RX_EN 
/*******************************************************************************
*   Name: Test_CAL_MAX_RX
*  Brief: 列最大值算法
*  Input:
* Output:
* Return: none
*******************************************************************************/
void Test_CAL_MAX_RX(void)
{
    UINT8 i,j;
    UINT8 flag;
    SINT32 slTemp;
    SINT16 ssMaxBuf[CAL_TEST_RX];

    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nCAL ORG Max Rx Test");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT8)rand();
        }          
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;  
    CalParam.usCalCmd   = EX_OP_MAX;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_RX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_TEST_RX; i++)
    {
        ssMaxBuf[i] = *(T_tempbuf1 + i); 
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (*(T_tempbuf1 + j*RX_LOCAL_NUM + i) > ssMaxBuf[i])
            {
                ssMaxBuf[i] = *(T_tempbuf1 + j*RX_LOCAL_NUM + i);
            }
        }          
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssMaxBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_ERROR("\n\rOK->   Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG Max Rx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG Max Rx is OK!");
    }

    DBG_CAL("\n\rCAL ABS Max Rx Test");
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX; 
    CalParam.usCalCmd   = EX_OP_MAX;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_RX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_TEST_RX; i++)
    {
        slTemp = abs(*(T_tempbuf1 + i)); 
        for (j=0; j<CAL_TEST_TX; j++)
        {
            if (abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i)) > slTemp)
            {
                slTemp = abs(*(T_tempbuf1 + j*RX_LOCAL_NUM + i));
            }
        }
        if (slTemp > 0x7FFF)
        {
            ssMaxBuf[i] = 0x7FFF;
        }
        else
        {
            ssMaxBuf[i] = slTemp;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_RX; i++)
    {
        if (*(T_tempOut + i) != ssMaxBuf[i])
        {
            DBG_ERROR("\n\rERROR->Cal:%04x,Soft%04x",*(T_tempOut + i),ssMaxBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL("\n\rOK->   Cal:%04x,Soft%04x",*(T_tempOut + i),ssMaxBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS Max Rx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS Max Rx is OK!");
    }

#if ARAM_CAL_TEST

   DBG_CAL("\naram");
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT8)rand();
        }          
    }

    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX; 
    CalParam.usCalCmd   = EX_OP_MAX;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ORG;
    CalParam.ucLineCfg  = EX_MOD_RX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_ARAM_RX; i++)
    {
        ssMaxBuf[i] = *(g_pAfeAram + i); 
        for (j=0; j<CAL_ARAM_TX; j++)
        {
            if (*(g_pAfeAram + j*RX_ARAM_NUM + i) > ssMaxBuf[i])
            {
                ssMaxBuf[i] = *(g_pAfeAram + j*RX_ARAM_NUM + i);
            }
        }          
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_RX; i++)
    {
        if (*(T_tempOut + i) != ssMaxBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMaxBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK->   Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ORG Max Rx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ORG Max Rx is OK!");
    }

    DBG_CAL("\n\rCAL ABS MIN Rx Test");
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX; 
    CalParam.usCalCmd   = EX_OP_MAX;
    CalParam.ucCfg      = SIGN_MOD_0;
    CalParam.ucDataType = EX_CFG_ABS;
    CalParam.ucLineCfg  = EX_MOD_RX;

    DrvCal_MatrixMaxMin(&CalParam);

    for (i=0; i<CAL_ARAM_RX; i++)
    {
        slTemp = abs(*(g_pAfeAram + i)); 
        for (j=0; j<CAL_ARAM_TX; j++)
        {
            if (abs(*(g_pAfeAram + j*RX_ARAM_NUM + i)) > slTemp)
            {
                slTemp = abs(*(g_pAfeAram + j*RX_ARAM_NUM + i));
            }
        }
        if (slTemp > 0x7FFF)
        {
            ssMaxBuf[i] = 0x7FFF;
        }
        else
        {
            ssMaxBuf[i] = slTemp;
        }
    }

    g_ucCalFlag = 0;
    for (i = 0; i < CAL_ARAM_RX; i++)
    {
        if (*(T_tempOut + i) != ssMaxBuf[i])
        {
            DBG_ERROR("\n\r%02dERROR->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMaxBuf[i]);
            g_ucCalFlag = 1;
        }
        else
        {
            //DBG_CAL_DATA("\n\r%02dOK   ->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
        }
    }
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rTest CAL ABS Max Rx is Error!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rTest CAL ABS Max Rx is OK!");
    } 
#endif	
}
#else
#define Test_CAL_MAX_RX()   /##/
#endif

#if TEST_CAL_COUNT_EN 
/*******************************************************************************
*   Name: Test_CAL_Count
*  Brief: 矩阵处于范围[max , min]的个数
*  Input:
* Output:
* Return: none
*******************************************************************************/
void Test_CAL_Count(void)
{
    UINT8 i,j;
    UINT8 flag;
    SINT16 CountMax;
    SINT16 CountMin;
    UINT16 CalCountNum = 0;
    UINT16 SofCountNum = 0;
    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nTest Cal Count");
    
    DBG_CAL("\nmem");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand();
        }
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX; 
    CalParam.usCalCmd   = EX_OP_COUNT;
    
    CountMax = 1000;
    CountMin = -1000;

    CalCountNum = DrvCal_MatrixCount(&CalParam,CountMin,CountMax);
    DBG_CAL("\n\rCalCountNum:%d",CalCountNum);
   
    g_ucCalFlag = 0;
    for (i = 0; i < CAL_TEST_TX; i++)
    {
        for (j = 0; j < CAL_TEST_RX; j++)
        {
            if((*(T_tempbuf1 + i*RX_LOCAL_NUM + j) >= CountMin)&&(*(T_tempbuf1 + i*RX_LOCAL_NUM + j) <= CountMax))
            {
                SofCountNum++;
            }
        }
    }
    DBG_CAL("\n\rSofCountNum:%d",SofCountNum);
    
    if(CalCountNum != SofCountNum)
    {
         g_ucCalFlag = 1;
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal Test CAL Count is ERROR!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal Test CAL Count is OK!");
    }
#if ARAM_CAL_TEST

    DBG_CAL("\naram");
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_LOCAL_NUM + j) = (SINT16)rand();
        }
    }

    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX; 
    CalParam.usCalCmd   = EX_OP_COUNT;
    
    CountMax = 1000;
    CountMin = -1000;

    CalCountNum = DrvCal_MatrixCount(&CalParam,CountMin,CountMax);
    DBG_CAL("\n\rCalCountNum:%d",CalCountNum);
   
    g_ucCalFlag = 0;
    SofCountNum = 0;
    for (i = 0; i < CAL_ARAM_TX; i++)
    {
        for (j = 0; j < CAL_ARAM_RX; j++)
        {
            if((*(g_pAfeAram + i*RX_ARAM_NUM + j) >= CountMin)&&(*(g_pAfeAram + i*RX_ARAM_NUM + j) <= CountMax))
            {
                SofCountNum++;
            }
        }
    }
    DBG_CAL("\n\rSofCountNum:%d",SofCountNum);
    
    if(CalCountNum != SofCountNum)
    {
         g_ucCalFlag = 1;
    }

    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal Test CAL Count is ERROR!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal Test CAL Count is OK!");
    } 
#endif	
}
#else
#define Test_CAL_Count()   /##/
#endif

#if TEST_CAL_SUBCONST_EN 
/*******************************************************************************
*   Name: Test_CAL_SubConst
*  Brief: 计算每行(Tx)或者每列(Rx)的减去一个常数
*  Input:
* Output:
* Return: none
*******************************************************************************/
void Test_CAL_SubConst(void)
{
    UINT8 i,j;
    UINT8 flag;
    SINT32 temp;
    ST_CalMcMatrixParam CalParam;


    DBG_CAL("\n\nmem");

    DBG_CAL("\nTest CAL SubConst Tx");

    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (UINT8)rand();
        }
    }

    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        *(T_tempbuf2 + i) = (UINT8)rand();        
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usSrc2Addr = CAL_TEST_A1;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;  
    CalParam.usCalCmd   = EX_OP_SUBCONST;
    CalParam.ucLineCfg  = EX_MOD_TX;
    CalParam.ucCfg      = SIGN_MOD_1;
    DrvCal_MatrixSubConst(&CalParam);

    g_ucCalFlag = 0;
    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
            temp = (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) - *(T_tempbuf2 + i));
            if (temp > 32767)
            {   
                temp = 32767;
            }
            else if (temp < -32768)
            {
                temp = -32768;
            }
            if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (UINT16)temp)
            {
                DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
                g_ucCalFlag = 1;
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(UINT16)temp);
            }
        }
    }
    
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal Test SubConst Tx is ERROR!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        DBG_CAL("\n"); 
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
           DBG_CAL("%04x  ", *(T_tempbuf2 + i));     
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal Test SubConst Tx is OK!");
    }

    DBG_CAL("\n\rTest CAL SubConst Rx");
    for (i=0; i<RX_LOCAL_NUM; i++)
    {
        *(T_tempbuf2 + i) = (SINT8)rand();        
    }
    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usSrc2Addr = CAL_TEST_A1;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;  
    CalParam.usCalCmd   = EX_OP_SUBCONST;
    CalParam.ucLineCfg  = EX_MOD_RX;
    CalParam.ucCfg      = SIGN_MOD_0;
    
    DrvCal_MatrixSubConst(&CalParam);
    
    g_ucCalFlag = 0;
    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
            temp = (*(T_tempbuf1 + i*RX_LOCAL_NUM + j) - *(T_tempbuf2 + j));
            if (temp > 32767)
            {   
                temp = 32767;
            }
            else if (temp < -32768)
            {
                temp = -32768;
            }
            if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (SINT16)temp)
            {
                DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
                g_ucCalFlag = 1;
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK->   Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
            }
        }
    }
    
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal Test SubConst Rx is ERROR!");
        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        DBG_CAL("\n"); 
        for (i=0; i<RX_LOCAL_NUM; i++)
        {
           DBG_CAL("%04x  ", *(T_tempbuf2 + i));     
        }
       
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal Test SubConst Rx is OK!");
    }

#if ARAM_CAL_TEST

    DBG_CAL("\naram");
    DBG_CAL("\nTest CAL SubConst Tx");
    
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (SINT8)rand();
        }
    }

    for (i=0; i<TX_ARAM_NUM; i++)
    {
        *(T_tempbuf2 + i) = (SINT8)rand();        
    }

    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usSrc2Addr = CAL_TEST_A1;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;  
    CalParam.usCalCmd   = EX_OP_SUBCONST;
    CalParam.ucLineCfg  = EX_MOD_TX;
    CalParam.ucCfg      = SIGN_MOD_0;
    DrvCal_MatrixSubConst(&CalParam);

    g_ucCalFlag = 0;
    for (i=0; i<CAL_ARAM_TX; i++)
    {
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            temp = (*(g_pAfeAram + i*RX_ARAM_NUM + j) - *(T_tempbuf2 + i));
            if (temp > 32767)
            {   
                temp = 32767;
            }
            else if (temp < -32768)
            {
                temp = -32768;
            }
            if (*(T_tempOut + i*RX_ARAM_NUM + j) != (SINT16)temp)
            {
                DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_ARAM_NUM + j),(SINT16)temp);
                g_ucCalFlag = 1;
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
            }
        }
    }
    
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal Test SubConst Tx is ERROR!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        DBG_CAL("\n"); 
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
           DBG_CAL("%04x  ", *(T_tempbuf2 + i));     
        }        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal Test SubConst Tx is OK!");
    }

    DBG_CAL("\n\rTest CAL SubConst Rx");
    for (i=0; i<RX_ARAM_NUM; i++)
    {
        *(T_tempbuf2 + i) = (SINT8)rand();        
    }
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usSrc2Addr = CAL_TEST_A1;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;  
    CalParam.usCalCmd   = EX_OP_SUBCONST;
    CalParam.ucLineCfg  = EX_MOD_RX;
    CalParam.ucCfg      = SIGN_MOD_0;
    
    DrvCal_MatrixSubConst(&CalParam);
    
    g_ucCalFlag = 0;
    for (i=0; i<CAL_ARAM_TX; i++)
    {
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            temp = (*(g_pAfeAram + i*RX_ARAM_NUM + j) - *(T_tempbuf2 + j));
            if (temp > 32767)
            {   
                temp = 32767;
            }
            else if (temp < -32768)
            {
                temp = -32768;
            }
            if (*(T_tempOut + i*RX_ARAM_NUM + j) != (SINT16)temp)
            {
                DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_ARAM_NUM + j),(SINT16)temp);
                g_ucCalFlag = 1;
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK->   Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)temp);
            }
        }
    }
    
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal Test SubConst Rx is ERROR!");

        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        DBG_CAL("\n"); 
        for (i=0; i<RX_LOCAL_NUM; i++)
        {
           DBG_CAL("%04x  ", *(T_tempbuf2 + i));     
        }  

        
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal Test SubConst Rx is OK!");
    }  
#endif	
}
#else
#define Test_CAL_SubConst()   /##/
#endif

#if TEST_CAL_CMP_EN 
/*******************************************************************************
*   Name: Test_CAL_SubConst
*  Brief: 将操作数矩阵1与操作数矩阵2对应的位置进行比较，取
             最大值或者最小值写入结果矩阵
*  Input:  M*N
               M*N
* Output:  M*N
* Return: none
*******************************************************************************/
void Test_CAL_CMP(void)
{
    UINT8 i,j;
    UINT8 flag;
    SINT16 temp;
    ST_CalMcMatrixParam CalParam;

    DBG_CAL("\n\nTest CAL CMP");
    DBG_CAL("\n mem-mem");
    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        for (j=0; j<RX_LOCAL_NUM; j++)
        {
            *(T_tempbuf1 + i*RX_LOCAL_NUM + j) = (SINT16)rand()>>1;
            *(T_tempbuf2 + i*RX_LOCAL_NUM + j) = (SINT16)rand()>>1;            
        }
    }

    CalParam.usSrc1Addr = CAL_TEST_A0;
    CalParam.usSrc2Addr = CAL_TEST_A1;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_TEST_TX;
    CalParam.ucRxLen    = CAL_TEST_RX;  
    CalParam.usCalCmd   = EX_OP_CMP;
    CalParam.ucDataType = CMP_CFG_1;//取最大值
    CalParam.ucCfg = SIGN_MOD_0;//有符号数
    
    DrvCal_MatrixCMP(&CalParam);

    g_ucCalFlag = 0;
    for (i=0; i<CAL_TEST_TX; i++)
    {
        for (j=0; j<CAL_TEST_RX; j++)
        {
            #if 0//取最大值
            
                if((*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) > (*(T_tempbuf2 + i*RX_LOCAL_NUM + j)))
                {
                    temp = (*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
                }
                else
                {
                    temp = (*(T_tempbuf2 + i*RX_LOCAL_NUM + j));
                }
                
            #else//取最小值

                if((*(T_tempbuf1 + i*RX_LOCAL_NUM + j)) < (*(T_tempbuf2 + i*RX_LOCAL_NUM + j)))
                {
                    temp = (*(T_tempbuf1 + i*RX_LOCAL_NUM + j));
                }
                else
                {
                    temp = (*(T_tempbuf2 + i*RX_LOCAL_NUM + j));
                }
                
            #endif
            
            if (*(T_tempOut + i*RX_LOCAL_NUM + j) != temp)
            {
                DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),temp);
                g_ucCalFlag = 1;
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),temp);
            }
        }
    }
    
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal Test CMP is ERROR!");


        DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf1+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        DBG_CAL("\n"); 
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf2+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }     
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal Test CMP is OK!");
    }

    DBG_CAL("\nAram-mem");

    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = (UINT16)rand()>>1;
            *(T_tempbuf2 + i*RX_ARAM_NUM + j) = (UINT16)rand()>>1;            
        }
    }
#if ARAM_CAL_TEST

    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usSrc2Addr = CAL_TEST_A1;//(UINT16)T_tempbuf2;
    CalParam.usDstAddr  = CAL_TEST_A2;
    CalParam.ucTxLen    = CAL_ARAM_TX;
    CalParam.ucRxLen    = CAL_ARAM_RX;  
    CalParam.usCalCmd   = EX_OP_CMP;
    CalParam.ucDataType = CMP_CFG_1;//取最大值
    CalParam.ucCfg = SIGN_MOD_1;//有符号数
    
    DrvCal_MatrixCMP(&CalParam);

    g_ucCalFlag = 0;
    for (i=0; i<CAL_ARAM_TX; i++)
    {
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            #if 0//取最大值
            
                if((*(g_pAfeAram + i*RX_ARAM_NUM + j)) > (*(T_tempbuf2 + i*RX_ARAM_NUM + j)))
                {
                    temp = (*(g_pAfeAram + i*RX_ARAM_NUM + j));
                }
                else
                {
                    temp = (*(T_tempbuf2 + i*RX_ARAM_NUM + j));
                }
                
            #else//取最小值

                if((*(g_pAfeAram + i*RX_ARAM_NUM + j)) < (*(T_tempbuf2 + i*RX_ARAM_NUM + j)))
                {
                    temp = (*(g_pAfeAram + i*RX_ARAM_NUM + j));
                }
                else
                {
                    temp = (*(T_tempbuf2 + i*RX_ARAM_NUM + j));
                }
                
            #endif
            
            if (*(T_tempOut + i*RX_ARAM_NUM + j) != temp)
            {

                DBG_ERROR("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_ARAM_NUM + j),temp);
                g_ucCalFlag = 1;
            }
            else
            {
                //DBG_CAL_DATA("\n\rOK   ->Cal:%04x,Soft:%04x",*(T_tempOut + i*RX_ARAM_NUM + j),temp);
            }
        }
    }
    
    if (g_ucCalFlag)
    {
        DBG_CAL("\n\rCal Test CMP is ERROR!");
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        DBG_CAL("\n"); 
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf2+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }          
        ERROR_HOLD;
    }
    else
    {
        DBG_CAL("\n\rCal Test CMP is OK!");
    } 
#endif	
}
#else
#define Test_CAL_CMP()  /##/
#endif

#if TEST_CAL_MUL3_EN
/*******************************************************************************
 *   Name: Test_CAL_MaxtixMul_PtoP
 *  Brief: M1 : M*1
 *         M2 :   N*1
 *         OUT: M*N
 *         Out[i][j] = M1[i][1]*M2[j][1];
 *  Input: ST_CalMcMatrixParam *pMcMP =>
 * Output: None
 * Return: None
 *******************************************************************************/
BOOLEAN Test_CAL_MaxtixMul_PtoP3()
{
    UINT8 i,j;
    UINT8 ucShift;
    SINT32 tmp;
    BOOLEAN flag;
    ST_CalMcMatrixParam XRAM CalParam;
    static UINT8 counter = 0;

    DBG_CAL("\n\nTest: Matrix MUL3");
    DBG_CAL("\nmem-mem");

    for (i=0; i<TX_LOCAL_NUM; i++)
    {
        *(T_tempbuf1 + i) = (SINT8)rand()>>1;
    }

    for(j = 0; j < RX_LOCAL_NUM; j++)
    {
        *(T_tempbuf2 +j) = (SINT8)rand()>>1;    
    }

    for(i = 0; i<TX_ARAM_NUM;i++)
     {
        *(g_pAfeAram + i) = (SINT8)rand()>>1;
    }       

    if(counter == 16)
        counter = 0;
    
    ucShift = counter;
    counter ++;  



    //for (ucShift = 0; ucShift < 16; ucShift++)
    {
        DBG_CAL("\nshift:%d",ucShift);
        CalParam.usSrc1Addr = CAL_TEST_A0;
        CalParam.usSrc2Addr = CAL_TEST_A1;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_TEST_TX;
        CalParam.ucRxLen    = CAL_TEST_RX;
        CalParam.usCalCmd   = EX_OP_MUL3;
        CalParam.ucShift    = ucShift;

        DrvCal_MatrixMul3(&CalParam);

        g_ucCalFlag = 0;
       
        for (i = 0; i < CAL_TEST_TX; i++)
        {
            for (j = 0; j < CAL_TEST_RX; j++)
            {
                tmp = (*(T_tempbuf1 + i)) * (*(T_tempbuf2 + j));
                tmp >>= ucShift;
                if (tmp > 32767)
                {
                    tmp = 32767;
                }
                else if (tmp < -32768)
                {
                    tmp = -32768;
                }
                if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (SINT16)tmp )
                {
                    DBG_ERROR("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                    g_ucCalFlag = 1;
                }
                else
                {
                    //DBG_ERROR("\n\rOK->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                }
            }
        }

        if (g_ucCalFlag)
        {
            DBG_CAL("\n\rCal MUL3 test %02d is Error!",ucShift);
            DBG_CAL("\n");  
            for (i=0; i<TX_LOCAL_NUM; i++)
            {
                for (j=0; j<1; j++)
                {
                   
                    DBG_CAL("%04x  ",*(T_tempbuf1+ i*RX_LOCAL_NUM + j));
                }
                    DBG_CAL("\n");  
            }
            DBG_CAL("\n"); 
            for (i=0; i<1; i++)
            {
                for (j=0; j<RX_LOCAL_NUM; j++)
                {
                   
                    DBG_CAL("%04x  ",*(T_tempbuf2+ i*RX_LOCAL_NUM + j));
                }
                    DBG_CAL("\n");  
            }             
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rCal MUL3  test %02d is OK!",ucShift);
        }
    }
#if ARAM_CAL_TEST

    DBG_CAL("\nmem-aram");

    //for (ucShift = 0; ucShift < 16; ucShift++)
    {
        CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
        CalParam.usSrc2Addr = CAL_TEST_A1;
        CalParam.usDstAddr  = CAL_TEST_A2;
        CalParam.ucTxLen    = CAL_ARAM_TX;
        CalParam.ucRxLen    = CAL_TEST_RX;
        CalParam.usCalCmd   = EX_OP_MUL3;
        CalParam.ucShift    = ucShift;

        DrvCal_MatrixMul3(&CalParam);

        g_ucCalFlag = 0;
        for (i = 0; i < CAL_ARAM_TX; i++)
        {
            for (j = 0; j < CAL_TEST_RX; j++)
            {
                tmp = (*(g_pAfeAram + i)) * (*(T_tempbuf2 + j));
                tmp >>= ucShift;
                if (tmp > 32767)
                {
                    tmp = 32767;
                }
                else if (tmp < -32768)
                {
                    tmp = -32768;
                }
                if (*(T_tempOut + i*RX_LOCAL_NUM + j) != (SINT16)tmp )
                {
                    DBG_ERROR("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                    g_ucCalFlag = 1;
                }
                else
                {
                    //DBG_ERROR("\n\rOK->%04x,%04x,%04x,%04x",*(T_tempOut + i*RX_LOCAL_NUM + j),(SINT16)tmp,i,j);
                }
            }
        }

        if (g_ucCalFlag)
        {
            DBG_CAL("\n\rCal MUL3 test %02d is Error!",ucShift);

         DBG_CAL("\n");  
        for (i=0; i<TX_LOCAL_NUM; i++)
        {
            for (j=0; j<1; j++)
            {
               
                DBG_CAL("%04x  ",*(g_pAfeAram+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }
        DBG_CAL("\n"); 
        for (i=0; i<1; i++)
        {
            for (j=0; j<RX_LOCAL_NUM; j++)
            {
               
                DBG_CAL("%04x  ",*(T_tempbuf2+ i*RX_LOCAL_NUM + j));
            }
                DBG_CAL("\n");  
        }            
            ERROR_HOLD;
        }
        else
        {
            DBG_CAL("\n\rCal MUL3  test %02d is OK!",ucShift);
        }
    }  
#endif	
    return g_ucCalFlag;
}
#else
#define Test_CAL_MaxtixMul_PtoP3()  /##/
#endif


/******************************************************************************
*
*   Name: DrvClearIICState
*  Brief: 清IIC相关标志
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvClearIICState(void)
{
    /* 清I2C相关flag */
    I2CBUF = 0;
    I2CRI  = 0;
    I2CTI  = 0;

    /* 清I2C STOP相关flag */
    I2CSTP = 0;
    I2C_STOP_IF = 0;
    
    //I2CWK_STOP = 0;
}

UINT16 XRAM g_ucRawdata[CAL_ARAM_TX][CAL_ARAM_RX] _at_ (0x6000);

/*******************************************************************************
 *   Name: CalAmovAramToMem
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
void CalAmovAramToMem(void)
{
    UINT8 i,j;
    static BOOLEAN flag = 0;
    ST_CalMatrixAMov CalParam; 


    #if 0
    for (i=0; i<TX_ARAM_NUM; i++)
    {
        for (j=0; j<RX_ARAM_NUM; j++)
        {
            *(g_pAfeAram + i*RX_ARAM_NUM + j) = rand();
        }
    }
    #endif
    CalParam.usSrc1Addr = ARAM_DATA_BASE_ADDR;
    CalParam.usDstAddr  = (UINT16)g_ucRawdata;//0x6000;
    CalParam.ucS1TxLen  = CAL_ARAM_TX;
    CalParam.ucS1RxLen  = CAL_ARAM_RX;


    DrvCal_MatrixAMov(&CalParam);

    #if 1
    //flag = 0;
    for (i=0; i<CAL_ARAM_TX; i++)
    {
        for (j=0; j<CAL_ARAM_RX; j++)
        {
            if(g_ucRawdata[i][j]  != *(g_pAfeAram + i*RX_ARAM_NUM + j))
            {
                flag = 1;
                //DBG_ERROR("\n\rERROR->out=%04x,vl=%04x",*((UINT16 *)g_ucRawdata + i*RX_ARAM_NUM + j),*(g_pAfeAram + i*RX_ARAM_NUM + j));
            }
            else
            {
                //DBG_CAL("\n\rOK->   out=%04x,vl=%04x",*(g_usRawdata + i*RX_LOCAL_NUM + j),*(g_pAfeAram + i*RX_LOCAL_NUM + j));
            }
        }
    }

    if (flag)
    {
        DBG_CAL("\nInt Amov Aram to Mem ERROR");
    }
    else
    {
        DBG_CAL("\nInt Amov Aram to Mem OK");
    }

	if(g_ucCalFlag)
	{
		DBG_CAL("\nCAL ERROR");
	}
    #endif
}


/*******************************************************************************
 *   Name: RtcInit
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
void RtcInit(void)
{
    // 32K时钟使能
    CLK_WP = 1;
    EN_32K = 1;
    RTC_32K_EN = 1;
    
    // rtc clk enable
    RTCCKEN = 1;

    // clear rtc
    RTC_WP  = 1;
    RTC_CLR = 1;
    //DelayMs(100);

    // 设置RTC计数时间
    RTCIVH  = 0;
    RTCIVL  = 32;

    //Normal mode
    RTC_AUTO_MODE = 0;
    RTCCON1       = 1;

    RTC_INT_EN_CPU = 1;

    IT1   = 0;   
    EX1   = 1;       

}

/*******************************************************************************
 *   Name: RtcInit
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
void LcdIntInit(void)
{
	DrvAsmInterEnable1(2);//lcd run
    ES = 1;
}


/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2cInit(void)
{
    I2CCKEN = 1;

    I2CBUF = 0;
    I2CRI  = 0;
    I2CTI  = 0;

    /* 设置设备地址 */
    I2CADDR = I2C_SLAVE_ADDR&0xFE;

    I2C_STOP_EI = 1;        //Set to enable Additional Interrupt 0
    I2C_STOP_IF = 0;

    ET2 = 1;                 //I2C Interrupt Enable
    I2C_STOP_EI = 1;         //I2C_STP
}




/*******************************************************************************
*   Name: DrvIntPriority
*  Brief:
*         1.中断源优先级
*         2.注意高优先级中有调用cal中断，要设置比他低的中断，不能打断cal,不然会死锁。
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void DrvIntPriority(void)
{
    /* 优先级--先清0 */
    IPH0 = 0x00;
    IPL0 = 0x00;
    AIPH = 0x00;
    AIPL = 0x00;

    /* Int0优先级设置为3---唤醒要求 */
    IPHX0 = 1;
    IPLX0 = 1;

    /* 通信优先 设置为3 */
    I2C_IPH = 1;
    I2C_IPL = 1;

	SPI0_IPH = 1;
	SPI0_IPL = 1;

    I2C_STOP_IPH = 1;
    I2C_STOP_IPL = 1;

	LCD_IPH = 1;
	LCD_IPL = 1;

    /* ASM中断的优先级第二 */
    ASM_IPH = 1;
    ASM_IPL = 0;

    /* Cnt or Rtc 计数器 */
    IPHX1 = 1;
    IPLX1 = 0;

    /* Time0优先级设置为 */
    IPHT0 = 0;
    IPLT0 = 0;

    /* Time1 */
    IPHT1 = 0;
    IPLT1 = 0;

#if _BLK_DBG_EN
    /* uart优先级设置为2--低优先级中断中不能使用串口 */
    Uart_IPH = 1;
    Uart_IPL = 1;
#endif
}


#define PRESCALE_24                       0       // 1:24个cycle计数一次;0:384个cycle计数一次

//WDT 定时数 110ms、400ms、25.2S
#define CNT_WDT_MS  6000

#if PRESCALE_24
#define WDT_MS(n)  ((0x7FFC-(UINT32)(n)*1000/48)&0x00FF) > 0x0080?(((0x7FFC-(UINT32)(n)*1000/48)>>8)+1):((0x7FFC-(UINT32)(n)*1000/48)>>8)
#else
#define WDT_MS(n)  ((0x7FFC-(UINT32)(n)*1000/768)&0x00FF) > 0x0080?(((0x7FFC-(UINT32)(n)*1000/768)>>8)+1):((0x7FFC-(UINT32)(n)*1000/768)>>8)
#endif

/*******************************************************************************
* Name:WDT_Init
* Input:
* Output:
* function:
*  1.WTD时钟默认为 fclk = 500KHZ固定，一个时间周期是2us
*  2.溢出时间 (0x7FFC - 0xXX00)*2*12*2us
*  3.最小最大值12.096ms(0xFC*2*12*2us)~25.2S(0x7FFC*2*12*2us*16)
********************************************************************************/
void WDT_Init(void)
{
    WDT_500K_EN = 1;    //wdt clk
    WDTSTARTEN = 1;     //start en = 1

    /* 时钟计数: 只配置高7位，低8位固定为0 
    wdtrel[7]  1: 每384  个cycle  计数一次
               0: 每  24  个cycle  计数一次*/

#if 0	
    //WDTREL = 0x5E;//0x77;
    WDTREL = 0x60;//0x7E;
    /* 16倍分频器使能 */
    WDTREL |= 0x00;
#else
    WDTREL = WDT_MS(CNT_WDT_MS);
#if PRESCALE_24
    WDTREL &= 0x7F;
#else
    WDTREL |= 0x80;

#endif

#endif
    WDT  = 1;           //刷新计数器值
    SWDT = 1;           //启动wdt计数

    WDT_INT_IF = 0;
    WDT_INT_EI = 1;

}


/********************************************************************************
* Name:WDT_Feed
* Input:
* Output:
* function:
********************************************************************************/
void WDT_Feed(void)
{
    WDT  = 1;  //刷新计数器值
    SWDT = 1;  //启动wtd计数
}


/*******************************************************************************
 *   Name: Test_CAL
 *  Brief:
 *  Input:
 * Output:
 * Return:
 *******************************************************************************/
void Test_CAL(void)
{
    BOOLEAN flag = TRUE;

    UINT16 CALMask =   0;//BITn(0);
    UINT16 AmoveMask = 0;//BITn(0);
    UINT16 i;

    AFEACKEN = 1;
    ARAM_SEL = 1;

    T_tempbuf1 = CAL_TEST_A0;
    T_tempbuf2 = CAL_TEST_A1;
    T_tempOut  = CAL_TEST_A2;
    
    T_tempbuf3 = CAL_TEST_PKS;

    DBG_CAL("\n\rStart CalTest!\n\r");
    DBG_CAL("\n\rCal-A0:%08lx",T_tempbuf1);
    DBG_CAL("\n\rCal-A1:%08lx",T_tempbuf2);
    DBG_CAL("\n\rCal-A2:%08lx",T_tempOut);
    DBG_CAL("\n\rCal-A3:%08lx",CAL_TEST_PKS);
    DBG_CAL("\n\rAram:%08lx",g_pAfeAram);
    
    DrvClearIICState();

	DrvIntPriority();
	IEN0 = 0;
	AIE = 0;

#if TEST_RTC_CAL_EN
	CALMask |= BITn(2); 
	//AmoveMask |=BITn(2);
	RtcInit();
#endif

#if TEST_LCD_CAL_EN
	CALMask |= BITn(4);
	AmoveMask |= BITn(4);
	LcdIntInit();
#endif

#if TEST_IIC_CAL_EN
	CALMask |= BITn(5);  //IIC
	AmoveMask |= BITn(5);//IIC
	CALMask |= BITn(8);  //IIC_STOP
	AmoveMask |= BITn(8);//IIC_STOP
	I2cInit();
#endif

#if TEST_ASM_CAL_EN
	CALMask |= BITn(9);
	//AmoveMask |= BITn(9);
	Afe_120Hz_Run();
#endif

#if TEST_SPI0_CAL_INT_EN
	CALMask |= BITn(11); 
	AmoveMask |=BITn(11);
    SPI0CKEN = 1;
    SPI0CON5 = 0xff;
    SPI0CON2 = 0x00;
    SPI0CON3 = 0;
    SPI0CON4 = 0X00;
    /* IO配置: P05-->P02  MOSI MISO CLK CS */
    P0MOD |= BITn(5) + BITn(4)+BITn(3) + BITn(2);
    P0SEL |= BITn(5) + BITn(4)+BITn(3) + BITn(2);
    
    P0DIR |= BITn(4)+BITn(3) + BITn(2);
    P0DIR &= ~ BITn(5);
    
    SPI0_EI = 1;
    
    //中断标志使能
    SPI0RI_EN = 1;
    SPI0TI_EN = 0;

    SPI0_IPH = 1;
    SPI0_IPL = 1;

#if TEST_SPI0_DMA_INT_EN

    SPI0_32K_EN =1;
    pSpi0_DmaRegs->dma_ctrl = 0;
    pSpi0_DmaRegs->timeout_ctrl = 0;
    pSpi0_DmaRegs->addr_h = (1<<14) + (0<<8) + (0);    //[15:14] dma ram sel.0:aram;1:dram;2:pram. [9:8]ram起始地址[17:16]bit. [1:0] ram结束地址[1:0] 
    pSpi0_DmaRegs->start_addr_l = 0X9000;
    pSpi0_DmaRegs->end_addr_l = 0x900F;
    pSpi0_DmaRegs->dma_srcr = 0x000f;

    for(i = 0; i < 0x10; i++)
    {
        *(UINT8 *)(0x9000 + i) = i;
    }
    
#endif
#endif
    DrvCal_Init(TX_LOCAL_NUM, RX_LOCAL_NUM, CALMask,AmoveMask);

    EA = 1; 


	P0BUF = 0;
	P1BUF = 0;
    
while(1)
{
#if 1
	P1_4 = !P1_4;

    Test_CAL_MaxtixAdd();
	
    Test_CAL_MaxtixSub();
	
    Test_CAL_MaxtixAmp();

    Test_CAL_MaxtixDiv();
	
    Test_CAL_MaxtixMov();
	
    Test_CAL_MaxtixMov2();
	
    Test_CAL_MaxtixCom_1();

    Test_CAL_MaxtixCom_2();
	
    Test_CAL_MaxtixMul_PtoP1();

    Test_CAL_MaxtixMul_PtoP2();

    Test_CAL_LDS();
	
    Test_CAL_MDS();
	
    Test_CAL_CHK();
	
    Test_CAL_ID();
	
    Test_CAL_MAC_1();
	
    Test_CAL_MAC_2();
	
    Test_CAL_CRC();

    Test_CAL_XORSUM();

    Test_CAL_SearchPeak();

    //扩展算法
    //Test_CAL_AMov();

    Test_CAL_AVG_TX();

    Test_CAL_AVG_RX();

    Test_CAL_AVG2_TX();

    Test_CAL_AVG2_RX();
    //Test_CAL_AVG_ARAM();
 
    Test_CAL_MIN_TX();
	
    Test_CAL_MIN_RX();

    Test_CAL_MAX_TX();

    Test_CAL_MAX_RX();

    Test_CAL_Count();

    Test_CAL_SubConst();

    Test_CAL_CMP();

    Test_CAL_MaxtixMul_PtoP3();
#endif	
} 

    AFEACKEN = 0;
    ARAM_SEL = 0;
    DBG_CAL("\n\r\n\rCAL test End");

    while (1);
}



/*******************************************************************************
 *   Name:
 *  Brief:
 *  Input:
 * Output:
 * Return: INT0中断响应函数
 *******************************************************************************/
void Exint0_IRQHandler(void) interrupt 0
{ 


    #if 0

    RTC_CNT_WKEN = 0;
    #endif
    
    DBG_INT("\nint0");

}


/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT1中断响应函数.
*******************************************************************************/
void Exint1_IRQHandler(void) interrupt 2
{   
    //如果是在AUTO模式，则不清rtc，否则一定要清RTC，不然会一直在中断中出不去
	P0_6 = 1;	
    while(RTC_START_STA == 0);
#if 0	
   	DELAY;
	if(g_ucCalStartFlag == 1)
	{
		WATI_CAL_SUSPEND;//等到suspend起来
	}
#endif	
    RTC_WP  = 1;
    RTC_CLR = 1;

	DBG_INT("\nRTC");



	RTCIVH = 0;
	RTCIVL = (UINT8)rand();
	P0_6 = 0;

	//RTC_WP = 1;
	//RTC_START = 1;

}

/*******************************************************************************
*   Name: ISR_LcdRun
*  Brief: lcd run
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void ISR_LcdRun_IRQHandler(void) interrupt  4
{
    UINT16 usAsmIntEn0,usAsmIntEn1;
    UINT16 usAsmIntFlag0,usAsmIntFlag1;

    usAsmIntEn0   = pAsmRegs->usAsmIntEn0;
    usAsmIntEn1   = pAsmRegs->usAsmIntEn1;

    usAsmIntFlag0 = pAsmRegs->usAsmIntFlag0;
    usAsmIntFlag1 = pAsmRegs->usAsmIntFlag1;

    /* LCD RUN int */
    if (usAsmIntEn1&LCD_RUN_INT1)
    {
        if (usAsmIntFlag1&LCD_RUN_INT1)
        {
            /* lcd_run极性设置 1: 检测高 */
            if(pAsmRegs->usAsmScanCfg1&BITn(15)) 
            {
               pAsmRegs->usAsmScanCfg1&=~(1<<15);     // [15] LCD RUN中断电平选择，                               
               DBG_FLOW("\nRun INTPHAS 1");
            }
            else
            {
               pAsmRegs->usAsmScanCfg1|=(1<<15);     // [15] LCD RUN中断电平选择，                               
               DBG_FLOW("\nRun INTPHAS 2");
            }
       
            pAsmRegs->usAsmIntClr1 |=LCD_RUN_INT1;
            //DBG_FLOW("\nLCD RUN int");
        }
    }

}

/*******************************************************************************
 *   Name:
 *  Brief:
 *  Input:
 * Output:
 * Return: I2C中断响应函数
 *******************************************************************************/
void I2C_ISR(void) interrupt 5
{
    UINT8 ch = 0;
	P0_2 = 1;
	P0_4 = 1;
    //DBG_INT("\n I2C Init");

    if (RIFLAG)
    {
#if 0    
    	DELAY;
		if(g_ucAmoveStart == 1)
		{
			WAIT_AMOVE_SUSPEND;
		}	
		else if(g_ucCalStartFlag == 1)
		{
			WATI_CAL_SUSPEND;//等到suspend起来
		}
#endif		
        RIFLAG = 0;
        ch = DATABUFF;
        g_I2cCnt++; 

    }
    if (TIFLAG)
    {
#if 0    
    	DELAY;  
		if(g_ucAmoveStart == 1)
		{
			WAIT_AMOVE_SUSPEND;
		}	
		else if(g_ucCalStartFlag == 1)
		{
			WATI_CAL_SUSPEND;//等到suspend起来
		}
#endif		
        TIFLAG = 0;

    }	
	P0_4 = 0;
	P0_2 = 0;
}

/*******************************************************************************
 *   Name:
 *  Brief:
 *  Input:
 * Output:
 * Return: I2C STOP中断响应函数
 *******************************************************************************/
void I2C_STOP_ISR(void) interrupt 8
{
	P0_3 = 1;
	P0_5 = 1;

#if 0	
	DELAY;
	if(g_ucAmoveStart == 1)
	{
		WAIT_AMOVE_SUSPEND;
	}	
	else if(g_ucCalStartFlag == 1)
	{
		WATI_CAL_SUSPEND;//等到suspend起来
	}
#endif	
    I2CSTP = 0;
	P0_3 = 0;
	P0_5 =0;
}

/*******************************************************************************
*   Name: DrvScanCtrl_IRQHandler
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvScanCtrl_IRQHandler(void) interrupt 9
{
    UINT16 usAsmIntEn0,usAsmIntEn1;
    UINT16 usAsmIntFlag0,usAsmIntFlag1;

	P1_1 = 1;
    usAsmIntEn0   = pAsmRegs->usAsmIntEn0;
    usAsmIntEn1   = pAsmRegs->usAsmIntEn1;

    usAsmIntFlag0 = pAsmRegs->usAsmIntFlag0;
    usAsmIntFlag1 = pAsmRegs->usAsmIntFlag1;
	

    /* aram ready int */
    if (usAsmIntEn0&ARAM_READY_INT0)
    {
        if (usAsmIntFlag0&ARAM_READY_INT0)
        {
        	P1_3 = 1;
#if 0			
        	DELAY;
			if(g_ucCalStartFlag == 1)
			{
				WATI_CAL_SUSPEND;//等到suspend起来
			}
#endif			
            pAsmRegs->usAsmIntClr0 |= ARAM_READY_INT0;
			//Test_CAL_AMov();

			ARAM_SEL = 1;
	
			CalAmovAramToMem();
            DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据, 触发AramReady中断
			ARAM_SEL = 0;
			
            DBG_INT("\nint Aram");
			P1_3 = 0;
        }
    }

  

    /* lcd vstart int */
    if (usAsmIntEn0&LCD_VSTART_INT0)
    {
        if (usAsmIntFlag0&LCD_VSTART_INT0)
        {
        	P1_2 = 1;
#if 0			
        	DELAY;
			if(g_ucCalStartFlag == 1)
			{
				WATI_CAL_SUSPEND;//等到suspend起来
			}
#endif			
            pAsmRegs->usAsmIntClr0 |= LCD_VSTART_INT0;
            DBG_INT("\nint vstart");
            DrvAsmScanStart();  
			P1_2 = 0;
        }
    }
	P1_1 = 0;

}



/*******************************************************************************
*   Name: SPI0_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
******************************************************************************/
void SPI0_IRQHandler(void) interrupt 11
{
    UINT8 ch = 0;  

    DBG_INT("\nSPI0 INT"); 
    
    if (SPI0RI)
    {
#if 0   
    	DELAY;
		if(g_ucAmoveStart == 1)
		{
			WAIT_AMOVE_SUSPEND;
		}	
		else if(g_ucCalStartFlag == 1)
		{
			WATI_CAL_SUSPEND;//等到suspend起来
		}
#endif		
        SPI0RI_CLR = 1;          //清除RI标志
        ch = SPI0BUF;  
        
        if(SPI0_START)
        {        
            SPI0_START_CLR = 1; //清除START标志
        }

#if TEST_SPI0_DMA_INT_EN
        if(ch == 0x01)
        {
            pSpi0_DmaRegs->dma_ctrl = 1;//启动dma 
        }
#endif

    }
 
    SPI0CON5 =0xff; 
}

#endif

