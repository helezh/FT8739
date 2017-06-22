/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: task_main.c
*
*    Author: tangsujun
*
*   Created: 2016-12-22
*
*  Abstract:
*
* Reference:
*
* Version:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/

#include "CfgGlobal.h"
#include "DrvCalCrc.h" 
#include "DrvTimer.h"
#include "Task_main.h"
#include "Drv_mcu.h"
#include "Spi_flash.h"
#include "uart.h"
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define FLASH_LOAD_OK   0x01   //flash 数据有效
#define FLASH_LOAD_ERR  0x02   //flash 数据导入出错
#define FLASH_LOAD_NOF  0x03   //flash 空
#define HOST_HAVE_CMD   0x04   //导入过程有升级命令

#define PRAM_VALID      0x00   //pram有效
#define PRAM_INVALID    0x01   //pram无效
#define UPGRAGE_FLAG    0x02   //有upgrade标志

#define APP_INFO_LEN     32     //len+ecc共12BYTE
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
typedef union
{
    UINT16 buf16[APP_INFO_LEN/2];
    UINT8  buf8[APP_INFO_LEN];
} UNION_APP_INFO;

typedef struct
{
    UINT32 app_code_len;
    UINT16 app_part1_ecc;
    UINT16 app_part1_ecc_N;
    UINT16 app_part2_ecc;
    UINT16 app_part2_ecc_N;
    UINT8  Vendor;
    UINT8  Vendor_N;
    UINT8  FW_Version;
    UINT8  FW_Version_N;
    UINT8  Upgrade_flag1;
    UINT8  Upgrade_flag2;
    UINT32 app_code_len_N;
    UINT8  Reserved1;
    UINT8  Reserved2;
    UINT8  Reserved3;
    UINT8  Reserved4;
    UINT8  Reserved5;
    UINT8  Reserved6;
    UINT8  Reserved7;
    UINT8  Reserved8;
    UINT8  app_id_h;
    UINT8  app_id_l;
}STRUCT_APP_INFO;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT8  g_nRSTtype = RST_POR;   // 软件复位or硬件复位
UINT32 g_ulAppLen ;         // app 长度
UNION_APP_INFO XRAM g_unAppInfo;    // app info缓冲区
STRUCT_APP_INFO XRAM g_strAppInfo;
BOOLEAN g_bTime20ms_Flag ;  // Host升级窗口时间

#if _TEST_FLASH_LOAD_EN
volatile UINT32 far *load_ok  =   ((UINT32 *)(0xFE0000-0X04));
volatile UINT32 far *load_err =   ((UINT32 *)(0xFE0000-0X08));
volatile UINT32 far *load_cnt =   ((UINT32 *)(0xFE0000-0X0C));
#endif
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/
/*******************************************************************************
*   Name: task_check_mem
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT8 task_check_mem_ecc(UINT32 StartAddr, UINT32 Len, UINT16 EccAddr)
{
    UINT16 ecc1;
    UINT16 ecc2;
    UINT16 cal_ecc;

    // ecc
    ecc1 = PRAM_ADDR16(EccAddr);
    ecc2 = PRAM_ADDR16(EccAddr+2);
    
    DBG_ECC("\necc1=%x",ecc1);
    DBG_ECC("\necc2=%x",ecc2);
    
    if ((ecc1 + ecc2) != (UINT16)0xFFFF)
    {
        return INVALID;
    }

#if _CRC_CAL_EN
    cal_ecc = CAL_Check((UINT16)StartAddr, (UINT16)(Len>>1),CRC_TYPE_PRAM);
#else
    cal_ecc = DrvCRC(StartAddr, (UINT16)(Len>>1));
#endif

    DBG_ECC("\necc1=%x",ecc1);
    DBG_ECC("\ncal_ecc=%x",cal_ecc);

    if (ecc1 != cal_ecc)
    {
        return INVALID;
    }

    return VALID;
}

/*******************************************************************************
*   Name: task_check_mem
*  Brief: 检验pram里的代码是否 valid
*  Input:
* Output:
* Return:
*******************************************************************************/
BOOLEAN task_check_mem(void)
{
    UINT16 lenH,lenH_ne,lenL,lenL_ne;
    UINT32 len;
    
    // 1.首地址
    if(PRAM2_ADDR8(0)!=0x02) return INVALID;
    // 2 PART1 ECC
    if (!task_check_mem_ecc(APP_ADDR_PART1_START, APP_ADDR_PART1_LEN, ADDR_PART1_ECC))
    {
        return INVALID;
    }
#if 1    
    // PART2 ECC
    lenH = PRAM_ADDR16(ADDR_APP_LEN_H);
    lenH_ne = PRAM_ADDR16(ADDR_APP_LEN_H_NE);
    lenL = PRAM_ADDR16(ADDR_APP_LEN);
    lenL_ne = PRAM_ADDR16(ADDR_APP_NE_LEN);

    len = ((UINT32)lenH<<16)|lenL;

    if (((lenH + lenH_ne) != 0xFFFF)||((lenL + lenL_ne) != 0xFFFF))
    {
        return INVALID;
    }
#else
    // PART2 ECC
    lenH = PRAM_ADDR32(ADDR_APP_LEN);
    lenH_ne = PRAM_ADDR32(ADDR_APP_LEN_H);   

    if ((lenH + lenH_ne) != 0xFFFFFFFF)
    {
        return INVALID;
    }
    
    len = lenH;
#endif
    //长度溢出
    if ((len > APP_DATA_MAX)||(len < APP_DATA_MIN))
    {
        return INVALID;
    }
    DBG_FLOW("\nlen=%lx",len);
    len -= APP_ADDR_PART2_OFFSET;
    return task_check_mem_ecc(APP_ADDR_PART2_START, len, ADDR_PART2_ECC);
}

