#include "ui_mserialport.h"
#include"serialport/slavethread.h"
#include"serialport/mserialport.h"
mserialport::mserialport(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mserialport)
{
    ui->setupUi(this);
    const auto infos = QSerialPortInfo::availablePorts();
      for (const QSerialPortInfo &info : infos)
          ui->m_serialPortCombox->addItem(info.portName());
     connect(&m_thread, &SlaveThread::request, this,&mserialport::showRequest);
      connect(&m_thread, &SlaveThread::error, this, &mserialport::processError);
      connect(&m_thread, &SlaveThread::timeout, this, &mserialport::processTimeout);
  ui->spinBox->setRange(500,2000);
      connect(ui->m_serialPortCombox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
              this, &mserialport::activateRunButton);
     connect(ui->spinBox, QOverload<const QString &>::of(&QSpinBox::valueChanged),
              this, &mserialport::activateRunButton);
     connect(ui->lineEdit, &QLineEdit::textChanged, this, &mserialport::activateRunButton);
}
mserialport::~mserialport()
{
    delete ui;
}
void mserialport::showRequest(const QString &s)
{
    ui->label_traffic->setText(tr("Traffic, transaction #%1:"
                               "\n\r-request: %2"
                               "\n\r-response: %3")
                            .arg(++m_transactionCount)
                            .arg(s)
                            .arg(ui->lineEdit->text()));
}
void mserialport::processError(const QString &s)
{
    activateRunButton();
    ui->label_status->setText(tr("Status: Not running, %1.").arg(s));
    ui->label_traffic->setText(tr("No traffic."));
}

void mserialport::processTimeout(const QString &s)
{
    ui->label_status->setText(tr("Status: Running, %1.").arg(s));
   ui->label_traffic->setText(tr("No traffic."));
}

void mserialport::activateRunButton()
{
    ui->pushButton_start->setEnabled(true);
}
void mserialport::on_pushButton_start_clicked()
{
    ui->pushButton_start->setEnabled(false);
     ui->label_status->setText(
                 tr("Status: Running, connected to port %1.").
                 arg(ui->m_serialPortCombox->currentText())
                 );
    m_thread.startSlave(ui->m_serialPortCombox->currentText(),
                        ui->spinBox->value(),
                        ui->lineEdit->text());
}
