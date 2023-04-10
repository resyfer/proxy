#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <include/update.h>
#include <include/global.h>

void
update(void)
{
	// Open the config file in Terminal Text Editor
	#ifdef __unix__

		char* editor = getenv("EDITOR") ? str_n_dup(getenv("EDITOR"), MAX_SIZE) : "/usr/bin/vi";
		char *command = malloc((strlen(editor) + 1 + strlen(config_file_path) + 1) * sizeof(char));
		sprintf(command, "%s %s", editor, config_file_path);

	#elif _WIN32

		char* command = malloc((54 + strlen(config_file_path) + 1) * sizeof(char));
		sprintf(command, "Start-Process -FilePath \"notepad.exe\" -ArgumentList \"\"", config_file_path);

	#endif

	system(command);

	#ifdef __unix__

		free(editor);

	#endif

	free(command);
}