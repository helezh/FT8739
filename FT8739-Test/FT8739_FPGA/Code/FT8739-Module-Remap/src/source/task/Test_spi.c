/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_spi.c
*
*    Author: tangsujun
*
*   Created: 2016-12-26
*
*  Abstract: 
*
* Reference:
*
*******************************************************************************/
#include "Test_SPI.h"
//#include "Drv_XBUS.h"
#if _TEST_SPI_EN


#define SPI1_AUTO_CLR      1 // 
/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/

#define SPI_VECTOR 10

#define SPI_CON  SPI1CON
#define SPI_CON2 SPI1CON2
#define SPI_BUF  SPI1BUF

//位功能

#define SPI_CS   SPI1_SLVSLELEN

#define SPI_BUSY   SPI1_BUSY
#define SPI_STOP   SPI1_STOP
#define SPI_START  SPI1_START
#define SPI_SLVEL0 SPI1SLVELO
#define SPI_TI_EN  SPI1TI_EN


//flash信息宏
#define PAGE_SIZE           ((UINT8)0x80)     // 定义页大小
#define SECTOR_SIZE         ((UINT16)0x1000)   // 定义扇区大小
#define BLOCK_SIZE          ((UINT32)0x10000)  // 定义块区大小

// SPI FLASH操作指令定义
#define CMD_WRSR            0x01     // Write Status Register Command
#define CMD_WRITE           0x02     // Write Command
#define CMD_READ            0x03     // Read Command
#define CMD_WRDI            0x04     // Reset Write Enable Latch Command
#define CMD_RDSR            0x05     // Read Status Register Command
#define CMD_RDSR2            0x35     // Read Status Register Command
#define CMD_WREN            0x06     // Set Write Enable Latch Command
#define CMD_FAST_READ       0x0B     // Fast Read Command
#define CMD_RD_JEDEC_ID     0x9F     // Read Manufacturer and Product ID
#define CMD_RDID            0x90     // Read Manufacturer, Memory Type and Capacity
#define CMD_SECTOR_ERASE    0x20     // Erase One Sector in Memory Array
#define CMD_BLOCK_ERASE     0xD8     // Erase One Block in Memory Array
#define CMD_CHIP_ERASE      0x60     // Erase All Sectors in Memory Array
#define CMD_WAKEUP          0xAB     // Release Power_down or Read Device ID according to usage
#define CMD_POWERDOWN       0xB9     // Power down 



#define CMD_READ_DUAL_O       0x3B     // Fast Read Dual Output Command
#define CMD_READ_QUAD_O       0x6B     // Fast Read Quad Output Command
#define CMD_READ_DUAL_IO      0xBB     // Fast Read Dual I/O Command
#define CMD_READ_QUAD_IO      0xEB     // Fast Read Quad I/O Command


#define SPI_FLASH_LEN   ((UINT16)256)


#define SPI1_MODE_STD        ((UINT8) 0)
#define SPI1_MODE_DUAL       ((UINT8) 1)
#define SPI1_MODE_QUAD       ((UINT8) 2)

#define SPI1_IO_OUTPUT       ((UINT8) 0)
#define SPI1_IO_INPUT        ((UINT8) 1)

#define SPI1_CS_PIN      BITn(0)
#define SPI1_CLK_PIN     BITn(1)
#define SPI1_SI_PIN      BITn(2)
#define SPI1_SO_PIN      BITn(3)
#define SPI1_HOLD_PIN    BITn(4)
#define SPI1_WP_PIN      BITn(7)

#define SPI1_CS      P1_0 //BITn(0)
#define SPI1_CLK     P1_1 //BITn(1)
#define SPI1_MOSI      P1_2 //BITn(2)
#define SPI1_MISO      P1_3 //BITn(3)
#define SPI1_HD      P1_4 //BITn(4)
#define SPI1_WP      P1_7 //BITn(7)


//#define SPI_SLVEL0 SPI1_CS
/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
UINT8 g_nDummyData = 0;

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/
UINT8 SPI_RW_Byte(UINT8 val);

