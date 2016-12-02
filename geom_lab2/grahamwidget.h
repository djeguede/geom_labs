#ifndef GRAHAMWIDGET_H
#define GRAHAMWIDGET_H

#include <QWidget>
#include "cpoint.h"
#include <QtPrintSupport/QPrinter>

namespace Ui {
class GrahamWidget;
}

class GrahamWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GrahamWidget(QWidget *parent = 0);
    ~GrahamWidget();

protected:
    void paintEvent(QPaintEvent *e);

private:
    Ui::GrahamWidget *ui;
    static CPoint pivot;
};

#endif // GRAHAMWIDGET_H
