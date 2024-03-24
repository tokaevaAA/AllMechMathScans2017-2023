#yFinance_Equity_Data_Cleaning.py

import os
import sys
sys.path.append(os.path.dirname(os.path.realpath(__file__)))

import numpy as np
import pandas as pd
pd.options.mode.chained_assignment = None  # default='warn'
from datetime import datetime
import matplotlib.pyplot as plt

from Black_utilities import black_price_formula, black_delta_formula, black_implied_vol

HARD_STRIKE_LOWER_LIMIT = 0.4
HARD_STRIKE_UPPER_LIMIT = 2.5
DELTA_LIMIT = 0.001
IV_BID_ASK_SPREAD_QUANTILE_LIMIT = 0.95
COMPUTE_ADJUSTED_FORWARD = True

#-----------------------------------------------------------------------------
def is_price_above_intrinsic(price, F, K, isCall):
    if isCall:
        return True if (price>max(F-K,0)) else False
    else:
        return True if (price>max(K-F,0)) else False

# pandas utilities 
def find_neighbours(value, df, colname):
    exactmatch = df[df[colname] == value]
    if not exactmatch.empty:
        return exactmatch.index
    else:
        lowerneighbour_ind = df[df[colname] < value][colname].idxmax()
        upperneighbour_ind = df[df[colname] > value][colname].idxmin()
        return [lowerneighbour_ind, upperneighbour_ind]
    
#-----------------------------------------------------------------------------
# Function to compute the forward from the data by parity when possible
def yFinance_compute_forward_by_parity_for_given_expiry(reference_fwd, discount_factor, options_at_given_expiry_yf_pddf, compute_adjutment_when_only_one_strike = True, log = False):
    optionsTduplicateStrikes = options_at_given_expiry_yf_pddf[options_at_given_expiry_yf_pddf.duplicated(["strike"], keep=False)]
    optionsTduplicateStrikes = optionsTduplicateStrikes.sort_values(by=['strike'], ascending = [False])
    if log: print("both options traded on", int(len(optionsTduplicateStrikes)/2), "contracts.")
    #pd.set_option('display.max_rows', len(optionsTduplicateStrikes))
    #optionsTduplicateStrikes.head(len(optionsTduplicateStrikes))

    if (len(optionsTduplicateStrikes)==0): #degenerated case
        adjusted_fwd = reference_fwd

    elif compute_adjutment_when_only_one_strike and (len(optionsTduplicateStrikes)==2): #there are two lines, hence only one strike
        strike = optionsTduplicateStrikes.iloc[0]["strike"].item()
        mid_call_price = optionsTduplicateStrikes.loc[(optionsTduplicateStrikes["strike"]==strike) & (optionsTduplicateStrikes["isCall"]==True)]["mid"].item()
        mid_put_price = optionsTduplicateStrikes.loc[(optionsTduplicateStrikes["strike"]==strike) & (optionsTduplicateStrikes["isCall"]==False)]["mid"].item()
        adjusted_fwd= (mid_call_price-mid_put_price)/discount_factor + strike

    elif (reference_fwd > max(optionsTduplicateStrikes["strike"])) or (reference_fwd < min(optionsTduplicateStrikes["strike"])): # reference fwd beyond the strikes, or compute_adjutment_when_only_one_strike = False and only one strike
        adjusted_fwd = reference_fwd

    else : #regular case, i.e. len(optionsTduplicateStrikes)>=4
        strikes = find_neighbours(reference_fwd, optionsTduplicateStrikes, "strike")
        #computation of the adjusted fwd from the strike just below the reference fwd
        strike_below_fwd = optionsTduplicateStrikes.loc[strikes[0]]["strike"]
        mid_call_price = optionsTduplicateStrikes.loc[(optionsTduplicateStrikes["strike"]==strike_below_fwd) & (optionsTduplicateStrikes["isCall"]==True)]["mid"].item()
        mid_put_price = optionsTduplicateStrikes.loc[(optionsTduplicateStrikes["strike"]==strike_below_fwd) & (optionsTduplicateStrikes["isCall"]==False)]["mid"].item()
        fwd_from_strike_below_fwd = (mid_call_price-mid_put_price)/discount_factor + strike_below_fwd
        #computation of the adjusted fwd from the strike just above the reference fwd
        strike_above_fwd = optionsTduplicateStrikes.loc[strikes[1]]["strike"]
        mid_call_price = optionsTduplicateStrikes.loc[(optionsTduplicateStrikes["strike"]==strike_above_fwd) & (optionsTduplicateStrikes["isCall"]==True)]["mid"].item()
        mid_put_price = optionsTduplicateStrikes.loc[(optionsTduplicateStrikes["strike"]==strike_above_fwd) & (optionsTduplicateStrikes["isCall"]==False)]["mid"].item()
        fwd_from_strike_above_fwd = (mid_call_price-mid_put_price)/discount_factor + strike_above_fwd
        #average of previous results
        adjusted_fwd = (fwd_from_strike_below_fwd+fwd_from_strike_above_fwd)/2

    if log: print("Reference forward:", reference_fwd)
    if log: print("New adjusted forward:", adjusted_fwd)

    return adjusted_fwd

