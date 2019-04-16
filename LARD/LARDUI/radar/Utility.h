#ifndef ___UTILITIES_H___
#define ___UTILITIES_H___

#include <QPoint>
#include <QRectF>
#include <QPolygon>
#include <cmath>
#include <Windows.h>
#include <QTextCodec>
#include <QDateTime>
#include <QColor>

static const std::string MAIN_WINDOW_TITLE = "RadarClient_L_V103";


static const QColor ORIGINAL_PLOT_COLOR_PIPEI              = QColor(255, 255, 0, 255); 
static const QColor AGGLOMERATOR_PLOT_COLOR           = QColor(255, 0,255,255); 
static const QColor ORIGINAL_PLOT_COLOR                        = QColor(192, 192, 192, 255); 
static const QColor ORIGINAL_PLOT_COLOR_RADAR1       = QColor(255, 0,255,255);
static const QColor ORIGINAL_PLOT_COLOR_RADAR2       = QColor(192, 192, 192,255);
static const QColor ORIGINAL_PLOT_COLOR_RADAR3       = QColor(149,48,4,255);



////目标列表的颜色----------------------------------------------------------------------------------------
static const QColor TARGET_LIST_TEXT_COLOR            = Qt::white;
static const QColor TARGET_LIST_TEXT_HIGHLIGHT_COLOR  = Qt::darkCyan;
////目标列表的颜色----------------------------------------------------------------------------------------


///目标的颜色----------------------------------------------------------------------------------------------
static const QColor TARGET_COLOR					  = QColor(255, 128, 64,   255);
static const QColor TARGET_HIGHLIGHT_COLOR            = QColor(255, 0  , 64,   255);
///目标的颜色----------------------------------------------------------------------------------------------


///ADS-B目标的颜色------------------------------------------------------------------------------------------

static const QColor ADS_TARGET_COLOR				  = Qt::darkYellow;

///ADS-B目标的颜色------------------------------------------------------------------------------------------







///----------------------------雷达的颜色----------------------------------------------------------------

/// 外圈园、十字线
static const QColor PERPHERAL_CIRCLE_AND_CROSS_LINE_BRUSH_0 =  QColor(50,50,50);
static const QColor PERPHERAL_CIRCLE_AND_CROSS_LINE_BRUSH_1 =  Qt::black;
static const QColor PERPHERAL_CIRCLE_AND_CROSS_LINE_PEN     =  Qt::darkGreen;

/// 分割圈、分割线
static const QColor DIVIDED_CIRCLE_AND_DIVIDED_LINE_BRUSH =  Qt::transparent;
static const QColor DIVIDED_CIRCLE_AND_DIVIDED_LINE_PEN   =  QColor(75, 75, 75, 255);

/// 刻度线
static const QColor SCALE_MARK_BRUSH =  Qt::green;
static const QColor SCALE_MARK_PEN   =  Qt::green;

/// 刻度文字
static const QColor SCALE_TEXT_PEN   =  Qt::green;

///----------------------------雷达的颜色-----------------------------------------------------------------







///----------------------------背景的颜色-----------------------------------------------------------------

static const QColor BACKGROUND_BRUSH = Qt::black;

///----------------------------背景的颜色-----------------------------------------------------------------





///----------------------------XY 视图颜色----------------------------------------------------------------

static const QColor XY_VIEW_BACKGROUND_BRUSH = QColor(50,50,50);
static const QColor XY_VIEW_AXIS_PEN         = QColor(125, 125, 125, 255);
static const QColor XY_VIEW_AXIS_BRUSH       = QColor(125, 125, 125, 255);
static const QColor XY_VIEW_MARK_PEN         = Qt::white;
static const QColor XY_VIEW_MARK_BRUSH       = Qt::white;

///----------------------------XY 视图颜色----------------------------------------------------------------






///圆点的图像----------------------------------------------------------------------------------------------

static const QRectF POINT_IMAGE_LARGE                 = QRectF(-1.5F,-1.5F,3.0F,3.0F);
static const QRectF POINT_IMAGE_MINI                  = QRectF(-1.0F,-1.0F,2.0F,2.0F);
static const QRectF POINT_IMAGE_MIN                   = QRectF(-1.0F,-1.0F,1.0F,1.0F);

///圆点的图像----------------------------------------------------------------------------------------------


//设置航迹最大航迹点数
static const int MAX_TRACK_PLOT_NUMS = 500;


enum { PC0_ADD  = 0x01 };
enum { CCM_ADD  = 0x01 };
enum { RM1_ADD  = 0x02,RM2_ADD  = 0x03,RM3_ADD = 0x04,RM4_ADD = 0x05 };
enum { PA1_ADD  = 0x06,PA2_ADD  = 0x07,PA3_ADD = 0x08,PA4_ADD = 0x09 };
enum { SG_ADD   = 0x0A };
enum { PCM_ADD  = 0x0B };
enum { SPP1_ADD = 0x10, SPP2_ADD = 0x11 };
enum { SMP1_ADD = 0x12, SMP2_ADD = 0x13 };
enum { DP1_ADD  = 0x14, DP2_ADD  = 0x15 };


