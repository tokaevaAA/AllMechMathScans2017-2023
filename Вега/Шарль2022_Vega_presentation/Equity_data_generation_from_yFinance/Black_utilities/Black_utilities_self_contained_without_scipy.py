# Black_utilities_self_contained.py

"""
Basic Black formulas for:
 - price (black_price_formula),
 - delta (Black_delta_formula),
 - gamma (Black_gamma_formula),
 - vega (Black_vega_formula),
 - naive implied vol ( directly coded Newton Raphson method)
"""


from math import sqrt, exp, log

import numpy as np
DOUBLE_EPSILON = np.finfo(float).eps

#-----------------------------------------------------------------------------
def normcdf(x):
    #Numerical Recipes
    A1 = 0.31938153
    A2 = -0.356563782
    A3 = 1.781477937
    A4 = -1.821255978
    A5 = 1.330274429
    RSQRT2PI = 0.39894228040143267793994605993438
    K = 1.0 / (1.0 + 0.2316419 * abs(x))
    ret_val = (RSQRT2PI * exp(-0.5 * x * x) *
               (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5))))))
    if x > 0:
        ret_val = 1.0 - ret_val
    return ret_val
    """
    #Abramowitz Stegun
    a1 =  0.254829592
    a2 = -0.284496736
    a3 =  1.421413741
    a4 = -1.453152027
    a5 =  1.061405429
    p  =  0.3275911

    # Save the sign of x
    sign = 1
    if x < 0:
        sign = -1
    x = abs(x)/sqrt(2.0)

    # A&S formula 7.1.26
    t = 1.0/(1.0 + p*x)
    y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x)

    return 0.5*(1.0 + sign*y)
    """
#-----------------------------------------------------------------------------
def normpdf(x):
    RSQRT2PI = 0.39894228040143267793994605993438
    return RSQRT2PI * exp(-0.5*x*x)

#-----------------------------------------------------------------------------
def black_price_formula(F, K, T, sigma, isCall):
        stddev = sigma*sqrt(T)
        d1 = log(F/K)/stddev + 0.5*stddev
        d2 = d1 - stddev
        eps = 1.0 if isCall else -1.0
        return eps *(F * normcdf(eps*d1) - K * normcdf(eps*d2))

#-----------------------------------------------------------------------------
def black_delta_formula(F, K, T, sigma, isCall):
    stddev = sigma*sqrt(T)
    d1 = log(F/K)/stddev + 0.5*stddev
    eps = 1.0 if isCall else -1.0
    return eps *normcdf(eps*d1)

#-----------------------------------------------------------------------------
def black_gamma_formula(F, K, T, sigma):
    stddev = sigma*sqrt(T)
    d1 = log(F/K)/stddev + 0.5*stddev
    return normpdf(d1) / ( F * sigma * sqrt(T))

#-----------------------------------------------------------------------------
def black_vega_formula(F, K, T, sigma):
    stddev = sigma*sqrt(T)
    d1 = log(F/K)/stddev + 0.5*stddev
    return 0.01 * F * normpdf(d1) * sqrt(T) #return for a move of 1%

#-----------------------------------------------------------------------------
def black_implied_vol(undiscounted_price, F, K, T, isCall, initial_guess = 0.25):
    target_price = undiscounted_price
    eps = 1.0 if isCall else -1.0
    if isCall and K < F:
        target_price = undiscounted_price + K - F
        eps = -1.0
    if not isCall and K> F:
         target_price = undiscounted_price + F - K
         eps = 1.0
    MAX_ITERATIONS = 200
    PRECISION = min(1.0e-5, target_price/F)
    sigma = initial_guess
    for i in range(0, MAX_ITERATIONS):
        stddev = sigma*sqrt(T)
        d1 = log(F/K)/stddev + 0.5*stddev
        d2 = d1 - stddev
        price = eps *(F * normcdf(eps*d1) - K * normcdf(eps*d2))
        vega = F * normpdf(d1) * sqrt(T)
        diff = target_price - price
        if (vega<=DOUBLE_EPSILON):
            return initial_guess #likely to be far off the money anyway....
        if (abs(diff) < PRECISION):
            return sigma
        sigma = sigma + diff/vega # Newton–Raphson
    return sigma # if MAX_ITERATIONS, return estimate so far