#-----------------------------------------------------------------------------
# Analysis of an Expiry (quote cleaning and implied volatility computation)
def yFinance_compute_adjusted_fwd_and_IV_for_expiry(options_at_given_expiry_yf_pddf, data_date, expiry_date, discount_factor, compute_adjusted_fwd = True, forced_dividend_yield = None, hard_strike_lower_limit = 0.4, hard_strike_upper_limit = 2.5, delta_limit = 0.01, IV_bid_ask_spread_quantile_limit = 0.75, log = False ):
    T_days = (datetime.strptime(expiry_date, "%Y-%m-%d")-datetime.strptime(data_date, "%Y-%m-%d")).days
    T_act365 = T_days/365
    close = options_at_given_expiry_yf_pddf["last close"].iloc[0]
    dividend_yield = options_at_given_expiry_yf_pddf["yFinance_dividend_yield"].iloc[0] if not forced_dividend_yield else forced_dividend_yield
    reference_fwd = close / discount_factor * np.exp(- dividend_yield * T_act365) #no div, no repo rate
    if log: print("Reference fwd:", reference_fwd)

    #remove quotes without bids
    nb_of_contract = len(options_at_given_expiry_yf_pddf)
    options_at_given_expiry_yf_pddf.drop(options_at_given_expiry_yf_pddf[(options_at_given_expiry_yf_pddf.bid==0) | (options_at_given_expiry_yf_pddf.ask - options_at_given_expiry_yf_pddf.bid < 0)].index,  inplace=True)
    discarted_rows = nb_of_contract - len(options_at_given_expiry_yf_pddf)
    if log: print("Number of rows removed because bid is null:", discarted_rows)
    nb_of_contract = nb_of_contract - discarted_rows

    #Compute adjusted reference fwd if required
    if compute_adjusted_fwd:
        compute_adjutment_when_only_one_strike = True
        reference_fwd = yFinance_compute_forward_by_parity_for_given_expiry(reference_fwd, discount_factor, options_at_given_expiry_yf_pddf, compute_adjutment_when_only_one_strike, log)
    options_at_given_expiry_yf_pddf["reference_fwd"] = reference_fwd

    #Keep only the OTM options
    options_at_given_expiry_yf_pddf = options_at_given_expiry_yf_pddf.loc[((options_at_given_expiry_yf_pddf["strike"]>=reference_fwd) & (options_at_given_expiry_yf_pddf["isCall"]==True)) | ((options_at_given_expiry_yf_pddf["strike"]<reference_fwd) & (options_at_given_expiry_yf_pddf["isCall"]==False))]
    options_at_given_expiry_yf_pddf.sort_values(by=['strike'], inplace=True)

    #Filter data based on moneyness criteria
    options_at_given_expiry_yf_pddf.drop(options_at_given_expiry_yf_pddf[(options_at_given_expiry_yf_pddf.strike<hard_strike_lower_limit*reference_fwd) | (options_at_given_expiry_yf_pddf.strike>hard_strike_upper_limit*reference_fwd)].index, inplace=True)
    discarted_rows = nb_of_contract - len(options_at_given_expiry_yf_pddf)
    if log: print("Number of rows removed based on strike criteria:", discarted_rows)
    nb_of_contract = nb_of_contract - discarted_rows
    
    #implied vol computation
    options_at_given_expiry_yf_pddf["IV_from_mid_and_ref_fwd"] = options_at_given_expiry_yf_pddf.apply(lambda row: black_implied_vol(row.mid / discount_factor, reference_fwd, row.strike, T_act365, row.isCall) if is_price_above_intrinsic(row.mid / discount_factor, reference_fwd, row.strike, row.isCall) else -1, axis=1)
    options_at_given_expiry_yf_pddf["IV_from_bid_and_ref_fwd"] = options_at_given_expiry_yf_pddf.apply(lambda row: black_implied_vol(row.bid / discount_factor, reference_fwd, row.strike, T_act365, row.isCall) if is_price_above_intrinsic(row.bid / discount_factor, reference_fwd, row.strike, row.isCall) else -1, axis=1)
    options_at_given_expiry_yf_pddf["IV_from_ask_and_ref_fwd"] = options_at_given_expiry_yf_pddf.apply(lambda row: black_implied_vol(row.ask / discount_factor, reference_fwd, row.strike, T_act365, row.isCall) if is_price_above_intrinsic(row.ask / discount_factor, reference_fwd, row.strike, row.isCall) else -1, axis=1)
    options_at_given_expiry_yf_pddf["IV_bid_ask_spread"] = options_at_given_expiry_yf_pddf["IV_from_ask_and_ref_fwd"] - options_at_given_expiry_yf_pddf["IV_from_bid_and_ref_fwd"]
    options_at_given_expiry_yf_pddf.drop(options_at_given_expiry_yf_pddf.index[(options_at_given_expiry_yf_pddf["IV_from_bid_and_ref_fwd"]<0.0) | (options_at_given_expiry_yf_pddf["IV_from_ask_and_ref_fwd"]<0.0)], inplace=True)  #if the price is below intrinsic, IV is set to -1, so we remove all lines showing negative bid IV

    #Filter data based on delta criteria
    for strike in options_at_given_expiry_yf_pddf["strike"]:
        isCall = True if strike> reference_fwd else False
        if len(options_at_given_expiry_yf_pddf.loc[(options_at_given_expiry_yf_pddf["strike"]==strike) & (options_at_given_expiry_yf_pddf["isCall"]==isCall)]["impliedVolatility"])==0: #degenerated case when only listed option is ITM
            options_at_given_expiry_yf_pddf.drop(options_at_given_expiry_yf_pddf.index[options_at_given_expiry_yf_pddf["strike"]==strike], inplace=True)
        else:
            impliedVolatility_from_yahoo = options_at_given_expiry_yf_pddf.loc[(options_at_given_expiry_yf_pddf["strike"]==strike) & (options_at_given_expiry_yf_pddf["isCall"]==isCall)]["IV_from_mid_and_ref_fwd"].item()
            delta = black_delta_formula(reference_fwd, strike, T_act365, impliedVolatility_from_yahoo, isCall)
            if abs(delta)<=delta_limit: 
                options_at_given_expiry_yf_pddf.drop(options_at_given_expiry_yf_pddf.index[options_at_given_expiry_yf_pddf["strike"]==strike], inplace=True)
    discarted_rows = nb_of_contract - len(options_at_given_expiry_yf_pddf)
    if log: print("Number of rows removed based on delta criteria:", discarted_rows)
    nb_of_contract = nb_of_contract - discarted_rows

    #cleaning of remaining data based on the size of the bid-ask spread
    bid_ask_spread_limit = options_at_given_expiry_yf_pddf["IV_bid_ask_spread"].quantile(IV_bid_ask_spread_quantile_limit)
    if len(options_at_given_expiry_yf_pddf)>=10:
        options_at_given_expiry_yf_pddf.drop(options_at_given_expiry_yf_pddf[options_at_given_expiry_yf_pddf["IV_bid_ask_spread"]>bid_ask_spread_limit].index, inplace=True)
    discarted_rows = nb_of_contract - len(options_at_given_expiry_yf_pddf)
    if log: print("Number of rows removed based on IV bid-ask spread criteria:", discarted_rows, "(quotes kept for vol spread of ", round(bid_ask_spread_limit, 4), ").")

    return options_at_given_expiry_yf_pddf

