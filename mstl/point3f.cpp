#include "point3f.h"

Point3f::Point3f()
{

}
Point3f::Point3f(float _x, float _y, float _z)
{
    x=_x;
    y=_y;
    z=_z;
}
int Point3f::SetParam(float _x, float _y, float _z)
{
    x=_x;
    y=_y;
    z=_z;
    return 0;
}