#define SPI_WriteData(n)  SPI_RW_Byte(n)
#define SPI_ReadData(void)  SPI_RW_Byte(0)
/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


#if 1
void SPI1_Mode_Sel(UINT8 mode)
{
    if(mode==1)
    {
        SPI1MODE_SELH   =0;
        SPI1MODE_SELL   =1;
    }
    else if(mode==2)
    {
         SPI1MODE_SELH   =1;
        SPI1MODE_SELL   =0;
    }
    else
    {
         SPI1MODE_SELH   =0;
        SPI1MODE_SELL   =0;     
    }

}

void SPI1_IO_Set(UINT8 mode)
{
    if(mode==1)
    { 
        Flash_WP =1;
        Flash_HOLD = 1;  
        P1MOD = 0x0f;
        SPI1_SW_IO_ENH=0;
        SPI1_SW_IO_ENL=1;

    }
    else if(mode==2)
    {   
        P1MOD = 0x9f;
        SPI1_SW_IO_ENH=1;
        SPI1_SW_IO_ENL=1;


    }
    else
    {   
        Flash_WP =1;
        Flash_HOLD = 1;  
        P1MOD = 0x0f;
        SPI1_SW_IO_ENH=0;
        SPI1_SW_IO_ENL=0;

    }
}


void SPI1_IO_Switch(UINT8 time,UINT8 dir)
{
    
        
        SW_1BYTE_LATER  =time&0x01;
         
        SPI1_SW_DIR        =dir&0x01;

        SPI1_SW_EN          =1;

}
#endif
/*******************************************************************************
*   Name: SPI_Init
*  Brief: MAIN CLK: 48M
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI_Init(void)
{

    SPI1CKEN = 1;
    SPI1CON2 =0x46;
    SPI1CON3 =0;
    SPI1CON4 =0X10;
    /* IO配置: P10-->P13 */
    P1MOD = 0xFF;//9f;
    P1SEL = 0xff;
    P1SEL &= ~(SPI1_SI_PIN|SPI1_SO_PIN|SPI1_HOLD_PIN|SPI1_WP_PIN);
    
    P1DIR |= SPI1_CS_PIN|SPI1_CLK_PIN|SPI1_SI_PIN|SPI1_HOLD_PIN|SPI1_WP_PIN;
    P1DIR &= ~SPI1_SO_PIN;
    
    SPI1_EI = 0;

    SPI1MAS = 1;                       // 1：maste mode;
    SPI1_SLVSLELEN  = 1;  //                      // 1：master 模式下slvselo受SPI0CON2[2]控制

    SPI1PH = 0;
    SPI1PO = 0;

    //SPI分频配置
    SPI1CKH  = 1;
    SPI1CKM  = 1;
    SPI1CKL  = 1;                // 00：4分频

    //中断标志使能
    SPI1RI_EN = 1;
    SPI1TI_EN = 0;


     SPI1_SW_IO_ENH=0;
     SPI1_SW_IO_ENL=0;
     
#if SPI1_AUTO_CLR
    SPI1RX_AUTO_CLR =1;
    SPI1TX_AUTO_CLR =0;

#endif

    DBG_SPI("\n SPI1CON1=%02x ",SPI1CON);
    DBG_SPI("\n SPI1CON2=%02x ",SPI1CON2);
    DBG_SPI("\n SPI1CON3=%02x ",SPI1CON3);
    DBG_SPI("\n SPI1CON4=%02x ",SPI1CON4);
    DBG_SPI("\n P1MOD=%02x ",P1MOD);
    DBG_SPI("\n P1SEL=%02x ",P1SEL);
    DBG_SPI("\n P1DIR=%02x ",P1DIR);
    DBG_SPI("\n P1BUF=%02x ",P1BUF);
    
}

