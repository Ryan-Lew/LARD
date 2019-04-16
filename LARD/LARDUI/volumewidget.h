#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include <QWidget>

namespace Ui {
class VolumeWidget;
}

class VolumeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeWidget(QWidget *parent = 0);
    ~VolumeWidget();


    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::VolumeWidget *ui;

    int m_margin = 8;
    int m_high = 1;
    int m_volume = 50;
};

#endif // VOLUMEWIDGET_H
