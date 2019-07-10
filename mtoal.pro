#-------------------------------------------------
#
# Project created by QtCreator 2019-06-15T19:11:04
#
#-------------------------------------------------

QT       += core gui network serialport serialbus axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mtoal
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        IODevice/miodevice.cpp \
        dxf/dl_dxf.cpp \
        dxf/dl_writer_ascii.cpp \
        dxf/smain.cpp \
        dxf/test_creationclass.cpp \
        excel/mexcel.cpp \
        main.cpp \
        mainwindow.cpp \
        mhttp/widget.cpp \
        modbus/master/master_mainwindow.cpp \
        modbus/master/master_settingsdialog.cpp \
        modbus/master/master_writeregistermodel.cpp \
        modbus/slave/settingsdialog.cpp \
        modbus/slave/smainwindow.cpp \
        mstl/point3f.cpp \
        mstl/readstlfile.cpp \
        mtcpserver.cpp \
        mtcpsocket.cpp \
        mudpserver.cpp \
        mudpsocket.cpp \
        qt-opcda-base-master/clientgui.cpp \
        qt-opcda-base-master/include/opcda/OPCClient.cpp \
        qt-opcda-base-master/include/opcda/OpcEnum_i.c \
        qt-opcda-base-master/include/opcda/Opcda_i.c \
        qt-opcda-base-master/include/opcda/copcdatacallback.cpp \
        qt-opcda-base-master/include/opcda/copctransaction.cpp \
        qt-opcda-base-master/include/opcda/opccomn_i.c \
        serialport/mserialport.cpp \
        serialport/slavethread.cpp
HEADERS += \
        IODevice/miodevice.h \
        dxf/dl_attributes.h \
        dxf/dl_codes.h \
        dxf/dl_creationadapter.h \
        dxf/dl_creationinterface.h \
        dxf/dl_dxf.h \
        dxf/dl_entities.h \
        dxf/dl_exception.h \
        dxf/dl_extrusion.h \
        dxf/dl_global.h \
        dxf/dl_writer.h \
        dxf/dl_writer_ascii.h \
        dxf/smain.h \
        dxf/test_creationclass.h \
        excel/mexcel.h \
        mainwindow.h \
        mhttp/widget.h \
        modbus/master/master_mainwindow.h \
        modbus/master/master_settingsdialog.h \
        modbus/master/master_writeregistermodel.h \
        modbus/slave/settingsdialog.h \
        modbus/slave/smainwindow.h \
        mstl/point3f.h \
        mstl/readstlfile.h \
        mtcpserver.h \
        mtcpsocket.h \
        mudpserver.h \
        mudpsocket.h \
        qt-opcda-base-master/clientgui.h \
        qt-opcda-base-master/include/opcda/OPCClient.h \
        qt-opcda-base-master/include/opcda/OpcEnum.h \
        qt-opcda-base-master/include/opcda/Opcda.h \
        qt-opcda-base-master/include/opcda/copcdatacallback.h \
        qt-opcda-base-master/include/opcda/copctransaction.h \
        qt-opcda-base-master/include/opcda/opccomn.h \
        qt-opcda-base-master/include/opcda/opcerror.h \
        qt-opcda-base-master/include/opcda/unknownbase.h \
        qt-opcda-base-master/include/opcda/wldef.h \
        serialport/mserialport.h \
        serialport/slavethread.h

FORMS += \
        IODevice/miodevice.ui \
        excel/mexcel.ui \
        mainwindow.ui \
        mhttp/mdialog.ui \
        mhttp/mform.ui \
        mhttp/widget.ui \
        modbus/master/master_mainwindow.ui \
        modbus/master/master_settingsdialog.ui \
        modbus/slave/settingsdialog.ui \
        modbus/slave/smainwindow.ui \
        mtcpserver.ui \
        mtcpsocket.ui \
        mudpserver.ui \
        mudpsocket.ui \
        qt-opcda-base-master/clientgui.ui \
        serialport/mserialport.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
LIBS += -luuid -loleaut32 -lole32 -lcomctl32  -lWs2_32

#TEMPLATE = subdirs
#SUBDIRS += \
  #  qt-opcda-base-master/D-Opc.pro

DISTFILES += \
    Drawing1.dxf \
    dxf/demo.dxf \
    dxf/myfile.dxf \
    dxf/ss1.dxf \
    mstl/cylin_20_10.STL \
    s1.dxf \
    s2.dxf

RESOURCES += \
    modbus/master/master.qrc \
    modbus/slave/slave.qrc
