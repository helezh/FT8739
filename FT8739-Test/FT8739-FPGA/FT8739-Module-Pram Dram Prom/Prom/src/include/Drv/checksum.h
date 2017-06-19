/*
 * Library: libcrc
 * File:    include/checksum.h
 * Author:  Lammert Bies
 *
 * This file is licensed under the MIT License as stated below
 *
 * Copyright (c) 1999-2016 Lammert Bies
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Description
 * -----------
 * The headerfile include/checksum.h contains the definitions and prototypes
 * for routines that can be used to calculate several kinds of checksums.
 */

#ifndef DEF_LIBCRC_CHECKSUM_H
#define DEF_LIBCRC_CHECKSUM_H

#include <stdio.h>
#include "CfgGlobal.h"
/*
 * #define CRC_POLY_xxxx
 *
 * The constants of the form CRC_POLY_xxxx define the polynomials for some well
 * known CRC calculations.
 */

#define CRC_POLY_16         0xA001
#define CRC_POLY_32         0xEDB88320L
#define CRC_POLY_CCITT      0x1021
#define CRC_POLY_DNP        0xA6BC
#define CRC_POLY_KERMIT     0x8408
#define CRC_POLY_SICK       0x8005

/*
 * #define CRC_START_xxxx
 *
 * The constants of the form CRC_START_xxxx define the values that are used for
 * initialization of a CRC value for common used calculation methods.
 */

#define CRC_START_8 0x00
#define CRC_START_16    0x0000
#define CRC_START_MODBUS    0xFFFF
#define CRC_START_XMODEM    0x0000
#define CRC_START_CCITT_1D0F    0x1D0F
#define CRC_START_CCITT_FFFF    0xFFFF
#define CRC_START_KERMIT    0xFFFF//0x0000
#define CRC_START_SICK  0x0000
#define CRC_START_DNP   0x0000
#define CRC_START_32    0xFFFFFFFFL

/*
 * Prototype list of global functions
 */
#if 0
unsigned char *		checksum_NMEA(     const unsigned char *input_str, unsigned char *result  );
unsigned char			crc_8(             const unsigned char *input_str, size_t num_bytes       );
unsigned short		crc_16(            const unsigned char *input_str, size_t num_bytes       );
unsigned long		crc_32(            const unsigned char *input_str, size_t num_bytes       );
unsigned short		crc_ccitt_1d0f(    const unsigned char *input_str, size_t num_bytes       );
unsigned short		crc_ccitt_ffff(    const unsigned char *input_str, size_t num_bytes       );
unsigned short		crc_dnp(           const unsigned char *input_str, size_t num_bytes       );
unsigned short		crc_kermit(        const unsigned char *input_str, size_t num_bytes       );
unsigned short		crc_modbus(        const unsigned char *input_str, size_t num_bytes       );
unsigned short		crc_sick(          const unsigned char *input_str, size_t num_bytes       );
unsigned short		crc_xmodem(        const unsigned char *input_str, size_t num_bytes       );
unsigned char			update_crc_8(      unsigned char  crc, unsigned char c                          );
unsigned short		update_crc_16(     unsigned short crc, unsigned char c                          );
unsigned long		update_crc_32(     unsigned long crc, unsigned char c                          );
unsigned short		update_crc_ccitt(  unsigned short crc, unsigned char c                          );
unsigned short		update_crc_dnp(    unsigned short crc, unsigned char c                          );
unsigned short		update_crc_kermit( unsigned short crc, unsigned char c                          );
unsigned short		update_crc_sick(   unsigned short crc, unsigned char c, unsigned char prev_byte );
#endif  
unsigned short  crc_kermit(const unsigned char *input_str, unsigned short num_bytes);
unsigned short  update_crc_kermit(unsigned short crc, unsigned char c );
#endif  // DEF_LIBCRC_CHECKSUM_H
