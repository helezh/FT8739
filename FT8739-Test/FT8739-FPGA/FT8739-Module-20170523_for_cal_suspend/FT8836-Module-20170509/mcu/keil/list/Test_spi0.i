
#line 1 "..\..\src\source\task\Test_spi0.c" 













 
  
#line 1 "..\..\src\include\task\Test_SPI0.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 46 "..\..\src\include\config\CfgGlobal.h" 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
#line 62 "..\..\src\include\config\CfgGlobal.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
  
#line 1 "..\..\src\include\Drv\Typedef.h" 









 
 
 
 


 
 


 
 
 
 
 
 
 
 
 
 
#line 30 "..\..\src\include\Drv\Typedef.h" 
  
  
  
  
  
 
#line 36 "..\..\src\include\Drv\Typedef.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 
 typedef bit  BOOLEAN;
 typedef unsigned char  UINT8;
 typedef signed   char  SINT8;
 typedef unsigned short UINT16;
 typedef signed   short SINT16;
 typedef unsigned long  UINT32;
 typedef signed   long  SINT32;
 typedef float          FP32;
 typedef double         FP64;


 
 


 
 
 
 
#line 85 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\Drv\FT8836.h" 




































 
 
 
 
 
 
 


 
 


 
 
 
 
 
 sfr P0BUF           = 0x80;    
 sfr SP              = 0x81; 
 sfr DPL             = 0x82;
 sfr DPH             = 0x83;
 sfr DPXL            = 0x84;
 sfr PCON            = 0x87;
 
 
 sfr TCON            = 0x88;
 sfr TMOD            = 0x89;
 sfr TL0             = 0x8A;    
 sfr TL1             = 0x8B;    
 sfr TH0             = 0x8C;    
 sfr TH1             = 0x8D;    
 
 
 sfr I2CCON          = 0x90;
 sfr I2CBUF          = 0x91;
 sfr I2CADDR         = 0x92;
 sfr I2CSTOP         = 0x93;
 sfr P1BUF           = 0x94;    
 sfr I2CSEL          = 0x95;
 sfr MMCON           = 0x97;
 
 
 sfr SYSCON          = 0x98;
 sfr WDTCON          = 0x99;
 sfr WDTREL          = 0x9A;
 sfr TDIV            = 0x9B;
 sfr RTCIVL          = 0x9C;  
 sfr RTCIVH          = 0x9D;  
 sfr RTCCON          = 0x9E;
 sfr RTCSLN          = 0x9F;  
 
 
 sfr ANACON8         = 0xA0;
 sfr SPI0CON         = 0xA2;
 sfr SPI0CON2        = 0xA3;
 sfr SPI0BUF         = 0xA4;
 sfr SPI0CON3        = 0xA5;
 sfr SPI0CON4        = 0xA6; 
 sfr SPI0CON5        = 0xA7;
 
 
 sfr IEN0            = 0xA8;
 sfr UARTCON         = 0xA9;
 sfr UARTBUF         = 0xAA;
 sfr UART_RELL       = 0xAB;
 sfr P0DIR           = 0xAC;    
 sfr P1DIR           = 0xAD;    
 sfr UART_RELH       = 0xAE;
 sfr UART_SDA        = 0xAF;
 
 
 sfr ANACON9         = 0xB0;
 sfr SPI1CON3        = 0xB1;
 sfr SPI1CON4        = 0xB2;
 sfr SPI1CON         = 0xB3;
 sfr SPI1CON2        = 0xB4;
 sfr SPI1BUF         = 0xB5;
 sfr RTCCON1         = 0xB6;
 sfr IPH0            = 0xB7; 
 
 
 sfr IPL0            = 0xB8;
 sfr CNTCON          = 0xB9;
 sfr CNTIVL          = 0xBA;   
 sfr CNTIVM          = 0xBB;   
 sfr CNTIVH          = 0xBC;   
 sfr FT_EN_REG       = 0xBD;   
 sfr SPH             = 0xBE;
 sfr CGUCON8         = 0xBF;
 
 
 sfr AIF            = 0xC0;
 sfr ANACON1        = 0xC1;
 sfr ANACON2        = 0xC2;
 sfr ANACON3        = 0xC3;
 sfr ANACON4        = 0xC4;
 sfr ANACON5        = 0xC5;
 sfr ANACON6        = 0xC6;
 sfr ANACON7        = 0xC7;
 
 
 sfr CGUCON1        = 0xC8;
 sfr CGUCON0        = 0xC9;
 sfr CGUCON2        = 0xCA;
 sfr CGUCON3        = 0xCB;
 sfr CGUCON4        = 0xCC;
 sfr CGUCON5        = 0xCD;
 sfr CGUCON6        = 0xCE;
 sfr CGUCON7        = 0xCF;
 
 
 sfr MEMBIST_EN1         = 0xD2;
 sfr MEMBIST_EN2         = 0xD3;
 sfr MEMBIST_FINISH1     = 0xD4;
 sfr MEMBIST_FINISH2     = 0xD5;
 sfr MEMBIST_FAIL1       = 0xD6;
 sfr MEMBIST_FAIL2       = 0xD7;
 
 
 sfr MEMBIST_ERRMAP1     = 0xD8;
 sfr MEMBIST_ERRMAP2     = 0xD9;
 sfr DSV_CON             = 0xDA;
 sfr MEMBIST_ROMCRC0     = 0xDB;
 sfr MEMBIST_ROMCRC1     = 0xDC; 
 sfr MEMBIST_ROMCRC2     = 0xDD;
 sfr MEMBIST_ROMCRC3     = 0xDE;
 sfr IEN1                = 0xDF;
 
 
 sfr TESTCON0            = 0xE1;
 sfr TESTCON1            = 0xE2;
 sfr TESTCON2            = 0xE3;
 sfr TESTCON3            = 0xE4;
 sfr IWKSTA              = 0xE5;
 sfr POR_STA             = 0xE6;  
 sfr RST_STA             = 0xE7;  
 
 
 
 sfr AIE                 = 0xE8;
 sfr SFTRST              = 0xE9;
 sfr ANACON              = 0xEA;
 sfr P0MOD               = 0xEB;  
 sfr P0SEL               = 0xEC;  
 sfr P1MOD               = 0xED;  
 sfr P1SEL               = 0xEE;  
 sfr XDP_STA             = 0xEF;
 
 
 sfr CNT_MASK            = 0xF1;  
 sfr CNT_STA             = 0xF2;  
 sfr SSCG_CON0           = 0xF5;
 sfr SSCG_CON1           = 0xF6;  
 sfr AIPH                = 0xF7;
 
 
 sfr AIPL                = 0xF8;
 sfr I2C_CMD0            = 0xF9;  
 sfr I2C_CMD1            = 0xFA;  
 sfr I2C_CMD2            = 0xFB;  
 sfr I2C_CMD3            = 0xFC;  
 sfr I2C_STATE           = 0xFD;  
 sfr LED_EN              = 0xFE;  
 sfr LED_H_NUM           = 0xFF;  
 
 
 
 
 
 
 
 sbit SSCG_SCAN_EN           = SSCG_CON0^1;  
 sbit SSCG_EN                = SSCG_CON0^0;  
 
 
 sbit SPI0RX_OVF_FLAG        = SPI0CON^6;   
 sbit SPI0TX_UNF_FLAG        = SPI0CON^5;   
 sbit SPI0_START             = SPI0CON^4;   
 sbit SPI0_STOP              = SPI0CON^3;   
 sbit DMA_END_FLAG           = SPI0CON^2;   
 sbit SPI0RI                 = SPI0CON^1;   
 sbit SPI0TI                 = SPI0CON^0;   
 
 
 sbit SPI0TX_AUTO_CLR        = SPI0CON2^7;  
 sbit SPI0RX_AUTO_CLR        = SPI0CON2^6;  
 sbit SPI0_EDGE_SEL          = SPI0CON2^5;  
 sbit SPI0_BUSY              = SPI0CON2^4;  
 sbit SPI0_STOP_EI           = SPI0CON2^3;  
 sbit DMA_END_EI             = SPI0CON2^2;  
 sbit SPI0RI_EN              = SPI0CON2^1;  
 sbit SPI0TI_EN              = SPI0CON2^0;  
 
 
 sbit SPI0_WKEN              = SPI0CON3^7;  
 sbit SPI0_RI_PULSE_SEL      = SPI0CON3^4;  
 
 
 
 
 
 
 
 
 sbit SPI0RX_OVF_CLR         = SPI0CON5^6;   
 sbit SPI0TX_UNF_CLR         = SPI0CON5^5;   
 sbit SPI0_START_CLR         = SPI0CON5^4;   
 sbit SPI0_STOP_CLR          = SPI0CON5^3;   
 sbit DMA_END_CLR            = SPI0CON5^2;   
 sbit SPI0RI_CLR             = SPI0CON5^1;   
 sbit SPI0TI_CLR             = SPI0CON5^0;   
 
 
 
 
 sbit SPI1TI                  = SPI1CON^7;   
 sbit SPI1RI                  = SPI1CON^6;   
 sbit SPI1CKM                 = SPI1CON^5;   
 sbit SPI1CKL                 = SPI1CON^4;   
 sbit SPI1PH                  = SPI1CON^3;   
 sbit SPI1PO                  = SPI1CON^2;   
 sbit SPI1MAS                 = SPI1CON^1;   
 sbit SPI1_SLVSLELEN          = SPI1CON^0;   
 
 
 sbit SPI1TX_AUTO_CLR         = SPI1CON2^7;  
 sbit SPI1RX_AUTO_CLR         = SPI1CON2^6;  
 sbit SPI1_BUSY               = SPI1CON2^5;  
 sbit SPI1_STOP               = SPI1CON2^4; 
 sbit SPI1_START              = SPI1CON2^3;
 sbit SPI1SLVELO              = SPI1CON2^2;  
 sbit SPI1RI_EN               = SPI1CON2^1;  
 sbit SPI1TI_EN               = SPI1CON2^0;  
 
 
 sbit SPI1MODE_SELH           = SPI1CON3^7;  
 sbit SPI1MODE_SELL           = SPI1CON3^6;  
 sbit SPI1_SW_IO_ENH          = SPI1CON3^5;  
 sbit SPI1_SW_IO_ENL          = SPI1CON3^4;  
 sbit SW_1BYTE_LATER          = SPI1CON3^2;  
 sbit SPI1_SW_DIR             = SPI1CON3^1;  
 sbit SPI1_SW_EN              = SPI1CON3^0;  
 
 
 sbit SPI1IOSW_CKDLY_EN      = SPI1CON4^4;  
 sbit SPI1_CURR_MODE         = SPI1CON4^3;  
 sbit SPI1CKH                = SPI1CON4^2;  
 
 
 
 
 sbit UART_MODE              = UARTCON^7;  
 sbit UART_SM21              = UARTCON^5;  
 sbit UART_REN1              = UARTCON^4;  
 sbit UART_TB81              = UARTCON^3;  
 sbit UART_RB81              = UARTCON^2;   
 sbit UART_TI                = UARTCON^1;
 sbit UART_RI                = UARTCON^0;
 
 
 sbit RTC_START              = RTCCON^7;
 sbit RTC_INT_EN_ASM         = RTCCON^6;    
 sbit RTC_START_STA          = RTCCON^5;    
 sbit RTC_CLR                = RTCCON^4;
 sbit RTC_INT_EN_CPU         = RTCCON^2;    
 sbit RTC_AUTO_MODE          = RTCCON^1;    
 sbit RTC_WP                 = RTCCON^0;
 
 
 
 sbit LCD_SRC_SEL_H          = RTCCON1^2;
 sbit LCD_SRC_SEL_L          = RTCCON1^1;
 sbit LCD_START_EN           = RTCCON1^0;    
 
 
 sbit REMAP                  = SYSCON^7;
 sbit ESD_RST_EN             = SYSCON^6;    
 sbit BUS_SEL                = SYSCON^5;    
 sbit WDT                    = SYSCON^4;    
 sbit UART1                  = SYSCON^3;    
 sbit UART0                  = SYSCON^2;    
 sbit LVD_INT_CLR            = SYSCON^1;    
 sbit ESD_INT_CLR            = SYSCON^0;    
 
 
 
 sbit GPIO_INT               = IWKSTA^7;  
 sbit LCD_ESD_WK_INT         = IWKSTA^6;  
 sbit LCD_LVD_WK_INT         = IWKSTA^5;  
 sbit LCD_GPIO_WK_INT        = IWKSTA^4;  
 sbit LCD_RELOAD_FLASH       = IWKSTA^3;  
 sbit ASM_MON_INT            = IWKSTA^2;  
 sbit I2C_MON_INT            = IWKSTA^1;  
 sbit RTC_CNT_INT            = IWKSTA^0;  
 
 
 sbit SOFT_RST               = SFTRST^7;  
 sbit WDT_RST                = SFTRST^6;  
 sbit EXT_RST                = SFTRST^5;  
 sbit POR_RST                = SFTRST^4;  
 sbit FLASH_HOLD_STA         = SFTRST^3;  
 sbit REMAP_RST              = SFTRST^1;  
 
 
 
 sbit ARAM_SEL               = ANACON^7;   
 sbit LCD_DSTAB_IOLOW        = ANACON^6;   
 sbit I2C_WK_RST             = ANACON^5;   
 sbit I2C_SF_RST             = ANACON^4;   
 sbit XSI_SEL                = ANACON^3;   
 sbit AFE_RST                = ANACON^2;   
 sbit FlASH_HOLD             = ANACON^1;   
 sbit GPIO_INT_SEL           = ANACON^0;   
 
 
 sbit LVD_STA                = XDP_STA^6;   
 sbit ESD_FLAG               = XDP_STA^5;   
 sbit LVD_FLAG               = XDP_STA^4;   
 sbit ESD_STA                = XDP_STA^3;   
 sbit LVD_VDDI_STA           = XDP_STA^2;   
 sbit LVD_AVDD_STA           = XDP_STA^1;   
 sbit LVD_AVEE_STA           = XDP_STA^0;   
 
 
 sbit TEST_OUT0_EN           = TESTCON0^7; 
 
 
 
 sbit TEST_OUT1_EN           = TESTCON1^7; 
 
 
 
 sbit TEST_OUT2_EN           = TESTCON2^7; 
 
 
 
 sbit TEST_OUT3_EN           = TESTCON3^7; 
 
 
 
 sbit UART_INH               = DSV_CON^6;        
 sbit UART_INL               = DSV_CON^5;        
 sbit SPI_REPLACE_STA        = DSV_CON^4;        
 sbit SPI_REPLACE_SEL        = DSV_CON^3;        
 sbit SPI_REPLACE_EN         = DSV_CON^2;        
 sbit DSV_EN6_STA            = DSV_CON^1;        
 sbit DSV_EN                 = DSV_CON^0;        
 
 
 sbit PDB                    = FT_EN_REG^6;      
 sbit PDB_EN                 = FT_EN_REG^5;      
 sbit DMA_REQ_INT_MASK       = FT_EN_REG^4;      
 sbit DMA_ACK_INT_MASK       = FT_EN_REG^3;      
 sbit TEST_CLK_EN            = FT_EN_REG^2;      
 sbit XSI_SEL_STA            = FT_EN_REG^1;      
 sbit FT_EN                  = FT_EN_REG^0;      
 
 
 sbit POWERGATING_CTRL       = ANACON1^7;  
 
 sbit VREFTP_BUF_SEL_M       = ANACON1^3;  
 sbit VREFTP_BUF_SH_M        = ANACON1^2;  
 sbit VREFTP_BUF_EN_M        = ANACON1^1;  
 sbit VREFTP_SETOP_EN_M      = ANACON1^0;  
 
 
 sbit REFBG_EN               = ANACON2^7;  
 sbit VREFTP_BUF_SEL         = ANACON2^6;  
 sbit VREFTP_BUF_SH          = ANACON2^5;  
 sbit VREFTP_BUF_EN          = ANACON2^4;  
 sbit VREFTP_SETOP_EN        = ANACON2^3;  
 sbit VDD5_SETOP_EN          = ANACON2^2;  
 sbit VDD5_BUF_EN            = ANACON2^1;  
 sbit VDD5_SECTRL            = ANACON2^0;  
 
 
 sbit DSV_EN_ALLON           = ANACON3^7;  
 sbit LR_SEL                 = ANACON3^6;  
 sbit VCOM_OPT_SEL           = ANACON3^5;  
 sbit BGP_MASK               = ANACON3^4;  
 sbit LVD_MASK               = ANACON3^3;  
 
 
 sbit VREFTP_LOADREGU        = ANACON7^7;  
 sbit DSV_EN_MASK            = ANACON7^6;  
 sbit NVDD2_MASK             = ANACON7^5;  
 sbit VRGEN_EN               = ANACON7^4;  















 
 
 
 sbit VDD_TP_N2_MASK         = ANACON8^7;  
 sbit VDD_TP_N1_MASK         = ANACON8^6;  
 sbit VREFTP_SETOP_EN_M_MASK = ANACON8^5;  
 sbit VREFTP_BUF_EN_M_MASK   = ANACON8^4;  
 sbit VREFTP_SH_MASK         = ANACON8^3;  
 sbit VREFTP_SRCTRL_M_MASK   = ANACON8^2;  
 sbit BGP_MASK_MASK          = ANACON8^1;  
 sbit NVDD2_MASK_MASK        = ANACON8^0;  
 
 
 sbit VDD_TP_N3_MASK         = ANACON9^7;  
 sbit REGBG_EN_MASK          = ANACON9^6;  
 sbit VREFTP_SETOP_EN_MASK   = ANACON9^5;  
 sbit VREFTP_BUF_EN_MASK     = ANACON9^4;  
 sbit VREFTP_SRCTRL_MASK     = ANACON9^3;  
 sbit VDD5_SETOP_EN_MASK     = ANACON9^2;  
 sbit VDD5_BUF_EN_MASK       = ANACON9^1;  
 sbit VDD5_SRCTRL_MASK       = ANACON9^0;  
 
 
 sbit SMOD1                  = PCON^7;
 sbit SMOD0                  = PCON^6;
 sbit POF                    = PCON^4;
 sbit GF1                    = PCON^3;
 sbit GF0                    = PCON^2;
 sbit CORE_STOP              = PCON^1;          
 sbit CORE_IDLE              = PCON^0;          
 
 
 sbit ASM_32K_EN             = CGUCON0^7;   
 sbit STANDBY                = CGUCON0^6;   
 sbit EN_32K                 = CGUCON0^5;   
 sbit SPI0_32K_EN            = CGUCON0^4;   
 sbit SPI0CKEN               = CGUCON0^3;   
 sbit PROBE32K_DIG_EN        = CGUCON0^2;   
 sbit LVD_SLEEP_EN           = CGUCON0^1;   
 sbit PROBE32K_FROM1M_EN     = CGUCON0^0;   
 
 
 
 sbit SYSCKEN                = CGUCON1^7;      
 sbit I2CCKEN                = CGUCON1^6;      
 sbit XSICKEN                = CGUCON1^5;      
 sbit TIMER_500K_EN          = CGUCON1^4;      
 sbit TIMERCKEN              = CGUCON1^3;      
 sbit UARTCKEN               = CGUCON1^2;      
 sbit DEBUGCKEN              = CGUCON1^1;      
 sbit SPI1CKEN               = CGUCON1^0;      
 
 
 sbit CLKEN_500K             = CGUCON2^7;      
 sbit CNTCKEN                = CGUCON2^6;      
 sbit LED_32K_EN             = CGUCON2^5;      
 sbit PROMCKEN               = CGUCON2^4;      
 sbit PRAMCKEN               = CGUCON2^3;      
 sbit AFEACKEN               = CGUCON2^2;      
 sbit LEDCKEN                = CGUCON2^1;      
 sbit RTC_32K_EN             = CGUCON2^0;      
 
 
 sbit DMACKEN                = CGUCON3^7;      
 sbit CALCKEN                = CGUCON3^6;      
 sbit AFECKEN                = CGUCON3^5;      
 sbit CLOSE_500K_EN          = CGUCON3^4;      
 sbit XBUSCKEN               = CGUCON3^3;      
 sbit AFESCKEN               = CGUCON3^2;      
 sbit CLOSE_TIMER_EN         = CGUCON3^1;      
 sbit RTCCKEN                = CGUCON3^0;
 
 
 sbit SSCG_CKEN              = CGUCON4^7;    
 sbit WDT_500K_EN            = CGUCON4^6;    
 sbit PROBE32K_CKEN          = CGUCON4^4;    
 sbit PROBE48M_CKEN          = CGUCON4^3;    
 
 
 
 
 sbit GPIO_WKEN              = CGUCON5^7;   
 sbit LCD_ESD_WKEN           = CGUCON5^6;   
 sbit LCD_LVD_WKEN           = CGUCON5^5;   
 sbit LCD_TIM_WKEN           = CGUCON5^4;   
 sbit LCD_RELOAD_FLASH_WKEN  = CGUCON5^3;   
 sbit ASM_MON_WKEN           = CGUCON5^2;   
 sbit I2C_MON_WKEN           = CGUCON5^1;   
 sbit RTC_CNT_WKEN           = CGUCON5^0;   
 
 
 sbit CLK_WP                 = CGUCON6^0;  
 
 
 
 
 
 sbit SEL_32K_SRC            = CGUCON8^7;  

 
 
 
 sbit I2C_WKEN               = I2CCON^5;       
 sbit I2C_DEGLITCH_EN        = I2CCON^4;       
 sbit I2C_BUSY               = I2CCON^3;       
 sbit I2CTI                  = I2CCON^1;       
 sbit I2CRI                  = I2CCON^0;       
 
 
 sbit I2C_WAIT               = I2CSTOP^7;      
 sbit COMP_BPSS              = I2CSTOP^6;      
 sbit ADDR_NACK              = I2CSTOP^5;      
 sbit DATA_NACK              = I2CSTOP^4;      
 sbit I2C_WK_STOP            = I2CSTOP^2;      
 sbit STOPID                 = I2CSTOP^1;      
 sbit I2CSTP                 = I2CSTOP^0;      
 
 
 sbit I2C_MON_CFG            = I2CSEL^4;    
 
 
 sbit I2C_WK_BYTE4_FLAG      = I2C_STATE^3;
 sbit I2C_WK_BYTE3_FLAG      = I2C_STATE^2;
 sbit I2C_WK_BYTE2_FLAG      = I2C_STATE^1;
 sbit I2C_WK_BYTE1_FLAG      = I2C_STATE^0;
 
 
 sbit SWDT                   = IEN1^6;      
 
 
 sbit WDTACT                 = WDTCON^2;    
 sbit WDTSTARTEN             = WDTCON^1;    
 sbit WDTSTOPEN              = WDTCON^0;    
 
 
 sbit WDT_PRESCALE           = WDTREL^7;   
 
 
 
 sbit TF1 = TCON^7;                

 sbit TR1 = TCON^6;                

 sbit TF0 = TCON^5;                

 sbit TR0 = TCON^4;                

 sbit IF1 = TCON^3;                


 sbit IT1 = TCON^2;                


 sbit IF0 = TCON^1;                


 sbit IT0 = TCON^0;                


 
 sbit GATE1              = TMOD^7;   
 sbit GATE0              = TMOD^3;   
 
 
 
 
 sbit INTSEL1            = TDIV^7;    
 sbit INTSEL0            = TDIV^6;    
 sbit INTCLR1            = TDIV^5;    
 sbit INTCLR0            = TDIV^4;    
 
 
 sbit CNT_START          = CNTCON^7;    
 sbit CNT_CLEAR          = CNTCON^4;    
 sbit CNT_WKEN           = CNTCON^3;    
 
 
 sbit LED_5_EN           = LED_EN^5;
 sbit LED_4_EN           = LED_EN^4;
 sbit LED_3_EN           = LED_EN^3;
 sbit LED_2_EN           = LED_EN^2;
 sbit LED_1_EN           = LED_EN^1;
 sbit LED_0_EN           = LED_EN^0;
 
 
 sbit DRAM2_BIST_EN      = MEMBIST_EN1^7;
 sbit DRAM1_BIST_EN      = MEMBIST_EN1^6;
 sbit DRAM0_BIST_EN      = MEMBIST_EN1^5;
 sbit PRAM4_BIST_EN      = MEMBIST_EN1^4;
 sbit PRAM3_BIST_EN      = MEMBIST_EN1^3;
 sbit PRAM2_BIST_EN      = MEMBIST_EN1^2;
 sbit PRAM1_BIST_EN      = MEMBIST_EN1^1;
 sbit PRAM0_BIST_EN      = MEMBIST_EN1^0;
 
 
 sbit AFERAM_R_BIST_EN   = MEMBIST_EN2^3;
 sbit AFERAM_L_BIST_EN   = MEMBIST_EN2^2;
 sbit ARAM_BIST_EN       = MEMBIST_EN2^1;
 sbit PROM_BIST_EN       = MEMBIST_EN2^0;
 
 
 sbit DRAM2_FINISH       = MEMBIST_FINISH1^7;
 sbit DRAM1_FINISH       = MEMBIST_FINISH1^6;
 sbit DRAM0_FINISH       = MEMBIST_FINISH1^5;
 sbit PRAM4_FINISH       = MEMBIST_FINISH1^4;
 sbit PRAM3_FINISH       = MEMBIST_FINISH1^3;
 sbit PRAM2_FINISH       = MEMBIST_FINISH1^2;
 sbit PRAM1_FINISH       = MEMBIST_FINISH1^1;
 sbit PRAM0_FINISH       = MEMBIST_FINISH1^0;
 
 
 sbit RPTRAM_R_FINISH    = MEMBIST_FINISH2^7;
 sbit RPTRAM_L_FINISH    = MEMBIST_FINISH2^6;
 sbit ACCRAM_R_FINISH    = MEMBIST_FINISH2^5;
 sbit ACCRAM_L_FINISH    = MEMBIST_FINISH2^4;
 sbit TABRAM_R_FINISH    = MEMBIST_FINISH2^3;
 sbit TABRAM_L_FINISH    = MEMBIST_FINISH2^2;
 sbit ARAM_FINISH        = MEMBIST_FINISH2^1;
 sbit PROM_FINISH        = MEMBIST_FINISH2^0;
 
 
 sbit DRAM2_FAIL         = MEMBIST_FAIL1^7;
 sbit DRAM1_FAIL         = MEMBIST_FAIL1^6;
 sbit DRAM0_FAIL         = MEMBIST_FAIL1^5;
 sbit PRAM4_FAIL         = MEMBIST_FAIL1^4;
 sbit PRAM3_FAIL         = MEMBIST_FAIL1^3;
 sbit PRAM2_FAIL         = MEMBIST_FAIL1^2;
 sbit PRAM1_FAIL         = MEMBIST_FAIL1^1;
 sbit PRAM0_FAIL         = MEMBIST_FAIL1^0;
 
 
 sbit RPTRAM_R_FAIL      = MEMBIST_FAIL2^7;
 sbit RPTRAM_L_FAIL      = MEMBIST_FAIL2^6;
 sbit ACCRAM_R_FAIL      = MEMBIST_FAIL2^5;
 sbit ACCRAM_L_FAIL      = MEMBIST_FAIL2^4;
 sbit TABRAM_R_FAIL      = MEMBIST_FAIL2^3;
 sbit TABRAM_L_FAIL      = MEMBIST_FAIL2^2;
 sbit ARAM_FAIL          = MEMBIST_FAIL2^1;
 sbit PROM_FAIL          = MEMBIST_FAIL2^0;
 
 
 sbit DRAM2_ERRMAP       = MEMBIST_ERRMAP1^7;
 sbit DRAM1_ERRMAP       = MEMBIST_ERRMAP1^6;
 sbit DRAM0_ERRMAP       = MEMBIST_ERRMAP1^5;
 sbit PRAM4_ERRMAP       = MEMBIST_ERRMAP1^4;
 sbit PRAM3_ERRMAP       = MEMBIST_ERRMAP1^3;
 sbit PRAM2_ERRMAP       = MEMBIST_ERRMAP1^2;
 sbit PRAM1_ERRMAP       = MEMBIST_ERRMAP1^1;
 sbit PRAM0_ERRMAP       = MEMBIST_ERRMAP1^0;
 
 
 sbit RPTRAM_R_ERRMAP    = MEMBIST_ERRMAP2^7;
 sbit RPTRAM_L_ERRMAP    = MEMBIST_ERRMAP2^6;
 sbit ACCRAM_R_ERRMAP    = MEMBIST_ERRMAP2^5;
 sbit ACCRAM_L_ERRMAP    = MEMBIST_ERRMAP2^4;
 sbit TABRAM_R_ERRMAP    = MEMBIST_ERRMAP2^3;
 sbit TABRAM_L_ERRMAP    = MEMBIST_ERRMAP2^2;
 sbit ARAM_ERRMAP        = MEMBIST_ERRMAP2^1;
 sbit PROM_ERRMAP        = MEMBIST_ERRMAP2^0;
 
 
 sbit WDT_INT_IF         = AIF^4;       
 sbit SPI0_INT_IF        = AIF^3;       
 sbit SPI1_INT_IF        = AIF^2;       
 sbit ASM_INT_IF         = AIF^1;       
 sbit I2C_STOP_IF        = AIF^0;       
 
 
 sbit WDT_INT_EI         = AIE^4;     
 sbit SPI0_EI            = AIE^3;     
 sbit SPI1_EI            = AIE^2;     
 sbit ASM_EI             = AIE^1;     
 sbit I2C_STOP_EI        = AIE^0;     
 
 
 
 sbit EA                 = IEN0^7;   
 sbit EC                 = IEN0^6;   
 sbit ET2                = IEN0^5;   
 sbit ES                 = IEN0^4;   
 sbit ET1                = IEN0^3;   
 sbit EX1                = IEN0^2;   
 sbit ET0                = IEN0^1;   
 sbit EX0                = IEN0^0;   
 
 
 sbit IPHX0              = IPH0^0;    
 sbit IPLX0              = IPL0^0;
 sbit IPHT0              = IPH0^1;    
 sbit IPLT0              = IPL0^1;
 sbit IPHX1              = IPH0^2;    
 sbit IPLX1              = IPL0^2;
 sbit IPHT1              = IPH0^3;    
 sbit IPLT1              = IPL0^3;
 sbit LCD_IPH            = IPH0^4;    
 sbit LCD_IPL            = IPL0^4;
 sbit I2C_IPH            = IPH0^5;    
 sbit I2C_IPL            = IPL0^5;
 sbit Uart_IPH           = IPH0^6;    
 sbit Uart_IPL           = IPL0^6;
 sbit I2C_STOP_IPH       = AIPH^0;    
 sbit I2C_STOP_IPL       = AIPL^0;
 sbit ASM_IPH            = AIPH^1;    
 sbit ASM_IPL            = AIPL^1;   
 sbit SPI1_IPH           = AIPH^2;    
 sbit SPI1_IPL           = AIPL^2;
 sbit SPI0_IPH           = AIPH^3;    
 sbit SPI0_IPL           = AIPL^3;
 sbit WDT_IPH            = AIPH^4;    
 sbit WDT_IPL            = AIPL^4;
 
 
 sbit P0_7               = P0BUF^7;
 sbit P0_6               = P0BUF^6;
 sbit P0_5               = P0BUF^5;
 sbit P0_4               = P0BUF^4;
 sbit P0_3               = P0BUF^3;
 sbit P0_2               = P0BUF^2;
 sbit P0_1               = P0BUF^1;
 sbit P0_0               = P0BUF^0;
 
 
 sbit P1_7               = P1BUF^7;
 sbit P1_6               = P1BUF^6;
 sbit P1_5               = P1BUF^5;
 sbit P1_4               = P1BUF^4;
 sbit P1_3               = P1BUF^3;
 sbit P1_2               = P1BUF^2;
 sbit P1_1               = P1BUF^1;
 sbit P1_0               = P1BUF^0;
 
 
 
 sbit Flash_WP           = P1BUF^7;
 sbit Flash_HOLD         = P1BUF^4;
 
 sbit Flash_pad          = P1BUF^6;
 sbit Flash_DIR          = P1DIR^6;
 sbit Flash_GPIO         = P1MOD^6;
 sbit Flash_DM           = P1SEL^6;
 
 sbit INTOUT             = P0BUF^6;
 sbit INTOUT_DIR         = P0DIR^6;
 sbit GPIO_INTOUT        = P0MOD^6;
 sbit INTOUT_DM          = P0SEL^6;
 
 sbit GPIO3              = P0BUF^7;
 sbit GPIO3_DIR          = P0DIR^7;
 sbit GPIO3_INTOUT       = P0MOD^7;
 sbit GPIO3_DM           = P0SEL^7;
 
 sbit GPIO4              = P1BUF^5;
 sbit GPIO4_DIR          = P1DIR^5;
 sbit GPIO4_INTOUT       = P1MOD^5;
 sbit GPIO4_DM           = P1SEL^5;
 
 
 


 
 


 
 
 



 
 
 
 
 
 
 
 
 
 
 
 
 
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
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 





 
 
 
 
 
 typedef enum
 {
 FW_CFG_I2C_OFFSET              = 0x00,      
 FW_CFG_I2C_NE_OFFSET           = 0x01,      
 FW_CFG_IOVOLTAGE_OFFSET        = 0x02,      
 FW_CFG_IOVOLTAGE_NE_OFFSET     = 0x03,      
 FW_CFG_VENDOR_OFFSET           = 0x04,      
 FW_CFG_VENDOR_NE_OFFSET        = 0x05,      
 FW_CFG_SPI_CLK_OFFSET          = 0x06,      
 FW_CFG_SPI_CLK_NE_OFFSET       = 0x07,      
 FW_CFG_SYS_CLK_OFFSET          = 0x08,      
 FW_CFG_SYS_CLK_NE_OFFSET       = 0x09,      
 FW_CFG_XBUS_CLK_OFFSET         = 0x0A,      
 FW_CFG_XBUS_CLK_NE_OFFSET      = 0x0B,      
 FW_CFG_SPI_IOMODE_OFFSET       = 0x0C,      
 FW_CFG_SPI_IOMODE_NE_OFFSET    = 0x0D,      
 } ENUM_FW_CFG_OFFSET;
 
 
 typedef enum
 {
 FW_CFG_START_FLASH_ADDR        = 0x0F80,
 FW_CFG_I2C_FLASH_ADDR          = (FW_CFG_START_FLASH_ADDR+
 FW_CFG_I2C_OFFSET),
 } ENUM_FW_CFG_FLASH_ADDR;
 
 
 typedef enum
 {
 FW_CFG_BKUP_START_FLASH_ADDR   = 0x1120,
 FW_CFG_BKUP_I2C_FLASH_ADDR     = (FW_CFG_BKUP_START_FLASH_ADDR+FW_CFG_I2C_OFFSET),
 } ENUM_FW_CFG_BKUP_FLASH_ADDR;
 
 
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
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 
 