enum { ACCUMULATION_PERIOD_128 = 128, ACCUMULATION_PERIOD_256 = 256, ACCUMULATION_PERIOD_512 = 512, ACCUMULATION_PERIOD_1024 = 1024, ACCUMULATION_PERIOD_2048 = 2048};

enum { PACKET_BUFFER_SIZE  = 65536 }; 

enum { SCENE_2D_MAX_PLOT_NUMS = 2048,	XY_SCENE_2D_MAX_PLOT_NUMS = 2048 };

const std::string DATA_PATH = "./";

enum PLOT_TYPE{ ORIGINAL_PLOT = 0, AGGLOMERATOR_PLOT = 1, POLAR_FILTERED_PLOT = 2};

static const double MY_PI  = 3.1415926535897932384626433832795;
static const double MY_2PI = 2.0 * MY_PI;

enum {	CLIENT_TO_HOST_XM_CONTROL_PORT			             = 51006,
		HOST_TO_CLIENT_XM_CONTROL_PORT				         = 51007,
		HOST_TO_DATA_PROCESSOR_REALTIME_PLOT_PORT			 = 51009,
		SIMPLE_REPLAYER_TO_DATA_PROCESSOR_PREVIOUS_PLOT_PORT = 50012,
		SIMPLE_REPLAYER_TO_CLIENT_ADS_B_PREVIOUS_TRACK_PORT	 = 50020,
		DATA_PROCESSOR_TO_CLIENT_REALTIME_PLOT_PORT		     = 50015,
		DATA_PROCESSOR_TO_CLIENT_TRACK_PORT		             = 50016,
		DATA_PROCESSOR_TO_CLIENT_AGGLOMERATION_PLOT_PORT     = 50017,
		DATA_PROCESSOR_TO_CLIENT_PREVIOUS_PLOT_PORT	         = 50019,
		ADS_B_REALTIME_TRACK_PORT                            = 5783  };
enum{
	RADAR1_TO_CLIENT_PORT = 16666,
	CLIENT_TO_RADAR1_PORT = 6666,
	RADAR2_TO_CLIENT_PORT = 16667,
	CLIENT_TO_RADAR2_PORT = 6667,
	RADAR3_TO_CLIENT_PORT = 16668,
	CLIENT_TO_RADAR3_PORT = 6668,
};

static const double SPEEDRAT = 0.3756;


static const double SIGMA_RHO_MEASUREMENT_SQUARE_FOR_CARTESIAN_FILTER       = 1E-6;
static const double SIGMA_THETA_MEASUREMENT_SQUARE_FOR_CARTESIAN_FILTER     = 1E-6;

static const double Q_ADJUST_FACTOR_0_FOR_CARTESIAN_FILTER                  = 0.0001;
static const double Q_ADJUST_FACTOR_1_FOR_CARTESIAN_FILTER                  = 0.0001;

static const double TARGET_STATE_PREDICTING_INTERVALS_S                     = 1.5;   ///S
static const int    TARGET_TIMOUT_UPDATED_NUMS_GATE                         = 10;
static const double TARGET_TIMOUT_S_0						                = 300;
static const double TARGET_TIMOUT_S_1                                       = 60;


void OrthogonalToPolar(double x,double y,double* rho,double* theta);

void PolarToOrthogonal(double rho,double theta,double* x,double* y);

double string_to_double(const std::string& str);

std::string double_to_string(double num,int precision = 15);

QString Chinese(const std::string& str);

/// Memory order HIGH-LOW 
UINT16 TwoBytesToUINT16(const BYTE* two_bytes);

/// Memory order HIGH-LOW 
void UINT16ToTwoBytes(UINT16 word,BYTE* two_bytes);

/// Memory order HIGH-LOW 
UINT32 FourBytesToUINT32(const BYTE* four_bytes);

/// Memory order HIGH-LOW 
void UINT32ToFourBytes(UINT32 dword,BYTE* four_bytes);

BYTE GetBitValue(BYTE data,BYTE pos);

void SetBitValue(BYTE* data,BYTE pos);

void ClearBitValue(BYTE* data, byte pos);


static const std::string UINFORM_DATETIME_TEXT_FORMAT = "yyyy-MM-ddThh:mm:ss:zzz";

inline double GetSecondIntervals(const QDateTime& dt0,const QDateTime& dt1)
{
	return double(dt0.msecsTo(dt1)) / 1000.0;
}

inline UINT64 GetMillisecondIntervals(const QDateTime& dt0,const QDateTime& dt1)
{
	return dt0.msecsTo(dt1);
}

inline bool PointInRectStrict(const QPointF& point,const QRectF& rect)
{
	return rect.contains(point.x(),point.y());
}

inline bool PointInRectRough(const QPointF& point,const QRectF& rect)
{
	return QRectF(rect.left() - 2.0F, rect.top() - 2.0F, rect.width() + 4.0F, rect.height() + 4.0F).contains(point.x(),point.y());
}

inline bool PointInPolygon(const QPointF& point,const QPolygonF& polygon)
{
	return polygon.containsPoint(point,Qt::OddEvenFill);
}


#endif