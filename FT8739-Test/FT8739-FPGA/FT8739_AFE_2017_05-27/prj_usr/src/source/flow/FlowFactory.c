 /*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: FlowFactory.c
*
*    Author: lisen
*
*   Created: 2016-12-06
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "FlowFactory.h"
#include "DrvSysCtrl.h"
#include "AppHostComm.h"
#include "AppSysCtrl.h"
#include "CfgSystem.h"
#include "AppParameter.h"
#include "LibDrv.h"
#include "DrvAsm.h"
#include "DrvAfe.h"
#include <intrins.h>

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define CFG_TX_NUM     (9*2)
#define CFG_RX_NUM     36

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/


typedef enum
{
    UP_K1_DELAY = 0x0001,
    UP_K2_DELAY = 0x0002,
    UP_SYNC_NUM = 0x0004,
    UP_CF       = 0x0008,
    UP_SUB_BASE = 0x0010,
    UP_NUM_LIST = 0x0020,
    UP_CB       = 0x0040,
    UP_ORDER    = 0x0080,
    UP_DUMMY    = 0x0100,
    UP_NOISE_THR    = 0x0200,
    UP_SWITCH_FREQ  = 0x0400,
    UP_TEST_CH      = 0x0800,     // 通道检测
    UP_MON_THR      = 0x1000,
} ENUM_UP_PARA;

typedef enum
{
    UP_SYS_PARA = 0x01,
    UP_PANEL_PARA = 0x02,
} ENUM_UP_GROUP_PARA;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

BOOLEAN s_bPanelParamUpdated = FALSE;   /* 系统参数更新标志 */
UINT16 XRAM s_usParaFlag = 0x00;        /* AFE参数写入更新标志，按bit位安排 */

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT16 XRAM s_usRawCnt;               /* Read rawdata counter */
UINT16 XRAM s_usCbCnt;                /* RW CB counter */
UINT16 XRAM s_usOrderCnt;             /* RW Order counter */

UINT8 XRAM * XRAM s_pucCbBuf;
UINT16 XRAM * XRAM s_pucOrderBuf;
UINT8 XRAM * XRAM s_pucRawBuf;

UINT16 XRAM  g_usCBBuf[CH_LEN_MAX<<1];           //Tab表中初始化CB用的Buffer
UINT8  XRAM  ucCbValue[CH_LEN_MAX<<1];            /* CB值 先放Tp.后放Key*/

UINT16 XRAM  g_usInfo[30];                       // Info信息标志
UINT16 XRAM  g_usRawdataBuf[(CH_LEN_MAX+1)*2];   // Rawdata (288+4key) *2 
UINT16 XRAM  g_usBaseBuf[(CH_LEN_MAX+1)*2];      // Base    (288+4key) *2 

UINT16  XRAM  g_ucOrderBuf[CH_ORDER_MAX<<1];      // Order   288不包含key


volatile UINT16 XRAM g_usAsmIntFlag0      = 0x00;    // 中断中的软件标志
volatile UINT16 XRAM g_usAsmIntFlag1      = 0x00;

volatile UINT8 XRAM g_ucFrameEndFlag    = 0x00;  // frame end
volatile UINT8 XRAM g_ucAramReadyFlag   = 0x00;  // Aram ready
volatile UINT8 XRAM g_ucCbAdjOverFlag   = 0x00;  // Cb over
volatile UINT8 XRAM g_ucConvertOverFlag = 0x00;

volatile UINT8 XRAM g_ucLcdBusyFlag     = 0x00;
volatile UINT8 XRAM g_ucLcdStopFlag     = 0x00;
volatile UINT8 XRAM g_ucLcdStartFlag    = 0x00;
volatile UINT8 XRAM g_ucLcdSyncMissFlag = 0x00;   
volatile UINT8 XRAM g_ucTimeOutFlag     = 0x00;  // hw mon time out
volatile UINT8 XRAM g_ucTchDetFlag      = 0x00;  // tch det

volatile UINT8 XRAM g_ucAbnormalFlag    = 0x00;   // 0x01:esd 0x02:LVD 0x04:sync_mis
volatile UINT8 XRAM g_ucState0 = 0x00;
volatile UINT8 XRAM g_ucState1 = 0x00;

UINT8 XRAM ucAfeRunMode   = 0x00;
UINT16 *XRAM ap0;
UINT16 *XRAM g_ucAram;
volatile UINT16 XRAM g_ucIntCount = 0;
UINT16 XRAM g_usAsmSta1 = 0;
volatile UINT16 XRAM g_usAsmIntSta;


#if TEST_60HZ_SCAN_MODE
UINT8 XRAM g_ucAfeScanMode   = TP_60HZ_RUN_MODE;
#else
UINT8 XRAM g_ucAfeScanMode   = TP_120HZ_RUN_MODE; 
#endif

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


/*******************************************************************************
*   Name: AppWriteReg0x01
*  Brief:
*  Input:
*
* Output: None
* Return:
*******************************************************************************/
void AppWriteReg0x01(UINT8 ucData)
{
    switch (ucData)
    {
        case R01_CNT_CLEAR:
        {
            s_usRawCnt = 0;
            break;
        }
        case R01_CNT_KEY:
        {
            s_usRawCnt = (TX_NUM * RX_NUM)<<1;
            g_unPanelParam.reg.ucRawAddrH = (s_usRawCnt>>1)>>8;
            g_unPanelParam.reg.ucRawAddrL = (s_usRawCnt>>1)%256;
            break;
        }

        default:
        {
            break;
        }
    }
}
/*******************************************************************************
*   Name: AppWriteRegMapDataTest
*  Brief: Write a byte to the register at given address in test device mode
*  Input: UINT8 ucAddr => register address
*         UINT8 ucData => register value to be written
* Output: None
* Return: UINT8 => the read byte
*******************************************************************************/
void AppWriteRegMapDataTest(UINT8 ucAddr,  UINT8 ucData)
{
    UINT16 usBufAddr;

    /* set System parameters */
    if (ucAddr == ID_G_DEVICE_MODE)
    {
        AppHostUpdateHeadState(ucData);
    }
    
    /* make s_pucRawBuf point to related raw row data */
    else if (ucAddr == ID_G_RAWDATA_SETCT)
    {
        g_unPanelParam.reg.ucRawSel = ucData;
        AppWriteReg0x01(ucData);
    } 
    else if (ucAddr <= ID_G_DIFF_NOISE0)
    {
        if (ucAddr == ID_G_SCAN_MODE)
        {
            /* 模式不变，或者异常数据，则不更新 */
            if ((ucData == g_unPanelParam.reg.ucScanMode)
                || (ucData >= 4))
            {
                return;
            }
        }

        switch (ucAddr)
        {
            // 只读寄存器处理
            // case ID_G_TX_NUM:
            // case ID_G_RX_NUM:
            case ID_G_LCD_BUSY_NUM:
            case ID_G_RUN_MODE:
            case ID_G_P1P2_DELAY:
            case ID_G_DROP_FLAG:
            case ID_G_RAW_BUF_STA:
            case ID_G_PARAUP_STATE:
                return;
        }

        g_unPanelParam.Offset[ucAddr] = ucData;

        switch (ucAddr)
        {
            case ID_G_CLB:
            case ID_G_SCAN_MODE:
            case ID_G_KEY_EN_LEFT:
            case ID_G_KEY_EN_RIGHT:
            case ID_G_DATA_MODE:
            case ID_G_RAW_BUF_SEL:
            {
                s_bPanelParamUpdated = TRUE;
                break;
            }

            case ID_G_INT_TEST_EN:
            {
                //AppTestIntPin();
                break;
            }

            case ID_G_DUMMY_STB:
            case ID_G_DUMMY_FRM:
            case ID_G_DUMMY_SEG:
            {
                s_usParaFlag |= UP_DUMMY;
                break;
            }

            case ID_G_K1_DELAY:
            {
                s_usParaFlag |= UP_K1_DELAY;
                break;
            }

            case ID_G_K2_DELAY:
            {
                s_usParaFlag |= UP_K2_DELAY;
                break;
            }

            case ID_G_SYNC_NUM:
            {
                s_usParaFlag |= UP_SYNC_NUM;
                break;
            }

            case ID_G_CF:
            {
                s_usParaFlag |= UP_CF;
                break;
            }

            case ID_G_SUB_BASE0:
            {
                s_usParaFlag |= UP_SUB_BASE;
                break;
            }

            /* 设置 CB地址, 单位8bit */
            case ID_G_CB_ADDR_L:
            {
                s_usCbCnt = (g_unPanelParam.Offset[ID_G_CB_ADDR_H]<<8) + ucData;
                break;
            }

            /* 设置 order地址, 单位8bit */
            case ID_G_ORDER_ADDR_L:
            {
                s_usOrderCnt = (g_unPanelParam.Offset[ID_G_ORDER_ADDR_H]<<8) + ucData;
                break;
            }

            /* 设置 rawdta地址, 单位16bit */
            case ID_G_RAW_ADDR_L:
            {
                s_usRawCnt = ((g_unPanelParam.Offset[ID_G_RAW_ADDR_H]<<8) + ucData)<<1;
                break;
            }

            default:
            {
                break;
            }
        }

        if (ucAddr >= ID_G_NUMLIST0 && ucAddr <= ID_G_NUMLIST15)
        {
            /* 写低位的时候更新寄存器 */
            if (ucAddr % 0x02 == 1)
            {
                s_usParaFlag |= UP_NUM_LIST;
            }
        }

        if (ucAddr >= ID_G_RF_NOISE1)
        {
            s_usParaFlag |= UP_NOISE_THR;
        }

        if (ucAddr == ID_G_FREQ_IDX)
        {
            s_usParaFlag |= UP_SWITCH_FREQ;
        }
    }
    /* Write order data */
    else if ((ucAddr == ID_G_ORDER_BUF0) || (ucAddr == ID_G_ORDER_BUF1))
    {
        s_usParaFlag |= UP_ORDER;
        usBufAddr = (g_unPanelParam.reg.ucOrderAddrH<<8) + g_unPanelParam.reg.ucOrderAddrL;
        g_unPanelParam.reg.ucOrderAddrL++;
        if (g_unPanelParam.reg.ucOrderAddrL == 0x00)
        {
            g_unPanelParam.reg.ucOrderAddrH++;
        }
        //g_stFrmInfo.ch.aucOrder[usBufAddr] = ucData;
        if (ucAddr == ID_G_ORDER_BUF1)
        {
            g_ucI2cDataAddr = ID_G_ORDER_BUF0;
        }
    }
    /* Write CB data */
    else if ((ucAddr == ID_G_CB_BUF0) || (ucAddr == ID_G_CB_BUF1))
    {
        s_usParaFlag |= UP_CB;
        usBufAddr = (g_unPanelParam.reg.ucCbAddrH<<8) + g_unPanelParam.reg.ucCbAddrL;
        g_unPanelParam.reg.ucCbAddrL++;
        if (g_unPanelParam.reg.ucCbAddrL == 0x00)
        {
            g_unPanelParam.reg.ucCbAddrH++;
        }
        if ((ucData >= 64)&&(usBufAddr < CH_LEN))      /* 有效通道总长度, 不含按键 */
        {
            ucData = 64 + ((ucData-64)*4);
        }
        s_pucCbBuf[usBufAddr] = ucData&0x7F;
        if (ucAddr == ID_G_CB_BUF1)
        {
            g_ucI2cDataAddr = ID_G_CB_BUF0;
        }
    }
}

/*******************************************************************************
*   Name: AppReadRegMapDataTest
*  Brief: Read a byte from the register at given address in test device mode
*  Input: UINT8 ucAddr => register address
* Output: None
* Return: UINT8 => the read byte
*******************************************************************************/
UINT8 AppReadRegMapDataTest(UINT8 ucAddr)
{
    UINT8 ucData;

    /* system parameters */
    if (ucAddr <= ID_G_DIFF_NOISE0)
    {
        return g_unPanelParam.Offset[ucAddr];
    }
    /* 一次性连续读取所有rawdata数据 */
    else if ((ucAddr == ID_G_RAW_BUF0) || (ucAddr == ID_G_RAW_BUF1))
    {
        ucData = s_pucRawBuf[s_usRawCnt++];
        if (ucAddr == ID_G_RAW_BUF1)
        {
            g_ucI2cDataAddr = ID_G_RAW_BUF0;
        }
        return ucData;
    }
    /* 一次性连续读取所有 CB 数据: va 6bit ,key 8bit*/
    else if ((ucAddr == ID_G_CB_BUF0) || (ucAddr == ID_G_CB_BUF1))
    {

        if (s_usCbCnt < CH_LEN) // 288/324 *2
        {
            ucData = s_pucCbBuf[s_usCbCnt]&0x3F;
        }
        else
        {
            ucData = s_pucCbBuf[s_usCbCnt];
        }
        s_usCbCnt++;
        if (ucAddr == ID_G_CB_BUF1)
        {
            g_ucI2cDataAddr = ID_G_CB_BUF0;
        }
        return ucData;
    }

    /* 一次性连续读取所有 Order 数据 */
    else if ((ucAddr == ID_G_ORDER_BUF0) || (ucAddr == ID_G_ORDER_BUF1))
    {
        ucData = s_pucOrderBuf[s_usOrderCnt++];
        if (ucAddr == ID_G_ORDER_BUF1)
        {
            g_ucI2cDataAddr = ID_G_ORDER_BUF0;
        }
        return ucData;
    }

    else if ((ucAddr >= ID_FREE_RUN) && (ucAddr <= ID_G_LCD_INFO_END))
    {
        //return AppReadLcdInfo(ucAddr);
        return 0; //ls
    }

    /* 取FW buf */
    else if ((ucAddr == ID_G_FW_BUG0) || (ucAddr == ID_G_FW_BUG1))
    {
        UINT16 FwInfoStart;
        FwInfoStart = 0x70;

        //tmp = XDATA_ADDR8(FwInfoStart + g_unPanelParam.reg.FwInfoCnt);
        ucData = PRAM_ADDR8(FwInfoStart + g_unPanelParam.reg.FwInfoCnt);

        g_unPanelParam.reg.FwInfoCnt++;
        if (ucAddr == ID_G_FW_BUG1)
        {
            g_ucI2cDataAddr = ID_G_FW_BUG0;
        }

        return ucData;
    }
    /* 调试窗口信息 */
    else
    {
        return 0;
    }
}

void AppPanelParamUpdate(void)
{
    s_pucRawBuf =(UINT8 XRAM *)&g_usRawdataBuf[0]; 
    s_pucOrderBuf = (UINT16 XRAM *)&g_ucOrderBuf[0];
    s_pucCbBuf = (UINT8 XRAM *)&ucCbValue[0];
    s_usCbCnt = 0x00;
}

void AppShowRawdata(void)
{
    UINT16  i;

    // TP Rawdata
    for(i = 0; i < (CH_ORDER_MAX)*2;i++)
    {
        if(i<CH_ORDER_MAX)
        {
            if((i%(RX_NUM/2)) == 0)  
            //if((i%(30)) == 0)  
            {
                DBG_FLOW("\n ");   
            }
            DBG_FLOW("%04x ",g_usRawdataBuf[i]);
        }
    }

    // KEY rawdata 最后8个数据放key, 左右各4个，只用一边。
    DBG_FLOW("\n ");
    for(i = 0;i < 8; i++)
    {
        DBG_FLOW("K%d :%05x ",i,g_usRawdataBuf[CH_ORDER_MAX*2 + i]);
    }
    
    // Info信息
    DBG_FLOW("\n ");
    for(i = 0;i < 6; i++)
    {
        DBG_FLOW("If%d:%05x ",i,g_usInfo[i]);
    }
}

void DrvGetDiffNoseMax(void)
{
    UINT16 XRAM DiffMaxLTP;
    UINT16 XRAM DiffMaxRTP;
    UINT16 XRAM DiffMaxLKey;
    UINT16 XRAM DiffMaxRKey;
    
    ARAM_SEL = 1;
    ap0 = (UINT16)ARAM_DATA_BASE_ADDR;  

    DiffMaxLTP = ap0[ARAM_INFO_BASE_ADDR + TP_L_DIFF_NOISE_MAX_ADDR];
    DiffMaxRTP = ap0[ARAM_INFO_BASE_ADDR + TP_R_DIFF_NOISE_MAX_ADDR];
    DiffMaxLKey = ap0[ARAM_INFO_BASE_ADDR + KEY_L_DIFF_NOISE_MAX_ADDR];
    DiffMaxRKey = ap0[ARAM_INFO_BASE_ADDR + KEY_R_DIFF_NOISE_MAX_ADDR];

    DBG_FLOW("\n DiffMax LTp:%05d  RTp:%05d  LKey:%05d  RKey:%05d",DiffMaxLTP,DiffMaxRTP,DiffMaxLKey,DiffMaxRKey);    
    ARAM_SEL = 0;
}

