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
	#elif _WIN32
	// Dunno the condition in Windows Terminals. VSCode Inbuilt terminal supports it.
	// while powershell's terminal or CMD
	// return "";
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
	case BLACK | RED | GREEN | YELLOW | BLUE | PURPLE | CYAN | WHITE:
		return COLOR_CODE(color, NORMAL);
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