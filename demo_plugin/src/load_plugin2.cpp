#include"ros/ros.h"
#include"demo_plugin/polygon_plugins.h"
#include"pluginlib/class_loader.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "loader2");
    ros::NodeHandle n;
    pluginlib::ClassLoader<polygon_base::RegularPolygon> loader("demo_plugin","polygon_base::RegularPolygon");
    try
    {
        boost::shared_ptr<polygon_base::RegularPolygon> ptr_angle = loader.createInstance("polygon_plugins::Triangle");    
        ptr_angle->initialize(190);
        std::cout << ptr_angle->area() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}