void DrvGetBase(void)
{
    UINT16  i;
    
    for(i = 0; i < (CH_LEN_MAX)*2;i++)
    {
        g_usBaseBuf[i] = g_usRawdataBuf[i];
    }
    DBG_FLOW("\n-------Get Base-----");    
}

void DrvGetDiffdata(void)
{
    UINT16  i;
    SINT16 XRAM diff;
    
    DBG_FLOW("\n-------Get differ-----");    

    for(i = 0; i < (CH_LEN_MAX)*2;i++)
    {        
        diff = g_usRawdataBuf[i]-g_usBaseBuf[i];
        if(i<400)
        {
            if((i%18)==0)
            {
                DBG_FLOW("\n");
            }
            DBG_FLOW("%05d ",diff);
        }
    }
}

void DrvInitAram(void)
{
    UINT16  i;

    ARAM_SEL = 1;
    EA = 0;

    g_ucAram = (UINT16)ARAM_DATA_BASE_ADDR; 
    
    // TP Rawdata + Key 
    for(i = 0; i < (CH_LEN_MAX)*2;i++)  // (324+4)*2  324,324,4,4
    {  
        g_ucAram[i] = 0;
    }
    EA = 1;
    ARAM_SEL = 0;
}     

void DrvGetAramData(void)
{
    UINT16  i;

    ARAM_SEL = 1;
    EA = 0;

    ap0 = (UINT16)ARAM_DATA_BASE_ADDR; 
   
    // TP Rawdata
    for(i = 0; i < (CH_ORDER_MAX)*2;i++)
    {
        EA = 1;
        g_usRawdataBuf[i] = ap0[i];
    }

    // KEY rawdata 最后8个数据放key, 左右各4个，只用一边。
    for(i = 0;i < 8; i++)
    {
        g_usRawdataBuf[CH_ORDER_MAX*2 + i] = ap0[CH_ORDER_MAX*2 + i];
    }
    
    // Info信息
    for(i = 0;i < 6; i++)
    {
        g_usInfo[i] = ap0[CH_ORDER_MAX*2 + 8 + i];
    }
    
    ARAM_SEL = 0;
    EA = 1;
}

void DrvGetRawdata(void)
{
    UINT16  i;

    ARAM_SEL = 1;
    EA = 0;

    ap0 = (UINT16)ARAM_DATA_BASE_ADDR; 
    
    // TP Rawdata
    for(i = 0; i < (CH_ORDER_MAX)*2;i++)
    {
        EA = 1;
        g_usRawdataBuf[i] = ap0[i];
        if(i<CH_ORDER_MAX)
        {
            if((i%(RX_NUM/2)) == 0)  
            //if((i%(30)) == 0)  
            {
                DBG_FLOW("\n ");   
            }
            DBG_FLOW("%04x ",g_usRawdataBuf[i]);
        }
    }

    // KEY rawdata 最后8个数据放key, 左右各4个，只用一边。
    DBG_FLOW("\n ");
    for(i = 0;i < 8; i++)
    {
        g_usRawdataBuf[CH_ORDER_MAX*2 + i] = ap0[CH_ORDER_MAX*2 + i];
        DBG_FLOW("Key%d :%05x ",i,g_usRawdataBuf[CH_ORDER_MAX*2 + i]);
    }
    
    // Info信息
    DBG_FLOW("\n ");
    for(i = 0;i < 6; i++)
    {
        g_usInfo[i] = ap0[CH_ORDER_MAX*2 + 8 + i];
        DBG_FLOW("Info%d:%05x ",i,g_usInfo[i]);
    }
    
    ARAM_SEL = 0;
    EA = 1;
}


/*******************************************************************************
*   Name: DrvGetRptRamRawBase
*  Brief: 地址: 0-323: Tp通道与Key键上报Rawdata所需的Order
*         地址: 324-651: Tp通道 Rawdata/Base 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void DrvGetRptRamRawBase(void)
{
    UINT16 XRAM j;
    UINT16 XRAM i;
//    SINT16 XRAM diff;
    static UINT16 XRAM getBaseCount = 0;    
    UINT16 XRAM ausBaseBufL[BASE_RAM_BASE_LEN + BASE_RAM_KEY_LEN]; // Base + 4key
    UINT16 XRAM ausBaseBufR[BASE_RAM_BASE_LEN + BASE_RAM_KEY_LEN]; // Base + 4key

    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);
    
    Drv_XsiRead(pXSI0Regs, BASE_RAM_START_ADDR + BASE_RAM_TP_RAWBASE_ADDR, ausBaseBufL,CH_LEN_MAX, AFE_REG);  
    Drv_XsiRead(pXSI1Regs, BASE_RAM_START_ADDR + BASE_RAM_TP_RAWBASE_ADDR, ausBaseBufR,CH_LEN_MAX, AFE_REG);  

    DBG_FLOW("\n---------DrvGet Rpt Ram ----------------------");
//    if(getBaseCount<60)
    {
        for(j = 0;j <CH_LEN_MAX;j++) //左边
        {
            if((j%18)==0)
            {
                DBG_FLOW("\n");
            }
          
            //if(j>=(CH_LEN_MAX-4))
            //{
                DBG_FLOW("%04x ",ausBaseBufL[j]);
            //}  
           
        }
#if 0  //右边  
        for(j = 0;j <CH_LEN_MAX;j++)//右边
        {
            if((j%18)==0)
            {
                DBG_FLOW("\n");
            }
            DBG_FLOW("%04x ",ausBaseBufR[j]);
        } 
#endif        
        getBaseCount++;
        DBG_FLOW("\n%04d",getBaseCount);
    }

    if(getBaseCount == 50)// Base
    {        
        for(i = 0;i <CH_LEN_MAX;i++)
        {
            g_usBaseBuf[i] = ausBaseBufL[i]; 
            if((i%18)==0)
            {
                DBG_FLOW("\n");
            }
            DBG_FLOW("%04x ",g_usBaseBuf[i]);
        }
    
        for(i = 0;i <CH_LEN_MAX;i++)
        {
            g_usBaseBuf[i+CH_LEN_MAX] = ausBaseBufR[i];
            if((i%18)==0)
            {
                DBG_FLOW("\n");
            }
            DBG_FLOW("%04x ",g_usBaseBuf[i+CH_LEN_MAX]);
        } 
    }

#if 0    //differ
    else if(getBaseCount>50)
    {
        for(i = 0;i <CH_LEN_MAX;i++)
        {
            diff = ausBaseBufL[i]-g_usBaseBuf[i]; 
            if((i%18)==0)
            {
                DBG_FLOW("\n");
            }
            DBG_FLOW("%04d ",diff);
        }
#if 0
        for(i = 0;i <CH_LEN_MAX;i++)
        {
            diff = ausBaseBufR[i]- g_usBaseBuf[i+CH_LEN_MAX];
            if((i%30)==0)
            {
                DBG_FLOW("\n");
            }
            DBG_FLOW("%04d ",diff);
        } 
#endif
    }  
#endif
    
}

/*******************************************************************************
*   Name: Afe_Clk_Init
*  Brief: Afe时钟初始化
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Clk_Init(void)
{  
    AFEACKEN = 1;    
    AFECKEN  = 1;   
    AFESCKEN = 1;
    ARAM_SEL = 0;  //0: afe控制aram 
	
    
#if 0 //Close Clk
//    AFEACKEN = 0;    
//    AFECKEN  = 0;  
    AFESCKEN = 0;   //FPGA版本 关闭无效
#endif
}

/*******************************************************************************
*   Name: Afe_Order_Init
*  Brief: 重排序表初始化
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Order_Init(void)
{
#if 1
    SINT16 i;
    UINT16 len;
    UINT16 XRAM Buf[CH_ORDER_MAX];

    //左半屏Order
    for(i = 0; i<CH_ORDER_MAX; i++)
    {
       g_ucOrderBuf[i] = i; //0- 287/323
    }

    //右半屏Order
    for(i = 0; i <CH_ORDER_MAX; i++)
    {
       g_ucOrderBuf[i+CH_ORDER_MAX] = ((CH_ORDER_MAX-1)-i); // 287/323 -0
    }
    
    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);

    //按照Order Ram字节配置
    len = CH_ORDER_MAX;
    for (i = 0; i < len; i++)
    {
       //Buf[i] = ((i*2+1+3)<<8)+i*2+3;                      //  正序   3开始--290结束 
       //Buf[i] = (g_ucOrderBuf[i*2+1]<<8)+g_ucOrderBuf[i*2];  //  值: 04_03;06_05...226_225...290_289 
       Buf[i] = g_ucOrderBuf[i];  //  值: 04_03;06_05...226_225...290_289        
    }
    Drv_XsiWrite(pXSI0Regs,256,Buf,len,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256,Buf,len,AFE_REG);        //左右同序

    
    len = CH_ORDER_MAX;
    for (i = 0; i < len; i++)
    {
       //Buf[i] = (111-i)*2+3 + (((111-i)*2+1+3)<<8);                                                     // 反序   290开始--3结束 
       //Buf[i] = (g_ucOrderBuf[((CH_ORDER_MAX/2-1)-i)*2 +1]<<8)+(g_ucOrderBuf[((CH_ORDER_MAX/2-1)-i)*2]);  //值:290_289.. 226_225; 224_223...04_03
       Buf[i] = g_ucOrderBuf[(CH_ORDER_MAX-1)-i];            //值:290_289.. 226_225; 224_223...04_03
    }
//    Drv_XsiWrite(pXSI0Regs,256,Buf,len,AFE_REG);       //左反序
//    Drv_XsiWrite(pXSI1Regs,256,Buf,len,AFE_REG);     //左右反序

#else // 跳序测试order表 324-9
    SINT16 i;
    UINT16 Order = 0;
    UINT16 len;
    UINT16 XRAM Buf[CH_ORDER_MAX];

    //半屏Order
    for(i = 0; i<CH_ORDER_MAX; i++)
    {
       g_ucOrderBuf[i] = i; //0- 323
    }

    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);

    //按照Order Ram字节配置
    len = CH_ORDER_MAX;
    for (i = 0; i < len; i++)
    {
#if 1    
       if((Order%36)== 0) //通道1,37,73,109,145,181,217,253,289，对应order号减1，即通道1表示order0
       {
           Order++; 
           len--;
       }
#endif
       Buf[i] = g_ucOrderBuf[Order];  //  
       Order++;
    }
    Drv_XsiWrite(pXSI0Regs,256,Buf,len,AFE_REG);
    Drv_XsiWrite(pXSI1Regs,256,Buf,len,AFE_REG);        //左右同序
#endif


#if 0 // 读取重排序表是否配置正确
    for (i = 0; i < len; i++)
    {
       Buf[i] = 0;
    }
    Drv_XsiRead(pXSI0Regs,256,Buf,len,AFE_REG);
    for (i = 0; i < len; i++)
    {
        DBG_FLOW("\nRegL[%02d] =  %04d",i,Buf[i]);
    }
    
    Drv_XsiRead(pXSI1Regs,256,Buf,len,AFE_REG);
    for (i = 0; i < len; i++)
    {
        DBG_FLOW("\nRegR[%02d] =  %04d",i,Buf[i]);
    }
    while(1);
#endif
}



/*******************************************************************************
*   Name: Afe_Table_Init
*  Brief: Afe Tab Ram初始化，通道使能打开，CB初始值配置为0。
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Table_Init()
{
    UINT8 i;
    UINT16 XRAM aus_tabbuf[TAB_RAM_LEN];

    memset(aus_tabbuf, 0, TAB_RAM_LEN*2);

    /* set Ch enable, set CB 0*/ 
    for(i = TAB_TP_KEY_CB_START_ADDR ;i<TAB_RAM_LEN;i++)
    {
        aus_tabbuf[i] = 0x4040;   // [6]:EN  [5:0]:CB
    }
#if TEMP_CLOSE_KEY
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0;      //4个按键:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0;
#else
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 0] = 0x0100;      //4个按键:  Key0-3  [8]:EN [7:0]:CB
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 1] = 0x0100;      
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 2] = 0x0100;
    aus_tabbuf[TAB_TP_KEY_CB_START_ADDR + 3] = 0x0100;
#endif    

    /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    for (i = 0;i < 4;i++)
    { 
        Drv_XsiWrite(pXSI0Regs,256+i*TAB_RAM_LEN,aus_tabbuf,TAB_RAM_LEN,AFE_REG);
        Drv_XsiWrite(pXSI1Regs,256+i*TAB_RAM_LEN,aus_tabbuf,TAB_RAM_LEN,AFE_REG);
    }
}

