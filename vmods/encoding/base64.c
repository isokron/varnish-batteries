/*-------------------------------------------------------------------------
 *
 * base64.c
 *    Encoding and decoding routines for base64 without whitespace.
 *
 * Copyright (c) 2001-2019, PostgreSQL Global Development Group
 *
 *
 * IDENTIFICATION
 *    src/common/base64.c
 *
 *-------------------------------------------------------------------------
 */

#include <string.h>
#include <inttypes.h>
#include <assert.h>

typedef int8_t int8;
typedef uint32_t uint32;
#define Assert assert

#include "base64.h"

/*
 * BASE64
 */

static const char _base64[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int8 b64lookup[128] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
};

/*
 * pg_b64_encode
 *
 * Encode into base64 the given string.  Returns the length of the encoded
 * string, and -1 in the event of an error with the result buffer zeroed
 * for safety.
 */
int
pg_b64_encode(const char *src, int len, char *dst, int dstlen)
{
    char       *p;
    const char *s,
               *end = src + len;
    int         pos = 2;
    uint32      buf = 0;

    s = src;
    p = dst;

    while (s < end)
    {
        buf |= (unsigned char) *s << (pos << 3);
        pos--;
        s++;

        /* write it out */
        if (pos < 0)
        {
            /*
             * Leave if there is an overflow in the area allocated for the
             * encoded string.
             */
            if ((p - dst + 4) > dstlen)
                goto error;

            *p++ = _base64[(buf >> 18) & 0x3f];
            *p++ = _base64[(buf >> 12) & 0x3f];
            *p++ = _base64[(buf >> 6) & 0x3f];
            *p++ = _base64[buf & 0x3f];

            pos = 2;
            buf = 0;
        }
    }
    if (pos != 2)
    {
        /*
         * Leave if there is an overflow in the area allocated for the encoded
         * string.
         */
        if ((p - dst + 4) > dstlen)
            goto error;

        *p++ = _base64[(buf >> 18) & 0x3f];
        *p++ = _base64[(buf >> 12) & 0x3f];
        *p++ = (pos == 0) ? _base64[(buf >> 6) & 0x3f] : '=';
        *p++ = '=';
    }

    Assert((p - dst) <= dstlen);
    return p - dst;

error:
    memset(dst, 0, dstlen);
    return -1;
}

/*
 * pg_b64_decode
 *
 * Decode the given base64 string.  Returns the length of the decoded
 * string on success, and -1 in the event of an error with the result
 * buffer zeroed for safety.
 */
int
pg_b64_decode(const char *src, int len, char *dst, int dstlen)
{
    const char *srcend = src + len,
               *s = src;
    char       *p = dst;
    char        c;
    int         b = 0;
    uint32      buf = 0;
    int         pos = 0,
                end = 0;

    while (s < srcend)
    {
        c = *s++;

        /* Leave if a whitespace is found */
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
            goto error;

        if (c == '=')
        {
            /* end sequence */
            if (!end)
            {
                if (pos == 2)
                    end = 1;
                else if (pos == 3)
                    end = 2;
                else
                {
                    /*
                     * Unexpected "=" character found while decoding base64
                     * sequence.
                     */
                    goto error;
                }
            }
            b = 0;
        }
        else
        {
            b = -1;
            if (c > 0 && c < 127)
                b = b64lookup[(unsigned char) c];
            if (b < 0)
            {
                /* invalid symbol found */
                goto error;
            }
        }
        /* add it to buffer */
        buf = (buf << 6) + b;
        pos++;
        if (pos == 4)
        {
            /*
             * Leave if there is an overflow in the area allocated for the
             * decoded string.
             */
            if ((p - dst + 1) > dstlen)
                goto error;
            *p++ = (buf >> 16) & 255;

            if (end == 0 || end > 1)
            {
                /* overflow check */
                if ((p - dst + 1) > dstlen)
                    goto error;
                *p++ = (buf >> 8) & 255;
            }
            if (end == 0 || end > 2)
            {
                /* overflow check */
                if ((p - dst + 1) > dstlen)
                    goto error;
                *p++ = buf & 255;
            }
            buf = 0;
            pos = 0;
        }
    }

    if (pos != 0)
    {
        /*
         * base64 end sequence is invalid.  Input data is missing padding, is
         * truncated or is otherwise corrupted.
         */
        goto error;
    }

    Assert((p - dst) <= dstlen);
    return p - dst;

error:
    memset(dst, 0, dstlen);
    return -1;
}

/*
 * pg_b64_enc_len
 *
 * Returns to caller the length of the string if it were encoded with
 * base64 based on the length provided by caller.  This is useful to
 * estimate how large a buffer allocation needs to be done before doing
 * the actual encoding.
 */
int
pg_b64_enc_len(int srclen)
{
    /* 3 bytes will be converted to 4 */
    return (srclen + 2) * 4 / 3;
}

/*
 * pg_b64_dec_len
 *
 * Returns to caller the length of the string if it were to be decoded
 * with base64, based on the length given by caller.  This is useful to
 * estimate how large a buffer allocation needs to be done before doing
 * the actual decoding.
 */
int
pg_b64_dec_len(int srclen)
{
    return (srclen * 3) >> 2;
}


#ifdef TESTRUNNER
#include <stdio.h>
void b64enc_and_dec(char * buf) {
	int enclen = pg_b64_enc_len(strlen(buf)) * 2;
	char encoded[enclen];
	memset(encoded, '\0', enclen);
	int len = pg_b64_encode(buf, strlen(buf), encoded, enclen);
	if (len < 0) return;

	// printf("Encoded text is: \"%s\" (%i bytes in %lu sized buffer)\n", encoded, len, sizeof(encoded));

	int declen = pg_b64_dec_len(strlen(encoded));
	char decoded[declen];
	memset(decoded, '\0', declen);

	len = pg_b64_decode(encoded, strlen(encoded), decoded, declen);
	if (len < 0) return;

    // extern int pg_b64_decode(const char *src, int len, char *dst, int dstlen);
	// printf("Decoded text is: \"%s\" (%d==%lu bytes in %lu byte buffer)", decoded, len, strlen(decoded), sizeof(decoded) );
	return;
}

#include <ctype.h>
#include <sys/types.h>
int LLVMFuzzerTestOneInput(u_int8_t *data, size_t sz) {
	for (int i=0; i<sz; i++) {
		if (data[i] > 128) {
			return(0);
		}
	}
	char buf[sz+1];
	memcpy(buf, data, sz);
	buf[sz+1] = '\0';
	// printf("%s\n", buf);
	b64enc_and_dec(buf);
	return(0);
}
#endif

/*
int main() {
	char foo[] = "super æøå %$! secret string";
	b64enc_and_dec((char *)&foo);
}
*/
