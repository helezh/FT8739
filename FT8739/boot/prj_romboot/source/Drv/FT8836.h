/*******************************************************************************
 * Copyright (C) 2012-2013, FocalTech Systems (R)��All Rights Reserved.
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
sfr TL0         = 0x8A;   /* �趨������ʱ���8λ������ʱ��ΪTL0[7:0]X4us,���ֵ���ܳ���1msҲ����˵���ֵΪ8��hF9,���ڴ�ֵʱ��ǿ��Ϊ8��hF9. */
sfr TL1         = 0x8B;   /* �趨������ʱ���8λ������ʱ��ΪTL1[7:0]X4us */
sfr TH0         = 0x8C;   /* �趨������ʱ���8λ������ʱ��ΪTH0[7:0]X1ms,TH0[7]����Ϊ0�������ʱ��Ϊ127ms */
sfr TH1         = 0x8D;   /* �趨������ʱ���8λ������ʱ��ΪTH1[7:0]X1ms,TH1[7]����Ϊ0�������ʱ��Ϊ127ms */

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
sfr RTCIVL      = 0x9C; /*rtc������ֹ��8λ*/      
sfr RTCIVH      = 0x9D; /*rtc������ֹ��8λ*/
sfr RTCCON      = 0x9E;
sfr RTCSLN      = 0x9F; /*rtc ʱ��Ƭ����*/

/*A0-A7*/
sfr SPI0CON       = 0xA2;
sfr SPI0CON2      = 0xA3;
sfr SPI0BUF       = 0xA4;
sfr SPI0CON3      = 0xA5;
sfr SPI0CON4      = 0xA6; 
sfr SPI0CON5      = 0xA7;

/*A8-AF*/
sfr IEN0        = 0xA8;
sfr UARTCON     = 0xA9;
sfr UARTBUF     = 0xAA;
sfr UART_RELL   = 0xAB;
sfr P0DIR       = 0xAC;   /*P0�ڷ������ã�1:���, 0:����*/
sfr P1DIR       = 0xAD;   /*P1�ڷ������ã�1:���, 0:����*/
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
sfr CNTIVL      = 0xBA;  /*CNT������ֹ��8λ*/
sfr CNTIVM      = 0xBB;  /*CNT������ֹ�м�8λ*/
sfr CNTIVH      = 0xBC;	 /*CNT������ֹ��8λ*/
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
sfr POR_STA             = 0xE6;/*POR��λ���*/
sfr RST_STA             = 0xE7;/*Pin reset��λ���*/


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
sfr PORRST_CNT         = 0xF1; /* pro rst������*/
sfr WDTRST_CNT         = 0xF2; /* wdt rst������*/
sfr EXTRST_CNT         = 0xF3; /* ext rst������*/
sfr LCDRST_CNT         = 0xF4; /* lcd rst������*/
sfr SSCG_CON0          = 0xF5;
sfr SSCG_CON1          = 0xF6; /* sscg_step:sscg increase/decrease period(500us/step). sscg trim code will increase in every(500ns*(step+1))*/
sfr AIPH               = 0xF7;

/*F8-FF*/
sfr AIPL                = 0xF8;
sfr DBGCON0             = 0xF9; /*xram_en[7:0]=AAʱ,Enable���xram access mode(ʹ��i2c debug��acess��xram memory space)*/
sfr DBGCON1             = 0xFA; /*Ҫaccess��xram_addr��λ*/ 
sfr DBGCON2             = 0xFB; /*Ҫaccess��xram_addr��λ*/
sfr DBGCON3             = 0xFC; /*д���byteʱ,��д�뵽�ڲ��ݴ�xram_data[15:8]��;����ʱ,��byteΪxram_addr[14:0]λ�õ�����ֵxram_rdata[15:8]*/
sfr DBGCON4             = 0xFD;	/*д���byteʱ,��д�뵽�ڲ��ݴ�xram_data[7:0]��;����ʱ,��byteΪxram_addr[14:0]λ�õ�����ֵxram_rdata[7:0]*/
sfr LED_EN              = 0xFE;   /* 4��LED��ʹ��; bit3~bit0��Ч,ÿbit�ֱ��Ӧһ��LEDʹ�� */
sfr LED_H_NUM           = 0xFF;   /* led PWM���ߵ�ƽ��������������0~63���䣬0����1��32k���ڸߵ�ƽ��63����64��32k���ڸߵ�ƽ����һֱΪ�ߣ�*/


