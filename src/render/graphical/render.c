/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** render.c
*/

#include <stdio.h>
#include <signal.h>
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

static void render_window(sfRenderWindow *window, lemipc_t *lem,
	sfVector2f *win_size)
{
	char *msg = NULL;
	char *interp_msg = NULL;

	while (sfRenderWindow_isOpen(window) && CONTINUE) {
		receive_message(lem->msg_id, 1, &msg, IPC_NOWAIT);
		if (msg != NULL) {
			interp_msg = interpret_message(msg);
			printf("%s\n", interp_msg);
			free(msg);
			free(interp_msg);
			msg = NULL;
		}
		draw_window(window, lem, win_size);
	}
}

void *graphical_render(void *arg)
{
	lemipc_t *lem = arg;
	sfVector2f win_size;
	size_t width = lem->mem->width;
	size_t height = lem->mem->height;
	size_t cell_size = get_cell_size(width, height, WIN_WIDTH, WIN_HEIGHT);
	sfRenderWindow *window = open_window("LemIPC", cell_size * (width + 2),
					     cell_size * (height + 2));

	win_size.x = cell_size * (width + 2);
	win_size.y = cell_size * (height + 2);
	printf("%s", WELCOME_MESSAGE);
	render_window(window, lem, &win_size);
	sfRenderWindow_destroy(window);
	kill(0, SIGINT);
	return ("OK");
}