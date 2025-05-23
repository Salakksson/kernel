#pragma once

#include "pch.h"

#define int int // Prevent some warnings

#define VGA_ROWS 25
#define VGA_COLS 80

enum
{
    BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GRAY = 7,
	DARK_GRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	PINK = 13,
	YELLOW = 14,
	WHITE = 15,
};

void tty_clear();
void tty_colour(uint8_t bg, uint8_t fg);

void puts(char* str);

void set_cursor_position(size_t r, size_t c);
void get_cursor_position(size_t*r, size_t*c);
