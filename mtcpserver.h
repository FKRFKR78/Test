#ifndef MTCPSERVER_H
#define MTCPSERVER_H

#include <QMainWindow>
#include<QTcpSocket>
#include<QDebug>
#include <QAbstractSocket>
#include<QTcpServer>
#include<QList>
namespace Ui {
class mtcpserver;
}

class mtcpserver : public QMainWindow
{
    Q_OBJECT

public:
    explicit mtcpserver(QWidget *parent = nullptr);
    ~mtcpserver();

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_send_clicked();
    void sucessful_listen();
    void mdisconnect();
    void mread();
    void merror(QAbstractSocket::SocketError socketError);
private:
    Ui::mtcpserver *ui;
    QTcpServer *mserver;
    QList<QTcpSocket*> tcpClient;
     QTcpSocket *currentClient;

};

#endif // MTCPSERVER_H
