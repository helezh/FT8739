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
SFR SP               = 0x81; 
SFR DPL             = 0x82;
SFR DPH             = 0x83;
SFR DPXL            = 0x84;
SFR PCON            = 0x87;

/*88-8F*/
SFR TCON        = 0x88;
SFR TMOD        = 0x89;
SFR TL0           = 0x8A;   /* 设定计数器时间低8位，计数时间为TL0[7:0]X4us,最大值不能超过1ms也就是说最大值为8’hF9,大于此值时将强制为8’hF9. */
SFR TL1           = 0x8B;   /* 设定计数器时间低8位，计数时间为TL1[7:0]X4us */
SFR TH0          = 0x8C;   /* 设定计数器时间高8位，计数时间为TH0[7:0]X1ms,TH0[7]必须为0，所以最长时间为127ms */
SFR TH1          = 0x8D;   /* 设定计数器时间高8位，计数时间为TH1[7:0]X1ms,TH1[7]必须为0，所以最长时间为127ms */

/*90-97*/
SFR I2CCON       = 0x90;
SFR I2CBUF       = 0x91;
SFR I2CADDR     = 0x92;
SFR I2CSTOP     = 0x93;
SFR P1BUF        = 0x94;   /*P1Buf*/
SFR I2CSEL       = 0x95;
SFR MMCON       = 0x97;

/*98-9F*/
SFR SYSCON       = 0x98;
SFR WDTCON      = 0x99;
SFR WDTREL       = 0x9A;
SFR TDIV            = 0x9B;
SFR RTCIVL        = 0x9C; /*rtc计数终止低8位*/      
SFR RTCIVH       = 0x9D; /*rtc计数终止高8位*/
SFR RTCCON       = 0x9E;
SFR RTCSLN       = 0x9F; /*rtc 时间片个数*/

/*A0-A7*/

/*A8-AF*/
SFR IEN0                 = 0xA8;
SFR UARTCON          = 0xA9;
SFR UARTBUF          = 0xAA;
SFR UART_RELL       = 0xAB;
SFR P0DIR               = 0xAC;   /*P0口方向配置，1:输出, 0:输入*/
SFR P1DIR               = 0xAD;   /*P1口方向配置，1:输出, 0:输入*/
SFR UART_RELH      = 0xAE;
SFR UART_SDA        = 0xAF;

/*B0-B7*/
SFR SPI1CON3       = 0xB1;
SFR SPI1CON4       = 0xB2;
SFR SPI1CON         = 0xB3;
SFR SPI1CON2       = 0xB4;
SFR SPI1BUF         = 0xB5;
SFR IPH0               = 0xB7; 

/*B8-BF*/
SFR IPL0             = 0xB8;
SFR CNTCON       = 0xB9;
SFR CNTIVL         = 0xBA;  /*CNT计数终止低8位*/
SFR CNTIVM        = 0xBB;  /*CNT计数终止中间8位*/
SFR CNTIVH        = 0xBC;   /*CNT计数终止高8位*/
SFR SPH              = 0xBE;

/*C0-C7*/
SFR AIF              = 0xC0;
SFR CGUCON8     = 0xC1;
SFR CGUCON9     = 0xC2;
SFR CGUCONA     = 0xC3;
SFR CGUCONB     = 0xC4;
SFR CGUCONC     = 0xC5;
SFR CGUCOND     = 0xC6;
SFR CGUCONE     = 0xC7;

/*C8-CF*/
SFR CGUCON1     = 0xC8;
SFR CGUCON0     = 0xC9;
SFR CGUCON2     = 0xCA;
SFR CGUCON3     = 0xCB;
SFR CGUCON4     = 0xCC;
SFR CGUCON5     = 0xCD;
SFR CGUCON6     = 0xCE;
SFR CGUCON7     = 0xCF;

/* D1-D7 */
SFR MEMBIST_EN_ID1        = 0xD2;
SFR MEMBIST_EN_ID2        = 0xD3;
SFR MEMBIST_FINISH_ID1 = 0xD4;
SFR MEMBIST_FINISH_ID2 = 0xD5;
SFR MEMBIST_FAIL_ID1     = 0xD6;
SFR MEMBIST_FAIL_ID2     = 0xD7;

/* D8-DF */
SFR MEMBIST_ERRMAP_ID1 = 0xD8;
SFR MEMBIST_ERRMAP_ID2 = 0xD9;
//SFR TRIMOSC_CON           = 0xDA;
//SFR TRIMOSC_CFG1          = 0xDB;
//SFR TRIMOSC_CFG2          = 0xDC;
SFR MEMBIST_ROMCRCH_ID = 0xDD;
SFR MEMBIST_ROMCRCL_ID = 0xDE;
SFR IEN1                              = 0xDF;

