/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** lemipc.h
*/

#ifndef LEMIPC_LEMIPC_H
	#define LEMIPC_LEMIPC_H

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
	int **map;
} sh_mem_t;

typedef struct lemipc_s {
	sh_mem_t *mem;
} lemipc_t;


/*
** Functions
*/
void lemipc_init(args_t *args);

// need it because stdio.h does not have it...
int asprintf(char **strp, const char *fmt, ...);

#endif //LEMIPC_LEMIPC_H
