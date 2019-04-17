#ifndef SERIALNMEA_H
#define SERIALNMEA_H

//   @brief 罗经仪通信类

#include "serialcombase.h"
#include <QDateTime>

class serialNMEA : public SerialComBase
{
public:
    serialNMEA(stComConfig cfg);

protected :
    virtual void    run();
    void            sendAskMessage();

private:
    bool    m_bstop;
    QDateTime   m_time;

};

#endif // SERIALNMEA_H
