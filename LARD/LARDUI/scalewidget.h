#ifndef SCALEWIDGET_H
#define SCALEWIDGET_H

#include <QWidget>
#include <QVector>

class ScaleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScaleWidget(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent *event);
    void updateList();
signals:

public slots:

private:
    QVector<QRectF> m_list;
    int m_index = 12;
};

#endif // SCALEWIDGET_H
