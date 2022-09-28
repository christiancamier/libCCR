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

#include <stdarg.h>
#include <stdio.h>
#ifdef HAVE_STDIO_EXT_H
# include<stdio_ext.h>
# define fpurge(x)	__fpurge(x)
#endif
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "cc_confirm.h"

extern int cc_confirm(int, const char *, ...);
extern int cc_confirm_or_quit(int, const char *, ...);

struct answers_st {
	int                 code;
	const char * const *answers;
};

static const char *N_answers[] = { "n", "no",   NULL };
static const char *Q_answers[] = { "q", "quit", NULL };
static const char *Y_answers[] = { "y", "yes",  NULL };

static struct answers_st NQY[] = {
	{ CC_CONFIRM_NO,   N_answers },
	{ CC_CONFIRM_QUIT, Q_answers },
	{ CC_CONFIRM_YES,  Y_answers },
	{              0,       NULL }
};

static struct answers_st NY[] = {
	{ CC_CONFIRM_NO,   N_answers },
	{ CC_CONFIRM_YES,  Y_answers },
	{              0,       NULL }
};

static int do_confirm(struct answers_st *answers, const char *format, va_list ap)
{
	int fd;

	fd = fileno(stdin);
	if(isatty(fd))
	{
		char                answ[16];
		char               *aptr;
		struct answers_st  *rptr;
		const char * const *sptr;

		while(1)
		{
			vfprintf(stdout, format, ap);
			fflush(stdout);
			(void)tcflush(fd, TCIFLUSH);
			(void)fpurge(stdin);
			(void)clearerr(stdin);
			if(NULL == (aptr = fgets(answ, (int)(sizeof(answ) - 1), stdin)))
			{
				if(feof(stdin))
					continue;
				perror("stdin");
				return CC_CONFIRM_ERROR;
			}
			while(*aptr)
			{
				if('\n' == *aptr || '\r' == *aptr)
				{
					*aptr = '\0';
					break;
				}
				aptr += 1;
			}
			for(rptr = answers; rptr->answers; rptr += 1)
				for(sptr = rptr->answers; *sptr; sptr += 1)
					if(0 == strcasecmp(*sptr, answ))
						return rptr->code;
			fprintf(stdout, "Wrong answer ..\nPossible answers are:\n");
			for(rptr = answers; rptr->answers; rptr += 1)
			{
				const char *x = "";
				fprintf(stdout, " - ");
				for(sptr = rptr->answers; *sptr; sptr += 1)
				{
					fprintf(stdout, "%s%s", x, *sptr);
					x = ", ";
				}
				fprintf(stdout, "\n");
			}
		}
	}
	return CC_CONFIRM_YES;
}

/*
 * NAME
 *	cc_confirm
 *
 * SYNOPSIS
 *	#include <cc_confirm.h>
 *	int cc_confirm(int default, const char *format, ...)
 *
 * DESCRIPTION
 *	Produce output on stdout according to a format as described in printf(3)
 *	and wait for a confirmation from the user.
 *	The parameter `default' is the value returned if STDIN_FILENO is not a
 *	tty.
 *
 * RETURN VALUE
 *	If STDIN_FILENO is not a tty, returns always `default' else returns one
 *	of the folowing values :
 *	- CC_CONFIRM_NO	   ( 0) - The user has infirmed
 *	- CC_CONFIRM_YES   ( 1) - The user has confirmed
 *	- CC_CONFIRM_ERROR (-1) - An error has occured
 *	
 */

int cc_confirm(int dflt, const char *format, ...)
{
	int     ans;
	va_list ap;

	if(!isatty(STDIN_FILENO))
		return dflt;

	va_start(ap, format);
	ans = do_confirm(NY, format, ap);
	va_end(ap);
	return ans;
}

/*
 * NAME
 *	cc_confirm_or_quit
 *
 * SYNOPSIS
 *	#include <cc_confirm.h>
 *	int cc_confirm_or_quit(int default, const char *format, ...)
 *
 * DESCRIPTION
 *	Produce output on stdout according to a format as described in printf(3)
 *	and wait for a confirmation from the user.
 *	The parameter `default' is the value returned if STDIN_FILENO is not a
 *	tty.
 *
 * RETURN VALUE
 *	If STDIN_FILENO is not a tty, returns always `default' else returns one
 *	of the folowing values :
 *	- CC_CONFIRM_NO	   ( 0) - The user has infirmed
 *	- CC_CONFIRM_YES   ( 1) - The user has confirmed
 *	- CC_CONFIRM_QUIT  ( 2) - The user want to quit
 *	- CC_CONFIRM_ERROR (-1) - An error has occured
 *	
 */

int cc_confirm_or_quit(int dflt, const char *format, ...)
{
	int     ans;
	va_list ap;

	if(!isatty(STDIN_FILENO))
		return dflt;

	va_start(ap, format);
	ans = do_confirm(NQY, format, ap);
	va_end(ap);
	return ans;
}
