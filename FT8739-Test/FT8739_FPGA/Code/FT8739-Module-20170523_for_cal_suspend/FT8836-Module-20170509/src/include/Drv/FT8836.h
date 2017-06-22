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
SFR TL0             = 0x8A;   /* �趨������ʱ���8λ������ʱ��ΪTL0[7:0]X4us,���ֵ���ܳ���1msҲ����˵���ֵΪ8��hF9,���ڴ�ֵʱ��ǿ��Ϊ8��hF9. */
SFR TL1             = 0x8B;   /* �趨������ʱ���8λ������ʱ��ΪTL1[7:0]X4us */
SFR TH0             = 0x8C;   /* �趨������ʱ���8λ������ʱ��ΪTH0[7:0]X1ms,TH0[7]����Ϊ0�������ʱ��Ϊ127ms */
SFR TH1             = 0x8D;   /* �趨������ʱ���8λ������ʱ��ΪTH1[7:0]X1ms,TH1[7]����Ϊ0�������ʱ��Ϊ127ms */

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
SFR RTCIVL          = 0x9C; /*rtc������ֹ��8λ*/      
SFR RTCIVH          = 0x9D; /*rtc������ֹ��8λ*/
SFR RTCCON          = 0x9E;
SFR RTCSLN          = 0x9F; /*rtc ʱ��Ƭ����*/

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
SFR P0DIR           = 0xAC;   /*P0�ڷ������ã�1:���, 0:����*/
SFR P1DIR           = 0xAD;   /*P1�ڷ������ã�1:���, 0:����*/
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
SFR CNTIVL          = 0xBA;  /*CNT������ֹ��8λ*/
SFR CNTIVM          = 0xBB;  /*CNT������ֹ�м�8λ*/
SFR CNTIVH          = 0xBC;  /*CNT������ֹ��8λ*/
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
SFR POR_STA             = 0xE6; /*POR��λ���*/
SFR RST_STA             = 0xE7; /*Pin reset��λ���*/


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
SFR CNT_STA             = 0xF2; /* ����cnt_mask��ֵ��������ͬ��cntֵ*/
SFR SSCG_CON0           = 0xF5;
SFR SSCG_CON1           = 0xF6; /* sscg_step:sscg increase/decrease period(500us/step). sscg trim code will increase in every(500ns*(step+1))*/
SFR AIPH                = 0xF7;

/*F8-FF*/
SFR AIPL                = 0xF8;
SFR I2C_CMD0            = 0xF9; /* i2c hid command byte1 */
SFR I2C_CMD1            = 0xFA; /* i2c hid command byte2 */
SFR I2C_CMD2            = 0xFB; /* i2c hid command byte3 */
SFR I2C_CMD3            = 0xFC; /* i2c hid command byte4 */
SFR I2C_STATE           = 0xFD; /* i2C hid �жϱ�־�Ĵ��� */
SFR LED_EN              = 0xFE; /* 4��LED��ʹ��; bit3~bit0��Ч,ÿbit�ֱ��Ӧһ��LEDʹ�� */
SFR LED_H_NUM           = 0xFF; /* led PWM���ߵ�ƽ��������������0~63���䣬0����1��32k���ڸߵ�ƽ��63����64��32k���ڸߵ�ƽ����һֱΪ�ߣ�*/


/******************************************************************************/
/* bit Registers */

/*SSCG_CON0*/
/*bit5-4  sscg_amp */   /*sscg amplitude. Control the output sequence of DA_TRIM[2:0]. Clock stable time between each trim code is located in range 100ns-200ns*/
SBIT SSCG_SCAN_EN           = SSCG_CON0^1; /*0:stop sscg when scan 1:contiune sscg when scan(sync with scan)*/
SBIT SSCG_EN                = SSCG_CON0^0; /*0:disable sscg  1:enable sscg*/

/*SPI0CON*/
SBIT SPI0RX_OVF_FLAG        = SPI0CON^6;  /*rx_reg_overflow��־λ��spi0����������rx_regΪ��ʱ��Ӳ����1*/
SBIT SPI0TX_UNF_FLAG        = SPI0CON^5;  /*tx_reg_underflow��־λ��spi0��������ʱrx_regΪ��ʱ��Ӳ����1*/
SBIT SPI0_START             = SPI0CON^4;  /*SPI0��slvel�½�����ʱΪ�ߵ�ƽ���������*/
SBIT SPI0_STOP              = SPI0CON^3;  /*SPI0��slvel��������ʱΪ�ߵ�ƽ���������*/
SBIT DMA_END_FLAG           = SPI0CON^2;  /*DMA���������ж������־λ���������*/
SBIT SPI0RI                 = SPI0CON^1;  /*��������ж������־λ*/
SBIT SPI0TI                 = SPI0CON^0;  /*���������жϱ�־λ*/

