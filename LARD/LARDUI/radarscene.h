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

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    virtual void drawBackground(QPainter *painter, const QRectF &rect);


    float seaMile() const;
    void setSeaMile(float seaMile);

    void updateItem();


    bool dictSwitch() const;
    void setDictSwitch(bool dictSwitch);

private:

    QColor m_radarLineColor = QColor(0,130,0);
    QColor m_radarLineCenterColor = QColor(130,130,130);
    //�����״�ͼ
    void updateRadar(const QRectF &);

    //�״�Ȧ��С
    QList<float> m_radarRings;
    //�̶ȵ�λ��
    QList<float> m_scaleLists;
    //�̶ȿ��
    int m_scaleWidth = 5;

    //Ĭ��һ����
    float m_seaMile = 2.0;

    //��ֹ���� ����
    float m_denialSeaMile = 1.3;
    //������� ����
    float m_warningSeaMile = 3.3;

    //�ָ��̶ȳ�
    int m_splitMile = 5;
    //�״����߿�ľ���
    int m_padding = 50;
    //�̶��Ĵ�С
    float m_fixRadius = 0;
    //�̶���һ�����������
    float m_fixSeaMile = 0;
    //�״�Ȧ����ĵ�
    QPointF m_radarTopPoint;
    QPointF m_radarBottomPoint;
    QPointF m_radarLeftPoint;
    QPointF m_radarRightPoint;





    //��������
    bool m_dictSwitch = true;

    //����λ��
    QMap<QString,QRectF> m_northMap ;
    float m_northWidth = 40;
    float m_northHeight = 30;
    //�״�ͼ�ϵ�ÿһ���̶ȵĽǶ�,Ĭ��30��
    float m_angle = 30;

    QList<RadarAngleInfo> m_angleMap;
};

#endif // RADARSCENE_H
