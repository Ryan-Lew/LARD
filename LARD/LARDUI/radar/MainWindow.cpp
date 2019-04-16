#include "MainWindow.h"
#include "Scene2D.h"
#include "View2D.h"

#include "PlotParametersInterface.h"
#include "TargetListInterface.h"
#include "XYScene2D.h"
#include "XYView2D.h"
#include <QTimer>
#include <QToolBar>
#include <QDockWidget>
#include "dispRadarState.h"
#include "setRadarWorkparm.h"

template<> MainWindow* Singleton< MainWindow >::m_singleton = 0;

MainWindow::MainWindow()
{	
	setWindowFlags(Qt::Window);
	this->setWindowTitle(Chinese(MAIN_WINDOW_TITLE));	

	View2D* view_2d = new View2D(this,Scene2D::GetPointer());	
	this->setCentralWidget(view_2d);
	view_2d->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

	QAction* quit_atn = new QAction(this);
	quit_atn->setShortcut( Qt::CTRL + Qt::Key_Q );
	QObject::connect(quit_atn, SIGNAL(triggered()), this, SLOT(close()));
	this->addAction(quit_atn);

	QToolBar* tb = new QToolBar(this);
	tb->setAllowedAreas(Qt::TopToolBarArea);
	tb->setContextMenuPolicy(Qt::PreventContextMenu);
	this->addToolBar(tb);
	tb->addWidget(new ToolsInterface(this));
	this->setFocusPolicy( Qt::ClickFocus );

// 	QDockWidget *shapesDockWidget = new QDockWidget(Chinese("    "));
// 	shapesDockWidget->setObjectName("shapesDockWidget");
// 	shapesDockWidget->setWidget(new setRadarWorkparm(this));
// 	shapesDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
// 	shapesDockWidget->setFeatures(QDockWidget::DockWidgetMovable);
// 	this->addDockWidget(Qt::RightDockWidgetArea,shapesDockWidget);
// 	this->setFocusPolicy(Qt::ClickFocus);

	m_rend_scene_timer = new QTimer(this);
	connect( m_rend_scene_timer, SIGNAL(timeout()),this,SLOT(RendScene()));
	m_rend_scene_timer->start(40);
}

void MainWindow::CreateAndLayoutInterfaces()
{
	dispRadarState *dispradarstate = new dispRadarState(this,ToolsInterface::GetPointer()->GetDispRadarState());
	dispradarstate->setWindowOpacity(0.8);
	dispradarstate->move(1,60);

	setRadarWorkparm* setradarworkparm = new setRadarWorkparm(this,ToolsInterface::GetPointer()->GetDispSetSystemPara());
	setradarworkparm->setWindowOpacity(0.8);
	setradarworkparm->move(60,160);

	PlotParametersInterface* plot_interface     = new PlotParametersInterface(this,ToolsInterface::GetPointer()->GetPlotParametersInterfaceButton());
	plot_interface->setWindowOpacity(0.80);
	plot_interface->setFixedSize(520,40);
	plot_interface->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() - 8,53);

//	XYView2D* distance_view = new XYView2D(this,plot_interface->GetDistanceViewButton(),DistanceScene2D::GetPointer());
//	distance_view->setWindowTitle(Chinese("À×´ï1:¾àÀë-Ö¡ÐòºÅÊÓÍ¼"));
//	distance_view->setWindowOpacity(0.8);
//	distance_view->resize(478,220);
//	distance_view->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + 53 );
	
//	XYView2D* angle_view    = new XYView2D(this,plot_interface->GetAngleViewButton(),AngleScene2D::GetPointer());
//	angle_view->setWindowTitle(Chinese("À×´ï1:½Ç¶È-Ö¡ÐòºÅÊÓÍ¼"));
//	angle_view->setWindowOpacity(0.8);
//	angle_view->resize(478,220);
//	angle_view->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + distance_view->frameGeometry().height() + 53 );

//	XYView2D* velocity_view = new XYView2D(this,plot_interface->GetVelocityViewButton(),VelocityScene2D::GetPointer());
//	velocity_view->setWindowTitle(Chinese("À×´ï1:ËÙ¶È-Ö¡ÐòºÅÊÓÍ¼"));
//	velocity_view->setWindowOpacity(0.8);
//	velocity_view->resize(478,220);
//	velocity_view->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + distance_view->frameGeometry().height() + angle_view->frameGeometry().height() + 53 );

