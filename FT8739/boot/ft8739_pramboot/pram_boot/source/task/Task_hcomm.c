/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: task_hcomm.c
*
*    Author: tangsujun
*
*   Created: 2017-01-20
*
*  Abstract: ����ͨѶģ��
*
* Reference:
*
* Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include "Task_hcomm.h"
#include "Drv_mcu.h"
#include "Spi_flash.h"
#include "uart.h"
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define CHECK_FLASH_BUF_LEN 0x80

/* FT8836 pramboot ID */
#define CHIP_ID_H       0x88
#define CHIP_ID_L       0xA6

typedef enum
{
    HCMD_NOF            = 0x00,
    HCMD_TOUCH          = 0x01,
    HCMD_DATA_R         = 0x03,  // Host read data
    HCMD_FLASH_TYPE     = 0x05,  // Read pramboot Version ID
    HCMD_RST            = 0x07,
    HCMD_APP_START      = 0x08,
    HCMD_MODE           = 0x09,  // pramboot����ģʽѡ��
    HCMD_SEND_INT       = 0x10,  // �жϷ���ʹ��
    HCMD_START1         = 0x55,
    HCMD_FLASH_E_APP    = 0x61,
    HCMD_FECC_INIT      = 0x64,
    HCMD_FECC_CMD       = 0x65,
    HCMD_FECC_READ      = 0x66,
    HCMD_FLASH_STATUS   = 0x6A,
    HCMD_ID             = 0x90,  // Read pramboot ID
    HCMD_START2         = 0xAA,
    HCMD_DATA_W         = 0xBF,
    HCMD_ECC            = 0xCC,  // ͨ��У��Ecc
    HCMD_IC_CUT_VERSION = 0xF5,
} ENUM_PramBootCmd;
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
BOOLEAN g_bHostI2C            = TRUE;      // Host����
BOOLEAN g_bWriteFlag          = FALSE;     // дʱ����Ҫ����ֵ��host��־
BOOLEAN g_bRstFlag            = FALSE;     // Host����

UINT8  g_ucHostIdx            = 0;                 // Hostÿ��ͨѶRW���ֽ����
UINT8  g_ucHostCmdNow         = 0;                 // Host--�����ĵ�һ���ֽڣ�������ͷ
UINT8  g_ucDownloadMode       = BOOT_UPGRADE_FLAG; // 0x0A:download 0x0B: upgrade  others: config upgrade
UINT8  g_ucErasePageLen       = 0;
UINT8  g_ucSendIntFlag        = 0;
UINT16 g_usFlashOperationFlag = 0;

// Double buffer
BOOLEAN g_bbufSel;
ST_BuffInfo *g_pstBufCurComm;
ST_BuffInfo *g_pstBufMainTask;
ST_BuffInfo XRAM g_stBuf1;
ST_BuffInfo XRAM g_stBuf2;

UINT8  g_ucDataBuf[10];             // ���������
ENUM_mTask g_nMainTask = MTASK_NOF;
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: task_send_int
*  Brief: �����������ж�
*  Input:
* Output:
* Return:
*******************************************************************************/
void task_send_int()
{
    if (g_ucSendIntFlag == BOOT_INT_FLAG)
    {
        //��һ�����壬��������
        INTOUT    = INT_EN;
        DelayUs(1000);
        INTOUT    = INT_DIS;
    }
}

