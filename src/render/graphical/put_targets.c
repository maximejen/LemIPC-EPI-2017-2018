/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** put_targets.c
*/

#include <stdio.h>
#include "../../../include/lemipc.h"

static int add_target_to_list(team_target_list_t **list, team_target_t *data)
{
	team_target_list_t *tmp = *list;
	team_target_list_t *element = malloc(sizeof(team_target_list_t));

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
remove_target_from_list(team_target_list_t **list, team_target_list_t *element)
{
	team_target_list_t *tmp = *list;

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

void edit_target(int team_id, int x, int y, team_target_list_t **list)
{
	team_target_list_t *tmp = *list;
	team_target_t *element = NULL;

	while (tmp && tmp->data->team_id != team_id)
		tmp = tmp->next;
	if (tmp) {
		element = tmp->data;
		element->x = x;
		element->y = y;
	} else {
		element = malloc(sizeof(team_target_t));
		if (element) {
			element->x = x;
			element->y = y;
			element->team_id = team_id;
			add_target_to_list(list, element);
		}
	}
}

void put_targets(sfRenderWindow *window, lemipc_t *lem)
{
	team_target_list_t *tmp = lem->trg_list;
	color_t *color;
	size_t w = lem->mem->width;
	size_t h = lem->mem->height;
	sfUint8 s = (sfUint8)get_cell_size(w, h, WIN_WIDTH, WIN_HEIGHT);
	sfRectangleShape *target = sfRectangleShape_create();
	int x;
	int y;

	sfRectangleShape_setSize(target, crvec(s / 2, s / 2));
	while (tmp) {
		x = tmp->data->x;
		y = tmp->data->y;
		color = get_color((unsigned int)tmp->data->team_id);
		draw_rectangle(target, window, crvec((x + 1) * s + s / 4,
			(y + 1) * s + s / 4),
			transform_color(color));
		tmp = tmp->next;
	}
	sfRectangleShape_destroy(target);
}

void reset_target_stack(team_target_list_t **list)
{
	while (*list)
		remove_target_from_list(list, *list);
	free(*list);
	*list = NULL;
}
