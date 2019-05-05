#include "cloud.h"

Cloud::Cloud(stComConfig cfg):Serial422(cfg),m_speedlevel(2)
{
    SetSpeed();
}


void Cloud::onSpeedLevel(int level)
{
    m_speedlevel = level;
    SetSpeed();
}


char Cloud::getLevelSpeed()
{
    switch (m_speedlevel) {
    case 1:
    {
        return 0x04;
        break;
    }
    case 2:
    {
        return 0x08;
        break;
    }
    case 3:
    {
        return 0x0C;
        break;
    }
    case 4:
    {
        return 0x10;
        break;
    }
    case 5:
    {
        return 0x13;
        break;
    }
    default:
        break;
    }
}

char Cloud::getPitchSpeed()
{
    switch (m_speedlevel) {
    case 1:
    {
        return 0x01;
        break;
    }
    case 2:
    {
        return 0x03;
        break;
    }
    case 3:
    {
        return 0x05;
        break;
    }
    case 4:
    {
        return 0x07;
        break;
    }
    case 5:
    {
        return 0x09;
        break;
    }
    default:
        break;
    }
}


void Cloud::MoveStilRight()
{
    QByteArray arr;
    char speed = getLevelSpeed();
    char check = (0x01 + 0x00 +  0x02 + speed) & 0xFF;
    arr.append(0xff);
    arr.append(0x01);
    arr.append((char)0x00);
    arr.append(0x02);
    arr.append(speed);
    arr.append((char)0x00);
    arr.append(check);
    sendData(arr);
}

void Cloud::MoveStilLeft()
{
    QByteArray arr;
    char speed = getLevelSpeed();
    char check = (0x01 + 0x00 +  0x04 + speed) & 0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x04).append(speed).append((char)0x00).append(check);
    sendData(arr);
}

void Cloud::MoveStilUp()
{
    QByteArray arr;
    char speed = getPitchSpeed();
    char check = (0x01 +  0x08 + speed) & 0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x08).append((char)0x00).append(speed).append(check);
    sendData(arr);
}

void Cloud::MoveStilDown()
{
    QByteArray arr;
    char speed = getPitchSpeed();
    char check = (0x01 +  0x10 + speed) & 0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x10).append((char)0x00).append(speed).append(check);
    sendData(arr);
}

void Cloud::StopMoving()
{
    QByteArray arr;
    arr.append(0xFF).append(0x01).append((char)0x00).append((char)0x00).append((char)0x00).append((char)0x00).append(0x01);
    sendData(arr);
}


void Cloud::SetSpeed()
{
    QByteArray arr;
    char levelspeed = getLevelSpeed();
    char pitchspeed = getPitchSpeed();
    char check = (0x01+0x45+levelspeed) & 0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x45).append((char)0x00).append(levelspeed).append(check);
    sendData(arr);
    arr.clear();
    check = (0x01+0x47+pitchspeed) & 0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x47).append((char)0x00).append(pitchspeed).append(check);
    sendData(arr);
}

void Cloud::MoveHorizon(float val)
{
    int angle = val*100;
    QByteArray arr;
    char low = angle;
    char high = angle >> 8;
    char check = (0x01+0x41+high+low)&0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x41).append(high).append(low).append(check);
    sendData(arr);
}

void Cloud::MoveVertical(float val)
{
    int angle = (val + 180)*100;
    QByteArray arr;
    char low = angle;
    char high = angle >> 8;
    char check = (0x01+0x43+high+low)&0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x43).append(high).append(low).append(check);
    sendData(arr);
}

void Cloud::SetLeftLmt(float val)
{
    int angle = val*100;
    QByteArray arr;
    char low = angle;
    char high = angle >> 8;
    char check = (0x01+0x31+high+low)&0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x31).append(high).append(low).append(check);
    sendData(arr);
}

void Cloud::SetRightLmt(float val)
{
    int angle = val*100;
    QByteArray arr;
    char low = angle;
    char high = angle >> 8;
    char check = (0x01+0x33+high+low)&0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x33).append(high).append(low).append(check);
    sendData(arr);
}

void Cloud::SetUpLmt(float val)
{
    int angle = val*100;
    QByteArray arr;
    char low = angle;
    char high = angle >> 8;
    char check = (0x01+0x35+high+low)&0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x35).append(high).append(low).append(check);
    sendData(arr);
}

void Cloud::SetDownLmt(float val)
{
    int angle = val*100;
    QByteArray arr;
    char low = angle;
    char high = angle >> 8;
    char check = (0x01+0x37+high+low)&0xFF;
    arr.append(0xFF).append(0x01).append((char)0x00).append(0x37).append(high).append(low).append(check);
    sendData(arr);
}

void Cloud::Reset()
{
    QByteArray arr;
    arr.append(0xFF).append(0x01).append((char)0x00).append((char)0x07).append((char)0x00).append((char)0x22).append(0x2A);
    sendData(arr);
}

void Cloud::MoveToZero()
{
    QByteArray arr;
    arr.append(0xFF).append(0x01).append((char)0x00).append((char)0x07).append((char)0x00).append((char)0x23).append(0x2B);
    sendData(arr);
}

