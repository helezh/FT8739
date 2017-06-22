/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)£¬All Rights Reserved.
*
* File Name: Test_GPIO.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-18
*
*  Abstract:
*
* Reference:
*
*   Version:   0.1: Transplant from FT5412 by xinkunpeng
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_GPIO.h"

#if _TEST_GPIO_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef enum
{
    GPIO_NOP,
    GPIO_INPUT,
    GPIO_PULLOUTPUT,
    GPIO_ODOUTPUT,
    GPIO_PULLTRIGGER,
    GPIO_ODTRIGGER,
} ENUM_GPIO;

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_GPIO(void)
{  
    UINT8 temp;
    SYSCKEN = 1;
    temp = GPIO_INPUT;

    switch (temp)
    {
        /* test gpio input  */
        case GPIO_INPUT:
        {
	        DBG_GPIO("\n\r--------------------");
            DBG_GPIO("\n\rTest GPIO input :");
			
            #if _UART_OUT_GPIO2   // P0_6 use as uart, this micro defined in "uart.h"
            DBG_GPIO("\n\rP0_6 use as uart ");
	        DBG_GPIO("\n\r--------------------");	 
	        P0MOD = BITn(6)+0x00;      //uart : gpio6
            P0DIR &= 0x40;
            P0SEL |= 0xbf;
		 
	        P1MOD = 0x00;
            P1DIR = 0x00;
            P1SEL = 0xff;
			
	        #elif _UART_OUT_GPIO3    // P0_7 use as uart, this micro defined in "uart.h"
            DBG_GPIO("\n\rP0_7 use as uart !");
	        DBG_GPIO("\n\r--------------------");
            P0MOD = BITn(7)+0x00;      //uart : gpio7
            P0DIR &= 0x80;
            P0SEL |= 0x7f;
	        P1MOD = 0x00;
            P1DIR = 0x00;
            P1SEL = 0;//xff;

	        #elif  _UART_OUT_GPIO4
	        DBG_GPIO("\n\rP1_5 use as uart !");
	        DBG_GPIO("\n\r--------------------");
	     
	        P0MOD = 0x00;
            P0DIR = 0x00;
            P0SEL = 0xff;
            #endif
            P1SEL = 0xff;
			
            while (1)
            {
                DBG_GPIO("\r\nP0MOD:  0x%02x",P0MOD);
		        DBG_GPIO("\r\nP0DIR:  0x%02x",P0DIR);
		        DBG_GPIO("\r\nP0SEL:  0x%02x",P0SEL);
                DBG_GPIO("\r\nP0BUF:  0x%02x",P0BUF); 
                DBG_GPIO("\n");
                DBG_GPIO("\r\nP1MOD:  0x%02x",P1MOD);
		        DBG_GPIO("\r\nP1DIR:  0x%02x",P1DIR);
		        DBG_GPIO("\r\nP1SEL:  0x%02x",P1SEL);               	
                DBG_GPIO("\r\nP1BUF:  0x%02x",P1BUF);
                DBG_GPIO("\r\n--------");
                DelayMs(2000);
            }
            break;
        }
        /* test gpio pull output default state */
        case GPIO_PULLOUTPUT:
        {
            DBG_GPIO("\n\rTest GPIO pull output :");
            #if _UART_OUT_GPIO2
            P0MOD = BITn(6)+0x00;      //uart : gpio6
            P0DIR |= 0xbf;
            P0SEL |= 0xbf;

	        P1MOD = 0x00;
            P1DIR = 0xff;
            P1SEL = 0xff;
			
            #elif _UART_OUT_GPIO3
            P0MOD = BITn(7)+ 0x00;      //uart : gpio7
            P0DIR |= 0x7f;
            P0SEL |= 0x7f;

	        P1MOD = 0x00;
            P1DIR = 0xff;
            P1SEL = 0xff;
			
            #elif  _UART_OUT_GPIO4
            P0MOD = 0x00;                     //uart : gpio1_5
            P0DIR = 0xff;
            P0SEL = 0xff;
	        #endif

	        DBG_GPIO("\n\rP0:%4x",P0BUF);	 
            DBG_GPIO("\n\rP1:%4x",P1BUF);
            break;
						
        }
		
        /* test gpio OD output default state */
        case GPIO_ODOUTPUT:
        {
            DBG_GPIO("\n\rTest GPIO OD output :");
            #if _UART_OUT_GPIO2
            P0MOD = BITn(6)+0x00;      //uart : gpio6
            P0DIR |= 0xbf;
            P0SEL &= 0x40;

	        P1MOD = 0x00;
            P1DIR = 0xff;
            P1SEL = 0x00;
			
            #elif _UART_OUT_GPIO3
            P0MOD = BITn(7)+0x00;      //uart : gpio7
            P0DIR |= 0x7f;
            P0SEL &= 0x80;

	        P1MOD = 0x00;
            P1DIR = 0xff;
            P1SEL = 0x00;

            #elif  _UART_OUT_GPIO4     //uart: gpio1_5
			
	        P0MOD = 0x00;
            P0DIR = 0xff;
            P0SEL = 0x00;		
            #endif
			
            DBG_GPIO("\n\rP0:%4x",P0BUF);            
            DBG_GPIO("\n\rP1:%4x",P1BUF);

            break;
        }
        /* test gpio pull output trigger 0 or 1 */
        case GPIO_PULLTRIGGER:
        {
            DBG_GPIO("\n\rTest GPIO PULL trigger :");
            #if _UART_OUT_GPIO2
            P0MOD = BITn(6)+0x00;      //uart : gpio6
            P0DIR |= 0xbf;
            P0SEL |= 0xbf;

            P1MOD = 0x00;
            P1DIR = 0xff;
            P1SEL = 0xff;	
			
            #elif _UART_OUT_GPIO3
            P0MOD = BITn(7)+0x00;      //uart : gpio7
            P0DIR |= 0x7f;
            P0SEL |= 0x7f;

            P1MOD = 0x00;
            P1DIR = 0xff;
            P1SEL = 0xff;			
            
            #else
            P0MOD = 0x00;
            P0DIR = 0xff;
            P0SEL = 0xff;
	     #endif
		 
            #if _UART_OUT_GPIO2
            P0BUF |= 0xbf;
	        P1BUF = 0xff;
		 
            #elif _UART_OUT_GPIO3
            P0BUF |= 0x7f;
	        P1BUF = 0xff;

	     #else	 
	        P1BUF = 0xff;	 
            #endif
            
            
            while (1)
            {
                P0BUF = ~P0BUF;
                P1BUF = ~P1BUF;
                DBG_GPIO("\n\rP0:%4x",P0BUF);
                DBG_GPIO("\n\rP1:%4x",P1BUF);
                DelayMs(100);
            }
            break;
        }
        /* test gpio OD output trigger 0 or 1 */
        case GPIO_ODTRIGGER:
        {
            DBG_GPIO("\n\rTest GPIO OD trigger :");
            #if _UART_OUT_GPIO2
            P0MOD = BITn(6)+0x00;      //uart : gpio6
            P0DIR |= 0xbf;
            P0SEL &= 0x40;

	        P1MOD = 0x00;
            P1DIR = 0xff;
            P1SEL = 0x00;
			
            #elif _UART_OUT_GPIO3
            P0MOD = BITn(7)+0x00;      //uart : gpio7
            P0DIR |= 0x7f;
            P0SEL &= 0x80;

	        P1MOD = 0x00;
            P1DIR = 0xff;
            P1SEL = 0x00;
  
            #else 
            P0MOD = 0x00;
            P0DIR = 0xff;
            P0SEL = 0x00;		
			
            #endif

			
            #if _UART_OUT_GPIO2
            P0BUF |= 0xbf;
	        P1BUF = 0xff;
		 
            #elif _UART_OUT_GPIO3
            P0BUF |= 0x7f;
	        P1BUF = 0xff;

	     #else
	        P0BUF = 0xff;
            #endif
           
            while (1)
            {
                P0BUF = ~P0BUF;
                P1BUF = ~P1BUF;
                DBG_GPIO("\n\rP0:%4x",P0BUF);
                DBG_GPIO("\n\rP1:%4x",P1BUF);
                DelayMs(1000);
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
#endif

