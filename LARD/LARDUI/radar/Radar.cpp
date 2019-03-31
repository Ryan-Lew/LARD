#include <QTextCodec>
#include <QFont>
#include <QFontMetrics>
#include <cmath>
#include <sstream>
#include "Radar.h"
#include "View2D.h"
#include "Utility.h"



const int   Radar::m_circle_divided_count = 7;
const int   Radar::m_line_mark_count      = 28;
const int   Radar::m_line_divided_count   = 12;
const int   Radar::m_circle_mark_count    = 72;
const float Radar::m_mark_5_length        = 5.0f;
const float Radar::m_mark_1_length        = 2.0f;
const int   Radar::m_text_font_size       = 16;


Radar::Radar(float measure_radius) : m_measure_radius(measure_radius)
{
	///外圈园
	m_measure_circle.x = -m_measure_radius;
	m_measure_circle.y = -m_measure_radius;
	m_measure_circle.w = 2 * m_measure_radius;
	m_measure_circle.h = 2 * m_measure_radius;

	///十字线，横线
	m_horizontal_line.from_x = -m_measure_radius;
	m_horizontal_line.from_y = 0.0f;
	m_horizontal_line.to_x   = m_measure_radius;
	m_horizontal_line.to_y   = 0.0f;

	///十字线，竖线
	m_vertical_line.from_x = 0.0f;
	m_vertical_line.from_y = -m_measure_radius;
	m_vertical_line.to_x   = 0.0f;
	m_vertical_line.to_y   = m_measure_radius;

	///分割圈
	float circle_divided_step = m_measure_radius / m_circle_divided_count;
	for (int i = 0; i < m_circle_divided_count - 1; ++i)
	{
		CIRCLE* circle = new CIRCLE;
		float radius   = circle_divided_step * (i + 1) ;
		circle->x = 0.0f-radius;
		circle->y = 0.0f-radius;
		circle->w = 2 * radius;
		circle->h = 2 * radius;
		m_divided_circle_list.push_back(circle);
	}

	///分割线
	float line_divided_step = MY_2PI / m_line_divided_count;
	for (int i = 0; i < m_line_divided_count; ++i)
	{
		LINE* line = new LINE;
		line->from_x = 0.0f;
		line->from_y = 0.0f;
		float radian = line_divided_step * i;
		line->to_x   = m_measure_radius * cos(radian);
		line->to_y   = m_measure_radius * sin(radian);
		if (! ((static_cast<int>(line->from_x) == 0 && static_cast<int>(line->to_x) == 0 )  || (static_cast<int>(line->from_y) == 0 && static_cast<int>(line->to_y) == 0 ) ))
		{
			m_divided_line_list.push_back(line);
		}
	}


	QFont mark_font;
	mark_font.setPixelSize(m_text_font_size);
    QFontMetrics mark_font_metrics(mark_font);
    QTextCodec* textcodec = QTextCodec::codecForLocale();

    ///环形刻度和刻度文字
    float circle_mark_step_radian = MY_2PI / m_circle_mark_count;
    float circle_mark_step_degree = 360.0  / m_circle_mark_count;

    for (int i = 0; i < m_circle_mark_count; ++i)
    {
		MARK* mark = new MARK;
		float radian = circle_mark_step_radian * i;
		float degree = circle_mark_step_degree * i;
		mark->x = m_measure_radius * cos(radian);
		mark->y = m_measure_radius * sin(radian);

		mark->angle = degree;
		if (0 == ((int)degree % 5))
		{
			mark->length = m_mark_5_length;	
            if ( 0 == ((int)degree % 15))
			{
				TEXT_RD* text = new TEXT_RD;
				text->angle = (int)(450 - degree) % 360 ;
				text->x = mark->x;
				text->y = mark->y;
				std::ostringstream os;
                if(text->angle == 0){
                     os<<"N";
                }else if(text->angle == 90){
                     os<<"E";
                }else if(text->angle == 180){
                     os<<"W";
                }else if(text->angle == 270){
                     os<<"S";
                }else {
                    os<<text->angle<<"°";
                }


				QRectF font_rect = mark_font_metrics.boundingRect(textcodec->toUnicode(os.str().c_str()));
				text->path->addText(QPointF(-font_rect.width() / 2.0,-2.0), mark_font, textcodec->toUnicode(os.str().c_str()));
				m_scale_text_list.push_back(text);
			}
		}
		else
		{
			mark->length = m_mark_1_length;
		}
		m_scale_mark_list.push_back(mark);
	}

	///线刻度和刻度文字
	float line_mark_step = 2.0f * m_measure_radius / m_line_mark_count;
	for (int i = -m_line_mark_count / 2 + 1; i < m_line_mark_count / 2 ; ++i)
	{
		int length = line_mark_step * i;		
		MARK* mark_horizontal = new MARK;		
		mark_horizontal->x = length;
		mark_horizontal->y = 0.0f;
		MARK* mark_vertical   = new MARK;
		mark_vertical->x = 0.0f;
		mark_vertical->y = length;
		mark_horizontal->length = m_mark_5_length;
		mark_vertical->length   = m_mark_5_length;
		if ( (i != 0)  && (0 == ( i % 2)))
		{
			std::ostringstream os;
			os<<int(abs(length / 1000));
			QRectF font_rect = mark_font_metrics.boundingRect(textcodec->toUnicode(os.str().c_str()));
			TEXT_RD* horizontal_text = new TEXT_RD;
			horizontal_text->angle = 0.0 ;
			horizontal_text->x = mark_horizontal->x;
			horizontal_text->y = mark_horizontal->y;
			horizontal_text->path->addText(QPointF(-font_rect.width() / 2.0 - 1.0,font_rect.height() - 2.0), mark_font, textcodec->toUnicode(os.str().c_str()));
			m_scale_text_list.push_back(horizontal_text);
			TEXT_RD* vertical_text = new TEXT_RD;
			vertical_text->angle = 0.0 ;
			vertical_text->x = mark_vertical->x;
			vertical_text->y = mark_vertical->y;
			vertical_text->path->addText(QPointF(-font_rect.width() - 2.0,font_rect.height() / 2.0 - 2.0), mark_font, textcodec->toUnicode(os.str().c_str()));
			m_scale_text_list.push_back(vertical_text);
		}
		if ( 0 == i )
		{
			std::ostringstream os;
			os<<int(abs(length / 1000));
			QRectF font_rect = mark_font_metrics.boundingRect(textcodec->toUnicode(os.str().c_str()));
			TEXT_RD* horizontal_text = new TEXT_RD;
			horizontal_text->angle = 0.0 ;
			horizontal_text->x = mark_horizontal->x;
			horizontal_text->y = mark_horizontal->y;
			horizontal_text->path->addText(QPointF(-font_rect.width() / 2.0 - 3.0,font_rect.height() - 2.0), mark_font, textcodec->toUnicode(os.str().c_str()));
			m_scale_text_list.push_back(horizontal_text);
		}
		mark_horizontal->angle = -90.0;
		mark_vertical->angle = 180.0;
		m_scale_mark_list.push_back(mark_horizontal);
		m_scale_mark_list.push_back(mark_vertical);
	}
}

