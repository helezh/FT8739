
#line 1 "..\..\src\source\task\Test_CAL.c" 















 
 


 
  
#line 1 "D:\software\Keil\C251\INC\stdlib.h" 






 
 
 #pragma SAVE
 #pragma PARM251
 
 
 
 typedef unsigned int size_t;
 
 
 
 
 
 
 
 
 typedef char wchar_t;
 
 
 
 
 
 
 
 extern int     abs  (int   val) reentrant;
 extern long   labs  (long  val) reentrant;
 
 extern double atof (char *s1) reentrant;
 extern long   atol (char *s1) reentrant;
 extern int    atoi (char *s1) reentrant;
 extern int    rand ()         reentrant;
 extern void   srand (int)     reentrant;
 
 #pragma SAVE
 #pragma functions (static)
 
#line 43 "D:\software\Keil\C251\INC\stdlib.h" 
 
 
 
 
 
 
#line 49 "D:\software\Keil\C251\INC\stdlib.h" 
 extern void far   *malloc        (unsigned int size);
 extern void        free          (void far *p);
 extern void        init_mempool  (void far *p, unsigned int size);
 extern void far   *realloc       (void far *p, unsigned int size);
 extern void far   *calloc        (unsigned int size, unsigned int len);
 
 
 extern void far   *fmalloc       (unsigned int size);
 extern void        ffree         (void far *p);
 extern void        finit_mempool (void far *p, unsigned int size);
 extern void far   *frealloc      (void far *p, unsigned int size);
 extern void far   *fcalloc       (unsigned int size, unsigned int len);
 
 extern void xdata *xmalloc       (unsigned int size);
 extern void        xfree         (void xdata *p);
 extern void        xinit_mempool (void xdata *p, unsigned int size);
 extern void xdata *xrealloc      (void xdata *p, unsigned int size);
 extern void xdata *xcalloc       (unsigned int size, unsigned int len);
 #pragma RESTORE
 
#line 69 "D:\software\Keil\C251\INC\stdlib.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 84 "D:\software\Keil\C251\INC\stdlib.h" 
 
 #pragma RESTORE
#line 21 "..\..\src\source\task\Test_CAL.c" 
 
  
#line 1 "D:\software\Keil\C251\INC\math.h" 






 
 
 #pragma SAVE
 #pragma PARM251
 
 
 extern char   cabs  (char   val) reentrant;
 extern int     abs  (int    val) reentrant;
 extern long   labs  (long   val) reentrant;
 extern double fabs  (double val) reentrant;
 extern double sqrt  (double val) reentrant;
 extern double exp   (double val) reentrant;
 extern double log   (double val) reentrant;
 extern double log10 (double val) reentrant;
 extern double sin   (double val) reentrant;
 extern double cos   (double val) reentrant;
 extern double tan   (double val) reentrant;
 extern double asin  (double val) reentrant;
 extern double acos  (double val) reentrant;
 extern double atan  (double val) reentrant;
 extern double sinh  (double val) reentrant;
 extern double cosh  (double val) reentrant;
 extern double tanh  (double val) reentrant;
 extern double atan2 (double y, double x) reentrant;
 extern double ceil  (double val) reentrant;
 extern double floor (double val) reentrant;
 extern double modf  (double val, double *n) reentrant;
 extern double pow   (double x, double y) reentrant;
 extern double fmod  (double x, double y) reentrant;
 
 extern unsigned char _chkfloat_  (float x)  reentrant;
 extern unsigned char _chkdouble_ (double x) reentrant;
 
#line 40 "D:\software\Keil\C251\INC\math.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 64 "D:\software\Keil\C251\INC\math.h" 
 
 #pragma RESTORE
#line 22 "..\..\src\source\task\Test_CAL.c" 
 
  
#line 1 "..\..\src\include\task\Test_CAL.h" 
















 
 
 
 
 


 
  
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
 
 
 
 
 
 
#line 17 "D:\software\Keil\C251\INC\STDIO.H" 
  
 
#line 19 "D:\software\Keil\C251\INC\STDIO.H" 
 
 
#line 21 "D:\software\Keil\C251\INC\STDIO.H" 
  
 
 
#line 24 "D:\software\Keil\C251\INC\STDIO.H" 
 
 
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
















 
 
#line 19 "..\..\src\include\task\Test_CAL.h" 
  
 
 


 
  
 
 


 
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
 
 
 
  
  
 
 
  
  
 
 
 
  
  
  
  
  
  
  
  
 
 
 


 
 


 
 
 


 
 
 
  
 
 
 
#line 142 "..\..\src\include\task\Test_CAL.h" 
 
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













 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 21 "..\..\src\include\task\Test_spi0.h" 
#line 21 "..\..\src\include\task\Test_spi0.h" 
 
 


 
 
#line 27 "..\..\src\include\task\Test_spi0.h" 


 
 


 
 


 
 
 
 
 
#line 42 "..\..\src\include\task\Test_spi0.h" 
 
 
 
 
 
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
 


 
 


 
 


 
 
 
#line 25 "..\..\src\include\task\Test_CAL.h" 
 
 
 


 
 
 
#line 33 "..\..\src\include\task\Test_CAL.h" 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
 
#line 67 "..\..\src\include\task\Test_CAL.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 107 "..\..\src\include\task\Test_CAL.h" 
 
  
  
 
 
#line 112 "..\..\src\include\task\Test_CAL.h" 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 


 
 void Test_CAL(void);
 
#line 138 "..\..\src\include\task\Test_CAL.h" 
  
 
#line 140 "..\..\src\include\task\Test_CAL.h" 
 
 
 
#line 23 "..\..\src\source\task\Test_CAL.c" 
 
  
#line 1 "..\..\src\include\Drv\Drv_Cal.h" 














 
 
 
 
 


 
  
#line 1 "..\..\src\include\config\CfgGlobal.h" 















 
 
#line 18 "..\..\src\include\config\CfgGlobal.h" 
  
 


 
 
  
  
 
  
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  


 
 


 
 


 
 
 
#line 23 "..\..\src\include\Drv\Drv_Cal.h" 
#line 23 "..\..\src\include\Drv\Drv_Cal.h" 
 
  
#line 1 "\work space\FT8836 SVN\CAL¥Ú∂œ≤‚ ‘\FT8836-Module-20170523_for_cal_suspend\FT8836-Module-20170509\src\include\Drv\FT8836_Reg.h" 













 
 
 
#line 17 "\work space\FT8836 SVN\CAL¥Ú∂œ≤‚ ‘\FT8836-Module-20170523_for_cal_suspend\FT8836-Module-20170509\src\include\Drv\FT8836_Reg.h" 
  
 
 
 


 
  
 


 
  
  
 
  
 
  
  
  
  
  
  
  
 
 
 
  
 
  
  
  
  
  
 
 
  
 
  
  
  
  
  
 
 
  
 
  
  
  
  
  
 
 
 
 
 
 
  
 
 
  
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 
#line 24 "..\..\src\include\Drv\Drv_Cal.h" 
#line 24 "..\..\src\include\Drv\Drv_Cal.h" 
 
 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 61 "..\..\src\include\Drv\Drv_Cal.h" 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
#line 80 "..\..\src\include\Drv\Drv_Cal.h" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef struct
 {
 UINT16 CalBaseAddr[(18*36)];       
 UINT16 CalBaseAddr1[(18*36)];       
 UINT16 CalBaseAddr2[(18*36)];       
 SINT16 ScDiff[(18*36)];            
 UINT16 LastIdPos[10<<1];   
 UINT16 CurrIdPos[10<<1];   
 SINT16 CalOut[(11*11)];          
 } ST_FrameData;


 
 
 typedef struct
 {
 UINT8 ucTxLen;            
 UINT8 ucRxLen;            
 UINT8 ucShift;            
 UINT8 ucCfg;             
 UINT8 ucDataType;        
 UINT8 ucLineCfg;         
 UINT16 usSrc1Addr;        
 UINT16 usSrc2Addr;        
 UINT16 usDstAddr;         
 UINT16 usCalCmd;          
 } ST_CalMcMatrixParam;
 
 
 typedef struct
 {
 UINT8 ucMcPosPeakNum;      
 UINT8 ucMcNegPeakNum;      
 UINT16 ucMcPosAreaChNum;   
 UINT16 ucMcNegAreaChNum;   
 UINT16 usMCminValue;       
 UINT16 usMCminPos;         
 UINT16 usMCmaxValue;       
 UINT16 usMCmaxPos;         
 } ST_CalMcPeakInfo;
 
 
 typedef struct
 {
 UINT8 ucRxLen;            
 UINT8 ucTxLen;            
 UINT8 ucMaxPeakNum;       
 UINT8 ucSearchMod;        
 
 UINT16 usDiffAddr;        
 UINT16 usCalOutAddr;      
 UINT16 usNegOutAddr;      
 
 SINT16 usPosThd;          
 SINT16 usNegThd;          
 UINT16 usAreaThd;         
 SINT16 usNegAreaThd;      
 } ST_CalMcPeakDetectParam;
 
 
 typedef struct
 {
 UINT8 aucMcPosPeak[(10*3 )][2];             
 UINT8 aucMcNegPeak[(10*3 )][2];             
 UINT8 aucMcPeakValid[((10*3 ) >> 3) + 1];   
 UINT8 ucMcPosPeakNum;                          
 UINT8 ucMcNegPeakNum;                          
 UINT8 ucCurrPeakNum;                           
 UINT8 ucLastPeakNum;                           
 UINT16 ucMcPosAreaChNum;                        
 UINT16 ucMcNegAreaChNum;                        
 } ST_PeakData;
 
 typedef struct
 {
 UINT8 ucRxStart;
 UINT8 ucTxStart;
 UINT8 ucRxLen;
 UINT8 ucTxLen;
 UINT8 ucNoise;
 UINT8 ucMode;       
 UINT16 usDiffAddr;
 UINT16 usCalOutAddr;
 } ST_CalMcMacParam;
 
 
 typedef struct
 {
 UINT8  ucLastPoint;       
 UINT8  ucCurrPoint;       
 UINT16 usLastIdPosAddr;   
 UINT16 usCurrIdPosAddr;   
 UINT16 usCalOut;          
 } ST_CalKmIdParam;
 
 
 typedef struct
 {
 UINT8 ucS1TxLen;       
 UINT8 ucS1RxLen;       
 UINT16 usSrc1Addr;     
 UINT16 usDstAddr;      
 UINT16 usDmaMask;      
 } ST_CalMatrixAMov;
 


 
 extern BOOLEAN g_bCalResumeFlag;
 extern ST_CalRegisters *pCalRegs;
 extern UINT8 g_ucCalStartFlag,g_ucAmoveStart;
 


 
 void DrvCal_Init(UINT8 ucTxNum, UINT8 ucRxNum, UINT16 usDmask,UINT16 usDmaskA);
 void DrvCal_Cmd(UINT16 cmd);
 void DrvCal_MatrixProc(ST_CalMcMatrixParam *pMcMP);
 void DrvCal_MatrixAmp(ST_CalMcMatrixParam *pMcMP, SINT16 mul);
 void DrvCal_MatrixDiv(ST_CalMcMatrixParam *pMcMP, UINT8 div);
 void DrvCal_MatrixMul(ST_CalMcMatrixParam *pMcMP, UINT8 K_Num);
 void DrvCal_McPeak(ST_CalMcPeakDetectParam *pMcPDP, ST_CalMcPeakInfo *pMcPI);
 void DrvCal_Mac(ST_CalMcMacParam *pMacParm);
 void DrvCal_KmID(ST_CalKmIdParam *pKmIDParm);
 UINT16 DrvCal_CRC16(UINT16 usSrc1Addr, UINT16 usLen, UINT8 Area, BOOLEAN type);
 void DrvCal_MatrixMul2(ST_CalMcMatrixParam *pMcMP,BOOLEAN MulMode);
 void DrvCal_MatrixCompensation(ST_CalMcMatrixParam *pMcMP, UINT8 Thr, UINT8 Cfg);
 void DrvCal_LDS(ST_CalMcMatrixParam *pMcMP);
 void DrvCal_MDS(ST_CalMcMatrixParam *pMcMP);
 UINT16 DrvCal_Noise(UINT16 usSrc1Addr,UINT8 Tx_Len, UINT8 Rx_Len);
 void DrvCal_MatrixAMov(ST_CalMatrixAMov *pMcMP);
 void DrvCal_MatrixAvg(ST_CalMcMatrixParam *pMcMP,UINT8 usAvgMode);
 void DrvCal_MatrixMaxMin(ST_CalMcMatrixParam *pMcMP);
 UINT16 DrvCal_MatrixCount(ST_CalMcMatrixParam *pMcMP, SINT16 ssMin,SINT16 ssMax);
 void DrvCal_MatrixSubConst(ST_CalMcMatrixParam *pMcMP);
 void DrvCal_MatrixCMP(ST_CalMcMatrixParam *pMcMP);
 void DrvCal_MatrixMul3(ST_CalMcMatrixParam *pMcMP);
 
 
 
 
#line 24 "..\..\src\source\task\Test_CAL.c" 
 
  
#line 1 "..\..\src\include\Drv\FT8836_Reg.h" 













 
 
 
#line 17 "..\..\src\include\Drv\FT8836_Reg.h" 
  
 
 
 


 
  
 


 
  
  
 
  
 
  
  
  
  
  
  
  
 
 
 
  
 
  
  
  
  
  
 
 
  
 
  
  
  
  
  
 
 
  
 
  
  
  
  
  
 
 
 
 
 
 
  
 
 
  
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 
#line 25 "..\..\src\source\task\Test_CAL.c" 
#line 25 "..\..\src\source\task\Test_CAL.c" 
 
  
#line 1 "..\..\src\include\task\Test_Afe.h" 














 
 
