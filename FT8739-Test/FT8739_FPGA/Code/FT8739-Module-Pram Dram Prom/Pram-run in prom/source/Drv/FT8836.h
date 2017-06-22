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
 *            Architecture Variants Bit Address Memory/sfr Address Comments
 *            -------------------------------------------------------------------
 *            MCS251       Memory -- NA ------- 20H.0-7FH.7        does not have
 *            (bit)        sfr ----- NA ------- All defined SFRs   bit addresses
 *            -------------------------------------------------------------------
 *            MCS 51       Memory -- 00H-7FH -- 20H.0-7FH.7        not all SFRs
 *            (bit51)      sfr ----- 80H-F8H -- XXH.0-XXH.7, where have bit
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
sfr P0BUF          = 0x80;   /*PoBuf*/
sfr SP          = 0x81; 
sfr DPL         = 0x82;
sfr DPH         = 0x83;
sfr DPXL        = 0x84;
sfr PCON        = 0x87;

/*88-8F*/
sfr TCON        = 0x88;
sfr TMOD        = 0x89;
sfr TL0         = 0x8A;   /* 设定计数器时间低8位，计数时间为TL0[7:0]X4us,最大值不能超过1ms也就是说最大值为8’hF9,大于此值时将强制为8’hF9. */
sfr TL1         = 0x8B;   /* 设定计数器时间低8位，计数时间为TL1[7:0]X4us */
sfr TH0         = 0x8C;   /* 设定计数器时间高8位，计数时间为TH0[7:0]X1ms,TH0[7]必须为0，所以最长时间为127ms */
sfr TH1         = 0x8D;   /* 设定计数器时间高8位，计数时间为TH1[7:0]X1ms,TH1[7]必须为0，所以最长时间为127ms */

/*90-97*/
sfr I2CCON      = 0x90;
sfr I2CBUF      = 0x91;
sfr I2CADDR     = 0x92;
sfr I2CSTOP     = 0x93;
sfr P1BUF       = 0x94;   /*P1Buf*/
sfr I2CSEL      = 0x95;
sfr MMCON       = 0x97;

/*98-9F*/
sfr SYSCON      = 0x98;
sfr WDTCON      = 0x99;
sfr WDTREL      = 0x9A;
sfr TDIV        = 0x9B;
sfr RTCIVL      = 0x9C; /*rtc计数终止低8位*/      
sfr RTCIVH      = 0x9D; /*rtc计数终止高8位*/
sfr RTCCON      = 0x9E;
sfr RTCSLN      = 0x9F; /*rtc 时间片个数*/

/*A0-A7*/

/*A8-AF*/
sfr IEN0        = 0xA8;
sfr UARTCON     = 0xA9;
sfr UARTBUF     = 0xAA;
sfr UART_RELL   = 0xAB;
sfr P0DIR       = 0xAC;   /*P0口方向配置，1:输出, 0:输入*/
sfr P1DIR       = 0xAD;   /*P1口方向配置，1:输出, 0:输入*/
sfr UART_RELH   = 0xAE;
sfr UART_SDA    = 0xAF;

/*B0-B7*/
sfr SPI1CON3    = 0xB1;
sfr SPI1CON4    = 0xB2;
sfr SPI1CON     = 0xB3;
sfr SPI1CON2    = 0xB4;
sfr SPI1BUF     = 0xB5;
sfr IPH0        = 0xB7; 

/*B8-BF*/
sfr IPL0         = 0xB8;
sfr CNTCON      = 0xB9;
sfr CNTIVL      = 0xBA;  /*CNT计数终止低8位*/
sfr CNTIVM      = 0xBB;  /*CNT计数终止中间8位*/
sfr CNTIVH      = 0xBC;	 /*CNT计数终止高8位*/
sfr SPH         = 0xBE;

/*C0-C7*/
sfr AIF          = 0xC0;
sfr CGUCON8     = 0xC1;
sfr CGUCON9     = 0xC2;
sfr CGUCONA     = 0xC3;
sfr CGUCONB     = 0xC4;
sfr CGUCONC     = 0xC5;
sfr CGUCOND     = 0xC6;
sfr CGUCONE     = 0xC7;

/*C8-CF*/
sfr CGUCON1     = 0xC8;
sfr CGUCON0     = 0xC9;
sfr CGUCON2     = 0xCA;
sfr CGUCON3     = 0xCB;
sfr CGUCON4     = 0xCC;
sfr CGUCON5     = 0xCD;
sfr CGUCON6     = 0xCE;
sfr CGUCON7     = 0xCF;

/* D1-D7 */
sfr MEMBIST_EN_ID1     = 0xD2;
sfr MEMBIST_EN_ID2     = 0xD3;
sfr MEMBIST_FINISH_ID1 = 0xD4;
sfr MEMBIST_FINISH_ID2 = 0xD5;
sfr MEMBIST_FAIL_ID1   = 0xD6;
sfr MEMBIST_FAIL_ID2   = 0xD7;