/*******************************************************************************
*   Name: SPI_ReadData
*  Brief: 读1个数据
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT8 SPI_RW_Byte(UINT8 val)
{
    SPI_BUF = val;                        // Dummy write to output serial clock
    while (!SPI1RI);                    // Wait for the value to be read
    //SPI1RI  = 0;    
    return SPI_BUF;
}

/*******************************************************************************
*   Name: SPI_Read
*  Brief: 读n个数据
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPI_Read(UINT8 far *pBuf, UINT32 len)
{
    UINT32 i;

#if 0
    for (i = 0; i < len; i++)
    {
        SPI_BUF  = 0;
        while (!SPI1RI);
       // SPI1RI = 0;
        *pBuf++ = SPI_BUF;
    }

#else
    SPI_BUF  = 0;
    for (i = 0; i < (len-1); i++)
    {
        
        while (!SPI1RI);
        SPI_BUF  = 0;
   //    SPI1RI = 0;
        *pBuf++ = SPI_BUF;
    }
    while (!SPI1RI);
    *pBuf++ = SPI_BUF;
#endif
}

/*******************************************************************************
* Name: SPIFlash_WP
* Brief:写使能
* Input:
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
* Name: SPIFlash_Busy
* Brief: 读Flash状态
* Input:
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

    DelayMs(8);
    
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
* Name: SPIFlash_WriteCmd
* Brief:
*         1.spi-flash命令发送
*         2.spi-flash地址发送
* Input:
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
* Name: SPIFlash_WritePage
* Brief:
*        1.写N个字节
*        2.连写不能超过1个页面
* Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_WritePage(UINT32 addr, UINT8 *pBuf, UINT16 len)
{
    UINT16 i,TEMP;
    SPIFlash_WP(TRUE);
    SPIFlash_WriteCmd(CMD_WRITE,addr);

    for (i = 0; i < len; i++)
    {
        SPI_BUF = pBuf[i];
        while (!SPI1RI);
        SPI1RI = 0;
        //TEMP=SPI_BUF;
    }
    SPI_SLVEL0 = 1;                  // 禁止芯片操作
    while (SPIFlash_Busy());         // 等待芯片不忙
}

/*******************************************************************************
*   Name: SPIFlash_FastReadAddr
*  Brief:
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

    SPI_SLVEL0 = 0;                        // 使能芯片操作
    SPI_WriteData(CMD_FAST_READ);          // 读指令
    SPI_WriteData(adr[2]);                 // 写地址
    SPI_WriteData(adr[1]);                 // 写地址
    SPI_WriteData(adr[0]);                 // 写地址
    SPI_WriteData(0x00);                   // dummy data to insert 8 dummy clocks
}

/*******************************************************************************
*   Name: SPIFlash_FastReadAddr
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_DUALAddr(UINT32 addr,UINT8 cmd,UINT8 mode)
{
    UINT8 adr[3];
    adr[2] = (addr>>16)&0xFF;
    adr[1] = (addr>>8)&0xFF;
    adr[0] = addr&0xFF;

    
    
    SPI1_Mode_Sel(SPI1_MODE_STD);
    SPI1_IO_Set(SPI1_MODE_DUAL);  
    
    
    SPI_SLVEL0 = 0;                        // 使能芯片操作
    if(cmd !=0)  //0xbb
    {
        SPI_WriteData(CMD_READ_DUAL_IO);          // 读指令
        SPI1_Mode_Sel(SPI1_MODE_DUAL);    
        SPI1_IO_Switch(0, SPI1_IO_OUTPUT);
    }
    else    //0x3b
    {
        SPI_WriteData(CMD_READ_DUAL_O);          // 读指令
    }
    SPI_WriteData(adr[2]);                 // 写地址
    SPI_WriteData(adr[1]);                 // 写地址
    SPI_WriteData(adr[0]);                 // 写地址

    
    SPI1_IO_Switch(1, SPI1_IO_INPUT);
    
    SPI_WriteData(0x00);                   // dummy data to insert 8 dummy clocks
    if(cmd==0)  //0x3b
    {
        SPI1_Mode_Sel(SPI1_MODE_DUAL); 
    }

}

/*******************************************************************************
*   Name: SPIFlash_FastReadAddr
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlash_QUADAddr(UINT32 addr,UINT8 cmd,UINT8 mode)
{
    UINT8 adr[3];
    adr[2] = (addr>>16)&0xFF;
    adr[1] = (addr>>8)&0xFF;
    adr[0] = addr&0xFF;

    
    
    SPI1_Mode_Sel(SPI1_MODE_STD);
    SPI1_IO_Set(SPI1_MODE_QUAD);  
    
    
    SPI_SLVEL0 = 0;                        // 使能芯片操作
    
    if(cmd !=0)//0xeb
    {
        SPI_WriteData(CMD_READ_QUAD_IO);          // 读指令
        SPI1_Mode_Sel(SPI1_MODE_QUAD);    
        SPI1_IO_Switch(0, SPI1_IO_OUTPUT);
    }
    else    //0x6b
    {
        SPI_WriteData(CMD_READ_QUAD_O);          // 读指令
    }
    SPI_WriteData(adr[2]);                 // 写地址
    SPI_WriteData(adr[1]);                 // 写地址
    SPI_WriteData(adr[0]);                 // 写地址

    if(cmd !=0)//0xeb
    {
        SPI_WriteData(0x00);                   // M7-M0
        SPI_WriteData(0x00);                   // dummy data to insert 8 dummy clocks
    }
    SPI1_IO_Switch(1, SPI1_IO_INPUT);
    
    SPI_WriteData(0x00);                   // dummy data to insert 8 dummy clocks
    if(cmd==0)  //0x6b
    {
        SPI1_Mode_Sel(SPI1_MODE_QUAD); 
    }

    
}
/*******************************************************************************
*   Name: SPIFlash_FastRead
*  Brief: 1.读N个字节 2.快速读命令
*  Input:
* Output:
* Return:
*******************************************************************************/
BOOLEAN SPIFlash_FastRead(UINT32 addr, UINT8 far *pBuf, UINT32 len)
{
    SPIFlash_FastReadAddr(addr);
    SPI_Read(pBuf,len);                     // 读数据     
    SPI_SLVEL0 = 1;                         // 禁止芯片操作
    return TRUE;
}
BOOLEAN SPIFlash_DualRead(UINT32 addr, UINT8 far *pBuf, UINT32 len)
{
    SPIFlash_DUALAddr(addr,1,SPI1_MODE_DUAL);
    SPI_Read(pBuf,len);                     // 读数据
   
    SPI_SLVEL0 = 1;                         // 禁止芯片操作
    SPI1_Mode_Sel(SPI1_MODE_STD);
    SPI1_IO_Set(SPI1_MODE_STD);  
    return TRUE;
}
BOOLEAN SPIFlash_QuadRead(UINT32 addr, UINT8 far *pBuf, UINT32 len)
{
    SPIFlash_QUADAddr(addr,1,SPI1_MODE_QUAD);//  
    SPI_Read(pBuf,len);                     // 读数据    
    SPI_SLVEL0 = 1;                         // 禁止芯片操作
    SPI1_Mode_Sel(SPI1_MODE_STD);
    SPI1_IO_Set(SPI1_MODE_STD);  
    return TRUE;
}
/*******************************************************************************
*   Name: SPIFlash_EraseSector
*  Brief: Erase sector: 4KB
*  Input:
* Output:
* Return:
*******************************************************************************/
BOOLEAN SPIFlash_EraseSector(UINT8 sector)
{
    SPIFlash_WP(TRUE);
    SPIFlash_WriteCmd(CMD_SECTOR_ERASE,sector*SECTOR_SIZE);
    SPI_SLVEL0 = 1;                     // 禁止芯片操作
    while (SPIFlash_Busy());
    return TRUE;
}
/******************************************************************************
*
* Name: SPIFlashSoftWpInit
* Brief: 打开软件写保护，兼容默认软件写保护使能其他型号flash
* Input:
* Output:
* Return:
*******************************************************************************/
void SPIFlashSoftWpInit(void)
{
    UINT8 ucTmp;

    SPIFlash_WP(TRUE);
    DBG_FLOW("\nWpInit 0");
    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_RDSR);
    ucTmp = SPI_ReadData();           // 读取flash状态寄存器的值
    SPI_SLVEL0 = 1;
    DBG_FLOW("\n RDSR1=%02x",ucTmp);
    ucTmp &= 0x83;                    // 清除软件写保护，bit4~bit2(BP2~BP0)
    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_WRSR);          // 写flash状态寄存器
    SPI_WriteData(ucTmp);
    
    SPI_SLVEL0 = 1;                   // 禁止芯片操作
    DBG_FLOW("\nWpInit 3");
    while (SPIFlash_Busy());
    
    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_RDSR);
    ucTmp = SPI_ReadData();           // 读取flash状态寄存器的值
    SPI_SLVEL0 = 1;
    DBG_FLOW("\n RDSR11=%02x",ucTmp);
    
}
/**************************************************/
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

    return (flashID + ((UINT32)manuID<<16));
}
/**************************************************/
void SPIFlashQUAD_EN(UINT8 qe)
{
    UINT8 ucTmp,ucTmp2;

     SPIFlash_WP(TRUE);
    
    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_RDSR);
    ucTmp = SPI_ReadData();           // 读取flash状态寄存器的值
    SPI_SLVEL0 = 1;
    
    ucTmp &= 0x83;                    // 清除软件写保护，bit4~bit2(BP2~BP0)

    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_RDSR2);
    ucTmp2 = SPI_ReadData();           // 读取flash状态寄存器的值
    SPI_SLVEL0 = 1;
    
    DBG_FLOW("\n 0 RDSR1=%02x",ucTmp);
    DBG_FLOW("\n 0 RDSR2=%02x",ucTmp2);
    ucTmp2 &= ~0x02;
    ucTmp2 |= (qe<<1);
    
   
    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_WRSR);          // 写flash状态寄存器
    SPI_WriteData(ucTmp);
    SPI_WriteData(ucTmp2);
    SPI_SLVEL0 = 1;                   // 禁止芯片操作   
    
    while (SPIFlash_Busy());

    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_RDSR2);
    ucTmp2 = SPI_ReadData();           // 读取flash状态寄存器的值
    SPI_SLVEL0 = 1;
    
    DBG_FLOW("\n 1 QUAD=%02x",ucTmp2);
    
   
}
/**************************************************/
void SPIFlashQUAD_EN2(UINT8 qe)
{
    UINT8 ucTmp,ucTmp2;

     SPIFlash_WP(TRUE);
    
    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_RDSR);
    ucTmp = SPI_ReadData();           // 读取flash状态寄存器的值
    SPI_SLVEL0 = 1;
    
    ucTmp &= 0x83;                    // 清除软件写保护，bit4~bit2(BP2~BP0)


    
    DBG_FLOW("\n 0 RDSR1=%02x",ucTmp);

    ucTmp &= ~(1<<6);
    ucTmp |= (qe<<6);
    
   
    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_WRSR);          // 写flash状态寄存器
    SPI_WriteData(ucTmp);

    SPI_SLVEL0 = 1;                   // 禁止芯片操作   
    
    while (SPIFlash_Busy());

    SPI_SLVEL0 = 0;
    SPI_WriteData(CMD_RDSR);
    ucTmp2 = SPI_ReadData();           // 读取flash状态寄存器的值
    SPI_SLVEL0 = 1;
    
    DBG_FLOW("\n 1 QUAD=%02x",ucTmp2);
    
   
}
/******************************************************************************
*
* Name: SPIFLASH_Read_ID()
* Brief: 读Flash ID 来判断FLASH型号是5003还是WB
* Input:
* Output:
* Return:
*******************************************************************************/

