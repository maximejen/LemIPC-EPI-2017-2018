/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** player_move.c
*/

#include <stdio.h>
#include "../../include/lemipc.h"

void move_right(player_t *player)
{
	int x = player->posx;
	int y = player->posy;

	if (is_in_range(x + 1, y, player->mem->width, player->mem->height) &&
		player->mem->map[y][x + 1] == 0) {
		player->mem->map[y][x + 1] = player->team_id;
		player->mem->map[y][x] = 0;
		player->posx++;
	}
}

void move_left(player_t *player)
{
	int x = player->posx;
	int y = player->posy;

	if (is_in_range(x - 1, y, player->mem->width, player->mem->height) &&
		player->mem->map[y][x - 1] == 0) {
		player->mem->map[y][x - 1] = player->team_id;
		player->mem->map[y][x] = 0;
		player->posx--;
	}
}

void move_bot(player_t *player)
{
	int x = player->posx;
	int y = player->posy;

	if (is_in_range(x, y + 1, player->mem->width, player->mem->height) &&
		player->mem->map[y + 1][x] == 0) {
		player->mem->map[y + 1][x] = player->team_id;
		player->mem->map[y][x] = 0;
		player->posy++;
	}
}

void move_top(player_t *player)
{
	int x = player->posx;
	int y = player->posy;

	if (is_in_range(x, y - 1, player->mem->width, player->mem->height) &&
		player->mem->map[y - 1][x] == 0) {
		player->mem->map[y - 1][x] = player->team_id;
		player->mem->map[y][x] = 0;
		player->posy--;
	}
}

void follow_the_order(player_t *player)
{
	int x = player->tx;
	int y = player->ty;

	if (ABS(y - player->posy) > ABS(x - player->posx))
		if (y - player->posy < 0)
			move_top(player);
		else
			move_bot(player);
	else {
		if (x - player->posx < 0)
			move_left(player);
		else
			move_right(player);
	}
}