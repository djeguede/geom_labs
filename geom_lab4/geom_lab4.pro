#-------------------------------------------------
#
# Project created by QtCreator 2016-12-17T19:06:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = geom_lab4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    swidget.cpp \
    segment_intersection.cpp \
    geom_lab4.cpp

HEADERS  += mainwindow.h \
    sweepline.h \
    swidget.h \
    segment_intersection.h \
    geom_lab4.h

FORMS    += mainwindow.ui \
    swidget.ui \
    geom_lab4.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/release/ -lqcustomplotd2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/debug/ -lqcustomplotd2

INCLUDEPATH += $$PWD/../QCustomPlot/
DEPENDPATH += $$PWD/../QCustomPlot/
