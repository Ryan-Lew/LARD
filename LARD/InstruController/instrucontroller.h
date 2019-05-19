#ifndef INSTRUCONTROLLER_H
#define INSTRUCONTROLLER_H
#include <QObject>
#include "boost/smart_ptr.hpp"
#include "instrucontroller_global.h"
#include <QTimer>

class Cloud;
class Radar;
class TargetInfo;

class INSTRUCONTROLLERSHARED_EXPORT InstruController:public QObject
{
    Q_OBJECT

public:
    InstruController();

public slots:
    //////////////////////转台控制///////////////////////////////
    void    onSetSpeed(int speed);
    void    onMoveLeft();
    void    onMoveRight();
    void    onMoveUp();
    void    onMoveDown();
    void    onMoveAngleH(float angle);
    void    onMoveAngleV(float angle);
    void    onStop();

    void    SetLeftLmt(float val);
    void    SetRightLmt(float val);
    void    SetUpLmt(float val);
    void    SetDownLmt(float val);
    void    Reset();
    void    MoveToZero();

    //////////////////////雷达目标///////////////////////////////////
    void    onRadarTimeout();

signals:
    void    RadarTargetReport(boost::shared_ptr<TargetInfo> target); //雷达目标上报

private:
    void    init();

private:
    boost::shared_ptr<Cloud>    m_pcloud;
    boost::shared_ptr<Radar>    m_pradar;
    boost::shared_ptr<QTimer>  m_pradartimer;

};

#endif // INSTRUCONTROLLER_H
