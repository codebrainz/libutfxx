/**
 * utf.cxx - This file is part of LibUTF++
 *
 * Copyright (c) 2014 Matthew Brush <mbrush@codebrainz.ca>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * See also the Unicode Inc. license comments embedded in the "ConvertUTF.h
 * Header" and "ConvertUTF.c Source File" sections below.
 *
 * This is version 0.1, generated on 2014-08-26 02:05:52.796996.
 */

#include "utf.h"
#include <cassert>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// ConvertUTF.h Header                                                      //
//////////////////////////////////////////////////////////////////////////////

typedef utf::char8 UTF8;
typedef utf::char16 UTF16;
typedef utf::char32 UTF32;

/*
 * Copyright 2001-2004 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/* ---------------------------------------------------------------------

	Conversions between UTF32, UTF-16, and UTF-8.  Header file.

	Several funtions are included here, forming a complete set of
	conversions between the three formats.  UTF-7 is not included
	here, but is handled in a separate source file.

	Each of these routines takes pointers to input buffers and output
	buffers.  The input buffers are const.

	Each routine converts the text between *sourceStart and sourceEnd,
	putting the result into the buffer between *targetStart and
	targetEnd. Note: the end pointers are *after* the last item: e.g.
	*(sourceEnd - 1) is the last item.

	The return result indicates whether the conversion was successful,
	and if not, whether the problem was in the source or target buffers.
	(Only the first encountered problem is indicated.)

	After the conversion, *sourceStart and *targetStart are both
	updated to point to the end of last text successfully converted in
	the respective buffers.

	Input parameters:
	sourceStart - pointer to a pointer to the source buffer.
		The contents of this are modified on return so that
		it points at the next thing to be converted.
	targetStart - similarly, pointer to pointer to the target buffer.
	sourceEnd, targetEnd - respectively pointers to the ends of the
		two buffers, for overflow checking only.

	These conversion functions take a ConversionFlags argument. When this
	flag is set to strict, both irregular sequences and isolated surrogates
	will cause an error.  When the flag is set to lenient, both irregular
	sequences and isolated surrogates are converted.

	Whether the flag is strict or lenient, all illegal sequences will cause
	an error return. This includes sequences such as: <F4 90 80 80>, <C0 80>,
	or <A0> in UTF-8, and values above 0x10FFFF in UTF-32. Conformant code
	must check for illegal sequences.

	When the flag is set to lenient, characters over 0x10FFFF are converted
	to the replacement character; otherwise (when the flag is set to strict)
	they constitute an error.

	Output parameters:
	The value "sourceIllegal" is returned from some routines if the input
	sequence is malformed.  When "sourceIllegal" is returned, the source
	value will point to the illegal value that caused the problem. E.g.,
	in UTF-8 when a sequence is malformed, it points to the start of the
	malformed sequence.

	Author: Mark E. Davis, 1994.
	Rev History: Rick McGowan, fixes & updates May 2001.
		 Fixes & updates, Sept 2001.

------------------------------------------------------------------------ */

/* ---------------------------------------------------------------------
	The following 4 definitions are compiler-specific.
	The C standard does not guarantee that wchar_t has at least
	16 bits, so wchar_t is no less portable than unsigned short!
	All should be unsigned values to avoid sign extension during
	bit mask & shift operations.
------------------------------------------------------------------------ */

#define CONVERT_UTF_H_INCLUDED_ 1

#include <stdint.h>

typedef unsigned char	Boolean; /* 0 or 1 */

/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (UTF32)0x0010FFFF

typedef enum {
	conversionOK, 		/* conversion successful */
	sourceExhausted,	/* partial character in source, but hit end */
	targetExhausted,	/* insuff. room in target for conversion */
	sourceIllegal		/* source sequence is illegal/malformed */
} ConversionResult;

typedef enum {
	strictConversion = 0,
	lenientConversion
} ConversionFlags;

