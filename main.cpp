
#include <QApplication>
#include <QLoggingCategory>
#include"modbus/master/master_mainwindow.h"
#include"modbus/slave/smainwindow.h"
#include"IODevice/miodevice.h"
#include"mstl/readstlfile.h"
#include"mtcpserver.h"
#include"mtcpsocket.h"
#include"dxf/smain.h"
#include"excel/mexcel.h"
int main(int argc, char *argv[])
{

    QLoggingCategory::setFilterRules(QStringLiteral("qt.modbus* = true"));
    QApplication a(argc, argv);
    mtcpsocket s1;
    s1.show();
  //  mexcel s;
    //s.show();
    /*
    mtcpserver s1;
    mtcpsocket s2;
    s1.show();
    s2.show();
    */
  // miodevice s;
   // s.show();
   // ReadSTLFile pl;
   //const char *name="cylin_20_10.STL";
    //qDebug()<<QString::number(pl.ReadFile(name));
   // pl.mshow();
  //  msamin s1;
  //  s1.smain();
    return a.exec();
}
