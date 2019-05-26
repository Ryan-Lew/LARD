#include "radar.h"
#include "communication/serial422.h"
#include "commonstruct.h"
#include <QCoreApplication>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
//#include "gpio.h"

Radar::Radar()
{
    init();
}

void Radar::init()
{
    m_config = make_shared<stConfig>();
    QString configfile = QCoreApplication::applicationDirPath() + "/../config/config.json";
    property_tree::ptree ptr;
    property_tree::read_json(configfile.toStdString().c_str(), ptr);
    m_config->commcfg.port = ptr.get<int>("TTM.port");
    m_config->commcfg.baurate = ptr.get<int>("TTM.baudrate");
    m_config->commcfg.databit = ptr.get<int>("TTM.databit");
    m_pcomm = make_shared<Serial422>(m_config->commcfg);

//    IOCTL_GPIO_READ_PINS();
}

QVector<boost::shared_ptr<TargetInfo> > Radar::GetRadarInfo()
{
    QVector<shared_ptr<TargetInfo> > vectarget;
    QVector<QByteArray> vecorgdata;
    vecorgdata = m_pcomm->Getdata();
    for(auto a: vecorgdata)
    {
        QByteArray arr = a;
        QString msg = QString::fromStdString(arr.toStdString());
        QStringList splits = msg.split(",");
        if(splits.size() >= 15)
        {
            shared_ptr<TargetInfo> target = make_shared<TargetInfo>();
            QString batch = splits[1];
            QString speed = splits[5];      //节
            QString bearing = splits[2];    //方位
            Flag bearingflag;//方位标识
            if(splits[3] == QString("T"))
            {
                bearingflag = Flag::enum_Abs;
            }
            else
            {
                bearingflag = Flag::enum_Rel;
            }
            QString distance = splits[2];   //距离
            QString course = splits[6] ;    //航向
            Flag courseflag; //航向标识
            if(splits[7] == QString("T"))
            {
                courseflag = Flag::enum_Abs;
            }
            else
            {
                courseflag = Flag::enum_Rel;
            }
            target->batch = batch.toInt();
            target->speed = speed.toFloat();
            target->bearing = bearing.toFloat();
            target->bearingflag = bearingflag;
            target->distance = distance.toFloat();
            target->course  = course.toFloat();
            target->courseflag = courseflag;
            vectarget.append(target);
        }
    }
    return vectarget;
}
