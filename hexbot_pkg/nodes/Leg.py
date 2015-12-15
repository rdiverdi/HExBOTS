"""Leg Class for HExBOT"""
from math import *


class Leg():

    def __init__(self, index):
        self.index = index
        self.angleoffset = (60 * (index + 1)) % 360  # angle from horizontal starboard

        # current position of foot before offsets
        self.x = sqrt(15) + 1
        self.y = 0
        self.z = -4

        # whether the leg is currently rising or lowering at the end of a step
        self.switching = False

        # whether the leg is currently on the ground and able to support weight (-1 is down, 1 is up)
        self.onground = -1

        r = 3  # radius from center of hexbot to leg origin (theta servo) in whatever units we're using for this
        self.xoffset = r * cos(self.angleoffset)
        self.yoffset = r * sin(self.angleoffset)

        # the amount shifted out and forward the step pattern is,
        # relative to a side leg. 0 for now, unless needed

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

        # even or odd
        if index % 2 == 0:
            self.even = True
        else:
            self.even = False

        # lengths of each leg link
        self.L0 = 1
        self.L1 = 4
        self.L2 = 5

    def findangles(self, x, y, z):
        """
        Takes in the x, y, and z positions of the foot relative to the leg origin.
        Returns the theta, phi, and psi angles.
        """
        # move to correct horizontal position

        xy_dist = sqrt(x**2 + y**2) - self.L0  # distance to the foot in the xy plane
        abs_dist = sqrt(xy_dist**2 + z**2)  # 3D distance to the end of the foot
        angle_down = degrees(atan2(z, xy_dist))  # angle down from the xy plane to the foot (negative)
        # law of cosines to find angles
        v = degrees(acos(((self.L1**2) - (self.L2**2) + (abs_dist**2)) / (2 * self.L1 * abs_dist)))  # phi angle without height added
        w = degrees(acos(((self.L1**2) + (self.L2**2) - (abs_dist**2)) / (2 * self.L1 * self.L2)))  # psi angle

        tha = degrees(atan2(y, x)) - self.angleoffset
        phi = (angle_down + v)
        if phi >= 90:
            phi = 90
        psi = w
        return (tha, phi, psi)

    def returnangles(self):
        """
        returns the theta, phi, and psi angles
        that correspond to its current position
        """
        x = x + self.stepxoffset
        y = y + self.stepyoffset

        angles = findangles(self, x, y, self.z)
        return angles

    def movespeed(self, dx, dy, runrate):
        """
        takes in the speed the hexbot is moving in inches per second
        and the rate of the loop running in hertz
        updates the leg.x, y, and z
        automatically raises and lowers legs
        returns array of 18 angles to send to arduino.
        """
        persecond = runrate*60  # times the loop runs per second
        # multiplying by onground makes foot move in opposite direction to desired motion while touching ground
        xmove = dx/persecond*self.onground
        ymove = dy/persecond*self.onground

        self.x += xmove
        self.y += ymove

        angles1 = findangles(x1, y1, self.z)

        #check whether any angles are within ten degrees of a limit
        if (angles1(0) < -35 or
           angles1(0) > 35 or
           angles1(1) < 0 or
           angles1(1) > 80 or
           angles1(2) < 20 or
           angles1(3) > 120):
            self.switching = True
        else:
            self.switching = False

        if self.switching:
            # raise or lower leg at end of step
            raiserate = -1*self.onground*norm(dx, dy)/runrate  # make the rate of foot lowering somewhat proportional to the rate it's approaching the limit
            self.z += raiserate

        # check whether leg is still on ground or not and make sure it doesn't overshoot
        # doesn't switch on-ground state until the lift or lower has completed, hopefully.         
        if self.z <= -4:
            self.z = -4
            self.onground = -1
        elif self.z >= 0:
            self.z = 0
            self.onground = 1

        outangles = self.returnangles()
        return outangles

if __name__ == '__main__':
    leg = Leg(3)
    print leg.findangles(-5, 0, 0)
