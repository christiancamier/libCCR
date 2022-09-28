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
#include <unistd.h>

#define CC_TRACER
#include "cc_tracer.h"

extern void *cc_tr_calloc      (const char *, size_t, const char *, size_t, size_t);
extern void  cc_tr_free        (const char *, size_t, const char *, void *);
extern void *cc_tr_malloc      (const char *, size_t, const char *, size_t);
extern void  cc_tr_meminfo     (void);
extern void *cc_tr_realloc     (const char *, size_t, const char *, void *, size_t);

static size_t  nalloc = 0;
static size_t  nfree  = 0;
static char    *start_break    = NULL;

void *cc_tr_calloc(const char *source, size_t line, const char *function, size_t nmemb, size_t size)
{
	void   *result;
	size_t  total  = nmemb * size;

	if(NULL != (result = calloc(nmemb, size)))
		nalloc += 1;
	cc_tr_printf(source, line, "%s - calloc: nmemb = %lu, size = %lu, total %lu bytes - returned %p", function, nmemb, size, total, result);
	return result;
}

void  cc_tr_free(const char *source, size_t line, const char *function, void *pointer)
{
	nfree += 1;
	cc_tr_printf(source, line, "%s - free %p", function, pointer);
	free(pointer);
	return;
}

void *cc_tr_malloc(const char *source, size_t line, const char *function, size_t size)
{
	void   *result;
	if(NULL != (result = malloc(size)))
		nalloc += 1;
	cc_tr_printf(source, line, "%s - malloc %lu bytes - returned %p", function, size, result);
	return result;
}

void cc_tr_meminfo(void)
{
	char *final_break = (char *)sbrk(0);
	cc_tr_info("Memory usage:");
	cc_tr_info(" Break:");
	cc_tr_info("  Start: %p", start_break);
	cc_tr_info("  Final: %p", final_break);
	cc_tr_info(" Total alloc: %lu", nalloc);
	cc_tr_info(" Total free : %lu", nfree);
	return;
}

void *cc_tr_realloc(const char *source, size_t line, const char *function, void *ptr, size_t size)
{
	void   *result;
	result = realloc(ptr, size);
	cc_tr_printf(source, line, "%s - realloc %p new size %lu - returned %p", function, ptr, size, result);
	return result;
}

static __attribute__((constructor)) void set_start_break(void)
{
	start_break = (char *)sbrk(0);
}

