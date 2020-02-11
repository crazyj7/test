

'''
3d plot test
'''

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter

dfthres = pd.read_csv('thresstat.csv')
print(dfthres)
print(dfthres.shape)


fig=plt.figure()
ax = fig.add_subplot(111, projection='3d')

X = dfthres.FThres
Y = dfthres.DThres
# X,Y = np.meshgrid(X,Y)
Z = dfthres.FA
Z2 = dfthres.FR
ax.set_xlabel('Fthres')
ax.set_ylabel('Dthres')
ax.scatter(X,Y,Z, c='b', label='FA')
ax.scatter(X,Y,Z2, c='r', label='FR')
ax.legend()
plt.show()



