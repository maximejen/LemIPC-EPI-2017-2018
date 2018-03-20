/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** handle_color_list.c
*/

#include <stdlib.h>
#include "../../../include/color.h"

color_list_t *LIST;

int add_color_to_list(color_t *color)
{
	color_list_t *tmp = LIST;
	color_list_t *element = malloc(sizeof(color_list_t));

	if (!element)
		return (-1);
	element->color = color;
	if (tmp == NULL) {
		LIST = element;
		return (0);
	}
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp)
		tmp->next = element;
	return (0);
}

void remove_from_list(color_list_t *element)
{
	color_list_t *tmp = LIST;

	if (element == LIST) {
		LIST = element->next;
		free(element);
		tmp = NULL;
	}
	while (tmp && tmp->next != NULL && tmp->next != element) {
		tmp = tmp->next;
	}
	if (tmp) {
		tmp->next = element->next;
		free(element->color);
		free(element);
	}
	element = NULL;
}