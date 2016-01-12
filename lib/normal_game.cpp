#include "normal_game.h"
#include "board.h"
#include "block.h"

using namespace util;

normal_game::normal_game(int w, int h) {
	next = block(point(0, 0), block_shape::GetRandomBlockShape());
	brd = board(w, h);
	running = false;
}

int normal_game::GetHeight() {
	return brd.height;
}

int normal_game::GetWidth() {
	return brd.width;
}

void normal_game::Reset() {
	*this = normal_game(GetWidth(), GetHeight());
}

void normal_game::Start() {
	now = next;
	next = block(point(0, 0), block_shape::GetRandomBlockShape());
	now.start_point = point(0, (brd.width - now.shape.width) >> 1);
	running = true;
}

void normal_game::Pause() {
	running = false;
}

void normal_game::Resume() {
	running = true;
}

bool normal_game::isRunning() {
	return running;
}

bool normal_game::Drop() {
	if (now.Drop(brd)) {
		now = next;
		next = block(point(0, 0), block_shape::GetRandomBlockShape());
		now.start_point = point(0, (brd.width - now.shape.width) >> 1);
		return true;
	}
	return false;
}

void normal_game::Rotate() {
	if (now.start_point.x + now.shape.height - 1 >= brd.width) return;
	now.RotateClockwise();
}

void normal_game::MoveLeft() {
	now.MoveLeft(brd);
}

void normal_game::MoveRight() {
	now.MoveRight(brd);
}

int normal_game::EraseRows() {
	return brd.EraseRows();
}

void normal_game::DropToBottom()
{
	now.DropToBottom(brd);
	now = next;
	next = block(point(0, 0), block_shape::GetRandomBlockShape());
	now.start_point = point(0, (brd.width - now.shape.width) >> 1);
}

block normal_game::GetDropPosition() {
	return now.FakeDropToBottom(brd);
}