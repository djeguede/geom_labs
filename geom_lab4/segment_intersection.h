#ifndef SEGMENT_INTERSECTION_H
#define SEGMENT_INTERSECTION_H

#include <QDebug>

#include <set>
#include <math.h>
//#include <hash_set>
#include <unordered_set>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

struct pt {
    pt(int x, int y):x(x), y(y){}

    friend ostream &operator <<(ostream &stream, const pt &point);
    friend bool operator ==(const pt &first, const pt &second);
    int x;
    int y;
};

struct seg {
    seg(pt first, pt second):p(first), q(second) {}

    seg(): p{0,0}, q{0,0} {

    }

    double get_y (double x) const {
        if (p.x == q.x)  return p.y;
        return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }

    friend bool operator ==(const seg &first, const seg &second);
    friend ostream &operator <<(ostream &stream, const seg &segment);

    pt p;
    pt q;
    int id;
};

struct SegmentLessThan: public std::binary_function<seg, seg, bool> {
    bool operator () (const seg &first, const seg &second) const  {
        return first == second;
    }
};

struct event {
    int x;
    int tp;
    int id;

    event() { }
    event (int x, int tp, int id)
        : x(x), tp(tp), id(id)
    { }

    bool operator< (const event & e) const {
        if (this->x != e.x)  return x < e.x;
        return tp > e.tp;
    }
};

bool intersect1d (int l1, int r1, int l2, int r2);
int vec (const pt & a, const pt & b, const pt & c);
bool intersect (const seg & a, const seg & b);
bool operator< (const seg & a, const seg & b);
set<seg>::iterator prev (set<seg>::iterator it, const set<seg> &s);
set<seg>::iterator next (set<seg>::iterator it);
set<pair<int, int> > solve(const vector<seg> & a);

#endif // SEGMENT_INTERSECTION_H
