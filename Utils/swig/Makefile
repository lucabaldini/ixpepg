SRCDIR := ../src
INCDIR := ../include
PYTHONDIR := /usr/include/python2.7

all:
	swig -python -c++ Utils.i
	g++ -fPIC -c -std=gnu++14 $(SRCDIR)/*.cpp Utils_wrap.cxx \
	-I$(PYTHONDIR) -I$(INCDIR)
	c++ -shared *.o -o _Utils.so
	cp Utils.py _Utils.so $(IXPESWPYMODULES)

clean:
	rm -f *.o *.cxx Utils.py *.pyc *.so *~
