/*******************************************************************************
 * Copyright (C) 2012-2013, FocalTech Systems (R)，All Rights Reserved.
 *
 * File Name: FT8836.h
 *
 *    Author: 
 *
 *   Created: 2016-07-11
 *
 *  Abstract: 1. In this file, sfrs(special function registers) and their bits
 *            are defined for chip ft8626 based on platform C251.
 *
 *            2. Please note that there are some differences in the way the
 *            instructions address bits between the two architectures MCS251 and
 *            MCS51. The MCS251 does not have bit addresses as MCS51 does. A bit
 *            can be addressed by name or by its location within a certain
 *            register, but not by a bit address.
 *
 *            Table: Addressing Modes for Bit Instructions
 *            -------------------------------------------------------------------
 *            Architecture Variants Bit Address Memory/SFR Address Comments
 *            -------------------------------------------------------------------
 *            MCS251       Memory -- NA ------- 20H.0-7FH.7        does not have
 *            (bit)        SFR ----- NA ------- All defined SFRs   bit addresses
 *            -------------------------------------------------------------------
 *            MCS 51       Memory -- 00H-7FH -- 20H.0-7FH.7        not all SFRs
 *            (bit51)      SFR ----- 80H-F8H -- XXH.0-XXH.7, where have bit
 *                                              XX = 80,88,90,98,  addresses.
 *                                              ..., F0, F8.
 *            -------------------------------------------------------------------
 *
 *            3. This file is only used by library and driver of project ft5412.
 *
 * Reference: 1. Intel 8xc251sx User's Manual (8xc251sx_um.pdf)
 *            2. Keil C251 help document
 *
 *******************************************************************************/
#ifndef __FT8836_H__
#define __FT8836_H__

/* Conditional Compiler Options */

/* Conditional Compiler Options */
/*******************************************************************************
 * 1.Included files
 *******************************************************************************/

/*******************************************************************************
 * 2.Global constant and macro definitions using #define
 *******************************************************************************/
/******************************************************************************/
/* byte Registers */

/*80-87*/
SFR P0BUF           = 0x80;   /*PoBuf*/
SFR SP              = 0x81; 
SFR DPL             = 0x82;
SFR DPH             = 0x83;
SFR DPXL            = 0x84;
SFR PCON            = 0x87;

/*88-8F*/
SFR TCON            = 0x88;
SFR TMOD            = 0x89;
SFR TL0             = 0x8A;   /* 设定计数器时间低8位，计数时间为TL0[7:0]X4us,最大值不能超过1ms也就是说最大值为8’hF9,大于此值时将强制为8’hF9. */
SFR TL1             = 0x8B;   /* 设定计数器时间低8位，计数时间为TL1[7:0]X4us */
SFR TH0             = 0x8C;   /* 设定计数器时间高8位，计数时间为TH0[7:0]X1ms,TH0[7]必须为0，所以最长时间为127ms */
SFR TH1             = 0x8D;   /* 设定计数器时间高8位，计数时间为TH1[7:0]X1ms,TH1[7]必须为0，所以最长时间为127ms */

/*90-97*/
SFR I2CCON          = 0x90;
SFR I2CBUF          = 0x91;
SFR I2CADDR         = 0x92;
SFR I2CSTOP         = 0x93;
SFR P1BUF           = 0x94;   /*P1Buf*/
SFR I2CSEL          = 0x95;
SFR MMCON           = 0x97;

/*98-9F*/
SFR SYSCON          = 0x98;
SFR WDTCON          = 0x99;
SFR WDTREL          = 0x9A;
SFR TDIV            = 0x9B;
SFR RTCIVL          = 0x9C; /*rtc计数终止低8位*/      
SFR RTCIVH          = 0x9D; /*rtc计数终止高8位*/
SFR RTCCON          = 0x9E;
SFR RTCSLN          = 0x9F; /*rtc 时间片个数*/

/*A0-A7*/
SFR ANACON8         = 0xA0;
SFR SPI0CON         = 0xA2;
SFR SPI0CON2        = 0xA3;
SFR SPI0BUF         = 0xA4;
SFR SPI0CON3        = 0xA5;
SFR SPI0CON4        = 0xA6; 
SFR SPI0CON5        = 0xA7;

/*A8-AF*/
SFR IEN0            = 0xA8;
SFR UARTCON         = 0xA9;
SFR UARTBUF         = 0xAA;
SFR UART_RELL       = 0xAB;
SFR P0DIR           = 0xAC;   /*P0口方向配置，1:输出, 0:输入*/
SFR P1DIR           = 0xAD;   /*P1口方向配置，1:输出, 0:输入*/
SFR UART_RELH       = 0xAE;
SFR UART_SDA        = 0xAF;

/*B0-B7*/
SFR ANACON9         = 0xB0;
SFR SPI1CON3        = 0xB1;
SFR SPI1CON4        = 0xB2;
SFR SPI1CON         = 0xB3;
SFR SPI1CON2        = 0xB4;
SFR SPI1BUF         = 0xB5;
SFR RTCCON1         = 0xB6;
SFR IPH0            = 0xB7; 

/*B8-BF*/
SFR IPL0            = 0xB8;
SFR CNTCON          = 0xB9;
SFR CNTIVL          = 0xBA;  /*CNT计数终止低8位*/
SFR CNTIVM          = 0xBB;  /*CNT计数终止中间8位*/
SFR CNTIVH          = 0xBC;  /*CNT计数终止高8位*/
SFR FT_EN_REG       = 0xBD;  /*lcd otp to tp soc*/
SFR SPH             = 0xBE;
SFR CGUCON8         = 0xBF;

/*C0-C7*/
SFR AIF            = 0xC0;
SFR ANACON1        = 0xC1;
SFR ANACON2        = 0xC2;
SFR ANACON3        = 0xC3;
SFR ANACON4        = 0xC4;
SFR ANACON5        = 0xC5;
SFR ANACON6        = 0xC6;
SFR ANACON7        = 0xC7;

/*C8-CF*/
SFR CGUCON1        = 0xC8;
SFR CGUCON0        = 0xC9;
SFR CGUCON2        = 0xCA;
SFR CGUCON3        = 0xCB;
SFR CGUCON4        = 0xCC;
SFR CGUCON5        = 0xCD;
SFR CGUCON6        = 0xCE;
SFR CGUCON7        = 0xCF;

/* D1-D7 */
SFR MEMBIST_EN1         = 0xD2;
SFR MEMBIST_EN2         = 0xD3;
SFR MEMBIST_FINISH1     = 0xD4;
SFR MEMBIST_FINISH2     = 0xD5;
SFR MEMBIST_FAIL1       = 0xD6;
SFR MEMBIST_FAIL2       = 0xD7;

/* D8-DF */
SFR MEMBIST_ERRMAP1     = 0xD8;
SFR MEMBIST_ERRMAP2     = 0xD9;
SFR DSV_CON             = 0xDA;
SFR MEMBIST_ROMCRC0     = 0xDB;
SFR MEMBIST_ROMCRC1     = 0xDC; 
SFR MEMBIST_ROMCRC2     = 0xDD;
SFR MEMBIST_ROMCRC3     = 0xDE;
SFR IEN1                = 0xDF;

/*E0-E7*/
SFR TESTCON0            = 0xE1;
SFR TESTCON1            = 0xE2;
SFR TESTCON2            = 0xE3;
SFR TESTCON3            = 0xE4;
SFR IWKSTA              = 0xE5;
SFR POR_STA             = 0xE6; /*POR复位检查*/
SFR RST_STA             = 0xE7; /*Pin reset复位检查*/


/*E8-EF*/
SFR AIE                 = 0xE8;
SFR SFTRST              = 0xE9;
SFR ANACON              = 0xEA;
SFR P0MOD               = 0xEB; /*0:P0 use as gpio;1:po use as function define*/
SFR P0SEL               = 0xEC; /*0:P0 as OD port; 1:P0 as PUSH-PULL port*/
SFR P1MOD               = 0xED; /*0:P1 use as gpio;1:p1 use as function define*/
SFR P1SEL               = 0xEE; /*0:P1 as OD port; 1:P1 as PUSH-PULL port*/
SFR XDP_STA             = 0xEF;

