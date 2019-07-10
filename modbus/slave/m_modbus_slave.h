#ifndef M_MODBUS_SLAVE_H
#define M_MODBUS_SLAVE_H

#include <QMainWindow>
namespace Ui {
class m_modbus_slave;
}

class m_modbus_slave : public QMainWindow
{
    Q_OBJECT

public:
    explicit m_modbus_slave(QWidget *parent = nullptr);
    ~m_modbus_slave();

private:
    Ui::m_modbus_slave *ui;
};

#endif // M_MODBUS_SLAVE_H
