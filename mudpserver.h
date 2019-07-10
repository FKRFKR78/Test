#ifndef MUDPSERVER_H
#define MUDPSERVER_H
#include <QMainWindow>
#include<QUdpSocket>
#include<QMessageBox>
#include<QList>
namespace Ui {
class mudpserver;
}

class mudpserver : public QMainWindow
{
    Q_OBJECT

public:
    explicit mudpserver(QWidget *parent = nullptr);
    ~mudpserver();
    QList<QHostAddress>msender;
        QList<quint16>msenderPort;
private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_disconnect_clicked();

    void readPendingDatagrams();
private:
    Ui::mudpserver *ui;
    QUdpSocket    *mudpSocket;
};

#endif // MUDPSERVER_H
