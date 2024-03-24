
HOW TO GENERATE THE COMPILED FILE:
----------------------------------
To generate a file 'LetsBeRationalForPython.<<platform_info>>.<<os_specific_extension>>' where:
- <<platform_info>> is something like 'cp310-win_amd64', 'cpython-310-darwin',or'cpython-310-x86_64-linux-gnu' (cpython with python version 3.10, and os specific information),
- <<os_specific_extension>> is something like 'pyd', 'so'.

1 - create  and activate a virtual environment with the target version of python (not mandatory, just cleaner)
2 - pip install numpy, cython
3 - run 'python setup.py build_ext --inplace' from the directory where the setup.py is located (cd Black_utilities\).
