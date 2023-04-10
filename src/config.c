
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __unix__
#include <stddef.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

#include <include/parser.h>
#include <include/util.h>
#include <include/config.h>
#include <include/colors.h>
#include <include/global.h>

void
config_parse(settings_t **conf)
{
	settings_t *user_settings = malloc(sizeof(settings_t));

	config_t *config = NULL;
	parser(&config, config_file_path);

	int proxy_idx = 0;
	user_settings->proxy_count = config->n_tables - 1;
	user_settings->proxy = malloc(sizeof(proxy_t) * user_settings->proxy_count);
	user_settings->extras_count = 0;
	user_settings->extras = NULL;

	for(int i = 0; i< config->n_tables; i++)
	{
		table_t *table = config->tables[i];

		if(!strcmp(table->header, "proxy")) {
			/* Main Table */

			table->header = str_n_dup("proxy", MAX_SIZE);

			for(int j = 0; j < table->n_rows; j++)
			{
				/* Row */
				row_t *row = table->rows[j];

				if(!strcmp(row->key, "college")) {
					user_settings->college = str_n_dup(row->value, MAX_SIZE);
				} else if(!strcmp(row->key, "desktop")) {
					user_settings->desktop = str_n_dup(row->value, MAX_SIZE);
				} else if(!strcmp(row->key, "os")) {
					user_settings->os = str_n_dup(row->value, MAX_SIZE);
				} else if(!strcmp(row->key, "shell")) {
					user_settings->shell = str_n_dup(row->value, MAX_SIZE);
				} else if(!strcmp(row->key, "extra")) {

					char str[MAX_SIZE] = {0};
					int str_idx = 0;
					int idx = 0;

					while(row->value[idx]) {

						if(row->value[idx] == ',') {
							user_settings->extras_count++;
							user_settings->extras = realloc(user_settings->extras, user_settings->extras_count * sizeof(char*));
							user_settings->extras[user_settings->extras_count - 1] = str_n_dup(str, MAX_SIZE);
							str_rst(str);
							str_idx = 0;

							while(row->value[++idx] == ' ');
							idx--; // For next iteration of while loop
						} else {
							str[str_idx++] = row->value[idx];
						}

						idx++;
					}

					if(strlen(str)) {
						user_settings->extras_count++;
						user_settings->extras = realloc(user_settings->extras, user_settings->extras_count * sizeof(char*));
						user_settings->extras[user_settings->extras_count - 1] = str_n_dup(str, MAX_SIZE);
					}

				}

			}

		} else {
			/* Proxy Tables */

			for(int j = 0; j < table->n_rows; j++) {

				row_t *row = table->rows[j];

				user_settings->proxy[proxy_idx].name = str_n_dup(table->header, MAX_SIZE);

				if(!strcmp(row->key, "host")) {
					user_settings->proxy[proxy_idx].host = str_n_dup(row->value, MAX_SIZE);
				} else if(!strcmp(row->key, "port")) {
					user_settings->proxy[proxy_idx].port = str_n_dup(row->value, MAX_SIZE);
				}
			}

			proxy_idx++;
		}
	}

	*conf = user_settings;

	free_config(&config);
}