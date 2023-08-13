cimport cython
from libc.math cimport  sqrt,log,exp,erf
cdef double ONE_OVER_SQRT_TWO=0.70710678118654752440084436210484903928483593768847
cdef double ONE_OVER_SQRT_TWO_PI=0.3989422804014326779399460599343818684758586311649

@cython.cdivision(True)
@cython.boundscheck(False)
@cython.wraparound(False)
@cython.nonecheck(False)
cdef double gaussian_cdf(double x) nogil:
    return 0.5*(1+erf(x*ONE_OVER_SQRT_TWO))

@cython.cdivision(True)
@cython.boundscheck(False)
@cython.wraparound(False)
@cython.nonecheck(False)
cdef double gaussian_pdf(double x) nogil:
    return ONE_OVER_SQRT_TWO_PI * exp(-0.5*x*x)

@cython.cdivision(True)
@cython.boundscheck(False)
@cython.wraparound(False)
@cython.nonecheck(False)
cpdef double black_price_formula(double F, double K, double T, double sigma, int isCall) nogil:
    cdef double eps = -1.0 + 2*isCall
    cdef double stddev = sigma*sqrt(T)
    cdef double d1 = log(F/K) / stddev + 0.5*stddev
    cdef double d2 = d1 - stddev
    return eps*(F*gaussian_cdf(eps*d1) - K*gaussian_cdf(eps*d2))

@cython.cdivision(True)
@cython.boundscheck(False)
@cython.wraparound(False)
@cython.nonecheck(False)
cpdef double black_delta_formula(double F, double K, double T, double sigma, int isCall) nogil:
    cdef double eps = -1.0 + 2*isCall
    cdef double stddev = sigma*sqrt(T)
    cdef double d1 = log(F/K) / stddev + 0.5*stddev
    return eps*gaussian_cdf(eps*d1)

@cython.cdivision(True)
@cython.boundscheck(False)
@cython.wraparound(False)
@cython.nonecheck(False)
cpdef double black_gamma_formula(double F, double K, double T, double sigma) nogil:
    cdef double stddev = sigma*sqrt(T)
    cdef double d1 = log(F/K) / stddev + 0.5*stddev
    return gaussian_pdf(d1) / (F * stddev)

@cython.cdivision(True)
@cython.boundscheck(False)
@cython.wraparound(False)
@cython.nonecheck(False)
cpdef double black_vega_formula(double F, double K, double T, double sigma) nogil:
    cdef double stddev = sigma*sqrt(T)
    cdef double d1 = log(F/K) / stddev + 0.5*stddev
    return 0.01 * F * gaussian_pdf(d1) * sqrt(T)
