#include "widget.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    //w.show();

    MainWindow mw;
    mw.show();

    return a.exec();
}
