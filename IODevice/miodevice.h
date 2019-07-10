#ifndef MIODEVICE_H
#define MIODEVICE_H

#include <QMainWindow>
#include<QFileDialog>
#include<QFile>
#include<QFileDevice>
#include<iostream>
#include<QByteArray>
namespace Ui {
class miodevice;
}

class miodevice : public QMainWindow
{
    Q_OBJECT

public:
    explicit miodevice(QWidget *parent = nullptr);
    ~miodevice();

private slots:
    void on_pushButton_load_clicked();
    
    void on_pushButton_write_clicked();
    
    void on_pushButton_read_clicked();
    
private:
    Ui::miodevice *ui;
    QString path;
};

#endif // MIODEVICE_H
