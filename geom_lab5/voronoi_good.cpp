#include "voronoi_good.h"

Voronoi::FortuneAlgorithm::FortuneAlgorithm()
{
    root = 0;
    X0 = 0.0;
    X1 = 0.0;
    Y0 = 0.0;
    Y1 = 0.0;
}

Voronoi::FortuneAlgorithm::~FortuneAlgorithm()
{
    clear();
}

vector<Voronoi::seg*> Voronoi::FortuneAlgorithm::getVoronoiDiagram(set<point> sourcePoint)
{
    clear();
    // Read points from input.
    point p;

    for (set<Voronoi::point>::const_iterator it = sourcePoint.cbegin(); it != sourcePoint.cend(); ++it) {
        p = (*it);
        points.push(p);

        // Keep track of bounding box size.
        if (p.first < X0) X0 = p.first;
        if (p.second < Y0) Y0 = p.second;
        if (p.first > X1) X1 = p.first;
        if (p.second > Y1) Y1 = p.second;
    }
    // Add 20% margins to the bounding box.
    double dx = (X1-X0+1.0)/5.0;
    double dy = (Y1-Y0+1.0)/5.0;
    X0 -= dx;
    X1 += dx;
    Y0 -= dy;
    Y1 += dy;

    // Process the queues; select the top element with smaller x coordinate.
    while (!points.empty())
        if (!events.empty() && events.top()->x <= points.top().first)
            process_event();
        else
            process_point();

    // After all points are processed, do the remaining circle events.
    while (!events.empty())
        process_event();

    finish_edges(); // Clean up dangling edges.
    //print_output(); // Output the voronoi diagram.
    return output;
}

void Voronoi::FortuneAlgorithm::clear()
{
    while (!events.empty()) {
        event *e = events.top();
        events.pop();
        delete e;
    }
    while (!points.empty()) {
        points.pop();
    }
    for(vector<seg*>::size_type i = 0;i < output.size(); ++i) {
        delete output[i];
    }
    output.clear();

    root = 0;
    X0 = 0.0;
    X1 = 0.0;
    Y0 = 0.0;
    Y1 = 0.0;
}

void Voronoi::FortuneAlgorithm::process_point()
{
    // Get the next point from the queue.
    point p = points.top();
    points.pop();

    // Add a new arc to the parabolic front.
    front_insert(p);
}

void Voronoi::FortuneAlgorithm::process_event()
{
    // Get the next event from the queue.
    event *e = events.top();
    events.pop();

    if (e->valid) {
        // Start a new edge.
        seg *s = new seg(e->p);
        //output.push_back(s);

        // Remove the associated arc from the front.
        arc *a = e->a;
        if (a->prev) {
            a->prev->next = a->next;
            a->prev->s1 = s;
        }
        if (a->next) {
            a->next->prev = a->prev;
            a->next->s0 = s;
        }

        // Finish the edges before and after a.
        if (a->s0) {
            a->s0->finish(e->p);
            output.push_back(a->s0);
        }
        if (a->s1) {
            a->s1->finish(e->p);
            output.push_back(a->s1);
        }

        // Recheck circle events on either side of p:
        if (a->prev) {
            check_circle_event(a->prev, e->x);
        }
        if (a->next) {
            check_circle_event(a->next, e->x);
        }
    }
    delete e;
}

void Voronoi::FortuneAlgorithm::front_insert(point p)
{
    if (!root) {
        root = new arc(p);
        return;
    }

    // Find the current arc(s) at height p.y (if there are any).
    for (arc *i = root; i; i = i->next) {
        point z, zz;
        if (intersect(p,i,&z)) {
            // New parabola intersects arc i.  If necessary, duplicate i.
            if (i->next) {
                if (!intersect(p,i->next, &zz)) {
                    i->next->prev = new arc(i->p, i, i->next);
                    i->next = i->next->prev;
                }
            }
            else {
                i->next = new arc(i->p,i);
            }
            i->next->s1 = i->s1;

            //            if (i->next && !intersect(p,i->next, &zz)) {
            //                i->next->prev = new arc(i->p,i,i->next);
            //                i->next = i->next->prev;
            //            }
            //            else i->next = new arc(i->p,i);
            //            i->next->s1 = i->s1;

            // Add p between i and i->next.
            i->next->prev = new arc(p, i, i->next);
            i->next = i->next->prev;

            i = i->next; // Now i points to the new arc.

            // Add new half-edges connected to i's endpoints.
            i->prev->s1 = i->s0 = new seg(z);
            //output.push_back(i->s0);
            i->next->s0 = i->s1 = new seg(z);
            //output.push_back(i->s1);

            // Check for new circle events around the new arc:
            check_circle_event(i, p.first);
            check_circle_event(i->prev, p.first);
            check_circle_event(i->next, p.first);

            return;
        }
    }

    // Special case: If p never intersects an arc, append it to the list.

    arc *i;
    for (i = root; i->next; i=i->next) ; // Find the last node.

    i->next = new arc(p,i);
    // Insert segment between p and i
    point start;
    start.first = X0;
    start.second = (i->next->p.second + i->p.second) / 2.0;
    i->s1 = i->next->s0 = new seg(start);
    //output.push_back(i->s1);
}

