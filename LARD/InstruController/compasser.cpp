#include "compasser.h"


Compasser::Compasser(stComConfig cfg):SerialComBase(cfg),m_bstop(false)
{

}

void Compasser::run()
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
                QStringList strs = msg.split(",");
                if(strs.size() > 2)
                {
                    m_HDT = strs.at(1).toInt();
                }
            }
        }
    }
}

void Compasser::sendAskMessage()
{
    QByteArray arr;
    arr = "HEHDT";
    m_serial->write(arr);
}
