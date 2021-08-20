#include"ros/ros.h"
#include"turtlesim/Spawn.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    // if(argc != 5)
    // {
    //     ROS_ERROR("需要四个个参数: name theta x y");
    //     return -1;
    // }
    const std::string turtleName = argv[1];
    float theta = atoi(argv[2]);
    float x = atoi(argv[3]);
    float y = atoi(argv[4]);
    std::cout << "解析到参数如下: " << std::endl;
    ROS_INFO("turtle_name = %s, x = %.2f, y = %.2f, theta = %.2f", 
            turtleName.c_str(),
            x,
            y,
            theta    
            );
    ros::init(argc, argv, "create_turtle");
    ros::NodeHandle n;
    // 创建一个服务
    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("/spawn");
    // 创建一个新海龟
    turtlesim::Spawn spawn;
    spawn.request.name = "turtle2";
    spawn.request.theta = theta;
    spawn.request.x = x;
    spawn.request.y = y;
    if(client.waitForExistence()){
        client.call(spawn);
        ROS_INFO("%s创建成功!", turtleName.c_str());
    } 
    return 0;
}