/******************************************************************************/
/* bit Registers */

/*SSCG_CON0*/
/*bit5-4  sscg_amp */   /*sscg amplitude. Control the output sequence of DA_TRIM[2:0]. Clock stable time between each trim code is located in range 100ns-200ns*/
sbit SSCG_SCAN_EN     = SSCG_CON0^1; /*0:stop sscg when scan 1:contiune sscg when scan(sync with scan)*/
sbit SSCG_EN          = SSCG_CON0^0; /*0:disable sscg  1:enable sscg*/

/*SPI0CON*/
sbit SPI0RX_OVF_FLAG        = SPI0CON^6;  /*rx_reg_overflow��־λ��spi0����������rx_regΪ��ʱ��Ӳ����1*/
sbit SPI0TX_UNF_FLAG        = SPI0CON^5;  /*tx_reg_underflow��־λ��spi0��������ʱrx_regΪ��ʱ��Ӳ����1*/
sbit SPI0_START             = SPI0CON^4;  /*SPI0��slvel�½�����ʱΪ�ߵ�ƽ���������*/
sbit SPI0_STOP              = SPI0CON^3;  /*SPI0��slvel��������ʱΪ�ߵ�ƽ���������*/
sbit DMA_END_FLAG           = SPI0CON^2;  /*DMA���������ж������־λ���������*/
sbit SPI0RI                 = SPI0CON^1;  /*��������ж������־λ*/
sbit SPI0TI                 = SPI0CON^0;  /*���������жϱ�־λ*/

/*SPI0CON2*/
sbit SPI0TX_AUTO_CLR        = SPI0CON2^7; /*�Ƿ��Զ����ti�жϱ�־λ��0:��Ҫ����壻1:�����дtx_regʱӲ���Զ���*/
sbit SPI0RX_AUTO_CLR        = SPI0CON2^6; /*�Ƿ��Զ����ri�жϱ�־λ. 0:��Ҫ�����; 1:����ڶ�rx_regʱӲ���Զ���*/
sbit SPI0_EDGE_SEL          = SPI0CON2^5; /*0:sck���������;1:sck�½������*/
sbit SPI0_BUSY              = SPI0CON2^4; /*0:�͵�ƽ״̬��ֻ�ܶ�����д;1:SPI0���ڼ���״̬*/
sbit SPI0_STOP_EI           = SPI0CON2^3; /*spi_stop�ж������ź�ʹ��*/
sbit DMA_END_EI             = SPI0CON2^2; /*DMA���������ж�����ʹ��*/
sbit SPI0RI_EN              = SPI0CON2^1; /*0:��ֹ���������ж������ź�;1:������������ж������ź�*/
sbit SPI0TI_EN              = SPI0CON2^0; /*0:��ֹ���������ж������ź�;1:������������ж������ź�*/

/*SPI0CON3*/
sbit SPI0_WKEN              = SPI0CON3^7; /*spi wake up����ʹ��λ.0:disable;1:enable*/
/*spi0con3[3:0] dummy_byte_num cs�½��ؿ�ʼ�����dummy byte��*/

/*SPI0CON4*/
/*SPI0CON4[7:6] byte_num_rd_sel  byte_num����ѡ��.2'b00:byte_num_h; 2'b01:byte_num_m; 2'b10:byte_num_l */
/*SPI0CON4[5:0] byte_num_rd byte_num 6bit,��byte_num����*/

/*SPI0CON5*/
sbit SPI0RX_OVF_CLR         = SPI0CON5^6;  /*д1���rx_reg_overflow��־λ*/
sbit SPI0TX_UNF_CLR         = SPI0CON5^5;  /*д1���tx_reg_underflow��־λ*/
sbit SPI0_START_CLR         = SPI0CON5^4;  /*д1���spi0 start*/
sbit SPI0_STOP_CLR          = SPI0CON5^3;  /*д1���spi0 stop*/
sbit DMA_END_CLR            = SPI0CON5^2;  /*д1���dma end flag*/
sbit SPI0RI_CLR             = SPI0CON5^1;  /*д1���SPI0RT*/
sbit SPI0TI_CLR             = SPI0CON5^0;  /*д1���SPI0TI*/


