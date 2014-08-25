LibUTF++
========

LibUTF++ is a simple C++ library for converting between [UTF-8][utf8],
[UTF-16][utf16], and [UTF-32][utf32] encodings. The API consists of a set
of free functions taking particular `std::basic_string` specialized types
depending on the encoding.

[utf8]: http://en.wikipedia.org/wiki/UTF-8
[utf16]: http://en.wikipedia.org/wiki/UTF-16
[utf32]: http://en.wikipedia.org/wiki/UTF-32

Using LibUTF++ in your Project
------------------------------

The recommended way to use LibUTF++ is to copy the (generated) `utf.cxx` file
and the header `utf.h` into your own project tree and compile them with your
existing build system. This is the intended way to use LibUTF++ since it
reduces distribution and versioning complexities and compatibility problems
from using different compilers and such, even if it's not a best practice on
all platforms.

Using the shared library
------------------------

LibUTF++ comes with a very simple GNU Make build system that can compile
LibUTF++ as a shared library for UNIX-like platforms. To compile the library
simply run `make` from the source directory.

Dependencies
------------

Not much, basically any relatively modern C++ compiler should do.

To use the GNU Make build system requires:

- GNU Make
- A GCC-like C++ compiler
- sed (to process `utf.cxx.in`)
- Various other UNIX-like tools (cp, rm, etc)

WTF are the ConvertUTF.[ch] files?
----------------------------------

The files `ConvertUTF.c` and `ConvertUTF.h` are plain C files that contain
algorithms for converting between UTF encodings. They used to be distributed
on the official Unicode website but are no longer hosted or supported.

Several projects include these same files in their source tree such as
[LLVM/Clang/LLDB][llvm] and [Gears][gears] (the top hits I found when search
Google for "ConvertUTF.c"). I chose to use these existing conversion routines
rather than re-write them myself from scratch (likely much, much more buggy)
or cobble together routines from several different sources. Some day it would
be nice to remove these files and just use the features built in to standard
C++.

To make distribution simpler I have chose to inline these files straight
into the C++ code to avoid numerous files and to possibly provide some more
optimization oportunities for the optimizing compiler. This is similar to the
[SQLite Amalgamation][sqlite].

[llvm]: http://llvm.org/docs/doxygen/html/ConvertUTF_8c_source.html
[gears]: http://gears.googlecode.com/svn/trunk/third_party/convert_utf/ConvertUTF.c
[sqlite]: http://www.sqlite.org/amalgamation.html

Similar and Related Projects
----------------------------

There are many open source and commercial alternatives to LibUTF++, I can
recommened the following projects:

- [UTF8-CPP][utf8cpp]: A nice and simple to use header-only library that provides
routines to convert to and from UTF-8.
- [ICU][icu]: If you need full-blown Unicode support (and more), you probably
won't find a better library than this.

[utf8cpp]: http://utfcpp.sourceforge.net/
[icu]: http://site.icu-project.org/

The API
-------

The functions exposed are very simple to use and are intended to convert
between UTF encodings of whole strings at time. To do streaming-style
conversion of massive amounts of data, consider using the ConvertUTF.[ch]
files directly or using a much better library like ICU.

When the API refers to the numbers 8, 16, and 32, it's referring to the
UTF-8, UTF-16, and UTF-32 encodings, respectively.

### Types

The `utf.h` header typedef's a few types in the `utf` namespace.

#### utf::char8

This is always typedef'd to the builtin C++ `char` type.

#### utf::char16

This is typedef'd differently depending on the compiler's support for C++11
and the size of `wchar_t`. When C++11 support is enabled, this is typedef'd
to `char16_t` (from `cuchar` header), otherwise if the platform uses a 16-bit
`wchar_t` type (ex. Win32), it's typedef'd to that. In all other cases it's
typedef'd to the `uint16_t` type.

When using C++11 mode, you can use the u""-style Unicode string literals
with this type, or else if in 16-bit `wchar_t` mode (ex. Win32) you can use
wide character string literals L"" (not recommended).

#### utf::char32

This is just like `utf::char16` except it's it's 32-bits wide and so uses
`char32_t` in C++11 mode, `wchar_t` if in 32-bit `wchar_t` mode (ex. Linux
and most UNIXes), or `uint32_t` otherwise.

When using C++11 mode, you can use the U""-style Unicode string literals
with this type, or else if in 32-bit `wchar_t` mode you can use wide character
string literals L"" (not recommended).

