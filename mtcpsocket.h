#ifndef MTCPSOCKET_H
#define MTCPSOCKET_H

#include <QDialog>
#include<QTcpSocket>
#include<QDebug>
#include <QAbstractSocket>
#include<windows.h>
#include<algorithm>
namespace Ui {
class mtcpsocket;
}

class mtcpsocket : public QDialog
{
    Q_OBJECT

public:
    explicit mtcpsocket(QWidget *parent = nullptr);
    ~mtcpsocket();
    QString tcp_ip;
    QString tcp_port;
    bool is_connected;
    void ReadMultipleRegsiter(int ResigterNum,int StartAddress,bool ifSlow,QByteArray sp1);
private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_disconnect_clicked();

    void on_pushButton_send_clicked();
    void tcp_connected();
    void tcp_readready();
    void mdisconnect();
    void merror(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket *msock;
    Ui::mtcpsocket *ui;
    int toalbyteCount=0;
};

#endif // MTCPSOCKET_H