/* This is for C++ and does no harm in C */
#ifdef __cplusplus
extern "C" {
#endif

ConversionResult ConvertUTF8toUTF16 (
		const UTF8** sourceStart, const UTF8* sourceEnd,
		UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF8 (
		const UTF16** sourceStart, const UTF16* sourceEnd,
		UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF8toUTF32 (
		const UTF8** sourceStart, const UTF8* sourceEnd,
		UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF8 (
		const UTF32** sourceStart, const UTF32* sourceEnd,
		UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF32 (
		const UTF16** sourceStart, const UTF16* sourceEnd,
		UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF16 (
		const UTF32** sourceStart, const UTF32* sourceEnd,
		UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd);

#ifdef __cplusplus
}
#endif

/* --------------------------------------------------------------------- */

//////////////////////////////////////////////////////////////////////////////
// ConvertUTF.h Source File                                                 //
//////////////////////////////////////////////////////////////////////////////

/*
 * Copyright 2001-2004 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/* ---------------------------------------------------------------------

	Conversions between UTF32, UTF-16, and UTF-8. Source code file.
	Author: Mark E. Davis, 1994.
	Rev History: Rick McGowan, fixes & updates May 2001.
	Sept 2001: fixed const & error conditions per
	mods suggested by S. Parent & A. Lillich.
	June 2002: Tim Dodd added detection and handling of incomplete
	source sequences, enhanced error detection, added casts
	to eliminate compiler warnings.
	July 2003: slight mods to back out aggressive FFFE detection.
	Jan 2004: updated switches in from-UTF8 conversions.
	Oct 2004: updated to use UNI_MAX_LEGAL_UTF32 in UTF-32 conversions.

	See the header file "ConvertUTF.h" for complete documentation.

------------------------------------------------------------------------ */

#define CONVERT_UTF_C_INCLUDED_ 1

#ifdef CVTUTF_DEBUG
#include <stdio.h>
#endif

static const int halfShift  = 10; /* used for shifting by 10 bits */

static const UTF32 halfBase = 0x0010000UL;
static const UTF32 halfMask = 0x3FFUL;

#define UNI_SUR_HIGH_START  (UTF32)0xD800
#define UNI_SUR_HIGH_END    (UTF32)0xDBFF
#define UNI_SUR_LOW_START   (UTF32)0xDC00
#define UNI_SUR_LOW_END     (UTF32)0xDFFF
#define false	   0
#define true	    1

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF32toUTF16 (
	const UTF32** sourceStart, const UTF32* sourceEnd,
	UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
	ConversionResult result = conversionOK;
	const UTF32* source = *sourceStart;
	UTF16* target = *targetStart;
	while (source < sourceEnd) {
	UTF32 ch;
	if (target >= targetEnd) {
		result = targetExhausted; break;
	}
	ch = *source++;
	if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
		/* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
		if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
		if (flags == strictConversion) {
			--source; /* return to the illegal value itself */
			result = sourceIllegal;
			break;
		} else {
			*target++ = UNI_REPLACEMENT_CHAR;
		}
		} else {
		*target++ = (UTF16)ch; /* normal case */
		}
	} else if (ch > UNI_MAX_LEGAL_UTF32) {
		if (flags == strictConversion) {
		result = sourceIllegal;
		} else {
		*target++ = UNI_REPLACEMENT_CHAR;
		}
	} else {
		/* target is a character in range 0xFFFF - 0x10FFFF. */
		if (target + 1 >= targetEnd) {
		--source; /* Back up source pointer! */
		result = targetExhausted; break;
		}
		ch -= halfBase;
		*target++ = (UTF16)((ch >> halfShift) + UNI_SUR_HIGH_START);
		*target++ = (UTF16)((ch & halfMask) + UNI_SUR_LOW_START);
	}
	}
	*sourceStart = source;
	*targetStart = target;
	return result;
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF16toUTF32 (
	const UTF16** sourceStart, const UTF16* sourceEnd,
	UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
	ConversionResult result = conversionOK;
	const UTF16* source = *sourceStart;
	UTF32* target = *targetStart;
	UTF32 ch, ch2;
	while (source < sourceEnd) {
	const UTF16* oldSource = source; /*  In case we have to back up because of target overflow. */
	ch = *source++;
	/* If we have a surrogate pair, convert to UTF32 first. */
	if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END) {
		/* If the 16 bits following the high surrogate are in the source buffer... */
		if (source < sourceEnd) {
		ch2 = *source;
		/* If it's a low surrogate, convert to UTF32. */
		if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
			ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
			+ (ch2 - UNI_SUR_LOW_START) + halfBase;
			++source;
		} else if (flags == strictConversion) { /* it's an unpaired high surrogate */
			--source; /* return to the illegal value itself */
			result = sourceIllegal;
			break;
		}
		} else { /* We don't have the 16 bits following the high surrogate. */
		--source; /* return to the high surrogate */
		result = sourceExhausted;
		break;
		}
	} else if (flags == strictConversion) {
		/* UTF-16 surrogate values are illegal in UTF-32 */
		if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END) {
		--source; /* return to the illegal value itself */
		result = sourceIllegal;
		break;
		}
	}
	if (target >= targetEnd) {
		source = oldSource; /* Back up source pointer! */
		result = targetExhausted; break;
	}
	*target++ = ch;
	}
	*sourceStart = source;
	*targetStart = target;
#ifdef CVTUTF_DEBUG
if (result == sourceIllegal) {
	fprintf(stderr, "ConvertUTF16toUTF32 illegal seq 0x%04x,%04x\n", ch, ch2);
	fflush(stderr);
}
#endif
	return result;
}

