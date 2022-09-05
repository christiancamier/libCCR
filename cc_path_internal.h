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

#include "cc_machdep.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#ifndef __CC_PATH_INTERNAL_H__
#define __CC_PATH_INTERNAL_H__
#include "cc_path.h"

#ifdef HAVE_PATHCONF
extern size_t __cc_path_max;
extern size_t __cc_path_siz;

# define INIT_PATH_MAX(error_value)				\
	if(0 == __cc_path_max)					\
	{							\
		long pm;					\
		if(-1 == (pm = pathconf("/", _PC_PATH_MAX)))	\
		{						\
			perror("pathconf('/', _PC_PATH_MAX)");	\
			return error_value;			\
		}						\
		__cc_path_max = (size_t)pm;			\
		__cc_path_siz = __cc_path_max + 1;		\
	}
#else
# define INIT_PATH_MAX(error_value)
# define __cc_path_max (size_t)(PATH_MAX + 0)
# define __cc_path_max (size_t)(PATH_MAX + 1)
#endif 
#endif /*!__CC_PATH_INTERNAL_H__*/