#line 17 "..\..\src\include\task\Test_Afe.h" 
  
 


 
  
 
 


 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
 
 
  
  
 
 
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 
 
 
 
 
 
 
#line 284 "..\..\src\include\task\Test_Afe.h" 
 
#line 26 "..\..\src\source\task\Test_CAL.c" 
 
 
 


 
 ST_FrameData  g_stFrmData _at_ 0x1000; 
 volatile ST_Spi0DmaRegisters *near pSpi0_DmaRegs = (ST_Spi0DmaRegisters *)0xB200;
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 


 
 


 
 SINT16 * near T_tempbuf1;
 SINT16 * near T_tempbuf2;
 SINT16 * near T_tempbuf3;
 SINT16 * near T_tempOut;
 SINT16 * near g_pAfeAram = (volatile SINT16*)0xA000;
 UINT32 g_I2cCnt =0;
 UINT8 g_ucCalFlag = 0;
 
 


 
 
 






 
 BOOLEAN Test_CAL_MaxtixAdd()
 {
 UINT8 i,j;
 UINT8 shift;
 BOOLEAN flag;
 SINT32 temp;
 ST_CalMcMatrixParam near CalParam;
 static UINT8 counter = 0;
 
 printf("\n\nTest: Matrix add");
 
 if(counter == 4)
 counter = 0;
 
 shift = counter;
 counter ++;
 
 {
 printf("\nShift=%d",shift);
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 *(T_tempbuf1 + i*36 + j) =  rand()>>1;
 *(T_tempbuf2 + i*36 + j) =  rand()>>1;
 
 }
 }
 printf("\n\rMem-Mem:");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.ucShift    = shift;
 CalParam.usCalCmd   = (0x01<<4);
 CalParam.ucCfg      = 0;
 
 DrvCal_MatrixProc(&CalParam);
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 temp = (*(T_tempbuf1 + i*36 + j) + *(T_tempbuf2 + i*36 + j)) >> shift;
 if (temp > 0x7FFF)
 {   
 temp = 0x7FFF;
 }
 else if (temp < -32768)
 {
 temp = 0x8000;
 }
 if (*(T_tempOut + i*36 + j) != (SINT16)temp)
 {
 g_ucCalFlag = 1;
 printf("\n\r%03derror%04X,%04x",(i*36 + j),*(T_tempOut + i*36 + j),(SINT16)temp);
 }
 else
 {
 
 }
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rCal Add test is Error");
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf2 + i*36 + j)); 
 }
 printf("\n");
 }       
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal Add test is OK!");
 }
 
 
#line 176 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 255 "..\..\src\source\task\Test_CAL.c" 
 }
 
 return g_ucCalFlag;
 }
 
#line 260 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 262 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 BOOLEAN Test_CAL_MaxtixSub()
 {
 UINT8 i,j;
 UINT8 shift;
 UINT16 usSubMax;
 SINT16 temp;
 BOOLEAN flag;
 ST_CalMcMatrixParam near CalParam;
 static UINT8 counter = 0;
 printf("\n\nTest: Matrix sub");
 
 if(counter == 4)
 counter = 0;
 
 shift = counter;
 counter ++;
 
 
 {
 printf("\nShift=%d",shift);
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 T_tempbuf1[i*36 + j] = rand()>>1; 
 T_tempbuf2[i*36 + j] = rand()>>1; 
 
 }
 }
 
 printf("\nMem-Mem:");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.ucShift    = shift;
 CalParam.usCalCmd   = (0x00<<4);
 CalParam.ucCfg      = 0;
 
 DrvCal_MatrixProc(&CalParam);
 g_ucCalFlag = 0;
 usSubMax = 0;
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 temp = ((SINT16)*(T_tempbuf1 + i*36 + j) - (SINT16)*(T_tempbuf2 + i*36 + j)) >> shift;
 if (temp > 32767)
 {   
 temp = 32767;
 }
 else if (temp < -32768)
 {
 temp = -32768;
 }
 if (abs((SINT16)temp) > usSubMax)
 {
 usSubMax = abs((SINT16)temp);
 }
 if (*(T_tempOut + i*36 + j) != (SINT16)temp)
 {
 g_ucCalFlag = 1;
 printf("\n\r%03derror%04X,%04x",(i*36 + j),*(T_tempOut + i*36 + j),(SINT16)temp);
 }
 else
 {
 
 }
 }
 }
 if (g_ucCalFlag)
 {
 printf("\nCal SUB test is ERROR!");
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf2 + i*36 + j)); 
 }
 printf("\n");
 } 
 
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal SUB test is OK!");
 }
 
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 T_tempbuf1[i*36 + j] = rand()>>1; 
 
 g_pAfeAram[i*36 + j] = rand()>>1;
 }
 }
 
 
#line 385 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 466 "..\..\src\source\task\Test_CAL.c" 
 }
 return g_ucCalFlag;
 }
 
#line 470 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 472 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 BOOLEAN Test_CAL_MaxtixAmp()
 {
 UINT8 i,j;
 BOOLEAN flag;
 UINT8 shift;
 SINT16 mul;
 SINT32 temp;
 
 ST_CalMcMatrixParam near CalParam;
 static UINT8 counter = 0;
 printf("\n\nTest: Matrix amp");
 
 if(counter == 16)
 counter = 0;
 
 shift = counter;
 counter ++;   
 
 
 {
 printf("\n\rshift:%02d",shift);
 for (mul = -100; mul < 100; mul++)
 {         
 
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand() >> 4; 
 
 }
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.ucShift    = shift;
 CalParam.usCalCmd   = (0x04<<4);
 
 DrvCal_MatrixAmp(&CalParam,mul);
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 temp = (SINT16)(*(T_tempbuf1 + i*36 + j)) * mul;
 temp >>= shift;
 if (temp > 32767)
 {   
 temp = 32767;
 }
 else if (temp < -32768)
 {
 temp = -32768;
 }
 if (*(T_tempbuf2 + i*36 + j) != (SINT16)temp )
 {
 g_ucCalFlag = 1;
 printf("\nerror=%04x,%04x,%04x",*(T_tempbuf2 + i*36 + j),(SINT16)temp,*(T_tempbuf1 + i*36 + j));
 }
 else
 {
 
 }
 }    
 }
 if (g_ucCalFlag)
 {
 printf("\n\r\Mul:%03d,shift:%02d",mul,shift);
 printf("\n\rError");
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 {DelayMs(100);while(1);};
 }
 
 
#line 567 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 629 "..\..\src\source\task\Test_CAL.c" 
 
 }  
 printf("\nCal AMP test is OK!");
 
 }
 
 
 return g_ucCalFlag;
 }
 
#line 639 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 641 "..\..\src\source\task\Test_CAL.c" 
 
 
 






 
 BOOLEAN Test_CAL_MaxtixDiv()
 {
 UINT8 i,j;
 BOOLEAN flag;
 UINT8 Div;
 
 ST_CalMcMatrixParam near CalParam;
 
 printf("\n\nTest: Matrix div");
 
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand(); 
 }
 }
 
 Div = 25;
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x0F<<4); 
 
 DrvCal_MatrixDiv(&CalParam,Div);
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 if (*(T_tempbuf2 + i*36 + j) != (*(T_tempbuf1 + i*36 + j))/Div )
 {
 g_ucCalFlag = 1;
 printf("\n\r%03dERROR->Soft:%04X,Cal:%04x ",i*36+j,(*(T_tempbuf1 + i*36 + j))/Div,*(T_tempbuf2 + i*36 + j));
 }
 else
 {
 
 }
 }
 }
 if (g_ucCalFlag)
 {
 printf("\nCal DIV test mem is Error!");
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\nCal DIV test mem is OK!");
 }
 
 
#line 716 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 772 "..\..\src\source\task\Test_CAL.c" 
 return g_ucCalFlag;
 }
 
#line 775 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 777 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 BOOLEAN Test_CAL_MaxtixMov()
 {
 UINT8 i,j;
 BOOLEAN flag = 0;
 
 
#line 792 "..\..\src\source\task\Test_CAL.c" 
 
 
#line 794 "..\..\src\source\task\Test_CAL.c" 
 
 ST_CalMcMatrixParam near CalParam;
 
 printf("\n\nTest: Matrix mov");
 
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = rand();
 
 }
 }
 
 printf("\nMem to Mem");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x02<<4);
 CalParam.ucCfg      = 0;     
 
 DrvCal_MatrixProc(&CalParam);
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 if (*(T_tempbuf2 + i*36 + j) != *(T_tempbuf1 + i*36 + j))
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR->%04x,%04x",*(T_tempbuf2 + i*36 + j),*(T_tempbuf1 + i*36 + j));
 }
 else
 {
 
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\nCal MOV test is Error");
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\nCal MOV test is OK!");
 }
 
#line 844 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 891 "..\..\src\source\task\Test_CAL.c" 
 return g_ucCalFlag;
 }
 
#line 894 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 896 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 BOOLEAN Test_CAL_MaxtixMov2()
 {
 UINT8 i,j;
 BOOLEAN flag = 0;
 ST_CalMcMatrixParam near CalParam;
 
 printf("\n\nTest: Matrix mov2");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = rand();
 }
 }
 
 printf("\n\rMem to Mem");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x02<<4);
 CalParam.ucCfg      = 1;     
 
 DrvCal_MatrixProc(&CalParam);
 
 for (i = 0; i < 36; i++)
 {
 for (j = 0; j < 18; j++)
 {
 *(T_tempOut+ i*18 + j) = *(T_tempbuf1 + j*36 + i);
 }
 }
 g_ucCalFlag = 0;
 
 for (i = 0; i < 36; i++)
 {
 for (j = 0; j < 18; j++)
 {
 if (*(T_tempbuf2 + i*18 + j) != *(T_tempOut + i*18 + j))
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR->%04x,%04x",*(T_tempbuf2 + i*18 + j),*(T_tempOut + i*18 + j));
 }
 else
 {
 
 }
 }
 }
 if (g_ucCalFlag)
 {
 printf("\nCal MOV2 test is Error");
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\nCal MOV2 test is OK!");
 }
 
 
#line 965 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 1020 "..\..\src\source\task\Test_CAL.c" 
 return g_ucCalFlag;
 }
 
#line 1023 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 1025 "..\..\src\source\task\Test_CAL.c" 
 
 









 
 BOOLEAN Test_CAL_MaxtixMul_PtoP1()
 {
 UINT8 i,j;
 UINT8 ucShift;
 SINT16 tmp;
 BOOLEAN flag;
 ST_CalMcMatrixParam near CalParam;
 static UINT8 counter = 0;
 
 printf("\n\nTest: Matrix MUL2_1");
 
 
 if(counter == 16)
 counter = 0;
 
 ucShift = counter;
 counter ++;    
 
 printf("\nmem-mem");
 
 for (i=0; i<36; i++)
 {
 *(T_tempbuf1 + i) = (SINT8)rand()>>2; 
 
 }
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf2 + i*36 + j) = (SINT8)rand()>>2; 
 }
 
 }
 
 
 {
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x0E<<4);
 CalParam.ucShift    = ucShift;
 CalParam.ucCfg      = 0;
 
 DrvCal_MatrixMul2(&CalParam,0);
 
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 tmp = (((SINT16)*(T_tempbuf1 + j)) * ((SINT16)*(T_tempbuf2 + i*36 + j)));
 tmp >>= ucShift;
 if (tmp > 32767)
 {
 tmp = 32767;
 }
 else if (tmp < -32768)
 {
 tmp = -32768;
 }
 if (*(T_tempOut + i*36 + j) != (SINT16)tmp )
 {
 printf("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*36 + j),(SINT16)tmp,i,j);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rCal MUL2 Rx test %02d is Error!",ucShift);
 printf("\n");
 for (i = 0; i < 1; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf2 + i*36 + j)); 
 }
 printf("\n");
 }             
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal MUL2 Rx test %02d is OK!",ucShift);
 }
 }
 
 
 for (i=0; i<18; i++)
 {
 *(T_tempbuf1 + i) = (SINT8)rand()>>2;
 
 }
 
 
 {
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x0E<<4);
 CalParam.ucShift    = ucShift;
 CalParam.ucCfg      = 1;
 
 DrvCal_MatrixMul2(&CalParam,0);        
 
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 tmp = (((SINT16)*(T_tempbuf1 + i)) * ((SINT16)*(T_tempbuf2 + i*36 + j)));
 tmp >>= ucShift;
 if (tmp > 32767)
 {
 tmp = 32767;
 }
 else if (tmp < -32768)
 {
 tmp = -32768;
 }
 if (*(T_tempOut + i*36 + j) != (SINT16)tmp )
 {
 printf("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*36 + j),(SINT16)tmp,i,j);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rCal MUL2 Tx test %02d is Error!",ucShift);
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 1; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf2 + i*36 + j)); 
 }
 printf("\n");
 }             
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal MUL2 Tx test %02d is OK!",ucShift);
 }
 }
 
 
#line 1222 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 1391 "..\..\src\source\task\Test_CAL.c" 
 
 return g_ucCalFlag;
 }
 
