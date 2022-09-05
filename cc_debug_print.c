/*
 * Copyright (c) 2010
 *      Christian CAMIER <chcamier@free.fr>
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


#include "cc_debug_internal.h"

extern void  cc_debug_print(const char *, ...);

void cc_debug_print(const char *format, ...)
{
	va_list ap;
	if(__cc_debug_flag)
	{
		__cc_debug_initialize();
		(void)fprintf(__cc_debug_stream, "DEBUG: ");
		va_start(ap, format);
		vfprintf(__cc_debug_stream, format, ap);
		va_end(ap);
	}
	return;
}
