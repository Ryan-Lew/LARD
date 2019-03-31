#ifndef ___SECENE_H___
#define ___SECENE_H___

#include <Windows.h>
#include <map>
#include <deque>
#include "Singleton.h"
#include "Utility.h"


class View2D;
class Radar;
class Point;
class Target;

class Scene2D :  public Singleton<Scene2D>
{
public:
	typedef std::map<UINT32,Target*> TARGET_LIST;
	typedef TARGET_LIST::iterator	 TARGET_LIST_ITERATOR;
	typedef std::deque<Point*>       PLOT_LIST;
	typedef PLOT_LIST::iterator      PLOT_LIST_ITERATOR;
public:
	Scene2D(float radar_measure_radius);
	virtual ~Scene2D();
	void Draw();
	const QSize& GetSize() const;
	void SetView(View2D* view);
	View2D* GetView();
	bool HitTest(const QPointF& pointf_in_view);
	void UpdateTarget(UINT32 id, double pos_x,double pos_y,double vel_x,double vel_y);
	void AddPlot(double pos_x,double pos_y,PLOT_TYPE type,int frame,int radar);
	void SelectTarget(UINT32 block);
	void ClearPlotList();
	void ClearTargetList();
	void DeleteTarget(UINT32 id);
	void SetDisplayingTargets(bool on);
	void SetDisplayingPlotsRadar1(bool on);
	void SetDisplayingPlotsRadar2(bool on);
	void SetDisplayingPlotsRadar3(bool on);

	int		m_change_plot_size_flag_radar1;
	int		m_change_plot_size_flag_radar2;
	int		m_change_plot_size_flag_radar3;

	int    m_change_plot_size_frame;
	int    m_frame_change_plot_size;
	int    m_radar_id;
private:
	static void   DecodeTrackData(double pos_x,double pos_y,double* x_in_scene,double* y_in_scen);
	static double DecodeDirection(float x_off,float y_off);
	void    SelectTarget(Target* target);
	Target* CreateTarget(UINT32 id, float x_in_scene, float y_in_scene, float direction_in_scene);	
private:
	View2D*      m_view2D;
	TARGET_LIST  m_target_list;
	Radar*       m_radar;
	QSize        m_size;
	PLOT_LIST    m_plot_list_radar1;
	PLOT_LIST    m_plot_list_radar2;
	PLOT_LIST    m_plot_list_radar3;
	Target*      m_selected_target;
private:
	bool         m_displaying_targets;
	bool         m_displaying_plots_radar1;
	bool		 m_displaying_plots_radar2;
	bool         m_displaying_plots_radar3;

//////////////////////ADS------------------------------------
private:
	struct ADS_TARGET
	{
		Target*   m_target;
		QDateTime m_time;
	};
	typedef std::map<UINT32,ADS_TARGET>  ADS_TARGET_LIST;
	typedef ADS_TARGET_LIST::iterator    ADS_TARGET_LIST_ITERATOR;
public:
	void UpdateADSTarget(UINT32 id,const std::string& label_text,double rho,double alpha,double beta,double ew_velocity,double sn_velocity,double up_velocity);
	void UpdateADSTargetList();

private:
	ADS_TARGET_LIST     m_ads_target_list;
	static const double m_ads_target_time_out_ms;

//////////////////////ADS------------------------------------

};

#endif