#ifndef LARDVIDEO_H
#define LARDVIDEO_H

#include <QWidget>
#include "videoplayer.h"
namespace Ui {
class LardVideo;
}

class LardVideo : public QWidget
{
    Q_OBJECT

public:
    explicit LardVideo(QWidget *parent = 0);
    ~LardVideo();
    QString bkSrc() const;
    void setBkSrc(const QString &bkSrc);

    QString hintInfo() const;
    void setHintInfo(const QString &hintInfo);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::LardVideo *ui;


    VideoPlayer *mPlayer; //播放线程

    QImage mImage; //记录当前的图像
    QImage R_mImage;

    QString url;
    QString m_bkSrc = "";
    QString m_hintInfo = "";
    bool open_red=false;

private slots:
    void slotGetOneFrame(QImage img);
    void slotGetRFrame(QImage img);

};

#endif // LARDVIDEO_H
