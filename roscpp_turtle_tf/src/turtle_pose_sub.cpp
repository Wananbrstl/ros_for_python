#include"ros/ros.h"
#include"tf2_ros/transform_broadcaster.h"
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"
#include"geometry_msgs/TransformStamped.h"
#include"turtlesim/Pose.h"
#include"tf2/LinearMath/Quaternion.h"
// 如果只是静态发布 则只用发布一次消息， 这个时候采用 static_transform_broadcasterster
#include"tf2_ros/static_transform_broadcaster.h"
/*
    传入 turtleName 通过订阅 /turtleName/pose 信息 
    转化成坐标转化信息， 发布
*/



static std::string turtleName;

void cb(const turtlesim::Pose::ConstPtr &ptr){  
    float x = ptr->x;
    float y = ptr->y;
    float theta = ptr->theta;
    static tf2_ros::TransformBroadcaster  broadcaster;
    // tf2_ros::TransformBroadcaster  broadcaster;
    geometry_msgs::TransformStamped trans;
    tf2::Quaternion qtn;
    qtn.setEuler(0,0,theta);

    trans.child_frame_id = turtleName;
    trans.header.frame_id = "world";
    trans.header.stamp = ros::Time::now();
    trans.transform.translation.x = x;
    trans.transform.translation.y = y;
    trans.transform.translation.z = 0;
    trans.transform.rotation.x = qtn.getX();
    trans.transform.rotation.y = qtn.getY();
    trans.transform.rotation.z = qtn.getZ();
    trans.transform.rotation.w = qtn.getW();
    
    broadcaster.sendTransform(trans);
    ROS_INFO("发送成功....\n 位置信息如下:\n x = %.2f,y = %.2f,z = 0",
            trans.transform.translation.x,
            trans.transform.translation.y);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    // 解析turtleName
    if (argc != 3) ROS_ERROR("需要一个string参数");
    turtleName = argv[1];
    ROS_INFO("获得参数 turtleName: %s", turtleName.c_str());
    ros::init(argc, argv, "turtle_pose_sub");
    ros::NodeHandle nh;
    // 创建sub
    std::string nodeName;
    nodeName = turtleName + "/pose"; 
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>(nodeName,100,&cb);
    ros::spin();
    return 0;
}