/*E0-E7*/
SFR DSVCON                  = 0xE1;
SFR DEBUGCON0           = 0xE2;
SFR DEBUGCON1           = 0xE3;
SFR I2CSAD                   = 0xE4;
SFR IWKSTA                  = 0xE5;
SFR POR_STA                 = 0xE6;/*POR复位检查*/
SFR RST_STA                 = 0xE7;/*Pin reset复位检查*/


/*E8-EF*/
SFR AIE                     = 0xE8;
SFR SFTRST              = 0xE9;
SFR ANACON             = 0xEA;
SFR P0MOD               = 0xEB;/*0:P0 use as gpio;1:po use as function define*/
SFR P0SEL                = 0xEC;/*0:P0 as OD port; 1:P0 as PUSH-PULL port*/
SFR P1MOD               = 0xED;/*0:P1 use as gpio;1:p1 use as function define*/
SFR P1SEL                 = 0xEE;/*0:P1 as OD port; 1:P1 as PUSH-PULL port*/
SFR LCD_ESD_STA    = 0xEF;

/*F0-F7*/
SFR SSCG_CON0          = 0xF4;
SFR SSCG_CON1          = 0xF5; /*sscg_step:sscg increase/decrease period(500us/step). sscg trim code will increase in every(500ns*(step+1))*/
SFR AIPH                    = 0xF7;

/*F8-FF*/
SFR AIPL                     = 0xF8;
SFR DBGCON0             = 0xF9; /*xram_en[7:0]=AA时,Enable间接xram access mode(使用i2c debug可acess到xram memory space)*/
SFR DBGCON1             = 0xFA; /*要access的xram_addr高位*/ 
SFR DBGCON2             = 0xFB; /*要access的xram_addr低位*/
SFR DBGCON3             = 0xFC; /*写入此byte时,会写入到内部暂存xram_data[15:8]内;读出时,此byte为xram_addr[14:0]位置的内容值xram_rdata[15:8]*/
SFR DBGCON4             = 0xFD;	/*写入此byte时,会写入到内部暂存xram_data[7:0]内;读出时,此byte为xram_addr[14:0]位置的内容值xram_rdata[7:0]*/
SFR LED_EN                = 0xFE;   /* 4个LED灯使能; bit3~bit0有效,每bit分别对应一个LED使能 */
SFR LED_H_NUM          = 0xFF;   /* led PWM波高电平持续的周期数，0~63可配，0代表1个32k周期高电平，63代表64个32k周期高电平，即一直为高；*/


/******************************************************************************/
/* bit Registers */

/*SSCG_CON0*/
/*bit5-4  sscg_amp */   /*sscg amplitude. Control the output sequence of DA_TRIM[2:0]. Clock stable time between each trim code is located in range 100ns-200ns*/
SBIT SSCG_SCAN_EN     = SSCG_CON0^1; /*0:stop sscg when scan 1:contiune sscg when scan(sync with scan)*/
SBIT SSCG_EN                = SSCG_CON0^0; /*0:disable sscg  1:enable sscg*/


/*SPICLKDIV: 000:4分频;001:6分频;010:8分频;011:12分频;100:16分频;101:18分频;110:20分频;111:24分频*/
/*SPI1CON*/
SBIT SPI1TI                  = SPI1CON^7; /*发送请求中断标志位*/
SBIT SPI1RI                  = SPI1CON^6;  /*接收完毕中断请求标志位*/
SBIT SPI1CKM               = SPI1CON^5;  /*SPI1CLKDIV中间位*/
SBIT SPI1CKL                = SPI1CON^4;  /*SPI1CLKDIV低位*/
SBIT SPI1PH                 = SPI1CON^3; /*0:直接发送数据,缓存半个cycle接收数据;1:直接接收数据,缓存半个cycle发送数据*/
SBIT SPI1PO                 = SPI1CON^2; /*0:low idle; 1:high idle*/
SBIT SPI1MAS               = SPI1CON^1; /*0:slave mode; 1:master mode*/ 
SBIT SPI1_SLVSLELEN  = SPI1CON^0; /*0:master模式下的slvselo受内部启动控制;1:master模式下slvselo受SPI1CON2[2]控制*/


