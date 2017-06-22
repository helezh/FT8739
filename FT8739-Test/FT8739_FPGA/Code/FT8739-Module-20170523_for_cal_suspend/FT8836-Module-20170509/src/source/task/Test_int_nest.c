/*******************************************************************************
 * Copyright (c) 2010~2014 Focaltech (Shenzhen) Inc.
 * All right reserved.
 *
 * Project:     FT8836
 * File:        �ж�Ƕ�ײ���
 *
 * VERSION        DATE              AUTHOR
 * V0.1           2014-04-29        xinkunpeng
 *******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_int_nest.h"

#if _TEST_INT_NEST_EN

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
//time0
#define T0MODE                            0x02     //����λΪT1,����λΪT0
#define IRQTIME0_VALUE                    100      //(MS)
#define IRQTIME0_LOAD()                   TMOD|=T0MODE;TH0=IRQTIME0_VALUE;TL0=0

//time1
#define T1MODE                            0x20     //����λΪT1,����λΪT0
#define IRQTIME1_VALUE                    100      //(MS)
#define IRQTIME1_LOAD()                   TMOD|=T1MODE;TH1=IRQTIME1_VALUE;TL1=0
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
UINT8 g_usCntFlag = 0;
/*******************************************************************************
*   Name: DrvHostI2cInit
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvHostI2cInit(void)
{
    I2CBUF = 0;
    I2CRI  = 0;
    I2CTI  = 0;

    I2CADDR = I2C_SLAVE_ADDR&0xFE;

    I2C_STOP_IF = 0;  //����жϱ�־
    I2C_STOP_EI = 1;  //�����ж�

    ET2 = 1;          /* ����I2C�ж� */
}

/*******************************************************************************
*   Name: DrvSysTimer0_Init
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvSysTimer0_Init(void)
{
    TR0 = 0;
    IRQTIME0_LOAD();
    TR0 = 1;
    ET0 = 1;
}

/*******************************************************************************
*   Name: DrvSysTimer1_Init
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvSysTimer1_Init(void)
{
    TR1 = 0;
    IRQTIME1_LOAD();
    TR1 = 1;
    ET1 = 1;
}

/*******************************************************************************
*   Name:  DrvCounterInit
*  Brief: Counter��ʼ��
*          1.ʱ���ǹ̶�500K,
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvCounterInit(void)
{
    // cnt clk enable
    CNTCKEN = 1;

    // ����CNT����ʱ��
    CNTIVH = 0x10;
    CNTIVM = 0xa0;
    CNTIVL = 0x00;

    CNT_WKEN = 1;
//    RTC_CNT_WKEN  = 1;

    // clear cnt
    CNT_CLEAR     = 1;
    CNT_START     = 1;
    DBG_INT("\n\rinit count OK!");
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT1�жϳ�ʼ������
*******************************************************************************/
void ExternInt1Init(void)
{
    IT1 = 0;   // 0:LOW level triggered 1:falling edge
    EX1 = 1;

    EA = 1;
}
/*******************************************************************************
*   Name: Timer_IRQHandler
*  Brief: Timer �ж���Ӧ����
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void Timer0_IRQHandler(void) interrupt  1
{
    DBG_INT("\n\rTimer0 in");
    DBG_INT("\n\rTimer0 out");
}

/*******************************************************************************
*   Name: Timer_IRQHandler
*  Brief: Timer �ж���Ӧ����
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void Timer1_IRQHandler(void) interrupt  3
{
    UINT8 cnt = 100;
    DBG_INT("\n\rTimer1 in");
    while (cnt--)
    {
        DelayMs(100);
    }
    DBG_INT("\n\rTimer1 out");
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT1�ж���Ӧ����
*******************************************************************************/
void Exint1_IRQHandler(void) interrupt 2
{
    UINT8 cnt = 100;
    DBG_FLOW("\n\rint1 in");
    while (cnt--)
    {
        DelayMs(100);
    }   
    // ��cnt
    CNT_CLEAR     = 1;
    CNT_START     = 0;
    g_usCntFlag = 1;
    DBG_FLOW("\n\rint1 out");
}

/*******************************************************************************
*   Name: I2C_IRQHandler
*  Brief:
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void I2C_IRQHandler(void) interrupt 5
{
    UINT16 cnt = 200;
    DBG_INT("\n\rI2C in");
    if (RIFLAG)
    {
        RIFLAG = 0;

        while (cnt--)
        {
            DelayMs(100);
        }
    }

    if (TIFLAG)
    {
        TIFLAG = 0;
    }

    DBG_INT("\n\rI2C out");
}

/*******************************************************************************
*   Name: I2CStop_IRQHandler
*  Brief:
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void I2CStop_IRQHandler(void) interrupt 8
{
    I2CSTP = 0;
}

/*******************************************************************************
*   Name: init_int
*  Brief:
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void init_int(void)
{
    //I2C�ж�
    DrvHostI2cInit();

    //��ʱ��0
    DrvSysTimer0_Init();

    //��ʱ��1
   DrvSysTimer1_Init();

    /*counter �ж�*/
    DrvCounterInit();
    
    ExternInt1Init();   
    //UART ���ȼ� = 3
    Uart_IPH = 1;
    Uart_IPL = 1;

    //I2C ���ȼ�  = 2
    I2C_IPH = 1;
    I2C_IPL = 0;
   //exint1 ���ȼ�  = 1
    IPHX1= 0;
    IPLX1= 1;   
    //time0 ���ȼ� = 0
    IPHT0 = 0;
    IPLT0 = 0;

    //time1 ���ȼ� = 0
    IPHT1 = 0;
    IPLT1 = 0;

    //�����ж�
    EA = 1;
}

/*******************************************************************************
*   Name: Test_int_nest
*  Brief:
*  Input: none
* Output: none
* Return: none
*******************************************************************************/
void Test_int_nest(void)
{
    init_int();
    while (1)
    {
        while(!g_usCntFlag);
        g_usCntFlag = 0;
        CNT_START = 1;
    }
}

#endif