/*SPI0CON2*/
SBIT SPI0TX_AUTO_CLR        = SPI0CON2^7; /*�Ƿ��Զ����ti�жϱ�־λ��0:��Ҫ����壻1:�����дtx_regʱӲ���Զ���*/
SBIT SPI0RX_AUTO_CLR        = SPI0CON2^6; /*�Ƿ��Զ����ri�жϱ�־λ. 0:��Ҫ�����; 1:����ڶ�rx_regʱӲ���Զ���*/
SBIT SPI0_EDGE_SEL          = SPI0CON2^5; /*0:sck���������;1:sck�½������*/
SBIT SPI0_BUSY              = SPI0CON2^4; /*0:�͵�ƽ״̬��ֻ�ܶ�����д;1:SPI0���ڼ���״̬*/
SBIT SPI0_STOP_EI           = SPI0CON2^3; /*spi_stop�ж������ź�ʹ��*/
SBIT DMA_END_EI             = SPI0CON2^2; /*DMA���������ж�����ʹ��*/
SBIT SPI0RI_EN              = SPI0CON2^1; /*0:��ֹ���������ж������ź�;1:������������ж������ź�*/
SBIT SPI0TI_EN              = SPI0CON2^0; /*0:��ֹ���������ж������ź�;1:������������ж������ź�*/

/*SPI0CON3*/
SBIT SPI0_WKEN              = SPI0CON3^7; /*spi wake up����ʹ��λ.0:disable;1:enable*/
SBIT SPI0_RI_PULSE_SEL      = SPI0CON3^4; /*0:rx_reg load at ti_ri_pulse falling edg;1:rx_reg load at ri_pulse rising edge*/
//SBIT SPI0_CLR_NUM           = SPI0CON3^4; /*write 1 to clear byte num*/
/*spi0con3[3:0] dummy_byte_num cs�½��ؿ�ʼ�����dummy byte��*/

/*SPI0CON4*/
/*SPI0CON4[7:6] byte_num_rd_sel  byte_num����ѡ��.2'b00:byte_num_h; 2'b01:byte_num_m; 2'b10:byte_num_l */
/*SPI0CON4[5:0] byte_num_rd byte_num 6bit,��byte_num����*/

/*SPI0CON5*/
SBIT SPI0RX_OVF_CLR         = SPI0CON5^6;  /*д1���rx_reg_overflow��־λ*/
SBIT SPI0TX_UNF_CLR         = SPI0CON5^5;  /*д1���tx_reg_underflow��־λ*/
SBIT SPI0_START_CLR         = SPI0CON5^4;  /*д1���spi0 start*/
SBIT SPI0_STOP_CLR          = SPI0CON5^3;  /*д1���spi0 stop*/
SBIT DMA_END_CLR            = SPI0CON5^2;  /*д1���dma end flag*/
SBIT SPI0RI_CLR             = SPI0CON5^1;  /*д1���SPI0RT*/
SBIT SPI0TI_CLR             = SPI0CON5^0;  /*д1���SPI0TI*/


/*SPICLKDIV: 000:4��Ƶ;001:6��Ƶ;010:8��Ƶ;011:12��Ƶ;100:16��Ƶ;101:18��Ƶ;110:20��Ƶ;111:24��Ƶ*/
/*SPI1CON*/
SBIT SPI1TI                  = SPI1CON^7;  /*���������жϱ�־λ*/
SBIT SPI1RI                  = SPI1CON^6;  /*��������ж������־λ*/
SBIT SPI1CKM                 = SPI1CON^5;  /*SPI1CLKDIV�м�λ*/
SBIT SPI1CKL                 = SPI1CON^4;  /*SPI1CLKDIV��λ*/
SBIT SPI1PH                  = SPI1CON^3;  /*0:ֱ�ӷ�������,������cycle��������;1:ֱ�ӽ�������,������cycle��������*/
SBIT SPI1PO                  = SPI1CON^2;  /*0:low idle; 1:high idle*/
SBIT SPI1MAS                 = SPI1CON^1;  /*0:slave mode; 1:master mode*/ 
SBIT SPI1_SLVSLELEN          = SPI1CON^0;  /*0:masterģʽ�µ�slvselo���ڲ���������;1:masterģʽ��slvselo��SPI1CON2[2]����*/

