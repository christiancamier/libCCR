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

#include <stdlib.h>
#include <string.h>

#include "cc_memory.h"
#include "cc_path_internal.h"

extern dev_t        cc_path_dev(const char *);
extern ino_t        cc_path_node(const char *);
extern mode_t       cc_path_mode(const char *);
extern nlink_t      cc_path_nlink(const char *);
extern uid_t        cc_path_uid(const char *);
extern gid_t        cc_path_gid(const char *);
extern off_t        cc_path_size(const char *);
extern blkcnt_t     cc_path_blocks(const char *);
extern time_t       cc_path_atime(const char *);
extern time_t       cc_path_ctime(const char *);
extern time_t       cc_path_mtime(const char *);
extern struct stat *cc_path_stat(const char *);

#define FUNCTION(field, type, extra)			\
	type cc_path_##field(const char *filename)	\
	{						\
		struct stat st;				\
		if(-1 == stat(filename, &st))		\
			return (type)-1;		\
		return st.st_##field extra;		\
	}
FUNCTION(atime,  time_t,)
FUNCTION(blocks, blkcnt_t,)
FUNCTION(ctime,  time_t,)
FUNCTION(dev,    dev_t,)
FUNCTION(gid,    gid_t,)
FUNCTION(mode,   mode_t, & 07777)
FUNCTION(mtime,  time_t,)
FUNCTION(nlink,  nlink_t,)
FUNCTION(ino,    ino_t,)
FUNCTION(size,   off_t,)
FUNCTION(uid,    uid_t,)
#undef FUNCTION

struct stat *cc_path_stat(const char *filename)
{
	struct stat  st[1];
	struct stat *re;
	if(-1 == stat(filename, st))
		return (struct stat *)NULL;
	if((struct stat *)NULL == (re = CC_TALLOC(struct stat, 1)))
		return (struct stat *)NULL;
	(void)memcpy((void *)re, (void *)st, sizeof(struct stat));
	cc_memclr(st, sizeof(struct stat));
	return re;
}