/*SPICLKDIV: 000:4��Ƶ;001:6��Ƶ;010:8��Ƶ;011:12��Ƶ;100:16��Ƶ;101:18��Ƶ;110:20��Ƶ;111:24��Ƶ*/
/*SPI1CON*/
sbit SPI1TI           = SPI1CON^7; /*���������жϱ�־λ*/
sbit SPI1RI           = SPI1CON^6;  /*��������ж������־λ*/
sbit SPI1CKM          = SPI1CON^5;  /*SPI1CLKDIV�м�λ*/
sbit SPI1CKL          = SPI1CON^4;  /*SPI1CLKDIV��λ*/
sbit SPI1PH           = SPI1CON^3; /*0:ֱ�ӷ�������,������cycle��������;1:ֱ�ӽ�������,������cycle��������*/
sbit SPI1PO           = SPI1CON^2; /*0:low idle; 1:high idle*/
sbit SPI1MAS          = SPI1CON^1; /*0:slave mode; 1:master mode*/ 
sbit SPI1_SLVSLELEN   = SPI1CON^0; /*0:masterģʽ�µ�slvselo���ڲ���������;1:masterģʽ��slvselo��SPI1CON2[2]����*/


/*SPI1CON2*/
sbit SPI1TX_AUTO_CLR = SPI1CON2^7; /*0:����Զ���ri�жϱ�־λ;1:����ڶ�rx regʱӲ������*/
sbit SPI1RX_AUTO_CLR = SPI1CON2^6; /*0:����Զ���ti�жϱ�־λ;1:����ڶ�tx regʱӲ������*/
sbit SPI1_BUSY        = SPI1CON2^5; /*0:�͵�ƽ״̬,ֻ�ܶ�;1:SPI1������active*/ 
sbit SPI1_STOP        = SPI1CON2^4; 
sbit SPI1_START      = SPI1CON2^3;
sbit SPI1SLVELO      = SPI1CON2^2; /*��SPI1CON[0]Ϊ1ʱ,master״̬�¸�λֱ�����SPI1��slvsel����SPI1CON[0]Ϊ0ʱ����λ��Ч*/
sbit SPI1RI_EN       = SPI1CON2^1; /*0:��ֹ���������ж������ź�;1:������������ж������ź�*/
sbit SPI1TI_EN       = SPI1CON2^0; /*0:��ֹ���������ж������ź�;1:������������ж������ź�*/

/*SPI1CON3*/
sbit SPI1MODE_SELH   = SPI1CON3^7; /*1:��IO0-IO2��������;0:����SPI1CON3[6]״̬����*/
sbit SPI1MODE_SELL   = SPI1CON3^6; /*��SPI1MODE_SELHΪ0,��0:��IO0����;1:��IO0,IO1����*/
sbit SPI1_SW_IO_ENH  = SPI1CON3^5; /*IO0,IO1�������λ. 0:standard spi IO setting;1:����IO0,IO1�����Զ��л�,�л�ʱ���reg����spi_dat_opn_num*/
sbit SPI1_SW_IO_ENL  = SPI1CON3^4; /*IO2,IO3�������λ. 0:standard spi IO setting;1:����IO2,IO3�����Զ��л�,�л�ʱ���reg����spi_dat_opn_num*/
sbit SW_1BYTE_LATER  = SPI1CON3^2; /*dual/quad spi����л�ʱ��.0:�����л�;1:���¸�byte���ݴ�������Ժ�ĵ�һ��shift_out_sck_edg֮ǰ����л�*/
sbit SPI1_SW_DIR     = SPI1CON3^1; /*dual/quad spiʱ����л�io�ķ���.0:���;1:����*/
sbit SPI1_SW_EN      = SPI1CON3^0; /*dual/quad spi ���io�����л�ʹ�ܣ�д1��Ч.Ӳ�����л�֮������*/

/*SPI1CON4*/
sbit IOSW_CKDLY_EN = SPI1CON4^4; /*����IO�л�����ʱ 0:�л�������ʱ;1:�л������ӳ�2��clk cycle*/
sbit SPI1CKH            = SPI1CON4^2; /*SPI1CLKDIV��λ*/

