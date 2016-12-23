#ifndef VORNOIWIDGET_H
#define VORNOIWIDGET_H

#include <QWidget>
#include "voronoi_good.h"
#include <QtPrintSupport/QPrinter>
#include <QPainter>

using namespace Voronoi;

namespace Ui {
class VornoiWidget;
}

class VornoiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VornoiWidget(QWidget *parent = 0);
    ~VornoiWidget();

protected:
    void paintEvent(QPaintEvent *e);

private:
    Ui::VornoiWidget *ui;
};

#endif // VORNOIWIDGET_H
