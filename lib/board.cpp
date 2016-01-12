#include "board.h"

#include <iterator>

board::board(int w, int h) {
	width = w;
	height = h;
	map.clear();
	for (int i = 0; i<h; i++) {
		board::row r;
		for (int j = 0; j<w; j++)
			r.push_back(false);
		map.push_back(r);
	}
}

void board::Merge(const block &b) {
	const int h = b.shape.height, w = b.shape.width;
	for (int i = 0; i<w; i++) {
		for (int j = 0; j<h; j++) {
			if (b.shape.b[j][i])
				map[height - (b.start_point.x + j) - 1]
					[b.start_point.y + i] = true;
		}
	}
}
