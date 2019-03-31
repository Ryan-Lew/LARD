#include "mainwindow.h"
#include <QApplication>
#include <commonhelper.h>
#include <QDebug>
#include "./radar/Scene2D.h"
#include "./radar/XYScene2D.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scene2D*     scene_2d               = new Scene2D(4000.0F);
    DistanceScene2D* distance_scene_2d  = new DistanceScene2D(1500.0F,12000.0F);
    VelocityScene2D* velocity_scene_2d  = new VelocityScene2D(1500.0F,438.0F);
    AngleScene2D*    angle_scene_2d     = new AngleScene2D(1500.0F,352.0F);

    VelocityScene2DRadar2* velocity_scene2d_radar2 = new VelocityScene2DRadar2(1500.0F,438.0F);
    DistanceScene2DRadar2* distance_scene2d_radar2 = new DistanceScene2DRadar2(1500.0F,20000.0F);
    AngleScene2DRadar2    * angle_scene2d_radar2      = new AngleScene2DRadar2(1500.0F,352.0F);

    VelocityScene2DRadar3* velocity_scene2d_radar3 = new VelocityScene2DRadar3(1500.0F,438.0F);
    DistanceScene2DRadar3* distance_scene2d_radar3 = new DistanceScene2DRadar3(1500.0F,20000.0F);
    AngleScene2DRadar3    * angle_scene2d_radar3      = new AngleScene2DRadar3(1500.0F,352.0F);


    CommonHelper::setStyle(":/src/lard.qss");
    MainWindow w;
    //w.showFullScreen();
    w.show();
    return a.exec();
}
