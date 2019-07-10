#include "readstlfile.h"
#include<QString>
#include<QDebug>
ReadSTLFile::ReadSTLFile()
{

}
double ReadSTLFile::getdistance(Point3f A,Point3f B)
{
    double mx=abs(A.x-B.x);
    double my=abs(A.y-B.y);
    double mz=abs(A.z-B.z);
    return sqrt(mx*mx+my*my+mz*mz);
}
void ReadSTLFile::insert_map(Point3f A)
{
    int x1=(int)(A.x*100);
    int y1=(int)(A.y*100);
    int z1=(int)(A.z*100);
    mtoal_data[z1][y1].insert(x1);
}
void ReadSTLFile::getmore(Point3f A, Point3f B, Point3f C)
{
    Point3f madd((A.x+B.x+C.x)/3,(A.y+B.y+C.y)/3,(A.z+B.z+C.z)/3);
   if(A==B||B==C||A==C||A==madd||B==madd||C==madd)
        return;
    double l1=getdistance(A,B);
    double l2=getdistance(C,B);
    double l3=getdistance(A,C);
    double p = (l1 + l2 + l3) / 2;
    double s = sqrt(p*(p - l1)*(p - l2)*(p - l3));
    double maxlegth = max(max(l1, l2), l3);
        if (s <= 0.01*maxlegth)
            return;
      //insert_map(madd);
        insert_line(A,madd);
         insert_line(B,madd);
          insert_line(C,madd);
        getmore(A,madd,B);
        getmore(A,madd,C);
        getmore(B,madd,C);
}
void ReadSTLFile::insert_line(Point3f A, Point3f B)
{
    double mdis=getdistance(A,B);
    int number=(int)(mdis/0.01);
    double kx=(B.x-A.x);
    double ky=(B.y-A.y);
    double kz=(B.z-A.z);
    for(int i=0;i<=number;i++)
    {
        Point3f C(kx*i+A.x,ky*i+A.y,kz*i+A.z);
        insert_map(C);
    }
}
int ReadSTLFile::ReadFile(const char *cfilename)
{
    FILE * pFile;
    long lSize;
    char* buffer;
    size_t result;
    /* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
    fopen_s(&pFile,cfilename, "rb");
    if (pFile == NULL)
    {
        fputs("File error", stderr);
        return 1;
    }

    /* 获取文件大小 */
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    /* 分配内存存储整个文件 */
    buffer = (char*)malloc(sizeof(char)*lSize);
    if (buffer == NULL)
    {
        fputs("Memory error", stderr);
        return 2;
    }
    char *title[80];
        fread(title, sizeof(unsigned char), 80, pFile);
        int number;
        fread(&number, sizeof(int), 1, pFile);
        //string s(title);
        printf("%s\n", title);
        cout << number << endl;
        unTriangles = number;
        float unless[3];
        float x[3];
        float y[3];
        float z[3];
          int color;
        for (int i = 0; i < number; i++)
        {
            fread(&unless, sizeof(float), 3, pFile);
            fread(&x, sizeof(float), 3, pFile);
            fread(&y, sizeof(float), 3, pFile);
            fread(&z, sizeof(float), 3, pFile);
            for (int i = 0; i < 3; i++)
            {
                pointList.push_back(Point3f(x[i], y[i], z[i]));
           //     cout << x[i] << "," << y[i] << "," << z[i] << endl;
            }
            fread(&color, sizeof(char), 2, pFile);
        }

    /* 将文件拷贝到buffer中 */
    //result = fread(buffer, 1, lSize, pFile);
    //if (result != lSize)
   // {
    //    fputs("Reading error", stderr);
     //   return 3;
   // }

    /* 结束演示，关闭文件并释放内存 */
    fclose(pFile);

    return 4;
}

bool ReadSTLFile::ReadASCII(const char *buffer)
{
    qDebug()<<"ASCII"<<endl;
    unTriangles = 0;
    float x, y, z;
    int i;
    string name, useless;
    stringstream ss(buffer);
    ss >> name >> name;
    ss.get();
    do {
        ss >> useless;
       if (useless != "facet")
            break;
        getline(ss, useless);
        getline(ss, useless);
        for (i = 0; i < 3; i++)
        {
            ss >> useless >> x >> y >> z;
            pointList.push_back(Point3f(x, y, z));
        }
        unTriangles++;
        getline(ss, useless);
        getline(ss, useless);
        getline(ss, useless);
    } while (1);
    qDebug()<<QString::number(unTriangles)<<endl;
    return true;
}

bool ReadSTLFile::ReadBinary(const char *buffer)
{
    qDebug()<<"Binary"<<endl;
    const char* p = buffer;
    char name[80];
    int i, j;
    memcpy(name, p, 80);
    p += 80;
    unTriangles= cpyint(p);
    for (i = 0; i < unTriangles; i++)
    {
        p += 12;//跳过头部法向量
        for (j = 0; j < 3; j++)//读取三顶点
            pointList.push_back(Point3f(cpyfloat(p), cpyfloat(p), cpyfloat(p)));
        p += 2;//跳过尾部标志
    }
    return true;
}

int ReadSTLFile::NumTri()
{
    return unTriangles;
}

vector<Point3f>& ReadSTLFile::PointList()
{
    return pointList;
}

int ReadSTLFile::cpyint(const char*& p)
{
    int cpy;
    memwriter = (char*)&cpy;
    memcpy(memwriter, p, 4);
    p += 4;
    return cpy;
}
float ReadSTLFile::cpyfloat(const char*& p)
{
    float cpy;
    memwriter = (char*)&cpy;
    memcpy(memwriter, p, 4);
        p += 4;
    return cpy;
}
void ReadSTLFile::mshow()
{
   // for(int i=0;i<pointList.size();i++)
  //  {
    //    QString s=QString("%1,%2,%3").arg(pointList[i].x).arg(pointList[i].y).arg(pointList[i].z);
   //     qDebug()<<s<<endl;
   // }
    for(int i=0;i<pointList.size();i=i+3)
    {
        insert_line(pointList[i],pointList[i+1]);
        insert_line(pointList[i],pointList[i+2]);
        insert_line(pointList[i+2],pointList[i+1]);
  //      insert_map(pointList[i]);
   //     insert_map(pointList[i+1]);
    //    insert_map(pointList[i+2]);
        getmore(pointList[i],pointList[i+1],pointList[2]);
    }
    auto j1=mtoal_data.begin();
    while(j1!=mtoal_data.end())
    {
        auto jj1=j1->second.begin();

        while(jj1!=j1->second.end())
        {
            auto jjj1=jj1->second.begin();
                while(jjj1!=jj1->second.end())
                 {
                    cout<<j1->first<<","<<jj1->first<<","<<(*jjj1)<<endl;
                    jjj1++;
                }
                jj1++;
        }
        j1++;
    }
    cout<<"--------------------------"<<endl;
   cout<<pointList.size()<<endl;
    cout<<mtoal_data.size()<<endl;
}
