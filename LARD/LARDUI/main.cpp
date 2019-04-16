#include "mainwindow.h"
#include <QApplication>
#include <commonhelper.h>
#include <QDebug>
#include <windows.h>
#include <stdio.h>
#include "splashscreen.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommonHelper::setStyle(":/src/lard.qss");
    SplashScreen s;
    s.setFixedWidth(1920);
    s.setFixedHeight(1080);
    //s.showFullScreen();
    s.show();
    return a.exec();
}
