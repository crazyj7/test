import numpy as np
import matplotlib.pyplot as plt

from MyPlot import MyPlot
import sys




# line1:(x11,y11)-(x12,y12) , line2:(x21,y21)-(x22,y22)
def get_crosspt(x11,y11, x12,y12, x21,y21, x22,y22):
    if x12==x11 or x22==x21:
        print('delta x=0')
        if x12==x11:
            cx = x12
            m2 = (y22 - y21) / (x22 - x21)
            cy = m2 * (cx - x21) + y21
            return cx, cy
        if x22==x21:
            cx = x22
            m1 = (y12 - y11) / (x12 - x11)
            cy = m1 * (cx - x11) + y11
            return cx, cy

    m1 = (y12 - y11) / (x12 - x11)
    m2 = (y22 - y21) / (x22 - x21)
    if m1==m2:
        print('parallel')
        return None
    print(x11,y11, x12, y12, x21, y21, x22, y22, m1, m2)
    cx = (x11 * m1 - y11 - x21 * m2 + y21) / (m1 - m2)
    cy = m1 * (cx - x11) + y11

    return cx, cy


# line1:(x11,y11)-(x12,y12) , line2:(x21,y21)-(x22,y22)
# check corss or not?
def is_divide_pt(x11,y11, x12,y12, x21,y21, x22,y22):
    '''input: 4 points
    output: True/False
    '''
    #  // line1 extension이 line2의 두 점을 양분하는지 검사..
    # 직선의 양분 판단
    f1= (x12-x11)*(y21-y11) - (y12-y11)*(x21-x11)
    f2= (x12-x11)*(y22-y11) - (y12-y11)*(x22-x11)
    if f1*f2 < 0 :
      return True
    else:
      return False

def is_cross_pt(x11,y11, x12,y12, x21,y21, x22,y22):
    b1 = is_divide_pt(x11,y11, x12,y12, x21,y21, x22,y22)
    if b1: print('OK divide')
    else: print('No divide')
    b2 = is_divide_pt(x21,y21, x22,y22, x11,y11, x12,y12)
    if b2: print('OK divide')
    else: print('No divide')
    if b1 and b2:
        print('OK Cross')
        return True
    print('No Cross')
    return False

# mp = MyPlot()
# mp.initplot(1,1)
#
# # horizontal test
# x11,y11 = 10,  50
# x12,y12 = 100, 50
# x21,y21 = 50, 10
# x22,y22 = 50, 100
#
#
# # vertical test
# x11,y11 = 50, 10
# x12,y12 = 50, 100
# x21,y21 = 10, 50
# x22,y22 = 100, 50
#
# mp.nextplot()
# plt.plot([x11, x12], [y11, y12], c='r')
# plt.plot([x21, x22], [y21, y22], c='b')
# isInterSect = is_cross_pt(x11, y11, x12, y12, x21, y21, x22, y22)
# if isInterSect:
#     plt.xlabel("INTERSECT")
#     # intersect point
#     cx, cy = get_crosspt(x11, y11, x12, y12, x21, y21, x22, y22)
#     plt.plot(cx, cy, 'ro')
#
# mp.show()
# sys.exit(1)



mp = MyPlot()
mp.initplot(4,4)
for i in range(16):
    x11 =np.random.randint(1,100)
    y11 =np.random.randint(1,100)
    x12 =np.random.randint(1,100)
    y12 =np.random.randint(1,100)
    x21 =np.random.randint(1,100)
    y21 =np.random.randint(1,100)
    x22 =np.random.randint(1,100)
    y22 =np.random.randint(1,100)

    # x11, y11 = 10, 50
    # x12, y12 = 100, 50
    # x11,y11 = 50, 10
    # x12,y12 = 50, 100

    mp.nextplot()
    plt.plot([x11,x12], [y11,y12], c='r')
    plt.plot([x21,x22], [y21,y22], c='b')
    isInterSect = is_cross_pt(x11, y11, x12, y12, x21, y21, x22, y22)
    if isInterSect :
        plt.xlabel("INTERSECT")
        # intersect point
        cx, cy = get_crosspt(x11, y11, x12, y12, x21, y21, x22, y22)
        plt.plot(cx, cy, 'ro')
    # else:
    #     plt.xlabel("NO CROSS")

mp.show()