/*F0-F7*/
SFR CNT_MASK            = 0xF1; /* 3'b00:porrst_cnt;3'b01:wdtrst_cnt;3'h02:extrst_cnt;3'h03:lcdrst_cnt;3'b04:esd_cnt;3'h05:lvd_cnt*/
SFR CNT_STA             = 0xF2; /* 根据cnt_mask的值，独处不同的cnt值*/
SFR SSCG_CON0           = 0xF5;
SFR SSCG_CON1           = 0xF6; /* sscg_step:sscg increase/decrease period(500us/step). sscg trim code will increase in every(500ns*(step+1))*/
SFR AIPH                = 0xF7;

/*F8-FF*/
SFR AIPL                = 0xF8;
SFR I2C_CMD0            = 0xF9; /* i2c hid command byte1 */
SFR I2C_CMD1            = 0xFA; /* i2c hid command byte2 */
SFR I2C_CMD2            = 0xFB; /* i2c hid command byte3 */
SFR I2C_CMD3            = 0xFC; /* i2c hid command byte4 */
SFR I2C_STATE           = 0xFD; /* i2C hid 中断标志寄存器 */
SFR LED_EN              = 0xFE; /* 4个LED灯使能; bit3~bit0有效,每bit分别对应一个LED使能 */
SFR LED_H_NUM           = 0xFF; /* led PWM波高电平持续的周期数，0~63可配，0代表1个32k周期高电平，63代表64个32k周期高电平，即一直为高；*/


/******************************************************************************/
/* bit Registers */

/*SSCG_CON0*/
/*bit5-4  sscg_amp */   /*sscg amplitude. Control the output sequence of DA_TRIM[2:0]. Clock stable time between each trim code is located in range 100ns-200ns*/
SBIT SSCG_SCAN_EN           = SSCG_CON0^1; /*0:stop sscg when scan 1:contiune sscg when scan(sync with scan)*/
SBIT SSCG_EN                = SSCG_CON0^0; /*0:disable sscg  1:enable sscg*/

/*SPI0CON*/
SBIT SPI0RX_OVF_FLAG        = SPI0CON^6;  /*rx_reg_overflow标志位，spi0接收完数据rx_reg为满时，硬件置1*/
SBIT SPI0TX_UNF_FLAG        = SPI0CON^5;  /*tx_reg_underflow标志位，spi0发送数据时rx_reg为空时，硬件置1*/
SBIT SPI0_START             = SPI0CON^4;  /*SPI0的slvel下降沿来时为高电平，软件清零*/
SBIT SPI0_STOP              = SPI0CON^3;  /*SPI0的slvel上升沿来时为高电平，软件清零*/
SBIT DMA_END_FLAG           = SPI0CON^2;  /*DMA操作结束中断请求标志位，软件清零*/
SBIT SPI0RI                 = SPI0CON^1;  /*接收完毕中断请求标志位*/
SBIT SPI0TI                 = SPI0CON^0;  /*发送请求中断标志位*/

/*SPI0CON2*/
SBIT SPI0TX_AUTO_CLR        = SPI0CON2^7; /*是否自动清除ti中断标志位；0:需要软件清；1:软件在写tx_reg时硬件自动清*/
SBIT SPI0RX_AUTO_CLR        = SPI0CON2^6; /*是否自动清除ri中断标志位. 0:需要软件清; 1:软件在读rx_reg时硬件自动清*/
SBIT SPI0_EDGE_SEL          = SPI0CON2^5; /*0:sck上升沿输出;1:sck下降沿输出*/
SBIT SPI0_BUSY              = SPI0CON2^4; /*0:低电平状态，只能读不能写;1:SPI0正在激活状态*/
SBIT SPI0_STOP_EI           = SPI0CON2^3; /*spi_stop中断请求信号使能*/
SBIT DMA_END_EI             = SPI0CON2^2; /*DMA操作结束中断请求使能*/
SBIT SPI0RI_EN              = SPI0CON2^1; /*0:禁止产生接收中断请求信号;1:允许产生接收中断请求信号*/
SBIT SPI0TI_EN              = SPI0CON2^0; /*0:禁止产生发送中断请求信号;1:允许产生发送中断请求信号*/

/*SPI0CON3*/
SBIT SPI0_WKEN              = SPI0CON3^7; /*spi wake up功能使能位.0:disable;1:enable*/
SBIT SPI0_RI_PULSE_SEL      = SPI0CON3^4; /*0:rx_reg load at ti_ri_pulse falling edg;1:rx_reg load at ri_pulse rising edge*/
//SBIT SPI0_CLR_NUM           = SPI0CON3^4; /*write 1 to clear byte num*/
/*spi0con3[3:0] dummy_byte_num cs下降沿开始插入的dummy byte数*/

/*SPI0CON4*/
/*SPI0CON4[7:6] byte_num_rd_sel  byte_num读出选择.2'b00:byte_num_h; 2'b01:byte_num_m; 2'b10:byte_num_l */
/*SPI0CON4[5:0] byte_num_rd byte_num 6bit,由byte_num决定*/

/*SPI0CON5*/
SBIT SPI0RX_OVF_CLR         = SPI0CON5^6;  /*写1清除rx_reg_overflow标志位*/
SBIT SPI0TX_UNF_CLR         = SPI0CON5^5;  /*写1清除tx_reg_underflow标志位*/
SBIT SPI0_START_CLR         = SPI0CON5^4;  /*写1清除spi0 start*/
SBIT SPI0_STOP_CLR          = SPI0CON5^3;  /*写1清除spi0 stop*/
SBIT DMA_END_CLR            = SPI0CON5^2;  /*写1清除dma end flag*/
SBIT SPI0RI_CLR             = SPI0CON5^1;  /*写1清除SPI0RT*/
SBIT SPI0TI_CLR             = SPI0CON5^0;  /*写1清除SPI0TI*/


/*SPICLKDIV: 000:4分频;001:6分频;010:8分频;011:12分频;100:16分频;101:18分频;110:20分频;111:24分频*/
/*SPI1CON*/
SBIT SPI1TI                  = SPI1CON^7;  /*发送请求中断标志位*/
SBIT SPI1RI                  = SPI1CON^6;  /*接收完毕中断请求标志位*/
SBIT SPI1CKM                 = SPI1CON^5;  /*SPI1CLKDIV中间位*/
SBIT SPI1CKL                 = SPI1CON^4;  /*SPI1CLKDIV低位*/
SBIT SPI1PH                  = SPI1CON^3;  /*0:直接发送数据,缓存半个cycle接收数据;1:直接接收数据,缓存半个cycle发送数据*/
SBIT SPI1PO                  = SPI1CON^2;  /*0:low idle; 1:high idle*/
SBIT SPI1MAS                 = SPI1CON^1;  /*0:slave mode; 1:master mode*/ 
SBIT SPI1_SLVSLELEN          = SPI1CON^0;  /*0:master模式下的slvselo受内部启动控制;1:master模式下slvselo受SPI1CON2[2]控制*/

/*SPI1CON2*/
SBIT SPI1TX_AUTO_CLR         = SPI1CON2^7; /*0:软件自动清ti中断标志位;1:软件在读rx reg时硬件自清*/
SBIT SPI1RX_AUTO_CLR         = SPI1CON2^6; /*0:软件自动清ri中断标志位;1:软件在读tx reg时硬件自清*/
SBIT SPI1_BUSY               = SPI1CON2^5; /*0:低电平状态,只能读;1:SPI1正处于active*/ 
SBIT SPI1_STOP               = SPI1CON2^4; 
SBIT SPI1_START              = SPI1CON2^3;
SBIT SPI1SLVELO              = SPI1CON2^2; /*当SPI1CON[0]为1时,master状态下该位直接输出SPI1的slvsel；当SPI1CON[0]为0时，该位无效*/
SBIT SPI1RI_EN               = SPI1CON2^1; /*0:禁止产生接收中断请求信号;1:允许产生接收中断请求信号*/
SBIT SPI1TI_EN               = SPI1CON2^0; /*0:禁止产生接收中断请求信号;1:允许产生接收中断请求信号*/

