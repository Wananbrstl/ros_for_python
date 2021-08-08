# URDF and Xacro
一些ROS资料:
- [B站赵虚左教程](http://www.autolabor.com.cn/book/ROSTutorials/)
- [ROS教学文档](http://www.autolabor.com.cn/book/ROSTutorials/di-7-zhang-ji-qi-ren-dao-822a28-fang-771f29/103-nodelet/1031-shi-yong-yan-shi.html)
- [ROS-WIKI官方](http://wiki.ros.org/cn/)
- [github](http://github.com)
- [github简单教学](https://www.cnblogs.com/future-dream/p/11979399.html)
- [github一些操作](https://www.cnblogs.com/ydxblog/p/7988317.html)

目录
---

[toc]
## About URDF
> urdf是universal robot description file的简写，它可以用于描述很多机器人的本体机构，比如：机械臂、移动小车、串联四足机器人等等模型。一般来说，ROS官方支持的是sdf，此时就需要将urdf格式转化为sdf格式。
> ROS官方URDF资料[ROS-URDF](http://wiki.ros.org/cn/urdf)。
### URDF standard file format 
This is a standard urdf file:
```
<？xml version = "1.0"？>
<robot name = "ROBOT_NAME">
    <link name = "LINK_NAME">
        <!-- the visualization configure -->
        <It concludes three child tag: geometry, >
        <!-- 连杆的第一个子标签是：可视化 -->
        <visual>
            <!-- 可视化的第一个标签是形状 -->
            <geometry>
                <!--the first geomtrty: cylinder -->
                <cyliner radius = "RADIUS" length = "LENGTH" />
                <!-- the second geomtetry: sphere-->
                <sphere radius = "RADIUS" />
                <!-- the third geometry: box-->
                <box size = "LENGTH WIDTH HEIGHT" />
                <!-- alse you can use a mesh file to display -->
                <mesh filename = "资源路径(格式格式:package://<packagename>/<path>/文件)">
            </geometry>
            <！-- 第二个可视化标签是偏移origin -->
            <origin xyz = "X Y Z" rpy = "r p y" />
            <!-- 第三个标签是材料，用于设置颜色-->
            <material name = ""> 
                <color rgba = "R G B 透明度" />
            </material>
        </visual>
        <!-- 连杆的第二个标签是碰撞属性(Gazebo仿真中，必须有这个属性) -->
        <collision>
            <>
        </collision>
        <!-- 连杆的第三个标签是惯性Inertial-->
        <inertial>
            <>
        </inertial>
    </link>

    <!--robot另外一个重要的标签是joint>
    <joint name = "JOINT_NAME type = "TYPE">
    <!--JOINT的类型TYPE有六种：
    1. continuous: 旋转关节， 可以围绕单个轴无限制旋转
    2. reolute： 旋转关节， 类似与continuous， 但是它有角度限制
    3. prismatic： 滑动关节， 沿着一个轴进行滑动， 有位置极限
    4. planar： 平面关节， 允许在平面正交方向上平移或者旋转
    5. floating： 浮动关节， 允许进行平移， 旋转运动
    6. fixed： 固定关节， 不允许有运动
    常用为continuous， revolute， fixed(坐标转换)
    -->
        <!-- 第一个关节子标签为： 父连杆 -->
        <parent link = "PARENT_LINK" />
        <!-- 第二个关节子标签为： 子连杆 -->
        <child link = "CHILD_LINK">
        <!-- 第三个关节子标签为： 偏移量-->
        <origin xyz = "" rpy = "" />
        <!-- 其他标签： 类如axis等-->
        <axis xyz = "X Y Z" />
    </joint>
</robot>
```
### URDF tools

## About XACRO
> 由于urdf中存在很多问题，所以xacro格式诞生用于优化urdf。在urdf中，会出现很多重复,代码重复，且人工计算参数，不方便，且容易出现错误。 Xacro也是一种XML语言，可以声明变量，数学求解和函数宏块来解决这些问题。
### 使用方法
在开始Xacro之前，需要指定一个命名空间，使得系统能够解析Xarco语言，下面是一个实例:
```
<?xml version = "1.0"?>
<robot xmlns = "http://www.ros.org/wiki/xacro" name = "mobile" >
...
</robot>
```
此外，文件的后缀名应该是<u>.xacro</u>
#### 1.常量
**声明**： 我们使用Xacro声明常量，需要声明name及value，比如:
```
<xacro:property name = "length_wheel" value = "0.05" \>
<xacro:pr使用operty name = "radius_wheel" value = "0.05" \>
```
**使用**： 使用`${nameOfValue}`代码块，例子：
```
<cylinder radius = ${RADIUS} length = ${LEGNTH} />
```

#### 2.数学运算
**使用方法**:可以在${}中使用基本的四则运算(+), (-), (*), (/)，不支持求幂和取模等操作，例子:
```
<cylinder radius = "${wheel_heigh/2}" length = "1.0" />
```

#### 3.宏
宏是Xacro功能中最重要的组件，在3D机器人模型中的，可以通过下面这段代码减少对inertial的初始化：
**声明格式**
```
<xacro:macro name = "宏名称" params = "参数列表(多参数之间使用空格分割开)">
    ...
    参数列表调用格式: ${参数名}
</xacro:macro>
```

**声明例子**
```
<xacro:macro name = "default_inertial" param = "mass">
    <inertial>
        <mass value = "${mass}" />
        <inertial ixx = "1.0" iyy = "1.0" izz = "1.0" 
        ixy = "0.0" ixz = "0.0" 
        iyx = "0.0" iyz = "0.0"
        izx = "0.0" izy = "0.0"
        />
    </inertial>
</xacro>
```
***使用模板 ***
```
<xacro:宏名称 参数1 = xxx 参数2  = xxx/>
```
**使用例子**
```
<xacro:default_inertial mass = "0.05" />
```
**文件包含**
Xacro中是可以进行文件包含的，其使用的语法为:
```
<xacro:include filename = "xxx.xacro"/>
```
一个例子:
```
<robot name = "xxx" xmlns:xacro = "http://wiki.ros.org/xacro">
    <xacro:include filename = "my_base.xacro">
    <xacro:include filename = "my_camera.xacro">
    <xacro:include filename = "my_laser.xacro">
</robot>
```
### Xacro转换成URDF
通过`rosrun xacro xacro xxx.xacro`
- 应当在xacro文件下面进行操作
-  `rosrun xacro xacro xxx.xacro > xxx.urdf`

### Arbotix使用
**1.安装 Arbotix**
源码编译: `git clone http://github.com/vanadiumlabs/arbotix_ros.git`
**2.创建新功能包，准备机器人 urdf、xacro**
在这步中，创建你的机器人urdf或xacro模型文件
**3.添加 arbotix 所需的配置文件**
```
# 该文件是控制器配置,一个机器人模型可能有多个控制器，比如: 底盘、机械臂、夹持器(机械手)....
# 因此，根 name 是 controller
controllers: {
   # 单控制器设置
   base_controller: {
          #类型: 差速控制器
       type: diff_controller,
       #参考坐标
       base_frame_id: base_footprint, 
       #两个轮子之间的间距
       base_width: 0.2,
       #控制频率
       ticks_meter: 2000, 
       #PID控制参数，使机器人车轮快速达到预期速度
       Kp: 12, 
       Kd: 12, 
       Ki: 0, 
       Ko: 50, 
       #加速限制
       accel_limit: 1.0 
    }
}

```
其他的可以参考<http://wiki.ros.org/arbotix_python/diff_controller>
**4.launch 文件中配置 arbotix 节点**
```
<node name="arbotix" pkg="arbotix_python" type="arbotix_driver" output="screen">
     <rosparam file="$(find my_urdf05_rviz)/config/hello.yaml" command="load" />
     <param name="sim" value="true" />
</node>
```
代码解释:
`<node>` 调用了 arbotix_python 功能包下的 arbotix_driver 节点
`<rosparam>` arbotix 驱动机器人运行时，需要获取机器人信息，可以通过 file 加载配置文件
`<param>` 在仿真环境下，需要配置 sim 为 true
**5.启动 launch 文件并控制机器人模型运动**

# 机器人仿真
## Gazebo仿真使用
URDF与Gazebo的集成流程与Rviz相似，都有以下几步：
- 创建功能包， 导入依赖环境
- 编写URDF或者Xacro文件
- 启动Gazebo并显示机器人模型(主要在人roslaunch中体现)
### 步骤1： 创建功能包
- `cd (catkin_worksapce)/src`
- `catkin_create_pkg 功能包名字 依赖`
- `mkdir urdf xacro launch`
- 写入urdf、xacro文件
###  步骤二： 集成launch文件，启动Gazebo
###  步骤三： 将参数服务器中的urdf文件导入gazebo中仿真
具体的launch文件:
```
<?xml version = "1.0"?>
<launch>
    <!--步骤一  导入urdf-->
    <param name = "robot_description" textfile = "$(your worksapce)/urdf/xx.urdf" />
    <!--或者导入xacro-->
    <!--方式一： 在launch文件中进行导入-->
    <param name = "robot_description  command = "$(find xacro)/xacro  $(find your_workspace)/xacro/xx.xacro" />
    <!-- 方式二： 在终端输入rosrun xcaro xacro xx.xacro > xx.urdf然后按照urdf的方式导入 -->
    <-- 步骤二  启动GAZEBO -->
    <include file = "$(find gazebo_ros)/launch/empty_world.launch"/>
    <!-- 步骤三  在GAZEBO中加载参数服务器中的robot -->
    <node pkg = "gazebo_ros" name = "spawn_model" type = "spawn_model" args = "-urdf -model name -param robot_description" />
</launch>
```

## ros_control
### ros_control简介
> ros_control:是一组软件包，它包含了控制器接口，控制器管理器，传输和硬件接口。ros_control 是一套机器人控制的中间件，是一套规范，不同的机器人平台只要按照这套规范实现，那么就可以保证 与ROS 程序兼容，通过这套规范，实现了一种可插拔的架构设计，大大提高了程序设计的效率与灵活性。
gazebo 已经实现了 ros_control 的相关接口，如果需要在 gazebo 中控制机器人运动，直接调用相关接口即可
### 运动基本流程
- 创建一个



# ROS进阶
## 一. Action通讯
关于action通信，我们先从之前导航中的应用场景开始介绍，描述如下:
> 机器人导航到某个目标点,此过程需要一个节点A发布目标信息，然后一个节点B接收到请求并控制移动，最终响应目标达成状态信息。

乍一看，这好像是服务通信实现，因为需求中要A发送目标，B执行并返回结果，这是一个典型的基于请求响应的应答模式，不过，如果只是使用基本的服务通信实现，存在一个问题：导航是一个过程，是耗时操作，如果使用服务通信，那么只有在导航结束时，才会产生响应结果，而在导航过程中，节点A是不会获取到任何反馈的，从而可能出现程序"假死"的现象，过程的不可控意味着不良的用户体验，以及逻辑处理的缺陷(比如:导航中止的需求无法实现)。更合理的方案应该是:导航过程中，可以连续反馈当前机器人状态信息，当导航终止时，再返回最终的执行结果。在ROS中，该实现策略称之为:action 通信。
简单来说，如果一个任务是基于"请求-相应"的，并且是一个耗时操作，可以考虑使用Action通讯。

一些概念:
- goal :目标任务
- cancel： 取消任务(很多应用场景下，任务并不是一下就完成了，而是一个连续的过程，这期间就需要不断反馈给我们信息，这时候也有可能需要取消任务来优化体验)
- status： 服务器的状态
- result： 最终执行的结果(只会发布一次)
- feedback: 连续反馈(可以发布多次)
### 1. 定义action信息
首先导入功能包，带入依赖`roscpp rospy std_msgs actionlib action_msgs`
然后功能包下创建action目录，新增一个xx.action文件.
action文件内容一般分为三个部分：
```
# goal 
int32 num
---
# result
int32 result
---
# feedback
float64 progress_bar
```

## 2. Server 
- 创建一个服务:`server = actionlib.SimpleActionServer(name, ActionSpec, execute_cb=None, auto_start=True)`
- 创建一个服务:`server = actionlib.SimpleActionServer(name, ActionSpec, execute_cb=None, auto_start=True)`
- 假如`auto_start = False`,手动开启服务器: `server.start()`
- 编写回调函数`def execute_cb(goal)`

###  3. Client
- 创建一个客户端: `client = actionlib.SimpleActionClient(ns, ActionSpec)`
- 等待服务器`client.wait_for_server()`
- 发送请求`client.send_goal(goal, done_cb = ,feedback_cb = ,active_cb = )`
- 创建激活/反馈/完成的回调函数,
    - 对于激活回调函数: 没有参数
    - 对于反馈回调函数: 反馈的信息
    - 对于完成回调函数: 处理的结果状态(bool),结果(result)
## 二. 动态参数
### 动态参数客户端
需求:
> 编写两个节点，一个节点可以动态修改参数，另一个节点时时解析修改后的数据。多用于需要动态修改参数的情况，典型应用： 导航时参数的动态调节.
客户端实现流程:
* 新建并编辑 .cfg 文件;
* 编辑CMakeLists.txt;
* 编译。
**一个案例**
动态修改参数，服务端可以解析参数


## Pluginlib
### 应用场景
通过规范化的USB接口协议实现计算机与USB接口协议， 最大程度上实现规范。
在ROS中使用插件的场景:
> 1. 导航插件，在导航中涉及到路径规划、轨迹规划等多中算法，可以自主实现，导航应用中，可能需要测试不同算法的优劣从而选择合适的实现。在这种情况下，ROS通过插件灵活地切换不同的算法。
> 2. Rviz插件，在rviz中已经提供了丰富的功能实现，但是即使如此，特定场景下，开发者可能需要实现某些定制化功能，这一集成也是插件。
**概念**
Plugin是一个c++库，用来从一个ROS功能包中加载和卸载(plug)。插件是指从运行库中动态加载的类。通过使用Pluginlib，不必将某个应用程序显示地链接到包含的库，而不是需要应用程序事先知道包含类定义的库或者头文件。
**作用**
- 结构清晰
- 低耦合，修改简单，可维护性强
- 可移植性能强，具有复用性
- 结构容易调整，插件可以自由增减
**需求**
以插件的形式实现正多边形的相关计算
- 实现的流程
    - 准备工作
    
## nodelet
ROS通讯是基于NODE届节点，可以满足大多数场景，由于一个Node启动之后独占一根进程，不同NOde之间通讯交互是基于不同进程之间的数据传输的，当传输类似图片，点云等大容量数据时，会出现延时等现象。比如：

> 编写一个相机驱动，A发送原始数据，B接受数据并进行人脸标定，如果采用原始的传输方式，那么会导致延迟。

ROS给出的解决方式是Nodelet，通过Nodelet可以将多个节点集成进一个进程当中。这样免除了数据传输的过程，将不同进程集成一个进程，可以共享一个内容。类似于值传递和地址传递。

**作用**：避免延时和阻塞等情况
### 使用流程
> tip:这里可以将nodelet看成一个项目，由于两个同事工作的时候需要数据交互，然而他们的数据非常多，这个时候可以将他们安排进同一个办公室。这个时候需要一个项目经理来管理他们，对应的是`rosrun nodelet nodelet manager __name:=经理名称`来创建一个经历来管理他们，还需要往这个办公室里面添加员工，对应的操作是：`rosrun ndoelet nodelet load pkg/Type(员工) __name:=manager(管理他们的经理)`。

### 自定义的nodelet实现
步骤：

- 1. 创建插件类注册插件 
- 2. 构建插件库
- 3. 使用插件可用于ROS工具链
- 4. 执行



# MoveIt!让机械臂动起来
**用户接口**：
- C++: 使用move_group_interface包提供的API
- python: 使用moveit_commander包提供的API
- GUI: 使用MoveIt的Rviz插件

**ROS参数服务器**：
- URDF: robot_description参数，用于获取URDF模型的描述信息
- SRDF: robot_description_semantic参数，用于获取机器人的配置信息
- configure: 机器人的其他配置信息，例如关节限制，运动学插件，运动规划插件等。

**机器人**：
- 采用Action和topic的通讯机制
## MoveIt!系统构架

## 创建机械臂模型

## MoveIt!编成