/* --------------------------------------------------------------------- */

/*
 * Index into the table below with the first byte of a UTF-8 sequence to
 * get the number of trailing bytes that are supposed to follow it.
 * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
 * left as-is for anyone who may want to do such conversion, which was
 * allowed in earlier algorithms.
 */
static const char trailingBytesForUTF8[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/*
 * Magic values subtracted from a buffer value during UTF8 conversion.
 * This table contains as many values as there might be trailing bytes
 * in a UTF-8 sequence.
 */
static const UTF32 offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
			 0x03C82080UL, 0xFA082080UL, 0x82082080UL };

/*
 * Once the bits are split out into bytes of UTF-8, this is a mask OR-ed
 * into the first byte, depending on how many bytes follow.  There are
 * as many entries in this table as there are UTF-8 sequence types.
 * (I.e., one byte sequence, two byte... etc.). Remember that sequencs
 * for *legal* UTF-8 will be 4 or fewer bytes total.
 */
static const UTF8 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

/* --------------------------------------------------------------------- */

/* The interface converts a whole buffer to avoid function-call overhead.
 * Constants have been gathered. Loops & conditionals have been removed as
 * much as possible for efficiency, in favor of drop-through switches.
 * (See "Note A" at the bottom of the file for equivalent code.)
 * If your compiler supports it, the "isLegalUTF8" call can be turned
 * into an inline function.
 */

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF16toUTF8 (
	const UTF16** sourceStart, const UTF16* sourceEnd,
	UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags) {
	ConversionResult result = conversionOK;
	const UTF16* source = *sourceStart;
	UTF8* target = *targetStart;
	while (source < sourceEnd) {
	UTF32 ch;
	unsigned short bytesToWrite = 0;
	const UTF32 byteMask = 0xBF;
	const UTF32 byteMark = 0x80;
	const UTF16* oldSource = source; /* In case we have to back up because of target overflow. */
	ch = *source++;
	/* If we have a surrogate pair, convert to UTF32 first. */
	if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END) {
		/* If the 16 bits following the high surrogate are in the source buffer... */
		if (source < sourceEnd) {
		UTF32 ch2 = *source;
		/* If it's a low surrogate, convert to UTF32. */
		if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
			ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
			+ (ch2 - UNI_SUR_LOW_START) + halfBase;
			++source;
		} else if (flags == strictConversion) { /* it's an unpaired high surrogate */
			--source; /* return to the illegal value itself */
			result = sourceIllegal;
			break;
		}
		} else { /* We don't have the 16 bits following the high surrogate. */
		--source; /* return to the high surrogate */
		result = sourceExhausted;
		break;
		}
	} else if (flags == strictConversion) {
		/* UTF-16 surrogate values are illegal in UTF-32 */
		if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END) {
		--source; /* return to the illegal value itself */
		result = sourceIllegal;
		break;
		}
	}
	/* Figure out how many bytes the result will require */
	if (ch < (UTF32)0x80) {	     bytesToWrite = 1;
	} else if (ch < (UTF32)0x800) {     bytesToWrite = 2;
	} else if (ch < (UTF32)0x10000) {   bytesToWrite = 3;
	} else if (ch < (UTF32)0x110000) {  bytesToWrite = 4;
	} else {			    bytesToWrite = 3;
						ch = UNI_REPLACEMENT_CHAR;
	}

	target += bytesToWrite;
	if (target > targetEnd) {
		source = oldSource; /* Back up source pointer! */
		target -= bytesToWrite; result = targetExhausted; break;
	}
	switch (bytesToWrite) { /* note: everything falls through. */
		case 4: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 3: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 2: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 1: *--target =  (UTF8)(ch | firstByteMark[bytesToWrite]);
	}
	target += bytesToWrite;
	}
	*sourceStart = source;
	*targetStart = target;
	return result;
}

