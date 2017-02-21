
MODULE_NAME := Geometry

ifeq ($(OS),Windows_NT)
	RM = del /Q
	RMF = rmdir /S /Q 
	CP = copy
	PYTHON_EXT = .pyd
else
	RM = rm -f
	RMF = rm -rf
	CP = cp
	PYTHON_EXT = .so
endif

all:
	swig -python -c++ $(MODULE_NAME).i
	python setup.py build_ext --inplace
	$(CP) $(MODULE_NAME).py $(IXPESWPYMODULES)
	$(CP) _$(MODULE_NAME)$(PYTHON_EXT) $(IXPESWPYMODULES)

clean:
	$(RM) *.o *.cxx $(MODULE_NAME).py *.pyc *.pyd *.so *~
	$(RMF) build