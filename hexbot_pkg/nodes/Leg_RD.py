"""Leg Class for HExBOT"""
from math import *


class Leg():

    def __init__(self, index):
        self.lim = False
        self.index = index
        self.angleoffset = (60 * (index + 1)) % 360  # angle from horizontal starboard

        self.angles = []

        #is even?
        if index % 2 == 0:
            self.even = True
        else:
            self.even = False


        # current position of foot before offsets
        if self.index > 3:
           self.x = 5
        else:
            self.x = -5
        if self.index == 1 or self.index == 6:
            self.x = 4./5*self.x
            self.y = 3
        elif self.index == 3 or self.index == 4:
            self.x = 4./5*self.x
            self.y = -3
        else:
            self.y = 0

        if self.even:
            self.z = -4
        else:
            self.z = 0

        # whether the leg is currently rising or lowering at the end of a step
        self.switching = False

        # whether the leg is currently on the ground and able to support weight (-1 is down, 1 is up)

        r = 3  # radius from center of hexbot to leg origin (theta servo) in whatever units we're using for this
        self.xoffset = r * cos(self.angleoffset*pi/180)
        self.yoffset = r * sin(self.angleoffset*pi/180)

        # the amount shifted out and forward the step pattern is,
        # relative to a side leg. 0 for now, unless needed
        '''
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
        '''
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

        #make range -180 to 180
        tha = (tha+180)%360-180
        phi = (phi+180)%360-180
        psi = (psi+180)%360-180

        return [tha, phi, psi]

    def returnangles(self):
        """
        returns the theta, phi, and psi angles
        that correspond to its current position
        """
        x_real = self.x# + self.stepxoffset
        y_real = self.y# + self.stepyoffset

        angles = self.findangles(x_real, y_real, self.z)
        return angles

    def movespeed(self, dx, dy, z, ds, runrate):
        """
        takes in the speed the hexbot is moving in inches per second
        and the rate of the loop running in hertz
        updates the leg.x, y, and z
        automatically raises and lowers legs
        returns array of 18 angles to send to arduino.
        """
        persecond = runrate  # times the loop runs per second
        # multiplying by onground makes foot move in opposite direction to desired motion while touching ground
        xmove = dx/float(persecond)
        ymove = dy/float(persecond)

        
        abs_x = self.x + self.xoffset
        abs_y = self.y + self.yoffset

        new_x = sqrt(abs_x**2 + abs_y**2)*cos(atan2(abs_y, abs_x)+(ds*pi/180.))
        new_y = sqrt(abs_x**2 + abs_y**2)*sin(atan2(abs_y, abs_x)+(ds*pi/180.))
        self.x = new_x - self.xoffset
        self.y = new_y - self.yoffset


        self.x += xmove
        self.y += ymove
        self.z = z

        outangles = self.returnangles()
        return outangles

    def check_limit(self):
        angles1 = self.returnangles()

        if (((angles1[0]+180)%360-180 < -25 and (self.angles[0] - angles1[0]) > 0) or
           ((angles1[0]+180)%360-180 > 25 and (self.angles[0] - angles1[0]) < 0) or
           (angles1[1] < 0 and (self.angles[1] - angles1[1]) > 0) or
           (angles1[1] > 88 and (self.angles[1] - angles1[1]) < 0) or
           (angles1[2] < 30 and (self.angles[2] - angles1[2]) > 3) or
           (angles1[2] > 110 and (self.angles[2] - angles1[2]) < -3)):
            print 'ahh'
            print self.index
            #print (angles1[0]+180)%360-180
            #print self.angles[0] - angles1[0]
            self.angles = angles1
            self.lim = True
            return True
        else:
            self.angles = angles1
            self.lim = False
            return False

if __name__ == '__main__':
    leg = Leg(3)
    print leg.findangles(-5, 0, 0)
