/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** lemipc.h
*/

#ifndef LEMIPC_LEMIPC_H
	#define LEMIPC_LEMIPC_H

	#define HEIGHT 30
	#define WIDTH 30
	#define MSG_SIZE 32

	#include <sys/ipc.h>
	#include <pthread.h>

typedef struct args_s {
	char *path;
	int team_id;
	char *team_name;
	int is_graphical;
	char *graphical_lib_path;
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

typedef struct msg_s {
	long mtype;
	char data[MSG_SIZE];
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
	key_t key;
	args_t *args;
	pthread_t graph_thread;
} lemipc_t;

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
** Render Functions
*/
void *textual_render(void *arg);
void print_map(lemipc_t *lem, int back);

void *graphical_render(void *arg);

// need it because stdio.h does not have it... no need, need #define GNU_SOURCE
int asprintf(char **strp, const char *fmt, ...);

#endif //LEMIPC_LEMIPC_H