BOOLEAN SPIFLASHRead_ID(void)
{
    UINT8 ucId;
    SPI_SLVEL0 = 0;                     // 使能芯片操作
    SPI_WriteData(CMD_RD_JEDEC_ID);     // 写读状态命令
    ucId=SPI_ReadData();                   //读三笔:manuID,Device ID

    SPI_SLVEL0 = 1;                     // 禁止芯片操作

    DBG_MODE("\nucId=%x",ucId);
//  DBG_BOOT("@:%02x %02x %02x ",pBuf[0],pBuf[1],pBuf[2]); 
    if (ucId == 0 || ucId == 0xFF)   //读出ID为全0或全F，说明是FT5003
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }

   
}

/*******************************************************************************
* Name: test_flash_to_pram48kb
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/

 void test_flash_to_pram48kb(void)
 {
 
    /********FastRead*******************/
    SPIFlash_FastRead(0x0000,PRAM2_PTR8(0),48UL*1024UL);
    DelayMs(100);    
    DBG_MODE("\n spi DualRead 70k \n");
    

    /********DualRead*******************/
    SPIFlash_DualRead(0x0000,PRAM2_PTR8(0),48UL*1024UL);
    DelayMs(100);
    DBG_MODE("\n spi DualRead 70k  end\n");
    
    
    /********QuadRead*******************/     
    SPIFlashQUAD_EN(1);
    SPIFlash_QuadRead(0x0000,PRAM2_PTR8(0),48UL*1024UL); 
    SPIFlashQUAD_EN(0);
    DBG_MODE("\n spi QuadRead 70k END \n");

}
/*******************************************************************************
* Name: test_readwrite_1k_flash
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void test_readwrite_1k_flash(UINT8 temp,UINT8 *buf1,UINT8 *buf2)
{
    UINT16 i,j;
    #if 1
    /*********EraseSector*****************/
    SPIFlash_EraseSector(0);      //Erase 第一扇区，只有先擦除后才能写入
    DelayMs(1000);
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
    DBG_MODE("\n\rspi flash Test is end\n");
    /********WritePage*******************/
    SPIFlash_WritePage(0,buf1,SPI_FLASH_LEN);
    DelayMs(1000);
    #endif
    
    /********FastRead*******************/
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
    DelayMs(100);
    
    DBG_MODE("\n spi DualRead 1k \n");

    /********DualRead*******************/     
    SPIFlash_DualRead(0x0000,PRAM2_PTR8(0),256);// 1UL*1024UL);

    
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (PRAM2_ADDR8(i) != ((i+temp)&0xff))
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
    DelayMs(100);


    /********QuadRead*******************/  
    SPIFlashQUAD_EN(1);
    SPIFlash_QuadRead(0x0000,PRAM2_PTR8(0),256);// 1UL*1024UL);
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (PRAM2_ADDR8(i) != ((i+temp)&0xff))
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
}
/*******************************************************************************
* Name: test_readwirte_flash_to_dram
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
#define     SECTOR_N    ((UINT16)1)

void test_readwirte_flash_to_dram(UINT8 *buf1,UINT8 *buf2)
{
   UINT16 i,j,k=1,ucTmp;
    UINT8    arr[16]={0x12,0x45,0x67,0x89,0xAB,0x24,0x79,\
        0x68,0x86,0x69,0x6A,0XA7,0xB1,0x56,0x76,0x81};
   #if 0
   /*********EraseSector*****************/
    SPIFlash_EraseSector(SECTOR_N);      //Erase 第一扇区，只有先擦除后才能写入
    DelayMs(1500);
    DBG_SPI("\n\rErase is OK");
    SPIFlash_FastRead(SECTOR_N*SECTOR_SIZE,buf2,SPI_FLASH_LEN);
    
    
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (i%16 == 0)
        {
            DBG_SPI("\n");
        }
        DBG_SPI("%02x ",buf2[i]);
    }
    DBG_MODE("\n\rspi flash Test is end\n");

   
    /********WritePage*******************/  
    SPIFlash_WritePage(SECTOR_N*SECTOR_SIZE,buf1,SPI_FLASH_LEN);
    DelayMs(1000);
   #endif   
