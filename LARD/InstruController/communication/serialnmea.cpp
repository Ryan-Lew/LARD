#include "serialnmea.h"

serialNMEA::serialNMEA(stComConfig cfg):SerialComBase(cfg),m_bstop(false)
{

}

void serialNMEA::run()
{
    connectSerial();

    while (!m_bstop)
    {
        QThread::sleep(3);
        sendAskMessage();
        QByteArray data;
        data = m_serial->readAll();
        if(!data.isEmpty())
        {
            QString msg = QString().fromStdString(data.toStdString());
            if(msg.startsWith("--HDT"))
            {
                
            }
        }
    }
}

void serialNMEA::sendAskMessage()
{
    QByteArray arr;
    arr = "HEHDT";
    m_serial->write(arr);
}


