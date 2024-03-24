import numpy as np
import sys

q=int(sys.argv[1])
mean=np.array([0.010111,0.0043552,0.0137058])
cov=np.array([[0.00324625,0.00022983,0.00420395],
             [0.00022983,0.00049937,0.00019247],
             [0.00420395,0.00019247,0.00764897]])
             
otv=np.random.multivariate_normal(mean,cov,q);
np.savetxt('Generatedy1y2y3.txt',otv)
