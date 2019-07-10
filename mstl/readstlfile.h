#ifndef READSTLFILE_H
#define READSTLFILE_H
#include<vector>
#include"point3f.h"
#include <fstream>
#include <string>
#include <sstream>
#include<set>
#include<map>
using namespace std;
class ReadSTLFile
{
public:
    int ReadFile(const char *cfilename);
      int NumTri();
      vector<Point3f>& PointList();
      //set<Point3f>mtoal_data;
      map<int,map<int,set<int>>>mtoal_data;
      ReadSTLFile();
      void mshow();
      void insert_line(Point3f A,Point3f B);
      void getmore(Point3f A,Point3f B,Point3f C);
      double getdistance(Point3f A,Point3f B);
      void insert_map(Point3f A);
  protected:
    vector<Point3f> pointList;
        unsigned int unTriangles;
        bool ReadASCII(const char *cfilename);
        bool ReadBinary(const char *cfilename);
        char* memwriter;
        int cpyint(const char*& p);
        float cpyfloat(const char*& p);
};

#endif // READSTLFILE_H
