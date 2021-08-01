<<<<<<< HEAD
# ROS总结
一些ROS资料:
- [B站赵虚左教程](http://www.autolabor.com.cn/book/ROSTutorials/)
- [ROS-WIKI官方](http://wiki.ros.org/cn/)
- [github](http://github.com)

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
=======
# ROS FOR PYTHON
>>>>>>> 576f30823b80b76f200aba411abc8bab933dc382
