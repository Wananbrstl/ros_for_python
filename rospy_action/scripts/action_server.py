#! /usr/bin/env python3
# coding: utf-8

import rospy
import actionlib
from rospy_action.msg import *

class MyAction():
    
    def __init__(self):
        self.server = actionlib.SimpleActionServer("addInts", addIntsAction,self.cb, auto_start= False )
        self.server.start()
        rospy.loginfo("服务端启动....")


    # 处理请求，回调函数的任务
    # a. 解析目标值 
    # b. 发送连续反馈
    # c. 相应最终的结果
    def cb(self,goal):
        goal_num = goal.num
        rospy.loginfo("目标数值: %d",goal.num)
        rate = rospy.Rate(10)
        # 接收求和的结果变量
        sum = 0
        # 循环操作
        rospy.loginfo("请求处理中....")
        for i in range(1,goal_num+1) :
            sum += i
            rate.sleep()
            # 发送连续反馈
            fb_obj = addIntsFeedback()
            fb_obj.propress_bar = i / goal_num
            self.server.publish_feedback(fb_obj)
        result = addIntsResult()
        result.result = sum
        self.server.set_succeeded(result)
        rospy.loginfo("结果为: {}".format(sum))

if __name__ == "__main__":
    rospy.init_node("addInts_server")
    action = MyAction()