/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** color_generator.c
*/

#include <stdlib.h>
#include "../../../include/color.h"

color_t *find_color_by_key(color_list_t **list, unsigned int key)
{
	color_list_t *tmp = *list;

	while (tmp && tmp->next != NULL) {
		if (key == tmp->color->key)
			return (tmp->color);
		tmp = tmp->next;
	}
	return (NULL);
}

int add_color_to_list(color_list_t **list, color_t *color)
{
	color_list_t *tmp = *list;
	color_list_t *element = malloc(sizeof(color_list_t));

	if (!element)
		return (-1);
	element->color = color;
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

color_t *get_color(int key)
{
	static color_list_t *list = NULL;
	color_t *color = find_color_by_key(&list, (unsigned int)key);

	if (key == -1) {
		reset_colors(&list);
		return (NULL);
	}
	if (!color) {
		color = generate_color((unsigned int)key);
		if (!color)
			return (NULL);
		add_color_to_list(&list, color);
	}
	return (color);
}

void remove_from_list(color_list_t **list, color_list_t *element)
{
	color_list_t *tmp = *list;

	if (element == *list) {
		*list = element->next;
		free(element->color);
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

void reset_colors(color_list_t **list)
{
	while (*list) {
		remove_from_list(list, *list);
	}
	free(*list);
	*list = NULL;
}
