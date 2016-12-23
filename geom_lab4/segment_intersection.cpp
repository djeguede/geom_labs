#include "segment_intersection.h"

bool intersect1d (int l1, int r1, int l2, int r2) {
    if (l1 > r1)  swap (l1, r1);
    if (l2 > r2)  swap (l2, r2);
    return max(l1, l2) <= min(r1, r2);
}

int vec (const pt & a, const pt & b, const pt & c) {
    double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return /*s == 0 ? 0 :*/ s > 0 ? +1 : -1;
}

bool intersect (const seg & a, const seg & b) {
    return intersect1d (a.p.x, a.q.x, b.p.x, b.q.x)
            && intersect1d (a.p.y, a.q.y, b.p.y, b.q.y)
            && vec (a.p, a.q, b.p) * vec (a.p, a.q, b.q) <= 0
            && vec (b.p, b.q, a.p) * vec (b.p, b.q, a.q) <= 0;
}

bool operator< (const seg & a, const seg & b) {
    int x = max (min (a.p.x, a.q.x), min (b.p.x, b.q.x));
    return a.get_y(x) < b.get_y(x);
}

set<seg>::iterator prev (set<seg>::iterator it, const set<seg> &s) {
    return it == s.begin() ? s.end() : --it;
}

set<seg>::iterator next (set<seg>::iterator it, const set<seg> &s) {
    if (it != s.end()) {
        return ++it;
    } else {
        return it;
    }
}

//set< pair<int,int> > solve (const vector<seg> &a) {
//    const clock_t begin_time = clock();
//    vector<event> e;
//    for (auto i = 0; i < a.size(); ++i) {
//        e.push_back (event (min (a[i].p.x, a[i].q.x), +1, i));
//        e.push_back (event (max (a[i].p.x, a[i].q.x), -1, i));
//    }
//    qDebug() << "1";
//    sort(e.begin(), e.end());
//    qDebug() << "2";

//    set<seg> s;
//    vector < set<seg>::iterator > where;
//    set < pair<int, int> > intersectSegments;
//    where.resize (a.size());

//    qDebug() << "3";
//    for (size_t i = 0; i < e.size(); ++i) {
//        //std::cout << e[i].id << " " << e[i].x << endl;
//        int id = e[i].id;
//        if (e[i].tp == +1) {
//            qDebug() << "3.2";
//            for (auto it = s.begin(); it != s.end(); ++it) {
//                set<seg>::iterator nxt = it;
//                set<seg>::iterator prv = prev (nxt, s);
//                if (nxt != s.end() && intersect (*nxt, a[id]) && !((*nxt) == a[id])) {
//                    //intersectSegments.insert(make_pair (nxt->id, id));
//                    //cout << "intersection+n " << (*nxt) << " " << a[id] << endl;
//                }
//                if (prv != s.end() && intersect (*prv, a[id]) && !((*prv) == a[id])){
//                    //intersectSegments.insert(make_pair (prv->id, id));
//                    //cout << "intersection+p " << (*prv) << " " << a[id] <<  endl;
//                }
//            }
//            qDebug() << "3.5";
//            seg temp = a[id];
//            temp.id = id;
//            set<seg>::iterator nxt = s.lower_bound (a[id]);
//            where[id] = s.insert (nxt, temp);

//            qDebug() << "4.0";
////            cout << "insert " << temp << endl;

////            for(seg segment:s) {
////                cout << segment.id << " ";
////            }
////            cout << endl;
//        }
//        else {
//            set<seg>::iterator nxt = next (where[id]);
//            set<seg>::iterator  prv = prev (where[id], s);
//            if (nxt != s.end() && prv != s.end() && intersect (*nxt, *prv)) {
//                intersectSegments.insert(make_pair (prv->id, nxt->id));
//                //cout << "intersection- " << (*prv) << " " << (*nxt) << endl;
//            }
//            //cout << "erase " << (*where[id]) << endl;
//            qDebug() << "5.0";
//            s.erase (where[id]);
//            qDebug() << "6.0";
//        }
//    }
//    qDebug() << "time = " << double(clock () - begin_time)/ CLOCKS_PER_SEC;
//    return intersectSegments;
//}

set< pair<int,int> > solve (const vector<seg> &a) {
    //const clock_t begin_time = clock();

    vector<event> e;
    for (auto i = 0; i < a.size(); ++i) {
        e.push_back (event (min (a[i].p.x, a[i].q.x), +1, i));
        e.push_back (event (max (a[i].p.x, a[i].q.x), -1, i));
    }
    sort(e.begin(), e.end());

    set<seg> s;
    map <size_t, seg> where;
    set < pair<int, int> > intersectSegments;

    for (size_t i = 0; i < e.size(); ++i) {
        int id = e[i].id;
        if (e[i].tp == +1) {
            for (auto it = s.begin(); it != s.end(); ++it) {
                set<seg>::iterator nxt = it;
                set<seg>::iterator prv = prev (nxt, s);
                if (nxt != s.end() && intersect (*nxt, a[id]) && !((*nxt) == a[id])) {
                    intersectSegments.insert(make_pair (nxt->id, id));
                }
                if (prv != s.end() && intersect (*prv, a[id]) && !((*prv) == a[id])){
                    intersectSegments.insert(make_pair (prv->id, id));
                }
            }

            seg temp = a[id];
            temp.id = id;
            set<seg>::iterator nxt = s.lower_bound (temp);
            s.insert (nxt, temp);

            map<size_t, seg>::iterator it = where.find(id);
            if (it == where.end()) {
                where[id] = temp;
            } else {
                it->second = temp;
            }
        } else {
            map<size_t, seg>::iterator it = where.find(id);
            if (it != where.end()) {
                set<seg>::iterator itSegment = s.find(it->second);
                set<seg>::iterator nxt = next(itSegment, s);
                set<seg>::iterator  prv = prev (itSegment, s);
                if (nxt != s.end() && prv != s.end() && intersect (*nxt, *prv)) {
                    intersectSegments.insert(make_pair (prv->id, nxt->id));
                }
                where.erase(it);
            }
        }
    }
    //qDebug() << "time = " << double(clock () - begin_time)/ CLOCKS_PER_SEC;
    return intersectSegments;
}


ostream &operator <<(ostream &stream, const pt &point)
{
    stream << "[" << point.x << " " << point.y << "]";
    return stream;
}

ostream &operator <<(ostream &stream, const seg &segment)
{
    stream << segment.id << " " << segment.p << " " << segment.q;
    return stream;
}

bool operator ==(const seg &first, const seg &second)
{
    return first.p == second.p && first.q == second.q;
}

bool operator ==(const pt &first, const pt &second)
{
    return first.x == second.x && first.y == second.y;
}
