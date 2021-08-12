#include<ros/ros.h>
#include<rospy_cfg/drConfig.h>
#include<dynamic_reconfigure/server.h>
/*
    动态参数服务端
    1. 包含头文件
    2. 初始化操作
    3. 创建服务端
    4. 回调函数
*/
void callback(rospy_cfg::drConfig &configure, uint32_t level)
{
    ROS_INFO("修改后的整形数据为:%d", configure.int_param);}
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "dr");

    dynamic_reconfigure::Server<rospy_cfg::drConfig> server;
    dynamic_reconfigure::Server<rospy_cfg::drConfig>::CallbackType f;
    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);
    ros::spin();
    return 0;
}
