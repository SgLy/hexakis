#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <vector>
#include <list>

class board {
public:
    typedef std::vector<bool> row;
    typedef std::list<row> table;

    int height, width;
    table map;
    board();
    board(int w, int h);
};

#endif
