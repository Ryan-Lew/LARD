#ifndef ___VIEW2D_H___
#define ___VIEW2D_H___

#include <QGLWidget>
#include <QPainter>
#include <QMatrix>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QPointF>
#include "../radar/Singleton.h"



class Scene2D;

class View2D : public QWidget,public Singleton<View2D>
{
	Q_OBJECT
public:
	View2D(QWidget* parent,Scene2D* scene,float zoom_step = 1.025f,float margin = 20.0F);
	virtual ~View2D();
	QPainter* GetRender();
	Scene2D*  GetScene();
	const QMatrix& GetViewMatrix() const;
	void  Draw();
	void  loadMenu();
    void initShipPoint();
    void DrawShip(QPainter *painter);
    QPointF RotaryAngle(QPointF centerPt,QPointF lastPt);
	BOOL b_dispGPSinfo;
	BOOL b_leftbutton_press;
protected:
	void UpdateViewMatrix();
	public slots:
		void  ZoomIn();
		void  ZoomOut();
		void  Reset();
		void  clear_plot();
		void  clear_track();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
        //双击还原
	virtual void mouseDoubleClickEvent(QMouseEvent * event);


private:
	QPainter* m_render;
private:
	Scene2D*  m_scene;
	QMatrix   m_view_matrix;
	QPointF   m_last_cursor;	
	float     m_margin;
	float     m_zoom_scale;
	float     m_zoom_step;
	float     m_scene_offset_x;
	float     m_scene_offset_y;
	float     m_scene_size_x;
	float     m_scene_size_y;
    int m_width;
    int m_height;

    QPointF m_centerPoint;
    QPointF m_headShipPoint;     //船头
    QPointF m_headLeftShipPoint;     //船头
    QPointF m_headRightShipPoint;
    QPointF m_tailLeftShipPoint;
    QPointF m_tailRightShipPoint;
private:
	void      DispLeftPressInfo();
	void      DrawScaleRect();
	bool      m_rect_scaling;
	bool      m_translating_label;
	bool		 m_right_mouse_down;
	bool		 m_right_mouse_up;
	bool      m_right_mouse_move;
	bool      b_right_mouse_scal;//设置鼠标右键选择区域后不显示坐标点
	QPointF   m_scale_rect_left_top;
	QPointF   m_scale_rect_right_bottom;
	QMenu    *m_main_menu;
	QAction  *m_clear_plot_action;
	QAction  *m_clear_track_action;
	QAction  *m_hide_plot_action_radar1;
	QAction  *m_hide_plot_action_radar2;
	QAction  *m_hide_plot_action_radar3;
	QAction  *m_hide_track_action;
	QPoint      m_right_mouse_place;//鼠标右键位置
	QPointF      m_left_mouse_location;//鼠标左键位置
	QPixmap  m_clear_map;
	QPixmap  m_hide_map;
	BOOL	  bDis_plot_radar1;
	BOOL	  bDis_plot_radar2;
	BOOL	  bDis_plot_radar3;
	BOOL    bDis_track;
	float        m_left_mouse_angle;
	float        m_left_mouse_dist;


};

#endif
