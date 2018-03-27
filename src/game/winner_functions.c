/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** print_winner.c
*/

#include <stdio.h>
#include <zconf.h>
#include "../../include/lemipc.h"

void print_winner(lemipc_t *lem)
{
	color_t *c;
	int t = 0;

	t = find_winner(lem);
	if (t) {
		c = get_color((unsigned int) t);
		printf("\nAnd the winner of THE FIGHT is...");
		fflush(stdout);
		sleep(2);
		printf("Team : \e[48;5;%d;%d;%dm\e[30m%d\e[0m\nGG!\n",
		       c->r, c->g, c->b, t);
	}
}