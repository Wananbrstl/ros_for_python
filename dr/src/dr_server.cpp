#include"ros/ros.h"
#include"dynamic_reconfigure/server.h"
#include"dr/parameter_server_Config.h"

void cb(dr::parameter_server_Config &config, uint32_t level){
    ROS_INFO("解析出来的参数为:%d, %.2f, %s", 
            config.int_param,
            config.double_param,
            config.bool_param? "True":"False");
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "dr_server");
    dynamic_reconfigure::Server<dr::parameter_server_Config> server;
    dynamic_reconfigure::Server<dr::parameter_server_Config>::CallbackType f;
    f = boost::bind(&cb, _1, _2);
    server.setCallback(f);
    ros::spin();
    return 0;
}
