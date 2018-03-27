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
#include "../include/lemipc.h"

static const char FLAGS[5][12] = {
	"-tn",
	"--help",
	"-h",
	"-g",
	"--graphical"
};

static const char *ERROR_MESSAGE = "Error : The team_id should be greater"
	" than 0 and you should also precise a path.";

static const char *HELP_MESSAGE =
	"USAGE\n"
		"\t./lemipc PATH TEAM_NUMBER\n\n"
		"DESCRIPTION\n"
		"\tPATH\t\tnumber of philosophers\n"
		"\tTEAM_NUMBER\tteam number of the current champion"
		"(greater than 0)";

static void fill_string(char **str, const char *to_copy)
{
	free(*str);
	*str = strdup(to_copy);
}

/*
** Description:
**  This function parse the arguments sent by the user when exec the program
**  then it stores the datas in a struct args_t.
*/
static int parse_args(int argc, char **argv, args_t *args)
{
	struct stat buf;

	for (int i = 1 ; i < argc ; i++) {
		if (argv[i][0] >= '0' && argv[i][0] <= '9')
			args->team_id = atoi(argv[i]);
		if (stat(argv[i], &buf) != -1)
			fill_string(&args->path, argv[i]);
		if (strcmp(argv[i], FLAGS[0]) == 0 && (i + 1) < argc) {
			i++;
			fill_string(&args->team_name, argv[i]);
		} else if ((strcmp(argv[i], FLAGS[3]) == 0 ||
			    strcmp(argv[i], FLAGS[4]) == 0))
			args->is_graphical = 1;
	}
	if (args->team_id <= 0 || args->path == NULL)
		return (fprintf(stderr, "%s\n", ERROR_MESSAGE) * 0 + 84);
	return (0);
}

/*
** Description:
** This function free the args and also destroy the IPCs if necessary.
*/
static void finish_program(args_t *args)
{
	free(args->path);
	free(args->team_name);
}

int main(int argc, char **argv)
{
	args_t args = {NULL, -1, NULL, 0};
	int ret = 84;

	if (argc >= 3) {
		ret = parse_args(argc, argv, &args);
		if (ret != 84)
			lemipc_start(&args);
		finish_program(&args);
		return (ret);
	}
	if (argc >= 2 && (strcmp(argv[1], FLAGS[1]) == 0 ||
			  strcmp(argv[1], FLAGS[2]) == 0)) {
		printf("%s\n", HELP_MESSAGE);
		return (0);
	}
	return (ret);
}

