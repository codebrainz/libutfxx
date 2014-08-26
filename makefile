VERSION = 0.1
PYTHON ?= python
SED ?= sed

export VERSION PYTHON SED

DIST_FILES = \
	makefile \
	readme.md \
	doc/index.html \
	doc/index.html.in \
	doc/makefile \
	scripts/combine.py \
	scripts/dist.py \
	utf/ConvertUTF.c \
	utf/ConvertUTF.h \
	utf/ConvertUTF_readme.txt \
	utf/makefile \
	utf/utf.cxx \
	utf/utf.cxx.in \
	utf/utf.h \
	utf/utfstring.h

all:
	$(MAKE) -C doc $@
	$(MAKE) -C utf $@

TAR_NAME = libutf++-$(VERSION).tar.bz2

$(TAR_NAME): $(DIST_FILES)
	$(PYTHON) scripts/dist.py $@ $^

dist: all $(TAR_NAME)

html:
	$(MAKE) -C doc $@

clean:
	$(MAKE) -C doc $@
	$(MAKE) -C utf $@
	$(RM) -f $(TAR_NAME)

.PHONY: all clean dist html
