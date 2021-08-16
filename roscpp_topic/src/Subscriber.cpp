#include"ros/ros.h"
#include"roscpp_topic/Person.h"
#include"std_msgs/String.h"
void cb(const roscpp_topic::Person::ConstPtr &ptr){
    ROS_INFO("进行消息解析...");
    ROS_INFO("姓名: %s, 年龄: %d, 身高: %d, 体重: %d",
            ptr->name.c_str(),
            ptr->age,
            ptr->height,
            ptr->weight);
}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<roscpp_topic::Person>("/person",1000, cb);
    ros::spin();
    return 0;
}