#if 0
    DBG_SPI("\n SPI1CON1=%02x ",SPI1CON);
    DBG_SPI("\n SPI1CON2=%02x ",SPI1CON2);
    DBG_SPI("\n SPI1CON3=%02x ",SPI1CON3);
    DBG_SPI("\n SPI1CON4=%02x ",SPI1CON4);
    DBG_SPI("\n P1MOD=%02x ",P1MOD);
    DBG_SPI("\n P1SEL=%02x ",P1SEL);
    DBG_SPI("\n P1DIR=%02x ",P1DIR);
#endif  
#if 1

    

 
    /********FastRead*******************/ 
    DBG_SPI("\n\rSPI read 32 bytes from address 0:\n");
    DelayMs(1000);
    SPIFlash_FastRead(SECTOR_N*SECTOR_SIZE,buf2,SPI_FLASH_LEN);

    
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (buf2[i] != i)//arr[i%16] )
        {
            DBG_SPI("\nerr0\n");
            HOLD;
        }
        if (i%16 == 0)
        {
            DBG_SPI("\n");
        }
        DBG_SPI("%02x ",buf2[i]);
    }
    DBG_MODE("\n\rspi flash Test is end\n");
   #endif  
 

    

   /********DualRead*******************/
   SPIFlash_DualRead(SECTOR_N*SECTOR_SIZE,buf2,SPI_FLASH_LEN);
   #if 0
    for (j = 0; j < SPI_FLASH_LEN; j+=k)
    {
        SPIFlash_DualRead(SECTOR_N*SECTOR_SIZE+j,buf2+j,k);
    }
  #endif
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (buf2[i] != i)//arr[i%16] )
        {
            DBG_SPI("\nerr1\n");
            HOLD;
        }
        if (i%16 == 0)
        {
            DBG_SPI("\n");
        }
        DBG_SPI("%02x ",buf2[i]);
    }
    
    DBG_MODE("\n\rspi DUAL Test is end\n");






 //       while(1)
        {
#if 1 

   
    /********QuadRead*******************/  
    SPIFlashQUAD_EN(1);    
    SPIFlash_QuadRead(SECTOR_N*SECTOR_SIZE,buf2,SPI_FLASH_LEN);
    SPIFlashQUAD_EN(0);

    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        if (buf2[i] != i)
        {
            DBG_SPI("\nerr2\n");
            HOLD;
        }
        if (i%16 == 0)
        {
            DBG_SPI("\n");
        }
        DBG_SPI("%02x ",buf2[i]);
    }
    DBG_MODE("\n\rspi Quad Test is end\n");


