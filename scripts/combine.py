#!/usr/bin/env python
#
# combine.py - This file is part of LibUTF++
#
# Copyright (c) 2014 Matthew Brush <mbrush@codebrainz.ca>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

import sys

def main(args):
	import os.path

	if len(args) < 2:
		sys.stderr.write('error: not enough arguments, expecting version number\n')
		return 1

	VERSION = args[1].strip()
	SRCROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

	def mkpath(*args):
		return os.path.join(SRCROOT, *args)

	def fread(*fn_args):
		with open(mkpath(*fn_args), 'rb') as f:
			return f.read().decode('utf8')

	def fwrite(txt, *fn_args):
		with open(mkpath(*fn_args), 'wb') as f:
			f.write(txt.encode('utf-8'))

	def fsubst(data, *fn_args):
		def subst(tmpl, data):
			txt = tmpl
			for k,v in data.items():
				txt = txt.replace(k,v)
			return txt
		return subst(fread(*fn_args), data)

	def now():
		import datetime
		return unicode(datetime.datetime.utcnow())

	fwrite(fsubst({
		"/*@@convert_header@@*/": fread('utf','ConvertUTF.h').strip(),
		"/*@@convert_source@@*/": fread('utf','ConvertUTF.c').strip(),
		"@@version@@":            VERSION,
		"@@timestamp@@":          now(),
	}, 'utf','utf.cxx.in'), 'utf','utf.cxx')

	return 0

if __name__ == "__main__":
	sys.exit(main(sys.argv))