/*SPI1CON2*/
SBIT SPI1TX_AUTO_CLR         = SPI1CON2^7; /*0:����Զ���ti�жϱ�־λ;1:����ڶ�rx regʱӲ������*/
SBIT SPI1RX_AUTO_CLR         = SPI1CON2^6; /*0:����Զ���ri�жϱ�־λ;1:����ڶ�tx regʱӲ������*/
SBIT SPI1_BUSY               = SPI1CON2^5; /*0:�͵�ƽ״̬,ֻ�ܶ�;1:SPI1������active*/ 
SBIT SPI1_STOP               = SPI1CON2^4; 
SBIT SPI1_START              = SPI1CON2^3;
SBIT SPI1SLVELO              = SPI1CON2^2; /*��SPI1CON[0]Ϊ1ʱ,master״̬�¸�λֱ�����SPI1��slvsel����SPI1CON[0]Ϊ0ʱ����λ��Ч*/
SBIT SPI1RI_EN               = SPI1CON2^1; /*0:��ֹ���������ж������ź�;1:������������ж������ź�*/
SBIT SPI1TI_EN               = SPI1CON2^0; /*0:��ֹ���������ж������ź�;1:������������ж������ź�*/

/*SPI1CON3*/
SBIT SPI1MODE_SELH           = SPI1CON3^7; /*1:��IO0-IO2��������;0:����SPI1CON3[6]״̬����*/
SBIT SPI1MODE_SELL           = SPI1CON3^6; /*��SPI1MODE_SELHΪ0,��0:��IO0����;1:��IO0,IO1����*/
SBIT SPI1_SW_IO_ENH          = SPI1CON3^5; /*IO0,IO1�������λ. 0:standard spi IO setting;1:����IO0,IO1�����Զ��л�,�л�ʱ���reg����spi_dat_opn_num*/
SBIT SPI1_SW_IO_ENL          = SPI1CON3^4; /*IO2,IO3�������λ. 0:standard spi IO setting;1:����IO2,IO3�����Զ��л�,�л�ʱ���reg����spi_dat_opn_num*/
SBIT SW_1BYTE_LATER          = SPI1CON3^2; /*dual/quad spi����л�ʱ��.0:�����л�;1:���¸�byte���ݴ�������Ժ�ĵ�һ��shift_out_sck_edg֮ǰ����л�*/
SBIT SPI1_SW_DIR             = SPI1CON3^1; /*dual/quad spiʱ����л�io�ķ���.0:���;1:����*/
SBIT SPI1_SW_EN              = SPI1CON3^0; /*dual/quad spi ���io�����л�ʹ�ܣ�д1��Ч.Ӳ�����л�֮������*/

/*SPI1CON4*/
SBIT SPI1IOSW_CKDLY_EN      = SPI1CON4^4; /*����IO�л�����ʱ 0:�л�������ʱ;1:�л������ӳ�2��clk cycle*/
SBIT SPI1_CURR_MODE         = SPI1CON4^3; /*spi master/slave mode״̬λ.1:ĿǰΪmaster mode.0:Ŀǰδslave mode */
SBIT SPI1CKH                = SPI1CON4^2; /*SPI1CLKDIV��λ*/
/*spi1con[1:0] sample_phase_sel*/ /*����ʱ���ӳ�ѡ��. 00:���ӳ�;01:�ӳ�1��clk cycle; 10:�ӳ�2��clk cycle; 11:�ӳ�3��clk cycle*/


/*UARTCON*/
SBIT UART_MODE              = UARTCON^7; /*uartģʽ�趨. 0:9bitģʽ; 1:8bitģʽ*/
SBIT UART_SM21              = UARTCON^5; /*1:��9bitһ�Զ�ͨ��ģʽ��;0:��9bit��Ե�ģʽ*/  
SBIT UART_REN1              = UARTCON^4; /*�������ܿ���λ.1:�������;0:��ֹ����*/
SBIT UART_TB81              = UARTCON^3; /*��9bitģʽ�£�the content of���͵ĵ�9bit*/
SBIT UART_RB81              = UARTCON^2;   
SBIT UART_TI                = UARTCON^1;
SBIT UART_RI                = UARTCON^0;

/* RTCCON */
SBIT RTC_START              = RTCCON^7;
SBIT RTC_INT_EN_ASM         = RTCCON^6;   /* �����жϸ�asmʹ��.1:��;0:�ر� */
SBIT RTC_START_STA          = RTCCON^5;   /* RTC����״̬.1:rtc�����ɹ������;0:rtc�������������ڸ�λ*/
SBIT RTC_CLR                = RTCCON^4;
SBIT RTC_INT_EN_CPU         = RTCCON^2;   /* �����жϸ�cpuʹ��.1:��;0:�ر� */
SBIT RTC_AUTO_MODE          = RTCCON^1;   /* rtc����Ҫ��clr���Զ��ظ�����*/
SBIT RTC_WP                 = RTCCON^0;

