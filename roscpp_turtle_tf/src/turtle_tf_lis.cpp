#include"ros/ros.h"
#include"tf2_ros/buffer.h"
#include"tf2_ros/transform_listener.h"
#include"geometry_msgs/TransformStamped.h"
#include"geometry_msgs/PointStamped.h"
static std::string turtleName;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    // 输入turtleName
    if(argc != 2) ROS_ERROR("输入两个参数!");
    turtleName = argv[1];
    // turtleName.append("/pose");
    ros::init(argc, argv, "turtle_tf_lis");
    ros::NodeHandle nh;
    // pbulisher
    ros::Publisher pub = nh.advertise<geometry_msgs::TransformStamped>("/trans",1000);
    // 创建一个buffer
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener lis(buffer);
    ros::Rate r(10);
    geometry_msgs::PointStamped point_in;
    point_in.header.frame_id = turtleName;
    point_in.header.stamp = ros::Time(0);
    point_in.point.x = 1;
    point_in.point.y = 1;
    point_in.point.z = 1;
    while (ros::ok())
    {
        
        try{
            geometry_msgs::TransformStamped trans;
            trans = buffer.lookupTransform(turtleName, "world", ros::Time(0));
            // std::cout<<"=================================="<<std::endl;
            // std::cout<<"target_link =  "<< trans.header.frame_id.c_str() << "child_lin = " << trans.child_frame_id.c_str() <<std::endl;
            // std::cout<<"(x, y, z) = " << "(" << trans.transform.translation.x << "," << \
            // trans.transform.translation.y<<","<<trans.transform.translation.z <<")" <<std::endl;
            // pub.publish(trans);
            ROS_INFO("解析完成....");
        }
        catch(std::exception &ex){
            std::cout<< ex.what();
        }
        // std::cout<< trans_out.transform.translation.x <<std::endl;
        // std::cout<< trans_out.transform.translation.y <<std::endl;
        // std::cout<< trans_out.transform.translation.z <<std::endl;
        r.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
