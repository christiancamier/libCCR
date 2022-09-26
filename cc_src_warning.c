/*-
 * Copyright (c) 2010
 * 	Christian CAMIER <chcamier@free.fr>
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

#include "cc_src_warning.h"

extern void  cc_src_warning_add    (struct cc_warning_st *);
extern void  cc_src_warning_display(void);
extern int   cc_src_warning_exist  (void);
extern void  cc_src_warning_walk   (void (*)(const char *));

struct cc_src_warning_st *src_warnings = NULL;

void cc_src_warning_add(struct cc_warning_st *warning)
{
	warning->next = src_warnings;
	src_warnings = warning;
	return;
}

void cc_src_warning_display(void)
{
	struct cc_warning_st *p;
	for(p = src_warnings; p; p = p->next)
		fprintf(stderr, "WARNING: %s\n", p->message);
	return;
}

int cc_src_warning_exists(void)
{
	return NULL != src_warnings;
}

void cc_src_warning_walk(void (*callback)(const char *))
{
	struct cc_warning_st *p;
	for(p = src_warnings; p; p = p->next)
		callback(p->message);
	return;
}
