#yFinance_utilities.py

"""
Code to scrap equity options volatilities from yFiance
"""
import pandas as pd
pd.options.mode.chained_assignment = None  # default='warn'
from datetime import datetime
from datetime import timedelta
import pytz

import yfinance as yf

#-----------------------------------------------------------------------------
# Function to retrieve all listed options for given stock
def yFinance_retrieve_options_chain(yticker):
    tk = yf.Ticker(yticker)
    exps = tk.options # Expiration dates

    options_yf_pddf = pd.DataFrame() # Get options for each expiration
    for e in exps:
        opt = tk.option_chain(e)
        opt = pd.concat([opt.calls, opt.puts], axis=0)
        opt['expiryDate'] = e
        options_yf_pddf = pd.concat([options_yf_pddf, opt], ignore_index=True, axis=0)
    
    options_yf_pddf['isCall'] = options_yf_pddf['contractSymbol'].str[4:].apply(lambda x: "C" in x) # Boolean column if the option is a Call
    options_yf_pddf['mid'] = (options_yf_pddf['bid'] + options_yf_pddf['ask']) / 2 # Calculate the midpoint of the bid-ask
    options_yf_pddf = options_yf_pddf.drop(columns = ['contractSize', 'currency', 'change', 'inTheMoney' , 'percentChange']) # Drop unnecessary and meaningless columns
    
    return options_yf_pddf

#-----------------------------------------------------------------------------
# Function to retrieve the option traded today only and add:
# - a reference spot (neareast to the lastTradeDate), 
# - a dividend yield
def yFinance_collect_live_listed_options_information(yticker, dividend_yield=0, cutoff_hours_lag_from_now=None, log=False):
    options_yf_pddf = yFinance_retrieve_options_chain(yticker)
    if log: print("Number of options retrieved :", len(options_yf_pddf))

    spots = yf.download( yticker, period="5d",interval="1m", progress=False)

    #if no cutoff_hours we keep options traded between today 00:00 and tomorrow 00:00, else we keep from (now-cutoff_hours_lag_from_now) and (now_plus_one_day-cutoff_hours_lag_from_now
    now = datetime.now()
    ref_time = datetime.min.time() if cutoff_hours_lag_from_now is None else (now+timedelta(hours=-cutoff_hours_lag_from_now)).time()
    cutoff = datetime.combine(now, ref_time, pytz.UTC)
    cutoff_plus_one = datetime.combine(now+ timedelta(days=+1), ref_time, pytz.UTC)
    
    #Retrieve reference spot for last trade date
    options_yf_pddf["referenceSpot"]=-1.0
    for i in range(len(options_yf_pddf)):
        lastTradeDate = pd.to_datetime(options_yf_pddf.loc[i, "lastTradeDate"])
        if lastTradeDate>cutoff and lastTradeDate<cutoff_plus_one :
            iloc_idx = spots.index.get_indexer([lastTradeDate], method='nearest')
            options_yf_pddf.loc[i, "referenceSpot"]=round(spots.iloc[iloc_idx]["Adj Close"].item(),4)
    options_yf_pddf = options_yf_pddf.loc[options_yf_pddf["referenceSpot"]>0]
    options_yf_pddf["last close"] = round(spots["Close"][-1],4)
    options_yf_pddf["yFinance_dividend_yield"] = dividend_yield
    options_yf_pddf["ticker"] = yticker

    if log: print("close:",round(spots["Close"][-1],4))
    if log: print("Number of options kept (reference spot available):", len(options_yf_pddf))

    return options_yf_pddf