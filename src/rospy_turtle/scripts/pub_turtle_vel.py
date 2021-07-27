#! /usr/bin/env python
#coding: utf-8

import rospy
from turtlesim.msg import *
import sys
from geometry_msgs.msg import *

if __name__ == '__main__':
    rospy.init_node('pub_vel_cmd')
    pub = rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=100)
    if len(sys.argv) == 4:
        vel_cmd = Twist()
        vel_cmd.linear.x = float(sys.argv[1])
        vel_cmd.linear.y = float(sys.argv[2])
        vel_cmd.linear.z = 0

        vel_cmd.angular.x = 0
        vel_cmd.angular.y = 0
        vel_cmd.angular.z = float(sys.argv[3])
        print('----------------\n数据收集成功\n--------------\n')
    else:
        print('--------\nsomething gets wrong\n-------------')
        
    while not rospy.is_shutdown():
        pub.publish(vel_cmd)
    
    rospy.spin()
    #print('发送成功\n--------------\n线速度为({},{},{}),角速度为({},{},{})')