#include "Target.h"
#include "Scene2D.h"
#include "Utility.h"
#include "View2D.h"
#include "Point.h"
#include "Label.h"



QPolygonF Target::m_polygon_image = QPolygonF() << QPointF(4.0F, 0.0F)<< QPointF(0.0F, 4.0F)<< QPointF(16.0F, 0.0F)<< QPointF(0.0F, -4.0F)<< QPointF(4.0F, 0.0F);


Target::Target(UINT32 id,const std::string& label_text,float pos_x, float pos_y, float direction_in_scene,const QColor& common_color,const QColor& highlight_color,UINT32 max_plot_nums) :
m_id(id),
Graphic(pos_x,pos_y,direction_in_scene),
m_label(new Label(this,label_text)),
m_common_color(common_color),
m_highlight_color(highlight_color),
m_max_track_plot_nums(MAX_TRACK_PLOT_NUMS)
{
}


Target::~Target()
{
	for (TRACK_ITERATOR it = m_track.begin(); it != m_track.end(); ++it)
	{
		delete (*it);
		*it = NULL;
	}
	m_track.clear();
	delete m_label;
	m_label = NULL;
}



void Target::Draw(View2D* view)
{
	if (Graphic::HighLight == GetState())
	{
		Draw(view,m_highlight_color);
	}
	else
	{
		Draw(view,m_common_color);
	}
	m_label->Draw(view);
}


void Target::Draw(View2D* view,const QColor& color)
{
	QPainter* render = view->GetRender();
	render->save();

	render->setPen(QPen(color,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	render->setBrush(QBrush(color));


	Point  point_temp = Point(GetPositionX(),GetPositionY(),color,0);
	Point* point_0    = &point_temp;

	for (TRACK_ITERATOR it = m_track.begin();it != m_track.end(); ++it)
	{
		QPointF pos_in_view_0 = view->GetViewMatrix().map(QPointF(point_0->GetPositionX(),point_0->GetPositionY()));

		Point* point_1 = *it;
		QPointF pos_in_view_1 = view->GetViewMatrix().map(QPointF(point_1->GetPositionX(),point_1->GetPositionY()));

		render->drawLine(pos_in_view_0,pos_in_view_1); 
		
		point_0 = point_1;
	}


	///-------------------------------------------------------
	render->restore();	

}



bool Target::HitTest(const QPointF& pointf_in_view)
{	
	if (m_label->HitTest(pointf_in_view))
	{
		return true;
	}
	else
	{
		if (PointInRectRough(pointf_in_view,m_head_bounding_rect_in_view))
		{
			return true;
		}
		else
		{
			for (TRACK_ITERATOR it = m_track.begin(); it != m_track.end(); ++it)
			{
				Point* point = *it;
				if ((*it)->HitTest(pointf_in_view))
				{
					return true;
				}
			}
		}
	}
	return false;
}


Label* Target::GetLabel() const
{
	return m_label;
}



void Target::Update(float pos_x, float pos_y, float direction_in_scene)
{
	m_track.push_front(new Point(GetPositionX(),GetPositionY(),TARGET_COLOR,0));
	SetPosition(pos_x,pos_y);
	SetRotation(direction_in_scene);
	if ( m_track.size() > m_max_track_plot_nums )
	{
		Point* front_plot = m_track.back();
		delete front_plot;
		m_track.pop_back();
	}
}

UINT32	Target::GetID() const
{
	return m_id;
}

void Target::SetState(Graphic::STATE state)
{
	Graphic::SetState(state);
	m_label->SetState(state);
}


const QColor& Target::GetCommonColor() const
{
	return m_common_color;
}

const QColor& Target::GetHighlightColor() const
{
	return m_highlight_color;
}
