#include "clientgui.h"
#include "ui_clientgui.h"
#include <QDateTime>
#include <QUuid>
#include<QTime>
#include<QFile>
#include <QDateTime>
#include <QTime>
#include<QJsonArray>
#include<QMessageBox>
bool has_first_opc_readed=false;
ClientGui::ClientGui(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ClientGui)
{
  ui->setupUi(this);
  this->m_useID=" ";
  ui->textEdit_opc->setMaximumHeight(120);
  ui->groupBox_5->setMaximumHeight(160);
  this->is_tcp_connect=false;
  this->is_opc_error=false;
  this->opcreconned=new QTimer;
  this->tcpreconned=new QTimer;
  msock=new QTcpSocket;
  opc = 0;
  msettable();
  readtext();
  ui->pushButton->setEnabled(false);
  ui->pushButton_2->setEnabled(false);
  ui->pushButton_3->setEnabled(false);
  ui->pushButton_4->setEnabled(false);
  ui->pushButton_group->setEnabled(false);
  mtimer=new QTimer();
  this->clear_all_time=new QTimer();
  connect(this->clear_all_time,&QTimer::timeout,this,&ClientGui::on_time_clearall);
  connect(this->opcreconned,&QTimer::timeout,this,&ClientGui::mopcronnect);
  connect(this->tcpreconned,&QTimer::timeout,this,&ClientGui::mtcprconnect);
  connect(mtimer,&QTimer::timeout,this,&ClientGui::mtimerout);
  on_btn_startopc_clicked();
}
void ClientGui::msettable()
{
    ui->tableWidget->setColumnCount(4);
    QStringList header;
    header<<"item ID"<<"value"<<"updataTime"<<"Quality";
    ui->tableWidget->setHorizontalHeaderLabels(header);
}
void ClientGui::mupdatetable(QString name,QString value,QString state)
{
    if(this->m_map.contains(name))
    {
        int mrows=m_map[name];
        if(ui->tableWidget->item(mrows,1)->text()!=value||ui->tableWidget->item(mrows,3)->text()!=state)
        {
            ui->tableWidget->item(mrows,1)->setText(value);
            ui->tableWidget->item(mrows,2)->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            ui->tableWidget->item(mrows,3)->setText(state);
        }
    }
}
void ClientGui::mopcronnect()
{
    this->is_opc_error=true;
    on_btn_startopc_clicked();
}
void ClientGui::mtcprconnect()
{
    is_tcp_connect=false;
    on_pushButton_tcp_server_connect_clicked();
}
void ClientGui::readtext()
{
    QString path="read.txt";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
        return;
    }
        QByteArray line;
        line= file.readLine();
        QString str;
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        this->read_tdta.ip=str;
        str.clear();
        line.clear();/////IP
        ////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        this->read_tdta.port=str;
        str.clear();
        line.clear();/////port
        ////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        this->read_tdta.prjID=str;
        str.clear();
        line.clear();/////project
        ////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        this->read_tdta.areaId=str;
        str.clear();
        line.clear();/////areadID
        ////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        this->read_tdta.equID=str;
        str.clear();
        line.clear();/////equit
        ////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        this->read_tdta.topcname=str;
        qDebug()<<str<<endl;
        str.clear();
        line.clear();/////opcname
        ////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        this->read_tdta.groupname=str;
        str.clear();
        line.clear();/////gruopnmae
        ////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        this->read_tdta.max_items=str.toInt();
        ui->tableWidget->setRowCount(this->read_tdta.max_items);
        str.clear();
        line.clear();/////maxitems
        ////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        QString headname=str;
        str.clear();
        line.clear();/////frontname
        ////////////////////////////////////////////////////////////
        line= file.readLine();
        str=QString(line);
        str=str.simplified();
        str=str.section(":",1,1);
        QString endname=str;
        str.clear();
        line.clear();/////endname
        ////////////////////////////////////////////////////////////
        for(int  i=0;i< this->read_tdta.max_items;i++)
        {
            line= file.readLine();
            str=QString(line);
            str=str.simplified();
            str=str.section(":",1,1);
            if(!str.contains("."))
            {
                str=headname+QString(".")+str+QString(".")+endname;
            }
            this->m_map[str]=i;
            this->read_tdta.mitems_name.push_back(str);
            ui->lineEdit_2->setText(str);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(str));
             ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString("0")));
              ui->tableWidget->setItem(i,2,new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString("good")));
            str.clear();
            line.clear();
        }
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->show();
        ui->lineEdit_tcp_ip->setText(this->read_tdta.ip);
        ui->lineEdit_tcp_port->setText(this->read_tdta.port);
        ui->lineEdit_opc_server_name->setText(this->read_tdta.topcname);
        ui->lineEdit_group->setText(this->read_tdta.groupname);
}
void ClientGui::writejson_tcp()
{
    QJsonObject json;
    json.insert("prjID", this->read_tdta.prjID);
    json.insert("areaID", this->read_tdta.areaId);
    json.insert("equID",this->read_tdta.equID);
    json.insert("tm",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QJsonArray yuio;
    json.insert("type",QString("0"));
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QJsonObject tjson;
        tjson.insert("tagName",ui->tableWidget->item(i,0)->text().simplified());
        tjson.insert("sdata",ui->tableWidget->item(i,1)->text().simplified());
        yuio.append(QJsonValue(tjson));
    }
       json.insert("item",QJsonValue(yuio));
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    this->msock->write((QString::fromLocal8Bit(byte_array)+"\n").toLocal8Bit());
    ui->textEdit_tcp->append(QString::fromLocal8Bit(byte_array));
}
void ClientGui::tcpsuccessfulconnect()
{
    this->tcpreconned->stop();
    ui->textEdit_tcp->append(QTime::currentTime().toString("hh:mm:ss")+tr(": TCP 成功连接"));
    this->is_tcp_connect=true;
    ui->label_tcp_server_state->setText(tr("true"));
    ui->pushButton_tcp_server_connect->setEnabled(false);
    connect(msock,&QTcpSocket::readyRead,this,&ClientGui::mtcpread);
}
void ClientGui::tcpdisconnect()
{
    ui->textEdit_tcp->append(QTime::currentTime().toString("hh:mm:ss")+tr(": TCP 断开连接"));
    this->is_tcp_connect=false;
    ui->label_tcp_server_state->setText(tr("false"));
    ui->pushButton_tcp_server_connect->setEnabled(true);
    this->tcpreconned->start(5000);
}
ClientGui::~ClientGui()
{
  if(opc){
      opc->DisConnect();
      opc->deleteLater();
    }
  delete ui;
}
void ClientGui::mtimerout()//上传数据
{
    if(has_first_opc_readed&&this->is_tcp_connect)
    writejson_tcp();
/*
    if(this->is_opc_error)
        return;
 bool m_iserror=false;
 if(ui->comboBox->count()!=0)
    if(opc->isConnected())
    {
        int i=0;
        for(i=0;i<opc->items->size();i++)
        {
                 if(opc->ReadItem(opc->items->value(i)))
                 {
                            if(!opc->QualityString(opc->items->value(i)->quality).startsWith("B"))
                            {
                                tjson_son.push_back(mjson_son(opc->items->at(i)->name,opc->VariantString(opc->items->value(i)->value)));
                                mupdatetable(opc->items->at(i)->name,opc->VariantString(opc->items->value(i)->value),opc->QualityString(opc->items->value(i)->quality));
                                if(opc->items->at(i)->name==ui->comboBox->currentText())
                                {
                                    ui->textEdit_opc->append(ui->comboBox->currentText()+": read the value is :"+opc->VariantString(opc->items->value(i)->value));
                                }
                                }
                            else
                            {
                                m_iserror=true;
                                break;
                            }
                 }
                 else
                 {
                     m_iserror=true;
                     break;
                 }
        }
        writejson_tcp();
            if(m_iserror)
        {
                for(int j=0;j<m_map.size();j++)
                    ui->tableWidget->item(j,3)->setText(QString("bad"));
         this->is_opc_error=true;
        opc->minit();//初始化
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_group->setEnabled(false);
        ui->btn_startopc->setEnabled(true);
        ui->label_opcserver_state->setText("false");
        ui->comboBox->clear();
        ui->comboBox_group->clear();
       mtimer->stop();
       this->opcreconned->start(5000);
        }
    }
    */
}
void ClientGui::sl_OnDataChange(OPCHANDLE hGroup,  DWORD dwCount, OPCHANDLE *phClientItems, VARIANT *pvValues, WORD *pwQualities, FILETIME *pftTimeStamps, HRESULT *pErrors, DWORD dwTransid)//opc异步读取数据
{
    if(this->is_opc_error)
        return;
  if(!has_first_opc_readed)
      has_first_opc_readed=true;
 bool m_iserror=false;
    if(opc->isConnected())
    {
        tjson_son.clear();
          for (DWORD i = 0; i < dwCount;i++)
           {
                 int rows =phClientItems[i];
                 QString mname=opc->items->at(rows)->name;
                 QString mvalue=opc->VariantString(pvValues[i]);
                 QString mstate=opc->QualityString(pwQualities[i]);
                 if(mstate.startsWith("BA"))
                 {
                     m_iserror=true;
                     break;
                 }
                 tjson_son.push_back(mjson_son(mname,mvalue));
                 mupdatetable(mname,mvalue,mstate);
             /*     <<opc->VariantString(pvValues[i])<<","
                  <<opc->QualityString(pwQualities[i])<<","
                  <<QString::number(pftTimeStamps[i].dwLowDateTime)<<","
                  <<pErrors[i]<<"ssssssssssssssss"
                 <<dwTransid<<endl;
                 */
          }
    }
          if(m_iserror)
          {
              has_first_opc_readed=false;
          disconnect(opc->m_COPCTransaction,SIGNAL(sg_OnDataChange(OPCHANDLE,DWORD,OPCHANDLE*,VARIANT*,WORD*,FILETIME*,HRESULT*, DWORD )),this,SLOT(sl_OnDataChange(OPCHANDLE,DWORD,OPCHANDLE*,VARIANT*,WORD*,FILETIME*,HRESULT*, DWORD)));
              for(int j=0;j<m_map.size();j++)
                  ui->tableWidget->item(j,3)->setText(QString("bad"));
                    this->is_opc_error=true;
                 opc->minit();//初始化
                ui->pushButton->setEnabled(false);
                ui->pushButton_2->setEnabled(false);
                 ui->pushButton_3->setEnabled(false);
                  ui->pushButton_4->setEnabled(false);
                  ui->pushButton_group->setEnabled(false);
                  ui->btn_startopc->setEnabled(true);
                  ui->label_opcserver_state->setText("false");
                  ui->comboBox->clear();
                  ui->comboBox_group->clear();
                 mtimer->stop();
                 this->opcreconned->start(5000);
          }
    }
