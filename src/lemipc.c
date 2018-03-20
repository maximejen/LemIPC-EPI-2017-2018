/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** lemipc.c
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <pthread.h>
#include "../include/lemipc.h"

/*
** Description:
** This function creates the threads (Graphical or Textual) or the Commander
*/
static int create_threads(lemipc_t *lem)
{
	int ret = 0;

	if (lem->is_first) {
		if (lem->args->is_graphical) {
			ret = pthread_create(&lem->graph_thread, NULL,
					     &graphical_render, lem);
		}
		else {
			ret = pthread_create(&lem->graph_thread, NULL,
					     &textual_render, lem);
		}
		if (ret != 0)
			perror("pthread_create");
	}
	// Todo : HERE CREATE THE COMMANDER IF NEEDED.
	return (ret);
}

/*
** Description:
** This function join the threads created before the game.
*/
static int join_threads(lemipc_t *lem)
{
	void *status;

	if (lem->graph_thread && pthread_join(lem->graph_thread, &status))
		perror("pthread_join");
	printf("Graphical thread joined, the game is finished\n");
	// Todo : HERE JOIN THE COMMANDER IF NEEDED
	return (0);
}

static int lemipc_init(args_t *args, lemipc_t *lem)
{
	lem->key = ftok(args->path, 0);
	lem->args = args;
	if (args->team_name == NULL)
		asprintf(&args->team_name, "%d", args->team_id);
	init_shared_memory(lem);
	init_semaphores(lem);
	init_message_queue(lem);
	// Todo : HERE DETERMINE IF YOU NEED TO CREATE A COMMANDER.
	return (0);
}

/*
** Description:
** This function should create the map and then init the shared memory.
** It also needs to init the semaphore to be sure all the players do not play
** at the same time.
** if everything exists already, it only fill the lemipc struct.
*/
int lemipc_start(args_t *args)
{
	lemipc_t lem;

	if (lemipc_init(args, &lem) != 0)
		return (1);
	create_threads(&lem);
	join_threads(&lem);
	return (0);
}

