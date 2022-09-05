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
#include <unistd.h>

#include "cc_path_internal.h"

extern size_t cc_path_link_max(void);
extern size_t cc_path_name_max(void);
extern size_t cc_path_path_max(void);

extern size_t CC_PATH_LINK_MAX;
extern size_t CC_PATH_NAME_MAX;
extern size_t CC_PATH_PATH_MAX;

#ifdef HAVE_PATHCONF
size_t CC_PATH_LINK_MAX = 0;
size_t CC_PATH_NAME_MAX = 0;
size_t CC_PATH_PATH_MAX = 0;

static __attribute__((constructor)) void initialize(void)
{
	long pcnf;
	errno = 0;
#define GETLIMIT(name) if(-1 == (pcnf = pathconf("/", _PC_##name)) && 0 != errno) goto error; CC_PATH_##name = (size_t)pcnf
	GETLIMIT(LINK_MAX);
	GETLIMIT(NAME_MAX);
	GETLIMIT(PATH_MAX);
#undef GETLIMIT
	return;
error:
	perror("pathconf");
	exit(1);
}
#else
size_t CC_PATH_LINK_MAX = LINK_MAX;
size_t CC_PATH_NAME_MAX = NAME_MAX;
size_t CC_PATH_PATH_MAX = PATH_MAX;
#endif


size_t cc_path_link_max(void)
{
	return (size_t)CC_PATH_LINK_MAX;
}

size_t cc_path_name_max(void)
{
	return (size_t)CC_PATH_NAME_MAX;
}

size_t cc_path_path_max(void)
{
	return (size_t)CC_PATH_PATH_MAX;
}
