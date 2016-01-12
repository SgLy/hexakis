#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <vector>
#include <deque>

class board;
class block;

#include "block.h"

class board {
public:
	typedef std::vector<int> row;
	typedef std::deque<row> table;

	int height, width;
	table map;
	board() {}
	board(int w, int h);
	board(board &b) {
		map = b.map;
		height = b.height;
		width = b.width;
	}
	board(const board &b) {
		map.clear();
		for (const row r : b.map) {
			map.push_back(r);
		}
		height = b.height;
		width = b.width;
	}

	int EraseRows();

	void Merge(const block &b);
};

#endif
