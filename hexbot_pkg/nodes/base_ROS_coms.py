#!/usr/bin/env python

""" Base structure for communicating with ROS """
""" ## = required for all ros programs, # = specific to this example """

import rospy ##import ros
from std_msgs.msg import String #import the ros messages we want to use

class SimpleParticleFilter(object): #classes make things better, promise
    """ This class encompasses the entire node """
    def __init__(self):
        ''' setup ROS stuff '''
        rospy.init_node('message_counter') ## initialize node

        rospy.Subscriber('chatter', String, self.process_chatter) # listen to 'chatter' topic
        self.pub = rospy.Publisher('chatter_count', String, queue_size=10) # publish to 'chatter_count' topic

        ''' initialize variables to use later '''
        self.msg = "no messages yet"
        self.msgs_recieved = 0

    def process_chatter(self, msg):
        """ Runs every time another node publishes to the chatter topic """
        # note, nothing in here is ROS specific, it's just python code that runs when new info appears
        
        print msg.data #print the recieved message

        self.msgs_recieved += 1 #increase msg count
        self.msgs_recieved %= 500 #mod 500 so we don't get enormous numbers
        self.msg = "%d messages recieved" %self.msgs_recieved #set message


    def run(self):
        """ main run loop """
        r = rospy.Rate(2) ## sets rate for the program to run (Hz)
        while not rospy.is_shutdown(): #instead of while true, otherwice crtl+C doesn't work

            self.pub.publish(self.msg) #publish message to 'chatter_count' topic

            r.sleep() ## wait until next time this code should run (according to rospy.Rate above)

if __name__ == '__main__':
    "run above code"
    node = SimpleParticleFilter()
    node.run()