/* D8-DF */
sfr MEMBIST_ERRMAP_ID1 = 0xD8;
sfr MEMBIST_ERRMAP_ID2 = 0xD9;
//sfr TRIMOSC_CON         = 0xDA;
//sfr TRIMOSC_CFG1        = 0xDB;
//sfr TRIMOSC_CFG2        = 0xDC;
sfr MEMBIST_ROMCRCH_ID = 0xDD;
sfr MEMBIST_ROMCRCL_ID = 0xDE;
sfr IEN1                = 0xDF;

/*E0-E7*/
sfr DSVCON              = 0xE1;
sfr DEBUGCON0           = 0xE2;
sfr DEBUGCON1           = 0xE3;
sfr I2CSAD              = 0xE4;
sfr IWKSTA              = 0xE5;
sfr POR_STA             = 0xE6;/*POR复位检查*/
sfr RST_STA             = 0xE7;/*Pin reset复位检查*/


/*E8-EF*/
sfr AIE                 = 0xE8;
sfr SFTRST              = 0xE9;
sfr ANACON              = 0xEA;
sfr P0MOD               = 0xEB;/*0:P0 use as gpio;1:po use as function define*/
sfr P0SEL               = 0xEC;/*0:P0 as OD port; 1:P0 as PUSH-PULL port*/
sfr P1MOD               = 0xED;/*0:P1 use as gpio;1:p1 use as function define*/
sfr P1SEL               = 0xEE;/*0:P1 as OD port; 1:P1 as PUSH-PULL port*/
sfr LCD_ESD_STA        = 0xEF;

/*F0-F7*/
sfr SSCG_CON0          = 0xF4;
sfr SSCG_CON1          = 0xF5; /*sscg_step:sscg increase/decrease period(500us/step). sscg trim code will increase in every(500ns*(step+1))*/
sfr AIPH                = 0xF7;

/*F8-FF*/
sfr AIPL                = 0xF8;
sfr DBGCON0             = 0xF9; /*xram_en[7:0]=AA时,Enable间接xram access mode(使用i2c debug可acess到xram memory space)*/
sfr DBGCON1             = 0xFA; /*要access的xram_addr高位*/ 
sfr DBGCON2             = 0xFB; /*要access的xram_addr低位*/
sfr DBGCON3             = 0xFC; /*写入此byte时,会写入到内部暂存xram_data[15:8]内;读出时,此byte为xram_addr[14:0]位置的内容值xram_rdata[15:8]*/
sfr DBGCON4             = 0xFD;	/*写入此byte时,会写入到内部暂存xram_data[7:0]内;读出时,此byte为xram_addr[14:0]位置的内容值xram_rdata[7:0]*/
sfr LED_EN              = 0xFE;   /* 4个LED灯使能; bit3~bit0有效,每bit分别对应一个LED使能 */
sfr LED_H_NUM           = 0xFF;   /* led PWM波高电平持续的周期数，0~63可配，0代表1个32k周期高电平，63代表64个32k周期高电平，即一直为高；*/


/******************************************************************************/
/* bit Registers */

/*SSCG_CON0*/
/*bit5-4  sscg_amp */   /*sscg amplitude. Control the output sequence of DA_TRIM[2:0]. Clock stable time between each trim code is located in range 100ns-200ns*/
sbit SSCG_SCAN_EN     = SSCG_CON0^1; /*0:stop sscg when scan 1:contiune sscg when scan(sync with scan)*/
sbit SSCG_EN          = SSCG_CON0^0; /*0:disable sscg  1:enable sscg*/


/*SPICLKDIV: 000:4分频;001:6分频;010:8分频;011:12分频;100:16分频;101:18分频;110:20分频;111:24分频*/
/*SPI1CON*/
sbit SPI1TI           = SPI1CON^7; /*发送请求中断标志位*/
sbit SPI1RI           = SPI1CON^6;  /*接收完毕中断请求标志位*/
sbit SPI1CKM          = SPI1CON^5;  /*SPI1CLKDIV中间位*/
sbit SPI1CKL          = SPI1CON^4;  /*SPI1CLKDIV低位*/
sbit SPI1PH           = SPI1CON^3; /*0:直接发送数据,缓存半个cycle接收数据;1:直接接收数据,缓存半个cycle发送数据*/
sbit SPI1PO           = SPI1CON^2; /*0:low idle; 1:high idle*/
sbit SPI1MAS          = SPI1CON^1; /*0:slave mode; 1:master mode*/ 
sbit SPI1_SLVSLELEN  = SPI1CON^0; /*0:master模式下的slvselo受内部启动控制;1:master模式下slvselo受SPI1CON2[2]控制*/


