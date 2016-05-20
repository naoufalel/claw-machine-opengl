#-------------------------------------------------
#
# Project created by QtCreator 2016-05-20T21:48:04
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AnimatedClawMachine
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp \
    user.cpp \
    score.cpp \
    camerainteraction.cpp \
    clawinteraction.cpp

HEADERS  += mainview.h \
    user.h \
    score.h \
    camerainteraction.h \
    clawinteraction.h

FORMS    += mainview.ui \
    scores.ui



INCLUDEPATH +=$$(OPENCV_DIR)\include

LIBS += -lglut -lGLU


LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_video \
    -lopencv_features2d \
    -lopencv_calib3d \
    -lopencv_objdetect
