#include <stdlib.h>
#include <time.h>
#include "util.h"
#include <stdio.h>

#if defined _POSIX_SOURCE
#include <unistd.h> // Microsoft Visual C++ do not has this header
#include <fcntl.h>
#endif

#if defined WIN32
#include <windows.h> // POSIX-only environment do not has this header
#endif

namespace util{

static FILE *fdevrandom = NULL;
static bool use_devrandom = true;

#if defined _POSIX_SOURCE
	int random(int range) {
		if (!use_devrandom) return rand() % range;
		if (fdevrandom == NULL) {
			fdevrandom = fopen("/dev/urandom","r");
			if (fdevrandom == NULL) {
				use_devrandom = false;
				return rand() % range;
			}
		}
		int n;
		fread (&n, sizeof(int), 1, fdevrandom);
		if (ferror (fdevrandom)) {
			use_devrandom = false;
			return rand() % range;
		}
		if (n < 0) n = -n;
		return n % range;
	}
#else
	int random(int range) {
		return rand() % range;
	}
#endif

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
