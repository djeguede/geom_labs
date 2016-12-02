#include "cpoint.h"

CPoint::CPoint()
{

}

CPoint::CPoint(double xx, double yy):x(xx),y(yy)
{

}

void CPoint::setX(double arg)
{
 x= arg;
}

void CPoint::setY(double arg)
{
 y=arg;
}

double CPoint::getX()
{
 return x;
}

double CPoint::getY()
{
 return y;
}

bool CPoint::operator <(CPoint &pt)
{
 if(y<pt.getY() || (y==pt.getY() && x<pt.getX() ) ) return true;
 else return false;
}

bool CPoint::operator <=(CPoint &pt)
{
    if(y<=pt.getY() || (y==pt.getY() && x<=pt.getX() ) ) return true;
    else return false;
}

bool CPoint::operator >(CPoint &pt)
{
    if(y>pt.getY() || (y==pt.getY() && x>pt.getX() ) ) return true;
    else return false;
}

bool CPoint::operator >=(CPoint &pt)
{
    if(y>=pt.getY() || (y==pt.getY() && x>=pt.getX() )  ) return true;
    else return false;
}

bool CPoint::operator ==(CPoint &pt)
{
    return ( (x== pt.getX()) && y ==pt.getY() ) ;
}

bool CPoint::operator !=(CPoint &pt)
{
    return ( (x!= pt.getX()) || y !=pt.getY() ) ;
}

CPoint &CPoint::operator =(CPoint &pt)
{
  x=pt.getX();
  y=pt.getY();
  return *this;
}

void swapp(CPoint& pt1, CPoint& pt2)
{
    CPoint temp = pt1;
    pt1 = pt2;
    pt2 = temp;
}

double distSq(CPoint p1, CPoint p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}




// returns -1 if a -> b -> c forms a counter-clockwise turn,
// +1 for a clockwise turn, 0 if they are collinear
int ccw(CPoint a, CPoint b, CPoint c)
{
    double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area > 0)
        return -1;
    else if (area < 0)
        return 1;
    return 0;
}