#line 1395 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 1397 "..\..\src\source\task\Test_CAL.c" 
 
 









 
 BOOLEAN Test_CAL_MaxtixMul_PtoP2()
 {
 UINT8 i,j;
 UINT8 ucShift;
 SINT16 tmp;
 BOOLEAN flag;
 ST_CalMcMatrixParam near CalParam;
 static UINT8 counter = 0;
 
 printf("\n\n\rTest: Matrix MUL2");
 
 
 if(counter == 16)
 counter = 0;
 
 ucShift = counter;
 counter ++;  
 
 
 
 printf("\nmem-men");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT8)rand()>>2; 
 *(T_tempbuf2 + i*36 + j) = (SINT8)rand()>>2; 
 }
 
 }
 
 
 {
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x0E<<4);
 CalParam.ucShift    = ucShift;
 
 DrvCal_MatrixMul2(&CalParam,1);
 
 
 g_ucCalFlag = 0;
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 tmp = (*(T_tempbuf1 + i*36 + j)* (((SINT16)*(T_tempbuf2 + i*36 + j))));
 tmp >>= ucShift;
 if (tmp > 32767)
 {
 tmp = 32767;
 }
 else if (tmp < -32768)
 {
 tmp = -32768;
 }
 if (*(T_tempOut + i*36 + j) != (SINT16)tmp )
 {
 printf("\n\rERROR->%04x,%04x",*(T_tempOut + i*36 + j),tmp);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rCal MUL2 test %d is Error!",ucShift);
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf2 + i*36 + j)); 
 }
 printf("\n");
 }             
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal MUL2 test %d is OK!",ucShift);
 }     
 }
 
 
#line 1511 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 1593 "..\..\src\source\task\Test_CAL.c" 
 return g_ucCalFlag;
 }
 
#line 1596 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 1598 "..\..\src\source\task\Test_CAL.c" 
 
 
 






 
 BOOLEAN Test_CAL_MaxtixCom_1()
 {
 UINT8 i,j;
 BOOLEAN flag;
 UINT8 step = 50;
 UINT8 Threshlod = 100;
 ST_CalMcMatrixParam near CalParam;
 
 printf("\n\nTest: Matrix Compensation_1");
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand()>>1;
 *(T_tempbuf2 + i*36 + j) = rand()>>8; 
 }
 
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);     
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);     
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);     
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x03<<4);
 CalParam.ucCfg      = 0;
 
 DrvCal_MatrixCompensation(&CalParam,Threshlod,step);
 
 g_ucCalFlag = 0;
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 
#line 1645 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
#line 1651 "..\..\src\source\task\Test_CAL.c" 
 {
 
 if (*(T_tempbuf1 + i*36 + j) > Threshlod)
 {
 if (*(T_tempOut + i*36 + j) != *(T_tempbuf2 + i*36 + j) + step )
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR->out=%04x,base=%04x,step=%04x",*(T_tempOut + i*36 + j),*(T_tempbuf2 + i*36 + j),step);
 }
 else
 {
 
 }
 }
 else if (*(T_tempbuf1 + i*36 + j) < -Threshlod)
 {
 if (*(T_tempOut + i*36 + j) != *(T_tempbuf2 + i*36 + j) - step )
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR->out=%04x,base=%04x,step=%04x",*(T_tempOut + i*36 + j),*(T_tempbuf2 + i*36 + j),step);
 }
 else
 {
 
 }
 }
 else
 {
 if (*(T_tempOut + i*36 + j) != *(T_tempbuf2 + i*36 + j))
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR->out=%04x,base=%04x,step=%04x",*(T_tempOut + i*36 + j),*(T_tempbuf2 + i*36 + j),step);
 }
 else
 {
 
 }
 }
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rCal COM_1 test is Error!");
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf2 + i*36 + j)); 
 }
 printf("\n");
 }    
 
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal COM_1 test is OK!");
 }
 
 return g_ucCalFlag;
 }
 
 
#line 1729 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 1731 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 BOOLEAN Test_CAL_MaxtixCom_2()
 {
 UINT8 i,j;
 BOOLEAN flag;
 UINT8 mode;
 UINT8 step = 50;
 UINT8 Threshlod = 100;
 ST_CalMcMatrixParam near CalParam;
 
 printf("\n\nTest Matrix Compensation_2 TX");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand()>>1;
 }
 }
 for (i = 0; i < 18; i++)
 {
 *(T_tempbuf2 + i) = rand()>>8; 
 }
 mode = 0;
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);     
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);     
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);     
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x03<<4);
 CalParam.ucCfg      = 1;
 
 DrvCal_MatrixCompensation(&CalParam,Threshlod,mode);
 
 g_ucCalFlag = 0;
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
#line 1778 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
#line 1784 "..\..\src\source\task\Test_CAL.c" 
 {
 
 if (*(T_tempbuf1 + i*36 + j) > Threshlod)
 {
 if (*(T_tempOut + i*36 + j) != *(T_tempbuf1 + i*36 + j) - (T_tempbuf2[i]))
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR>->out=%04x,%04x,%04x",*(T_tempOut + i*36 + j),*(T_tempbuf1+ i*36 + j) - T_tempbuf2[i],i);
 }
 }
 else if (*(T_tempbuf1 + i*36 + j) < -Threshlod)
 {
 if (*(T_tempOut + i*36 + j) != *(T_tempbuf1 + i*36 + j) + T_tempbuf2[i])
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR<->out=%04x,%04x,%04x",*(T_tempOut + i*36 + j),*(T_tempbuf1+ i*36 + j) - T_tempbuf2[i],i);
 }
 else
 {
 
 }
 }
 else
 {
 
 if (*(T_tempOut + i*36 + j) != *(T_tempbuf1 + i*36 + j))
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR=->out=%04x,%04x,%04x",*(T_tempOut + i*36 + j),*(T_tempbuf1+ i*36 + j) - T_tempbuf2[i],i);
 }
 else
 {
 
 }
 }
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\nCal COM_2 Tx test is Error!");
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf2 + i*36 + j)); 
 }
 printf("\n");
 }    
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\nCal COM_2 Tx test is OK!");
 }
 
 
 printf("\n\nTest  Matrix Compensation_2 Rx");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand()>>1;
 }
 }
 for (i = 0; i < 36; i++)
 {
 *(T_tempbuf2 + i) = i+20;
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);     
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);     
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);     
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x03<<4);
 CalParam.ucCfg      = 1;
 mode = 1;
 DrvCal_MatrixCompensation(&CalParam,Threshlod,mode);
 
 g_ucCalFlag = 0;
 for (i=0; i<36; i++)
 {
 for (j=0; j<18; j++)
 {
 
#line 1884 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
#line 1890 "..\..\src\source\task\Test_CAL.c" 
 {
 if (*(T_tempbuf1 + j*36 + i) > Threshlod)
 {
 if (*(T_tempOut + j*36 + i) != *(T_tempbuf1 + j*36 + i) - T_tempbuf2[i])
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR->out=%04x,%04x,%04x",*(T_tempOut + j*36 + i),*(T_tempbuf1+ j*36 + i) - T_tempbuf2[i],i);
 }
 else
 {
 
 }
 }
 else if (*(T_tempbuf1 + j*36 + i) < -Threshlod)
 {
 if (*(T_tempOut + j*36 + i) != *(T_tempbuf1 + j*36 + i) + T_tempbuf2[i])
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR->out=%04x,%04x,%04x",*(T_tempOut + j*18 + i),*(T_tempbuf1+ j*18 + i) - T_tempbuf2[i],i);
 }
 }
 else
 {
 if (*(T_tempOut + j*36 + i) != *(T_tempbuf1 + j*36 + i))
 {
 g_ucCalFlag = 1;
 printf("\n\rERROR->out=%04x,%04x,%04x",*(T_tempOut + j*36 + i),*(T_tempbuf1+ j*36 + i) - T_tempbuf2[i],i);
 }
 
 }
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\nCal COM_2 Rx test is Error!");
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf2 + i*36 + j)); 
 }
 printf("\n");
 }    
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\nCal COM_2 Rx test is OK!");
 }
 return g_ucCalFlag;
 }
 
#line 1957 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 1959 "..\..\src\source\task\Test_CAL.c" 
 
 







 
 BOOLEAN Test_CAL_LDS()
 {
 UINT8 i,j;
 UINT16 x0,x1,y0,y1;
 BOOLEAN flag;
 
 UINT16 DisSoft;
 UINT16 DisCal;
 
 ST_CalMcMatrixParam near CalParam;
 
 
 
 
 printf("\n\nTest: LDS %d*%d",18,36);
 for (i=0; i<18/2; i++)
 {
 for (j=0; j<36*2; j++)
 {
 *(T_tempbuf1 + i*2*36 + j) = (UINT8)rand();
 *(T_tempbuf2 + i*2*36 + j) = (UINT8)rand();
 }
 }
 
 
 
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18/2;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x07<<4);
 
 DrvCal_LDS(&CalParam);
 
 
 printf("\n\nAfter LDS");
 for (i=0; i<18/2; i++)
 {
 for (j=0; j<36; j++)
 {
 x0 = *(T_tempbuf1 + i*2*36 + 2*j);
 y0 = *(T_tempbuf1 + i*2*36 + 2*j+1);
 x1 = *(T_tempbuf2 + i*2*36 + 2*j);
 y1 = *(T_tempbuf2 + i*2*36 + 2*j+1); 
 
 DisSoft = sqrt(((UINT32)x0-x1)*((UINT32)x0-x1)+((UINT32)y0-y1)*((UINT32)y0-y1));
 DisCal = *(T_tempOut + i*36 + j);
 
 if (DisSoft != DisCal)
 {
 g_ucCalFlag = 1;
 printf("\nLDS error soft:%d,cal:%d",DisSoft,DisCal);
 printf("\nx0=%d,x1=%d,y1=%d,y2=%d",x0,x1,y0,y1);
 }
 }
 }
 
 if(g_ucCalFlag)
 {
 printf("\nLDS ERROR"); 
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(g_pAfeAram + i*36 + j)); 
 }
 printf("\n");
 }    
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\nLDS OK");
 }
 return 0;   
 }
 
#line 2061 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 2063 "..\..\src\source\task\Test_CAL.c" 
 
 









 
 
 
 
 BOOLEAN Test_CAL_MDS()
 {
 
#line 2081 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 2156 "..\..\src\source\task\Test_CAL.c" 
 UINT8 i,j;
 UINT16 x0,x1,y0,y1;
 BOOLEAN flag;
 
 UINT16 DisSoft;
 UINT16 DisCal;
 
 ST_CalMcMatrixParam near CalParam;
 
 
 
 
 printf("\n\rTest: MDS %d*%d",18,36);
 
 for (i=0; i<11*2; i++)
 {
 *(T_tempbuf1 + i) = (UINT8)rand(); 
 }
 
 for (i=0; i<11*2; i++)
 {
 *(T_tempbuf2 + i) = (UINT8)rand(); 
 }
 
 
 
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 
 
 CalParam.ucTxLen    = 11;
 CalParam.ucRxLen    = 11;
 CalParam.usCalCmd   = (0x06<<4);
 
 DrvCal_MDS(&CalParam);
 
 printf("\n\nAfter MDS\n");
 for (i=0; i<11; i++)
 {
 for (j=0; j<11; j++)
 {
 
 x0 = *(T_tempbuf1 + 2*j);
 y0 = *(T_tempbuf1 + 2*j+1);
 x1 = *(T_tempbuf2 + 2*i);
 y1 = *(T_tempbuf2 + 2*i+1); 
 
 DisSoft = sqrt(((UINT32)x0-x1)*((UINT32)x0-x1)+((UINT32)y0-y1)*((UINT32)y0-y1));       
 DisCal = *(T_tempOut + j*11 + i);
 if (DisSoft != DisCal)
 {
 g_ucCalFlag = 1;
 printf("\n\rMDS ERROR->out:%04x,soft=%04x",DisCal,DisSoft);
 {DelayMs(100);while(1);};
 return 1;
 } 
 else
 {
 
 }
 }
 }
 printf("\nMDS OK");
 return 0;
 
 }
 
#line 2225 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 2227 "..\..\src\source\task\Test_CAL.c" 
 
 










 
 BOOLEAN Test_CAL_CHK()
 {
 BOOLEAN flag = 0;
 UINT8 i,j;
 UINT16 check;
 
 UINT16 max;
 UINT16 min;
 UINT16 max_all;
 UINT16 near RxMax[36];
 printf("\n");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 T_tempbuf1[i*36 + j] = (SINT16)rand()>>1; 
 }
 
 }
 
 printf("\n\nTest: CHK");
 printf("\nmen");
 
 max_all = 0;
 for (i = 0; i < 36; i++)
 {
 min = 0x7FFF;
 max = 0;
 for (j = 0; j < 18; j++)
 {
 if (T_tempbuf1[j*36 + i] > max)
 {
 max = T_tempbuf1[j*36 + i];
 }
 if (T_tempbuf1[j*36 + i] < min)
 {
 min = T_tempbuf1[j*36 + i];
 }
 }
 RxMax[i] = max - min;
 if (RxMax[i] > max_all)
 {
 max_all = RxMax[i];
 }
 }
 
 check = DrvCal_Noise((UINT16)(g_stFrmData.CalBaseAddr),18,36);
 
 if (max_all != check)
 {
 g_ucCalFlag = 1;
 }
 
 printf("\nCHK = 0x%x,soft:0x%x",check,max_all);
 
 if (g_ucCalFlag)
 {
 printf("\nError");
 printf("\n");
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 printf(" %04x",*(T_tempbuf1 + i*36 + j)); 
 }
 printf("\n");
 }
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\nOK!");
 }
 
 
#line 2316 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 2382 "..\..\src\source\task\Test_CAL.c" 
 return g_ucCalFlag;
 }
 
 
