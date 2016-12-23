#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T00:54:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = geom_lab3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpoint.cpp \
    divideconquer.cpp

HEADERS  += mainwindow.h \
    cpoint.h \
    divideconquer.h

FORMS    += mainwindow.ui \
    divideconquer.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/release/ -lqcustomplotd2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build/Debug/QCustomPlot/debug/ -lqcustomplotd2

INCLUDEPATH += $$PWD/../QCustomPlot
DEPENDPATH += $$PWD/../QCustomPlot
