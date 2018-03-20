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

static void draw_window(sfRenderWindow *window, sfTexture *texture,
			sfSprite *sprite, lemipc_t *lem)
{
	sfEvent e;

	(void)lem;
	(void)texture;
	(void)sprite;
	while (sfRenderWindow_pollEvent(window, &e))
	{
		if (e.type == sfEvtClosed || (is_esc_pressed(&e) == 1) ||
			!CONTINUE)
			sfRenderWindow_close(window);
	}
	sfRenderWindow_clear(window, sfBlack);
	// Todo : Draw the rectangles in the texture
	// Todo : Draw the sprite in the window
//	sfRenderWindow_drawSprite(window, sprite, NULL);
	sfRenderWindow_display(window);
}

static void render_map(lemipc_t *lem)
{
	sfRenderWindow *window = open_window("LemIPC");
	sfTexture *texture = sfTexture_create(WIN_WIDTH, WIN_HEIGHT);
	sfSprite *sprite = sfSprite_create();

	sfSprite_setTexture(sprite, texture, sfTrue);
	while (sfRenderWindow_isOpen(window) && CONTINUE)
	{
		draw_window(window, texture, sprite, lem);
	}
	sfRenderWindow_destroy(window);
	sfTexture_destroy(texture);
	sfSprite_destroy(sprite);
}

void *graphical_render(void *arg)
{
	lemipc_t *lem = arg;

	printf("%s", WELCOME_MESSAGE);
	// Todo : Here, launch the graphical render.
	render_map(lem);
	return ("OK");
}