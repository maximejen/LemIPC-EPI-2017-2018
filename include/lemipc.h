/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** lemipc.h
*/

#ifndef LEMIPC_LEMIPC_H
	#define LEMIPC_LEMIPC_H

	#define WIDTH 46
	#define HEIGHT 46
	#define WIN_WIDTH 800
	#define WIN_HEIGHT 800
	#define MSG_SIZE 32

	#define LOG_CHANNEL 1

	#include <sys/ipc.h>
	#include <pthread.h>
	#include <SFML/Graphics.h>
	#include "color.h"

extern int CONTINUE;

typedef struct args_s {
	char *path;
	int team_id;
	char *team_name;
	int is_graphical;
} args_t;

/*
** This struct represent the memory shared between all the programs
** keys for the map :
** -1 => cell is free
** 1,2,... => cell is taken by a member of the team with the same value
*/
typedef struct shared_mem_s {
	size_t width;
	size_t height;
	int map[HEIGHT][WIDTH];
} sh_mem_t;

typedef struct tmp_data_s {
	size_t width;
	size_t height;
	int *x;
	int *y;
	int size;
	int count;
} tmp_data_t;

typedef struct msg_s {
	long mtype;
	char mtext[MSG_SIZE];
} msg_t;

/*
** two semaphores will be created.
** id 0 is sem to write in the map
** id 1 is sem to create commander
*/
typedef struct lemipc_s {
	sh_mem_t *mem;
	int shm_id;
	int sem_id;
	int msg_id;
	unsigned short is_first;
	unsigned short is_commander;
	key_t key;
	args_t *args;
	pthread_t graph_thread;
	pthread_t cmd;
} lemipc_t;

typedef struct player_s {
	sh_mem_t *mem;
	int shm_id;
	int sem_id;
	int msg_id;
	int posx;
	int posy;
	int team_id;
} player_t;

typedef struct commander_s {
	sh_mem_t *mem;
	int shm_id;
	int sem_id;
	int msg_id;
	int target_x;
	int target_y;
	int team_id;
} commander_t;

typedef struct graph_print_s {

} graph_print_t;


/*
** Functions
*/
int lemipc_start(args_t *args);
void init_shared_memory(lemipc_t *lem);
void init_semaphores(lemipc_t *lem);
void init_message_queue(lemipc_t *lem);

/*
** Textual Render Functions
*/
void *textual_render(void *arg);
void print_map_text(lemipc_t *lem, int back);

/*
** Graphical Render Functions
*/
void *graphical_render(void *arg);
sfRenderWindow *open_window(const char *, size_t, size_t);
int is_esc_pressed(sfEvent *event);
sfColor transform_color(color_t *color);
sfVector2f crvec(float x, float y);
size_t get_cell_size(size_t width, size_t height, float, float);
void print_map_graph(lemipc_t *lem, sfRenderWindow *window,
	sfVector2f *win_size);
void draw_rectangle(sfRectangleShape *cell, sfRenderWindow *window,
		    sfVector2f position, sfColor color);

/*
** Player Functions
*/
int start_player(lemipc_t *lem);
int init_player(lemipc_t *lem, player_t *player);
int determine_starting_position(player_t *player);
void get_nearby_cells(int *nearby, player_t *p);
void move_right(player_t *player);
void move_left(player_t *player);
void move_top(player_t *player);
void move_bot(player_t *player);

/*
** Utility Functions
*/
int rand_nbr(size_t max);
int is_in_range(int x, int y, size_t w, size_t h);
void operate_on_sem(int sem_id, short op);
int send_message(int msg_q, int channel, char *content);
int receive_message(int msg_q, int channel, char **content, int flags);
char **my_str_to_wordtab(const char *str, char c);

/*
** Message Functions
*/
char *interpret_message(const char *content);

/*
** Commander Functions
*/
int create_commander(lemipc_t *);
int find_target(commander_t *cmd);

// need it because stdio.h does not have it... no need, need #define GNU_SOURCE
int asprintf(char **strp, const char *fmt, ...);

#endif //LEMIPC_LEMIPC_H
