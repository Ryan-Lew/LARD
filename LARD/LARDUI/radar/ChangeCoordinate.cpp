#include "ChangeCoordinate.h"
#include <math.h>

ChangeCoordinate::ChangeCoordinate()
{
	//WGS-84 prameter
	earthradius = 6378137.0;//%m
	curvature = 1/298.257223563;
	partialityrat =0.081819190842621;
}

ChangeCoordinate ::~ChangeCoordinate()
{

}

/************************************************************************/
/* 将目标坐标系的GPS坐标转换到以主站为中心的极坐标系统
   输入：目标坐标系的GPS
         主站坐标系的GPS
	输出：以主站为中心的极坐标系										*/
/************************************************************************/

//MY_VECTOR_3 ChangeCoordinate::change(MY_VECTOR_3 object,
//									 MY_VECTOR_3 mainstation)
//{
//	MY_VECTOR_3 object_xyz = WGS2CTP(object);
//	MY_VECTOR_3 main_xyz /*  = WGS2CIP(mainstation)*/;
//	WGS2CTP2(mainstation,main_xyz);
//	double objectx   =  object_xyz[0];
//	double objecty   =  object_xyz[1];
//	double objectz   =  object_xyz[2];

//	double mainx     =  main_xyz[0];
//	double mainy     =  main_xyz[1];
//	double mainz     =  main_xyz[2];

//	double delta_x   =  mainx - objectx  ;
//	double delta_y   =  mainy - objecty  ;
//	double delta_z   =  mainz - objectz;

//	double Phi0      =  object[0] * PI/180.0;
//	double Jay0      =  object[1] * PI/180.0;

//	MY_MATRIX_33   transmatrix;
//	transmatrix[0][0] = -sin(Phi0) * cos(Jay0);
//	transmatrix[0][1] = -sin(Phi0) * sin(Jay0);
//	transmatrix[0][2] = cos(Phi0);

//	transmatrix[1][0] = -sin(Jay0);
//	transmatrix[1][1] = cos(Jay0);
//	transmatrix[1][2] = 0;

//	transmatrix[2][0] = cos(Phi0) * cos(Jay0);
//	transmatrix[2][1] = cos(Phi0) * sin(Jay0);
//	transmatrix[2][2] = sin(Phi0);


//	MY_VECTOR_3 delta;
//	delta[0] = delta_x;
//	delta[1] = delta_y;
//	delta[2] = delta_z;

//	MY_VECTOR_3 delta_cart;
//	delta_cart = transmatrix * delta;
//	double GPS_distance = sqrt(delta_cart[0] * delta_cart[0]
//								+delta_cart[1]*delta_cart[1]
//								+delta_cart[2]*delta_cart[2]);

//	double azimuth_gps = 0.0;
//	azimuth_gps = atan2(delta_cart[1],delta_cart[0])*180/PI;
//	if (azimuth_gps < 0)
//	{
//		azimuth_gps = azimuth_gps + 180;
//	}
	 
//	MY_VECTOR_3 changeafter;

//	changeafter[0] = GPS_distance;
//	changeafter[1] = azimuth_gps;
//	changeafter[2] = atan2(delta_cart[2],GPS_distance) * 180/PI;
//	return changeafter;

//}

/************************************************************************/
/* 将GPS坐标系转换为以地心为坐标的XYZ坐标                  */
/************************************************************************/

//MY_VECTOR_3 ChangeCoordinate::WGS2CTP(MY_VECTOR_3 vect)
//{
//	MY_VECTOR_3 XYZ;
//	double sqrttest = sqrt(1 - partialityrat*partialityrat * sin(vect[0]*PI/180.0) * sin(vect[0]*PI/180.0));
//	double N = earthradius/sqrttest;
//	XYZ[0]   =  (N + vect[2]) * cos(vect[0]*PI/180) * cos(vect[1]*PI/180);
//	XYZ[1]   =  (N + vect[2]) * cos(vect[0]*PI/180) * sin(vect[1]*PI/180);
//	XYZ[2]   =  (N * (1 - partialityrat*partialityrat)+vect[2]) * sin(vect[0]*PI/180);
//	return XYZ;

//}


//void ChangeCoordinate::WGS2CTP2(MY_VECTOR_3 vect,MY_VECTOR_3& vect2)
//{

//	double sqrttest = sqrt(1 - partialityrat*partialityrat * sin(vect[0]*PI/180.0) * sin(vect[0]*PI/180.0));
//	double N = earthradius/sqrttest;
//	vect2[0]   =  (N + vect[2]) * cos(vect[0]*PI/180) * cos(vect[1]*PI/180);
//	vect2[1]   =  (N + vect[2]) * cos(vect[0]*PI/180) * sin(vect[1]*PI/180);
//	vect2[2]   =  (N * (1 - partialityrat*partialityrat)+vect[2]) * sin(vect[0]*PI/180);
//}

