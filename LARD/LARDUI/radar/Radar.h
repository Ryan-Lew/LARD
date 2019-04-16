#ifndef ___RADAR_H___
#define ___RADAR_H___

#include "Graphic.h"
#include <vector>
#include <QPainterPath>

class View2D;

class Radar : public Graphic
{

	struct LINE
	{
		float from_x;
		float from_y;
		float to_x;
		float to_y;
	};

	typedef std::vector<LINE*>        LINE_LIST;
	typedef LINE_LIST::iterator       LINE_LIST_ITERATOR;
	typedef LINE_LIST::const_iterator LINE_LIST_CONST_ITERATOR;

	struct CIRCLE
	{
		float x;
		float y;
		float w;
		float h;
	};

	typedef std::vector<CIRCLE*>        CIRCLE_LIST;
	typedef CIRCLE_LIST::iterator       CIRCLE_LIST_ITERATOR;
	typedef CIRCLE_LIST::const_iterator CIRCLE_LIST_CONST_ITERATOR;

	struct MARK
	{
		float x;
		float y;
		float length;	
		float angle;
	};

	typedef std::vector<MARK*>        MARK_LIST;
	typedef MARK_LIST::iterator       MARK_LIST_ITERATOR;
	typedef MARK_LIST::const_iterator MARK_LIST_CONST_ITERATOR;

	struct TEXT_RD
	{
		TEXT_RD() : path(new QPainterPath) {}
		~TEXT_RD() { delete path;} 
		float         x;
		float         y;
		float         angle;
		QPainterPath* path;
	};

	typedef std::vector<TEXT_RD*>       TEXT_LIST;
	typedef TEXT_LIST::iterator         TEXT_LIST_ITERATOR;
	typedef TEXT_LIST::const_iterator   TEXT_LIST_CONST_ITERATOR;

public:
	Radar(float measure_radius);
	virtual ~Radar();
	virtual void Draw(View2D* view);
private:
	float       m_measure_radius;
	LINE_LIST   m_divided_line_list;
	CIRCLE_LIST m_divided_circle_list;
	MARK_LIST   m_scale_mark_list;
	CIRCLE      m_measure_circle;
	LINE        m_horizontal_line;
	LINE        m_vertical_line;
	TEXT_LIST   m_scale_text_list;
private:
	static const float m_mark_5_length;
	static const float m_mark_1_length;
	static const int   m_circle_divided_count;
	static const int   m_line_divided_count;
	static const int   m_circle_mark_count;
	static const int   m_line_mark_count;
	static const int   m_text_font_size;
};

#endif