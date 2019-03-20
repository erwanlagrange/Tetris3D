#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T15:06:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestWebCamQt

TEMPLATE = app

SOURCES += main.cpp\
    myglwidget.cpp \
    Widget.cpp \
    camera.cpp

HEADERS  += \
    myglwidget.h \
    Widget.h \
    camera.h

FORMS    += \
    widget.ui \
    camera.ui \
    camera.ui

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413 \
    -lopencv_objdetect2413

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
        DEFINES  += _WIN32
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
unix:!macx {
        LIBS     += -lGL -lGLU
}