/*spi1con[1:0] sample_phase_sel*/ /*����ʱ���ӳ�ѡ��. 00:���ӳ�;01:�ӳ�1��clk cycle; 10:�ӳ�2��clk cycle; 11:�ӳ�3��clk cycle*/


/*UARTCON*/
sbit UART_MODE        = UARTCON^7; /*uartģʽ�趨. 0:9bitģʽ; 1:8bitģʽ*/
sbit UART_SM21        = UARTCON^5; /*1:��9bitһ�Զ�ͨ��ģʽ��;0:��9bit��Ե�ģʽ*/  
sbit UART_REN1        = UARTCON^4; /*�������ܿ���λ.1:�������;0:��ֹ����*/
sbit UART_TB81        = UARTCON^3; /*��9bitģʽ�£�the content of���͵ĵ�9bit*/
sbit UART_RB81        = UARTCON^2;   
sbit UART_TI          = UARTCON^1;
sbit UART_RI          = UARTCON^0;

/* RTCCON */
sbit RTC_START        = RTCCON^7;
sbit RTC_CLR          = RTCCON^4;
sbit RTC_WKEN         = RTCCON^3;   /* RTC����ʹ��;��CNT_WKEN����,����ֻ��ͬʱ��һ�� */
sbit RTC_WKEN_SUB       = RTCCON^2;   /* FT8707D ADD , disable RTC SLOT NUM Function */
sbit RTC_AUTO_MODE   = RTCCON^1;
sbit RTC_WP           = RTCCON^0;


/*SYSCON*/
sbit REMAP            = SYSCON^7;
sbit OSCTEST_SEL7     = SYSCON^6;   /* output(32k/48M)cgucon7[5:0] to p0.7 */
sbit BUS_SEL          = SYSCON^5;   /* output(32k/48M)cgucon7[5:0] to p0.6 */
sbit WDT              = SYSCON^4;   /* wdtʹ�� */
sbit UART1            = SYSCON^3;   /* uart1 */
sbit UART0            = SYSCON^2;   /* uart0: 2'b01: GPIO6; 2'b10: GPIO7; 2'b11: GPIO1.5; 2'b00: ����;  */
sbit LCD_LVD_PHASE    = SYSCON^1;   /* lcd_lvd�ļ�������: 0:����, 1:���� */
sbit LCD_ESD_PHASE    = SYSCON^0;   /* lcd_esd�ļ�������: 0:����, 1:���� */


/*IWKSTA*/
sbit GPIO_INT          = IWKSTA^7; /* p0.6 pin���жϻ��ѱ�־*/
sbit LCD_ESD_WK_INT   = IWKSTA^6; /* lcd esd wakeup�жϻ��ѱ�־ */
sbit LCD_LVD_WK_INT   = IWKSTA^5; /* lcd lvd wakeup�жϻ��ѱ�־ */
sbit LCD_GPIO_WK_INT  = IWKSTA^4; /* lcd gpio wakeup status */
sbit LCD_RELOAD_FLASH = IWKSTA^3; /* LCD initial code reload */
sbit ASM_MON_INT      = IWKSTA^2; /* asm monitor�жϻ��ѱ�־ */
sbit I2C_MON_INT      = IWKSTA^1; /* i2c monitor�жϻ��ѱ�־ */
sbit RTC_CNT_INT      = IWKSTA^0; /* RTC or CNT�жϻ��ѱ�־ */

/*SFTRST*/
sbit SOFT_RST         = SFTRST^7;/*��:��λ��־*/
sbit WDT_RST          = SFTRST^6;/*��:wdt��λ��־*/
sbit EXT_RST          = SFTRST^5;/*��:�ⲿ��λ��־*/
sbit POR_RST          = SFTRST^4;/*por��λ��־*/
sbit FLASH_HOLD_STA   = SFTRST^3;/*flash hold state*/
sbit REMAP_RST        = SFTRST^1;/*��:��remap��λʹ��*/
/*SFTRST[0] */ /*��ȫд1�ǲ�����λ;ȫд0�ǲ���remap��λ;����ʱʱ��λ��־*/

