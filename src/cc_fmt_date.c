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
#include <errno.h>
#include <time.h>

#include "cc_fmt_internal.h"

extern void    cc_fmt_timestamp_setgmt(void);
extern void    cc_fmt_timestamp_setloc(void);
extern ssize_t cc_fmt_date            (char **, size_t *, const char *, struct tm *);
extern ssize_t cc_fmt_timestamp       (char **, size_t *, const char *);

struct tm *(*xxtime)(const time_t *, struct tm *) = localtime_r;

ssize_t cc_fmt_date(char **buffer, size_t *bufsiz, const char *format, struct tm *tm)
{
	char   *buf = *buffer;
	size_t  bsz = *bufsiz;
	size_t  nbw;

	nbw = strftime(buf, bsz, format, tm);
	if(nbw > 0)
	{
		*bufsiz -= nbw;
		*buffer += nbw;
	}

	return (ssize_t)nbw;
}

void cc_fmt_timestamp_setgmt(void) { xxtime = gmtime_r;    return; }
void cc_fmt_timestamp_setloc(void) { xxtime = localtime_r; return; }

ssize_t cc_fmt_timestamp(char **buffer, size_t *bufsiz, const char *format)
{
	time_t    ti[1];
	struct tm tm[1];
	(void)time(ti);
	(void)xxtime(ti, tm);
	return cc_fmt_date(buffer, bufsiz, format, tm);
}

