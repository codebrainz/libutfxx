VERSION=0.1
SED ?= sed

all:
	$(MAKE) -C utf $@

ROOT_FILES =  \
	index.html \
	index.html.in \
	Makefile \
	README.md \

DIST_FILES = \
	$(ROOT_FILES) \
	utf/ConvertUTF.c \
	utf/ConvertUTF.h \
	utf/ConvertUTF_readme.txt \
	utf/Makefile \
	utf/utf.cxx \
	utf/utf.cxx.in \
	utf/utf.h

libutf++-$(VERSION).tar.gz: all $(DIST_FILES)
	mkdir -p libutf++-$(VERSION) && \
	cp -r $(ROOT_FILES) utf libutf++-$(VERSION)/ &&   \
	rm -f libutf++-$(VERSION)/utf/*.o && \
	rm -f libutf++-$(VERSION)/utf/*.so && \
	tar -cf $@ libutf++-$(VERSION)/ && \
	rm -rf libutf++-$(VERSION)

dist: libutf++-$(VERSION).tar.gz

index.html: index.html.in README.md
	$(SED) -e '/@@readme_contents@@/{r README.md' -e 'd}' $< > $@

html: index.html

clean:
	$(MAKE) -C utf $@
	$(RM) -f libutf++-$(VERSION).tar.gz index.html

.PHONY: all clean
