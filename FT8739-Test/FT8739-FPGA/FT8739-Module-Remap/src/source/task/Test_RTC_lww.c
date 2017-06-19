/*******************************************************************************
* Copyright (C) 2013-2014, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: Test_RTC.c
*
*    Author: xinkunpeng
*
*   Created: 2014-04-18
*
*  Abstract:
*
* Reference:
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Test_RTC.h"

#if _TEST_RTC_EN
 
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
/* RTC */
#define RTC_MS        32
#define RTC_N_MS     (RTC_MS*10)//100ms

/*
 * Normal   :��ʱCPU����RTC��RTC����һ�ζ�ʱ�жϣ���ʱʱ�������Counter���
 * Slot     :��ʱCPU����RTC������wake_sub_en����RTC�����slot_num+1���жϸ�CPU
 * Auto     :��ʱCPU����һ��RTC������һ��RTC�жϸ�CPU���������޴��жϸ�ASM��
             ֱ��CPU CLR RTC
 * LCD Start:��ʱRTC�����LCD�ź���������Counter�м���Զ�����LCD��start
             �ź�
 * ����ģʽ��CPU��ֻ����һ���жϣ������ж�����Ҫ��RTC_CLR
*/
/*
 * ����㣺
 * 1.eint1�в���RTC_CLRҲ���ᵼ��һֱͣ��eint1�ж��в����������ó�small����big int��һ��
 * 2.RTC��ӡ�����Ķ�ʱʱ�����趨ʱ�䲻һ�����趨ʱ��100ms��ʵ�ʳ���ʱ����66ms
*/
//RTC MODE 0-Normal,1-Slot,2-Auto,3-Lcd Start
#define RTC_MODE    0

/* time0 */
#define T0MODE                            0x02    //����λΪT1,����λΪT0
#define IRQTIME0_VALUE                    1       //(MS)
//#define IRQTIME0_LOAD()                   TMOD|=T0MODE;TH0=IRQTIME0_VALUE;TL0=0 old
#define IRQTIME0_LOAD()                   TMOD|=T0MODE;TH0=IRQTIME0_VALUE;TL0=0

#define TEST_RTC_WK                       0//0:������rtc wk��1 ����rtc wk
#define INT1_TRI_MODE                     1// 0:LOW level triggered 1:falling edge

//#define AUTO_MODE                         1//0:������Auto_mode  1:����Auto_Mode
#define RTC_SLOT_NUM                      9
#define RTC_SLOT_NUM_NONE                 0
#define TEST_WAKE_EN_SUB                  0

//��������ģʽ���ֻ�ܽ���һ��
#define STANDBY_MODE                      0//0:������standy 1:����standy
#define STOP_MODE                         0// 0:������stop   1:����stop
#define IDLE_MODE                         0//0:������idle     1:����idle

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
UINT8 g_nWKsrc     = 0x00;
BOOLEAN g_bWKsrcOut = 1;
BOOLEAN g_bRtcFlag  = 0;