/* RTCCON1 */
//[2:1] LCD_SRC_SEL lcd start sourcѡ��. 2'b00:vstart;2'b01:vmdi;2'b10:vend;2'b11:vblank
SBIT LCD_SRC_SEL_H          = RTCCON1^2;
SBIT LCD_SRC_SEL_L          = RTCCON1^1;
SBIT LCD_START_EN           = RTCCON1^0;   /* lcd vstart/wmid.vend/vblank ����rtcʹ���ź� */ 

/*SYSCON*/
SBIT REMAP                  = SYSCON^7;
SBIT ESD_RST_EN             = SYSCON^6;   /* esd����ʱ�費��Ҫrstϵͳ.1:��ʾ��Ҫrstϵͳ;0:��ʾ��rstϵͳ*/
SBIT BUS_SEL                = SYSCON^5;   /* RO. pad bus_sel */
SBIT WDT                    = SYSCON^4;   /* wdtʹ�� */
SBIT UART1                  = SYSCON^3;   /* uart1 */
SBIT UART0                  = SYSCON^2;   /* uart0: 2'b01: GPIO6; 2'b10: GPIO7; 2'b11: GPIO1.5; 2'b00: ����;  */
SBIT LVD_INT_CLR            = SYSCON^1;   /* д1���lvd���жϱ�־,��bitλд1���� */
SBIT ESD_INT_CLR            = SYSCON^0;   /* д1���esd���жϱ�־,��bitλд1���� */


/*IWKSTA*/
SBIT GPIO_INT               = IWKSTA^7; /* p0.6 pin���жϻ��ѱ�־*/
SBIT LCD_ESD_WK_INT         = IWKSTA^6; /* lcd esd wakeup�жϻ��ѱ�־ */
SBIT LCD_LVD_WK_INT         = IWKSTA^5; /* lcd lvd wakeup�жϻ��ѱ�־ */
SBIT LCD_GPIO_WK_INT        = IWKSTA^4; /* lcd gpio wakeup status */
SBIT LCD_RELOAD_FLASH       = IWKSTA^3; /* LCD initial code reload */
SBIT ASM_MON_INT            = IWKSTA^2; /* asm monitor�жϻ��ѱ�־ */
SBIT I2C_MON_INT            = IWKSTA^1; /* i2c monitor�жϻ��ѱ�־ */
SBIT RTC_CNT_INT            = IWKSTA^0; /* RTC or CNT�жϻ��ѱ�־ */

/*SFTRST*/
SBIT SOFT_RST               = SFTRST^7; /*��:��λ��־*/
SBIT WDT_RST                = SFTRST^6; /*��:wdt��λ��־*/
SBIT EXT_RST                = SFTRST^5; /*��:�ⲿ��λ��־*/
SBIT POR_RST                = SFTRST^4; /*por��λ��־*/
SBIT FLASH_HOLD_STA         = SFTRST^3; /*flash hold state*/
SBIT REMAP_RST              = SFTRST^1; /*��:��remap��λʹ��*/
/*SFTRST[0] */              /*��ȫд1�ǲ�����λ;ȫд0�ǲ���remap��λ;����ʱʱ��λ��־*/

/* ANACON */
SBIT ARAM_SEL               = ANACON^7;  /* 1: mcu����aram; 0: afe����aram */
SBIT LCD_DSTAB_IOLOW        = ANACON^6;  /* lcd dstab����ʱ,����TP��LCD DP���ź��Ƿ����Ϊ�ͣ��Ӷ�����©�� 1: ���Ϊ�ͣ�0: �����Ϊ�� */
SBIT I2C_WK_RST             = ANACON^5;  /* 0:Reset I2C monitor interrupt;1: release*/
SBIT I2C_SF_RST             = ANACON^4;  /* I2C module soft reset */
SBIT XSI_SEL                = ANACON^3;  /* xsi0/xsi1 accessing clock switch select. 0:MCU;1:AFE. */
SBIT AFE_RST                = ANACON^2;  /* afe sub-system soft reset including asm*/
SBIT FlASH_HOLD             = ANACON^1;  /* external SPI flash hold,1:hold state '0';0:hold state '1' */
SBIT GPIO_INT_SEL           = ANACON^0;  /* GPIO Interrupt source selecetion.1:GPIO interrupt is from p0.7;0:GPIO interrupt is from p0.6 */

