/*******************************************************************************
* Copyright (C) 2016-2018, FocalTech Systems (R)��All Rights Reserved.
*
* File Name: DrvAsm.h
*
*    Author: lisen
*
*   Created: 2016-12-27
*
*  Abstract:
*
* Reference:
*
* Version:
* 0.1:
*
*******************************************************************************/
#ifndef __DRV_ASM_H_
#define __DRV_ASM_H_

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"

/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/
/* Asm int */
#define LCD_BUSY_FALL_INT0          BITn(15)
#define LCD_BUSY_RISE_INT0          BITn(14)
#define LCD_PANEL_CONFLICT_INT0     BITn(13)
#define LCD_DSTB_FAIL_INT0          BITn(12)
#define LCD_DSTB_RISE_INT0          BITn(11)
#define LCD_SYNC_MISS_FALL_INT0     BITn(10)
#define LCD_SYNC_MISS_RISE_INT0     BITn(9)
#define ARAM_READY_INT0             BITn(8)
#define FRAME_END_INT0              BITn(7)
#define AFE_DET_INT0                BITn(6)
#define LCD_VSTART_INT0             BITn(5)
#define LCD_VMID_INT0               BITn(4)
#define LCD_VEND_INT0               BITn(3)
#define LCD_VBLANK_INT0             BITn(2)
#define LCD_RUN_FALL_INT0           BITn(1)
#define LCD_RUN_RISE_INT0           BITn(0)

#define LCD_HW_MON_TIMEOUT_INT1     BITn(14) 
#define LCD_LPF_MODE_EN_FALL_INT1   BITn(13)
#define LCD_LPF_MODE_EN_RISE_INT1   BITn(12)
#define LCD_STB_TICK_INT1           BITn(11)
#define LCD_ODD_EVEN_FALL_INT1      BITn(10)
#define LCD_ODD_EVEN_RISE_INT1      BITn(9)
#define LCD_VDO_MODE_FALL_INT1      BITn(8)
#define LCD_VDO_MODE_RISE_INT1      BITn(7)  
#define LCD_IDLE_MODE_FALL_INT1     BITn(6)  
#define LCD_IDLE_MODE_RISE_INT1     BITn(5)
#define LCD_3D_MODE_FALL_INT1       BITn(4)
#define LCD_3D_MODE_RISE_INT1       BITn(3)
#define LCD_RUN_INT1                BITn(2)
#define LCD_DSTB_INT1               BITn(1)


/* Asm Sta */
#define LCD_PANEL_CONFLICT_STA      BITn(14)
#define LCD_DSTB_STA                BITn(13)
#define LCD_SYNC_MISS_STA           BITn(12)
#define LCD_FRAME_END_STA           BITn(11)
#define LCD_TCH_DET_STA             BITn(10)
#define LCD_STB_TICK_STA            BITn(9)
#define LCD_VSTART_STA              BITn(8)
#define LCD_VMID_STA                BITn(7)
#define LCD_VEND_STA                BITn(6)
#define LCD_VBLANK_STA              BITn(5)
#define LCD_ODD_EVEN_STA            BITn(4)
#define LCD_VDO_MODE_STA            BITn(3)
#define LCD_IDLE_MODE_STA           BITn(2)
#define LCD_3D_MODE_STA             BITn(1)
#define LCD_RUN_STA                 BITn(0)

/*Scan Sta1*/
#define TP_BUSY_STA                 BITn(11) // [11]  RO: TP busy��ʵʱ״̬
#define LCD_BUSY_STA                BITn(10) // [10]  RO: LCD busy��ʵʱ״̬   

/*Scan Sta2*/
#define LPF_MODE_TP_TURBO_ACK       BITn(13) // [13]  RO: 0:������  1:����
#define VB_MODE_ACK                 BITn(12) // [12]  RO: 0:С��    1:��� 

