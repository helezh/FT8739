/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: uart.c
*
*    Author: xinkunpeng
*
*   Created: 2013-05-26
*
*  Abstract:             
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "uart.h"
#include "DrvSysCtrl.h"
#include <string.h>

#if _BLK_DBG_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define CHAR_NOF   0x00

#define U1_ON    (EC = 1)
#define U1_OFF   (EC = 0)

#define UBUF_OUT_LEN 1024        //size of serial transimit buffer
#define UBUF_IN_LEN  32         //size of serial receiving buffer 

#define UART_CLK  (48000000/16/(MAIN_CLK+1))

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
UINT8 XRAM s_aucUartOutBuf[UBUF_OUT_LEN];  // transmit buffer

UINT16 XRAM s_ucUartTxPos = 0;              // transmit current pos
VOLATILE UINT16 XRAM s_ucUartTxStore = 0;   // mcu store 
VOLATILE UINT16 XRAM s_ucUartTxLen = 0;     // length of transmit

#ifdef UART_RECEIVE_OPEN
UINT8 XRAM s_aucUartInBuf[UBUF_IN_LEN];    // receiving buffer

UINT8 XRAM s_ucUartRxPos = 0;              // receive current pos
VOLATILE UINT8 XRAM s_ucUartRxStore = 0;   // host store
VOLATILE UINT8 XRAM s_ucUartRxLen = 0;     // length of receive
#endif

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: putchar
*  Brief: 
*  Input: 
* Output: None
* Return: None
*******************************************************************************/ 
SINT8 putchar(SINT8 ch)
{ 
    U1_ON;
    while (s_ucUartTxLen >= UBUF_OUT_LEN)         //缓冲区满时，等待
    {
    }
    //暂停串行输出中断，以免数据比较时出错    
    U1_OFF;

    s_ucUartTxLen++;                              //长度+1
    if (s_ucUartTxLen == 1)                       //第一个数据，直接发送,不进入缓冲区   
    {
        UARTBUF = ch; 
    }    
    else
    {
        s_aucUartOutBuf[s_ucUartTxStore++] = ch;  //数据放入缓冲区,先入后加
        if (s_ucUartTxStore >= UBUF_OUT_LEN) 
        {
            s_ucUartTxStore = 0;                  //环形缓冲区
        }
    }    

    U1_ON;
    return 0;
} 