void ClientGui::Mdestroyed(QObject *)
{
    qDebug()<<"the group is destroyed"<<endl;
}
void ClientGui::on_btn_startopc_clicked()//opc开始连接
{
  if(!opc){
      opc=new OPCClient();
    }
  if(!opc->isConnected()){
     // ui->lineEdit_ERROR->setText("begin to connect opc server");
      ui->textEdit_opc->append(QTime::currentTime().toString("hh:mm:ss")+tr(": init to connect opc"));
      QString serverName = ui->lineEdit_opc_server_name->text().simplified();
      this->is_opc_error=false;
      bool result =  opc->Connect(serverName);//连接服务器
      ui->label_opcserver_state->setText(QString("false"));
      if(result==S_OK){
          ui->textEdit_opc->append(tr( "连接opc服务器成功"));
          ui->pushButton_group->setEnabled(true);
          this->opcreconned->stop();
          ui->label_opcserver_state->setText(QString("true"));
          ui->btn_startopc->setEnabled(false);
     //     on_pushButton_group_clicked();//开始添加组
          /*
          QString groupName = "Device1";
          if(opc->AddGroup(groupName,1000)==S_OK){
              qDebug()<< "分组添加成功";
              connect(opc->m_COPCTransaction,&COPCTransaction::destroyed,this,&ClientGui::Mdestroyed);
              connect(opc->m_COPCTransaction,SIGNAL(sg_OnDataChange(OPCHANDLE,DWORD,OPCHANDLE*,VARIANT*,WORD*,FILETIME*,HRESULT*)),this,SLOT(sl_OnDataChange(OPCHANDLE,DWORD,OPCHANDLE*,VARIANT*,WORD*,FILETIME*,HRESULT*)));
            */  }
        else{
          ui->textEdit_opc->append(tr("连接失败"));
            }
        }
}
void ClientGui::on_time_clearall()//清除显示
{
  //  ui->textEdit_opc->clear();
    ui->textEdit_tcp->clear();
}
void ClientGui::on_pushButton_clicked()//清除opc项
{
    if(opc){
        ui->textEdit_opc->append(QTime::currentTime().toString("hh:mm:ss")+tr(": delete all opc items"));
      opc->RemoveAllItems();
        ui->comboBox->clear();
        maxlisten=0;
      }
}

