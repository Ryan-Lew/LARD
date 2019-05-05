#include "XYView2D.h"
#include <QAction>
#include <QApplication>
#include <QMatrix>
#include "XYScene2D.h"
#include "Utility.h"


XYView2D::XYView2D(QWidget* parent,XYScene2D* xy_scene,float zoom_step,float mark_step_x,float mark_step_y) :
QWidget(parent),
m_render(new QPainter),
m_xy_scene(xy_scene),
m_last_cursor(0.0f,0.0f),
m_zoom_step(zoom_step),
m_zoom_scale_x(1.0f),
m_zoom_scale_y(1.0f),
m_mark_step_x(mark_step_x),
m_mark_step_y(mark_step_y),
m_moving_mode(true),
m_rect_scaling(false)
{
    m_view_matrix.reset();
    m_xy_scene->SetXYView(this);
    setAutoFillBackground(false);
    setMinimumSize(300,200);
    m_view_size_x    = 300;
    m_view_size_y    = 200;
    m_scene_size_x   = xy_scene->GetSize().width();
    m_scene_size_y   = xy_scene->GetSize().height();
    m_scene_offset_x = m_scene_size_x / 2.0F;
    m_scene_offset_y = m_scene_size_y / 2.0F;
    setAutoFillBackground(false);
    this->setFocusPolicy( Qt::ClickFocus );
    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
}

XYView2D::~XYView2D()
{
	delete m_render;
	m_render = NULL;
}

void XYView2D::resizeEvent(QResizeEvent* event )
{
	m_view_size_x = this->size().width();
	m_view_size_y = this->size().height();
	UpdateViewMatrix();
	Draw();
	QWidget::resizeEvent(event);
}

QPainter* XYView2D::GetRender()
{
	return m_render;
}

void XYView2D::paintEvent(QPaintEvent* event)
{
	if (m_moving_mode)
	{
		m_scene_offset_x = m_xy_scene->GetCurrentX();
		UpdateViewMatrix();
	}
	m_render->begin(this);
	m_render->setRenderHint(QPainter::Antialiasing,true);
	m_render->fillRect(QRectF(QPointF(0.0,0.0),this->size()),XY_VIEW_BACKGROUND_BRUSH);
	m_xy_scene->Draw();
	DrawAxises();
	DrawMarks();
	DrawScaleRect();
	m_render->end();
}

