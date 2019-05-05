#ifndef __MY_PLOT_H__
#define __MY_PLOT_H__

#include "Graphic.h"
#include <QColor>

class Plot : public Graphic
{
public:
	Plot(float pos_x,float pos_y,const QColor& color = QColor(240, 240, 240, 255));
	virtual ~Plot() {}
	virtual void Draw(View2D* view);
	void SetColor(const QColor& color);
private:
	static QRectF m_circle_image;
	QColor m_color;
};

#endif