all:
	swig -python -c++ Utils.i
	python setup.py build_ext --inplace
	cp Utils.py _Utils.so $(IXPESWPYMODULES)

clean:
	rm -f *.o *.cxx Utils.py *.pyc *.so *~