/*******************************************************************************
*   Name: Afe_Config_Init
*  Brief: Afe配置参数初始化
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Config_Init(void)
{
    UINT16 ReadXSI0 = 0;
    UINT16 ReadXSI1 = 0;

//    Drv_XsiWriteReg(pXSI0Regs, 0, 0x01, AFE_REG);
//    Drv_XsiWriteReg(pXSI1Regs, 0, 0x01, AFE_REG);

//    ReadXSI0 = Drv_XsiReadReg(pXSI0Regs,0x00,AFE_REG);
//    ReadXSI1 = Drv_XsiReadReg(pXSI1Regs,0x00,AFE_REG);
//    DBG_FLOW("\nReg%d 0x%x  0x%x ",0x00,ReadXSI0,ReadXSI1);

    Drv_XsiWriteReg(pXSI0Regs, Addr_PANEL_MODE_CFG0, rPANEL_MODE_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_PANEL_MODE_CFG0, rPANEL_MODE_CFG0, AFE_REG);
        
    Drv_XsiWriteReg(pXSI0Regs, Addr_PANEL_MODE_CFG1, rPANEL_MODE_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_PANEL_MODE_CFG1, rPANEL_MODE_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_PANEL_MODE_CFG2, rPANEL_MODE_CFG2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_PANEL_MODE_CFG2, rPANEL_MODE_CFG2, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, rAFE_SYS_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, rAFE_SYS_CFG0, AFE_REG);
   
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG1, rAFE_SYS_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG1, rAFE_SYS_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SCAN_CFG0, rAFE_SCAN_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SCAN_CFG0, rAFE_SCAN_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SCAN_CFG1, rAFE_SCAN_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SCAN_CFG1, rAFE_SCAN_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_DUMMY_SCAN_CFG, rAFE_DUMMY_SCAN_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_DUMMY_SCAN_CFG, rAFE_DUMMY_SCAN_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_BASE_TRACK_CFG, rAFE_BASE_TRACK_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_BASE_TRACK_CFG, rAFE_BASE_TRACK_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ACC_OFFSET, rACC_OFFSET, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ACC_OFFSET, rACC_OFFSET, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_TP_MONITOR_THRESHOLD, rTP_MONITOR_THRESHOLD, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TP_MONITOR_THRESHOLD, rTP_MONITOR_THRESHOLD, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_KEY_MONITOR_THRESHOLD, rKEY_MONITOR_THRESHOLD, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_KEY_MONITOR_THRESHOLD, rKEY_MONITOR_THRESHOLD, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_K1_CFG0, rAFE_ANA_K1_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_K1_CFG0, rAFE_ANA_K1_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_K2_CFG1, rAFE_ANA_K2_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_K2_CFG1, rAFE_ANA_K2_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_CA_CFG0, rAFE_ANA_CA_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_CA_CFG0, rAFE_ANA_CA_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_CA_CFG1, rAFE_ANA_CA_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_CA_CFG1, rAFE_ANA_CA_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_CA_CFG2, rAFE_ANA_CA_CFG2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_CA_CFG2, rAFE_ANA_CA_CFG2, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_P1_P2_CFG0, rAFE_ANA_P1_P2_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_P1_P2_CFG0, rAFE_ANA_P1_P2_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_P1_P2_CFG1, rAFE_ANA_P1_P2_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_P1_P2_CFG1, rAFE_ANA_P1_P2_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_P1_P2_CFG2, rAFE_ANA_P1_P2_CFG2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_P1_P2_CFG2, rAFE_ANA_P1_P2_CFG2, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_P1_P2_CFG3, rAFE_ANA_P1_P2_CFG3, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_P1_P2_CFG3, rAFE_ANA_P1_P2_CFG3, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_P1_P2_CFG4, rAFE_ANA_P1_P2_CFG4, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_P1_P2_CFG4, rAFE_ANA_P1_P2_CFG4, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_P1_P2_CFG5, rAFE_ANA_P1_P2_CFG5, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_P1_P2_CFG5, rAFE_ANA_P1_P2_CFG5, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_P1_P2_DLY_CFG0, rAFE_P1_P2_DLY_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_P1_P2_DLY_CFG0, rAFE_P1_P2_DLY_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_P1_P2_DLY_CFG1, rAFE_P1_P2_DLY_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_P1_P2_DLY_CFG1, rAFE_P1_P2_DLY_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_SH_CFG0, rAFE_ANA_SH_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_SH_CFG0, rAFE_ANA_SH_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_SH_CFG1, rAFE_ANA_SH_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_SH_CFG1, rAFE_ANA_SH_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_SH_CFG2, rAFE_ANA_SH_CFG2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_SH_CFG2, rAFE_ANA_SH_CFG2, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_SH_CFG3, rAFE_ANA_SH_CFG3, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_SH_CFG3, rAFE_ANA_SH_CFG3, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_SH_CFG4, rAFE_ANA_SH_CFG4, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_SH_CFG4, rAFE_ANA_SH_CFG4, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_SH_CFG5, rAFE_ANA_SH_CFG5, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_SH_CFG5, rAFE_ANA_SH_CFG5, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_SH_CFG6, rAFE_ANA_SH_CFG6, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_SH_CFG6, rAFE_ANA_SH_CFG6, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_ADC_CFG0, rAFE_ANA_ADC_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_ADC_CFG0, rAFE_ANA_ADC_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_ADC_CFG1, rAFE_ANA_ADC_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_ADC_CFG1, rAFE_ANA_ADC_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_ADC_CFG2, rAFE_ANA_ADC_CFG2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_ADC_CFG2, rAFE_ANA_ADC_CFG2, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_ANA_ADC_CFG3, rAFE_ANA_ADC_CFG3, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_ANA_ADC_CFG3, rAFE_ANA_ADC_CFG3, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_GIPH_P1_P2_CFG, rAFE_GIPH_P1_P2_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_GIPH_P1_P2_CFG, rAFE_GIPH_P1_P2_CFG, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_GIPL_P1_P2_CFG, rAFE_GIPL_P1_P2_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_GIPL_P1_P2_CFG, rAFE_GIPL_P1_P2_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SD_VOM_OPT_P1_P2_CFG, rAFE_SD_VOM_OPT_P1_P2_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SD_VOM_OPT_P1_P2_CFG, rAFE_SD_VOM_OPT_P1_P2_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, rAFE_SX_P1_P2_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, rAFE_SX_P1_P2_CFG, AFE_REG);

//41
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_MOUT_GIPH_CFG, rAFE_MOUT_GIPH_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_MOUT_GIPH_CFG, rAFE_MOUT_GIPH_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_MOUT_GIPL_CFG, rAFE_MOUT_GIPL_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_MOUT_GIPL_CFG, rAFE_MOUT_GIPL_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_GOUT_GIPH_CFG, rAFE_GOUT_GIPH_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_GOUT_GIPH_CFG, rAFE_GOUT_GIPH_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_GOUT_GIPL_CFG, rAFE_GOUT_GIPL_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_GOUT_GIPL_CFG, rAFE_GOUT_GIPL_CFG, AFE_REG);
//
    

    Drv_XsiWriteReg(pXSI0Regs, Addr_ALL_GATE_ON_L_CFG, rALL_GATE_ON_L_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ALL_GATE_ON_L_CFG, rALL_GATE_ON_L_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ALL_GATE_OFF_L_CFG, rALL_GATE_OFF_L_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ALL_GATE_OFF_L_CFG, rALL_GATE_OFF_L_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ALL_GATE_STOP_L_CFG, rALL_GATE_STOP_L_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ALL_GATE_STOP_L_CFG, rALL_GATE_STOP_L_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ALL_GATE_H_CFG, rALL_GATE_H_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ALL_GATE_H_CFG, rALL_GATE_H_CFG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_RPT_RAWDATA_NUM, rRPT_RAWDATA_NUM, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_RPT_RAWDATA_NUM, rRPT_RAWDATA_NUM, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_CB_ADJUST_THLD_TP, rCB_ADJUST_THLD_TP, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_CB_ADJUST_THLD_TP, rCB_ADJUST_THLD_TP, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_TEST_MODE_FLAG, rTEST_MODE_FLAG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TEST_MODE_FLAG, rTEST_MODE_FLAG, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_PRESCAN_TIME, rPRESCAN_TIME, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_PRESCAN_TIME, rPRESCAN_TIME, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_DISCHARGE_TIME, rDISCHARGE_TIME, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_DISCHARGE_TIME, rDISCHARGE_TIME, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, rANA_STATIC_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, rANA_STATIC_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG1, rANA_STATIC_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG1, rANA_STATIC_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG2, rANA_STATIC_CFG2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG2, rANA_STATIC_CFG2, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG3, rANA_STATIC_CFG3, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG3, rANA_STATIC_CFG3, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_TEST_P0_CFG0, rTEST_P0_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TEST_P0_CFG0, rTEST_P0_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_TEST_P0_CFG1, rTEST_P0_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TEST_P0_CFG1, rTEST_P0_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_TEST_P0_CFG2, rTEST_P0_CFG2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TEST_P0_CFG2, rTEST_P0_CFG2, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_TEST_P1_CFG0, rTEST_P1_CFG0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TEST_P1_CFG0, rTEST_P1_CFG0, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_TEST_P1_CFG1, rTEST_P1_CFG1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TEST_P1_CFG1, rTEST_P1_CFG1, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_TEST_P1_CFG2, rTEST_P1_CFG2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_TEST_P1_CFG2, rTEST_P1_CFG2, AFE_REG);
    
//  MCAP KEY
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_SCAN_CFG, rMCAP_SCAN_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_SCAN_CFG, rMCAP_SCAN_CFG, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_SCANSR, rMCAP_SCANSR, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_SCANSR, rMCAP_SCANSR, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_SUM_NUM, DAT_MCAP_LPFIR_SUM_NUM, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_SUM_NUM, DAT_MCAP_LPFIR_SUM_NUM, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_RAWSHIFTCAF, rRAWSHIFTCAF, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_RAWSHIFTCAF, rRAWSHIFTCAF, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_RAWDATA_OFFSET_L, rRAWDATA_OFFSET_L, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_RAWDATA_OFFSET_L, rRAWDATA_OFFSET_L, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_ADC_CFG, rADC_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ADC_CFG, rADC_CFG, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_ADC_DATA0, rADC_DATA0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ADC_DATA0, rADC_DATA0, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_INIT_SAMPL_CFG, rMCAP_INIT_SAMPL_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_INIT_SAMPL_CFG, rMCAP_INIT_SAMPL_CFG, AFE_REG);
        
    Drv_XsiWriteReg(pXSI0Regs, Addr_OVERFLOW_THR, rOVERFLOW_THR, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_OVERFLOW_THR, rOVERFLOW_THR, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_UNDERFLOW_THR, rUNDERFLOW_THR, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_UNDERFLOW_THR, rUNDERFLOW_THR, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_OVERFLOW_UPBOUND, rOVERFLOW_UPBOUND, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_OVERFLOW_UPBOUND, rOVERFLOW_UPBOUND, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_OVER_POINT_FRAME, rOVER_POINT_FRAME, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_OVER_POINT_FRAME, rOVER_POINT_FRAME, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_NORMAL_SIGNAL_UPTHR, rNORMAL_SIGNAL_UPTHR, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_NORMAL_SIGNAL_UPTHR, rNORMAL_SIGNAL_UPTHR, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_NORMAL_SIGNAL_DWTHR, rNORMAL_SIGNAL_DWTHR, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_NORMAL_SIGNAL_DWTHR, rNORMAL_SIGNAL_DWTHR, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_OVERFLOW_CLR_FRAMENUM, rOVERFLOW_CLR_FRAMENUM, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_OVERFLOW_CLR_FRAMENUM, rOVERFLOW_CLR_FRAMENUM, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_CFG, rMCAP_LPFIR_CFG, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_CFG, rMCAP_LPFIR_CFG, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_COF0, rMCAP_LPFIR_COF0, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_COF0, rMCAP_LPFIR_COF0, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_COF1, rMCAP_LPFIR_COF1, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_COF1, rMCAP_LPFIR_COF1, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_COF2, rMCAP_LPFIR_COF2, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_COF2, rMCAP_LPFIR_COF2, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_COF3, rMCAP_LPFIR_COF3, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_COF3, rMCAP_LPFIR_COF3, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_COF4, rMCAP_LPFIR_COF4, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_COF4, rMCAP_LPFIR_COF4, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_COF5, rMCAP_LPFIR_COF5, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_COF5, rMCAP_LPFIR_COF5, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_COF6, rMCAP_LPFIR_COF6, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_COF6, rMCAP_LPFIR_COF6, AFE_REG);
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_MCAP_LPFIR_COF7, rMCAP_LPFIR_COF7, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_MCAP_LPFIR_COF7, rMCAP_LPFIR_COF7, AFE_REG);

    Drv_XsiWriteReg(pXSI0Regs, Addr_CB_ADJUST_THLD_KEY, rCB_ADJUST_THLD_KEY, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_CB_ADJUST_THLD_KEY, rCB_ADJUST_THLD_KEY, AFE_REG);	

#if  TEST_GROUP_SEL1 
    // Default:  MUX1: G1 G9  MUX2: G2  G8  MUX3: G3 G7  MUX4: G4 G6  MUX5: X G5
    // Config:   MUX1: G1 G5  MUX2: G2  G6  MUX3: G3 G7  MUX4: G4 G8  MUX5: X G9
    DrvAFEGroupSelReg1(0,0,1,1,2,2);
    DrvAFEGroupSelReg2(3,3,4,4);
#endif
#if  TEST_GROUP_SEL2 
    // Default:  MUX1: G1 G9  MUX2: G2  G8  MUX3: G3 G7  MUX4: G4 G6  MUX5: X G5
    // Config:   MUX1: G4 G5  MUX2: G3  G6  MUX3: G2 G7  MUX4: G1 G8  MUX5: X G9
    DrvAFEGroupSelReg1(3,0,2,1,1,2);
    DrvAFEGroupSelReg2(0,3,4,4);
#endif

#ifdef COF_MODE
    DrvAfeEnCOF();
    DrvAfeEnRawdataNum(CH_ORDER_MAX); //左右各324
//    DrvAfeEnRawdataNum(10);     // test   
//    DrvAfeEnRawdataNum(300);     // test  
//    DrvAfeEnRawdataNum(CH_ORDER_MAX-9);     // test order  跳序   
#endif

#if  IS_4_MUX_MODE
    DrvAfeEn4mux();
    // Config:   MUX1: G1 G5  MUX2: G2  G6  MUX3: G3 G7  MUX4: G4 G8  MUX5: X G9
    DrvAFEGroupSelReg1(0,0,1,1,2,2);
    DrvAFEGroupSelReg2(3,3,4,4); // G5配置无效
#endif
    
}

void Afe_Tab_Config(void)
{
    XSICKEN = 1;
    
    Afe_Config_Tab0();
    Afe_Config_Tab1();
    Afe_Config_Tab2();
    Afe_Config_Tab3();
  
}

/*******************************************************************************
*   Name: Afe_Init
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Init(void)
{
    Afe_Order_Init();
    
    Afe_Table_Init();
    
    Afe_Config_Init();

    Asm_Config_Init();

    Afe_Tab_Config();
  
    DBG_FLOW("\nAfe Init is OK");

}

/*******************************************************************************
*   Name: Afe_Free_Run
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Free_Run(void)
{
    static XRAM getBaseCount = 0; 
    static XRAM FristStart = 1;
    UINT16 XRAM usConfigValue;
    UINT8 XRAM ucTPFramePerScan = 0;

    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

#if TEMP_CLOSE_KEY
    usConfigValue = 0x101;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG); // close key enable
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG);
#endif
    

    /* 加载Tab表*/
#ifdef TEST_MUL_SCAN
     ucTPFramePerScan = 3;   // 连续4次扫描
//    ucTPFramePerScan = 2;   // 连续3次扫描
//    ucTPFramePerScan = 1;   // 连续2次扫描
    DrvLoadTabMultiple(0,5,0,0,ucTPFramePerScan,0);    // 表0  启动后，每次扫描多帧  1=2次
#else
    DrvLoadTabSingle(0,0);            // 表0  启动后，每次扫描1帧
//    DrvLoadTabSingle(1,0);            // 表1  启动后，每次扫描1帧
//    DrvLoadTabSingle(2,0);            // 表2  启动后，每次扫描1帧
//    DrvLoadTabSingle(3,0);            // 表3  启动后，每次扫描1帧
#endif
    
    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0); 
    DrvAsmInterDisable0(BIT_LCD_VSTART_EN0);   // Close Vstart interrupt
   
    g_ucAramReadyFlag = 0;

    while(ucAfeRunMode == TP_FREE_RUN_MODE) // 表示LCD灭屏
    {
        AppPanelParamUpdate();
        
        if(FristStart == 1)
        {
#ifdef TEST_MUL_SCAN    
            if((g_ucIntCount%(ucTPFramePerScan+1))==0)    
            {
                DrvAsmScanStart();
            }
            //FristStart = 0;
#else 

#if TEST_ASM_ARAM_READY_WAKEUP
            ASM_MON_WKEN = 1;
            DrvAsmWakeEnable0(BIT_LCD_ARAM_RDY_WAKE_EN0);       //8
            DBG_FLOW("\nFreeRun ARAM_RDY Standby in------");
            DelayMs(100); // For Print
            EA = 0;
#endif        
            DrvAsmScanStart();
#if TEST_ASM_ARAM_READY_WAKEUP
            DrvSysPowerStandby();
            EA = 1;
#endif 
#endif  
            //DrvAfeSofeReset();
            //DrvAsmScanStart();
        }

        while(!g_ucAramReadyFlag);
        g_ucAramReadyFlag = 0;
        DBG_FLOW("\n=======Afe_Free_Run====== :%d  Sta:0x%x",g_ucIntCount,g_usAsmIntSta);
        DBG_FLOW("\nReg4 0x%x ",DebugReadAFEOneReg(4));

        //当前扫描的TP帧号
        //DBG_FLOW("\n9usAsmScanSta0: %04x",(pAsmRegs->usAsmScanSta0>>BIT_CUR_TP_FRAME_ID_STA));          // 09  RO
        //AppGetAsmState();

        DrvGetRptRamRawBase();

        DrvGetRawdata(); 

        DrvInitAram();
        
#ifdef TEST_MUL_SCAN  // 多次扫描，第2次扫描在AramReady中断后启动，这时AFE会操作report ram，mcu不适合操作report ram
#else
        DrvInitRptRam();
#endif

        DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据

        //AppGetAsmState();
        
        getBaseCount++;
        if(getBaseCount == 20)
        {
            DrvGetBase();
        }

        //DrvGetDiffdata();
        
        //DelayMs(5);   

        g_RegHead.bits.ucDataReadToggle = 0;   
    }
}

/*******************************************************************************
*   Name: Afe_Free_Run
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Free_Run_Monitor(void)
{
	UINT16 XRAM usConfigValue;
	static UINT16 XRAM usScanCount = 0;
	static UINT8 XRAM ucConfigOne = 1;

	usConfigValue = 0xFF;
	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
	
#if TEMP_CLOSE_KEY
	usConfigValue = 0x101;
	Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG); // close key enable
	Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG);
#endif    
	
	DrvAsmMonitoModeInit(); 
	DBG_FLOW("\nDrvAsmMonitoModeInit"); 
	
	/* 加载Tab表*/
	DrvLoadTabSingle(2,0);				  //表2 用于Monitor模式
 
	DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
	DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);

	//使能触摸检测中断
	DrvAsmInterClear0(BIT_LCD_TCH_DET_CLR0);
//	  DrvAsmInterEnable0(BIT_LCD_TCH_DET_EN0);
		 
	while(ucAfeRunMode == TP_FREE_RUN_MODE) // 表示LCD灭屏
	{
		g_usAsmIntFlag0 = 0;
		g_usAsmIntFlag1 = 0;
		
		g_ucFrameEndFlag = 0;
			  
#if TEST_ASM_FRAME_END_WAKEUP
		ASM_MON_WKEN = 1;
		DrvAsmWakeEnable0(BIT_LCD_FRAME_END_WAKE_EN0);		 //7
		DBG_FLOW("\nFreeRun FRAME_END Standby in------");
		DelayMs(100); // For Print
		EA = 0;
		DrvAsmScanStart(); 
		DrvSysPowerStandby();
		EA = 1;
#else
		DrvAsmScanStart(); 
#endif

	  
//		  DBG_FLOW("\nMonitor---StartScan:%d",g_ucFrameEndFlag);		   
		while(!g_ucFrameEndFlag);
		g_ucFrameEndFlag = 0;
//		  DBG_FLOW("\nAsm int: 0x%x 0x%x",g_usAsmIntFlag0,g_usAsmIntFlag1);
		
		DBG_FLOW("\nReg11 0x%x ",DebugReadAFEOneReg(11));
		DBG_FLOW("\nReg12 0x%x ",DebugReadAFEOneReg(12));
		DBG_FLOW("\nFreeRun Montor");		
		
		DrvGetRptRamRawBase(); // Monitor模式不上报数据到ARAM,通过RptRam上报。
#if TEST_ASM_FRAME_END_WAKEUP
		DBG_FLOW("\nFreeRun---------ucWake up");	   
#endif
		if(ucConfigOne == 1)
		{
			ucConfigOne = 0;
			//使能触摸检测中断
			DrvAsmInterClear0(BIT_LCD_TCH_DET_CLR0); //清除 DET INT
			DrvAsmInterEnable0(BIT_LCD_TCH_DET_EN0);
		}

		//DrvGetTabRam();
		
		DelayMs(50);

		g_RegHead.bits.ucDataReadToggle = 0;   
	}
}


