#include"ros/ros.h"
#include"actionlib/client/simple_action_client.h"
#include"test_action/jiechenAction.h"

void done_cb(const actionlib::SimpleClientGoalState &state,const test_action::jiechenResultConstPtr &result)
{
    ROS_INFO("done!!!!");
}

void feedback_cb(const test_action::jiechenFeedbackConstPtr &feedback){
    std::cout<< " feedback_cb is called ";
    ROS_INFO("feedback is %d", feedback->feedback.back()); 
}
void active_cb(){
    ROS_INFO("start ....");
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "client");
    ros::NodeHandle n;
    // create client
    actionlib::SimpleActionClient<test_action::jiechenAction> client(n,"fibonacci");
    // wait for server
    client.waitForServer();
    test_action::jiechenGoal goal;
    goal.goal = 15;
//     void SimpleActionClient<ActionSpec>::sendGoal(const Goal & goal,
//   SimpleDoneCallback done_cb,
//   SimpleActiveCallback active_cb,
//   SimpleFeedbackCallback feedback_cb)
    client.sendGoal(goal, &done_cb, &active_cb, &feedback_cb);
    ros::spin();
    return 0;
}
