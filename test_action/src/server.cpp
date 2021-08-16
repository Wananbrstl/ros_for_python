#include"ros/ros.h"
#include"actionlib/server/simple_action_server.h"
#include"test_action/jiechenAction.h"

int fibonacci(int num){
    if(num == 0) return 0;
    if(num == 1) return 1;
    else    return fibonacci(num-1) + fibonacci(num-2);
}

void callback(const test_action::jiechenGoalConstPtr &goal, actionlib::SimpleActionServer<test_action::jiechenAction> *server){
    ROS_INFO("start to work....");
    int num = goal->goal;
    ROS_INFO("the goal is %d", goal->goal);
    test_action::jiechenFeedback feedback;
    test_action::jiechenActionResult result;
    ros::Rate r(1);
    feedback.feedback.clear();
    while(ros::ok()){
        for(int i = 0;i < num; i++)
        {
            int feed = fibonacci(i);
            feedback.feedback.push_back(feed);
            server->publishFeedback(feedback);
            r.sleep();
        }
    }
    test_action::jiechenResult res;
    res.result = fibonacci(num);
    server->setSucceeded(res);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "fibonacci");
    ros::NodeHandle nh;
    actionlib::SimpleActionServer<test_action::jiechenAction> server(nh, "fibonacci", boost::bind(&callback, _1, &server), false);
    server.start();
    ros::spin();
    return 0;
}
