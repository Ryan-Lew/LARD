#ifndef RADARSCENE_H
#define RADARSCENE_H
#include <QGraphicsScene>
#include <QMap>

class RadarAngleInfo{
public:
    RadarAngleInfo(){}
    QPointF startPt() const;
    void setStartPt(const QPointF &startPt);

    QPointF endPt() const;
    void setEndPt(const QPointF &endPt);

    QString text() const;
    void setText(const QString &text);


    QRectF rect() const;


    float angle() const;
    void setAngle(float angle);

private:
    QPointF m_startPt;
    QPointF m_endPt;
    QString m_text;
    float m_angle = 0;
    float height = 10;
    float width = 40;
};

class RadarScene : public QGraphicsScene
{
    Q_OBJECT
public:
    RadarScene(QObject *parent = nullptr);

signals:

public slots:

public:

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void drawBackground(QPainter *painter, const QRectF &rect);


    float seaMile() const;
    void setSeaMile(float seaMile);

    void updateItem();


    bool dictSwitch() const;
    void setDictSwitch(bool dictSwitch);
    //更新船喇叭角度
    void updateShipBugle();
    //更新所有船只信息
    void updateEnemyShip();
private:

    QColor m_radarLineColor = QColor(0,130,0);
    QColor m_radarLineCenterColor = QColor(130,130,130);
    //更新雷达图
    void updateRadar(const QRectF &);

    //雷达圈大小
    QList<float> m_radarRings;
    //刻度点位置
    QList<float> m_scaleLists;
    //刻度宽度
    int m_scaleWidth = 5;

    //默认一海里
    float m_seaMile = 2.0;

    //拒止距离 海里
    float m_denialSeaMile = 1.3;
    //警告距离 海里
    float m_warningSeaMile = 3.3;

    //分割海里刻度尺
    int m_splitMile = 5;
    //雷达距离边框的距离
    int m_padding = 50;
    //固定的大小
    float m_fixRadius = 0;
    //固定的一海里多少像素
    float m_fixSeaMile = 0;
    //雷达圈上面的点
    QPointF m_radarTopPoint;
    QPointF m_radarBottomPoint;
    QPointF m_radarLeftPoint;
    QPointF m_radarRightPoint;





    //正北开关
    bool m_dictSwitch = true;

    //正北位置
    QMap<QString,QRectF> m_northMap ;
    float m_northWidth = 40;
    float m_northHeight = 30;
    //雷达图上的每一个刻度的角度,默认30度
    float m_angle = 30;

    QList<RadarAngleInfo> m_angleMap;
};

#endif // RADARSCENE_H
