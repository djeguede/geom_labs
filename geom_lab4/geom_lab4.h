#ifndef GEOM_LAB4_H
#define GEOM_LAB4_H

#include <QMainWindow>
#include "swidget.h"
#include <QtPrintSupport/QPrinter>

namespace Ui {
class geom_lab4;
}

class geom_lab4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit geom_lab4(QWidget *parent = 0);
    ~geom_lab4();

private:
    Ui::geom_lab4 *ui;

public slots:
    void drawGraphic();

private:
    QVector<double> n;
    QVector<double> nlogn;
    QVector<double> lab4;
};

#endif // GEOM_LAB4_H
