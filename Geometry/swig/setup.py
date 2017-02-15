from distutils.core import setup, Extension

import glob
import os


MODULE_NAME = 'Geometry'
DEPS = ['Utils']

# Absolute or relative paths?
BASE_DIR = os.pardir
SRC = glob.glob(os.path.join(BASE_DIR, 'src', '*.cpp'))
SRC.append('%s_wrap.cxx' % MODULE_NAME)
INCL = [os.path.join(BASE_DIR, 'include')]
for dep in DEPS:
    SRC += glob.glob(os.path.join(BASE_DIR, os.pardir, dep, 'src', '*.cpp'))
    INCL.append(os.path.join(BASE_DIR, os.pardir, dep, 'include'))

# Print the SRC and INCL lists.
print('SRC = %s' % SRC)
print('INCL = %s' % INCL)


module = Extension(
    '_%s' % MODULE_NAME,
    sources=SRC,
    include_dirs=INCL
)

setup(
    name = MODULE_NAME,
    ext_modules = [module],
    py_modules = [MODULE_NAME]
)
