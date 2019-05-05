#include <QPointF>
#include <QFont>
#include "Label.h"
#include "Target.h"
#include "View2d.h"
#include "Scene2D.h"
#include "Utility.h"


QRectF  Label::m_origin_text_rect   = QRectF(-10.0f,-10.0f,20.0f,20.0f);

float   Label::m_origin_relative_to_aircraft_x = 12.0f;
float   Label::m_origin_relative_to_aircraft_y = 10.0f;

Label::Label(Target* target,const std::string& label_text) : 
Graphic(m_origin_relative_to_aircraft_x,m_origin_relative_to_aircraft_y),
m_target(target),
m_label_text(label_text)
{

}

Label::~Label()
{
}

void Label::Draw(View2D* view)
{	
	QPointF target_pos_in_view = ( view->GetViewMatrix() ).map( QPointF( m_target->GetPositionX(),m_target->GetPositionY() ) );	

	QMatrix transform_in_view;
	transform_in_view.translate(target_pos_in_view.x() + GetPositionX(),target_pos_in_view.y() + GetPositionY());
	QRectF text_rect_in_view = transform_in_view.mapRect( m_origin_text_rect );
	
	QPainter* render = view->GetRender();

	QFont font("Times New Roman",10);
	font.setBold(true);

	render->save();
	{
		render->setFont(font);
		m_bounding_rect_in_view = render->boundingRect(text_rect_in_view,Qt::AlignLeft|Qt::AlignVCenter|Qt::TextIncludeTrailingSpaces,Chinese(m_label_text.c_str()));
	}
	render->restore();

	if (Graphic::HighLight == GetState())
	{
		render->save();
		{	
			render->setBrush(m_target->GetHighlightColor());	
			render->setPen(m_target->GetHighlightColor());
			render->setFont(font);
			render->drawText(m_bounding_rect_in_view,Qt::AlignLeft|Qt::AlignVCenter|Qt::TextIncludeTrailingSpaces,Chinese(m_label_text.c_str()),NULL);
		}
		render->restore();
	}
	else
	{
		render->save();
		{	
			render->setBrush(m_target->GetCommonColor());	
			render->setPen(m_target->GetCommonColor());
			render->setFont(font);
			render->drawText(m_bounding_rect_in_view,Qt::AlignLeft|Qt::AlignVCenter,Chinese(m_label_text.c_str()),NULL);
		}
		render->restore();
	}
}


bool Label::HitTest(const QPointF& pointf_in_view)
{
	return PointInRectRough(pointf_in_view,m_bounding_rect_in_view);
}
