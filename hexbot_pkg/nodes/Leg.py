"""Leg Class for HExBOT"""
from math import *

class Leg():

    def __init__(self, index):
        self.index = index
        self.angleoffset = 30 + 60 * (index - 1)  # angle from horizontal starboard 

        r = #radius from center to leg origin (theta servo) in whatever units we're using for this
        self.xoffset = r*cos(angleoffset)
        self.yoffset = r*sin(angleoffset)

        #the amount shifted out and forward the step pattern is,
        #relative to a side leg. 0 for now, unless needed
        self.stepxoffset = 0
        self.stepyoffset = 0

        #even or odd
        if index % 2 == 0:
            self.even = True
        else:
            self.even = False

        #lengths of each leg link??
        self.L0 = 
        self.L1 =
        self.L2 = 

    def findangles(self, x, y, z):
        """
        Takes in the x, y, and z positions of the foot relative to the leg origin.
        Returns the theta, phi, and psi angles.
        """

        e = sqrt(x**2 + y**2) - L0
        f = sqrt(e**2 + z**2)
        u = math.degrees(math.atan(z / e))
        v = math.degrees(math.acos(((L1**2) - (L2**2) + (f**2)) / (2 * L1 * f)))
        w = math.degrees(math.acos(((L1**2) + (L2**2) - (f**2)) / (2 * L1 * L2)))

        tha = math.degrees(math.atan(y / x))
        phi = (u + v)
        if phi >= 90:
            phi = 90
        psi = w
        
        return (tha, phi, psi)
