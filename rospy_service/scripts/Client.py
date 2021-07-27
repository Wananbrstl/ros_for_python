#! /usr/bin/env python
#coding :utf-8
from __future__ import print_function
import rospy
import sys
from rospy_service.srv import *

def add_two_ints_client(x,y):
    add_two_ints = rospy.wait_for_service('/service/add_two_ints')
    try:
        add_two_ints = rospy.ServiceProxy('/service/add_two_ints',AddTwoInts)
        resp1 = add_two_ints(x,y)
        return resp1.sum
    except rospy.ServiceException as e :
        print('Service call fail: %s'%e)

def usage():
    return '%s [x ,y]'%sys.argv[0]

if __name__ == '__main__':
    if len(sys.argv) == 3:
        x = int(sys.argv[1])
        y = int(sys.argv[2])
    else:
        print(usage())
        sys.exit(1)
    print('Requesting %s+%s'%(x,y))
    print("%s + %s = %s"%(x, y, add_two_ints_client(x, y)))