UINT16 m_usCnt = 0;
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:  DrvRTCInit
*  Brief:  RTC��ʼ��
*          1.ʱ���ǹ̶�32K, 1��32000�Σ�1ms��32�� = 0x20
*          2.������Ϊ16λ��--��0�������ж�
*          3.���ʱʱ��: t = 0x10000/0x20 = 65536/32 = 2048ms
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvRTCInit(void)
{
    // 32Kʱ��ʹ��
    CLK_WP = 1;
    EN_32K = 1;
    CKEN_32KRTC = 1;
    
    // rtc clk enable
    RTCCKEN = 1;
//    DBG_RTC("\nRTCCON:%x",RTCCON);
    // clear rtc
    RTC_WP  = 1;
    RTC_CLR = 1;
    //DelayMs(100);

    // ����RTC����ʱ��
    RTCIVH  = RTC_N_MS>>8;
    RTCIVL  = RTC_N_MS;

    //Normal mode
    #if (RTC_MODE == 0)
//    RTCSLN        = RTC_SLOT_NUM_NONE;
    RTC_AUTO_MODE = 0;
    LCD_START_EN  = 0;
    #endif

    //Slot mode
    #if (RTC_MODE == 1)
//    RTCSLN          = RTC_SLOT_NUM;
    RTC_AUTO_MODE   = 0;
    LCD_START_EN    = 0;
    #endif

    //Auto mode
    #if (RTC_MODE == 2)
//    RTCSLN          = RTC_SLOT_NUM_NONE;
    RTC_AUTO_MODE   = 1;
    LCD_START_EN    = 0;
    #endif

    //LCD Start mode
    #if (RTC_MODE == 3)
//    RTCSLN = RTC_SLOT_NUM_NONE;
    RTC_AUTO_MODE = 1;
    LCD_START_EN = 1;
    #endif

//    DBG_RTC("\nRTCCON:%x",RTCCON);

    #if TEST_RTC_WK
    RTC_CNT_WKEN = 1;  // RTC wake en  
    #endif

    //RTC�ж���Ϊ�ж�0
    #if TEST_WAKE_EN_SUB
    RTC_WKEN_SUB = 1;
    RTC_WKEN     = 0;
    RTCSLN       = RTC_SLOT_NUM;
    #else
    RTC_WKEN     = 1;  // select rtc  
    RTC_WKEN_SUB = 0;
    RTCSLN = RTC_SLOT_NUM_NONE;    
    #endif
 
    DBG_RTC("\nRTC Interval:%dms",RTC_N_MS/RTC_MS);         // 1.8ms@115200bps total 19 character 100us per character
    DBG_RTC("\nRTC_IVH:%02X,RTC_IVL:%02X",RTCIVH,RTCIVL);
    DBG_RTC("\ninit RTC OK!");
    P0_3 = 1;
    DelayMs(200);   
    P0_3 = 0;
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT0�жϳ�ʼ������
*******************************************************************************/
void ExternInt0Init(void)
{
    IT0   = 0;   // 0:LOW level triggered 1:falling edge

    IPL0  = 0;
    IPH0  = 0;

    IPLX0 = 1;
    IPHX0 = 1;  //�ж�0���ȼ��������

    EX0   = 1;
}

/*******************************************************************************
*   Name: DrvSysTimer0_Init
*  Brief: ��ʱ1ms
*  Input:
* Output:
* Return: timer0 ��ʱ����ʼ������
*******************************************************************************/
void DrvSysTimer0_Init(void)
{
    TR0 = 0;     /* Stop Timer Counter */
    IRQTIME0_LOAD();    //1//1ms interval

//    IPHT0 = 1;
//    IPLT0 = 1;
    
    TR0 = 1;
    ET0 = 1;     // enable timer interrupt
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
    IT1 = INT1_TRI_MODE;   // 0:LOW level triggered 1:falling edge
    IPHX1 = 1;
    IPLX1 = 1;
    EX1   = 1;       
    EA    = 1;
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT0�ж���Ӧ����
*******************************************************************************/
void Exint0_IRQHandler(void) interrupt 0
{
    if (g_bWKsrcOut)
    {
        g_nWKsrc = IWKSTA;
        g_bWKsrcOut = FALSE;
    }
    g_bRtcFlag = TRUE;
    if(RTC_CNT_INT)
    {
        //P0_6 = ~P0_6;
        RTC_CNT_WKEN = 0;
        //RTC_WP  = 1;
        //RTC_CLR = 1;        
        //DBG_FLOW("\n\rrtc int0");
        DBG_RTC("\n0");
    }
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: timer0 ��ʱ���ж���Ӧ����
*******************************************************************************/
void Timer0_IRQHandler(void) interrupt  1
{
    m_usCnt++;
    #if 1
    P0_7 = 1;
    DelayUs(5);
    P0_7 = 0;
    #else
    DBG_RTC("\n1");
    #endif
}

/*******************************************************************************
*   Name:
*  Brief:
*  Input:
* Output:
* Return: INT1�ж���Ӧ����.
*******************************************************************************/
void Exint1_IRQHandler(void) interrupt 2
{   
    #if 0
    P0_7 = 1;
//    DelayMs(1);
    P0_7 = 0;
    #endif
    //if(RTC_CNT_INT)//������RTC_CNT_INT�жϣ�����int0�øñ�־�ж��ˣ�����int1ʱ�ñ�־�Ѿ�Ϊ0
    {
        //P0_7 = ~ P0_7;
        
        //��rtc
//        #if !AUTO_MODE//AUTO MODE����дCLR����ΪдCLRʱ��ر�RTC�ڲ���gating��û���ظ�����RTC�жϡ�
        RTC_WP  = 1;
        RTC_CLR = 1;
//        #endif
        
        #if !INT1_TRI_MODE//����ǵ͵�ƽ����ģʽ����Ҫ�ȴ�RTC_CNT_INT��0���������뼸���жϣ��ñ�־����ʱ��Ϊ1��RTC CLK
        while(RTC_CNT_INT);
        #endif
        
        //DBG_FLOW("\n\rrtc int1");
        DBG_RTC("\n2");
        g_bRtcFlag = TRUE;

        #if TEST_RTC_WK
            RTC_CNT_WKEN = 1;
        #endif
    }
}


/*******************************************************************************
*   Name: Test_RTC
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_RTC(void)
{
    P0_3 = 0;
    IPL0  = 0;
    IPH0  = 0;
    DrvRTCInit();
    ExternInt1Init();
    DrvSysTimer0_Init();
    
    #if TEST_RTC_WK
    ExternInt0Init();
    #endif
    
    // clear rtc
//    RTC_WP  = 1;
//    RTC_CLR = 1;    

    // RTC Start
    RTC_WP    = 1;
    RTC_START = 1;

    g_bRtcFlag  = FALSE;
    
    #if 1
//    P0_7 = 1;
//    DelayUs(1);
    P0_7 = 0;
    #endif

    while (1)
    {     
        #if TEST_RTC_WK
        RTC_CNT_WKEN = 1;  // RTC wake en  
        #endif 
      
        g_bWKsrcOut = 1;
//        DBG_RTC("\n\rRTC init time=%dms",m_usCnt);  

        //idle_mode
        #if  IDLE_MODE
        DBG_RTC("\nj");
        DelayMs(1);
        DrvSysPowerIdle();
        DBG_RTC("\ne");        
        #endif

        //standby_mode
        #if STANDBY_MODE
        DBG_RTC("\njoin in Standby");
        //DelayMs(50);    
        DrvSysPowerStandby();
        DBG_RTC("\n exit power");
        #endif
        
        //stop_mode
        #if STOP_MODE
        DBG_RTC("\njoin in Stop");
        //DelayMs(50);        
        DrvSysPowerStop();
        DBG_RTC("\nexit power");        
        #endif
        
        while (!g_bRtcFlag)
        {
            P0_2 = 1;
            P0_2 = 0;
        }
        DBG_RTC("\n=%dms",m_usCnt);   
        m_usCnt = 0;
//        RTC_WP    = 1;
//        RTC_START = 1;
//        DelayMs(5);
//        m_usCnt = 0;
        if (g_bRtcFlag && g_bWKsrcOut == FALSE)
        {
            DBG_RTC("\n\rWK src:%x",g_nWKsrc);
        }
    //DelayMs(2000);
    }
}
#endif