/*SPI1CON2*/
SBIT SPI1TX_AUTO_CLR  = SPI1CON2^7; /*0:软件自动清ri中断标志位;1:软件在读rx reg时硬件自清*/
SBIT SPI1RX_AUTO_CLR  = SPI1CON2^6; /*0:软件自动清ti中断标志位;1:软件在读tx reg时硬件自清*/
SBIT SPI1_BUSY              = SPI1CON2^5; /*0:低电平状态,只能读;1:SPI1正处于active*/ 
SBIT SPI1_STOP              = SPI1CON2^4; 
SBIT SPI1_START            = SPI1CON2^3;
SBIT SPI1SLVELO             = SPI1CON2^2; /*当SPI1CON[0]为1时,master状态下该位直接输出SPI1的slvsel；当SPI1CON[0]为0时，该位无效*/
SBIT SPI1RI_EN              = SPI1CON2^1; /*0:禁止产生接收中断请求信号;1:允许产生接收中断请求信号*/
SBIT SPI1TI_EN              = SPI1CON2^0; /*0:禁止产生接收中断请求信号;1:允许产生接收中断请求信号*/

/*SPI1CON3*/
SBIT SPI1MODE_SELH     = SPI1CON3^7; /*1:用IO0-IO2传输数据;0:根据SPI1CON3[6]状态决定*/
SBIT SPI1MODE_SELL     = SPI1CON3^6; /*若SPI1MODE_SELH为0,则0:用IO0传输;1:用IO0,IO1传输*/
SBIT SPI1_SW_IO_ENH  = SPI1CON3^5; /*IO0,IO1方向控制位. 0:standard spi IO setting;1:控制IO0,IO1方向自动切换,切换时间参reg配置spi_dat_opn_num*/
SBIT SPI1_SW_IO_ENL   = SPI1CON3^4; /*IO2,IO3方向控制位. 0:standard spi IO setting;1:控制IO2,IO3方向自动切换,切换时间参reg配置spi_dat_opn_num*/
SBIT SW_1BYTE_LATER  = SPI1CON3^2; /*dual/quad spi软件切换时间.0:立即切换;1:在下个byte数据传输结束以后的第一个shift_out_sck_edg之前完成切换*/
SBIT SPI1_SW_DIR        = SPI1CON3^1; /*dual/quad spi时软件切换io的方向.0:输出;1:输入*/
SBIT SPI1_SW_EN          = SPI1CON3^0; /*dual/quad spi 软件io方向切换使能，写1有效.硬件在切换之后自清*/

/*SPI1CON4*/
SBIT SPI1IOSW_CKDLY_EN = SPI1CON4^4; /*传输IO切换方向时 0:切换方向不延时;1:切换方向延长2个clk cycle*/
SBIT SPI1CKH                      = SPI1CON4^2; /*SPI1CLKDIV高位*/

/*spi1con[1:0] sample_phase_sel*/ /*采样时钟延迟选择. 00:无延迟;01:延迟1个clk cycle; 10:延迟2个clk cycle; 11:延迟3个clk cycle*/


/*UARTCON*/
SBIT UART_MODE        = UARTCON^7; /*uart模式设定. 0:9bit模式; 1:8bit模式*/
SBIT UART_SM21        = UARTCON^5; /*1:在9bit一对多通信模式下;0:在9bit点对点模式*/  
SBIT UART_REN1        = UARTCON^4; /*接收是能控制位.1:允许接收;0:禁止接收*/
SBIT UART_TB81        = UARTCON^3; /*在9bit模式下，the content of发送的第9bit*/
SBIT UART_RB81        = UARTCON^2;   
SBIT UART_RI             = UARTCON^0;
SBIT UART_TI             = UARTCON^1;

/* RTCCON */
SBIT RTC_START           = RTCCON^7;
SBIT RTC_CLR                = RTCCON^4;
SBIT RTC_WKEN            = RTCCON^3;   /* RTC唤醒使能;和CNT_WKEN互斥,二者只能同时打开一个 */
SBIT RTC_WKEN_SUB    = RTCCON^2;   /* FT8707D ADD , disable RTC SLOT NUM Function */
SBIT RTC_AUTO_MODE  = RTCCON^1;
SBIT RTC_WP                 = RTCCON^0;


