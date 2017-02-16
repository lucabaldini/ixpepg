
MODULE_NAME := IDF

all:
	swig -python -c++ $(MODULE_NAME).i
	python setup.py build_ext --inplace
	cp $(MODULE_NAME).py _$(MODULE_NAME).so $(IXPESWPYMODULES)

clean:
	rm -f *.o *.cxx $(MODULE_NAME).py *.pyc *.so *~
	rm -rf build
