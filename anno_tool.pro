#-------------------------------------------------
#
# Project created by QtCreator 2016-03-03T12:50:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = anno_tool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintWidget.cpp \
    donewdialog.cpp

HEADERS  += mainwindow.h \
    paintWidget.h \
    donewdialog.h

INCLUDEPATH += C:\opencv\build\include

win32:CONFIG(debug, debug|release): {
LIBS += -LC:\opencv\build\x86\vc10\lib \
-lopencv_core249d \
-lopencv_imgproc249d \
-lopencv_highgui249d \
-lopencv_ml249d \
-lopencv_video249d \
-lopencv_features2d249d \
-lopencv_calib3d249d \
-lopencv_objdetect249d \
-lopencv_contrib249d \
-lopencv_legacy249d \
-lopencv_flann249d
} else:win32:CONFIG(release, debug|release): {
LIBS += -LD:/openCV_build/x86/vc11/lib \
-lopencv_core249 \
-lopencv_imgproc249 \
-lopencv_highgui249 \
-lopencv_ml249 \
-lopencv_video249 \
-lopencv_features2d249 \
-lopencv_calib3d249 \
-lopencv_objdetect249 \
-lopencv_contrib249 \
-lopencv_legacy249 \
-lopencv_flann249
}

FORMS    += mainwindow.ui
