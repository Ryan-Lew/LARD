#include "Scene2D.h"
#include "Radar.h"
#include "Point.h"
#include "Target.h"
#include "View2D.h"



#include <sstream>
#include <iomanip>

template<> Scene2D* Singleton<Scene2D>::m_singleton = 0;

Scene2D::Scene2D(float radar_measure_radius) : 
m_view2D(NULL),
m_size(radar_measure_radius * 2.0F,radar_measure_radius * 2.0F),
m_radar(new Radar(radar_measure_radius)),
m_selected_target(NULL),
m_displaying_targets(true),
m_displaying_plots_radar1(true),
m_displaying_plots_radar2(true),
m_displaying_plots_radar3(true)
{
	m_change_plot_size_flag_radar1 = 0;
	m_change_plot_size_flag_radar2 = 0;
	m_change_plot_size_flag_radar3 = 0;
	m_frame_change_plot_size = 0;
	m_frame_change_plot_size = 0;
	m_radar_id               = 0;
}

Scene2D::~Scene2D()
{ 
	delete m_radar;
	m_radar = NULL;

	ClearTargetList();

	ClearPlotList();

	/////////////ADS----------------------------------
	for (ADS_TARGET_LIST_ITERATOR pos = m_ads_target_list.begin(); pos != m_ads_target_list.end(); ++pos)
	{
		delete pos->second.m_target;
	}
	m_ads_target_list.clear();
	/////////////ADS----------------------------------
}


void Scene2D::SetView(View2D* view2d)
{
	m_view2D = view2d;
}

View2D* Scene2D::GetView()
{
	return m_view2D;
}

void Scene2D::Draw()
{
	m_radar->Draw(m_view2D);


	if (m_displaying_plots_radar1)
	{	
		m_radar_id = 1;
		for (PLOT_LIST_ITERATOR it = m_plot_list_radar1.begin(); it != m_plot_list_radar1.end(); ++it)
		{

			(*it)->Draw(m_view2D);
		}
	}
	if (m_displaying_plots_radar2)
	{
		m_radar_id = 2;
		for (PLOT_LIST_ITERATOR it = m_plot_list_radar2.begin(); it != m_plot_list_radar2.end(); ++it)
		{

			(*it)->Draw(m_view2D);
		}

	}
	if (m_displaying_plots_radar3)
	{
		m_radar_id = 3;
		for (PLOT_LIST_ITERATOR it = m_plot_list_radar3.begin(); it != m_plot_list_radar3.end(); ++it)
		{

			(*it)->Draw(m_view2D);
		}
	}
		
	
	/////////ADS--------------------------------
	for (ADS_TARGET_LIST_ITERATOR pos = m_ads_target_list.begin(); pos != m_ads_target_list.end(); ++pos)
	{
		pos->second.m_target->Draw(m_view2D);
	}
	/////////ADS--------------------------------

	if (m_displaying_targets)
	{
		for (TARGET_LIST_ITERATOR it = m_target_list.begin(); it != m_target_list.end(); ++it)
		{
			it->second->Draw(m_view2D);
		}
	}
}

bool Scene2D::HitTest(const QPointF& pointf_in_view)
{
	for (TARGET_LIST_ITERATOR it = m_target_list.begin(); it != m_target_list.end(); ++it)
	{
		if (it->second->HitTest(pointf_in_view))
		{
			SelectTarget(it->second);	

			return true;
		}
	}	
	return false;
}

void Scene2D::SelectTarget(Target* target)
{
	if (m_selected_target)
	{
		m_selected_target->SetState(Graphic::Visible);
	}
	target->SetState(Graphic::HighLight);
	m_selected_target = target;
}

void Scene2D::SelectTarget(UINT32 block)
{
	TARGET_LIST_ITERATOR it = m_target_list.find(block);
	if (it != m_target_list.end())
	{
		SelectTarget(it->second);	
	}

}


Target* Scene2D::CreateTarget(UINT32 id, float x_in_scene, float y_in_scene, float direction_in_scene)
{
	std::ostringstream os;
	os<<std::setw(3)<<std::right<<std::setfill('0')<<id;
	Target* target = new Target( id,os.str(),x_in_scene,y_in_scene,direction_in_scene,TARGET_COLOR,TARGET_HIGHLIGHT_COLOR);
	m_target_list.insert(std::make_pair(id,target));
	return target;
}

void Scene2D::DeleteTarget(UINT32 id)
{
	TARGET_LIST_ITERATOR it = m_target_list.find(id);
	if (it != m_target_list.end())
	{
		if (it->second == m_selected_target)
		{
			m_selected_target = NULL;
		}
		delete it->second;
		it->second = NULL;
		m_target_list.erase(it);
	}
}

void Scene2D::ClearTargetList()
{

	for (TARGET_LIST_ITERATOR it = m_target_list.begin(); it != m_target_list.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}
	m_target_list.clear();
	m_selected_target = NULL;
}


double Scene2D::DecodeDirection(float x_off,float y_off)
{
	double rho   = 0;
	double theta = 0;
	OrthogonalToPolar(x_off,y_off,&rho,&theta);
	return theta;
}

void Scene2D::DecodeTrackData(double pos_x,double pos_y,double* x_in_scene,double* y_in_scene)
{
	double distance = 0.0; double angle = 0.0;
	OrthogonalToPolar( pos_x, pos_y, &distance, &angle );
	double angle_in_scene = 90.0 - angle;
	angle_in_scene = ( angle_in_scene > 0 ) ? angle_in_scene : ( angle_in_scene + 360.0 );
	PolarToOrthogonal( distance, angle_in_scene, x_in_scene, y_in_scene );

}