//	XYView2D* distance_view_radar2 = new XYView2D(this,plot_interface->GetDistanceViewButtonRadar2(),DistanceScene2DRadar2::GetPointer());
//	distance_view_radar2->setWindowTitle(Chinese("À×´ï2:¾àÀë-Ö¡ÐòºÅÊÓÍ¼"));
//	distance_view_radar2->setWindowOpacity(0.8);
//	distance_view_radar2->resize(478,220);
//	distance_view_radar2->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + 53);

//	XYView2D* angle_view_radar2    = new XYView2D(this,plot_interface->GetAngleViewButtonRadar2(),AngleScene2DRadar2::GetPointer());
//	angle_view_radar2->setWindowTitle(Chinese("À×´ï2:½Ç¶È-Ö¡ÐòºÅÊÓÍ¼"));
//	angle_view_radar2->setWindowOpacity(0.8);
//	angle_view_radar2->resize(478,220);
//	angle_view_radar2->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + distance_view_radar2->frameGeometry().height() + 53  );

//	XYView2D* velocity_view_radar2 = new XYView2D(this,plot_interface->GetVelocityViewButtonRadar2(),VelocityScene2DRadar2::GetPointer());
//	velocity_view_radar2->setWindowTitle(Chinese("À×´ï2:ËÙ¶È-Ö¡ÐòºÅÊÓÍ¼"));
//	velocity_view_radar2->setWindowOpacity(0.8);
//	velocity_view_radar2->resize(478,220);
//	velocity_view_radar2->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + distance_view_radar2->frameGeometry().height() + angle_view_radar2->frameGeometry().height() + 53 );

//	XYView2D* distance_view_radar3 = new XYView2D(this,plot_interface->GetDistanceViewButtonRadar3(),DistanceScene2DRadar3::GetPointer());
//	distance_view_radar3->setWindowTitle(Chinese("À×´ï3:¾àÀë-Ö¡ÐòºÅÊÓÍ¼"));
//	distance_view_radar3->setWindowOpacity(0.8);
//	distance_view_radar3->resize(478,220);
//	distance_view_radar3->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + 53 );

//	XYView2D* angle_view_radar3    = new XYView2D(this,plot_interface->GetAngleViewButtonRadar3(),AngleScene2DRadar3::GetPointer());
//	angle_view_radar3->setWindowTitle(Chinese("À×´ï3:½Ç¶È-Ö¡ÐòºÅÊÓÍ¼"));
//	angle_view_radar3->setWindowOpacity(0.8);
//	angle_view_radar3->resize(478,220);
//	angle_view_radar3->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + distance_view_radar3->frameGeometry().height() + 53 );

//	XYView2D* velocity_view_radar3 = new XYView2D(this,plot_interface->GetVelocityViewButtonRadar3(),VelocityScene2DRadar3::GetPointer());
//	velocity_view_radar3->setWindowTitle(Chinese("À×´ï3:ËÙ¶È-Ö¡ÐòºÅÊÓÍ¼"));
//	velocity_view_radar3->setWindowOpacity(0.8);
//	velocity_view_radar3->resize(478,220);
//	velocity_view_radar3->move(this->frameGeometry().width() - plot_interface->frameGeometry().width() + 108, plot_interface->frameGeometry().height() + distance_view_radar3->frameGeometry().height() + angle_view_radar3->frameGeometry().height() + 53 );

}


void MainWindow::RendScene()
{

	/////////////ADS----------------------------------
	Scene2D::GetPointer()->UpdateADSTargetList();
	/////////////ADS----------------------------------

	Scene2D::GetPointer()->GetView()->Draw();
	DistanceScene2D::GetPointer()->GetXYView()->Draw();
	VelocityScene2D::GetPointer()->GetXYView()->Draw();
	AngleScene2D::GetPointer()->GetXYView()->Draw();

	DistanceScene2DRadar2::GetPointer()->GetXYView()->Draw();
	VelocityScene2DRadar2::GetPointer()->GetXYView()->Draw();
	AngleScene2DRadar2::GetPointer()->GetXYView()->Draw();

	DistanceScene2DRadar3::GetPointer()->GetXYView()->Draw();
	VelocityScene2DRadar3::GetPointer()->GetXYView()->Draw();
	AngleScene2DRadar3::GetPointer()->GetXYView()->Draw();
}