#line 2386 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 2388 "..\..\src\source\task\Test_CAL.c" 
 
 
 






 
 UINT16 GetCrc16(UINT32 addr,UINT16 length,UINT8 bPram)
 {
 UINT16 cFcs = 0;
 UINT32 i, j;
 
 for ( i = 0; i < length; i++ )
 {
 if ((bPram == 3)||(bPram == 4))
 {
 
#line 2408 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
#line 2418 "..\..\src\source\task\Test_CAL.c" 
 
 cFcs ^= (*((UINT16 far *)(0xFEE800 + addr+i*2)));
 
 }
 else if(bPram == 0)
 {
 cFcs ^= (*((UINT16 *)((UINT32)0x0000 + (addr+i*2))));
 }
 else if(bPram == 2)
 {
 cFcs ^= (*((UINT16 far *)((UINT32)0xFD0000 + (addr+i*2))));
 }           
 
 for (j = 0; j < 16; j ++)
 {
 if (cFcs & 1)
 {
 cFcs = (UINT16)((cFcs >> 1) ^ ((1 << 15) + (1 << 10) + (1 << 3)));
 }
 else
 {
 cFcs >>= 1;
 }
 }
 }
 return cFcs;
 }






 
 BOOLEAN Test_CAL_CRC()
 {
 BOOLEAN flag = 0;
 
 UINT16 ResultCal;
 UINT16 ResultSoft;
 
 printf("\n\nTest: CRC");
 
 
 
#line 2463 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 2492 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 printf("\n\rPram:");
 
 
 ResultCal = DrvCal_CRC16(0xE800,35*1024,3,0);
 
 printf("\n\rCal CRC = %x",ResultCal);
 
 ResultSoft = GetCrc16(0x0000,35*1024,3);
 
 printf("\n\rSoft CRC = %x",ResultSoft);
 
 if (ResultCal != ResultSoft)
 {
 g_ucCalFlag = 1;
 printf("\n\rError");
 {DelayMs(100);while(1);};
 return 1;
 }
 else
 {
 printf("\n\rOK");
 }
 
 
 
 printf("\n\rProm:");
 
 
 ResultCal = DrvCal_CRC16(0x00,2*1024,2,0);
 printf("\n\rCal CRC = %x",ResultCal);
 
 
 ResultSoft = GetCrc16(0x00,2*1024,2);
 printf("\n\rSoft CRC = %x",ResultSoft);
 
 if (ResultCal != ResultSoft)
 {
 g_ucCalFlag = 1;
 printf("\n\rError");
 {DelayMs(100);while(1);};
 return 1;
 }
 else
 {
 printf("\n\rOK");
 }    
 
 return g_ucCalFlag;
 }
 
 
#line 2546 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 2548 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 UINT16 GetXorSum(UINT32 addr,UINT16 length,UINT8 bPram)
 {
 UINT16 cFcs = 0;
 UINT32 i,j;
 for ( i = 0; i < length; i++ )
 {
 if ((bPram == 4)||(bPram == 3))
 {
 
#line 2566 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
#line 2576 "..\..\src\source\task\Test_CAL.c" 
 
 cFcs ^= (*((UINT16 far *)(0xFEE800 + addr+i*2)));
 
 }
 else if(bPram == 0)
 {
 cFcs ^= (*((UINT16 *)((UINT32)0x0000 + (addr+i*2))));
 }
 else if(bPram == 2)
 {
 cFcs ^= (*((UINT16 far *)((UINT32)0xFD0000 + (addr+i*2))));
 }           
 
 }
 
 return cFcs;
 }
 






 
 BOOLEAN Test_CAL_XORSUM()
 {
 UINT8 i,j;
 BOOLEAN flag = 0;
 UINT16 ResultCal;
 UINT16 ResultSoft;
 
 printf("\n\nTest: XORSUM");
 
 
 printf("\nDram:");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = rand();
 }
 }
 
 ResultCal = DrvCal_CRC16((UINT16)T_tempbuf1,18*36*2,0,1);
 printf("\nCal Xorsum = %x",ResultCal);
 
 ResultSoft = GetXorSum((UINT16)T_tempbuf1,18*36*2,0);
 printf("\n\rSoft Xorsum = %x",ResultSoft);
 
 if (ResultCal != ResultSoft)
 {
 g_ucCalFlag = 1;
 printf("\nError");
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\nOK");
 }
 
 
 
 printf("\n\rPram:");
 
 
 ResultCal = DrvCal_CRC16(0xE800,35*1024,3,1);
 printf("\n\rCal Xorsum = %x",ResultCal);
 
 ResultSoft = GetXorSum(0x0000,35*1024,3);
 printf("\n\rSoft Xorsum = %x",ResultSoft);
 
 if (ResultCal != ResultSoft)
 {
 g_ucCalFlag = 1;
 printf("\n\rError");
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rOK");
 }
 
 
 
 
 
 printf("\n\rProm:");
 
 
 ResultCal = DrvCal_CRC16(0x00,2*1024,2,1);
 printf("\n\rCal Xorsum = %x",ResultCal);
 
 ResultSoft = GetXorSum(0x0000,2*1024,2);
 printf("\n\rSoft Xorsum = %x",ResultSoft);
 
 if (ResultCal != ResultSoft)
 {
 g_ucCalFlag = 1;
 printf("\n\rError");
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rOK");
 }
 
 
 return g_ucCalFlag;
 }
 
 
#line 2688 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 2690 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 






 
 
 void Test_CAL_MAC_1()
 {
 UINT8 i,j;
 SINT32 ulSum_c  = 0;
 SINT32 ulSum_tx = 0;
 SINT32 ulSum_rx = 0;
 ST_CalMcMacParam near CalParam;
 
 printf("\n\nCal Mac test start\n");
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = rand();
 *(T_tempbuf2 + i*36 + j) = 0x00;
 }
 }
 
 
#line 2722 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
#line 2734 "..\..\src\source\task\Test_CAL.c" 
 
 
 CalParam.usDiffAddr    = (UINT16)(g_stFrmData.CalBaseAddr) + (2*36 + 2)*2;   
 CalParam.usCalOutAddr  = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);    
 CalParam.ucTxStart     = 2;
 CalParam.ucRxStart     = 2;
 CalParam.ucTxLen       = 5;
 CalParam.ucRxLen       = 5;
 
 
 CalParam.ucMode        = (0<<1) + 0;
 CalParam.ucNoise       = 0;
 
 DrvCal_Mac(&CalParam);
 
 for (i = 2; i<(2+5); i++)
 {
 for (j = 2; j<(2+5); j++)
 {
 
 if ((T_tempbuf1[i*36 + j] - 0) >= 0)
 {
 ulSum_c  += T_tempbuf1[i*36 + j] - 0;
 ulSum_tx += ((T_tempbuf1[i*36 + j] - 0)*i);
 ulSum_rx += ((T_tempbuf1[i*36 + j] - 0)*j);
 }
 
#line 2761 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 2774 "..\..\src\source\task\Test_CAL.c" 
 }
 }
 
 printf("\n\r%08lx %08lx %08lx",ulSum_c,ulSum_tx,ulSum_rx);
 
 printf("\n");
 for (i=0; i<6; i++)
 {
 printf("%04x ",*(T_tempbuf2 + i));
 }
 if(((SINT16)(ulSum_c>>16)==T_tempbuf2[0])&&((SINT16)(ulSum_c&0xFFFF) == T_tempbuf2[1])      &&((SINT16)(ulSum_tx>>16)==T_tempbuf2[2])&&((SINT16)(ulSum_tx&0xFFFF) == T_tempbuf2[3])      &&((SINT16)(ulSum_rx>>16)==T_tempbuf2[4])&&((SINT16)(ulSum_rx&0xFFFF) == T_tempbuf2[5]))


 
 {
 printf("\nMAC_1 OK");
 }
 else
 {
 printf("\nMAC_1 ERROR");
 {DelayMs(100);while(1);};
 }
 
 
 }
 
#line 2800 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 2802 "..\..\src\source\task\Test_CAL.c" 
 
 
 






 
 void Test_CAL_MAC_2()
 {
 UINT8 i,j;
 SINT32 ulSum_c  = 0;
 SINT32 ulSum_tx = 0;
 SINT32 ulSum_rx = 0;
 ST_CalMcMacParam near CalParam;
 
 printf("\n\nCal Mac test start\n");
 
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = rand();
 *(T_tempbuf2 + i*36 + j) = 0x00;
 }
 }
 
#line 2832 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
#line 2844 "..\..\src\source\task\Test_CAL.c" 
 CalParam.usDiffAddr    = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usCalOutAddr  = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.ucTxStart     = 0;
 CalParam.ucRxStart     = 0;
 CalParam.ucTxLen       = 5;
 CalParam.ucRxLen       = 5;
 CalParam.ucMode        = (1<<1) + 1;
 CalParam.ucNoise       = 0;
 
 DrvCal_Mac(&CalParam);
 
 for (i = 0; i<5; i++)
 {
 for (j = 0; j<5; j++)
 {
 
#line 2860 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
#line 2867 "..\..\src\source\task\Test_CAL.c" 
 if ((T_tempbuf1[i*5 + j] - 0) >= 0)
 {
 ulSum_c  += (T_tempbuf1[i*5 + j] - 0);
 ulSum_tx += ((T_tempbuf1[i*5 + j] - 0)*i);
 ulSum_rx += ((T_tempbuf1[i*5 + j] - 0)*j);
 }
 else if ((0-T_tempbuf1[i*5 + j] - 0) >= 0)
 {
 ulSum_c  += (0-T_tempbuf1[i*5 + j] - 0);
 ulSum_tx += ((0-T_tempbuf1[i*5 + j] - 0)*i);
 ulSum_rx += ((0-T_tempbuf1[i*5 + j] - 0)*j);
 }
 
 
 }
 }
 printf("\n%08lx %08lx %08lx",ulSum_c,ulSum_tx,ulSum_rx);
 
 printf("\n");
 for (i=0; i<6; i++)
 {
 printf("%04x ",*(T_tempbuf2 + i));
 }
 
 
 if(((SINT16)(ulSum_c>>16)==T_tempbuf2[0])&&((SINT16)(ulSum_c&0xFFFF) == T_tempbuf2[1])  &&((SINT16)(ulSum_tx>>16)==T_tempbuf2[2])&&((SINT16)(ulSum_tx&0xFFFF) == T_tempbuf2[3])  &&((SINT16)(ulSum_rx>>16)==T_tempbuf2[4])&&((SINT16)(ulSum_rx&0xFFFF) == T_tempbuf2[5]))    


 {
 printf("\nMAC_2 OK");
 }
 else
 {
 printf("\nMAC_2 ERROR");
 {DelayMs(100);while(1);};
 }
 
 }
 
#line 2906 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 2908 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 void Test_CAL_ID()
 {
 UINT8 i;
 UINT8 ucLastNum = 4;
 UINT8 ucCurrNum = 8;
 UINT8 ucMaxNum  = 10;
 ST_CalKmIdParam near stKmIDp;
 
 printf("\n\nCal ID test start");
 
 
 for (i = 0; i < (ucMaxNum << 1); i++ )
 {
 g_stFrmData.CurrIdPos[i] = 0x7FFF;
 g_stFrmData.LastIdPos[i] = 0x7FFF;
 }
 
 for (i = 0; i < ucLastNum; i++)
 {
 g_stFrmData.LastIdPos[2*i]   = i*10;
 g_stFrmData.LastIdPos[2*i+1] = i*10;
 }
 
 for (i = 0; i < ucCurrNum; i++)
 {
 g_stFrmData.CurrIdPos[2*i]   = (ucCurrNum-i)*10 + 1;
 g_stFrmData.CurrIdPos[2*i+1] = (ucCurrNum-i)*10 + 1;
 }
 
 stKmIDp.usLastIdPosAddr = (UINT16)g_stFrmData.LastIdPos;
 stKmIDp.usCurrIdPosAddr = (UINT16)g_stFrmData.CurrIdPos;
 stKmIDp.usCalOut   = (UINT16)T_tempOut;
 stKmIDp.ucLastPoint = ucLastNum;
 stKmIDp.ucCurrPoint = ucCurrNum;
 
 printf("\n\rFirst ID:L=%d,N=%d",ucLastNum,ucCurrNum);
 DrvCal_KmID(&stKmIDp);
 
 for (i = 0; i < ucMaxNum; i++)
 {
 UINT8 id;
 id = *(UINT16*)(T_tempOut + i);
 
 if (id == 0x0F)
 {
 printf("\n\rID%x:  %2d--  %4d--XXXX",i,id + 1, g_stFrmData.LastIdPos[i*2]);
 }
 else
 {
 printf("\n\rID%x:  %2d--  %4d--  %4d",i,id + 1, g_stFrmData.LastIdPos[i*2], g_stFrmData.CurrIdPos[id*2]);
 }
 }
 
 if((*(UINT16*)(T_tempOut ) != 7)||(*(UINT16*)(T_tempOut + 1) != 6)||(*(UINT16*)(T_tempOut + 2) != 5)||(*(UINT16*)(T_tempOut + 3) != 4))
 {
 printf("\nERROR");
 {DelayMs(100);while(1);};
 }
 
 ucLastNum = 8;
 ucCurrNum = 4;
 stKmIDp.ucLastPoint = ucLastNum;
 stKmIDp.ucCurrPoint = ucCurrNum;
 
 printf("\n\nSecond ID:L=%d,N=%d",ucLastNum,ucCurrNum);
 
 for (i = 0; i < (ucMaxNum << 1); i++ )
 {
 g_stFrmData.CurrIdPos[i] = 0x7FFF;
 g_stFrmData.LastIdPos[i] = 0x7FFF;
 }
 
 for (i = 0; i < ucLastNum; i++)
 {
 g_stFrmData.LastIdPos[2*i]   = i*10;
 g_stFrmData.LastIdPos[2*i+1] = i*10;
 }
 
 for (i = 0; i < ucCurrNum; i++)
 {
 g_stFrmData.CurrIdPos[2*i]   = i*10 + 1;
 g_stFrmData.CurrIdPos[2*i+1] = i*10 + 1;
 }
 
 DrvCal_KmID(&stKmIDp);
 
 for (i = 0; i < ucMaxNum; i++)
 {
 UINT8 id;
 id = *(UINT16*)(T_tempOut + i);
 if (id == 0x0F)
 {
 printf("\n\rID%x:%2d--%4d--XXXX",i,id + 1, g_stFrmData.LastIdPos[i*2]);
 }
 else
 {
 printf("\n\rID%x:%2d--%4d--%4d",i,id + 1, g_stFrmData.LastIdPos[i*2], g_stFrmData.CurrIdPos[id*2]);
 }
 }
 
 if((*(UINT16*)(T_tempOut ) != 0)||(*(UINT16*)(T_tempOut + 1) != 1)||(*(UINT16*)(T_tempOut + 2) != 2)||(*(UINT16*)(T_tempOut + 3) != 3))
 {
 printf("\nERROR");
 {DelayMs(100);while(1);};
 }
 
 
 }
 
