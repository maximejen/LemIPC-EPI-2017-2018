/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** utility.c
*/

#include <fcntl.h>
#include <zconf.h>
#include <stdio.h>
#include <sys/sem.h>
#include "../../include/lemipc.h"

/*
** Description:
** This function find a random nbr under max using /dev/urandom file
*/
int rand_nbr(size_t max)
{
	int rand = 0;
	int fd = open("/dev/urandom", O_RDONLY);

	if (fd != -1) {
		read(fd, &rand, 4);
		rand %= max;
		close(fd);
	}
	return (rand);
}

/*
** Description:
** This function find a random starting position for the player
** using rand_nbr function
*/
int determine_starting_position(player_t *player)
{
	int fd = open("/dev/urandom", O_RDONLY);
	int x;
	int y;
	int max_try = 15;

	if (fd != -1) {
		do {
			x = rand_nbr(player->mem->width);
			y = rand_nbr(player->mem->height);
			max_try--;
		} while (player->mem->map[y][x] != 0 && max_try);
		if (!max_try)
			return (1);
		player->posx = x;
		player->posy = y;
		close(fd);
		return (0);
	}
	return (1);
}

/*
** Description:
** Check if the cell that is checked is in the map.
*/
int is_in_range(int x, int y, size_t w, size_t h)
{
	int ret = 1;

	if (x < 0 || (size_t) x >= w)
		ret = 0;
	if (ret && (y < 0 || (size_t) y >= h))
		ret = 0;
	return (ret);
}

/*
** Description:
** Get the 8 values arround the player and fill an int[] with it.
*/
void get_nearby_cells(int *nearby, player_t *p)
{
	int x = p->posx;
	int y = p->posy;
	size_t w = p->mem->width;
	size_t h = p->mem->height;

	nearby[0] = is_in_range(x - 1, y - 1, w, h) ? p->mem->map[y - 1][x - 1]
						    : -1;
	nearby[1] = is_in_range(x, y - 1, w, h) ? p->mem->map[y - 1][x] : -1;
	nearby[2] = is_in_range(x + 1, y - 1, w, h) ? p->mem->map[y - 1][x + 1]
						    : -1;
	nearby[3] = is_in_range(x - 1, y, w, h) ? p->mem->map[y][x - 1] : -1;
	nearby[4] = is_in_range(x + 1, y, w, h) ? p->mem->map[y][x + 1] : -1;
	nearby[5] = is_in_range(x - 1, y + 1, w, h) ? p->mem->map[y + 1][x - 1]
						    : -1;
	nearby[6] = is_in_range(x, y + 1, w, h) ? p->mem->map[y + 1][x] : -1;
	nearby[7] = is_in_range(x + 1, y + 1, w, h) ? p->mem->map[y + 1][x + 1]
						    : -1;
}

int get_commander_orders(player_t *p, lemipc_t *lem)
{
	char *str;
	char **tab = NULL;
	int type;

	if (receive_message(p->msg_id, p->team_id + 1, &str, IPC_NOWAIT)) {
		if (str && str[0] == '1') {
			send_message(p->msg_id, p->team_id + 1, str);
			return (1);
		}
		tab = my_str_to_wordtab(str, ';');
		type = atoi(tab[2]);
		if (type == 3) {
			p->tx = atoi(tab[3]);
			p->ty = atoi(tab[4]);
		}
		else if (type == 2)
			commander_relieving(lem);
		free(str);
		free_wordtab(tab);
		return (1);
	}
	return (0);
}