/*SYSCON*/
SBIT REMAP                  = SYSCON^7;
SBIT OSCTEST_SEL7     = SYSCON^6;   /* output(32k/48M)cgucon7[5:0] to p0.7 */
SBIT OSCTEST_SEL6     = SYSCON^5;   /* output(32k/48M)cgucon7[5:0] to p0.6 */
SBIT WDT                      = SYSCON^4;   /* wdt使能 */
SBIT UART1                   = SYSCON^3;   /* uart1 */
SBIT UART0                   = SYSCON^2;   /* uart0: 2'b01: GPIO6; 2'b10: GPIO7; 2'b11: GPIO1.5; 2'b00: 其他;  */
SBIT LCD_LVD_PHASE   = SYSCON^1;   /* lcd_lvd的极性设置: 0:不变, 1:反相 */
SBIT LCD_ESD_PHASE   = SYSCON^0;   /* lcd_esd的极性设置: 0:不变, 1:反相 */


/*IWKSTA*/
SBIT GPIO_INT                   = IWKSTA^7; /* p0.6 pin脚中断唤醒标志*/
SBIT LCD_ESD_WK_INT     = IWKSTA^6; /* lcd esd wakeup中断唤醒标志 */
SBIT LCD_LVD_WK_INT     = IWKSTA^5; /* lcd lvd wakeup中断唤醒标志 */
SBIT LCD_GPIO_WK_INT   = IWKSTA^4; /* lcd gpio wakeup status */
SBIT LCD_RELOAD_FLASH = IWKSTA^3; /* LCD initial code reload */
SBIT ASM_MON_INT          = IWKSTA^2; /* asm monitor中断唤醒标志 */
SBIT I2C_MON_INT            = IWKSTA^1; /* i2c monitor中断唤醒标志 */
SBIT RTC_CNT_INT             = IWKSTA^0; /* RTC or CNT中断唤醒标志 */

/*SFTRST*/
SBIT SOFT_RST                = SFTRST^7;/*读:软复位标志*/
SBIT WDT_RST                 = SFTRST^6;/*读:wdt复位标志*/
SBIT EXT_RST                  = SFTRST^5;/*读:外部复位标志*/
SBIT POR_RST                  = SFTRST^4;/*por复位标志*/
SBIT FLASH_HOLD_STA   = SFTRST^3;/*flash hold state*/
SBIT REMAP_RST              = SFTRST^2;/*读:打开remap复位使能*/
/*SFTRST[0] */ /*当全写1是产生复位;全写0是产生remap复位;当读时时软复位标志*/

/* ANACON */
SBIT ARAM_SEL                = ANACON^7; /* 1: mcu控制aram; 0: afe控制aram */
SBIT LCD_DSTAB_IOLOW  = ANACON^6; /* lcd dstab发生时,控制TP到LCD DP的信号是否输出为低，从而降低漏电 1: 输出为低，0: 不输出为低*/
SBIT I2C_WK_RST            = ANACON^5;
SBIT I2C_RST                   = ANACON^4;  /* I2C module soft reset */
SBIT IOVCC_SEL               = ANACON^3;   /*1:3V;0:1.8v*/
SBIT AFE_RST                  = ANACON^2;  /*afe sub-system soft reset including asm*/
SBIT FlASH_HOLD            = ANACON^1;  /* external SPI flash hold,1:hold state '0';0:hold state '1' */
SBIT GPIO_INT_SEL         = ANACON^0;  /* FT8707D ADD ,0:GPIO2, 1:GPIO3 */

/* DSVCON */
SBIT DSV_LVDMASK      = DSVCON^1;  /*LVD mask @monitor mode. 1:no mask,LVD comes from DP;1:mask ,no LVD comes from DP*/
SBIT DSV_EN                 = DSVCON^0;  /*power gating to analog circuit.1:power gating(sync with P1.5 state);0:no power gating*/

/* DEBUGCON0 */
SBIT DEBUG_OUT_EN    = DEBUGCON0^7;/*1:output signals to GPIO[4:2],cs ,sclk ,mosi,miso,hold ,wp;0:disable*/
SBIT DEBUG_COB           = DEBUGCON0^6; /*1:w/o flash(cob),8 output;0:w/i flash,2 output (gpio[3:2])*/
/*DEBUGCON0[3:0]*/   /*debug_cob =1 debug signals selection*/

/* DEBUGCON1 */
SBIT AFE_RL_SEL         = DEBUGCON1^7; /*debug_cob=0,1:output afe_r to gpio[3:2]; 0:output afe_l to gpio[3:2]*/
SBIT AFE_TEST_EN      = DEBUGCON1^3;/*gpio2/gpio3 output selecion is controlled by afe_test_sel or gpio3_sel/gpio2_sel.1:controlled by afe_test_sel*/
/*DEBUGCON1[6:4] gpio3_sel         debug_cob=0,gpio3 selection*/
/*DEBUGCON1[2:0] gpio2_sel         debug_cob=0,gpio2 selection*/

