import pyximport; pyximport.install()
from .cython_Black_formulas import *

import os
import sys
sys.path.append(os.path.dirname(os.path.realpath(__file__)))

import LetsBeRationalForPython
def black_implied_vol(undiscounted_price, F, K, T, isCall):
    eps = 1. if isCall else -1. 
    return LetsBeRationalForPython.implied_volatility(undiscounted_price, F, K, T, eps)

#alternatively (no cython)
#from .Black_utilities_self_contained import *