/* XDP_STATUS*/
SBIT LVD_STA                = XDP_STA^6;  /* R0.lvd��status */
SBIT ESD_FLAG               = XDP_STA^5;  /* RW.esd������־.1:��ʾ�з���esd�¼�;0:��ʾû�з���esd�¼�.��������*/
SBIT LVD_FLAG               = XDP_STA^4;  /* RW.lvd������־.1:��lvd�¼�;0:û��lvd�¼�.�������� */
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
SBIT SPI_REPLACE_STA        = DSV_CON^4;       /* spi1�Ƿ����spi0��Ϊslave��״̬λ;1:spi1��Ϊslave;0:spi1����Ϊslave*/
SBIT SPI_REPLACE_SEL        = DSV_CON^3;       /* spi1��Ϊslave�Ŀ��ƣ���spi_replace_en=1ʱ������.1:spi1�滻spi0��Ϊslave;0:spi1���滻spi0 */
SBIT SPI_REPLACE_EN         = DSV_CON^2;       /* spi1��Ϊslave�Ŀ���.1:spi1�Ƿ�Ϊslave��spi_replace_sel����;*/
SBIT DSV_EN6_STA            = DSV_CON^1;       /* lcd�����dsv_en6��״̬ */
SBIT DSV_EN                 = DSV_CON^0;       /* dsv en reg */

/*FT_EN_REG*/
SBIT PDB                    = FT_EN_REG^6;     /* lcd to tp,�����������ʱ,�����.1:����;0:��û��*/
SBIT PDB_EN                 = FT_EN_REG^5;     /* tp to lcd.1:����������� */
SBIT DMA_REQ_INT_MASK       = FT_EN_REG^4;     /* dma_req����cpu�ж�ʹ��.1:��dma_reqΪ1ʱ,����cpu��(����timer0,timer1)�ж�*/
SBIT DMA_ACK_INT_MASK       = FT_EN_REG^3;     /* dma_ack����cpu�ж�ʹ��.1:��dma_ackΪ1ʱ,����cpu��(����timer0,timer1)�ж�*/
SBIT TEST_CLK_EN            = FT_EN_REG^2;     /* ʱ�Ӳ������ʹ��,GPIO6��� */
SBIT XSI_SEL_STA            = FT_EN_REG^1;     /* anacon[3] xsi clk swtich result.1:AFE can control xsi;0:MCU can control xsi*/
SBIT FT_EN                  = FT_EN_REG^0;     /* lcd otp to tp soc */

/* ANACON1 */
SBIT POWERGATING_CTRL       = ANACON1^7; /* ��avdd��aveeʱ,����afe��sx switch�ŵ�.1:ȡ����dsv_en,dsv_enΪ1ʱ,���ŵ�.dsv_enΪ0ʱ,�ŵ�.0:���ŵ� */
/* [6:4] vreftp_sel. vREF_TP voltage selection bits.0:2v; 1:2.5v; 2:3v; 3:3.5v; 4:4v; 5:4.5v; 6:5v; 7:4.5v*/
SBIT VREFTP_BUF_SEL_M       = ANACON1^3; /* vref_tp/vdd5 slew rate control bit,output to xtp.0: no sr control,vref_tp rise quickly.1:with sr control,set 1 for t32clk and then set to 0*/
SBIT VREFTP_BUF_SH_M        = ANACON1^2; /* ������ѹ,�̶�������ѹ,�����xtp.vref_tp/vdd5 sample/hold signal.0:hold; 1:enable*/
SBIT VREFTP_BUF_EN_M        = ANACON1^1; /* �������buf enable,�����xtp.vref_tp buf enable signal.0:disable;1:enable*/
SBIT VREFTP_SETOP_EN_M      = ANACON1^0; /* vref_tp setting op��enable,�����xtp.vref_tp volatge setting op enable singal.0:disable;1:enable */

/* ANACON2 */
SBIT REFBG_EN               = ANACON2^7; /* tp��bandgap��enbale.ɨ��ʱ,һ��Ҫ��.afe ref enable signal.0:disable;1:enable */
SBIT VREFTP_BUF_SEL         = ANACON2^6; /* vref_tp/vdd5 slew rate control bit,output to xae_l,xafe_r.0:no sr control,vref_tp rise quickly;1:with sr control,set 1 for 16 t32clk and then set to 0*/
SBIT VREFTP_BUF_SH          = ANACON2^5; /* ������ѹ,�̶�������ѹ,�����xafe_l,xafe_r.vref_tp/vdd5 sample/hold signal.0:hold; 1:enable*/
SBIT VREFTP_BUF_EN          = ANACON2^4; /* �������buf enable,�����xafe_l,xafe_r.vref_tp buf enable signal.0:disable;1:enable*/
SBIT VREFTP_SETOP_EN        = ANACON2^3; /* vref tp setting op��enable,�����xafe_l,xafe_r.vref_tp volatge setting op enable singal.0:disable;1:enable */
SBIT VDD5_SETOP_EN          = ANACON2^2; /* vdd5 volatage setting op enable signal.0:disable;1:enable*/
SBIT VDD5_BUF_EN            = ANACON2^1; /* vdd5 buf enable signal.0:disable;1:enable*/
SBIT VDD5_SECTRL            = ANACON2^0; /* vdd5 slew rate control bit.0:no sr control,vref_tp rise quickly.1:with sr control,set 1 for 16 t32clk and the set to 0*/

