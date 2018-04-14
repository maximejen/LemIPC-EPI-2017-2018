/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** utility.c
*/

#include <sys/sem.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <asm/errno.h>
#include "../include/lemipc.h"

void operate_on_sem(int sem_id, short num, short op)
{
	struct sembuf sops;

	sops.sem_num = (unsigned short)num;
	sops.sem_flg = 0;
	sops.sem_op = op;
	semop(sem_id, &sops, 1);
}

int should_i_be_commander(lemipc_t *lem)
{
	size_t w = lem->mem->width;
	size_t h = lem->mem->height;

	for (size_t i = 0 ; i < h * w ; i++) {
		if (lem->mem->map[i / h][i % w] == lem->args->team_id)
			return (0);
	}
	return (1);
}