#include "block.h"
#include "board.h"

#include <iterator>

using namespace util;

// Class Blcok_Shape

const int block_shape::PRESET_N = 7;
const int block_shape::PRESET_SHAPE[PRESET_N] = {114, 15, 51, 547, 275, 99, 54};
const int block_shape::PRESET_WIDTH[PRESET_N] = {3, 4, 2, 2, 2, 3, 3};
const int block_shape::PRESET_HEIGHT[PRESET_N] = {2, 1, 2, 3, 3, 2, 2};

block_shape::block_shape() {}

block_shape::block_shape(int w, int h, int s) {
	width = w;
	height = h;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			b[i][j] = ((s >> (i * 4 + j)) % 2 == 1);
}

int block_shape::toInt() {
	int s = 0;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j) {
			if (!b[i][j]) continue;
			s ^= (1 << (i * 4 + j));
		}
	return s;
}

void block_shape::Clear() {
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			b[i][j] = false;
}

void block_shape::RotateClockwise() {
	block_shape t;
	t.Clear();
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			t.b[j][height - 1 - i] = b[i][j];
	int tmp = width;
	width = height;
	height = tmp;
	Clear();
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			b[i][j] = t.b[i][j];
}

void block_shape::RotateCounterClockwise() {
	block_shape t;
	t.Clear();
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			t.b[width - 1 - j][i] = b[i][j];
	int tmp = width;
	width = height;
	height = tmp;
	Clear();
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			b[i][j] = t.b[i][j];
}

block::block() {}

block::block(point s, block_shape bs) {
	start_point = s;
	shape = bs;
}

block_shape block_shape::GetRandomBlockShape() {
	int t = random(7);
	block_shape bs = preset(t);
	int r = random(4);
	while (r--)
		bs.RotateClockwise();
	return bs;
}
// Class Block_Shape Done

//Class Block
block block::FakeDrop() {
	return block(start_point + point(0, 1), shape);
}

bool block::Drop(board b) {
	block t = FakeDrop();
	if (t.isHitBoard(b)) {
		b.Merge(*this);
		return true;
	}
	start_point.y++;
	return false;
}

void block::RotateClockwise() {
	shape.RotateClockwise();
}

void block::RotateCounterClockwise() {
	shape.RotateCounterClockwise();
}

void block::MoveLeft() {
	start_point += point(0, 1);
}

void block::MoveRight() {
	start_point += point(0, -1);
}

bool block::isHitBoard(board b) {
	const int h = shape.height, w = shape.width;
	
	// under construction
	// if bottom of block above top of map
	if (start_point.x + h - 1 < b.height - 1 - b.map.size())
		return false;

	board::table::reverse_iterator it = b.map.rbegin();
	// i indicates the row coord processing now
	// starting from the top of the map
	int i = b.height - 1 - b.map.size();
	// judgement start from the top of the block
	for (; i < start_point.x; ++i, ++it);
	// i to the bottom of the block
	for (; i < start_point.x + h - 1; ++it, ++i) {
		for (int j = 0; j < w; ++j)
			if ( (*it)[j] && shape.b[i][j]) return true;
	}
	return false;
}

void block::DropToBottom(board b) {
	while (!Drop(b));
}