/* PCON */
SBIT SMOD1               =PCON^7;
SBIT SMOD0               = PCON^6;
SBIT POF                    = PCON^4;
SBIT GF1                    = PCON^3;
SBIT GF0                    =PCON^2;
SBIT CORE_STOP        = PCON^1;         /* Stop 模式控制位 */
SBIT CORE_IDLE         = PCON^0;         /* Idle 模式控制位 */


/* CGUCON8 */
SBIT LDOOSC_ALLOW_EN = CGUCON8^7; /*32K osc bias selection 1:5v;0:1.8v */
//SBIT LDOOSC_SEL       = CGUCON8^0;

/* CGUCON9 */
SBIT VREF_SR_CTRL       = CGUCON9^6;
SBIT VRGEN_M_EN          = CGUCON9^4;
SBIT VRGEN_L_EN          = CGUCON9^3;
SBIT VCOM_OPT_SEL     = CGUCON9^2;


/* CGUCONA */
SBIT EN_VREF2                  = CGUCONA^7;     /*0:dynamic timing;1:always on*/
SBIT EN_VREF1                  = CGUCONA^6;    /*0:dynamic timing;1:always on*/
SBIT XDP_IBIAS_EN_BGP   = CGUCONA^5;  /*0:off;1:on*/
SBIT XDP_REG_EN_VDD18  = CGUCONA^4;  /*0:off;1:on*/
SBIT VREF_SH                     = CGUCONA^3;   /*0:vref_sh refresh 60hz;1:vref_sh always on*/
/*CGUCONA[2:0] VREF_SEL     afe reference volatge select: 111:5v;110:4.5v;101:4v;100:3.5v;011:3v;010:2.5v;001:2v;000:1.5v*/


/* CGUCONE */
SBIT BGP_MASK_EN              = CGUCONE^7;  /*1:enable bandbap mask ;0:disable bandgap mask*/
SBIT DSV_EN_ALL_ON           = CGUCONE^6;  /*1:dsv_en always on hw mode;0:dsv_en on/off controllable*/
SBIT REG_ENH_VDD_TP_N2  = CGUCONE^5; /*1:tp2xp_en_vdd_tp n1/n2 always on hw mode;0:on/off with dsv_en*/
SBIT REG_ENH_VDD_TP_N1  = CGUCONE^4; /*1.2v LDO driving capabality 1:strong ;0:weak*/
/*CGUCONE[3:0] VREF_VDD_TPS       VDDO 1.2V seting.  */

/* CGUCON0 */
//SBIT SLEEP                                = CGUCON0^7;  /* sleep mode contral */
SBIT STANDBY              = CGUCON0^6;  /* Standy mode contral */
SBIT EN_32K                = CGUCON0^5;  /*1:打开32k osc*/
//SBIT OSC48MSEL                      = CGUCON0^4;
//SBIT LCD_CLK_EN                    = CGUCON0^3;  /* 1:lcd 55M时钟开启, 0: lcd 55M时钟关闭 */
SBIT OSC48M_EN             = CGUCON0^2;  /*1:打开48m osc ; 0:关闭*/
SBIT LVD_SLEEP_EN        = CGUCON0^1; /*1.5V LD0 sleep使能.1:1.5v LDO Sleep; 0:1.5v LDO work*/
//SBIT CLKSEL                  = CGUCON0^0;

/* CGUCON1 */
SBIT SYSCKEN             = CGUCON1^7;     /* sys clk and P0 */
SBIT I2CCKEN              = CGUCON1^6;     /* i2c clk enable */
SBIT XSI1CKEN            = CGUCON1^5;     /* Xsi1 clk enable */
SBIT XBUSCKEN           = CGUCON1^4;     /* Xsi2 clk enable */
SBIT TIMERCKEN         = CGUCON1^3;
SBIT UARTCKEN           = CGUCON1^2;
SBIT DEBUGCKEN         = CGUCON1^1;     /* i2c debug clk enable */
SBIT SPI1CKEN            = CGUCON1^0;

/* CGUCON2 */

SBIT CNTCKEN            = CGUCON2^6;     /* cnt clk enable */
SBIT PROMCKEN           = CGUCON2^4;
SBIT PRAMCKEN           = CGUCON2^3;
SBIT AFEACKEN           = CGUCON2^2;     /* afe-aram clk enable */
SBIT LEDCKEN            = CGUCON2^1;     /* led clk enable */


