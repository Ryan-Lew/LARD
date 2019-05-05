#include "shipitem.h"
#include <QPainter>
#include <QPoint>
#include <QtMath>
#include <QDebug>



ShipItem::ShipItem(QGraphicsItem *parent):QGraphicsPathItem(parent)
{
    this->setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QRectF ShipItem::boundingRect() const
{
    return QRectF(-m_width/2.0,-m_height/2.0,m_width,m_height);
}

void ShipItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"ShipItem::mousePressEvent";
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
    if(m_dueNorth){
        const static QPointF polygon[9] = {
            (m_centerLeftShipPoint),
            (m_centerRightShipPoint),
            (m_headRightShipPoint),
            (m_headShipPoint),
            (m_headLeftShipPoint),
            (m_centerLeftShipPoint),
            (m_tailLeftShipPoint),
            (m_tailRightShipPoint),
            (m_centerRightShipPoint)
        };
        m_localHeadShipPoint = m_headLeftShipPoint;
        painter->drawPolygon(polygon, 9);

        //gradientOtherArc(painter,m_seaMileLength, 90  - m_rightAngle+45/2.0 ,-45,(m_centerRightShipPoint),QColor(220,20,60));
        //gradientOtherArc(painter,m_seaMileLength, 90  + m_leftAngle-45/2.0 ,45,(m_centerLeftShipPoint),QColor(0,255,255));

        gradientArc(painter,m_seaMileLength, 90  - m_rightAngle ,-m_dxAngle,(m_centerRightShipPoint),QColor(220,20,60));
        gradientArc(painter,m_seaMileLength, 90  + m_leftAngle ,m_dxAngle,(m_centerLeftShipPoint),QColor(0,255,255));
    }else{
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
        m_localHeadShipPoint =rotaryAngle(m_headLeftShipPoint);
        painter->drawPolygon(polygon, 9);
        //gradientOtherArc(painter,m_seaMileLength, 90 -m_angle - m_rightAngle ,-45,rotaryAngle(m_centerRightShipPoint),QColor(220,20,60));
        //gradientOtherArc(painter,m_seaMileLength, 90 -m_angle + m_leftAngle ,45,rotaryAngle(m_centerLeftShipPoint),QColor(0,255,255));
        gradientArc(painter,m_seaMileLength, 90 -m_angle - m_rightAngle ,-m_dxAngle,rotaryAngle(m_centerRightShipPoint),QColor(220,20,60));
        gradientArc(painter,m_seaMileLength, 90 -m_angle + m_leftAngle ,m_dxAngle,rotaryAngle(m_centerLeftShipPoint),QColor(0,255,255));
    }

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

bool ShipItem::dueNorth() const
{
    return m_dueNorth;
}

void ShipItem::setDueNorth(bool dueNorth)
{
    m_dueNorth = dueNorth;
}

float ShipItem::angle() const
{
    return m_angle;
}

void ShipItem::setAngle(float angle)
{
    m_angle = angle;
}

QPointF ShipItem::localHeadShipPoint() const
{
    return m_localHeadShipPoint;
}

void ShipItem::setLocalHeadShipPoint(const QPointF &localHeadShipPoint)
{
    m_localHeadShipPoint = localHeadShipPoint;
}



void ShipItem::updateLeftAngle(float leftAngle)
{
    m_leftAngle = leftAngle + m_dxAngle/2;
    qDebug()<<m_leftAngle;
}





void ShipItem::updateRightAngle(float rightAngle)
{
    m_rightAngle = rightAngle + m_dxAngle/2;
    qDebug()<<m_rightAngle;
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
    float rad = qDegreesToRadians(static_cast<float>(angleLength - startAngle));
    QRadialGradient radialGradient(centerPt,100);
    radialGradient.setColorAt(0,QColor(60,60,60,140));
    radialGradient.setColorAt(1,QColor(200,200,200,140));
    painter->setBrush(QBrush(radialGradient));

    painter->drawPie(rect, startAngle * 16, angleLength * 16);
}

void ShipItem::gradientOtherArc(QPainter *painter, int radius, int startAngle, int angleLength, QPointF centerPt, QColor color)
{
    QRectF rect(centerPt.x()-radius,centerPt.y()-radius ,2*radius,2*radius);


    float rad = qDegreesToRadians(static_cast<float>(angleLength - startAngle));
    QRadialGradient radialGradient(centerPt,100);
    radialGradient.setColorAt(0,QColor(60,60,60,140));
    radialGradient.setColorAt(1,QColor(200,200,200,140));
    painter->setBrush(QBrush(radialGradient));

    painter->drawPie(rect, startAngle * 16, angleLength * 16);
}