/* ASM_INT_FLAG0 bit��ϢRO  0x00*/
typedef enum
{
    BIT_LCD_BUSY_FALL_FLAG0          = 15,
    BIT_LCD_BUSY_RISE_FLAG0          = 14,
    BIT_LCD_PANEL_CONFLICT_FLAG0     = 13,
    BIT_LCD_DSTB_FAIL_FLAG0          = 12,
    BIT_LCD_DSTB_RISE_FLAG0          = 11,
    BIT_LCD_SYNC_MISS_FALL_FLAG0     = 10,
    BIT_LCD_SYNC_MISS_RISE_FLAG0     = 9,
    BIT_LCD_ARAM_RDY_FLAG0           = 8,
    BIT_LCD_FRAME_END_FLAG0          = 7,
    BIT_LCD_TCH_DET_FLAG0            = 6,
    BIT_LCD_VSTART_FLAG0             = 5,
    BIT_LCD_VMID_FLAG0               = 4,
    BIT_LCD_VEND_FLAG0               = 3,
    BIT_LCD_VBLANK_FLAG0             = 2,
    BIT_LCD_RUN_FALL_FLAG0           = 1,
    BIT_LCD_RUN_RISE_FLAG0           = 0,          
} ENUM_BIT_ASM_INT_FLAG0;

/* ASM_INT_FLAG1 bit��ϢRO  0x01*/
typedef enum
{           
    
    BIT_LCD_STB_TICK_FLAG1           = 11,
    BIT_LCD_ODD_EVEN_FALL_FLAG1      = 10,
    BIT_LCD_ODD_EVEN_RISE_FLAG1      = 9,
    BIT_LCD_VDO_MODE_FALL_FLAG1      = 8,
    BIT_LCD_VDO_MODE_RISE_FLAG1      = 7,  
    BIT_LCD_IDLE_MODE_FALL_FLAG1     = 6,  
    BIT_LCD_IDLE_MODE_RISE_FLAG1     = 5,
    BIT_LCD_3D_MODE_FALL_FLAG1       = 4,
    BIT_LCD_3D_MODE_RISE_FLAG1       = 3,
    BIT_LCD_RUN_FLAG1                = 2,
    BIT_LCD_DSTB_FLAG1               = 1,
} ENUM_BIT_ASM_INT_FLAG1;

/* ASM_INT_CLR0 bit��ϢWO 0x02*/
typedef enum
{
    BIT_LCD_BUSY_FALL_CLR0          = 15,
    BIT_LCD_BUSY_RISE_CLR0          = 14,
    BIT_LCD_PANEL_CONFLICT_CLR0     = 13,
    BIT_LCD_DSTB_FAIL_CLR0          = 12,
    BIT_LCD_DSTB_RISE_CLR0          = 11,
    BIT_LCD_SYNC_MISS_FALL_CLR0     = 10,
    BIT_LCD_SYNC_MISS_RISE_CLR0     = 9,
    BIT_LCD_ARAM_RDY_CLR0           = 8,
    BIT_LCD_FRAME_END_CLR0          = 7,
    BIT_LCD_TCH_DET_CLR0            = 6,
    BIT_LCD_VSTART_CLR0             = 5,
    BIT_LCD_VMID_CLR0               = 4,
    BIT_LCD_VEND_CLR0               = 3,
    BIT_LCD_VBLANK_CLR0             = 2,
    BIT_LCD_RUN_FALL_CLR0           = 1,
    BIT_LCD_RUN_RISE_CLR0           = 0,        
} ENUM_BIT_ASM_INT_CLR0;

/* ASM_INT_CLR1 bit��ϢWO 0x03*/
typedef enum
{   
    BIT_HW_MON_TIMEOUT_CLR1         = 14,
    BIT_LPF_MODE_EN_FALL_CLR1       = 13,
    BIT_LPF_MODE_EN_RISE_CLR1       = 12,
    BIT_LCD_STB_TICK_CLR1           = 11,    
    BIT_LCD_ODD_EVEN_FALL_CLR1      = 10,
    BIT_LCD_ODD_EVEN_RISE_CLR1      = 9,
    BIT_LCD_VDO_MODE_FALL_CLR1      = 8,
    BIT_LCD_VDO_MODE_RISE_CLR1      = 7,  
    BIT_LCD_IDLE_MODE_FALL_CLR1     = 6,  
    BIT_LCD_IDLE_MODE_RISE_CLR1     = 5,
    BIT_LCD_3D_MODE_FALL_CLR1       = 4,
    BIT_LCD_3D_MODE_RISE_CLR1       = 3,
    BIT_LCD_RUN_CLR1                = 2,
    BIT_LCD_DSTB_CLR1               = 1,   
} ENUM_BIT_ASM_INT_CLR1;

