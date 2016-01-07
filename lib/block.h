#ifndef BLOCK_INCLUDED
#define BLOCK_INCLUDED

#include <utility> //for std::move
#include "board.h"
#include "util.h"

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

    static block_shape GetRandomBlockShape();

    static const int PRESET_N;
    static const int PRESET_SHAPE[];
    static const int PRESET_WIDTH[];
    static const int PRESET_HEIGHT[];
    static block_shape &&preset(int i){
        return std::move(block_shape(PRESET_WIDTH[i], PRESET_HEIGHT[i], PRESET_SHAPE[i]));
    }
};

class block {
public:
    util::point start_point;
    block_shape shape;
    block();
    block(util::point s, block_shape bs);
    void Drop();
    void RotateClockwise();
    void RotateCounterClockwise();
    void MoveLeft();
    void MoveRight();
    void DropToBottom(board b);
    bool isHitBoard(board b);
};

#endif
