/*******************************************************************************
* Copyright (C) 2017-2019, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Drv_XBUS.c
*
*    Author: tangsujun
*   Created: 2017-03-22
*
*  Abstract:
*
* Reference:
*
*   Version:CRC 0X020304 0305
*
*******************************************************************************/
/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <intrins.h>
#include "CfgGlobal.h"
#include "Drv_XBUS.h"
#include "FT8835_Reg.h"

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
#define WRITERREAD  1
#define READONLY    0
/* lcd wrap base addr */
#define LCD_WRAP_START_ADDR     0xBC00
//对lcd reg操作，小心操作
#define LCD_REG_BASE_ADDR      0x020000
#define Xbus_ADDR8(n)    (*((UINT8 far *)(LCD_REG_BASE_ADDR + n)))
#define Xbus_ADDR16(n)   (*((UINT16 far *)(LCD_REG_BASE_ADDR + n)))


/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
ST_LcdWrapRegisters *XRAM pLcdWrapRegs = (volatile ST_LcdWrapRegisters *)XBUS_REG_BASE_ADDR;
/*******************************************************************************
* 4.Static variables
*******************************************************************************/

/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/


/*******************************************************************************
*   Name: Drv_XbusInit
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
void Drv_XbusInit(void)
{
    XBUSCKEN = 1;//
    LCD_RELOAD_FLASH_WKEN =1;

}


/******************************************************************************
*
*   Name: DrvXbus_ReadLcd16
*  Brief: 读lcd数据 16位(双字节对齐)
*  Input:
* Output:
* Return:
*******************************************************************************/
UINT16 DrvXbus_ReadLcd16(UINT16 usaddr)
{
    volatile UINT8 Dummy;
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(1))) == 0);   //wait wr enable
    Dummy = Xbus_ADDR8(usaddr);     
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(0))) == 0);   //wait rdata redy
    //return (UINT16)((pLcdWrapRegs->rdata_lo_byte << 8) + (pLcdWrapRegs->rdata_ho_byte & 0x00ff)); //Big-endian
    return (UINT16)(pLcdWrapRegs->rdata_lo_byte);

}


/******************************************************************************
*
*   Name: DrvXbus_WriteLcd8
*  Brief:写lcd数据 8位
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvXbus_WriteLcd8(UINT16 usaddr,UINT8 usdata)
{
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(1))) == 0); //wait wr enable
    Xbus_ADDR8(usaddr) = usdata;
}

/******************************************************************************
*
*   Name: DrvXbus_WriteLcd16
*  Brief:写lcd数据 16位
*  Input:
* Output:
* Return:
*******************************************************************************/
/*void DrvXbus_WriteLcd16(UINT16 usaddr,UINT16 usdata)
{
    while(((pLcdWrapRegs->lcd_regfile_ctrl) & (BITn(1))) == 0); //wait wr enable
    Xbus_ADDR16(usaddr) = usdata;
}*/




