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
#include <signal.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <zconf.h>
#include "../include/lemipc.h"

int CONTINUE = 1;

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
		} else {
			ret = pthread_create(&lem->graph_thread, NULL,
					     &textual_render, lem);
		}
		if (ret != 0)
			perror("pthread_create");
		ret = pthread_create(&lem->time, NULL, &time_handle, lem);
		if (ret != 0)
			perror("pthread_create");
	}
	if (lem->is_commander)
		create_commander(lem);
	return (ret);
}

/*
** Description:
** This function join the threads created before the game.
*/
static int join_threads(lemipc_t *lem)
{
	void *status;

	if (lem->is_first) {
		if (lem->graph_thread &&
		    pthread_join(lem->graph_thread, &status))
			perror("pthread_join");
		printf("Graphical thread joined, the game is finished\n");
	}
	if (lem->is_commander) {
		if (lem->cmd && pthread_join(lem->cmd, &status))
			perror("pthread_join");
		printf("The Commander is dead, long live the Commander\n");
	}
	return (0);
}

/*
** Description:
** initialize of the IPCs or just link to them.
*/
static int lemipc_init(args_t *args, lemipc_t *lem)
{
	lem->is_first = 0;
	lem->is_commander = 0;
	lem->key = ftok(args->path, 0);
	lem->args = args;
	if (args->team_name == NULL)
		asprintf(&args->team_name, "%d", args->team_id);
	init_shared_memory(lem);
	init_semaphores(lem);
	init_message_queue(lem);
	return (0);
}

/*
** Description:
** if a sigint is catched, this function is called.
*/
static void sig_int_handle(int sig)
{
	(void) sig;
	CONTINUE = 0;
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
	signal(SIGINT, sig_int_handle);
	create_threads(&lem);
	start_player(&lem);
	join_threads(&lem);
	if (lem.is_first) {
		print_winner(&lem);
		shmctl(lem.shm_id, IPC_RMID, NULL);
		semctl(lem.sem_id, 0, IPC_RMID);
		semctl(lem.sem_id, 1, IPC_RMID);
		msgctl(lem.msg_id, IPC_RMID, NULL);
	}
	return (0);
}

