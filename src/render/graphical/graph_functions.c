/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** open_window.c
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include "../../../include/lemipc.h"
#include "../../../include/color.h"

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

sfColor transform_color(color_t *color)
{
	sfColor color1;

	color1.r = (sfUint8)color->r;
	color1.g = (sfUint8)color->g;
	color1.b = (sfUint8)color->b;
	color1.a = 255;
	return (color1);
}

sfVector2f crvec(float x, float y)
{
	sfVector2f vec = {x, y};

	return (vec);
}

void draw_rectangle(sfRectangleShape *cell, sfRenderWindow *window,
		    sfVector2f position, sfColor color) {
	sfRectangleShape_setPosition(cell, position);
	sfRectangleShape_setFillColor(cell, color);
	sfRenderWindow_drawRectangleShape(window, cell, NULL);
}