#! /usr/bin/env python
#coding: utf-8

import rospy
import tf
import geometry_msgs.msg
import turtlesim.msg
import turtlesim.srv
import sys
import math

if __name__ == '__main__':
    rospy.init_node('follow')
    if len(sys.argv) == 3:
        turtlename1 = sys.argv[1]
        turtlename2 = sys.argv[2]
    else:
        print('参数输入错误')
        raise('参数输入错误')
    #publisher类 发送/turtle/cmd_vel信息
    pub = rospy.Publisher('{}/cmd_vel'.format(turtlename1),geometry_msgs.msg.Twist,queue_size=1)
    listener = tf.TransformListener()
    while not rospy.is_shutdown():
        cmd = geometry_msgs.msg.Twist()
        try:
            (trans,rot) = listener.lookupTransform(turtlename1, turtlename2, rospy.Time(0))
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue
        angular = 4 * math.atan2(trans[1], trans[0])
        linear = 2 * math.sqrt(trans[0] ** 2 + trans[1] ** 2)
        cmd.linear.x = linear
        cmd.angular.z = angular
        pub.publish(cmd)
    rospy.spin()