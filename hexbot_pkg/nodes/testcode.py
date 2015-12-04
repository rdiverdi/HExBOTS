from math import *
import numpy as np
import time

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim3d(-10, 10)
ax.set_ylim3d(-10, 10)
ax.set_zlim3d(-5, 5)

body_r = 3

def get_end_pos(t1, t2, t3, leg):
    L1 = 4
    L2 = 5
    body_r = 3
    start_t = leg * pi/3 - pi/6
    start_pos = [body_r*cos(start_t), body_r*sin(start_t)]

    r = sqrt(L1**2 + L2**2 - 2*L1*L2*cos(t3*pi/180))
    phi = (90-t2)*pi/180+asin(L2*sin(t3*pi/180)/r)
    theta = t1*pi/180+start_t

    x = r*cos(theta)*sin(phi)+start_pos[0]
    y = r*sin(theta)*sin(phi)+start_pos[1]
    z = r*cos(phi)

    return [start_pos + [0], [x, y, z]]


theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
z = [0]*len(theta)
x = body_r * np.sin(theta)
y = body_r * np.cos(theta)
ax.plot(x, y, z, label='MainBody')
plt.ion()
plt.show()
for i in range(6):
    line = get_end_pos(0, 20, 120, i+1)
    line_xyz = [[line[end][var] for end in range(len(line))] for var in range(3)]
    ax.plot(line_xyz[0], line_xyz[1], line_xyz[2], label='leg%d' %(i+1))
    ax.legend()

plt.draw()
time.sleep(3)