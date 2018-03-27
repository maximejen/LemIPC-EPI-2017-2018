/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** commander_functions.c
*/

#include <memory.h>
#include <stdio.h>
#include "../../include/lemipc.h"

int update_connections(commander_t *cmd)
{
	int count = 0;
	size_t h = cmd->mem->height;
	size_t w = cmd->mem->width;

	for (size_t i = 0 ; i < h * w ; i++) {
		if (cmd->mem->map[i / h][i % w] == cmd->team_id)
			count++;
	}
	cmd->p_count = count;
	return (0);
}