/*SPI1CON3*/
SBIT SPI1MODE_SELH           = SPI1CON3^7; /*1:用IO0-IO2传输数据;0:根据SPI1CON3[6]状态决定*/
SBIT SPI1MODE_SELL           = SPI1CON3^6; /*若SPI1MODE_SELH为0,则0:用IO0传输;1:用IO0,IO1传输*/
SBIT SPI1_SW_IO_ENH          = SPI1CON3^5; /*IO0,IO1方向控制位. 0:standard spi IO setting;1:控制IO0,IO1方向自动切换,切换时间参reg配置spi_dat_opn_num*/
SBIT SPI1_SW_IO_ENL          = SPI1CON3^4; /*IO2,IO3方向控制位. 0:standard spi IO setting;1:控制IO2,IO3方向自动切换,切换时间参reg配置spi_dat_opn_num*/
SBIT SW_1BYTE_LATER          = SPI1CON3^2; /*dual/quad spi软件切换时间.0:立即切换;1:在下个byte数据传输结束以后的第一个shift_out_sck_edg之前完成切换*/
SBIT SPI1_SW_DIR             = SPI1CON3^1; /*dual/quad spi时软件切换io的方向.0:输出;1:输入*/
SBIT SPI1_SW_EN              = SPI1CON3^0; /*dual/quad spi 软件io方向切换使能，写1有效.硬件在切换之后自清*/

/*SPI1CON4*/
SBIT SPI1IOSW_CKDLY_EN      = SPI1CON4^4; /*传输IO切换方向时 0:切换方向不延时;1:切换方向延长2个clk cycle*/
SBIT SPI1_CURR_MODE         = SPI1CON4^3; /*spi master/slave mode状态位.1:目前为master mode.0:目前未slave mode */
SBIT SPI1CKH                = SPI1CON4^2; /*SPI1CLKDIV高位*/
/*spi1con[1:0] sample_phase_sel*/ /*采样时钟延迟选择. 00:无延迟;01:延迟1个clk cycle; 10:延迟2个clk cycle; 11:延迟3个clk cycle*/


/*UARTCON*/
SBIT UART_MODE              = UARTCON^7; /*uart模式设定. 0:9bit模式; 1:8bit模式*/
SBIT UART_SM21              = UARTCON^5; /*1:在9bit一对多通信模式下;0:在9bit点对点模式*/  
SBIT UART_REN1              = UARTCON^4; /*接收是能控制位.1:允许接收;0:禁止接收*/
SBIT UART_TB81              = UARTCON^3; /*在9bit模式下，the content of发送的第9bit*/
SBIT UART_RB81              = UARTCON^2;   
SBIT UART_TI                = UARTCON^1;
SBIT UART_RI                = UARTCON^0;

/* RTCCON */
SBIT RTC_START              = RTCCON^7;
SBIT RTC_INT_EN_ASM         = RTCCON^6;   /* 产生中断给asm使能.1:打开;0:关闭 */
SBIT RTC_START_STA          = RTCCON^5;   /* RTC启动状态.1:rtc启动成功或空闲;0:rtc正在启动或正在复位*/
SBIT RTC_CLR                = RTCCON^4;
SBIT RTC_INT_EN_CPU         = RTCCON^2;   /* 产生中断给cpu使能.1:打开;0:关闭 */
SBIT RTC_AUTO_MODE          = RTCCON^1;   /* rtc不需要做clr，自动重复计数*/
SBIT RTC_WP                 = RTCCON^0;

/* RTCCON1 */
//[2:1] LCD_SRC_SEL lcd start sourc选择. 2'b00:vstart;2'b01:vmdi;2'b10:vend;2'b11:vblank
SBIT LCD_SRC_SEL_H          = RTCCON1^2;
SBIT LCD_SRC_SEL_L          = RTCCON1^1;
SBIT LCD_START_EN           = RTCCON1^0;   /* lcd vstart/wmid.vend/vblank 启动rtc使能信号 */ 

/*SYSCON*/
SBIT REMAP                  = SYSCON^7;
SBIT ESD_RST_EN             = SYSCON^6;   /* esd发生时需不需要rst系统.1:表示需要rst系统;0:表示不rst系统*/
SBIT BUS_SEL                = SYSCON^5;   /* RO. pad bus_sel */
SBIT WDT                    = SYSCON^4;   /* wdt使能 */
SBIT UART1                  = SYSCON^3;   /* uart1 */
SBIT UART0                  = SYSCON^2;   /* uart0: 2'b01: GPIO6; 2'b10: GPIO7; 2'b11: GPIO1.5; 2'b00: 其他;  */
SBIT LVD_INT_CLR            = SYSCON^1;   /* 写1清除lvd的中断标志,该bit位写1自清 */
SBIT ESD_INT_CLR            = SYSCON^0;   /* 写1清除esd的中断标志,该bit位写1自清 */


/*IWKSTA*/
SBIT GPIO_INT               = IWKSTA^7; /* p0.6 pin脚中断唤醒标志*/
SBIT LCD_ESD_WK_INT         = IWKSTA^6; /* lcd esd wakeup中断唤醒标志 */
SBIT LCD_LVD_WK_INT         = IWKSTA^5; /* lcd lvd wakeup中断唤醒标志 */
SBIT LCD_GPIO_WK_INT        = IWKSTA^4; /* lcd gpio wakeup status */
SBIT LCD_RELOAD_FLASH       = IWKSTA^3; /* LCD initial code reload */
SBIT ASM_MON_INT            = IWKSTA^2; /* asm monitor中断唤醒标志 */
SBIT I2C_MON_INT            = IWKSTA^1; /* i2c monitor中断唤醒标志 */
SBIT RTC_CNT_INT            = IWKSTA^0; /* RTC or CNT中断唤醒标志 */

/*SFTRST*/
SBIT SOFT_RST               = SFTRST^7; /*读:软复位标志*/
SBIT WDT_RST                = SFTRST^6; /*读:wdt复位标志*/
SBIT EXT_RST                = SFTRST^5; /*读:外部复位标志*/
SBIT POR_RST                = SFTRST^4; /*por复位标志*/
SBIT FLASH_HOLD_STA         = SFTRST^3; /*flash hold state*/
SBIT REMAP_RST              = SFTRST^1; /*读:打开remap复位使能*/
/*SFTRST[0] */              /*当全写1是产生复位;全写0是产生remap复位;当读时时软复位标志*/

/* ANACON */
SBIT ARAM_SEL               = ANACON^7;  /* 1: mcu控制aram; 0: afe控制aram */
SBIT LCD_DSTAB_IOLOW        = ANACON^6;  /* lcd dstab发生时,控制TP到LCD DP的信号是否输出为低，从而降低漏电 1: 输出为低，0: 不输出为低 */
SBIT I2C_WK_RST             = ANACON^5;  /* 0:Reset I2C monitor interrupt;1: release*/
SBIT I2C_SF_RST             = ANACON^4;  /* I2C module soft reset */
SBIT XSI_SEL                = ANACON^3;  /* xsi0/xsi1 accessing clock switch select. 0:MCU;1:AFE. */
SBIT AFE_RST                = ANACON^2;  /* afe sub-system soft reset including asm*/
SBIT FlASH_HOLD             = ANACON^1;  /* external SPI flash hold,1:hold state '0';0:hold state '1' */
SBIT GPIO_INT_SEL           = ANACON^0;  /* GPIO Interrupt source selecetion.1:GPIO interrupt is from p0.7;0:GPIO interrupt is from p0.6 */

/* XDP_STATUS*/
SBIT LVD_STA                = XDP_STA^6;  /* R0.lvd的status */
SBIT ESD_FLAG               = XDP_STA^5;  /* RW.esd发生标志.1:表示有发生esd事件;0:表示没有发生esd事件.软件可清除*/
SBIT LVD_FLAG               = XDP_STA^4;  /* RW.lvd发生标志.1:有lvd事件;0:没有lvd事件.软件可清除 */
SBIT ESD_STA                = XDP_STA^3;  /* RO.xdp esd status */
SBIT LVD_VDDI_STA           = XDP_STA^2;  /* RO.lvd_vddi status */
SBIT LVD_AVDD_STA           = XDP_STA^1;  /* RO.lvd_avdd status */
SBIT LVD_AVEE_STA           = XDP_STA^0;  /* RO.lvd_avee status */

/* TEST_CON0 */
SBIT TEST_OUT0_EN           = TESTCON0^7; 
/*TEST_CON0[6:0]*/          /*Test out0 control */