/*SPI1CON2*/
sbit SPI1RX_AUTO_CLR = SPI1CON2^7; /*0:软件自动清ri中断标志位;1:软件在读rx reg时硬件自清*/
sbit SPI1TX_AUTO_CLR = SPI1CON2^6; /*0:软件自动清ti中断标志位;1:软件在读tx reg时硬件自清*/
sbit SPI1_BUSY        = SPI1CON2^5; /*0:低电平状态,只能读;1:SPI1正处于active*/ 
sbit SPI1_STOP        = SPI1CON2^4; 
sbit SPI1_START      = SPI1CON2^3;
sbit SPI1SLVELO      = SPI1CON2^2; /*当SPI1CON[0]为1时,master状态下该位直接输出SPI1的slvsel；当SPI1CON[0]为0时，该位无效*/
sbit SPI1RI_EN       = SPI1CON2^1; /*0:禁止产生接收中断请求信号;1:允许产生接收中断请求信号*/
sbit SPI1TI_EN       = SPI1CON2^0; /*0:禁止产生接收中断请求信号;1:允许产生接收中断请求信号*/

/*SPI1CON3*/
sbit SPI1MODE_SELH   = SPI1CON3^7; /*1:用IO0-IO2传输数据;0:根据SPI1CON3[6]状态决定*/
sbit SPI1MODE_SELL   = SPI1CON3^6; /*若SPI1MODE_SELH为0,则0:用IO0传输;1:用IO0,IO1传输*/
sbit SPI1_SW_IO_ENH  = SPI1CON3^5; /*IO0,IO1方向控制位. 0:standard spi IO setting;1:控制IO0,IO1方向自动切换,切换时间参reg配置spi_dat_opn_num*/
sbit SPI1_SW_IO_ENL  = SPI1CON3^4; /*IO2,IO3方向控制位. 0:standard spi IO setting;1:控制IO2,IO3方向自动切换,切换时间参reg配置spi_dat_opn_num*/
sbit SW_1BYTE_LATER  = SPI1CON3^2; /*dual/quad spi软件切换时间.0:立即切换;1:在下个byte数据传输结束以后的第一个shift_out_sck_edg之前完成切换*/
sbit SPI1_SW_DIR     = SPI1CON3^1; /*dual/quad spi时软件切换io的方向.0:输出;1:输入*/
sbit SPI1_SW_EN      = SPI1CON3^0; /*dual/quad spi 软件io方向切换使能，写1有效.硬件在切换之后自清*/

/*SPI1CON4*/
sbit SPI1IOSW_CKDLY_EN = SPI1CON4^4; /*传输IO切换方向时 0:切换方向不延时;1:切换方向延长2个clk cycle*/
sbit SPI1CKH            = SPI1CON4^2; /*SPI1CLKDIV高位*/

/*spi1con[1:0] sample_phase_sel*/ /*采样时钟延迟选择. 00:无延迟;01:延迟1个clk cycle; 10:延迟2个clk cycle; 11:延迟3个clk cycle*/


/*UARTCON*/
sbit UART_MODE        = UARTCON^7; /*uart模式设定. 0:9bit模式; 1:8bit模式*/
sbit UART_SM21        = UARTCON^5; /*1:在9bit一对多通信模式下;0:在9bit点对点模式*/  
sbit UART_REN1        = UARTCON^4; /*接收是能控制位.1:允许接收;0:禁止接收*/
sbit UART_TB81        = UARTCON^3; /*在9bit模式下，the content of发送的第9bit*/
sbit UART_RB81        = UARTCON^2;   
sbit UART_TI          = UARTCON^1;
sbit UART_RI          = UARTCON^0;

/* RTCCON */
sbit RTC_START        = RTCCON^7;
sbit RTC_CLR          = RTCCON^4;
sbit RTC_WKEN         = RTCCON^3;   /* RTC唤醒使能;和CNT_WKEN互斥,二者只能同时打开一个 */
sbit RTC_WKEN_SUB    = RTCCON^2;   /* FT8707D ADD , disable RTC SLOT NUM Function */
sbit RTC_AUTO_MODE   = RTCCON^1;
sbit RTC_WP           = RTCCON^0;


/*SYSCON*/
sbit REMAP            = SYSCON^7;
sbit OSCTEST_SEL7    = SYSCON^6;   /* output(32k/48M)cgucon7[5:0] to p0.7 */
sbit OSCTEST_SEL6    = SYSCON^5;   /* output(32k/48M)cgucon7[5:0] to p0.6 */
sbit WDT              = SYSCON^4;   /* wdt使能 */
sbit UART1            = SYSCON^3;   /* uart1 */
sbit UART0            = SYSCON^2;   /* uart0: 2'b01: GPIO6; 2'b10: GPIO7; 2'b11: GPIO1.5; 2'b00: 其他;  */
sbit LCD_LVD_PHASE   = SYSCON^1;   /* lcd_lvd的极性设置: 0:不变, 1:反相 */
sbit LCD_ESD_PHASE   = SYSCON^0;   /* lcd_esd的极性设置: 0:不变, 1:反相 */


/*IWKSTA*/
sbit GPIO_INT          = IWKSTA^7; /* p0.6 pin脚中断唤醒标志*/
sbit LCD_ESD_WK_INT   = IWKSTA^6; /* lcd esd wakeup中断唤醒标志 */
sbit LCD_LVD_WK_INT   = IWKSTA^5; /* lcd lvd wakeup中断唤醒标志 */
sbit LCD_GPIO_WK_INT  = IWKSTA^4; /* lcd gpio wakeup status */
sbit LCD_RELOAD_FLASH = IWKSTA^3; /* LCD initial code reload */
sbit ASM_MON_INT       = IWKSTA^2; /* asm monitor中断唤醒标志 */
sbit I2C_MON_INT      = IWKSTA^1; /* i2c monitor中断唤醒标志 */
sbit RTC_CNT_INT      = IWKSTA^0; /* RTC or CNT中断唤醒标志 */

