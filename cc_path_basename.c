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

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cc_path_internal.h"
#include "cc_memory.h"
#include "cc_util.h"
#include "cc_fmt.h"

extern char *cc_path_basename(const char *, char *, size_t);
extern char *cc_path_dirname(const char *, char *, size_t);

static const char *Xname(const char *path, int is_dirname)
{
	if(NULL == path || '\0' == *path || ('.' == *path && '\0' == *(path + 1)))
		return ".";
	if('.' == *(path + 0) && '.' == *(path + 1) && '\0' == *(path + 2))
		return ".." + is_dirname;
	if('/' == *(path + 0) && '\0' == *(path + 1))
		return "/";
	return NULL;
}

extern char *cc_path_basename(const char *path, char *buffer, size_t bufsiz)
{
	char       *b;
	const char *p;

	if(NULL != (p = Xname(path, 0)))
		goto end;
	p = (const char *)strrchr(path, '/');
	if(NULL == p) p  = path;
	else                    p += 1;

end:
	if(NULL == buffer)
	{
		b = cc_strdup(p);
	}
	else
	{
		b  = buffer;
		bufsiz -= 1;
		*(buffer + bufsiz) = '\0';
		(void)cc_fmt_bytes(&buffer, &bufsiz, p, strlen(p));
	}
	return b;
}

extern char *cc_path_dirname(const char *path, char *buffer, size_t bufsiz)
{
	char       *b;
	const char *p;
	size_t      l;
	size_t      s;

	if(NULL != (p = Xname(path, 1)))
	{
		l = strlen(p);
		goto end;
	}
	p = (const char *)strrchr(path, '/');
	if(NULL == p) 
	{
		p = ".";
		l = 1;
		goto end;
	}
	l = p - path;
end:
	if(NULL == buffer)
	{
		if(NULL == (b = cc_malloc(l + 1)))
			return NULL;
		s = l;
	}
	else
	{
		b = buffer;
		s = bufsiz - 1;
	}
	*(b + s) = '\0';
	(void)cc_fmt_bytes(&buffer, &s, p, l);
	return b;
}
