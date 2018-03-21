/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** color_generator.c
*/

#include <stdlib.h>
#include "../../../include/color.h"

color_list_t *LIST = NULL;

color_t *find_color_by_key(unsigned int key)
{
	color_list_t *tmp = LIST;

	while (tmp && tmp->next != NULL) {
		if (key == tmp->color->key)
			return (tmp->color);
		tmp = tmp->next;
	}
	return (NULL);
}

color_t *generate_color(unsigned int key)
{
	color_t *color = malloc(sizeof(color_t));

	if (key) {
		srandom(key);
		color->key = key;
		color->r = (int)(random() % 256);
		color->g = (int)(random() % 256);
		color->b = (int)(random() % 256);
	}
	else {
		color->key = key;
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	return (color);
}

color_t *get_color(unsigned int key)
{
	color_t *color = find_color_by_key(key);

	if (!color) {
		color = generate_color(key);
		add_color_to_list(color);
	}
	return (color);
}

void reset_colors(void)
{
	while (LIST) {
		remove_from_list(LIST);
	}
	free(LIST);
	LIST = NULL;
}

