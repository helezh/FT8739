/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: AppHostComm.c
*
*    Author:
*
*   Created: 2016-12-26
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
#include <string.h>
#include "DrvHostComm.h"
#include "DrvSysCtrl.h"
#include "AppHostComm.h"
#include "AppParameter.h"
#include "FlowFactory.h"
#include "FlowUpgrade.h"
#include "TestRwSFR.h"



/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

/* 标准I2C命令响应
 * W EB AA 09 r 03
 * 返回 EB AA 08
 */
#define STD_I2C_CMD_ACK_EN   1
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef enum
{
    SWITCH_TO_STD_I2C_INIT = 0,
    SWITCH_TO_STD_I2C_EB = SWITCH_TO_STD_I2C_INIT,
    SWITCH_TO_STD_I2C_AA,
    SWITCH_TO_STD_I2C_09,
    SWITCH_TO_STD_I2C_END = SWITCH_TO_STD_I2C_09,
} ENUM_SWITCH_TO_STD_I2C;

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
static UINT8 DRAM s_ucI2cWrByteIdx;      /* the byte index of each Host Write */
UINT8 DRAM g_ucI2cDataAddr;              /* current data accessing address */

static ENUM_SWITCH_TO_STD_I2C XRAM g_ucSwitch2STDI2C = SWITCH_TO_STD_I2C_INIT;


/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
/* Touch Panel Parameters */
UNION_PanelParameter XRAM g_unPanelParam;


/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
UINT8 AppAnswerSwitch2STDI2C(UINT8 ucAddr);
void AppHandleSwitch2STDI2C(UINT8 ucAddr, UINT8 ucData);
/*******************************************************************************
*   Name: AppAnswerSwitch2STDI2C
*  Brief: Answer Switch2STDI2C command.
*  Input: None
* Output: None
* Return: UINT8 => the read byte
*******************************************************************************/
UINT8 AppAnswerSwitch2STDI2C(UINT8 ucAddr)
{
    static UINT8 CROM bufCmd[3] = {0xEB,0xAA,0x08};
    static UINT8 XRAM bufIdx;
    UINT8 cmdByte;

    if (ucAddr == 0xEB)
    {
        bufIdx = 0;
    }

    cmdByte = bufCmd[bufIdx];
    bufIdx ++;
    if (bufIdx == 3)
    {
        bufIdx = 0;
        g_ucSwitch2STDI2C = SWITCH_TO_STD_I2C_INIT;
    }
    g_ucI2cDataAddr = 0xEB;

    return cmdByte;
}

/*******************************************************************************
*   Name: AppHandleSwitch2STDI2C
*  Brief: Handlef Switch2STDI2C command.
*  Input: None
* Output: None
* Return: UINT8 => the read byte
*******************************************************************************/
void AppHandleSwitch2STDI2C(UINT8 ucAddr, UINT8 ucData)
{
    if ((ucAddr == 0xEB) || (ucAddr == 0xEC))
    {
        if (g_ucSwitch2STDI2C == SWITCH_TO_STD_I2C_INIT)
        {
            if (ucData == 0xAA)
            {
                g_ucSwitch2STDI2C = SWITCH_TO_STD_I2C_AA;
                g_ucI2cDataAddr --;
            }
        }
        if (g_ucSwitch2STDI2C == SWITCH_TO_STD_I2C_AA)
        {
            if (ucData == 0x09)
            {
                g_ucSwitch2STDI2C = SWITCH_TO_STD_I2C_END;
            }
            else
            {
                g_ucSwitch2STDI2C = SWITCH_TO_STD_I2C_INIT;
            }
        }
        g_ucI2cDataAddr = 0xEA;
    }
}
/*******************************************************************************
*   Name: AppReadGestureData
*  Brief: Read Spec Gesture Data from the register at 0xD3 in normal device mode
*  Input: None
* Output: None
* Return: UINT8 => the read byte
*******************************************************************************/

#define AppReadGestureData()    0xFF;


