#include"ros/ros.h"
#include"roscpp_server/triangleErea.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "jiedian2");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<roscpp_server::triangleErea>("erea");
    if(argc == 2){
        int length = atoi(argv[1]);
        //客户端发送的参数
        ROS_INFO("客户端解析的参数为: %d", length); 
        ros::service::waitForService("erea");
        // 等待存在
    // client.waitForExistence();
    // 开始请求服务
    roscpp_server::triangleErea req;
    req.request.length = length;
    bool flag = client.call(req);
    if(flag){
        ROS_INFO("解析到的结果为: %.2f", req.response.erea);
    }
        ros::spin();
    }
    else ROS_ERROR("输入参数应为一个整数");
    return 0;
}
