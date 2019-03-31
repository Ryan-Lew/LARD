#include "XYScene2D.h"
#include "XYView2D.h"


XYScene2D::XYScene2D(float size_x,float size_y) : 
m_xy_view2D(NULL),
m_size(size_x,size_y),
m_current_x(size_x / 2.0f),
m_current_y(size_y / 2.0f),
m_displaying_plots(true)
{
}

XYScene2D::~XYScene2D()
{ 

}

float XYScene2D::GetCurrentX() const
{
	return m_current_x;
}


float XYScene2D::GetCurrentY() const
{
	return m_current_y;
}


const QSizeF& XYScene2D::GetSize() const
{
	return m_size;
}



void XYScene2D::SetXYView(XYView2D* xy_view)
{
	m_xy_view2D = xy_view;
}

XYView2D* XYScene2D::GetXYView()
{
	return m_xy_view2D;
}

void XYScene2D::Draw()
{
	QPainter* render = m_xy_view2D->GetRender();

	if (m_displaying_plots)
	{
		QMatrix trans;
		for (XY_DATA_LIST_CONST_ITERATOR point = m_xy_data_list.begin(); point != m_xy_data_list.end(); ++point)
		{			
			QPointF pos_in_world(point->m_frame_num,point->m_value);
			if (m_xy_view2D->IsInView(pos_in_world))
			{
				render->save();
				{
					switch( point->m_type )
					{
					case ORIGINAL_PLOT:
						render->setPen(QPen(ORIGINAL_PLOT_COLOR_RADAR1,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
						render->setBrush(QBrush(ORIGINAL_PLOT_COLOR));
						break;
					case AGGLOMERATOR_PLOT:
						render->setPen(QPen(ORIGINAL_PLOT_COLOR_RADAR2,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
						render->setBrush(QBrush(AGGLOMERATOR_PLOT_COLOR));
						break;
					case POLAR_FILTERED_PLOT:
						render->setPen(QPen(ORIGINAL_PLOT_COLOR_RADAR3,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
						render->setBrush(QBrush(ORIGINAL_PLOT_COLOR));
						break;
					}	
					QPointF pos_in_view = m_xy_view2D->GetViewMatrix().map(pos_in_world);
					trans.reset();
					trans.translate(pos_in_view.x(),pos_in_view.y());
					render->drawEllipse(trans.mapRect(POINT_IMAGE_MINI));
				}	
				render->restore();
			}
		}	
	}
}


void XYScene2D::AddXYData(INT32 frame_num,float value,PLOT_TYPE type)
{
	INT32 size = m_xy_data_list.size();
	if (m_xy_data_list.size() > XY_SCENE_2D_MAX_PLOT_NUMS)
	{
		m_xy_data_list.pop_front();
	}
	m_xy_data_list.push_back(XY_DATA(frame_num,value,type));
	m_current_x = frame_num;
	m_current_y = value;
}


void XYScene2D::ClearPlotList()
{
	m_xy_data_list.clear();
}


void XYScene2D::SetDisplayingPlots(bool on)
{
	m_displaying_plots = on;
}



template<> VelocityScene2D* Singleton<VelocityScene2D>::m_singleton = 0;
template<> DistanceScene2D* Singleton<DistanceScene2D>::m_singleton = 0;
template<> AngleScene2D* Singleton<AngleScene2D>::m_singleton = 0;

template<> VelocityScene2DRadar2* Singleton<VelocityScene2DRadar2>::m_singleton = 0;
template<> DistanceScene2DRadar2* Singleton<DistanceScene2DRadar2>::m_singleton = 0;
template<> AngleScene2DRadar2* Singleton<AngleScene2DRadar2>::m_singleton = 0;

template<> VelocityScene2DRadar3* Singleton<VelocityScene2DRadar3>::m_singleton = 0;
template<> DistanceScene2DRadar3* Singleton<DistanceScene2DRadar3>::m_singleton = 0;
template<> AngleScene2DRadar3* Singleton<AngleScene2DRadar3>::m_singleton = 0;