Radar::~Radar()
{
	for (LINE_LIST_ITERATOR it = m_divided_line_list.begin(); it != m_divided_line_list.end(); ++it)
	{
		delete (*it);
	}
	m_divided_line_list.clear();

	for (CIRCLE_LIST_ITERATOR it = m_divided_circle_list.begin(); it != m_divided_circle_list.end(); ++it)
	{
		delete (*it);
	}
	m_divided_circle_list.clear();

	for (MARK_LIST_ITERATOR it = m_scale_mark_list.begin(); it != m_scale_mark_list.end(); ++it)
	{
		delete (*it);
	}
	m_scale_mark_list.clear();

	for (TEXT_LIST_ITERATOR it = m_scale_text_list.begin(); it != m_scale_text_list.end(); ++it)
	{
		delete (*it);
	}
	m_scale_text_list.clear();
};

void Radar::Draw(View2D* view)
{
	QPainter* render = view->GetRender();
	render->save();
	{
		render->setWorldTransform( QTransform(view->GetViewMatrix()));

		render->save();
		{
			QRadialGradient radial_gradient(0.0f,0.0f,m_measure_radius,0.0f,0.0f);
			radial_gradient.setColorAt(0.0,PERPHERAL_CIRCLE_AND_CROSS_LINE_BRUSH_0);
			radial_gradient.setColorAt(1.0,PERPHERAL_CIRCLE_AND_CROSS_LINE_BRUSH_1);
			render->setBrush(radial_gradient);
			render->setPen(QPen(PERPHERAL_CIRCLE_AND_CROSS_LINE_PEN,40.0f,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
			/// 外圈园
			render->drawEllipse(m_measure_circle.x,m_measure_circle.y,m_measure_circle.w,m_measure_circle.h);
			/// 十字线
			render->drawLine(m_horizontal_line.from_x,m_horizontal_line.from_y,m_horizontal_line.to_x,m_horizontal_line.to_y);
			render->drawLine(m_vertical_line.from_x,m_vertical_line.from_y,m_vertical_line.to_x,m_vertical_line.to_y);
		}
		
		render ->restore();

		render->save();
		{
			render->setBrush(DIVIDED_CIRCLE_AND_DIVIDED_LINE_BRUSH);
			render->setPen(QPen(DIVIDED_CIRCLE_AND_DIVIDED_LINE_PEN,0.0f,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
			/// 分割圈
			for (CIRCLE_LIST_CONST_ITERATOR it = m_divided_circle_list.begin(); it != m_divided_circle_list.end(); ++it)
			{
				CIRCLE* circle = *it;
				render->drawEllipse(circle->x,circle->y,circle->w,circle->h);
			}
			/// 分割线
			for (LINE_LIST_CONST_ITERATOR it = m_divided_line_list.begin(); it != m_divided_line_list.end(); ++it)
			{
				LINE* line = *it;
				render->drawLine(line->from_x,line->from_y,line->to_x,line->to_y);
			}
		}
		render->restore();
	}

	render->restore();

	/// 刻度线
	const QMatrix& view_matrix = view->GetViewMatrix();
	render->save();
	{
		render->setBrush(SCALE_MARK_BRUSH);
		render->setPen(QPen(SCALE_MARK_PEN,0.0f,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
		for (MARK_LIST_CONST_ITERATOR it = m_scale_mark_list.begin(); it != m_scale_mark_list.end(); ++it)
		{
			MARK* mark = *it;
			QPointF offset = view_matrix.map(QPointF(mark->x,mark->y));
			QTransform trans;
			trans.translate(offset.x(),offset.y());
			trans.rotate(-mark->angle);
			render->setWorldTransform(trans);		
			render->drawLine(-mark->length,0.0,0.0,0.0);
		}
	}
	render->restore();

	/// 刻度文字
	render->save();
	{
        for (TEXT_LIST_ITERATOR it = m_scale_text_list.begin(); it != m_scale_text_list.end(); ++it)
        {
            TEXT_RD* text = (*it);
            QPointF offset = view_matrix.map(QPointF(text->x,text->y));
            QTransform trans;
            trans.translate(offset.x(),offset.y());
            trans.rotate(text->angle);
            render->setWorldTransform(trans);

            QFont font("宋体",10);
            render->setFont(font);
            render->fillPath(*(text->path),SCALE_TEXT_PEN);
        }
	}
	render->restore();
}
