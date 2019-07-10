#include "mudpserver.h"
#include "ui_mudpserver.h"

mudpserver::mudpserver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mudpserver)
{
    ui->setupUi(this);
    this->mudpSocket=new   QUdpSocket;
}

mudpserver::~mudpserver()
{
    delete ui;
}

void mudpserver::on_pushButton_connect_clicked()
{
    this->mudpSocket->bind(QHostAddress(ui->lineEdit_ip->text()),ui->lineEdit_port->text().toInt());
      mudpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption,1024*1024*8);
    ui->textEdit->append(tr("bind"));
    connect(mudpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
          [=](QAbstractSocket::SocketError socketError){
    QMessageBox::warning(this,"error:",QString::number(socketError));
    });
   // this->mudpSocket->bind(QHostAddress::AnyIPv4,ui->lineEdit_port->text().toInt(),QUdpSocket::ShareAddress);
    //bool result = mudpSocket->joinMulticastGroup(QHostAddress(multicastIP));组播
    connect(mudpSocket,&QUdpSocket::readyRead,this,&mudpserver::readPendingDatagrams);
}
void mudpserver::readPendingDatagrams()
{
          while (mudpSocket->hasPendingDatagrams())
        {
              QHostAddress sender;
              quint16 senderPort;
            QByteArray datagram;
             datagram.resize(mudpSocket->pendingDatagramSize());
             mudpSocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
              QString strMes(datagram);
            ui->textEdit->append(strMes);
            if(msenderPort.size()==0||!msenderPort.contains(senderPort))
            {
                msenderPort.push_back(senderPort);
                msender.push_back(sender);
               ui->comboBox->addItem(QString::number(senderPort)+tr(":")+sender.toString());
            }
           }
}
void mudpserver::on_pushButton_send_clicked()
{
        QString text = ui->lineEdit_text->text();
        int num=ui->comboBox->currentIndex();
       QByteArray datagram = text.toLocal8Bit();
      mudpSocket->writeDatagram(datagram.data(),datagram.size(),msender[num],msenderPort[num]);
}

void mudpserver::on_pushButton_disconnect_clicked()
{

}
