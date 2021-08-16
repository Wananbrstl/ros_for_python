/*
    这是一个publisher发布者，发布消息用

*/
#include"ros/ros.h"
#include"roscpp_topic/Person.h"
#include"std_msgs/String.h"
#include"sstream"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nh;
    //创造一个发布者
    ros::Publisher pub = nh.advertise<roscpp_topic::Person>("/person",1000);
    //创造一个发布消息
    roscpp_topic::Person person;
    //这里面的消息通过参数传入
    // std_msgs/String name
    // int32 age
    // int32 weight
    // int32 height
    if(argc == 5)
    {
        ROS_INFO("开始处理.....");
        person.name = argv[1];
        person.age = atoi(argv[2]);
        person.height = atoi(argv[3]);
        person.weight = atoi(argv[4]);
    }
    else
    {
        ROS_ERROR("传入的参数不足!!!!");
    }
    ros::Rate r(1);
    while (ros::ok())
    {
        pub.publish(person);
        r.sleep();
        ros::spinOnce();
    }
    return 0;
}