/******************************************************************************
*
*   Name: DrvXbus_WriteLcd8
*  Brief:写lcd数据 8位
*  Input:
* Output:
* Return:
*******************************************************************************/
void DrvXbus_WriteInitCode(void)
{
    UINT16 XRAM ucData;
    ucData = DrvXbus_ReadLcd16(0x0A00);
    DBG_FLOW("\nLCD 0A00:%04x",ucData);

    DelayMs(100);
    DrvXbus_WriteLcd8(0x1100,0x00);      //sleep out

    DrvXbus_WriteLcd8(0x2900,0x00);     //display on 

    ucData = DrvXbus_ReadLcd16(0x0A00);
    DBG_FLOW("\nLCD 0A00:%04x",ucData);  //读到0x9c9c表明

    DrvXbus_WriteLcd8(0xff00,0x88);
    DrvXbus_WriteLcd8(0xff01,0x35);
    DrvXbus_WriteLcd8(0xff02,0x01);

    DrvXbus_WriteLcd8(0xff80,0x88);
    DrvXbus_WriteLcd8(0xff81,0x35);
    DrvXbus_WriteLcd8(0xff82,0x01);

    DrvXbus_WriteLcd8(0x1c00,0x02);
    DrvXbus_WriteLcd8(0xc080,0x01);
    DrvXbus_WriteLcd8(0xc081,0x40);
    DrvXbus_WriteLcd8(0xc0a0,0x01);
    DrvXbus_WriteLcd8(0xc0a1,0x40);

    DrvXbus_WriteLcd8(0xc1a4,0x00);
    DrvXbus_WriteLcd8(0xce96,0x80);
    DrvXbus_WriteLcd8(0xce97,0x10);
    DrvXbus_WriteLcd8(0xce98,0x02);
    DrvXbus_WriteLcd8(0xce99,0x00);
    DrvXbus_WriteLcd8(0xce9a,0x20);
    DrvXbus_WriteLcd8(0xce9b,0x02);    

    DrvXbus_WriteLcd8(0xb3a1,0x05);
    DrvXbus_WriteLcd8(0xb3a2,0xa0);
    DrvXbus_WriteLcd8(0xb3a3,0x0b);
    DrvXbus_WriteLcd8(0xb3a4,0x40);
    DrvXbus_WriteLcd8(0xb3a5,0x80);
    DrvXbus_WriteLcd8(0xb3a6,0xb2);
    DrvXbus_WriteLcd8(0xc0a3,0x10);        
    #if 1
    //============================================  
    // kyo TCON setting		 
    //============================================  
    DrvXbus_WriteLcd8(0xc080,0x00);       //reg_tcon_rtn_hi
    DrvXbus_WriteLcd8(0xc081,0x56);       //reg_tcon_rtn_lo
    DrvXbus_WriteLcd8(0xc084,0x00);       //reg_tcon_norm_vbp_hi
    DrvXbus_WriteLcd8(0xc085,0x10);       //reg_tcon_norm_vbp_lo
    DrvXbus_WriteLcd8(0xc0a3,0x10);       //reg_tcon_pwrseq_vfp_lo[7:0]
    DrvXbus_WriteLcd8(0xc0c1,0x80);       //[7:6]reg_tcon_pwron_mode, [4]reg_tcon_pwrof_2_en, [3:0]reg_tcon_f_powof_2
    DrvXbus_WriteLcd8(0xc180,0x33);       //[6:4]reg_osc_idle_freq,   [2:0]reg_osc_normal_freq  
    DrvXbus_WriteLcd8(0xc181,0x33);       //[6:4]reg_osc_pwrseq_freq, [2:0]reg_osc_video_freq
    DrvXbus_WriteLcd8(0xc190,0x44);       //[7:4]reg_oscdiv_pwrseq_num, [3:0]reg_oscdiv_num
    DrvXbus_WriteLcd8(0xc1a1,0x80);       //vs_video, hs_video, clk_video, bp_video
    DrvXbus_WriteLcd8(0xc1a3,0x03);       //reg_oscref_video_vs_shift_hi
    DrvXbus_WriteLcd8(0xc1a4,0x9b);       //reg_oscref_video_vs_shift_lo
    DrvXbus_WriteLcd8(0xc1a5,0x00);       //reg_oscref_video_hs_shift_hi
    DrvXbus_WriteLcd8(0xc1a6,0x00);       //reg_oscref_video_hs_shift_lo
    DrvXbus_WriteLcd8(0xc0a5,0x00);       //reg_tcon_mck_shift1_hi
    DrvXbus_WriteLcd8(0xc0a6,0x05);       //reg_tcon_mck_shift1_lo
    DrvXbus_WriteLcd8(0xc0a7,0x00);       //reg_tcon_mck_shift2_hi
    DrvXbus_WriteLcd8(0xc0a8,0x08);       //reg_tcon_mck_shift2_lo
    DrvXbus_WriteLcd8(0xc0a9,0x00);       //reg_tcon_mck_shift3_hi
    DrvXbus_WriteLcd8(0xc0aa,0x07);       //reg_tcon_mck_shift3_lo
    DrvXbus_WriteLcd8(0xc0e2,0x85);       //reg_tcon_datapath_dly_offset
    DrvXbus_WriteLcd8(0xc0a0,0x00);       //reg_tcon_pwrseq_rtn_hi
    DrvXbus_WriteLcd8(0xc0a1,0x20);       //reg_tcon_pwrseq_rtn_lo
    DrvXbus_WriteLcd8(0xc0c1,0xc0);       //[7:6]reg_tcon_pwron_mode, [4]reg_tcon_pwrof_2_en,[3:0]reg_tcon_f_powof_2
    //============================================
    // kyo TCON LPF setting
    //============================================
    DrvXbus_WriteLcd8(0xced0,0x85);       //[7]reg_tcon_dfr_video_en,[2]reg_tcon_lpf_mode, [1]reg_tcon_lpf, [0]reg_tcon_lpf_auto
    DrvXbus_WriteLcd8(0xced1,0x02);       //reg_tcon_dfr_num
    DrvXbus_WriteLcd8(0xced2,0x01);       //reg_tcon_lpfscan_num
    DrvXbus_WriteLcd8(0xced3,0x00);       //reg_tcon_lpf_rtn_hi
    DrvXbus_WriteLcd8(0xced4,0x50);       //reg_tcon_lpf_rtn_lo
    DrvXbus_WriteLcd8(0xced5,0x00);       //reg_tcon_lpf_vfp_hi
    DrvXbus_WriteLcd8(0xced6,0x10);       //reg_tcon_lpf_vfp_lo
    DrvXbus_WriteLcd8(0xced7,0x00);       //reg_tcon_lpf_vbp_hi
    DrvXbus_WriteLcd8(0xced8,0x10);       //reg_tcon_lpf_vbp_lo
    DrvXbus_WriteLcd8(0xced9,0x00);       //reg_tcon_lpf_shift
    DrvXbus_WriteLcd8(0xceda,0x06);       //reg_tcon_lpf_pcg_dri
    DrvXbus_WriteLcd8(0xcedb,0x05);       //reg_tcon_lpf_pcg_nop
    DrvXbus_WriteLcd8(0xcedc,0x04);       //reg_tcon_lpf_pcg_swt
    DrvXbus_WriteLcd8(0xcedd,0x15);       //reg_tcon_lpf_ckh_dri
    DrvXbus_WriteLcd8(0xcede,0x03);       //reg_tcon_lpf_ckh_nop
    DrvXbus_WriteLcd8(0xcedf,0x01);
    
    //reg_tcon_lpf_ckh_swt
    //============================================
    // kyo TP setting
    //============================================
    DrvXbus_WriteLcd8(0xce80,0x01);       //reg_tp_en
    DrvXbus_WriteLcd8(0xce81,0x01);       //reg_tp_line_num_of_unit_1st_hi
    DrvXbus_WriteLcd8(0xce82,0x20);       //reg_tp_line_num_of_unit_1st_lo
    DrvXbus_WriteLcd8(0xce83,0x01);       //reg_tp_line_num_of_unit_2nd_hi
    DrvXbus_WriteLcd8(0xce84,0x20);       //reg_tp_line_num_of_unit_2nd_lo
    DrvXbus_WriteLcd8(0xce85,0xFF);       //reg_tcon_tp_swt_rgn
    DrvXbus_WriteLcd8(0xce86,0x01);       //[7]reg_tcon_tp_1st_rgn_ena, [3:0]reg_tcon_tp_lnpb_1st_hi
    DrvXbus_WriteLcd8(0xce87,0x20);       //reg_tcon_tp_lnpb_1st_lo
    DrvXbus_WriteLcd8(0xce88,0x09);       //reg_tcon_tp_last_rgn
    DrvXbus_WriteLcd8(0xce89,0x01);       //reg_tcon_tp_lnpb_last_hi
    DrvXbus_WriteLcd8(0xce8a,0x20);       //reg_tcon_tp_lnpb_last_lo
    DrvXbus_WriteLcd8(0xce8b,0x00);       //reg_tcon_tp_break_rgn
    DrvXbus_WriteLcd8(0xce8c,0x00);       //[7]reg_tcon_tp_rgn_break_ena, [3:0]reg_tcon_tp_lnpb_break_hi
    DrvXbus_WriteLcd8(0xce8d,0x00);       //reg_tcon_tp_lnpb_break_lo
    DrvXbus_WriteLcd8(0xce90,0x00);       //reg_tp_term1_width_hi 
    DrvXbus_WriteLcd8(0xce91,0x76);       //reg_tp_term1_width_lo
    DrvXbus_WriteLcd8(0xce92,0x0F);       //reg_tp_term2_width_hi
    DrvXbus_WriteLcd8(0xce93,0x50);       //reg_tp_term2_width_lo
    DrvXbus_WriteLcd8(0xce94,0x00);       //reg_tp_term3_width_hi
    DrvXbus_WriteLcd8(0xce95,0x76);       //reg_tp_term3_width_lo
    DrvXbus_WriteLcd8(0xce96,0x00);       //reg_tcon_tp_vb_str_hi
    DrvXbus_WriteLcd8(0xce97,0x00);       //reg_tcon_tp_vb_str_lo
    DrvXbus_WriteLcd8(0xce98,0x02);       //reg_tcon_tp_term1a_vb_ln
    DrvXbus_WriteLcd8(0xce99,0x00);       //reg_tcon_tp_term1b_vb_ln_hi
    DrvXbus_WriteLcd8(0xce9a,0xA0);       //reg_tcon_tp_term1b_vb_ln_lo
    
    DrvXbus_WriteLcd8(0xce9b,0x02);         //reg_tcon_tp_term2_vb_ln
    //DrvXbus_WriteLcd8(0xceaa,`ROW_NO/256);//reg_tcon_tp_cnt_stp_disp_hi
    //DrvXbus_WriteLcd8(0xceab,`ROW_NO%256);//reg_tcon_tp_cnt_stp_disp_lo
    
    DrvXbus_WriteLcd8(0xceaa,0x0B);        //reg_tcon_tp_cnt_stp_disp_hi
    DrvXbus_WriteLcd8(0xceab,0x40);       //reg_tcon_tp_cnt_stp_disp_lo
    DrvXbus_WriteLcd8(0xceb1,0x00);       //reg_tp_pre_dmy_rtn_hi, reg_tp_pos_dmy_rtn_hi
    DrvXbus_WriteLcd8(0xceb2,0x56);       //reg_tp_pre_dmy_rtn_lo
    DrvXbus_WriteLcd8(0xceb3,0x56);       //reg_tp_pos_dmy_rtn_lo
    DrvXbus_WriteLcd8(0xcfd2,0x00);       //reg_tp_busy_termx_start_cnt_hi
    DrvXbus_WriteLcd8(0xcfd3,0x1d);      //reg_tp_busy_termx_start_cnt_lo
    DrvXbus_WriteLcd8(0xcfd4,0x00);       //reg_tp_busy_termx_end_cnt_hi
    DrvXbus_WriteLcd8(0xcfd5,0x1d);      //reg_tp_busy_termx_end_cnt_lo
    DrvXbus_WriteLcd8(0xcfd7,0x00);       //reg_tp_sw_termx_start_cnt_hi
    DrvXbus_WriteLcd8(0xcfd8,0x28);       //reg_tp_sw_termx_start_cnt_lo
    DrvXbus_WriteLcd8(0xcfd9,0x00);       //reg_tp_sw_termx_end_cnt_hi
    DrvXbus_WriteLcd8(0xcfda,0x12);      //reg_tp_sw_termx_end_cnt_lo
    DrvXbus_WriteLcd8(0xcf84,0x00);      //reg_tp_vcom_termx_start_cnt_hi
    DrvXbus_WriteLcd8(0xcf85,0x28);      //reg_tp_vcom_termx_start_cnt_lo
    DrvXbus_WriteLcd8(0xcf86,0x00);      //reg_tp_vcom_termx_end_cnt_hi
    DrvXbus_WriteLcd8(0xcf87,0x12);      //reg_tp_vcom_termx_end_cnt_lo
    DrvXbus_WriteLcd8(0xcf88,0x05);      //reg_abnormal_width_swb_lo_vcom
    DrvXbus_WriteLcd8(0xcf89,0x00);      //[7:6]reg_abnormal_width_swb_hi_vcom, [1:0]reg_abnormal_width_swb_hi_vglo
    DrvXbus_WriteLcd8(0xcf8a,0x05);      //reg_abnormal_width_swb_lo_vglo
    DrvXbus_WriteLcd8(0xcf8c,0x00);      //reg_tp_vglo_termx_start_cnt_hi
    DrvXbus_WriteLcd8(0xcf8d,0x28);      //reg_tp_vglo_termx_start_cnt_lo
    DrvXbus_WriteLcd8(0xcf8e,0x00);      //reg_tp_vglo_termx_end_cnt_hi 
    DrvXbus_WriteLcd8(0xcf8f,0x12);      //reg_tp_vglo_termx_end_cnt_lo
    DrvXbus_WriteLcd8(0xcfa0,0x00);      //reg_tp_gpio0_start_hi
    DrvXbus_WriteLcd8(0xcfa2,0x10);      //reg_tp_gpio0_start_lo
    DrvXbus_WriteLcd8(0xcfa1,0x00);      //reg_tp_gpio0_end_hi
    DrvXbus_WriteLcd8(0xcfa3,0x20);      //reg_tp_gpio0_end_lo
    DrvXbus_WriteLcd8(0xcfa4,0x03);      //reg_tp_gpio1_start_hi
    DrvXbus_WriteLcd8(0xcfa6,0xD0);      //reg_tp_gpio1_start_lo
    DrvXbus_WriteLcd8(0xcfa5,0x03);      //reg_tp_gpio1_end_hi
    DrvXbus_WriteLcd8(0xcfa7,0xE0);       //reg_tp_gpio1_end_lo
    DrvXbus_WriteLcd8(0xcfa8,0x07);       //reg_tp_gpio2_start_hi
    DrvXbus_WriteLcd8(0xcfaa,0x90);      //reg_tp_gpio2_start_lo
    DrvXbus_WriteLcd8(0xcfa9,0x07);       //reg_tp_gpio2_end_hi
    DrvXbus_WriteLcd8(0xcfab,0xA0);       //reg_tp_gpio2_end_lo
    DrvXbus_WriteLcd8(0xcfac,0x0B);       //reg_tp_gpio3_start_hi
    DrvXbus_WriteLcd8(0xcfae,0x50);      //reg_tp_gpio3_start_lo
    DrvXbus_WriteLcd8(0xcfad,0x0B);      //reg_tp_gpio3_end_hi
    DrvXbus_WriteLcd8(0xcfaf,0x60);      //reg_tp_gpio3_end_lo
    
    //============================================
    // kyo latch control
    //============================================
    DrvXbus_WriteLcd8(0xc491,0x80);//[7]reg_latch_clk_opt
    
    #endif

}


