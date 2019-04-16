#ifndef ENEMYSHIPITEM_H
#define ENEMYSHIPITEM_H
#include <QObject>
#include <QGraphicsRectItem>
enum ENEMYSHIPSTATUS{
    SHIP_NORMAL = 0,     //一般
    SHIP_WARNING = 1,    //警告
    SHIP_ERROR = 2,      //危险
};

class EnemyShipItem : public QGraphicsRectItem
{

public:
    EnemyShipItem(QGraphicsItem *parent = nullptr);



    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual int type() const override;


    float fixSeaMile() const;
    void setFixSeaMile(float fixSeaMile);

    float seaMile() const;
    void setSeaMile(float seaMile);

    float seaAngle() const;
    void setSeaAngle(float seaAngle);

    float angle() const;
    void setAngle(float angle);

    bool dueNorth() const;
    void setDueNorth(bool dueNorth);

    float shipRadius() const;
    void setShipRadius(float shipRadius);

    QPointF centerPt() const;
    void setCenterPt(const QPointF &centerPt);

    ENEMYSHIPSTATUS status() const;
    void setStatus(const ENEMYSHIPSTATUS &status);

private:
    float m_shipRadius = 0;
    bool m_dueNorth = true;
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
    ENEMYSHIPSTATUS m_status;

};

#endif // ENEMYSHIPITEM_H
