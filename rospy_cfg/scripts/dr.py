#! /usr/bin/env python3
#coding :utf-8

import rospy
from dynamic_reconfigure.server import Server
from rospy_cfg.cfg import drConfig

def cb(drConfig, level):
    rospy.loginfo("解析的参数: %d",drConfig.int_param)
    rospy.loginfo("解析的参数: %d",drConfig.double_param)
    return drConfig


if __name__ == "__main__":
    rospy.init_node("server")
    server = Server(drConfig, cb )
    rospy.spin()