void XYView2D::DrawAxises()
{
	m_render->save();
	m_render->setPen(QPen(XY_VIEW_AXIS_PEN,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	m_render->setBrush(XY_VIEW_MARK_BRUSH);
	m_render->drawLine(0.0f,m_view_size_y - m_mark_step_y,m_view_size_x,m_view_size_y - m_mark_step_y);
	m_render->drawLine(m_mark_step_x,m_view_size_y,m_mark_step_x,0);	
	m_render->restore();
}

void XYView2D::DrawMarks()
{	
	QMatrix inverted = m_view_matrix.inverted();
	m_render->save();
	m_render->setPen(QPen(XY_VIEW_MARK_PEN,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	m_render->setBrush(XY_VIEW_MARK_BRUSH);

	float x_mark_y = m_view_size_y - m_mark_step_y;
	for (float x_mark_x = m_mark_step_x * 2.0f; x_mark_x < m_view_size_x; x_mark_x = x_mark_x + m_mark_step_x)
	{		
		QPointF pos_view(x_mark_x,x_mark_y);
		QPointF pos_world = inverted.map(pos_view);
		m_render->drawLine(x_mark_x,x_mark_y,x_mark_x,x_mark_y-5);
		m_render->drawText(x_mark_x - m_mark_step_x / 2.0f, x_mark_y,m_mark_step_x,m_mark_step_y, Qt::AlignCenter, QString("%1").arg( (int)(pos_world.x()) ) );
	}
	float y_mark_x = m_mark_step_x;
	for (float y_mark_y = m_view_size_y - m_mark_step_y *2.0f; y_mark_y  > 0; y_mark_y = y_mark_y - m_mark_step_y)
	{
		QPointF pos_view(y_mark_x,y_mark_y);
		QPointF pos_world = inverted.map(pos_view);
		m_render->drawLine(y_mark_x,y_mark_y,y_mark_x + 5,y_mark_y);
		m_render->drawText(y_mark_x - m_mark_step_x, y_mark_y - m_mark_step_y / 2.0f,m_mark_step_x,m_mark_step_y, Qt::AlignRight | Qt::AlignVCenter, QString("%1").arg(pos_world.y(),0,'f',1)  );
	}
	m_render->restore();
}

XYScene2D* XYView2D::GetXYScene()
{
	return m_xy_scene;
}

const QMatrix& XYView2D::GetViewMatrix() const
{
	return m_view_matrix;
}

void XYView2D::mousePressEvent (QMouseEvent* event)
{
    m_last_cursor = event->pos();
// 	if (event->button() == Qt::LeftButton)
// 	{
//  		if (m_scene->HitTest(m_last_cursor))//取消左键移动视图
//  		{
// 			Draw();
//  		}
// 
// 	}
	if (event->button() == Qt::RightButton)
	{
		m_scale_rect_left_top    = m_last_cursor;
		m_scale_rect_right_bottom = m_last_cursor;
	}	
}

void XYView2D::mouseMoveEvent(QMouseEvent* event)
{
	if (QApplication::mouseButtons().testFlag(Qt::LeftButton))
	{	
		if (!m_moving_mode)
		{
			this->setCursor(Qt::ClosedHandCursor);
			QMatrix inverted = m_view_matrix.inverted();
            QPointF curr_in_scene = inverted.map(event->pos());
			QPointF last_in_scene = inverted.map(m_last_cursor);
			m_scene_offset_x += last_in_scene.x() - curr_in_scene.x();
			m_scene_offset_y += last_in_scene.y() - curr_in_scene.y();
            m_last_cursor = event->pos();
			UpdateViewMatrix();
			Draw();
		}
	}
	else if (QApplication::mouseButtons().testFlag(Qt::RightButton))
	{
		m_rect_scaling = true;
        m_scale_rect_right_bottom = event->pos();
		Draw();
	}
}

void XYView2D::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton )
	{
		this->setCursor(Qt::ArrowCursor);		
	}
	else if (event->button() == Qt::RightButton)
	{
		if (m_rect_scaling)
		{	
			m_rect_scaling = false;
			QPointF center_in_scene = m_view_matrix.inverted().map( (m_scale_rect_left_top +  m_scale_rect_right_bottom ) / 2.0f );
			m_scene_offset_x = center_in_scene.x();
			m_scene_offset_y = center_in_scene.y();
			float rect_w = abs(m_scale_rect_right_bottom.x() - m_scale_rect_left_top.x());
			float rect_h = abs(m_scale_rect_right_bottom.y() - m_scale_rect_left_top.y());
			if (rect_w > 0.0f && rect_h > 0.0f)
			{
				float scale_x = (this->size().width() ) / rect_w;
				float scale_y = (this->size().height()) / rect_h;
// 				float scale   = (scale_x < scale_y) ? scale_x : scale_y;
				m_zoom_scale_x = m_zoom_scale_x * scale_x;
				m_zoom_scale_y = m_zoom_scale_y * scale_y;
			}			
			UpdateViewMatrix();
			Draw();
		}
	}
}

void XYView2D::UpdateViewMatrix()
{
	float view_x = m_view_size_x - 2 * m_mark_step_x;
	float view_y = m_view_size_y - 2 * m_mark_step_y;
	float m11 =  view_x / m_scene_size_x * m_zoom_scale_x;
	float m22 = -view_y / m_scene_size_y * m_zoom_scale_y;
	float dx  =  m_view_size_x / 2.0F - m_scene_offset_x * m11;
	float dy  =  m_view_size_y / 2.0F - m_scene_offset_y * m22;
	m_view_matrix.setMatrix(m11,0.0f,0.0f,m22,dx,dy);
	m_clut_rect_world = m_view_matrix.inverted().mapRect(rect());
}

void XYView2D::Draw()
{
	repaint();
}

void XYView2D::wheelEvent(QWheelEvent* event)
{
	event->accept();
	event->delta() > 0 ? this->ZoomIn() : this->ZoomOut();
}

void XYView2D::ZoomIn()
{
	m_zoom_scale_x = m_zoom_scale_x  * m_zoom_step;
	m_zoom_scale_y = m_zoom_scale_y  * m_zoom_step; 
	UpdateViewMatrix();
	Draw();
}

void XYView2D::ZoomOut()
{
	m_zoom_scale_x = m_zoom_scale_x  / m_zoom_step;
	m_zoom_scale_y = m_zoom_scale_y  / m_zoom_step; 
	UpdateViewMatrix();
	Draw();
}


bool XYView2D::IsInView(const QPointF& point_wold)
{
	return PointInRectStrict(point_wold,m_clut_rect_world);
}

void XYView2D::SetMovingMode(bool is_auto)
{
	m_moving_mode = is_auto;
}


void XYView2D::DrawScaleRect()
{
	if (m_rect_scaling)
	{
		float x = m_scale_rect_left_top.x(); 
		float y = m_scale_rect_left_top.y();
		float w = m_scale_rect_right_bottom.x() - x;
		float h = m_scale_rect_right_bottom.y() - y;
		if (0.0 != w && 0.0 != h)
		{
			m_render->save();
			{
				m_render->setBrush(Qt::transparent);
				m_render->setPen(QPen(QColor(255, 255,255, 255),0.0f,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
				m_render->drawRect(x,y,w,h);
			}
			m_render->restore();	
		}
	}
}

void XYView2D::mouseDoubleClickEvent(QMouseEvent * event)
{
	Reset();
	if (m_moving_mode)
	{
		m_moving_mode = false;
	}
	else
		m_moving_mode = true;
}

void XYView2D::Reset()
{
	m_zoom_scale_x     = 1.0f;
	m_zoom_scale_y     = 1.0f;
// 	m_scene_offset_x = 0.0f;
// 	m_scene_offset_y = 0.0f;

	UpdateViewMatrix();
	Draw();
}

