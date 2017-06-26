/* --------------------------------------------------------------
convert xxx.bin to xxx.i
the format of I file is
0xab,0xcd ...

release history
version 1.0: [2014/8/20]
    1.For FT8606 initial version

version 1.1: [2014/8/26]
    1.增加 XBUS时钟配置

version 1.2: [2014/10/23]
    1.Boot ID移到 FILE_SYSCFG

version 1.3: [2014/10/30]
    1.解决长度为奇数时， LenMax - 0x1000处，被写0xFF bug

version 1.4: [2014/11/10]
    1.参数文件名同步

version 1.5: [2014/11/26]
    1. lcd配置文件名改为  "lcd_cfg.v"

version 1.6: [2015/03/17]
    1. 识别 _LCD_RELOAD_EN, 可关闭Rom的 lcd配置功能

version 1.7: [2015/11/09]
    1.CRC改为16位;
    2.适用FT8736;

version 1.8: [2016/12/05]
	1.将app长度改为70k
	2.增加两byte用于记录code_length，以满足70k的需要
	3.适用FT8836

--------------------------------------------------------------- */


/*******************************************************************************
* 1.Included header files
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>

/*******************************************************************************
* 2.Private constant and macro definitions using #define
*******************************************************************************/
//版本信息提取文件路径
#define     FILE_CONFIG    "../../src/include/config/CfgPanelPara.h"
#define     FILE_PARAMETER "../../src/include/config/CfgPanelPara.h"
#define     FILE_SYSCFG    "../../src/include/config/CfgSystem.h"
#define     FILE_CFG       "../../src/include/config/CfgGlobal.h"


#define     MAX_LINE_BUF_SIZE   (32768)
#define     MAX_STR_SIZE        (1024)
#define     BIN_MERGE_VERSION   "2.0"

#define     CUSTOMER_CODE_LEN   16
#define     PROJECT_CODE_LEN    32
//------------------------------------------------------------------------------
#define     DBG_INFO   printf

// app
#define     APP_ADDR_PART1_START 0x0000
#define     APP_INFO_ADDR        0x0100  //info开始地址
#define     APP_VERIF_LEN        0x20

// flash
#define     FLASH_LCD_CRC         0x0006
#define     FLASH_APP_START       0x1000  //app开始地址
#define     FLASH_APP_INFO       (FLASH_APP_START+APP_INFO_ADDR)

#define     ALL_ADDR_PART1_START    FLASH_APP_START
#define     ALL_ADDR_PART1_LEN      APP_INFO_ADDR
#define     ALL_ADDR_PART2_START   (FLASH_APP_INFO+APP_VERIF_LEN+FW_CFG_INFO_SIZE)
//lcd 
#define     LCD_CONFIG_LEN        0x1000

/******************************************************************************/
// App Info
typedef enum
{
    APP_LEN_L_H    = 0,
    APP_LEN_L_L    = 1,
    APP_LEN_L_H_NE = 2,
    APP_LEN_L_L_NE = 3,
    P1_ECC_H       = 4,
    P1_ECC_L       = 5,
    P1_ECC_NE_H    = 6,
    P1_ECC_NE_L    = 7,
    P2_ECC_H       = 8,
    P2_ECC_L       = 9,
    P2_ECC_NE_H    = 0x0A,
    P2_ECC_NE_L    = 0x0B,
    VENDER_ID      = 0x0C,
    VENDER_ID_NE   = 0x0D,
    FW_VERSION     = 0x0E,
    FW_VERSION_NE  = 0x0F,
    UP_FLAG        = 0x10,
    UP_FLAG_NE     = 0x11,
    APP_LEN_H_H    = 0x12,
    APP_LEN_H_L    = 0x13,
    APP_LEN_H_H_NE = 0x14,
    APP_LEN_H_L_NE = 0x15,
    PBOOT_ID_H     = 0x1E,
    PBOOT_ID_L     = 0x1F,
} ENUM_APP_INFO;

#define     ADDR_APP_LEN_L_H    (FLASH_APP_INFO + APP_LEN_L_H)
#define     ADDR_APP_LEN_L_L    (FLASH_APP_INFO + APP_LEN_L_L)
#define     ADDR_APP_LEN_L_H_NE (FLASH_APP_INFO + APP_LEN_L_H_NE)
#define     ADDR_APP_LEN_L_L_NE (FLASH_APP_INFO + APP_LEN_L_L_NE)
#define     ADDR_PART1_ECC_H    (FLASH_APP_INFO + P1_ECC_H)
#define     ADDR_PART1_ECC_L    (FLASH_APP_INFO + P1_ECC_L)
#define     ADDR_PART1_ECC_NE_H (FLASH_APP_INFO + P1_ECC_NE_H)
#define     ADDR_PART1_ECC_NE_L (FLASH_APP_INFO + P1_ECC_NE_L)
#define     ADDR_PART2_ECC_H    (FLASH_APP_INFO + P2_ECC_H)
#define     ADDR_PART2_ECC_L    (FLASH_APP_INFO + P2_ECC_L)
#define     ADDR_PART2_ECC_NE_H (FLASH_APP_INFO + P2_ECC_NE_H)
#define     ADDR_PART2_ECC_NE_L (FLASH_APP_INFO + P2_ECC_NE_L)

#define     ADDR_PANEL_ID       (FLASH_APP_INFO + VENDER_ID)
#define     ADDR_PANEL_ID_NE    (FLASH_APP_INFO + VENDER_ID_NE)
#define     ADDR_VERSION        (FLASH_APP_INFO + FW_VERSION)
#define     ADDR_VERSION_NE     (FLASH_APP_INFO + FW_VERSION_NE)
#define     ADDR_UPGRADE_FLG1   (FLASH_APP_INFO + UP_FLAG)
#define     ADDR_UPGRADE_FLG2   (FLASH_APP_INFO + UP_FLAG_NE)

#define     ADDR_APP_LEN_H_H    (FLASH_APP_INFO + APP_LEN_H_H)
#define     ADDR_APP_LEN_H_L    (FLASH_APP_INFO + APP_LEN_H_L)
#define     ADDR_APP_LEN_H_H_NE (FLASH_APP_INFO + APP_LEN_H_H_NE)
#define     ADDR_APP_LEN_H_L_NE (FLASH_APP_INFO + APP_LEN_H_L_NE)

#define     ADDR_BOOT_ID_HIGH   (FLASH_APP_INFO + PBOOT_ID_H)
#define     ADDR_BOOT_ID_LOW    (FLASH_APP_INFO + PBOOT_ID_L)
/******************************************************************************/
// Boot Cfg
#define     FW_CFG_INFO_ADDR       0x0F80        //FW配置区地址 0x0780
#define     FW_CFG_INFO_SIZE       0x80          //FW配置区长度
#define     FW_CFG_INFO_BKUP_ADDR  (FLASH_APP_INFO+APP_VERIF_LEN)  //FW配置区备份地址 0x1120

