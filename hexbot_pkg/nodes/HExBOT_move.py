"""
Move function for hexbot.

"""

import math
from numpy import *
from Leg import *
print dir(Leg)
print type(Leg.findangles)
# Leg.findangles(6,1.8,-3)

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

for j in range(24):
    trans1 = matrix([[xp], [yp], [0]])
    trans3 = matrix([[xp], [-yp], [0]])
    vec = matrix([[x[j]], [Yrange[j]], [z[j]]])
    new_vec1 = (Rotate1*vec) + trans1
    new_vec3 = (Rotate3*vec) + trans3
#     print "vec"
#     print vec
#     print "new 1"
#     print new_vec1
#     print "new 3"
#     print new_vec3
    walkdown.append(new_vec1[0,0])
    walkdown.append(new_vec1[1,0])
    walkdown.append(new_vec1[2,0])
    walkdown.append(vec[0,0])
    walkdown.append(vec[1,0])
    walkdown.append(vec[2,0])
    walkdown.append(new_vec3[0,0])
    walkdown.append(new_vec3[1,0])
    walkdown.append(new_vec3[2,0])

# print walkdown


walkup = []

for j in range(0, 24):
    trans1 = matrix([[xp], [yp], [0]])
    trans3 = matrix([[xp], [-yp], [0]])
    vec = matrix([[x[j]], [Yrange[j]], [z[j]]])
    new_vec1 = (Rotate1*vec) + trans1
    new_vec3 = (Rotate3*vec) + trans3
    walkup.append(new_vec1[0,0])
    walkup.append(new_vec1[1,0])
    walkup.append(new_vec1[2,0])
    walkup.append(vec[0,0])
    walkup.append(vec[1,0])
    walkup.append(vec[2,0])
    walkup.append(new_vec3[0,0])
    walkup.append(new_vec3[1,0])
    walkup.append(new_vec3[2,0])

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
    elif command == 'turn':
        print "Hahaha good one no."
    else:
        print "That's not a command I know."

def walkforward(timestep, legs):
    move = []
    # check which legs should be down on this step
    if timestep < 24:
        evensturn = True
    else:
        evensturn = False

    for leg in legs:
        check = leg%2
        if check == 0:
            second_check = True
        else: second_check = False
        if second_check == evensturn:
            Leg.findangles(walkup[(timestep*9)+0], walkup[(timestep*9)+1], walkup[(timestep*9)+2])
            Leg.findangles(walkdown[(timestep*9)+3], walkdown[(timestep*9)+4], walkdown[(timestep*9)+5])
            Leg.findangles(walkup[(timestep*9)+6], walkup[(timestep*9)+7], walkup[(timestep*9)+8])
            Leg.findangles(walkdown[(timestep*9)+6], walkdown[(timestep*9)+7], walkdown[(timestep*9)+8])
            Leg.findangles(walkup[(timestep*9)+3], walkup[(timestep*9)+4], walkup[(timestep*9)+5])
            Leg.findangles(walkdown[(timestep*9)+0], walkdown[(timestep*9)+1], walkdown[(timestep*9)+2])

        else:
            Leg.findangles(walkdown[(timestep*9)+0], walkdown[(timestep*9)+1], walkdown[(timestep*9)+2])
            Leg.findangles(walkup[(timestep*9)+3], walkup[(timestep*9)+4], walkup[(timestep*9)+5])
            Leg.findangles(walkdown[(timestep*9)+6], walkdown[(timestep*9)+7], walkdown[(timestep*9)+8])
            Leg.findangles(walkup[(timestep*9)+6], walkup[(timestep*9)+7], walkup[(timestep*9)+8])
            Leg.findangles(walkdown[(timestep*9)+3], walkdown[(timestep*9)+4], walkdown[(timestep*9)+5])
            Leg.findangles(walkup[(timestep*9)+0], walkup[(timestep*9)+1], walkup[(timestep*9)+2])

for i in range(48):
    movebot('walkforward', i, [0,1,2,3,4,5])
# print len(walkdown)
# for i in range(len(walkdown)):
#     print type(walkdown[i])
