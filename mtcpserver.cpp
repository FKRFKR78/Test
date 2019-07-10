#include "mtcpserver.h"
#include "ui_mtcpserver.h"
#include<QMessageBox>
mtcpserver::mtcpserver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mtcpserver)
{
    ui->setupUi(this);
    mserver=new QTcpServer();
}
void mtcpserver::sucessful_listen()
{
    this->currentClient=mserver->nextPendingConnection();
    tcpClient.append(this->currentClient);
    ui->comboBox->addItem(this->currentClient->peerAddress().toString());
    connect(currentClient, SIGNAL(readyRead()), this, SLOT(mread()));
     connect(currentClient, SIGNAL(disconnected()), this, SLOT(mdisconnect()));
     connect(currentClient, SIGNAL(error(QAbstractSocket::SocketError)),
           this, SLOT(merror(QAbstractSocket::SocketError))) ;
}
void mtcpserver::mdisconnect()
{
    QTcpSocket *yup=static_cast<QTcpSocket *>(this->sender());
    for (int i=0;i<tcpClient.length();i++) {
        if(tcpClient[i]->peerName()==yup->peerName()&&tcpClient[i]->peerPort()==yup->peerPort())
        {
            tcpClient.removeAt(i);
            ui->comboBox->removeItem(i);
            break;
        }
    }
 }
void mtcpserver::mread()
{
    QTcpSocket *yup=static_cast<QTcpSocket *>(this->sender());
    ui->textEdit->append(yup->peerAddress().toString()+QString(":")+QString::fromUtf8(yup->readAll()));
}
void mtcpserver::merror(QAbstractSocket::SocketError socketError)
{
    QTcpSocket *yup=static_cast<QTcpSocket *>(this->sender());
    for (int i=0;i<tcpClient.length();i++) {
        if(tcpClient[i]->peerName()==yup->peerName()&&tcpClient[i]->peerPort()==yup->peerPort())
        {
            tcpClient.removeAt(i);
            ui->comboBox->removeItem(i);
            ui->textEdit->append(tr("unconnected")+yup->peerAddress().toString()+tr("\n"));
      //      QMessageBox::warning(this,"error",yup->errorString());
            break;
        }
    }
}
mtcpserver::~mtcpserver()
{
    delete ui;
}

void mtcpserver::on_pushButton_connect_clicked()
{
    QString ip=ui->lineEdit_ip->text();
    QString port=ui->lineEdit_port->text();
    bool ok;
    if(ip.startsWith("0"))
        ok=mserver->listen(QHostAddress::AnyIPv4,port.toInt());
    else
        ok=mserver->listen(QHostAddress(ip),port.toInt());
    if(ok==false)
    {
        QMessageBox msgBox;
         msgBox.setText(tr("failed to listen"));
    }
    ui->textEdit->append("listen");
    ui->pushButton_connect->setEnabled(false);
   connect(mserver,&QTcpServer::newConnection,this,&mtcpserver::sucessful_listen);
}

void mtcpserver::on_pushButton_send_clicked()
{
    int coloun=ui->comboBox->currentIndex();
    ui->textEdit->append(QString("send:")+ui->lineEdit_text->text());
    tcpClient[coloun]->write((ui->lineEdit_text->text()+QString("\n")).toUtf8());
}