/*******************************************************************************
*   Name: Afe_Free_Run_RTC_Monitor
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Free_Run_RTC_Monitor(void)
{
    UINT16 XRAM usConfigValue;
    UINT16 XRAM ucData;
    UINT8 XRAM usStartFlag = 1;

	ASM_32K_EN = 1;

#if TEST_MCAP_HWMON	
	//配置rf_sel
	usConfigValue = Drv_XsiReadReg(pXSIREG,Addr_ANA_STATIC_CFG0,AFE_REG);
	usConfigValue &= 0x87FF;

	usConfigValue |= (0x01<<13) +  (0x01<<11);						//写key的rf
	Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
	Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
	
	//Afe_Change_Tab3(2,4,13);   //hw mon,扫描方式5
	Afe_Change_Tab3(2,7,13);   //hw mon,扫描方式8	

	/*使能mcap,更新tab0以及afe reg相关参数*/
	DrvMcapModeInit(1,3);	
#else
	Afe_Change_Tab3(1,4,1);   //HW Monitor,扫描方式5
	//Afe_Change_Tab3(1,7,1);   //HW Monitor,扫描方式8	
#endif

	SEL_32K_SRC = 0;
    Drv_Rtc_Init(0);//auto_mode

#if 1//PWR_EN
	ANACON8 = 0xFF;
	ANACON9 = 0xFF;
	DrvAsmSetPwrOn();
#endif

    DBG_FLOW("\nRTC MONITOR");
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);//sx全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);//sx全驱

	/*改变tab表中的触摸阈值*/
    DrvSetTabMonThr(0xfff,10,3);

	/*HW MON配置*/    
    DrvAsmRtcMonitoModeInit();
	//DelayMs(1000);	

    ucData = Drv_XsiReadReg(pXSI0Regs, Addr_AFE_SYS_CFG0, AFE_REG);
    DBG_FLOW("\nXSI0 AfeReg4:%04x",ucData);

    ucData = Drv_XsiReadReg(pXSI1Regs, Addr_AFE_SYS_CFG0, AFE_REG);
    DBG_FLOW("\nXSI1 AfeReg4:%04x",ucData);

    P0_4 = 0;
    DelayMs(10);
    P0_4 = 1;
    DelayMs(10);
    P0_4 = 0;
    DelayMs(10);    
    
    /*不能用*/
    RTC_CNT_WKEN = 0;
                     
    DBG_FLOW("\n\nrtc monitor");
         
    DelayMs(100);
    
    DrvAsmClrInt();
     
    g_ucFrameEndFlag = 0;
    g_usAsmIntFlag0 = 0;
    g_usAsmIntFlag1 = 0;
    g_ucTimeOutFlag = 0;

#if PWR_EN
    DrvAsmSetHwMonPwrEn(1);                                //设置在硬件monitor下，控制上下电时序。1:控制;0:不控制
#else
    DrvAsmSetHwMonPwrEn(0);                                //设置在硬件monitor下，控制上下电时序。1:控制;0:不控制
#endif

	DelayMs(100);

    //while(ucAfeRunMode == TP_FREE_RUN_MODE) // 表示LCD灭屏
    //while(1)
    {
            
        RTC_CNT_WKEN = 0;        //RTC int0唤       
        ASM_MON_WKEN = 1;        //scan mon int0唤醒

        if(usStartFlag)
        {
            //刷base以后才能配置进入hw mon
            DrvAsmSetRtcMonitorMode(TRUE);                          //1:开启rtc monitor模式        
            P0_4 = 1;
            DelayMs(1);            
            P0_4 = 0;            
            RTC_WP = 1;
            RTC_START = 1;
            usStartFlag = 0;
        }
#if 1  

        AFEACKEN = 1; //该bit不能关闭,关闭后ASM不能工作
        AFECKEN  = 0; //可以关闭,但是实际上没必要手动关,进入stop或者standby,硬件会自动关闭.   
        AFESCKEN = 0; //可以关闭,但是实际上没必要手动关,进入stop或者standby,硬件会自动关闭.         
      
        DrvSysPowerStop();

        //DrvSysPowerStandby();
        DrvAsmSetRtcMonitorMode(FALSE);        
        AFEACKEN = 1;
        AFECKEN  = 1;   
        AFESCKEN = 1;

        P0_4 = 1;
        while(RTC_START_STA == 0);
        RTC_WP = 1;
        RTC_CLR = 1;

        DBG_FLOW("\nexit stop");

#endif
        while((!g_ucTimeOutFlag)&&(!g_ucTchDetFlag));
        //DrvAsmSetRtcMonitorMode(FALSE); 
        DelayMs(10); 

        DBG_FLOW("\nTHR:%04x",Drv_XsiReadReg(pXSI0Regs,0x0b,AFE_REG));
        
        DBG_FLOW("\nwake up-------------");
        DBG_FLOW("\nWake up intflag: 0x%x 0x%x",g_usAsmIntFlag0,g_usAsmIntFlag1);
        DBG_FLOW("\niwksta:%02x",g_ucState0);
        
        DelayMs(5);
        if ((g_usAsmIntFlag0 &0x08) == 0x08)
        {
            DBG_FLOW("\n*************Mon Det %02x",g_usAsmIntFlag0);
            while(1);
            DelayMs(1000);
            g_usAsmIntFlag0 = 0x00;            
        }

        if(g_ucTimeOutFlag)
        {
            DBG_FLOW("\n*************Mon Timeout %02x",g_usAsmIntFlag1);
            DelayMs(1000);
        }

        g_ucTimeOutFlag = 0;
        g_ucTchDetFlag = 0;
        DBG_FLOW("\nRTC wake\n");
        
        DrvGetRptRamRawBase();

        g_ucFrameEndFlag = 0;
        g_usAsmIntFlag0 = 0;
        g_usAsmIntFlag1 = 0;

        DelayMs(1000);
        while(1);
        //g_RegHead.bits.ucDataReadToggle = 0;
    }
}

/*******************************************************************************
*   Name: Afe_Free_Run_H_CB
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Free_Run_H_CB(void)
{
    UINT8  XRAM ausTabId = 3;

#if TEST_MCAP_CB
	UINT16 usConfigValue;

	//配置rf_sel
	usConfigValue = Drv_XsiReadReg(pXSIREG,Addr_ANA_STATIC_CFG0,AFE_REG);
	usConfigValue &= 0x87FF;

	usConfigValue |= (0x01<<13) +  (0x01<<11);						//写key的rf
	Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
	Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);

    Afe_Change_Tab3(2,4,18);   //CB,扫描方式5
    //Afe_Change_Tab3(2,7,18);   //CB,扫描方式8

    /*使能mcap,更新tab0以及afe reg相关参数*/
    DrvMcapModeInit(1,3);

#else
    //Afe_Change_Tab3(0,4,2);   //CB,扫描方式5
    Afe_Change_Tab3(0,7,2);   //CB,扫描方式8
#endif
    
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, 0xFF, AFE_REG);//sx p1/p2 配成全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, 0xFF, AFE_REG);//sx p1/p2 配成全驱 

  
    g_ucFrameEndFlag = FALSE;
    g_ucAramReadyFlag = 0;
    g_usAsmIntFlag0 = 0;

#if 1

    /*设置CB校正的方向*/
    DrvSetCbDir(1,1);  //0:顺时针 若raw<th cb变大;1:逆时针 若rawdata<th cb变小

    /*CB校正模式*/ 
    DrvAsmSetCBAdjustMode(1);

    /*设置硬件CB校正的目标值*/
    DrvAfeSetHCBTarget(10000,10000);

    /* 加载Tab表*/
    DrvLoadTabCB(3,AFE_FREERUN_MODE);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);//开启AramReady中断使能
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);//开启Frame end中断使能    
    DelayMs(20);

//while(1)
{
    /*启动扫描*/
    DrvAsmScanStart();
    
    while(g_ucAramReadyFlag == 0);//CB校正模式，硬件数到8帧TP帧结束时才会发Aram Ready中断，这时候才表示CB校正结束

    g_ucAramReadyFlag = 0;
    
    DelayMs(10000);
#if 1 //从ARAM中读出CB 
    DrvGetAramCb();
#endif
    DrvAsmAramAvail(); 
    
#if 0 //从TAB表中读出CB
    DelayMs(2000);    
    DrvGetTabRamCb();
    DelayMs(2000);
#endif

#if 0 //从RptRam中后去Rawdata
    DBG_FLOW("\nRead Rawdata from RptRam");
    DrvGetRptRamRawBase();
#endif    
}

#endif

#if 0//AFE阶段中，由于CB是由外部的CB决定的，CB的大小对RAWDATA实际上没影响，因此不再进行一次扫描，看RAWDATA的值是否接近设定值,在芯片验证阶段。则有影响

    DelayMs(2000);

    DBG_FLOW("\nAFE RUN");
    
    g_ucFrameEndFlag = FALSE;
    g_ucAramReadyFlag = 0;
    g_usAsmIntFlag0 = 0;
    
    /*正常工作模式*/ 
    DrvAsmSetCBAdjustMode(0);    

    /*单次扫描*/
    DrvLoadTabSingle(0,0);
    
    DelayMs(20);

    DBG_FLOW("\n\n");
    /*启动扫描*/
    
    while(1)
    {
        DrvAsmScanStart();
        while((g_ucAramReadyFlag == 0)||(g_ucFrameEndFlag == 0));

        g_ucAramReadyFlag = 0;
        g_ucFrameEndFlag = 0;
        
        DrvGetAramRawData();
        
        DrvAsmAramAvail();
        
        DelayMs(2000);
    }
#endif

    DBG_FLOW("\nCB FINISH");
    HOLD;
}

/*******************************************************************************
*   Name: Mcap_Free_Run
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Mcap_Free_Run(void)
{
#if TEST_SAMP_INT
    UINT16 XRAM ucData,ucMax,ucInit;
#endif
    static XRAM getBaseCount = 0;
    static XRAM FristStart = 1;
    UINT16 XRAM usConfigValue;
    UINT8 XRAM ucTPFramePerScan = 0;
    UINT8 XRAM ucTabId = 3;
    UINT8 XRAM ucTestMode = 1;//0:测试模式;1:普通模式
    UINT8 XRAM ucScanNum = 13;
	UINT16 XRAM i,j;

    Afe_Change_Tab3(2,4,ucScanNum );   //MCAP,扫描方式5
    //Afe_Change_Tab3(2,7,ucScanNum );   //MCAP,扫描方式8
    
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

#if 1
    //配置rf_sel
    usConfigValue = Drv_XsiReadReg(pXSIREG,Addr_ANA_STATIC_CFG0,AFE_REG);
    usConfigValue &= 0x87FF;

    usConfigValue |= (0x01<<13) +  (0x01<<11);                      //写key的rf
    Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);

    DBG_FLOW("REG_36:%04x",usConfigValue);
#endif
   
    /*使能mcap,更新tab0以及afe reg相关参数*/
    DrvMcapModeInit(1,ucTabId);

    /* 加载Tab表*/
    DrvLoadTabSingle(ucTabId,0);            // 表3  启动后，每次扫描1帧
    
    DrvMcapSetTestMode(ucTestMode,0);          //0为开启测试模式,1为普通模式,选择输出key2
    //DrvAfeSetOneChannelTestMode(0,0,0);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);//开启AramReady中断使能
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);//开启FrameEnd中断使能

    g_ucAramReadyFlag = 0;

#if PWR_EN
    ANACON8 = 0xFF;
    ANACON9 = 0xFF;
    DrvAsmSetPwrOn();
#endif

#if TEST_SAMP_INT
    ucMax = 0;
    ucInit = 0;
    DrvMcapSetTestMode(1,1); 

    for(i = 0x0; i < ((g_pMcapPara->usK1 + g_pMcapPara->usK2)*2 - 29 - 2*3); i++)
    {
        g_pMcapPara->usSampl_Init = i;
        Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_INIT_SAMPL_CFG,g_pMcapPara->usSampl_Init,AFE_REG);
        Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_INIT_SAMPL_CFG,g_pMcapPara->usSampl_Init,AFE_REG);
        
        DrvAsmScanStart();
        while(!g_ucAramReadyFlag);
        g_ucAramReadyFlag = 0;
        
        ARAM_SEL = 1;
        ucData = ARAM_ADDR16(CH_ORDER_MAX*4);
        ARAM_SEL = 0;
        
        if(ucData > ucMax)
        {
            ucMax = ucData;
            ucInit = i;
        }

        DBG_FLOW("\nSamp_Init:%04x,Rawdata:%04x",i,ucData);
        DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据

        DelayMs(500);
    }

    Drv_XsiWriteReg(pXSI0Regs,Addr_MCAP_INIT_SAMPL_CFG,ucInit,AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs,Addr_MCAP_INIT_SAMPL_CFG,ucInit,AFE_REG);

    ucInit = Drv_XsiReadReg(pXSIREG,Addr_MCAP_INIT_SAMPL_CFG,AFE_REG);
    DBG_FLOW("\nwhen rawdata is max,samp_init is:%04x",ucInit);
    
    DrvMcapSetTestMode(ucTestMode,1);          //0为开启测试模式,1为普通模式,选择输出key2     
#endif

    while(ucAfeRunMode == TP_FREE_RUN_MODE) // 表示LCD灭屏
    //for(j = 0; j < 2000; j++)
    {
     
    #if 1
        ARAM_SEL = 1;
        for(i = 0; i < 0x500; i++)
        {
            *(UINT8 *)(0xA000 + i) = 0;//清除aram
        }
        ARAM_SEL = 0;
    #endif
    
        DrvAsmScanStart();
            
        while(!g_ucAramReadyFlag);
        g_ucAramReadyFlag = 0;
        DBG_FLOW("\nHave Aram Ready");

        DrvMcapReadSta(g_pMcapPara);
        if(g_pMcapPara->usErrFlg)
        {
            DBG_FLOW("\nMcap Scan Err:%01x",g_pMcapPara->usErrSta);
            DBG_FLOW("\n");
        }
        else
        {            
            if(ucTestMode == 0)
            {
                if(g_pMcapPara->usSampl_6)
                {
                    DrvGetAdcData(ucScanNum * 6);
                }
                else
                {
                    DrvGetAdcData(ucScanNum * 8);
                }
            }
            else
            {
				//DrvGetRptRamRawBase();            
                DrvGetAramRawData();
				
            }           
        }
        DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据

#if PWR_EN
        DrvAsmSetPwrOff();       
#endif        
        DelayMs(1);

    }    
}

/*******************************************************************************
*   Name: Afe_60Hz_Run
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_60Hz_Run(void)
{ 
    UINT16 XRAM usConfigValue;
    static XRAM FristStart = 1;
     
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG); // sx全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
    DrvAsmInterEnable0(BIT_LCD_BUSY_FALL_EN0);
    DrvAsmInterEnable0(BIT_LCD_VBLANK_EN0);
    DrvAsmInterEnable0(BIT_LCD_PANEL_CONFLICT_EN0);
    DrvAsmInterEnable0(BIT_LCD_SYNC_MISS_RISE_EN0);

//    DBG_FLOW("\npAsmRegs->usAsmIntEn0:0x%x",pAsmRegs->usAsmIntEn0);
    
//    DrvLoadTabMultiple(1,2,0,0,1,1);    // 60hz表1  启动扫描后，每次连续扫描2帧，第1次启动从1坑开始，第2次启动从2坑开始，
//    DrvLoadTabMultiple(1,1,0,0,1,1);    // 60hz表1  启动扫描后，每次连续扫描2帧，第1次启动从1坑开始，第2次启动从1坑开始，
     DrvLoadTabMultiple(1,1,1,1,3,1);    // 60hz表1  启动扫描后，每次连续扫描4帧，第1次启动从1坑开始，第2次启动从1坑开始，第4次启动从1坑开始，


     DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
                                      
    DrvAsmReq60hz_Big_LcdBusy(); //请求60hz
    
    g_ucAramReadyFlag = 0;

//    DrvAsmScanStart();

    // Vstart 中断里启动扫描
    while((DrvAsmGetSta()&LCD_RUN_STA)==1)    
    {     
        if((DrvAsmGetSta1()&LCD_BUSY_STA)==0)
        {
            AppPanelParamUpdate();
         
            g_ucAramReadyFlag = 0;

            while(g_ucAramReadyFlag==0);

            DBG_FLOW("\n=======60HZ=======:%d",g_ucIntCount);

            DrvAsmInterDisable0(BIT_LCD_VSTART_EN0);
            
            AppShowRawdata();

            DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
            DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
        }
        
        g_RegHead.bits.ucDataReadToggle = 0;
    }
}
/*******************************************************************************
*   Name: Afe_60Hz_H_Clb
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_60Hz_H_Clb(void)
{

#if TEST_MCAP_CB
	UINT16 usConfigValue;

	//配置rf_sel
	usConfigValue = Drv_XsiReadReg(pXSIREG,Addr_ANA_STATIC_CFG0,AFE_REG);
	usConfigValue &= 0x87FF;

	usConfigValue |= (0x01<<13) +  (0x01<<11);						//写key的rf
	Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
	Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
	
	Afe_Change_Tab3(2,CB_AFE_SCAN_MODE,18);   //CB,扫描方式

	/*使能mcap,更新tab0以及afe reg相关参数*/
	DrvMcapModeInit(1,3);	
