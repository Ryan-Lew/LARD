#-------------------------------------------------
#
# Project created by QtCreator 2019-03-31T20:42:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network opengl

TARGET = LARDUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = $$PWD/../../bin

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    control.cpp \
    othercontrol.cpp \
    chook.cpp \
    commonhelper.cpp \
    qcustomcalendarwidget.cpp \
    switchbutton.cpp \
    lardvideo.cpp \
    videoplayer.cpp \
    videotableviewmodel.cpp \
    recordingtableviewmodel.cpp \
    volumewidget.cpp \
    optiondialog.cpp \
    doubleslider.cpp \
    scalewidget.cpp \
    radarscene.cpp \
    shipitem.cpp \
    enemyshipitem.cpp \
    verifydialog.cpp \
    splashscreen.cpp


HEADERS += \
        mainwindow.h \
    control.h \
    othercontrol.h \
    chook.h \
    commonhelper.h \
    qcustomcalendarwidget.h \
    switchbutton.h \
    lardvideo.h \
    videoplayer.h \
    videotableviewmodel.h \
    recordingtableviewmodel.h \
    volumewidget.h \
    optiondialog.h \
    doubleslider.h \
    scalewidget.h \
    radarscene.h \
    shipitem.h \
    enemyshipitem.h \
    verifydialog.h \
    splashscreen.h


FORMS += \
        mainwindow.ui \
    control.ui \
    othercontrol.ui \
    lardvideo.ui \
    volumewidget.ui \
    optiondialog.ui \
    verifydialog.ui


RESOURCES += \
    qrc.qrc

INCLUDEPATH += $$PWD/thirdpart/dev/include \
#INCLUDEPATH += $$PWD/thirdpart/cwmtx-stat-0.6.1 \
#INCLUDEPATH += $$PWD/thirdpart/qextserialport-1.2 \

LIBS += $$PWD/thirdpart/dev/lib/avcodec.lib \
        $$PWD/thirdpart/dev/lib/avdevice.lib \
        $$PWD/thirdpart/dev/lib/avfilter.lib \
        $$PWD/thirdpart/dev/lib/avformat.lib \
        $$PWD/thirdpart/dev/lib/avutil.lib \
        $$PWD/thirdpart/dev/lib/postproc.lib \
        $$PWD/thirdpart/dev/lib/swresample.lib \
        $$PWD/thirdpart/dev/lib/swscale.lib

DISTFILES += \
    src/background_1.jpg
