#include "enemyshipitem.h"

#include <QPainter>
#include <QDebug>
#include <QtMath>

EnemyShipItem::EnemyShipItem(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    this->setAcceptedMouseButtons(Qt::LeftButton);
    setFlags(QGraphicsItem::ItemIsSelectable);

}

QRectF EnemyShipItem::boundingRect() const
{
    return QRectF(m_centerPt.x()-m_radius,m_centerPt.y()-m_radius,2*m_radius,2*m_radius);
}


void EnemyShipItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    if(isSelected()){

        painter->setPen(QPen(Qt::red,1));
    }else{
        if(m_status == SHIP_NORMAL){
            painter->setPen(QPen(Qt::white,1));
        }else if(m_status == SHIP_WARNING){
            painter->setPen(QPen(Qt::yellow,1));
        }else if(m_status == SHIP_ERROR){
            painter->setPen(QPen(QColor(86,18,85),1));
        }
    }
    updateHintRect();
    painter->drawEllipse(m_centerPt,m_radius,m_radius);

    QPointF startPt = rotaryAngle(QPointF(m_centerPt.x(),m_centerPt.y()-m_radius));
    QPointF endPt = rotaryAngle(QPointF(m_centerPt.x(),m_centerPt.y()-2*m_radius));
    painter->setPen(QPen(Qt::white,1));
    painter->drawLine(startPt,endPt);


    painter->setPen(QPen(QColor(183,159,91),1));
    painter->drawRect(m_hintRect);
    painter->drawText(QRectF(m_hintRect.x(),m_hintRect.y() ,m_hintWidth,m_hintHeight/2),QString("B:%1").arg(m_B),Qt::AlignHCenter|Qt::AlignVCenter);
    painter->drawText(QRectF(m_hintRect.x(),m_hintRect.y()+m_hintHeight/2 ,m_hintWidth,m_hintHeight/2),QString("S:%1").arg(m_S),Qt::AlignHCenter|Qt::AlignVCenter);

}

void EnemyShipItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"EnemyShipItem::mousePressEvent";
    QGraphicsRectItem::mousePressEvent(event);

}

void EnemyShipItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"EnemyShipItem::mouseReleaseEvent";
    QGraphicsRectItem::mouseReleaseEvent(event);
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

bool EnemyShipItem::dueNorth() const
{
    return m_dueNorth;
}

void EnemyShipItem::setDueNorth(bool dueNorth)
{
    m_dueNorth = dueNorth;
}

float EnemyShipItem::shipRadius() const
{
    return m_shipRadius;
}

void EnemyShipItem::setShipRadius(float shipRadius)
{
    m_shipRadius = shipRadius;
}

QPointF EnemyShipItem::centerPt() const
{
    return m_centerPt;
}

void EnemyShipItem::setCenterPt(const QPointF &centerPt)
{
    m_centerPt = centerPt;
}

QPointF EnemyShipItem::rotaryAngle(QPointF lastPt)
{
    if(m_dueNorth){
        double angleHude = m_angle * M_PI / 180;
        float x = (lastPt.x() - m_centerPt.x())*qCos(angleHude) - (lastPt.y() - m_centerPt.y())*qSin(angleHude) + m_centerPt.x();
         float y = (lastPt.x() - m_centerPt.x())*qSin(angleHude) + (lastPt.y() - m_centerPt.y())*qCos(angleHude) + m_centerPt.y();

         return QPointF(x,y);
     }else{
         double angleHude =(m_angle + m_shipRadius )  * M_PI / 180;
         float x = (lastPt.x() - m_centerPt.x())*qCos(angleHude) - (lastPt.y() - m_centerPt.y())*qSin(angleHude) + m_centerPt.x();
         float y = (lastPt.x() - m_centerPt.x())*qSin(angleHude) + (lastPt.y() - m_centerPt.y())*qCos(angleHude) + m_centerPt.y();

         return QPointF(x,y);
     }

}

void EnemyShipItem::updateHintRect()
{
    if(m_dueNorth){
        float rad = qDegreesToRadians(static_cast<float>(m_seaAngle -90));
        m_centerPt.setX(m_fixSeaMile*m_seaMile*qCos(static_cast<qreal>(rad)));
        m_centerPt.setY(m_fixSeaMile*m_seaMile*qSin(static_cast<qreal>(rad)));
    }else{

        float rad = qDegreesToRadians(static_cast<float>(m_seaAngle + m_shipRadius -90));
        m_centerPt.setX(m_fixSeaMile*m_seaMile*qCos(static_cast<qreal>(rad)));
        m_centerPt.setY(m_fixSeaMile*m_seaMile*qSin(static_cast<qreal>(rad)));

    }



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
    setRect(m_centerPt.x()-m_radius,m_centerPt.y()-m_radius,2*m_radius,2*m_radius);


}

ENEMYSHIPSTATUS EnemyShipItem::status() const
{
    return m_status;
}

void EnemyShipItem::setStatus(const ENEMYSHIPSTATUS &status)
{
    m_status = status;
}
