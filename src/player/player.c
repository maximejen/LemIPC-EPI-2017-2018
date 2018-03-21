/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** player.c
*/

#include <stdio.h>
#include "../../include/lemipc.h"

static const char *ERROR_MSG = "Error : can't find a positon for the player";

/*
** Description:
** This function init the content of the player struct.
*/
int init_player(lemipc_t *lem, player_t *player)
{
	player->mem = lem->mem;
	player->shm_id = lem->shm_id;
	player->sem_id = lem->sem_id;
	player->msg_id = lem->msg_id;
	player->team_id = lem->args->team_id;
	if (determine_starting_position(player))
		return (dprintf(2, "%s", ERROR_MSG) * 0 + 1);
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

int start_player(lemipc_t *lem)
{
	player_t player;

	if (init_player(lem, &player))
		return (1);
	while (!should_player_die(&player)) {

	}
	return (1);
}