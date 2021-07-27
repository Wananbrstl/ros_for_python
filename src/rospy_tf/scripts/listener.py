#! /usr/bin/env python
#coding: utf-8

import rospy
import tf
from geometry_msgs.msg import *
from turtlesim.srv import *
import math
import sys


def callback(msg,turtlename2):
    br = tf.TransformBroadcaster()
    br.sendTransform((msg.x, msg.y, 0),
                    tf.transformations.quaternion_from_euler(0,0,msg.theta),
                    rospy.Time.now(),turtlename2,"world")
    print('done')

if __name__ == "__main__":
    rospy.init_node('listnener')
    
    if len(sys.argv) == 3:
        turtlename1 = sys.argv[1]
        turtlename2 = sys.argv[2]
        print('监听对象{}->{}'.format(turtlename1,turtlename2))
    else:
        print('出错')
    listener = tf.TransformListener()
    rospy.wait_for_service('spawn')
    spawner = rospy.ServiceProxy('spawn',Spawn)
    spawner(4,2,0,turtlename2)

    sub = rospy.Subscriber('/%s/pose'%turtlename2,Pose,callback,turtlename2)


    turtle_vel = rospy.Publisher('/{}/cmd_vel'.format(turtlename2),Twist,queue_size=1)

    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        try:
            (trans,rot) = listener.lookupTransform(turtlename1,turtlename2,rospy.Time(0))
            print(trans)
            print('转换完成')
        except (tf.LookupException,tf.ConnectivityException,tf.ExtrapolationException):
            continue
        
        angular = 4 * math.atan2(trans[1], trans[0])
        linear = 0.5 * math.sqrt(trans[0] ** 2 + trans[1] ** 2)
        cmd = Twist()
        cmd.linear.x = linear
        cmd.angular.z = angular
        turtle_vel.publish(cmd)

        rate.sleep()