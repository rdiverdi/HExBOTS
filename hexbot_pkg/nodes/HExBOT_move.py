"""
Move function for hexbot.

"""

from numpy import *
from Leg import *

# lookup tables
# index of array is the timestep
# element of array is [x, y, z] position of leg relative to leg origin
# for legs touching ground (repeats because some legs will do things on 1st timestep and some will do on the 25th.)
walkdown = [None]*48
walkup = [None]*48
for i in range(0, 24):
    walkdown[i] = [6, 1.8 - (i*3.6/23), -4]
    walkdown[i + 24] = walkdown[i]
    walkup[i] = ([6, -1.8 + (i*3.6/23), -abs(i - 11)/3.0])
    walkup[i + 24] = walkup[i]

def init_legs():
    legs = []
    for i in range(0,6):
        legs.append(Leg(i+1))
    return legs

def movebot(command, timestep, legs):
    """
    Executes command. Meant to be run every timestep.
    Timesteps should be from 1 to 48
    legs is a list of instances of legs (0-5)
    Returns 16-element array of servo positions.
    """
    if command == 'walkforward':
        return walkforward(timestep, legs)
    elif command == 'turn':
        print "Hahaha good one no."
    else:
        print "That's not a command I know."


def walkforward(timestep, legs):
    """
    takes in the timestep (1-48) and a list of instances of the legs
    check the lookup tables and output the x, y, z positions of each foot with respect to its leg origin
    in the form of a list of 18 angles
    """
    anglelist = []
    # check which legs should be down on this step
    if timestep < 24:
        evensturn = True
    else:
        evensturn = False

    for leg in legs:
        if leg.even == evensturn:
            # find the x y z position for this timestep
            [x, y, z] = walkup[timestep]
            # mirror across the y axis for legs on the left
        else:
            [x, y, z] = walkdown[timestep]

        if leg.index < 4:
            x = -1*x
        angles = leg.findangles(x, y, z)
        for (i, angle) in enumerate(angles):
            if leg.even != evensturn and i%3 == 1:
                angle = angle-15
            anglelist.append((angle+180)%360-180)
    return anglelist

# create leg instances for testing. In use, these will be created in ROS_coms file
if __name__=='__main__':
    legs = []
    for i in range(0, 6):
        legs.append(Leg(i))

    #for i in range(48):
    #    movebot('walkforward', i, legs)
    #print len(walkdown)
    #for i in range(len(walkdown)):
    #    print walkdown[i]
    #print len(walkforward(7, legs))