/* ANACON */
sbit ARAM_SEL          = ANACON^7; /* 1: mcu����aram; 0: afe����aram */
sbit LCD_DSTAB_IOLOW  = ANACON^6; /* lcd dstab����ʱ,����TP��LCD DP���ź��Ƿ����Ϊ�ͣ��Ӷ�����©�� 1: ���Ϊ�ͣ�0: �����Ϊ��*/
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
sbit CORE_STOP     = PCON^1;         /* Stop ģʽ����λ */
sbit CORE_IDLE     = PCON^0;         /* Idle ģʽ����λ */


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
sbit EN_32K               = CGUCON0^5;  /*1:��32k osc*/
sbit CLKEN_32K4SPI0       = CGUCON0^4;  /* SPI0 DMAģ���е�counterʱ��gating*/
sbit SPI0CKEN             = CGUCON0^3;  /* SPI0����ʱ�ӵ�enable gating */
sbit OSC48M_EN            = CGUCON0^2;  /*1:��48m osc ; 0:�ر�*/
sbit LVD_SLEEP_EN         = CGUCON0^1; /*1.5V LD0 sleepʹ��.1:1.5v LDO Sleep; 0:1.5v LDO work*/
//sbit CLKSEL                              = CGUCON0^0;

/* CGUCON1 */
sbit SYSCKEN            = CGUCON1^7;     /* sys clk and P0 */
sbit I2CCKEN            = CGUCON1^6;     /* i2c clk enable */
sbit XSI1CKEN           = CGUCON1^5;     /* Xsi1 clk enable */
sbit HW_MON_KEEP        = CGUCON1^4;     /* HW_MON_KEEP clk enable */
sbit TIMERCKEN          = CGUCON1^3;
sbit UARTCKEN           = CGUCON1^2;
sbit DEBUGCKEN          = CGUCON1^1;     /* i2c debug clk enable */
sbit SPI1CKEN           = CGUCON1^0;

/* CGUCON2 */
sbit CLKEN_500K         = CGUCON2^7;     /* 500k clock gating enable*/
sbit CNTCKEN            = CGUCON2^6;     /* cnt clk enable */
sbit CKEN_32KLED        = CGUCON2^5;     /* Led controller working clock*/
sbit PROMCKEN           = CGUCON2^4;
sbit PRAMCKEN           = CGUCON2^3;
sbit AFEACKEN           = CGUCON2^2;     /* afe-aram clk enable */
sbit LEDCKEN            = CGUCON2^1;     /* led clk enable */
sbit CKEN_32KRTC        = CGUCON2^0;     /* RTC Working clock*/

/* CGUCON3 */
sbit CALCKEN            = CGUCON3^6;
sbit AFECKEN            = CGUCON3^5;     /* left and right afe clk enable */
sbit XBUSCKEN           = CGUCON3^3;     /* XBUS clk enable */
sbit AFESCKEN           = CGUCON3^2;     /* afe-scan control clk enable */
sbit ASMCKEN            = CGUCON3^1;     /* scan control clk enable */
sbit RTCCKEN            = CGUCON3^0;

/* CGUCON4 */
sbit SSCG_CKEN          = CGUCON4^7;   /* sscg clk enable */
sbit CLKEN_TP4_500k     = CGUCON4^6;   /* CLK_500K��gating enable */
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
sbit OSC_TEST_SEL           = CGUCON7^6; /* ��gpio�ڲ���osc32k��osc48mʱ��ʱ��ѡ���ź�.1:32K , 0:48M */
/*CGUCON7[5:0] OSC_TEST_DIV     ����OSC48M����32k OSCʱ��ʱ����Ƶϴ������*/

/*I2CCON*/
sbit I2C_DEGLITCH_EN        = I2CCON^6;      /* analog deglitch enable.0:disable;1:enable */
sbit I2C_WAKEN              = I2CCON^5;      /* 0:disable i2c wakeup;1:enable i2c wakeup */
sbit I2C_WAKMSB             = I2CCON^4;      /* 0:lsb first 1:deault, msb first */
sbit I2C_BUSY               = I2CCON^3;      /* i2c�Ƿ��ڷ���/����״̬.0:idle;1:busy */
sbit I2CTI                  = I2CCON^1;      /* hw set, sw clear */
sbit I2CRI                  = I2CCON^0;      /* hw set, sw clear */

