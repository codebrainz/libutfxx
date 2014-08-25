
SED ?= sed

#FIXME: fix -Wnarrowing warnings
CXXFLAGS_ = $(CXXFLAGS) -fPIC -Wno-narrowing
LDFLAGS_ = $(LDFLAGS)

all: libutf++.so utfstring-demo

libutf++.so: utf.o
	$(CXX) -shared $(CXXFLAGS_) -o $@ $^ $(LDFLAGS_)

utf.o: utf.cxx utf.h
	$(CXX) -c $(CXXFLAGS_) -o $@ $<

utf.cxx: utf.cxx.in ConvertUTF.c ConvertUTF.h
	$(SED) -e '/\/\*@@convert_source@@\*\//{r ConvertUTF.c' -e 'd}' $< | \
		$(SED) -e '/\/\*@@convert_header@@\*\//{r ConvertUTF.h' -e 'd}' > $@

utfstring-demo: string-demo.cxx libutf++.so
	$(CXX) $(CXXFLAGS_) -o $@ string-demo.cxx $(LDFLAGS_) -L. -lutf++

clean:
	$(RM) *.o *.so utf.cxx utfstring-demo