/* --------------------------------------------------------------------- */

/*
 * Utility routine to tell whether a sequence of bytes is legal UTF-8.
 * This must be called with the length pre-determined by the first byte.
 * If not calling this from ConvertUTF8to*, then the length can be set by:
 *  length = trailingBytesForUTF8[*source]+1;
 * and the sequence is illegal right away if there aren't that many bytes
 * available.
 * If presented with a length > 4, this returns false.  The Unicode
 * definition of UTF-8 goes up to 4-byte sequences.
 */

static Boolean isLegalUTF8(const UTF8 *source, int length) {
	UTF8 a;
	const UTF8 *srcptr = source+length;
	switch (length) {
	default: return false;
	/* Everything else falls through when "true"... */
	case 4: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
	case 3: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
	case 2: if ((a = (*--srcptr)) > 0xBF) return false;

	switch ((unsigned char) *source) {
		/* no fall-through in this inner switch */
		case 0xE0: if (a < 0xA0) return false; break;
		case 0xED: if (a > 0x9F) return false; break;
		case 0xF0: if (a < 0x90) return false; break;
		case 0xF4: if (a > 0x8F) return false; break;
		default:   if (a < 0x80) return false;
	}

	case 1: if (*source >= 0x80 && *source < 0xC2) return false;
	}
	if (*source > 0xF4) return false;
	return true;
}

/* --------------------------------------------------------------------- */

