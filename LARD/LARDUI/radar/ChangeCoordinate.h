#ifndef _CHANGECOORDINATE_H_
#define _CHANGECOORDINATE_H_

#define PI 3.1415926535897932384626433832795
#define e  2.718281828459

class ChangeCoordinate
{
public:
	ChangeCoordinate();
	~ChangeCoordinate();
    //MY_VECTOR_3 object_radar;
    //MY_VECTOR_3 main_station;
    //MY_VECTOR_3 change(MY_VECTOR_3 object,MY_VECTOR_3 mainstation);
protected:
    //MY_VECTOR_3 WGS2CTP(MY_VECTOR_3 vect);
    //void WGS2CTP2(MY_VECTOR_3 vect,MY_VECTOR_3& vect2);
private:
	double earthradius ;//%µØÇò°ë¾¶
	double curvature ;//µØÇòÇúÂÊ
	double partialityrat ;//

};
#endif
