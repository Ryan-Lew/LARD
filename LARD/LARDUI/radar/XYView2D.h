#ifndef ___XY_VIEW2D_H___
#define ___XY_VIEW2D_H___

#include "XInterface.h"
#include <QPainter>
#include <QMatrix>
#include <QMouseEvent>
#include <QKeyEvent>



class XYScene2D;
class XYView2DInterface;

class XYView2D : public QWidget
{
	Q_OBJECT
public:
     XYView2D(QWidget* parent,XYScene2D* xy_scene,float zoom_step = 2.0f,float mark_step_x = 40.0F,float mark_step_y = 20.0F);

    virtual ~XYView2D();
	QPainter*   GetRender();
	XYScene2D*  GetXYScene();
	const QMatrix& GetViewMatrix() const;
	void  Draw();
	bool  IsInView(const QPointF& point_wold);
	void  SetMovingMode(bool is_auto);
	void  SetMarkStep(float mark_step_x,float mark_step_y);
protected:
	void DrawAxises();
	void DrawMarks();
	void UpdateViewMatrix();
public slots:
	void  ZoomIn();
	void  ZoomOut();
protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event );
	virtual void mouseDoubleClickEvent(QMouseEvent * event);

private:
	QPainter*    m_render;
	XYScene2D*   m_xy_scene;
	QMatrix      m_view_matrix;
	QPointF      m_last_cursor;	
	float        m_zoom_scale_x;
	float        m_zoom_scale_y;
	float        m_zoom_step;
	float        m_scene_offset_x;
	float        m_scene_offset_y;
	float        m_scene_size_x;
	float        m_scene_size_y;
	float        m_mark_step_x;
	float        m_mark_step_y;
	float        m_view_size_x;
	float        m_view_size_y;
	bool         m_moving_mode;
private:
	QRectF       m_clut_rect_world;
private:
	XYView2DInterface*   m_view_interface;
private:
	void         DrawScaleRect();
	void         Reset();
	bool         m_rect_scaling;
	QPointF      m_scale_rect_left_top;
	QPointF      m_scale_rect_right_bottom;
};

#endif
