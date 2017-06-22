/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Test_UART.c
*
*    Author: 
*
*   Created: 2016-11-29
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
#include "Test_Uart.h"

#if _TEST_UART_EN
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define TEST_UART_RECEIVE_EN    1             //����uart���չ���

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

/*******************************************************************************
*   Name: Uart_Set_RaudRate
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Uart_Set_RaudRate(UINT32 Rate, UINT8 main_clk)
{
    UINT16 cnt;
    
    cnt = (0x400 - (main_clk*1000000/16)/Rate);  //����������
    UART_RELH = cnt>>8;
    UART_RELL = cnt;
}

/*******************************************************************************
*   Name: Test_Uart
*  Brief: ����uart�ڲ�ͬ��Ƶϵ�����ܷ�������ӡ
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_UART(void)
{
#if (TEST_UART_RECEIVE_EN&&_UART_RECEIVE_EN)
	UINT8 ucData;
#endif
    UINT8 Div,i,main_clk = 48;

    DBG_FLOW("\nDSV_CON:%02x",DSV_CON);
    DBG_FLOW("\nSYS_CON:%02x",SYSCON);
    DBG_FLOW("\nP0MOD:%02x",P0MOD);
    DBG_FLOW("\nTESTCON3:%02x",TESTCON3);
    DBG_UART("\nTest Uart Start");
    DelayMs(500);
#if (TEST_UART_RECEIVE_EN&&_UART_RECEIVE_EN)
 //��ѯ��ʽ�����������Ƿ���ȷ
	EC = 0;
	while(1)
	{
		while(UART_RI == 0);//�ȴ�����
		UART_RI = 0;
		ucData = UARTBUF;

		UARTBUF = ucData;
		while(UART_TI == 0);//�ȴ�����
		UART_TI = 0;
	}
#endif    
    for(Div = 0 ; Div < 2; Div ++)
    {
        DrvSysClkInit(Div);

        main_clk = 48/CLK_DIV(Div);

        Uart_Set_RaudRate(BAUD_RATE,main_clk);
        DelayMs(1000);

        DBG_UART("\nmain clk is %dM",main_clk);

#if 0        
        for(i = 0;i < 100; i++)
        {
            DBG_UART("\n%x",0x55);
            DBG_UART("\n%x",0xAA);            
        }
#endif        
        DelayMs(1000);//��ʱ���Ա�֤��ӡ�Ժ�uart�����òŻᷢ���ı�
    }


    DrvSysClkInit(MAIN_CLK); //�л�ԭ��״̬ 
    Uart_Set_RaudRate(BAUD_RATE,48);

    DelayMs(1000);
    DBG_UART("\n%x",0x55);
    DBG_UART("\n%x",0xAA);

    /*���Է��ʹ�������*/
    for(i = 0; i < 0xFF; i++ )
    {
        DBG_UART("\nTest Sending large number of data");
        DBG_UART("\nThe %d Test",i);
     }
    
    DBG_UART("\nTest Uart End");  
    
}
#endif
