#ifndef __XY_SCENE_2D_H__
#define __XY_SCENE_2D_H__

#include <Windows.h>
#include <deque>
#include "Singleton.h"
#include "Utility.h"

class XYView2D;

class XYScene2D
{
public:
	struct XY_DATA
	{
	public:
		XY_DATA(INT32 frame_num,float value,PLOT_TYPE type) : m_frame_num(frame_num),m_value(value),m_type(type) { }
		INT32     m_frame_num;
		float     m_value;
		PLOT_TYPE m_type;
	};
	typedef std::deque<XY_DATA>          XY_DATA_LIST;
	typedef XY_DATA_LIST::iterator       XY_DATA_LIST_ITERATOR;
	typedef XY_DATA_LIST::const_iterator XY_DATA_LIST_CONST_ITERATOR;
public:
	XYScene2D(float size_x,float size_y);
	const QSizeF& GetSize() const;
	virtual ~XYScene2D();
	void  Draw();
	void  SetXYView(XYView2D* xy_view);
	XYView2D* GetXYView();
	void  AddXYData(INT32 frame_num,float value,PLOT_TYPE type);
	void  ClearPlotList();
	float GetCurrentX() const;
	float GetCurrentY() const;
	void  SetDisplayingPlots(bool on);
private:
	XYView2D*    m_xy_view2D;
	XY_DATA_LIST m_xy_data_list;
	QSizeF       m_size;
	float        m_current_x;
	float        m_current_y;
private:
	bool         m_displaying_plots;
};

class VelocityScene2D : public XYScene2D,public Singleton<VelocityScene2D>
{
public:
	VelocityScene2D(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~VelocityScene2D() {}
};

class DistanceScene2D : public XYScene2D,public Singleton<DistanceScene2D>
{
public:
	DistanceScene2D(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~DistanceScene2D() {}
};


class AngleScene2D : public XYScene2D,public Singleton<AngleScene2D>
{
public:
	AngleScene2D(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~AngleScene2D() {}
};

class VelocityScene2DRadar2 : public XYScene2D,public Singleton<VelocityScene2DRadar2>
{
public:
	VelocityScene2DRadar2(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~VelocityScene2DRadar2() {}
};

class DistanceScene2DRadar2 : public XYScene2D,public Singleton<DistanceScene2DRadar2>
{
public:
	DistanceScene2DRadar2(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~DistanceScene2DRadar2() {}
};


class AngleScene2DRadar2 : public XYScene2D,public Singleton<AngleScene2DRadar2>
{
public:
	AngleScene2DRadar2(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~AngleScene2DRadar2() {}
};

class VelocityScene2DRadar3: public XYScene2D,public Singleton<VelocityScene2DRadar3>
{
public:
	VelocityScene2DRadar3(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~VelocityScene2DRadar3() {}
};

class DistanceScene2DRadar3 : public XYScene2D,public Singleton<DistanceScene2DRadar3>
{
public:
	DistanceScene2DRadar3(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~DistanceScene2DRadar3() {}
};


class AngleScene2DRadar3 : public XYScene2D,public Singleton<AngleScene2DRadar3>
{
public:
	AngleScene2DRadar3(float size_x,float size_y) : XYScene2D(size_x,size_y) {}
	virtual ~AngleScene2DRadar3() {}
};




#endif