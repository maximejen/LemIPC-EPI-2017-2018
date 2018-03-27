/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** commander.c
*/

#include <stdio.h>
#include <memory.h>
#include <zconf.h>
#include "../../include/lemipc.h"

static int count_players(commander_t *cmd)
{
	int count = 0;
	size_t h = cmd->mem->height;
	size_t w = cmd->mem->width;

	for (size_t i = 0 ; i < h * w ; i++) {
		if (cmd->mem->map[i / h][i % w] == cmd->team_id)
			count++;
	}
	return (count);
}

/*
** Description:
** This function init the content of the commander struct.
*/
static int init_commander(lemipc_t *lem, commander_t *commander)
{
	char *str = NULL;

	commander->mem = lem->mem;
	commander->shm_id = lem->shm_id;
	commander->sem_id = lem->sem_id;
	commander->msg_id = lem->msg_id;
	commander->tx = rand_nbr(lem->mem->width);
	commander->ty = rand_nbr(lem->mem->height);
	commander->team_id = lem->args->team_id;
	commander->p_count = count_players(commander);
	commander->game_started = 0;
	asprintf(&str, "2;%d;1", commander->team_id);
	send_message(commander->msg_id, LOG_CHANNEL, str);
	free(str);
	return (0);
}

static int commander_actions(commander_t *c)
{
	char *order;

	update_connections(c);
	if (find_target(c)) {
		c->game_started = 1;
		asprintf(&order, "2;%d;3;%d;%d", c->team_id, c->tx, c->ty);
		for (int i = 0 ; i < c->p_count ; i++) {
			send_message(c->msg_id, c->team_id + 1, order);
		}
		send_message(c->msg_id, LOG_CHANNEL, order);
		free(order);
	}
	else if (c->game_started && !count_players(c))
		return (0);
	else {
		c->tx = rand_nbr(c->mem->width);
		c->ty = rand_nbr(c->mem->height);
	}
	return (1);
}

static void *start_commander(void *arg)
{
	lemipc_t *lem = arg;
	commander_t cmd;
	char *str;
	int still_continue = 1;

	init_commander(lem, &cmd);
	while (CONTINUE && still_continue) {
		if (!commander_actions(&cmd))
			still_continue = 0;
		usleep(100000);
	}
	asprintf(&str, "2;%d;2", cmd.team_id);
	send_message(cmd.msg_id, cmd.team_id + 1, str);
	send_message(cmd.msg_id, LOG_CHANNEL, str);
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