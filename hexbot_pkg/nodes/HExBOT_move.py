"""
Move function for hexbot.

"""

from numpy import *
from Leg import *

class Hexbot:
    def __init__(self, runrate):
        # lookup tables
        # index of array is the timestep
        # element of array is [x, y, z] position of leg relative to leg origin
        # for legs touching ground (repeats because some legs will do things on 1st timestep and some will do on the 25th.)
        self.runrate = runrate

        '''
        self.walkdown = [None] * 48
        self.walkup = [None] * 48
        for i in range(0, 24):
            walkdown[i] = [6, 1.8 - (i * 3.6 / 23), -4]
            walkdown[i + 24] = walkdown[i]
            walkup[i] = ([6, -1.8 + (i * 3.6 / 23), -abs(i - 11) / 3.0])
            walkup[i + 24] = walkup[i]
        '''

        self.even_down = True

        self.legs = self.init_legs()
        self.t = 1
        self.legpositions = []

         # start even legs off the ground
        for leg in self.legs:
            if leg.even:
                leg.z = 0
                leg.onground = 1
            self.legpositions.extend(leg.returnangles())


    def init_legs(self):
        legs = []
        for i in range(0, 6):
            legs.append(Leg(i + 1))
        return legs


    def movebot(self, command):
        """
        Executes command. Meant to be run every timestep.
        Timesteps should be from 1 to 48
        legs is a list of instances of legs (0-5)
        Returns 16-element array of servo positions.
        """
        if command == 'walkforward':
            return walkforward()
        elif command == 'turn':
            print "Hahaha good one no."
        else:
            print "That's not a command I know."


    def walkforward(self):
        """
        takes in the timestep (1-48) and a list of instances of the legs
        check the lookup tables and output the x, y, z positions of each foot with respect to its leg origin
        in the form of a list of 18 angles
        """
        anglelist = []
        # check which legs should be down on this step

        for leg in self.legs:
            if leg.even == evensturn:
                # find the x y z position for this timestep
                [x, y, z] = walkup[timestep]
                # mirror across the y axis for legs on the left
            else:
                [x, y, z] = walkdown[timestep]

            if leg.index < 4:
                x = -1 * x
            angles = leg.findangles(x, y, z)
            for (i, angle) in enumerate(angles):
                if leg.even != evensturn and i % 3 == 1:  # find servo 1 of all legs that are down
                    angle = angle - 18  # move servo 1 an extra 18 degrees down to account for angle loss due to holding weight
                anglelist.append((angle + 180) % 360 - 180)  # convert angle to -180 to 180
        return anglelist


    def walkrate(self, dx, dy, runrate):
        """
        takes in a list of the leg instances
        walks in dx, dy direction (rates given in inches per second)
        returns the list of 18 angles for the current time
        """
        anglelist = []

        switching = False
        for leg in self.legs:
            switching = switching or leg.check_limit()
        print switching

        for leg in self.legs:
            if switching and leg.even:
                angles = leg.movespeed(dx, dy, -2, runrate)
            elif switching and not leg.even:
                angles = leg.movespeed(dx, dy, 2, runrate)
            else:
                angles = leg.movespeed(dx, dy, 0, runrate)
            # add 18 degrees down to servo 1 if the leg should be on the ground 
            # maybe we should move this to findangles
            if leg.even:
                angles[1] -= 0
            anglelist.extend(angles)
        return anglelist

# create leg instances for testing. In use, these will be created in ROS_coms file
if __name__=='__main__':
    legs = []
    for i in range(0, 6):
        legs.append(Leg(i))

    # for i in range(48):
    #    movebot('walkforward', i, legs)
    # print len(walkdown)
    # for i in range(len(walkdown)):
    #    print walkdown[i]
    # print len(walkforward(7, legs))
