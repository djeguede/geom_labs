#ifndef GEOM_LAB5_H
#define GEOM_LAB5_H

#include <QMainWindow>
#include "vornoiwidget.h"
#include <QtPrintSupport/QPrinter>

namespace Ui {
class geom_lab5;
}

class geom_lab5 : public QMainWindow
{
    Q_OBJECT

public:
    explicit geom_lab5(QWidget *parent = 0);
    ~geom_lab5();

private:
    Ui::geom_lab5 *ui;

public slots:
    void drawGraphic();

private:
    QVector<double> n;
    QVector<double> nlogn;
    QVector<double> lab5;
};

#endif // GEOM_LAB5_H
