#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "cpoint.h"
#include <QtPrintSupport/QPrinter>

using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent();

protected:
    void paintEvent(QPaintEvent *e);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
