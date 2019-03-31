#ifndef ___LABEL_H___
#define ___LABEL_H___

#include <Windows.h>
#include "Graphic.h"

class Target;
class View2D;

class Label : public Graphic
{
public:
	Label(Target* target,const std::string& label_text);
	virtual ~Label();
	bool HitTest(const QPointF& pointf_in_view);
	virtual void Draw(View2D* view);
private:
	QRectF      m_bounding_rect_in_view;
	Target*     m_target;
	std::string m_label_text;
private:
	static  QRectF  m_origin_text_rect;
	static  float   m_origin_relative_to_aircraft_x;
	static  float   m_origin_relative_to_aircraft_y;
};

#endif