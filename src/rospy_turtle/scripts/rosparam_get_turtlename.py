#! /usr/bin/env python
#coding: utf-8

import rospy
from turtlesim.msg import *

if __name__ == '__main__':
    rospy.init_node('get_turtlename')
    turtlename = rospy.get_param('~/background_b')
    print(turtlename)