/* CGUCON3 */
SBIT CALCKEN            = CGUCON3^6;
SBIT AFECKEN            = CGUCON3^5;     /* left and right afe clk enable */
SBIT XSI0CKEN           = CGUCON3^3;     /* Xsi0 clk enable */
SBIT AFESCKEN           = CGUCON3^2;     /* afe-scan control clk enable */
SBIT ASMCKEN            = CGUCON3^1;     /* scan control clk enable */
SBIT RTCCKEN            = CGUCON3^0;

/* CGUCON4 */
SBIT SSCG_CKEN              = CGUCON4^7;   /* sscg clk enable */
SBIT REG_CLK_EXT          = CGUCON4^6;   /* 由P0_6输入外部clk */
SBIT PROBE32K_CKEN      = CGUCON4^4;   /* probe 32K clk enable */
SBIT PROBE48M_CKEN      = CGUCON4^3;   /* probe 48M clk enable */
/*CGUCON4[2:0] clk_div  use for select frequence for div clock source*/


/* CGUCON5 for INT0 wake up */
SBIT GPIO_WKEN                             = CGUCON5^7;  /* int0 wake up enable */
SBIT LCD_ESD_WKEN                       = CGUCON5^6;  /* lcd esd wake up enble */
SBIT LCD_LVD_WKEN                       = CGUCON5^5;  /* lcd lvd wake up enble */
SBIT LCD_TIM_WKEN                        = CGUCON5^4;  /* lcd timing wake up enble */
SBIT LCD_RELOAD_FLASH_WKEN     = CGUCON5^3;  /* LCD reload flash wake up enable */
SBIT ASM_MON_WKEN                      = CGUCON5^2;  /* scan monitor wake up enable */
SBIT I2C_MON_WKEN                       = CGUCON5^1;  /* i2c monitor wake up enable */
SBIT RTC_CNT_WKEN                       = CGUCON5^0;  /* RTC or CNT wake up enable */

/* CGUCON6 */
SBIT CLK_WP                      = CGUCON6^0; /* Only CGU0 need */

/* CGUCON7 */
SBIT OSC_TEST_SEL           = CGUCON7^6; /* 在gpio口测量osc32k和osc48m时钟时的选择信号.1:32K , 0:48M */
/*CGUCON7[5:0] OSC_TEST_DIV     量测OSC48M或者32k OSC时钟时，分频洗漱配置*/

/*I2CCON*/
SBIT I2C_DEGLITCH_EN        = I2CCON^6;      /* analog deglitch enable.0:disable;1:enable */
SBIT I2C_WAKEN                   = I2CCON^5;      /* 0:disable i2c wakeup;1:enable i2c wakeup */
SBIT I2C_WAKMSB                = I2CCON^4;      /* 0:lsb first 1:deault, msb first */
SBIT I2C_BUSY                     = I2CCON^3;      /* i2c是否处于发送/接收状态.0:idle;1:busy */
SBIT I2CTI                           = I2CCON^1;      /* hw set, sw clear */
SBIT I2CRI                           = I2CCON^0;      /* hw set, sw clear */

/*I2CSTOP*/
SBIT I2C_WAIT                = I2CSTOP^7;     /* 0:释放i2c scl;1:拉低i2c scl,扩展scl周期;当slave忙时不能及时响应 */
SBIT COMP_BPSS              = I2CSTOP^6;     /*0:使能i2c地址匹配;1:取消地址匹配控制*/
SBIT ADDR_NACK              = I2CSTOP^5;     /*0:对i2c地址阶段发ack;1:对i2c地址阶段发送nack*/
SBIT DATA_NACK              = I2CSTOP^4;    /*0:对i2c数据阶段发ack;1:对i2c数据阶段发nack*/
SBIT STOPID                     = I2CSTOP^1;     /* stop状态状态位,表示当前是wr stop还是rd stop.0: host write stop 1: host read stop */
SBIT I2CSTP                     = I2CSTOP^0;     /* hw set when received right i2c stop statue,sw clear */


/*I2CSEL*/
SBIT I2C_MON_CFG            = I2CSEL^4;   /* 0: i2c工作，i2c monitor不工作; 1:i2c不工作,i2c_monitor工作 */

/*IEN1*/
SBIT SWDT                          = IEN1^6;     /*Active watchdog timer.1:active;0:idle*/

/* WDTCON */
SBIT WDTACT                      = WDTCON^2;   /* wdt work state.1:wdt in running mode; 0:wdt in stop mode */
SBIT WDTSTARTEN              = WDTCON^1;   /* when write 1,wdt start running,it is auto clear to 0 */
SBIT WDTSTOPEN                = WDTCON^0;   /* when write 1,wdt stop running,it is auto clear to 0 */

