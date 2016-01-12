#ifndef NORMAL_GAME_DEFINED
#define NORMAL_GAME_DEFINED

#include "block.h"
#include "board.h"

class normal_game {
	bool running;
public:
	block now, next;
	board brd;
	normal_game(int w, int h);
	int GetHeight();
	int GetWidth();
	void Reset();
	void Start();
	void Pause();
	void Resume();
	bool isRunning();
	bool Drop(); // return true if hit and new block generated
	void Rotate();
	void MoveLeft();
	void MoveRight();
	int EraseRows();
	void DropToBottom();
};


#endif
