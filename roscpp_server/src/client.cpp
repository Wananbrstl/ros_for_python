#include"ros/ros.h"
#include"roscpp_server/triangleErea.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "/server/client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<roscpp_server::triangleErea>("erea");
    if(argc == 2){
        int length = atoi(argv[1]);
        //客户端发送的参数
        ROS_INFO("客户端解析的参数为: %d", length); 
        // 等待存在
    client.waitForExistence();
    // 开始请求服务
    roscpp_server::triangleErea req;
    req.request.length = length;
    client.call(req);
    }
    else ROS_ERROR("输入参数应为一个整数");
    return 0;
}
