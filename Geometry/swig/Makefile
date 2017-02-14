SRCDIR := ../src
INCDIR := ../include
PYTHONDIR := /usr/include/python2.7

all:
	swig -python -c++ Geometry.i
	g++ -fPIC -std=c++11 -c $(SRCDIR)/*.cpp Geometry_wrap.cxx \
	-I$(PYTHONDIR) -I$(INCDIR)
	c++ -shared *.o -o _Geometry.so
	cp Geometry.py _Geometry.so $(IXPESWPYMODULES)

clean:
	rm -f *.o *.cxx Geometry.py *.pyc *.so *~
