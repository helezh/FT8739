/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: main.c
*
*    Author: tangsujun
*
*   Created: 2017-01-20
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "CfgGlobal.h"
#include "Drv_mcu.h"
#include "Task_hcomm.h"
#include "SPI_flash.h"

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
//#define APP_VERIF_ADDR    0x0100  // Verification Info
#define APP_INFO_ADDR    0xFEE900  // Verification Info
#define APP_VERIF_LEN     0x20

#define FW_CFG_TOTAL_SIZE         0x80

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
/* 预留给校验码信息的代码区 */
UINT8 ecode g_aucVerfication[APP_VERIF_LEN+FW_CFG_TOTAL_SIZE] _at_ APP_INFO_ADDR;

BOOLEAN g_bFlashWriteFlag = TRUE;


/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name:  init_mcu
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void init_mcu(void)
{
    DrvSysInit();
    DrvUartInit();
 
    DBG_FLOW("\npram boot");
    SPI_Init();    
    DrvHostI2cInit();
    DrvSysTimer0Init();
    EA = 1;
    DBG_FLOW("\npram boot init ok,%s!",__DATE__);
}

/*******************************************************************************
*   Name:  main
*  Brief:
*  Input:
* Output:
* Return:
*
******************************************************************************/
void main(void)
{
    init_mcu();

 //   test_flash_to_pram();

    //回调函数，执行主机发来的命令
    while (1)
    {
        switch (g_nMainTask)
        {
            case MTASK_FLASH_WRITE:
            {
                g_nMainTask = MTASK_NOF;
                g_usFlashOperationFlag = FLASH_STATUS_NOP;
                if (g_bFlashWriteFlag)
                {
                    task_send_int();
                    g_bFlashWriteFlag = FALSE;
                }
                SPIFlash_Write( g_pstBufMainTask->usStartAddr,
                                g_pstBufMainTask->pBuf,
                                g_pstBufMainTask->usLen);
                g_bFlashWriteFlag = TRUE;
                g_usFlashOperationFlag = FLASH_STATUS_WRITE_OK + g_pstBufMainTask->usStartAddr/g_pstBufMainTask->usLen;
                DBG_HOST("\nBuf write");
                break;
            }

            case MTASK_FLASH_READ:
            {
                g_nMainTask = MTASK_NOF;
                SPIFlash_FastRead( g_pstBufMainTask->usStartAddr,
                                   g_pstBufMainTask->pBuf,256);

                if (g_bHostI2C)
                {
                    DATABUFF = g_pstBufMainTask->pBuf[0];
                }
                DBG_HOST("\nBuf read");
                break;
            }

            case MTASK_FLASH_ECC:
            {
                g_nMainTask = MTASK_NOF;
                g_usFlashOperationFlag = FLASH_STATUS_NOP;
                CheckFlash( g_pstBufMainTask->usStartAddr,
                            g_pstBufMainTask->usLen,
                            &g_ucAppEcc);
                task_send_int();
                g_usFlashOperationFlag = FLASH_STATUS_ECC_OK;
                DBG_HOST("\nFlash ecc");
                break;
            }

            case MTASK_FLASH_ERASE:
            {
                g_nMainTask = MTASK_NOF;
                g_usFlashOperationFlag = FLASH_STATUS_NOP;

                if (g_ucDownloadMode == BOOT_DOWNLOAD_FLAG)
                {
                    /*修改成只Erase 128K*/
                    SPIFlash_EraseBlock(0);
                    SPIFlash_EraseBlock(1);
         
                }
                else if (g_ucDownloadMode == BOOT_UPGRADE_FLAG)
                {
                    UINT8 i;

                    for (i = 1; i < 19; i++)
                    {
                        SPIFlash_EraseSector(i);
                    }

                }
                else
                {
                    UINT8 i;
                    UINT8 ucStartPage;

                    ucStartPage = g_ucDownloadMode - BOOT_ERASE_PAGE_ADDR;

                    // 从第ucStartPage开始擦除g_ucErasePageLen个Page,每个page为4KByte
                    for (i = 0; i < g_ucErasePageLen; i++)
                    {
                        SPIFlash_EraseSector(ucStartPage);
                        ucStartPage++;
                    }
                }

                task_send_int();
                g_usFlashOperationFlag = FLASH_STATUS_ERASE_OK;
                DBG_HOST("\nFlash erase");
                break;
            }

            default:
            {
                break;
            }
        }
        if (g_bRstFlag)
        {
            DelayUs(5000);
            DelayUs(5000);
            SFTRST  = 0xFF;
        }
    }
}

