#! /usr/bin/env python
#conding :utf-8

import rospy
from std_msgs.msg import String

def callback(msg):
    rospy.loginfo(msg)

if __name__ == '__main__':
    rospy.init_node('subscriber')
    sub = rospy.Subscriber('/learn_topic/topic',String, callback)
    rospy.spin()
