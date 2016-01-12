#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <vector>
#include <deque>

class board;
class block;

#include "block.h"

class board {
public:
	typedef std::vector<bool> row;
	typedef std::deque<row> table;

	int height, width;
	table map;
	board();
	board(int w, int h);
	void Merge(block b);
};

#endif
