#ifndef BLOCK_INCLUDED
#define BLOCK_INCLUDED

#include "board.h"
#include "util.h"

#define PRESET_N 7
#define PRESET(i) block_shape(PRESET_WIDTH[i], PRESET_HEIGHT[i], PRESET_SHAPE[i])

const int PRESET_SHAPE[PRESET_N] = {114, 15, 51, 547, 275, 99, 54};
const int PRESET_WIDTH[PRESET_N] = {3, 4, 2, 2, 2, 3, 3};
const int PRESET_HEIGHT[PRESET_N] = {2, 1, 2, 3, 3, 2, 2};

class block_shape {
public:
    int width, height;
    bool b[4][4];
    block_shape();
    block_shape(int w, int h, int s);
    int toInt();
    void Clear();
    void RotateClockwise();
    void RotateCounterClockwise();
};

block_shape GetRandomBlockShape();

class block {
public:
    point start_point;
    block_shape shape;
    block();
    block(point s, block_shape bs);
    void Drop();
    void RotateClockwise();
    void RotateCounterClockwise();
    void MoveLeft();
    void MoveRight();
    void DropToBottom(board b);
    bool isHitBoard(board b);
};

#endif