void ClientGui::on_pushButton_2_clicked()//添加项目
{
  if(!opc) return;
  QStringList inames;
  for(int i=0;i<this->read_tdta.max_items;i++)
      inames.append(this->read_tdta.mitems_name.at(i));
  QStringList r_inames= opc->AddItems(inames);
  if(r_inames.count()>0){
      ui->textEdit_opc->append(QTime::currentTime().toString("hh:mm:ss")+tr(": 添加项目监视成功"));
      ui->comboBox->clear();
      maxlisten=0;
                 for(int i=0;i<opc->items->count();i++){
                     ui->comboBox->addItem(opc->items->value(i)->name);
                     maxlisten=maxlisten+1;
                 //     qDebug()<<"读取指定项目值：" ;
               //       if(opc->ReadItem(opc->items->value(i))){
                //          qDebug()<< opc->items->value(i)->hServerHandle
                 //                 <<opc->items->value(i)->hClientHandle
                  //               <<opc->QualityString(opc->items->value(i)->quality)
                   //             <<opc->VariantString(opc->items->value(i)->value);
                     //   }
                    }
    }else{
      ui->textEdit_opc->append(QTime::currentTime().toString("hh:mm:ss")+tr(": 添加项目监视失败"));
    }
  on_pushButton_tcp_server_connect_clicked();
  this->mtimer->start(10000);
  this->clear_all_time->start(60000);
}

