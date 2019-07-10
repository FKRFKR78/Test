#include "mudpsocket.h"
#include "ui_mudpsocket.h"
#include<QMessageBox>
mudpsocket::mudpsocket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mudpsocket)
{
    ui->setupUi(this);
    msock=new QUdpSocket();
   // msock->bind(7070);  本机端口
    connect(msock, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
          [=](QAbstractSocket::SocketError socketError){
    QMessageBox::warning(this,"error:",QString::number(socketError));
    });
}

mudpsocket::~mudpsocket()
{
    delete ui;
}
void mudpsocket::mreadyread()
{
    while (msock->hasPendingDatagrams()) {
        QByteArray datagram;
             datagram.resize(msock->pendingDatagramSize());
               msock->readDatagram(datagram.data(), datagram.size(),&maddress, &mport);
              QString text = QString::fromLocal8Bit(datagram);
              ui->textEdit->append(tr("read:")+maddress.toString()+tr(":")+QString::number(mport)+tr(" :")+text);
    }
}
void mudpsocket::on_pushButton_clicked()
{
    this->maddress=QHostAddress(ui->lineEdit_ip->text());
    this->mport=ui->lineEdit_port->text().toInt();
    QString text=ui->lineEdit_text->text();
    QByteArray datagram=text.toLocal8Bit();
    int msend;
    msend=msock->writeDatagram(datagram,datagram.size(),this->maddress,this->mport);
    if(msend==-1)
        QMessageBox::warning(this,"error","has an error");
    
}
