#include "serialcombase.h"

SerialComBase::SerialComBase(stComConfig cfg):m_cfg(cfg), m_serial(nullptr)
{
    connectSerial();
}

SerialComBase::~SerialComBase()
{

}

void SerialComBase::connectSerial()
{
    if(m_serial != nullptr && m_serial->isOpen())
    {
        m_serial->close();
        QThread::sleep(1);
    }

    m_serial = make_shared<QSerialPort>();
    m_serial->setPortName(m_cfg.port);
    m_serial->open(QIODevice::ReadWrite);
    m_serial->setBaudRate(m_cfg.baurate.toInt());
    switch (m_cfg.databit.toInt())
    {
        case 5:
        {
            m_serial->setDataBits(QSerialPort::Data5);
            break;
        }
        case 6:
        {
            m_serial->setDataBits(QSerialPort::Data6);
            break;
        }
        case 7:
        {
            m_serial->setDataBits(QSerialPort::Data7);
            break;
        }
        case 8:
        {
            m_serial->setDataBits(QSerialPort::Data8);
            break;
        }
        default:
            break;
    }
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

}
