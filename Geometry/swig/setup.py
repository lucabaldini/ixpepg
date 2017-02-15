from distutils.core import setup, Extension

import glob


MODULE_NAME = 'Geometry'

SRC = glob.glob('../src/*.cpp')
SRC.append('%s_wrap.cxx' % MODULE_NAME)
INCL = ['../include']


module = Extension('_%s' % MODULE_NAME,
                   sources=SRC,
                   include_dirs=INCL
)

setup (name = MODULE_NAME,
       ext_modules = [module],
       py_modules = [MODULE_NAME]
)
