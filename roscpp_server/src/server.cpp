#include"ros/ros.h"
#include"roscpp_server/triangleErea.h"
#include"cmath"
bool cb(roscpp_server::triangleErea::Request &req,
        roscpp_server::triangleErea::Response &res)
{
    ROS_INFO("开始解析...");
    double area = sqrt(3) * pow(req.length, 2);
    res.erea = area;
    ROS_INFO("请求的三角形面积为: %.2f", area);
    return true;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "jiedian1");
    ros::NodeHandle nh;
    // 创建一个服务器
    ros::ServiceServer server = nh.advertiseService<roscpp_server::triangleErea::Request, roscpp_server::triangleErea::Response>("/erea",cb);
    ros::spin();
    return 0;
}