/*******************************************************************************
*   Name: DrvRomRegRead
*  Brief:
*    1.g_ucHostCmdNow ��Ϊȫ�ֱ��������ٴ��ͣ���ʡ����
*    2.idx: 0--->255
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT8 DrvRomRegRead(UINT8 idx)
{
    UINT8 ch = BOOT_CODE_FLAG;

    switch (g_ucHostCmdNow)
    {
        // xx xx (cmd = 0x90)
        case HCMD_ID:
        {
            if (idx == 0)
            {
                ch = CHIP_ID_H;
            }
            else if (idx == 1)
            {
                ch = CHIP_ID_L;
            }
            break;
        }

        // xx (cmd = 0x03)
        case HCMD_DATA_R:
        {
            ch = g_pstBufCurComm->pBuf[idx];
            break;
        }

        // xx (cmd = 0xCC)
        case HCMD_ECC:
        {
            ch = g_ucAppEcc;
            break;
        }

        // xx xx (cmd = 0x66)
        case HCMD_FECC_READ:
        {
            ch = g_ucAppEcc;
            break;
        }

        // xx xx (cmd = 0x6A)
        case HCMD_FLASH_STATUS:
        {
            if (idx == 0)
            {
                ch = (UINT8)(g_usFlashOperationFlag >> 8);
            }
            else if (idx == 1)
            {
                ch = (UINT8)(g_usFlashOperationFlag&0xFF);
            }
            break;
        }

        // xx (cmd = 0xF5)
        case HCMD_IC_CUT_VERSION:
        {
            if (idx == 0)
            {
                return g_ucICVersion;
            }
            else if (idx == 1)
            {
                return ~g_ucICVersion;
            }
        }
        default:
        {
            break;
        }
    }
    return ch;
}

/*******************************************************************************
*   Name: DrvRomRegWrite
*  Brief:
*    1.idx: 0-->255
*    2.����ʱ��д�ټ�
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvRomRegWrite(UINT8 idx,UINT8 ucData)
{
    g_bWriteFlag  = FALSE;
    switch (g_ucHostCmdNow)
    {
        // 55
        case HCMD_START1:
        {
            g_ucAppEcc = 0x00;
            break;
        }

        // AA
        case HCMD_START2:
        {
            g_ucAppEcc = 0x00;
            break;
        }

        // 90 xx xx xx
        case HCMD_ID:
        {
            if (idx < 4)
            {
                g_ucAppEcc = 0x00;
                g_ucDataBuf[idx] = ucData;
            }
            if (idx == 0)
            {
                g_bWriteFlag = TRUE;
            }
            break;
        }

        //AE AH AM AL LH LL D0 D1 ... Dn
        case HCMD_DATA_W:
        {

            switch (idx)
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    if (g_bbufSel)
                    {
                        g_pstBufCurComm = &g_stBuf1;
                    }
                    else
                    {
                        g_pstBufCurComm = &g_stBuf2;
                    }
                    g_pstBufCurComm->usStartAddr = ((UINT32)ucData<<16);
                    break;
                }
                case 2:
                {
                    g_pstBufCurComm->usStartAddr += (ucData<<8);
                    break;
                }
                case 3:
                {
                    g_pstBufCurComm->usStartAddr += ucData;
                    break;
                }
                case 4:
                {
                    g_pstBufCurComm->usLen = (ucData<<8);
                    break;
                }
                case 5:
                {
                    g_pstBufCurComm->usLen += ucData;
                    g_pstBufCurComm->usPos = 0;
                    break;
                }
                // 6-->255
                default:
                {
                    g_ucAppEcc ^= ucData;
                    g_pstBufCurComm->pBuf[g_pstBufCurComm->usPos++] = ucData;
                    // д��һ������flash
                    if (g_pstBufCurComm->usPos >= g_pstBufCurComm->usLen)
                    {
                        g_bbufSel = !g_bbufSel;
                        g_pstBufMainTask = g_pstBufCurComm;
                        g_nMainTask = MTASK_FLASH_WRITE;
                    }
                    break;
                }
            }
            break;
        }

        //85 AH AM AL  --> set read address
        case HCMD_DATA_R:
        {
            switch (idx)
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    if (g_bbufSel)
                    {
                        g_pstBufCurComm = &g_stBuf1;
                    }
                    else
                    {
                        g_pstBufCurComm = &g_stBuf2;
                    }
                    g_pstBufCurComm->usStartAddr = ((UINT32)ucData<<16);
                    break;
                }
                case 2:
                {
                    g_pstBufCurComm->usStartAddr += (ucData<<8);
                    break;
                }
                case 3:
                {

                    g_pstBufCurComm->usStartAddr += ucData;
                    g_pstBufMainTask = g_pstBufCurComm;
                    g_bWriteFlag = TRUE;
                    g_nMainTask = MTASK_FLASH_READ;
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }

        //07
        case HCMD_RST:
        {
            POR_STA = 0x00;  //��Ӳ����λ��־
            PRAM_ADDR16(ADDR_PART1_ECC) = 0x00;     
            PRAM_ADDR16(ADDR_PART2_ECC) = 0x00;
         
            g_bRstFlag = TRUE;
            break;
        }

        //09
        case HCMD_MODE:
        {
            if (idx == 1)
            {
                g_ucDownloadMode = ucData;
            }
            else if (idx == 2)
            {
                g_ucErasePageLen = ucData;
            }
            break;
        }

        //10
        case HCMD_SEND_INT:
        {
            g_ucSendIntFlag = ucData;
            break;
        }

        //01 --- touch point
        case HCMD_TOUCH:
        case HCMD_ECC:
        case HCMD_FECC_READ:
        case HCMD_FLASH_STATUS:
        case HCMD_IC_CUT_VERSION:
        {
            g_bWriteFlag = TRUE;
            break;
        }

        case HCMD_FECC_INIT:
        {
            g_ucAppEcc = 0x00;
            break;
        }

        case HCMD_FECC_CMD:
        {
            switch (idx)
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    g_pstBufCurComm->usStartAddr = ((UINT32)ucData<<16);
                    break;
                }
                case 2:
                {
                    g_pstBufCurComm->usStartAddr += (ucData<<8);
                    break;
                }
                case 3:
                {
                    g_pstBufCurComm->usStartAddr += ucData;
                    break;
                }
                case 4:
                {
                    g_pstBufCurComm->usLen = (ucData<<8);
                    break;
                }
                case 5:
                {
                    g_pstBufCurComm->usLen += ucData;
                    g_nMainTask = MTASK_FLASH_ECC;
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }

        // erase app area
        case HCMD_FLASH_E_APP:
        {
            g_nMainTask = MTASK_FLASH_ERASE;
            g_ucAppEcc  = 0x00;
            break;
        }

        default:
        {
            break;
        }
    }
}

/*******************************************************************************
*   Name: I2C_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2C_IRQHandler(void) interrupt 5
{
    UINT8 ch = 0;
    DBG_I2C("\nI2C INT");
    g_bHostI2C = TRUE;
    if (RIFLAG)
    {
        /* ����ж� */
        RIFLAG = 0;
        ch = DATABUFF;
        DBG_I2C("\nI2C CH=%02x",ch);
        /* ���� Host д�ĵ�һ�����ݣ�����Ϊcmd */
        if (g_ucHostIdx ==  0)
        {
            g_ucHostCmdNow = ch;
        }

        // idx �ȼӣ������
        DrvRomRegWrite(g_ucHostIdx,ch);
        g_ucHostIdx++;

        if (g_bWriteFlag)
        {
            DATABUFF = DrvRomRegRead(0x00);
        }
    }

    //ÿһ֡���ĵ�һ�����ݣ�������ǰ׼��������ж������index�Ǵ�1��ʼ��
    if (TIFLAG)
    {
        /* ����ж� */
        TIFLAG = 0;
        g_ucHostIdx++;
        DATABUFF = DrvRomRegRead(g_ucHostIdx); //place next byte
    }
}

