#include "lardvideo.h"
#include "ui_lardvideo.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
LardVideo::LardVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LardVideo)
{
    ui->setupUi(this);
    mPlayer = new VideoPlayer;
    connect(mPlayer,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(slotGetOneFrame(QImage)));
    ///2017.8.11---lizhen
    connect(mPlayer,SIGNAL(sig_GetRFrame(QImage)),this,SLOT(slotGetRFrame(QImage)));
    ///2017.8.12---lizhen

    mPlayer->startPlay();
}

LardVideo::~LardVideo()
{
    delete ui;
}

void LardVideo::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    QPixmap pix;
    painter.translate(0, 0);
    pix.load(":/src/background.jpeg");//加载图片地址 可以是资源文件
    painter.drawPixmap(0, 0, width(), height(), pix);//绘制图片 横坐标、纵坐标、宽度、高度

    painter.save();


    painter.setPen(QColor(0,0,0,200));
    QBrush brush1 = QBrush(QColor(0,0,0,200),Qt::SolidPattern);
    painter.setBrush(brush1);//设置画刷形式
    painter.drawRect(QRect(this->width()*4/9,0,this->width()*5/9,40));


    QFont font1("宋体",12,QFont::Bold);
    painter.setPen(QColor(255,255,255));
    painter.setFont(font1);
    painter.drawText(QRect(this->width()*4/9,0,this->width()*5/9,40),"16:55:2122NoV 2018 H:317 STBD P:072 T:-2",
                     Qt::AlignVCenter|Qt::AlignHCenter);

    painter.restore();

    //painter.setBrush(Qt::white);
    //painter.drawRect(0, 0, this->width(), this->height()); //先画成白色

    if (mImage.size().width() <= 0) return;

    ///将图像按比例缩放成和窗口一样大小
    QImage img = mImage.scaled(this->size(),Qt::KeepAspectRatio);

    int x = this->width() - img.width();
    int y = this->height() - img.height();

    x /= 2;
    y /= 2;

    painter.drawImage(QPoint(x,y),img); //画出图像

    if(open_red==true){
    ///2017.8.12
    QWidget *red_video=new QWidget(this);
    red_video->resize(this->width()/3,this->height()/3);
    ///2017.8.11---lizhen
    //提取出图像中的R数据
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, red_video->width(),red_video->height()); //先画成白色

    if (R_mImage.size().width() <= 0) return;

    ///将图像按比例缩放成和窗口一样大小
    QImage R_img = R_mImage.scaled(red_video->size(),Qt::KeepAspectRatio);

    int R_x = red_video->width() - R_img.width();
    int R_y = red_video->height() - R_img.height();

    R_x /= 2;
    R_y /= 2;

    painter.drawImage(QPoint(R_x,R_y),R_img);  //画出图像
    }

    ///2017.8.10---lizhen
    //获取图像中心点
    double x0=this->width()/2;
    double y0=this->height()/2;

    //载体偏移角度，可从设备处获得
    double alpha=2;             //横滚角alpha
    int length=60;

    //设备偏移后的“水平”参考坐标
    //横滚角产生
    double x_Horizental_right=length*qCos(alpha);
    double y_Horizental_right=-length*qSin(alpha);
    double x_Horizental_left=-length*qCos(alpha);
    double y_Horizental_left=length*qSin(alpha);
    double x_Vertical_up=length*qSin(alpha);
    double y_Vertical_up=length*qCos(alpha);
    double x_Vertical_down=-length*qSin(alpha);
    double y_Vertical_down=-length*qCos(alpha);

    ///水平参考坐标系，2017.8.7---lizhen
    painter.setPen(QPen(Qt::blue,1,Qt::DotLine));
    painter.drawLine( x0-40,y0, x0+40,y0);
    painter.drawLine( x0,y0-40, x0,y0+40);

    ///横滚运动-偏移坐标系，2017.8.7---lizhen
    if(alpha!=0)
    {
        painter.setPen(QPen(Qt::blue,3));
        painter.drawLine( x0+x_Horizental_left,y0+y_Horizental_left, x0+x_Horizental_right,y0+y_Horizental_right);
        painter.drawLine( x0+x_Vertical_up,y0+y_Vertical_up, x0+x_Vertical_down,y0+y_Vertical_down);
    }
}

void LardVideo::slotGetOneFrame(QImage img)
{
    mImage = img;
    update(); //调用update将执行 paintEvent函数
}
///小窗口显示
void LardVideo::slotGetRFrame(QImage img)
{
    R_mImage = img;
    update(); //调用update将执行 paintEvent函数
}

