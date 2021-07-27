#! /usr/bin/env python
#conding :utf-8

import rospy
from std_msgs.msg import String

if __name__ == '__main__':
    rospy.init_node('publisher')
    pub = rospy.Publisher('/learn_topic/topic',String,queue_size=100)
    rate = rospy.Rate(2)
    while not rospy.is_shutdown():
        hello_string = 'hello world %s'%rospy.get_time()
        rospy.loginfo(hello_string)
        pub.publish(hello_string)
        rate.sleep()

