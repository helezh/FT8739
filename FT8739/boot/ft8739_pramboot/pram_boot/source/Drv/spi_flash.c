/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: SPI-flash.c
*
*    Author: tangsujun
*
*   Created: 2017-01-20
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
#include "SPI_Flash.h"
#include "Drv_mcu.h"
#include "Task_hcomm.h"

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define SPI_BUF               SPI1BUF
#define SPI_RI                SPI1RI
#define SPI_SLVEL0            SPI1SLVELO

// SPI FLASH操作指令定义
#define CMD_WRSR            0x01     // Write Status Register Command
#define CMD_WRITE           0x02     // Write Command
#define CMD_READ            0x03     // Read Command
#define CMD_WRDI            0x04     // Reset Write Enable Latch Command
#define CMD_RDSR            0x05     // Read Status Register Command
#define CMD_RDSR2           0x35     // Read Status Register Command
#define CMD_WREN            0x06     // Set Write Enable Latch Command
#define CMD_FAST_READ       0x0B     // Fast Read Command
#define CMD_RD_JEDEC_ID     0x9F     // Read Manufacturer and Product ID
#define CMD_RDID            0x90     // Read Manufacturer, Memory Type and Capacity
#define CMD_SECTOR_ERASE    0x20     // Erase One Sector in Memory Array
#define CMD_BLOCK_ERASE     0xD8     // Erase One Block in Memory Array
#define CMD_CHIP_ERASE      0x60     // Erase All Sectors in Memory Array
#define CMD_WAKEUP          0xAB     // Release Power_down or Read Device ID according to usage
#define CMD_POWERDOWN       0xB9     // Power down 
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
UINT8 SPI_RW_Byte(UINT8 val);

#define SPI_WriteData(n)  SPI_RW_Byte(n)
#define SPI_ReadData(void)  SPI_RW_Byte(0)
/*******************************************************************************
*   Name: SPI_Init
*  Brief:
*         1.初始化spi时钟分频: 默认48M时8分频；24M时4分频
*         2.初始化spi接口
*         3.spi配置
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI_Init(void)
{

    SPI1CKEN = 1;
    
    SPI1CON =0x03;
    SPI1CON2 =0x46;
    SPI1CON3 =0;
    SPI1CON4 =0X11;
    /* IO配置: P10-->P13 */
    P1MOD = 0x9f;
    P1SEL = 0xff;
    
#if 0
    
    SPI1_EI = 0;

    SPI1MAS = 1;                       // 1：maste mode;
    SPI1_SLVSLELEN  = 1;  //                      // 1：master 模式下slvselo受SPI0CON2[2]控制

    SPI1PH = 0;
    SPI1PO = 0;

    //SPI分频配置
    SPI1CKH  = 0;
    SPI1CKM  = 0;
    SPI1CKL   = 0;                // 00：4分频

    //中断标志使能
    SPI1RI_EN = 1;
    SPI1TI_EN = 0;


     SPI1_SW_IO_ENH=0;
     SPI1_SW_IO_ENL=0;
     

    SPI1RX_AUTO_CLR =1;
    SPI1TX_AUTO_CLR =0;

    DBG_SPI("\n SPI1CON1=%02x ",SPI1CON);
    DBG_SPI("\n SPI1CON2=%02x ",SPI1CON2);
    DBG_SPI("\n SPI1CON3=%02x ",SPI1CON3);
    DBG_SPI("\n SPI1CON4=%02x ",SPI1CON4);    
#endif

    SPIFlash_ReadID();
    SPIFlashSoftWpInit();  //wb 
}


/******************************************************************************
*
*   Name: SPI_ReadWriteData
*  Brief: 读写1个数据
*  Input:
* Output:
* Return:
******************************************************************************/
UINT8 SPI_RW_Byte(UINT8 val)
{
    SPI_BUF = val;                        // Dummy write to output serial clock
    while (!SPI1RI);                    // Wait for the value to be read
    //SPI1RI  = 0;    
    return SPI_BUF;
}
/*******************************************************************************
*   Name: SPI_Write
*  Brief: 写N个数据
*  Input:
* Output:
* Return:
*******************************************************************************/
BOOLEAN SPI_Write(UINT8 *pBuf, UINT16 len)
{
    UINT16 i;
    UINT8 temp;

    for (i=0; i<len; i++)
    {
        SPI_BUF = *pBuf++;
        while (!SPI_RI);
        //SPI_RI = 0;
        temp=SPI_BUF;
    }

    return TRUE;
}


