/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** color.h
*/

#ifndef LEMIPC_COLOR_H_
	#define LEMIPC_COLOR_H_

	#include <stdlib.h>

typedef struct color_s {
	unsigned int key;
	int r;
	int g;
	int b;
} color_t;

typedef struct color_list_s {
	color_t *color;
	struct color_list_s *next;
} color_list_t;

color_t *get_color(int key);
color_t *generate_color(unsigned int key);
void reset_colors(color_list_t **list);
int add_color_to_list(color_list_t **list, color_t *color);
void remove_from_list(color_list_t **list, color_list_t *element);

#endif //LEMIPC_COLOR_H_
