#include"ros/ros.h"
#include"sensor_msgs/JointState.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "control_car");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<sensor_msgs::JointState>("/joint_states", 100);
    ros::Rate r(10);
    while (ros::ok())
    {
        sensor_msgs::JointState state;
        state.header.seq = 10;
        state.header.stamp = ros::Time::now();
        state.name.push_back("left2base");
        state.name.push_back("right2base");
        state.position.push_back(1);
        state.position.push_back(1);
        pub.publish(state);
        r.sleep();
    }
    return 0;
}
