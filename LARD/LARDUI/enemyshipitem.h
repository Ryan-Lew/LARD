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
    //���ٺ���
    float m_seaMile = 0;
    //һ�����Ӧ������
    float m_fixSeaMile = 0;
    //��������Ƕ�
    float m_seaAngle = 0;
    //���ĵ�ͨ������������Ƕȼ���
    QPointF m_centerPt = QPointF(0.0,0.0);
    //�뾶
    float m_radius = 10;
    //����ķ���� �����������������������ͼ�ȥ��Դ�ֻ�ĽǶ�
    float m_angle = 0;

    QRectF m_hintRect ;
    float m_hintWidth = 40;
    float m_hintHeight = 26;
    //��ת�Ƕ�
    QPointF rotaryAngle(QPointF lastPt);
    //��ʼ����ʾ�Ի���
    void updateHintRect();
    QString m_B = "100";//��λ��
    QString m_S = "233";//�ٶ�
    void updateChooseRect();


};

#endif // ENEMYSHIPITEM_H
