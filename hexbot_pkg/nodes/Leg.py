"""Leg Class for HExBOT"""
from math import *

class Leg():

    def __init__(self, index):
        self.index = index
        self.angleoffset = 30 + 60 * (index - 1)  # angle from straight ahead
        self.xoffset = False  # I still don't quite get how you determine x and y offset
        self.yoffset = False  # Please to fill in
        if index % 2 == 0:
            self.even = True
        else:
            self.even = False

    def findangles(self, x, y, z):
        """
        Takes in the x, y, and z positions of the foot relative to the leg origin.
        Returns the theta, phi, and psi angles.
        """
        # Needs to be filled with actual math
        # possibly put the actual math in a different file and call functions from it, for neatness.

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
        # angles.append(tha)
        # angles.append(phi)
        # angles.append(psi)
        # return angles
        
        # Nothing is being returned...
        
        pass