/*******************************************************************************
*   Name: I2CStop_IRQHandler
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void I2CStop_IRQHandler(void) interrupt 8
{
    I2CSTP = 0;
    g_ucHostIdx = 0;
    DBG_I2C("\nI2C STOP");
}

/*******************************************************************************
*   Name: CheckFlash
*  Brief: Read flash and colculate or sum relust
*  Input: UINT32 start: flash start address
*         UINT16 len: flash length
* Output: UINT8 *ecc
* Return:
*******************************************************************************/
void CheckFlash(UINT32 start, UINT16 len, UINT8 *ecc)
{
    UINT8 OverFlag = 0;
    UINT8 XRAM buf[CHECK_FLASH_BUF_LEN];
    UINT16 i;

    if (len <= 0x0000)
    {
        len = 0xFFFF;
        OverFlag = 1;
    }
    while (len > CHECK_FLASH_BUF_LEN)
    {
        SPIFlash_FastRead(start,buf,CHECK_FLASH_BUF_LEN);
        len -= CHECK_FLASH_BUF_LEN;
        start += CHECK_FLASH_BUF_LEN;
        for (i = 0; i < CHECK_FLASH_BUF_LEN; i++)
        {
            *ecc ^= buf[i];
        }
    }
    if (OverFlag)
    {
        len += 1;
    }
    SPIFlash_FastRead(start,buf,len);
    for (i = 0; i < len; i++)
    {
        *ecc ^= buf[i];
    }

    DBG_FLASH_ECC("\nFlash:%x",*ecc);
}

