#include "board.h"

board::board() {}

board::board(int w, int h) {
	width = w;
	height = h;
	map.clear();
}