#else
	Afe_Change_Tab3(0,CB_AFE_SCAN_MODE,1);	 //CB,扫描方式
#endif

    if(CB_AFE_SCAN_MODE == 4)//扫描方式5，大坑模式
    {
        DrvAsmReq60hz_Big_LcdBusy();
    }
    else
    {
        DrvAsmReq120hz_Small_LcdBusy();
    }

    
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, 0xFF, AFE_REG);//sx p1/p2 配成全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, 0xFF, AFE_REG);//sx p1/p2 配成全驱 

  
    g_ucFrameEndFlag = FALSE;
    g_ucAramReadyFlag = 0;
    g_usAsmIntFlag0 = 0;

    /*设置CB校正的方向*/
    DrvSetCbDir(0,0);  //0:顺时针 若raw<th cb变大;1:逆时针 若rawdata<th cb变小

    /*CB校正模式*/ 
    DrvAsmSetCBAdjustMode(1);

    /*设置硬件CB校正的目标值*/
    DrvAfeSetHCBTarget(0,0);

    /* 加载Tab表*/
    DrvLoadTabCB(3,AFE_60HZ_MODE);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);//开启AramReady中断使能
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);//开启Frame end中断使能 
    
    DelayMs(20);

//while(1)
{
    /*启动扫描*/
    DrvAsmScanStart();
    
    while(g_ucAramReadyFlag == 0);//CB校正模式，硬件数到8帧TP帧结束时才会发Aram Ready中断，这时候才表示CB校正结束

    g_ucAramReadyFlag = 0;
    
    DelayMs(10000);
#if 1 //从ARAM中读出CB 
    DrvGetAramCb();
#endif
    DrvAsmAramAvail(); 
    
#if 1 //从TAB表中读出CB
    DelayMs(2000);    
    DrvGetTabRamCb();
    DelayMs(2000);
#endif

#if 1 //从RptRam中后去Rawdata
    DBG_FLOW("\nRead Rawdata from RptRam");
    DrvGetRptRamRawBase();
#endif    
}



#if 0//AFE阶段中，由于CB是由外部的CB决定的，CB的大小对RAWDATA实际上没影响，因此不再进行一次扫描，看RAWDATA的值是否接近设定值,在芯片验证阶段。则有影响

    DelayMs(2000);

    DBG_FLOW("\nAFE RUN");
    
    g_ucFrameEndFlag = FALSE;
    g_ucAramReadyFlag = 0;
    g_usAsmIntFlag0 = 0;
    
    /*正常工作模式*/ 
    DrvAsmSetCBAdjustMode(0);    

    /*单次扫描*/
    DrvLoadTabSingle(0,0);
    
    DelayMs(20);

    DBG_FLOW("\n\n");
    /*启动扫描*/
    
    while(1)
    {
        DrvAsmScanStart();
        while((g_ucAramReadyFlag == 0)||(g_ucFrameEndFlag == 0));

        g_ucAramReadyFlag = 0;
        g_ucFrameEndFlag = 0;
        
        DrvGetAramRawData();
        
        DrvAsmAramAvail();
        
        DelayMs(2000);
    }
#endif

    DBG_FLOW("\nCB FINISH");
    HOLD;
}

/*******************************************************************************
*   Name: Mcap_60Hz_Run
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Mcap_60Hz_Run()
{
    static XRAM getBaseCount = 0;
    static XRAM FristStart = 1;
    UINT16 XRAM usConfigValue;
    UINT8 XRAM ucTPFramePerScan = 0;
    UINT8 ucTabId = 3;
    UINT8 ucTestMode = 1;//0:测试模式;1:普通模式
    UINT8 ucScanNum = 13;
    UINT8 ucScanMode = 0;//扫描方式5
    UINT16 i;

    if(ucScanMode == 4)//扫描方式5，大坑模式
    {
        DrvAsmReq60hz_Big_LcdBusy();
    }
    else
    {
        DrvAsmReq120hz_Small_LcdBusy();
    }    

    Afe_Change_Tab3(2,ucScanMode,ucScanNum );   //MCAP,扫描方式5
    
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

#if 1
    //配置rf_sel
    usConfigValue = Drv_XsiReadReg(pXSIREG,Addr_ANA_STATIC_CFG0,AFE_REG);
    usConfigValue &= 0x87FF;

    usConfigValue |= (0x01<<13) +  (0x01<<11);                      //写key的rf
    Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);

    DBG_FLOW("\nREG_36:%04x",usConfigValue);
#endif

    /*使能mcap,更新tab0以及afe reg相关参数*/
    DrvMcapModeInit(1,ucTabId);
    /* 加载Tab表*/
    DrvLoadTabSingle(ucTabId,1);            // 表3  启动后，每次扫描1帧
    
    DrvMcapSetTestMode(ucTestMode,0);          //0为开启测试模式,1为普通模式,选择输出key2
    
    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);//开启AramReady中断使能
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);//开启AramReady中断使能
    DrvAsmInterEnable0(BIT_LCD_PANEL_CONFLICT_EN0);//开启屏体冲突中断使能

    g_ucAramReadyFlag = 0;

#if PWR_EN
    ANACON8 = 0xFF;
    ANACON9 = 0xFF;
    DrvAsmSetPwrOn();
#endif


    while(ucAfeRunMode == TP_60HZ_RUN_MODE) 
    {
    
#if 1
        ARAM_SEL = 1;
        for(i = 0; i < 0x500; i++)
        {
            *(UINT8 *)(0xA000 + i) = 0;//清除aram
        }
        ARAM_SEL = 0;
#endif
    
        DrvAsmScanStart();
            
        while(!g_ucAramReadyFlag);
        g_ucAramReadyFlag = 0;
        DBG_FLOW("\nHave Aram Ready");

        DrvMcapReadSta(g_pMcapPara);
        if(g_pMcapPara->usErrFlg)
        {
            DBG_FLOW("\nMcap Scan Err:%01x",g_pMcapPara->usErrSta);
            DBG_FLOW("\n");
        }
        else
        {
#if 1            
            if(ucTestMode == 0)
            {
                if(g_pMcapPara->usSampl_6)
                {
                    DrvGetAdcData(ucScanNum * 6);
                }
                else
                {
                    DrvGetAdcData(ucScanNum * 8);
                }
            }
            else
            {
                DrvGetAramRawData();
            }
#endif            
        }
        
        DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据

#if 0//PWR_EN
        DrvAsmSetPwrOff();       
#endif        
        DelayMs(1000);
    }
    
}

/*******************************************************************************
*   Name: Afe_120Hz_Run
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_120Hz_Run(void)
{ 
    UINT16 XRAM usConfigValue;
    static XRAM FristStart = 1;
//    UINT16 XRAM i;
     
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG); // sx全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
#if TEMP_CLOSE_KEY
    usConfigValue = 0x101;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG); // close key enable
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG);
#endif

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
    DrvAsmInterEnable0(BIT_LCD_BUSY_FALL_EN0);
    DrvAsmInterEnable0(BIT_LCD_BUSY_RISE_EN0);
    DrvAsmInterEnable0(BIT_LCD_VBLANK_EN0);
    DrvAsmInterEnable0(BIT_LCD_PANEL_CONFLICT_EN0);
    DrvAsmInterEnable1(BIT_LCD_STB_TICK_EN1);

//    DrvAsmSeStbtMask(0xFFFF);
    DrvAsmSeStbtMask(0xFFFC); //1100
    
    DrvAsmSetIDReset();  //busy_id_max busy_id_min clear
    
//    DBG_FLOW("\npAsmRegs->usAsmIntEn0:0x%x",pAsmRegs->usAsmIntEn0);
    
#if 0  //启动扫描，每次扫描一个TP帧
    DrvAsmInterDisable0(BIT_LCD_VSTART_EN0);      //关闭LCD_VSTART中断使能  

    /* 加载Tab表*/
    DrvLoadTabSingle(1,1);          // 第2个表， 第1个坑开始。

    DrvAsmReq120hz_Small_LcdBusy(); //请求120hz

    g_ucAramReadyFlag = 0;

    while((DrvAsmGetSta()&LCD_RUN_STA)==1)     // 亮屏 lcd_run = 1
    {     
        if((DrvAsmGetSta1()&LCD_BUSY_STA)==0)// lcd busy 下沿开始启动
        {
            AppPanelParamUpdate();

            DrvAsmScanStart();
            DBG_FLOW("\nStartA");  

            DBG_FLOW("\nHave Aram Ready:%d",g_ucAramReadyFlag);
            //当前扫描的TP帧号
            DBG_FLOW("\n9usAsmScanSta0: %04x",DrvAsmGetSta());          // 09  RO
            DBG_FLOW("\n10usAsmScanSta1: %04x",DrvAsmGetSta1()); 

            DBG_FLOW("\nReg6 0x%x ",DebugReadAFEOneReg(6));
            DBG_FLOW("\nReg11 0x%x ",DebugReadAFEOneReg(11));
            DBG_FLOW("\nReg12 0x%x ",DebugReadAFEOneReg(12)); 
            // DBG_FLOW("\n0x%02x 0x%02x",g_usAsmIntFlag0,g_usAsmIntFlag1);
            while((g_ucAramReadyFlag==0)); //&&(g_ucLcdStopFlag==0)&&(g_ucLcdSyncMissFlag==0));
            g_ucAramReadyFlag = 0;
                
            DrvGetRawdata();

            DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据                                  
        }
      
        DelayMs(10); 
        g_RegHead.bits.ucDataReadToggle = 0;
    }

#else  //启动扫描，每次扫描多个TP帧

    DrvLoadTabMultiple(1,6,0,0,1,1);    // 120hz表1  启动扫描后，每次连续扫描2帧，第1次启动从1坑开始，第2次启动从6坑开始，

#if TEST_MUX_ABC_SACN
    DrvLoadTabMultiple(1,4,7,0,2,1);    // 120hz表1  启动扫描后，每次连续扫描3帧，第1次启动从1坑开始，第2次启动从4坑开始，第3次启动从7坑开始，
#endif
#if TEST_MUX_ABCD_SACN
    DrvLoadTabMultiple(1,3,5,7,3,1);    // 120hz表1  启动扫描后，每次连续扫描4帧，第1次1坑开始，第2次从4坑开始，第3次从7坑开始，第4次从7坑开始，
#endif

    DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);   //开启LCD_VSTART中断使能  
                                        
    DrvAsmReq120hz_Small_LcdBusy(); //请求120h
    
    g_ucAramReadyFlag = 0;

//    AFECKEN = 0;   
//    DrvAsmAfeClkGateEn();         //测试自动门控

#if TEST_SCAN_START_IN_VSTART_INT // Vstart 中断里启动扫描
    while((DrvAsmGetSta()&LCD_RUN_STA)==1)    
    {     
        if((DrvAsmGetSta1()&LCD_BUSY_STA)==0)
        {
            AppPanelParamUpdate();
        
            g_ucAramReadyFlag = 0;
#if TEST_120_ARAM_READY_WAKEUP
            ASM_MON_WKEN = 1;
            DrvAsmWakeEnable0(BIT_LCD_ARAM_RDY_WAKE_EN0);       //8
            DBG_FLOW("\n120 ARAM_RDY Standby in------");
            DelayMs(100); // For Print            

            DrvAsmScanStart();
            DrvSysPowerStandby();
#endif 

            while(g_ucAramReadyFlag==0);
            DBG_FLOW("\n=======Afe_120Hz_Run====== :%d,0x%x",g_ucIntCount,g_usAsmIntSta);

            //AppGetAsmState();
#if TEST_120_ARAM_READY_WAKEUP       
            DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据
#endif            
            DrvAsmInterDisable0(BIT_LCD_VSTART_EN0);      //Close  Vstart interrupt

            AppShowRawdata();
            DrvInitRptRam();
            DrvInitAram(); 

            //DBG_FLOW("\n0RegB 0x%x ",DebugReadAFEOneReg(11));

            DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
            DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);           
        }
        
        g_RegHead.bits.ucDataReadToggle = 0;
    }

#endif


#endif
}

/*******************************************************************************
*   Name: Afe_120Hz_Run_Monitor
*  Brief: 120hz亮屏情况，在硬件Monitro情况，上报数据到RptRam,用于触摸检测
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_120Hz_Run_Monitor(void)
{ 
    UINT16 XRAM usConfigValue;
    static XRAM FristStart = 1;

    DrvAsmReq120hz_Small_LcdBusy(); //请求120h
    
    //启动扫描，每次扫描多个TP帧  
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG); // sx全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    
#if TEMP_CLOSE_KEY
    usConfigValue = 0x101;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG); // close key enable
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SYS_CFG0, usConfigValue, AFE_REG);
#endif

    DrvAsmMonitoModeInit(); 

    DBG_FLOW("\n0Reg4 0x%x ",DebugReadAFEOneReg(4));
    DBG_FLOW("\n0RegB 0x%x ",DebugReadAFEOneReg(11));
    DBG_FLOW("\n0RegC 0x%x ",DebugReadAFEOneReg(12));

    DrvLoadTabMultiple(1,0,0,0,0,2);    // 120hz  Tab2  启动扫描后，每次连续扫描1帧，第1次启动从1坑开始

    DBG_FLOW("\nAfe_120Hz_Run_Monitor");  

    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
    DrvAsmInterEnable0(BIT_LCD_TCH_DET_EN0);
    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);

//    DBG_FLOW("\npAsmRegs->usAsmIntEn0:0x%x",pAsmRegs->usAsmIntEn0);
                                           
    g_ucFrameEndFlag = 0;

    while((DrvAsmGetSta()&LCD_RUN_STA)==1)    
    {   
        if((DrvAsmGetSta1()&LCD_BUSY_STA)==0)
        {
            g_usAsmIntFlag0 = 0;
            g_usAsmIntFlag1 = 0;
            DBG_FLOW("\nReg4 0x%x ",DebugReadAFEOneReg(4));
            DBG_FLOW("\nRegB 0x%x ",DebugReadAFEOneReg(11));
            DBG_FLOW("\nRegC 0x%x ",DebugReadAFEOneReg(12));
            DBG_FLOW("\n===120hz Montor===");    

            DrvAsmScanStart();
                
            g_ucFrameEndFlag = 0;
          
            while(!g_ucFrameEndFlag);
            
            DrvAsmInterDisable0(BIT_LCD_FRAME_END_EN0);       //关闭Frame end中断 
            DrvGetRptRamRawBase(); // Monitor模式不上报数据到ARAM,通过RptRam上报。
            DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
 
            DelayMs(5);
    
            g_RegHead.bits.ucDataReadToggle = 0;   

        }
        
        g_RegHead.bits.ucDataReadToggle = 0;
    }

}

/*******************************************************************************
*   Name: Afe_120Hz_H_Clb
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_120Hz_H_Clb(void)
{

#if TEST_MCAP_CB
	UINT16 usConfigValue;

	//配置rf_sel
	usConfigValue = Drv_XsiReadReg(pXSIREG,Addr_ANA_STATIC_CFG0,AFE_REG);
	usConfigValue &= 0x87FF;

	usConfigValue |= (0x01<<13) +  (0x01<<11);						//写key的rf
	Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
	Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);

	Afe_Change_Tab3(2,CB_AFE_SCAN_MODE,18);   //CB,扫描方式

	/*使能mcap,更新tab0以及afe reg相关参数*/
	DrvMcapModeInit(1,3);	
