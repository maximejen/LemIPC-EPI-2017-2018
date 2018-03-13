/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** lemipc.c
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include "include/lemipc.h"

/*
** Description:
** This function should create the map and then init the shared memory.
** It also needs to init the semaphore to be sure all the players do not play
** at the same time.
** if everything exists already, it only fill the lemipc struct.
*/
void lemipc_init(args_t *args)
{
	key_t key = ftok(args->path, 0);

	if (args->team_name == NULL)
		asprintf(&args->team_name, "%d", args->team_id);
	printf("path given    : %s\n", args->path);
	printf("key is        : %i\n", key);
	printf("team_id given : %d\n", args->team_id);
	printf("team_name     : %s\n", args->team_name);
	printf("is graph      : %d\n", args->is_graphical);
	printf("graph lib     : %s\n", args->graphical_lib_path);
}

