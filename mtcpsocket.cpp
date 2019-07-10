#include "mtcpsocket.h"
#include "ui_mtcpsocket.h"
#include<QMessageBox>
#include<QByteArray>
#include<iostream>
mtcpsocket::mtcpsocket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mtcpsocket)
{
    ui->setupUi(this);
    msock=new QTcpSocket();
    ui->lineEdit_ip->setText(tr("192.168.1.110"));
    ui->lineEdit_port->setText(tr("30003"));
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    ui->pushButton_send->setEnabled(false);
    on_pushButton_connect_clicked();
}
void mtcpsocket::ReadMultipleRegsiter(int ResigterNum,int StartAddress,bool IfSlow,QByteArray sp1)
{
    /*
    BYTE *TruelyDateBye=new BYTE[ResigterNum*2];
    QVector<int>TruelyDataInt(ResigterNum);
    QList<BYTE>sendData{255};
    for(int i=0;i<2*ResigterNum;i++)
        TruelyDateBye[i]=sp1[i+9];
    for(int i=0;i<2*ResigterNum;i++)
        TruelyDataInt[i]=TruelyDateBye[i*2]*256+TruelyDateBye[i*2+1];
    double AnglesFil[6];
    for(int i=0;i<6;i++)
    {
        if(TruelyDataInt[i]>32768)
            TruelyDataInt[i]=TruelyDataInt[i]-65535;
        AnglesFil[i]=(double)TruelyDataInt[i]/1000*(180/3.1415);
        if(i!=4)
            AnglesFil[i]=AnglesFil[i]-360.0;
        std::cout<<AnglesFil[i]<<endl;
    }
    delete []TruelyDateBye;
    */
}
void mtcpsocket::merror(QAbstractSocket::SocketError socketError)
{
    msock->disconnectFromHost();
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    ui->pushButton_send->setEnabled(false);
    this->is_connected=false;
    QMessageBox msgBox;
   msgBox.setText(tr("failed to connect server because %1").arg(msock->errorString()));
}
mtcpsocket::~mtcpsocket()
{
    delete ui;
    delete  msock;
}
void mtcpsocket::tcp_connected()
{
    this->is_connected=true;
    ui->pushButton_connect->setEnabled(false);
    ui->pushButton_disconnect->setEnabled(true);
    ui->pushButton_send->setEnabled(true);
    connect(this->msock,&QTcpSocket::readyRead,this,&mtcpsocket::tcp_readready);
}
void mtcpsocket::tcp_readready()
{
    QByteArray s=msock->read(1044);
    ReadMultipleRegsiter(6,270,false,s);
}
void mtcpsocket::mdisconnect()
{
    this->is_connected=false;
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    ui->pushButton_send->setEnabled(false);
}
void mtcpsocket::on_pushButton_connect_clicked()
{
    this->msock->abort();
    this->tcp_ip=ui->lineEdit_ip->text();
    this->tcp_port=ui->lineEdit_port->text();
    connect(this->msock,&QTcpSocket::connected,this,&mtcpsocket::tcp_connected);
    connect(this->msock,&QTcpSocket::disconnected,this,&mtcpsocket::mdisconnect);
    connect(msock, SIGNAL(error(QAbstractSocket::SocketError)),
          this, SLOT(merror(QAbstractSocket::SocketError))) ;  this->msock->connectToHost(this->tcp_ip,this->tcp_port.toInt());
}

void mtcpsocket::on_pushButton_disconnect_clicked()
{
    this->msock->abort();
    this->is_connected=false;
}

void mtcpsocket::on_pushButton_send_clicked()
{
    qDebug()<<tr("send");
    msock->write((ui->lineEdit_text->text()+QString("\n")).toUtf8());
}
