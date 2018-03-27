/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** commander_functions.c
*/

#include <memory.h>
#include <stdio.h>
#include "../../include/lemipc.h"

static int FLAGS = IPC_NOWAIT;

int update_connections(commander_t *cmd)
{
	char *content = NULL;
	char *connection_message = NULL;
	char *disconnection_message = NULL;

	if (!receive_message(cmd->msg_id, cmd->team_id + 1, &content, FLAGS))
		return (0);
	if (content && content[0] == '2')
		send_message(cmd->msg_id, cmd->team_id + 1, content);
	if (content) {
		asprintf(&connection_message, "1;%d;1", cmd->team_id);
		asprintf(&disconnection_message, "1;%d;2", cmd->team_id);
		if (strcmp(content, connection_message) == 0)
			cmd->p_count++;
		if (strcmp(content, disconnection_message) == 0)
			cmd->p_count--;
	}
	free(connection_message);
	free(disconnection_message);
	free(content);
	return (1);
}

