#ifndef CONSOLECONTROL_H
#define CONSOLECONTROL_H

#include <QObject>

enum enumBTNCtl
{
    Ctl_AT_PORT = 0x01,     //左舷云台自动跟踪
    Ctl_AT_STBD = 0x02,     //右舷云台自动跟踪
    Ctl_PT_PORT = 0x03,     //左舷云台手动控制
    Ctl_PT_STBD = 0x04,     //右舷云台手动控制
    Ctl_MIC_PLAY = 0x05,    //麦克风音频回放
    Ctl_MIC_REC = 0x06,     //麦克风音频录制
    Ctl_WARNING = 0x07,     //选择警示音源类别
    Ctl_DEFENCE = 0x08,     //选择拒止音源类别
    Ctl_VOICE = 0x09,       //音频播放/暂停
    Ctl_STOP_BTN = 0x0A,    //停止音频
    Ctl_PREV = 0x0B,        //选择上一个音频文件
    Ctl_NEXT = 0x0C,        //选择下一个音频文件
    Ctl_LVOLINC = 0x0D,     //左舷音量增加
    Ctl_LVOLDES = 0x0E,     //左舷音量减少
    Ctl_RVOLINC = 0x0F,     //右舷音量增加
    Ctl_RVOLDES = 0x20,     //右舷音量减少
    Ctl_LRAD_POW = 0x21,    //右舷音量减少
};

enum enumIndicator
{
    In_AT_PORT = 0x22,      //左舷云台自动跟踪开
    In_AT_STBD = 0x23,      //右舷云台自动跟踪开
    In_PT_PORT = 0x24,      //左舷云台手动控制开
    In_PT_STBD = 0x25,      //右舷云台手动控制开
    In_MIC_EXIST = 0x26,    //麦克风录音存在
    In_MIC_PLAY = 0x27,     //麦克风音频回放中
    In_MIC_VOL = 0x28,      //麦克风音频接入
    In_MIC_REC = 0x29,      //麦克风音频录制
    In_WARNING = 0x2A,      //已选择警示音源类别
    In_DEFENCE = 0x2B,      //已选择拒止音源类别
    In_LRAD_POW = 0x2C,     //LRAD电源开启
};

enum enumRockBar
{
    RB_PAN = 0x32,  //云台水平转动
    TITLE = 0x33,   //云台俯仰转动
    ZOOM = 0x34,    //摄像机和补光灯变焦
};

enum enumOtherCtl
{
    WARNING = 0x2D,  //高速目标接近警告
};


class ConsoleControl:public QObject
{
    Q_OBJECT

public:
    ConsoleControl();

    void    onMessageHandler(QByteArray contant);



};

#endif // CONSOLECONTROL_H
