#ifndef ___GRAPHIC_H___
#define ___GRAPHIC_H___

#include <QMatrix>

class View2D;

class Graphic
{
public:
	enum STATE{ Visible,Invisible,HighLight,Selected};
public:
	Graphic(float pos_x = 0.0f,float pos_y = 0.0f,float rotation = 0.0f,float scale_x = 1.0f,float scale_y = 1.0f);
	virtual ~Graphic();
	virtual void  SetPosition(float x,float y);
	virtual void  Translate( float dx, float dy );
	virtual float GetPositionX() const;	
	virtual float GetPositionY() const;
	virtual void  SetScale(float x,float y);
	virtual void  Scale( float sx, float sy );
	virtual float GetScaleX() const;
	virtual float GetScaleY() const;
	virtual void  SetRotation(float degree);
	virtual void  Rotate( float degree );
	virtual float GetRotation() const;
	virtual void  SetState(STATE state);
	virtual STATE GetState() const;
	virtual void  ResetTransform();
	virtual const QMatrix& GetTransform() const;
protected:
	virtual void  Transform();
public:
	virtual void Draw(View2D* view) = 0;	
private:
	float   m_positon_x;
	float   m_positon_y;
	float   m_rotation;
	float   m_scale_x;
	float   m_scale_y;
	STATE   m_diaplay_state;
	QMatrix m_transform;
};



#endif