/* ASM_INT_EN0 bit��Ϣ0x04 */
typedef enum
{
    BIT_LCD_BUSY_FALL_EN0          = 15,
    BIT_LCD_BUSY_RISE_EN0          = 14,
    BIT_LCD_PANEL_CONFLICT_EN0     = 13,
    BIT_LCD_DSTB_FAIL_EN0          = 12,
    BIT_LCD_DSTB_RISE_EN0          = 11,
    BIT_LCD_SYNC_MISS_FALL_EN0     = 10,
    BIT_LCD_SYNC_MISS_RISE_EN0     = 9,
    BIT_LCD_ARAM_RDY_EN0           = 8,
    BIT_LCD_FRAME_END_EN0          = 7,
    BIT_LCD_TCH_DET_EN0            = 6,
    BIT_LCD_VSTART_EN0             = 5,
    BIT_LCD_VMID_EN0               = 4,
    BIT_LCD_VEND_EN0               = 3,
    BIT_LCD_VBLANK_EN0             = 2,
    BIT_LCD_RUN_FALL_EN0           = 1,
    BIT_LCD_RUN_RISE_EN0           = 0,        
} ENUM_BIT_ASM_INT_EN0;

/* ASM_INT_EN1 bit��Ϣ0x05 */
typedef enum
{
    BIT_HW_MON_TIMEOUT_EN1         = 14,
    BIT_LCD_LPF_MODE_EN_FALL_EN1   = 13,
    BIT_LCD_LPF_MODE_EN_RISE_EN1   = 12,
    BIT_LCD_STB_TICK_EN1           = 11,   
    BIT_LCD_ODD_EVEN_FALL_EN1      = 10,
    BIT_LCD_ODD_EVEN_RISE_EN1      = 9,
    BIT_LCD_VDO_MODE_FALL_EN1      = 8,
    BIT_LCD_VDO_MODE_RISE_EN1      = 7,  
    BIT_LCD_IDLE_MODE_FALL_EN1     = 6,  
    BIT_LCD_IDLE_MODE_RISE_EN1     = 5,
    BIT_LCD_3D_MODE_FALL_EN1       = 4,
    BIT_LCD_3D_MODE_RISE_EN1       = 3,
    BIT_LCD_RUN_EN1                = 2,
    BIT_LCD_DSTB_EN1               = 1,
   
} ENUM_BIT_ASM_INT_EN1;

/* ASM_INT_WAKE_EN0 bit��Ϣ  06 */
typedef enum
{
    BIT_LCD_BUSY_FALL_WAKE_EN0          = 15,
    BIT_LCD_BUSY_RISE_WAKE_EN0          = 14,
    BIT_LCD_PANEL_CONFLICT_WAKE_EN0     = 13,
    BIT_LCD_DSTB_FAIL_WAKE_EN0          = 12,
    BIT_LCD_DSTB_RISE_WAKE_EN0          = 11,
    BIT_LCD_SYNC_MISS_FALL_WAKE_EN0     = 10,
    BIT_LCD_SYNC_MISS_RISE_WAKE_EN0     = 9,
    BIT_LCD_ARAM_RDY_WAKE_EN0           = 8,
    BIT_LCD_FRAME_END_WAKE_EN0          = 7,
    BIT_LCD_TCH_DET_WAKE_EN0            = 6,
    BIT_LCD_VSTART_WAKE_EN0             = 5,
    BIT_LCD_VMID_WAKE_EN0               = 4,
    BIT_LCD_VEND_WAKE_EN0               = 3,
    BIT_LCD_VBLANK_WAKE_EN0             = 2,
    BIT_LCD_RUN_FALL_WAKE_EN0           = 1,
    BIT_LCD_RUN_RISE_WAKE_EN0           = 0,              
} ENUM_BIT_ASM_WAKE_EN0 ;

