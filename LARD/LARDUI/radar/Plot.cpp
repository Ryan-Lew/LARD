#include "Plot.h"
#include "View2D.h"

QRectF Plot::m_circle_image = QRectF(-1.0f,-1.0f,2.0f,2.0f);

Plot::Plot(float pos_x,float pos_y,const QColor& color /* = QColor */):Graphic(pos_x,pos_y),m_color(color)
{

}

void Plot::SetColor(const QColor& color)
{
	m_color = color;
}


void Plot::Draw(View2D* view)
{
	QPainter* render = view->GetRender();
	render->save();
	render->setPen(QPen(m_color,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	render->setBrush(QBrush(m_color));

	/////-----------�㼣���ų�����С����-------------------------------------------
	//render->setWorldTransform(QTransform(GetTransform() * view->GetViewMatrix()));
	//render->drawEllipse(m_circle_image);
	/////--------------------------------------------------------------------------


	///-----------�㼣��С���ֲ���----------------------
	QPointF pos_in_view = view->GetViewMatrix().map(QPointF(GetPositionX(),GetPositionY()));
	QMatrix trans;
	trans.translate(pos_in_view.x(),pos_in_view.y());
	render->drawEllipse(trans.mapRect(m_circle_image));
	///-------------------------------------------------------

	render->restore();	
}