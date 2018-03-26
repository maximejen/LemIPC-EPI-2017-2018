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

void operate_on_sem(int sem_id, short op)
{
	struct sembuf sops;

	sops.sem_num = 0;
	sops.sem_flg = 0;
	sops.sem_op = op;
	semop(sem_id, &sops, 1);
}