#line 3026 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 3028 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 void Test_CAL_SearchPeak()
 {
 UINT8 i,j;
 UINT8 ucPeakValidGroup;
 UINT8 ucPeakValidPos;
 UINT16 near ausNegPeaks[(10*3 ) + 1];
 UINT16 *pNegPeakBuf;
 ST_CalMcPeakDetectParam near stMcPDP;
 ST_CalMcPeakInfo near stMcPI;
 ST_PeakData  near  g_stPeakData;
 
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 T_tempbuf3[i*36 + j] = 0;
 }
 }
 printf("\n\nCal Search Peak test start\n");
 
 
 T_tempbuf3[2*36 + 7] = -400;
 T_tempbuf3[2*36 + 8] = 100;
 T_tempbuf3[2*36 + 9] = 100;
 
 T_tempbuf3[3*36 + 7] = -250;
 T_tempbuf3[3*36 + 8] = 800;
 T_tempbuf3[3*36 + 9] = -200;
 
 T_tempbuf3[4*36 + 7] = -200;
 T_tempbuf3[4*36 + 8] = -200;
 T_tempbuf3[4*36 + 9] = 100;
 
 T_tempbuf3[8*36 + 8] = -1200;
 T_tempbuf3[5*36 + 9] = 8100;
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 printf("%04d ",T_tempbuf3[i*36 + j]);
 }
 printf("\n");
 }
 
 
 pNegPeakBuf = (UINT16 *)((UINT16)(ausNegPeaks+1)& 0xFFFE);
 
 
 stMcPDP.usDiffAddr = (UINT16)(g_stFrmData.ScDiff);
 stMcPDP.usNegOutAddr = (UINT16)pNegPeakBuf;
 stMcPDP.usCalOutAddr = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 
 stMcPDP.ucTxLen = 18;
 stMcPDP.ucRxLen = 36;
 stMcPDP.usPosThd     = 200;
 stMcPDP.usNegThd     = -200;
 stMcPDP.usAreaThd    = 50;
 stMcPDP.usNegAreaThd = -50;
 
 stMcPDP.ucMaxPeakNum = (10*3 ) - 1; 
 stMcPDP.ucSearchMod  = 0; 
 
 
 DrvCal_McPeak(&stMcPDP, &stMcPI);
 
 
 g_stPeakData.ucMcPosPeakNum = stMcPI.ucMcPosPeakNum;
 g_stPeakData.ucMcNegPeakNum = stMcPI.ucMcNegPeakNum;
 g_stPeakData.ucMcPosAreaChNum = stMcPI.ucMcPosAreaChNum;
 g_stPeakData.ucMcNegAreaChNum = stMcPI.ucMcNegAreaChNum;
 
 
 for (i = 0; i < g_stPeakData.ucMcPosPeakNum; i++)
 {
 ucPeakValidGroup = i >> 3;
 ucPeakValidPos = 1 << (i & 0x7);
 g_stPeakData.aucMcPeakValid[ucPeakValidGroup] |= ucPeakValidPos;
 
 g_stPeakData.aucMcPosPeak[i][0] = T_tempOut[i] >> 8;   
 g_stPeakData.aucMcPosPeak[i][1] = T_tempOut[i] %256;   
 }
 
 for (i = 0; i < g_stPeakData.ucMcNegPeakNum; i++)
 {
 g_stPeakData.aucMcNegPeak[i][0] = pNegPeakBuf[i] >> 8;    
 g_stPeakData.aucMcNegPeak[i][1] = pNegPeakBuf[i] %256;    
 }
 
 if (g_stPeakData.ucMcPosPeakNum > 0)
 {
 printf("\npeak pos:%x--%x",2,g_stPeakData.ucMcPosPeakNum);
 printf("\npeak neg:%x--%x",2,g_stPeakData.ucMcNegPeakNum);
 printf("\nArea pos:%x--%x",2,g_stPeakData.ucMcPosAreaChNum);
 printf("\nArea Neg:%x--%x",2,g_stPeakData.ucMcNegAreaChNum);
 
 for (i = 0; i < g_stPeakData.ucMcPosPeakNum; i++)
 {
 printf("\npos%x:%x-%x",i,g_stPeakData.aucMcPosPeak[i][0],g_stPeakData.aucMcPosPeak[i][1]);
 }
 
 for (i = 0; i < g_stPeakData.ucMcNegPeakNum; i++)
 {
 printf("\nNeg%x:%x-%x",i,g_stPeakData.aucMcNegPeak[i][0],g_stPeakData.aucMcNegPeak[i][1]);
 }
 }
 
 if((g_stPeakData.ucMcPosPeakNum != 2)||(g_stPeakData.ucMcNegPeakNum != 4)||(g_stPeakData.ucMcPosAreaChNum != 5)||(g_stPeakData.ucMcNegAreaChNum != 6))
 {
 printf("\n Search Peak ERROR");
 {DelayMs(100);while(1);};
 }
 }
 
#line 3152 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 3154 "..\..\src\source\task\Test_CAL.c" 
 
 
#line 3156 "..\..\src\source\task\Test_CAL.c" 






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 3266 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 






 
 void Test_CAL_AVG_TX(void)
 {
 UINT8 usAvgMode;
 UINT8 i,j;
 UINT8 flag;
 SINT32 slSumDiff = 0;
 SINT16 ssAvgBuf[18];
 
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nCAL ORG AVG Tx Test");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand();
 }          
 }
 
 for(i = 0;i<18;i++)
 {
 *(T_tempbuf2 + i) = (UINT16)rand(); 
 *(T_tempbuf2 + 18 + i) = ((SINT16)rand()>>1)|0x8000; 
 }
 
 
 CalParam.usSrc1Addr    = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr    = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);    
 CalParam.usDstAddr     = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen       = 18;
 CalParam.ucRxLen       = 36;  
 CalParam.usCalCmd      = (0x00<<4);
 CalParam.ucCfg         = 0;
 CalParam.ucDataType    = 0;
 CalParam.ucLineCfg     = 0;
 
 usAvgMode = 0; 
 
 DrvCal_MatrixAvg(&CalParam,usAvgMode);
 
 for (i=0; i<18; i++)
 {
 slSumDiff = 0; 
 for (j=0; j<36; j++)
 {
 if (*(T_tempbuf1 + i*36 + j) > *(T_tempbuf2 + i))
 {
 slSumDiff += *(T_tempbuf2 + i);
 }
 else if (*(T_tempbuf1 + i*36 + j) < *(T_tempbuf2 + 18 + i))
 {
 slSumDiff += *(T_tempbuf2 + 18 + i);
 }
 else
 {
 slSumDiff += *(T_tempbuf1 + i*36 + j);
 }   
 }
 
 
 ssAvgBuf[i] = (slSumDiff/36);   
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 if (*(T_tempOut + i) != ssAvgBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ORG AVG Tx is ERROR!");
 
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 for(i = 0;i<18;i++)
 {
 printf("\n%04d ",*(T_tempbuf2 + i));
 printf("%04d ",*(T_tempbuf2 + 18 + i));
 
 }  
 
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ORG AVG Tx is OK!");
 }
 
 
 for(i = 0;i<18;i++) 
 {
 *(T_tempbuf2 + 18 + i) = (((T_tempbuf2[i]-1000)<0)?(0):(((T_tempbuf2[i]-1000)<((UINT8)rand()))?(T_tempbuf2[i]-1000):((UINT8)rand())));
 }
 
 
 printf("\n\rCAL ABS AVG Tx Test");
 CalParam.usSrc1Addr    = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr    = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);    
 CalParam.usDstAddr     = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen       = 18;
 CalParam.ucRxLen       = 36;  
 CalParam.usCalCmd      = (0x00<<4);
 CalParam.ucCfg         = 0;
 CalParam.ucDataType    = 1;
 CalParam.ucLineCfg     = 0;
 usAvgMode = 0; 
 
 DrvCal_MatrixAvg(&CalParam,usAvgMode);
 for (i=0; i<18; i++)
 {
 slSumDiff = 0; 
 for (j=0; j<36; j++)
 {
 if (abs(*(T_tempbuf1 + i*36 + j)) > *(T_tempbuf2 + i))
 {
 slSumDiff += *(T_tempbuf2 + i);
 }
 else if (abs(*(T_tempbuf1 + i*36 + j)) < *(T_tempbuf2 + 18 + i))
 {
 slSumDiff += *(T_tempbuf2 + 18 + i);
 }
 else
 {
 slSumDiff += abs(*(T_tempbuf1 + i*36 + j));
 }
 
 }
 ssAvgBuf[i] = slSumDiff/36;   
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 if (*(T_tempOut + i) != ssAvgBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ABS AVG Tx is ERROR!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 for(i = 0;i<18;i++)
 {
 printf("\n%04d ",*(T_tempbuf2 + i));
 printf("%04d ",*(T_tempbuf2 + 18 + i));
 
 }  
 
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ABS AVG Tx is OK!");
 }
 
 }
 
#line 3471 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 3473 "..\..\src\source\task\Test_CAL.c" 
 
 
 






 
 void Test_CAL_AVG_RX(void)
 {
 UINT8 usAvgMode;
 UINT8 i,j;
 UINT8 flag;
 SINT32 slSumDiff = 0;
 SINT16 ssAvgBuf[36];
 
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nCAL ORG AVG Rx Test");
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand();
 
 }
 
 }
 
 for(i = 0;i<36;i++)
 {
 *(T_tempbuf2 + i) = (UINT16)rand();                
 *(T_tempbuf2 + 36 + i) = ((SINT16)rand()>>1)|0x8000; 
 }
 
 
 CalParam.usSrc1Addr    = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr    = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);    
 CalParam.usDstAddr     = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen       = 18;
 CalParam.ucRxLen       = 36;  
 CalParam.usCalCmd      = (0x00<<4);
 CalParam.ucCfg         = 0; 
 CalParam.ucDataType    = 0;
 CalParam.ucLineCfg     = 1;
 
 usAvgMode = 0; 
 
 DrvCal_MatrixAvg(&CalParam,usAvgMode);
 
 for (i=0; i<36; i++)
 {
 slSumDiff = 0; 
 for (j=0; j<18; j++)
 {
 if (*(T_tempbuf1 + j*36 + i) > *(T_tempbuf2 + i))
 {
 slSumDiff += *(T_tempbuf2 + i);
 }
 else if (*(T_tempbuf1 + j*36 + i) < *(T_tempbuf2 + 36 + i))
 {
 slSumDiff += *(T_tempbuf2 + 36 + i);
 }
 else
 {
 slSumDiff += *(T_tempbuf1 + j*36 + i);
 }   
 }
 
 
 ssAvgBuf[i] = (slSumDiff/18);   
 }
 
 
 g_ucCalFlag = 0;
 for (i = 0; i < 36; i++)
 {
 if (*(T_tempOut + i) != ssAvgBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ORG AVG Rx is ERROR!");
 
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 for(i = 0;i<36;i++)
 {
 printf("\n%04d ",*(T_tempbuf2 + i));
 printf("%04d ",*(T_tempbuf2 + 36 + i));
 
 }  
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ORG AVG Rx is OK!");
 }
 
 
 for(i = 0;i<36;i++) 
 {
 *(T_tempbuf2 + 36 + i) = (((T_tempbuf2[i]-1000)<0)?(0):(((T_tempbuf2[i]-1000)<((UINT8)rand()))?(T_tempbuf2[i]-1000):((UINT8)rand())));
 }
 
 
 printf("\n\rCAL ABS AVG Rx Test");
 CalParam.usSrc1Addr    = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr    = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);    
 CalParam.usDstAddr     = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen       = 18;
 CalParam.ucRxLen       = 36;  
 CalParam.usCalCmd      = (0x00<<4);
 CalParam.ucCfg         = 0;
 CalParam.ucDataType    = 1;
 CalParam.ucLineCfg     = 1;
 usAvgMode = 0; 
 
 DrvCal_MatrixAvg(&CalParam,usAvgMode);
 for (i=0; i<36; i++)
 {
 slSumDiff = 0; 
 for (j=0; j<18; j++)
 {
 if (abs(*(T_tempbuf1 + j*36 + i)) > *(T_tempbuf2 + i))
 {
 slSumDiff += *(T_tempbuf2 + i);
 }
 else if (abs(*(T_tempbuf1 + j*36 + i)) < *(T_tempbuf2 + 36 + i))
 {
 slSumDiff += *(T_tempbuf2 + 36 + i);
 }
 else
 {
 slSumDiff += abs(*(T_tempbuf1 + j*36 + i));
 }
 
 }
 ssAvgBuf[i] = slSumDiff/18;   
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 36; i++)
 {
 if (*(T_tempOut + i) != ssAvgBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 for(i = 0;i<36;i++)
 {
 printf("\n%04d ",*(T_tempbuf2 + i));
 printf("%04d ",*(T_tempbuf2 + 36 + i));
 
 }        
 printf("\n\rTest CAL ABS AVG Rx is ERROR!");
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ABS AVG Rx is OK!");
 }
 
 }
 
