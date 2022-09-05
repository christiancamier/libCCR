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

#include <sys/types.h>

#include "cc_debug_internal.h"
#include "cc_fmt_internal.h"
#include "cc_memory.h"

extern void cc_debug_memdump(const char *, void *, size_t);

void cc_debug_memdump(const char *title, void *address, size_t length)
{
	char           l[60];
	int            i;
	int            j;
	unsigned char *p;
	char          *b;
	char          *c;
	if(!__cc_debug_flag)
		return;
	__cc_debug_initialize();
	fprintf(__cc_debug_stream, "DEBUG: Dump: '%s'\n       Address = %p, lenght = %lu\n", title, address, (unsigned long)length);
	l[54] = '\0';
	for(p = (unsigned char *)address, i = 0; length; i += 16)
	{
		b = l;
		c = l + 40;
		for(j = 0; j < 16 && length; j += 1, p += 1, length -= 1)
		{
			*(b++) = __cc_fmt_digits[((*p) >> 4) & 0x0F];
			*(b++) = __cc_fmt_digits[((*p) >> 0) & 0x0F];
			if(1 == (j & 1))
				*(b++) = ' ';
			*(c++) = isprint(*p) ? *p : '.';
		}
		fprintf(__cc_debug_stream, "       +%04X: %s\n", i, l);
	}
	cc_memclr(l, sizeof(l));
	return;
}