/*
 * Exported function to return whether a UTF-8 sequence is legal or not.
 * This is not used here; it's just exported.
 */
Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd) {
	int length = trailingBytesForUTF8[*source]+1;
	if (source+length > sourceEnd) {
	return false;
	}
	return isLegalUTF8(source, length);
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF8toUTF16 (
	const UTF8** sourceStart, const UTF8* sourceEnd,
	UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
	ConversionResult result = conversionOK;
	const UTF8* source = *sourceStart;
	UTF16* target = *targetStart;
	while (source < sourceEnd) {
	UTF32 ch = 0;
	unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
	if (source + extraBytesToRead >= sourceEnd) {
		result = sourceExhausted; break;
	}
	/* Do this check whether lenient or strict */
	if (! isLegalUTF8(source, extraBytesToRead+1)) {
		result = sourceIllegal;
		break;
	}
	/*
	 * The cases all fall through. See "Note A" below.
	 */
	switch (extraBytesToRead) {
		case 5: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
		case 4: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
		case 3: ch += *source++; ch <<= 6;
		case 2: ch += *source++; ch <<= 6;
		case 1: ch += *source++; ch <<= 6;
		case 0: ch += *source++;
	}
	ch -= offsetsFromUTF8[extraBytesToRead];

	if (target >= targetEnd) {
		source -= (extraBytesToRead+1); /* Back up source pointer! */
		result = targetExhausted; break;
	}
	if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
		/* UTF-16 surrogate values are illegal in UTF-32 */
		if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
		if (flags == strictConversion) {
			source -= (extraBytesToRead+1); /* return to the illegal value itself */
			result = sourceIllegal;
			break;
		} else {
			*target++ = UNI_REPLACEMENT_CHAR;
		}
		} else {
		*target++ = (UTF16)ch; /* normal case */
		}
	} else if (ch > UNI_MAX_UTF16) {
		if (flags == strictConversion) {
		result = sourceIllegal;
		source -= (extraBytesToRead+1); /* return to the start */
		break; /* Bail out; shouldn't continue */
		} else {
		*target++ = UNI_REPLACEMENT_CHAR;
		}
	} else {
		/* target is a character in range 0xFFFF - 0x10FFFF. */
		if (target + 1 >= targetEnd) {
		source -= (extraBytesToRead+1); /* Back up source pointer! */
		result = targetExhausted; break;
		}
		ch -= halfBase;
		*target++ = (UTF16)((ch >> halfShift) + UNI_SUR_HIGH_START);
		*target++ = (UTF16)((ch & halfMask) + UNI_SUR_LOW_START);
	}
	}
	*sourceStart = source;
	*targetStart = target;
	return result;
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF32toUTF8 (
	const UTF32** sourceStart, const UTF32* sourceEnd,
	UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags) {
	ConversionResult result = conversionOK;
	const UTF32* source = *sourceStart;
	UTF8* target = *targetStart;
	while (source < sourceEnd) {
	UTF32 ch;
	unsigned short bytesToWrite = 0;
	const UTF32 byteMask = 0xBF;
	const UTF32 byteMark = 0x80;
	ch = *source++;
	if (flags == strictConversion ) {
		/* UTF-16 surrogate values are illegal in UTF-32 */
		if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
		--source; /* return to the illegal value itself */
		result = sourceIllegal;
		break;
		}
	}
	/*
	 * Figure out how many bytes the result will require. Turn any
	 * illegally large UTF32 things (> Plane 17) into replacement chars.
	 */
	if (ch < (UTF32)0x80) {	     bytesToWrite = 1;
	} else if (ch < (UTF32)0x800) {     bytesToWrite = 2;
	} else if (ch < (UTF32)0x10000) {   bytesToWrite = 3;
	} else if (ch <= UNI_MAX_LEGAL_UTF32) {  bytesToWrite = 4;
	} else {			    bytesToWrite = 3;
						ch = UNI_REPLACEMENT_CHAR;
						result = sourceIllegal;
	}

	target += bytesToWrite;
	if (target > targetEnd) {
		--source; /* Back up source pointer! */
		target -= bytesToWrite; result = targetExhausted; break;
	}
	switch (bytesToWrite) { /* note: everything falls through. */
		case 4: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 3: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 2: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 1: *--target = (UTF8) (ch | firstByteMark[bytesToWrite]);
	}
	target += bytesToWrite;
	}
	*sourceStart = source;
	*targetStart = target;
	return result;
}

/* --------------------------------------------------------------------- */

