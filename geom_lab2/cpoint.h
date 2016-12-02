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

//http://www.personal.kent.edu/~rmuhamma/Compgeometry/MyCG/ConvexHull/GrahamScan/grahamScan.htm
//https://github.com/kartikkukreja/blog-codes/blob/master/src/Graham%20Scan%20Convex%20Hull.cpp
//http://www.sanfoundry.com/cpp-program-implement-jarvis-march-find-convex-hull/
//https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%94%D0%B6%D0%B0%D1%80%D0%B2%D0%B8%D1%81%D0%B0
//http://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/

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




};

#endif // CPOINT_H
