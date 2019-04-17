#ifndef SERIALCOMBASE_H
#define SERIALCOMBASE_H

#include <QObject>
#include <QThread>
#include "commonstruct.h"
#include "boost/smart_ptr.hpp"
#include <QtSerialPort/QSerialPort>

using namespace boost;

class SerialComBase : public QThread
{
public:
    SerialComBase(stComConfig cfg);
    virtual  ~SerialComBase();

protected:
    /**连接串口
     * @brief connectSerial
     */
    void    connectSerial();

protected:
    stComConfig    m_cfg;
    shared_ptr<QSerialPort>     m_serial;
};

#endif // SERIALCOMBASE_H
