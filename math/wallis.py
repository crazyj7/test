import numpy as np

def wall(n):
	W=1
	for i in range(1,n+1):
		v1=(2*i)/(2*i-1)
		v2=(2*i)/(2*i+1)
		W=W*v1*v2
	return W


print('Wallis loop(10)=', wall(10))
print('Wallis loop(50)=', wall(50))
print('Wallis loop(100)=', wall(100))
print('Wallis loop(1000)=', wall(1000))
print('Wallis loop(10000)=', wall(10000))
print('Wallis loop(100000)=', wall(100000))
print('pi/2=', np.pi/2)

