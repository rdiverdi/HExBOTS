#!/usr/bin/env python

""" Base structure for communicating with ROS """
""" ## = required for all ros programs, # = specific to this example """

import rospy ##import ros
from std_msgs.msg import String #import the ros messages we want to use
# Jayce's Imports
from Walk import *
import math
from numpy import *

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
        
#########################################################
# Stuff that Jayce is editing, and likely fucking up
        
	def push_data(self):
		## This is sudo code right now...
		# We're going to need to import from Walk.py, and then call these specific to the fxn
		# This is a step for each set of legs
		
		# This may or may not make it so the variables defined in this function 
		# (below if __name__) exist. We need the parameters to exist
		locations()
		
		# These are "step functions" that tell the servos where to turn
		# First set is odd down, second set is odd up
		for i in range(0,len(Yrange)):
			# Walk.positions needs an x,y,z coordinate for the foot to be at any time
			# It also needs to know if the foot is not a side foot, and how far off
			# it is (xp,yp), and it needs to know by how much the foot's "zero"
			# is rotated (Rotate1,2,3)
			angles1 = Walk.positions(x,Yrange[i],z,xp,yp,Rotate1)
			angles2 = Walk.positions(xmove[i],ymove[i],zmove[i],0,0,Rotate2)
			angles3 = Walk.positions(x,Yrange[i],z,xp,-yp,Rotate3)
			angles4 = Walk.positions(xmove[i],ymove[i],zmove[i],xp,-yp,Rotate3)
			angles5 = Walk.positions(x,Yrange[i],z,0,0,Rotate2)
			angles6 = Walk.positions(xmove[i],ymove[i],zmove[i],xp,yp,Rotate1)
			
		for i in range(0,len(Yrange)):
			angles6 = Walk.positions(x,Yrange[i],z,xp,yp,Rotate1)
			angles5 = Walk.positions(xmove[i],ymove[i],zmove[i],0,0,Rotate2)
			angles4 = Walk.positions(x,Yrange[i],z,xp,-yp,Rotate3)
			angles3 = Walk.positions(xmove[i],ymove[i],zmove[i],xp,-yp,Rotate3)
			angles2 = Walk.positions(x,Yrange[i],z,0,0,Rotate2)
			angles1 = Walk.positions(xmove[i],ymove[i],zmove[i],xp,yp,Rotate1)
			
#########################################################


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

## This function is here because we need these parameters, I don't know if they will
 # will just pull from Walk.py
def locations():
	# I don't know if I need to return things or if these variables will exist
	# when I call the function
	x = 6;
	z = -3;
	SL = 4;
	xp = math.sin(math.radians(60))*SL;
	yp = math.cos(math.radians(60))*SL;
	Yrange = frange(1.8,-1.8,-(3.6/23))
	Rotate1 = matrix([[math.cos(math.radians(60)),math.sin(math.radians(60)),0],
	[-math.sin(math.radians(60)),math.cos(math.radians(60)),0],[0,0,1]])
	Rotate2 = matrix([[1,0,0],[0,1,0],[0,0,1]])
	Rotate3 = matrix([[math.cos(math.radians(60)),-math.sin(math.radians(60)),0],
	[math.sin(math.radians(60)),math.cos(math.radians(60)),0],[0,0,1]])	

	zlift = halfrange(-3.0,-1.0-(2.0/12.0),2.0/12.0)
	zlower = halfrange(-1.0+(2.0/12.0),-3.0,2.0/12.0)
	zmove = [];
	for zint in range(0,len(zlift)):
		zmove.append(zlift[zint]);
	for zint in range(0,len(zlower)):
		zmove.append(zlower[zint]);
	
	ymove = frange(-1.8,1.8,(3.6/23))

	xlift = halfrange(6.0,4.0+(2.0/12.0),-2.0/12.0)
	xlower = halfrange(4.0+(2.0/12.0),6.0,2.0/12.0)
	xmove = [];
	for xint in range(0,len(xlift)):
		xmove.append(xlift[xint])
	for xint in range(0,len(xlower)):
		xmove.append(xlower[xint]);