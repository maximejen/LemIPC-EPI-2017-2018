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

int send_message(int msg_q, int channel, char *content)
{
	msg_t message;
	int ret = 1;

	message.mtype = channel;
	memset(message.mtext, 0, 32);
	strncpy(message.mtext, content, 31);
	if (msgsnd(msg_q, &message, sizeof(msg_t), IPC_NOWAIT) == -1)
		ret = 0;
	return (ret);
}

int receive_message(int msg_q, int channel, char **content, int flags)
{
	msg_t msg;
	int ret = 1;

	if (msgrcv(msg_q, &msg, sizeof(msg_t), channel, flags) == -1) {
		if (errno != ENOMSG)
			ret = 0;
	}
	else {
		*content = strdup(msg.mtext);
	}
	return (ret);
}