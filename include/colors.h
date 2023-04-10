#include <stdio.h>

#include "util.h"

#ifndef __COLORS_H
#define __COLORS_H

#define ESC	"\e"

#define NORMAL			0
#define BOLD			1
#define ITALIC			3
#define UNDERLINE		4
#define STRIKETHROUGH	9

#define BLACK   30
#define RED     31
#define GREEN   32
#define YELLOW  33
#define BLUE    34
#define PURPLE  35
#define CYAN    36
#define WHITE   37

#define COLOR_CODE(COLOR, STYLE) (ESC "[" STR(STYLE) ";" STR(COLOR) "m")

#define RESET ESC "[0m"

typedef unsigned short int color_t;

const char*
colorify(color_t color);

void
print_col(char **dest, const char *text, color_t color);

void
pcol(const char* text, color_t color);

#endif