/* TEST_CON1 */
SBIT TEST_OUT1_EN           = TESTCON1^7; 
/*TEST_CON1[6:0]*/          /*Test out1 control */

/* TEST_CON2 */
SBIT TEST_OUT2_EN           = TESTCON2^7; 
/*TEST_CON2[6:0]*/          /*Test out2 control */

/* TEST_CON0 */
SBIT TEST_OUT3_EN           = TESTCON3^7; 
/*TEST_CON3[6:0]*/          /*Test out3 control */

/* DSV_CON */
SBIT UART_INH               = DSV_CON^6;       /* selection of uart rx port*/
SBIT UART_INL               = DSV_CON^5;       /* 2'b00/2'b11:disable uart rxd;2'b01:p0.6;2'b10:p0.7*/
SBIT SPI_REPLACE_STA        = DSV_CON^4;       /* spi1是否替代spi0作为slave的状态位;1:spi1作为slave;0:spi1不作为slave*/
SBIT SPI_REPLACE_SEL        = DSV_CON^3;       /* spi1作为slave的控制，在spi_replace_en=1时起作用.1:spi1替换spi0作为slave;0:spi1不替换spi0 */
SBIT SPI_REPLACE_EN         = DSV_CON^2;       /* spi1作为slave的控制.1:spi1是否为slave受spi_replace_sel控制;*/
SBIT DSV_EN6_STA            = DSV_CON^1;       /* lcd输出的dsv_en6的状态 */
SBIT DSV_EN                 = DSV_CON^0;       /* dsv en reg */

/*FT_EN_REG*/
SBIT PDB                    = FT_EN_REG^6;     /* lcd to tp,当打开批评检测时,检测结果.1:屏破;0:屏没破*/
SBIT PDB_EN                 = FT_EN_REG^5;     /* tp to lcd.1:开启破屏检测 */
SBIT DMA_REQ_INT_MASK       = FT_EN_REG^4;     /* dma_req屏蔽cpu中断使能.1:当dma_req为1时,屏蔽cpu的(除了timer0,timer1)中断*/
SBIT DMA_ACK_INT_MASK       = FT_EN_REG^3;     /* dma_ack屏蔽cpu中断使能.1:当dma_ack为1时,屏蔽cpu的(除了timer0,timer1)中断*/
SBIT TEST_CLK_EN            = FT_EN_REG^2;     /* 时钟测试输出使能,GPIO6输出 */
SBIT XSI_SEL_STA            = FT_EN_REG^1;     /* anacon[3] xsi clk swtich result.1:AFE can control xsi;0:MCU can control xsi*/
SBIT FT_EN                  = FT_EN_REG^0;     /* lcd otp to tp soc */

/* ANACON1 */
SBIT POWERGATING_CTRL       = ANACON1^7; /* 无avdd和avee时,控制afe的sx switch放电.1:取决于dsv_en,dsv_en为1时,不放电.dsv_en为0时,放电.0:不放电 */
/* [6:4] vreftp_sel. vREF_TP voltage selection bits.0:2v; 1:2.5v; 2:3v; 3:3.5v; 4:4v; 5:4.5v; 6:5v; 7:4.5v*/
SBIT VREFTP_BUF_SEL_M       = ANACON1^3; /* vref_tp/vdd5 slew rate control bit,output to xtp.0: no sr control,vref_tp rise quickly.1:with sr control,set 1 for t32clk and then set to 0*/
SBIT VREFTP_BUF_SH_M        = ANACON1^2; /* 采样电压,固定采样电压,输出给xtp.vref_tp/vdd5 sample/hold signal.0:hold; 1:enable*/
SBIT VREFTP_BUF_EN_M        = ANACON1^1; /* 控制输出buf enable,输出给xtp.vref_tp buf enable signal.0:disable;1:enable*/
SBIT VREFTP_SETOP_EN_M      = ANACON1^0; /* vref_tp setting op的enable,输出给xtp.vref_tp volatge setting op enable singal.0:disable;1:enable */

/* ANACON2 */
SBIT REFBG_EN               = ANACON2^7; /* tp的bandgap的enbale.扫描时,一定要打开.afe ref enable signal.0:disable;1:enable */
SBIT VREFTP_BUF_SEL         = ANACON2^6; /* vref_tp/vdd5 slew rate control bit,output to xae_l,xafe_r.0:no sr control,vref_tp rise quickly;1:with sr control,set 1 for 16 t32clk and then set to 0*/
SBIT VREFTP_BUF_SH          = ANACON2^5; /* 采样电压,固定采样电压,输出给xafe_l,xafe_r.vref_tp/vdd5 sample/hold signal.0:hold; 1:enable*/
SBIT VREFTP_BUF_EN          = ANACON2^4; /* 控制输出buf enable,输出给xafe_l,xafe_r.vref_tp buf enable signal.0:disable;1:enable*/
SBIT VREFTP_SETOP_EN        = ANACON2^3; /* vref tp setting op的enable,输出给xafe_l,xafe_r.vref_tp volatge setting op enable singal.0:disable;1:enable */
SBIT VDD5_SETOP_EN          = ANACON2^2; /* vdd5 volatage setting op enable signal.0:disable;1:enable*/
SBIT VDD5_BUF_EN            = ANACON2^1; /* vdd5 buf enable signal.0:disable;1:enable*/
SBIT VDD5_SECTRL            = ANACON2^0; /* vdd5 slew rate control bit.0:no sr control,vref_tp rise quickly.1:with sr control,set 1 for 16 t32clk and the set to 0*/

/* ANACON3 */
SBIT DSV_EN_ALLON           = ANACON3^7; /* dsv_en是否时刻打开.1:时刻打开;0:由上电时序决定*/
SBIT LR_SEL                 = ANACON3^6; /* select p1_af and p2_af from left or right afe controller.1:right;0:left*/
SBIT VCOM_OPT_SEL           = ANACON3^5; /* 用于控制vcom_opt的输出.0:强制输出为vcom.1:lcd term时为vcom,tp term时,为afd*/
SBIT BGP_MASK               = ANACON3^4; /* 用于控制黑屏时lcd的bandgap开关.亮屏时,此开关由lcd控制,黑屏时,由tp控制.dsv模式下,动态切换,用于节省功耗.1:开启lcd的bandgap,tp扫描时,需要开启此开关.0:关闭lcd的bandgap,tp不扫描时,可以关闭此开关*/
SBIT LVD_MASK               = ANACON3^3; /* 用于控制是否开启avdd/avee的掉电侦测电路.dsv模式下,dsv_en使能时,可开启,dsv_en不使能,需要关闭avdd/avee的掉电侦测电路,以放误触发lvd侦测电路.1:开启掉电侦测电路.0:关闭*/

/* ANACON7*/
SBIT VREFTP_LOADREGU        = ANACON7^7; /* vreftp output buffer driving ability control signal.1:enhance the driving ability to about 55mA.0:use default value about 37mA driving ability at least*/
SBIT DSV_EN_MASK            = ANACON7^6; /* dsv_en信号的选择信号.0:asm生成的dsv_en信号无效,由mcu决定是否启动dsv_en;1:asm生辰过的dsv_en信号有效*/
SBIT NVDD2_MASK             = ANACON7^5; /* NVDD2在黑屏时的使能信号.nvdd2亮屏时受lcd控制,黑屏时,受tp控制.0:关闭nvdd2;1:开启nvdd2*/
SBIT VRGEN_EN               = ANACON7^4; /* 32k时钟电源切换功能.0:选择来自偏置.1:选择lcd来的bandgap偏置.黑屏时,此bit位一定需要配置为0,亮屏可配置0，也可配置成1*/
/* [3:0] VRFE_VDD_TPS. VDDD 1.2V setting. 0:  1.3v; 
                                          1:  1v;
                                          2:  1.025v;
                                          3:  1.05v;
                                          4:  1.075v;
                                          5:  1.1v;
                                          6:  1.125v;
                                          7:  1.150v;
                                          8:  1.175v;
                                          9:  1.2v
                                          10: 1.225v
                                          11: 1.25v
                                          12: 1.275v
                                          13: 1.325v
                                          14: 1.35v
                                          15: 1.375v*/

