#include <stdlib.h>
#include <string.h>

#include <include/colors.h>
#include <include/global.h>
#include <include/loader.h>
#include <include/remove.h>

int
choice(void)
{
	char in[2] = {0};

	if(!fgets(in, 2, stdin)) {
		pcol("Error Getting Choice\n", RED);
		exit(1);
	}

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
	#ifdef __unix__
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

	sprintf(command, "sudo rm -rf %s", config_dir);

	load(&loader, RED);

	if(system(command)) {
		// TODO
	}

	load(&loader, RED);

	if(system("sudo rm /usr/bin/proxy")) {

	}

	load(&loader, RED);

	if(system("sed -i \"/source \\/home\\/" USER "\\/.config\\/proxy\\/proxy.sh/d\" /home/" USER "/" SHELL_CONFIG_FILE)) {
		// TODO
	}

	load(&loader, RED);

	pcol("Done!\n", RED);

	#elif _WIN32

		// TODO
		// There is an error (atleast when I try), where the config file refuses to be removed as
		// it is "used by another process".
		char buf[MAX_SIZE] = {0};
		sprintf(buf, "Please remove this folder \"%s\" to complete uninstall this utility!\n\nPlease also remove the path of this folder from PATH variables as well!", config_dir);

		pcol(buf, PURPLE);

	#endif

}