/*	$OpenBSD: pciide_amd_reg.h,v 1.1 2000/03/24 17:47:41 chris Exp $ 	*/

/*
 * Copyright (c) 2000 David Sainty.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/*
 * Registers definitions for AMD 756 PCI IDE controller.  Documentation
 * available at: http://www.amd.com/products/cpg/athlon/techdocs/pdf/22548.pdf
 */

/* Channel enable */
#define AMD756_CHANSTATUS_EN		0x40
#define AMD756_CHAN_EN(chan)		(0x01 << (1 - (chan)))

/* Data port timing controls */
#define AMD756_DATATIM 0x48
#define AMD756_DATATIM_MASK(channel) (0xffff << ((1 - (channel)) << 4))
#define AMD756_DATATIM_RECOV(channel, drive, x) (((x) & 0xf) << \
	(((1 - (channel)) << 4) + ((1 - (drive)) << 3)))
#define AMD756_DATATIM_PULSE(channel, drive, x) (((x) & 0xf) << \
	(((1 - (channel)) << 4) + ((1 - (drive)) << 3) + 4))

#define AMDCS5536_DRIVE_TIMING   0x48
#define AMDCS5536_ADDRESS_SETUP  0x4c
#define AMDCS5536_8BIT_TIMING    0x4e
#define AMDCS5536_UDMA_TIMING    0x50

struct ide_timing {
	int cyc;   /*cycle time*/
	int setup; /*Address setup time*/
	int data;  /*pulse width, and recovery time*/
};

static struct ide_timing amdcs5536_pio_set[5] = {
	{0x09, 0x02, 0x98}, /* PIO 0 */
	{0x09, 0x01, 0x55}, /* PIO 1 */
	{0x09, 0x00, 0x32}, /* PIO 2 */
	{0x02, 0x00, 0x21}, /* PIO 3 */
	{0x02, 0x99, 0x20}, /* PIO 4 */
};

static const int8_t amd756_pio_set[] = {0x0a, 0x0a, 0x0a, 0x02, 0x02};
static const int8_t amd756_pio_rec[] = {0x08, 0x08, 0x08, 0x02, 0x00};

/* Ultra-DMA/33 control */
#define AMD756_UDMA 0x50
#define AMD756_UDMA_MASK(channel) (0xffff << ((1 - (channel)) << 4))
#define AMD756_UDMA_TIME(channel, drive, x) (((x) & 0x7) << \
	(((1 - (channel)) << 4) + ((1 - (drive)) << 3)))
#define AMD756_UDMA_EN(channel, drive) (0x40 << \
	(((1 - (channel)) << 4) + ((1 - (drive)) << 3)))
#define AMD756_UDMA_EN_MTH(channel, drive) (0x80 << \
	(((1 - (channel)) << 4) + ((1 - (drive)) << 3)))

static const int8_t amd756_udma_tim[] = {0x02, 0x01, 0x00, 0x04, 0x05};
