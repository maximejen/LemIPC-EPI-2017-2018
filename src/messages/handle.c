/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** handle.c
*/

#include <stdio.h>
#include <memory.h>
#include <sys/msg.h>
#include <errno.h>
#include "../../include/lemipc.h"

const char *SUB[2] = {"Player", "Commander"};

const char *MSG_TYPE[3] = {
	"A %s from team %s just connected",
	"A %s from team %s just disconnected",
	"Commander[%s] commands to go %s:%s"
};

char *interpret_message(const char *content)
{
	char **tab = my_str_to_wordtab(content, ';');
	char *ret = NULL;
	int type = 0;
	int sub = 0;

	if (tab) {
		type = atoi(tab[2]);
		sub = atoi(tab[0]);
		if (type < 2)
			asprintf(&ret, MSG_TYPE[type - 1], SUB[sub - 1],
				 tab[1]);
		else
			asprintf(&ret, MSG_TYPE[type - 1], tab[1], tab[3],
				 tab[4]);
	}
	return (ret);
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
