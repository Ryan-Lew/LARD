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

    virtual bool contains(const QPointF &point) const override;


    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QPainterPath shape() const override;
    virtual int type() const override;

    QPointF centerPt() const;
    void setCenterPt(const QPointF &centerPt);


    float fixSeaMile() const;
    void setFixSeaMile(float fixSeaMile);

private :
    float m_width = 20;
    float m_height = 50;

    float m_seaMile = 1.2;
    float m_seaMileLength = 200;
    float m_leftAngle = 0;               //��ǰ����Ƕ�
    float m_rightAngle = 30;              //��ǰ����Ƕ�
    float m_dxAngle = 30;               //����Ĭ�ϵĽǶ�
    float m_angle = 280;                  //Ĭ�ϽǶ�
    float m_headPercent = 4/5.0;
    float m_leftPercent = 3/5.0;
    float m_fixSeaMile = 0;                 //һ�����Ӧ������
    QPointF m_centerPt = QPointF(0.0,0.0);
    QPointF m_headShipPoint;            //��ͷ
    QPointF m_headLeftShipPoint;        //��ǰ����
    QPointF m_headRightShipPoint;       //��ǰ����
    QPointF m_centerLeftShipPoint;      //�����������
    QPointF m_centerRightShipPoint;     //�����Ҳ������
    QPointF m_tailLeftShipPoint;        //�������
    QPointF m_tailRightShipPoint;       //�Һ�����



    //���㴬ֻ����Ϣ
    void countShip();
    //��ת�Ƕ�
    QPointF rotaryAngle(QPointF lastPt);

    QPointF rotaryAngle(QPointF centerPt, QPointF lastPt,float angle);

    //��������
    //��һ����������
    //�ڶ��������뾶
    //������������ʼ�Ƕ�
    //���ĸ�������Խ�Ƕ�
    //������������ĵ�
    void gradientArc(QPainter *painter, int radius, int startAngle, int angleLength,QPointF centerPt, QColor color);
};

#endif // SHIPITEM_H
