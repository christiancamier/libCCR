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
 * NOTE
 *	This source file exists only for documentation purpose
 */

/*
 * NAME
 *	cc_fmt_bytes, cc_fmt_char, cc_fmt_crlf, cc_fmt_hexdump, cc_fmt_int, cc_fmt_long, cc_fmt_short, cc_fmt_sint08,
 *	cc_fmt_sint16, cc_fmt_sint32, cc_fmt_sint64, cc_fmt_string, cc_fmt_ubytes, cc_fmt_uchar, cc_fmt_uint, cc_fmt_uint08,
 *	cc_fmt_uint16, cc_fmt_uint32, cc_fmt_uint64, cc_fmt_ulong, cc_fmt_ushort - Buffer data formating
 *
 * SYNOPSIS
 *	#include <sys/types.h>
 *	#include <stdint.h>
 *	#include <cc_fmt.h>
 *	ssize_t cc_fmt_bytes(char **buffer, size_t *bufsiz, const char *value, size_t valsz);
 *	ssize_t cc_fmt_char(char **buffer, size_t *bufsiz, char value);
 *	ssize_t cc_fmt_crlf(char **buffer, size_t *bufsiz);
 *	ssize_t cc_fmt_hexdump(char **buffer, size_t *bufsiz, const unsigned char *value, size_t valsiz);
 *	ssize_t cc_fmt_int(char **buffer, size_t *bufsiz, int value, int base);
 *	ssize_t cc_fmt_long(char **buffer, size_t *bufsiz, long value, int base);
 *	ssize_t cc_fmt_short(char **buffer, size_t *bufsiz, short value, int base);
 *	ssize_t cc_fmt_sint08(char **buffer, size_t *bufsiz, int8_t value, int base);
 *	ssize_t cc_fmt_sint16(char **buffer, size_t *bufsiz, int16_t value, int base);
 *	ssize_t cc_fmt_sint32(char **buffer, size_t *bufsiz, int32_t value, int base);
 *	ssize_t cc_fmt_sint64(char **buffer, size_t *bufsiz, int64_t value, int base);
 *	ssize_t cc_fmt_string(char **buffer, size_t *bufsiz, const char *value);
 *	ssize_t cc_fmt_ubytes(char **buffer, size_t *bufsiz, const unsigned char *value, size_t valsz);
 *	ssize_t cc_fmt_uchar(char **buffer, size_t *bufsiz, unsigned char value);
 *	ssize_t cc_fmt_uint(char **buffer, size_t *bufsiz, unsigned int value, int base);
 *	ssize_t cc_fmt_uint08(char **buffer, size_t *bufsiz, uint8_t value, int base);
 *	ssize_t cc_fmt_uint16(char **buffer, size_t *bufsiz, uint16_t value, int base);
 *	ssize_t cc_fmt_uint32(char **buffer, size_t *bufsiz, uint32_t value, int base);
 *	ssize_t cc_fmt_uint64(char **buffer, size_t *bufsiz, uint64_t value, int base);
 *	ssize_t cc_fmt_ulong(char **buffer, size_t *bufsiz, unsigned long value, int base);
 *	ssize_t cc_fmt_ushort(char **buffer, size_t *bufsiz, unsigned short value, int base);
 *
 * DESCRIPTION
 *
 * RETURN VALUE
 *
 */
