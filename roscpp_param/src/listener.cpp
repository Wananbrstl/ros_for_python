#include"ros/ros.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "get");
    std::string name;
    int age;
    std::vector<int> vec;
    std::map<std::string, std::string> name_map;
    double weight, height;
    bool flage;
    ros::param::get("name", name);
    ros::param::get("age", age);
    ros::param::get("weight", weight);
    ros::param::get("height", height);
    ros::param::get("vec", vec);
    ros::param::get("name_map", name_map);
    ros::param::get("sex",flage );
    ROS_INFO("姓名: %s", name.c_str());
    ROS_INFO("年龄: %d", age);
    ROS_INFO("体重: %.2f", weight);
    ROS_INFO("身高: %.2f", height);
    ROS_INFO("性别: %s", flage? "男生":"女生");
    // 解析vector和map
    int num;
    for(auto num: vec)
    {
        ROS_INFO("vector中数值为: %d", num);
    }
    for (auto &&f : name_map)
    {
        ROS_INFO("map中参数为: pair<%s, %s>", f.first.c_str(), f.second.c_str());
    }
    return 0;
}
