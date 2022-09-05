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
#include <unistd.h>

#include "cc_path_internal.h"

extern int cc_is_bdev(const char *);
extern int cc_is_cdev(const char *);
extern int cc_is_directory(const char *);
extern int cc_is_fifo(const char *);
extern int cc_is_link(const char *);
extern int cc_is_mount(const char *);
extern int cc_is_regular(const char *);
extern int cc_is_socket(const char *);

static dev_t getdev(const char *, const char *);

static dev_t getdev(const char *dirname, const char *subdirname)
{
	dev_t retval;
	INIT_PATH_MAX((dev_t)-1);
	{
		char path[__cc_path_siz];
		if(__cc_path_max < snprintf(path, __cc_path_siz, "%s/%s", dirname, subdirname))
			return (dev_t)-1;
		retval = cc_path_dev(path);
	}
	return retval;
}

#define FUNCTION(name, test)				\
	int cc_is_##name(const char *filename)		\
	{						\
		struct stat st;				\
		if(-1 == stat(filename, &st))		\
			return 0;			\
		return test(st.st_mode);		\
	}
FUNCTION(bdev,      S_ISBLK)
FUNCTION(cdev,      S_ISCHR)
FUNCTION(directory, S_ISDIR)
FUNCTION(fifo,      S_ISFIFO)
FUNCTION(link,      S_ISLNK)
FUNCTION(regular,   S_ISREG)
FUNCTION(socket,    S_ISSOCK)
#undef FUNCTION

int cc_is_mount(const char *filename)
{
	dev_t  dot;
	dev_t  dotdot;

	if((dev_t)-1 == (dot    = getdev (filename,  "."))) return 0 == 1;
	if((dev_t)-1 == (dotdot = getdev (filename, ".."))) return 0 == 1;
	return dot != dotdot;
}