/*I2CSTOP*/
sbit I2C_WAIT               = I2CSTOP^7;     /* 0:�ͷ�i2c scl;1:����i2c scl,��չscl����;��slaveæʱ���ܼ�ʱ��Ӧ */
sbit COMP_BPSS              = I2CSTOP^6;     /*0:ʹ��i2c��ַƥ��;1:ȡ����ַƥ�����*/
sbit ADDR_NACK              = I2CSTOP^5;     /*0:��i2c��ַ�׶η�ack;1:��i2c��ַ�׶η���nack*/
sbit DATA_NACK              = I2CSTOP^4;		/*0:��i2c���ݽ׶η�ack;1:��i2c���ݽ׶η�nack*/
sbit STOPID                 = I2CSTOP^1;     /* stop״̬״̬λ,��ʾ��ǰ��wr stop����rd stop.0: host write stop 1: host read stop */
sbit I2CSTP                 = I2CSTOP^0;     /* hw set when received right i2c stop statue,sw clear */


/*I2CSEL*/
sbit I2C_MON_CFG            = I2CSEL^4;   /* 0: i2c������i2c monitor������; 1:i2c������,i2c_monitor���� */

/*IEN1*/
sbit SWDT                   = IEN1^6;     /*Active watchdog timer.1:active;0:idle*/

/* WDTCON */
sbit WDTACT                 = WDTCON^2;   /* wdt work state.1:wdt in running mode; 0:wdt in stop mode */
sbit WDTSTARTEN             = WDTCON^1;   /* when write 1,wdt start running,it is auto clear to 0 */
sbit WDTSTOPEN              = WDTCON^0;   /* when write 1,wdt stop running,it is auto clear to 0 */

/*WDTREL*/
sbit WDT_PRESCALE           = WDTREL^7;  /*Reload value for high-byte watchdog.1:ÿ384��cycle����һ��;0:ÿ24��cycle����һ��*/
/*WDTREL[6:0]    reload value for the high_seven_byte of the watchdog timer when a refresh is triggered.*/

/* TCON */
sbit TF1 = TCON^7;               /* timer1 overflow flag��
                                   ��timer1 overflowsʱ����1���ж���ӦʱӲ�������� */
sbit TR1 = TCON^6;               /* timer1�Ŀ���λ��
                                   ��1������timer1,Ӳ���Զ����㣨ע�⣺����timer1֮ǰ����Ҫ��timer1�趨�ã� */
sbit TF0 = TCON^5;               /* timer0 overflow flag��
                                    ��timer0 overflowsʱ����1���ж���ӦʱӲ�������� */
sbit TR0 = TCON^4;               /* timer0�Ŀ���λ��
                                   ��1������timer0,Ӳ���Զ����㣨ע�⣺����timer0֮ǰ����Ҫ��timer0�趨�ã� */
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
/*TMOD[5:4] time1 mode select. 00:timer stop; 01:16 bit counter single mode; 10:16 bit counter repeat mode; 11:half timer1��ͣ����,�����ԭ��֮ǰ��ģʽ,timer1����������*/
/*TMOD[1:0] time0 mode select.����ͬ��*/

/*TDIV*/
sbit INTSEL1  = TDIV^7;   /*timer1�ж����ѡ��.1:������,дintclr1���timer1�ж�;0:Ӳ�����*/
sbit INTSEL0  = TDIV^6;   /*timer0�ж����ѡ��.1:������,дintclr0���timer1�ж�;0:Ӳ�����*/
sbit INTCLR1  = TDIV^5;   /*������ʱ,INTCLR1д1ʱ���timer1�ж�*/
sbit INTCLR0  = TDIV^4;   /*������ʱ,INTCLR0д1ʱ���timer1�ж�*/

/* CNTCON */
sbit CNT_START    = CNTCON^7;   /* 1: ����CNT; 0: ������ֹ(���Զ�ȡ����ֵ) */
sbit CNT_CLEAR    = CNTCON^4;   /* ���CNT������ֵ��0 */
sbit CNT_WKEN_SEL = CNTCON^3;   /* CNT����ʹ��: 1:��ʹ�� 0:�رջ���ʹ�� */

/*LED_EN*/
sbit LED_5_EN     = LED_EN^5;
sbit LED_4_EN     = LED_EN^4;
sbit LED_3_EN     = LED_EN^3;
sbit LED_2_EN     = LED_EN^2;
sbit LED_1_EN     = LED_EN^1;
sbit LED_0_EN     = LED_EN^0;

