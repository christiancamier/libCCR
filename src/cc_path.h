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

#ifndef __CC_PATH_H__
#define __CC_PATH_H__
extern dev_t    cc_path_dev(const char *);
extern ino_t    cc_path_node(const char *);
extern mode_t   cc_path_mode(const char *);
extern nlink_t  cc_path_nlink(const char *);
extern uid_t    cc_path_uid(const char *);
extern gid_t    cc_path_gid(const char *);
extern off_t    cc_path_size(const char *);
extern blkcnt_t cc_path_blocks(const char *);
extern time_t   cc_path_atime(const char *);
extern time_t   cc_path_ctime(const char *);
extern time_t   cc_path_mtime(const char *);

extern int cc_is_bdev(const char *);
extern int cc_is_cdev(const char *);
extern int cc_is_directory(const char *);
extern int cc_is_fifo(const char *);
extern int cc_is_link(const char *);
#define cc_is_symlink(path) cc_is_link(path)
extern int cc_is_regular(const char *);
extern int cc_is_socket(const char *);

extern size_t CC_PATH_LINK_MAX;
extern size_t CC_PATH_NAME_MAX;
extern size_t CC_PATH_PATH_MAX;

extern size_t cc_path_link_max(void);
extern size_t cc_path_name_max(void);
extern size_t cc_path_path_max(void);

extern size_t cc_filesize(const char *);

extern int    cc_mkpath(const char *, int);

#if defined(S_IFMT)
extern struct stat *cc_path_stat(const char *);
#endif

#endif /*!__CC_PATH_H__*/
