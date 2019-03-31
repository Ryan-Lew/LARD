#ifndef ENEMYSHIPITEM_H
#define ENEMYSHIPITEM_H
#include <QObject>
#include <QGraphicsRectItem>

class EnemyShipItem : public QGraphicsRectItem
{

public:
    EnemyShipItem(QGraphicsItem* parent = nullptr);



    virtual QRectF boundingRect() const override;

    virtual bool contains(const QPointF &point) const override;


    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual QPainterPath shape() const override;
    virtual int type() const override;


    float fixSeaMile() const;
    void setFixSeaMile(float fixSeaMile);

    float seaMile() const;
    void setSeaMile(float seaMile);

    float seaAngle() const;
    void setSeaAngle(float seaAngle);

    float angle() const;
    void setAngle(float angle);

private:
    //多少海里
    float m_seaMile = 0;
    //一海里对应的像素
    float m_fixSeaMile = 0;
    //相对正北角度
    float m_seaAngle = 0;
    //中心点通过海里和正北角度计算
    QPointF m_centerPt = QPointF(0.0,0.0);
    //半径
    float m_radius = 10;
    //自身的方向角 正北方向，如果不是正北方向就减去相对船只的角度
    float m_angle = 0;

    QRectF m_hintRect ;
    float m_hintWidth = 40;
    float m_hintHeight = 26;
    //旋转角度
    QPointF rotaryAngle(QPointF lastPt);
    //初始化提示对话框
    void updateHintRect();
    QString m_B = "100";//方位角
    QString m_S = "233";//速度
    void updateChooseRect();


};

#endif // ENEMYSHIPITEM_H
