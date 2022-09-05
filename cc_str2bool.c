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
#include <strings.h>

#include "cc_str2bool.h"

extern int cc_str2bool(const char *, int, int, int);

static const char *Tvals[] = { "on",  "true",  "yes", NULL };
static const char *Fvals[] = { "off", "false", "no",  NULL };

int cc_str2bool(const char *string, int tval, int fval, int other)
{
	const char **p;
	for(p = Tvals; *p; p += 1)
		if(0 == strcasecmp(string, *p))
			return tval;
	for(p = Fvals; *p; p += 1)
		if(0 == strcasecmp(string, *p))
			return fval;
	return other;
}
