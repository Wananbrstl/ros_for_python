#! /usr/bin/env python3
import rospy
import actionlib
from rospy_action.msg import *


def done_cb(state,result):
    if state == actionlib.GoalStatus.SUCCEEDED:
        rospy.loginfo("result :%d",result.result)

def active_cb():
    rospy.loginfo("active....")


def fb_cb(fb):
    rospy.loginfo("progress:%.2f",fb.progress_bar)

if __name__ == "__main__":
    rospy.init_node("action_client_p")
    client = actionlib.SimpleActionClient("addInts",addIntsAction)
    client.wait_for_server()
    goal_obj = addIntsGoal()
    goal_obj.num = 10
    client.send_goal(goal_obj,done_cb,active_cb,fb_cb)
    rospy.spin()