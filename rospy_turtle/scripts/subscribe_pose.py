#! /usr/bin/env python
#coding: utf-8

import rospy
from turtlesim.msg import *

def callback(msg):
    print('坐标 ({},{})，速度为({})'.format(msg.x,msg.y,msg.linear_velocity))

if __name__ == '__main__':
    rospy.init_node('pose_info')
    sub = rospy.Subscriber('/turtle1/pose',Pose,callback)
    print('现在正在监听turtlesim的位置信号: \n -----------------')
    rospy.spin()