#include"ros/ros.h"
#include"tf2_ros/buffer.h"
#include"tf2_ros/transform_listener.h"
#include"geometry_msgs/TransformStamped.h"
#include"geometry_msgs/PointStamped.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "lis");
    ros::NodeHandle nh;
    // Buffer and Listener
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    // define a geometry::PointStamped
    geometry_msgs::PointStamped point;
    point.header.frame_id = "child_link";
    point.header.stamp = ros::Time::now();
    point.point.x = 1;
    point.point.y = 2;
    point.point.z = 3;
    
    ros::Rate r(1);
    ros::Duration(2).sleep();
    while (ros::ok())
    {
        try
        {
            geometry_msgs::PointStamped point_base;
            point_base = buffer.transform(point,"base_link");
            ROS_INFO("(%.2f, %.2f, %.2f)",
                        point_base.point.x,
                        point_base.point.y,
                        point_base.point.z);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        r.sleep();
        ros::spinOnce();
    }
    return 0;
    
}