/*SFTRST*/
sbit SOFT_RST         = SFTRST^7;/*读:软复位标志*/
sbit WDT_RST          = SFTRST^6;/*读:wdt复位标志*/
sbit EXT_RST          = SFTRST^5;/*读:外部复位标志*/
sbit POR_RST          = SFTRST^4;/*por复位标志*/
sbit FLASH_HOLD_STA   = SFTRST^3;/*flash hold state*/
sbit REMAP_RST        = SFTRST^2;/*读:打开remap复位使能*/
/*SFTRST[0] */ /*当全写1是产生复位;全写0是产生remap复位;当读时时软复位标志*/

/* ANACON */
sbit ARAM_SEL          = ANACON^7; /* 1: mcu控制aram; 0: afe控制aram */
sbit LCD_DSTAB_IOLOW  = ANACON^6; /* lcd dstab发生时,控制TP到LCD DP的信号是否输出为低，从而降低漏电 1: 输出为低，0: 不输出为低*/
sbit I2C_WK_RST        = ANACON^5;
sbit I2C_RST           = ANACON^4;  /* I2C module soft reset */
sbit IOVCC_SEL         = ANACON^3;   /*1:3V;0:1.8v*/
sbit AFE_RST           = ANACON^2;	  /*afe sub-system soft reset including asm*/
sbit FlASH_HOLD       = ANACON^1;  /* external SPI flash hold,1:hold state '0';0:hold state '1' */
sbit GPIO_INT_SEL     = ANACON^0;  /* FT8707D ADD ,0:GPIO2, 1:GPIO3 */

/* DSVCON */
sbit DSV_LVDMASK      = DSVCON^1;  /*LVD mask @monitor mode. 1:no mask,LVD comes from DP;1:mask ,no LVD comes from DP*/
sbit DSV_EN            = DSVCON^0;  /*power gating to analog circuit.1:power gating(sync with P1.5 state);0:no power gating*/

/* DEBUGCON0 */
sbit DEBUG_OUT_EN    = DEBUGCON0^7;/*1:output signals to GPIO[4:2],cs ,sclk ,mosi,miso,hold ,wp;0:disable*/
sbit DEBUG_COB       = DEBUGCON0^6; /*1:w/o flash(cob),8 output;0:w/i flash,2 output (gpio[3:2])*/
/*DEBUGCON0[3:0]*/   /*debug_cob =1 debug signals selection*/

/* DEBUGCON1 */
sbit AFE_RL_SEL       = DEBUGCON1^7; /*debug_cob=0,1:output afe_r to gpio[3:2]; 0:output afe_l to gpio[3:2]*/
sbit AFE_TEST_EN      = DEBUGCON1^3;/*gpio2/gpio3 output selecion is controlled by afe_test_sel or gpio3_sel/gpio2_sel.1:controlled by afe_test_sel*/
/*DEBUGCON1[6:4] gpio3_sel         debug_cob=0,gpio3 selection*/
/*DEBUGCON1[2:0] gpio2_sel         debug_cob=0,gpio2 selection*/

/* PCON */
sbit SMOD1          =PCON^7;
sbit SMOD0          = PCON^6;
sbit POF            = PCON^4;
sbit GF1            = PCON^3;
sbit GF0            =PCON^2;
sbit CORE_STOP     = PCON^1;         /* Stop 模式控制位 */
sbit CORE_IDLE     = PCON^0;         /* Idle 模式控制位 */


/* CGUCON8 */
sbit LDOOSC_ALLOW_EN = CGUCON8^7; /*32K osc bias selection 1:5v;0:1.8v */
//sbit LDOOSC_SEL       = CGUCON8^0;

/* CGUCON9 */
sbit VREF_SR_CTRL    = CGUCON9^6;
sbit VRGEN_M_EN      = CGUCON9^4;
sbit VRGEN_L_EN      = CGUCON9^3;
sbit VCOM_OPT_SEL    = CGUCON9^2;


/* CGUCONA */
sbit EN_VREF2           = CGUCONA^7;     /*0:dynamic timing;1:always on*/
sbit EN_VREF1           = CGUCONA^6;    /*0:dynamic timing;1:always on*/
sbit XDP_IBIAS_EN_BGP  = CGUCONA^5;  /*0:off;1:on*/
sbit XDP_REG_EN_VDD18  = CGUCONA^4;  /*0:off;1:on*/
sbit VREF_SH            = CGUCONA^3;   /*0:vref_sh refresh 60hz;1:vref_sh always on*/
/*CGUCONA[2:0] VREF_SEL     afe reference volatge select: 111:5v;110:4.5v;101:4v;100:3.5v;011:3v;010:2.5v;001:2v;000:1.5v*/


