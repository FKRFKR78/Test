#include "mexcel.h"
#include "ui_mexcel.h"
#include<QDir>
#include<QFileDevice>
#include<QFileDialog>
#include<QDebug>
#include<QMessageBox>
#include<stdio.h>
mexcel::mexcel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mexcel)
{
    ui->setupUi(this);
}

mexcel::~mexcel()
{
    delete ui;
}
void mexcel::on_pushButton_load_clicked()//打开文件
{
    QString curPath=QDir::currentPath();
    QString dlgfile=tr("select a file:");
    QString filter=tr(" 文本文件(*.txt);;excel(*.xls *.xlsx);;所有文件(*.*)");
    QString afilename=QFileDialog::getOpenFileName(this,dlgfile,curPath,filter);
    if(afilename.isEmpty())
        return;
    this->filename=afilename;
    ui->lineEdit_path->setText(afilename);

}
/*
bool mexcel::close()//关闭文件
{
    qDebug()<<"excel close...";
    if (m_pExcel)
    {
        qDebug()<<"closing...";
        m_pWorkbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filename));
        m_pWorkbook->dynamicCall("Close()");
        m_pExcel->dynamicCall("Quit()");
        delete m_pExcel;
        m_pExcel = NULL;
    }
    return true;
}
int mexcel::getSheetsCount()
{
    QAxObject *pWorkSheet = NULL;
    int snum=0;
    try {
        int count = m_pWorksheets->property("Count").toInt();  //获取工作表数目
        snum=count;
        QAxObject *pLastSheet = m_pWorksheets->querySubObject("Item(int)", count);
        pWorkSheet = m_pWorksheets->querySubObject("Add(QVariant)", pLastSheet->asVariant());
        pLastSheet->dynamicCall("Move(QVariant)", pWorkSheet->asVariant());
        pWorkSheet->setProperty("Name", filename);  //设置工作表名称
    } catch (...) {
        qCritical()<<"创建sheet失败...";
    }
    return snum;
}
bool mexcel::delSheet(QString name)
{
    try {
        QAxObject *pFirstSheet = m_pWorksheets->querySubObject("Item(QString)", name);
        pFirstSheet->dynamicCall("delete");
    } catch (...) {
        qCritical()<<"删除sheet失败...";
        return false;
    }
    return true;
}
bool mexcel::delSheet(int index)
{
    int count =  0;
    count = m_pWorksheets->property("Count").toInt();
    return count;
}
QAxObject* mexcel::addSheet(QString name)
{
    try {
        QAxObject *pFirstSheet = m_pWorksheets->querySubObject("Item(int)", index);
        pFirstSheet->dynamicCall("delete");
    } catch (...) {
        qCritical()<<"删除sheet失败...";
        return false;
    }
    return true;
}
QAxObject* mexcel::getSheet(QString name)
{
    QAxObject* pWorkSheet = NULL;
    try {
        pWorkSheet = m_pWorksheets->querySubObject("Item(QString)", name);
    } catch (...) {
        qCritical()<<"获取sheet失败...";
    }
    return pWorkSheet;
}

QAxObject* mexcel::getSheet(int index)
{
    QAxObject* pWorkSheet = NULL;
    try {
        pWorkSheet = m_pWorksheets->querySubObject("Item(int)", index);
    } catch (...) {
        qCritical()<<"获取sheet失败...";
    }
    return pWorkSheet;
}

QAxObject* mexcel::getRows(QAxObject* pSheet)
{
    QAxObject* pRows = NULL;
    try {
        pRows = pSheet->querySubObject("Rows");
    } catch (...) {
        qCritical()<<"获取行失败...";
    }
    return pRows;
}

int mexcel::getRowsCount(QAxObject* pSheet)
{
    int rows = 0;
    try {
        QAxObject* pRows = getRows(pSheet);
        rows = pRows->property("Count").toInt();
    } catch (...) {
        qCritical()<<"获取行数失败...";
    }
    return rows;
}

QAxObject* mexcel::getColumns(QAxObject* pSheet)
{
    QAxObject* pColumns = NULL;
    try {
        pColumns = pSheet->querySubObject("Columns");
    } catch (...) {
        qCritical()<<"获取列失败...";
    }
    return pColumns;
}

int mexcel::getColumnsCount(QAxObject* pSheet)
{
    int columns = 0;
    try {
        QAxObject* pColumns = getColumns(pSheet);
        columns = pColumns->property("Count").toInt();
    } catch (...) {
        qCritical()<<"获取列数失败...";
    }
    return columns;
}

QString mexcel::getCell(QAxObject* pSheet, int row, int column)
{
    QString strCell = "";
    try {
        QAxObject* pCell = pSheet->querySubObject("Cells(int, int)", row, column);
        strCell = pCell->property("Value").toString();
    } catch (...) {
        qCritical()<<"获取单元格信息失败...";
    }

    return strCell;
}

QString mexcel::getCell(QAxObject* pSheet, QString number)
{
    QString strCell = "";
    try {
        QAxObject* pCell = pSheet->querySubObject("Range(QString)", number);
        strCell = pCell->property("Value").toString();
    } catch (...) {
        qCritical()<<"获取单元格信息失败...";
    }

    return strCell;
}

bool mexcel::setCell(QAxObject* pSheet, int row, int column, QString value)
{
    try {
        QAxObject* pCell = pSheet->querySubObject("Cells(int, int)", row, column);
        pCell->setProperty("Value", value);
    } catch (...) {
        qCritical()<<"写入单元格信息失败...";
        return false;
    }
    return true;
}

bool mexcel::setCell(QAxObject* pSheet, QString number, QString value)
{
    try {
        QAxObject* pCell = pSheet->querySubObject("Range(QString)", number);
        pCell->setProperty("Value", value);
    } catch (...) {
        qCritical()<<"写入单元格信息失败...";
        return false;
    }
    return true;
}
*/
void mexcel::on_pushButton_read_clicked()
{

    QAxObject excel("Excel.Application");
        excel.setProperty("Visible", false);
        QAxObject *work_books = excel.querySubObject("WorkBooks");
        work_books->dynamicCall("Open(const QString&)", filename);
        QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
        QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets
        int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
        if (sheet_count > 0)
        {
            QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);

            QVariant var = readAll(work_sheet);
            castVariant2ListListVariant(var);
        }
        work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
        excel.dynamicCall("Quit(void)");  //退出
}
void mexcel::getmax_rows(const QVariant &var)
{
    this->max_rows=var.toList().size();
}
void mexcel::getmax_cols(const QVariant &var)
{
    int num=-10;
    for(int i=0;i<max_rows;i++)
    {
        QVariantList varRows = var.toList();
        if(num<=varRows[i].toList().size())
            num=varRows[i].toList().size();
    }
    this->max_cols=num;
}
QVariant mexcel::readAll(QAxObject *sheet)
{
    QVariant var;
    if (sheet != NULL && !sheet->isNull())
    {
        QAxObject *usedRange = sheet->querySubObject("UsedRange");
        if (NULL == usedRange || usedRange->isNull())
        {
            return var;
        }
        var = usedRange->dynamicCall("Value");
        delete usedRange;
    }
    return var;
}

