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
#include <stdio.h>

#include "cc_util.h"

#include "cc_debug_internal.h"

extern int   cc_debug_get_flag(void);
extern FILE *cc_debug_get_stream(void);
extern int   cc_debug_set_flag(int flag);
extern FILE *cc_debug_set_stream(FILE *stream);

extern void  __cc_debug_initialize(void);

extern int __cc_debug_flag;
int __cc_debug_flag = 0;

extern FILE *__cc_debug_stream;
FILE *__cc_debug_stream = NULL;

void  __cc_debug_initialize(void)
{
	if(NULL == __cc_debug_stream)
		__cc_debug_stream = stderr;
	return;
}

int cc_debug_get_flag(void)
{
	__cc_debug_initialize();
	return __cc_debug_flag;
}

FILE *cc_debug_get_stream(void)
{
	__cc_debug_initialize();
	return __cc_debug_stream;
}

int cc_debug_set_flag(int flag)
{
	int old;
	__cc_debug_initialize();
	old = __cc_debug_flag;
	__cc_debug_flag = flag;
	return old;
}

FILE *cc_debug_set_stream(FILE *stream)
{
	FILE *old;
	__cc_debug_initialize();
	old = __cc_debug_stream;
	if(stream)
		__cc_debug_stream = stream;
	return old;
}
