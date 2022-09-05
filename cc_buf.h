/*-
 * Copyright (c) 2022
 * 	Christian CAMIER <christian.c@promethee.services>
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __CC_BUFFER_H__
#define __CC_BUFFER_H__

typedef struct cc_buffer_st {
	size_t         size;	/* Buffer actual size */
	size_t         incr;	/* Buffer size increment when grow */
	size_t         maxs;	/* Buffer max size */
	size_t         rems;	/* Unused space */
	unsigned long *data;	/* Buffer data pointer */
	unsigned char *cpos;	/* Current position in the buffer */
} cc_buffer_t;

#define cc_buffer_data(B)	(unsigned char *)((B)->data)
#define cc_buffer_reset(B)	(B)->curpos = cc_buffer_data(B)

#endif /*!__CC_BUFFER_H__*/
