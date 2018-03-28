/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** put_targets.c
*/

#include <stdio.h>
#include "../../../include/lemipc.h"

static team_target_list_t *TRG_LIST = NULL;

static int add_target_to_list(team_target_t *data)
{
	team_target_list_t *tmp = TRG_LIST;
	team_target_list_t *element = malloc(sizeof(team_target_list_t));

	if (!element)
		return (-1);
	element->data = data;
	element->next = NULL;
	if (tmp == NULL) {
		TRG_LIST = element;
		return (0);
	}
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp)
		tmp->next = element;
	return (0);
}

static void remove_target_from_list(team_target_list_t *element)
{
	team_target_list_t *tmp = TRG_LIST;

	if (element == TRG_LIST) {
		TRG_LIST = element->next;
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

void edit_target(int team_id, int x, int y)
{
	team_target_list_t *tmp = TRG_LIST;
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
			add_target_to_list(element);
		}
	}
}

void put_targets(sfRenderWindow *window, lemipc_t *lem)
{
	team_target_list_t *tmp = TRG_LIST;
	color_t *color;
	size_t w = lem->mem->width;
	size_t h = lem->mem->height;
	sfUint8 s = (sfUint8) get_cell_size(w, h, WIN_WIDTH, WIN_HEIGHT);
	sfRectangleShape *target = sfRectangleShape_create();
	int x;
	int y;

	sfRectangleShape_setSize(target, crvec(s / 2, s / 2));
	while (tmp) {
		x = tmp->data->x;
		y = tmp->data->y;
		color = get_color((unsigned int) tmp->data->team_id);
		draw_rectangle(target, window, crvec((x + 1) * s + s / 4,
						     (y + 1) * s + s / 4),
			       transform_color(color));
		tmp = tmp->next;
	}
	sfRectangleShape_destroy(target);
}

void reset_target_stack()
{
	while (TRG_LIST)
		remove_target_from_list(TRG_LIST);
	free(TRG_LIST);
	TRG_LIST = NULL;
}

//static const char *TARGET[40] = {
//	"0000000000000000000000000000000000000000",
//	"0000000000000000000000000000000000000000",
//	"0000000000000000000110000000000000000000",
//	"0000000000000000000110000000000000000000",
//	"0000000000000000000110000000000000000000",
//	"0000000000000000000110000000000000000000",
//	"0000000000000000011111100000000000000000",
//	"0000000000000011111111111100000000000000",
//	"0000000000000111111111111110000000000000",
//	"0000000000011111000110001111100000000000",
//	"0000000000111100000110000011110000000000",
//	"0000000001110000000110000000111000000000",
//	"0000000001100000000110000000011000000000",
//	"0000000011100000000110000000011100000000",
//	"0000000111000000000110000000001110000000",
//	"0000000111000000000000000000001110000000",
//	"0000000110000000000000000000000110000000",
//	"0000001110000000000000000000000111000000",
//	"0000001110000000000000000000000111000000",
//	"0011111111111110000000000111111111111100",
//	"0011111111111110000000000111111111111100",
//	"0000001110000000000000000000000111000000",
//	"0000001110000000000000000000000111000000",
//	"0000000110000000000000000000000110000000",
//	"0000000111000000000000000000001110000000",
//	"0000000111000000000110000000001110000000",
//	"0000000011100000000110000000011100000000",
//	"0000000001100000000110000000011000000000",
//	"0000000001110000000110000000111000000000",
//	"0000000000111100000110000011110000000000",
//	"0000000000011111000110001111100000000000",
//	"0000000000000111111111111110000000000000",
//	"0000000000000011111111111100000000000000",
//	"0000000000000000011111100000000000000000",
//	"0000000000000000000110000000000000000000",
//	"0000000000000000000110000000000000000000",
//	"0000000000000000000110000000000000000000",
//	"0000000000000000000110000000000000000000",
//	"0000000000000000000000000000000000000000",
//	"0000000000000000000000000000000000000000"
//};
