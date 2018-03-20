/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** render.c
*/

#include <stdio.h>
#include <unistd.h>
#include "../../include/lemipc.h"

static char *chars[8] = {
	"┏", "┓", "┗", "┛", "━", "┃", "━━", "━━━━━━━━"
};

static void print_char(int team_id)
{
	team_id = team_id % 256;
	if (team_id)
		printf("\e[48;5;%dm  \e[0m", team_id);
	else
		printf("\e[0m  ");
	fflush(stdout);
}

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

void print_map(lemipc_t *lem, int back)
{
	size_t height = lem->mem->height;
	size_t width = lem->mem->width;

	write(1, chars[0], 3);
	print_line(width);
	printf("%s\n", chars[1]);
	for (size_t i = 0 ; i < height ; i++) {
		write(1, chars[5], 3);
		for (size_t j = 0 ; j < width ; j++)
			print_char(lem->mem->map[i][j]);
		printf("%s\n", chars[5]);
	}
	write(1, chars[2], 3);
	print_line(width);
	printf("%s\n", chars[3]);
	if (back)
		printf("\e[%dA", HEIGHT + 2);
	fflush(stdout);
}

/*
** Description :
** When the user did not precise to render in graphic the program, a thread
** is created and render the view of the map in text in the terminal.
*/
void *textual_render(void *arg)
{
	lemipc_t *lem = arg;

	printf("You just entered the textual printing thread...\n");
	printf("Enjoy your experience...\n\n");
	printf("\e[?25l");
	fflush(stdout);
	for (int i = 0 ; i < 1000 ; i++) {
		print_map(lem, 1);
	}
	print_map(lem, 0);
	printf("\e[?25h");
	fflush(stdout);
	return ("OK");
}
