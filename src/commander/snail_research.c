/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** snail_research.c
*/

#include <memory.h>
#include <stdio.h>
#include <zconf.h>
#include "../../include/lemipc.h"

static const int OPE_X[4] = {0, 1, 0, -1};
static const int OPE_Y[4] = {-1, 0, 1, 0};

//static void dump_map(int **tmp, size_t x, size_t y)
//{
//	for (size_t i = 0 ; i < y ; i++) {
//		for (size_t j = 0 ; j < x - 1 ; j++) {
//			if (tmp[i][j] > 0)
//				printf("%d", tmp[i][j]);
//			else if (tmp[i][j] == -1)
//				printf(" ");
//			else
//				printf(".");
//		}
//		if (tmp[i][x - 1] > 0)
//			printf("%d\n", tmp[i][x - 1]);
//		else if (tmp[i][x - 1] == -1)
//			printf(" \n");
//		else
//			printf(".\n");
//	}
//}
static int find_in_line(tmp_data_t *s, int **tmp, int team_id)
{
	for (int i = 0 ; i < s->size ; i++) {
		if (is_in_range(*s->x, *s->y, s->width, s->height) &&
			tmp[*s->y][*s->x] != team_id && tmp[*s->y][*s->x] > 0)
			return (1);
		if (is_in_range(*s->x, *s->y, s->width, s->height))
			tmp[*s->y][*s->x] = -1;
		*s->x += OPE_X[s->count % 4];
		*s->y += OPE_Y[s->count % 4];
	}
	return (0);
}

static int **copy_tab(sh_mem_t *mem)
{
	int **ret = malloc(sizeof(int *) * mem->height);

	if (!ret)
		return (NULL);
	for (size_t i = 0 ; i < mem->height ; i++) {
		ret[i] = malloc(sizeof(int) * mem->width);
		if (!ret[i])
			return (NULL);
		for (size_t j = 0 ; j < mem->width ; ++j) {
			ret[i][j] = mem->map[i][j];
		}
	}
	return (ret);
}

static void free_tmp(int **tmp, size_t height)
{
	for (size_t i = 0 ; i < height ; i++) {
		free(tmp[i]);
	}
	free(tmp);
	tmp = NULL;
}

static int can_continue(int **tmp, tmp_data_t *s, commander_t *cmd)
{
	size_t w = cmd->mem->width;
	size_t h = cmd->mem->height;
	int ret = 1;

	if (!CONTINUE || !tmp)
		return (0);
	if ((size_t)s->size >= w || (size_t)s->size >= h)
		ret = 0;
	for (size_t i = 0 ; !ret && i < h * w ; i++) {
		if (tmp[i / h][i % w] != -1)
			ret = 1;
	}
	if (ret && !(!is_in_range(*s->x, *s->y, s->width, s->height) ||
		tmp[*s->y][*s->x] == cmd->team_id ||
		tmp[*s->y][*s->x] <= 0))
		ret = 0;
	return (ret);
}

int find_target(commander_t *cmd)
{
	size_t width = cmd->mem->width;
	size_t height = cmd->mem->height;
	int **tmp = copy_tab(cmd->mem);
	tmp_data_t s = {width, height, &cmd->tx, &cmd->ty, 0, 0};

	while (can_continue(tmp, &s, cmd)) {
		if (find_in_line(&s, tmp, cmd->team_id) == 1) {
			cmd->tx = *s.x;
			cmd->ty = *s.y;
			free_tmp(tmp, height);
			return (1);
		}
		if (s.count % 2 == 0)
			s.size++;
		s.count++;
	}
	free_tmp(tmp, height);
	return (0);
}