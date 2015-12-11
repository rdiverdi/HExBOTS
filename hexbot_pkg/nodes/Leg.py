"""Leg Class for HExBOT"""
from math import *

class Leg():

    def __init__(self, index):
        self.index = index
        self.angleoffset = (60 * (index+1))%360  # angle from horizontal starboard 

        r = 3#radius from center to leg origin (theta servo) in whatever units we're using for this
        self.xoffset = r*cos(self.angleoffset)
        self.yoffset = r*sin(self.angleoffset)

        #the amount shifted out and forward the step pattern is,
        #relative to a side leg. 0 for now, unless needed

        yoffset = 4
        xoffset = -1
        if self.index == 1:
            self.stepyoffset = yoffset
            self.stepxoffset = -xoffset
        elif self.index == 3:
            self.stepyoffset = -yoffset
            self.stepxoffset = -xoffset
        elif self.index == 4:
            self.stepyoffset = -yoffset
            self.stepxoffset = xoffset
        elif self.index == 6:
            self.stepyoffset = yoffset
            self.stepxoffset = xoffset
        else:
            self.stepyoffset = 0
            self.stepxoffset = 0

        #even or odd
        if index % 2 == 0:
            self.even = True
        else:
            self.even = False

        #lengths of each leg link??
        self.L0 = 1
        self.L1 = 4
        self.L2 = 5

    def findangles(self, x, y, z):
        """
        Takes in the x, y, and z positions of the foot relative to the leg origin.
        Returns the theta, phi, and psi angles.
        """
        #move to correct horizontal position
        x = x+self.stepxoffset
        y = y+self.stepyoffset 

        xy_dist = sqrt(x**2 + y**2) - self.L0 #distance to the foot in the xy plane
        abs_dist = sqrt(xy_dist**2 + z**2) #3D distance to the end of the foot
        angle_down = degrees(atan2(z, xy_dist)) #angle down from the xy plane to the foot (negative)
        #law of cosines to find angles
        v = degrees(acos(((self.L1**2) - (self.L2**2) + (abs_dist**2)) / (2 * self.L1 * abs_dist))) #phi angle without height added
        w = degrees(acos(((self.L1**2) + (self.L2**2) - (abs_dist**2)) / (2 * self.L1 * self.L2))) #psi angle

        tha = degrees(atan2(y, x)) - self.angleoffset
        phi = (angle_down + v)
        if phi >= 90:
            phi = 90
        psi = w
        return (tha, phi, psi)

if __name__ == '__main__':
    leg = Leg(3)
    print leg.findangles(-5, 0, 0)