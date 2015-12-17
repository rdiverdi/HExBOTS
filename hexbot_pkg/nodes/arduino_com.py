#!/usr/bin/env python
import serial
import time

""" Base structure for communicating with ROS """
""" ## = required for all ros programs, # = specific to this example """

import rospy ##import ros
from std_msgs.msg import String, Int16MultiArray #import the ros messages we want to use

class ComHandler(object): #classes make things better, promise
    """ This class encompasses the entire node """
    def __init__(self):
        ''' setup ROS stuff '''
        rospy.init_node('message_counter') ## initialize node

        rospy.Subscriber('data_array', Int16MultiArray, self.send_data) # listen to 'chatter' topic
        self.pub = rospy.Publisher('errors', String, queue_size=10) # publish to 'chatter_count' topic

        self.ser = serial.Serial('/dev/ttyUSB0')

        while self.ser.inWaiting <= 0:
            time.sleep(1)
        print self.ser.read()

        ''' initialize variables to use later '''
        self.data = [1, 2, 3, 4, 5, 6]
        self.msg = "no coms yet"

    def send_data(self, msg):
        """ Runs every time another node publishes to the chatter topic """
        # note, nothing in here is ROS specific, it's just python code that runs when new info appears
        
        #print msg.data
        self.data = msg.data #print the recieved message
        print self.data
        for num in self.data:
            self.ser.write('a')
            self.ser.write(str(num))
            self.ser.write(',')
        self.ser.write('\n')


    def run(self):
        """ main run loop """
        r = rospy.Rate(2) ## sets rate for the program to run (Hz)
        while not rospy.is_shutdown(): #instead of while true, otherwice crtl+C doesn't work

            response = ''
            if self.ser.inWaiting() > 0:
                response += self.ser.readline()
                if response[0] == '0':
                    #print response
                    self.msg = "no error"
                elif response[0] == '1':
                    print "list length error"
                    self.msg = "list length error"
                else:
                    self.msg = "error"


            self.pub.publish(self.msg) #publish message to 'chatter_count' topic

            r.sleep() ## wait until next time this code should run (according to rospy.Rate above)

if __name__ == '__main__':
    "run above code"
    node = ComHandler()
    node.run()