/* CGUCONE */
sbit BGP_MASK_EN        = CGUCONE^7;  /*1:enable bandbap mask ;0:disable bandgap mask*/
sbit DSV_EN_ALL_ON      = CGUCONE^6;  /*1:dsv_en always on hw mode;0:dsv_en on/off controllable*/
sbit REG_ENH_VDD_TP_N2  = CGUCONE^5; /*1:tp2xp_en_vdd_tp n1/n2 always on hw mode;0:on/off with dsv_en*/
sbit REG_ENH_VDD_TP_N1  = CGUCONE^4; /*1.2v LDO driving capabality 1:strong ;0:weak*/
/*CGUCONE[3:0] VREF_VDD_TPS       VDDO 1.2V seting.  */

/* CGUCON0 */
//sbit SLEEP                                = CGUCON0^7;  /* sleep mode contral */
sbit STANDBY              = CGUCON0^6;  /* Standy mode contral */
sbit EN_32K               = CGUCON0^5;  /*1:打开32k osc*/
//sbit OSC48MSEL                      = CGUCON0^4;
//sbit LCD_CLK_EN                    = CGUCON0^3;  /* 1:lcd 55M时钟开启, 0: lcd 55M时钟关闭 */
sbit OSC48M_EN           = CGUCON0^2;  /*1:打开48m osc ; 0:关闭*/
sbit LVD_SLEEP_EN        = CGUCON0^1; /*1.5V LD0 sleep使能.1:1.5v LDO Sleep; 0:1.5v LDO work*/
//sbit CLKSEL                              = CGUCON0^0;

/* CGUCON1 */
sbit SYSCKEN            = CGUCON1^7;     /* sys clk and P0 */
sbit I2CCKEN            = CGUCON1^6;     /* i2c clk enable */
sbit XSI1CKEN           = CGUCON1^5;     /* Xsi1 clk enable */
sbit XBUSCKEN           = CGUCON1^4;     /* Xsi2 clk enable */
sbit TIMERCKEN          = CGUCON1^3;
sbit UARTCKEN           = CGUCON1^2;
sbit DEBUGCKEN          = CGUCON1^1;     /* i2c debug clk enable */
sbit SPI1CKEN           = CGUCON1^0;

/* CGUCON2 */

sbit CNTCKEN            = CGUCON2^6;     /* cnt clk enable */
sbit PROMCKEN           = CGUCON2^4;
sbit PRAMCKEN           = CGUCON2^3;
sbit AFEACKEN           = CGUCON2^2;     /* afe-aram clk enable */
sbit LEDCKEN            = CGUCON2^1;     /* led clk enable */


/* CGUCON3 */
sbit CALCKEN            = CGUCON3^6;
sbit AFECKEN            = CGUCON3^5;     /* left and right afe clk enable */
sbit XSI0CKEN           = CGUCON3^3;     /* Xsi0 clk enable */
sbit AFESCKEN           = CGUCON3^2;     /* afe-scan control clk enable */
sbit ASMCKEN            = CGUCON3^1;     /* scan control clk enable */
sbit RTCCKEN            = CGUCON3^0;

/* CGUCON4 */
sbit SSCG_CKEN          = CGUCON4^7;   /* sscg clk enable */
sbit REG_CLK_EXT        = CGUCON4^6;   /* 由P0_6输入外部clk */
sbit PROBE32K_CKEN      = CGUCON4^4;   /* probe 32K clk enable */
sbit PROBE48M_CKEN      = CGUCON4^3;   /* probe 48M clk enable */
/*CGUCON4[2:0] clk_div  use for select frequence for div clock source*/


/* CGUCON5 for INT0 wake up */
sbit GPIO_WKEN                  = CGUCON5^7;  /* int0 wake up enable */
sbit LCD_ESD_WKEN               = CGUCON5^6;  /* lcd esd wake up enble */
sbit LCD_LVD_WKEN               = CGUCON5^5;  /* lcd lvd wake up enble */
sbit LCD_TIM_WKEN               = CGUCON5^4;  /* lcd timing wake up enble */
sbit LCD_RELOAD_FLASH_WKEN     = CGUCON5^3;  /* LCD reload flash wake up enable */
sbit ASM_MON_WKEN               = CGUCON5^2;  /* scan monitor wake up enable */
sbit I2C_MON_WKEN               = CGUCON5^1;  /* i2c monitor wake up enable */
sbit RTC_CNT_WKEN               = CGUCON5^0;  /* RTC or CNT wake up enable */

/* CGUCON6 */
sbit CLK_WP                 = CGUCON6^0; /* Only CGU0 need */

/* CGUCON7 */
sbit OSC_TEST_SEL           = CGUCON7^6; /* 在gpio口测量osc32k和osc48m时钟时的选择信号.1:32K , 0:48M */
/*CGUCON7[5:0] OSC_TEST_DIV     量测OSC48M或者32k OSC时钟时，分频洗漱配置*/