ConversionResult ConvertUTF8toUTF32 (
	const UTF8** sourceStart, const UTF8* sourceEnd,
	UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
	ConversionResult result = conversionOK;
	const UTF8* source = *sourceStart;
	UTF32* target = *targetStart;
	while (source < sourceEnd) {
	UTF32 ch = 0;
	unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
	if (source + extraBytesToRead >= sourceEnd) {
		result = sourceExhausted; break;
	}
	/* Do this check whether lenient or strict */
	if (! isLegalUTF8(source, extraBytesToRead+1)) {
		result = sourceIllegal;
		break;
	}
	/*
	 * The cases all fall through. See "Note A" below.
	 */
	switch (extraBytesToRead) {
		case 5: ch += *source++; ch <<= 6;
		case 4: ch += *source++; ch <<= 6;
		case 3: ch += *source++; ch <<= 6;
		case 2: ch += *source++; ch <<= 6;
		case 1: ch += *source++; ch <<= 6;
		case 0: ch += *source++;
	}
	ch -= offsetsFromUTF8[extraBytesToRead];

	if (target >= targetEnd) {
		source -= (extraBytesToRead+1); /* Back up the source pointer! */
		result = targetExhausted; break;
	}
	if (ch <= UNI_MAX_LEGAL_UTF32) {
		/*
		 * UTF-16 surrogate values are illegal in UTF-32, and anything
		 * over Plane 17 (> 0x10FFFF) is illegal.
		 */
		if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
		if (flags == strictConversion) {
			source -= (extraBytesToRead+1); /* return to the illegal value itself */
			result = sourceIllegal;
			break;
		} else {
			*target++ = UNI_REPLACEMENT_CHAR;
		}
		} else {
		*target++ = ch;
		}
	} else { /* i.e., ch > UNI_MAX_LEGAL_UTF32 */
		result = sourceIllegal;
		*target++ = UNI_REPLACEMENT_CHAR;
	}
	}
	*sourceStart = source;
	*targetStart = target;
	return result;
}

/* ---------------------------------------------------------------------

	Note A.
	The fall-through switches in UTF-8 reading code save a
	temp variable, some decrements & conditionals.  The switches
	are equivalent to the following loop:
	{
		int tmpBytesToRead = extraBytesToRead+1;
		do {
		ch += *source++;
		--tmpBytesToRead;
		if (tmpBytesToRead) ch <<= 6;
		} while (tmpBytesToRead > 0);
	}
	In UTF-8 writing code, the switches on "bytesToWrite" are
	similarly unrolled loops.

   --------------------------------------------------------------------- */

//////////////////////////////////////////////////////////////////////////////
// C++ wrapper                                                              //
//////////////////////////////////////////////////////////////////////////////

#ifndef CONVERT_UTF_H_INCLUDED_
# error "Missing ConvertUTF.h contents in utf.cxx, did you forget to process utf.cxx.in?"
#endif

#ifndef CONVERT_UTF_C_INCLUDED_
# error "Missing ConvertUTF.c contents in utf.cxx, did you forget to process utf.cxx.in?"
#endif

#include <algorithm>
#include <cstring>