typedef enum
{
    I2C_SLAVE_ID  = 0x00,
    IO_VOLTAGE_ID = 0x02,
    VENDOR_ID     = 0x04,
    SPI_CLK_ID    = 0x06,
    SYS_CLK_ID    = 0x08,
    XBUS_CLK_ID    = 0x0A,
	SPI_IO_MODE_ID= 0x0C,
    PRJ_NAME_ID   = 0x20,
    CUSTOMER_ID   = 0x40,
} ENUM_BOOT_CFG;

/******************************************************************************/

#define     FLASH_FILE_BUF_SIZE   (0x20000)        //128K
#define     APP_FILE_MAX_SIZE     (0x11800-2)//70K         (0x10000-FLASH_APP_START-2)      //60K

#define     CLK_SELECT_SUM 0xAB
#define     ROM_SPI_DIV4   0x04  // 0x57:4分频,其它:8分频
#define     ROM_SYS_48M    0x48  // 0x5C:50M,其它:25M

//------------------------------------------------------------------------------
#define     AL2_FCS_COEF        ((1 << 7) + (1 << 6) + (1 << 5))
#define     AL2_FCS_COEF16      ((1 << 15) + (1 << 10) + (1 << 3))
#define     FTS_I2C_SLAVE       0x70

#define     GRAB_BIT(x,y)       ((x&(0x0001<<y))>>y)
//------------------------------------------------------------------------------
//lcd配置相关
#define FILE_LCD_CFG          "./lcd_cfg.v"   /* LCD配置文件 */
#define LCD_REG_MAX_SIZE      0xF80

/*******************************************************************************
* 3.Private enumerations, structures and unions using typedef
*******************************************************************************/
/*后续考虑统一字长定义*/
typedef unsigned char   UINT8;
typedef signed char     INT8;
typedef unsigned short  UINT16;
typedef signed short    INT16;
typedef unsigned int    UINT32;
typedef signed int      INT32;

/*******************************************************************************
* 4.Static variables
*******************************************************************************/
static unsigned char _suc_i2c_enable = 1;
static unsigned char s_bLcdValid = 0;
/*******************************************************************************
* 5.Global variable or extern global variabls/functions
*******************************************************************************/

/*******************************************************************************
* 6.Static function prototypes
*******************************************************************************/

