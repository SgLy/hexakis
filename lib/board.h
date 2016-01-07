#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <vector>
#include <list>

typedef std::vector<bool> row;
typedef std::list<row> table;

class board {
public:
    int height, width;
    table map;
    board();
    board(int w, int h);
};

#endif