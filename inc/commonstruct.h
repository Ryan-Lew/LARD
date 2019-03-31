#ifndef COMMONSTRUCT_H
#define COMMONSTRUCT_H

#include <QString>

enum Flag
{
    enum_Abs=0,  //绝对
    enum_Rel=1,  //相对
};

struct stComConfig
{
    QString    port;  //端口
    QString    baurate; //波特率
    QString    databit; //数据位
    QString    parity; //校验位
    QString    stopbit; //停止位
    QString    flowcontrol;//控制流
    ComConfig() {}
};

struct stConfig
{
    stComConfig  commcfg;

    Config() {}
};

struct TargetInfo
{
    int     batch;      //编号
    float   speed;      //节
    float   bearing;    //方位
    Flag    bearingflag;//方位标识
    float   distance;   //距离
    float   course ;    //航向
    Flag    courseflag; //航向标识

    TargetInfo() {}

};


#endif // COMMONSTRUCT_H
