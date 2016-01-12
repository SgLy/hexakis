#include <stdlib.h>
#include <time.h>
#include "util.h"

#if defined linux
#include <unistd.h> // Microsoft Visual C++ do not has this header
#endif

#if defined WIN32
#include <windows.h> // POSIX-only environment do not has this header
#endif

namespace util{

#if defined linux
	void milliSleep(int ms) {
		timespec ts;
		ts.tv_sec = ms / 1000;
		ts.tv_nsec = (ms % 1000) * 1000000L;
		nanosleep(&ts, NULL);
	}
#endif

#if defined WIN32
	void milliSleep(int ms) {
		sleep(ms);
	}
#endif

	int random(int range) {
		return rand() % range;
	}

	bool operator == (const point a, const point b) {
		return a.x == b.x && a.y == b.y;
	}

	bool operator != (const point a, const point b) {
		return !(a == b);
	}

	point operator - (const point a) {
		return point(-a.x, -a.y);
	}

	point operator + (const point a, const point b) {
		return point(a.x + b.x, a.y + b.y);
	}

	point &operator += (point &a, const point b) {
		a.x += b.x;
		a.y += b.y;
		return a;
	}

	point operator - (const point a, const point b) {
		return a + (-b);
	}

}