void Scene2D::UpdateTarget(UINT32 id, double pos_x,double pos_y,double vel_x,double vel_y)
{
	double x_in_scene = 0.0; double y_in_scene = 0.0; 
	DecodeTrackData( pos_x, pos_y, &x_in_scene, &y_in_scene);

	TARGET_LIST_ITERATOR it = m_target_list.find(id);
	if (it != m_target_list.end())
	{
		Target* target = it->second;
		target->Update( x_in_scene,y_in_scene,0);
	}
	else
	{
		CreateTarget(id,x_in_scene,y_in_scene,0); 
	}
}

const QSize& Scene2D::GetSize() const
{
	return m_size;
}

void Scene2D::AddPlot(double pos_x,double pos_y,PLOT_TYPE type,int frame_number,int radar)
{
	if ( m_plot_list_radar1.size() == SCENE_2D_MAX_PLOT_NUMS )
	{
		delete m_plot_list_radar1.front();
		m_plot_list_radar1.pop_front();
	}
	switch( type )
	{
	case ORIGINAL_PLOT:
		{
			switch(radar)
			{
			case 1:
				m_plot_list_radar1.push_back( new Point( pos_x,pos_y,ORIGINAL_PLOT_COLOR_RADAR1,frame_number ) );
				break;
			case 2:
				m_plot_list_radar2.push_back(new Point( pos_x,pos_y,ORIGINAL_PLOT_COLOR_RADAR2,frame_number ));
				break;
			case 3:
				m_plot_list_radar3.push_back(new Point( pos_x,pos_y,ORIGINAL_PLOT_COLOR_RADAR3,frame_number ));

			}

		}
		break;
	case AGGLOMERATOR_PLOT:
		m_plot_list_radar1.push_back( new Point( pos_x,pos_y,AGGLOMERATOR_PLOT_COLOR,frame_number ) );
		break;
	case  POLAR_FILTERED_PLOT:
		m_plot_list_radar1.push_back(new Point(pos_x,pos_y,ORIGINAL_PLOT_COLOR_PIPEI,frame_number));
		break;
	}	
    //m_frame_change_plot_size = setRadarWorkparm::GetPointer()->m_frame_number;

}

void Scene2D::ClearPlotList()
{
	for (PLOT_LIST_ITERATOR it = m_plot_list_radar1.begin(); it != m_plot_list_radar1.end(); ++it)
	{
		delete (*it);
	}
	m_plot_list_radar1.clear();
	for (PLOT_LIST_ITERATOR it = m_plot_list_radar2.begin(); it != m_plot_list_radar2.end(); ++it)
	{
		delete (*it);
	}
	m_plot_list_radar2.clear();
	for (PLOT_LIST_ITERATOR it = m_plot_list_radar3.begin(); it != m_plot_list_radar3.end(); ++it)
	{
		delete (*it);
	}
	m_plot_list_radar3.clear();
}



void Scene2D::SetDisplayingTargets(bool on)
{
	m_displaying_targets = on;
}

void Scene2D::SetDisplayingPlotsRadar1(bool on)
{
	m_displaying_plots_radar1 = on;
}

void Scene2D::SetDisplayingPlotsRadar2(bool on)
{
	m_displaying_plots_radar2 = on;
}

void Scene2D::SetDisplayingPlotsRadar3(bool on)
{
	m_displaying_plots_radar3 = on;
}


/////////////ADS----------------------------------

void Scene2D::UpdateADSTarget(UINT32 id,const std::string& label_text,double rho,double alpha,double beta,double ew_velocity,double sn_velocity,double up_velocity)
{
	if (rho > 120000.0)
	{
		return;
	}
	double alpha_R = alpha / 360.0 * MY_2PI;
	double x_in_scene = rho * cos(alpha_R);
	double y_in_scene = rho * sin(alpha_R); 
	double vel_abs    = sqrt(ew_velocity*ew_velocity + sn_velocity*sn_velocity + up_velocity*up_velocity);
	double snr        = 0.0;
	ADS_TARGET_LIST_ITERATOR it = m_ads_target_list.find(id);
	if (it != m_ads_target_list.end())
	{
		it->second.m_target->Update(x_in_scene,y_in_scene,DecodeDirection(ew_velocity,sn_velocity));
		it->second.m_time = QDateTime::currentDateTime();
	}
	else
	{
		ADS_TARGET ads_target;
		ads_target.m_target = new Target( id,label_text,x_in_scene,y_in_scene,DecodeDirection(ew_velocity,sn_velocity),ADS_TARGET_COLOR,ADS_TARGET_COLOR,150);
		ads_target.m_time   = QDateTime::currentDateTime();
		m_ads_target_list.insert(std::make_pair(id,ads_target));
	}
}

const double Scene2D::m_ads_target_time_out_ms = 20000;


void Scene2D::UpdateADSTargetList()
{
	QDateTime now = QDateTime::currentDateTime();
	for (ADS_TARGET_LIST_ITERATOR pos = m_ads_target_list.begin(); pos != m_ads_target_list.end(); )
	{
		if ( GetMillisecondIntervals(pos->second.m_time,now) > m_ads_target_time_out_ms)
		{
			delete pos->second.m_target;
			m_ads_target_list.erase(pos++);
		}
		else
		{
			++pos;
		}
	}
}

/////////////ADS----------------------------------
