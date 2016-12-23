#ifndef DIVIDECONQUER_H
#define DIVIDECONQUER_H

#include <QWidget>
#include "cpoint.h"
#include <QtPrintSupport/QPrinter>

namespace Ui {
class DivideConquer;
}

class DivideConquer : public QWidget
{
    Q_OBJECT

public:
    explicit DivideConquer(QWidget *parent = 0);
    ~DivideConquer();

    std::vector<CPoint> jarvis(std::vector<CPoint> lpoints);
    std::vector<CPoint> Merge(std::vector<CPoint>P1,  std::vector<CPoint>P2);
    std::vector<CPoint> divideConq(std::vector<CPoint> vertex, QPainter & paint);

protected:
    void paintEvent(QPaintEvent *e);


private:
    Ui::DivideConquer *ui;


public:
    static CPoint pivotP1;
    static CPoint pivotP2;
};

#endif // DIVIDECONQUER_H
