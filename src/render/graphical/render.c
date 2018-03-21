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

static void draw_window(sfRenderWindow *window, lemipc_t *lem,
	sfVector2f *win_size)
{
	sfEvent e;

	while (sfRenderWindow_pollEvent(window, &e)) {
		if (e.type == sfEvtClosed || (is_esc_pressed(&e) == 1) ||
		    !CONTINUE)
			sfRenderWindow_close(window);
	}
	sfRenderWindow_clear(window, sfBlack);
	print_map_graph(lem, window, win_size);
	sfRenderWindow_display(window);
}

void *graphical_render(void *arg)
{
	lemipc_t *lem = arg;
	sfVector2f win_size;
	size_t size = get_cell_size(lem->mem->width, lem->mem->height,
				    WIN_WIDTH, WIN_HEIGHT);
	sfRenderWindow *window = open_window("LemIPC",
					     size * (lem->mem->width + 2),
					     size * (lem->mem->height + 2));

	win_size.x = size * (lem->mem->width + 2);
	win_size.y = size * (lem->mem->height + 2);
	printf("%s", WELCOME_MESSAGE);
	while (sfRenderWindow_isOpen(window) && CONTINUE) {
		draw_window(window, lem, &win_size);
	}
	sfRenderWindow_destroy(window);
	return ("OK");
}