/* ANACON8 */
SBIT VDD_TP_N2_MASK         = ANACON8^7; /* reg_en_vdd_tp_n2信号的来源.0:来自mcu;1:来自asm*/
SBIT VDD_TP_N1_MASK         = ANACON8^6; /* reg_en_vdd_tp_n1信号来源.0:来自mcu;1:来自asm*/
SBIT VREFTP_SETOP_EN_M_MASK = ANACON8^5; /* vreftp_setop_en_m信号的来源.0:来自mcu;1:来自asm*/
SBIT VREFTP_BUF_EN_M_MASK   = ANACON8^4; /* vreftp_buf_en_m信号的来源.0:来自mcu;1:来自asm*/
SBIT VREFTP_SH_MASK         = ANACON8^3; /* vreftp_sh信号的来源.0:来自mcu;1:来自asm*/
SBIT VREFTP_SRCTRL_M_MASK   = ANACON8^2; /* vreftp_srctrl_m信号的来源.0:来自mcu;1:来自asm*/
SBIT BGP_MASK_MASK          = ANACON8^1; /* bgp_mask信号的来源.0:来自mcu;1:来自asm*/
SBIT NVDD2_MASK_MASK        = ANACON8^0; /* nvdd2_mask信号的来源.0:来自mcu;1:来自asm*/

/* ANACON9 */
SBIT VDD_TP_N3_MASK         = ANACON9^7; /* reg_en_vdd_tp_n3信号的来源.0:来自mcu;1:来自asm*/
SBIT REGBG_EN_MASK          = ANACON9^6; /* reg_en1信号的来源.0:来自mcu;1:来自asm*/
SBIT VREFTP_SETOP_EN_MASK   = ANACON9^5; /* vreftp_setop_en信号的来源.0:来自mcu;1:来自asm*/
SBIT VREFTP_BUF_EN_MASK     = ANACON9^4; /* vreftp_buf_en信号的来源.0:来自mcu;1:来自asm*/
SBIT VREFTP_SRCTRL_MASK     = ANACON9^3; /* vreftp_srctrl信号的来源.0:来自mcu;1:来自asm*/
SBIT VDD5_SETOP_EN_MASK     = ANACON9^2; /* vdd5_setop_en信号的来源.0:来自mcu;1:来自asm*/
SBIT VDD5_BUF_EN_MASK       = ANACON9^1; /* vdd5_buf_en信号的来源.0:来自mcu;1:来自asm*/
SBIT VDD5_SRCTRL_MASK       = ANACON9^0; /* vdd5_srctrl信号的来源.0:来自mcu;1:来自asm*/

/* PCON */
SBIT SMOD1                  = PCON^7;
SBIT SMOD0                  = PCON^6;
SBIT POF                    = PCON^4;
SBIT GF1                    = PCON^3;
SBIT GF0                    = PCON^2;
SBIT CORE_STOP              = PCON^1;         /* Stop 模式控制位 .该位写1，将进入stop模式，如果读该位，读出来的值为0*/
SBIT CORE_IDLE              = PCON^0;         /* Idle 模式控制位 。该为写1，强进入IDLE模式，如果读该位，读出来的值为0*/

/* CGUCON0 */
SBIT ASM_32K_EN             = CGUCON0^7;  /* asm 32k clock enable.1:enable;0:disable*/
SBIT STANDBY                = CGUCON0^6;  /* 用于在正常模式下，mcu处于power down时，对osc时钟以及digital的主时钟的disable.0:disable clock tree, osc48m;1:不关时钟 */
SBIT EN_32K                 = CGUCON0^5;  /* 1:打开32k osc*/
SBIT SPI0_32K_EN            = CGUCON0^4;  /* SPI0 DMA模块中的counter时钟gating*/
SBIT SPI0CKEN               = CGUCON0^3;  /* SPI0工作时钟的enable gating */
SBIT PROBE32K_DIG_EN        = CGUCON0^2;  /* clk_32k dig probe enable signal.1:enable;0:disable */
SBIT LVD_SLEEP_EN           = CGUCON0^1;  /* LVD事件发生时，是否关闭OSC.0:不关闭,default为0.1:关闭 */
SBIT PROBE32K_FROM1M_EN     = CGUCON0^0;  /* clk_32k_from_1m probe enable signal.1:enable;0:disable */


/* CGUCON1 */
SBIT SYSCKEN                = CGUCON1^7;     /* clock gating module:sysctrl,p0,p1*/
SBIT I2CCKEN                = CGUCON1^6;     /* i2c clk enable */
SBIT XSICKEN                = CGUCON1^5;     /* xsi source from core clock ,gating enable */
SBIT TIMER_500K_EN          = CGUCON1^4;     /* timer working clock enable signal.1:enable;0:disable*/
SBIT TIMERCKEN              = CGUCON1^3;     /* timer clk enable*/
SBIT UARTCKEN               = CGUCON1^2;     /* uart clk enable*/
SBIT DEBUGCKEN              = CGUCON1^1;     /* debug(including i2c debug) clk enable */
SBIT SPI1CKEN               = CGUCON1^0;     /* spi1 clk enable*/

/* CGUCON2 */
SBIT CLKEN_500K             = CGUCON2^7;     /* 500k clock gating enable*/
SBIT CNTCKEN                = CGUCON2^6;     /* cnt clk enable */
SBIT LED_32K_EN             = CGUCON2^5;     /* Led controller working clock*/
SBIT PROMCKEN               = CGUCON2^4;     /* prom clk enable */
SBIT PRAMCKEN               = CGUCON2^3;     /* pram clk enable */
SBIT AFEACKEN               = CGUCON2^2;     /* asm clock gating enbale */
SBIT LEDCKEN                = CGUCON2^1;     /* led clk enable */
SBIT RTC_32K_EN             = CGUCON2^0;     /* RTC Working clock*/

/* CGUCON3 */
SBIT DMACKEN                = CGUCON3^7;     /* CAL运行时，cpu是否进入idle状态。0:不进入idle状态;1:进入idle状态*/
SBIT CALCKEN                = CGUCON3^6;     /* cal clock enable*/
SBIT AFECKEN                = CGUCON3^5;     /* Clock dynamic gating AFE controller */
SBIT CLOSE_500K_EN          = CGUCON3^4;     /* mcu standby close 500k enable signal.1:close*/
SBIT XBUSCKEN               = CGUCON3^3;     /* Xsi0 clk enable */
SBIT AFESCKEN               = CGUCON3^2;     /* asm configure clock */
SBIT CLOSE_TIMER_EN         = CGUCON3^1;     /* mcu standby close timer clock enable sigal.1:close*/
SBIT RTCCKEN                = CGUCON3^0;

/* CGUCON4 */
SBIT SSCG_CKEN              = CGUCON4^7;   /* sscg clk enable */
SBIT WDT_500K_EN            = CGUCON4^6;   /* CLK_500K的gating enable for wdt*/
SBIT PROBE32K_CKEN          = CGUCON4^4;   /* probe 32K clk enable */
SBIT PROBE48M_CKEN          = CGUCON4^3;   /* probe 48M clk enable */
/*CGUCON4[1:0] clk_div  use for select frequence for div clock source 0:1div;1:2div;2:4 div;3:8div*/


/* CGUCON5 for INT0 wake up */
SBIT GPIO_WKEN              = CGUCON5^7;  /* int0 wake up enable */
SBIT LCD_ESD_WKEN           = CGUCON5^6;  /* lcd esd wake up enble */
SBIT LCD_LVD_WKEN           = CGUCON5^5;  /* lcd lvd wake up enble */
SBIT LCD_TIM_WKEN           = CGUCON5^4;  /* lcd timing wake up enble */
SBIT LCD_RELOAD_FLASH_WKEN  = CGUCON5^3;  /* LCD reload flash wake up enable */
SBIT ASM_MON_WKEN           = CGUCON5^2;  /* scan monitor wake up enable */
SBIT I2C_MON_WKEN           = CGUCON5^1;  /* i2c monitor wake up enable */
SBIT RTC_CNT_WKEN           = CGUCON5^0;  /* RTC or CNT wake up enable */

/* CGUCON6 */
SBIT CLK_WP                 = CGUCON6^0; /* Only CGU0 need */