#line 3678 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 3680 "..\..\src\source\task\Test_CAL.c" 
 
 
#line 3682 "..\..\src\source\task\Test_CAL.c" 
 






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
 
 
#line 3843 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 void Test_CAL_AVG2_TX(void)
 {
 UINT8 usAvgMode;
 UINT8 i,j;
 UINT8 flag;
 UINT8 removalData;
 SINT32 slSumDiff = 0;
 SINT16 ssAvgBuf[18];
 
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nCAL ORG AVG2 Tx Test");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand();
 }          
 }
 
 for(i = 0;i<18;i++)
 {
 *(T_tempbuf2 + i) = (UINT16)rand(); 
 *(T_tempbuf2 + 18 + i) = ((SINT16)rand())|0x8000; 
 }
 
 CalParam.usSrc1Addr    = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr    = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);    
 CalParam.usDstAddr     = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen       = 18;
 CalParam.ucRxLen       = 36;  
 CalParam.usCalCmd      = (0x00<<4);
 CalParam.ucCfg         = 0;
 CalParam.ucDataType    = 0;
 CalParam.ucLineCfg     = 0;
 usAvgMode = 1; 
 
 DrvCal_MatrixAvg(&CalParam,usAvgMode);
 
 for (i=0; i<18; i++)
 {
 slSumDiff = 0; 
 removalData = 0;
 for (j=0; j<36; j++)
 {
 if (*(T_tempbuf1 + i*36 + j) > *(T_tempbuf2 + i))
 {
 removalData++;
 continue;
 }
 else if (*(T_tempbuf1 + i*36 + j) < *(T_tempbuf2 + 18 + i))
 {
 removalData++;
 continue;
 }
 else
 {
 slSumDiff += *(T_tempbuf1 + i*36 + j);
 }
 }
 if(removalData == 36)
 ssAvgBuf[i] = 0x7fff;
 else
 ssAvgBuf[i] = (slSumDiff/(36-removalData));   
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 if (*(T_tempOut + i) != ssAvgBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ORG AVG2 Tx is ERROR!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 for(i = 0;i<18;i++)
 {
 printf("\n%04d ",*(T_tempbuf2 + i));
 printf("%04d ",*(T_tempbuf2 + 18 + i));
 
 }  
 
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ORG AVG2 Tx is OK!");
 }
 
 for(i = 0;i<18;i++) 
 {
 *(T_tempbuf2 + 18 + i) = (((T_tempbuf2[i]-1000)<0)?(0):(((T_tempbuf2[i]-1000)<((UINT8)rand()))?(T_tempbuf2[i]-1000):((UINT8)rand())));
 }
 
 
 printf("\n\rCAL ABS AVG2 Tx Test");
 CalParam.usSrc1Addr    = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr    = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2); 
 CalParam.usDstAddr     = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen       = 18;
 CalParam.ucRxLen       = 36; 
 CalParam.usCalCmd      = (0x00<<4);
 CalParam.ucCfg         = 0;
 CalParam.ucDataType    = 1;
 CalParam.ucLineCfg     = 0;
 
 usAvgMode = 1; 
 DrvCal_MatrixAvg(&CalParam,usAvgMode);
 for (i=0; i<18; i++)
 {
 slSumDiff = 0;
 removalData = 0;
 for (j=0; j<36; j++)
 {
 if (abs(*(T_tempbuf1 + i*36 + j)) > *(T_tempbuf2 + i))
 {
 removalData++;
 continue;
 }
 else if (abs(*(T_tempbuf1 + i*36 + j)) < *(T_tempbuf2 + 18 + i))
 {
 removalData++;
 continue;
 }
 else
 {
 slSumDiff += abs(*(T_tempbuf1 + i*36 + j));
 }
 }
 if(removalData == 36)
 ssAvgBuf[i] = 0x7fff;
 else
 ssAvgBuf[i] = (slSumDiff/(36-removalData));   
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 if (*(T_tempOut + i) != ssAvgBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ABS AVG2 Tx is ERROR!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 for(i = 0;i<18;i++)
 {
 printf("\n%04d ",*(T_tempbuf2 + i));
 printf("%04d ",*(T_tempbuf2 + 18 + i));
 
 }  
 
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ABS AVG2 Tx is OK!");
 }
 }
 
#line 4051 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 4053 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 void Test_CAL_AVG2_RX(void)
 {
 UINT8 usAvgMode;
 UINT8 i,j;
 UINT8 flag;
 UINT8 removalData;
 SINT32 slSumDiff = 0;
 SINT16 ssAvgBuf[36];
 
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nCAL ORG AVG2 Rx Test");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand();
 }          
 }
 
 for(i = 0;i<36;i++)
 {
 *(T_tempbuf2 + i) = (UINT16)rand(); 
 *(T_tempbuf2 + 36 + i) = ((SINT16)rand())|0x8000; 
 }    
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);    
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36; 
 CalParam.usCalCmd   = (0x00<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 0;
 CalParam.ucLineCfg  = 1;
 
 usAvgMode = 1; 
 
 DrvCal_MatrixAvg(&CalParam,usAvgMode);
 for (i=0; i<36; i++)
 {
 slSumDiff = 0;
 removalData = 0;
 for (j=0; j<18; j++)
 {
 if (*(T_tempbuf1 + j*36 + i) > *(T_tempbuf2 + i))
 {
 removalData++;
 continue;
 }
 else if (*(T_tempbuf1 + j*36 + i) < *(T_tempbuf2 + 36 + i))
 {
 removalData++;
 continue;
 }
 else
 {
 slSumDiff += *(T_tempbuf1 + j*36 + i);
 }
 }
 if(removalData < 18)
 ssAvgBuf[i] = (slSumDiff/(18-removalData));   
 else
 ssAvgBuf[i]= 0x7fff;           
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 36; i++)
 {
 if (*(T_tempOut + i) != ssAvgBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ORG AVG2 Rx is ERROR!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 for(i = 0;i<36;i++)
 {
 printf("\n%04d ",*(T_tempbuf2 + i));
 printf("%04d ",*(T_tempbuf2 + 36 + i));
 
 }  
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ORG AVG2 Rx is OK!");
 }
 
 for(i = 0;i<36;i++) 
 {
 *(T_tempbuf2 + 36 + i) = (((T_tempbuf2[i]-1000)<0)?(0):(((T_tempbuf2[i]-1000)<((UINT8)rand()))?(T_tempbuf2[i]-1000):((UINT8)rand())));
 }
 
 
 
 printf("\n\rCAL ABS AVG2 Rx Test");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);   
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;  
 CalParam.usCalCmd   = (0x00<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 1;
 CalParam.ucLineCfg  = 1;
 
 usAvgMode = 1; 
 
 DrvCal_MatrixAvg(&CalParam,usAvgMode);
 for (i=0; i<36; i++)
 {
 slSumDiff = 0; 
 removalData = 0;
 for (j=0; j<18; j++)
 {
 if (abs(*(T_tempbuf1 + j*36 + i)) > *(T_tempbuf2 + i))
 {
 removalData++;
 continue;
 }
 else if (abs(*(T_tempbuf1 + j*36 + i)) < *(T_tempbuf2 + 36 + i))
 {
 removalData++;
 continue;
 }
 else
 {
 slSumDiff += abs(*(T_tempbuf1 + j*36 + i));
 }
 }          
 if(removalData < 18)
 {
 ssAvgBuf[i] = (SINT16)(slSumDiff/(18-removalData));  
 }
 else
 {
 ssAvgBuf[i]= 0x7fff;
 }
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 36; i++)
 {
 if (*(T_tempOut + i) != ssAvgBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,soft:%04x",i,*(T_tempOut + i),ssAvgBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ABS AVG2 Rx is ERROR!");
 
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 for(i = 0;i<36;i++)
 {
 printf("\n%04d ",*(T_tempbuf2 + i));
 printf("%04d ",*(T_tempbuf2 + 36 + i));
 
 }          
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ABS AVG2 Rx is OK!");
 }
 }
 
#line 4265 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 4267 "..\..\src\source\task\Test_CAL.c" 
 
 
#line 4269 "..\..\src\source\task\Test_CAL.c" 






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 4486 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 






 
 void Test_CAL_MIN_TX(void)
 {
 UINT8 i,j;
 UINT8 flag;
 SINT16 slTemp;
 SINT16 ssMinBuf[18];
 
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nCAL ORG MIN Tx Test");
 
 printf("\n mem");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT8)rand();
 }          
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;  
 CalParam.usCalCmd   = (0x01<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 0;
 CalParam.ucLineCfg  = 0;
 
 DrvCal_MatrixMaxMin(&CalParam);
 
 for (i=0; i<18; i++)
 {
 ssMinBuf[i] = *(T_tempbuf1 + i*36 + 0); 
 for (j=0; j<36; j++)
 {
 if (*(T_tempbuf1 + i*36 + j) < ssMinBuf[i])
 {
 ssMinBuf[i] = *(T_tempbuf1 + i*36 + j);
 }
 }          
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 if (*(T_tempOut + i) != ssMinBuf[i])
 {
 printf("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ORG Min Tx is Error!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ORG Min Tx is OK!");
 }
 
 printf("\n\rCAL ABS MIN Tx Test");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;   
 CalParam.usCalCmd   = (0x01<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 1;
 CalParam.ucLineCfg  = 0;
 
 DrvCal_MatrixMaxMin(&CalParam);
 
 for (i=0; i<18; i++)
 {
 slTemp = abs(*(T_tempbuf1 + i*36 + 0)); 
 for (j=0; j<36; j++)
 {
 if (abs(*(T_tempbuf1 + i*36 + j)) < slTemp)
 {
 slTemp = abs(*(T_tempbuf1 + i*36 + j));
 }
 }
 if (slTemp > 0x7FFF)
 {
 ssMinBuf[i] = 0x7FFF;
 }
 else
 {
 ssMinBuf[i] = slTemp;
 }
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 if (*(T_tempOut + i) != ssMinBuf[i])
 {
 printf("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMinBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ABS Min Tx is Error!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ABS Min Tx is OK!");
 }
 
 printf("\naram");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(g_pAfeAram + i*36 + j) = (SINT8)rand();
 }          
 }
 
#line 4649 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 4777 "..\..\src\source\task\Test_CAL.c" 
 
 }
 
#line 4780 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 4782 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 void Test_CAL_MIN_RX(void)
 {
 UINT8 i,j;
 UINT8 flag;
 SINT32 slTemp;
 SINT16 ssMinBuf[36];
 
 ST_CalMcMatrixParam CalParam;
 
 
 printf("\n\nCAL ORG MIN Rx Test");
 
 printf("\nmem");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT8)rand();
 }          
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36; 
 CalParam.usCalCmd   = (0x01<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 0;
 CalParam.ucLineCfg  = 1;
 
 DrvCal_MatrixMaxMin(&CalParam);
 
 for (i=0; i<36; i++)
 {
 ssMinBuf[i] = *(T_tempbuf1 + i); 
 for (j=0; j<18; j++)
 {
 if (*(T_tempbuf1 + j*36 + i) < ssMinBuf[i])
 {
 ssMinBuf[i] = *(T_tempbuf1 + j*36 + i);
 }
 }          
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 36; i++)
 {
 if (*(T_tempOut + i) != ssMinBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ORG Min Rx is Error!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ORG Min Rx is OK!");
 }
 
 printf("\n\rCAL ABS MIN Rx Test");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36; 
 CalParam.usCalCmd   = (0x01<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 1;
 CalParam.ucLineCfg  = 1;
 
 DrvCal_MatrixMaxMin(&CalParam);
 
 for (i=0; i<36; i++)
 {
 slTemp = abs(*(T_tempbuf1 + i)); 
 for (j=0; j<18; j++)
 {
 if (abs(*(T_tempbuf1 + j*36 + i)) < slTemp)
 {
 slTemp = abs(*(T_tempbuf1 + j*36 + i));
 }
 }
 if (slTemp > 0x7FFF)
 {
 ssMinBuf[i] = 0x7FFF;
 }
 else
 {
 ssMinBuf[i] = slTemp;
 }
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 36; i++)
 {
 if (*(T_tempOut + i) != ssMinBuf[i])
 {
 printf("\n\r%02dERROR->Cal:%04x,Soft:%04x",i,*(T_tempOut + i),ssMinBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ABS Min Rx is Error!");
 
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }        
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ABS Min Rx is OK!");
 }
 
 
#line 4936 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 5068 "..\..\src\source\task\Test_CAL.c" 
 }
 
#line 5070 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 5072 "..\..\src\source\task\Test_CAL.c" 
 
 
 






 
 void Test_CAL_MAX_TX(void)
 {
 UINT8 i,j;
 UINT8 flag;
 SINT32 slTemp;
 SINT16 ssMaxBuf[18];
 
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nCAL ORG Max Tx Test");
 
 printf("\n mem");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT8)rand();
 }          
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36; 
 CalParam.usCalCmd   = (0x02<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 0;
 CalParam.ucLineCfg  = 0;
 
 DrvCal_MatrixMaxMin(&CalParam);
 
 for (i=0; i<18; i++)
 {
 ssMaxBuf[i] = *(T_tempbuf1 + i*36 + 0); 
 for (j=0; j<36; j++)
 {
 if (*(T_tempbuf1 + i*36 + j) > ssMaxBuf[i])
 {
 ssMaxBuf[i] = *(T_tempbuf1 + i*36 + j);
 }
 }          
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 if (*(T_tempOut + i) != ssMaxBuf[i])
 {
 printf("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 
 }
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ORG Max Tx is Error!");
 
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }        
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ORG Max Tx is OK!");
 }
 
 printf("\n\rCAL ABS Max Tx Test");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36; 
 CalParam.usCalCmd   = (0x02<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 1;
 CalParam.ucLineCfg  = 0;
 
 DrvCal_MatrixMaxMin(&CalParam);
 
 for (i=0; i<18; i++)
 {        
 slTemp = abs(*(T_tempbuf1 + i*36 + 0)); 
 for (j=0; j<36; j++)
 {
 if (abs(*(T_tempbuf1 + i*36 + j)) > slTemp)
 {
 slTemp = abs(*(T_tempbuf1 + i*36 + j));
 }
 }
 if (slTemp > 0x7FFF)
 {
 ssMaxBuf[i] = 0x7FFF;
 }
 else
 {
 ssMaxBuf[i] = slTemp;
 }
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 if (*(T_tempOut + i) != ssMaxBuf[i])
 {
 printf("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ABS Max Tx is Error!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }        
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ABS Max Tx is OK!");
 }
 
 printf("\naram");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(g_pAfeAram + i*36 + j) = (SINT8)rand();
 }          
 }
 
 
#line 5235 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 5357 "..\..\src\source\task\Test_CAL.c" 
 }
 
#line 5359 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 5361 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 void Test_CAL_MAX_RX(void)
 {
 UINT8 i,j;
 UINT8 flag;
 SINT32 slTemp;
 SINT16 ssMaxBuf[36];
 
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nCAL ORG Max Rx Test");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT8)rand();
 }          
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;  
 CalParam.usCalCmd   = (0x02<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 0;
 CalParam.ucLineCfg  = 1;
 
 DrvCal_MatrixMaxMin(&CalParam);
 
 for (i=0; i<36; i++)
 {
 ssMaxBuf[i] = *(T_tempbuf1 + i); 
 for (j=0; j<18; j++)
 {
 if (*(T_tempbuf1 + j*36 + i) > ssMaxBuf[i])
 {
 ssMaxBuf[i] = *(T_tempbuf1 + j*36 + i);
 }
 }          
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 36; i++)
 {
 if (*(T_tempOut + i) != ssMaxBuf[i])
 {
 printf("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i),ssMaxBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ORG Max Rx is Error!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1+ i*36 + j));
 }
 printf("\n");  
 }        
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ORG Max Rx is OK!");
 }
 
 printf("\n\rCAL ABS Max Rx Test");
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36; 
 CalParam.usCalCmd   = (0x02<<4);
 CalParam.ucCfg      = 0;
 CalParam.ucDataType = 1;
 CalParam.ucLineCfg  = 1;
 
 DrvCal_MatrixMaxMin(&CalParam);
 
 for (i=0; i<36; i++)
 {
 slTemp = abs(*(T_tempbuf1 + i)); 
 for (j=0; j<18; j++)
 {
 if (abs(*(T_tempbuf1 + j*36 + i)) > slTemp)
 {
 slTemp = abs(*(T_tempbuf1 + j*36 + i));
 }
 }
 if (slTemp > 0x7FFF)
 {
 ssMaxBuf[i] = 0x7FFF;
 }
 else
 {
 ssMaxBuf[i] = slTemp;
 }
 }
 
 g_ucCalFlag = 0;
 for (i = 0; i < 36; i++)
 {
 if (*(T_tempOut + i) != ssMaxBuf[i])
 {
 printf("\n\rERROR->Cal:%04x,Soft%04x",*(T_tempOut + i),ssMaxBuf[i]);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 if (g_ucCalFlag)
 {
 printf("\n\rTest CAL ABS Max Rx is Error!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1 + i*36 + j));
 }
 printf("\n");  
 }        
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rTest CAL ABS Max Rx is OK!");
 }
 
 
#line 5510 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 5641 "..\..\src\source\task\Test_CAL.c" 
 }
 
#line 5643 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 5645 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 void Test_CAL_Count(void)
 {
 UINT8 i,j;
 UINT8 flag;
 SINT16 CountMax;
 SINT16 CountMin;
 UINT16 CalCountNum = 0;
 UINT16 SofCountNum = 0;
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nTest Cal Count");
 
 printf("\nmem");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand();
 }
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36; 
 CalParam.usCalCmd   = (0x04<<4);
 
 CountMax = 1000;
 CountMin = -1000;
 
 CalCountNum = DrvCal_MatrixCount(&CalParam,CountMin,CountMax);
 printf("\n\rCalCountNum:%d",CalCountNum);
 
 g_ucCalFlag = 0;
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 if((*(T_tempbuf1 + i*36 + j) >= CountMin)&&(*(T_tempbuf1 + i*36 + j) <= CountMax))
 {
 SofCountNum++;
 }
 }
 }
 printf("\n\rSofCountNum:%d",SofCountNum);
 
 if(CalCountNum != SofCountNum)
 {
 g_ucCalFlag = 1;
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rCal Test CAL Count is ERROR!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1+ i*36 + j));
 }
 printf("\n");  
 }        
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal Test CAL Count is OK!");
 }
 
