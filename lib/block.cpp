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

block_shape::block_shape(int w, int h, int s, int c) {
	width = w;
	height = h;
	color = c;
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
	return block(start_point + point(1, 0), shape);
}

bool block::Drop(board &b) {
	block t = FakeDrop();
	if (t.isHitBoard(b)) {
		b.Merge(*this);
		return true;
	}
	start_point.x++;
	return false;
}

void block::RotateClockwise() {
	shape.RotateClockwise();
}

void block::RotateCounterClockwise() {
	shape.RotateCounterClockwise();
}

void block::MoveLeft(const board &b) {
	point tmp_point = start_point + point(0,-1);
	if (block(tmp_point,shape).isHitBoard(b)) return;
	start_point = tmp_point;
}

void block::MoveRight(const board &b) {
	point tmp_point = start_point + point(0,1);
	if (block(tmp_point,shape).isHitBoard(b)) return;
	start_point = tmp_point;
}

bool block::isHitBoard(const board &b) {
	const int h = shape.height, w = shape.width;
	
	// under construction
	for (int i = 0; i<h; i++) {
		for (int j = 0; j<w; j++) {
			int x = i + start_point.x;
			int y = j + start_point.y;
			if (shape.b[i][j] &&
				(x >= b.height || y >= b.width || y < 0 ||
				b.map[b.height - 1 - x][y]))
				return true;
		}
	}
	return false;
}

block block::FakeDropToBottom(board b) {
	block p, q;
	p = *this;
	q = p.FakeDrop();
	while (!q.isHitBoard(b)) {
		p = q;
		q = q.FakeDrop();
	}
	return p;
}

void block::DropToBottom(board &b) {
	while (!Drop(b));
}