#line 86 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\Drv\FT8836_Reg.h" 













 
 
 
 
 
 
 


 
  
#line 1 "\work space\FT8836 SVN\CAL¥Ú∂œ≤‚ ‘\FT8836-Module-20170523_for_cal_suspend\FT8836-Module-20170509\src\include\Drv\FT8836.h" 




































 
 
#line 39 "\work space\FT8836 SVN\CAL¥Ú∂œ≤‚ ‘\FT8836-Module-20170523_for_cal_suspend\FT8836-Module-20170509\src\include\Drv\FT8836.h" 
  
 
 
 
 


 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 















 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  


 
 


 
 
 



 
 
  
  
 
 
  
  
 
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
 
  





 
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
 
  
  
 
  
  
 
  
  
 
 
  
 
  
  
 
  


 
 
 
#line 24 "..\..\src\include\Drv\FT8836_Reg.h" 
#line 24 "..\..\src\include\Drv\FT8836_Reg.h" 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 
 
 typedef struct
 {
 UINT16 Wdata;         
 UINT16 Rdata;         
 UINT16 Clksel;        
 UINT16 Stop;          
 UINT16 Tx_int;        
 } ST_XSIRegisters;
 
 typedef union
 {
 ST_XSIRegisters reg;
 UINT16 offset[sizeof(ST_XSIRegisters)>>1];
 } Union_XSIReg;
 
 
 
 typedef struct
 {
 UINT16 rCmd;            
 UINT16 rDmaLen;         
 UINT16 rS1Addr;         
 UINT16 rS2Addr;         
 UINT16 rOutAddr;        
 UINT16 rPar;            
 UINT16 rSize;           
 UINT16 rPThd;           
 UINT16 rNThd;           
 UINT16 rAThd;           
 UINT16 rDmask;          
 UINT16 rPaCnt;          
 UINT16 rNaCnt;          
 UINT16 rPsCnt;          
 UINT16 rNsCnt;          
 UINT16 rMaxV;           
 UINT16 rMaxPos;         
 UINT16 rMinV;           
 UINT16 rMinPos;         
 UINT16 rID0;            
 UINT16 rID1;            
 UINT16 rID2;            
 UINT16 rCrc;            
 UINT16 rChk;            
 UINT16 rNaThd;          
 UINT16 rTxRxNum;        
 UINT16 rDivShift;       
 UINT16 rSubabsMax;      
 UINT16 rInt;            
 UINT16 rCntNum;         
 UINT16 rDmaskA;         
 UINT16 rTxRxNumAm;      
 UINT16 rTxRxNumAs;      
 UINT16 rSizeAm;         
 UINT16 rSizeAs;         
 UINT16 rS1AddrA;        
 UINT16 rS2AddrA;        
 UINT16 rOutAddrA;       
 UINT16 rSel;            
 } ST_CalRegisters;
 
 typedef union
 {
 ST_CalRegisters reg;
 UINT16 offset[sizeof(ST_CalRegisters)>>1];
 } Union_CalReg;
 
 
 
 typedef struct
 {  
 UINT16 rdata_lo_byte;
 UINT16 rdata_ho_byte;
 UINT16 lcd_regfile_ctrl;
 UINT16 xbus_cmd; 
 UINT16 xbus_rld_data; 
 }ST_LcdWrapRegisters;
 
 typedef union
 {
 ST_LcdWrapRegisters reg;
 UINT16 offset[sizeof(ST_LcdWrapRegisters)>>1];
 }Union_LcdReg;
 
 
 
 typedef struct
 {
 UINT16 dma_ctrl;
 UINT16 timeout_ctrl;
 UINT16 addr_h;
 UINT16 start_addr_l;
 UINT16 end_addr_l;
 UINT16 dma_crc;
 UINT16 dma_srcr;
 
 }ST_Spi0DmaRegisters;
 
 
 typedef struct
 {
 UINT16 dma_ctrl;
 UINT16 timeout_ctrl;
 UINT16 addr_h;
 UINT16 start_addr_l;
 UINT16 end_addr_l;
 UINT16 dma_crc;
 UINT16 dma_srcr;
 
 }ST_Spi1DmaRegisters;
 
 typedef union
 {
 ST_Spi0DmaRegisters reg;
 UINT16 offset[sizeof(ST_Spi0DmaRegisters)>>1];
 }Union_Spi0Reg;
 
 
 
 typedef struct
 {
 UINT16 usAsmIntFlag0;          
 UINT16 usAsmIntFlag1;          
 UINT16 usAsmIntClr0;           
 UINT16 usAsmIntClr1;           
 UINT16 usAsmIntEn0;            
 UINT16 usAsmIntEn1;            
 UINT16 usAsmIntWakeEn0;        
 UINT16 usAsmIntWakeEn1;        
 UINT16 usAsmIntSta;            
 UINT16 usAsmScanSta0;          
 UINT16 usAsmScanSta1;          
 UINT16 usAsmScanSta2;          
 UINT16 usAsmScanSta3;          
 UINT16 usAsmScanCtrl;          
 UINT16 usAsmScanCfg0;          
 UINT16 usAsmScanCfg1;          
 UINT16 usAsmTpFrameCfg0;       
 UINT16 usAsmTpFrameCfg1;       
 UINT16 usAsmTpFrameCfg2;       
 UINT16 usAsmTpFrameCfg3;       
 UINT16 usAsmScanDly;           
 UINT16 usAsmStbMaseL;          
 UINT16 usAsmStbMaseH;          
 UINT16 usAsmAramBaseL;         
 UINT16 usAsmAramBaseR;         
 UINT16 usAsmAramBaseKey;       
 UINT16 usAsmAramCBL;           
 UINT16 usAsmAramCBR;           
 UINT16 usAsmAramCBKey;         
 UINT16 usAsmReserve0;          
 UINT16 usAsmReserve1;          
 UINT16 usAsmReserve2;          
 UINT16 usAsmHwMonCrtl0;        
 UINT16 usAsmHwMonCtrl1;        
 UINT16 usAsmHwMonCfg0;         
 UINT16 usAsmHwMonCfg1;         
 UINT16 usAsmHwMonCfg2;         
 UINT16 usAsmHwMonCfg3;         
 UINT16 usAsmHwMonCfg4;         
 UINT16 usAsmHwMonTimer;        
 UINT16 usAsmVreshCfgLcdon;     
 } ST_AsmRegisters;
 
 typedef union
 {
 ST_AsmRegisters reg;
 UINT16 offset[sizeof(ST_AsmRegisters)>>1];
 } Union_AsmReg;
 
 
 
 
 
