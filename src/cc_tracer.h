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

#ifndef __CC_TRACER_H__

#if defined(CC_TRACER)

extern void cc_tr_close (void);
extern void cc_tr_enter (const char *, size_t, const char *, size_t);
extern void cc_tr_info  (const char *, ...);
extern void cc_tr_exit  (const char *, size_t, int) __attribute__((noreturn));
extern void cc_tr_open  (const char *, size_t, const char *);
extern void cc_tr_printf(const char *, size_t, const char *, ...);
extern void cc_tr_return(const char *, size_t, const char *);

#define CC_TR_OPEN(filename)	cc_tr_open(__FILE__, __LINE__, filename)
#define CC_TR_CLOSE()           cc_tr_close()
#define CC_TR_PRINTF(...)	cc_tr_printf(__FILE__, __LINE__, __VA_ARGS__)
#define CC_TR_ENTER(fct)	static const char *cc_tr_function = #fct; static size_t cc_tr_ncalls = 0; cc_tr_enter(__FILE__, __LINE__, cc_tr_function, ++cc_tr_ncalls)
#define CC_TR_RETURN		cc_tr_return(__FILE__, __LINE__, cc_tr_function); return
#define CC_TR_EXIT(n)           cc_tr_exit(__FILE__, __LINE__, n)

extern void *cc_tr_calloc      (const char *, size_t, const char *, size_t, size_t);
extern void  cc_tr_free        (const char *, size_t, const char *, void *);
extern void *cc_tr_malloc      (const char *, size_t, const char *, size_t);
extern void  cc_tr_meminfo     (void);
extern void *cc_tr_realloc     (const char *, size_t, const char *, void *, size_t);

#define CC_TR_CALLOC(n, s)	cc_tr_calloc (__FILE__, __LINE__, cc_tr_function, n, s)
#define CC_TR_FREE(p)		cc_tr_free   (__FILE__, __LINE__, cc_tr_function, p)
#define CC_TR_MALLOC(s)		cc_tr_malloc (__FILE__, __LINE__, cc_tr_function, s)
#define CC_TR_REALLOC(p, s)	cc_tr_realloc(__FILE__, __LINE__, cc_tr_function, p, s)

#else

#define CC_TR_OPEN(filename)
#define CC_TR_CLOSE()
#define CC_TR_PRINTF(...)
#define CC_TR_ENTER(function)
#define CC_TR_RETURN		return
#define CC_TR_EXIT(n)           exit(n)

#define CC_TR_CALLOC(n, s)	calloc(n, s)
#define CC_TR_FREE(p)		free(p)
#define CC_TR_MALLOC(s)		malloc(s)
#define CC_TR_REALLOC(p, s)	realloc(p, s)

#endif

#endif
