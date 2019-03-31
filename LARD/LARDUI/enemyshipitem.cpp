#include "enemyshipitem.h"

#include <QPainter>
#include <QDebug>
#include <QtMath>

EnemyShipItem::EnemyShipItem(QGraphicsItem *parent):QGraphicsRectItem(parent)
{

}

QRectF EnemyShipItem::boundingRect() const
{
    return QRectF(-2*m_radius,-2*m_radius,4*m_radius,4*m_radius);
}

bool EnemyShipItem::contains(const QPointF &point) const
{
    qDebug()<<point;
    return false;
}

void EnemyShipItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    //»æÖÆÄ¿±ê
    if(isSelected()){
        painter->setPen(QPen(Qt::red,1));
    }else{
        painter->setPen(QPen(Qt::white,1));
    }

    painter->drawEllipse(m_centerPt,m_radius,m_radius);

    QPointF startPt = rotaryAngle(QPointF(m_centerPt.x(),m_centerPt.y()-m_radius));
    QPointF endPt = rotaryAngle(QPointF(m_centerPt.x(),m_centerPt.y()-2*m_radius));
    painter->drawLine(startPt,endPt);

    updateHintRect();
    painter->setPen(QPen(QColor(183,159,91),1));
    painter->drawRect(m_hintRect);
    painter->drawText(QRectF(m_hintRect.x(),m_hintRect.y() ,m_hintWidth,m_hintHeight/2),QString("B:%1").arg(m_B),Qt::AlignHCenter|Qt::AlignVCenter);
    painter->drawText(QRectF(m_hintRect.x(),m_hintRect.y()+m_hintHeight/2 ,m_hintWidth,m_hintHeight/2),QString("S:%1").arg(m_S),Qt::AlignHCenter|Qt::AlignVCenter);
}

QPainterPath EnemyShipItem::shape() const
{
    const QVector<QPointF> points;
    QPainterPath path;
    QPolygonF polygon;
    polygon.append(points);
    path.addPolygon(polygon);
    return path;
}

int EnemyShipItem::type() const
{
    return 2;
}



float EnemyShipItem::fixSeaMile() const
{
    return m_fixSeaMile;
}

void EnemyShipItem::setFixSeaMile(float fixSeaMile)
{
    m_fixSeaMile = fixSeaMile;
    float rad = qDegreesToRadians(static_cast<float>(m_seaAngle -90));


    m_centerPt.setX(m_fixSeaMile*m_seaMile*qCos(static_cast<qreal>(rad)));
    m_centerPt.setY(m_fixSeaMile*m_seaMile*qSin(static_cast<qreal>(rad)));

}

float EnemyShipItem::seaMile() const
{
    return m_seaMile;
}

void EnemyShipItem::setSeaMile(float seaMile)
{
    m_seaMile = seaMile;
}

float EnemyShipItem::seaAngle() const
{
    return m_seaAngle;
}

void EnemyShipItem::setSeaAngle(float seaAngle)
{
    m_seaAngle = seaAngle;
}

float EnemyShipItem::angle() const
{
    return m_angle;
}

void EnemyShipItem::setAngle(float angle)
{
    m_angle = angle;
}

QPointF EnemyShipItem::rotaryAngle(QPointF lastPt)
{
    double angleHude = m_angle * M_PI / 180;
    float x = (lastPt.x() - m_centerPt.x())*qCos(angleHude) - (lastPt.y() - m_centerPt.y())*qSin(angleHude) + m_centerPt.x();
    float y = (lastPt.x() - m_centerPt.x())*qSin(angleHude) + (lastPt.y() - m_centerPt.y())*qCos(angleHude) + m_centerPt.y();

    return QPointF(x,y);
}

void EnemyShipItem::updateHintRect()
{
    double angleHude = (m_angle + 180) * M_PI / 180;

    QPointF lastPt = QPointF(m_centerPt.x(),m_centerPt.y()-m_radius);
    float x = (lastPt.x() - m_centerPt.x())*qCos(angleHude) - (lastPt.y() - m_centerPt.y())*qSin(angleHude) + m_centerPt.x();
    float y = (lastPt.x() - m_centerPt.x())*qSin(angleHude) + (lastPt.y() - m_centerPt.y())*qCos(angleHude) + m_centerPt.y();


    float d_angle = (float)(((int)m_angle + 180)%360);



    if( d_angle >=0&&d_angle < 90){
        m_hintRect.setX(x);
        m_hintRect.setY(y - m_hintHeight);


    }else if(d_angle >= 90&&d_angle <180){
        m_hintRect.setX(x);
        m_hintRect.setY(y);

    }else if(d_angle >= 180&&d_angle < 270){
        m_hintRect.setX(x - m_hintWidth);
        m_hintRect.setY(y);


    }else if(d_angle >= 270 &&d_angle < 360){
        m_hintRect.setX(x - m_hintWidth);
        m_hintRect.setY(y - m_hintHeight);
    }
    m_hintRect.setWidth(m_hintWidth);
    m_hintRect.setHeight(m_hintHeight);
}
