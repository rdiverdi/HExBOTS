#!/usr/bin/env python
"""
Base structure for communicating with ROS
## = required for all ros programs, # = specific to this example
"""

import rospy  # import ros
from std_msgs.msg import String, Int16MultiArray, MultiArrayLayout, MultiArrayDimension # import the ros messages we want to use

# Jayce's Imports
import math
from numpy import *

# RJ's Imports
import HExBOT_move as hexy
from Leg import *


""" ## = required for all ros programs, # = specific to this example """
class HExBOT(object):  # classes make things better, promise

    """ This class encompasses the entire node """

    def __init__(self):
        ''' setup ROS stuff '''

        # my stuff
        self.t = 1
        self.legs = hexy.init_legs()
        self.legpositions = []

        rospy.init_node('hexbot_control')  # initialize node

        # publish to 'data_array' topic
        self.pub = rospy.Publisher('data_array', Int16MultiArray, queue_size=10)
        self.error_pub = rospy.Publisher('errors', String, queue_size=10) # publish to 'errors' topic

        ''' initialize variables to use later '''
        self.out = Int16MultiArray()

#########################################################
# Stuff that Jayce is editing, and likely fucking up


    def run(self):
        """ main run loop """
        r = rospy.Rate(3)  # sets rate for the program to run (Hz)
        # instead of while true, otherwice crtl+C doesn't work

        while not rospy.is_shutdown():

            # find next servo position
            self.legpositions = hexy.movebot('walkforward', self.t, self.legs)
            self.out.data = self.legpositions
            self.pub.publish(self.out)
            # increment timestep
            self.t += 1
            if self.t >= 48:
                self.t = 1
            # wait until next time this code should run (according to rospy.Rate above)
            r.sleep()

if __name__ == '__main__':
    #run above code
    node = HExBOT()
    node.run()