/* ASM_INT_WAKE_EN1 bit��Ϣ  07 */
typedef enum
{
    BIT_HW_MON_TIMEOUT_WAKE_EN1         = 14,
    BIT_LCD_LPF_MODE_EN_FALL_WAKE_EN1   = 13,
    BIT_LCD_LPF_MODE_EN_RISE_WAKE_EN1   = 12,
    BIT_LCD_STB_TICK_WAKE_EN1           = 11, 
    BIT_LCD_ODD_EVEN_FALL_WAKE_EN1      = 10,
    BIT_LCD_ODD_EVEN_RISE_WAKE_EN1      = 9,
    BIT_LCD_VDO_MODE_FALL_WAKE_EN1      = 8,
    BIT_LCD_VDO_MODE_RISE_WAKE_EN1      = 7,  
    BIT_LCD_IDLE_MODE_FALL_WAKE_EN1     = 6,  
    BIT_LCD_IDLE_MODE_RISE_WAKE_EN1     = 5,
    BIT_LCD_3D_MODE_FALL_WAKE_EN1       = 4,
    BIT_LCD_3D_MODE_RISE_WAKE_EN1       = 3,
} ENUM_BIT_ASM_WAKE_EN1;

/* ASM_INT_STA0 bit��Ϣ  RO  08 */
typedef enum
{
    BIT_LCD_BUSY_STA                = 15,
    BIT_LCD_PANEL_CONFLICT_STA      = 14,
    BIT_LCD_DSTB_STA                = 13,
    BIT_LCD_SYNC_MISS_STA           = 12,
    BIT_LCD_FRAME_END_STA           = 11,
    BIT_LCD_TCH_DET_STA             = 10,
    BIT_LCD_STB_TICK_STA            = 9,
    BIT_LCD_VSTART_STA              = 8,
    BIT_LCD_VMID_STA                = 7,
    BIT_LCD_VEND_STA                = 6,
    BIT_LCD_VBLANK_STA              = 5,
    BIT_LCD_ODD_EVEN_STA            = 4,
    BIT_LCD_VDO_MODE_STA            = 3,
    BIT_LCD_IDLE_MODE_STA           = 2,
    BIT_LCD_3D_MODE_STA             = 1,
    BIT_LCD_RUN_STA                 = 0,
} ENUM_BIT_ASM_INT_STA0;

/* ASM_SCAN_STA0 bit��Ϣ  RO  09 */
typedef enum
{
    BIT_CUR_TP_FRAME_ID_STA   = 12,         // [15:12] RO:��ǰɨ���TP֡��
    //BIT_TPFRM_NUM_DISCARD      = 6,          // [8:6]   RO:1:��ʾ��֡    
    BIT_BUSY_ID_STA1           = 0,          // [5:0]   RO:��IDʵʱ״̬        
} ENUM_BIT_SCAN_STA0;

/* ASM_SCAN_STA1 bit��Ϣ  RO  10 */
typedef enum
{
    BIT_HW_MON_TIMEOUT_STA    = 15,           // [15]  RO: 1:��ʱ
    BIT_LPF_MODE_EN_STA       = 14,           // [14]  RO: 1:skip frame ״̬
    BIT_LPF_MODE_TP_TURBO_ACK = 13,           // [13]  RO: 0:������  1:����
    BIT_VB_MODE_ACK = 12,                     // [12]  RO: 0:С��    1:��� 
    BIT_TP_BUSY     = 11,                     // [11]  RO: TP busy��ʵʱ״̬
    BIT_LCD_BUSY    = 10,                     // [10]  RO: LCD busy��ʵʱ״̬                   
    //BIT_TAIL_MARGIN = 0,                      // [9:0] RO: TPÿ��ɨ���β����                        
} ENUM_BIT_SCAN_STA1;

/* ASM_SCAN_STA2 bit��Ϣ  RO  11 */
typedef enum
{    
    BIT_AFE_WR_ARAM_AVAIL_N  = 12,            // [12]   RO: 1: ��ǰ������дARAM
    BIT_STB_ID       = 6,                     // [11:6] RO:LCD����������ʵʱ״̬                  
    BIT_STB_TICK_ID  = 0,                     // [5:0]  RO:LCD���ʱ����������״̬������mask��            
} ENUM_BIT_SCAN_STA2;

/* ASM_SCAN_STA2 bit��Ϣ  RO  12 */
typedef enum
{    
    BIT_BUSY_ID_MAX  = 6,                     // [11:6] RO:���Ӻ�               
    BIT_BUSY_ID_MIN  = 0,                     // [5:0]  RO:��С�Ӻ�         
} ENUM_BIT_SCAN_STA3;

