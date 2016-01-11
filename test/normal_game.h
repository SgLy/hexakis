#ifndef NORMAL_GAME_DEFINED
#define NORMAL_GAME_DEFINED

class normal_game {
	block now, next;
	board brd;
	bool running;
	normal_game(int w, int h);
	int GetHeight();
	int GetWidth();
	block GetCurrentBlock();
	block GetNextBlock();
	board GetBoard();
	void Reset();
	void Pause();
	void Resume();
	bool isRunning();
	bool Drop(); // return true if hit and new block generated
	void Rotate();
	void MoveLeft();
	void MoveRight();
};


#endif