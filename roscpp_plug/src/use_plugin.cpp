#include"ros/ros.h"
#include"pluginlib/class_loader.h"
#include"roscpp_plug/polygon_plugins.h"
#include"roscpp_plug/polygon_base.h"

int main(int argc, char *argv[])
{   
    setlocale(LC_ALL, "");
    pluginlib::ClassLoader<polygon_base::RegularPolygon> loader("roscpp_plug","polygon_base::RegularPolygon");
    try{
        boost::shared_ptr<polygon_base::RegularPolygon> tri = loader.createInstance("plugins::Square");
        tri->initialize(10.2);
        double area = tri->area();
        ROS_INFO("得到三角形的面积是: %.2f", area);
    }
    catch(pluginlib::PluginlibException ex){
        ROS_ERROR(ex.what());
    }
    return 0;
}