/* ASM_SCAN_CTRL bit��Ϣ WO 13*/
typedef enum
{             
    BIT_AFE_WR_ARAM_AVAIL_N_CLR = 2,          // [2] WO: 1:���Բ���ARAM
    BIT_BUSY_ID_MAX_RESET   = 1,              // [1] WO: ��ͳ�Ƽ��������ֵ��λ��д1��λ            
    BIT_SCAN_START          = 0,              // [0] WO: ����ɨ��                       
} ENUM_BIT_ASM_SCAN_CTRL;

/* ASM_SCAN_CFG0 bit��Ϣ 14 */
typedef enum
{
    BIT_MONITOR_MODE         = 15,              // [15]Ӳ���������ģʽ: 1: �ǣ�      0:��   
    BIT_CB_ADJUST_MODE       = 14,              // [14]CBУ��ģʽ:       1:У��ģʽ   0:����ģʽ           
    BIT_AFE_CLKGATE_EN       = 12,              // [12]�Զ��ſ�AFEʱ��:  1:�Զ��ſ� 0:���Զ��ſ� 
    BIT_SCAN_START_STORE_EN  = 10,              // [10]1:���棬�Զ�������һ��ɨ�裬0:�����棬���Զ������´�ɨ�衣        
    BIT_LCD_FRAME_HEAD_ALIGN = 9,               // [9]��0֡������ʱ��ѡ��:0:��ǰLCD֡��ʼʣ���ɨ��; 1:���ID,��LCD֡��ʼɨ��    
    BIT_VBLANK_EDGE_SEL      = 8,               // [8]busy_id�����ź�ѡ��: 0:������ ��1: �½���  
    BIT_VSTART_EDGE_SEL      = 7,               // [7]busy_id�����ź�ѡ��: 0:������ ��1: �½���      
    BIT_VMID_EDGE_SEL        = 6,               // [6]busy_id�����ź�ѡ��: 0:������ ��1: �½��� 
    BIT_VEND_EDGE_SEL        = 5,               // [5]busy_id�����ź�ѡ��: 0:������ ��1: �½��� 
    BIT_CLR_BUSY_ID_SEL      = 3,               // [4:3] �����ź�ѡ��: 0:vstart; 1:vmid 2:vend 3:vblank
    BIT_TP_FRAME_NUM         = 0,               // [2:0]��֡ɨ�����֡�� 0-3: ɨ��1-4��TP֡   CB:4-7 ɨ��5-8��TP֡  
} ENUM_BIT_ASM_SCAN_CFG0;

/* ASM_SCAN_CFG1 bit��Ϣ 15*/
typedef enum
{
    BIT_LCD_RUN_INTPHASE     = 15,              // [15] LCD RUN �жϵ�ƽѡ��0:�͵�ƽ��1:�ߵ�ƽ  
    BIT_LCD_DSTB_INTPHASE    = 14,              // [14] LCD Deep Standby�жϵ�ƽѡ��0:�͵�ƽ��1:�ߵ�ƽ  
    BIT_LPF_MODE_TP_TURBO_REQ= 9,               // [9]:Tp����LCD��skip frameʱ���Ƿ񿪿ӡ�0:�����ӣ�1:���ӡ� 
    BIT_VB_MODE_REQ          = 8,               // [8]:Tp����LCD�л���С��.               0:С��(120hz)��  1:���(60hz)��
    BIT_TP_END_SEL           = 5,               // [5] TP֡������־ѡ��. 0:tp frane end;  1:aram ready
    BIT_STB_EN               = 4,               // [4] Ԥ�ȼ��ز�������CB shiftʹ��: 1:ʹ��         
    BIT_HW_MONITOR_EN        = 3,               // [3] Ӳ��Monitorʹ�ܣ�           1: ʹ�� 
    BIT_VBLANK_INV           = 1,               // [1] Vblank��Ч��ƽѡ�������ж�, 0:�ߵ�ƽ��1:�͵�ƽ   
} ENUM_BIT_ASM_SCAN_CFG1;

/* ASM TP FRAME CFG0 bit��Ϣ 16*/
typedef enum
{
    BIT_TAB_ID1              = 14,              // [14] ��1��TP֡�õ�Table���  
    BIT_BUSY_ID1             = 8,               // [8] ��1��TP֡��ʼ�Ӻ�        
    BIT_TAB_ID0              = 6,               // [6] ��0��TP֡�õ�Table���     
    BIT_BUSY_ID0             = 0,               // [0] ��0��TP֡��ʼ�Ӻ� 
} ENUM_BIT_ASM_TP_FRAME_CFG0;

