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


#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#include "cc_path_internal.h"

extern int    cc_mkpath(const char *, int);

int cc_mkpath(const char *path, int mode)
{
	char         bpath[strlen(path) + 1];
	const char  *srcpt;
	char        *tgtpt;
	struct stat  statb[1];

	srcpt = path;
	tgtpt = bpath;

	if('/' == *srcpt)
		*(tgtpt++) = *(srcpt++);
	while('/' == *srcpt)
		srcpt += 1;
	while(*srcpt)
	{
		while('/' != *srcpt && *srcpt)
			*(tgtpt++) = *(srcpt++);
		*tgtpt  = '\0';
		if(-1 == stat(bpath, statb))
		{
			if(ENOENT == errno)
			{
				if(-1 == mkdir(bpath, mode))
					return -1;
			}
			else
			{
				return -1;
			}
		}
		if('/' == *(srcpt))
			*(tgtpt++) = *(srcpt++);
	}

	return 0;
}

