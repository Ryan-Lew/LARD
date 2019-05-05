#ifndef __MY_PLOT_H__
#define __MY_PLOT_H__

#include "Graphic.h"
#include <QColor>

class Point : public Graphic
{
public:
	Point(float pos_x,float pos_y,const QColor& color,int frame_number);
	virtual ~Point() {}
	virtual void Draw(View2D* view);
	void SetColor(const QColor& color);
	bool HitTest(const QPointF& pointf_in_view);
	int         m_frame_number;

private:
	QColor m_color;
	QRectF m_bounding_rect_in_view_radar1;
	QRectF m_bounding_rect_in_view_radar2;
	QRectF m_bounding_rect_in_view_radar3;

};

#endif