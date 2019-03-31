#ifndef RADARSCENE_H
#define RADARSCENE_H
#include <QGraphicsScene>

class RadarScene : public QGraphicsScene
{
    Q_OBJECT
public:
    RadarScene(QObject *parent = nullptr);

signals:

public slots:

public:

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    virtual void drawBackground(QPainter *painter, const QRectF &rect);


};

#endif // RADARSCENE_H
