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
	put_targets(window, lem);
	sfRenderWindow_display(window);
}

static void interpret_and_print_log(lemipc_t *lem)
{
	char *msg = NULL;
	char *interp_msg = NULL;
	char **t;

	receive_message(lem->msg_id, 1, &msg, IPC_NOWAIT);
	if (msg != NULL) {
		t = my_str_to_wordtab(msg, ';');
		interp_msg = interpret_message(msg);
		printf("%s\n", interp_msg);
		if (atoi(t[0]) == 2 && atoi(t[2]) == 3)
			edit_target(atoi(t[1]), atoi(t[3]), atoi(t[4]));
		free(msg);
		free(interp_msg);
		free_wordtab(t);
		msg = NULL;
	}
}

static void render_window(sfRenderWindow *window,
	lemipc_t *lem, sfVector2f *win_size)
{
	while (sfRenderWindow_isOpen(window) && CONTINUE) {
		interpret_and_print_log(lem);
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
	reset_target_stack();
	kill(0, SIGINT);
	return ("OK");
}