#else
	Afe_Change_Tab3(0,CB_AFE_SCAN_MODE,2);	 //CB,扫描方式
#endif


    if(CB_AFE_SCAN_MODE == 4)//扫描方式5，大坑模式
    {
        DrvAsmReq60hz_Big_LcdBusy();     //申请为大坑模式
    }
    else
    {
        DrvAsmReq120hz_Small_LcdBusy();  //申请为小坑模式
    }

    
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, 0xFF, AFE_REG);//sx p1/p2 配成全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, 0xFF, AFE_REG);//sx p1/p2 配成全驱 

  
    g_ucFrameEndFlag = FALSE;
    g_ucAramReadyFlag = 0;
    g_usAsmIntFlag0 = 0;

    /*设置CB校正的方向*/
    DrvSetCbDir(1,1);  //0:顺时针 若raw<th cb变大;1:逆时针 若rawdata<th cb变小

    /*CB校正模式*/ 
    DrvAsmSetCBAdjustMode(1);

    /*设置硬件CB校正的目标值*/
    DrvAfeSetHCBTarget(10000,10000);

    /* 加载Tab表*/
    DrvLoadTabCB(3,AFE_120HZ_MODE);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);//开启AramReady中断使能
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);//开启Frame end中断使能 
    
    DelayMs(20);

//while(1)
{
    /*启动扫描*/
    DrvAsmScanStart();
    
    while(g_ucAramReadyFlag == 0);//CB校正模式，硬件数到8帧TP帧结束时才会发Aram Ready中断，这时候才表示CB校正结束

    g_ucAramReadyFlag = 0;
    
    DelayMs(10000);
#if 1 //从ARAM中读出CB 
    DrvGetAramCb();
#endif
    DrvAsmAramAvail(); 
    
#if 1 //从TAB表中读出CB
    DelayMs(2000);    
    DrvGetTabRamCb();
    DelayMs(2000);
#endif

#if 1 //从RptRam中后去Rawdata
    DBG_FLOW("\nRead Rawdata from RptRam");
    DrvGetRptRamRawBase();
#endif    
}

#if 0//AFE阶段中，由于CB是由外部的CB决定的，CB的大小对RAWDATA实际上没影响，因此不再进行一次扫描，看RAWDATA的值是否接近设定值,在芯片验证阶段。则有影响

    DelayMs(2000);

    DBG_FLOW("\nAFE RUN");
    
    g_ucFrameEndFlag = FALSE;
    g_ucAramReadyFlag = 0;
    g_usAsmIntFlag0 = 0;
    
    /*正常工作模式*/ 
    DrvAsmSetCBAdjustMode(0);    

    /*单次扫描*/
    DrvLoadTabSingle(0,0);
    
    DelayMs(20);

    DBG_FLOW("\n\n");
    /*启动扫描*/
    
    while(1)
    {
        DrvAsmScanStart();
        while((g_ucAramReadyFlag == 0)||(g_ucFrameEndFlag == 0));

        g_ucAramReadyFlag = 0;
        g_ucFrameEndFlag = 0;
        
        DrvGetAramRawData();
        
        DrvAsmAramAvail();
        
        DelayMs(2000);
    }
#endif

    DBG_FLOW("\nCB FINISH");
    HOLD;
}

/*******************************************************************************
*   Name: Afe_120Hz_Run_Rtc_Monitor
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_120Hz_Run_RTC_Monitor(void)
{
    UINT16 XRAM usConfigValue;
    UINT8 XRAM usStartFlag = 1;
    UINT8 XRAM ucScanMode = 7;      //扫描方式
    UINT8 XRAM ucRtcMode = 1;       //0:auto_mode;1:lcd_start_mode

    if(ucScanMode == 4)//扫描方式5，大坑模式
    {
        DrvAsmReq60hz_Big_LcdBusy();     //申请为大坑模式
    }
    else
    {
        DrvAsmReq120hz_Small_LcdBusy();  //申请为小坑模式
    }

	ASM_32K_EN = 1;

#if TEST_MCAP_HWMON	
	//配置rf_sel
	usConfigValue = Drv_XsiReadReg(pXSIREG,Addr_ANA_STATIC_CFG0,AFE_REG);
	usConfigValue &= 0x87FF;

	usConfigValue |= (0x01<<13) +  (0x01<<11);						//写key的rf
	Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
	Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
	
    Afe_Change_Tab3(2,ucScanMode,13);   //HW MON,扫描方式 	

	/*使能mcap,更新tab0以及afe reg相关参数*/
	DrvMcapModeInit(1,3);	
#else
    Afe_Change_Tab3(1,ucScanMode,2);   //HW MON,扫描方式  

#endif	

    SEL_32K_SRC = 1;
    Drv_Rtc_Init(ucRtcMode);

#if 1//PWR_EN
    ANACON8 = 0xFF;
    ANACON9 = 0xFF;
    DrvAsmSetPwrOn();
#endif

    DBG_FLOW("\nRTC MONITOR");
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);//sx全驱
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);//sx全驱
    
	/*改变tab表中的触摸阈值*/
    DrvSetTabMonThr(0xfff,20,3);

    DrvAsmRtcMonitoModeInit();
    
    P0_4 = 0;
    DelayMs(10);
    P0_4 = 1;
    DelayMs(10);
    P0_4 = 0;
    DelayMs(10);    

    
    /*不能用*/
    RTC_CNT_WKEN = 0;
                     
    DBG_FLOW("\n\nrtc monitor");
         
    DelayMs(100);

    DrvAsmClrInt();
    g_ucFrameEndFlag = 0;
    g_usAsmIntFlag0 = 0;
    g_usAsmIntFlag1 = 0;
    g_ucTimeOutFlag = 0;

#if PWR_EN
    DrvAsmSetHwMonPwrEn(1);                                //设置在硬件monitor下，控制上下电时序。1:控制;0:不控制
#else
    DrvAsmSetHwMonPwrEn(0);                                //设置在硬件monitor下，控制上下电时序。1:控制;0:不控制
#endif

    //while(ucAfeRunMode == TP_FREE_RUN_MODE) // 表示LCD灭屏
    //while(1)
    {
            
        RTC_CNT_WKEN = 0;        //RTC int0唤       
        ASM_MON_WKEN = 1;        //scan mon int0唤醒

        if(usStartFlag)
        {
            //刷base以后才能配置进入hw mon
            DrvAsmSetRtcMonitorMode(TRUE);                          //1:开启rtc monitor模式        
            P0_4 = 1;
            DelayMs(1);            
            P0_4 = 0;
            if(ucRtcMode == 0)
            {
                RTC_WP = 1;
                RTC_START = 1;
            }
            else
            {
                LCD_START_EN = 1;
            }
            usStartFlag = 0;
        }

        //关闭AFE时钟，让RTC定时控制

#if 1
        AFEACKEN = 1;
        AFECKEN  = 0;     
        AFESCKEN = 0;  
        
        //DrvSysPowerStandby();      
        DrvSysPowerStop();
        AFEACKEN = 1;
        AFECKEN  = 1;     
        AFESCKEN = 1;          

        //DBG_FLOW("\nexit stop"); 
#endif
        while((!g_ucTimeOutFlag)&&(!g_ucTchDetFlag));
        DrvAsmSetRtcMonitorMode(FALSE);        

        P0_4 = 1;
        while(RTC_START_STA == 0);
        RTC_WP = 1;
        RTC_CLR = 1;

        if(ucRtcMode)
        {
            LCD_START_EN = 0;
        }

        DelayMs(10); 
        
        DBG_FLOW("\nwake up-------------");
        DBG_FLOW("\nWake up intflag: 0x%x 0x%x",g_usAsmIntFlag0,g_usAsmIntFlag1);
        DBG_FLOW("\niwksta:%02x",g_ucState0);
        
        DelayMs(5);
        if ((g_usAsmIntFlag0 &0x08) == 0x08)
        {
            DBG_FLOW("\n*************Mon Det %02x",g_usAsmIntFlag0);
            DelayMs(1000);
            g_usAsmIntFlag0 = 0x00;            
        }

        if(g_ucTimeOutFlag)
        {
            DBG_FLOW("\n*************Mon Timeout %02x",g_usAsmIntFlag1);
            DelayMs(1000);
        }

        g_ucTimeOutFlag = 0;
        g_ucTchDetFlag = 0;
        DBG_FLOW("\nRTC wake\n");
        
        DrvGetRptRamRawBase();

        g_ucFrameEndFlag = 0;
        g_usAsmIntFlag0 = 0;
        g_usAsmIntFlag1 = 0;

        DelayMs(1000);
        while(1);
        //g_RegHead.bits.ucDataReadToggle = 0;
    }
}

/*******************************************************************************
*   Name: Mcap_120Hz_Run
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Mcap_120Hz_Run()
{
    static XRAM getBaseCount = 0;
    static XRAM FristStart = 1;
    UINT16 XRAM usConfigValue;
    UINT8 XRAM ucTPFramePerScan = 0;
    UINT8 ucTabId = 3;
    UINT8 ucTestMode = 1;//0:测试模式;1:普通模式
    UINT8 ucScanNum = 13;
    UINT8 ucScanMode = 0;//扫描方式
    UINT16 i;   

    Afe_Change_Tab3(2,ucScanMode,ucScanNum );   //MCAP,扫描方式5
        
    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

#if 1
    //配置rf_sel
    usConfigValue = Drv_XsiReadReg(pXSIREG,Addr_ANA_STATIC_CFG0,AFE_REG);
    usConfigValue &= 0x87FF;

    usConfigValue |= (0x01<<13) +  (0x01<<11);                      //写key的rf
    Drv_XsiWriteReg(pXSI0Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_ANA_STATIC_CFG0, usConfigValue, AFE_REG);

    DBG_FLOW("REG_36:%04x",usConfigValue);
#endif

    /*使能mcap,更新tab0以及afe reg相关参数*/
    DrvMcapModeInit(1,ucTabId);
    /* 加载Tab表*/
    //DrvLoadTabSingle(ucTabId,0);            // 表3  启动后，每次扫描1帧

    if(ucScanMode == 4)//扫描方式5，大坑模式
    {
        DrvAsmReq60hz_Big_LcdBusy();
        DrvLoadTabMultiple(1,2,0,0,1,ucTabId);
    }
    else
    {
        DrvAsmReq120hz_Small_LcdBusy();
        DrvLoadTabMultiple(1,6,0,0,1,ucTabId);        
    } 
    
    DrvMcapSetTestMode(ucTestMode,1);          //0为开启测试模式,1为普通模式,选择输出key2   

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);//开启AramReady中断使能
    DrvAsmInterEnable0(BIT_LCD_PANEL_CONFLICT_EN0);//开启屏体冲突中断使能

    g_ucAramReadyFlag = 0;

#if PWR_EN
    ANACON8 = 0xFF;
    ANACON9 = 0xFF;
    DrvAsmSetPwrOn();
#endif

    while(ucAfeRunMode == TP_120HZ_RUN_MODE) // 表示LCD灭屏
    {
    
#if 1
        ARAM_SEL = 1;
        for(i = 0; i < 0x500; i++)
        {
            *(UINT8 *)(0xA000 + i) = 0;//清除aram
        }
        ARAM_SEL = 0;
#endif
    
        DrvAsmScanStart();

        for(i = 0; i < 2; i++)
        {
            while(!g_ucAramReadyFlag);
            g_ucAramReadyFlag = 0;
            DBG_FLOW("\nHave Aram Ready");

            DrvMcapReadSta(g_pMcapPara);
            if(g_pMcapPara->usErrFlg)
            {
                DBG_FLOW("\nMcap Scan Err:%01x",g_pMcapPara->usErrSta);
                DBG_FLOW("\n");
            }
            else
            {           
                if(ucTestMode == 0)
                {
                    if(g_pMcapPara->usSampl_6)
                    {
                        DrvGetAdcData(ucScanNum * 6);
                    }
                    else
                    {
                        DrvGetAdcData(ucScanNum * 8);
                    }
                }
                else
                {
                    DrvGetAramRawData();
                }           
            }
            
            DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据
        }
        

#if 0//PWR_EN
        DrvAsmSetPwrOff();       
#endif        
        DelayMs(2000);
    }
    
}




/*******************************************************************************
*   Name: Afe_Lcd_WakeUp_StandBy
*  Brief: 
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_Lcd_WakeUp_StandBy(void)
{
    UINT16 XRAM usConfigValue;

    DBG_FLOW("\n====Afe_Lcd_WakeUp_StandBy====");

    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    
    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);

    DrvAsmInterDisable0(BIT_LCD_VSTART_EN0);   //Close Vstart interrupt

#if TEST_LCD_RUN_FALL_WAKEUP   
    DrvAsmInterEnable0(BIT_LCD_RUN_FALL_EN0);     
    DrvAsmWakeEnable0(BIT_LCD_RUN_FALL_WAKE_EN0);        //1
#endif
#if TEST_LCD_RUN_RISE_WAKEUP 
    DrvAsmInterEnable0(BIT_LCD_RUN_RISE_EN0);
    DrvAsmWakeEnable0(BIT_LCD_RUN_RISE_WAKE_EN0);        //0  
#endif
#if TEST_LCD_DSTB_FAIL_WAKEUP
    DrvAsmInterEnable0(BIT_LCD_DSTB_FAIL_EN0);  
    DrvAsmWakeEnable0(BIT_LCD_DSTB_FAIL_WAKE_EN0);       //12
#endif  
#if TEST_LCD_DSTB_RISE_WAKEUP
    DrvAsmInterEnable0(BIT_LCD_DSTB_RISE_EN0);  
    DrvAsmWakeEnable0(BIT_LCD_DSTB_RISE_WAKE_EN0);        //11
#endif                                
#if TEST_LCD_VDO_MODE_FALL_WAKEUP                                 
    DrvAsmInterEnable1(BIT_LCD_VDO_MODE_FALL_EN1);
    DrvAsmWakeEnable1(BIT_LCD_VDO_MODE_FALL_WAKE_EN1);    //8
#endif    
#if TEST_LCD_VDO_MODE_RISE_WAKEUP 
    DrvAsmInterEnable1(BIT_LCD_VDO_MODE_RISE_EN1);
    DrvAsmWakeEnable1(BIT_LCD_VDO_MODE_RISE_WAKE_EN1);    //7
#endif
#if TEST_LCD_IDLE_MODE_FALL_WAKEUP 
    DrvAsmInterEnable1(BIT_LCD_IDLE_MODE_FALL_EN1);
    DrvAsmWakeEnable1(BIT_LCD_IDLE_MODE_FALL_WAKE_EN1);   //6
#endif
#if TEST_LCD_IDLE_MODE_RISE_WAKEUP
    DrvAsmInterEnable1(BIT_LCD_IDLE_MODE_RISE_EN1);
    DrvAsmWakeEnable1(BIT_LCD_IDLE_MODE_RISE_WAKE_EN1);   //5
#endif
#if TEST_LCD_3D_MODE_FALL_WAKEUP 
    DrvAsmInterEnable1(BIT_LCD_3D_MODE_FALL_EN1);
    DrvAsmWakeEnable1(BIT_LCD_3D_MODE_FALL_WAKE_EN1);     //4
#endif
#if TEST_LCD_3D_MODE_RISE_WAKEUP
    DrvAsmInterEnable1(BIT_LCD_3D_MODE_RISE_EN1);
    DrvAsmWakeEnable1(BIT_LCD_3D_MODE_RISE_WAKE_EN1);     //3
#endif

//    DBG_FLOW("\nWakeEn0:0x%x WakeEn1:0x%x",pAsmRegs->usAsmIntWakeEn0,pAsmRegs->usAsmIntWakeEn1);                                                                                               
    g_ucAramReadyFlag = 0;
    
    while(1) // 表示LCD灭屏
    {     
        if(ucAfeRunMode == TP_120HZ_RUN_MODE)
        { 
            //Vstart 中启动扫描
            DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
         
            /* 加载Tab表*/
            DrvLoadTabMultiple(1,6,0,0,1,1);    // 120hz表1  启动扫描后，每次连续扫描1帧，第1次启动从1坑开始.
            
            DBG_FLOW("\n120hz Wake in------");
            DelayMs(100); // For Print
            EA = 0;
            ASM_MON_WKEN = 1;
            DrvSysPowerStandby();

            EA = 1;
            DBG_FLOW("\n120hz---------ucWake up:0x%x",ucAfeRunMode);            
        }

        if(ucAfeRunMode == TP_FREE_RUN_MODE)
        {            
            DBG_FLOW("\nFree Wake in------");
            DelayMs(100); // For Print
            EA = 0;
            ASM_MON_WKEN = 1;
            DrvSysPowerStandby();

            EA = 1;
            DBG_FLOW("\nFree---------ucWake up:0x%x",ucAfeRunMode);           
        }
             
        g_RegHead.bits.ucDataReadToggle = 0;   
    }
}