#### utf::string8

This is a typedef of `std::basic_string<char8>`, which is the same as the
`std::string` type.

#### utf::string16

This is a typedef of `std::basic_string<char16>`, which, depending on the
`utf::char16` type may be equivalent to `std::u16string`, `std::wstring`
or `std::basic_string<uint16_t>`.

#### utf::string32

This is a typedef of `std::basic_string<char32>`, which, depending on the
`utf::char32` type may be equivalent to `std::u32string`, `std::wstring`
or `std::basic_string<uint32_t>`.

#### utf::conversion_error

This is the top-level exception and any exceptions in the API inherit from
this. It itself derives from `std::runtime_error` and so provides the
`what()` member function to retrieve a string explaining the exception. It
also provides a `code()` member function which gives an error number based
on the ConvertUTF.[ch] result type (mostly useless in C++, just catch the
specific dervied exception type).

#### utf::source_exhausted

This type of exception is thrown when the end of the input string is reached
in the middle of decoding a code point. This class derives from
`utf::conversion_error`.

#### utf::illegal_input

This type of exception is thrown when invalid UTF-encoded data is encountered
in the input string. This class derives from `utf::conversion_error`.

### Conversion Functions

There's a few different types of functions that can be used to perform the
conversions, which one to use is mostly a matter of taste/style and mostly
they are simple inline wrappers around the type-specific conversion functions.

#### Type-specific Conversion Functions

These functions are named according to the input and output encoding. You
probably won't want to use these directly but rather through the `utf::convert()`
function.

The prototype of these functions are like:

	void cvt_N1_to_N2(const utf::stringN1& in, utf::stringN2& out);

Where N1 and N2 are one of 8, 16, or 32 depending on the encoding.

#### Generic Overloaded Conversion Function

This function is probably the best choice in most cases. The signature is
the same as the type-specific conversion functions but uses the argument
types and C++ function overloading to choose the correct type-specific
conversion function automatically.

The prototype of this function is:

	void convert(const utf::stringN1& in, utf::stringN2& out);

Where N1 and N2 are one of 8, 16, or 32 depending on the encoding. For example
to convert from UTF-8 to UTF-32:

	utf::string8 s8 = "Hello World";
	utf::string32 s32;
	try {
		utf::convert(s8, s32);
	} catch (utf::conversion_error& e) {
		std::cerr << "Failed: " << e.what() << std::endl;
	}

#### Return Type-specific Functions

These functions are specific to the return type and rather than use an
output argument for the target string, a new string is created and returned
to the called using the return value (and hopefull RVO).

The prototype for these functions is:

	utf::stringN2 to_utfN2(const utf::stringN1& in);

Where N1 and N2 are one of 8, 16, or 32 depending on the encoding. For example
to convert from UTF-16 to UTF-8 (exception handling not shown):

	utf::string16 s16 = u"Hello World";
	utf::string8 s = utf::to_utf8(s16);

The functions are overloaded to accept any of the UTF-8, UTF-16 or UTF-32
string types defined in the `utf` namespace.

Legal
-----

The C++ wrapper code is distributed under the MIT license to make it easier
to embed the files inside other projects. The ConvertUTF.[ch] files from
Unicode, Inc. also have their own license (see below) that is compatible with
LibUTF++'s MIT license.

For using the LibUTF++ files in your project, all you need to do is copy the
(generated) `utf.cxx` file and the header `utf.h` into your source tree and
simply leave the license/copyright comments in the files as is.

### The LibUTF++ MIT License

> Copyright (c) 2014 Matthew Brush <mbrush@codebrainz.ca>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

- The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

### The Unicode, Inc. license for ConvertUTF.[ch] files

> Copyright 2001-2004 Unicode, Inc.

#### Disclaimer

This source code is provided as is by Unicode, Inc. No claims are
made as to fitness for any particular purpose. No warranties of any
kind are expressed or implied. The recipient agrees to determine
applicability of information provided. If this file has been
purchased on magnetic or optical media from Unicode, Inc., the
sole remedy for any claim will be exchange of defective media
within 90 days of receipt.

#### Limitations on Rights to Redistribute This Code

Unicode, Inc. hereby grants the right to freely use the information
supplied in this file in the creation of products supporting the
Unicode Standard, and to make copies of this file in any form
for internal or external distribution as long as this notice
remains attached.
