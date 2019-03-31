#include "scalewidget.h"
#include <QPainter>
ScaleWidget::ScaleWidget(QWidget *parent) : QWidget(parent)
{

}

void ScaleWidget::paintEvent(QPaintEvent *event)
{
    updateList();
    QPainter painter(this);
    painter.save();
        QPen pen(QColor(153,217,234));
        painter.setPen(pen);
        for(int i =0;i<m_list.size();i++){
            if(i == 3||i==4){
                painter.setBrush(QColor(102,102,102));
            }else{
                painter.setBrush(Qt::black);
            }
            painter.drawRect(m_list.at(i));
        }


    painter.restore();
}

void ScaleWidget::updateList()
{
    m_list.clear();
    float width = this->width()-2;
    float height = this->height();

    float dx = width/m_index;
    for(float i = 0.0;i<width;i+=dx){
        QRectF rect(i,0,dx,height-1);
        m_list.append(rect);
    }
}
