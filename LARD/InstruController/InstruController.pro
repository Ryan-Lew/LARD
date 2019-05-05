#-------------------------------------------------
#
# Project created by QtCreator 2019-03-31T20:40:19
#
#-------------------------------------------------

QT       -= gui
QT += serialport

TARGET = InstruController
TEMPLATE = lib

DEFINES += INSTRUCONTROLLER_LIBRARY

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
        instrucontroller.cpp \
    communication/serial422.cpp \
    communication/serialcombase.cpp \
#    communication/serialnmea.cpp \
    radar.cpp \
    compasser.cpp \
    consolecontrol.cpp \
    cloud.cpp

HEADERS += \
        instrucontroller.h \
        instrucontroller_global.h \ 
    communication/serial422.h \
    communication/serialcombase.h \
#    communication/serialnmea.h \
    ../../inc/commonstruct.h \
    radar.h \
    compasser.h \
    consolecontrol.h \
    cloud.h

INCLUDEPATH += ../../inc

LIBS += $$PWD/../../lib/libboost_serialization-mgw53-mt-d-x32-1_68.a

unix {
    target.path = /usr/lib
    INSTALLS += target
}