#line 259 "..\..\src\include\Drv\FT8836_Reg.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 353 "..\..\src\include\Drv\FT8836_Reg.h" 
 
 typedef enum
 {
 Addr_PANEL_MODE_CFG0 =1, 
 Addr_PANEL_MODE_CFG1 =2,
 Addr_PANEL_MODE_CFG2 =3, 
 Addr_AFE_SYS_CFG0 =4, 
 Addr_AFE_SYS_CFG1 =5, 
 Addr_AFE_SCAN_CFG0 =6, 
 Addr_AFE_SCAN_CFG1 =7, 
 Addr_AFE_DUMMY_SCAN_CFG =8, 
 Addr_AFE_BASE_TRACK_CFG =9, 
 Addr_ACC_OFFSET =10, 
 Addr_TP_MONITOR_THRESHOLD =11,
 Addr_KEY_MONITOR_THRESHOLD =12, 
 Addr_AFE_ANA_K1_CFG0 =13,
 Addr_AFE_ANA_K2_CFG1 =14,
 Addr_AFE_ANA_CA_CFG0 =15, 
 Addr_AFE_ANA_CA_CFG1 =16, 
 Addr_AFE_ANA_CA_CFG2 =17,
 Addr_AFE_ANA_P1_P2_CFG0 =18, 
 Addr_AFE_ANA_P1_P2_CFG1 =19,
 Addr_AFE_ANA_P1_P2_CFG2 =20, 
 Addr_AFE_ANA_P1_P2_CFG3 =21,
 Addr_AFE_ANA_P1_P2_CFG4 =22, 
 Addr_AFE_ANA_P1_P2_CFG5 =23, 
 Addr_AFE_P1_P2_DLY_CFG0 =24, 
 Addr_AFE_P1_P2_DLY_CFG1 =25, 
 Addr_AFE_ANA_SH_CFG0 =26,
 Addr_AFE_ANA_SH_CFG1 =27, 
 Addr_AFE_ANA_SH_CFG2 =28, 
 Addr_AFE_ANA_SH_CFG3 =29, 
 Addr_AFE_ANA_SH_CFG4 =30, 
 Addr_AFE_ANA_SH_CFG5 =31,
 Addr_AFE_ANA_SH_CFG6 =32, 
 Addr_AFE_ANA_ADC_CFG0 =33, 
 Addr_AFE_ANA_ADC_CFG1 =34, 
 Addr_AFE_ANA_ADC_CFG2 =35, 
 Addr_AFE_ANA_ADC_CFG3 =36, 
 Addr_AFE_GIPH_P1_P2_CFG =37, 
 Addr_AFE_GIPL_P1_P2_CFG =38, 
 Addr_AFE_SD_VOM_OPT_P1_P2_CFG =39,
 Addr_AFE_SX_P1_P2_CFG =40, 
 Addr_AFE_MOUT_GIPH_CFG = 41,
 Addr_AFE_MOUT_GIPL_CFG = 42,
 Addr_AFE_GOUT_GIPH_CFG = 43,
 Addr_AFE_GOUT_GIPL_CFG = 44,
 
 Addr_ALL_GATE_ON_L_CFG =45, 
 Addr_ALL_GATE_OFF_L_CFG =46,
 Addr_ALL_GATE_STOP_L_CFG =47, 
 Addr_ALL_GATE_H_CFG =48,                              
 Addr_RPT_RAWDATA_NUM =49,                             
 Addr_CB_ADJUST_THLD =50,                                
 Addr_TEST_MODE_FLAG =51,                              
 Addr_PRESCAN_TIME =52,                                 
 Addr_DISCHARGE_TIME =53,                               
 Addr_ANA_STATIC_CFG0 =54,                              
 Addr_ANA_STATIC_CFG1 =55,                               
 Addr_ANA_STATIC_CFG2 =56,                              
 Addr_ANA_STATIC_CFG3 =57,                            
 Addr_TEST_P0_CFG0 =58,                               
 Addr_TEST_P0_CFG1 =59,                               
 Addr_TEST_P0_CFG2 =60,                                 
 Addr_TEST_P1_CFG0 =61,                               
 Addr_TEST_P1_CFG1 =62,                                
 Addr_TEST_P1_CFG2 =63,                                 
 
 Addr_MCAP_SCAN_CFG =64,                                
 Addr_MCAP_SCANSR =65,                                  
 Addr_KEY_SAMPLE_INTERVAL_6 =66,                     
 Addr_RAWSHIFTCAF =67,                                
 Addr_RAWDATA_OFFSET_L =68,                           
 Addr_ADC_CFG =69,                                      
 Addr_ADC_DATA0 =70,                                   
 Addr_MCAP_INIT_SAMPL_CFG =71,                         
 Addr_OVERFLOW_THR =72,                                 
 Addr_UNDERFLOW_THR =73,                                
 Addr_OVERFLOW_UPBOUND =74,                            
 Addr_OVER_POINT_FRAME =75,                             
 Addr_NORMAL_SIGNAL_UPTHR =76,                          
 Addr_NORMAL_SIGNAL_DWTHR =77,                        
 Addr_OVERFLOW_CLR_FRAMENUM =78,                       
 Addr_MCAP_LPFIR_CFG =79,                               
 Addr_MCAP_LPFIR_COF0 =80,                              
 Addr_MCAP_LPFIR_COF1 =81,                              
 Addr_MCAP_LPFIR_COF2 =82,                             
 Addr_MCAP_LPFIR_COF3 =83,                              
 Addr_MCAP_LPFIR_COF4 =84,                              
 Addr_MCAP_LPFIR_COF5 =85,                            
 Addr_MCAP_LPFIR_COF6 =86,                             
 Addr_MCAP_LPFIR_COF7 =87,   
 }ENUM_AFE_ADDR;
 
 
 
 
 
 
 
 


 
 


 
 
 
