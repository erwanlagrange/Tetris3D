QT       += core gui
QT       += opengl
QT       += widgets

HEADERS       = tetrixboard.h \
                tetrixpiece.h \
                tetrixwindow.h \
    camera.h
SOURCES       = main.cpp \
                tetrixboard.cpp \
                tetrixpiece.cpp \
                tetrixwindow.cpp \
    camera.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/tetrix
INSTALLS += target

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
