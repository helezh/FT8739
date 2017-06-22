/*******************************************************************************
* Copyright (C) 2012-2014, FocalTech Systems (R)，All Rights Reserved.
*
* File Name: Test_Afe.h
*
*    Author: xinkunpeng
*
*   Created: 2014-05-15
*
*  Abstract:
*
* Reference:
*
*   Version:
*******************************************************************************/
#ifndef __TEST_AFE_H__
#define __TEST_AFE_H__

/*******************************************************************************
* 1.Included files
*******************************************************************************/
#include "CfgGlobal.h"


/*******************************************************************************
* 2.Global constant and macro definitions using #define
*******************************************************************************/

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
#define TP_BUSY_STA                 BITn(11) // [11]  RO: TP busy的实时状态
#define LCD_BUSY_STA                BITn(10) // [10]  RO: LCD busy的实时状态   

/*Scan Sta2*/
#define LPF_MODE_TP_TURBO_ACK       BITn(13) // [13]  RO: 0:不开坑  1:开坑
#define VB_MODE_ACK                 BITn(12) // [12]  RO: 0:小坑    1:大坑 



/*******************************************************************************
* 3.Global structures, unions and enumerations using typedef
*******************************************************************************/
/* ASM_INT_FLAG0 bit信息RO	0x00*/
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

/* ASM_INT_FLAG1 bit信息RO	0x01*/
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

/* ASM_INT_CLR0 bit信息WO 0x02*/
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

/* ASM_INT_CLR1 bit信息WO 0x03*/
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

/* ASM_INT_EN0 bit信息0x04 */
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

/* ASM_INT_EN1 bit信息0x05 */
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

/* ASM_INT_WAKE_EN0 bit信息  06 */
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

/* ASM_INT_WAKE_EN1 bit信息  07 */
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

/* ASM_INT_STA0 bit信息  RO  08 */
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

/*******************************************************************************
* 4.Global variable extern declarations
*******************************************************************************/
extern ST_AsmRegisters * XRAM pAsmRegs;
/*******************************************************************************
* 5.Global function prototypes
********************************************************************************/
void Afe_120Hz_Run(void);
void DrvAsmInterEnable0(UINT16 usInterMode);
void DrvAsmAramAvail(void);
void DrvAsmScanStart(void);
void DrvAsmInterEnable1(UINT16 usInterMode);

#endif

