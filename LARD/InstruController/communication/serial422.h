#ifndef SERIAL422_H
#define SERIAL422_H

#include "serialcombase.h"

/** RS422通信
 * @brief The Serial422 class
 */

#include <QVector>
#include <QMutex>

class Serial422:public SerialComBase
{
    Q_OBJECT

public:
    Serial422(stComConfig cfg);
    virtual  ~Serial422();

    void    SetStopRun(){m_bstop=true;}
    QVector<QByteArray>     Getdata();


protected:
    void    readData();
    void    sendData(QByteArray data);
    virtual void    run();

private:
    QMutex      m_lock;
    bool        m_bstop;
    QVector<QByteArray>  m_arrdata;

};

#endif // SERIAL422_H
