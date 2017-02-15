from distutils.core import setup, Extension

import glob


_src = glob.glob('../src/*.cpp')
_src.append('Utils_wrap.cxx')
_incl = ['../include']

module = Extension('_Utils', sources=_src, include_dirs=_incl)

setup (name = 'Utils',
       ext_modules = [module],
       py_modules = ['Utils']
)