/* CGUCON7 */
/*CGUCON7[7:6] OSC_TEST_SEL            在gpio口测量osc32k和osc48m时钟时的选择信号.3:32k_from_1m;2:32k_dig;1:32K , 0:48M */
/*CGUCON7[5:0] OSC_TEST_DIV            量测OSC48M或者32k OSC时钟时，分频洗漱配置*/

SBIT SEL_32K_SRC            = CGUCON8^7; /* 32k时钟源选择.1:32k选择产生于模拟osc,1:32k来源于1m分频*/
/* [6:0] fre_noadj_set. 数字32k时钟是否调整的容值. 1m时钟,48m来测,如果正好是32k,个数为1536.但是1m分频可能调整不到正好32k.
因此会来回震荡.为了解决该问题,需设置该值.若设置值为15,分频出来的时钟,被检测在[1536-15,1536+15]之间,不会调整 */

/*I2CCON*/
SBIT I2C_WKEN               = I2CCON^5;      /* 0:disable i2c wakeup;1:enable i2c wakeup */
SBIT I2C_DEGLITCH_EN        = I2CCON^4;      /* analog deglitch enable.0:disable;1:enable */
SBIT I2C_BUSY               = I2CCON^3;      /* i2c是否处于发送/接收状态.0:idle;1:busy */
SBIT I2CTI                  = I2CCON^1;      /* hw set, sw clear */
SBIT I2CRI                  = I2CCON^0;      /* hw set, sw clear */

/*I2CSTOP*/
SBIT I2C_WAIT               = I2CSTOP^7;     /* 0:释放i2c scl;1:拉低i2c scl,扩展scl周期;当slave忙时不能及时响应 */
SBIT COMP_BPSS              = I2CSTOP^6;     /* 0:使能i2c地址匹配;1:取消地址匹配控制 */
SBIT ADDR_NACK              = I2CSTOP^5;     /* 0:对i2c地址阶段发ack;1:对i2c地址阶段发送nack */
SBIT DATA_NACK              = I2CSTOP^4;     /* 0:对i2c数据阶段发ack;1:对i2c数据阶段发nack */
SBIT I2C_WK_STOP            = I2CSTOP^2;     /* wakeup模块接收到正确的stop，write 0 to clear */
SBIT STOPID                 = I2CSTOP^1;     /* stop状态状态位,表示当前是wr stop还是rd stop.0: host write stop 1: host read stop */
SBIT I2CSTP                 = I2CSTOP^0;     /* hw set when received right i2c stop statue,sw clear */

/*I2CSEL*/
SBIT I2C_MON_CFG            = I2CSEL^4;   /* 0: i2c工作，i2c monitor不工作; 1:i2c不工作,i2c_monitor工作 */

/* I2CStart*/
SBIT I2C_WK_BYTE4_FLAG      = I2C_STATE^3;
SBIT I2C_WK_BYTE3_FLAG      = I2C_STATE^2;
SBIT I2C_WK_BYTE2_FLAG      = I2C_STATE^1;
SBIT I2C_WK_BYTE1_FLAG      = I2C_STATE^0;

/*IEN1*/
SBIT SWDT                   = IEN1^6;     /*Active watchdog timer.1:active;0:idle*/

/* WDTCON */
SBIT WDTACT                 = WDTCON^2;   /* wdt work state.1:wdt in running mode; 0:wdt in stop mode */
SBIT WDTSTARTEN             = WDTCON^1;   /* when write 1,wdt start running,it is auto clear to 0 */
SBIT WDTSTOPEN              = WDTCON^0;   /* when write 1,wdt stop running,it is auto clear to 0 */

/*WDTREL*/
SBIT WDT_PRESCALE           = WDTREL^7;  /*Reload value for high-byte watchdog.1:每384个cycle计数一次;0:每24个cycle计数一次*/
/*WDTREL[6:0]                   reload value for the high_seven_byte of the watchdog timer when a refresh is triggered.*/

/* TCON */
SBIT TF1 = TCON^7;               /* timer1 overflow flag：
                                   当timer1 overflows时会置1，中断响应时硬件会清零 */
SBIT TR1 = TCON^6;               /* timer1的控制位。
                                   “1”：起动timer1,硬件自动清零（注意：在起动timer1之前必须要把timer1设定好） */
SBIT TF0 = TCON^5;               /* timer0 overflow flag：
                                    当timer0 overflows时会置1，中断响应时硬件会清零 */
SBIT TR0 = TCON^4;               /* timer0的控制位。
                                   “1”：起动timer0,硬件自动清零（注意：在起动timer0之前必须要把timer0设定好） */
SBIT IF1 = TCON^3;               /* external interrupt 1 edge flag,hardware controlled
                                    set when external interrupt 1 is detected
                                    cleared when interrupt is processed */
SBIT IT1 = TCON^2;               /* external interrupt 1 signal type control bit
                                    set to specify external interrupt 1 as falling edge triggered
                                    cleared to specify external interrupt 1 as low level triggered */
SBIT IF0 = TCON^1;               /* external interrupt 0 edge flag , hardware controlled
                                    set when external interrupt 0 is detected
                                    cleared when interrupt is processed */
SBIT IT0 = TCON^0;               /* external interrupt 0 signal type control bit.
                                    Set to specify External interrupt 0 as falling edge triggered.
                                    Cleared to specify External interrupt 0 as low level triggered. */
/*TMOD*/
SBIT GATE1              = TMOD^7;  /*timer 1 gate*/
SBIT GATE0              = TMOD^3;  /*timer0 gate*/
/*TMOD[5:4]             time1 mode select. 00:timer stop; 01:16 bit counter single mode; 10:16 bit counter repeat mode; 11:half timer1暂停工作,如果复原到之前的模式,timer1将继续工作*/
/*TMOD[1:0]             time0 mode select.功能同上*/

/*TDIV*/
SBIT INTSEL1            = TDIV^7;   /*timer1中断清除选择.1:软件清除,写intclr1清除timer1中断;0:硬件清除*/
SBIT INTSEL0            = TDIV^6;   /*timer0中断清除选择.1:软件清除,写intclr0清除timer1中断;0:硬件清除*/
SBIT INTCLR1            = TDIV^5;   /*软件清除时,INTCLR1写1时清除timer1中断*/
SBIT INTCLR0            = TDIV^4;   /*软件清除时,INTCLR0写1时清除timer1中断*/

/* CNTCON */
SBIT CNT_START          = CNTCON^7;   /* 1: 启动CNT; 0: 计数终止(可以读取计数值) */
SBIT CNT_CLEAR          = CNTCON^4;   /* 清除CNT计数器值到0 */
SBIT CNT_WKEN           = CNTCON^3;   /* CNT唤醒使能: 1:打开使能 0:关闭唤醒使能 */

/*LED_EN*/
SBIT LED_5_EN           = LED_EN^5;
SBIT LED_4_EN           = LED_EN^4;
SBIT LED_3_EN           = LED_EN^3;
SBIT LED_2_EN           = LED_EN^2;
SBIT LED_1_EN           = LED_EN^1;
SBIT LED_0_EN           = LED_EN^0;

/*MEMBIST_EN1*/
SBIT DRAM2_BIST_EN      = MEMBIST_EN1^7;
SBIT DRAM1_BIST_EN      = MEMBIST_EN1^6;
SBIT DRAM0_BIST_EN      = MEMBIST_EN1^5;
SBIT PRAM4_BIST_EN      = MEMBIST_EN1^4;
SBIT PRAM3_BIST_EN      = MEMBIST_EN1^3;
SBIT PRAM2_BIST_EN      = MEMBIST_EN1^2;
SBIT PRAM1_BIST_EN      = MEMBIST_EN1^1;
SBIT PRAM0_BIST_EN      = MEMBIST_EN1^0;

/*MEMBIST_EN2*/
SBIT AFERAM_R_BIST_EN   = MEMBIST_EN2^3;
SBIT AFERAM_L_BIST_EN   = MEMBIST_EN2^2;
SBIT ARAM_BIST_EN       = MEMBIST_EN2^1;
SBIT PROM_BIST_EN       = MEMBIST_EN2^0;

