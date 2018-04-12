/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** render.c
*/

#include <stdio.h>
#include <unistd.h>
#include "../../../include/lemipc.h"
#include "../../../include/color.h"

static const char *chars[8] = {
	"┏", "┓", "┗", "┛", "━", "┃", "━━", "━━━━━━━━"
};

static const char *WELCOME_MESSAGE = "You just entered the textual printing"
	" thread...\nEnjoy your experience...\n\n";

/*
** The purpose of this function is to print a char in the color dedicated
** to the team of the player in the map.
*/
void print_char(int team_id)
{
	color_t *color = get_color((unsigned int)team_id);
	printf("\e[48;5;%d;%d;%dm  \e[0m",
		color->r, color->g, color->b);
	fflush(stdout);
}

/*
** Description:
** This purpose of this function is to print a line of - of the width of
** the map.
*/
static void print_line(size_t width)
{
	int reducer = 4;
	size_t size = width / reducer;

	for (size_t k = 0 ; k < size ; k++) {
		printf("%s", chars[7]);
		fflush(stdout);
		if (k < width % reducer)
			write(1, chars[6], 6);
	}
}

/*
** Description:
** print the map in the shared_memory in the standard output.
*/
void print_map_text(lemipc_t *lem, int back)
{
	size_t height = lem->mem->height;
	size_t width = lem->mem->width;

	write(1, chars[0], 3);
	print_line(width);
	printf("%s\n", chars[1]);
	for (size_t i = 0 ; i < height ; i++) {
		write(1, chars[5], 3);
		for (size_t j = 0 ; j < width ; j++) {
			print_char(lem->mem->map[i][j]);
		}
		printf("%s\n", chars[5]);
	}
	write(1, chars[2], 3);
	print_line(width);
	printf("%s\n", chars[3]);
	if (back)
		printf("\e[%dA", HEIGHT + 2);
	fflush(stdout);
}

static void print_logs(lemipc_t *lem)
{
	char *msg = NULL;
	char *interp_msg;

	receive_message(lem->msg_id, 1, &msg, IPC_NOWAIT);
	if (msg != NULL) {
		interp_msg = interpret_message(msg);
		printf("%*s\n", WIDTH * 2 + 2, interp_msg);
		free(msg);
		free(interp_msg);
		msg = NULL;
	}
}

/*
** Description :
** When the user did not precise to render in graphic the program, a thread
** is created and render the view of the map in text in the terminal.
*/
void *textual_render(void *arg)
{
	lemipc_t *lem = arg;

	printf("%s", WELCOME_MESSAGE);
	printf("\e[?25l");
	fflush(stdout);
	while (CONTINUE) {
		print_logs(lem);
		print_map_text(lem, 1);
	}
	print_map_text(lem, 0);
	get_color(-1);
	printf("\e[?25h");
	fflush(stdout);
	return ("OK");
}
