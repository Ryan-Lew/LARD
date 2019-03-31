#include "radarscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QString>
#include <QStringLiteral>
#include <QGraphicsItem>
#include <QDebug>
#include "shipitem.h"
#include "enemyshipitem.h"

RadarScene::RadarScene(QObject *parent):QGraphicsScene(parent)
{

}

void RadarScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void RadarScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void RadarScene::drawBackground(QPainter *painter, const QRectF &rect)
{

    //�����
    painter->setRenderHint(QPainter::Antialiasing, true);
    updateRadar(rect);
    painter->save();
    painter->fillRect(rect,QBrush(Qt::black));
    //�����״�Ȧ
    for(int i =0;i<m_radarRings.size();i++){
        auto w = m_radarRings.at(i);

            painter->setPen(QPen(m_radarLineColor,1));
            painter->drawEllipse(-w,-w,2*w,2*w);


    }
    painter->setPen(QPen(m_radarLineColor,1));
    //����ֱ��
    painter->drawLine(m_radarTopPoint,m_radarBottomPoint);
    painter->drawLine(m_radarLeftPoint,m_radarRightPoint);
    //���ƿ̶ȳ�
    for (auto w : m_scaleLists)
    {
        painter->drawLine(QPoint(0.0,w),QPoint(m_scaleWidth,w));
        painter->drawLine(QPoint(0.0,-w),QPoint(m_scaleWidth,-w));
        painter->drawLine(QPoint(w,0),QPoint(w,-m_scaleWidth));
        painter->drawLine(QPoint(-w,0),QPoint(-w,-m_scaleWidth));
    }

    //���ƿ̶ȳ�����ľ��徫��
    QFontMetrics mit(painter->font());
    for(int i =0;i<m_scaleLists.size()-1;i++)
    {
        auto text = QString("%1").arg((2.0*m_splitMile-i-1)/(2*m_splitMile)*m_seaMile);
        auto w = m_scaleLists.at(i);
        {
            painter->save();
            QSize nSize= mit.size( Qt::TextSingleLine , text);
            painter->translate(QPoint(0.0,w));
            painter->rotate(270);
            painter->drawText(QPoint(-nSize.width()/2,-nSize.height()/2), text);
            painter->restore();
        }
        {
            painter->save();
            QSize nSize= mit.size( Qt::TextSingleLine , text);
            painter->translate(QPoint(0.0,-w));
            painter->rotate(270);
            painter->drawText(QPoint(-nSize.width()/2,-nSize.height()/2), text);
            painter->restore();
        }
        {
            painter->save();
            QSize nSize= mit.size( Qt::TextSingleLine , text);
            painter->translate(QPoint(w,0));

            painter->drawText(QPoint(-nSize.width()/2,nSize.height()), text);
            painter->restore();
        }
        {
            painter->save();
            QSize nSize= mit.size( Qt::TextSingleLine , text);
            painter->translate(QPoint(-w,0));

            painter->drawText(QPoint(-nSize.width()/2,nSize.height()), text);
            painter->restore();
        }

    }
    if(m_dictSwitch){
        painter->save();
        painter->setBrush(Qt::black);
        painter->setPen(QPen(m_radarLineColor,2));
        QFont font;
        font.setPixelSize(16);
        painter->setFont(font);
        foreach (QString key, m_northMap.keys()) {
            painter->drawRect(m_northMap[key]);
            painter->drawText(m_northMap[key],key,Qt::AlignHCenter|Qt::AlignVCenter);
        }
        painter->restore();

    }else{
        //����ԲȦ����ĽǶ�
        for(auto var : m_angleMap){
           //painter->setPen(QPen(m_radarLineCenterColor,1));
           //painter->drawLine(var.startPt(),QPointF(0.0,0.0));
           painter->setPen(QPen(m_radarLineColor,3));
           painter->drawLine(var.startPt(),var.endPt());
        }
        //����ԲȦ�ϵĽǶ���Ϣ
        painter->setPen(QPen(m_radarLineColor,1));

        for(auto var : m_angleMap)
        {
            painter->save();
            QSize nSize= mit.size( Qt::TextSingleLine , var.text());
            painter->translate(var.startPt());
            painter->rotate(var.angle());
            painter->drawText(QPoint(-nSize.width()/2,-nSize.height()/2), var.text());
            painter->restore();
        }

    }
    //���ƾ�ֹ���� ����
    painter->setPen(QPen(Qt::red,1));
    auto denial_w = m_denialSeaMile*m_fixSeaMile;
    painter->drawEllipse(-denial_w,-denial_w,2*denial_w,2*denial_w);
    //���ƾ������ ����
    painter->setPen(QPen(Qt::white,1));
    auto warning_w = m_warningSeaMile*m_fixSeaMile;
    painter->drawEllipse(-warning_w,-warning_w,2*warning_w,2*warning_w);
    //��Բ
    painter->restore();
}

