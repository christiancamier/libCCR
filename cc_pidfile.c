/*
 * Copyright (c) 2022
 *      Christian CAMIER <christian.c@promethee.services>
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
#include <sys/param.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cc_fmt.h"
#include "cc_log.h"
#include "cc_path.h"

static char pidfile[MAXPATHLEN + 1];

extern int          cc_ctl_pidfile(const char *);
extern const char  *cc_get_pidfile(void);
extern int          cc_set_pidfile(const char *);
extern pid_t        cc_pidfile    (const char *, int);

static void cleanup(void)
{
	(void)unlink(pidfile);
}

static int pid_running(pid_t pid)
{
	if(-1 == kill(pid, 0))
		return ESRCH != errno;
	return 1;
}

int cc_ctl_pidfile(const char *newpf)
{
	size_t l_newpf = strlen(newpf);
	if('/' != newpf[0])
	{
		cc_log_error("pidfile must be absolute");
		return -1;
	}
	if(l_newpf < 3)
	{
		cc_log_error("pidfile name too short");
		return -1;
	}
	if(l_newpf > MAXPATHLEN)
	{
		cc_log_error("pidfile name too long");
		return -1;
	}
	return 0;
}

const char *cc_get_pidfile(void)
{
	return pidfile;
}

int cc_set_pidfile(const char *newpf)
{
	int status = cc_ctl_pidfile(newpf);
	if(-1 != status)
		(void)strcpy(pidfile, newpf);
	return status;
}

pid_t cc_pidfile(const char *filename, int create)
{
	int    pfpid;
	pid_t  mypid;
	FILE  *fdesc;

	mypid = getpid();

	if(NULL == (fdesc = fopen(filename, "r")))
	{
		if(ENOENT != errno)
		{
			int sverr = errno;
			cc_log_perror(filename);
			errno = sverr;
			pfpid = -1;
			goto stage2;
		}
		pfpid = 0;
		goto stage2;
	}

	if(-1 == fscanf(fdesc, "%d", &pfpid))
	{
		cc_log_warning("%s: Misformed %s pid file", filename);
		if(!create)
		{
			cc_log_notice("Assuming there is no other daemon running");
		}
		pfpid = 0;
	}
	fclose(fdesc);

stage2:
	/* If not create, just return the running pid (0 if not running) */
	if(!create)
	{
		if(pfpid <= 0 || !pid_running(pfpid))
			pfpid = 0;
		goto end;
	}

	if(pfpid > 0 && (pid_t)pfpid != mypid && pid_running(pfpid))
	{
		cc_log_error("There is another daemon running (pid = %d, %s)", pfpid, mypid);
		goto end;
	}

	if(create && !pfpid)
	{
		if(-1 == unlink(filename) && errno != ENOENT)
		{
			cc_log_perror(filename);
			pfpid = -1;
			goto end;
		}		

		do {
			const char *slhptr;

			if(NULL != (slhptr = (const char *)strrchr(filename, '/')))
			{
				char        dirnam[slhptr - filename + 1];
				const char *srcptr;
				char       *tgtptr;

				for(tgtptr = dirnam, srcptr = filename; srcptr < slhptr; *(tgtptr++) = *(srcptr++));
				*(tgtptr) = '\0';
				if(-1 == cc_mkpath(dirnam, 0700))
				{
					cc_log_perror(dirnam);
					pfpid = -1;
					goto end;
				}
			}
		} while(0);

		if(NULL == (fdesc = fopen(filename, "w")))
		{
			cc_log_perror(filename);
			pfpid = -1;
			goto end;
		}

		(void)fprintf(fdesc, "%d", (int)mypid);
		(void)fclose(fdesc);

		do {
			char   *bufptr = pidfile;
			size_t  bufsiz = sizeof(pidfile) - 1;
			(void)cc_fmt_string(&bufptr, &bufsiz, filename);
			*bufptr = '\0';
		} while(0);

		(void)atexit(cleanup);
	}	
end:
	return (pid_t)pfpid != mypid ? (pid_t)pfpid : 0;
}