#-----------------------------------------------------------------------------
# Full analysis of the surface and return dictionnary with full information
def yFinance_generate_refined_implied_volatility_surface_dictionnary(options_yf_pddf, discounting_curve_daycountfractions_list, discounting_curve_dfs_list, expiry_date_list = None, forced_dividend_yield = None, log = False ):
    if(len(options_yf_pddf)==0):
        return {}
    
    data_date = options_yf_pddf["lastTradeDate"].iloc[0].date().isoformat()
    has_expiry_date_list_input = False
    if not expiry_date_list:
        expiry_date_list=options_yf_pddf["expiryDate"].unique().tolist()
    else:
        has_expiry_date_list_input = True

    equity_IV_dict={}
    equity_IV_dict["underlying_ticker"]= options_yf_pddf["ticker"].iloc[0]
    equity_IV_dict["data_date"] = data_date
    equity_IV_dict["reference_spot"] = reference_spot = float(options_yf_pddf["last close"].iloc[0])
    implied_volatility_surface =list()

    for expiry_date in expiry_date_list:
        options_at_given_expiry_yf_pddf = options_yf_pddf.loc[options_yf_pddf["expiryDate"]==expiry_date]
        if (len(options_at_given_expiry_yf_pddf)>0):
            #basic sanity checks are expiry in the future (strict) and at least 2 strikes listed and we only keep the maturity if it is a Friday if we use the list from the dataframe
            if (has_expiry_date_list_input and (expiry_date>data_date) and (len(options_at_given_expiry_yf_pddf["strike"].unique().tolist())>=2)) or ((expiry_date>data_date) and (pd.Timestamp(expiry_date).dayofweek==4) and (len(options_at_given_expiry_yf_pddf["strike"].unique().tolist())>=2)):
                T_days = (datetime.strptime(expiry_date, "%Y-%m-%d")-datetime.strptime(data_date, "%Y-%m-%d")).days
                T_act360 = T_days/360
                discount_factor = np.exp(np.interp(T_act360, discounting_curve_daycountfractions_list, np.log(discounting_curve_dfs_list)))
                
                #Data Analysis
                options_at_given_expiry_yf_pddf = yFinance_compute_adjusted_fwd_and_IV_for_expiry(options_at_given_expiry_yf_pddf, data_date, expiry_date, discount_factor, COMPUTE_ADJUSTED_FORWARD, forced_dividend_yield,
                            HARD_STRIKE_LOWER_LIMIT, HARD_STRIKE_UPPER_LIMIT, DELTA_LIMIT, IV_BID_ASK_SPREAD_QUANTILE_LIMIT, log)
                if(len(options_at_given_expiry_yf_pddf)>0):
                    reference_fwd = options_at_given_expiry_yf_pddf["reference_fwd"].iloc[0]
                    equity_data_for_specific_expiry={}
                    equity_data_for_specific_expiry["expiry_date"] = expiry_date
                    equity_data_for_specific_expiry["number_of_days_from_value_date"] = T_days
                    equity_data_for_specific_expiry["expiry_date_in_act365_year_fraction"] = T_days/365
                    equity_data_for_specific_expiry["reference_forward"] = reference_fwd
                    equity_data_for_specific_expiry["reference_discount_factor"] = discount_factor
                    equity_data_for_specific_expiry["implied_carry_rate"] = np.log(discount_factor * reference_fwd/reference_spot) * 365 / T_days
                    equity_data_for_specific_expiry["strikes"] = options_at_given_expiry_yf_pddf["strike"].tolist()
                    equity_data_for_specific_expiry["mid_implied_volatilities"] = options_at_given_expiry_yf_pddf["IV_from_mid_and_ref_fwd"].tolist()
                    equity_data_for_specific_expiry["bid_implied_volatilities"] = options_at_given_expiry_yf_pddf["IV_from_bid_and_ref_fwd"].tolist()
                    equity_data_for_specific_expiry["ask_implied_volatilities"] = options_at_given_expiry_yf_pddf["IV_from_ask_and_ref_fwd"].tolist()

                    implied_volatility_surface.append(equity_data_for_specific_expiry)
    equity_IV_dict["implied_volatility_surface"] = implied_volatility_surface
    
    return equity_IV_dict