/*******************************************************************************
*   Name: task_send_int
*  Brief: 向主机发送中断
*  Input:
* Output:
* Return:
*******************************************************************************/
void task_send_int(void)
{
    UINT16 time = 0x5000;  //8ms

    //来一个脉冲，告诉主机
    DBG_INT("\nI");
    INTOUT  = INT_EN;  
    while (time--);
    INTOUT  = INT_DIS;
    
}


/*******************************************************************************
*   Name: task_check_flash
*  Brief:
*  1.检测flash的合法性
*  Input:
* Output:
* Return:
*******************************************************************************/
#if 1
BOOLEAN task_check_flash(void)
{

    // len/len_h/ecc1/ecc2
    SPIFlash_FastRead(FLASH_APP_INFO, (UINT8 *)g_unAppInfo.buf8,APP_INFO_LEN);
  
    if ( ((g_unAppInfo.buf16[APP_LEN>>1] + g_unAppInfo.buf16[APP_NE_LEN>>1]) != 0xFFFF)
         || ((g_unAppInfo.buf16[APP_LEN_H>>1] + g_unAppInfo.buf16[APP_LEN_H_NE>>1]) != 0xFFFF)
         || ((g_unAppInfo.buf16[P1_ECC_H>>1] + g_unAppInfo.buf16[P1_ECC_NE_L>>1]) != 0xFFFF)
         || ((g_unAppInfo.buf16[P2_ECC_H>>1] + g_unAppInfo.buf16[P2_ECC_NE_L>>1]) != 0xFFFF))
    {
        DBG_FLOW("\nFlash ecc Error!");
        return FALSE;
    }

    //app长度
    g_ulAppLen = (g_unAppInfo.buf16[APP_LEN>>1]|((UINT32)g_unAppInfo.buf16[APP_LEN_H>>1]<<16));        
    DBG_FLOW("\ng_ulAppLen=%lx",g_ulAppLen);

    if((g_ulAppLen> APP_DATA_MAX)||(g_ulAppLen < APP_DATA_MIN))
    {
        DBG_FLOW("\nAppLen Error!");
        return FALSE;
    }
    return TRUE;
}
#else
BOOLEAN task_check_flash()
{
//    STRUCT_APP_INFO *strAppInfo_ptr;
    // len/len_h/ecc1/ecc2
    SPIFlash_FastRead(FLASH_APP_INFO, (UINT8 *)&g_strAppInfo,APP_INFO_LEN);

//    strAppInfo_ptr =&g_strAppInfo;
    if(((g_strAppInfo.app_code_len +g_strAppInfo.app_code_len_N)!=0xffffffff)
        ||((g_strAppInfo.app_part1_ecc+g_strAppInfo.app_part1_ecc_N)!=0xffff)
        ||((g_strAppInfo.app_part2_ecc+g_strAppInfo.app_part2_ecc_N)!=0xffff))       

    {
        DBG_BOOT("Load Error!\n");
        return FALSE;
    }

    //app长度
    g_ulAppLen = g_strAppInfo.app_code_len;

    return TRUE;
}
#endif
/*******************************************************************************
*   Name: task_read_flash
*  Brief:
*  1.从flash读入app数据
*  Input:
* Output:
* Return:
*******************************************************************************/
void task_read_flash(void)
{
    UINT32 ulflashAddr = CODE_START_ADDR;
    UINT32 pramAddr  = APP_ADDR_START;
    UINT32 len;

#if 1 
    len = g_ulAppLen;      //

    DBG_BOOT("\ng_ulAppLen=%lx",g_ulAppLen);
    DBG_BOOT("\nulflashAddr=%lx,pramAddr=%lx,len=%lx",ulflashAddr,pramAddr,len);


    SPIFlash_ReadToPram(ulflashAddr,pramAddr,len);    
#else //比上面多55 byte
    UINT8 i;
        /*PRAM中 app info区先清空*/
    for (i = 0; i < APP_VERIF_LEN; i++)
    {
        PRAM_ADDR8(APP_VERIF_ADDR+i) = 0;
    }
    len = g_ulAppLen - 512;      //留长度2 page最后写
    /*先写3 -> N page */
    SPIFlash_ReadToPram(ulflashAddr+512,pramAddr+512,len);
    /*最后写前2page (app info在第二页)*/
    SPIFlash_ReadToPram(ulflashAddr,pramAddr,512);
    
#endif

}

