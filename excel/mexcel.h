#ifndef MEXCEL_H
#define MEXCEL_H

#include <QMainWindow>
#include<QVariant>
#include<QScopedPointer>
#include <objbase.h>
#include <ActiveQt/QAxObject>
namespace Ui {
class mexcel;
}

class mexcel : public QMainWindow
{
    Q_OBJECT

public:
    explicit mexcel(QWidget *parent = nullptr);
    ~mexcel();
    /*
    bool close();
     //获取工作表数量
     int getSheetsCount();
     //根据名称创建工作表
     QAxObject* addSheet(QString name);
     //根据名称删除工作表
     bool delSheet(QString name);
     //根据编号删除工作表
     bool delSheet(int index);
     //根据名称获取工作表
     QAxObject* getSheet(QString name);
     //根据编号获取工作表
     QAxObject* getSheet(int index);
     //获取行对象
     QAxObject* getRows(QAxObject* pSheet);
     //获取行数
     int getRowsCount(QAxObject* pSheet);
     //获取列对象
     QAxObject* getColumns(QAxObject* pSheet);
     //获取列数
     int getColumnsCount(QAxObject* pSheet);
     //根据行列值获取单元格值, 如: 3行，5列
     QString getCell(QAxObject* pSheet, int row, int column);
     //根据行列编号获取单元格值, 如: "F6"
     QString getCell(QAxObject* pSheet, QString number);
     //根据行列值设置单元格值
     bool setCell(QAxObject* pSheet, int row, int column, QString value);
     //根据行列编号设置单元格值
     bool setCell(QAxObject* pSheet, QString number, QString value);
     */
     QVariant readAll(QAxObject *sheet);
     void castVariant2ListListVariant(const QVariant &var);
     void getmax_rows(const QVariant &var);
     void getmax_cols(const QVariant &var);
private slots:
    void on_pushButton_load_clicked();

    void on_pushButton_read_clicked();

private:
    Ui::mexcel *ui;
    QString filename;
    int max_rows;
    int max_cols;
};

#endif // MEXCEL_H
