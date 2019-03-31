#include "Graphic.h"

Graphic::Graphic(float pos_x ,float pos_y ,float rotation,float scale_x ,float scale_y ) : m_positon_x(pos_x),m_positon_y(pos_y),m_scale_x(scale_x),m_scale_y(scale_y),m_rotation(rotation),m_diaplay_state(Visible)
{
	m_transform.reset();
	Transform();
}

Graphic::~Graphic() {}

void Graphic::SetPosition(float x,float y)
{	
	m_positon_x = x;
	m_positon_y = y;
	Transform();
}

float Graphic::GetPositionX() const
{
	return m_positon_x;
}

float Graphic::GetPositionY() const
{
	return m_positon_y;
}

void Graphic::SetScale(float x,float y) 
{
	m_scale_x = x;
	m_scale_y = y;
	Transform();
}

float Graphic::GetScaleX() const 
{
	return m_scale_x;
}
float Graphic::GetScaleY() const 
{
	return m_scale_y;
}

void Graphic::SetRotation(float degree)
{
	m_rotation = degree;
	Transform();
}

float Graphic::GetRotation() const
{
	return m_rotation;
}

void Graphic::Rotate( float degree )
{
	m_rotation += degree;
	Transform();
}
void Graphic::Scale( float sx, float sy )
{
	m_scale_x *= sx;
	m_scale_y *= sy;
	Transform();
}

void Graphic::Translate ( float dx, float dy )
{
	m_positon_x += dx;
	m_positon_y += dy;
	Transform();
}

const QMatrix&  Graphic::GetTransform() const
{
	return m_transform;
}

void Graphic::Transform()
{
	m_transform.reset();
	m_transform.translate(m_positon_x,m_positon_y);
	m_transform.rotate(m_rotation);
	m_transform.scale(m_scale_x,m_scale_y);
}

void Graphic::SetState(Graphic::STATE state)
{
	m_diaplay_state = state;
}
Graphic::STATE Graphic::GetState() const
{
	return m_diaplay_state;
}

void Graphic::ResetTransform()
{
	m_transform.reset();
	m_positon_x = 0.0f;
	m_positon_y = 0.0f;
	m_rotation  = 0.0f;
	m_transform.translate(m_positon_x,m_positon_y);
	m_transform.rotate(m_rotation);
	m_transform.scale(m_scale_x,m_scale_y);	
}
