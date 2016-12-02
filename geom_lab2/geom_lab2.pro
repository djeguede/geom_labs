#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T09:26:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = geom_lab2
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    cpoint.cpp \
    mainwindow.cpp \
    grahamwidget.cpp

HEADERS  += widget.h \
    cpoint.h \
    mainwindow.h \
    grahamwidget.h

FORMS    += widget.ui \
    mainwindow.ui \
    grahamwidget.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/release/ -lqcustomplotd2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/debug/ -lqcustomplotd2

INCLUDEPATH += $$PWD/../QCustomPlot
DEPENDPATH += $$PWD/../QCustomPlot
