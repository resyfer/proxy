#ifndef __ARGS_H
#define __ARGS_H

void
parse_args(int argc, char *argv[]);

typedef struct args {
	int update;
	int remove;
	int help;
	int version;
} args_t;

static args_t arglist;

#endif