#ifndef SWIDGET_H
#define SWIDGET_H

#include <QWidget>
#include "segment_intersection.h"
#include <QtPrintSupport/QPrinter>
#include <QPainter>

namespace Ui {
class SWidget;
}

class SWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SWidget(QWidget *parent = 0);
    ~SWidget();

protected:
    void paintEvent(QPaintEvent *e);

private:
    Ui::SWidget *ui;
};

#endif // SWIDGET_H
