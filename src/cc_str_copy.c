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
 * #@ "cc_str_concat.c"
 *	-- CC Utilities: String concatenation utilities
 *
 * Author : Christian CAMIER
 *
 * Rev : 1.0 (02/05/2008)
 */
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#include "cc_str.h"

extern size_t cc_str_copy(char *, size_t, const char *);

/*
 * NAME:
 *     cc_str_copy - copy a string
 *
 * SYNOPSIS:
 *     #include <sys/types.h>
 *     #include <cc_str.h>
 *
 *     size_t cc_str_copy(char *target, size_t target_size, const char *source);
 *
 * DESCRIPTION:
 *     The cc_str_copy function copy the `source' string to the `target'
 *     string including the trailing '\0'.
 *
 *     Arguments:
 *     - target:      The target string
 *     - target_size: The size of the space pointed by `target'
 *     - source:      The string that will be appended to `target'
 *
 * RETURN VALUE:
 *     Returns the number of characters (including the trailing '\0') added
 *     to `target'.
 *     The function cc_str_concat does not write more than allowed size of
 *     the target (included the trailing '\0'. If the source was truncated
 *     due this limit, then the return value is the number of characters
 *     (including the trailing '\0') which would have been appended to the
 *     target string if enough space had been available.
 */
size_t cc_str_copy(char *target, size_t tgtsize, const char *source)
{
	size_t  n;
	char   *d;
	char   *s;

	n = tgtsize - 1;
	d = target;
	s = (char *)source;

	while(n > 0 && *s != '\0')
		*(d++) = *(s++), n--;
	*(d++) = '\0';
	return strlen(source) + 1;
}