void Afe_TestOneChannelAdc(void)
{
    UINT16 XRAM usConfigValue;

    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);

    DrvAfeSetOneChannelTestMode(1,1,0);   //Test TP通道， 通道号1.
//    DrvAfeSetOneChannelTestMode(1,1,1);     //Test Key通道， 通道号1.    key键无SH,固定为双边采样，数字相减
   
    g_ucAramReadyFlag = 0;
    
    while(1) // 表示LCD灭屏
    {     
        if(ucAfeRunMode == TP_FREE_RUN_MODE)
        {                      
            /* 加载Tab表*/
            DrvLoadTabMultiple(1,0,0,0,0,0);    // Freerun表0  启动后，每次扫描1帧
            DrvAsmScanStart();
            
            while(!g_ucAramReadyFlag);
            g_ucAramReadyFlag = 0;
            
            DrvGetRptRamRawBase();  
            DrvGetRawdata(); 
            
            DrvInitRptRam();
            DrvInitAram();
            
            DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据, 触发AramReady中断

//            DBG_FLOW("\nFreeRun:0x%x",g_ucAramReadyFlag);
            DBG_FLOW("\nReg4 0x%x ",DebugReadAFEOneReg(4));
            DBG_FLOW("\nReg51 0x%x ",DebugReadAFEOneReg(51)); //0x33


        }
    }
}

void Afe_LVDESDWakeUp_Stop(void)
{
    UINT16 XRAM usConfigValue;

    DBG_FLOW("\n====Afe_LVDESDWakeUp_Stop====");

    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
    DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);

    
    g_ucAramReadyFlag = 0;
    
    while(1)  
    {     
        if(ucAfeRunMode == TP_120HZ_RUN_MODE)
        { 
            //Vstart 中启动扫描
            DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
         
            /* 加载Tab表*/
            DrvLoadTabMultiple(1,6,0,0,1,1);    // 120hz表1  启动扫描后，每次连续扫描1帧，第1次启动从1坑开始.
            
            DBG_FLOW("\n120hz LVD ESD Wake in------");
            DelayMs(100); // For Print
            EA = 0;

            //DrvSysPowerIdle();
            //DrvSysPowerStandby();
            DrvSysPowerStop();
            EA = 1;
            DBG_FLOW("\n120hz ucWake up LCD_ESD_STA:0x%x",ESD_STA);
            
        }
         
    }
}

void Afe_LcdRunWakeUp_Test(void)
{
    UINT16 XRAM usConfigValue;

    DBG_FLOW("\n====Afe_LcdRunWakeUp_Test====");

    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
    DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
    DrvAsmInterEnable0(BIT_LCD_RUN_FALL_EN0);  
    DrvAsmInterEnable0(BIT_LCD_RUN_RISE_EN0);
    
    g_ucAramReadyFlag = 0;
    
    while(1) // 表示LCD灭屏
    {     
        if(ucAfeRunMode == TP_FREE_RUN_MODE)
        {          
            DrvAsmInterDisable0(BIT_LCD_VSTART_EN0); // Close VStart中断  
            
            /* 加载Tab表*/
            DrvLoadTabMultiple(1,0,0,0,0,0);    // Freerun表0  启动后，每次扫描1帧
            DrvAsmScanStart();
            
            while(!g_ucAramReadyFlag);
            g_ucAramReadyFlag = 0;

            DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据, 触发AramReady中断

            DBG_FLOW("\nFreeRun Wake in------");
            DelayMs(100); // For Print
            EA = 0;
            LCD_TIM_WKEN = 1;
            //DrvSysPowerIdle();
            //DrvSysPowerStandby();
            DrvSysPowerStop();
            EA = 1;
            DBG_FLOW("\nFreeRun---------ucWake up:0x%x",ucAfeRunMode);

        }
        else if(ucAfeRunMode == TP_120HZ_RUN_MODE)
        { 
            //Vstart 中启动扫描
            DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
         
            /* 加载Tab表*/
            DrvLoadTabMultiple(1,6,0,0,1,1);    // 120hz表1  启动扫描后，每次连续扫描1帧，第1次启动从1坑开始.
            
            DBG_FLOW("\n120hz Wake in------");
            DelayMs(100); // For Print
            EA = 0;
            LCD_TIM_WKEN = 1;
            //DrvSysPowerIdle();
            //DrvSysPowerStandby();
            DrvSysPowerStop();
            EA = 1;
            DBG_FLOW("\n120hz---------ucWake up:0x%x",ucAfeRunMode);
            
        }
                  
        g_RegHead.bits.ucDataReadToggle = 0;   
    }
}


void Afe_LcdDSTBWakeUp_Test(void)
{
    UINT16 XRAM usConfigValue;

    DBG_FLOW("\n====Afe_LcdDSTBWakeUp_Test====");

    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
    DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);


    g_ucAramReadyFlag = 0;
    
    while(1)
    {     
        if(ucAfeRunMode == TP_120HZ_RUN_MODE) 
        { 
            //Vstart 中启动扫描
            DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
            //DrvAsmInterDisable0(BIT_LCD_VSTART_EN0);  //for test idle
         
            /* 加载Tab表*/
            DrvLoadTabMultiple(1,6,0,0,1,1);    // 120hz表1  启动扫描后，每次连续扫描1帧，第1次启动从1坑开始.
            
            DBG_FLOW("\n120hz DeepStandBy Wake in------");
            DelayMs(100); // For Print
            EA = 0;
            LCD_TIM_WKEN = 1;
            //DrvSysPowerIdle();
            //DrvSysPowerStandby();
            DrvSysPowerStop();
            EA = 1;
            DBG_FLOW("\n120hz---ucWake up STA:0x%x CGU5:0x%x",IWKSTA,CGUCON5);           
        }            
    }
}

void Afe_ALL_WakeUpStandby(void)
{
    UINT16 XRAM usConfigValue;

    DBG_FLOW("\n====Afe_ALL_WakeUpStandby====");

    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    g_ucAramReadyFlag = 0;
    
    while(1)
    {     
        if(ucAfeRunMode == TP_120HZ_RUN_MODE) 
        { 
            //Vstart 中启动扫描
            //DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
         
            /* 加载Tab表*/
            DrvLoadTabMultiple(1,6,0,0,1,1);    // 120hz表1  启动扫描后，每次连续扫描1帧，第1次启动从1坑开始.
            
            DrvAsmInterDisableAll();     // Close interrupt

            DBG_FLOW("\n120hz  StandBy Wake in---->");
            DelayMs(100); // For Print
            EA = 0;
            ASM_MON_WKEN = 1;
            LCD_TIM_WKEN = 1;
            LCD_LVD_WKEN = 1;   //lvd,esd state状态会保持，中断进入后，相位翻转硬件会清状态。    
            LCD_ESD_WKEN = 1;
            DrvAsmInterEnableAll();     // Open interrupt
#if 1
            DrvAsmWakeDisable0(BIT_LCD_BUSY_FALL_WAKE_EN0);
            DrvAsmWakeDisable0(BIT_LCD_BUSY_RISE_WAKE_EN0);

            DrvAsmWakeDisable0(BIT_LCD_VSTART_WAKE_EN0);
            DrvAsmWakeDisable0(BIT_LCD_VMID_WAKE_EN0);
            DrvAsmWakeDisable0(BIT_LCD_VEND_WAKE_EN0);
            DrvAsmWakeDisable0(BIT_LCD_VBLANK_WAKE_EN0);
            
            DrvAsmWakeDisable1(BIT_LCD_STB_TICK_WAKE_EN1);
#endif

            
            DrvAsmInterDisable0(BIT_LCD_VSTART_EN0);  //for test standby,Stop Scan.

            DrvSysPowerStandby();

            EA = 1;
            DBG_FLOW("\n120hz>---ucWake up out STA:0x%x CGU5:0x%x",IWKSTA,CGUCON5);           
        }            
    }
}

/*******************************************************************************
*   Name: Afe_LcdRun_Changed
*  Brief: Freerun , 亮屏切换，lcd 自己生成的信号，中断测试。
*  Input: 
* Output: 
* Return: 
*******************************************************************************/
void Afe_LcdRun_Changed(void)
{
    static XRAM getBaseCount = 0; 
    static XRAM FristStart = 1;
    UINT16 XRAM usConfigValue;
    UINT8 XRAM ucTPFramePerScan = 0;

    usConfigValue = 0xFF;
    Drv_XsiWriteReg(pXSI0Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);
    Drv_XsiWriteReg(pXSI1Regs, Addr_AFE_SX_P1_P2_CFG, usConfigValue, AFE_REG);

    DrvAsmInterEnable0(BIT_LCD_ARAM_RDY_EN0);
    DrvAsmInterEnable0(BIT_LCD_FRAME_END_EN0);
    DrvAsmInterDisable0(BIT_LCD_VSTART_EN0);  
//     DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);  
#if 0
    DrvAsmInterEnable0(BIT_LCD_VMID_EN0);  
    DrvAsmInterEnable0(BIT_LCD_VEND_EN0);  
    DrvAsmInterEnable0(BIT_LCD_VBLANK_EN0); 
    DrvAsmInterEnable0(BIT_LCD_BUSY_FALL_EN0); 
    DrvAsmInterEnable0(BIT_LCD_BUSY_RISE_EN0); 
#endif

    DrvAsmInterEnable0(BIT_LCD_RUN_FALL_EN0);  
    DrvAsmInterEnable0(BIT_LCD_RUN_RISE_EN0);

// test INT
#if 1
    DrvAsmInterEnable1(BIT_LCD_STB_TICK_EN1);   
    DrvAsmInterEnable1(BIT_LCD_ODD_EVEN_FALL_EN1);
    DrvAsmInterEnable1(BIT_LCD_ODD_EVEN_RISE_EN1);
    DrvAsmInterEnable1(BIT_LCD_VDO_MODE_FALL_EN1);
    DrvAsmInterEnable1(BIT_LCD_VDO_MODE_RISE_EN1);
    DrvAsmInterEnable1(BIT_LCD_IDLE_MODE_FALL_EN1);
    DrvAsmInterEnable1(BIT_LCD_IDLE_MODE_RISE_EN1);
    DrvAsmInterEnable1(BIT_LCD_3D_MODE_FALL_EN1);
    DrvAsmInterEnable1(BIT_LCD_3D_MODE_RISE_EN1);

#endif

//Test ESD,LVD, LCD_RUN, DSTB INT
#if 1
    //LCD_LVD_PHASE = 1; // default1: 1:检测高电平	  该寄存器已删除
    //LCD_ESD_PHASE = 1;                              该寄存器已删除
    DrvAsmSetPhase();

    LCD_ESD_WKEN = 1; //测试ESD中断0，要开启该enalbe
    LCD_LVD_WKEN = 1; //测试LVD中断0，要开启该enalbe
    DrvAsmInterEnable1(BIT_LCD_RUN_EN1);    // 控制中断4，LCD中断
    DrvAsmInterEnable1(BIT_LCD_DSTB_EN1);   // 控制中断4，LCD中断
#endif
 
    DBG_FLOW("\nucAfeRunMode:0x%x",ucAfeRunMode);

    g_ucAramReadyFlag = 0;
    
    while(1) // 表示LCD灭屏
    {     
        if(ucAfeRunMode == TP_FREE_RUN_MODE)
        {          
            DrvAsmInterDisable0(BIT_LCD_VSTART_EN0); // Close VStart中断  
            
            /* 加载Tab表*/
            DrvLoadTabMultiple(1,0,0,0,0,0);    // Freerun表0  启动后，每次扫描1帧
            DrvAsmScanStart();
            
            while(!g_ucAramReadyFlag);
            g_ucAramReadyFlag = 0;

            DrvAsmAramAvail(); // realse aram:  Asm可以往Aram写下一个tp帧数据, 触发AramReady中断

//            DBG_FLOW("\nFreeRun:0x%x",g_ucAramReadyFlag);

        }
        else if(ucAfeRunMode == TP_120HZ_RUN_MODE)
        {      
            /* 加载Tab表*/
            if(FristStart == 1)
            {
                //FristStart = 0;
                DrvLoadTabMultiple(1,6,0,0,1,1);    // 120hz表1  启动扫描后，每次连续扫描1帧，第1次启动从1坑开始.
            }
            
            //Vstart 中启动扫描
            DrvAsmInterEnable0(BIT_LCD_VSTART_EN0);
        }
   
//        DBG_FLOW("\nucAfeRunMode:0x%x",ucAfeRunMode);
//        DBG_FLOW("\npAsmRegs->usAsmIntSta:0x%x",pAsmRegs->usAsmIntSta);

                
        g_RegHead.bits.ucDataReadToggle = 0;   
    }
}

void Afe_60Hz_120Hz_Changed(void)
{
    /* 加载Tab表*/
    DrvLoadTabSingle(1,0);
    
    while(1)
    {
        //TP_120HZRE = ~TP_120HZRE; //TP_120HZ_REQ^0
        DelayMs(400);

        DrvAsmScanStart();
            
        //DBG_FLOW("\n%02x,%02x,%02x,%02x",tmp,tmp2,INT_FLAG0,IWKSTA);
        while((g_ucAramReadyFlag==0)&&(g_ucLcdStopFlag==0)&&(g_ucLcdSyncMissFlag==0));
     
//      DrvGetRawdata();
                
        g_ucAramReadyFlag = 0;

        g_RegHead.bits.ucDataReadToggle = 0;
    }
}

/*******************************************************************************
*   Name: TestXbus
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void TestXbus(void)
{
    UINT16 XRAM i;
    UINT16 XRAM ReadValue;

    DBG_FLOW("\nXbus test %02X",CGUCON1);
    
//    RLDMACKEN = 1;

    for(i = 0; i<100; i++)
    {
        DrvXbus_WriteLcdReg(0xF680,(UINT8)i);

        ReadValue = DrvXbus_ReadLcdReg(0xF680);
        DBG_FLOW("\nXbus Write:%d Read:%d",i,ReadValue);       
    } 
    while(1);
}

/*******************************************************************************
*   Name: Test_AfeRegWrite
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_AfeRegWrite(UINT16 addr,UINT16 mask0,UINT16 mask1)
{
    UINT16 tmp;
    UINT16 cnt_back;
    UINT16 cnt;
    UINT16 BackUp;
    BOOLEAN flag;

    flag = TRUE;
    BackUp = Drv_XsiReadReg(pXSI0Regs,addr,AFE_REG);
    for (cnt = 0; cnt < 0xffff; cnt++)
    {
        cnt_back = cnt;
        cnt &= mask0;
        cnt |= mask1;

        Drv_XsiWriteReg(pXSI0Regs,addr,cnt,AFE_REG);
        tmp = Drv_XsiReadReg(pXSI0Regs,addr,AFE_REG);
        if (tmp != cnt)
        {
            Drv_XsiWriteReg(pXSI0Regs,addr,BackUp,AFE_REG);
            DBG_FLOW("\n\Error rREG_%02d,write:%04x,read:%04x",addr,cnt,tmp);
            DelayMs(10);
            flag = 0;
            break;
        }
        cnt = cnt_back;
    }
    if (flag)
    {
       DBG_FLOW("\n\rREG_%02d write ok!",addr);
    }
    Drv_XsiWriteReg(pXSI0Regs,addr,BackUp,AFE_REG);
}

/*******************************************************************************
*   Name: Test_Afe_BaseRam
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Afe_BaseRam(void)
{
    UINT8 i;
    UINT8 ucLen;
    UINT16 usAddr;
    UINT16 XRAM Buf[BASE_RAM_LEN];
    
    XSICKEN = 1;

    DBG_FLOW("\n\rAfe Base Ram Test is start");

    /* set ram buf as base ram: testram_sel = 0;*/
    DrvAfeSelTaborRepRam(AREA_BASE_ORDER);

    ucLen  = 0xFF;
    usAddr = BASE_RAM_START_ADDR;
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rBase_Buf[%02d] = 0x%04x",i,Buf[i]);
        }
    }

    usAddr += ucLen;
    ucLen = 0xFF;
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rBase_Buf[%02d] = 0x%04x",i,Buf[i]);
        }
    }
 
    usAddr += ucLen;
    ucLen = BASE_RAM_LEN - ucLen*2;
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rBase_Buf[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\r\n\rRead BaseRam is OK!");

    DBG_FLOW("\n\r\n\rWrite BaseRam is start!");
    ucLen = 0xFF;
    usAddr = BASE_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
    }

    usAddr = BASE_RAM_START_ADDR + ucLen;
    ucLen = 0xFF;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
    }

    
    usAddr = BASE_RAM_START_ADDR + ucLen*2;
    ucLen = BASE_RAM_LEN - ucLen*2;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
    }
    DBG_FLOW("\n\r\n\rWrite BaseRam is OK!");
    DBG_FLOW("\n\rafe BaseRam test is end\n\r");
    while(1);
}

