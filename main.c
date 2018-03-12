/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** main.c
*/

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "include/lemipc.h"

static const char FLAGS[3][7] = {
"-tn",
"--help",
"-h"
};

static const char *HELP_MESSAGE =
"USAGE\n"
"\t./lemipc PATH TEAM_NUMBER\n\n"
"DESCRIPTION\n"
"\tPATH\t\tnumber of philosophers\n"
"\tTEAM_NUMBER\tteam number of the current champion (greater than 0)";

static int parse_args(int argc, char **argv, args_t *args)
{
	struct stat buf;

	for (int i = 1 ; i < argc ; i++) {
		if (argv[i][0] >= '0' && argv[i][0] <= '9')
			args->team_id = atoi(argv[i]);
		else if (stat(argv[i], &buf) != -1) {
			args->path = strdup(argv[i]);
		}
		if (strcmp(argv[i], FLAGS[0]) == 0 && (i + 1) < argc) {
			i++;
			args->team_name = strdup(argv[i]);
		}
	}
	return (0);
}

int main(int argc, char **argv)
{
	args_t args = {NULL, -1, NULL};
	int ret = 84;

	if (argc >= 3) {
		ret = parse_args(argc, argv, &args);
		printf("path given      : %s\n", args.path);
		printf("team_id given   : %d\n", args.team_id);
		printf("team_name given : %s\n", args.team_name);
		return (ret);
	}
	if (argc >= 2 && (strcmp(argv[1], FLAGS[1]) == 0 ||
			  strcmp(argv[1], FLAGS[2]) == 0)) {
		printf("%s\n", HELP_MESSAGE);
		return (0);
	}
	return (ret);

}

