"""
Move function for hexbot.

"""

import math
from numpy import *

# lookup tables
# index of array is the timestep
# element of array is [x, y, z] position of leg relative to leg origin

# for legs touching ground (repeats because some legs will do things on 1st timestep and some will do on the 25th.)

def frange(start, stop, step):
    i = start
    ans = []
    for j in range(0, 24):
        ans.append(i)
        i += step
    return ans


def halfrange(start, stop, step):
    i = start
    ans = []
    for j in range(0, 12):
        ans.append(i)
        i += step
    return ans

###################################################
# Jayce's attemt at tables
SL = 4
xp = math.sin(math.radians(60)) * SL
yp = math.cos(math.radians(60)) * SL

x = frange(6, 6, 0)
z = frange(-3, -3, 0)
Yrange = frange(1.8, -1.8, -(3.6 / 23))
Rotate1 = matrix([[math.cos(math.radians(60)), math.sin(math.radians(60)), 0],
                  [-math.sin(math.radians(60)), math.cos(math.radians(60)), 0], [0, 0, 1]])
Rotate2 = matrix([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
Rotate3 = matrix([[math.cos(math.radians(60)), -math.sin(math.radians(60)), 0],
                  [math.sin(math.radians(60)), math.cos(math.radians(60)), 0], [0, 0, 1]])

zlift = halfrange(-3.0, -1.0 - (2.0 / 12.0), 2.0 / 12.0)
zlower = halfrange(-1.0 + (2.0 / 12.0), -3.0, 2.0 / 12.0)
zmove = []
for zint in range(0, len(zlift)):
    zmove.append(zlift[zint])
for zint in range(0, len(zlower)):
    zmove.append(zlower[zint])

ymove = frange(-1.8, 1.8, (3.6 / 23))

xlift = halfrange(6.0, 4.0 + (2.0 / 12.0), -2.0 / 12.0)
xlower = halfrange(4.0 + (2.0 / 12.0), 6.0, 2.0 / 12.0)
xmove = []
for xint in range(0, len(xlift)):
    xmove.append(xlift[xint])
for xint in range(0, len(xlower)):
    xmove.append(xlower[xint])

# Six tables are walk:x,Yrange,z; lift: xmove,ymove,zmove
###################################################

walkdown = []

for j in range(0, 24):
    trans1 = [xp, yp, 0]
    trans3 = [xp, -yp, 0]
    vec = [x(j), Yrange(j), z(j)]
    new_vec1 = (Rotate1*vec) + trans1
    new_vec3 = (Rotate3*vec) + trans3
    walkdown.append(new_vec1)
    walkdown.append(vec)
    walkdown.append(new_vec3)


walkdup = []

for j in range(0, 24):
    trans1 = [xp, yp, 0]
    trans3 = [xp, -yp, 0]
    vec = [xmove(j), ymove(j), zmove(j)]
    new_vec1 = (Rotate1*vec) + trans1
    new_vec3 = (Rotate3*vec) + trans3
    walkup.append(new_vec1)
    walkup.append(vec)
    walkup.append(new_vec3)

    #or else turn this into a function with math to determine the position
# ]


def movebot(command, timestep, legs):
    """
    Executes command. Meant to be run every timestep.
    Timesteps should be from 1 to 48
    Returns 16-element array of servo positions.
    """
    if command == 'walkforward':
        walkforward(timestep, legs)
    else:
        print "That's not a command I know."

def walkforward(timestep, legs):
    # check which legs should be down on this step
    if timestep < 24:
        evensturn = True
    else:
        evensturn = False

    for leg in legs:
        if leg.even == evensturn:
            leg.findangles(walkdown(timestep-1)) # find position for this timestep in lookup table (indexed from 0)
        else:
            leg.findangles(walkup(timestep-1))


