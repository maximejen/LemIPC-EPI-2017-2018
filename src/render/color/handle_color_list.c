/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** handle_color_list.c
*/

#include <stdlib.h>
#include "../../../include/color.h"

color_t *generate_color(unsigned int key)
{
	color_t *color = malloc(sizeof(color_t));

	if (!color)
		return (NULL);
	if (key) {
		srandom(key);
		color->key = key;
		color->r = (int)(random() % 256);
		color->g = (int)(random() % 256);
		color->b = (int)(random() % 256);
	} else {
		color->key = key;
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	return (color);
}