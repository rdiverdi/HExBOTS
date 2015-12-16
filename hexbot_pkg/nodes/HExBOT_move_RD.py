"""
Move function for hexbot.

"""

from numpy import *
from Leg_RD import *

class Hexbot:
    def __init__(self, runrate):
        """ initialize variables for the hexbot level of control """
        self.runrate = runrate # get runrate in hertz

        self.even_down = True # start with even legs down

        self.legs = self.init_legs() # initialize list of legs
        self.move_down = False #start by not switching legs
        self.move_up = False
        self.z = 0.0

        self.legpositions = []
        for leg in self.legs: # initialize list of leg positions
            self.legpositions.extend(leg.returnangles())


    def init_legs(self):
        """ initializes a list of legs """
        legs = []
        for i in range(0, 6):
            legs.append(Leg(i + 1))
        return legs

    def walkrate(self, dx, dy, ds, runrate):
        """
        walks in dx, dy direction (rates given in inches per second)
        returns the list of 18 angles for the current time
        """
        anglelist = [] #start with empty angle list

        down = -4
        up = 0

        for leg in self.legs: #check for any limits, if limits are hit, start switching
            if not self.move_up or self.move_down:
                self.move_down = leg.check_limit() or self.move_down


        for leg in self.legs:
            if self.move_down and (leg.even != self.even_down):
                self.z -= 2.0/self.runrate
                if self.z < down:
                    self.z = down - 0.01
                angles = leg.movespeed(dx, dy, self.z, ds, runrate)
            elif self.move_up and (leg.even != self.even_down):
                self.z += 2.0/self.runrate
                if self.z > up:
                    self.z = up + 0.01
                angles = leg.movespeed(dx, dy, self.z, ds, runrate)
            elif leg.even == self.even_down:
                angles = leg.movespeed(-dx, -dy, down, -ds, runrate)
            else:
                angles = leg.movespeed(dx, dy, up, ds, runrate)

            # add 18 degrees down to servo 1 if the leg should be on the ground 
            # maybe we should move this to findangles
            if leg.even == self.even_down:
                angles[1] -= 0
            anglelist.extend(angles)

        if self.z < down:
            self.move_down = False
            self.move_up = True
            self.even_down = (not self.even_down)
            self.z = down

        if self.z > up:
            self.move_up = False
            self.z = up

        self.legpositions = anglelist

# create leg instances for testing. In use, these will be created in ROS_coms file
if __name__=='__main__':
    legs = []
    for i in range(0, 6):
        legs.append(Leg(i))

    # for i in range(48):
    #    movebot('walkforward', i, legs)
    # print len(walkdown)
    # for i in range(len(walkdown))
    #    print walkdown[i]
    # print len(walkforward(7, legs))