/* ANACON3 */
SBIT DSV_EN_ALLON           = ANACON3^7; /* dsv_en�Ƿ�ʱ�̴�.1:ʱ�̴�;0:���ϵ�ʱ�����*/
SBIT LR_SEL                 = ANACON3^6; /* select p1_af and p2_af from left or right afe controller.1:right;0:left*/
SBIT VCOM_OPT_SEL           = ANACON3^5; /* ���ڿ���vcom_opt�����.0:ǿ�����Ϊvcom.1:lcd termʱΪvcom,tp termʱ,Ϊafd*/
SBIT BGP_MASK               = ANACON3^4; /* ���ڿ��ƺ���ʱlcd��bandgap����.����ʱ,�˿�����lcd����,����ʱ,��tp����.dsvģʽ��,��̬�л�,���ڽ�ʡ����.1:����lcd��bandgap,tpɨ��ʱ,��Ҫ�����˿���.0:�ر�lcd��bandgap,tp��ɨ��ʱ,���Թرմ˿���*/
SBIT LVD_MASK               = ANACON3^3; /* ���ڿ����Ƿ���avdd/avee�ĵ�������·.dsvģʽ��,dsv_enʹ��ʱ,�ɿ���,dsv_en��ʹ��,��Ҫ�ر�avdd/avee�ĵ�������·,�Է��󴥷�lvd����·.1:������������·.0:�ر�*/

/* ANACON7*/
SBIT VREFTP_LOADREGU        = ANACON7^7; /* vreftp output buffer driving ability control signal.1:enhance the driving ability to about 55mA.0:use default value about 37mA driving ability at least*/
SBIT DSV_EN_MASK            = ANACON7^6; /* dsv_en�źŵ�ѡ���ź�.0:asm���ɵ�dsv_en�ź���Ч,��mcu�����Ƿ�����dsv_en;1:asm��������dsv_en�ź���Ч*/
SBIT NVDD2_MASK             = ANACON7^5; /* NVDD2�ں���ʱ��ʹ���ź�.nvdd2����ʱ��lcd����,����ʱ,��tp����.0:�ر�nvdd2;1:����nvdd2*/
SBIT VRGEN_EN               = ANACON7^4; /* 32kʱ�ӵ�Դ�л�����.0:ѡ������ƫ��.1:ѡ��lcd����bandgapƫ��.����ʱ,��bitλһ����Ҫ����Ϊ0,����������0��Ҳ�����ó�1*/
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
SBIT VDD_TP_N2_MASK         = ANACON8^7; /* reg_en_vdd_tp_n2�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VDD_TP_N1_MASK         = ANACON8^6; /* reg_en_vdd_tp_n1�ź���Դ.0:����mcu;1:����asm*/
SBIT VREFTP_SETOP_EN_M_MASK = ANACON8^5; /* vreftp_setop_en_m�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VREFTP_BUF_EN_M_MASK   = ANACON8^4; /* vreftp_buf_en_m�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VREFTP_SH_MASK         = ANACON8^3; /* vreftp_sh�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VREFTP_SRCTRL_M_MASK   = ANACON8^2; /* vreftp_srctrl_m�źŵ���Դ.0:����mcu;1:����asm*/
SBIT BGP_MASK_MASK          = ANACON8^1; /* bgp_mask�źŵ���Դ.0:����mcu;1:����asm*/
SBIT NVDD2_MASK_MASK        = ANACON8^0; /* nvdd2_mask�źŵ���Դ.0:����mcu;1:����asm*/

/* ANACON9 */
SBIT VDD_TP_N3_MASK         = ANACON9^7; /* reg_en_vdd_tp_n3�źŵ���Դ.0:����mcu;1:����asm*/
SBIT REGBG_EN_MASK          = ANACON9^6; /* reg_en1�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VREFTP_SETOP_EN_MASK   = ANACON9^5; /* vreftp_setop_en�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VREFTP_BUF_EN_MASK     = ANACON9^4; /* vreftp_buf_en�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VREFTP_SRCTRL_MASK     = ANACON9^3; /* vreftp_srctrl�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VDD5_SETOP_EN_MASK     = ANACON9^2; /* vdd5_setop_en�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VDD5_BUF_EN_MASK       = ANACON9^1; /* vdd5_buf_en�źŵ���Դ.0:����mcu;1:����asm*/
SBIT VDD5_SRCTRL_MASK       = ANACON9^0; /* vdd5_srctrl�źŵ���Դ.0:����mcu;1:����asm*/

