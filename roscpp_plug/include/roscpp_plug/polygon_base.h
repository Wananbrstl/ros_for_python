#ifndef ROSCPP_PLUG__POLYGON_BASE_H_
#define ROSCPP_PLUG__POLYGON_BASE_H_
namespace polygon_base
{
    class RegularPolygon
    {
    public:
        virtual void initialize(double size_lenth) = 0;
        virtual double area() = 0;
    protected:
        RegularPolygon(){}
    };
};
#endif