void RadarScene::updateRadar(const QRectF &rect)
{

    //���°뾶
    m_radarRings.clear();

    float width = rect.width()/2 - m_padding;
    float height = rect.height()/2 - m_padding;
    //���´�С
    m_fixRadius = this->width()/2 - m_padding;
    //����ÿһ���������ֵ
    m_fixSeaMile = m_fixRadius/m_seaMile;

    //ÿһ�εı仯
    float dx = width/m_splitMile;
    for (float i = width;i>0;i-=dx){
        m_radarRings.append(i);
    }
    //�����״�Ȧ����ĵ�
    m_radarTopPoint = QPointF(0.0,-height);
    m_radarBottomPoint= QPointF(0.0,height);
    m_radarLeftPoint= QPointF(-width,0.0);
    m_radarRightPoint= QPointF(width,0.0);
    //���¿̶ȵ���Ϣ
    float scale_dx = width/(m_splitMile*2);
    m_scaleLists.clear();
    for (float i = width;i>0;i-=scale_dx){
        if (i != width)
        {
            m_scaleLists.append(i);
        }
    }

    //���½Ƕ�����
    float radius = width;
    int angle_count = 360/m_angle;
    m_angleMap.clear();
    for (int i=0;i<angle_count;i++){

        float rad = qDegreesToRadians(static_cast<float>(540-i*m_angle));

        float x =radius*qSin(static_cast<qreal>(rad));
        float y = radius*qCos(static_cast<qreal>(rad));

        float x1 = (radius - m_scaleWidth)*qSin(static_cast<qreal>(rad));
        float y1 = (radius - m_scaleWidth)*qCos(static_cast<qreal>(rad));
        QString text  = QString("%1").arg(i*m_angle) ;

        RadarAngleInfo info;
        info.setStartPt(QPointF(x,y));
        info.setEndPt(QPointF(x1,y1));
        info.setText(text);
        info.setAngle(i*m_angle);
        m_angleMap.append(info);
    }

    m_northMap.clear();
    m_northMap[QStringLiteral("N")] = QRectF(m_radarTopPoint.x() - m_northWidth/2,m_radarTopPoint.y() - m_northHeight/2,m_northWidth,m_northHeight);
    m_northMap[QStringLiteral("W")] = QRectF(m_radarBottomPoint.x() - m_northWidth/2,m_radarBottomPoint.y() - m_northHeight/2,m_northWidth,m_northHeight);
    m_northMap[QStringLiteral("S")] = QRectF(m_radarLeftPoint.x() - m_northWidth/2,m_radarLeftPoint.y() - m_northHeight/2,m_northWidth,m_northHeight);
    m_northMap[QStringLiteral("E")] = QRectF(m_radarRightPoint.x() - m_northWidth/2,m_radarRightPoint.y() - m_northHeight/2,m_northWidth,m_northHeight);


    updateItem();
}

bool RadarScene::dictSwitch() const
{
    return m_dictSwitch;
}

void RadarScene::setDictSwitch(bool dictSwitch)
{
    m_dictSwitch = dictSwitch;
}



float RadarScene::seaMile() const
{
    return m_seaMile;
}

void RadarScene::setSeaMile(float seaMile)
{
    m_seaMile = seaMile;
}

void RadarScene::updateItem()
{

    foreach (QGraphicsItem *item, items())
    {

        //���±�����Ϣ
        if (item->type() == 1)
        {

            ShipItem* _item = nullptr;
            _item = (ShipItem*)item;
            if(_item!= nullptr){
                _item->setFixSeaMile(m_fixSeaMile);
            }
        }

        if (item->type() == 2)
        {
            EnemyShipItem* _item = nullptr;
            _item = (EnemyShipItem*)item;
            if(_item!= nullptr){
                _item->setFixSeaMile(m_fixSeaMile);
            }
        }
    }

}

QPointF RadarAngleInfo::startPt() const
{
    return m_startPt;
}

void RadarAngleInfo::setStartPt(const QPointF &startPt)
{
    m_startPt = startPt;
}

QPointF RadarAngleInfo::endPt() const
{
    return m_endPt;
}

void RadarAngleInfo::setEndPt(const QPointF &endPt)
{
    m_endPt = endPt;
}

QString RadarAngleInfo::text() const
{
    return m_text;
}

void RadarAngleInfo::setText(const QString &text)
{
    m_text = text;
}

QRectF RadarAngleInfo::rect() const
{
    QRectF m_rect(m_startPt.x() -  width/2,m_startPt.y() - height,width,height);
    return m_rect;
}

float RadarAngleInfo::angle() const
{
    return m_angle;
}

void RadarAngleInfo::setAngle(float angle)
{
    m_angle = angle;
}

