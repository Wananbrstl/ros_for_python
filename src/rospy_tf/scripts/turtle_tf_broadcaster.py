#! /usr/bin/env python
#coding: utf-8
"""
    
"""
import rospy
import tf
import turtlesim.msg
import sys

def handle_turtle_pose(msg,turtlename):
    br = tf.TransformBroadcaster()
    br.sendTransform((msg.x, msg.y, 0),
                    tf.transformations.quaternion_from_euler(0,0,msg.theta),
                    rospy.Time.now(),turtlename,"world")
    #print('现在的位置是({},{})'.format(msg.x ,msg.y))
    

if __name__ == '__main__':
    rospy.init_node('turtle1')
    if len(sys.argv) == 3:
        turtlename1 = sys.argv[1]
        turtlename2 = sys.argv[2]

        rospy.Subscriber('/%s/pose'%turtlename1,
                        turtlesim.msg.Pose,handle_turtle_pose,
                        turtlename1)
        rospy.Subscriber('/%s/pose'%turtlename2,
                        turtlesim.msg.Pose,handle_turtle_pose,
                        turtlename2)
        print('成功获取参数')
    else:
        print('坐标转换失败')
    rospy.spin()