/*I2CCON*/
sbit I2C_DEGLITCH_EN        = I2CCON^6;      /* analog deglitch enable.0:disable;1:enable */
sbit I2C_WAKEN              = I2CCON^5;      /* 0:disable i2c wakeup;1:enable i2c wakeup */
sbit I2C_WAKMSB             = I2CCON^4;      /* 0:lsb first 1:deault, msb first */
sbit I2C_BUSY               = I2CCON^3;      /* i2c是否处于发送/接收状态.0:idle;1:busy */
sbit I2CTI                  = I2CCON^1;      /* hw set, sw clear */
sbit I2CRI                  = I2CCON^0;      /* hw set, sw clear */

/*I2CSTOP*/
sbit I2C_WAIT               = I2CSTOP^7;     /* 0:释放i2c scl;1:拉低i2c scl,扩展scl周期;当slave忙时不能及时响应 */
sbit COMP_BPSS              = I2CSTOP^6;     /*0:使能i2c地址匹配;1:取消地址匹配控制*/
sbit ADDR_NACK              = I2CSTOP^5;     /*0:对i2c地址阶段发ack;1:对i2c地址阶段发送nack*/
sbit DATA_NACK              = I2CSTOP^4;		/*0:对i2c数据阶段发ack;1:对i2c数据阶段发nack*/
sbit STOPID                 = I2CSTOP^1;     /* stop状态状态位,表示当前是wr stop还是rd stop.0: host write stop 1: host read stop */
sbit I2CSTP                 = I2CSTOP^0;     /* hw set when received right i2c stop statue,sw clear */


/*I2CSEL*/
sbit I2C_MON_CFG            = I2CSEL^4;   /* 0: i2c工作，i2c monitor不工作; 1:i2c不工作,i2c_monitor工作 */

/*IEN1*/
sbit SWDT                   = IEN1^6;     /*Active watchdog timer.1:active;0:idle*/

/* WDTCON */
sbit WDTACT                 = WDTCON^2;   /* wdt work state.1:wdt in running mode; 0:wdt in stop mode */
sbit WDTSTARTEN             = WDTCON^1;   /* when write 1,wdt start running,it is auto clear to 0 */
sbit WDTSTOPEN              = WDTCON^0;   /* when write 1,wdt stop running,it is auto clear to 0 */

/*WDTREL*/
sbit WDT_PRESCALE           = WDTREL^7;  /*Reload value for high-byte watchdog.1:每384个cycle计数一次;0:每24个cycle计数一次*/
/*WDTREL[6:0]    reload value for the high_seven_byte of the watchdog timer when a refresh is triggered.*/

/* TCON */
sbit TF1 = TCON^7;               /* timer1 overflow flag：
                                   当timer1 overflows时会置1，中断响应时硬件会清零 */
sbit TR1 = TCON^6;               /* timer1的控制位。
                                   “1”：起动timer1,硬件自动清零（注意：在起动timer1之前必须要把timer1设定好） */
sbit TF0 = TCON^5;               /* timer0 overflow flag：
                                    当timer0 overflows时会置1，中断响应时硬件会清零 */
sbit TR0 = TCON^4;               /* timer0的控制位。
                                   “1”：起动timer0,硬件自动清零（注意：在起动timer0之前必须要把timer0设定好） */
sbit IE1_= TCON^3;               /* external interrupt 1 edge flag,hardware controlled
                                    set when external interrupt 1 is detected
                                    cleared when interrupt is processed */
sbit IT1 = TCON^2;               /* external interrupt 1 signal type control bit
                                    set to specify external interrupt 1 as falling edge triggered
                                    cleared to specify external interrupt 1 as low level triggered */
sbit IE0_= TCON^1;               /* external interrupt 0 edge flag , hardware controlled
                                    set when external interrupt 0 is detected
                                    cleared when interrupt is processed */
sbit IT0 = TCON^0;               /* external interrupt 0 signal type control bit.
                                    Set to specify External interrupt 0 as falling edge triggered.
                                    Cleared to specify External interrupt 0 as low level triggered. */

									
/*TMOD*/
sbit GATE1 = TMOD^7;  /*timer 1 gate*/
sbit GATE0 = TMOD^3;  /*timer0 gate*/
/*TMOD[5:4] time1 mode select. 00:timer stop; 01:16 bit counter single mode; 10:16 bit counter repeat mode; 11:half timer1暂停工作,如果复原到之前的模式,timer1将继续工作*/
/*TMOD[1:0] time0 mode select.功能同上*/

/*TDIV*/
sbit INTSEL1  = TDIV^7;   /*timer1中断清除选择.1:软件清除,写intclr1清除timer1中断;0:硬件清除*/
sbit INTSEL0  = TDIV^6;   /*timer0中断清除选择.1:软件清除,写intclr0清除timer1中断;0:硬件清除*/
sbit INTCLR1  = TDIV^5;   /*软件清除时,INTCLR1写1时清除timer1中断*/
sbit INTCLR0  = TDIV^4;   /*软件清除时,INTCLR0写1时清除timer1中断*/

/* CNTCON */
sbit CNT_START    = CNTCON^7;   /* 1: 启动CNT; 0: 计数终止(可以读取计数值) */
sbit CNT_CLEAR    = CNTCON^4;   /* 清除CNT计数器值到0 */
sbit CNT_WKEN_SEL = CNTCON^3;   /* CNT唤醒使能: 1:打开使能 0:关闭唤醒使能 */

