#！/usr/bin python3
#coding: utf-8
"""
小乌龟调试GUI程序
启动: python gui.py
创建时间: 2021.7.20
创建人: wananbrstl
"""
import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import rospy
from std_srvs.srv import Empty,EmptyRequest,EmptyResponse
from turtlesim.srv import Spawn, SpawnResponse, SpawnRequest
from turtlesim.srv import Kill,KillRequest,KillResponse
from turtlesim.srv import SetPen,SetPenRequest
from turtlesim.srv import TeleportAbsolute,TeleportAbsoluteRequest
from turtlesim.srv import TeleportRelative,TeleportRelativeRequest
from turtlesim.msg import Pose
import matplotlib.pyplot as plt

class main_wind(QWidget):
        def __init__(self):
                self.x = [0]
                self.y = [0]
                super(main_wind, self).__init__()
                self.__create_gui()
                self.create_controllor()
                self.guiji()

        def __create_gui(self):
                self.layout = QVBoxLayout(self)
                self.setWindowTitle('turtle controller')
                self.resize(600,0)
                self.move(500,600)
                self.setFont(QFont('times', 15))

                # clear
                self.clear_btn = QPushButton('clear')
                self.layout.addWidget(self.clear_btn)

        #         reset
                self.reset_btn = QPushButton('Reset')
                self.layout.addWidget(self.reset_btn)

        #           create turtle
                self.create_turtle_layout = QHBoxLayout()
                self.layout.addLayout(self.create_turtle_layout)
                self.turtle_name = QLineEdit()
                self.turtle_x = QLineEdit()
                self.turtle_y = QLineEdit()
                self.turtle_angle = QLineEdit()
                self.create_turtle_btn = QPushButton('Create')

                self.create_turtle_layout.addWidget(self.turtle_name)
                self.create_turtle_layout.addWidget(self.turtle_x)
                self.create_turtle_layout.addWidget(self.turtle_y)
                self.create_turtle_layout.addWidget(self.turtle_angle)
                self.create_turtle_layout.addWidget(self.create_turtle_btn)

                self.turtle_name.setPlaceholderText('Name')
                self.turtle_x.setPlaceholderText('x position')
                self.turtle_y.setPlaceholderText('y position')
                self.turtle_angle.setPlaceholderText('angle')

        #         kill turtle
                self.kill_turtle_name = QLineEdit()
                self.kill_btn = QPushButton('Kill')
                self.kill_layout = QHBoxLayout()

                self.layout.addLayout(self.kill_layout)
                self.kill_layout.addWidget(self.kill_turtle_name)
                self.kill_layout.addWidget(self.kill_btn)

                self.kill_turtle_name.setPlaceholderText('kill turtle name')

        #         set the pen
                self.pen_name = QLineEdit()
                self.rgb_r = QLineEdit()
                self.rgb_g = QLineEdit()
                self.rgb_b = QLineEdit()
                self.pen_width = QLineEdit()
                self.off_radio = QCheckBox('close')
                self.set_pen_btn = QPushButton('Set')

                self.pen_layout = QHBoxLayout()
                self.layout.addLayout(self.pen_layout)
                self.pen_layout.addWidget(self.pen_name)
                self.pen_layout.addWidget(self.rgb_r)
                self.pen_layout.addWidget(self.rgb_g)
                self.pen_layout.addWidget(self.rgb_b)
                self.pen_layout.addWidget(self.pen_width)
                self.pen_layout.addWidget(self.off_radio)
                self.pen_layout.addWidget(self.set_pen_btn)

                self.pen_name.setPlaceholderText('Name')
                self.rgb_r.setPlaceholderText('R')
                self.rgb_g .setPlaceholderText('G')
                self.rgb_b .setPlaceholderText('B')
                self.pen_width.setPlaceholderText('Width')

        #       absolute
                self.relative_turtle = QHBoxLayout()
                self.layout.addLayout(self.relative_turtle)
                self.absolute_turtle_name = QLineEdit()
                self.absolute_turtle_x = QLineEdit()
                self.absolute_turtle_y = QLineEdit()
                self.absolute_turtle_angle = QLineEdit()
                self.absolute_btn = QPushButton('Set')

                self.relative_turtle.addWidget(self.absolute_turtle_name)
                self.relative_turtle.addWidget(self.absolute_turtle_x)
                self.relative_turtle.addWidget(self.absolute_turtle_y)
                self.relative_turtle.addWidget(self.absolute_turtle_angle)
                self.relative_turtle.addWidget(self.absolute_btn)

                self.absolute_turtle_name.setPlaceholderText('Name')
                self.absolute_turtle_x.setPlaceholderText('x position')
                self.absolute_turtle_y.setPlaceholderText('y position')
                self.absolute_turtle_angle.setPlaceholderText('angle')

        #        ralative position

                self.ralative_layout = QHBoxLayout()
                self.layout.addLayout(self.ralative_layout)
                self.ralative_turtle_name = QLineEdit()
                self.ralative_turtle_x = QLineEdit()
                self.ralative_turtle_y = QLineEdit()
                self.ralative_btn = QPushButton('Set')

                self.ralative_layout.addWidget(self.ralative_turtle_name)
                self.ralative_layout.addWidget(self.ralative_turtle_x)
                self.ralative_layout.addWidget(self.ralative_turtle_y)
                self.ralative_layout.addWidget(self.ralative_btn)

                self.ralative_turtle_name.setPlaceholderText('Name')
                self.ralative_turtle_x.setPlaceholderText('linear velocity')
                self.ralative_turtle_y.setPlaceholderText('angle volocity')
                
        #create controllor to GUI
        def create_controllor(self):
                self.clear_btn.clicked.connect(self.clear)
                self.reset_btn.clicked.connect(self.reset)
                self.create_turtle_btn.clicked.connect(self.create_turtle)
                self.kill_btn.clicked.connect(self.kill_turtle)
                self.set_pen_btn.clicked.connect(self.set_pen)
                self.absolute_btn.clicked.connect(self.set_pose)
                self.ralative_btn.clicked.connect(self.relative_pose)

