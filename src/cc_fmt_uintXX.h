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

/*
 * #@ "cc_fmt_uintXX.h"
 *	-- CC Utilities: unsigned integer buffer formating template
 *
 * Author : Christian CAMIER
 *
 * Rev : 1.0 (01/22/2008)
 */

#include <sys/types.h>
#include <errno.h>

#include "cc_fmt_internal.h"

ssize_t __FCT(char **buffer, size_t *bufsiz, __TYP value, int base)
{
	char   *p = *buffer;
	size_t  n =  0;
	size_t  r =  0;
	size_t  s = *bufsiz;
	__TYP   v =  value;
	__TYP   t;

	errno = 0;

	if(s == (size_t)0)
		goto fmt_err;

	if(base < 2 || base > __cc_fmt_basemax)
	{
		errno = EINVAL;
		return -1;
	}

	if(v == 0)
	{
		*(p++) = __cc_fmt_digits[0];
		r += 1;
		goto fmt_end;
	}
	for(t = v, n = 0; t > 0; t /= base, n += 1);
	if(n > s)
		goto fmt_err;
	p += n;
	r += n;
	for(t = v; t > 0; *(--p) = __cc_fmt_digits[t % base], t /= base);

 fmt_end:
	*buffer += r;
	*bufsiz -= r;
	return (ssize_t)r;

 fmt_err:
	errno = ENOSPC;
	return -1;
}
