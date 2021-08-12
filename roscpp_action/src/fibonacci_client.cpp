#include "ros/ros.h"
#include "actionlib/client/simple_action_client.h"
#include "roscpp_action/fibonacciAction.h"

typedef actionlib::SimpleActionClient<roscpp_action::fibonacciAction> Client;
void donecallback(const actionlib::SimpleClientGoalState &state, const roscpp_action::fibonacciResultConstPtr &result)
{
    ROS_INFO("处理的结果是: %d", result->sequence[0]);

}

void feedback(const roscpp_action::fibonacciFeedbackConstPtr &feedback){
    ROS_INFO("中途的回调函数");
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "fibonacci_client");
    ros::NodeHandle n;
    Client client(n, "fibonacci");

    client.waitForServer();
    //void sendGoal(const roscpp_action::fibonacciGoal &goal,
    //              boost::function<void (const actionlib::SimpleClientGoalState &state, const roscpp_action::fibonacciResultConstPtr &result)> done_cb, boost::function<void ()> active_cb,
    //              boost::function<void (const roscpp_action::fibonacciFeedbackConstPtr &feedback)> feedback_cb)
    roscpp_action::fibonacciGoal goal;
    goal.order = 100;
    client.sendGoal(goal, &donecallback,  &feedback);
    return 0;
}

