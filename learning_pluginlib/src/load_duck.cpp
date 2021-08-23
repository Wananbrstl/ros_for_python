#include "ros/ros.h"
#include "pluginlib/class_loader.h"
#include "learning_pluginlib/Duck.h"
#include "learning_pluginlib/happy_duck.h"
#include "learning_pluginlib/simple_duck.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "load_pluginlib");
    ros::NodeHandle n;
    pluginlib::ClassLoader<learning_pluginlib::Duck> duck_loader("learning_pluginlib","learning_pluginlib::Duck");
    try
    {
        boost::shared_ptr<learning_pluginlib::Duck> green_duck = duck_loader.createInstance("learning_pluginlib::happy_duck");
        green_duck->initialize("GREEN");
        // boost::shared_ptr<learning_pluginlib::Duck> yellow_duck = duck_loader.createInstance("learning_pluginlib::simple_duck");
        // yellow_duck->initialize("YELLOW");
        // std::cout << green_duck->get_type() << std::endl;
        // std::cout << green_duck->get_type() << std::endl;
    }
    catch (pluginlib::PluginlibException &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
