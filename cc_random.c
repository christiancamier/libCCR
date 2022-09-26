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
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "cc_machdep.h"
#include "cc_src_warning.h"
#include "cc_random.h"

#if !defined(HAVE_ARC4RANDOM)
# if   defined(HAVE__DEV_ARANDOM)
#  define SEED_FILE	"/dev/arandom"
# elif defined(HAVE__DEV_RANDOM)
#  define SEED_FILE	"/dev/random"
# elif defined(HAVE__DEV_URANDOM)
#  define SEED_FILE	"/dev/urandom"
# endif
#endif

extern void          cc_random_init(void);
extern unsigned long cc_random(void);

void cc_random_init(void)
{
#ifdef HAVE_ARC4RANDOM
	arc4random_stir();
#else
	unsigned int seed;
# ifdef SEED_FILE
	int          fdes = -1;
	if(-1 != (fdes = open(SEED_FILE, O_RDONLY)))
	{
		size_t         s;
		ssize_t        n;
		unsigned char *p;
		for(n = 0, p = (unsigned char *)&seed, s = sizeof(unsigned int); s > 0; s -= n, p += n)
		{
			if(1 > (n = read(fdes, (void *)p, s)))
				goto seed_fail;
		}
		close(fdes);
		goto seed_ok;
	}
seed_fail:
	perror(SEED_FILE);
	fprintf(stderr, "Warning: CC_RANDOM - PRNG not properly initialised\n");
	if(fdes != -1)
		close(fdes);
# endif /* SEED_FILE */
	seed = (unsigned int)time(NULL);
# ifdef SEED_FILE
seed_ok:
# endif /* SEED_FILE */
	srandom(seed);
#endif /* HAVE_ARC4RANDOM */
	return;
}

unsigned long cc_random(void)
{
	unsigned long  r;
#ifdef HAVE_ARC4RANDOM
# ifdef ARCH_64BITS
	union {
		unsigned long v64;
		u_int32_t     v32[2];
	} a;
	erase_random_init();
	a.v32[0] = arc4random();
	a.v32[1] = arc4random();
	r = a.v64;
# else
	r = arc4random();
# endif
#else
	unsigned char *p;
	size_t         s;
	for(s = sizeof(unsigned long), p = (unsigned char *)&r; s > 0; s -=1, *(p++) = (unsigned char)(rand() & 0xFF));
#endif
	return r;
}

#ifndef HAVE__ARC4RANDOM
# ifndef SEED_FILE
CC_SRC_WARNING("CC_RANDOM: No strong PRNG found on your host")
# endif
#endif
