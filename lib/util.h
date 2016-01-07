#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED

#include <algorithm>

namespace util {

    using std::min;
    using std::max;

    void milliSleep(int ms);
    int random(int range);

    struct point {
        int x, y;
        point () : x(0), y(0) {}
        point (int xx, int yy) : x(xx), y(yy) {}
        point (const point &p) : x(p.x), y(p.y) {}
    };

    bool operator == (const point a, const point b);
    bool operator != (const point a, const point b);
    point operator - (const point a);
    point operator + (const point a, const point b);
    point operator += (const point a, const point b);
    point operator - (const point a, const point b);

}

#endif
