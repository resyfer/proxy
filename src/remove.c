#include <include/remove.h>
#include <include/colors.h>
#include <include/loader.h>
#include <include/global.h>
#include <stdlib.h>
#include <string.h>

int
choice(void)
{
	char in[2] = {0};
	fgets(in, 2, stdin);
	in[1] = 0;

	if(!strcmp(in, "y") || !strcmp(in, "Y")) {
		return 1;
	} else {
		return 0;
	}
}

void
uninstall(void)
{
	pcol("We're sorry to see you go!\n\n", PURPLE);

	pcol("We would be delighted to hear about any bugs/issues or features at\n", GREEN);
	pcol("https://github.com/resyfer/proxy\n\n", GREEN);

	pcol("Are you sure you want to continue? [y/N] > ", PURPLE);

	loader_t loader = -1;

	if(!choice()) {
		return;
	}

	load(&loader, RED);

	pcol("Uninstalling\n", YELLOW);

	load(&loader, RED);

	char command[MAX_SIZE] = {0};

	#ifdef __unix__
	sprintf(command, "sudo rm -rf %s", config_dir);
	#elif _WIN32
	sprintf(command, "Remove-Item -Path \"%s\" -Force", config_dir);
	printf("%s", command);
	#endif

	load(&loader, RED);

	system(command);

	load(&loader, RED);

	#ifdef __unix__
	system("sudo rm /usr/bin/proxy");

	load(&loader, RED);

	system("sed -i \"/source \\/home\\/" USER "\\/.config\\/proxy\\/proxy.sh/d\" /home/" USER "/" SHELL_CONFIG_FILE);
	load(&loader, RED);
	#endif


	pcol("Done!\n", RED);
}