/* AIF */
sbit WDT_INT_IF   = AIF^4;      /* wdt int�����ź� */
sbit SPI0_INT_IF  = AIF^3;      /* spi0 int�����ź� */
sbit SPI1_IF      = AIF^2;      /* spi1 int�����ź� */
sbit ASM_INT_IF   = AIF^1;      /* asm int�����ź� */
sbit I2C_STOP_IF  = AIF^0;      /* i2c stop int�����ź� */

/* AIE */
sbit WDT_INT_EI      = AIE^4;    /* wdt int enable */
sbit SPI0_EI         = AIE^3;    /* spi0 int enable */
sbit SPI1_EI         = AIE^2;    /* spi1 int enable */
sbit ASM_EI          = AIE^1;    /* Asm int enable */
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

/* interruption priority 2 */
sbit I2C_STOP_IPH    = AIPH^0;   /* I2C stop */
sbit I2C_STOP_IPL    = AIPL^0;
sbit SPI1_IPH        = AIPH^2;   /* spi1 int */
sbit SPI1_IPL        = AIPL^2;
sbit SPI0_IPH        = AIPH^3;   /* spi0 int */
sbit SPI0_IPL        = AIPL^3;
sbit WDT_IPH         = AIPH^4;   /* wdt */
sbit WDT_IPL         = AIPL^4;



/* LCD_ESD_STA */
sbit ESD_SX_R_STA    = LCD_ESD_STA^2;  /* SX(right)ESD����״̬λ */
sbit ESD_SX_L_STA    = LCD_ESD_STA^1;  /* SX(left)ESD����״̬λ */
sbit ESD_PWR_STA     = LCD_ESD_STA^0;  /* lcd pwr esd����״̬λ */

/* P0 */
sbit P0_7            = P0BUF^7;
sbit P0_6            = P0BUF^6;
sbit P0_5            = P0BUF^5;
sbit P0_4            = P0BUF^4;
sbit P0_3            = P0BUF^3;
sbit P0_2            = P0BUF^2;
sbit P0_1            = P0BUF^1;
sbit P0_0            = P0BUF^0;

/*p1*/
sbit P1_7            = P1BUF^7;
sbit P1_6            = P1BUF^6;
sbit P1_5            = P1BUF^5;
sbit P1_4            = P1BUF^4;
sbit P1_3            = P1BUF^3;
sbit P1_2            = P1BUF^2;
sbit P1_1            = P1BUF^1;
sbit P1_0            = P1BUF^0;


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

// IO�ڵ�ѹ����
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
//app ���ڵ������ַ
#define APP_ADDR_START          ((UINT32)0xFCE800)  // app start addr

#define CODE_START_ADDR         ((UINT32)0x1000)  /* 4KB��ʼ�Ǵ������λַ */
#define CODE_VERIF_ADDR         ((UINT32)(CODE_START_ADDR+APP_VERIF_ADDR))

#define APP_VERIF_ADDR          0x100   // Verification Info
#define APP_VERIF_LEN           0x20
#define APP_VERIF_CODE_LEN      0x04    //app��code������Ϣ
#define APP_CHECK_RELOAD_OFFSET 0x12
 
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
    RELOAD_OFFSET= 0X16,
} ENUM_APP_INFO;

// App��֤��Ϣ
#define ADDR_APP_LEN          (APP_VERIF_ADDR+APP_LEN)
#define ADDR_APP_NE_LEN       (APP_VERIF_ADDR+APP_NE_LEN)
#define ADDR_PART1_ECC        (APP_VERIF_ADDR+P1_ECC_H)
#define ADDR_PART1_ECC_NE     (APP_VERIF_ADDR+P1_ECC_NE_H)
#define ADDR_PART2_ECC        (APP_VERIF_ADDR+P2_ECC_H)
#define ADDR_PART2_ECC_NE     (APP_VERIF_ADDR+P2_ECC_NE_H)
#define ADDR_APP_LEN_H        (APP_VERIF_ADDR+APP_LEN_H)
#define ADDR_APP_LEN_H_NE     (APP_VERIF_ADDR+APP_LEN_H_NE)
#define LCD_RELOAD_OFFSET     (APP_VERIF_ADDR+RELOAD_OFFSET)


