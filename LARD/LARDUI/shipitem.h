#ifndef SHIPITEM_H
#define SHIPITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPathItem>

class ShipItem : public QGraphicsPathItem
{

public:
    ShipItem(QGraphicsItem* parent = nullptr);


    virtual QRectF boundingRect() const override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual bool contains(const QPointF &point) const override;


    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QPainterPath shape() const override;
    virtual int type() const override;

    QPointF centerPt() const;
    void setCenterPt(const QPointF &centerPt);


    float fixSeaMile() const;
    void setFixSeaMile(float fixSeaMile);

    bool dueNorth() const;
    void setDueNorth(bool dueNorth);

    float angle() const;
    void setAngle(float angle);

    QPointF localHeadShipPoint() const;
    void setLocalHeadShipPoint(const QPointF &localHeadShipPoint);


    void updateLeftAngle(float leftAngle);

    void updateRightAngle(float rightAngle);

private :
    bool m_dueNorth = true;
    float m_width = 20;
    float m_height = 50;

    float m_seaMile = 1.2;
    float m_seaMileLength = 200;
    float m_leftAngle = 0;               //左前旋翼角度
    float m_rightAngle = 30;              //右前旋翼角度
    float m_dxAngle = 30;               //喇叭默认的角度
    float m_angle = 30;                  //默认角度
    float m_headPercent = 4/5.0;
    float m_leftPercent = 3/5.0;
    float m_fixSeaMile = 0;                 //一海里对应的像素
    QPointF m_centerPt = QPointF(0.0,0.0);
    QPointF m_headShipPoint;            //船头
    QPointF m_headLeftShipPoint;        //左前旋翼
    QPointF m_headRightShipPoint;       //右前旋翼
    QPointF m_centerLeftShipPoint;      //中心左侧喇叭
    QPointF m_centerRightShipPoint;     //中心右侧侧喇叭
    QPointF m_tailLeftShipPoint;        //左后旋翼
    QPointF m_tailRightShipPoint;       //右后旋翼

    QPointF m_localHeadShipPoint;



    //计算船只点信息
    void countShip();
    //旋转角度
    QPointF rotaryAngle(QPointF lastPt);

    QPointF rotaryAngle(QPointF centerPt, QPointF lastPt,float angle);

    //绘制扇形
    //第一个参数画笔
    //第二个参数半径
    //第三个参数开始角度
    //第四个参数跨越角度
    //第五个参数中心点
    void gradientArc(QPainter *painter, int radius, int startAngle, int angleLength,QPointF centerPt, QColor color);


    //绘制扇形
    //第一个参数画笔
    //第二个参数半径
    //第三个参数开始角度
    //第四个参数跨越角度
    //第五个参数中心点
    void gradientOtherArc(QPainter *painter, int radius, int startAngle, int angleLength,QPointF centerPt, QColor color);
};

#endif // SHIPITEM_H
