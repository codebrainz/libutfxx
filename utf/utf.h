/**
 * utf.h - This file is part of LibUTF++
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
 */

#ifndef __UTF_H__
#define __UTF_H__ 1

#if __cplusplus >= 201103L
# define UTF_CXX11 1
#endif

#include <string>
#include <stdexcept>
#include <cwchar>

#ifdef UTF_CXX11
# include <uchar.h>
# include <cstdint>
#else
# include <stdint.h>
#endif

namespace utf
{

typedef char char8;
#if defined(UTF_CXX11)
typedef char16_t char16;
typedef char32_t char32;
#elif defined(WCHAR_MAX)
# if WCHAR_MAX >= 0x10000
typedef uint16_t char16;
typedef wchar_t  char32;
# else
typedef wchar_t  char16;
typedef uint32_t char32;
# endif
#else
typedef uint16_t char16;
typedef uint32_t char32;
#endif

typedef std::basic_string<char8>  string8;
typedef std::basic_string<char16> string16;
typedef std::basic_string<char32> string32;

struct conversion_error : public std::runtime_error {
	enum status {
		source_exhausted=1,
		target_exhausted,
		illegal_input
	};
	explicit conversion_error(status code, const std::string& what_arg)
		: std::runtime_error(what_arg), code_(code) {}
	status code() const { return code_; }
private:
	status code_;
};

struct source_exhausted : public conversion_error {
	source_exhausted()
		: conversion_error(conversion_error::source_exhausted,
			"The source string was exhausted during a partial character") {}
};

struct illegal_input : public conversion_error {
	illegal_input()
		: conversion_error(conversion_error::illegal_input,
			"The input string contains illegal/malformed data.") {}
};

void cvt_8_to_8(const string8& si, string8& so);
void cvt_8_to_16(const string8& si, string16& so);
void cvt_8_to_32(const string8& si, string32& so);

void cvt_8_to_8(const char8* si, string8& so);
void cvt_8_to_16(const char8* si, string16& so);
void cvt_8_to_32(const char8* si, string32& so);

void cvt_16_to_8(const string16& si, string8& so);
void cvt_16_to_16(const string16& si, string16& so);
void cvt_16_to_32(const string16& si, string32& so);

void cvt_16_to_8(const char16* si, string8& so);
void cvt_16_to_16(const char16* si, string16& so);
void cvt_16_to_32(const char16* si, string32& so);

void cvt_32_to_8(const string32& si, string8& so);
void cvt_32_to_16(const string32& si, string16& so);
void cvt_32_to_32(const string32& si, string32& so);

void cvt_32_to_8(const char32* si, string8& so);
void cvt_32_to_16(const char32* si, string16& so);
void cvt_32_to_32(const char32* si, string32& so);

static inline void convert(const string8& in, string8& out)
{
	cvt_8_to_8(in, out);
}

static inline void convert(const string8& in, string16& out)
{
	cvt_8_to_16(in, out);
}

static inline void convert(const string8& in, string32& out)
{
	cvt_8_to_32(in, out);
}

static inline void convert(const string16& in, string8& out)
{
	cvt_16_to_8(in, out);
}

static inline void convert(const string16& in, string16& out)
{
	cvt_16_to_16(in, out);
}

static inline void convert(const string16& in, string32& out)
{
	cvt_16_to_32(in, out);
}

static inline void convert(const string32& in, string8& out)
{
	cvt_32_to_8(in, out);
}

static inline void convert(const string32& in, string16& out)
{
	cvt_32_to_16(in, out);
}

static inline void convert(const string32& in, string32& out)
{
	cvt_32_to_32(in, out);
}

static inline string8 to_utf8(const string8& in)
{
	string8 out;
	convert(in, out);
	return out;
}

static inline string8 to_utf8(const string16& in)
{
	string8 out;
	convert(in, out);
	return out;
}

static inline string8 to_utf8(const string32& in)
{
	string8 out;
	convert(in, out);
	return out;
}

static inline string16 to_utf16(const string8& in)
{
	string16 out;
	convert(in, out);
	return out;
}

static inline string16 to_utf16(const string16& in)
{
	string16 out;
	convert(in, out);
	return out;
}

static inline string16 to_utf16(const string32& in)
{
	string16 out;
	convert(in, out);
	return out;
}

static inline string32 to_utf32(const string8& in)
{
	string32 out;
	convert(in, out);
	return out;
}

static inline string32 to_utf32(const string16& in)
{
	string32 out;
	convert(in, out);
	return out;
}

static inline string32 to_utf32(const string32& in)
{
	string32 out;
	convert(in, out);
	return out;
}

} // namespace

#endif // __UTF_H__
