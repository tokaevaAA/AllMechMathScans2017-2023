# Black_utilities_self_contained.py

"""
Basic Black formulas for:
 - price (black_price_formula),
 - delta (Black_delta_formula),
 - gamma (Black_gamma_formula),
 - vega (Black_vega_formula),
 - naive implied vol ( directly coded Newton Raphson method)
"""

import numpy as np
from scipy.stats import norm

DOUBLE_EPSILON = np.finfo(float).eps

#-----------------------------------------------------------------------------
def black_price_formula(F, K, T, sigma, isCall):
        stddev = sigma*np.sqrt(T)
        d1 = np.log(F/K)/stddev + 0.5*stddev
        d2 = d1 - stddev
        eps = 1.0 if isCall else -1.0
        return eps *(F * norm.cdf(eps*d1) - K * norm.cdf(eps*d2))

#-----------------------------------------------------------------------------
def black_delta_formula(F, K, T, sigma, isCall):
    stddev = sigma*np.sqrt(T)
    d1 = np.log(F/K)/stddev + 0.5*stddev
    eps = 1.0 if isCall else -1.0
    return eps *norm.cdf(eps*d1)

#-----------------------------------------------------------------------------
def black_gamma_formula(F, K, T, sigma):
    stddev = sigma*np.sqrt(T)
    d1 = np.log(F/K)/stddev + 0.5*stddev
    return norm.pdf(d1) / ( F * sigma * np.sqrt(T))

#-----------------------------------------------------------------------------
def black_vega_formula(F, K, T, sigma):
    stddev = sigma*np.sqrt(T)
    d1 = np.log(F/K)/stddev + 0.5*stddev
    return 0.01 * F * norm.pdf(d1) * np.sqrt(T) #return for a move of 1%

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
        stddev = sigma*np.sqrt(T)
        d1 = np.log(F/K)/stddev + 0.5*stddev
        d2 = d1 - stddev
        price = eps *(F * norm.cdf(eps*d1) - K * norm.cdf(eps*d2))
        vega = F * norm.pdf(d1) * np.sqrt(T)
        diff = target_price - price
        if (vega<=DOUBLE_EPSILON):
            return initial_guess #likely to be far off the money anyway....
        if (abs(diff) < PRECISION):
            return sigma
        sigma = sigma + diff/vega # Newton–Raphson
    return sigma # if MAX_ITERATIONS, return estimate so far