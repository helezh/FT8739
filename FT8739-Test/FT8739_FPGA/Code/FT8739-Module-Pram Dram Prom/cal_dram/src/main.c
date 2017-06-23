/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: main.c
*
*    Author: xinkunpeng
*
*   Created: 2013-11-11
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
#include <intrins.h>

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define DRAM data     // data can be mapped directly to the 251 data space
#define XRAM near     // xdata uses MOVX or MOV @DR56, use 251 near instead
#define PRAM near     // pdata uses MOVX Ri, use 251 near instead
#define CROM code     // code uses MOVC A, use 251 const instead

typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned long  UINT32;


#if 1
sfr CGUCON4     = 0xCC;
sfr P0BUF       = 0x80;
sfr P0DIR       = 0xAC;
sfr P0MOD       = 0xEB;
sfr P0SEL       = 0xEC;
sfr P1BUF       = 0x94;   /*P1Buf*/
sfr P1DIR       = 0xAD;   /*P1口方向配置，1:输出, 0:输入*/
sfr P1MOD       = 0xED;   /*0:P1 use as gpio;1:p1 use as function define*/
sfr P1SEL       = 0xEE;   /*0:P1 as OD port; 1:P1 as PUSH-PULL port*/
sfr CGUCON3     = 0xCB;
sfr SYSCON      = 0x98;
sfr CGUCON1     = 0xC8;
sfr UARTCON     = 0xA9;
sfr UART_RELH   = 0xAE;
sfr UART_RELL   = 0xAB;
sfr IEN0        = 0xA8;
sfr UARTBUF     = 0xAA;


sbit CALCKEN   = CGUCON3^6;     /* cal clock enable*/
sbit UART1     = SYSCON^3;   /* uart1 */
sbit UART0     = SYSCON^2;   /* uart0: 2'b01: GPIO6; 2'b10: GPIO7; 2'b11: GPIO1.5; 2'b00: 其他;  */
sbit UARTCKEN  = CGUCON1^2;     /* uart clk enable*/
sbit UART_TI   = UARTCON^1;
sbit UART_RI   = UARTCON^0;
sbit EA        = IEN0^7;  /* Global Interrupt Enable */
sbit SYSCKEN   = CGUCON1^7;



sbit P0_0 = P0BUF^0;
sbit P0_1 = P0BUF^1;
sbit P0_2 = P0BUF^2;
sbit P0_3 = P0BUF^3;
sbit P0_4 = P0BUF^4;
sbit P0_5 = P0BUF^5;
sbit P0_6 = P0BUF^6;
sbit P0_7 = P0BUF^7;

sbit P1_0 = P1BUF^0;
sbit P1_1 = P1BUF^1;
sbit P1_2 = P1BUF^2;
sbit P1_3 = P1BUF^3;
sbit P1_4 = P1BUF^4;
sbit P1_5 = P1BUF^5;
sbit P1_6 = P1BUF^6;
sbit P1_7 = P1BUF^7;
#else
sfr CGUCON4 = 0xCC;
sfr P0BUF   = 0x80;
sfr P0DIR   = 0xAC;
sfr P0MOD   = 0xEB;
sfr P0SEL   = 0xEC;
sfr P1BUF   = 0x94;   /*P1Buf*/
sfr P1DIR   = 0xAD;   /*P1口方向配置，1:输出, 0:输入*/
sfr P1MOD   = 0xED;   /*0:P1 use as gpio;1:p1 use as function define*/
sfr P1SEL   = 0xEE;   /*0:P1 as OD port; 1:P1 as PUSH-PULL port*/
sfr CGUCON3 = 0xCB;

sbit CALCKEN = CGUCON3^6;     /* cal clock enable*/

sbit P0_0 = P0BUF^0;
sbit P0_1 = P0BUF^1;
sbit P0_2 = P0BUF^2;
sbit P0_3 = P0BUF^3;
sbit P0_4 = P0BUF^4;
sbit P0_5 = P0BUF^5;
sbit P0_6 = P0BUF^6;
sbit P0_7 = P0BUF^7;

sbit P1_0 = P1BUF^0;
sbit P1_1 = P1BUF^1;
sbit P1_2 = P1BUF^2;
sbit P1_3 = P1BUF^3;
sbit P1_4 = P1BUF^4;
sbit P1_5 = P1BUF^5;
sbit P1_6 = P1BUF^6;
sbit P1_7 = P1BUF^7;
#endif