#endif
   }


}
/*******************************************************************************
* Name: Test_SPI_Flash
* Brief:
* Input:
* Output:
* Return:
*******************************************************************************/
void Test_SPI_Flash()
{
    UINT16 i,j;
    UINT8  XRAM buf1[SPI_FLASH_LEN];
    UINT8  XRAM buf2[SPI_FLASH_LEN];

    UINT8 
    ARR[16]={0x12,0x45,0x67,0x89,0xAB,0x24,0x79,0x68,0x86,0x69,0x6A,0XA7,0xB1,0x56,0x76,0x81};
    BOOLEAN bIsWb;
    UINT8 temp=0x66;//0x5A;//69;
    

    SPI_Init();
    
    Flash_WP =1;
    Flash_HOLD = 1;   //默认复位，这里释放复位，flash开始工作
    //EXTMCKEN  = 0;

    while(0)
    {
        SPI_SLVEL0 = 0;
        DBG_SPI("\n SPI1CON2 L=%02x ",SPI1CON2);
        SPI_RW_Byte(0x55);
        SPI_SLVEL0 = 1;
        DelayUs(1000);
        
        DBG_SPI("\n SPI1CON2 H=%02x ",SPI1CON2);

    }


    SPIFlash_ReadID();
    SPIFlashSoftWpInit();  //wb
    
    DBG_MODE("\nspi flash Test is start");
    for (i = 0; i < SPI_FLASH_LEN; i++)
    {
        
        //buf1[i] = i%0X10 + 0x04;
        buf1[i] = i;//c3;//i + 0x6A;//0x67;//0x73;
        //buf1[i] =ARR[i%16];
/*
        if((i%2 )==0)
        {
            buf1[i] =0X00;  

        }
        else
        {
            buf1[i] =0XBB ;
        }*/
            
    }
        
    DBG_SPI("\nSPI1CON == %02x",SPI1CON);    
   

#if 1
    while(1)
    {
        test_readwirte_flash_to_dram(buf1,buf2);
    }

#else

    test_readwrite_1k_flash(temp,buf1,buf2);

    #if 0 
    test_flash_to_pram48kb();
    #endif

#endif

}
#endif

