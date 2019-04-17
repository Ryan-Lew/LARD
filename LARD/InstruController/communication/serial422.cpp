#include "serial422.h"

Serial422::Serial422(stComConfig cfg):SerialComBase(cfg),m_bstop(false)
{

}

Serial422::~Serial422()
{

}

QVector<QByteArray> Serial422::GetTTMdata()
{
    QVector<QByteArray> arr;
    m_lock.lock();
    arr = m_arrdata;
    m_arrdata.clear();
    m_lock.unlock();
    return arr;
}

void Serial422::readData()
{
    QByteArray data;
    data = m_serial->readAll();
    if(!data.isEmpty())
    {
        m_lock.lock();
        m_arrdata.append(data);
        m_lock.unlock();
    }
}

void Serial422::sendData(QByteArray data)
{
    m_serial->write(data);
}

void Serial422::run()
{
    connectSerial();

    while (!m_bstop)
    {
        readData();
    }
}

