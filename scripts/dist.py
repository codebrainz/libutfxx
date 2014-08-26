#!/usr/bin/env python
#
# dist.py - This file is part of LibUTF++
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
import tarfile

def make_dist(fn, file_list):
	with tarfile.open(fn, mode='w:bz2') as tf:
		for f in file_list:
			tf.add(f)

def main(args):

	if len(args) < 3:
		sys.stderr.write('error: not enough arguments, specify tar filename ' +
		                 'and files to add\n')
		return 1

	make_dist(args[1], args[2:])

	return 0

if __name__ == "__main__":
	sys.exit(main(sys.argv))
