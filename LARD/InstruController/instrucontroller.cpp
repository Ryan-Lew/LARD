#include "instrucontroller.h"
#include "cloud.h"
#include "radar.h"

InstruController::InstruController()
{
    init();
}

void InstruController::onSetSpeed(int speed)
{
    m_pcloud->onSpeedLevel(speed);
}

void InstruController::onMoveLeft()
{
    m_pcloud->MoveStilLeft();
}

void InstruController::onMoveRight()
{
    m_pcloud->MoveStilRight();
}

void InstruController::onMoveUp()
{
    m_pcloud->MoveStilUp();
}

void InstruController::onMoveDown()
{
    m_pcloud->MoveStilDown();
}

void InstruController::onMoveAngleH(float angle)
{
    m_pcloud->MoveHorizon(angle);
}

void InstruController::onMoveAngleV(float angle)
{
    m_pcloud->MoveVertical(angle);
}

void InstruController::onStop()
{
    m_pcloud->StopMoving();
}

void InstruController::SetLeftLmt(float val)
{
    m_pcloud->SetLeftLmt(val);
}

void InstruController::SetRightLmt(float val)
{
    m_pcloud->SetRightLmt(val);
}

void InstruController::SetUpLmt(float val)
{
    m_pcloud->SetUpLmt(val);
}

void InstruController::SetDownLmt(float val)
{
    m_pcloud->SetDownLmt(val);
}

void InstruController::Reset()
{
    m_pcloud->Reset();
}

void InstruController::MoveToZero()
{
    m_pcloud->MoveToZero();
}

void InstruController::onRadarTimeout()
{
    QVector<boost::shared_ptr<TargetInfo> > vectargets = m_pradar->GetRadarInfo();
    for(auto &tmp:vectargets)
    {
        boost::shared_ptr<TargetInfo> ptarget  = tmp;
        emit RadarTargetReport(ptarget);
    }
}


void InstruController::init()
{
    stComConfig cfg ;
    cfg.port = "com6";  //端口
    cfg.baurate = "9600"; //波特率
    cfg.databit = "8"; //数据位
    cfg.parity = ""; //校验位
    cfg.stopbit = "1"; //停止位
    m_pcloud = boost::make_shared<Cloud>(cfg);

    m_pradar = boost::make_shared<Radar>();
    m_pradartimer = boost::make_shared<QTimer>();
    connect(m_pradartimer.get(), SIGNAL(timeout()), this , SLOT(onRadarTimeout()));

}