/*LED_EN*/
sbit LED_5_EN     = LED_EN^5;
sbit LED_4_EN     = LED_EN^4;
sbit LED_3_EN     = LED_EN^3;
sbit LED_2_EN     = LED_EN^2;
sbit LED_1_EN     = LED_EN^1;
sbit LED_0_EN     = LED_EN^0;

/* AIF */
sbit WDT_INT_IF   = AIF^4;      /* wdt int请求信号 */
sbit SPI1_IF      = AIF^2;      /* spi1 int请求信号 */
sbit LCD_TIM_IF   = AIF^1;
sbit I2C_STOP_IF  = AIF^0;      /* i2c stop int请求信号 */

/* AIE */
sbit WDT_INT_EI      = AIE^4;    /* wdt int enable */
sbit SPI1_EI         = AIE^2;    /* spi1 int enable */
sbit LCD_TIM_EI      = AIE^1;    /* LCD TIMING int enable */
sbit I2C_STOP_EI     = AIE^0;    /* i2c stop int enable */  


/* IEN0 */
sbit EA  = IEN0^7;  /* Global Interrupt Enable */
sbit EC  = IEN0^6;  /* uart */
sbit ET2 = IEN0^5;  /* I2C */
sbit ES  = IEN0^4;  /* asm int */
sbit ET1 = IEN0^3;  /* timer1 */
sbit EX1 = IEN0^2;  /* RTC or CNT */
sbit ET0 = IEN0^1;  /* timer0 */
sbit EX0 = IEN0^0;  /* int0 wake up */

/* interruption priority */
sbit IPHX0           = IPH0^0;   /* Int0 */
sbit IPLX0           = IPL0^0;
sbit IPHT0           = IPH0^1;   /* Time0 */
sbit IPLT0           = IPL0^1;
sbit IPHX1           = IPH0^2;   /* Int1 */
sbit IPLX1           = IPL0^2;
sbit IPHT1           = IPH0^3;   /* Time1 */
sbit IPLT1           = IPL0^3;
sbit ASM_IPH         = IPH0^4;   /* asm int run */
sbit ASM_IPL         = IPL0^4;
sbit I2C_IPH         = IPH0^5;   /* I2C */
sbit I2C_IPL         = IPL0^5;
sbit Uart_IPH        = IPH0^6;   /* Uart */
sbit Uart_IPL        = IPL0^6;
sbit I2C_STOP_IPH    = AIPH^0;   /* I2C stop */
sbit I2C_STOP_IPL    = AIPL^0;
sbit SPI1_IPH        = AIPH^2;   /* I2C stop */
sbit SPI1_IPL        = AIPL^2;
sbit WDT_IPH         = AIPH^4;   /* wdt */
sbit WDT_IPL         = AIPL^4;



/* LCD_ESD_STA */
sbit ESD_SX_R_STA    = LCD_ESD_STA^2;  /* SX(right)ESD发生状态位 */
sbit ESD_SX_L_STA    = LCD_ESD_STA^1;  /* SX(left)ESD发生状态位 */
sbit ESD_PWR_STA     = LCD_ESD_STA^0;  /* lcd pwr esd发生状态位 */

/* P0 */
sbit P0_7  = P0BUF^7;
sbit P0_6  = P0BUF^6;
sbit P0_2  = P0BUF^2;
sbit P0_1  = P0BUF^1;
sbit P0_0  = P0BUF^0;

/*p1*/
sbit P1_5  = P1BUF^5;


/* GPIO pin definition */
sbit Flash_WP        = P1BUF^7;
sbit Flash_HOLD      = P1BUF^4;

sbit Flash_pad       = P1BUF^6;
sbit Flash_DIR       = P1DIR^6;
sbit Flash_GPIO      = P1MOD^6;
sbit Flash_DM        = P1SEL^6;

sbit INTOUT          = P0BUF^6;
sbit INTOUT_DIR      = P0DIR^6;
sbit GPIO_INTOUT     = P0MOD^6;
sbit INTOUT_DM       = P0SEL^6;

sbit GPIO3           = P0BUF^7;
sbit GPIO3_DIR       = P0DIR^7;
sbit GPIO3_INTOUT    = P0MOD^7;
sbit GPIO3_DM        = P0SEL^7;

sbit GPIO4           = P1BUF^5;
sbit GPIO4_DIR       = P1DIR^5;
sbit GPIO4_INTOUT    = P1MOD^5;
sbit GPIO4_DM        = P1SEL^5;

// IO口电压设置
#define IO_VCC_33        1    // 0 --1.8v  1 -- 3.3V

#define INT_EN           0
#define INT_DIS          1

#define DIR_OUT          1
#define DIR_IN           0

#define G_USAGE          0
#define S_USAGE          1

#define DM_PP            1
#define DM_OD            0

#define ON               1
#define OFF              0
/*****************************************************************************/
//app 存在的物理地址
#define APP_ADDR_START          0x0000  // app start addr