/*******************************************************************************
*   Name: SPI_Read
*  Brief: 读n个数据
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI_Read(UINT8 *pBuf, UINT16 len)
{
    UINT16 i;

    for (i = 0; i < len; i++)
    {
        SPI_BUF  = 0;
        while (!SPI_RI);
        //SPI_RI = 0;
        *pBuf++ = SPI_BUF;
    }
}

/*******************************************************************************
*   Name: SPIFlash_WP
*  Brief: 写使能
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_WP(BOOLEAN flag)
{
    SPI_SLVEL0 = 0;                    // 使能芯片操作
    if (flag)
    {
        SPI_WriteData(CMD_WREN);       // 写使能
    }
    else
    {
        SPI_WriteData(CMD_WRDI);       // 写禁止
    }
    SPI_SLVEL0 = 1;                    // 禁止芯片操作
}

/*******************************************************************************
*   Name: SPIFlash_Busy
*  Brief: 读Flash Busy状态
*  Input:
* Output:
* Return:
*******************************************************************************/
BOOLEAN SPIFlash_Busy(void)
{
    UINT8 val;

    SPI_SLVEL0 = 0;                     // 使能芯片操作
    SPI_WriteData(CMD_RDSR);            // 写读状态命令
    val = SPI_ReadData();               // 读数据命令
    SPI_SLVEL0 = 1;                     // 禁止芯片操作

 //   DBG_SPI("\nBusy=%0x",val);
    if (val&0x01)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*******************************************************************************
* Name: SPIFlashSoftWpInit
* Brief: 打开软件写保护,兼容默认软件写保护使能的其他型号flash
* Input:
* Output:
* Return:
*******************************************************************************/
UINT32 SPIFlash_ReadID(void)
{    
    UINT8 manuID;
    UINT16 flashID = 0;
    
    SPI_SLVEL0 = 0;                        // 使能芯片操作
    SPI_WriteData(CMD_RD_JEDEC_ID);       // 写读状态命令
    manuID = SPI_ReadData();
    flashID = SPI_ReadData();   
    flashID <<=8;
    flashID |= SPI_ReadData();                // 读数据命令
    SPI_SLVEL0 = 1;                        // 禁止芯片操作
    
    DBG_SPI("\nmanuID is 0x%02x",manuID);
    DBG_SPI("\nID is 0x%04x",flashID);

    return (flashID + (manuID<<16));
}

/*******************************************************************************
* Name: SPIFlashSoftWpInit
* Brief: 打开软件写保护,兼容默认软件写保护使能的其他型号flash
* Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlashSoftWpInit(void)
{
    UINT8 ucTmp;

    SPIFlash_WP(TRUE);

    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_RDSR);
    ucTmp = SPI_ReadData();           // 读取flash状态寄存器的值
    SPI_SLVEL0 = 1;

    ucTmp &= 0x83;                    // 清除软件写保护,bit5~bit2(BP3~BP0)
    
    SPIFlash_WP(TRUE);
   
    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_WRSR);          // 写flash状态寄存器
    SPI_WriteData(ucTmp);
    SPI_SLVEL0 = 1;                   // 禁止芯片操作

    while (SPIFlash_Busy());
}

/*******************************************************************************
*   Name: SPIFlash_WriteCmd
*  Brief:
*         1.spi-flash命令发送
*         2.spi-flash地址发送
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_WriteCmd(UINT8 cmd,UINT32 addr)
{
    UINT8 adr[3];

    adr[2] = (addr>>16)&0xFF;
    adr[1] = (addr>>8)&0xFF;
    adr[0] = addr&0xFF;

    SPI_SLVEL0 = 0;         // 使能芯片操作
    SPI_WriteData(cmd);     // 擦除扇区

    SPI_WriteData(adr[2]);  // 写地址
    SPI_WriteData(adr[1]);  // 写地址
    SPI_WriteData(adr[0]);  // 写地址
}

/*******************************************************************************
*   Name: SPIFlash_WritePage
*  Brief:
*        1.写N个字节
*        2.连写不能超过1个页面
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_WritePage(UINT32 addr, UINT8 *pBuf, UINT16 len)
{
    SPIFlash_WP(TRUE);
    SPIFlash_WriteCmd(CMD_WRITE,addr);
    SPI_Write(pBuf,len);
    SPI_SLVEL0 = 1;    // 禁止芯片操作

    g_usTimerCnt = 0;
    while (SPIFlash_Busy()&&(g_usTimerCnt <= PAGE_WRITE_TIME)); // 等待芯片不忙
    if (g_usTimerCnt <= PAGE_WRITE_TIME)
    {
//        DrvSysTimer0Stop();
    }
    else
    {
        DelayUs(5000);
    }

}

/*******************************************************************************
*   Name: SPIFlash_FastReadAddr
*  Brief: 设置快速读命令+地址
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_FastReadAddr(UINT32 addr)
{
    UINT8 adr[3];

    adr[2] = (addr>>16)&0xFF;
    adr[1] = (addr>>8)&0xFF;
    adr[0] = addr&0xFF;

    SPI_SLVEL0 = 0;                         // 使能芯片操作
    SPI_WriteData(CMD_FAST_READ);           // 读指令
    SPI_WriteData(adr[2]);                  // 写地址
    SPI_WriteData(adr[1]);                  // 写地址
    SPI_WriteData(adr[0]);                  // 写地址
    SPI_WriteData(0x00);                    // dummy data to insert 8 dummy clocks
}

/*******************************************************************************
*   Name: SPIFlash_FastRead
*  Brief:
*        1.快速读main block N个字节;
*        2.读不分奇偶地址，字节长度也不分奇偶
*  Input:
* Output:
* Return:
*******************************************************************************/
BOOLEAN SPIFlash_FastRead(UINT32 addr, UINT8 *pBuf, UINT16 len)
{
    SPIFlash_FastReadAddr(addr);
    SPI_Read(pBuf,len);                        // 读数据
    SPI_SLVEL0 = 1;                            // 禁止芯片操作

    return TRUE;
}

/*******************************************************************************
*   Name: SPIFlash_Write
*  Brief:
*        1.写N个字节
*        2.可以连写，自动分成n个包
*  Input:
* Output:
* Return:
*******************************************************************************/
BOOLEAN SPIFlash_Write(UINT32 addr, UINT8 *pBuf, UINT16 len)
{
    UINT16 len_p1;

    len_p1 = PAGE_SIZE - addr%PAGE_SIZE; //计算第一页面的剩余长度

    if (len_p1 >= len)    //检测在同一页面内
    {
        SPIFlash_WritePage(addr,pBuf,len);
    }
    else
    {
        SPIFlash_WritePage(addr,pBuf,len_p1); //跨页,先写第一页

        len = len - len_p1;  //写第2--N页
        addr += len_p1;
        pBuf += len_p1;
        while (len >= PAGE_SIZE)
        {
            SPIFlash_WritePage(addr,pBuf,PAGE_SIZE);
            len  -= PAGE_SIZE;
            pBuf += PAGE_SIZE;
            addr += PAGE_SIZE;
        }
        if (len != 0)  // 最后尾数
        {
            SPIFlash_WritePage(addr,pBuf,len);
        }
    }

    return TRUE;
}

/*******************************************************************************
*   Name: SPIFlash_EraseSector
*  Brief:
*  Input: Winbond: per sector: 4KB, Page: 0~15
* Output:
* Return:
*******************************************************************************/
void SPIFlash_EraseSector(UINT8 sector)
{
    SPIFlash_WP(TRUE);
    SPIFlash_WriteCmd(CMD_SECTOR_ERASE,sector*SECTOR_SIZE);
    SPI_SLVEL0 = 1;                     // 禁止芯片操作

    g_usTimerCnt = 0;
    while (SPIFlash_Busy()&&(g_usTimerCnt <= SECTOR_ERASE_TIME)); // 等待芯片不忙
        if (g_usTimerCnt <= SECTOR_ERASE_TIME)
        {
//            DrvSysTimer0Stop();
        }
        else
        {
            DelayUs(5000);
        }
}

/*******************************************************************************
*   Name: SPIFlash_EraseBlock
*  Brief: Erase block: 64KB(Winbond Only)
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_EraseBlock(UINT8 block)
{
    SPIFlash_WP(TRUE);
    SPIFlash_WriteCmd(CMD_BLOCK_ERASE,block*BLOCK_SIZE);
    SPI_SLVEL0 = 1;     // 禁止芯片操作

    g_usTimerCnt = 0;
    while (SPIFlash_Busy()&&(g_usTimerCnt <= BLOCK_ERASE_TIME));// 等待芯片不忙
    if (g_usTimerCnt <= BLOCK_ERASE_TIME)
    {
//        DrvSysTimer0Stop();
    }
    else
    {
        DelayUs(5000);
    }
}

#if 0
/*******************************************************************************
*   Name: SPIFlash_EraseChip
*  Brief: 全页擦除 FT5003: main block; Winbond: all flash
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_EraseChip()
{
    SPIFlash_WP(TRUE);
    SPI_SLVEL0 = 0;                     // CS low :Enable chip
    SPI_WriteData(CMD_CHIP_ERASE);      // Erase whole chip
    SPI_SLVEL0 = 1;                     // CS low :Enable chip

    g_usTimerCnt = 0;
    while (SPIFlash_Busy()&&(g_usTimerCnt <= CHIP_ERASE_TIME));
    if (g_usTimerCnt > CHIP_ERASE_TIME)
    {
        INTOUT    = INT_EN;
        GPIO3 = INT_EN;
        DelayUs(5000);
        INTOUT    = INT_DIS;
        GPIO3 = INT_DIS;
    }
}
#endif

#define SPI_FLASH_LEN   256

void test_flash_to_pram(void)
{

    UINT16 i,j;
    UINT8  XRAM buf1[SPI_FLASH_LEN];
    UINT8  XRAM buf2[SPI_FLASH_LEN];
    BOOLEAN bIsWb;
    UINT8 temp=0x99;
    

    SPI_Init();
    
    Flash_WP =1;
    Flash_HOLD = 1;   //默认复位，这里释放复位，flash开始工作
    SPIFlashSoftWpInit();  //wb 
    
   #if 0
    
    DBG_SPI("\nspi flash Test is start");
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        buf1[i] = i + temp;
    }
        
    DBG_SPI("\nSPI1CON == %02x",SPI1CON); 
    SPIFlash_EraseSector(0);      //Erase 第一扇区，只有先擦除后才能写入
    DelayUs(1000);
    DBG_SPI("\n\rErase is OK");
    SPIFlash_FastRead(0x0000,buf2,SPI_FLASH_LEN);
    
    
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (i%16 == 0)
        {
            DBG_SPI("\n");
        }
        DBG_SPI("%02x ",buf2[i]);
    }
    DBG_SPI("\n\rspi flash Test is end\n");

    SPIFlash_WritePage(0,buf1,SPI_FLASH_LEN);
    DelayUs(1000);
    #endif
   #if 0  
    SPIFlash_FastRead(0x0000,PRAM2_PTR8(0) ,256);// 1UL*1024UL);
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (PRAM2_ADDR8(i) != ((i+temp)&0xff))
        {
            DBG_SPI("\nerr0\n");
            HOLD;
        }
        if(i%16 == 0)
        {
            DBG_SPI("\n");

        }
        DBG_SPI("%02x ",PRAM2_ADDR8(i));
    }
    
    
    DBG_SPI("\n spi DualRead 1k \n");

        
    SPIFlash_DualRead(0x0000,PRAM2_PTR8(0),256);// 1UL*1024UL);
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (PRAM2_ADDR8(i) != ((i+0x88)&0xff))
        {
            DBG_SPI("\nerr1\n");
            HOLD;
        }
        if(i%16 == 0)
        {
            DBG_SPI("\n");

        }
        DBG_SPI("%02x ",PRAM2_ADDR8(i));
    }
    DelayUs(10000);


    
    SPIFlashQUAD_EN(1);
    SPIFlash_QuadRead(0x0000,PRAM2_PTR8(0),256);// 1UL*1024UL);
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (PRAM2_ADDR8(i) != ((i+0x88)&0xff))
        {
            DBG_SPI("\nerr2\n");
            HOLD;
        }
        if(i%16 == 0)
        {
            DBG_SPI("\n");

        }
        DBG_SPI("%02x ",PRAM2_ADDR8(i));
    }

    SPIFlashQUAD_EN(0);
    DBG_MODE("\n spi QuadRead 1k  END \n");
 #endif
    
}