/* PCON */
SBIT SMOD1                  = PCON^7;
SBIT SMOD0                  = PCON^6;
SBIT POF                    = PCON^4;
SBIT GF1                    = PCON^3;
SBIT GF0                    = PCON^2;
SBIT CORE_STOP              = PCON^1;         /* Stop ģʽ����λ .��λд1��������stopģʽ���������λ����������ֵΪ0*/
SBIT CORE_IDLE              = PCON^0;         /* Idle ģʽ����λ ����Ϊд1��ǿ����IDLEģʽ���������λ����������ֵΪ0*/

/* CGUCON0 */
SBIT ASM_32K_EN             = CGUCON0^7;  /* asm 32k clock enable.1:enable;0:disable*/
SBIT STANDBY                = CGUCON0^6;  /* ����������ģʽ�£�mcu����power downʱ����oscʱ���Լ�digital����ʱ�ӵ�disable.0:disable clock tree, osc48m;1:����ʱ�� */
SBIT EN_32K                 = CGUCON0^5;  /* 1:��32k osc*/
SBIT SPI0_32K_EN            = CGUCON0^4;  /* SPI0 DMAģ���е�counterʱ��gating*/
SBIT SPI0CKEN               = CGUCON0^3;  /* SPI0����ʱ�ӵ�enable gating */
SBIT PROBE32K_DIG_EN        = CGUCON0^2;  /* clk_32k dig probe enable signal.1:enable;0:disable */
SBIT LVD_SLEEP_EN           = CGUCON0^1;  /* LVD�¼�����ʱ���Ƿ�ر�OSC.0:���ر�,defaultΪ0.1:�ر� */
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
SBIT DMACKEN                = CGUCON3^7;     /* CAL����ʱ��cpu�Ƿ����idle״̬��0:������idle״̬;1:����idle״̬*/
SBIT CALCKEN                = CGUCON3^6;     /* cal clock enable*/
SBIT AFECKEN                = CGUCON3^5;     /* Clock dynamic gating AFE controller */
SBIT CLOSE_500K_EN          = CGUCON3^4;     /* mcu standby close 500k enable signal.1:close*/
SBIT XBUSCKEN               = CGUCON3^3;     /* Xsi0 clk enable */
SBIT AFESCKEN               = CGUCON3^2;     /* asm configure clock */
SBIT CLOSE_TIMER_EN         = CGUCON3^1;     /* mcu standby close timer clock enable sigal.1:close*/
SBIT RTCCKEN                = CGUCON3^0;

/* CGUCON4 */
SBIT SSCG_CKEN              = CGUCON4^7;   /* sscg clk enable */
SBIT WDT_500K_EN            = CGUCON4^6;   /* CLK_500K��gating enable for wdt*/
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
/*CGUCON7[7:6] OSC_TEST_SEL            ��gpio�ڲ���osc32k��osc48mʱ��ʱ��ѡ���ź�.3:32k_from_1m;2:32k_dig;1:32K , 0:48M */
/*CGUCON7[5:0] OSC_TEST_DIV            ����OSC48M����32k OSCʱ��ʱ����Ƶϴ������*/

SBIT SEL_32K_SRC            = CGUCON8^7; /* 32kʱ��Դѡ��.1:32kѡ�������ģ��osc,1:32k��Դ��1m��Ƶ*/
/* [6:0] fre_noadj_set. ����32kʱ���Ƿ��������ֵ. 1mʱ��,48m����,���������32k,����Ϊ1536.����1m��Ƶ���ܵ�����������32k.
��˻�������.Ϊ�˽��������,�����ø�ֵ.������ֵΪ15,��Ƶ������ʱ��,�������[1536-15,1536+15]֮��,������� */

/*I2CCON*/
SBIT I2C_WKEN               = I2CCON^5;      /* 0:disable i2c wakeup;1:enable i2c wakeup */
SBIT I2C_DEGLITCH_EN        = I2CCON^4;      /* analog deglitch enable.0:disable;1:enable */
SBIT I2C_BUSY               = I2CCON^3;      /* i2c�Ƿ��ڷ���/����״̬.0:idle;1:busy */
SBIT I2CTI                  = I2CCON^1;      /* hw set, sw clear */
SBIT I2CRI                  = I2CCON^0;      /* hw set, sw clear */

/*I2CSTOP*/
SBIT I2C_WAIT               = I2CSTOP^7;     /* 0:�ͷ�i2c scl;1:����i2c scl,��չscl����;��slaveæʱ���ܼ�ʱ��Ӧ */
SBIT COMP_BPSS              = I2CSTOP^6;     /* 0:ʹ��i2c��ַƥ��;1:ȡ����ַƥ����� */
SBIT ADDR_NACK              = I2CSTOP^5;     /* 0:��i2c��ַ�׶η�ack;1:��i2c��ַ�׶η���nack */
SBIT DATA_NACK              = I2CSTOP^4;     /* 0:��i2c���ݽ׶η�ack;1:��i2c���ݽ׶η�nack */
SBIT I2C_WK_STOP            = I2CSTOP^2;     /* wakeupģ����յ���ȷ��stop��write 0 to clear */
SBIT STOPID                 = I2CSTOP^1;     /* stop״̬״̬λ,��ʾ��ǰ��wr stop����rd stop.0: host write stop 1: host read stop */
SBIT I2CSTP                 = I2CSTOP^0;     /* hw set when received right i2c stop statue,sw clear */

