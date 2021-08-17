#include"ros/ros.h"
#include"tf2_ros/static_transform_broadcaster.h"
#include"geometry_msgs/TransformStamped.h"
#include"geometry_msgs/Quaternion.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "broadcaster");
    ros::NodeHandle nh;
    // 创建一个发布者
    tf2_ros::StaticTransformBroadcaster broadcaster;
    // msg
    geometry_msgs::TransformStamped msg;
    msg.header.seq = 100;
    msg.header.stamp = ros::Time::now();
    msg.child_frame_id = "child_link";
    msg.header.frame_id = "base_link";
    // transform rotation
    // msg.transform.rotation.x = 

    // transform tranformation
    msg.transform.translation.x = 10;
    msg.transform.translation.y = 10;
    msg.transform.translation.z = 10;

    broadcaster.sendTransform(msg);
    ros::spin();
    return 0;
}