/* ASM TP FRAME CFG1 bit��Ϣ 17*/
typedef enum
{
    BIT_TAB_ID3              = 14,              // [14] ��3��TP֡�õ�Table���  
    BIT_BUSY_ID3             = 8,               // [8] ��3��TP֡��ʼ�Ӻ�        
    BIT_TAB_ID2              = 6,               // [6] ��2��TP֡�õ�Table���     
    BIT_BUSY_ID2             = 0,               // [0] ��2��TP֡��ʼ�Ӻ� 
} ENUM_BIT_ASM_TP_FRAME_CFG1;

/* ASM TP FRAME CFG2 bit��Ϣ 18*/
typedef enum
{
    BIT_BUSY_ID5             = 8,               // [8] ��5��TP֡��ʼ�Ӻ�        
    BIT_BUSY_ID4             = 0,               // [0] ��4��TP֡��ʼ�Ӻ� 
} ENUM_BIT_ASM_TP_FRAME_CFG2;

/* ASM TP FRAME CFG3 bit��Ϣ 19*/
typedef enum
{
    BIT_BUSY_ID7             = 8,               // [8] ��7��TP֡��ʼ�Ӻ�        
    BIT_BUSY_ID6             = 0,               // [0] ��6��TP֡��ʼ�Ӻ� 
} ENUM_BIT_ASM_TP_FRAME_CFG3;

/*ASM_ SCAN_DELAY  bit��Ϣ 20 */
typedef enum
{
    BIT_TAB_EN3             = 13,               // [13] Tab3��ʹ��: 1:ʹ�� 
    BIT_TAB_EN2             = 12,               // [12] Tab2��ʹ��: 1:ʹ�� 
    BIT_TAB_EN1             = 11,               // [11] Tab1��ʹ��: 1:ʹ�� 
    BIT_TAB_EN0             = 10,               // [10] Tab0��ʹ��: 1:ʹ�� 
    BIT_SCAN_DELAY          = 0,                // [9:0]LCD RUN�½��ص�ɨ�迪ʼ����ʱ
}ENUM_BIT_ASM_SCAN_DELAY;

/*ASM STB MASK L   bit��Ϣ 21 */
typedef enum
{
    BIT_STB_MASK_L          = 0,                // [15:0]STB_TICK�ж��������õ�λ
}ENUM_BIT_STB_MASK_L;

/*ASM STB MASK H   bit��Ϣ 22 */
typedef enum
{
    BIT_STB_MASK_H          = 0,                // [15:0]STB_TICK�ж��������ø�λ
}ENUM_BIT_STB_MASK_H;

/*ASM ARAM BASE L  bit��Ϣ 23 */
typedef enum
{
    BIT_ARAM_BASE_L         = 0,                // [9:0]��AFE������ARAM�д�ŵĻ���ַ
}ENUM_BIT_ARAM_BASE_L; 

/*ASM ARAM BASE R  bit��Ϣ 24*/
typedef enum
{
    BIT_ARAM_BASE_R         = 0,                // [9:0]��AFE������ARAM�д�ŵĻ���ַ
}ENUM_BIT_ARAM_BASE_R;

/*ASM ARAM BASE KEY bit��Ϣ 25*/
typedef enum
{
    BIT_ARAM_BASE_KEY       = 0,                // [9:0]KEY������ARAM�д�ŵĻ���ַ
}ENUM_BIT_ARAM_BASE_KEY; 

/*ASM CB BASE L  bit��Ϣ 26 */
typedef enum
{
    BIT_CB_BASE_L           = 0,                // [9:0]��CB������ARAM�д�ŵĻ���ַ
}ENUM_BIT_CB_BASE_L;

/*ASM CB BASE R  bit��Ϣ 27 */
typedef enum
{
    BIT_CB_BASE_R           = 0,                // [9:0]��CB������ARAM�д�ŵĻ���ַ
}ENUM_BIT_CB_BASE_R;

/*ASM CB BASE KEY bit��Ϣ 28 */
typedef enum
{
    BIT_CB_BASE_KEY         = 0,                // [9:0]KEY CB������ARAM�д�ŵĻ���ַ
}ENUM_BIT_CB_BASE_KEY; 

