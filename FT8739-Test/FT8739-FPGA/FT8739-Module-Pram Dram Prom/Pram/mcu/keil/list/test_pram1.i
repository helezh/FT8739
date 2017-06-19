
#line 1 "..\..\src\test_pram1.c" 














 
 


 
  
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
 
#line 20 "..\..\src\test_pram1.c" 
 


 
 


 
 


 
 
 


 
 
 






 
 void test_pram1(void)
 {
 UINT16 i = 0;
 UINT32 src_addr;
 UINT32 dest_addr;
 
 src_addr = (UINT32)0xFEE800 - 0xFEE800;
 dest_addr = (UINT32)0xFF2000 - 0xFEE800;
 
 P0_6 = 0;
 P0_7 = 0;
 
 for(i = 0; i < 0x300 ; i++)
 {
 (*((UINT8 far *)((UINT32)0xFEE800 + dest_addr + i))) = (*((UINT8 far *)((UINT32)0xFEE800 + src_addr + i)));
 }
 
 
 for(i = 0; i < ((UINT32)0xFF0000 - (UINT32)0xFEE800); i++)
 {
 (*((UINT8 far *)((UINT32)0xFEE800 + src_addr + i))) = 0x55;
 }
 
 for(i = 0; i < 0x300; i++)
 {
 if((*((UINT8 far *)((UINT32)0xFEE800 + src_addr + i))) != 0x55)
 {
 P0_0 = 0;
 P0_1 = 1;
 while(1);
 }
 else
 {
 P0_0 = ~ P0_0;
 }
 }
 
 
 
 for(i = 0; i < ((UINT32)0xFF0000 - (UINT32)0xFEE800); i++)
 {
 (*((UINT8 far *)((UINT32)0xFEE800 + src_addr + i))) = 0xAA;
 }
 
 for(i = 0; i < 0x300; i++)
 {
 if((*((UINT8 far *)((UINT32)0xFEE800 + src_addr + i))) != 0xAA)
 {
 P0_0 = 1;
 P0_1 = 0;
 while(1);
 }
 else
 {
 P0_0 = ~ P0_0;
 }        
 }
 
 
 for(i = 0; i < 0x300 ; i++)
 {
 (*((UINT8 far *)((UINT32)0xFEE800 + src_addr + i))) = (*((UINT8 far *)((UINT32)0xFEE800 + dest_addr + i)));
 }
 
 }
