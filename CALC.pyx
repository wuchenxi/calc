# distutils: language = c++
# distutils: sources = cal.cpp

from libcpp.string cimport string

cdef extern from "cal.h" namespace "cal":
    cdef cppclass calc_exp:
        calc_exp(string s)
        string get_exp()
        double calc()
        int set_exp(string s)

cdef class CALC:

    cdef calc_exp *_thisptr

    def __cinit__(self, string s):
        self._thisptr = new calc_exp(s)
        if self._thisptr == NULL:
            raise MemoryError()

    def __dealloc__(self):
        if self._thisptr != NULL:
            del self._thisptr

    def getexpr(self):
        return self._thisptr.get_exp()
    
    def setexpr(self, string s):
        return self._thisptr.set_exp(s)

    def evalexp(self):
        return self._thisptr.calc()