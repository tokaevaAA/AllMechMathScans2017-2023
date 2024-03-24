import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as sps

from ipywidgets import interact
from ipywidgets import widgets
from tqdm.auto import tqdm

from dataclasses import dataclass
from typing import Union, Callable, Optional
from copy import deepcopy
from scipy.optimize import root_scalar, brentq
from dataclasses import dataclass

from scipy.interpolate import RectBivariateSpline

import warnings
from  scipy.stats import norm
warnings.filterwarnings("ignore")


@dataclass
class StockOption:
    strike_price: Union[float, np.ndarray]
    expiration_time: Union[float, np.ndarray]  # in years
    is_call: bool

@dataclass
class CallStockOption(StockOption):
    def __init__(self, strike_price, expiration_time):
        super().__init__(strike_price, expiration_time, True)
        

@dataclass
class PutStockOption(StockOption):
    def __init__(self, strike_price, expiration_time):
        super().__init__(strike_price, expiration_time, False)
        
@dataclass
class MarketState:
    stock_price: Union[float, np.ndarray]
    interest_rate: Union[float, np.ndarray]  # r, assume constant
        
        
def make_local_vol_func(calls: CallStockOption,
                        call_prices: np.ndarray,
                        interest_rate: float = 0) -> Callable[[float, float], float]:
    r=interest_rate
    T=calls.expiration_time #T len=15
    K=calls.strike_price #K len=16
    C=call_prices #15*16
    C_T=np.gradient(C,T,axis=0) #T-for x_i,C-for fi
    C_K=np.gradient(C,K,axis=1) #K-for x_i,C-for fi
    C_KK=np.gradient(C_K,K,axis=1)
    sigma=(2*C_T+2*r*K*C_K)/(K*K*C_KK+1e-10)
    sigma[sigma<0]=0
    sigma=np.sqrt(sigma)
    interpolation=RectBivariateSpline(T,K,sigma)

    def local_vol_func(t, s):
        return interpolation(t,s,grid=False)
    
    return local_vol_func