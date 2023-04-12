#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <include/colors.h>
#include <include/global.h>

int SUPPORT_COLORS;

const char*
colorify(color_t color)
{
	#ifdef __unix__
	if(!SUPPORT_COLORS) {
		return "";
	}
	#endif

	if(color < BLACK || color > WHITE) {
		printf("Incorrected Colors\n");
		exit(1);
	}

	/*
	 * FUTURE: Wanted to give an option for bold,
	 * but too much redundant code.
	 */
	// if(text_style != NORMAL && text_style != BOLD) {
	// 	printf("Incorrect Text Style\n");
	// 	exit(1);
	// }

	switch(color) {
	case BLACK:
		return ESC "[" STR(NORMAL) ";" STR(BLACK) "m";
	case RED:
		return ESC "[" STR(NORMAL) ";" STR(RED) "m";
	case GREEN:
		return ESC "[" STR(NORMAL) ";" STR(GREEN) "m";
	case YELLOW:
		return ESC "[" STR(NORMAL) ";" STR(YELLOW) "m";
	case BLUE:
		return ESC "[" STR(NORMAL) ";" STR(BLUE) "m";
	case PURPLE:
		return ESC "[" STR(NORMAL) ";" STR(PURPLE) "m";
	case CYAN:
		return ESC "[" STR(NORMAL) ";" STR(CYAN) "m";
	case WHITE:
		return ESC "[" STR(NORMAL) ";" STR(WHITE) "m";
	default:
		return "";
	}
}

void
print_col(char **dest, const char *text, color_t color)
{
	const char* color_text = colorify(color);
	*dest = (char*) realloc(*dest,
				(strlen(color_text) + strlen(text) + strlen(RESET) + 1) * sizeof(char));
	snprintf(*dest, MAX_SIZE, "%s%s%s", colorify(color), text, RESET);
}

void
pcol(const char* text, color_t color)
{
	char* col_text = NULL;
	print_col(&col_text, text, color);

	printf("%s", col_text);

	free(col_text);
}