#line 87 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\Drv\Drv_mcu.h" 














 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 23 "..\..\src\include\Drv\Drv_mcu.h" 
#line 23 "..\..\src\include\Drv\Drv_mcu.h" 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 extern UINT8 near g_ucbuf[16];
 


 
 
 void DrvSysPowerMode(UINT8 pmode);
 void DrvSysClkInit(UINT8 ucDiv);
 void DrvIOInit(void);
 void DelayUs(UINT8 ucDlyCnt);
 void DelayMs(UINT16 ucDlyCnt);
 
 
#line 88 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\Drv\Drv_XSI.h" 














 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 22 "..\..\src\include\Drv\Drv_XSI.h" 
#line 22 "..\..\src\include\Drv\Drv_XSI.h" 
 
  
#line 1 "\work space\FT8836 SVN\CAL¥Ú∂œ≤‚ ‘\FT8836-Module-20170523_for_cal_suspend\FT8836-Module-20170509\src\include\Drv\FT8836_Reg.h" 













 
 
 
#line 17 "\work space\FT8836 SVN\CAL¥Ú∂œ≤‚ ‘\FT8836-Module-20170523_for_cal_suspend\FT8836-Module-20170509\src\include\Drv\FT8836_Reg.h" 
  
 
 
 


 
  
 


 
  
  
 
  
 
  
  
  
  
  
  
  
 
 
 
  
 
  
  
  
  
  
 
 
  
 
  
  
  
  
  
 
 
  
 
  
  
  
  
  
 
 
 
 
 
 
  
 
 
  
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 
#line 23 "..\..\src\include\Drv\Drv_XSI.h" 
#line 23 "..\..\src\include\Drv\Drv_XSI.h" 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 extern ST_XSIRegisters * near pXSI0Regs;
 extern ST_XSIRegisters * near pXSI1Regs;
 


 
 void Drv_XsiInit();
 UINT16 Drv_XsiReadReg(ST_XSIRegisters *pXSIRegs, UINT16 addr, UINT8 flag);
 void Drv_XsiWriteReg(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 usData,UINT8 flag);
 void Drv_XsiRead(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 *pBuf, UINT16 len, UINT8 flag);
 void Drv_XsiWrite(ST_XSIRegisters *pXSIRegs, UINT16 usAddr, UINT16 *pBuf, UINT16 len, UINT8 flag);
 
 
