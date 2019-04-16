#include "volumewidget.h"
#include "ui_volumewidget.h"
#include <QPainter>
#include <QDebug>

VolumeWidget::VolumeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeWidget)
{
    ui->setupUi(this);
}

VolumeWidget::~VolumeWidget()
{
    delete ui;
}

void VolumeWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.save();
    int width = this->width();
    int height = this->height();



    float dy  = height / 20.0;

    for (float h = height, i = dy ;h>0;h-=dy,i+=5){


        if(m_volume>i){
            QBrush brush(QColor(62,175,239));
            painter.setPen(QPen(QColor(62,175,239)));
            painter.setBrush(brush);
            painter.drawRect(QRect(m_margin,h - m_high,width - 2* m_margin,m_high));
        }else{
            QBrush brush(QColor(69,73,76));
            painter.setPen(QPen(QColor(69,73,76)));
            painter.setBrush(brush);
            painter.drawRect(QRect(m_margin,h - m_high,width - 2* m_margin,m_high));
        }

    }
    painter.restore();
}