/*MEMBIST_FINISH1*/
SBIT DRAM2_FINISH       = MEMBIST_FINISH1^7;
SBIT DRAM1_FINISH       = MEMBIST_FINISH1^6;
SBIT DRAM0_FINISH       = MEMBIST_FINISH1^5;
SBIT PRAM4_FINISH       = MEMBIST_FINISH1^4;
SBIT PRAM3_FINISH       = MEMBIST_FINISH1^3;
SBIT PRAM2_FINISH       = MEMBIST_FINISH1^2;
SBIT PRAM1_FINISH       = MEMBIST_FINISH1^1;
SBIT PRAM0_FINISH       = MEMBIST_FINISH1^0;

/*MEMBIST_FINISH2*/
SBIT RPTRAM_R_FINISH    = MEMBIST_FINISH2^7;
SBIT RPTRAM_L_FINISH    = MEMBIST_FINISH2^6;
SBIT ACCRAM_R_FINISH    = MEMBIST_FINISH2^5;
SBIT ACCRAM_L_FINISH    = MEMBIST_FINISH2^4;
SBIT TABRAM_R_FINISH    = MEMBIST_FINISH2^3;
SBIT TABRAM_L_FINISH    = MEMBIST_FINISH2^2;
SBIT ARAM_FINISH        = MEMBIST_FINISH2^1;
SBIT PROM_FINISH        = MEMBIST_FINISH2^0;

/*MEMBIST_FAIL1*/
SBIT DRAM2_FAIL         = MEMBIST_FAIL1^7;
SBIT DRAM1_FAIL         = MEMBIST_FAIL1^6;
SBIT DRAM0_FAIL         = MEMBIST_FAIL1^5;
SBIT PRAM4_FAIL         = MEMBIST_FAIL1^4;
SBIT PRAM3_FAIL         = MEMBIST_FAIL1^3;
SBIT PRAM2_FAIL         = MEMBIST_FAIL1^2;
SBIT PRAM1_FAIL         = MEMBIST_FAIL1^1;
SBIT PRAM0_FAIL         = MEMBIST_FAIL1^0;

/*MEMBIST_FAIL2*/
SBIT RPTRAM_R_FAIL      = MEMBIST_FAIL2^7;
SBIT RPTRAM_L_FAIL      = MEMBIST_FAIL2^6;
SBIT ACCRAM_R_FAIL      = MEMBIST_FAIL2^5;
SBIT ACCRAM_L_FAIL      = MEMBIST_FAIL2^4;
SBIT TABRAM_R_FAIL      = MEMBIST_FAIL2^3;
SBIT TABRAM_L_FAIL      = MEMBIST_FAIL2^2;
SBIT ARAM_FAIL          = MEMBIST_FAIL2^1;
SBIT PROM_FAIL          = MEMBIST_FAIL2^0;

/*MEMBIST_ERRMAP1*/
SBIT DRAM2_ERRMAP       = MEMBIST_ERRMAP1^7;
SBIT DRAM1_ERRMAP       = MEMBIST_ERRMAP1^6;
SBIT DRAM0_ERRMAP       = MEMBIST_ERRMAP1^5;
SBIT PRAM4_ERRMAP       = MEMBIST_ERRMAP1^4;
SBIT PRAM3_ERRMAP       = MEMBIST_ERRMAP1^3;
SBIT PRAM2_ERRMAP       = MEMBIST_ERRMAP1^2;
SBIT PRAM1_ERRMAP       = MEMBIST_ERRMAP1^1;
SBIT PRAM0_ERRMAP       = MEMBIST_ERRMAP1^0;

/*MEMBIST_ERRMAP2*/
SBIT RPTRAM_R_ERRMAP    = MEMBIST_ERRMAP2^7;
SBIT RPTRAM_L_ERRMAP    = MEMBIST_ERRMAP2^6;
SBIT ACCRAM_R_ERRMAP    = MEMBIST_ERRMAP2^5;
SBIT ACCRAM_L_ERRMAP    = MEMBIST_ERRMAP2^4;
SBIT TABRAM_R_ERRMAP    = MEMBIST_ERRMAP2^3;
SBIT TABRAM_L_ERRMAP    = MEMBIST_ERRMAP2^2;
SBIT ARAM_ERRMAP        = MEMBIST_ERRMAP2^1;
SBIT PROM_ERRMAP        = MEMBIST_ERRMAP2^0;

/* AIF */
SBIT WDT_INT_IF         = AIF^4;      /* wdt int请求信号 */
SBIT SPI0_INT_IF        = AIF^3;      /* spi0 int请求信号 */
SBIT SPI1_INT_IF        = AIF^2;      /* spi1 int请求信号 */
SBIT ASM_INT_IF         = AIF^1;      /* asm int请求信号 */
SBIT I2C_STOP_IF        = AIF^0;      /* i2c stop int请求信号 */

/* AIE */
SBIT WDT_INT_EI         = AIE^4;    /* wdt int enable */
SBIT SPI0_EI            = AIE^3;    /* spi0 int enable*/
SBIT SPI1_EI            = AIE^2;    /* spi1 int enable */
SBIT ASM_EI             = AIE^1;    /* Asm int enable */
SBIT I2C_STOP_EI        = AIE^0;    /* i2c stop int enable */  


/* IEN0 */
SBIT EA                 = IEN0^7;  /* Global Interrupt Enable */
SBIT EC                 = IEN0^6;  /* uart */
SBIT ET2                = IEN0^5;  /* I2C */
SBIT ES                 = IEN0^4;  /* LCD TIMING int */
SBIT ET1                = IEN0^3;  /* timer1 */
SBIT EX1                = IEN0^2;  /* RTC or CNT */
SBIT ET0                = IEN0^1;  /* timer0 */
SBIT EX0                = IEN0^0;  /* int0 wake up */

/* interruption priority */
SBIT IPHX0              = IPH0^0;   /* Int0 */
SBIT IPLX0              = IPL0^0;
SBIT IPHT0              = IPH0^1;   /* Time0 */
SBIT IPLT0              = IPL0^1;
SBIT IPHX1              = IPH0^2;   /* Int1 */
SBIT IPLX1              = IPL0^2;
SBIT IPHT1              = IPH0^3;   /* Time1 */
SBIT IPLT1              = IPL0^3;
SBIT LCD_IPH            = IPH0^4;   /* LCD int run */
SBIT LCD_IPL            = IPL0^4;
SBIT I2C_IPH            = IPH0^5;   /* I2C */
SBIT I2C_IPL            = IPL0^5;
SBIT Uart_IPH           = IPH0^6;   /* Uart */
SBIT Uart_IPL           = IPL0^6;
SBIT I2C_STOP_IPH       = AIPH^0;   /* I2C Stop */
SBIT I2C_STOP_IPL       = AIPL^0;
SBIT ASM_IPH            = AIPH^1;   /* ASM */
SBIT ASM_IPL            = AIPL^1;   
SBIT SPI1_IPH           = AIPH^2;   /* SPI1 */
SBIT SPI1_IPL           = AIPL^2;
SBIT SPI0_IPH           = AIPH^3;   /* SPI0 */
SBIT SPI0_IPL           = AIPL^3;
SBIT WDT_IPH            = AIPH^4;   /* wdt */
SBIT WDT_IPL            = AIPL^4;

/* P0 */
SBIT P0_7               = P0BUF^7;
SBIT P0_6               = P0BUF^6;
SBIT P0_5               = P0BUF^5;
SBIT P0_4               = P0BUF^4;
SBIT P0_3               = P0BUF^3;
SBIT P0_2               = P0BUF^2;
SBIT P0_1               = P0BUF^1;
SBIT P0_0               = P0BUF^0;

/*p1*/
SBIT P1_7               = P1BUF^7;
SBIT P1_6               = P1BUF^6;
SBIT P1_5               = P1BUF^5;
SBIT P1_4               = P1BUF^4;
SBIT P1_3               = P1BUF^3;
SBIT P1_2               = P1BUF^2;
SBIT P1_1               = P1BUF^1;
SBIT P1_0               = P1BUF^0;


/* GPIO pin definition */
SBIT Flash_WP           = P1BUF^7;
SBIT Flash_HOLD         = P1BUF^4;

SBIT Flash_pad          = P1BUF^6;
SBIT Flash_DIR          = P1DIR^6;
SBIT Flash_GPIO         = P1MOD^6;
SBIT Flash_DM           = P1SEL^6;

