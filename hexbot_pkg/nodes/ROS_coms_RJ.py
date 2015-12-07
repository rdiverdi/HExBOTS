#!/usr/bin/env python
"""
Base structure for communicating with ROS
## = required for all ros programs, # = specific to this example
"""

import rospy  # import ros
from std_msgs.msg import String, Int16MultiArray  # import the ros messages we want to use

# Jayce's Imports
from Walk import *
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
        self.legs = []
        self.legpositions = []

        for i in range(0,5):
            self.legs.append(Leg(i))

        #example code
        rospy.init_node('message_counter')  # initialize node

        # listen to 'chatter' topic
        rospy.Subscriber('chatter', String, self.process_chatter)
        # publish to 'chatter_count' topic
        self.pub = rospy.Publisher('data_array', Int16MultiArray, queue_size=10)

        ''' initialize variables to use later '''
        self.out = Int16MultiArray
        self.msg = "no messages yet"
        self.msgs_recieved = 0

    def process_chatter(self, msg):
        """ Runs every time another node publishes to the chatter topic """
        # note, nothing in here is ROS specific, it's just python code that
        # runs when new info appears

        # print msg.data  # print the recieved message

        self.msgs_recieved += 1  # increase msg count
        self.msgs_recieved %= 500  # mod 500 so we don't get enormous numbers
        self.msg = "%d messages recieved" % self.msgs_recieved  # set message

#########################################################
# Stuff that Jayce is editing, and likely fucking up

    def push_data(self):

        self.pub('servo_positions', Array, queue_size=10)


    def run(self):
        """ main run loop """
        r = rospy.Rate(2)  # sets rate for the program to run (Hz)
        # instead of while true, otherwice crtl+C doesn't work

        while not rospy.is_shutdown():

            # find next servo position
            self.legpositions = hexy.movebot('walkforward', self.t, self.legs)
            # publish message to 'chatter_count' topic
            self.out.data = self.legpositions
            self.pub.publish(self.out)
            # increment timestep
            self.t += 1
            if self.t > 48:
                self.t = 1
            # wait until next time this code should run (according to rospy.Rate above)
            r.sleep()

if __name__ == '__main__':
    #run above code
    node = HExBOT()
    node.run()

