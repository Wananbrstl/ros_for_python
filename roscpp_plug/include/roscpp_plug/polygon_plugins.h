#ifndef ROSCPP_PLUG__POLYGON_PLUGINS_H_
#define ROSCPP_PLUG__POLYGON_PLUGINS_H_
#include <roscpp_plug/polygon_base.h>

#include <cmath>
namespace plugins
{
    class Triangle :public polygon_base::RegularPolygon{
    public:
        void initialize(double size_length){
            size_length_ = size_length;
        }
        double area(){
            return sqrt(3) * pow(size_length_,2) / 2;
        }
    private:
        double size_length_ = 0;
    };


    class Square: public polygon_base::RegularPolygon{
    public:
        void initialize(double size_length){
            size_length_ = size_length;
        }
        double area(){
            return size_length_ * size_length_;
        }
    private:
        double size_length_ = 0;
    };
};
#endif