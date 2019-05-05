#include "Point.h"
#include "View2D.h"
#include "Utility.h"
#include "Scene2D.h"



Point::Point(float pos_x,float pos_y,const QColor& color,int frame_number):Graphic(pos_x,pos_y),m_color(color),m_frame_number(frame_number)
{
}

void Point::SetColor(const QColor& color)
{
	m_color = color;
}


void Point::Draw(View2D* view)
{
	QPainter* render = view->GetRender();
	render->save();

	render->setPen(QPen(m_color,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	render->setBrush(QBrush(m_color));
	///-----------点迹大小保持不变----------------------
	QPointF pos_in_view = view->GetViewMatrix().map(QPointF(GetPositionX(),GetPositionY()));
	QMatrix trans;
	trans.translate(pos_in_view.x(),pos_in_view.y());
	switch(Scene2D::GetPointer()->m_radar_id)
	{
	case 1:
		{
			if (Scene2D::GetPointer()->m_change_plot_size_flag_radar1 == 1)
			{
				m_bounding_rect_in_view_radar1 = trans.mapRect(POINT_IMAGE_LARGE);
			}
			else
				m_bounding_rect_in_view_radar1 = trans.mapRect(POINT_IMAGE_MIN);
			render->drawEllipse(m_bounding_rect_in_view_radar1);
		}
		break;
	case 2:
		{
			if (Scene2D::GetPointer()->m_change_plot_size_flag_radar2 == 1)
			{
				m_bounding_rect_in_view_radar2 = trans.mapRect(POINT_IMAGE_LARGE);
			}
			else
				m_bounding_rect_in_view_radar2 = trans.mapRect(POINT_IMAGE_MIN);
			render->drawEllipse(m_bounding_rect_in_view_radar2);
		}
		break;
	case 3:
		{
			if (Scene2D::GetPointer()->m_change_plot_size_flag_radar3 == 1)
			{
				m_bounding_rect_in_view_radar3 = trans.mapRect(POINT_IMAGE_LARGE);
			}
			else
				m_bounding_rect_in_view_radar3 = trans.mapRect(POINT_IMAGE_MIN);
			render->drawEllipse(m_bounding_rect_in_view_radar3);
		}
		break;
	default:
		break;
	}



	///-------------------------------------------------------
	render->restore();	
}

bool Point::HitTest(const QPointF& pointf_in_view)
{
	return PointInRectRough(pointf_in_view,m_bounding_rect_in_view_radar1);
}