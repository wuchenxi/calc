from distutils.core import setup, Extension
from Cython.Build import cythonize

ext = Extension("CALC",
                sources=["CALC.pyx", "cal.cpp"],
                language="c++")

setup(name="CALC",
      ext_modules=cythonize(ext))