/*WDTREL*/
SBIT WDT_PRESCALE           = WDTREL^7;  /*Reload value for high-byte watchdog.1:每384个cycle计数一次;0:每24个cycle计数一次*/
/*WDTREL[6:0]    reload value for the high_seven_byte of the watchdog timer when a refresh is triggered.*/

/* TCON */
SBIT TF1 = TCON^7;               /* timer1 overflow flag：
                                   当timer1 overflows时会置1，中断响应时硬件会清零 */
SBIT TR1 = TCON^6;               /* timer1的控制位。
                                   “1”：起动timer1,硬件自动清零（注意：在起动timer1之前必须要把timer1设定好） */
SBIT TF0 = TCON^5;               /* timer0 overflow flag：
                                    当timer0 overflows时会置1，中断响应时硬件会清零 */
SBIT TR0 = TCON^4;               /* timer0的控制位。
                                   “1”：起动timer0,硬件自动清零（注意：在起动timer0之前必须要把timer0设定好） */
SBIT IE1_= TCON^3;               /* external interrupt 1 edge flag,hardware controlled
                                    set when external interrupt 1 is detected
                                    cleared when interrupt is processed */
SBIT IT1 = TCON^2;               /* external interrupt 1 signal type control bit
                                    set to specify external interrupt 1 as falling edge triggered
                                    cleared to specify external interrupt 1 as low level triggered */
SBIT IE0_= TCON^1;               /* external interrupt 0 edge flag , hardware controlled
                                    set when external interrupt 0 is detected
                                    cleared when interrupt is processed */
SBIT IT0 = TCON^0;               /* external interrupt 0 signal type control bit.
                                    Set to specify External interrupt 0 as falling edge triggered.
                                    Cleared to specify External interrupt 0 as low level triggered. */


/*TMOD*/
SBIT GATE1 = TMOD^7;  /*timer 1 gate*/
SBIT GATE0 = TMOD^3;  /*timer0 gate*/
/*TMOD[5:4] time1 mode select. 00:timer stop; 01:16 bit counter single mode; 10:16 bit counter repeat mode; 11:half timer1暂停工作,如果复原到之前的模式,timer1将继续工作*/
/*TMOD[1:0] time0 mode select.功能同上*/

/*TDIV*/
SBIT INTSEL1  = TDIV^7;   /*timer1中断清除选择.1:软件清除,写intclr1清除timer1中断;0:硬件清除*/
SBIT INTSEL0  = TDIV^6;   /*timer0中断清除选择.1:软件清除,写intclr0清除timer1中断;0:硬件清除*/
SBIT INTCLR1  = TDIV^5;   /*软件清除时,INTCLR1写1时清除timer1中断*/
SBIT INTCLR0  = TDIV^4;   /*软件清除时,INTCLR0写1时清除timer1中断*/

/* CNTCON */
SBIT CNT_START    = CNTCON^7;   /* 1: 启动CNT; 0: 计数终止(可以读取计数值) */
SBIT CNT_CLEAR    = CNTCON^4;   /* 清除CNT计数器值到0 */
SBIT CNT_WKEN_SEL = CNTCON^3;   /* CNT唤醒使能: 1:打开使能 0:关闭唤醒使能 */

/*LED_EN*/
SBIT LED_5_EN     = LED_EN^5;
SBIT LED_4_EN     = LED_EN^4;
SBIT LED_3_EN     = LED_EN^3;
SBIT LED_2_EN     =LED_EN^2;
SBIT LED_1_EN     = LED_EN^1;
SBIT LED_0_EN     = LED_EN^0;

/* AIF */
SBIT WDT_INT_IF   = AIF^4;      /* wdt int请求信号 */
SBIT SPI1_IF      = AIF^2;      /* spi1 int请求信号 */
SBIT LCD_TIM_IF   = AIF^1;
SBIT I2C_STOP_IF  = AIF^0;      /* i2c stop int请求信号 */

/* AIE */
SBIT WDT_INT_EI       = AIE^4;    /* wdt int enable */
SBIT SPI1_EI              = AIE^2;    /* spi1 int enable */
SBIT LCD_TIM_EI       = AIE^1;    /* LCD TIMING int enable */
SBIT I2C_STOP_EI     = AIE^0;    /* i2c stop int enable */  


