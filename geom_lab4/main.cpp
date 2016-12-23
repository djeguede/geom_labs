#include "mainwindow.h"
#include <QApplication>
#include "swidget.h"
#include "geom_lab4.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    SWidget sw;
    sw.show();

    geom_lab4 lab4;
    lab4.show();

    return a.exec();
}
