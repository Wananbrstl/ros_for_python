#include"ros/ros.h"
#include"geometry_msgs/TransformStamped.h"
#include"tf2_ros/buffer.h"
#include"tf2_ros/transform_listener.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"
#include"turtlesim/Spawn.h"
#include"geometry_msgs/Twist.h"
#include <cmath>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtles");
    ros::NodeHandle n;
    // 监听 两个海龟 的坐标变化, 然后发布 vel_cmd消息
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",100);
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener lis(buffer);
    ros::Rate r(10);
    while (ros::ok())
    {
        try
        {
            geometry_msgs::TransformStamped trans;
            trans = buffer.lookupTransform("turtle2", "turtle1", ros::Time(0));
            double x = trans.transform.translation.x;
            double y = trans.transform.translation.y;
            // 打印信息
            ROS_INFO("d_x = %.2f, d_y = %.2f ", x, y);
            // 计算vel_cmd信息
            geometry_msgs::Twist twist;
            double turtle_angle = tan(y/x); 
            twist.angular.z = turtle_angle;
            twist.linear.x = x;
            // 发布完成
            pub.publish(twist);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        r.sleep();
    }
    r.sleep();
    return 0;
}