/*******************************************************************************
*   Name: FlashToPram
*  Brief:
*  1.从flash读入app数据
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT8 FlashToPram(void)
{
    BOOLEAN bFlashValid;
    BOOLEAN bPramValid;
    UINT8 i;

    // 1.Flash合法性
    bFlashValid = task_check_flash();
    
    // 2.导数据
    if (bFlashValid)
    {
        DBG_SPI("\nPram Load!\n");
        //b.导入spi-flash数据
        bPramValid = 0;
        for (i=0; i<3; i++)
        {
            //d.如果失败，再来一次
            if (!bPramValid)
            {
                #if _TEST_FLASH_LOAD_EN
                (*load_cnt)++;
                #endif
                task_read_flash();
             
                DBG_SPI("\nS");
                bPramValid = task_check_mem();             
                DBG_SPI("\nD");
            }
        }
        //d.返回状态
        if (bPramValid)
        {
            #if _TEST_FLASH_LOAD_EN
            (*load_ok)++;
            #endif
            DBG_SPI("\nFLASH_LOAD_OK!\n");
            return S_FLASH_OK;
        }
        else
        {
            #if _TEST_FLASH_LOAD_EN
            (*load_err)++;
            #endif
            //pram里的代码有誤
            DBG_SPI("\nFLASH_LOAD_ERR!\n");
            return S_FLASH_ERR;
        }
    }
    else
    {
        #if _TEST_FLASH_LOAD_EN
        (*load_err)++;
        #endif
        //flash的資料有誤
        DBG_SPI("\nFLASH_LOAD_NOF!\n");
        return S_FLASH_NOF;
    }
}

/*******************************************************************************
*   Name: main_task_flash
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Sys_Remap_Set(void)
{

    //pin脚or POR 复位引入升级路径
    if ((g_nRSTtype == RST_PIN)||(g_nRSTtype == RST_POR))
    {        
        //20ms 时间窗
        while (!g_bTime20ms_Flag);

    }
    DBG_FLOW("\nRemap = 1\n");
#if _BLK_DBG_EN
    wait_printf_done();
#endif
    DrvClearState();     // 关中断，app再开启
    REMAP = 1;  //启动app
    
}

/*******************************************************************************
*   Name: check_pram_rststa
*  Brief:
*  1.发生复位后，检测app的有效性
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT8 check_pram_rststa(void)
{

    if (g_nRSTtype == RST_POR)
    { 
        //pram无效
        return S_NEED_LOAD;
    }
    //升级标志优先判断
    else if (g_nRSTtype == RST_UPGRADE)
    {        
        return S_MCU_WAIT;
    }
    else
    {
        // 2.如果软复位,检测app的合法性,ok直接运行
        if (task_check_mem())
        {
            return S_PRAM_OK;
        }
        else
        {
            //pram无效            
            return S_NEED_LOAD;
        }
    }
}

/*******************************************************************************
*   Name: main_task_flash
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void main_task_flash(void)
{    

    g_ucSysState = check_pram_rststa();
    DBG_FLOW("\ng_ucSysState0=%x",g_ucSysState);    

    
    if (g_ucSysState == S_PRAM_OK)
    {
        //导入app成功，启动app     
        Sys_Remap_Set();
        
    }
    
#if _SPI_FLASH_EN
    if(g_ucFlashMode)
    {
        if(g_ucSysState == S_NEED_LOAD)
        {    
            
            //从spi-flash搬运code
            g_ucSysState = FlashToPram();
            
            DBG_FLOW("\ng_ucSysState1=%x",g_ucSysState);
            #if _TEST_FLASH_LOAD_EN
            DBG_FLOW("\nload_cnt=%lx,load_ok=%lx,load_err=%lx",*load_cnt,*load_ok,*load_err);
            #endif
            
            if(g_ucSysState == S_FLASH_OK)
            {
                //导入app成功，启动app            
                Sys_Remap_Set();
            } 
            
        }
    }
 #endif    
 
    g_ucSysState = S_MCU_WAIT;
    task_send_int();
}



