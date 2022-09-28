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

#ifndef __CC_LOG_H__
#define __CC_LOG_H__

typedef enum cc_log_level_en {
	CC_LOG_GET      = -1,
	CC_LOG_EMERG	=  0,
	CC_LOG_ALERT    =  1,
	CC_LOG_CRIT     =  2,
	CC_LOG_ERR      =  3,
	CC_LOG_WARNING  =  4,
	CC_LOG_NOTICE   =  5,
	CC_LOG_INFO     =  6,
	CC_LOG_DEBUG    =  7
} cc_log_level_t;

struct cc_log_driver_info {
	const char *name;
	const char *desc;
};

#if defined(_STDARG_H) || defined(_ANSI_STDARG_H_)
struct cc_logger_st {
	struct cc_logger_st  *next;
	const char           *name;
	const char           *desc;
	int                 (*sopt)(const char *, const char *, int);
	void                (*open )(void);
	void                (*close)(void);
	void                (*log  )(int, const char *, va_list);
};

extern void            cc_log_register       (struct cc_logger_st *);

#define CC_LOG_REGISTER(aname, adesc, asopt, aopen, aclose, alog)	\
	static struct cc_logger_st drv_##aname = { .next = NULL, .name = #aname, .desc = adesc, .sopt = asopt, .open = aopen, .close = aclose, .log = alog }; \
	static __attribute__((constructor)) void ctor_##aname(void) { cc_log_register(&drv_##aname); }
#endif	

extern void            cc_log_add_option(const char *, int(*)(const char *, const char *, void *, int), void *);
extern int             cc_log_driver_exists(const char *);
extern size_t          cc_log_driver_list  (struct cc_log_driver_info *, size_t);
extern cc_log_level_t  cc_log_level_by_name(const char *);
extern const char     *cc_log_level_name   (cc_log_level_t);
extern cc_log_level_t  cc_log_set_level    (cc_log_level_t);
extern int             cc_log_set_driver   (const char *);
extern int             cc_log_set_option   (const char *, const char *);
extern int             cc_log_set_drv_opt  (const char *, const char *, const char *);
extern int             cc_log_tst_option   (const char *, const char *);
extern int             cc_log_tst_drv_opt  (const char *, const char *, const char *);
extern const char     *cc_log_timestamp    (void);

extern void            cc_log_alert          (const char *, ...);
extern void            cc_log_crit           (const char *, ...);
extern void            cc_log_debug          (const char *, ...);
extern void            cc_log_emerg          (const char *, ...);
extern void            cc_log_error          (const char *, ...);
extern void            cc_log_info           (const char *, ...);
extern void            cc_log_notice         (const char *, ...);
extern void            cc_log_warning        (const char *, ...);
extern void            cc_log_log            (cc_log_level_t, const char *, ...);
#if defined(_STDARG_H) || defined(_ANSI_STDARG_H_)
extern void            cc_log_vlog           (cc_log_level_t, const char *, va_list);
#endif

extern void            cc_log_perror	     (const char *);
extern void            cc_log_panic          (const char *, ...) __attribute__((noreturn));

extern void            cc_log_dbgcod         (const char *, size_t, const char *, ...);
#define CC_LOG_DBGCOD(...)	cc_log_dbgcod(__FILE__, __LINE__, __VA_ARGS__)

#define CC_LOG_OK         0
#define CC_LOG_BADOPTION -1
#define CC_LOG_BADOPTVAL -2
#define CC_LOG_BADDRIVER -3

#endif /* ! __CC_LOG_H__ */
