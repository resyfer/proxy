#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <include/global.h>

char*
str_n_dup(const char* s, size_t max)
{
	size_t s_len = strnlen(s, MAX_SIZE - 1);
	char* s_dup = calloc(s_len + 1, sizeof(char));
	memcpy(s_dup, s, s_len);
	return s_dup;
}

void
str_rst(char* str)
{
	int i = 0;
	while(str[i]) str[i++] = 0;
}