#line 61 "..\..\src\include\Drv\Drv_XSI.h" 
 
 
#line 63 "..\..\src\include\Drv\Drv_XSI.h" 
 
 
 
 
 
#line 89 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\Drv\Drv_XBUS.h" 














 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 22 "..\..\src\include\Drv\Drv_XBUS.h" 
#line 22 "..\..\src\include\Drv\Drv_XBUS.h" 
 
  
#line 1 "\work space\FT8836 SVN\CAL¥Ú∂œ≤‚ ‘\FT8836-Module-20170523_for_cal_suspend\FT8836-Module-20170509\src\include\Drv\FT8836_Reg.h" 













 
 
 
#line 17 "\work space\FT8836 SVN\CAL¥Ú∂œ≤‚ ‘\FT8836-Module-20170523_for_cal_suspend\FT8836-Module-20170509\src\include\Drv\FT8836_Reg.h" 
  
 
 
 


 
  
 


 
  
  
 
  
 
  
  
  
  
  
  
  
 
 
 
  
 
  
  
  
  
  
 
 
  
 
  
  
  
  
  
 
 
  
 
  
  
  
  
  
 
 
 
 
 
 
  
 
 
  
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 
#line 23 "..\..\src\include\Drv\Drv_XBUS.h" 
#line 23 "..\..\src\include\Drv\Drv_XBUS.h" 
 
 


 
 


 
 


 
 
 extern ST_LcdWrapRegisters *near pLcdWrapRegs;
 


 
 void Drv_XbusInit();
 UINT16 DrvXbus_ReadLcd16(UINT16 usaddr);
 void DrvXbus_WriteLcd8(UINT16 usaddr,UINT8 usdata);
 
 
#line 47 "..\..\src\include\Drv\Drv_XBUS.h" 
 
 
#line 49 "..\..\src\include\Drv\Drv_XBUS.h" 
 
 
 
 
 
#line 90 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\Debug\uart.h" 













 
 
 
 
 
 
 
 


 
  
#line 1 "D:\software\Keil\C251\INC\STDIO.H" 






 
 
 #pragma SAVE
 #pragma PARM251
 
 
 
 
 
 
 
 
 
 
 
 typedef unsigned int size_t;
 
 
 
 #pragma SAVE
 #pragma FUNCTIONS(STATIC)
 
 extern char _getkey  (void);
 extern char getchar  (void);
 extern char ungetchar(char);
 extern char putchar  (char);
 extern int  printf   (const char *, ...); 
 extern char *gets    (char *, int n);
 extern int  scanf    (const char *, ...);
 extern int  vprintf  (const char *, char *);
 extern int  puts     (const char *);
 #pragma RESTORE
 
 extern int  sprintf  (char *, const char *, ...);
 extern int  vsprintf (char *, const char *, char *);
 extern int  sscanf   (char *, const char *, ...);
 
#line 44 "D:\software\Keil\C251\INC\STDIO.H" 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 57 "D:\software\Keil\C251\INC\STDIO.H" 
 
 #pragma RESTORE
