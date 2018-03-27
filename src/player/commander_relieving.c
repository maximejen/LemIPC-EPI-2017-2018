/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** commander_relieving.c
*/

#include "../../include/lemipc.h"

void commander_relieving(lemipc_t *lem)
{
	lem->is_commander = 1;
	create_commander(lem);
}