// Look for a new circle event for arc i.
void Voronoi::FortuneAlgorithm::check_circle_event(arc *i, double x0)
{
    // Invalidate any old event.
    if (i->e && i->e->x != x0)
        i->e->valid = false;
    i->e = NULL;


    if (!i->prev || !i->next)
        return;

    double x;
    point o;

    if (circle(i->prev->p, i->p, i->next->p, &x, &o) && x >= x0) {
        // Create new event.
        i->e = new event(x, o, i);
        events.push(i->e);
    }
}

// Find the rightmost point on the circle through a,b,c.
bool Voronoi::FortuneAlgorithm::circle(point a, point b, point c, double *x, point *o)
{
    // Check that bc is a "right turn" from ab.
    if ((b.first-a.first)*(c.second-a.second) - (c.first-a.first)*(b.second-a.second) > 0.0)
        return false;

    // Algorithm from O'Rourke 2ed p. 189.
    double A = b.first - a.first,  B = b.second - a.second,
            C = c.first - a.first,  D = c.second - a.second,
            E = A*(a.first+b.first) + B*(a.second+b.second),
            F = C*(a.first+c.first) + D*(a.second+c.second),
            G = 2*(A*(c.second-b.second) - B*(c.first-b.first));

    if (G == 0.0)
        return false;  // Points are co-linear.

    // Point o is the center of the circle.
    o->first = (D*E-B*F)/G;
    o->second = (A*F-C*E)/G;

    // o.first plus radius equals max x coordinate.
    *x = o->first + sqrt( pow(a.first - o->first, 2) + pow(a.second - o->second, 2) );
    return true;
}

// Will a new parabola at point p intersect with arc i?
bool Voronoi::FortuneAlgorithm::intersect(point p, arc *i, point *result)
{
    if (i->p.first == p.first) return false;

    double a,b;
    if (i->prev) // Get the intersection of i->prev, i.
        a = intersection(i->prev->p, i->p, p.first).second;
    if (i->next) // Get the intersection of i->next, i.
        b = intersection(i->p, i->next->p, p.first).second;

    if ((!i->prev || a <= p.second) && (!i->next || p.second <= b)) {
        result->second = p.second;

        result->first = (i->p.first*i->p.first + (i->p.second-result->second)*(i->p.second-result->second) - p.first*p.first)
                / (2*i->p.first - 2*p.first);

        return true;
    }
    return false;
}

// Where do two parabolas intersect?
Voronoi::point Voronoi::FortuneAlgorithm::intersection(point p0, point p1, double l)
{
    point res, p = p0;

    double z0 = 2*(p0.first - l);
    double z1 = 2*(p1.first - l);

    if (p0.first == p1.first)
        res.second = (p0.second + p1.second) / 2.0;
    else if (p1.first == l) {
        res.second = p1.second;
    } else if (p0.first == l) {
        res.second = p0.second;
        p = p1;
    } else {
        // Use the quadratic formula.
        double a = 1/z0 - 1/z1;
        double b = -2*(p0.second/z0 - p1.second/z1);
        double c = (p0.second*p0.second + p0.first*p0.first - l*l)/z0 - (p1.second*p1.second + p1.first*p1.first - l*l)/z1;
        res.second = ( -b - sqrt(b*b - 4*a*c) ) / (2*a);
    }
    // Plug back into one of the parabola equations.
    res.first = (p.first*p.first + (p.second-res.second)*(p.second-res.second) - l*l)/(2*p.first-2*l);
    return res;
}

void Voronoi::FortuneAlgorithm::finish_edges()
{
    // Advance the sweep line so no parabolas can cross the bounding box.
    double l = X1 + (X1-X0) + (Y1-Y0);

    //     Extend each remaining segment to the new parabola intersections.
    //    for (arc *i = root; i->next; i = i->next) {
    //        if (i->s1) {
    //            i->s1->finish(intersection(i->p, i->next->p, l*2));
    //        }
    //    }

    for (arc *i = root; i; i = i->next) {
        if (i->s1 && i->next) {
            i->s1->finish(intersection(i->p, i->next->p, l*2));
            output.push_back(i->s1);
        } else if (i->s1 && i->s0) {
            //i->s1->end = i->s0->start;
        }
    }

    for (vector<seg*>::iterator it = output.begin(); it != output.end();) {
        //double distance = sqrt(pow((*it)->end.first - (*it)->start.first, 2) + pow((*it)->end.second - (*it)->start.second, 2));
        if ((*it)->end.first == 0.0 && (*it)->end.second == 0.0) {
            it = output.erase(it);
        } else {
            ++it;
        }
    }
}

void Voronoi::FortuneAlgorithm::print_output()
{
    // Bounding box coordinates.
    cout << X0 << " "<< X1 << " " << Y0 << " " << Y1 << endl;

    // Each output segment in four-column format.
    vector<seg*>::iterator i;
    for (i = output.begin(); i != output.end(); i++) {
        point p0 = (*i)->start;
        point p1 = (*i)->end;
        cout << "[" << p0.first << " " << p0.second << "] [" << p1.first << " " << p1.second << "]" << endl;
    }
}
