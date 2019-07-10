#ifndef POINT3F_H
#define POINT3F_H
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<math.h>
struct Vertex //顶点结构
{
    Vertex() {}
    Vertex(float x, float y, float z)
    {
        _x = x;  _y = y;  _z = z;
    }
    float _x, _y, _z;
    static const DWORD FVF;
};


class Point3f
{
public:
    Point3f();
    Point3f(float _x,float _y,float _z);
       int SetParam(float _x, float _y, float _z);
       inline Vertex IVertex()
       {
           return Vertex(x, y, z);
       }
       bool operator == (const Point3f &t) const
       {
           float mmax=std::max(std::max(std::abs(t.x-x),std::abs(t.y-y)),std::abs(t.z-z));
           if(mmax>0.01)
               return false;
           else
               return true;
       }
       bool operator < (const Point3f &t) const
       {
           if(z<t.z)
               return true;
           else {
               if(z>t.z)
                   return false;
               else {
                   if(y<t.y)
                       return true;
                   else {
                       if(y>t.y)
                           return false;
                       else {
                           return (x>=t.x)?true:false ;
                       }
                   }
               }
           }
           return false;
       }
       double x, y, z;
};

#endif // POINT3F_H