#-----------------------------------------------------------------------------
# SANITY CHECKS (clean data perfectly in line with raw prices)
def yFinance_raw_to_refined_data_sanity_check(options_yf_pddf, refined_data_as_dictionnary, reference_precision=1e-5, log=False):
    ticker = refined_data_as_dictionnary["underlying_ticker"]
    adjusted_precision = reference_precision * np.power(10,np.floor(np.log10(refined_data_as_dictionnary["reference_spot"]))) #reference_precision time the order of magnitude of the spot (e.g. if spot =4321.98, 1000 time reference_precision)
    if log : print (ticker, "adjusted_precision:",adjusted_precision)
    for k in refined_data_as_dictionnary["implied_volatility_surface"]:
        expiry_date = k['expiry_date'] 
        if log: print('expiry_date:', expiry_date)
        reference_forward = k['reference_forward'] 
        if log: print(reference_forward)
        expiry_date_in_act365_year_fraction = k['expiry_date_in_act365_year_fraction'] 
        if log: print(expiry_date_in_act365_year_fraction)
        discount_factor = k['reference_discount_factor'] 
        if log: print(discount_factor)
        strikes_list = k["strikes"]
        mid_implied_volatilities_list = k['mid_implied_volatilities']
        bid_implied_volatilities_list = k['bid_implied_volatilities']
        ask_implied_volatilities_list = k['ask_implied_volatilities']
        for i in range(len(strikes_list)):
            strike = strikes_list[i]
            optionsKT = options_yf_pddf.loc[(options_yf_pddf["expiryDate"]==expiry_date) & (options_yf_pddf["strike"]==strike)]
            for j in range(len(optionsKT)):
                isCall = optionsKT["isCall"].iloc[j]
                if (isCall and strike>=reference_forward) or (not isCall and strike<reference_forward): #we have only considered out of the money options w.r.t. the reference forward
                    input_price_mid = optionsKT["mid"].iloc[j]
                    input_price_bid = optionsKT["bid"].iloc[j]
                    input_price_ask = optionsKT["ask"].iloc[j]
                    reprice_mid = black_price_formula(reference_forward, strike, expiry_date_in_act365_year_fraction,mid_implied_volatilities_list[i],isCall) * discount_factor
                    reprice_bid = black_price_formula(reference_forward, strike, expiry_date_in_act365_year_fraction,bid_implied_volatilities_list[i],isCall) * discount_factor
                    reprice_ask = black_price_formula(reference_forward, strike, expiry_date_in_act365_year_fraction,ask_implied_volatilities_list[i],isCall) * discount_factor
                    if (abs(input_price_bid-reprice_bid)>adjusted_precision or (abs(input_price_mid-reprice_mid)>adjusted_precision) or (abs(input_price_ask-reprice_ask)>adjusted_precision)):
                        print("Und ticker:",ticker, "; expiry date:", expiry_date,"; strike:", strikes_list[i], "; isCall:",isCall, "; Differences:", reprice_bid - input_price_bid, reprice_mid - input_price_mid, reprice_ask - input_price_ask, 
                        "references: ",input_price_bid, input_price_mid, input_price_ask)
    if log : print ("analysis completed.")

