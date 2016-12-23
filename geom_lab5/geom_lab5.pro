#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T03:34:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = geom_lab5
TEMPLATE = app


SOURCES += main.cpp\
        geom_lab5.cpp \
    vornoiwidget.cpp \
    voronoi_good.cpp \
    voronoi_moi.cpp

HEADERS  += geom_lab5.h \
    vornoiwidget.h \
    voronoi_good.h \
    voronoi_moi.h

FORMS    += geom_lab5.ui \
    vornoiwidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/release/ -lqcustomplotd2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/debug/ -lqcustomplotd2

INCLUDEPATH += $$PWD/../QCustomPlot
DEPENDPATH += $$PWD/../QCustomPlot