/*******************************************************************************
*   Name: _get_crc8
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_crc8(unsigned char *ptr,int length)
{
    unsigned char cFcs = 0;
    int i, j;

    for ( i = 0; i < length; i++ )
    {
        cFcs ^= ptr[i];
        for (j = 0; j < 8; j ++)
        {
            if (cFcs & 1)
            {
                cFcs = (unsigned char)((cFcs >> 1) ^ AL2_FCS_COEF);
            }
            else
            {
                cFcs >>= 1;
            }
        }
    }
    return cFcs;
}

/*******************************************************************************
*   Name: GetCrc16
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned short _get_crc16(unsigned char *ptr,int length)
{
    unsigned short cFcs = 0;
    int i, j;
    //长度奇偶校验
    if (length%2)
    {
        return 0xFFFF;
    }

    for ( i = 0; i < length; i+=2 )
    {
        cFcs ^= ((ptr[i] << 8) + ptr[i+1]);
        for (j = 0; j < 16; j ++)
        {
            if (cFcs & 1)
            {
                cFcs = (unsigned short)((cFcs >> 1) ^ AL2_FCS_COEF16);
            }
            else
            {
                cFcs >>= 1;
            }
        }
    }
    return cFcs;
}


/******************************************************************************
*
*   Name: GetLcdCrc16
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned short _xorbit(unsigned char ucStart,unsigned char ucEnd,unsigned short usData,unsigned short usCrcCode)
{
    int j;
    //printf("Input = 0x%04x\n",usData);
    for(j =ucStart ;j < ucEnd; j++)
    {
        //printf("BitAdd = %2d Data =0x%04x Bit = %d ",j,usCrcCode,(GRAB_BIT(usData,j)));
        usCrcCode ^=(GRAB_BIT(usData,j)); 
        //printf("Ans = 0x%04x\n",usCrcCode);
        //getch();
    }
    return usCrcCode;
}
/******************************************************************************
*
*   Name: GetLcdCrc16
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned short _writebit(unsigned short usCrcCode,unsigned char ucData,unsigned char ucbitaddr)
{
    usCrcCode &= (~(0x0001 << ucbitaddr));
    usCrcCode |= ucData<<ucbitaddr;
    //printf("Bit = %2d CrcCode = 0x%04x\n",ucbitaddr,usCrcCode);

    return usCrcCode;
}

unsigned short _Lcd_crc16_cal(unsigned char *ptr,int length)
{
    unsigned short cFcs = 0;
    unsigned short usCrcTmp = 0x0001;
    unsigned short usDataTmp = 0;
    unsigned short usExeCode = 0xFFFF;
    unsigned short usXorBit = 0;
    unsigned short usCheckSum = 0;
    int i, j;
#if 0
    //长度奇偶校验
    if (length%2)
    {
        return 0xFFFF;
    }
#endif

    usDataTmp = 0;
    for ( i = 0; i < length; i++ )
    {
        //printf("%02x\n ",ptr[i]);
        usDataTmp = 0;
//      usCheckSum += ptr[i];

        usXorBit = (GRAB_BIT(usExeCode,8));
        usXorBit = _xorbit(9,16,usExeCode,usXorBit);
        usXorBit = _xorbit(0,8,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,0);

        //printf("%04x\n ",usDataTmp);

        usXorBit = (GRAB_BIT(usExeCode,9));
        usXorBit = _xorbit(10,16,usExeCode,usXorBit);
        usXorBit = _xorbit(1,8,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,1);

        usXorBit = (GRAB_BIT(usExeCode,8))^(GRAB_BIT(usExeCode,9));
        usXorBit = _xorbit(0,2,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,2);

        usXorBit = (GRAB_BIT(usExeCode,9))^(GRAB_BIT(usExeCode,10));
        usXorBit = _xorbit(1,3,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,3);

        usXorBit = (GRAB_BIT(usExeCode,10))^(GRAB_BIT(usExeCode,11));
        usXorBit = _xorbit(2,4,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,4);

        usXorBit = (GRAB_BIT(usExeCode,11))^(GRAB_BIT(usExeCode,12));
        usXorBit = _xorbit(3,5,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,5);

        usXorBit = (GRAB_BIT(usExeCode,12))^(GRAB_BIT(usExeCode,13));
        usXorBit = _xorbit(4,6,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,6);

        usXorBit = (GRAB_BIT(usExeCode,13))^(GRAB_BIT(usExeCode,14));
        usXorBit = _xorbit(5,7,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,7);

        usXorBit = (GRAB_BIT(usExeCode,0));
        usXorBit = _xorbit(14,16,usExeCode,usXorBit);
        usXorBit = _xorbit(6,8,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,8);

        usXorBit = (GRAB_BIT(usExeCode,1))^(GRAB_BIT(usExeCode,15))^(GRAB_BIT(ptr[i],7));

        usDataTmp = _writebit(usDataTmp,usXorBit,9);

        usDataTmp &= (~(0x0001 << 10));
        usDataTmp |= (GRAB_BIT(usExeCode,2))<<10;

        usDataTmp &= (~(0x0001 << 11));
        usDataTmp |= (GRAB_BIT(usExeCode,3))<<11;

        usDataTmp &= (~(0x0001 << 12));
        usDataTmp |= (GRAB_BIT(usExeCode,4))<<12;

        usDataTmp &= (~(0x0001 << 13));
        usDataTmp |= (GRAB_BIT(usExeCode,5))<<13;

        usDataTmp &= (~(0x0001 << 14));
        usDataTmp |= (GRAB_BIT(usExeCode,6))<<14;

        usXorBit = (GRAB_BIT(usExeCode,7));
        usXorBit = _xorbit(8,16,usExeCode,usXorBit);
        usXorBit = _xorbit(0,8,ptr[i],usXorBit);

        usDataTmp = _writebit(usDataTmp,usXorBit,15);

        usExeCode = usDataTmp;
        //printf("0x%04x\n ",usExeCode);
        //getch();
    }

    //printf("0x%04x ",usExeCode);
    //printf("usCheckSum = 0x%04x\n",usCheckSum);
//    g_usLcdCheckSum = usCheckSum;
    return usExeCode;
}
/*******************************************************************************
*   Name: _get_Lcd_crc16
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned short _get_Lcd_crc16()
{
    unsigned char ucTemp;
    unsigned short usAddr;
    unsigned char ucAddrH;
    unsigned char ucAddrL;
    unsigned char ucParaOffSet;
    unsigned short usIdx = 0;
    unsigned short usParaNum = 0;

    unsigned long ulCodeLen;
    unsigned long g_ulBufLen;
    unsigned long ulBufOffset = 0;
    unsigned char * pucLcdCrcbuf; // for calculate lcd crc
    
    unsigned short usLcd_crc;
    FILE * fp_bin;
    unsigned char auc_infoBuf[8];

    
    //内存申请
    g_ulBufLen = 0x2000;//BIN_INFO_START_ADDR + BIN_INFO_SZ;
    pucLcdCrcbuf = malloc(g_ulBufLen);
    if (NULL == pucLcdCrcbuf)  //not enough memory
    {
        return -1;
    }
    memset(pucLcdCrcbuf, 0xff, g_ulBufLen);
    //end

    fopen_s(&fp_bin,"./lcd_cfg.v", "rb");
    if (NULL == fp_bin)
    {
        return -1;
    }

    //前面固定8Byte，不计入CRC范围
    fread(auc_infoBuf, 1, 8, fp_bin);
    ulCodeLen = (auc_infoBuf[0] << 8) + auc_infoBuf[1];

    usIdx = 0;
    while ( !feof(fp_bin))
    {
        ucTemp = fgetc(fp_bin);

        if (usIdx == 0)
        {
            ucAddrH = ucTemp;
            pucLcdCrcbuf[ulBufOffset++] = ucTemp;
            usIdx = 1;
        }
        else if (usIdx == 1)
        {
            ucAddrL = ucTemp;
            usIdx = 2;
        }
        else if (usIdx == 2)
        {
            usParaNum = ucTemp;
            ucParaOffSet = 0;
            usIdx = 3;
        }
        else if (usIdx == 3)
        {

            pucLcdCrcbuf[ulBufOffset++] = ucTemp + ucAddrL + ucParaOffSet;//参数+偏移地址，只取低八位
            if (ucParaOffSet < usParaNum - 1)
            {
                ucParaOffSet++;
            }
            else
            {
                usIdx = 0;
                ucAddrH = 0;
                ucAddrL = 0;
            }
        }
    }

    if ((usIdx == 1)||(usIdx == 2))    //异常终止去掉地址位
    {
        ulBufOffset --;
    }
    fclose(fp_bin);

    usLcd_crc = _Lcd_crc16_cal(pucLcdCrcbuf,ulBufOffset);
    return usLcd_crc;
}
/*******************************************************************************
*   Name: _file_get_len
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _file_get_len(const char * sz_bin_file)
{
    int i_result = 0;
    FILE * fp_bin;
    unsigned char uc_buf[256];
    size_t z_temp;


    fopen_s(&fp_bin,sz_bin_file, "rb");
    if (NULL == fp_bin)
    {
        printf("binmerge: can't open file %s\n",sz_bin_file);
        return -1;
    }


    while ( !feof(fp_bin))
    {
        z_temp = fread(uc_buf, 1, 256, fp_bin);
        i_result += z_temp;
    }

    fclose(fp_bin);

    return i_result;
}

/*******************************************************************************
*   Name: _output_i_file
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _output_i_file(unsigned char * puc_buf, int i_len, const char * sz_i_file)
{

    FILE * fp_i;
    int i;
    unsigned char uc_data;

    fopen_s(&fp_i,sz_i_file, "w");
    if (NULL == fp_i)
    {
        printf("binmerge: can't open file %s\n",sz_i_file);
        return -1;
    }

    for (i =0; i <i_len; i++)
    {
        uc_data = puc_buf[i];
        if (uc_data >= 16)
        {
            fprintf(fp_i, "0x%x,", uc_data);
        }
        else
        {
            fprintf(fp_i, "0x%x, ", uc_data);
        }

        if ( (i+1) % 16 == 0)
        {
            fprintf(fp_i,"\n");
        }
    }

    fclose(fp_i);
    return 0;
}

/*******************************************************************************
*   Name: _get_line
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _get_line(FILE * fp, char * pc_line)
{
    int i_idx = 0;
    char c_cur;

    if (NULL == fp || NULL== pc_line)
    {
        return 0;
    }

    while (!feof(fp))
    {
        c_cur = fgetc(fp);
        pc_line[i_idx ++] = c_cur;
        if ('\n' == c_cur)
        {
            break;
        }
    }

    if (i_idx > 0)
    {
        if (i_idx == 1 && pc_line[0] == -1)
        {
            return 0;
        }
        else
        {
            pc_line[i_idx] = '\0';
            return 1;
        }

    }
    else
    {
        return 0;
    }
}

/*******************************************************************************
*   Name: _is_sperator
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _is_sperator(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************
*   Name: _is_digit_char
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _is_digit_char(char c)
{
    if (c == '0' || c == 'x' || c == 'X' || (c >= '0' && c <= '9') || (c >= 'A' && c<='F') || (c >= 'a' && c<='f'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************
*   Name: _c_to_int
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _c_to_int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'a' && c<='f')
    {
        return (10 + c - 'a');
    }
    else if (c >= 'A' && c<='F')
    {
        return (10 + c - 'A');
    }
    else
    {
        return -1;
    }
}

/*******************************************************************************
*   Name: _str_to_int
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _str_to_int(char * sz_str)
{
    int i_sum;
    int i_len;
    int i_factor;
    int i;
    int i_c;

    i_sum = 0;
    i_factor = 1;
    if (sz_str[0] == '0' && (sz_str[1] == 'x' || sz_str[1] == 'X'))
    {
        //hex format
        i_len = strlen(sz_str);
        for (i = i_len - 1; i>=2; i--)
        {
            i_c = _c_to_int(sz_str[i]);
            if (i_c < 0)
            {
                return -1;
            }
            i_sum += i_c * i_factor;
            i_factor = i_factor * 16;
        }
    }
    else
    {
        //decimal format
        i_len = strlen(sz_str);
        for (i = i_len - 1; i>=0; i--)
        {
            if (sz_str[i] < '0' || sz_str[i] > '9')
            {
                return -1;
            }
            i_c = _c_to_int(sz_str[i]);
            if (i_c < 0)
            {
                return -1;
            }
            i_sum += i_c * i_factor;
            i_factor = i_factor * 10;
        }
    }
    return i_sum;
}

/*******************************************************************************
*   Name: _get_str
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _get_str(char * sz_str, const char * sz_line_buf, int * pi_line_idx)
{
    int i;
    int i_count;

    if (NULL == pi_line_idx)
    {
    }

    i = * pi_line_idx;
    i_count = 0;

    //filter blank character
    while (i < MAX_LINE_BUF_SIZE && i_count < MAX_STR_SIZE && _is_sperator(sz_line_buf[i]))
    {
        i++;
    }

    //get the string.
    while (i < MAX_LINE_BUF_SIZE && i_count < MAX_STR_SIZE && !_is_sperator(sz_line_buf[i]))
    {
        sz_str[i_count] = sz_line_buf[i];
        i++;
        i_count ++;
    }

    sz_str[i_count] = '\0';
    * pi_line_idx = i;

    return 1;
}


/*******************************************************************************
*   Name: _get_digit_str
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _get_digit_str(char * sz_str,const char * sz_line_buf, int * pi_line_idx)
{
    int i;
    int i_count;

    if (NULL == pi_line_idx)
    {
    }

    i = * pi_line_idx;
    i_count = 0;

    //filter blank character
    while (i < MAX_LINE_BUF_SIZE && i_count < MAX_STR_SIZE && _is_sperator(sz_line_buf[i]))
    {
        i++;
    }

    //get the string.
    while (i < MAX_LINE_BUF_SIZE && i_count < MAX_STR_SIZE && _is_digit_char(sz_line_buf[i]))
    {
        sz_str[i_count] = sz_line_buf[i];
        i++;
        i_count ++;
    }

    sz_str[i_count] = '\0';
    * pi_line_idx = i;

    return 1;
}

int usCheckDefineCnt = 0; /* 关键字出现次数 */

