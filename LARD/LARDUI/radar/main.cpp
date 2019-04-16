#include "Scene2D.h"
#include "XYScene2D.h"
#include "MainWindow.h"
#include "TargetStateManager.h"
#include "PacketManager.h"
#include "Recorder.h"
#include "SystemParameters.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QApplication::setGraphicsSystem("opengl");
	app.setWindowIcon(QIcon(":/Resources/images/Radar.png"));
	Scene2D*     scene_2d               = new Scene2D(14000.0F);
	MainWindow*  mainwin                = new MainWindow;
	DistanceScene2D* distance_scene_2d  = new DistanceScene2D(1500.0F,12000.0F);
	VelocityScene2D* velocity_scene_2d  = new VelocityScene2D(1500.0F,438.0F);
	AngleScene2D*    angle_scene_2d     = new AngleScene2D(1500.0F,352.0F);

	VelocityScene2DRadar2* velocity_scene2d_radar2 = new VelocityScene2DRadar2(1500.0F,438.0F);
	DistanceScene2DRadar2* distance_scene2d_radar2 = new DistanceScene2DRadar2(1500.0F,20000.0F);
	AngleScene2DRadar2    * angle_scene2d_radar2      = new AngleScene2DRadar2(1500.0F,352.0F);

	VelocityScene2DRadar3* velocity_scene2d_radar3 = new VelocityScene2DRadar3(1500.0F,438.0F);
	DistanceScene2DRadar3* distance_scene2d_radar3 = new DistanceScene2DRadar3(1500.0F,20000.0F);
	AngleScene2DRadar3    * angle_scene2d_radar3      = new AngleScene2DRadar3(1500.0F,352.0F);

	mainwin->showMaximized();
	mainwin->CreateAndLayoutInterfaces();

	PacketManager*      packet_manager       = new PacketManager();

	TargetStateManager* target_state_manager = new TargetStateManager();
	Recorder*           recorder             = new Recorder;
	SystemParameters* system_parameters = new SystemParameters();

	app.exec();	

	delete system_parameters;
	delete recorder;
	delete packet_manager;
	delete target_state_manager;
	delete angle_scene_2d;
	delete velocity_scene_2d;
	delete distance_scene_2d;
	delete mainwin;
//	delete scene_2d;
	delete velocity_scene2d_radar2;
	delete distance_scene2d_radar2;
	delete angle_scene2d_radar2;
	delete velocity_scene2d_radar3;
	delete distance_scene2d_radar3;
	delete angle_scene2d_radar3;
	return 0;
}