/* IEN0 */
SBIT EA  = IEN0^7;  /* Global Interrupt Enable */
SBIT EC  = IEN0^6;  /* uart */
SBIT ET2 = IEN0^5;  /* I2C */
SBIT ES  = IEN0^4;  /* asm int */
SBIT ET1 = IEN0^3;  /* timer1 */
SBIT EX1 = IEN0^2;  /* RTC or CNT */
SBIT ET0 = IEN0^1;  /* timer0 */
SBIT EX0 = IEN0^0;  /* int0 wake up */

/* interruption priority */
SBIT IPHX0                = IPH0^0;   /* Int0 */
SBIT IPLX0                 = IPL0^0;
SBIT IPHT0                = IPH0^1;   /* Time0 */
SBIT IPLT0                 = IPL0^1;
SBIT IPHX1                 = IPH0^2;   /* Int1 */
SBIT IPLX1                 = IPL0^2;
SBIT IPHT1                  = IPH0^3;   /* Time1 */
SBIT IPLT1                  = IPL0^3;
SBIT ASM_IPH             = IPH0^4;   /* asm int run */
SBIT ASM_IPL              = IPL0^4;
SBIT I2C_IPH              = IPH0^5;   /* I2C */
SBIT I2C_IPL               = IPL0^5;
SBIT Uart_IPH             = IPH0^6;   /* Uart */
SBIT Uart_IPL             = IPL0^6;
SBIT I2C_STOP_IPH    = AIPH^0;   /* I2C stop */
SBIT I2C_STOP_IPL    = AIPL^0;
SBIT SPI1_IPH            = AIPH^2;   /* I2C stop */
SBIT SPI1_IPL            = AIPL^2;
SBIT WDT_IPH            = AIPH^4;   /* wdt */
SBIT WDT_IPL             = AIPL^4;



/* LCD_ESD_STA */
SBIT ESD_SX_R_STA    = LCD_ESD_STA^2;  /* SX(right)ESD发生状态位 */
SBIT ESD_SX_L_STA    = LCD_ESD_STA^1;  /* SX(left)ESD发生状态位 */
SBIT ESD_PWR_STA     = LCD_ESD_STA^0;  /* lcd pwr esd发生状态位 */

/* P0 */
SBIT P0_7  = P0BUF^7;
SBIT P0_6  = P0BUF^6;
SBIT P0_1  = P0BUF^1;
SBIT P0_0  = P0BUF^0;

/*p1*/
SBIT P1_5  = P1BUF^5;


/* GPIO pin definition */
SBIT Flash_WP         = P1BUF^7;
SBIT Flash_HOLD      = P1BUF^4;

SBIT Flash_pad        = P1BUF^6;
SBIT Flash_DIR        = P1DIR^6;
SBIT Flash_GPIO      = P1MOD^6;
SBIT Flash_DM         = P1SEL^6;

SBIT INTOUT               = P0BUF^6;
SBIT INTOUT_DIR       = P0DIR^6;
SBIT GPIO_INTOUT     = P0MOD^6;
SBIT INTOUT_DM        = P0SEL^6;

SBIT GPIO3                   = P0BUF^7;
SBIT GPIO3_DIR           = P0DIR^7;
SBIT GPIO3_INTOUT    = P0MOD^7;
SBIT GPIO3_DM           = P0SEL^7;

SBIT GPIO4                   = P1BUF^5;
SBIT GPIO4_DIR           = P1DIR^5;
SBIT GPIO4_INTOUT    = P1MOD^5;
SBIT GPIO4_DM            = P1SEL^5;

/* mcu clk config */
//#define MAIN_CLK  0 //0:48M; 1:24M   
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





#define PRAM_ADDR8(n)    (*((UINT8 far *)(0xFEE800 + n)))
#define PRAM2_ADDR8(n)    (*((UINT8 far *)(0xFFF000 + n)))
#define PRAM_PTR8(n)      ((volatile UINT8 *)(0xFEE800 + (n)))
#define PRAM2_PTR8(n)    ((volatile UINT8 *)(0xFFF000 + (n)))
#define PRAM3_PTR8(n)    ((volatile UINT8 *)(0xFefffe + (n)))

#define PROM_ADDR8(n)     (*((UINT8 far *)(0xFD0000 + n)))
#define DRAM_ADDR8(n)    (*((UINT8 *)(0x0000 + n)))


#define PRAM_ADDR16(n)  (*((UINT16 far *)(0xFEE800 + n)))

#define PROM_ADDR16(n)    (*((UINT16 far *)(0xFD0000 + n)))
#define DRAM_ADDR16(n)    (*((UINT16 *)(0x0000 + n)))

#define HOLD            while (1)
/*******************************************************************************
 * Global function prototypes
 *******************************************************************************/

#endif

