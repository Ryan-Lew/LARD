#ifndef RADAR_H
#define RADAR_H

#include <QObject>
#include "boost/smart_ptr.hpp"

class Serial422;
struct stConfig;
class TargetInfo;

class Radar
{
public:
    Radar();

    /**
     * @brief GetRadarInfo 获取雷达的目标信息
     * @return 目标信息
     */
    QVector<boost::shared_ptr<TargetInfo> > GetRadarInfo();

protected:
    void init();

private:
    boost::shared_ptr<stConfig>     m_config;
    boost::shared_ptr<Serial422>    m_pcomm;
};

#endif // RADAR_H
