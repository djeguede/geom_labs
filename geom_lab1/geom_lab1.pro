#-------------------------------------------------
#
# Project created by QtCreator 2016-10-23T23:03:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = geom_lab1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    clist.h

FORMS    += widget.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/release/ -lqcustomplotd2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/debug/ -lqcustomplotd2

INCLUDEPATH += $$PWD/../QCustomPlot
DEPENDPATH += $$PWD/../QCustomPlot
