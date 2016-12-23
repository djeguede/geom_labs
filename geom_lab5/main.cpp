#include "geom_lab5.h"
#include <QApplication>

#include "vornoiwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    geom_lab5 w;
    w.show();

    VornoiWidget VW;
    VW.show();

    return a.exec();
}