#line 5724 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 5784 "..\..\src\source\task\Test_CAL.c" 
 }
 
#line 5786 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 5788 "..\..\src\source\task\Test_CAL.c" 
 
 






 
 void Test_CAL_SubConst(void)
 {
 UINT8 i,j;
 UINT8 flag;
 SINT32 temp;
 ST_CalMcMatrixParam CalParam;
 
 
 printf("\n\nmem");
 
 printf("\nTest CAL SubConst Tx");
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (UINT8)rand();
 }
 }
 
 for (i=0; i<18; i++)
 {
 *(T_tempbuf2 + i) = (UINT8)rand();        
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;  
 CalParam.usCalCmd   = (0x03<<4);
 CalParam.ucLineCfg  = 0;
 CalParam.ucCfg      = 1;
 DrvCal_MatrixSubConst(&CalParam);
 
 g_ucCalFlag = 0;
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 temp = (*(T_tempbuf1 + i*36 + j) - *(T_tempbuf2 + i));
 if (temp > 32767)
 {   
 temp = 32767;
 }
 else if (temp < -32768)
 {
 temp = -32768;
 }
 if (*(T_tempOut + i*36 + j) != (UINT16)temp)
 {
 printf("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*36 + j),(SINT16)temp);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rCal Test SubConst Tx is ERROR!");
 
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1+ i*36 + j));
 }
 printf("\n");  
 }
 printf("\n"); 
 for (i=0; i<18; i++)
 {
 printf("%04x  ", *(T_tempbuf2 + i));     
 }        
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal Test SubConst Tx is OK!");
 }
 
 printf("\n\rTest CAL SubConst Rx");
 for (i=0; i<36; i++)
 {
 *(T_tempbuf2 + i) = (SINT8)rand();        
 }
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;  
 CalParam.usCalCmd   = (0x03<<4);
 CalParam.ucLineCfg  = 1;
 CalParam.ucCfg      = 0;
 
 DrvCal_MatrixSubConst(&CalParam);
 
 g_ucCalFlag = 0;
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 temp = (*(T_tempbuf1 + i*36 + j) - *(T_tempbuf2 + j));
 if (temp > 32767)
 {   
 temp = 32767;
 }
 else if (temp < -32768)
 {
 temp = -32768;
 }
 if (*(T_tempOut + i*36 + j) != (SINT16)temp)
 {
 printf("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*36 + j),(SINT16)temp);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rCal Test SubConst Rx is ERROR!");
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1+ i*36 + j));
 }
 printf("\n");  
 }
 printf("\n"); 
 for (i=0; i<36; i++)
 {
 printf("%04x  ", *(T_tempbuf2 + i));     
 }
 
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal Test SubConst Rx is OK!");
 }
 
 
#line 5953 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 6102 "..\..\src\source\task\Test_CAL.c" 
 }
 
#line 6104 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 6106 "..\..\src\source\task\Test_CAL.c" 
 
 








 
 void Test_CAL_CMP(void)
 {
 UINT8 i,j;
 UINT8 flag;
 SINT16 temp;
 ST_CalMcMatrixParam CalParam;
 
 printf("\n\nTest CAL CMP");
 printf("\n mem-mem");
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(T_tempbuf1 + i*36 + j) = (SINT16)rand()>>1;
 *(T_tempbuf2 + i*36 + j) = (SINT16)rand()>>1;            
 }
 }
 
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;  
 CalParam.usCalCmd   = (0x07<<4);
 CalParam.ucDataType = 1; 
 CalParam.ucCfg = 0; 
 
 DrvCal_MatrixCMP(&CalParam);
 
 g_ucCalFlag = 0;
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
#line 6152 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
#line 6163 "..\..\src\source\task\Test_CAL.c" 
 
 if((*(T_tempbuf1 + i*36 + j)) < (*(T_tempbuf2 + i*36 + j)))
 {
 temp = (*(T_tempbuf1 + i*36 + j));
 }
 else
 {
 temp = (*(T_tempbuf2 + i*36 + j));
 }
 
 
 
 if (*(T_tempOut + i*36 + j) != temp)
 {
 printf("\n\rERROR->Cal:%04x,Soft:%04x",*(T_tempOut + i*36 + j),temp);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rCal Test CMP is ERROR!");
 
 
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1+ i*36 + j));
 }
 printf("\n");  
 }
 printf("\n"); 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf2+ i*36 + j));
 }
 printf("\n");  
 }     
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal Test CMP is OK!");
 }
 
 printf("\nAram-mem");
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 *(g_pAfeAram + i*36 + j) = (UINT16)rand()>>1;
 *(T_tempbuf2 + i*36 + j) = (UINT16)rand()>>1;            
 }
 }
 
#line 6230 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 6313 "..\..\src\source\task\Test_CAL.c" 
 }
 
#line 6315 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 6317 "..\..\src\source\task\Test_CAL.c" 
 
 









 
 BOOLEAN Test_CAL_MaxtixMul_PtoP3()
 {
 UINT8 i,j;
 UINT8 ucShift;
 SINT32 tmp;
 BOOLEAN flag;
 ST_CalMcMatrixParam near CalParam;
 static UINT8 counter = 0;
 
 printf("\n\nTest: Matrix MUL3");
 printf("\nmem-mem");
 
 for (i=0; i<18; i++)
 {
 *(T_tempbuf1 + i) = (SINT8)rand()>>1;
 }
 
 for(j = 0; j < 36; j++)
 {
 *(T_tempbuf2 +j) = (SINT8)rand()>>1;    
 }
 
 for(i = 0; i<18;i++)
 {
 *(g_pAfeAram + i) = (SINT8)rand()>>1;
 }       
 
 if(counter == 16)
 counter = 0;
 
 ucShift = counter;
 counter ++;  
 
 
 
 
 {
 printf("\nshift:%d",ucShift);
 CalParam.usSrc1Addr = (UINT16)(g_stFrmData.CalBaseAddr);
 CalParam.usSrc2Addr = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 CalParam.usDstAddr  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 CalParam.ucTxLen    = 18;
 CalParam.ucRxLen    = 36;
 CalParam.usCalCmd   = (0x08<<4);
 CalParam.ucShift    = ucShift;
 
 DrvCal_MatrixMul3(&CalParam);
 
 g_ucCalFlag = 0;
 
 for (i = 0; i < 18; i++)
 {
 for (j = 0; j < 36; j++)
 {
 tmp = (*(T_tempbuf1 + i)) * (*(T_tempbuf2 + j));
 tmp >>= ucShift;
 if (tmp > 32767)
 {
 tmp = 32767;
 }
 else if (tmp < -32768)
 {
 tmp = -32768;
 }
 if (*(T_tempOut + i*36 + j) != (SINT16)tmp )
 {
 printf("\n\rERROR->%04x,%04x,%04x,%04x",*(T_tempOut + i*36 + j),(SINT16)tmp,i,j);
 g_ucCalFlag = 1;
 }
 else
 {
 
 }
 }
 }
 
 if (g_ucCalFlag)
 {
 printf("\n\rCal MUL3 test %02d is Error!",ucShift);
 printf("\n");  
 for (i=0; i<18; i++)
 {
 for (j=0; j<1; j++)
 {
 
 printf("%04x  ",*(T_tempbuf1+ i*36 + j));
 }
 printf("\n");  
 }
 printf("\n"); 
 for (i=0; i<1; i++)
 {
 for (j=0; j<36; j++)
 {
 
 printf("%04x  ",*(T_tempbuf2+ i*36 + j));
 }
 printf("\n");  
 }             
 {DelayMs(100);while(1);};
 }
 else
 {
 printf("\n\rCal MUL3  test %02d is OK!",ucShift);
 }
 }
 
#line 6436 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 6510 "..\..\src\source\task\Test_CAL.c" 
 return g_ucCalFlag;
 }
 
