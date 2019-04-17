#ifndef COMPASSER_H
#define COMPASSER_H

#include "communication/serialcombase.h"
#include <QDateTime>
#include <QObject>

class Compasser : public SerialComBase
{
public:
    Compasser(stComConfig cfg);

protected :
    virtual void    run();
    void            sendAskMessage();

private:
    float   m_HDT;
    bool    m_bstop;
    QDateTime   m_time;
};

#endif // COMPASSER_H