namespace utf
{

typedef ConversionResult (*Func8to16)(
		const UTF8** sourceStart, const UTF8* sourceEnd,
		UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

typedef ConversionResult (*Func16to8)(
		const UTF16** sourceStart, const UTF16* sourceEnd,
		UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

typedef ConversionResult (*Func8to32)(
		const UTF8** sourceStart, const UTF8* sourceEnd,
		UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

typedef ConversionResult (*Func32to8)(
		const UTF32** sourceStart, const UTF32* sourceEnd,
		UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

typedef ConversionResult (*Func16to32)(
		const UTF16** sourceStart, const UTF16* sourceEnd,
		UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

typedef ConversionResult (*Func32to16)(
		const UTF32** sourceStart, const UTF32* sourceEnd,
		UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

static const size_t buf_size = 32;
static ConversionFlags conv_flags = strictConversion;

template< typename T >
static size_t measure_nulterm(const T* p)
{
	const T* iter = p;
	size_t length = 0;
	while (*iter++)
		length++;
	return length;
}

template< typename InCharT,
          typename OutCharT,
          typename FuncT,
          size_t   BufSize >
void convert_ptr_(const InCharT* in, size_t in_size, std::basic_string<OutCharT>& out, FuncT cvt_func)
{
	OutCharT buf[BufSize] = {0};
	const InCharT* ss = in;
	const InCharT* se = ss + in_size;
	OutCharT* ts = &buf[0];
	OutCharT* te = ts + BufSize;

	while (true)
	{
		ConversionResult r = cvt_func(&ss, se, &ts, te, conv_flags);
		size_t len = ts - &buf[0];
		switch (r)
		{
			case conversionOK:
				out.append(buf, len);
				return;
			case sourceExhausted:
				throw source_exhausted();
			case targetExhausted:
				out.append(buf, len);
				ts = &buf[0];
				continue;
			case sourceIllegal:
				throw illegal_input();
		}
	}
}

template< typename InCharT,
          typename OutCharT,
          typename FuncT,
          size_t   BufSize >
void convert_(const std::basic_string<InCharT>& in, std::basic_string<OutCharT>& out, FuncT cvt_func)
{
	convert_ptr_<InCharT, OutCharT, FuncT, BufSize>(in.c_str(), in.size(), out, cvt_func);
}

void cvt_8_to_8(const string8& si, string8& so)
{
	so = si;
}

void cvt_8_to_16(const string8& si, string16& so)
{
	convert_<char8, char16, Func8to16, buf_size>(si, so, (Func8to16) ConvertUTF8toUTF16);
}

void cvt_8_to_32(const string8& si, string32& so)
{
	convert_<char8, char32, Func8to32, buf_size>(si, so, (Func8to32) ConvertUTF8toUTF32);
}

void cvt_8_to_8(const char8* si, string8& so)
{
	assert(si);
	so = si;
}

void cvt_8_to_16(const char8* si, string16& so)
{
	assert(si);
	convert_ptr_<char8, char16, Func8to16, buf_size>(
		si, measure_nulterm(si), so, (Func8to16) ConvertUTF8toUTF16);
}

void cvt_8_to_32(const char8* si, string32& so)
{
	assert(si);
	convert_ptr_<char8, char32, Func8to32, buf_size>(
		si, measure_nulterm(si), so, (Func8to32) ConvertUTF8toUTF32);
}

void cvt_16_to_8(const string16& si, string8& so)
{
	convert_<char16, char8, Func16to8, buf_size>(si, so, (Func16to8) ConvertUTF16toUTF8);
}

void cvt_16_to_16(const string16& si, string16& so)
{
	so = si;
}

void cvt_16_to_32(const string16& si, string32& so)
{
	convert_<char16, char32, Func16to32, buf_size>(si, so, (Func16to32) ConvertUTF16toUTF32);
}

void cvt_16_to_8(const char16* si, string8& so)
{
	assert(si);
	convert_ptr_<char16, char8, Func16to8, buf_size>(
		si, measure_nulterm(si), so, (Func16to8) ConvertUTF16toUTF8);
}

void cvt_16_to_16(const char16* si, string16& so)
{
	assert(si);
	so = si;
}

void cvt_16_to_32(const char16* si, string32& so)
{
	assert(si);
	convert_ptr_<char16, char32, Func16to32, buf_size>(
		si, measure_nulterm(si), so, (Func16to32) ConvertUTF16toUTF32);
}

void cvt_32_to_8(const string32& si, string8& so)
{
	convert_<char32, char8, Func32to8, buf_size>(si, so, (Func32to8) ConvertUTF32toUTF8);
}

void cvt_32_to_16(const string32& si, string16& so)
{
	convert_<char32, char16, Func32to16, buf_size>(si, so, (Func32to16) ConvertUTF32toUTF16);
}

void cvt_32_to_32(const string32& si, string32& so)
{
	so = si;
}

void cvt_32_to_8(const char32* si, string8& so)
{
	assert(si);
	convert_ptr_<char32, char8, Func32to8, buf_size>(
		si, measure_nulterm(si), so, (Func32to8) ConvertUTF32toUTF8);
}

void cvt_32_to_16(const char32* si, string16& so)
{
	assert(si);
	convert_ptr_<char32, char16, Func32to16, buf_size>(
		si, measure_nulterm(si), so, (Func32to16) ConvertUTF32toUTF16);
}

void cvt_32_to_32(const char32* si, string32& so)
{
	assert(si);
	so = si;
}

} // namespace utf