void mexcel::castVariant2ListListVariant(const QVariant &var)
{
    QVariantList varRows = var.toList();
   // qDebug()<<varRows<<endl;
//    qDebug()<<varRows.size()<<endl;
  //  qDebug()<<varRows[0].toList().size()<<endl;
    getmax_rows(var);
    getmax_cols(var);
    QStringList headers;
    for (int i=0 ;i< this->max_cols;i++)
    {
        QString value =QString::number(i);
        headers.append(value);
    }
    ui->tableWidget->setColumnCount(this->max_cols); //设置列数
    ui->tableWidget->setRowCount(this->max_rows);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    for (int i=0;i<max_rows;i++) {
        for(int j=0;j<varRows[i].toList().size();j++)
        {
            QString value = varRows[i].toList()[j].toString();
            QTableWidgetItem *item = new QTableWidgetItem(value);
            ui->tableWidget->setItem(i, j, item);
        }
    }
    /*
    if (varRows.isEmpty())
    {
        return;
    }
   const int rowCount = varRows.size();
    QVariantList rowData;
    for (int i = 0; i < rowCount; ++i)
    {
        rowData = varRows[i].toList();
        if (i == 0)
        {
            QStringList headers;
            for (auto item : rowData)
            {
                QString value = item.toString();
                headers.append(value);
            }
            ui->tableWidget->setColumnCount(headers.size()); //设置列数
            ui->tableWidget->setHorizontalHeaderLabels(headers);
        }
        else
        {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->setRowCount(row + 1);
            for (int j = 0; j < rowData.size(); j++)
            {
                QString value = rowData[j].toString();
                QTableWidgetItem *item = new QTableWidgetItem(value);
                ui->tableWidget->setItem(row, j, item);
            }
        }
    }
    */
}
