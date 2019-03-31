#include "shipitem.h"
#include <QPainter>
#include <QPoint>
#include <QtMath>
#include <QDebug>



ShipItem::ShipItem(QGraphicsItem *parent):QGraphicsPathItem(parent)
{

}

QRectF ShipItem::boundingRect() const
{
    return QRectF(-m_width/2.0,-m_height/2.0,m_width,m_height);
}

bool ShipItem::contains(const QPointF &point) const
{
    return false;
}

void ShipItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    countShip();
    painter->setPen(QPen(Qt::white,1));
    const static QPointF polygon[9] = {
        rotaryAngle(m_centerLeftShipPoint),
        rotaryAngle(m_centerRightShipPoint),
        rotaryAngle(m_headRightShipPoint),
        rotaryAngle(m_headShipPoint),
        rotaryAngle(m_headLeftShipPoint),
        rotaryAngle(m_centerLeftShipPoint),
        rotaryAngle(m_tailLeftShipPoint),
        rotaryAngle(m_tailRightShipPoint),
        rotaryAngle(m_centerRightShipPoint)
    };

    painter->drawPolygon(polygon, 9);

    gradientArc(painter,m_seaMileLength, 90 -m_angle - m_rightAngle ,-m_dxAngle,rotaryAngle(m_centerRightShipPoint),QColor(220,20,60));
    gradientArc(painter,m_seaMileLength, 90 -m_angle + m_leftAngle ,m_dxAngle,rotaryAngle(m_centerLeftShipPoint),QColor(0,255,255));
}

QPainterPath ShipItem::shape() const
{
    const QVector<QPointF> points;
    QPainterPath path;
    QPolygonF polygon;
    polygon.append(points);
    path.addPolygon(polygon);
    return path;
}

int ShipItem::type() const
{
    return 1;
}

QPointF ShipItem::centerPt() const
{
    return m_centerPt;
}

void ShipItem::setCenterPt(const QPointF &centerPt)
{
    m_centerPt = centerPt;
}



float ShipItem::fixSeaMile() const
{
    return m_fixSeaMile;
}

void ShipItem::setFixSeaMile(float fixSeaMile)
{
    m_fixSeaMile = fixSeaMile;
    m_seaMileLength = m_fixSeaMile*m_seaMile;

}

void ShipItem::countShip()
{
    
    m_headShipPoint = QPointF(m_centerPt.x(),m_centerPt.y()-m_height*m_headPercent);
    
    m_headLeftShipPoint = QPointF(m_centerPt.x() - m_width/2.0, m_centerPt.y() - (m_leftPercent*m_height));
    m_headRightShipPoint = QPointF(m_centerPt.x() + m_width/2.0, m_centerPt.y() - (m_leftPercent*m_height));

    m_centerLeftShipPoint = QPointF(m_centerPt.x() - m_width/2.0, m_centerPt.y() );
    m_centerRightShipPoint = QPointF(m_centerPt.x() + m_width/2.0, m_centerPt.y());

    m_tailLeftShipPoint = QPointF(m_centerPt.x() - m_width/2.0, (1-m_headPercent)*m_height );
    m_tailRightShipPoint = QPointF(m_centerPt.x() + m_width/2.0, (1-m_headPercent)*m_height);
}

QPointF ShipItem::rotaryAngle(QPointF lastPt)
{

    double angleHude = m_angle * M_PI / 180;
    float x = (lastPt.x() - m_centerPt.x())*qCos(angleHude) - (lastPt.y() - m_centerPt.y())*qSin(angleHude) + m_centerPt.x();

    float y = (lastPt.x() - m_centerPt.x())*qSin(angleHude) + (lastPt.y() - m_centerPt.y())*qCos(angleHude) + m_centerPt.y();

    return QPointF(x,y);
}

QPointF ShipItem::rotaryAngle(QPointF centerPt, QPointF lastPt, float angle)
{

    double angleHude = angle * M_PI / 180;
    float x = (lastPt.x() - centerPt.x())*qCos(angleHude) - (lastPt.y() - centerPt.y())*qSin(angleHude) + centerPt.x();

    float y = (lastPt.x() - centerPt.x())*qSin(angleHude) + (lastPt.y() - centerPt.y())*qCos(angleHude) + centerPt.y();

    return QPointF(x,y);
}

void ShipItem::gradientArc(QPainter *painter, int radius, int startAngle, int angleLength, QPointF centerPt, QColor color)
{



    QRectF rect(centerPt.x()-radius,centerPt.y()-radius ,2*radius,2*radius);

    painter->setPen(QPen(color,1));


    painter->drawPie(rect, startAngle * 16, angleLength * 16);
}
