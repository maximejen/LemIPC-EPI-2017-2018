/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** player.c
*/

#include <stdio.h>
#include <sys/sem.h>
#include <zconf.h>
#include <sys/shm.h>
#include "../../include/lemipc.h"

static const char *ERROR_MSG = "Error : can't find a positon for the player";

/*
** Description:
** This function init the content of the player struct.
*/
int init_player(lemipc_t *lem, player_t *player)
{
	char *str;

	player->mem = lem->mem;
	player->shm_id = lem->shm_id;
	player->sem_id = lem->sem_id;
	player->msg_id = lem->msg_id;
	player->team_id = lem->args->team_id;
	if (determine_starting_position(player))
		return (dprintf(2, "%s", ERROR_MSG) * 0 + 1);
	player->mem->map[player->posy][player->posx] = player->team_id;
	asprintf(&str, "1;%d;1", player->team_id);
	send_message(player->msg_id, LOG_CHANNEL, str);
	send_message(player->msg_id, player->team_id + 1, str);
	free(str);
	return (0);
}

/*
** Description:
** This function check if the player should die or not
** A player die if two members of the same team are in the 8 cells around him
*/
int should_player_die(player_t *player)
{
	int range[8];
	int team_id = player->team_id;

	get_nearby_cells(range, player);
	for (int i = 0 ; i < 8 * 8 ; i++) {
		if (i / 8 == i % 8 ||
		range[i / 8] <= 0 || range[i % 8] <= 0 ||
		range[i / 8] == team_id || range[i % 8] == team_id)
			continue;
		if (range[i / 8] == range[i % 8])
			return (1);
	}
	return (0);
}

void move_random(player_t *player)
{
	int direction = rand_nbr(4);

	operate_on_sem(player->sem_id, -1);
	switch (direction) {
	case 0:
		move_right(player);
		break;
	case 1:
		move_left(player);
		break;
	case 2:
		move_bot(player);
		break;
	default:
		move_top(player);
		break;
	}
	operate_on_sem(player->sem_id, 1);
}

int start_player(lemipc_t *lem)
{
	player_t player;
	char *str = NULL;

	if (init_player(lem, &player))
		return (1);
	while (!should_player_die(&player) && CONTINUE &&
		shmget(lem->key, sizeof(sh_mem_t), SHM_R) != -1) {
		if (get_commander_orders(&player, lem))
			follow_the_order(&player);
		else
			move_random(&player);
		usleep(70000);
	}
	player.mem->map[player.posy][player.posx] = 0;
	asprintf(&str, "1;%d;2", player.team_id);
	send_message(player.msg_id, LOG_CHANNEL, str);
	send_message(player.msg_id, player.team_id + 1, str);
	free(str);
	return (0);
}