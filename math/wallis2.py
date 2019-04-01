import numpy as np
import matplotlib.pyplot as plt


x=[]
y=[]

def wall(n):
	W=1
	for i in range(1,n+1):
		v1=(2*i)/(2*i-1)
		v2=(2*i)/(2*i+1)
		W=W*v1*v2
		x.append(i)
		y.append(W)
	return W

loop=1000
W=wall(loop)
plt.figure()
plt.ylim(1, 2)
plt.plot(x,y, label='W')
plt.hlines(np.pi/2, 0, loop, label='PI/2')
plt.legend()
plt.show()



