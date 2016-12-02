#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include "clist.h"
#include <ctime>
#include <math.h>
#include <QtPrintSupport/QPrinter>
#include <QTableWidgetItem>
#include <QFile>
#include <fstream>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QMap<int, int> map;
    QVector<double> y_exper;
    QVector<double> y_theory;
    QVector<double> n;

    QFile file1;
    ofstream myfile;
};

#endif // WIDGET_H
