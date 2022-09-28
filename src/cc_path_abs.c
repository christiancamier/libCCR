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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "cc_memory.h"

#include "cc_path_internal.h"

extern char *cc_path_absolute(const char *);

char *cc_path_absolute(const char *pathname)
{
#if HAVE_REALPATH
	char *retval;
	INIT_PATH_MAX((char *)NULL);
	{
		char pathrnam[__cc_path_siz];
		if((char *)NULL == realpath(pathname, pathrnam))
			return (char *)NULL;
		retval = cc_strdup(pathrnam);
		cc_memclr(pathrnam, __cc_path_siz);
	}
	return retval;
#else
	(void)pathname;
	errno = ENOSYS;
	return NULL;
#endif
}