/*******************************************************************************
*   Name: AppHostUpdateHeadState
*  Brief: Update Register Header and Switch Flow State
*  Input: UINT8 NewRegHeader => New Register Header Value
* Output: None
* Return: None
*******************************************************************************/
void AppHostUpdateHeadState(UINT8 NewRegHeader)
{
    UINT8 DeviceMode;

    g_RegHead.ucData = NewRegHeader;

    /* Optimize, make running time short */
    DeviceMode = g_DeviceMode;

    if (DeviceMode == DEVICE_MODE_TEST)
    {
        g_State = SS_FACTORY;
    }
    else if ((DeviceMode == DEVICE_MODE_NORMAL) || DeviceMode == DEVICE_MODE_INFO)
    {
        g_State = SS_WORK;
    }
    else
    {
        /* 非法命令---跳到工作模式  */
        DBG_HOST("\nMode:error,w00=%02x",NewRegHeader);
        g_State = SS_WORK;
        g_RegHead.ucData = 0x00;
    }
}

/*******************************************************************************
*   Name: AppWriteRegMapDataNormal
*  Brief: Write a byte to the register at given address in normal device mode
*  Input: UINT8 ucAddr => register address
*         UINT8 ucData => register value to be written
* Output: None
* Return: None
*******************************************************************************/
static void AppWriteRegMapDataNormal(UINT8 ucAddr, UINT8 ucData)
{
    /* DEVICE_MODE locates at register address 0x00 */
    if (ucAddr == 0x00)
    {
        AppHostUpdateHeadState(ucData);
    }

    /* REG ADDR 0xEB switch to STD I2C */
    else if ((ucAddr == 0xEB) || (ucAddr == 0xEC))
    {
        AppHandleSwitch2STDI2C(ucAddr, ucData);
    }

    /* REG ADDR 0x80 - 0xBF contain paramters of normal state */
    else if ((ucAddr >= REG_PARAM_ADDR_FIRST) && (ucAddr <= REG_PARAM_ADDR_LAST))
    {
        //AppParamWrite((UINT8)(ucAddr - REG_PARAM_ADDR_FIRST),ucData);
    }

    /* 连续写FC寄存器才有效，中间有别的寄存器插入，则需要重新发FC AA命令 */
    if (ucAddr == 0xFC)
    {
        //AppUpRstDownProc(ucData);
    }
    else
    {
        //g_ucLastState = SS_WORK;
    }
}

/*******************************************************************************
*   Name: AppReadRegMapDataNormal
*  Brief: Read a byte from the register at given address in normal device mode
*  Input: UINT8 ucAddr => register address
* Output: None
* Return: UINT8 => the read byte
*******************************************************************************/
static UINT8 AppReadRegMapDataNormal(UINT8 ucAddr)
{
    /* REG ADDR 0x00 stores devive mode for all kinds of register map */
    if (ucAddr == 0x00)
    {
        return g_RegHead.ucData;
    }
    /* REG ADDR 0x01 stores gesture ID,
     * REG ADDR 0x02 stores current point number,
     * REG ADDR 0x03 - 0x3E stores points status
     * 取数据指针
     */
#if 0        
    else if (ucAddr <= 0x03)
    {
        if (g_bBuffer1Finished)
        {
            g_pReportBuf = &g_unReportBuffer1;
        }
        else
        {
            g_pReportBuf = &g_unReportBuffer2;
        }
        return g_pReportBuf->buf[ucAddr - 1];
    }
    else if (ucAddr <= REG_OUTPUT_ADDR_LAST)
    {
        return g_pReportBuf->buf[ucAddr - 1];
    }
#endif
    else if ((ucAddr == 0xEB) || (ucAddr == 0xEC))
    {
        return AppAnswerSwitch2STDI2C(ucAddr);
    }
    else if ((ucAddr >= REG_PARAM_ADDR_FIRST) && (ucAddr <= REG_PARAM_ADDR_LAST))
    {
        return g_stSysParam.Offset[ucAddr - REG_PARAM_ADDR_FIRST];
    }


    /* REG ADDR 0xFC stores bootloader switch condition */
    else if (ucAddr == 0xFC)
    {
        return g_stSysParam.Params.reg.ucState;
    }
    else if (ucAddr == 0xFE)
    {
        //return g_stModeCtrl[g_ucParaModeCur].ucK2Delay;
        return 0; //   ls
    }
    else
    {
        return 0xFF;
    }
}

