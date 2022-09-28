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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include "cc_fmt.h"
#define CC_TRACER
#include "cc_tracer.h"

static size_t indentation =  0;
static int    filedesc    = -1;
static char   buffer[1024];
static time_t starttime;

extern void cc_tr_close (void);
extern void cc_tr_enter (const char *, size_t, const char *, size_t);
extern void cc_tr_info  (const char *, ...);
extern void cc_tr_exit  (const char *, size_t, int) __attribute__((noreturn));
extern void cc_tr_open  (const char *, size_t, const char *);
extern void cc_tr_printf(const char *, size_t, const char *, ...);
extern void cc_tr_return(const char *, size_t, const char *);

static const char *basename(const char *);

void cc_tr_close(void)
{
	if(-1 == filedesc)
	{
		time_t endtime = time(NULL);
		time_t seconds;
		time_t minutes;
		time_t hours;
		time_t days;

		endtime -= starttime;
		seconds = endtime % 60, endtime /= 60;
		minutes = endtime % 60, endtime /= 60;
		hours   = endtime % 24, endtime /= 24;
		days    = endtime;

		if(days)		cc_tr_info("Elapsed time: %lud %02ulh %02ulm %02uls", days, hours, minutes, seconds);
		else if(hours)		cc_tr_info("Elapsed time: %02ulh %02ulm %02uls", hours, minutes, seconds);
		else if(minutes)	cc_tr_info("Elapsed time: %02ulm %02uls", minutes, seconds);
		else			cc_tr_info("Elapsed time: %02uls", minutes, seconds);
		cc_tr_meminfo();
		cc_tr_info("Log closed");

		(void)close(filedesc);
		filedesc = -1;
	}
	return;
}

void cc_tr_enter(const char *source, size_t line, const char *fctname, size_t ncalls)
{
	static const char   *lastfct = NULL;
	static size_t        callcnt = 0;

	if(fctname == lastfct)
	{
		callcnt += 1;
		return;
	}
	
	if(lastfct && callcnt > 0)
	{
		cc_tr_info("  %s: %lu more calls", lastfct, callcnt);
	}

	cc_tr_printf(source, line, ">> %s (call #%lu)", fctname, ncalls);
	lastfct = fctname;
	callcnt = 0;
	indentation += 1;
	return;
}

void __attribute__((noreturn)) cc_tr_exit  (const char *source, size_t line, int status)
{
	cc_tr_printf(source, line, "Exiting (status = %d)", status);
	cc_tr_close();
	exit(status);
}

void cc_tr_info(const char *format, ...)
{
	if(-1 != filedesc)
	{
		va_list  ap;
		char    *bufptr = buffer;
		size_t   bufsiz = sizeof(buffer);
		size_t   rv;
		size_t   ind;

		(void)cc_fmt_timestamp(&bufptr, &bufsiz, "%Y%m%d %H%M%S ");
		for(ind = 0; ind < indentation; ind += 1)
			cc_fmt_char(&bufptr, &bufsiz, ' ');
		(void)cc_fmt_string   (&bufptr, &bufsiz, "INFO - ");
		va_start(ap, format);
		rv = (size_t)vsnprintf(bufptr, bufsiz, format, ap);
		va_end(ap);
		if(rv > bufsiz)
			rv = bufsiz;
		bufptr += rv, bufsiz -= rv;
		cc_fmt_char(&bufptr, &bufsiz, '\n');
		(void)write(filedesc, buffer, bufptr - buffer);
	}
	return;
}

void cc_tr_open(const char *source, size_t line, const char *filename)
{
	if(-1 == (filedesc = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0640)))
		perror(filename);
	else
		cc_tr_printf(source, line, "Log %s opened", filename);
	starttime = time(NULL);
	return;
}

void cc_tr_printf(const char *source, size_t line, const char *format, ...)
{

	if(-1 != filedesc)
	{
		va_list  ap;
		char    *bufptr = buffer;
		size_t   bufsiz = sizeof(buffer);
		size_t   rv;
		size_t   ind;

		(void)cc_fmt_timestamp(&bufptr, &bufsiz, "%Y%m%d %H%M%S ");
		for(ind = 0; ind < indentation; ind += 1)
			cc_fmt_char(&bufptr, &bufsiz, ' ');
		(void)cc_fmt_string(&bufptr, &bufsiz, basename(source));
		(void)cc_fmt_string(&bufptr, &bufsiz, " [");
		(void)cc_fmt_uint64(&bufptr, &bufsiz, line, 10);
		(void)cc_fmt_string(&bufptr, &bufsiz, "] ");

		va_start(ap, format);
		rv = (size_t)vsnprintf(bufptr, bufsiz, format, ap);
		va_end(ap);
		if(rv > bufsiz)
			rv = bufsiz;
		bufptr += rv, bufsiz -= rv;
		cc_fmt_char(&bufptr, &bufsiz, '\n');
		(void)write(filedesc, buffer, bufptr - buffer);
	}
	return;
}

void cc_tr_return(const char *source, size_t line, const char *function)
{
	if(0 < indentation) indentation -= 1;
	cc_tr_printf(source, line, "<< %s", function);
	return;
}

static const char *basename(const char *filename)
{
	char *r;
	if(NULL == (r = rindex(filename, '/'))) r  = (char *)filename;
	else                                    r += 1;
	return (const char *)r;
}
