#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QMainWindow>
#include "include/opcda/OPCClient.h"
#include <QDebug>
#include<QTimer>
#include<QTcpSocket>
#include <QJsonParseError>
#include<QJsonDocument>
#include<QJsonObject>
#include<QVector>
#include<QList>
#include<QMap>
struct mreaddata{
public:
    QString ip;
    QString port;
    QString prjID;
    QString areaId;
    QString equID;
    QString topcname;
    QString groupname;
    int max_items;
    QList<QString>mitems_name;
    void clear()
    {
        ip.clear();
        port.clear();
        prjID.clear();
        areaId.clear();
        equID.clear();
    }
};
struct mjson_son
{
public:
    QString mtargetname;
    QString mvalue;
    mjson_son(QString input1,QString input2)
    {
        mtargetname=input1;
        mvalue=input2;
    }
};
namespace Ui {
  class ClientGui;
}

class ClientGui : public QMainWindow
{
  Q_OBJECT

public:
  explicit ClientGui(QWidget *parent = 0);
  ~ClientGui();
  OPCClient *opc;
  void writejson_tcp();
  void readtext();
  void manswer_tcp(int key,QString mtype,QString tagname);
private slots:
  void on_btn_startopc_clicked();

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();
  void sl_OnDataChange(OPCHANDLE hGroup,  DWORD dwCount, OPCHANDLE *phClientItems, VARIANT *pvValues, WORD *pwQualities, FILETIME *pftTimeStamps, HRESULT *pErrors, DWORD dwTransid);
  void on_pushButton_4_clicked();
  void Mdestroyed(QObject * = Q_NULLPTR);
  void mtimerout();
  void on_pushButton_group_clicked();
  void on_time_clearall();
  void on_pushButton_tcp_server_connect_clicked();
    void tcpsuccessfulconnect();
    void tcpdisconnect();
    void mtcprconnect();
    void mopcronnect();
    void mtcpread();
private:
    void msettable();
    void mupdatetable(QString name,QString value,QString state);
  Ui::ClientGui *ui;
  int maxlisten;
  QString  m_useID;
QString m_kongID;
  bool is_opc_error;
  bool is_tcp_connect;
  QTimer *mtimer;
  QTimer *clear_all_time;
  QTimer *tcpreconned;
  QTimer *opcreconned;
  QTcpSocket *msock;
  mreaddata read_tdta;
  QList<mjson_son>tjson_son;
  QMap<QString,int>m_map;
};

#endif // CLIENTGUI_H
