#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class LardVideo;
class VideoTableViewModel;
class RecordingTableViewModel;
class VideoInfo;
class RadarScene;
class QGraphicsView;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    virtual void keyPressEvent(QKeyEvent *evt);
//    virtual void keyReleaseEvent(QKeyEvent *evt);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void timerEvent(QTimerEvent *event);
public:
    void createAndLayoutInterfaces();
    void updateVideoInfo();
    //初始化雷达相关信息
    void initRadarInfo();
    //更新时钟信息
    void updateTimer();
    //更改语言信息
    void updateTr(int index);



private slots:
    void slots_updateTr(int index);
    void on_switch_status_clicked();

    void on_option_clicked();

    void on_seamile2_clicked();

    void on_seamile4_clicked();

    void on_seamile8_clicked();


    void on_shipduenorth_clicked();

    void on_shipowndirect_clicked();

private:
    Ui::MainWindow *ui;
    LardVideo* m_video1 = nullptr;
    LardVideo* m_video2 = nullptr;

    VideoTableViewModel* m_videoModel = nullptr;
    RecordingTableViewModel* m_recordingvideoModel = nullptr;

    QList<VideoInfo*> list;
    QGraphicsView *m_view = nullptr;
    RadarScene* m_scene = nullptr;
    int m_updateTimerId = 0;
    int m_language = 0;
};

#endif // MAINWINDOW_H
