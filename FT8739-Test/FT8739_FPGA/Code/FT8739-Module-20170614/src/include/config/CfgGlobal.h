/*******************************************************************************
* Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: CfgGlobal.h
*
*    Author: xinkunpeng
*
*   Created: 2014-04-18
*
*  Abstract:
*
* Reference: Transplant from FT5422 by xinkunpeng
*
*   Version: 0.2
*
*******************************************************************************/
#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/

#define _SPI_FLASH_EN                   1      // spi flash--必须开
#define _LCD_RELOAD_EN                  1      // APP从Flash导入LCD_config

#define TEST_MODE                       1

#if TEST_MODE
#define _TEST_SFR_EN                    0       /* test the SFR read and write */
#define _TEST_DRAM_EN                   0       /* test dram read and write */
#define _TEST_PROM_EN                   0       /* test prom read only */   
#define _TEST_ARAM_EN                   0       /* test asmram read and write */
#define _TEST_XSI_REG_EN                0       /* XSI寄存器读写测试 */
#define _TEST_SPI0_REG_EN               0       /* SPI0寄存器读写测试 */ 
#define _TEST_XBUS_REG_EN               0       /* XBUS寄存器读写测试 */
#define _TEST_ASM_REG_EN                0       /* ASM寄存器读写测试 */
#define _TEST_CAL_REG_EN                0       /* CAL寄存器读写测试 */
#define _TEST_AFE_REG_EN                0       /* AFE寄存器读写测试 */
#define _TEST_LCD_REG_EN                0       /* LCD寄存器读写测试 */
#define _TEST_SPI_EN                    0       /* test SPI read  */
#define _TEST_LED_EN                    0       /* test the led */ 
#define _TEST_I2C_EN                    0       /* test I2C read and clk */
#define _TEST_AFE_RAM_EN                0       /* test the AFE ram buffer,测试太耗时间最好单独进行测试 */
#else
#define _TEST_SFR_EN                    1
#define _TEST_DRAM_EN                   1
#define _TEST_PROM_EN                   1
#define _TEST_ARAM_EN                   1
#define _TEST_SPI0_REG_EN               1
#define _TEST_XSI_REG_EN                1
#define _TEST_ASM_REG_EN                1      
#define _TEST_XBUS_REG_EN               1
#define _TEST_CAL_REG_EN                1
#define _TEST_AFE_REG_EN                1
#define _TEST_LCD_REG_EN                0
#define _TEST_SPI_EN                    1
#define _TEST_LED_EN                    1
#define _TEST_I2C_EN                    1
#define _TEST_AFE_RAM_EN                1
#endif

#define _TEST_RST_EN                    0     /* Reset测试*/
#define _TEST_UART_EN                   0     /* UART测试*/
#define _TEST_SOFT_RST_EN               0     /* 软件复位测试*/
#define _TEST_WDT_EN                    0     /* WDT单独进行测试 */
#define _TEST_RTC_EN                    0     /* 和CNT中断冲突，单独进行测试 */
#define _TEST_CNT_EN                    0     /* 和RTC中断冲突，单独进行测试 */
#define _TEST_GPIO_EN                   0     /* gpio需要判断其input output以及高低电平切换的状态，需分别单独进行测试 */
#define _TEST_TIMER_EN                  0     /* Timer单独进行测试 */ 
#define _TEST_GPIO_WK_EN                0     /* int0中断唤醒源过多,单独进行测试 */
#define _TEST_I2C_WK_EN                 0     /* 和I2C中断冲突，单独进行测试 */ 
#define _TEST_INT_NEST_EN               0     /* 中断嵌套测试,单独进行测试  */
#define _TEST_XSI_EN                    0     /* XSI读写拷机测试，单独测试 */
#define _TEST_CAL_EN                    1     /* CAL模块,测试模块较多,单独进行测试 */
#define _TEST_ROMBOOT_EN                0     /* romboot test使用所需相关测试bin */
#define _TEST_XBUS_EN                   0     /* XBUS读写测试*/
#define _TEST_ROMECC_EN                 0     /* 计算ecc和prom membist的结果比较*/
#define _TEST_SPI0_EN                   0     /* test SPI0   */
#define _TEST_SPI0_DMA_EN               0     /* test SPI0_dma */
#define _TEST_SPI0_WK_EN                0     /* 和SPI0,I2C中断冲突，单独进行测试 */   
#define _TEST_DEBUGOUT_EN               0     /* 测试内部信号，单独进行测试*/
#define _TEST_AFE_EN                    0
/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "Typedef.h"
#include "FT8836.h"
#include "FT8836_Reg.h"
#include "Drv_mcu.h"
#include "Drv_XSI.h"
#include "Drv_XBUS.h"
#include "uart.h"

#include "Test_GPIO.h"
#include "Test_WDT.h"
#include "Test_RTC.h"
#include "Test_timer.h"
#include "Test_Counter.h"
#include "Test_Prom.h"
#include "Test_Dram.h"
#include "Test_Aram.h"
#include "Test_SFR.h"
#include "Test_Reg.h"
#include "Test_I2C.h"
#include "Test_i2c_wakeup.h"
#include "Test_gpio_wakeup.h"
#include "Test_int_nest.h"
#include "Test_SPI.h"
#include "Test_CAL.h"
#include "Test_romboot.h"
#include "Test_Afe.h"
#include "Test_LED.h"
#include "Test_Xbus.h"
#include "Test_RomEcc.h"
#include "Test_Uart.h"
#include "Test_SOFT_RST.h"
#include "Test_spi0.h"
#include "Test_spi0_wakeup.h"
#include "Test_SPI0_dma.h"
#include "checksum.h"
#include "Test_DebugOut.h"
#include "Test_Reset.h"
/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/

/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/

#endif //GLOBAL_CONFIG_H