#define APP_ADDR_PART1_START  APP_ADDR_START
#define APP_ADDR_PART1_LEN    (APP_VERIF_ADDR)
#define APP_ADDR_PART2_OFFSET \
    ((UINT32)((APP_VERIF_ADDR)+(APP_VERIF_LEN)+(FW_CFG_TOTAL_SIZE)))

#define APP_ADDR_PART2_START  (UINT32)(APP_ADDR_START+APP_ADDR_PART2_OFFSET)


/******************************************************************************
*
* FW config data section
*******************************************************************************
/
/* FW�������򳤶� */
#define FW_CFG_TOTAL_SIZE          0x80
#define FW_CFG_INFO_SIZE           0x0E

/* FW��������ƫ���� */
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

/* FW��������Flashλ�� */
typedef enum
{
    FW_CFG_START_FLASH_ADDR        = 0x0F80,
    FW_CFG_I2C_FLASH_ADDR          = (FW_CFG_START_FLASH_ADDR+FW_CFG_I2C_OFFSET)
} ENUM_FW_CFG_FLASH_ADDR;

/* FW���ñ�������Flashλ�� */
typedef enum
{
    FW_CFG_BKUP_START_FLASH_ADDR   = 0x1120,
    FW_CFG_BKUP_I2C_FLASH_ADDR     = (FW_CFG_BKUP_START_FLASH_ADDR+FW_CFG_I2C_OFFSET)
} ENUM_FW_CFG_BKUP_FLASH_ADDR;
/******************************************************************************
*
* lcd init code section
******************************************************************************/
#define LCDINITCODE_TOTAL_SIZE      0x0F80  /* LCD Init Code���򳤶� */
#define LCDINITCODE_CRC_SIZE        0x0002  /* LCD Init Code: CRC */
#define LCDINITCODE_CODESIZE_MAX    (LCDINITCODE_TOTAL_SIZE-LCDINITCODE_CRC_SIZE) /* LCD Init Code max CodeSize */

/* LCD Init Code����ƫ���� */
typedef enum
{    
    LCDINITCODE_CODESIZE_OFFSET     = 0x00,   /* Code size */
    LCDINITCODE_CRC_OFFSET          = 0x02,   /* CRC       */ 
    LCDINITCODE_DATA_OFFSET         = 0x04,   /* DATA       */ 
} ENUM_LCDINITCODE_OFFSET;

/* LCD Init Code����Flashλ�� */
typedef enum
{
    LCDINITCODE_START_FLASH_ADDR     = 0x0000,
    LCDINITCODE_CRC_FLASH_ADDR       = (LCDINITCODE_START_FLASH_ADDR+LCDINITCODE_CRC_OFFSET),
    LCDINITCODE_DATA_START_ADDR      = (LCDINITCODE_START_FLASH_ADDR+LCDINITCODE_DATA_OFFSET),    
} ENUM_LCDINITCODE_FLASH_ADDR;
//-----------------------------------------------------------------------------
// flash
#define FW_CFG_ADDR           FW_CFG_I2C_FLASH_ADDR //FW_CFGλַ
#define FW_I2C_SLAVE_ADDR     0x00
#define FW_VENDOR_ADDR        0x04
#define FLASH_APP_INFO        (APP_VERIF_ADDR + CODE_START_ADDR)
//-----------------------------------------------------------------------------
#define APP_DATA_MAX         ((UINT32)0x11800)
#define APP_DATA_MIN         ((UINT32)0x01800)
#define RST_VALUE_UPGRADE    0x6B  //������־

/*****************************************************************************/

//��pram������С�Ĳ���
#define PRAM_ADDR8(n)   *((UINT8 far  *) ((UINT32)0xFCE800 + (n)))//(0xFDE800 + n)))
#define PRAM2_ADDR8(n)  *((UINT8 far  *) ((UINT32)0xFD0000 + (n)))
#define PRAM_ADDR16(n)  *((UINT16 far *) ((UINT32)0xFCE800 + (n)))
#define PRAM_ADDR32(n)  *((UINT32 far *) ((UINT32)0xFCE800 + (n)))

#define PRAM_PTR8(n)     ((UINT8 far  *) ((UINT32)0xFCE800 + (n)))

#define DRAM_ADDR8(n)   *((UINT8 far  *) ((UINT32)(n)))
#define DRAM_ADDR16(n)  *((UINT16 far *) ((UINT32)(n)))

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