######################################################
        def clear(self):
                client = rospy.ServiceProxy('/clear',Empty)
                client.wait_for_service()
                client.call(EmptyRequest())
                client.close()

        def reset(self):
                client = rospy.ServiceProxy('/reset',Empty)
                client.wait_for_service()
                client.call(EmptyRequest())
                client.close()

        def create_turtle(self):
                print('开始创建一个小乌龟\n-------------\n')
                print('名字： {}\n位置: ({}, {}) 朝向: {} rad'.format(self.turtle_name.text(),self.turtle_x.text(),self.turtle_y.text(),self.turtle_angle.text()))
                client = rospy.ServiceProxy('/spawn',Spawn)
                client.wait_for_service()
                req = SpawnRequest()
                x = float(self.turtle_x.text())
                y = float(self.turtle_x.text())
                name = str(self.turtle_name.text())
                theta = float(self.turtle_angle.text())

                req.x ,req.y, req.theta, req.name = x,y,theta,name
                client.call(req)
                client.close()
        
        def kill_turtle(self):
                kill_turtle_name = self.kill_turtle_name.text()
                client = rospy.ServiceProxy('/kill',Kill)
                client.wait_for_service()
                req = KillRequest()
                req.name = kill_turtle_name
                client.call(req)
                client.close()
                print('已经杀死{}'.format(kill_turtle_name))

        def set_pen(self):
                set_pen_turtlename = self.pen_name.text()
                set_pen_client = rospy.ServiceProxy('{}/set_pen'.format(set_pen_turtlename),SetPen)
                set_pen_client.wait_for_service()
                req = SetPenRequest()
                if self.off_radio.isChecked() == True:
                        #True 则不显示
                        print('关闭画笔')
                        req.off = 1
                else:
                        print('打开画笔')
                        (req.r, req.g, req.b) = int(self.rgb_r.text()), int(self.rgb_g.text()), int(self.rgb_b.text())
                        req.width = int(self.pen_width.text())
                set_pen_client.call(req)
                set_pen_client.close()

        def set_pose(self):
                if self.absolute_turtle_name.text() == '':
                        print('空名字，请修改')
                        raise ValueError('name必须有值')
                absolute_turtlenam = self.absolute_turtle_name.text()
                client = rospy.ServiceProxy('{}/teleport_absolute'.format(absolute_turtlenam),TeleportAbsolute)
                client.wait_for_service()
                req = TeleportAbsoluteRequest()
                req.x = float(self.absolute_turtle_x.text())
                req.y = float(self.absolute_turtle_y.text())
                req.theta = float(self.absolute_turtle_angle.text())
                client.call(req)
                client.close()
        
        def relative_pose(self):
                turtlenam = self.ralative_turtle_name.text()
                if turtlenam == '':
                        raise ValueError('必须有name')
                client = rospy.ServiceProxy('{}/teleport_relative'.format(turtlenam),TeleportRelative)
                client.wait_for_service()
                req = TeleportRelativeRequest()
                req.linear = float(self.ralative_turtle_x.text())
                req.angular = float(self.ralative_turtle_y.text())                
                client.call(req)
                client .close()
                print('---------\n相对线速度:  {}\n角速度: {}\n---------'.format(self.ralative_turtle_x.text(),self.ralative_turtle_y.text()))

        def guiji(self):
                sub = rospy.Subscriber('turtle1/pose',Pose,self.callback)
                rospy.spin()

        def callback(self,msg):
                self.x += msg.x
                self.y += msg.y

                #print('position: ({},{})'.format(x,y))

########################################################

if __name__ == '__main__':
        rospy.init_node('turtle_control_node')
        app = QApplication(sys.argv)
        wind = main_wind()
        wind.show()

        sys.exit(app.exec_())






