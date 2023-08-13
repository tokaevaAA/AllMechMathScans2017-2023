from distutils.core import setup                                        
from distutils.extension import Extension                               
from Cython.Build import cythonize
import numpy as np

ext_modules=[]

# We need to specify the path to all the scripts involved in this module
ext_modules+=[
    Extension("LetsBeRationalForPython",
    sources=["LetsBeRationalForPython.pyx",
    "./LetsBeRational/lets_be_rational.cpp",
    "./LetsBeRational/erf_cody.cpp",
    "./LetsBeRational/rationalcubic.cpp",
    "./LetsBeRational/normaldistribution.cpp"],
             )]


setup(name='LetsBeRationalForPython',
    description='Implied Volatility Library',
    author='CH following Aitor Muguruza',
    ext_modules = cythonize(ext_modules),
    script_args=["build_ext"],
    options={'build_ext':{'inplace':True}},
    include_dirs=[np.get_include()]
     )

