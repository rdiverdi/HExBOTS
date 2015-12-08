#!/usr/bin/env python

import rospy ##import ros
from std_msgs.msg import String, Int16MultiArray #import the ros messages we want to use
from math import *

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d
from matplotlib import cm


class Arrow3D(FancyArrowPatch):
    """ This class deals with the arrow pointing forward """
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)

class Plot():
    """ this class handles the actual plot """
    def __init__(self, body_r, elevation, azim):
        self.ground = -3.9

        fig = plt.figure()
        self.ax = fig.add_subplot(111, projection='3d')

        self.body_r = body_r

        theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
        self.z = [0]*len(theta)
        self.x = self.body_r * np.sin(theta)
        self.y = self.body_r * np.cos(theta)
        self.ax.plot(self.x, self.y, self.z, label='MainBody')
        self.plot_base()

        self.ax.view_init(elev=elevation, azim=azim)

        plt.ion()
        plt.show()

    def plot_base(self):
        self.ax.set_xlim3d(-10, 10)
        self.ax.set_ylim3d(-10, 10)
        self.ax.set_zlim3d(-5, 5)
        self.ax.plot(self.x, self.y, self.z, label='MainBody')
        a = Arrow3D([0, 5], [0, 0], [0, 0], mutation_scale=20, lw=3, arrowstyle="-|>", color="g")
        self.ax.add_artist(a)


    def get_end_pos(self, t1, t2, t3, leg):
        L0 = 1
        L1 = 4
        L2 = 5
        start_t = leg * pi/3 - pi/6
        start_pos = [self.body_r*cos(start_t), self.body_r*sin(start_t)]

        theta = t1*pi/180+start_t
        S1_pos = [start_pos[0]+L0*cos(theta), start_pos[1]+L0*sin(theta)]
        r = sqrt(L1**2 + L2**2 - 2*L1*L2*cos(t3*pi/180))
        phi = (90-t2)*pi/180+asin(L2*sin(t3*pi/180)/r)

        x = r*cos(theta)*sin(phi)+S1_pos[0]
        y = r*sin(theta)*sin(phi)+S1_pos[1]
        z = r*cos(phi)

        return [start_pos + [0], [x, y, z]]

    def update_plot(self, array):
        plt.cla()
        self.plot_base()
        for i in range(6):
            servos = array[3*i : 3*i+3]
            line = self.get_end_pos(servos[0], servos[1], servos[2], i+1)
            line_xyz = [[line[end][var] for end in range(len(line))] for var in range(3)]
            if line[1][2] > self.ground:
                self.ax.plot(line_xyz[0], line_xyz[1], line_xyz[2], '-k', label='leg%d' %(i+1))
            elif line[1][2] > self.ground-.25:
                self.ax.plot(line_xyz[0], line_xyz[1], line_xyz[2], '-g', label='leg%d' %(i+1))
            else:
                self.ax.plot(line_xyz[0], line_xyz[1], line_xyz[2], '-r', label='leg%d' %(i+1))

        plt.draw()

class SimHexbot(object): #classes make things better, promise
    """ This class encompasses the entire node """
    def __init__(self):
        ''' setup ROS stuff '''
        rospy.init_node('hexbot_sim') ## initialize node

        rospy.Subscriber('data_array', Int16MultiArray, self.process_array) # listen to 'chatter' topic
        self.error_pub = rospy.Publisher('errors', String, queue_size=10) # publish to 'errors' topic

        ''' initialize variables to use later '''

        height = rospy.get_param('~height', 90)
        spin = rospy.get_param('~spin', 180)

        self.msg = "nothing yet"

        self.body_r = 3

        self.servo_array=[0, 20, 90, 0, 40, 120]*3

        self.plot = Plot(self.body_r, height, spin)

    def process_chatter(self, msg):
        """ Runs every time another node publishes to the chatter topic """
        # note, nothing in here is ROS specific, it's just python code that runs when new info appears
        
        self.msg = msg.data

    def process_array(self, msg):
        if len(msg.data) == 18:
            self.servo_array = msg.data
        else:
            self.error_pub.publish("bad array input")


    def run(self):
        """ main run loop """
        r = rospy.Rate(15) ## sets rate for the program to run (Hz)
        while not rospy.is_shutdown(): #instead of while true, otherwice crtl+C doesn't work

            self.plot.update_plot(self.servo_array)

            r.sleep() ## wait until next time this code should run (according to rospy.Rate above)

if __name__ == '__main__':
    "run above code"
    node = SimHexbot()
    node.run()