#include normal_game

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

block normal_game::GetCurrentBlock() {
	return now;
}

block normal_game::GetNextBlock() {
	return next;
}

void normal_game::Reset() {
	*this = normal_game(GetWidth(), GetHeight());
}

void normal_game::Pause() {
	running = false;
}

void normal_game::Resume() {
	running = true;
}

bool isRunning() {
	return running;
}

bool Drop() {
	if (now.Drop(brd)) {
		now = next;
		next = block(point(0, 0), GetRandomBlockShape());
		now.start_point = point((width - now.width) shr 1), 0);
		return true;
	}
	return false;
}

void Rotate() {
	now.RotateClockwise();
}

void MoveLeft() {
	now.MoveLeft();
}

void MoveRight() {
	now.MoveRight();
}