/*******************************************************************************
*   Name: Test_Afe_AccRam
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Afe_AccRam(void)
{
    UINT8 i;
    UINT8 ucLen;
    UINT16 usAddr;
    UINT16 XRAM Buf[ACC_RAM_LEN];

    XSICKEN = 1;

    DBG_FLOW("\n\rAfe Acc Ram Test");
    
    usAddr = ACC_RAM_START_ADDR;
    ucLen  = ACC_RAM_LEN;
    
#if TEST_ACC_H_RAM_EN
    /* set ram buf as acc_h ram: */
    DrvAfeSelACCRam(3);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rAcc_Buf_h[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\r\n\rRead AccRam_H is OK!");

    DBG_FLOW("\n\r\n\rWrite AccRam_H is start!");
    for (i = 0; i < ucLen; i++)
    {        
        Test_AfeRegWrite(usAddr,0x007F,0x0000);  //54bit
        usAddr++;
    }
    DBG_FLOW("\n\r\n\rWrite AccRam_H is OK!");
#endif

#if TEST_ACC_M_RAM_EN
    /* set ram buf as acc_m ram:  */
    DrvAfeSelACCRam(2);

    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rAcc_Buf_m[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\r\n\rRead AccRam_M is OK!");

    DBG_FLOW("\n\r\n\rWrite AccRam_M is start!");
    usAddr = ACC_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_FLOW("\n\r\n\rWrite AccRam_M is OK!");
#endif

#if TEST_ACC_M2_RAM_EN
    /* set ram buf as acc_m ram:  */
    DrvAfeSelACCRam(1);

    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rAcc_Buf_m2[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\r\n\rRead AccRam_M2 is OK!");

    DBG_FLOW("\n\r\n\rWrite AccRam_M2 is start!");
    usAddr = ACC_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_FLOW("\n\r\n\rWrite AccRam_M2 is OK!");
#endif
#if TEST_ACC_L_RAM_EN
    /* set ram buf as acc_l ram:  */
    DrvAfeSelACCRam(0);

    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rAcc_Buf_l[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\r\n\rRead AccRam_L is OK!");

    DBG_FLOW("\n\r\n\rWrite AccRam_L is start!");
    usAddr = ACC_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
        usAddr++;
    }
    DBG_FLOW("\n\r\n\rWrite AccRam_L is OK!");
    DBG_FLOW("\n\rAfe acc ram test is end");
#endif
    while(1);
}


/*******************************************************************************
*   Name: Test_Afe_TabRam
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_Afe_TabRam(void)
{
    UINT8 i;
    UINT8 ucLen;
    UINT16 usAddr;
    UINT16 XRAM Buf[TAB_RAM_LEN];

    usAddr = TAB_RAM_START_ADDR;
    ucLen  = TAB_RAM_LEN;

    XSICKEN = 1;

    DBG_FLOW("\n\rAfe Tab Ram Test is start");
    
    /* set ram buf as tab ram: */
    DrvAfeSelTaborRepRam(AREA_TBL_RAM);

    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rRam_Tab1[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\rRead Ram_Tab1 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rRam_Tab2[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\rRead Ram_Tab2 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rRam_Tab3[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\rRead Ram_Tab3 is ok!");

    usAddr += TAB_RAM_LEN;
    memset(Buf,0xff,TAB_RAM_LEN*2);
    Drv_XsiRead(pXSI0Regs,usAddr,Buf,ucLen,AFE_REG);
    for (i = 0; i < ucLen; i++)
    {
        if (Buf[i] != 0x00)
        {
            DBG_FLOW("\n\rRam_Tab4[%02d] = 0x%04x",i,Buf[i]);
        }
    }
    DBG_FLOW("\n\rRead Ram_Tab4 is ok!");


    DBG_FLOW("\n\r\n\rWrite Ram_Tab is start!");
    usAddr = TAB_RAM_START_ADDR;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
    }
    DBG_FLOW("\n\r\n\rWrite Ram_Tab1 is OK!");
    
    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
    }
    DBG_FLOW("\n\r\n\rWrite Ram_Tab2 is OK!");

    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN*2;
    for (i = 0; i < ucLen; i++)
    {
        usAddr++;
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
    }
    DBG_FLOW("\n\r\n\rWrite Ram_Tab3 is OK!");


    usAddr = TAB_RAM_START_ADDR + TAB_RAM_LEN*3;
    for (i = 0; i < ucLen-1; i++)
    {
        usAddr++;
        Test_AfeRegWrite(usAddr,0xFFFF,0x0000);
    }
    DBG_FLOW("\n\r\n\rWrite Ram_Tab4 is OK!");
    DBG_FLOW("\n\rAfe Tab Ram is end");
    while(1);
}

/*******************************************************************************
*   Name: Test_AfeReg
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Test_AfeReg(void)
{
    UINT8 i;
//    UINT16 tmp,tmp1;
    UINT16 XRAM Buf[AFE_REG_LEN];

    DBG_FLOW("\n\rafe Reg Test is start");
    Drv_XsiInit();
#if 0
    /* XSI_S_REG Read and Write Test */
    tmp1 = Drv_XsiReadReg(pXSI0Regs,0,XSI_S_REG);
    DBG_FLOW("\n\rXSI0_S_Reg: %04x",tmp1);

    for (i = 0; i < 0x07; i++)
    {
        Drv_XsiWriteReg(pXSI0Regs,0,i,XSI_S_REG);
        tmp = Drv_XsiReadReg(pXSI0Regs,0,XSI_S_REG);
        if (tmp != i)
        {
            DBG_FLOW("\n\rError XSI0_S_Reg=%04x; i=%04x",tmp,i);
            break;
        }
    }
    Drv_XsiWriteReg(pXSI0Regs,0,tmp1,XSI_S_REG);
    DBG_FLOW("\n\rXSI_S_Reg write is OK!\n\r");
#endif
    /* AFE_REG Read and Write Test */
    DBG_FLOW("\n\rAfe Reg read and write:");
    Drv_XsiRead(pXSI0Regs,0,Buf,AFE_REG_LEN,AFE_REG);
    for (i = 0; i < AFE_REG_LEN; i++)
    {
        DBG_FLOW("\n\rreg[%02d] = 0x%04x",i,Buf[i]);
    }
//    Test_AfeRegWrite(0,0xFFFF,0x0000);

    Test_AfeRegWrite(1,0x7FFF,0x0000);
    Test_AfeRegWrite(2,0x07FF,0x0000);
    Test_AfeRegWrite(3,0x00FF,0x0000);
    Test_AfeRegWrite(4,0xFFFF,0x0000);
    Test_AfeRegWrite(5,0xFFFF,0x0000);
    Test_AfeRegWrite(6,0x007F,0x0000);
    Test_AfeRegWrite(7,0x007F,0x0000);
    Test_AfeRegWrite(8,0x0FFF,0x0000);
    Test_AfeRegWrite(9,0xFFFF,0x0000);
    Test_AfeRegWrite(10,0xFFFF,0x0000);
    Test_AfeRegWrite(11,0xFFFF,0x0000);
    Test_AfeRegWrite(12,0xFFFF,0x0000);
    Test_AfeRegWrite(13,0x07FF,0x0000);
    Test_AfeRegWrite(14,0x07FF,0x0000);
    Test_AfeRegWrite(15,0x0FFF,0x0000);
    Test_AfeRegWrite(16,0xFFFF,0x0000);
    Test_AfeRegWrite(17,0x003F,0x0000);
    Test_AfeRegWrite(18,0x03FF,0x0000);
    Test_AfeRegWrite(19,0x03FF,0x0000);
    Test_AfeRegWrite(20,0x03FF,0x0000);
    Test_AfeRegWrite(21,0x03FF,0x0000);
    Test_AfeRegWrite(22,0x03FF,0x0000);
    Test_AfeRegWrite(23,0x03FF,0x0000);
    Test_AfeRegWrite(24,0xFFFF,0x0000);
    Test_AfeRegWrite(25,0x00FF,0x0000);
    Test_AfeRegWrite(26,0x03FF,0x0000);
    Test_AfeRegWrite(27,0x03FF,0x0000);
    Test_AfeRegWrite(28,0x01FF,0x0000);
    Test_AfeRegWrite(29,0x01FF,0x0000);
    Test_AfeRegWrite(30,0x03FF,0x0000);
    Test_AfeRegWrite(31,0x01FF,0x0000);
    Test_AfeRegWrite(32,0x0FFF,0x4000); //bit12-14导致误扫描,必须固定配置。
    Test_AfeRegWrite(33,0xFFFF,0x0000);
    Test_AfeRegWrite(34,0x1FFF,0x0000);
    Test_AfeRegWrite(35,0x1FFF,0x0000);
    Test_AfeRegWrite(36,0x1FFF,0x0000);
    Test_AfeRegWrite(37,0x03FF,0x0000);
    Test_AfeRegWrite(38,0x03FF,0x0000);
    Test_AfeRegWrite(39,0xFFFF,0x0000);
    Test_AfeRegWrite(40,0x00FF,0x0000);
    Test_AfeRegWrite(41,0xFFFF,0x0000);
    Test_AfeRegWrite(42,0xFFFF,0x0000);
    Test_AfeRegWrite(43,0xFFFF,0x0000);
    Test_AfeRegWrite(44,0x002F,0x0000);
    Test_AfeRegWrite(45,0x03FF,0x0000);
    Test_AfeRegWrite(46,0xFFFF,0x0000);
    Test_AfeRegWrite(47,0xFFFF,0x0000);
    Test_AfeRegWrite(48,0xFFFF,0x0000);
    Test_AfeRegWrite(49,0xFFFF,0x0000);
    Test_AfeRegWrite(50,0xFFFF,0x0000);
    Test_AfeRegWrite(51,0xFFFF,0x0000);
    Test_AfeRegWrite(52,0xFFFF,0x0000);
    Test_AfeRegWrite(53,0xFFFF,0x0000);
    Test_AfeRegWrite(54,0x002F,0x0000);
    Test_AfeRegWrite(55,0x03FF,0x0000);
    Test_AfeRegWrite(56,0xFFFF,0x0000);
    Test_AfeRegWrite(57,0xFFFF,0x0000);
    Test_AfeRegWrite(58,0xFFFF,0x0000);
    Test_AfeRegWrite(59,0xFFFF,0x0000);
    Test_AfeRegWrite(60,0xFFFF,0x0000);
    Test_AfeRegWrite(61,0xFFFF,0x0000);   
    Test_AfeRegWrite(62,0xFFFF,0x0000);
    Test_AfeRegWrite(63,0xFFFF,0x0000);   

    Test_AfeRegWrite(0x40,0xA010,0x0000); //64
    Test_AfeRegWrite(0x41,0x0008,0x0000);
    Test_AfeRegWrite(0x42,0x03FF,0x0000);
    Test_AfeRegWrite(0x43,0xFFFF,0x0000);
    Test_AfeRegWrite(0x44,0xFFFF,0x0000);
    Test_AfeRegWrite(0x45,0x000F,0x0000);
    Test_AfeRegWrite(0x46,0x0000,0x0000);
    Test_AfeRegWrite(0x47,0x00FF,0x0000);
    Test_AfeRegWrite(0x48,0x0FFF,0x0000);
    Test_AfeRegWrite(0x49,0x0FFF,0x0000);
    Test_AfeRegWrite(0x4A,0x0FFF,0x0000);
    Test_AfeRegWrite(0x4B,0x0FFF,0x0000);
    Test_AfeRegWrite(0x4C,0x0FFF,0x0000);
    Test_AfeRegWrite(0x4D,0x0FFF,0x0000);
    Test_AfeRegWrite(0x4E,0x00FF,0x0000);
    Test_AfeRegWrite(0x4F,0x0FFF,0x0000);
    Test_AfeRegWrite(0x50,0xFFFF,0x0000);
    Test_AfeRegWrite(0x51,0xFFFF,0x0000);
    Test_AfeRegWrite(0x52,0xFFFF,0x0000);
    Test_AfeRegWrite(0x53,0xFFFF,0x0000);
    Test_AfeRegWrite(0x54,0xFFFF,0x0000);
    Test_AfeRegWrite(0x55,0xFFFF,0x0000);
    Test_AfeRegWrite(0x56,0xFFFF,0x0000);
    Test_AfeRegWrite(0x57,0xFFFF,0x0000);


    DBG_FLOW("\n\rAFE_Reg read and write is OK!\n\r");  
    while(1);
}

/*******************************************************************************
*   Name: AfeModeSelInit
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void AfeModeSelInit(void)
{
    if ((DrvAsmGetSta()&LCD_RUN_STA) == 0)
    {
        ucAfeRunMode = TP_FREE_RUN_MODE;
        DBG_FLOW("\nFree run Mode");
    }
    else if (DrvAsmGetSta()&LCD_RUN_STA)
    {
//        if (pAsmRegs->usAsmIntSta&LCD_GLANCE_STA)
//        {
//            ucAfeRunMode = TP_GLANCE_RUN_MODE;
//            DBG_FLOW("\nGlance Mode");
//        }
//        else
        {
             if (g_ucAfeScanMode == TP_60HZ_RUN_MODE)
             {
                 ucAfeRunMode = TP_60HZ_RUN_MODE;
                 DBG_FLOW("\nNomal   60HZ ");
//                 TP_120HZ_REQ = 0x00;                           
             }
             else
             {
                 ucAfeRunMode = TP_120HZ_RUN_MODE;
//                 TP_120HZ_REQ = 0x01;
                 DBG_FLOW("\nNomal   120Hz ");
             }
        }
    }
    DBG_FLOW("\nlcd run: %04x",DrvAsmGetSta());              
}

/*******************************************************************************
*   Name: FlowFactory
*  Brief: Factory flow, get raw touching data, then report the data to host for
*         more processing.
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void FlowFactory(void)
{
    UINT8 ucFlag;
    
    ucFlag = 1;

    Afe_Clk_Init();
    
//    Test_AfeReg();
//    Test_Afe_TabRam();
//    Test_Afe_AccRam();
//    Test_Afe_BaseRam();
//    TestXbus(); 
    Afe_Init();

    Test_DebugOut();

	DrvXbus_WriteInitCode();

    g_RegHead.bits.ucDataReadToggle = 1;

    while(1)
    {
        if (g_State == SS_FACTORY)
        {
            /* Check if need to start raw data collect */
            if (g_RegHead.bits.ucDataReadToggle)
            {
                if (ucFlag == 1)
                {
                    AfeModeSelInit();
                    ucFlag = 0;

#if TEST_LCD_CHANGED                  
                    Afe_LcdRun_Changed();
#endif

#if TEST_STANDBY_WAKEUP_ALL
                    Afe_ALL_WakeUpStandby();
#endif

#if TEST_LCD_RUN_WAKEUP
                    Afe_LcdRunWakeUp_Test();
#endif
#if TEST_LCD_DSTB_WAKEUP
                    Afe_LcdDSTBWakeUp_Test();
#endif
#if TEST_LCD_WAKE_UP_STANDBY
                    Afe_Lcd_WakeUp_StandBy();
#endif
#if TEST_LCD_LVDESD_WAKEUP
                    Afe_LVDESDWakeUp_Stop();
#endif
#if TEST_ONE_CHANNEL_ADC
                    Afe_TestOneChannelAdc();
#endif
                }
                switch(ucAfeRunMode)
                {
                    case TP_FREE_RUN_MODE:
                    {
                        DBG_FLOW("\nfree run");
                        //Afe_Free_Run();
#if TEST_FREERUN_MONITOR                        
                        Afe_Free_Run_Monitor();
#endif
                        //Afe_Free_Run_RTC_Monitor();
                        //Afe_Free_Run_H_CB();
                        Mcap_Free_Run();
                        break;
                    }
                    case TP_60HZ_RUN_MODE:
                    {
                        DBG_FLOW("\n60Hz run");
                        //Afe_60Hz_Run();
                        //Afe_60Hz_H_Clb();
                        Mcap_60Hz_Run();
                        break;
                    }
                    case TP_120HZ_RUN_MODE:
                    {
                        DBG_FLOW("\n120Hz run");
                     
                        //Afe_120Hz_Run(); 
#if TEST_120HZ_MONTIOR                        
                        Afe_120Hz_Run_Monitor();
#endif
                        //Afe_120Hz_H_Clb();
                        Mcap_120Hz_Run();
                        //Afe_120Hz_Run_RTC_Monitor();
                        //Afe_60Hz_120Hz_Changed();

                        break;
                    }
                    default:
                    {
                        break;
                    }
             
                }
            }
        }

    }  
}

