#! /usr/bin/env python
#coding: utf-8

import rospy

if __name__ == "__main__":
    rospy.init_node('hello')    
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        print('hello rospy')
        rate.sleep()