/* ASM TAIL MARGIN bit��Ϣ 29 */
typedef enum
{
	BIT_TAIL_MARGIN         = 0,                // [9:0]RO tpÿ��ɨ���β����.
}ENUM_BIT_TAIL_MARGIN;

/*ASM PWR CTRL bit��Ϣ 32*/
typedef enum
{
    BIT_PWROFF_AUTO           = 3,             //[3]�Ƿ���ɨ����ɺ��Զ��µ�,�üĴ�����hw monģʽ��������.0:��;1:��
    BIT_HWMON_PWR_EN          = 2,             //[2]�Ƿ���hw monģʽ�¿������µ�ʱ��.0:������;1:����
    BIT_PWROFF_START          = 1,             //[1]д1��ʼ�µ�ʱ��Ӳ���Զ����㣬����Ϊ0
    BIT_PWRON_START           = 0,             //[0]д1��ʼ�ϵ�ʱ��Ӳ���Զ����㣬����Ϊ0
}ENUM_BIT_PWR_CTRL;

/*ASM PWR STA bit��Ϣ 33*/
typedef enum
{
    BIT_PWR_STA               = 0,             //[0]ָʾ�Զ����µ�ģ����ϵ���µ�״̬.0:��ǰΪ�µ����״̬;1:��ǰΪ�ϵ����״̬
}ENUM_BIT_PWR_STA;


/*ASM PWR INTERVAL0 bit��Ϣ 34*/
typedef enum
{
    BIT_T1_DSVR_BGPR          = 8,             //[15:8]DSV_EN�����غ�NVDD2_MASK,VDD_TP_MASK_N1��BGP_MASK�����ص�ʱ�Ӹ���(rtc clk)=t1+1               
    BIT_T2_BGPR_REFBGR        = 4,             //[7:4] NVDD2_MASK,VDD_TP_MASK_N1�����ص�VDD_TP_MASK[3:2]��REFBG_EN�����ص�ʱ�Ӹ��� =t2+1
    BIT_T3_REFBGR_REFOPR      = 0,             //[3:0]VDD_TP_MASK[3:2]��REFBG_EN�����ص�VREFTP_SETOP_EN�����ص�ʱ�Ӹ���=t3+1
}ENUM_BIT_PWR_INTERVAL0;

/*ASM PWR INTERVAL1 bit��Ϣ 35*/
typedef enum
{
    BIT_T4_REFOPR_REFBUFR     = 12,            //[15:12]VREFTP_SETOP_EN�����ص�VREFTP_BUF_EN�����ص�rtcʱ�Ӹ���=t4
    BIT_T5_REFOPR_REFSHR      = 8,             //[11:8]VREFTP_SETOP_EN�����ص�VREFTP_SH�����ص�ʱ�Ӹ���=t5
    BIT_T6_REFSH_WIDTH        = 0,             //[7:0] VREFTP_SH���RTCʱ�Ӹ���=t6
}ENUM_BIT_PWR_INTERVAL1;

/*ASM PWR INTERVAL2 bit��Ϣ 36*/
typedef enum
{
    BIT_T7_REFBUFR_REFSRR     = 8,              //[15:8] VREFTP_BUF�����ص�VREFTP_SR_CTRL�����ص�ʱ�Ӹ���=t7+1
    BIT_T8_SRCTRLR_PWRON      = 0,              //[7:0]  VREFTP_SRCTRL��VDD5_SRCTRL����������ص�power�ȶ�������ɨ��������ص�ʱ�Ӹ���=t8+1
}ENUM_BIT_PWR_INTERVAL2;

/*ASM PWR INTERVAL3 bit��Ϣ 37*/
typedef enum
{
    T9_REFBUFR_VDD5SRR        = 8,              //[15:8]VREFTP_BUF�����ص�VDD5_SRCTRL�����ص�ʱ�Ӹ���=t9+1
    T10_TPBUSYF_REFBGF        = 4,              //[7:4] TP_BUSY�½��ص�REFBG_EN�½��ص�ʱ�Ӹ���=t10+1
    T11_REFBGF_BGPF           = 0,              //[3:0] REFBG_E�½��ص�BGP_MASK�½��ص�rtcʱ�Ӹ���=t11+1
}ENUM_BIT_PWR_INTERVAL3;

