/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** time_handler.c
*/

#include <zconf.h>
#include <stdio.h>
#include "../../include/lemipc.h"

static int is_there_only_one_team(lemipc_t *lem)
{
	size_t h = lem->mem->height;
	size_t w = lem->mem->width;
	int save = 0;
	int value = 0;

	for (size_t i = 0 ; i < h * w ; i++) {
		value = lem->mem->map[i / h][i % w];
		if (!save && value)
			save = lem->mem->map[i / h][i % w];
		if (save && value > 0 && save != value)
			return (0);
	}
	return (1);
}

void *time_handle(void *arg)
{
	lemipc_t *lem = arg;
	int count = 0;
	char *str;

	while (CONTINUE && count < TIMEOUT) {
		if (!is_there_only_one_team(lem)) {
			count = 0;
			continue;
		}
		reset_target_stack(&lem->trg_list);
		sleep(1);
		count++;
		asprintf(&str, "3;%d;4", TIMEOUT - count);
		send_message(lem->msg_id, 1, str);
		free(str);
	}
	CONTINUE = 0;
	return ("OK");
}