#line 25 "..\..\src\include\Debug\uart.h" 
 
  
#line 1 "D:\software\Keil\C251\INC\Intel\REG251S.H" 






 
 
 
 
 
 
 sfr P0   = 0x80;
 sfr P1   = 0x90;
 sfr P2   = 0xA0;
 sfr P3   = 0xB0;
 sfr PSW  = 0xD0;
 sfr PSW1 = 0xD1;
 sfr ACC  = 0xE0;
 sfr B    = 0xF0;
 sfr SP   = 0x81;
 sfr SPH  = 0xBE;
 sfr DPL  = 0x82;
 sfr DPH  = 0x83;
 sfr DPXL = 0x84;
 sfr PCON = 0x87;
 sfr TCON = 0x88;
 sfr TMOD = 0x89;
 sfr TL0  = 0x8A;
 sfr TL1  = 0x8B;
 sfr TH0  = 0x8C;
 sfr TH1  = 0x8D;
 sfr IE0  = 0xA8;
 sfr IPL0 = 0xB8;
 sfr IPH0 = 0xB7;
 sfr SCON = 0x98;
 sfr SBUF = 0x99;
 sfr SADDR  = 0xA9;
 sfr SADEN  = 0xB9;
 sfr T2CON  = 0xC8;
 sfr T2MOD  = 0xC9;
 sfr RCAP2L = 0xCA;
 sfr RCAP2H = 0xCB;
 sfr TL2    = 0xCC;
 sfr TH2    = 0xCD;
 sfr CCON   = 0xD8;
 sfr CMOD   = 0xD9;
 sfr CCAPM0 = 0xDA;
 sfr CCAPM1 = 0xDB;
 sfr CCAPM2 = 0xDC;
 sfr CCAPM3 = 0xDD;
 sfr CCAPM4 = 0xDE;
 sfr CL     = 0xE9;
 sfr CCAP0L = 0xEA;
 sfr CCAP1L = 0xEB;
 sfr CCAP2L = 0xEC;
 sfr CCAP3L = 0xED;
 sfr CCAP4L = 0xEE;
 sfr CH     = 0xF9;
 sfr CCAP0H = 0xFA;
 sfr CCAP1H = 0xFB;
 sfr CCAP2H = 0xFC;
 sfr CCAP3H = 0xFD;
 sfr CCAP4H = 0xFE;
 sfr WDTRST = 0xA6;
 sfr WCON   = 0xA7;
 
 
 
 
 sbit CY   = 0xD7;
 sbit AC   = 0xD6;
 sbit F0   = 0xD5;
 sbit RS1  = 0xD4;
 sbit RS0  = 0xD3;
 sbit OV   = 0xD2;
 sbit UD   = 0xD1;
 sbit P    = 0xD0;
 
 
 sbit TF1  = 0x8F;
 sbit TR1  = 0x8E;
 sbit TF0  = 0x8D;
 sbit TR0  = 0x8C;
 sbit IE1_ = 0x8B;
 sbit IT1  = 0x8A;
 sbit IE0_ = 0x89;
 sbit IT0  = 0x88;
 
 
 sbit EA   = 0xAF;
 sbit EC   = 0xAE;
 sbit ET2  = 0xAD;
 sbit ES   = 0xAC;
 sbit ET1  = 0xAB;
 sbit EX1  = 0xAA;
 sbit ET0  = 0xA9;
 sbit EX0  = 0xA8;
 
 
 sbit PPC  = 0xBE;
 sbit PT2  = 0xBD;
 sbit PS   = 0xBC;
 sbit PT1  = 0xBB;
 sbit PX1  = 0xBA;
 sbit PT0  = 0xB9;
 sbit PX0  = 0xB8;
 
 
 sbit RD   = 0xB7;
 sbit WR   = 0xB6;
 sbit T1   = 0xB5;
 sbit T0   = 0xB4;
 sbit INT1 = 0xB3;
 sbit INT0 = 0xB2;
 sbit TXD  = 0xB1;
 sbit RXD  = 0xB0;
 
 
 sbit FE   = 0x9F;
 sbit SM0  = 0x9F;
 sbit SM1  = 0x9E;
 sbit SM2  = 0x9D;
 sbit REN  = 0x9C;
 sbit TB8  = 0x9B;
 sbit RB8  = 0x9A;
 sbit TI   = 0x99;
 sbit RI   = 0x98;
 
 
 sbit CEX4 = 0x97;
 sbit CEX3 = 0x96;
 sbit CEX2 = 0x95;
 sbit CEX1 = 0x94;
 sbit CEX0 = 0x93;
 sbit ECI  = 0x92;
 sbit T2EX = 0x91;
 sbit T2   = 0x90;
 
 
 sbit TF2   = 0xCF;
 sbit EXF2  = 0xCE;
 sbit RCLK  = 0xCD;
 sbit TCLK  = 0xCC;
 sbit EXEN2 = 0xCB;
 sbit TR2   = 0xCA;
 sbit C_T2  = 0xC9;
 sbit CP_RL2= 0xC8;
 
 
 sbit CF    = 0xDF;
 sbit CR    = 0xDE;
 sbit CCF4  = 0xDC;
 sbit CCF3  = 0xDB;
 sbit CCF2  = 0xDA;
 sbit CCF1  = 0xD9;
 sbit CCF0  = 0xD8;
 
 
#line 26 "..\..\src\include\Debug\uart.h" 
 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 27 "..\..\src\include\Debug\uart.h" 
#line 27 "..\..\src\include\Debug\uart.h" 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 48 "..\..\src\include\Debug\uart.h" 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
#line 84 "..\..\src\include\Debug\uart.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void  DrvUartInit(void);
 SINT8 putchar(SINT8 c);
 UINT8 CLK_DIV(UINT8 div);
 
 extern volatile UINT16 near s_ucUartTxLen;
 
#line 129 "..\..\src\include\Debug\uart.h" 
  
  
 
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
#line 171 "..\..\src\include\Debug\uart.h" 


 
 


 
 
 
 
#line 91 "..\..\src\include\config\CfgGlobal.h" 
 
 
  
#line 1 "..\..\src\include\task\Test_GPIO.h" 
















 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 25 "..\..\src\include\task\Test_GPIO.h" 
#line 25 "..\..\src\include\task\Test_GPIO.h" 
 
 
 
#line 28 "..\..\src\include\task\Test_GPIO.h" 


 
 


 
 


 
 


 
 
 
#line 45 "..\..\src\include\task\Test_GPIO.h" 
 
 
 
 
 
#line 93 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_WDT.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_WDT.h" 
#line 21 "..\..\src\include\task\Test_WDT.h" 
 
 
 
#line 24 "..\..\src\include\task\Test_WDT.h" 
 


 
 


 
 


 
 


 
 
 
#line 42 "..\..\src\include\task\Test_WDT.h" 
 
 
 
 
 
#line 94 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_RTC.h" 
















 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 24 "..\..\src\include\task\Test_RTC.h" 
#line 24 "..\..\src\include\task\Test_RTC.h" 
 
 
 
#line 27 "..\..\src\include\task\Test_RTC.h" 
 


 
 


 
 


 
 


 
 
 
#line 45 "..\..\src\include\task\Test_RTC.h" 
 
 
 
 
#line 95 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_timer.h" 
















 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 24 "..\..\src\include\task\Test_timer.h" 
#line 24 "..\..\src\include\task\Test_timer.h" 
 
 
 
#line 27 "..\..\src\include\task\Test_timer.h" 
 


 
 


 
 


 
 


 
 
 
#line 45 "..\..\src\include\task\Test_timer.h" 
 
 
 
 
 
#line 96 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_Counter.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_Counter.h" 
#line 21 "..\..\src\include\task\Test_Counter.h" 
 
 
 
#line 24 "..\..\src\include\task\Test_Counter.h" 


 
 


 
 


 
 


 
 
 
#line 41 "..\..\src\include\task\Test_Counter.h" 
 
 
 
 
 
#line 97 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_Prom.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_Prom.h" 
#line 21 "..\..\src\include\task\Test_Prom.h" 
 
 


 
 
 
#line 28 "..\..\src\include\task\Test_Prom.h" 


 
 


 
 


 
 
 
#line 41 "..\..\src\include\task\Test_Prom.h" 
 
 
 
 
#line 98 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_Dram.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_Dram.h" 
#line 21 "..\..\src\include\task\Test_Dram.h" 
 
 
 
#line 24 "..\..\src\include\task\Test_Dram.h" 


 
  
  
  
  
  
  
 


 
 


 
 
 
 
 


 
 
 
#line 50 "..\..\src\include\task\Test_Dram.h" 
 
 
 
 
#line 99 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_Aram.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_Aram.h" 
#line 21 "..\..\src\include\task\Test_Aram.h" 
 
 


 
 
 
#line 28 "..\..\src\include\task\Test_Aram.h" 


 
 


 
 


 
 
 
#line 41 "..\..\src\include\task\Test_Aram.h" 
 
 
 
 
#line 100 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_SFR.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_SFR.h" 
#line 21 "..\..\src\include\task\Test_SFR.h" 
 
 
 
#line 24 "..\..\src\include\task\Test_SFR.h" 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 


 
 
 
 
#line 171 "..\..\src\include\task\Test_SFR.h" 
 
 
 
 
 
 
#line 101 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_Reg.h" 













 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 22 "..\..\src\include\task\Test_Reg.h" 
#line 22 "..\..\src\include\task\Test_Reg.h" 
 
 


 
 


 
 


 
 


 
 
#line 40 "..\..\src\include\task\Test_Reg.h" 
 
 
#line 42 "..\..\src\include\task\Test_Reg.h" 
 
 
 
 
#line 46 "..\..\src\include\task\Test_Reg.h" 
 
 
#line 48 "..\..\src\include\task\Test_Reg.h" 
 
 
 
 
#line 52 "..\..\src\include\task\Test_Reg.h" 
 
 
#line 54 "..\..\src\include\task\Test_Reg.h" 
 
 
 
 
#line 58 "..\..\src\include\task\Test_Reg.h" 
 
 
#line 60 "..\..\src\include\task\Test_Reg.h" 
 
 
 
 
#line 64 "..\..\src\include\task\Test_Reg.h" 
 
 
#line 66 "..\..\src\include\task\Test_Reg.h" 
 
 
 
 
#line 70 "..\..\src\include\task\Test_Reg.h" 
 
 
#line 72 "..\..\src\include\task\Test_Reg.h" 
 
 
 
#line 75 "..\..\src\include\task\Test_Reg.h" 
  
  
  
  
  
  
 
 
 
 
#line 85 "..\..\src\include\task\Test_Reg.h" 
 
 
 
 
#line 89 "..\..\src\include\task\Test_Reg.h" 
 
 
#line 91 "..\..\src\include\task\Test_Reg.h" 
 
 
 
 
#line 102 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_I2C.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_I2C.h" 
#line 21 "..\..\src\include\task\Test_I2C.h" 
 
 
 
