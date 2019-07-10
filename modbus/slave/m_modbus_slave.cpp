#include "m_modbus_slave.h"
#include "ui_m_modbus_slave.h"

m_modbus_slave::m_modbus_slave(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::m_modbus_slave)
{
    ui->setupUi(this);
}

m_modbus_slave::~m_modbus_slave()
{
    delete ui;
}
