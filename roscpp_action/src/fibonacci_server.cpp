#include "ros/ros.h"
#include "actionlib/server/simple_action_server.h"
#include "roscpp_action/fibonacciAction.h"

// class fibonacci_server
// {
// protected:
//     ros::NodeHandle n_;
//     actionlib::SimpleActionServer<roscpp_action::fibonacciAction> server_;
//     std::string action_name_;
//     roscpp_action::fibonacciActionFeedback feedback_;
//     roscpp_action::fibonacciResult result_;
// public:
//     fibonacci_server(std::string name): 
//     as_(n_, name, boost::bind(&fibonacci_server::executeCB, this, _1), false),
//     action_name_(name)
//     {
//         as_.start();
//     }
//     ~fibonacci_server();
// };
// fibonacci_server::~fibonacci_server()
// {
// }
int fibonacci(int num){
    if (num == 0){
        return 0;
    }
    else if(num == 1){
        return 1;
    }
    else{
        return fibonacci(num-1) + fibonacci(num-2);
    }
}
typedef actionlib::SimpleActionServer<roscpp_action::fibonacciAction> Server;

void callback(roscpp_action::fibonacciGoal &goal, Server *server){
    int num = goal.order;
    ROS_INFO("收到目标数为: %d", num);
    //fibonacci数列的操作:
    roscpp_action::fibonacciFeedback fb;
    for(int i = 0; i<num;i++ ){
        fb.sequence[i] = fibonacci(i);
        server->publishFeedback(fb);
    }
    roscpp_action::fibonacciResult result;
    result.sequence[0] = fibonacci(num);
    server->setSucceeded(result);
}

int main(int argc, char *argv[])
{   
    // 第一步 初始化节点
    ros::init(argc, argv, "fibonacci_server");
    // 
    ros::NodeHandle n;
    Server server(n,"fibonacci", boost::bind(&callback, _1, &server), false);
    server.start();
    ros::spin();
    return 0;
}
