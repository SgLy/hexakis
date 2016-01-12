#include "board.h"

#include <iterator>

board::board() {}

board::board(int w, int h) {
	width = w;
	height = h;
	map.clear();
}

void board::Merge(block b) {
    const int h = b.shape.height, w = b.shape.width;
    
    table::reverse_iterator it = map.rbegin();
    // i indicates the row coord processing now
    // starting from the top of the map
    int i = height - 1 - map.size();
    // judgement start from the top of the block
    for (; i < b.start_point.x; ++i, ++it);
    // i to the bottom of the block
    for (; i < b.start_point.x + h - 1; ++it, ++i) {
        for (int j = 0; j < w; ++j)
            if (b.shape.b[i - b.start_point.x][j]) (*it)[j] = true;
    }
}