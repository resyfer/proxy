#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>

#include <include/args.h>
#include <include/colors.h>
#include <include/change.h>
#include <include/update.h>
#include <include/remove.h>
#include <include/global.h>

static void version(void);
static void help(void);

static void
version(void)
{
	pcol(NAME " " VERSION "\n", PURPLE);
}

static void
help(void)
{
	version();
	pcol("\n", WHITE);
	pcol("Usage: ", GREEN); pcol(NAME " ", PURPLE); pcol("[OPTION...]\n\n", YELLOW);
	pcol("A program to switch between various proxies in your college.\n\n", BLUE);
	pcol("Flags:\n", GREEN);
	pcol("    -r", YELLOW); pcol(" ...... ", PURPLE); pcol("Uninstall this utility\n", BLUE);
	pcol("    -u", YELLOW); pcol(" ...... ", PURPLE); pcol("Update the config\n", BLUE);
	pcol("    -h", YELLOW); pcol(" ...... ", PURPLE); pcol("Print this helpful message\n", BLUE);
	pcol("    -v", YELLOW); pcol(" ...... ", PURPLE); pcol("Print this version of this utility\n", BLUE);
	pcol("\n\n", WHITE);
	pcol("Example Usage:\n", GREEN);
	pcol("    $ ", PURPLE); pcol(NAME " -h\n", YELLOW);
	pcol("    $ ", PURPLE); pcol(NAME " -v\n", YELLOW);
	pcol("    $ ", PURPLE); pcol(NAME " -u\n", YELLOW);
	pcol("    $ ", PURPLE); pcol(NAME " -r\n", YELLOW);
	pcol("\n\n", WHITE);
	pcol("Please report any bugs or features at:\n", BLUE);
	pcol("https://github.com/resyfer/proxy\n", PURPLE);
}

void
parse_args(int argc, char* argv[])
{
	if(argc == 1) {
		change();
		return;
	}

	// Use getopt_long

	int c;
	while((c = getopt(argc, argv, "urhv")) != -1) {
		switch (c)
		{
		case 'u':
			arglist.update = 1;
			break;

		case 'r':
			arglist.remove = 1;
			break;

		case 'h':
			arglist.help = 1;
			break;

		case 'v':
			arglist.version = 1;
			break;

		default:
			arglist.help = 1;
			pcol("**Incorrect Flags**\n\n", RED);
			goto end;
		}
	}

end:
	if(arglist.help) {
		help();
	} else if (arglist.version) {
		version();
	} else if (arglist.remove) {
		uninstall();
	} else if (arglist.update) {
		update();
	}
}