#line 6513 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 6515 "..\..\src\source\task\Test_CAL.c" 
 
 







 
 void DrvClearIICState(void)
 {
 
 I2CBUF = 0;
 I2CRI  = 0;
 I2CTI  = 0;
 
 
 I2CSTP = 0;
 I2C_STOP_IF = 0;
 
 
 }
 
 UINT16 near g_ucRawdata[18][36] _at_ (0x6000);
 






 
 void CalAmovAramToMem(void)
 {
 UINT8 i,j;
 static BOOLEAN flag = 0;
 ST_CalMatrixAMov CalParam; 
 
 
 
#line 6556 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
#line 6564 "..\..\src\source\task\Test_CAL.c" 
 CalParam.usSrc1Addr = 0xA000;
 CalParam.usDstAddr  = (UINT16)g_ucRawdata; 
 CalParam.ucS1TxLen  = 18;
 CalParam.ucS1RxLen  = 36;
 
 
 DrvCal_MatrixAMov(&CalParam);
 
 
 
 for (i=0; i<18; i++)
 {
 for (j=0; j<36; j++)
 {
 if(g_ucRawdata[i][j]  != *(g_pAfeAram + i*36 + j))
 {
 flag = 1;
 
 }
 else
 {
 
 }
 }
 }
 
 if (flag)
 {
 printf("\nInt Amov Aram to Mem ERROR");
 }
 else
 {
 printf("\nInt Amov Aram to Mem OK");
 }
 
 if(g_ucCalFlag)
 {
 printf("\nCAL ERROR");
 }
 
 }
 
 






 
 void RtcInit(void)
 {
 
 CLK_WP = 1;
 EN_32K = 1;
 RTC_32K_EN = 1;
 
 
 RTCCKEN = 1;
 
 
 RTC_WP  = 1;
 RTC_CLR = 1;
 
 
 
 RTCIVH  = 0;
 RTCIVL  = 32;
 
 
 RTC_AUTO_MODE = 0;
 RTCCON1       = 1;
 
 RTC_INT_EN_CPU = 1;
 
 IT1   = 0;   
 EX1   = 1;       
 
 }
 






 
 void LcdIntInit(void)
 {
 DrvAsmInterEnable1(2); 
 ES = 1;
 }
 
 






 
 void I2cInit(void)
 {
 I2CCKEN = 1;
 
 I2CBUF = 0;
 I2CRI  = 0;
 I2CTI  = 0;
 
 
 I2CADDR = 0x70&0xFE;
 
 I2C_STOP_EI = 1;         
 I2C_STOP_IF = 0;
 
 ET2 = 1;                  
 I2C_STOP_EI = 1;          
 }
 
 
 
 








 
 void DrvIntPriority(void)
 {
 
 IPH0 = 0x00;
 IPL0 = 0x00;
 AIPH = 0x00;
 AIPL = 0x00;
 
 
 IPHX0 = 1;
 IPLX0 = 1;
 
 
 I2C_IPH = 1;
 I2C_IPL = 1;
 
 SPI0_IPH = 1;
 SPI0_IPL = 1;
 
 I2C_STOP_IPH = 1;
 I2C_STOP_IPL = 1;
 
 LCD_IPH = 1;
 LCD_IPL = 1;
 
 
 ASM_IPH = 1;
 ASM_IPL = 0;
 
 
 IPHX1 = 1;
 IPLX1 = 0;
 
 
 IPHT0 = 0;
 IPLT0 = 0;
 
 
 IPHT1 = 0;
 IPLT1 = 0;
 
 
 
 Uart_IPH = 1;
 Uart_IPL = 1;
 
 }
 
 
 
 
 
 
 
 
#line 6750 "..\..\src\source\task\Test_CAL.c" 
  
 
#line 6752 "..\..\src\source\task\Test_CAL.c" 
 
 
 








 
 void WDT_Init(void)
 {
 WDT_500K_EN = 1;     
 WDTSTARTEN = 1;      
 


 
 
 
#line 6774 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
#line 6779 "..\..\src\source\task\Test_CAL.c" 
 WDTREL = ((0x7FFC-(UINT32)(6000)*1000/768)&0x00FF) > 0x0080?(((0x7FFC-(UINT32)(6000)*1000/768)>>8)+1):((0x7FFC-(UINT32)(6000)*1000/768)>>8);
 
#line 6781 "..\..\src\source\task\Test_CAL.c" 
 
 
#line 6783 "..\..\src\source\task\Test_CAL.c" 
 WDTREL |= 0x80;
 
 
 
 
 WDT  = 1;            
 SWDT = 1;            
 
 WDT_INT_IF = 0;
 WDT_INT_EI = 1;
 
 }
 
 





 
 void WDT_Feed(void)
 {
 WDT  = 1;   
 SWDT = 1;   
 }
 
 






 
 void Test_CAL(void)
 {
 BOOLEAN flag = 1;
 
 UINT16 CALMask =   0; 
 UINT16 AmoveMask = 0; 
 UINT16 i;
 
 AFEACKEN = 1;
 ARAM_SEL = 1;
 
 T_tempbuf1 = (UINT16)(g_stFrmData.CalBaseAddr);
 T_tempbuf2 = ((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2);
 T_tempOut  = (((UINT16)(g_stFrmData.CalBaseAddr)+(18*36)*2)+(18*36)*2);
 
 T_tempbuf3 = (UINT16)(g_stFrmData.ScDiff);
 
 printf("\n\rStart CalTest!\n\r");
 printf("\n\rCal-A0:%08lx",T_tempbuf1);
 printf("\n\rCal-A1:%08lx",T_tempbuf2);
 printf("\n\rCal-A2:%08lx",T_tempOut);
 printf("\n\rCal-A3:%08lx",(UINT16)(g_stFrmData.ScDiff));
 printf("\n\rAram:%08lx",g_pAfeAram);
 
 DrvClearIICState();
 
 DrvIntPriority();
 IEN0 = 0;
 AIE = 0;
 
 
 CALMask |= ((UINT16)1<<(2)); 
 
 RtcInit();
 
 
 
#line 6854 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
#line 6858 "..\..\src\source\task\Test_CAL.c" 
 
 
 CALMask |= ((UINT16)1<<(5));   
 AmoveMask |= ((UINT16)1<<(5)); 
 CALMask |= ((UINT16)1<<(8));   
 AmoveMask |= ((UINT16)1<<(8)); 
 I2cInit();
 
 
 
 CALMask |= ((UINT16)1<<(9));
 
 Afe_120Hz_Run();
 
 
 
#line 6874 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 6914 "..\..\src\source\task\Test_CAL.c" 
 DrvCal_Init(18, 36, CALMask,AmoveMask);
 
 EA = 1; 
 
 
 P0BUF = 0;
 P1BUF = 0;
 
 while(1)
 {
 
 P1_4 = !P1_4;
 
 Test_CAL_MaxtixAdd();
 
 Test_CAL_MaxtixSub();
 
 Test_CAL_MaxtixAmp();
 
 Test_CAL_MaxtixDiv();
 
 Test_CAL_MaxtixMov();
 
 Test_CAL_MaxtixMov2();
 
 Test_CAL_MaxtixCom_1();
 
 Test_CAL_MaxtixCom_2();
 
 Test_CAL_MaxtixMul_PtoP1();
 
 Test_CAL_MaxtixMul_PtoP2();
 
 Test_CAL_LDS();
 
 Test_CAL_MDS();
 
 Test_CAL_CHK();
 
 Test_CAL_ID();
 
 Test_CAL_MAC_1();
 
 Test_CAL_MAC_2();
 
 Test_CAL_CRC();
 
 Test_CAL_XORSUM();
 
 Test_CAL_SearchPeak();
 
 
 
 
 Test_CAL_AVG_TX();
 
 Test_CAL_AVG_RX();
 
 Test_CAL_AVG2_TX();
 
 Test_CAL_AVG2_RX();
 
 
 Test_CAL_MIN_TX();
 
 Test_CAL_MIN_RX();
 
 Test_CAL_MAX_TX();
 
 Test_CAL_MAX_RX();
 
 Test_CAL_Count();
 
 Test_CAL_SubConst();
 
 Test_CAL_CMP();
 
 Test_CAL_MaxtixMul_PtoP3();
 
 } 
 
 AFEACKEN = 0;
 ARAM_SEL = 0;
 printf("\n\r\n\rCAL test End");
 
 while (1);
 }
 
 
 






 
 void Exint0_IRQHandler(void) interrupt 0
 { 
 
 
 
#line 7016 "..\..\src\source\task\Test_CAL.c" 
 
 
 
#line 7019 "..\..\src\source\task\Test_CAL.c" 
 
  
 
 }
 
 






 
 void Exint1_IRQHandler(void) interrupt 2
 {   
 
 P0_6 = 1;	
 while(RTC_START_STA == 0);
 
#line 7038 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
#line 7044 "..\..\src\source\task\Test_CAL.c" 
 RTC_WP  = 1;
 RTC_CLR = 1;
 
  
 
 
 
 RTCIVH = 0;
 RTCIVL = (UINT8)rand();
 P0_6 = 0;
 
 
 
 
 }
 






 
 void ISR_LcdRun_IRQHandler(void) interrupt  4
 {
 UINT16 usAsmIntEn0,usAsmIntEn1;
 UINT16 usAsmIntFlag0,usAsmIntFlag1;
 
 usAsmIntEn0   = pAsmRegs->usAsmIntEn0;
 usAsmIntEn1   = pAsmRegs->usAsmIntEn1;
 
 usAsmIntFlag0 = pAsmRegs->usAsmIntFlag0;
 usAsmIntFlag1 = pAsmRegs->usAsmIntFlag1;
 
 
 if (usAsmIntEn1&((UINT16)1<<(2)))
 {
 if (usAsmIntFlag1&((UINT16)1<<(2)))
 {
 
 if(pAsmRegs->usAsmScanCfg1&((UINT16)1<<(15))) 
 {
 pAsmRegs->usAsmScanCfg1&=~(1<<15);      
 printf("\nRun INTPHAS 1");
 }
 else
 {
 pAsmRegs->usAsmScanCfg1|=(1<<15);      
 printf("\nRun INTPHAS 2");
 }
 
 pAsmRegs->usAsmIntClr1 |=((UINT16)1<<(2));
 
 }
 }
 
 }
 






 
 void I2C_ISR(void) interrupt 5
 {
 UINT8 ch = 0;
 P0_2 = 1;
 P0_4 = 1;
 
 
 if (I2CRI)
 {
 
#line 7119 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
#line 7129 "..\..\src\source\task\Test_CAL.c" 
 I2CRI = 0;
 ch = I2CBUF;
 g_I2cCnt++; 
 
 }
 if (I2CTI)
 {
 
#line 7137 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
#line 7147 "..\..\src\source\task\Test_CAL.c" 
 I2CTI = 0;
 
 }	
 P0_4 = 0;
 P0_2 = 0;
 }
 






 
 void I2C_STOP_ISR(void) interrupt 8
 {
 P0_3 = 1;
 P0_5 = 1;
 
 
#line 7167 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
#line 7177 "..\..\src\source\task\Test_CAL.c" 
 I2CSTP = 0;
 P0_3 = 0;
 P0_5 =0;
 }
 






 
 void DrvScanCtrl_IRQHandler(void) interrupt 9
 {
 UINT16 usAsmIntEn0,usAsmIntEn1;
 UINT16 usAsmIntFlag0,usAsmIntFlag1;
 
 P1_1 = 1;
 usAsmIntEn0   = pAsmRegs->usAsmIntEn0;
 usAsmIntEn1   = pAsmRegs->usAsmIntEn1;
 
 usAsmIntFlag0 = pAsmRegs->usAsmIntFlag0;
 usAsmIntFlag1 = pAsmRegs->usAsmIntFlag1;
 
 
 
 if (usAsmIntEn0&((UINT16)1<<(8)))
 {
 if (usAsmIntFlag0&((UINT16)1<<(8)))
 {
 P1_3 = 1;
 
#line 7209 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
#line 7215 "..\..\src\source\task\Test_CAL.c" 
 pAsmRegs->usAsmIntClr0 |= ((UINT16)1<<(8));
 
 
 ARAM_SEL = 1;
 
 CalAmovAramToMem();
 DrvAsmAramAvail();  
 ARAM_SEL = 0;
 
  
 P1_3 = 0;
 }
 }
 
 
 
 
 if (usAsmIntEn0&((UINT16)1<<(5)))
 {
 if (usAsmIntFlag0&((UINT16)1<<(5)))
 {
 P1_2 = 1;
 
#line 7238 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
#line 7244 "..\..\src\source\task\Test_CAL.c" 
 pAsmRegs->usAsmIntClr0 |= ((UINT16)1<<(5));
  
 DrvAsmScanStart();  
 P1_2 = 0;
 }
 }
 P1_1 = 0;
 
 }
 
 
 






 
 void SPI0_IRQHandler(void) interrupt 11
 {
 UINT8 ch = 0;  
 
  
 
 if (SPI0RI)
 {
 
#line 7272 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
 
 
 
 
 
#line 7282 "..\..\src\source\task\Test_CAL.c" 
 SPI0RI_CLR = 1;           
 ch = SPI0BUF;  
 
 if(SPI0_START)
 {        
 SPI0_START_CLR = 1;  
 }
 
 
#line 7291 "..\..\src\source\task\Test_CAL.c" 
 
 
 
 
 
#line 7296 "..\..\src\source\task\Test_CAL.c" 
 
 }
 
 SPI0CON5 =0xff; 
 }
 
 
 