/*******************************************************************************
*   Name: AppHostRegRead
*  Brief:
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
UINT8 AppHostRegRead(UINT8 addr)
{
    UINT8 DRAM myDeviceMode;
    UINT8 DRAM ch = 0;
    /* Optimize, make running time short */
    myDeviceMode = g_DeviceMode;
    if (myDeviceMode == DEVICE_MODE_NORMAL)
    {
        ch = AppReadRegMapDataNormal(addr);
    }
    else if (myDeviceMode == DEVICE_MODE_TEST)
    {
        ch = AppReadRegMapDataTest(addr);
    }
    else
    {
        DBG_HOST("\nR:mode error%0d",myDeviceMode);
    }
    return ch;
}


/*******************************************************************************
*   Name: AppHostRegWrite
*  Brief:
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void AppHostRegWrite(UINT8 addr,UINT8 ch)
{
    UINT8 DRAM myDeviceMode;
    /* Optimize, make running time short */
    myDeviceMode = g_DeviceMode;
    if (myDeviceMode == DEVICE_MODE_NORMAL)
    {
        AppWriteRegMapDataNormal(addr, ch);
    }
    else if (myDeviceMode == DEVICE_MODE_TEST)
    {
        AppWriteRegMapDataTest(addr, ch);
    }
    else
    {
        DBG_HOST("\nW:mode error");
    }
}

/*******************************************************************************
*   Name: CommInitHostCommCtrl
*  Brief: Initialize control variables of IRQ handlers
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
static void CommInitHostCommCtrl(void)
{
    s_ucI2cWrByteIdx = 0;
    g_ucI2cDataAddr  = 0;
    DATA_BUF = g_RegHead.ucData;
}

/*******************************************************************************
*   Name: HostCommProc
*  Brief:
*         标准I2C处理
*  Input:
* Output:
* Return:
*******************************************************************************/
static void HostCommProc(void)
{
    UINT8 DRAM tmp;

    /* Host Write while Chip Read */
    if (RI_FLAG)
    {
        RI_FLAG = 0;

        if (s_ucI2cWrByteIdx == 0)
        {
            s_ucI2cWrByteIdx = 1;
            /* Save first byte as data address */
            g_ucI2cDataAddr = DATA_BUF;
            /* Get ready for host to read the first byte after set address */
            DATA_BUF = AppHostRegRead(g_ucI2cDataAddr);
            return;
        }
        else
        {
            tmp = DATA_BUF;
            AppHostRegWrite(g_ucI2cDataAddr,tmp);
            g_ucI2cDataAddr++;
        }
    }

    /* Host read while FT5422 write */
    if (TI_FLAG)
    {
        TI_FLAG = 0;
        g_ucI2cDataAddr++;
        DATA_BUF = AppHostRegRead(g_ucI2cDataAddr);
    }
}

/*******************************************************************************
*   Name: ISR_I2C
*  Brief: Interrupt Service Routine (ISR) for I2C communication
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void ISR_I2C(void) interrupt 5
{
    HostCommProc();
}

/*******************************************************************************
*   Name: ISR_I2C
*  Brief: Interrupt Service Routine (ISR) for I2C communication stop
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void ISR_I2C_Stop(void) interrupt 8
{
    I2CSTP = 0;
    s_ucI2cWrByteIdx = 0;
}

/*******************************************************************************
*   Name: AppHostCommInit
*  Brief: Initialize the module communicats with host
*  Input: None
* Output: None
* Return: None
*******************************************************************************/
void AppHostCommInit(void)
{
    /* default device mode is normal mode */
    g_RegHead.ucData = 0; // g_unPanelParam.reg.RegHead.ucData

    /*  IF there is not have interrupt to host, host read the buffers, It maybe
     *  report the wrong status to host
     */

    /* Initialize hardware and controls of host communication interface */
    DrvHostCommInit();
    CommInitHostCommCtrl();
}


