#include"ros/ros.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "set");
    ros::param::set("name", "张三");
    ros::param::set("age", 12);
    ros::param::set("height", 170.2);
    ros::param::set("weight", 56.45);
    ros::param::set("sex", true);
    std::map<std::string, std::string> name_map;
    name_map.insert(std::pair<std::string,std::string>("name", "zhangsan"));
    ros::param::set("name_map",name_map);
    std::vector<int> a;
    for(int i = 0; i < 10; i++)
    {
        a.push_back(i);
    }
    ros::param::set("vec", a);
    ROS_INFO("参数设置完成....");
    return 0;
}

