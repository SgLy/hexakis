#include "block.h"
#include "board.h"

// Class Blcok_Shape
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

block_shape GetRandomBlockShape() {
    int t = random(7);
    // PRESET is a macro and declaring t is necessary
    block_shape bs = PRESET(t);
    int r = random(4);
    while (r--)
        bs.RotateClockwise();
    return bs;
}
// Class Block_Shape Done


//Class Block
void block::Drop() {
    start_point += point(1, 0);
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
    // under construction
    /*
    for (std::list<row>::iterator i = b.map.begin(); i != b.map.end(); ++i) {

    }*/
}

void block::DropToBottom(board b) {
    while (!isHitBoard(b)) Drop();
}