#! /usr/bin/env python3
# coding: utf-8
import rospy
import tf
import tf2_ros 
from geometry_msgs.msg import TransformStamped

if __name__ == "__main__":
    rospy.init_node("caster")
    pub = tf2_ros.StaticTransformBroadcaster()
    trans = TransformStamped()
    trans.child_frame_id = "child_link"
    trans.header.frame_id = "parent_link"
    trans.header.seq = 100
    trans.header.stamp = rospy.Time(0)
    trans.transform.translation.x = 10
    trans.transform.translation.y = 20
    trans.transform.translation.z = 30
    trans.transform.rotation.x = 1
    trans.transform.rotation.y = 2
    trans.transform.rotation.z = 3
    pub.sendTransform(trans)
    rospy.spin()