#! /usr/bin/env python
#coding: utf-8

import rospy
import tf
import geometry_msgs.msg

if __name__ == '__main__':
    rospy.init_node('add_a_frame')
    br = tf.TransformBroadcaster()
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        tr = geometry_msgs.msg.TransformStamped()
        tr.header.stamp = rospy.Time.now()
        tr.header.frame_id = 'child'

        tr.child_frame_id = 'turtle1'
        tr.transform.translation.x,tr.transform.translation.y, tr.transform.translation.z = 5,5,0
        tr.transform.rotation.x,tr.transform.rotation.y,tr.transform.rotation.z = 0,0,1
        br.sendTransformMessage(tr)

        rate.sleep()