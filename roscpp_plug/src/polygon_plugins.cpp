//pluginlib 宏，可以注册插件类
#include <pluginlib/class_list_macros.h>
#include <roscpp_plug/polygon_base.h>
#include <roscpp_plug/polygon_plugins.h>

//参数1:衍生类 参数2:基类
PLUGINLIB_EXPORT_CLASS(plugins::Triangle,polygon_base::RegularPolygon)
PLUGINLIB_EXPORT_CLASS(plugins::Square,polygon_base::RegularPolygon)