void ClientGui::on_pushButton_3_clicked()//写入
{
  if(opc->isWriteAble&&!is_opc_error){
      QString mname=opc->items->at(ui->comboBox->currentIndex())->name;
      QString mvalue=ui->lineEdit->text().simplified();
      int i=ui->comboBox->currentIndex();
      if(opc->ReadItem(opc->items->value(i)))
      {
           if(opc->WriteValue(mname,mvalue))
           {
             ui->tableWidget->item(i,1)->setText(mvalue);
             ui->textEdit_opc->append("write:"+mname+":"+mvalue);
           }
           else
               ui->textEdit_opc->append("write: + false : "+mname);
    }
  }
}

void ClientGui::on_pushButton_4_clicked()//清除项目
{
    if(opc){
        opc->RemoveItems(QStringList()<<ui->lineEdit_2->text());
        maxlisten=maxlisten-1;
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
      }
}
void ClientGui::manswer_tcp(int key,QString mtype,QString tagname)
{
    QString mstate=QString::number(key);
    QJsonObject json;
    json.insert("prjID", this->read_tdta.prjID);
    json.insert("areaID", this->read_tdta.areaId);
    json.insert("equID",this->read_tdta.equID);
    json.insert("tm",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
   json.insert("type",mtype);
   json.insert("userID",this->m_useID);
   json.insert("status",mstate);
   json.insert("kongID",this->m_kongID);
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    qDebug()<<"hear: "<<byte_array ;
    this->msock->write((QString::fromLocal8Bit(byte_array)+"\n").toLocal8Bit());
}
void ClientGui::on_pushButton_group_clicked()
{
    QString groupName = ui->lineEdit_group->text().simplified();
   if(ui->comboBox_group->count()==0)
        ui->comboBox_group->addItem(groupName);
    else
    {
        for(int i=0;i<ui->comboBox_group->count();i++)
            if(ui->comboBox_group->itemText(i)==groupName)
            {
                qDebug()<<"the combox of group name  is exit"<<endl;
                return ;
            }
    }
    if(!is_opc_error&&opc->AddGroup(groupName,1000)==S_OK){
        ui->textEdit_opc->append(QTime::currentTime().toString("hh:mm:ss")+tr(": 分组添加成功"));
      //  connect(opc->m_COPCTransaction,&COPCTransaction::destroyed,this,&ClientGui::Mdestroyed);
        connect(opc->m_COPCTransaction,SIGNAL(sg_OnDataChange(OPCHANDLE,DWORD,OPCHANDLE*,VARIANT*,WORD*,FILETIME*,HRESULT*, DWORD )),this,SLOT(sl_OnDataChange(OPCHANDLE,DWORD,OPCHANDLE*,VARIANT*,WORD*,FILETIME*,HRESULT*, DWORD)));
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
      //  ui->lineEdit_ERROR->setText("begin to init add opc items");
       on_pushButton_2_clicked();
    }
   }
void ClientGui::mtcpread()
{
    QByteArray marry=msock->readAll();
    qDebug()<<marry<<endl;
    QJsonDocument mjson=QJsonDocument::fromJson(marry);
    QJsonObject jsonobject=mjson.object();
    QString projectID=jsonobject.value("prjID").toString();
    if(projectID==this->read_tdta.prjID);
    {
        if(jsonobject.contains("tagName")&&jsonobject.contains("sdata"))
        {
            this->m_useID=jsonobject.value("userID").toString();
            this->m_kongID=jsonobject.value("kongID").toString();
                QString mname=jsonobject.value("tagName").toString().simplified();
                QString mvalue=jsonobject.value("sdata").toString().simplified();
                if(opc->isWriteAble&&!is_opc_error){
                    if(this->read_tdta.mitems_name.contains(mname))
                     {
                        int i=this->m_map[mname];
                        if(opc->ReadItem(opc->items->value(i)))
                        {
                            if(opc->WriteValue(mname,mvalue))
                            {
                              ui->tableWidget->item(i,1)->setText(mvalue);
                              ui->textEdit_opc->append("write:"+mname+":"+mvalue);
                              manswer_tcp(0,QString("1"),mname);
                            }
                            else
                               {
                                ui->textEdit_opc->append("write: + false : "+mname);
                                manswer_tcp(-1,QString("1"),mname);
                            }
                        }
                        else
                            manswer_tcp(-2,QString("1"),mname);
                    }
                }
        }
    }
}
void ClientGui::on_pushButton_tcp_server_connect_clicked()
{
    ui->textEdit_tcp->append(tr("read to connect host"));
    msock->connectToHost(ui->lineEdit_tcp_ip->text().simplified(),ui->lineEdit_tcp_port->text().simplified().toInt());
    connect(msock,&QTcpSocket::connected,this,&ClientGui::tcpsuccessfulconnect);
    connect(msock,&QTcpSocket::disconnected,this,&ClientGui::tcpdisconnect);
}
