/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** render.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <SFML/Graphics/Types.h>
#include "../../../include/lemipc.h"

static const char *WELCOME_MESSAGE = "You just entered the graphical"
	" thread...\nEnjoy your experience\n\n";

size_t get_cell_size(size_t width, size_t height)
{
	int is_height_smaller = height < width;
	size_t size;

	if (is_height_smaller) {
		size = WIN_WIDTH / width;
	} else {
		size = WIN_HEIGHT / height;
	}
	return (size);
}

static void draw_window(sfRenderWindow *window, lemipc_t *lem)
{
	sfEvent e;

	while (sfRenderWindow_pollEvent(window, &e)) {
		if (e.type == sfEvtClosed || (is_esc_pressed(&e) == 1) ||
		    !CONTINUE)
			sfRenderWindow_close(window);
	}
	sfRenderWindow_clear(window, sfBlack);
	print_map_graph(lem, window);
	sfRenderWindow_display(window);
}

static void render_map(lemipc_t *lem)
{
	sfRenderWindow *window = open_window("LemIPC");

	while (sfRenderWindow_isOpen(window) && CONTINUE) {
		draw_window(window, lem);
	}
	sfRenderWindow_destroy(window);
}

void *graphical_render(void *arg)
{
	lemipc_t *lem = arg;

	printf("%s", WELCOME_MESSAGE);
	// Todo : Here, launch the graphical render.
	render_map(lem);
	return ("OK");
}