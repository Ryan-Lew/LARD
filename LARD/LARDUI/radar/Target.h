#ifndef ___TARGET_H___
#define ___TARGET_H___

#include "Graphic.h"
#include <Windows.h>
#include <list>
#include <QColor>
#include "Utility.h"

class Label;
class View2D;
class Point;

class Target : public Graphic
{

public:

	typedef std::list<Point*> TRACK;
	typedef TRACK::iterator   TRACK_ITERATOR;

public:
	
	Target( UINT32 id,const std::string& label_text,float pos_x, float pos_y, float direction_in_scene,const QColor& common_color,const QColor& highlight_color,UINT32 max_plot_nums = MAX_TRACK_PLOT_NUMS);
	virtual ~Target();
	virtual void Draw(View2D* view);
	bool	HitTest(const QPointF& pointf_in_view);	
	Label*	GetLabel() const;
	void	ResetState();
	void	Update(float pos_x, float pos_y, float direction_in_scene);
	UINT32	GetID() const;
	virtual void  SetState(STATE state);
	const QColor& GetCommonColor() const;
	const QColor& GetHighlightColor() const;

public:

	void   Draw(View2D* view,const QColor& color);

private:

	UINT32    m_id;
	TRACK     m_track;
	Label*    m_label;

private:
	
	QRectF		        m_head_bounding_rect_in_view;
	QColor              m_common_color;
	QColor              m_highlight_color;
	static QPolygonF    m_polygon_image;
	UINT32              m_max_track_plot_nums;
};

#endif