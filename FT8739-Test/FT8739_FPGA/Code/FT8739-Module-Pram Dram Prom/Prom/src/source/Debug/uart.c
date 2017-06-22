/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: uart.c
*
*    Author: linjianjun
*
*   Created: 2013-06-05
*
*  Abstract:
*
* Reference: test Uart introduction:
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <string.h>
#include "uart.h"

#if _BLK_DBG_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define CHAR_NOF   0x00

#define U1_ON    (EC = 1)
#define U1_OFF   (EC = 0)

#define UBUF_OUT_LEN 250        //size of serial transimit buffer
#define UBUF_IN_LEN  32         //size of serial receiving buffer 

//#define UART_CLK  (48000000/16/(MAIN_CLK+1))
#define UART_CLK  (48000000/16/CLK_DIV(MAIN_CLK))
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
UINT8 XRAM s_aucUartOutBuf[UBUF_OUT_LEN];  // transmit buffer

UINT8 XRAM s_ucUartTxPos = 0;              // transmit current pos
volatile UINT8 XRAM s_ucUartTxStore = 0;   // mcu store
volatile UINT8 XRAM s_ucUartTxLen = 0;     // length of transmit

#if _UART_RECEIVE_EN
UINT8 XRAM s_aucUartInBuf[UBUF_IN_LEN];    // receiving buffer

UINT8 XRAM s_ucUartRxPos = 0;              // receive current pos
volatile UINT8 XRAM s_ucUartRxStore = 0;   // host store
volatile UINT8 XRAM s_ucUartRxLen = 0;     // length of receive
#endif

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
UINT8 CLK_DIV(UINT8 div)
{
    switch(div)
    {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 4;
        case 3:
            return 8;
        default:
            return 1;
    }
}


/*******************************************************************************
* Name: putchar
* Brief:
* Input:
* Output: None
* Return: None
*******************************************************************************/
SINT8 putchar(SINT8 ch)
{
    U1_ON;
    while (s_ucUartTxLen >= UBUF_OUT_LEN);    //缓冲区满时，等待
    //暂停串行输出中断，以免数据比较时出错
    U1_OFF;
    s_ucUartTxLen++;                          //长度+1
    if (s_ucUartTxLen == 1)                   //第一个数据，直接发送,不进入缓冲区
    {
        UARTBUF = ch;
    }
    else
    {
        s_aucUartOutBuf[s_ucUartTxStore++] = ch;  //数据放入缓冲区,先入后加
        if (s_ucUartTxStore >= UBUF_OUT_LEN)
        {
            s_ucUartTxStore = 0;                //环形缓冲区
        }
    }
    U1_ON;
    return 0;
}

#if _UART_RECEIVE_EN
/*******************************************************************************
* Name: getbyte
* Brief:
* Input:
* Output: None
* Return: None
*******************************************************************************/
UINT8 getbyte(UINT16 timeout)
{
    UINT8 ch;
    // 接收缓冲区为空时，等待数据或超时处理
    while (s_ucUartRxLen == 0)
    {
        if (timeout-- == 0)
        {
            return CHAR_NOF;
        }
    }
    // 暂停串行接收中断，以免数据比较时出错
    U1_OFF;
    ch = s_aucUartInBuf[s_ucUartRxPos++];
    if (s_ucUartRxPos >= UBUF_IN_LEN)
    {
        s_ucUartRxPos = 0;        // 环形缓冲区
    }
    s_ucUartRxLen--;
    // 恢复串口接收功能
    U1_ON;
    return (ch);
}
#endif

/*******************************************************************************
* Name: ISR_Uart
* Brief:
* Input:
* Output: None
* Return: None
*******************************************************************************/
void ISR_Uart(void) interrupt 6
{
#if _UART_RECEIVE_EN
    if (UART_RI)
    {
        UART_RI = 0;
        // 溢出，则放弃该数据
        if (s_ucUartRxLen >= UBUF_IN_LEN)
        {
            s_ucUartRxLen = UBUF_IN_LEN;
        }
        else
        {
            s_ucUartRxLen++;
            s_aucUartInBuf[s_ucUartRxStore++] = UARTBUF;
            if (s_ucUartRxStore >= UBUF_IN_LEN)
            {
                s_ucUartRxStore = 0;
            }
        }
    }
#endif
    if (UART_TI)
    {
        UART_TI = 0;
        if (s_ucUartTxLen)  // 长度不为0，继续发送
        {
            s_ucUartTxLen--;
            if (s_ucUartTxLen != 0)
            {
                // 未发送完继续发送
                UARTBUF = s_aucUartOutBuf[s_ucUartTxPos++];
                if (s_ucUartTxPos >= UBUF_OUT_LEN)
                {
                    s_ucUartTxPos = 0;
                }
            }
        }
    }
}

/*******************************************************************************
* Name: DrvUartInit
* Brief:
* baud =48M/(16X(2^10-uartrel)) = 3 000 000/(2^10 - uartrel)
* uartrel = 2^10 - 3000000/baud = 0x400 - 3000000/baud
* Input:
* Output: None
* Return: None
*******************************************************************************/
void DrvUartInit(void)
{
    UINT16 cnt;
    
#if _UART_OUT_GPIO3
    UART1  = 1;
    UART0  = 0;
    P0MOD |= BITn(7);  // UART: P0.7
#endif

#if _UART_OUT_GPIO2
    UART1  = 0;
    UART0  = 1;
    P0MOD |= BITn(6);  // UART: P0.6
#endif

#if _UART_OUT_GPIO4
    UART1  = 1;
    UART0  = 1;

	if(BUS_SEL == 1)
	{
    	P1MOD |= BITn(7);  // UART: P1.7		
	}
	else if(SPI_REPLACE_EN == 0)
	{
		P0MOD |= BITn(3);
	}
	

#endif


#if _UART_RECEIVE_EN   //接收使能
	UART_REN1 = 1;

#if _UART_OUT_GPIO3
	UART_INH = 0;
	UART_INL = 1;
	P0MOD |= BITn(6);  //uart rx p0.6
#else
	UART_INH = 1;
	UART_INL = 0;
	P0MOD |= BITn(7);  //uart rx p0.7
#endif
#endif
    Uart_IPH = 1;
    Uart_IPL = 1;

    UARTCKEN = 1;                        //开启UART时钟
    UARTCON |= BITn(7);                  //工作方式为8位

    cnt = (0x400 - UART_CLK/BAUD_RATE);  //波特率设置
    UART_RELH = cnt/256;
    UART_RELL = cnt%256;  

}
void wait_printf_done(void)
{
    while(s_ucUartTxLen);

}
#endif //_U_DEBUG

