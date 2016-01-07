#ifndef UTIL_INCLUDED
#define UTIL_INCLUDED

#include <map>

void milliSleep(int ms);
int random(int range);
int min(int a, int b);
int max(int a, int b);
int CalcTime(int max_time, int min_time, int interval, int len);

struct point {
    int x, y;
    point () : x(0), y(0) {}
    point (int xx, int yy) : x(xx), y(yy) {}
};

bool operator == (const point a, const point b);
bool operator != (const point a, const point b);
point operator - (const point a);
point operator + (const point a, const point b);
point operator += (const point a, const point b);
point operator - (const point a, const point b);

#endif