#ifdef UART_RECEIVE_OPEN
/*******************************************************************************
*   Name: getbyte
*  Brief: 
*  Input: 
* Output: None
* Return: None
*******************************************************************************/
UINT8 getbyte(UINT16 timeout)
{ 
    UINT8 XRAM ch; 

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
*   Name: ISR_Uart
*  Brief: 
*  Input: 
* Output: None
* Return: None
*******************************************************************************/
void ISR_Uart(void) interrupt 6
{ 
#ifdef UART_RECEIVE_OPEN
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
*   Name: DrvUartInit
*  Brief: 
*
* baud =48M/(16X(2^10-uartrel)) = 3 000 000/(2^10 - uartrel)
* uartrel = 2^10 - 3000000/baud = 0x400 - 3000000/baud
*
*  Input: 
* Output: None
* Return: None
*******************************************************************************/
void DrvUartInit(void)
{
    UINT16 XRAM cnt;

	UART_REN1 = 1;	
#if 1
    UART1 = 1;
    UART0 = 0; //P07
    // IO
    P0MOD |= BITn(7);

	UART_INH = 0;
	UART_INL = 1;
	P0MOD |= BITn(6);
#else
    UART1 = 0;
    UART0 = 1; //P06
    // IO
    P0MOD |= BITn(6);

	UART_INH = 1;
	UART_INL = 0;
	P0MOD |= BITn(7);	
#endif
    /* 开启UART时钟 */
    // CLK_WP   = 1;
    UARTCKEN = 1;    


    // 工作方式8位
    UARTCON |= BITn(7);

    // 波特率
    cnt = (0x400 - UART_CLK/BAUD_RATE);
    UART_RELH = cnt/256;
    UART_RELL = cnt%256;
}

#ifdef UART_RECEIVE_OPEN
void uart0_putc(SINT8 ch)
{
    while(!UART_TI);
    UART_TI = 0;
    UARTBUF = ch;
}

void uart0_puts(const UINT8*buf)
{
    UINT8 XRAM i = 0;
    
    while(buf[i]!= 0)
    {
        while(UART_TI)
        {
            if(buf[i] == '\n' )
            {
                UARTBUF = '\r';
                while(!UART_TI);
                UART_RI = 0;
            }
        
            UARTBUF = buf[i++];
            if(buf[i] == 0)
                return;
        }
        while(!UART_TI);
        UART_TI = 0;
    }
}

SINT8 uart0_getc(void)
{
    SINT8 XRAM rec_ch = -1;
    
    while(!UART_RI);
	UART_RI = 0;
    rec_ch = UARTBUF;
    
    return rec_ch;
}

void Uart_GetString(SINT8 *string)
{
    SINT8 XRAM c;
    SINT8 XRAM node = 0;
    
    while(1)
    {
        c = uart0_getc();
        string[node] = c;
              
        if((string[node-1]==92)&&(string[node]=='n'))
        {
        node--;
        break;
        }
        else if(string[node]== 0xd)
        {
        uart0_putc('\r');
        uart0_putc('\n');
        break;
        }
        else
        uart0_putc(c);
        
        node++;
    }
    string[node]='\0';
}

SINT8 Uart_GetIntNum(SINT8 *string)
{
    SINT8 XRAM LastIndex;
    SINT8 XRAM i;
    SINT8 XRAM Result = 0;
    SINT8 XRAM Base = 10;
    
    
    if(string[0]=='0' && (string[1]=='x' || string[1]=='X'))
    {
       Base = 16;
       string += 2;
    }
    
    LastIndex = strlen(string) - 1;
    if(LastIndex < 0)
        return -1;
    
    if(string[LastIndex]=='h' || string[LastIndex]=='H' )
    {
        Base = 16;
        string[LastIndex] = 0;
        LastIndex--;
    }
    
    if(Base==10)        //decimalist
    {
        Result = atoi(string);
    }
    else        //Hex
    {
        for(i=0;i<=LastIndex;i++)
        {
            if(isalpha(string[i]))
            {
                if(isupper(string[i]))
                    Result = (Result<<4) + string[i] - 'A' + 10;
                else
                    Result = (Result<<4) + string[i] - 'a' + 10;
            }
            else
                Result = (Result<<4) + string[i] - '0';
        }
    }
    
    return Result;
}

void TestFun1(void)
{
    DBG_FLOW(" RUN Fun1\n");
}

void TestFun2(void)
{
    DBG_FLOW(" RUN Fun2\n");
}


SINT8  XRAM string[50];

void XRAM *function[][2] =
{
	(void XRAM *)TestFun1, (void XRAM *)"Test	APP1", 
	(void XRAM *)TestFun2, (void XRAM *)"Test	APP2", 
	(void XRAM *)0,(void XRAM *)0
};


#if 1

void TestUart(void)
{
    UINT8 XRAM ch;
    UINT8 XRAM i = 0;
	DBG_FLOW("\nDSV_CON:%02x",DSV_CON);
	DBG_FLOW("\nSYS_CON:%02x",SYSCON);
	DBG_FLOW("\nP0MOD:%02x",P0MOD);
	DBG_FLOW("\nUARTCON:%02x",UARTCON);

	DelayMs(2000);
	
	EC = 0;
    while(1)
    {
#if 0    
		while(UART_RI == 0);//等待接收
		UART_RI = 0;
		ch = UARTBUF;

		UARTBUF = ch;
		while(UART_TI == 0);//等待发送
		UART_TI = 0;
#else
	
        ch = uart0_getc();
		UARTBUF = ch;
		while(UART_TI == 0);//等待发送
		UART_TI = 0;

        if(ch=='s' || ch=='S')
        break;
#endif		
    }
	EC = 1;
#if 0
    while(1)
    {
        DBG_FLOW("\n\n Test Program Ver1.00\n") ;
 
        while(1)
        {
            DBG_FLOW("  %2d:%s",i,function[i][1]);
            i++;
            if((int)(function[i][0])==0)
            {
                DBG_FLOW("\n");
                break;
            }     
        }
    }
#endif    
    DBG_FLOW("\nSelect the function to test : \n");
    Uart_GetString(string);
    i=Uart_GetIntNum(string);
    
    if(i>=0 && (i<(sizeof(function)/8)) )
        ( (void (*)(void)) (function[i][0]) )();
}
#endif
#endif



#endif //_U_DEBUG

