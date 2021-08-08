#include<ros/ros.h>
#include<rospy_action/addIntsAction.h>
#include<std_msgs/String.h>
#include<actionlib/server/action_server.h>

typedef actionlib::ActionServer<rospy_action::addIntsAction> server;
int main(int argc, char const *argv[])
{
    ros::init(argc, argv, "addInts");
    ros::NodeHandle n;
    server Server();

    return 0;
}