/*I2CSEL*/
SBIT I2C_MON_CFG            = I2CSEL^4;   /* 0: i2c������i2c monitor������; 1:i2c������,i2c_monitor���� */

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
SBIT WDT_PRESCALE           = WDTREL^7;  /*Reload value for high-byte watchdog.1:ÿ384��cycle����һ��;0:ÿ24��cycle����һ��*/
/*WDTREL[6:0]                   reload value for the high_seven_byte of the watchdog timer when a refresh is triggered.*/

/* TCON */
SBIT TF1 = TCON^7;               /* timer1 overflow flag��
                                   ��timer1 overflowsʱ����1���ж���ӦʱӲ�������� */
SBIT TR1 = TCON^6;               /* timer1�Ŀ���λ��
                                   ��1������timer1,Ӳ���Զ����㣨ע�⣺����timer1֮ǰ����Ҫ��timer1�趨�ã� */
SBIT TF0 = TCON^5;               /* timer0 overflow flag��
                                    ��timer0 overflowsʱ����1���ж���ӦʱӲ�������� */
SBIT TR0 = TCON^4;               /* timer0�Ŀ���λ��
                                   ��1������timer0,Ӳ���Զ����㣨ע�⣺����timer0֮ǰ����Ҫ��timer0�趨�ã� */
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
/*TMOD[5:4]             time1 mode select. 00:timer stop; 01:16 bit counter single mode; 10:16 bit counter repeat mode; 11:half timer1��ͣ����,�����ԭ��֮ǰ��ģʽ,timer1����������*/
/*TMOD[1:0]             time0 mode select.����ͬ��*/

/*TDIV*/
SBIT INTSEL1            = TDIV^7;   /*timer1�ж����ѡ��.1:������,дintclr1���timer1�ж�;0:Ӳ�����*/
SBIT INTSEL0            = TDIV^6;   /*timer0�ж����ѡ��.1:������,дintclr0���timer1�ж�;0:Ӳ�����*/
SBIT INTCLR1            = TDIV^5;   /*������ʱ,INTCLR1д1ʱ���timer1�ж�*/
SBIT INTCLR0            = TDIV^4;   /*������ʱ,INTCLR0д1ʱ���timer1�ж�*/

/* CNTCON */
SBIT CNT_START          = CNTCON^7;   /* 1: ����CNT; 0: ������ֹ(���Զ�ȡ����ֵ) */
SBIT CNT_CLEAR          = CNTCON^4;   /* ���CNT������ֵ��0 */
SBIT CNT_WKEN           = CNTCON^3;   /* CNT����ʹ��: 1:��ʹ�� 0:�رջ���ʹ�� */

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
SBIT WDT_INT_IF         = AIF^4;      /* wdt int�����ź� */
SBIT SPI0_INT_IF        = AIF^3;      /* spi0 int�����ź� */
SBIT SPI1_INT_IF        = AIF^2;      /* spi1 int�����ź� */
SBIT ASM_INT_IF         = AIF^1;      /* asm int�����ź� */
SBIT I2C_STOP_IF        = AIF^0;      /* i2c stop int�����ź� */

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
// app ����flash�������ַ
#define CODE_START_ADDR       0x1000
#define CODE_VERIF_ADDR       (CODE_START_ADDR+APP_VERIF_ADDR)

// app ����pram�������ַ
#define APP_ADDR_START        0x0000  // app start addr
#define APP_START_OPCODE      0x02

#define APP_VERIF_ADDR        0x100   // Verification Info
#define APP_VERIF_LEN         0x20
#define APP_VERIF_CODE_LEN    0x04    //app��code������Ϣ

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

// App��֤��Ϣ
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
    FW_CFG_I2C_FLASH_ADDR          = (FW_CFG_START_FLASH_ADDR+
FW_CFG_I2C_OFFSET),
} ENUM_FW_CFG_FLASH_ADDR;

/* FW���ñ�������Flashλ�� */
typedef enum
{
    FW_CFG_BKUP_START_FLASH_ADDR   = 0x1120,
    FW_CFG_BKUP_I2C_FLASH_ADDR     = (FW_CFG_BKUP_START_FLASH_ADDR+FW_CFG_I2C_OFFSET),
} ENUM_FW_CFG_BKUP_FLASH_ADDR;

/* LCD OTP��������λ�� */
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
