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

const char *SUB[3] = {"Player", "Commander", "Time"};

const char *MSG_TYPE[4] = {
	"A %s from team %s just connected",
	"A %s from team %s just disconnected",
	"Commander[%s] commands to go %s:%s",
	"%s is running out ... %s sec remaining"
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
		if (sub == 3)
			asprintf(&ret, MSG_TYPE[type - 1], SUB[sub - 1],
				tab[1]);
		if ((sub == 1 || sub == 2) && type - 1 < 2)
			asprintf(&ret, MSG_TYPE[type - 1], SUB[sub - 1],
				tab[1]);
		else if (sub == 1 || sub == 2)
			asprintf(&ret, MSG_TYPE[type - 1], tab[1], tab[3],
				tab[4]);
	}
	free_wordtab(tab);
	return (ret);
}

int send_message(int msg_q, int channel, char *content)
{
	msg_t message;
	int ret = 1;

	if (!content)
		return (0);
	memset(&message, 0, sizeof(msg_t));
	message.mtype = channel;
	strncpy(message.mtext, content, MSG_SIZE - 1);
	if (msgsnd(msg_q, (void *)&message, MSG_SIZE, IPC_NOWAIT) == -1)
		ret = 0;
	return (ret);
}

int receive_message(int msg_q, int channel, char **content, int flags)
{
	msg_t msg;
	int ret = 1;

	if (msgrcv(msg_q, &msg, MSG_SIZE, channel, flags) == -1) {
		if (errno == ENOMSG)
			ret = 0;
	} else {
		*content = strdup(msg.mtext);
	}
	return (ret);
}
