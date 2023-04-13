#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

#include <include/config.h>
#include <include/global.h>
#include <include/colors.h>
#include <include/loader.h>

static void print_options(settings_t *conf);
static int get_choice(settings_t *conf, const char* def);
static void set_source_file(proxy_t *proxy);
static void unset_source_file(void);
static void set_proxy(settings_t *conf, proxy_t *proxy);
static void unset_proxy(settings_t *conf);
static void free_user_conf(settings_t **conf);

static void
print_options(settings_t *conf)
{
	pcol("Choose a proxy:\n", GREEN);

	for(int i = 0; i<=conf->proxy_count; i++) {
		if(i == 0) {
			printf("[%s%d%s] ", COLOR_CODE(GREEN, BOLD),i,RESET);
			pcol("Remove Proxy (For Personal Network)\n", CYAN);
		} else {
			printf("[%s%d%s] ", COLOR_CODE(GREEN, BOLD),i,RESET);
			pcol(conf->proxy[i-1].name, BLUE);
			printf(" (");
			pcol(conf->proxy[i-1].host, BLUE);
			printf(":");
			pcol(conf->proxy[i-1].port, BLUE);
			printf(")\n");
		}
	}

	printf("\n");
	printf("%sChoose (%sdefault: 1%s) > %s",
		COLOR_CODE(PURPLE, NORMAL),
		COLOR_CODE(PURPLE, ITALIC),
		COLOR_CODE(PURPLE, NORMAL),
		RESET);
}

static int
get_choice(settings_t *conf, const char* def)
{
	char input[9]; // max 8-digit input
	fgets(input, 9, stdin);
	input[8] = 0;

	if(!strcmp(input, "\n")) {
		strcpy(input, def);
	}

	char* endptr;
	int choice = strtol(input, &endptr, 10);

	if(endptr == input) {
		pcol("No digits were found!", RED);
		exit(1);
	}
	if(choice < 0 || choice > conf->proxy_count) {
		pcol("Incorrect Choice", RED);
		exit(1);
	}

	return choice;
}

static void
set_source_file(proxy_t *proxy)
{
	#ifdef __unix__
	
	FILE *sh = fopen(source_path, "w+");
	fprintf(sh, "#!/bin/bash\n");
	fprintf(sh, "alias sudo='sudo -E'\n");
	fprintf(sh, "export http_proxy=\"http://%s:%s\"\n", proxy->host, proxy->port);
	fprintf(sh, "export https_proxy=\"http://%s:%s\"\n", proxy->host, proxy->port);
	fclose(sh);

	#endif
}

static void
unset_source_file(void)
{
	#ifdef __unix__

	FILE *sh = fopen(source_path, "w+");
	fprintf(sh, "#!/bin/bash\n");
	fclose(sh);

	#endif
}

static void
set_proxy(settings_t *conf, proxy_t *proxy)
{
	loader_t loader = -1;

	pcol("Updating proxy\n", YELLOW);

	load(&loader, YELLOW);

	#ifdef __unix__
	set_source_file(proxy);
	#endif

	load(&loader, YELLOW);

	char extras_arr[MAX_SIZE] = {0};
	char *temp = extras_arr;
	for(int i = 0; i<conf->extras_count; i++) {
		load(&loader, YELLOW);

		if(i == 0) {
			temp += sprintf(temp, "%s", conf->extras[i]);
		} else {
			temp += sprintf(temp, ",%s", conf->extras[i]);
		}
	}

	load(&loader, YELLOW);

	char command[2048] = {0};

	#ifdef __unix__
	sprintf(command, "%s %s %s %s %s", /* Can't use source because Ubuntu has dash not bash */
		script_path_set, extras_arr, proxy->host, proxy->port, conf->desktop);
	#elif _WIN32
	sprintf(command, "PowerShell -File %s %s %s %s",
		script_path_set, extras_arr, proxy->host, proxy->port);
	#endif

	load(&loader, YELLOW);

	if(system(command) != 0) {
		pcol("Error Setting Up Proxy!\n", RED);
		exit(1);
	}

	load(&loader, YELLOW);
	pcol("Done!\n", YELLOW);
}

static void
unset_proxy(settings_t *conf)
{
	loader_t loader = -1;

	pcol("Updating proxy\n", YELLOW);

	load(&loader, YELLOW);

	#ifdef __unix__

	unset_source_file();

	#endif

	load(&loader, YELLOW);

	char command[4096] = {0};

	load(&loader, YELLOW);

	char extras_arr[MAX_SIZE] = {0};
	char *temp = extras_arr;
	for(int i = 0; i<conf->extras_count; i++) {
		load(&loader, YELLOW);

		if(i == 0) {
			temp += sprintf(temp, "%s", conf->extras[i]);
		} else {
			temp += sprintf(temp, ",%s", conf->extras[i]);
		}
	}

	#ifdef __unix__

	sprintf(command, "%s %s %s", /* Can't use source because Ubuntu has dash not bash */
			script_path_unset, extras_arr, conf->desktop);

	#elif _WIN32

	sprintf(command, "PowerShell -File %s %s",
			script_path_unset, extras_arr);

	#endif

	load(&loader, YELLOW);

	if(system(command) != 0) {
		pcol("Error Setting Up Proxy!\n", RED);
		exit(1);
	}

	load(&loader, YELLOW);

	pcol("Done!\n", YELLOW);
}

static void
free_user_conf(settings_t **conf)
{
	free((*conf)->desktop);
	free((*conf)->shell);

	for(int i = 0; i < (*conf)->extras_count; i++)
		free((*conf)->extras[i]);

	for(int i = 0; i < (*conf)->proxy_count; i++) {
		free((*conf)->proxy[i].host);
		free((*conf)->proxy[i].port);
		free((*conf)->proxy[i].name);
	}

	*conf = NULL;
}

void
change(void)
{
	settings_t *conf;

	config_parse(&conf);

	print_options(conf);

	int choice = get_choice(conf, "1");

	if(choice == 0)
		unset_proxy(conf);
	else
		set_proxy(conf, &conf->proxy[choice-1]);

	free_user_conf(&conf);
}