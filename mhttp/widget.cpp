#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QMessageBox>
#include<QAuthenticator>
#include<QTime>
#include<QDir>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   //  ui->lineEdit_url->setText(tr("http://202.114.177.191/pyxx/login.aspx"));
     //this->mreply=new QNetworkReply;
  ui->lineEdit_url->setText(tr("http://www.weather.com.cn/data/sk/101200101.html"));
    m_manager=new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::authenticationRequired,
            this, &Widget::slotAuthenticationRequired);//验证身份
#ifndef QT_NO_SSL
    connect(m_manager, &QNetworkAccessManager::sslErrors,
            this, &Widget::sslErrors);//错误处理
#endif
    connect(m_manager,&QNetworkAccessManager::finished,this,&Widget::slot_replayFinished);
}
#ifndef QT_NO_SSL
void Widget::sslErrors(QNetworkReply *, const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }
    if (QMessageBox::warning(this, tr("SSL Errors"),
                             tr("One or more SSL errors has occurred:\n%1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        qDebug()<<errorString<<endl;
    }

}
#endif
void Widget::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator)//验证
{
    // Ui_Dialog mdialog;
     //QDialog mshow_dialog;
    mdialog.setupUi(&mshow_dialog);
    mdialog.label->setText(authenticator->realm()+"at"+murl.host());
    mdialog.lineEdit_user->setText(murl.userName());
    mdialog.lineEdit_password->setText(murl.password());
    if(mshow_dialog.exec()==QDialog::Accepted)
    {
        authenticator->setUser(mdialog.lineEdit_user->text().simplified());
        authenticator->setPassword(mdialog.lineEdit_password->text().simplified());
    }
}

void Widget::mshow_message()
{
  //  QJsonParseError jsonError;
    if(this->mjsonobject.contains("weatherinfo"))
    {
        QJsonValue value=mjsonobject.value("weatherinfo");
        if(value.isObject())
        {
            QJsonObject mobject=value.toObject();
            if(mobject.contains("city"))
            {
                QJsonValue strValue=mobject.value("city");
                qDebug()<<strValue.toString()<<endl;
            }
            if(mobject.contains("temp"))
            {
                QJsonValue strValue=mobject.value("temp");
                qDebug()<<strValue.toString()<<endl;
            }
        }
    }
    /*
     * QJsonParseError jsonError;

QJsonDocument doucment =QJsonDocument::fromJson(byteArray, &jsonError);  // 转化为 JSON 文档
if (!doucment.isNull() && (jsonError.error ==QJsonParseError::NoError)) {  // 解析未发生错误
    if(doucment.isObject()) {  // JSON 文档为对象
        QJsonObject object = doucment.object();  // 转化为对象
        if(object.contains("Name")) {
           QJsonValue value = object.value("Name");
            if(value.isString()) {
               QString strName = value.toString();
               qDebug() << "Name : " << strName;
            }
        }
        if(object.contains("Company")) {
           QJsonValue value = object.value("Company");
            if(value.isString()) {
               QString strCompany = value.toString();
                qDebug()<< "Company : " << strCompany;
            }
        }
        if(object.contains("From")) {
           QJsonValue value = object.value("From");
            if(value.isDouble()) {
                intnFrom = value.toVariant().toInt();
                qDebug() << "From : "<< nFrom;
            }
        }
        if(object.contains("Version")) {
           QJsonValue value = object.value("Version");
            if(value.isArray()) {  // Version 的 value 是数组
               QJsonArray array = value.toArray();
                intnSize = array.size();
                for(int i = 0; i < nSize; ++i) {
                   QJsonValue value = array.at(i);
                   if (value.isDouble()) {
                       double dVersion = value.toDouble();
                       qDebug() << "Version : " << dVersion;
                   }

                }

            }

        }

        if(object.contains("Page")) {

           QJsonValue value = object.value("Page");

            if(value.isObject()) {  // Page 的 value 是对象

               QJsonObject obj = value.toObject();

                if(obj.contains("Home")) {

                   QJsonValue value = obj.value("Home");

                   if (value.isString()) {

                       QString strHome =value.toString();

                       qDebug() << "Home : " << strHome;

                   }

                }

                if(obj.contains("Download")) {

                   QJsonValue value = obj.value("Download");

                    if (value.isString()) {

                       QString strDownload = value.toString();

                       qDebug() << "Download : " << strDownload;

                   }

                }

                if(obj.contains("Developers")) {

                   QJsonValue value = obj.value("Developers");

                   if (value.isString()) {

                       QString strDevelopers = value.toString();

                       qDebug() << "Developers : " << strDevelopers;

                    }

                }

            }

        }

    }

}
*/
}
QJsonObject Widget::mQStringtojson(QString jsonString)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
      if(jsonDocument.isNull())
      {
          qDebug()<< "String NULL"<< jsonString.toUtf8().data();
      }
      QJsonObject jsonObject = jsonDocument.object();
      return jsonObject;
}
void Widget::slot_replayFinished(QNetworkReply *reply)
{
   // QTextCodec *codec = QTextCodec::codecForName("utf8");
           //使用utf8编码, 这样可以显示中文
  //  this->mreply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //   QString str = codec->toUnicode(reply->readAll());
      // qDebug()<<"manger :"<<str<<endl;
    // ui->textBrowser->setText(str);
       reply->deleteLater();//最后要释放replay对象
}
Widget::~Widget()
{
    delete ui;
}
void Widget::on_readread()
{
    mfile->write(this->mreply->readAll());
   // qDebug()<<"mreplay "<<QString::fromUtf8(this->mreply->readAll())<<endl;
    qDebug()<<QTime::currentTime().toString("hh:mm:ss.zzz");
}
void Widget::on_DownloadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug()<<"toal :"<<bytesTotal<<",    send:    "<<bytesSent<<endl;
    qDebug()<<QTime::currentTime().toString("hh:mm:ss.zzz");
}
void Widget::on_replyfinished()
{
    qDebug()<<"this is finished"<<endl;
    qDebug()<<QTime::currentTime().toString("hh:mm:ss.zzz");
    mfile->close();
}
void Widget::init_file(QString filename)
{
    if (QFile::exists(filename)) {
        if (QMessageBox::question(this, tr("Overwrite Existing File"),
                                  tr("There already exists a file called %1 in "
                                     "the current directory. Overwrite?").arg(filename),
                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
            == QMessageBox::No)
            return;
        QFile::remove(filename);
    }
    this->mfile=new QFile(filename);
    if(!mfile->open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug()<<"error open";

}
void Widget::on_pushButton_clicked()
{
        murl = QUrl::fromUserInput(ui->lineEdit_url->text().simplified());
        ui->textBrowser->append(murl.fileName());
        ui->textBrowser->append(murl.path());
    if(murl.isValid())
    {
        init_file(murl.fileName());
        this->mreply=m_manager->get(QNetworkRequest(murl));
       connect(this->mreply,&QNetworkReply::readyRead,this,&Widget::on_readread);
       connect(mreply,&QNetworkReply::downloadProgress,this,&Widget::on_DownloadProgress);
       connect(mreply,&QNetworkReply::finished,this,&Widget::on_replyfinished);
    }
}