/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
#define XRAM_START_ADDRESS    0x0080
#define DRAM_START_ADDRESS    0x0000
#define DRAM_END_ADDRESS      0xA000//0xA000
#define DRAM_LENGTH_BYTE      (128 - 8)//定义数组没法定义到0x0000的，最前面只能定义到0x0008
#define XRAM_LENGTH_BYTE      (DRAM_END_ADDRESS-XRAM_START_ADDRESS)
#define XRAM_LENGTH_WORD      (XRAM_LENGTH_BYTE >> 1)
#define XRAM_LENGTH_DWORD     (XRAM_LENGTH_BYTE >> 2)

#define _TEST_DRAM              0
#define _TEST_XRAM_BYTE         0
#define _TEST_XRAM_WORD         0
#define _TEST_XRAM_DWORD        0
#define _TEST_CAL_DRAM          1

#define TEST_PATTERN1         0x55
#define TEST_PATTERN2         0xAA
#define TEST_PATTERN3         0x55AA
#define TEST_PATTERN4         0xAA55
#define TEST_PATTERN5         0x12345678//0x55AA55AA
#define TEST_PATTERN6         0xAA55AA55
#define BITn(n)               ((UINT16)1<<(n))

#if 1
#define UART_CLK  (48000000/16)
#define BAUD_RATE 115200
#endif

#define APP_INFO_ADDR             0xFEE900  // Verification Info
#define APP_VERIF_LEN             0x20

#define FW_CFG_TOTAL_SIZE         0x80

UINT8 ecode g_aucVerfication[APP_VERIF_LEN+FW_CFG_TOTAL_SIZE] _at_ APP_INFO_ADDR;


#define Cal_Len                 40*39
#define Test_CAL_Len            Cal_Len*13
#define CAL_REG_BASE_ADDR       0xB000
/*************************************************************/
// cal
typedef struct
{
    UINT16 rCmd;           // (0x00<<1)
    UINT16 rDmaLen;        // (0x01<<1)
    UINT16 rS1Addr;        // (0x02<<1)
    UINT16 rS2Addr;        // (0x03<<1)
    UINT16 rOutAddr;       // (0x04<<1)
    UINT16 rPar;           // (0x05<<1)
    UINT16 rSize;          // (0x06<<1)
    UINT16 rPThd;          // (0x07<<1)
    UINT16 rNThd;          // (0x08<<1)
    UINT16 rAThd;          // (0x09<<1)
    UINT16 rDmask;         // (0x0A<<1)
    UINT16 rPaCnt;         // (0x0B<<1)
    UINT16 rNaCnt;         // (0x0C<<1)
    UINT16 rPsCnt;         // (0x0D<<1)
    UINT16 rNsCnt;         // (0x0E<<1)
    UINT16 rMaxV;          // (0x0F<<1)
    UINT16 rMaxPos;        // (0x10<<1)
    UINT16 rMinV;          // (0x11<<1)
    UINT16 rMinPos;        // (0x12<<1)
    UINT16 rID0;           // (0x13<<1)
    UINT16 rID1;           // (0x14<<1)
    UINT16 rID2;           // (0x15<<1)
    UINT16 rCrc;           // (0x16<<1)
    UINT16 rChk;           // (0x17<<1)
    UINT16 rNaThd;         // (0x18<<1)
    UINT16 rTxRxNum;       // (0x19<<1)
    UINT16 rDivShift;      // (0x1a<<1)
    UINT16 rSubabsMax;     // (0x1b<<1)
    UINT16 rInt;           // (0x1c<<1)
    UINT16 rCntNum;        // (0x1d<<1)
    UINT16 rDmaskA;        // (0x1e<<1)
    UINT16 rTxRxNumAm;     // (0x1f<<1)
    UINT16 rTxRxNumAs;     // (0x20<<1)
    UINT16 rSizeAm;        // (0x21<<1)
    UINT16 rSizeAs;        // (0x22<<1)
    UINT16 rS1AddrA;       // (0x23<<1)
    UINT16 rS2AddrA;       // (0x24<<1)
    UINT16 rOutAddrA;      // (0x25<<1)
    UINT16 rSel;           // (0x26<<1)
} ST_CalRegisters;


