#include"ros/ros.h"
#include"roscpp_server/triangleErea.h"
bool cb(roscpp_server::triangleErea::Request &req,
        roscpp_server::triangleErea::Response &res)
{
    ROS_INFO("开始解析...");
    ROS_INFO("请求的三角形面积为: %d", req.length);
    return true;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "/server/server");
    ros::NodeHandle nh;
    // 创建一个服务器
    ros::ServiceServer server = nh.advertiseService<roscpp_server::triangleErea>("/erea",cb);
    ros::spin();
    return 0;
}
