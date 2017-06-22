/*
 * Library: libcrc
 * File:    src/crckrmit.c
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
 * The source file src/crckrmit.c contains routines which calculate the CRC
 * Kermit cyclic redundancy check value for an incomming byte string.
 */

#include "CfgGlobal.h"
#include "checksum.h"

static void		init_crc_tab( void );

static BOOLEAN		crc_tab_init = FALSE;
static unsigned short	XRAM	crc_tab[256];

/*
 * unsigned short crc_kermit( const unsigned char *input_str, size_t num_bytes );
 *
 * The function crc_kermit() calculates the 16 bits Kermit CRC in one pass for
 * a byte string of which the beginning has been passed to the function. The
 * number of bytes to check is also a parameter.
 */

unsigned short crc_kermit( const unsigned char *input_str, unsigned short num_bytes ) 
{

	unsigned short crc;
	unsigned short tmp;
	unsigned short short_c;
	unsigned short low_byte;
	unsigned short high_byte;
	const unsigned char *ptr;
	unsigned short a;

	if ( ! crc_tab_init ) init_crc_tab();

	crc = CRC_START_KERMIT;
	ptr = input_str;

	if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

		short_c = 0x00ff & (unsigned short) *ptr;
		tmp     =  crc       ^ short_c;
		crc     = (crc >> 8) ^ crc_tab[ tmp & 0xff ];

		ptr++;
	}

	//low_byte  = (crc & 0xff00) >> 8;
	//high_byte = (crc & 0x00ff) << 8;
	//crc       = low_byte | high_byte;

	return crc;

}  /* crc_kermit */

/*
 * unsigned short update_crc_kermit( unsigned short crc, unsigned char c );
 *
 * The function update_crc_kermit() calculates a new CRC Kermit value based on
 * the previous value of the CRC and the next byte of data to be checked.
 */

unsigned short update_crc_kermit( unsigned short crc, unsigned char c ) {

	unsigned short tmp;
	unsigned short short_c;

	short_c = 0x00ff & (unsigned short) c;

	if ( ! crc_tab_init ) init_crc_tab();

	tmp =  crc       ^ short_c;
	crc = (crc >> 8) ^ crc_tab[ tmp & 0xff ];

	return crc;

}  /* update_crc_kermit */

/*
 * static void init_crc_tab( void );
 *
 * For optimal performance, the  CRC Kermit routine uses a lookup table with
 * values that can be used directly in the XOR arithmetic in the algorithm.
 * This lookup table is calculated by the init_crc_tab() routine, the first
 * time the CRC function is called.
 */

static void init_crc_tab( void ) {

	unsigned short i;
	unsigned short j;
	unsigned short crc;
	unsigned short c;

	for (i=0; i<256; i++) {

		crc = 0;
		c   = i;

		for (j=0; j<8; j++) {

			if ( (crc ^ c) & 0x0001 ) crc = ( crc >> 1 ) ^ CRC_POLY_KERMIT;
			else                      crc =   crc >> 1;

			c = c >> 1;
		}

		crc_tab[i] = crc;
	}

	crc_tab_init = TRUE;

}  /* init_crc_tab */
