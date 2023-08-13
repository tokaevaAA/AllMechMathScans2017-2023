# Black_utilities

This is almost identical to what is presented in the lecture "cython" by Aitor Muguruza available at https://github.com/JackJacquier/python-for-finance.

The purpose of this small module is to provide Black Formula (price of an undiscounted european call or put option in a model where the forward to maturity of the underlying asset is described as an exponential brownian martingale under the T forward measure), Black delta, Black vega and Black gamma in C for python.

Moreover, an implied volatility computation based on Peter Jaeckel's "Let's be rational" is also provided. This requires a pre-computed file 'LetsBeRationalForPython.<<platform_info>>.<<os_specific_extension>>'. The distribution provides this file for mac, windows, and linux. If needed, README.txt in the folder 'Black_utilities' explains how this file can be generated.

Finally, a direct implementation in Python of these formulas and of an implied volatility computation using Newton-Raphson is provided in 'Black_utilities_self_contained.py'. The files 'Black_utilities_examples.ipynb' and 'Black_utilities_examples.py' shows the difference in term of performance between this direct python implementation and the C integration (note that implied volatility computation is not just faster using "Let's be rational", it is also more accurate).

Technical comments:
- required: python 3+, numpy, cython (and scipy to run 'Black_utilities_self_contained_using_scipy.py').
- a minimal distribution would only include one 'LetsBeRationalForPython.<<platform_info>>.<<os_specific_extension>>' (the one corresponding to the targeted platform), and woud not include 'setup.py', 'Black_utilities_self_contained_using_scipy.py', 'Black_utilities_self_contained_without_scipy.py' nor 'LetsBeRational.pdf' (in the forlder 'LetsBeRational').
