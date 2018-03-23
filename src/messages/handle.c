/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** handle.c
*/

#include <stdio.h>
#include "../../include/lemipc.h"

const char *SUB[2] = {"player", "commander"};

const char *MSG_TYPE[3] = {
	"A %s from team %s just connected",
	"A %s from team %s just disconnected",
	"Commander[%s] command to go %s:%s"
};

char *interpret_message(const char *content)
{
	char **tab = my_str_to_wordtab(content, ';');
	char *ret = NULL;
	int type = 0;
	int subject = 0;

	if (tab) {
		type = atoi(tab[2]);
		subject = atoi(tab[0]);
		if (type < 2)
			asprintf(&ret, MSG_TYPE[type - 1], SUB[subject - 1], tab[1]);
		else
			asprintf(&ret, MSG_TYPE[type - 1], tab[1], tab[3], tab[4]);
	}
	return (ret);
}
