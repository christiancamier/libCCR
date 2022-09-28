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
 * #@ "cc_src_waning.h"
 *	-- CC Utilities: Compilation time warnings
 *
 * Author : Christian CAMIER
 *
 * Rev : 1.0 (09/26/2022)
 */

#ifndef __CC_SRC_WARNING_H__
#define __CC_SRC_WARNING_H__

struct cc_src_warning_st {
	struct cc_src_warning_st *next;
	const char               *message;
} erase_warning_t;

extern void  cc_src_warning_add    (struct cc_src_warning_st *);
extern void  cc_src_warning_display(void);
extern int   cc_src_warning_exist  (void);
extern void  cc_src_warning_walk   (void (*)(const char *));

#define CC_SRC_WARNING(M)								\
	static __attribute__((constructor)) void cc_warn_fct##__LINE__(void) {		\
		static struct cc_src_warning_st warn_message = { .message = M };	\
		cc_src_warning_add(&warn_message);					\
		return;									\
	}

#endif /*! __CC_SRC_WARNING_H__*/
