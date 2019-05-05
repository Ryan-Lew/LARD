#include "radarscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

RadarScene::RadarScene(QObject *parent):QGraphicsScene(parent)
{

}

void RadarScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"mousePressEvent"<<mouseEvent->scenePos();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void RadarScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"mouseReleaseEvent"<<mouseEvent->scenePos();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void RadarScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->fillRect(rect,QBrush(Qt::black));
    painter->restore();
}