ST_CalRegisters *pCalRegs = (volatile ST_CalRegisters *)CAL_REG_BASE_ADDR ;
UINT16 XRAM ucData[Test_CAL_Len] _at_ (0x100);

UINT16  XRAM i_tmp _at_ (0x98);
UINT8  XRAM  ucErrFlag = 0;


/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
* Name: main
* Brief:
* Input:
* Output:
* Return:
* Note:不要使用函数嵌套，此时需要用到堆栈，堆栈分配在XRAM中，遍历XRAM的时候必定会
        对堆栈中的内容操作.使用函数嵌套，可能会在调用函数后出栈时找不到进入函数时
        的寄存器配置，导致系统跑飞。
*******************************************************************************/

void main(void)
{
    UINT16 cnt;

    CGUCON4 = 0x00;

    P0MOD   = 0x00;
    P0DIR   = 0xFF;
    P0SEL   = 0xFF;
    P0BUF   = 0x00;

    P1MOD   = 0x00;
    P1DIR   = 0xFF;
    P1SEL   = 0xFF;
    P1BUF   = 0xFF;

    UART1  = 1;
    UART0  = 0;
    P0MOD |= BITn(7);                    // UART: P0.7
    UARTCKEN = 1;                        //开启UART时钟
    UARTCON |= BITn(7);                  //工作方式为8位

    cnt = (0x400 - UART_CLK/BAUD_RATE);  //波特率设置
    UART_RELH = cnt/256;
    UART_RELL = cnt%256; 

    IEN0 = 0;

    for(i_tmp = 0; i_tmp < Test_CAL_Len; i_tmp ++)
    {
        ucData[i_tmp] =  0x5555;
    }

    CALCKEN = 1;

    pCalRegs->rDmaLen = 1;
    pCalRegs->rTxRxNum = (40<<8) + 39;

    pCalRegs->rDmask = 0;

    pCalRegs->rSize = (40<<8) + 39;

    pCalRegs->rPThd = 0;
    pCalRegs->rPar  = -1;

    pCalRegs->rCmd  = 0;    

    while(1)
    {
        for(i_tmp = 0; i_tmp < 14; i_tmp++)
        {
            pCalRegs->rS1Addr  = (UINT16)(&ucData[i_tmp*Cal_Len]);
            pCalRegs->rOutAddr = (UINT16)(&ucData[i_tmp*Cal_Len]);

            pCalRegs->rCmd = ((0x04<<4)|(1<<0));   //AMP Start

            while ( (pCalRegs->rInt&BITn(15)) != BITn(15) );//等待结束
            pCalRegs->rCmd |= BITn(14);
            pCalRegs->rCmd = 0;
        }


        for(i_tmp = 0; i_tmp < Test_CAL_Len; i_tmp ++)
        {
            if(ucData[i_tmp] !=  0xAAAB)
            {
                ucErrFlag = 1;
            }        
        }

        if(ucErrFlag)
        {
            UARTBUF = 'E';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = 'R';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = 'R';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;        

            UARTBUF = '1';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = '\n';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;        
        }
        else
        {
            UARTBUF = 'O';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = 'K';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = '1';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = '\n';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;        
        }

        ucErrFlag = 0;
        for(i_tmp = 0; i_tmp < 14; i_tmp++)
        {
            pCalRegs->rS1Addr  = (UINT16)(&ucData[i_tmp*Cal_Len]);
            pCalRegs->rOutAddr = (UINT16)(&ucData[i_tmp*Cal_Len]);

            pCalRegs->rCmd = ((0x04<<4)|(1<<0));   //AMP Start

            while ( (pCalRegs->rInt&BITn(15)) != BITn(15) );//等待结束
            pCalRegs->rCmd |= BITn(14);
            pCalRegs->rCmd = 0;
        }


        for(i_tmp = 0; i_tmp < Test_CAL_Len; i_tmp ++)
        {
            if(ucData[i_tmp] !=  0x5555)
            {
                ucErrFlag = 1;
            }        
        }

        if(ucErrFlag)
        {
            UARTBUF = 'E';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = 'R';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = 'R';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;        

            UARTBUF = '2';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = '\n';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;        
        }
        else
        {
            UARTBUF = 'O';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = 'K';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = '2';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;

            UARTBUF = '\n';
            while(UART_TI == 0);//等待发送
            UART_TI = 0;        
        }    
    }
        
    while(1);

}

