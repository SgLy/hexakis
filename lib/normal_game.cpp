#include "normal_game.h"

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
	now.start_point = point((brd.width - now.shape.width) >> 1, 0);
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
		now.start_point = point((brd.width - now.shape.width) >> 1, 0);
		return true;
	}
	return false;
}

void normal_game::Rotate() {
	now.RotateClockwise();
}

void normal_game::MoveLeft() {
	now.MoveLeft();
}

void normal_game::MoveRight() {
	now.MoveRight();
}
