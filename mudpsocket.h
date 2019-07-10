#ifndef MUDPSOCKET_H
#define MUDPSOCKET_H

#include <QMainWindow>
#include<QUdpSocket>
#include<QHostAddress>
namespace Ui {
class mudpsocket;
}

class mudpsocket : public QMainWindow
{
    Q_OBJECT
    QHostAddress maddress;
    quint16 mport;
public:
    explicit mudpsocket(QWidget *parent = nullptr);
    ~mudpsocket();

private slots:
    void on_pushButton_clicked();
    void mreadyread();
private:
    Ui::mudpsocket *ui;
    QUdpSocket *msock;
};

#endif // MUDPSOCKET_H