SBIT INTOUT             = P0BUF^6;
SBIT INTOUT_DIR         = P0DIR^6;
SBIT GPIO_INTOUT        = P0MOD^6;
SBIT INTOUT_DM          = P0SEL^6;

SBIT GPIO3              = P0BUF^7;
SBIT GPIO3_DIR          = P0DIR^7;
SBIT GPIO3_INTOUT       = P0MOD^7;
SBIT GPIO3_DM           = P0SEL^7;

SBIT GPIO4              = P1BUF^5;
SBIT GPIO4_DIR          = P1DIR^5;
SBIT GPIO4_INTOUT       = P1MOD^5;
SBIT GPIO4_DM           = P1SEL^5;

/* mcu clk config */
#define MAIN_CLK  0 //0:48M; 1:24M   
/*******************************************************************************
 * 3.Global structures, unions and enumerations using typedef
 *******************************************************************************/

/*******************************************************************************
 * 4.Global variable extern declarations
 *******************************************************************************/


/******************************************************************************
*
* App Info data section
******************************************************************************/
// app 存在flash的物理地址
#define CODE_START_ADDR       0x1000
#define CODE_VERIF_ADDR       (CODE_START_ADDR+APP_VERIF_ADDR)

// app 存在pram的物理地址
#define APP_ADDR_START        0x0000  // app start addr
#define APP_START_OPCODE      0x02

#define APP_VERIF_ADDR        0x100   // Verification Info
#define APP_VERIF_LEN         0x20
#define APP_VERIF_CODE_LEN    0x04    //app中code长度信息

typedef enum
{
    APP_LEN      = 0x00,
    APP_NE_LEN   = 0x02,
    P1_ECC_H     = 0x04,
    P1_ECC_L     = 0x05,
    P1_ECC_NE_H  = 0x06,
    P1_ECC_NE_L  = 0x07,
    P2_ECC_H     = 0x08,
    P2_ECC_L     = 0x09,
    P2_ECC_NE_H  = 0x0A,
    P2_ECC_NE_L  = 0x0B,
    APP_LEN_H    = 0x12,
    APP_LEN_H_NE = 0x14,
} ENUM_APP_INFO;

// App验证信息
#define ADDR_APP_LEN          (APP_VERIF_ADDR+APP_LEN)
#define ADDR_APP_NE_LEN       (APP_VERIF_ADDR+APP_NE_LEN)
#define ADDR_PART1_ECC        (APP_VERIF_ADDR+P1_ECC_H)
#define ADDR_PART1_ECC_NE     (APP_VERIF_ADDR+P1_ECC_NE_H)
#define ADDR_PART2_ECC        (APP_VERIF_ADDR+P2_ECC_H)
#define ADDR_PART2_ECC_NE     (APP_VERIF_ADDR+P2_ECC_NE_H)
#define ADDR_APP_LEN_H        (APP_VERIF_ADDR+APP_LEN_H)
#define ADDR_APP_LEN_H_NE     (APP_VERIF_ADDR+APP_LEN_H_NE)

#define APP_ADDR_PART1_START  0x0000
#define APP_ADDR_PART1_LEN    ((APP_VERIF_ADDR)-(APP_ADDR_PART1_START))
#define APP_ADDR_PART2_START  ((APP_VERIF_ADDR)+(APP_VERIF_LEN)+(FW_CFG_TOTAL_SIZE))

#define FLASH_APP_INFO        (APP_VERIF_ADDR + CODE_START_ADDR)
/******************************************************************************
*
* FW config data section
*******************************************************************************
/
/* FW配置区域长度 */
#define FW_CFG_TOTAL_SIZE          0x80
#define FW_CFG_INFO_SIZE           0x0E

/* FW配置区域偏移量 */
typedef enum
{
    FW_CFG_I2C_OFFSET              = 0x00,     // master I2C  addr
    FW_CFG_I2C_NE_OFFSET           = 0x01,     // ~master I2C addr
    FW_CFG_IOVOLTAGE_OFFSET        = 0x02,     // Io Voltage 
    FW_CFG_IOVOLTAGE_NE_OFFSET     = 0x03,     // ~Io Voltage
    FW_CFG_VENDOR_OFFSET           = 0x04,     // Vendor 
    FW_CFG_VENDOR_NE_OFFSET        = 0x05,     // ~Vendor
    FW_CFG_SPI_CLK_OFFSET          = 0x06,     // SPI Clk
    FW_CFG_SPI_CLK_NE_OFFSET       = 0x07,     // ~SPI Clk
    FW_CFG_SYS_CLK_OFFSET          = 0x08,     // Sys Clk
    FW_CFG_SYS_CLK_NE_OFFSET       = 0x09,     // ~Sys Clk 
    FW_CFG_XBUS_CLK_OFFSET         = 0x0A,     // LCD xbus clk
    FW_CFG_XBUS_CLK_NE_OFFSET      = 0x0B,     // ~LCD xbus clk
    FW_CFG_SPI_IOMODE_OFFSET       = 0x0C,     // spi iomode
    FW_CFG_SPI_IOMODE_NE_OFFSET    = 0x0D,     // ~spi iomode
} ENUM_FW_CFG_OFFSET;

/* FW配置区域Flash位置 */
typedef enum
{
    FW_CFG_START_FLASH_ADDR        = 0x0F80,
    FW_CFG_I2C_FLASH_ADDR          = (FW_CFG_START_FLASH_ADDR+
FW_CFG_I2C_OFFSET),
} ENUM_FW_CFG_FLASH_ADDR;

/* FW配置备份区域Flash位置 */
typedef enum
{
    FW_CFG_BKUP_START_FLASH_ADDR   = 0x1120,
    FW_CFG_BKUP_I2C_FLASH_ADDR     = (FW_CFG_BKUP_START_FLASH_ADDR+FW_CFG_I2C_OFFSET),
} ENUM_FW_CFG_BKUP_FLASH_ADDR;

/* LCD OTP配置区域位置 */
typedef enum
{
    LCD_OTP_REG_ADDR               = 0x9866,
    LCD_OTP_MASTER_I2C_ADDR        = (LCD_OTP_REG_ADDR+FW_CFG_I2C_OFFSET),
    LCD_OTP_MASTER_I2C_NE_ADDR,
    LCD_OTP_SPI_CLK_ADDR           = (LCD_OTP_REG_ADDR+FW_CFG_SPI_CLK_OFFSET),
    LCD_OTP_SPI_CLK_NE_ADDR,
    LCD_OTP_SYS_CLK_ADDR,
    LCD_OTP_SYS_CLK_NE_ADDR,
    LCD_OTP_XBUS_CLK_ADDR,
    LCD_OTP_XBUS_CLK_NE_ADDR,
    LCD_OTP_SPI_IOMODE_ADDR,
    LCD_OTP_SPI_IOMODE_NE_ADDR,
} ENUM_LCD_OTP_ADDR;

#define REG8(n)  (*((volatile UINT8  *)(n)))
#define REG16(n) (*((volatile UINT16 *)(n)))
#define REG32(n) (*((volatile UINT32 *)(n)))

#define APP_DATA_MAX         0x11800
#define RST_VALUE_UPGRADE    0x6B  /* Flag of upgrade according to Romboot */

#define PRAM_ADDR8(n)    (*((UINT8 far *)((UINT32)0xFEE800 + (n))))
#define PRAM2_ADDR8(n)   (*((UINT8 far *)((UINT32)0xFF4000 + (n))))

#define PRAM_PTR8(n)     ((volatile UINT8 far *)((UINT32)0xFEE800 + (n)))
#define PRAM2_PTR8(n)    ((volatile UINT8 far *)((UINT32)0xFF4000 + (n)))

#define PROM_ADDR8(n)     (*((UINT8 far *)(0xFD0000 + n)))
#define DRAM_ADDR8(n)     (*((UINT8 *)(0x0000 + n)))


#define PRAM_ADDR16(n)     (*((UINT16 far *)(0xFEE800 + n)))

#define PROM_ADDR16(n)     (*((UINT16 far *)((UINT32)0xFD0000 + n)))
#define DRAM_ADDR16(n)     (*((UINT16 *)((UINT32)0x0000 + n)))

#define HOLD            while (1)
/*******************************************************************************
 * Global function prototypes
 *******************************************************************************/

#endif
