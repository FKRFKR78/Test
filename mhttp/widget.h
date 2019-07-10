#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QWidget>
#include <QTextCodec>
#include <QString>
#include <QUrl>
#include<QJsonDocument>
#include<qjsonobject.h>
#include<QJsonArray>
#include<QFile>
#include"ui_mdialog.h"
namespace Ui {
class Widget;

}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
 private slots:
    void slot_replayFinished(QNetworkReply *reply);
    void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);
#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
#endif
    void on_pushButton_clicked();
    void on_readread();
    void on_DownloadProgress(qint64 bytesSent, qint64 bytesTotal);
    void on_replyfinished();
private:
    Ui::Widget *ui;
    QUrl murl;
    QFile *mfile;
    Ui_Dialog mdialog;
    QNetworkReply *mreply;
    QDialog mshow_dialog;
    QJsonObject mQStringtojson(QString str);
    QNetworkAccessManager *m_manager;
     QJsonObject mjsonobject;
     void mshow_message();
     void init_file(QString filename);
};

#endif // WIDGET_H
