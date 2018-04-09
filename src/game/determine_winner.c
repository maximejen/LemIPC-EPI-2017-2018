/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** determine_winner.c
*/

#include <stdio.h>
#include "../../include/lemipc.h"

static int add_team_to_list(mbr_counter_list_t **list, mbr_counter_t *data)
{
	mbr_counter_list_t *tmp = *list;
	mbr_counter_list_t *element = malloc(sizeof(mbr_counter_list_t));

	if (!element)
		return (-1);
	element->data = data;
	element->next = NULL;
	if (tmp == NULL) {
		*list = element;
		return (0);
	}
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp)
		tmp->next = element;
	return (0);
}

static void
remove_team_from_list(mbr_counter_list_t **list, mbr_counter_list_t *element)
{
	mbr_counter_list_t *tmp = *list;

	if (element == *list) {
		*list = element->next;
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

static mbr_counter_t *get_element(mbr_counter_list_t *list, int team_id)
{
	mbr_counter_list_t *tmp = list;

	while (tmp && tmp->next != NULL && tmp->data->team_id != team_id)
		tmp = tmp->next;
	if (tmp)
		return (tmp->data);
	return (NULL);
}

static void add_to_team(mbr_counter_list_t **list, int team_id)
{
	mbr_counter_t *element = get_element(*list, team_id);

	if (element) {
		element->count++;
	} else {
		element = malloc(sizeof(mbr_counter_t));
		if (element) {
			element->count = 1;
			element->team_id = team_id;
			add_team_to_list(list, element);
		}
	}
}

int find_winner(lemipc_t *lem)
{
	mbr_counter_t *save = NULL;
	size_t h = lem->mem->height;
	size_t w = lem->mem->width;
	mbr_counter_list_t *tmp;
	static mbr_counter_list_t *list = NULL;

	for (size_t i = 0 ; i < h * w ; i++)
		if (lem->mem->map[i / h][i % w] > 0)
			add_to_team(&list, lem->mem->map[i / h][i % w]);
	tmp = list;
	while (tmp) {
		if (!save || tmp->data->count > save->count)
			save = tmp->data;
		tmp = tmp->next;
	}
	while (list && list->next)
		remove_team_from_list(&list, list);
	free(list);
	list = NULL;
	return (save ? save->team_id : 0);
}