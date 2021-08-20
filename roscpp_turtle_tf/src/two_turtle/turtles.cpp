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
    // if(argc != 4)
    // {
    //     ROS_ERROR("需要三个参数: theta x y");
    //     return -1;
    // }
    // float theta = atoi(argv[1]);
    // float x = atoi(argv[2]);
    // float y = atoi(argv[3]);
    // std::cout << "解析到参数如下: " << std::endl;
    // ROS_INFO("x = %.2f, y = %.2f, theta = %.2f", 
    //         x,
    //         y,
    //         theta    
    //         );
    
    ros::init(argc, argv, "turtles");
    ros::NodeHandle n;
    // 创建一个服务
    // ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("/spawn");
    // 创建一个新海龟
    // turtlesim::Spawn spawn;
    // spawn.request.name = "turtle2";
    // spawn.request.theta = theta;
    // spawn.request.x = x;
    // spawn.request.y = y;
    // client.call(spawn); 
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