#line 24 "..\..\src\include\task\Test_I2C.h" 
 


 
 


 
 


 
 


 
 
 
 
#line 43 "..\..\src\include\task\Test_I2C.h" 
 
 
 
 
 
#line 103 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_i2c_wakeup.h" 
















 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 25 "..\..\src\include\task\Test_i2c_wakeup.h" 
#line 25 "..\..\src\include\task\Test_i2c_wakeup.h" 
 
 
 
#line 28 "..\..\src\include\task\Test_i2c_wakeup.h" 
 


 
 


 
 


 
 


 
 
 
#line 46 "..\..\src\include\task\Test_i2c_wakeup.h" 
 
 
 
 
 
#line 104 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_gpio_wakeup.h" 
















 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 25 "..\..\src\include\task\Test_gpio_wakeup.h" 
#line 25 "..\..\src\include\task\Test_gpio_wakeup.h" 
 
 
 
#line 28 "..\..\src\include\task\Test_gpio_wakeup.h" 
 


 
 


 
 


 
 


 
 
 
#line 46 "..\..\src\include\task\Test_gpio_wakeup.h" 
 
 
 
 
 
#line 105 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_int_nest.h" 















 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 24 "..\..\src\include\task\Test_int_nest.h" 
#line 24 "..\..\src\include\task\Test_int_nest.h" 
 
 
 
#line 27 "..\..\src\include\task\Test_int_nest.h" 
 


 
 


 
 


 
 


 
 
 
#line 45 "..\..\src\include\task\Test_int_nest.h" 
 
 
 
 
#line 106 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_SPI.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_SPI.h" 
#line 21 "..\..\src\include\task\Test_SPI.h" 
 
 


 
 
#line 27 "..\..\src\include\task\Test_SPI.h" 


 
 


 
 


 
 
 
 
 
#line 42 "..\..\src\include\task\Test_SPI.h" 
 
 
 
 
 
#line 107 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_CAL.h" 
















 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 25 "..\..\src\include\task\Test_CAL.h" 
#line 25 "..\..\src\include\task\Test_CAL.h" 
 
 
 


 
 
 
#line 33 "..\..\src\include\task\Test_CAL.h" 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
 
#line 67 "..\..\src\include\task\Test_CAL.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 107 "..\..\src\include\task\Test_CAL.h" 
 
  
  
 
 
#line 112 "..\..\src\include\task\Test_CAL.h" 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 


 
 void Test_CAL(void);
 
#line 138 "..\..\src\include\task\Test_CAL.h" 
  
 
#line 140 "..\..\src\include\task\Test_CAL.h" 
 
 
 
#line 108 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_romboot.h" 












 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 20 "..\..\src\include\task\Test_romboot.h" 
#line 20 "..\..\src\include\task\Test_romboot.h" 
 
 


 
 
 
#line 27 "..\..\src\include\task\Test_romboot.h" 


 
 


 
 


 
 
 
#line 40 "..\..\src\include\task\Test_romboot.h" 
 
 
 
 
#line 109 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_Afe.h" 














 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 22 "..\..\src\include\task\Test_Afe.h" 
#line 22 "..\..\src\include\task\Test_Afe.h" 
 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 
 typedef enum
 {
 BIT_LCD_BUSY_FALL_FLAG0 		 = 15,
 BIT_LCD_BUSY_RISE_FLAG0 		 = 14,
 BIT_LCD_PANEL_CONFLICT_FLAG0	 = 13,
 BIT_LCD_DSTB_FAIL_FLAG0 		 = 12,
 BIT_LCD_DSTB_RISE_FLAG0 		 = 11,
 BIT_LCD_SYNC_MISS_FALL_FLAG0	 = 10,
 BIT_LCD_SYNC_MISS_RISE_FLAG0	 = 9,
 BIT_LCD_ARAM_RDY_FLAG0			 = 8,
 BIT_LCD_FRAME_END_FLAG0 		 = 7,
 BIT_LCD_TCH_DET_FLAG0			 = 6,
 BIT_LCD_VSTART_FLAG0			 = 5,
 BIT_LCD_VMID_FLAG0				 = 4,
 BIT_LCD_VEND_FLAG0				 = 3,
 BIT_LCD_VBLANK_FLAG0			 = 2,
 BIT_LCD_RUN_FALL_FLAG0			 = 1,
 BIT_LCD_RUN_RISE_FLAG0			 = 0,		   
 } ENUM_BIT_ASM_INT_FLAG0;
 
 
 typedef enum
 {			
 
 BIT_LCD_STB_TICK_FLAG1			 = 11,
 BIT_LCD_ODD_EVEN_FALL_FLAG1 	 = 10,
 BIT_LCD_ODD_EVEN_RISE_FLAG1 	 = 9,
 BIT_LCD_VDO_MODE_FALL_FLAG1 	 = 8,
 BIT_LCD_VDO_MODE_RISE_FLAG1 	 = 7,  
 BIT_LCD_IDLE_MODE_FALL_FLAG1	 = 6,  
 BIT_LCD_IDLE_MODE_RISE_FLAG1	 = 5,
 BIT_LCD_3D_MODE_FALL_FLAG1		 = 4,
 BIT_LCD_3D_MODE_RISE_FLAG1		 = 3,
 BIT_LCD_RUN_FLAG1				 = 2,
 BIT_LCD_DSTB_FLAG1				 = 1,
 } ENUM_BIT_ASM_INT_FLAG1;
 
 
 typedef enum
 {
 BIT_LCD_BUSY_FALL_CLR0			= 15,
 BIT_LCD_BUSY_RISE_CLR0			= 14,
 BIT_LCD_PANEL_CONFLICT_CLR0 	= 13,
 BIT_LCD_DSTB_FAIL_CLR0			= 12,
 BIT_LCD_DSTB_RISE_CLR0			= 11,
 BIT_LCD_SYNC_MISS_FALL_CLR0 	= 10,
 BIT_LCD_SYNC_MISS_RISE_CLR0 	= 9,
 BIT_LCD_ARAM_RDY_CLR0			= 8,
 BIT_LCD_FRAME_END_CLR0			= 7,
 BIT_LCD_TCH_DET_CLR0			= 6,
 BIT_LCD_VSTART_CLR0 			= 5,
 BIT_LCD_VMID_CLR0				= 4,
 BIT_LCD_VEND_CLR0				= 3,
 BIT_LCD_VBLANK_CLR0 			= 2,
 BIT_LCD_RUN_FALL_CLR0			= 1,
 BIT_LCD_RUN_RISE_CLR0			= 0,		
 } ENUM_BIT_ASM_INT_CLR0;
 
 
 typedef enum
 {	
 BIT_HW_MON_TIMEOUT_CLR1 		= 14,
 BIT_LPF_MODE_EN_FALL_CLR1		= 13,
 BIT_LPF_MODE_EN_RISE_CLR1		= 12,
 BIT_LCD_STB_TICK_CLR1			= 11,	 
 BIT_LCD_ODD_EVEN_FALL_CLR1		= 10,
 BIT_LCD_ODD_EVEN_RISE_CLR1		= 9,
 BIT_LCD_VDO_MODE_FALL_CLR1		= 8,
 BIT_LCD_VDO_MODE_RISE_CLR1		= 7,  
 BIT_LCD_IDLE_MODE_FALL_CLR1 	= 6,  
 BIT_LCD_IDLE_MODE_RISE_CLR1 	= 5,
 BIT_LCD_3D_MODE_FALL_CLR1		= 4,
 BIT_LCD_3D_MODE_RISE_CLR1		= 3,
 BIT_LCD_RUN_CLR1				= 2,
 BIT_LCD_DSTB_CLR1				= 1,   
 } ENUM_BIT_ASM_INT_CLR1;
 
 
 typedef enum
 {
 BIT_LCD_BUSY_FALL_EN0		   = 15,
 BIT_LCD_BUSY_RISE_EN0		   = 14,
 BIT_LCD_PANEL_CONFLICT_EN0	   = 13,
 BIT_LCD_DSTB_FAIL_EN0		   = 12,
 BIT_LCD_DSTB_RISE_EN0		   = 11,
 BIT_LCD_SYNC_MISS_FALL_EN0	   = 10,
 BIT_LCD_SYNC_MISS_RISE_EN0	   = 9,
 BIT_LCD_ARAM_RDY_EN0		   = 8,
 BIT_LCD_FRAME_END_EN0		   = 7,
 BIT_LCD_TCH_DET_EN0 		   = 6,
 BIT_LCD_VSTART_EN0			   = 5,
 BIT_LCD_VMID_EN0			   = 4,
 BIT_LCD_VEND_EN0			   = 3,
 BIT_LCD_VBLANK_EN0			   = 2,
 BIT_LCD_RUN_FALL_EN0		   = 1,
 BIT_LCD_RUN_RISE_EN0		   = 0, 	   
 } ENUM_BIT_ASM_INT_EN0;
 
 
 typedef enum
 {
 BIT_HW_MON_TIMEOUT_EN1		   = 14,
 BIT_LCD_LPF_MODE_EN_FALL_EN1   = 13,
 BIT_LCD_LPF_MODE_EN_RISE_EN1   = 12,
 BIT_LCD_STB_TICK_EN1		   = 11,   
 BIT_LCD_ODD_EVEN_FALL_EN1	   = 10,
 BIT_LCD_ODD_EVEN_RISE_EN1	   = 9,
 BIT_LCD_VDO_MODE_FALL_EN1	   = 8,
 BIT_LCD_VDO_MODE_RISE_EN1	   = 7,  
 BIT_LCD_IDLE_MODE_FALL_EN1	   = 6,  
 BIT_LCD_IDLE_MODE_RISE_EN1	   = 5,
 BIT_LCD_3D_MODE_FALL_EN1	   = 4,
 BIT_LCD_3D_MODE_RISE_EN1	   = 3,
 BIT_LCD_RUN_EN1 			   = 2,
 BIT_LCD_DSTB_EN1			   = 1,
 
 } ENUM_BIT_ASM_INT_EN1;
 
 
 typedef enum
 {
 BIT_LCD_BUSY_FALL_WAKE_EN0			= 15,
 BIT_LCD_BUSY_RISE_WAKE_EN0			= 14,
 BIT_LCD_PANEL_CONFLICT_WAKE_EN0 	= 13,
 BIT_LCD_DSTB_FAIL_WAKE_EN0			= 12,
 BIT_LCD_DSTB_RISE_WAKE_EN0			= 11,
 BIT_LCD_SYNC_MISS_FALL_WAKE_EN0 	= 10,
 BIT_LCD_SYNC_MISS_RISE_WAKE_EN0 	= 9,
 BIT_LCD_ARAM_RDY_WAKE_EN0			= 8,
 BIT_LCD_FRAME_END_WAKE_EN0			= 7,
 BIT_LCD_TCH_DET_WAKE_EN0			= 6,
 BIT_LCD_VSTART_WAKE_EN0 			= 5,
 BIT_LCD_VMID_WAKE_EN0				= 4,
 BIT_LCD_VEND_WAKE_EN0				= 3,
 BIT_LCD_VBLANK_WAKE_EN0 			= 2,
 BIT_LCD_RUN_FALL_WAKE_EN0			= 1,
 BIT_LCD_RUN_RISE_WAKE_EN0			= 0,			  
 } ENUM_BIT_ASM_WAKE_EN0 ;
 
 
 typedef enum
 {
 BIT_HW_MON_TIMEOUT_WAKE_EN1 		= 14,
 BIT_LCD_LPF_MODE_EN_FALL_WAKE_EN1	= 13,
 BIT_LCD_LPF_MODE_EN_RISE_WAKE_EN1	= 12,
 BIT_LCD_STB_TICK_WAKE_EN1			= 11, 
 BIT_LCD_ODD_EVEN_FALL_WAKE_EN1		= 10,
 BIT_LCD_ODD_EVEN_RISE_WAKE_EN1		= 9,
 BIT_LCD_VDO_MODE_FALL_WAKE_EN1		= 8,
 BIT_LCD_VDO_MODE_RISE_WAKE_EN1		= 7,  
 BIT_LCD_IDLE_MODE_FALL_WAKE_EN1 	= 6,  
 BIT_LCD_IDLE_MODE_RISE_WAKE_EN1 	= 5,
 BIT_LCD_3D_MODE_FALL_WAKE_EN1		= 4,
 BIT_LCD_3D_MODE_RISE_WAKE_EN1		= 3,
 } ENUM_BIT_ASM_WAKE_EN1;
 
 
 typedef enum
 {
 BIT_LCD_BUSY_STA				= 15,
 BIT_LCD_PANEL_CONFLICT_STA		= 14,
 BIT_LCD_DSTB_STA				= 13,
 BIT_LCD_SYNC_MISS_STA			= 12,
 BIT_LCD_FRAME_END_STA			= 11,
 BIT_LCD_TCH_DET_STA 			= 10,
 BIT_LCD_STB_TICK_STA			= 9,
 BIT_LCD_VSTART_STA				= 8,
 BIT_LCD_VMID_STA				= 7,
 BIT_LCD_VEND_STA				= 6,
 BIT_LCD_VBLANK_STA				= 5,
 BIT_LCD_ODD_EVEN_STA			= 4,
 BIT_LCD_VDO_MODE_STA			= 3,
 BIT_LCD_IDLE_MODE_STA			= 2,
 BIT_LCD_3D_MODE_STA 			= 1,
 BIT_LCD_RUN_STA 				= 0,
 } ENUM_BIT_ASM_INT_STA0;
 


 
 extern ST_AsmRegisters * near pAsmRegs;


 
 void Afe_120Hz_Run(void);
 void DrvAsmInterEnable0(UINT16 usInterMode);
 void DrvAsmAramAvail(void);
 void DrvAsmScanStart(void);
 void DrvAsmInterEnable1(UINT16 usInterMode);
 
 
 
