#include <stdio.h>
#include <stdlib.h>

#ifdef __unix__
#include <unistd.h>
#elif _WIN32
#include <io.h>
#endif

#include <string.h>

#include <include/args.h>
#include <include/config.h>
#include <include/global.h>
#include <include/colors.h>

char* home;
char* config_dir;
char* config_file_path;
char* script_path_set;
char* script_path_unset;
char* source_path;

void
global_vars(void)
{
	char buf[MAX_SIZE] = {0};

	// TODO: Cross-platform
	sprintf(buf, "%s", getenv("HOME"));
	home = str_n_dup(buf, MAX_SIZE);

	str_rst(buf);
	sprintf(buf, "%s/.config/proxy", home);
	config_dir = str_n_dup(buf, MAX_SIZE);

	str_rst(buf);
	sprintf(buf, "%s/config", config_dir);
	config_file_path = str_n_dup(buf, MAX_SIZE);

	str_rst(buf);
	sprintf(buf, "%s/set.sh", config_dir);
	script_path_set = str_n_dup(buf, MAX_SIZE);

	str_rst(buf);
	sprintf(buf, "%s/unset.sh", config_dir);
	script_path_unset = str_n_dup(buf, MAX_SIZE);

	str_rst(buf);
	sprintf(buf, "%s/proxy.sh", config_dir);
	source_path = str_n_dup(buf, MAX_SIZE);
}

int
main(int argc, char *argv[])
{
	#ifdef __unix__

		// Check if colors are supported
		SUPPORT_COLORS = isatty(STDOUT_FILENO);

		// Handle the arguments
		if(getuid() == 0) {
			pcol("Please remove sudo\n", RED);
			return 1;
		}

	#endif

	global_vars();

	// Unsupported OS
	#if defined(__unix__) || defined(_WIN32) || defined(__APPLE__)
	#else
		printf("Not a supported platform\n");
		return 0;
	#endif

	// Open Config
	FILE* config = fopen(config_file_path, "r");

	if(config == NULL) {
		pcol("Config File Not Found\n", RED);
		pcol("Please follow the installation instructions properly!", PURPLE);
		return 1;
	}

	parse_args(argc, argv);

	fclose(config);

	return 0;
}