#-----------------------------------------------------------------------------
#Some Specific Graph utilities
class yFinance_Equity_IV_graph:
    def scatter_3D(ticker, data_dict):
        plt.figure(figsize = (8,8))
        ax = plt.axes(projection ="3d")

        for k in data_dict["implied_volatility_surface"]:
            ax.scatter( k['expiry_date_in_act365_year_fraction'], np.array(k['strikes'])/k['reference_forward'], k['mid_implied_volatilities'], s=10)
            
        ax.set_title(ticker)
        ax.set_xlabel(r'Maturity (year fraction)')
        ax.set_ylabel(r'Strike (fwd moneyness)')
        ax.set_zlabel(r'Implied Volatility')
        ax.grid()
        ax.view_init(20, 40)
        plt.show()

    def lines_3D(ticker, data_dict):
        plt.figure(figsize = (8,8))
        ax = plt.axes(projection ="3d")

        for k in data_dict["implied_volatility_surface"]:
            ax.plot(np.array(k['strikes'])/k['reference_forward'], k['mid_implied_volatilities'], zs=k['expiry_date_in_act365_year_fraction'],zdir='x')
            ax.scatter( k['expiry_date_in_act365_year_fraction'], np.array(k['strikes'])/k['reference_forward'], k['mid_implied_volatilities'], s=10)
            
        ax.set_title(ticker)
        ax.set_xlabel(r'Maturity (year fraction)')
        ax.axes.set_xlim3d(left=0, right=2)
        ax.set_ylabel(r'Strike (fwd moneyness)')
        ax.axes.set_ylim3d(bottom=0.4, top=2)
        ax.set_zlabel(r'Implied Volatility')
        ax.axes.set_zlim3d(bottom=0.0, top=1) 
        ax.set_zticks([0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])
        ax.grid()
        ax.view_init(20, 40)
        plt.show()

    def lines_2D(ticker, data_dict):
        plt.figure(figsize = (8,8))
        ax = plt.gca()

        for k in data_dict["implied_volatility_surface"]:
            ax.scatter(np.array(k['strikes'])/k['reference_forward'], k['mid_implied_volatilities'], label= k['expiry_date'], s=10)
            plt.plot(np.array(k['strikes'])/k['reference_forward'],k['mid_implied_volatilities'])

        ax.set_title(ticker)
        ax.set_xlabel(r'strike (fwd moneyness)')
        ax.set_ylabel(r'Implied Volatility')
        ax.legend()
        ax.grid()
        plt.show()