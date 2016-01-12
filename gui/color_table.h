#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

#include <cstddef>

struct tile_color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

extern tile_color tile_color_table[];
extern std::size_t tile_color_table_size;

#endif // COLOR_TABLE_H
