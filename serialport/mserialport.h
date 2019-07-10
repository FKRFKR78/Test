#ifndef MSERIALPORT_H
#define MSERIALPORT_H
#include "slavethread.h"
#include<QMainWindow>
namespace Ui {
class mserialport;
}

class mserialport : public QMainWindow
{
    Q_OBJECT

public:
    explicit mserialport(QWidget *parent = nullptr);
    ~mserialport();

private slots:
    void on_pushButton_start_clicked();
    void showRequest(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void activateRunButton();
private:
    int m_transactionCount = 0;
    Ui::mserialport *ui;
    SlaveThread m_thread;
};

#endif // MSERIALPORT_H