#line 110 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_LED.h" 
















 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 24 "..\..\src\include\task\Test_LED.h" 
#line 24 "..\..\src\include\task\Test_LED.h" 
 
 
 
#line 27 "..\..\src\include\task\Test_LED.h" 


 
 


 
 


 
 


 
 
 
#line 44 "..\..\src\include\task\Test_LED.h" 
 
 
 
 
#line 111 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_Xbus.h" 
















 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 24 "..\..\src\include\task\Test_Xbus.h" 
#line 24 "..\..\src\include\task\Test_Xbus.h" 
 
 
 
#line 27 "..\..\src\include\task\Test_Xbus.h" 


 
 


 
 


 
 


 
 
 
#line 44 "..\..\src\include\task\Test_Xbus.h" 
 
 
 
 
 
#line 112 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_RomEcc.h" 
















 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 24 "..\..\src\include\task\Test_RomEcc.h" 
#line 24 "..\..\src\include\task\Test_RomEcc.h" 
 
 
 
#line 27 "..\..\src\include\task\Test_RomEcc.h" 
 


 
 


 
 


 
 


 
 
 
#line 45 "..\..\src\include\task\Test_RomEcc.h" 
 
 
 
 
 
#line 113 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_Uart.h" 














 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 22 "..\..\src\include\task\Test_Uart.h" 
#line 22 "..\..\src\include\task\Test_Uart.h" 
 
 
 
#line 25 "..\..\src\include\task\Test_Uart.h" 


 
 


 
 


 
 


 
 
 
#line 42 "..\..\src\include\task\Test_Uart.h" 
 
 
 
 
 
#line 114 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_SOFT_RST.h" 
















 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 24 "..\..\src\include\task\Test_SOFT_RST.h" 
#line 24 "..\..\src\include\task\Test_SOFT_RST.h" 
 
 
 
#line 27 "..\..\src\include\task\Test_SOFT_RST.h" 
 


 
 


 
 


 
 


 
 
 
#line 45 "..\..\src\include\task\Test_SOFT_RST.h" 
 
 
 
 
#line 115 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_spi0.h" 













 
 
#line 16 "..\..\src\include\task\Test_spi0.h" 
  
 


 
  
 


 
 


 
 


 
 


 
 
 
 
 
  
  
 
 
 
#line 116 "..\..\src\include\config\CfgGlobal.h" 
#line 116 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_spi0_wakeup.h" 















 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 24 "..\..\src\include\task\Test_spi0_wakeup.h" 
#line 24 "..\..\src\include\task\Test_spi0_wakeup.h" 
 
 
 
#line 27 "..\..\src\include\task\Test_spi0_wakeup.h" 
 


 
 


 
 


 
 


 
 
 
#line 45 "..\..\src\include\task\Test_spi0_wakeup.h" 
 
 
 
 
 
#line 117 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_SPI0_dma.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_SPI0_dma.h" 
#line 21 "..\..\src\include\task\Test_SPI0_dma.h" 
 
 


 
 
#line 27 "..\..\src\include\task\Test_SPI0_dma.h" 


 
 


 
 
  
  
  
  
 
  
  
  
  
 
 
  
  
  
  
 
  
 
 
 
  
  
 
 
  
  
 
 
  
 
 
  
 
 
  


 
 
 
 
 
 
 
 
#line 80 "..\..\src\include\task\Test_SPI0_dma.h" 
 
 
 
 
 
 
 
 
 
 
#line 118 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\Drv\checksum.h" 































 
 
 
 
 
  
#line 1 "D:\software\Keil\C251\INC\stdio.h" 






 
 
 #pragma SAVE
 #pragma PARM251
 
 
#line 13 "D:\software\Keil\C251\INC\stdio.h" 
  
 
#line 15 "D:\software\Keil\C251\INC\stdio.h" 
 
 
#line 17 "D:\software\Keil\C251\INC\stdio.h" 
  
 
#line 19 "D:\software\Keil\C251\INC\stdio.h" 
 
 
#line 21 "D:\software\Keil\C251\INC\stdio.h" 
  
 
 
#line 24 "D:\software\Keil\C251\INC\stdio.h" 
 
 
 #pragma SAVE
 #pragma FUNCTIONS(STATIC)
 
 extern char _getkey  (void);
 extern char getchar  (void);
 extern char ungetchar(char);
 extern char putchar  (char);
 extern int  printf   (const char *, ...); 
 extern char *gets    (char *, int n);
 extern int  scanf    (const char *, ...);
 extern int  vprintf  (const char *, char *);
 extern int  puts     (const char *);
 #pragma RESTORE
 
 extern int  sprintf  (char *, const char *, ...);
 extern int  vsprintf (char *, const char *, char *);
 extern int  sscanf   (char *, const char *, ...);
 
#line 44 "D:\software\Keil\C251\INC\stdio.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 57 "D:\software\Keil\C251\INC\stdio.h" 
 
 #pragma RESTORE
#line 37 "..\..\src\include\Drv\checksum.h" 
 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 38 "..\..\src\include\Drv\checksum.h" 
#line 38 "..\..\src\include\Drv\checksum.h" 
 





 
 
 
 
 
 
 
 
 





 
 
 
 
 
 
 
 
 
 
 
 
 


 
 
#line 75 "..\..\src\include\Drv\checksum.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 94 "..\..\src\include\Drv\checksum.h" 
 unsigned short		crc_kermit(const unsigned char *input_str, unsigned short num_bytes);
 unsigned short		update_crc_kermit(unsigned short crc, unsigned char c );
 
#line 119 "..\..\src\include\config\CfgGlobal.h" 
 
  
#line 1 "..\..\src\include\task\Test_DebugOut.h" 













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_DebugOut.h" 
#line 21 "..\..\src\include\task\Test_DebugOut.h" 
 
 
 
#line 24 "..\..\src\include\task\Test_DebugOut.h" 


 
 


 
 


 
 


 
 
 
#line 41 "..\..\src\include\task\Test_DebugOut.h" 
 
 
 
 
 
 
#line 120 "..\..\src\include\config\CfgGlobal.h" 
 


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_SPI0.h" 
 
 


 
 
#line 27 "..\..\src\include\task\Test_SPI0.h" 


 
 


 
 


 
 
 
 
 
#line 42 "..\..\src\include\task\Test_SPI0.h" 
 
 
 
 
 
#line 15 "..\..\src\source\task\Test_spi0.c" 
 
  
#line 1 "..\..\src\include\task\Test_SPI0_dma.h" 













 
 
#line 16 "..\..\src\include\task\Test_SPI0_dma.h" 
  
 


 
  
 


 
 


 
 


 
 
  
  
  
  
 
  
  
  
  
 
 
  
  
  
  
 
  
 
 
 
  
  
 
 
  
  
 
 
  
 
 
  
 
 
  


 
 
 
 
 
 
 
 
  
  
  
  
  
  
 
 
 
 
#line 16 "..\..\src\source\task\Test_spi0.c" 
#line 16 "..\..\src\source\task\Test_spi0.c" 
 
 
 
#line 19 "..\..\src\source\task\Test_spi0.c" 
 


 
  
  
 
 
 
 
 
 
 
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 











 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 







 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 469 "..\..\src\source\task\Test_spi0.c" 
 
 
