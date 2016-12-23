#include "mainwindow.h"
#include <QApplication>
#include "divideconquer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //ыw.show();

    DivideConquer dc;
    dc.show();

    return a.exec();
}
