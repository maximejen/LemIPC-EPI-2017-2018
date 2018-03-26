/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** commander.c
*/

#include <stdio.h>
#include <memory.h>
#include "../../include/lemipc.h"

/*
** Description:
** This function init the content of the commander struct.
*/
static int init_commander(lemipc_t *lem, commander_t *commander)
{
	char *str;

	commander->mem = lem->mem;
	commander->shm_id = lem->shm_id;
	commander->sem_id = lem->sem_id;
	commander->msg_id = lem->msg_id;
	commander->target_x = rand_nbr(lem->mem->width);
	commander->target_y = rand_nbr(lem->mem->height);
	commander->team_id = lem->args->team_id;
	asprintf(&str, "2;%d;1", commander->team_id);
	send_message(commander->msg_id, LOG_CHANNEL, str);
	send_message(commander->msg_id, commander->team_id + 1, str);
	free(str);
	return (0);
}

static void *start_commander(void *arg)
{
	lemipc_t *lem = arg;
	commander_t cmd;
	char *str;

	init_commander(lem, &cmd);
	find_target(&cmd);
	while (CONTINUE) {

	}
	asprintf(&str, "2;%d;2", cmd.team_id);
	send_message(cmd.msg_id, LOG_CHANNEL, str);
	send_message(cmd.msg_id, cmd.team_id + 1, str);
	free(str);
	return ("OK");
}

int create_commander(lemipc_t *lem)
{
	int ret = 0;

	printf("A Commander has been created\n");
	ret = pthread_create(&lem->cmd, NULL, &start_commander, lem);
	if (ret != 0)
		perror("pthread_create");
	return (ret);
}