#define CODE_START_ADDR         0x2000  /* 8KB开始是代码20151103更新位址 */
#define CODE_VERIF_ADDR         (CODE_START_ADDR+APP_VERIF_ADDR)

#define APP_VERIF_ADDR          0x100   // Verification Info
#define APP_VERIF_LEN           0x20
#define APP_VERIF_CODE_LEN      0x04    //app中code长度信息
#define APP_CHECK_RELOAD_OFFSET 0x12

#define FW_SPI_CLK_ADDR         (FW_CFG_ADDR+6)
#define FW_SYS_CLK_ADDR         (FW_CFG_ADDR+8)
#define FW_LCD_REL_SEL_ADDR     (FW_CFG_ADDR+12)
#define FW_LCD_CRC_ADDR         (FW_CFG_ADDR+14)

typedef enum
{
    APP_LEN_H    = 0,
    APP_LEN_L    = 1,
    APP_NE_LEN_H = 2,
    APP_NE_LEN_L = 3,
    P1_ECC_H     = 4,
    P1_ECC_L     = 5,
    P1_ECC_NE_H  = 6,
    P1_ECC_NE_L  = 7,
    P2_ECC_H     = 8,
    P2_ECC_L     = 9,
    P2_ECC_NE_H  = 0x0A,
    P2_ECC_NE_L  = 0x0B,
    VENDER_ID    = 0x0C,
    VENDER_ID_NE = 0x0D,
    FW_VERSION   = 0x0E,
    FW_VERSION_NE= 0x0F,
    UP_FLAG      = 0x10,
    UP_FLAG_NE   = 0x11,

    PBOOT_ID_H   = 0x1E,
    PBOOT_ID_L   = 0x1F
} ENUM_APP_INFO;

#define ADDR_APP_LEN_H       (APP_VERIF_ADDR+APP_LEN_H)
#define ADDR_APP_LEN_L       (APP_VERIF_ADDR+APP_LEN_L)
#define ADDR_APP_NE_LEN_H    (APP_VERIF_ADDR+APP_NE_LEN_H)
#define ADDR_APP_NE_LEN_L    (APP_VERIF_ADDR+APP_NE_LEN_L)
#define ADDR_PART1_ECC       (APP_VERIF_ADDR+P1_ECC_H)
#define ADDR_PART1_ECC_NE    (APP_VERIF_ADDR+P1_ECC_NE_H)
#define ADDR_PART2_ECC       (APP_VERIF_ADDR+P2_ECC_H)
#define ADDR_PART2_ECC_NE    (APP_VERIF_ADDR+P2_ECC_NE_H)
#define ADDR_PANEL_ID        (APP_VERIF_ADDR+VENDER_ID)
#define ADDR_PANEL_ID_NE     (APP_VERIF_ADDR+VENDER_ID_NE)
#define ADDR_VERSION         (APP_VERIF_ADDR+FW_VERSION)
#define ADDR_VERSION_NE      (APP_VERIF_ADDR+FW_VERSION_NE)
#define ADDR_UPGRADE_FLG1    (APP_VERIF_ADDR+UP_FLAG)
#define ADDR_UPGRADE_FLG2    (APP_VERIF_ADDR+UP_FLAG_NE)

#define APP_ADDR_PART1_START  0x0000
#define APP_ADDR_PART1_LEN    ((APP_VERIF_ADDR)-(APP_ADDR_PART1_START))
#define APP_ADDR_PART2_START  ((APP_VERIF_ADDR)+(APP_VERIF_LEN))
//-----------------------------------------------------------------------------
// flash
#define FW_CFG_ADDR           0x1F80 //20151103更新FW_CFG位址
#define FW_I2C_SLAVE_ADDR     0x00
#define FW_VENDOR_ADDR        0x04
#define FLASH_APP_INFO        (APP_VERIF_ADDR + CODE_START_ADDR)
//-----------------------------------------------------------------------------
#define APP_DATA_MAX         (0xFFFE)

#define RST_VALUE_UPGRADE    0x6B  //升级标志

/*****************************************************************************/
//对pram操作，小心操作
#define PRAM_ADDR8(n)   (*((UINT8 far  *)  (0xFCE800 + n)))//(0xFDE800 + n)))
#define PRAM2_ADDR8(n)   (*((UINT8 far  *)  (0xFd0000 + n)))
#define PRAM_ADDR16(n)  (*((UINT16 far *)(0xFCE800 + (n))))
#define PRAM_ADDR32(n)  (*((UINT32 far *)(0xFCE800 + n)))

#define REG8(n)         (*((volatile UINT8  *)(n)))
#define REG16(n)        (*((volatile UINT16 *)(n)))
#define REG32(n)        (*((volatile UINT32 *)(n)))

#define HOLD            while (1)
/******************************************************************************
*
* 3.Global structures, unions and enumerations using typedef
******************************************************************************/

/******************************************************************************
*
* 4.Global variable extern declarations
******************************************************************************/

/******************************************************************************
*
* 5.Global function prototypes
******************************************************************************/

#endif

