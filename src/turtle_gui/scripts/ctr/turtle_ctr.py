#! /usr/bin/env python
# coding: utf-8

from PyQt5.QtWidgets import *

import sys
import rospy
import gui
from gui import hello

if __name__ == '__main__':
        rospy.init_node('turtle_control_node')
        app = QApplication(sys.argv)

        h =hello()
        h.print()

        wind = gui.main_wind()
        wind.show()

        sys.exit(app.exec_())