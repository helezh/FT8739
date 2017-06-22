
#line 1 "..\..\src\main.c" 














 
 


 
  
#line 1 "..\..\src\global.h" 














 
 
 
 


 
  
#line 1 "C:\Program Files (x86)\Keil\C251\Inc\intrins.h" 






 
 
 #pragma SAVE
 #pragma PARM251
 
 
 #pragma FUNCTIONS(STATIC)
 
 
 
 extern void          _nop_     (void);
 extern bit           _testbit_ (bit);
 extern unsigned char _cror_    (unsigned char, unsigned char);
 extern unsigned int  _iror_    (unsigned int,  unsigned char);
 extern unsigned long _lror_    (unsigned long, unsigned char);
 extern unsigned char _crol_    (unsigned char, unsigned char);
 extern unsigned int  _irol_    (unsigned int,  unsigned char);
 extern unsigned long _lrol_    (unsigned long, unsigned char);
 extern unsigned char _chkfloat_  (float x)  reentrant;
 extern unsigned char _chkdouble_ (double x) reentrant;
 
 #pragma RESTORE
#line 22 "..\..\src\global.h" 
 
 


 
 sfr CGUCON4 = 0xCC;
 sfr P0BUF   = 0x80;
 sfr P0DIR   = 0xAC;
 sfr P0MOD   = 0xEB;
 sfr P0SEL   = 0xEC;
 sfr P1BUF   = 0x94;    
 sfr P1DIR   = 0xAD;    
 sfr P1MOD   = 0xED;    
 sfr P1SEL   = 0xEE;    
 
 
 sbit P0_0 = P0BUF^0;
 sbit P0_1 = P0BUF^1;
 sbit P0_2 = P0BUF^2;
 sbit P0_3 = P0BUF^3;
 sbit P0_4 = P0BUF^4;
 sbit P0_5 = P0BUF^5;
 sbit P0_6 = P0BUF^6;
 sbit P0_7 = P0BUF^7;
 
 sbit P1_0 = P1BUF^0;
 sbit P1_1 = P1BUF^1;
 sbit P1_2 = P1BUF^2;
 sbit P1_3 = P1BUF^3;
 sbit P1_4 = P1BUF^4;
 sbit P1_5 = P1BUF^5;
 sbit P1_6 = P1BUF^6;
 sbit P1_7 = P1BUF^7;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


 
 typedef unsigned char  UINT8;
 typedef unsigned short UINT16;
 typedef unsigned long  UINT32;
 


 
 


 
 void test_pram1(void);
 void test_pram2(void);
 
#line 20 "..\..\src\main.c" 
 


 
 


 
 


 
 UINT8 ecode g_aucVerfication[0x20+0x80] _at_  0xFEE900;
 


 
 






 
 
 void main(void)
 {
 
 CGUCON4 = 0x00;
 
 P0MOD   = 0x00;
 P0DIR   = 0xFF;
 P0SEL   = 0xFF;
 P0BUF   = 0x00;
 
 P1MOD   = 0x00;
 P1DIR   = 0xFF;
 P1SEL   = 0xFF;
 P1BUF   = 0xFF;
 
 while(1)
 {
 test_pram1();        
 test_pram2();
 }
 
 }
 
