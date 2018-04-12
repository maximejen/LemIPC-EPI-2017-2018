/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** print_map.c
*/

#include <stdio.h>
#include <SFML/Graphics/Types.h>
#include "../../../include/color.h"
#include "../../../include/lemipc.h"

/*
** Description:
** Calculate the size of a "cell" in the window
*/
size_t get_cell_size(size_t width, size_t height,
	float win_width, float win_height)
{
	int is_height_smaller = height < width;
	size_t size;

	if (is_height_smaller) {
		size = (size_t) (win_height / (height + 2));
	} else {
		size = (size_t) (win_width / (width + 2));
	}
	return (size);
}

/*
** Description:
** print a line of of the map in the window
*/
void print_line_graph(lemipc_t *lem, size_t i, sfRenderWindow *window,
	sfVector2f *win_size)
{
	sfRectangleShape *cell = sfRectangleShape_create();
	size_t height = lem->mem->height;
	size_t width = lem->mem->width;
	size_t size = get_cell_size(width, height, win_size->x, win_size->y);
	color_t *color;

	sfRectangleShape_setSize(cell, crvec(size, size));
	for (size_t j = 0 ; j < width ; j++) {
		color = get_color((unsigned int) lem->mem->map[i][j]);
		draw_rectangle(cell, window,
			crvec((j + 1) * size, (i + 1) * size),
			transform_color(color));
	}
	sfRectangleShape_destroy(cell);
}

/*
** Description:
** Print the map that is in the shared_memory in the window
*/
void print_map_graph(lemipc_t *lem, sfRenderWindow *window,
	sfVector2f *win_size)
{
	sfRectangleShape *cell = sfRectangleShape_create();
	size_t width = lem->mem->width;
	size_t height = lem->mem->height;
	size_t size = get_cell_size(width, height, win_size->x, win_size->y);

	sfRectangleShape_setSize(cell, crvec((width + 2) * size, size));
	draw_rectangle(cell, window, crvec(0, 0), sfWhite);
	sfRectangleShape_setSize(cell, crvec(size, size));
	for (size_t i = 0 ; i < height ; i++) {
		draw_rectangle(cell, window, crvec(0, (i + 1) * size),
			sfWhite);
		print_line_graph(lem, i, window, win_size);
		draw_rectangle(cell, window,
			crvec((width + 1) * size, (i + 1) * size),
			sfWhite);
	}
	sfRectangleShape_setSize(cell, crvec((width + 2) * size, size));
	draw_rectangle(cell, window, crvec(0, (height + 1) * size), sfWhite);
	sfRectangleShape_destroy(cell);
}

