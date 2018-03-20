/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** open_window.c
*/

#include <SFML/Graphics.h>
#include "../../../include/lemipc.h"

static const sfUint32 FLAGS_WIN = sfClose | sfResize;

sfRenderWindow *open_window(const char *title)
{
	sfVideoMode mode;
	sfRenderWindow *window;

	mode.bitsPerPixel = 32;
	mode.width = WIN_WIDTH;
	mode.height = WIN_HEIGHT;
	window = sfRenderWindow_create(mode, title, FLAGS_WIN, NULL);
	sfRenderWindow_setMouseCursorVisible(window, sfFalse);
	return (window);
}

int is_esc_pressed(sfEvent *event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
		return (1);
	return (0);
}