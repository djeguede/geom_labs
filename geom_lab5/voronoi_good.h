#ifndef VORONOI_GOOD_H
#define VORONOI_GOOD_H

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <math.h>
#include <random>
#include <ctime>

#include <QDebug>

using namespace std;

namespace Voronoi {

typedef pair<double, double> point;
struct arc;
struct seg;

struct event {
    double x;
    point p;
    arc *a;
    bool valid;

    event(double xx, point pp, arc *aa)
        : x(xx), p(pp), a(aa), valid(true) {}
};

struct arc {
    point p;
    arc *prev, *next;
    event *e;

    seg *s0, *s1;

    arc(point pp, arc *a=0, arc *b=0)
        : p(pp), prev(a), next(b), e(0), s0(0), s1(0) {}
};

struct seg {
    point start, end;
    bool done;

    seg(point p)
        : start(p), end(0,0), done(false)
    {}

    // Set the end point and mark as "done."
    void finish(point p) {
        if (done) return;
        end = p;
        done = true;
    }
};

struct gt {
    bool operator()(point a, point b) {return a.first == b.first ? a.second > b.second : a.first > b.first;}
    bool operator()(event *a, event *b) {return a->x > b->x;}
};

class FortuneAlgorithm {
public:
    FortuneAlgorithm();
    ~FortuneAlgorithm();
    vector<seg*> getVoronoiDiagram(set<Voronoi::point> sourcePoint);

protected:
    void clear();

    void process_point();
    void process_event();
    void front_insert(point  p);

    bool circle(point a, point b, point c, double *x, point *o);
    void check_circle_event(arc *i, double x0);

    bool intersect(point p, arc *i, point *result = 0);
    point intersection(point p0, point p1, double l);

    void finish_edges();
    void print_output();

private:
    vector<seg*> output;

    arc *root;

    priority_queue<point,  vector<point>,  gt> points; // site events
    priority_queue<event*, vector<event*>, gt> events;

    double X0;
    double X1;
    double Y0;
    double Y1;
};


}
#endif // VORONOI_GOOD_H
