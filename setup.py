from distutils.core import setup, Extension
from Cython.Build import cythonize

ext = Extension("CALC",
                sources=["CALC.pyx", "cal.cpp"],
                language="c++",
		extra_compile_args=["-std=c++11"])

setup(name="CALC",
      ext_modules=cythonize(ext))