/*******************************************************************************
*   Name: _get_value_CheckDefine
*  Brief: 检查关键字是否出现多于1次的情况
*  Input:
* Output:
* Return:
*******************************************************************************/
int _get_value_CheckDefine(const char * sz_file, const char * sz_field_name, unsigned char * puc_value)
{
    char sz_line_buf[MAX_LINE_BUF_SIZE + 1];
    char sz_str[MAX_STR_SIZE + 1];
    int  i_line_idx;
    int  i_value;

    FILE * fp;

    fopen_s(&fp,sz_file, "r");
    if (NULL == fp)
    {
        return 0;
    }

    /* 初始化 */
    usCheckDefineCnt = 0;

    while (_get_line(fp, sz_line_buf))
    {
        i_line_idx = 0;

        //check #define
        _get_str(sz_str, sz_line_buf, &i_line_idx);
        if (strcmp(sz_str, "#define") == 0)
        {
            _get_str(sz_str, sz_line_buf, &i_line_idx);
            if (strcmp(sz_str,sz_field_name) == 0)
            {
                _get_digit_str(sz_str, sz_line_buf, &i_line_idx);
                i_value = _str_to_int(sz_str);
                if (i_value < 0)
                {
                    fclose(fp);
                    return 0;
                }
                else
                {
                    if (puc_value != NULL)
                    {
                        * puc_value = (unsigned char)(i_value);
                    }
                    //fclose(fp);

                    usCheckDefineCnt++;

                    /* 此时进行第二次检查，看是否还有能够匹配的 */
                    if (usCheckDefineCnt > 1)
                    {
                        return 0xff;
                    }

                }

            }
        }
    }

    fclose(fp);
    return 1;
}
/*******************************************************************************
*   Name: _get_value
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _get_value(const char * sz_file, const char * sz_field_name, unsigned char * puc_value)
{
    char sz_line_buf[MAX_LINE_BUF_SIZE + 1];
    char sz_str[MAX_STR_SIZE + 1];
    int  i_line_idx;
    int  i_value;

    FILE * fp;

    fopen_s(&fp,sz_file, "r");
    if (NULL == fp)
    {
        printf("binmerge: can't open file %s\n",sz_file);
        return 0;
    }

    while (_get_line(fp, sz_line_buf))
    {
        i_line_idx = 0;

        //check #define
        _get_str(sz_str, sz_line_buf, &i_line_idx);
        if (strcmp(sz_str, "#define") == 0)
        {
            _get_str(sz_str, sz_line_buf, &i_line_idx);
            if (strcmp(sz_str,sz_field_name) == 0)
            {
                _get_digit_str(sz_str, sz_line_buf, &i_line_idx);
                i_value = _str_to_int(sz_str);
                if (i_value < 0)
                {
                    fclose(fp);
                    return 0;
                }
                else
                {
                    if (puc_value != NULL)
                    {
                        * puc_value = (unsigned char)(i_value);
                    }
                    fclose(fp);
                    return 1;
                }

            }
        }
    }

    fclose(fp);
    return 0;
}

/*******************************************************************************
*   Name: _get_define_str
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int _get_define_str(const char * sz_file,  const char * sz_field_name, char * sz_buf)
{
    char sz_line_buf[MAX_LINE_BUF_SIZE + 1];
    char sz_str[MAX_STR_SIZE + 1];
    int  i_line_idx;
    int  i_len;

    FILE * fp;

    fopen_s(&fp,sz_file, "r");
    if (NULL == fp)
    {
        printf("binmerge: can't open file %s\n",sz_file);
        return 0;
    }

    while (_get_line(fp, sz_line_buf))
    {
        i_line_idx = 0;

        //check #define
        _get_str(sz_str, sz_line_buf, &i_line_idx);
        if (strcmp(sz_str, "#define") == 0)
        {
            _get_str(sz_str, sz_line_buf, &i_line_idx);
            if (strcmp(sz_str,sz_field_name) == 0)
            {
                _get_str(sz_str, sz_line_buf, &i_line_idx);
                i_len = strlen(sz_str);
                if (sz_str[0] == '"' && sz_str[i_len - 1] == '"')
                {
                    sz_str[i_len - 1] = '\0';
                    strcpy_s(sz_buf, i_len-1, sz_str + 1);
                    return 1;
                }

            }
        }
    }

    fclose(fp);
    return 0;
}

/*******************************************************************************
*   Name: _get_slaveaddr
*  Brief: I2C slave地址
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_slaveaddr_CheckDefine()
{
    unsigned char tmp;
    unsigned char uc_slave_addr;
    int ret = 1;

    uc_slave_addr = FTS_I2C_SLAVE;

    /* I2C_SLAVE_ADDR */
    if (0xff == _get_value_CheckDefine(FILE_CONFIG, "I2C_SLAVE_ADDR", &tmp))
    {
        printf("Error I2C_SLAVE_ADDR 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* IO_LEVEL_SELECTION */
    if (0xff == _get_value_CheckDefine(FILE_CONFIG, "IO_LEVEL_SELECTION", &tmp))
    {
        printf("Error IO_LEVEL_SELECTION 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* RV_G_VENDORID */
    if (0xff == _get_value_CheckDefine(FILE_CONFIG, "RV_G_VENDORID", &tmp))
    {
        printf("Error RV_G_VENDORID 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* RV_G_FIRMID */
    if (0xff == _get_value_CheckDefine(FILE_CONFIG, "RV_G_FIRMID", &tmp))
    {
        printf("Error RV_G_FIRMID 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* RV_G_BOOT_ID_HIGH */
    if (0xff == _get_value_CheckDefine(FILE_SYSCFG, "RV_G_BOOT_ID_HIGH", &tmp))
    {
        printf("Error RV_G_BOOT_ID_HIGH 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* RV_G_BOOT_ID_LOW */
    if (0xff == _get_value_CheckDefine(FILE_SYSCFG, "RV_G_BOOT_ID_LOW", &tmp))
    {
        printf("Error RV_G_BOOT_ID_LOW 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* RV_G_ROM_SPI_DIV */
    if (0xff == _get_value_CheckDefine(FILE_SYSCFG, "RV_G_ROM_SPI_DIV", &tmp))
    {
        printf("Error RV_G_ROM_SPI_DIV 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* RV_G_ROM_SYS_CLK */
    if (0xff == _get_value_CheckDefine(FILE_SYSCFG, "RV_G_ROM_SYS_CLK", &tmp))
    {
        printf("Error RV_G_ROM_SYS_CLK 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* RV_G_ROM_XBUS_DIV */    
    if (0xff == _get_value_CheckDefine(FILE_SYSCFG, "RV_G_ROM_XBUS_DIV", &tmp))
    {
        printf("Error RV_G_ROM_XBUS_DIV 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    /* _LCD_RELOAD_EN */
    if (0xff == _get_value_CheckDefine(FILE_CONFIG, "_LCD_RELOAD_EN", &tmp))
    {
        printf("Error _LCD_RELOAD_EN 超过2行，请保持一行宏定义!!!!! \n");
        ret = -1;
    }

    return ret;
}

/*******************************************************************************
*   Name: _get_slaveaddr
*  Brief: I2C slave地址
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_slaveaddr()
{
    unsigned char tmp;
    unsigned char uc_slave_addr;

    uc_slave_addr = FTS_I2C_SLAVE;

    if (_get_value(FILE_CONFIG, "I2C_SLAVE_ADDR", &tmp))
    {
        uc_slave_addr = tmp;
    }

    return uc_slave_addr;
}


/*******************************************************************************
*   Name: _get_iovoltage
*  Brief: IO电压
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_iovoltage()
{
    unsigned char uc_io_voltage;

    uc_io_voltage = 0x00;

    //Get IO Voltage
    if (_get_value(FILE_CONFIG, "IO_LEVEL_SELECTION", &uc_io_voltage))
    {

    }

    return uc_io_voltage;
}

/*******************************************************************************
*   Name: _get_vendor_id
*  Brief: Vendor ID
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_vendor_id()
{
    unsigned char uc_vendor_id;

    //get I2C Slave Addr
    if (_get_value(FILE_CONFIG, "RV_G_VENDORID", &uc_vendor_id))   //vender ID for panel factory
    {
    }
    else
    {
        uc_vendor_id = 0xff;
    }

    return uc_vendor_id;
}

/*******************************************************************************
*   Name: _get_version
*  Brief: FW版本号
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_version()
{
    unsigned char uc_version;

    //get I2C Slave Addr
    if (_get_value(FILE_PARAMETER, "RV_G_FIRMID", &uc_version))
    {

    }
    else
    {
        uc_version = 0xFF;
    }

    return uc_version;
}

/*******************************************************************************
*   Name: _get_boot_id
*  Brief: App Boot ID
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned int _get_boot_id()
{
    unsigned char ucTmp;
    unsigned int usBootId;

    //get I2C Slave Addr
    if (_get_value(FILE_SYSCFG, "RV_G_BOOT_ID_HIGH", &ucTmp))
    {

    }
    else
    {
        ucTmp = 0xFF;
    }

    usBootId = ucTmp*256;


    //get I2C Slave Addr
    if (_get_value(FILE_SYSCFG, "RV_G_BOOT_ID_LOW", &ucTmp))
    {

    }
    else
    {
        ucTmp = 0xFF;
    }

    usBootId += ucTmp;

    printf("BootId:%04X\n", usBootId);

    return usBootId;
}

/*******************************************************************************
*   Name: _get_spi_div
*  Brief: ROM搬运时的spi时钟
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_spi_div()
{
    unsigned char ucTmp;

    //get I2C Slave Addr
    if (_get_value(FILE_SYSCFG, "RV_G_ROM_SPI_DIV", &ucTmp))
    {

    }
    else
    {
        ucTmp = 0x01;//6分频
    }

    return ucTmp;
}

/*******************************************************************************
*   Name: _get_sys_clk
*  Brief: ROM搬运时的flash时钟
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_sys_clk()
{
    unsigned char ucTmp;

    //get I2C Slave Addr
    if (_get_value(FILE_SYSCFG, "RV_G_ROM_SYS_CLK", &ucTmp))
    {

    }
    else
    {
        ucTmp = 0x01;//24M
    }

    return ucTmp;
}

/*******************************************************************************
*   Name: _get_XBUS_clk
*  Brief: Rom阶段的XBUS时钟分频
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_XBUS_clk()
{
    unsigned char ucTmp;

    //get I2C Slave Addr
    if (_get_value(FILE_SYSCFG, "RV_G_ROM_XBUS_DIV", &ucTmp))
    {

    }
    else
    {
        ucTmp = 0x01;  //默认4分频
    }

    return ucTmp;
}

/*******************************************************************************
*   Name: _get_spi_io_mode
*  Brief: 
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_spi_io_mode()
{
    unsigned char ucTmp;

    if (_get_value(FILE_SYSCFG, "RV_G_ROM_SPI_MODE", &ucTmp))
    {

    }
    else
    {
        ucTmp = 0x00;  //默认std
    }

    return ucTmp;
}

/*******************************************************************************
*   Name: _get_project_code
*  Brief: 项目名称
*  Input:
* Output:
* Return:
*******************************************************************************/
int _get_project_code(char * sz_buf)
{
    if (_get_define_str(FILE_CONFIG, "CFG_PROJECT_CODE", sz_buf))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/*******************************************************************************
*   Name: _get_customer_code
*  Brief: 用户码
*  Input:
* Output:
* Return:
*******************************************************************************/
int _get_customer_code(char * sz_buf)
{
    if (_get_define_str(FILE_CONFIG, "CFG_CUSTOMER_CODE", sz_buf))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************
*   Name: _get_LcdReladFlag
*  Brief: LCD Reload信号
*  Input:
* Output:
* Return:
*******************************************************************************/
unsigned char _get_LcdReladFlag()
{
    unsigned char tmp = 0;

    _get_value(FILE_CFG, "_LCD_RELOAD_EN", &tmp);

    if (tmp == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************
*   Name: AppCheckReDefine
*  Brief: 检查同一个文件的宏定义重复定义
*  Input:
* Output:
* Return:
*******************************************************************************/
signed char AppCheckReDefine()
{
    int ret;
    
    if (1 == _get_slaveaddr_CheckDefine())
    {
        ret = 1;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

/*******************************************************************************
*   Name: main
*  Brief:
*  Input:
* Output:
* Return:
*******************************************************************************/
int main(int argc, char * argv[])
{
    char * sz_src;
    char * sz_app;
    char * sz_all;

    int  g_ssLcdLen;   //original binary size
    int  g_ssAppLen;   //original binary size
    long g_slBufLen;   //output binary size
    int  i;
    unsigned char * pucAllbuf; // all.bin
    unsigned char * pucAppbuf; // app.bin
	unsigned char * pucLcdbuf; // lcd_cfg.bin 
    FILE          * fp_bin;
    int  b_output_bin = 1;
    int  i_app_bin_size = 0;

	unsigned char uc_spi_dual = 0;
    unsigned char uc_slaveaddr = 0xff;

    unsigned char uc_iovoltage = 0xff;
    unsigned char uc_vendor_id = 0xff;
    unsigned char ucSpiDiv = 0x01;
    unsigned char ucSysClk = 0x01;
    unsigned char ucXbusClk = 0x01;
    unsigned char uc_version = 0xff;
    unsigned int ucBootId = 0xFFFF;   /* boot id */

    unsigned short usPart1_crc = 0xFFFF;
    unsigned short usPart2_crc = 0xFFFF;
    unsigned short usLcd_crc = 0xFFFF;
	unsigned short usFlash_crc = 0xFFFF;
    char          sz_project_code[MAX_STR_SIZE + 1];
    char          sz_customer_code[MAX_STR_SIZE + 1];
    unsigned char b_has_project_code;
    unsigned char b_has_customer_code;

	unsigned char Spi_Div_Tab[4] = { 4,6,8,12 };
	unsigned char SysClk_Tab[2] = { 48,24};

    char io_info18[5] = "1.8V";
    char io_info33[5] = "3.3V";
    char io_info[5];

    /* CfgPanelPara.h文件检查，当同一个宏定义出现2行则提示error */
    if ((-1) == AppCheckReDefine())
    {
        /* 退出执行 */
        printf("bin_merge: AppCheckReDefine error\n");
        return -1;
    }

    //-----------------------------------------------------------
    //输入参数检测
    //输入 XXX.bin生成 XXX_app.bin XXX_all.bin
    if (argc == 3)
    {
        sz_src  = argv[1];
        sz_app  = argv[2];
    }
    else if (argc == 4)
    {
        sz_src  = argv[1];
        sz_app  = argv[2];
        sz_all  = argv[3];
    }
    else
    {
        printf("[bin_merge app.bin ft_all.bin]\n");
        return -1;
    }

    //文件类型,判断是否生成.i文件
    if (argc == 3)
    {
        i = strlen(sz_app);
        if (  (i > 2)
              &&(sz_app[i-1] == 'i' || sz_app[i-1] == 'I')
              &&(sz_app[i-2] == '.') )
        {
            b_output_bin = 0;  //is I file
        }
    }

    //内存申请
    g_slBufLen = FLASH_FILE_BUF_SIZE;//BIN_INFO_START_ADDR + BIN_INFO_SZ;
    pucAllbuf = malloc(g_slBufLen);
    if (NULL == pucAllbuf)  //not enough memory
    {
        printf("binmerge: not enough memory\n");
        return -1;
    }
    memset(pucAllbuf, 0xff, g_slBufLen);

    //--------------------------------------------------------------------------
    //lcd配置文件加载体
    g_ssLcdLen = _file_get_len(FILE_LCD_CFG);
	if(g_ssLcdLen%2==1)g_ssLcdLen+=1;
    fp_bin = NULL;
    //检测文件是否有效
    if ((g_ssLcdLen > 0) && (g_ssLcdLen <= LCD_REG_MAX_SIZE))
    {
        fopen_s(&fp_bin,FILE_LCD_CFG, "rb");
    }

    if (NULL != fp_bin)
    {
        fread(pucAllbuf+4, g_ssLcdLen, 1, fp_bin);
        fclose(fp_bin);
    }
	
	
	
    //--------------------------------------------------------------------------
    //load app binary打开XXX.bin
    g_ssAppLen = _file_get_len(sz_src);

    //检测文件是否有效
    if (g_ssAppLen <= 0 || g_ssAppLen > APP_FILE_MAX_SIZE)  //invliad size
    {
        free(pucAllbuf);
        printf("ERROR: FW size is too large, the limit is 0x%x(%d),  current is 0x%x(%d)\n",
               APP_FILE_MAX_SIZE,APP_FILE_MAX_SIZE,g_ssAppLen,g_ssAppLen);
        printf("Creating bin files failed!!!\n");
        return -4;
    }
    fopen_s(&fp_bin,sz_src, "rb");
    if (NULL == fp_bin)
    {
        free(pucAllbuf);
        printf("binmerge: can't open file %s\n",sz_src);
        return -3;
    }
    fread(pucAllbuf+FLASH_APP_START, g_ssAppLen, 1, fp_bin);
    fclose(fp_bin);

    //对长度进行检测，如果奇数个，则补一个字节，FT5003要求
    if (g_ssAppLen % 2 == 1)
    {
        g_ssAppLen++;
    }

    // CfgGlobal.h 文件中读FW配置信息
	uc_spi_dual	 = _get_spi_io_mode();
    uc_slaveaddr = _get_slaveaddr();
    uc_iovoltage = _get_iovoltage();
    uc_vendor_id = _get_vendor_id();
    uc_version   = _get_version();
    ucBootId  = _get_boot_id();

    ucSpiDiv = _get_spi_div();
    ucSysClk = _get_sys_clk();
    ucXbusClk = _get_XBUS_clk();
    s_bLcdValid = _get_LcdReladFlag();
    usPart1_crc = _get_crc16(pucAllbuf+ALL_ADDR_PART1_START,ALL_ADDR_PART1_LEN);
    usPart2_crc = _get_crc16(pucAllbuf+ALL_ADDR_PART2_START,(g_ssAppLen-(ALL_ADDR_PART1_LEN)-(APP_VERIF_LEN)-(FW_CFG_INFO_SIZE)));
    if ((g_ssLcdLen > 0) && (g_ssLcdLen <= LCD_REG_MAX_SIZE))
    {
        usLcd_crc = _get_Lcd_crc16();
		
    }
    //app 长度信息
    pucAllbuf[ADDR_APP_LEN_L_H] = g_ssAppLen >> 8;
    pucAllbuf[ADDR_APP_LEN_L_L] = g_ssAppLen & 0xff;
    pucAllbuf[ADDR_APP_LEN_L_H_NE] = (~g_ssAppLen) >> 8;
    pucAllbuf[ADDR_APP_LEN_L_L_NE] = (~g_ssAppLen) & 0xff;


    pucAllbuf[ADDR_PART1_ECC_H] = usPart1_crc >> 8;
    pucAllbuf[ADDR_PART1_ECC_NE_H] = ~(pucAllbuf[ADDR_PART1_ECC_H]);
    pucAllbuf[ADDR_PART1_ECC_L] = usPart1_crc & 0xff;
    pucAllbuf[ADDR_PART1_ECC_NE_L] = ~(pucAllbuf[ADDR_PART1_ECC_L]);
    pucAllbuf[ADDR_PART2_ECC_H] = usPart2_crc >> 8;
    pucAllbuf[ADDR_PART2_ECC_NE_H] = ~(pucAllbuf[ADDR_PART2_ECC_H]);
    pucAllbuf[ADDR_PART2_ECC_L] = usPart2_crc & 0xff;
    pucAllbuf[ADDR_PART2_ECC_NE_L] = ~(pucAllbuf[ADDR_PART2_ECC_L]);
	pucAllbuf[ADDR_PANEL_ID ] = uc_vendor_id;
	pucAllbuf[ADDR_PANEL_ID_NE ] = ~uc_vendor_id;
    pucAllbuf[ADDR_VERSION] = uc_version;
    pucAllbuf[ADDR_VERSION_NE] = ~uc_version;

    pucAllbuf[ADDR_APP_LEN_H_H] = g_ssAppLen >> 24;
    pucAllbuf[ADDR_APP_LEN_H_L] = (g_ssAppLen>>16) & 0xff;
    pucAllbuf[ADDR_APP_LEN_H_H_NE] = (~g_ssAppLen) >> 24;
    pucAllbuf[ADDR_APP_LEN_H_L_NE] = ((~g_ssAppLen) >>16)& 0xff;

    pucAllbuf[ADDR_BOOT_ID_HIGH] = ucBootId/256;
    pucAllbuf[ADDR_BOOT_ID_LOW]  = ucBootId%256;

    i_app_bin_size = g_ssAppLen ;

    //--------------------------------------------------------------------------
    // FW config for _all.bin

    //Lcd Crc
    pucAllbuf[FLASH_LCD_CRC] = usLcd_crc >> 8;
    pucAllbuf[FLASH_LCD_CRC+1] = usLcd_crc & 0xFF;
	
    usFlash_crc=_get_crc16(pucAllbuf+4,g_ssLcdLen);
	g_ssLcdLen+=4;
	//usFlash len ,Crc
	pucAllbuf[0] = g_ssLcdLen >> 8;
    pucAllbuf[1] = g_ssLcdLen & 0xFF;
	
    pucAllbuf[2] = usFlash_crc >> 8;
    pucAllbuf[3] = usFlash_crc & 0xFF;
	
    //slave addr
    pucAllbuf[FW_CFG_INFO_ADDR + I2C_SLAVE_ID] = uc_slaveaddr;
    pucAllbuf[FW_CFG_INFO_ADDR + I2C_SLAVE_ID + 1] = ~uc_slaveaddr;

    //IO Voltage
    pucAllbuf[FW_CFG_INFO_ADDR + IO_VOLTAGE_ID] = uc_iovoltage;
    pucAllbuf[FW_CFG_INFO_ADDR + IO_VOLTAGE_ID + 1] = ~uc_iovoltage;

    //Vendor ID
    pucAllbuf[FW_CFG_INFO_ADDR + VENDOR_ID] = uc_vendor_id;
    pucAllbuf[FW_CFG_INFO_ADDR + VENDOR_ID + 1] = ~(uc_vendor_id);

    //SPI clk
    pucAllbuf[FW_CFG_INFO_ADDR + SPI_CLK_ID] = ucSpiDiv;
    pucAllbuf[FW_CFG_INFO_ADDR + SPI_CLK_ID + 1] = ~ ucSpiDiv;

    //sys clk
    pucAllbuf[FW_CFG_INFO_ADDR + SYS_CLK_ID] = ucSysClk;
    pucAllbuf[FW_CFG_INFO_ADDR + SYS_CLK_ID + 1] = ~ ucSysClk;

    //XBUS clk
    pucAllbuf[FW_CFG_INFO_ADDR + XBUS_CLK_ID] = ucXbusClk;
    pucAllbuf[FW_CFG_INFO_ADDR + XBUS_CLK_ID + 1] = ~ ucXbusClk;

    //SPI_IO_MODE
    pucAllbuf[FW_CFG_INFO_ADDR + SPI_IO_MODE_ID] = uc_spi_dual;
    pucAllbuf[FW_CFG_INFO_ADDR + SPI_IO_MODE_ID + 1] = ~uc_spi_dual;


    // LCD信号无效，则All中，设置LCD配置文件长度为0x00
    if (s_bLcdValid == 0x00)
    {
        // CodeSize
        pucAllbuf[0] = 0x00;
        pucAllbuf[1] = 0x00;

        // CRC
        pucAllbuf[2] = 0x00;
        pucAllbuf[3] = 0x00;
    }

    DBG_INFO("Flash-SPI = Div%d; ", Spi_Div_Tab[ucSpiDiv&0x03]);
    DBG_INFO("Flash-SYS = %dM; ", SysClk_Tab[ucSysClk&0x01]);
    DBG_INFO("Lcd-XBUS = Div%d\n", ucXbusClk);
    DBG_INFO("Lcd-Reload = %d, Len:0x%04X\n", s_bLcdValid, pucAllbuf[0]*256 + pucAllbuf[1]);

    //project code
    if (_get_project_code(sz_project_code))
    {
        b_has_project_code = 1;
    }
    else
    {
        strcpy_s(sz_project_code,PROJECT_CODE_LEN,"");
        b_has_project_code = 0;
    }
    // total size should not exceed CUSTOMER_CODE_LEN
    sz_project_code[PROJECT_CODE_LEN] = 0;
    strcpy_s(pucAllbuf + FW_CFG_INFO_ADDR + PRJ_NAME_ID, PROJECT_CODE_LEN, sz_project_code);

    //customer code
    if (_get_customer_code(sz_customer_code))
    {
        b_has_customer_code = 1;
    }
    else
    {
        strcpy_s(sz_customer_code,CUSTOMER_CODE_LEN, "");
        b_has_customer_code = 0;
    }
    sz_customer_code[CUSTOMER_CODE_LEN] = 0;
    strcpy_s(pucAllbuf + FW_CFG_INFO_ADDR + CUSTOMER_ID, CUSTOMER_CODE_LEN,sz_customer_code);

    //--------------------------------------------------------------------------
    // Only for information output
    if (uc_iovoltage)
    {
        memcpy(io_info,io_info33,5);
    }
    else
    {
        memcpy(io_info,io_info18,5);
    }

    //I2C接口
    if (_suc_i2c_enable)
    {
        printf("bin_merge(FT8836) version is %s: project_code=%s, customer_code=%s, app_binary_size = %d byte,fw_version = 0x%x, I2C_SALVE_ADDR = 0x%x, IO_VOLTAGE = %s, VEDNOR_ID=0x%x\n",
               BIN_MERGE_VERSION, sz_project_code, sz_customer_code, i_app_bin_size, uc_version, uc_slaveaddr, io_info, uc_vendor_id);
    }
    else
    {
        printf("bin_merge(FT8836) version is %s:  project_code=%s, customer_code=%s, app_binary_size = %d byte,fw_version = 0x%x, SPIMODE = 0x%x, IO_VOLTAGE = %s, VENDOR_ID=0x%x\n",
               BIN_MERGE_VERSION,sz_project_code, sz_customer_code, i_app_bin_size, uc_version, uc_spi_dual, io_info, uc_vendor_id);
    }

    //--------------------------------------------------------------------------
    // 配置区备份
    memcpy(&pucAllbuf[FW_CFG_INFO_BKUP_ADDR],
           &pucAllbuf[FW_CFG_INFO_ADDR],
           FW_CFG_INFO_SIZE);
    
    //--------------------------------------------------------------
    //新文件生成
    // generate app.bin or app.i

    //申请内存
    pucAppbuf = malloc(i_app_bin_size);
    if (NULL == pucAppbuf)  //not enough memory
    {
        free(pucAllbuf);
        printf("binmerge: not enough memory\n");
        return -6;
    }

    //code区
    memcpy(pucAppbuf,pucAllbuf + FLASH_APP_START,i_app_bin_size);

    //--------------------------------------------------------------------------
    // xxx_app.bin
    if (b_output_bin)
    {
        fopen_s(&fp_bin,sz_app, "wb");
        if (NULL == fp_bin)
        {
            free(pucAllbuf);
            free(pucAppbuf);
            printf("binmerge: can't open file %s\n",sz_app);
            return -4;
        }
        fwrite(pucAppbuf, 1, i_app_bin_size, fp_bin);
        fclose(fp_bin);
    }
    else  //.i文件
    {
        _output_i_file(pucAppbuf, i_app_bin_size, sz_app);
    }

    free(pucAppbuf);

    //--------------------------------------------------------------------------
    // XXX_all.bin生成
    if (argc == 4)
    {
        fopen_s(&fp_bin,sz_all, "wb");
        if (NULL == fp_bin)
        {
            printf("binmerge: can't open file %s\n",sz_all);
            free(pucAllbuf);
            return -4;
        }
        fwrite(pucAllbuf, 1, i_app_bin_size+FLASH_APP_START, fp_bin);
        fclose(fp_bin);
    }

	//新文件生成
	// generate lcd_cfg.bin 

	//申请内存
	pucLcdbuf = malloc(LCD_CONFIG_LEN);
	if (NULL == pucLcdbuf)  //not enough memory
	{
		free(pucAllbuf);
		printf("binmerge: not enough memory\n");
		return -6;
	}
	//code区
	memcpy(pucLcdbuf, pucAllbuf, LCD_CONFIG_LEN);

	//--------------------------------------------------------------------------
	// lcd_cfg.bin 

	fopen_s(&fp_bin, "lcd_cfg.bin", "wb");
	if (NULL == fp_bin)
	{
		free(pucAllbuf);
		free(pucLcdbuf);
		printf("binmerge: can't open file %s\n", "lcd_cfg.bin");
		return -4;
	}
	fwrite(pucLcdbuf, 1, LCD_CONFIG_LEN, fp_bin);
	fclose(fp_bin);
	
	free(pucLcdbuf);
	//-------------------------------------------------------------------------

    free(pucAllbuf);

    return 0;

}