/*ASM PWR INTERVAL4 bit��Ϣ 38*/
typedef enum
{
    T12_BGPF_DSVF            = 12,             //[15:12]BGP_MASK�½��ص�DSV_EN�½��ص�ʱ�Ӹ���=t12+1
    T_OPENAFECLK_TPSCAN      = 0,              //[4:0]  ��AFEʱ�ӿ�����ɨ���rtcʱ�Ӹ���=t+1
}ENMU_BIT_PWR_INTERVAL4;


/*ASM HW MON TIMER bit��Ϣ 39*/
typedef enum
{
    BIT_HW_MON_TIMER          = 0             // [11:0] ����rtcӲ��monitorģʽ,��RTC_INT�жϴ����ﵽhw_mon_timer+1,
                                              //        �����timeout�ж�(��ʹ���ж�) .��ʱAFEֻɨ��hw_mon_tiemr�� 
}ENUM_BIT_HW_MON_TIMER;

/*ASM VREFSH CFG LCDON bit��Ϣ 40*/
typedef enum
{
    BIT_VREFSH_REFSEL_LCDON   = 12,           // [12] ������TP2XTP_VREFTP_SH�����زο��ź�ѡ��
                                              //      0:vbp�ź�������;1:lcd_vend�ź�������
    BIT_VREFSH_DLY_LCDON      = 8,            // [11:8] ������TP2XTP_VREFTP_SH��ʱ����250khz����
    BIT_VREFSH_WIDTH_LCDON    = 0             // [7:0]  ������TP2XTP_VREFTP_SH��ȣ���250khz����
}ENUM_BIT_VREFSH_CFG_LCDON;

/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern volatile UINT16 XRAM g_usAsmIntSta;
extern ST_AsmRegisters * XRAM pAsmRegs;
/*******************************************************************************
* 5.Global function prototypes
*******************************************************************************/
void DrvAsmSetPhase(void);
void Asm_Config_Init(void);
void DrvLoadTabSingle(UINT8 ucTabId,UINT8 ucBusyID);
void DrvLoadTabMultiple(UINT8 ucBusyId0,UINT8 ucBusyId1,UINT8 ucBusyId2,UINT8 ucBusyId3,UINT8 ucScanMul,UINT8 ucTab);

void DrvAsmInterEnable0(UINT16 usInterMode);
void DrvAsmInterDisable0(UINT16 usInterMode);
void DrvAsmInterEnable1(UINT16 usInterMode);
void DrvAsmInterDisable1(UINT16 usInterMode);
void DrvAsmInterClear0(UINT16 usClearMode);
UINT16 DrvAsmGetSta(void);
UINT16 DrvAsmGetSta1(void);
void DrvAsmSetIDReset(void);
void DrvAsmSetPhase(void);
void DrvAsmSeStbtMask(UINT16 usMask);
void DrvAsmScanStart(void);
void DrvAsmAramAvail(void);
void DrvAsmMonitoModeInit(void);
void DrvAsmReq60hz_Big_LcdBusy(void);
void DrvAsmReq120hz_Small_LcdBusy(void);
void AppGetAsmState(void);
void DrvAsmWakeEnable0(UINT16 usWakeMode);
void DrvAsmWakeEnable1(UINT16 usWakeMode);
void DrvAsmSetCBAdjustMode(UINT8 ucModeEn);
void DrvLoadTabCB(UINT8 ucTabId,ENUM_AFE_MODE ucCbMode);
void DrvGetAramCb(void);
void DrvGetAramRawData(void);
void DrvAsmSetRtcMonitorMode(UINT8 ucModeEn);
void DrvAsmSetRtcMonitorTimer(UINT16 ucTimer);
void DrvAsmSetHwMonPwrEn(UINT8 ucEn);
void DrvAsmSetRTCMoniroMode(UINT8 ucModeEn);
void DrvAsmRtcMonitoModeInit(void);
void DrvAsmClrInt(void);
void DrvAsmSetPwrOn(void);
void DrvAsmSetPwrOff(void);
void DrvGetAdcData(UINT16 ucLen);
void DrvAsmWakeDisable0(UINT16 usWakeMode);
void DrvAsmWakeDisable1(UINT16 usWakeMode);
void DrvAsmInterDisableAll(void);
void DrvAsmAfeClkGateEn(void);

#endif
