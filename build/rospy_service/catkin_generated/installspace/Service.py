#!/usr/bin/env python3
#coding :utf-8
from __future__ import print_function
import rospy
from rospy_service.srv import AddTwoInts,AddTwoIntsResponse

def callback(req):
    print('Reuturn [ {} + {} = {} ]'.format(req.a,req.b,(req.a+req.b)))
    return AddTwoIntsResponse(req.a+req.b)

if __name__ == '__main__':
    rospy.init_node('service_publisher')
    service = rospy.Service('/service/add_two_ints',AddTwoInts, callback)
    print('ready to add two ints')
    rospy.spin()