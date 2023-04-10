#include <include/loader.h>
#include <include/colors.h>

#ifdef __unix__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

static char states[] = {'\\', '-', '/', '|'};

void
load(loader_t *loader, color_t color)
{
	(*loader)++;
	*loader%=4;

	char text[5] = {0};
	sprintf(text, "[%c]\r", states[*loader]);
	pcol(text, color);
	fflush(stdout);

	#ifdef __unix__

		usleep(25000);

	#elif _WIN32

		Sleep(25);

	#endif
}