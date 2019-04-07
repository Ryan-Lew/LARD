#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qcustomcalendarwidget.h>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QDebug>
#include <QTextCharFormat>
#include "./radar/XYView2D.h"
#include "./radar/XYScene2D.h"
#include "./radar/Scene2D.h"
#include "./radar/View2D.h"
#include "volumewidget.h"
#include "videotableviewmodel.h"
#include "recordingtableviewmodel.h"
#include "lardvideo.h"
#include "optiondialog.h"
#include <QScrollBar>
#include <QGraphicsView>
#include <QDateTime>
#include "doubleslider.h"
#include "scalewidget.h"
#include "radarscene.h"
#include "shipitem.h"
#include "enemyshipitem.h"
#include "verifydialog.h"

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //无边框
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->port_ac_power->setChecked(true);
    ui->dark->setChecked(true);
    av_register_all();

    createAndLayoutInterfaces();

    ui->calendarWidget->setGridVisible(false);
    QTextCharFormat format;
    format.setForeground( QColor(Qt::white));

    ui->calendarWidget->setWeekdayTextFormat(Qt::Monday, format);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Tuesday, format);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Wednesday, format);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Thursday, format);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Friday, format);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Saturday, format);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Sunday, format);

     ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat::NoVerticalHeader);

    m_video1 = new LardVideo;
    m_video2 = new LardVideo;
    ui->video1->layout()->addWidget(m_video1);
    ui->video2->layout()->addWidget(m_video2);


    m_videoModel= new VideoTableViewModel();
    ui->videofiletableView->setModel(m_videoModel);

     ui->videofiletableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->videofiletableView->horizontalHeader()->hide();

     ui->videofiletableView->horizontalHeader()->setObjectName("videohHeader");
     ui->videofiletableView->verticalHeader()->setObjectName("videovHeader");

     m_recordingvideoModel= new RecordingTableViewModel();
     ui->recordingtableView->setModel(m_recordingvideoModel);

     ui->recordingtableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->recordingtableView->horizontalHeader()->hide();


     ui->recordingtableView->horizontalHeader()->setObjectName("recordhHeader");
     ui->recordingtableView->verticalHeader()->setObjectName("recordvHeader");



    updateVideoInfo();
    VolumeWidget * widget = new VolumeWidget();
    ui->volume->layout()->addWidget(widget);


    DoubleSlider *slider = new DoubleSlider;
    ui->doubleslider->layout()->addWidget(slider);

    ScaleWidget * scale = new ScaleWidget;

    ui->scalewidget->layout()->addWidget(scale);
    ShipItem *item = new ShipItem();
    //qDebug()<<item->mapFromScene(100,100);

    item->setCenterPt(QPointF(0,0));
    m_scene->addItem(item);

    {
        EnemyShipItem* testItem = new EnemyShipItem();
        testItem->setSeaAngle(321);
        testItem->setSeaMile(1.9);
        testItem->setAngle(30);

        m_scene->addItem(testItem);
    }
    {
        EnemyShipItem* testItem = new EnemyShipItem();
        testItem->setSeaAngle(132);
        testItem->setSeaMile(2.3);
        testItem->setAngle(30);

        m_scene->addItem(testItem);
    }
    {
        EnemyShipItem* testItem = new EnemyShipItem();
        testItem->setSeaAngle(97);
        testItem->setSeaMile(1.7);
        testItem->setAngle(44);

        m_scene->addItem(testItem);
    }
    {
        EnemyShipItem* testItem1 = new EnemyShipItem();
        testItem1->setSeaAngle(30);
        testItem1->setSeaMile(4.3);
        testItem1->setAngle(187);

        m_scene->addItem(testItem1);
    }
    //开始刷新时间定时器
    m_updateTimerId = startTimer(1000);
    //初始化雷达相关信息
    initRadarInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *evt)
{


}

void MainWindow::keyReleaseEvent(QKeyEvent *evt)
{

}

void MainWindow::resizeEvent(QResizeEvent *event)
{

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_updateTimerId){
        updateTimer();
    }

}

void MainWindow::createAndLayoutInterfaces()
{

    m_view = new QGraphicsView();

    m_view->centerOn(0,0);
    m_view->setFixedWidth(1080);
    m_view->setFixedHeight(1080);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->verticalScrollBar()->hide();
    m_scene = new RadarScene();
    m_view->setScene(m_scene);
    m_scene->setSceneRect(-m_view->width()/2,-m_view->height()/2,m_view->width(),m_view->height());
    ui->gl_rander->layout()->addWidget(m_view);

}

void MainWindow::updateVideoInfo()
{

    list.clear();
    auto test1 = new VideoInfo();
    test1->setFilename("test1");
    list.append(test1);

    auto test2 = new VideoInfo();
    test2->setFilename("test2");
    list.append(test2);

    auto test3 = new VideoInfo();
    test3->setFilename("test3");
    list.append(test3);

    auto test4 = new VideoInfo();
    test4->setFilename("test4");
    list.append(test4);

}

void MainWindow::initRadarInfo()
{
    //船名和IMO代码（英文和数字，在系统设置里输入）
    ui->radarname->setText(QStringLiteral("VICTORIA"));
    ui->radarimo->setText(QStringLiteral("UN1234567"));
    //本船船头朝向，为罗经仪数据；
    ui->heading->setText(QStringLiteral("137"));


    //左舷LRAD指向和跟踪状态：当LARD电源开启时显示；云台指向的方位角和俯仰角；自动或手动跟踪状态；
    ui->portlrad_pan->setText(QStringLiteral("100"));
    //自动或手动跟踪状态； AUTO OR MANUAL
    ui->portlrad_state->setText(QStringLiteral("AUTO"));
    ui->portlrad_title->setText(QStringLiteral("-2"));

    ui->stbdlrad_pan->setText(QStringLiteral("120"));
    //自动或手动跟踪状态； AUTO OR MANUAL
    ui->stbdlrad_state->setText(QStringLiteral("MANUAL"));
    ui->stbdlrad_title->setText(QStringLiteral("-2"));
}

void MainWindow::updateTimer()
{
    QDateTime time = QDateTime::currentDateTime();
    QString date = time.toString("yyyy/MM/dd");
    QString _time = time.toString("hh:mm:ss");
    ui->localdate->setText(date);
    ui->localtime->setText(_time);

}

void MainWindow::on_switch_status_clicked()
{
    if(ui->switch_status->isChecked()){
        ui->stackedWidget->setCurrentWidget(ui->play_page);
    }else{
        ui->stackedWidget->setCurrentWidget(ui->video_page);
    }
}

void MainWindow::on_option_clicked()
{

    VerifyDialog dialog;
    if(dialog.exec() ==QDialog::Accepted){

    }
}

void MainWindow::on_seamile2_clicked()
{
    m_scene->setSeaMile(2);
    m_view->viewport()->update();
}

void MainWindow::on_seamile4_clicked()
{
    m_scene->setSeaMile(4);
    m_view->viewport()->update();
}

void MainWindow::on_seamile8_clicked()
{
    m_scene->setSeaMile(8);
    m_view->viewport()->update();
}

void MainWindow::on_shipduenorth_clicked()
{
    m_scene->setDictSwitch(true);
    m_view->viewport()->update();
}

void MainWindow::on_shipowndirect_clicked()
{
    m_scene->setDictSwitch(false);
    m_view->viewport()->update();
}
