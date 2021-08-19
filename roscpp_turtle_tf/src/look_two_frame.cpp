#include"ros/ros.h"
#include"geometry_msgs/TransformStamped.h"
#include"tf2_ros/buffer.h"
#include"tf2_ros/transform_listener.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "list_tf");
    if(argc != 3)
    {
        ROS_ERROR("请输入两个参数");
        return -1;
    }
    std::string tran1Name = argv[1]; 
    std::string tran2Name = argv[2];

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener lis(buffer);
    ros::Rate r(0.6);
    while (ros::ok())
    {
        try
        {
            geometry_msgs::TransformStamped trans = buffer.lookupTransform(tran1Name, tran2Name, ros::Time(0));
            ROS_INFO("===============");
            ROS_INFO("转换的结果如下");
            ROS_INFO("target_frame: %s   source_frame: %s",
                     trans.child_frame_id.c_str(),
                     trans.header.frame_id.c_str());
            ROS_INFO("位移为: (%.2f, %.2f, %.2f)",
                    trans.transform.translation.x,
                    trans.transform.translation.y,
                    trans.transform.translation.z);
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
