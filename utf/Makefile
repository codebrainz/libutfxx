
SED ?= sed

CXXFLAGS_ = $(CXXFLAGS) -fPIC
LDFLAGS_ = $(LDFLAGS)

all: libutf++.so

libutf++.so: utf.o
	$(CXX) -shared $(CXXFLAGS_) -o $@ $^ $(LDFLAGS_)

utf.o: utf.cxx utf.h
	$(CXX) -c $(CXXFLAGS_) -o $@ $<

utf.cxx: utf.cxx.in ConvertUTF.c ConvertUTF.h
	$(SED) -e '/\/\*@@convert_source@@\*\//{r ConvertUTF.c' -e 'd}' $< | \
		$(SED) -e '/\/\*@@convert_header@@\*\//{r ConvertUTF.h' -e 'd}' > $@

clean:
	$(RM) *.o *.so utf.cxx
