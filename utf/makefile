PYTHON ?= python

#FIXME: fix -Wnarrowing warnings
CXXFLAGS_ = $(CXXFLAGS) -fPIC -Wno-narrowing
LDFLAGS_ = $(LDFLAGS)

all: libutf++.so utfstring-demo

libutf++.so: utf.o
	$(CXX) -shared $(CXXFLAGS_) -o $@ $^ $(LDFLAGS_)

utf.o: utf.cxx utf.h
	$(CXX) -c $(CXXFLAGS_) -o $@ $<

utf.cxx: utf.cxx.in ConvertUTF.c ConvertUTF.h
	$(PYTHON) ../scripts/combine.py $(VERSION)

utfstring-demo: string-demo.cxx libutf++.so
	$(CXX) $(CXXFLAGS_) -o $@ string-demo.cxx $(LDFLAGS_) -L. -lutf++

clean:
	$(RM) *.o *.so utfstring-demo
