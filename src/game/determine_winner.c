/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** determine_winner.c
*/

#include <stdio.h>
#include "../../include/lemipc.h"

static mbr_counter_list_t *CTR_LIST = NULL;

static int add_team_to_list(mbr_counter_t *data)
{
	mbr_counter_list_t *tmp = CTR_LIST;
	mbr_counter_list_t *element = malloc(sizeof(mbr_counter_list_t));

	if (!element)
		return (-1);
	element->data = data;
	element->next = NULL;
	if (tmp == NULL) {
		CTR_LIST = element;
		return (0);
	}
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp)
		tmp->next = element;
	return (0);
}

static void remove_team_from_list(mbr_counter_list_t *element)
{
	mbr_counter_list_t *tmp = CTR_LIST;

	if (element == CTR_LIST) {
		CTR_LIST = element->next;
		free(element->data);
		free(element);
		tmp = NULL;
	}
	while (tmp && tmp->next != NULL && tmp->next != element) {
		tmp = tmp->next;
	}
	if (tmp) {
		tmp->next = element->next;
		free(element->data);
		free(element);
	}
	element = NULL;
}

static mbr_counter_t *get_element(int team_id)
{
	mbr_counter_list_t *tmp = CTR_LIST;

	while (tmp && tmp->next != NULL && tmp->data->team_id != team_id)
		tmp = tmp->next;
	if (tmp)
		return (tmp->data);
	return (NULL);
}

static void add_to_team(int team_id)
{
	mbr_counter_t *element = get_element(team_id);

	if (element) {
		element->count++;
	}
	else {
		element = malloc(sizeof(mbr_counter_t));
		if (element) {
			element->count = 1;
			element->team_id = team_id;
			add_team_to_list(element);
		}
	}
}

int find_winner(lemipc_t *lem)
{
	mbr_counter_t *save = NULL;
	size_t h = lem->mem->height;
	size_t w = lem->mem->width;
	mbr_counter_list_t *tmp;

	for (size_t i = 0 ; i < h * w ; i++)
		if (lem->mem->map[i / h][i % w] > 0)
			add_to_team(lem->mem->map[i / h][i % w]);
	tmp = CTR_LIST;
	while (tmp) {
		if (!save || tmp->data->count > save->count)
			save = tmp->data;
		tmp = tmp->next;
	}
	tmp = CTR_LIST;
	while (tmp && tmp->next)
		remove_team_from_list(tmp);
	free(CTR_LIST);
	CTR_LIST = NULL;
	return (save ? save->team_id : 0);
}