#ifndef CPOINT_H
#define CPOINT_H

#include <cstdlib>
#include  <algorithm>
#include <QDebug>
#include <ctime>
#include <math.h>
#include <QtPrintSupport/QPrinter>
#include <fstream>
#include <QFile>
#include <QPainter>
#include <QThread>




using namespace std;


class CPoint
{
private:
    double x;
    double y;

public:
    CPoint();
    CPoint(double xx, double yy);
    void setX(double arg);
    void setY(double arg);
    double getX();
    double getY();
    bool operator < (CPoint &pt);
    bool operator <= (CPoint &pt);
    bool operator > (CPoint &pt);
    bool operator >= (CPoint &pt);
    bool operator == (CPoint &pt);
    bool operator != (CPoint &pt);
    CPoint & operator = (CPoint &pt);
    friend void swapp(CPoint& pt1, CPoint& pt2);
    friend double distSq(CPoint p1, CPoint p2);
    friend int ccw(CPoint a, CPoint b, CPoint c);
    friend bool ccw2(CPoint a, CPoint b, CPoint c);




};

#endif // CPOINT_H
