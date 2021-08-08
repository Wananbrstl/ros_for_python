#! /usr/bin/env python3
# coding: utf-8
#
import rospy
import actionlib
from rospy_action.msg import *

def action_cb():
    rospy.loginfo("连接已经建立....")


def done(state, result):
    if state == actionlib.GoalStatus.SUCCEEDED:
        rospy.loginfo("成功完成!结果为: {}".format(result))
    else: 
        rospy.logerr("失败.....")

def feed(feedback):
    print("当前进度: %.2f", feedback.propress_bar)

if __name__ == "__main__":
    # 这个是普通的命名方式
    # 其他还有全局和局部
    rospy.init_node("client")
    clinet = actionlib.SimpleActionClient("addInts", addIntsAction)
    
    # 等待响应
    clinet.wait_for_server()
    # 发送求解
    # def send_goal(self, goal, done_cb=None, active_cb=None, feedback_cb=None
    goal = addIntsGoal()
    goal.num = 100
    clinet.send_goal(goal, done_cb= done, active_cb = action_cb, feedback_cb = feed )
    rospy.spin()
