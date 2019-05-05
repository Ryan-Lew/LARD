#ifndef CLOUD_H
#define CLOUD_H

#include "communication/serial422.h"

#define  unsigned short  UnShort

class Cloud : public Serial422
{
public:
    Cloud(stComConfig cfg);

    void    MoveStilRight(); //右移
    void    MoveStilLeft();  //左移
    void    MoveStilUp();  //上移
    void    MoveStilDown(); //下移
    void    StopMoving(); //停止移动
    void    MoveHorizon(float val); //移动一定角度
    //void    MoveHorizonL(short angle); //向右移动一定角度
    void    MoveVertical(float val); //垂直移动一定角度
    //void    MoveVerticalDn(short angle); //向下移动一定角度
    void    onSpeedLevel(int level);
    void    SetLeftLmt(float val);
    void    SetRightLmt(float val);
    void    SetUpLmt(float val);
    void    SetDownLmt(float val);
    void    Reset();
    void    MoveToZero();

public slots:
    //void    onSpeedLevel(int level);

private:
    char    getLevelSpeed(); //获取水平速度
    char    getPitchSpeed(); //获取俯仰速度
    void    SetSpeed();

private:
    int     m_speedlevel;


};

#endif // CLOUD_H
