/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** render.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../../../include/lemipc.h"

static const char *WELCOME_MESSAGE = "You just entered the graphical"
	"thread...\nEnjoy your experience\n\n";

static const int FLAGS = RTLD_NOW | RTLD_GLOBAL;

static int load_graph_lib(lemipc_t *lem, void **handle)
{
	char *path = lem->args->graphical_lib_path;

	if (path != NULL) {
		*handle = dlopen(lem->args->graphical_lib_path, FLAGS);
		if (!(*handle)) {
			fprintf(stderr, "%s\n", dlerror());
			return (-1);
		}
		dlerror();
	}
	return (0);
}

void *graphical_render(void *arg)
{
	lemipc_t *lem = arg;
	void *handle = NULL;

	if (load_graph_lib(lem, &handle) == -1)
		return ("KO");
	printf(WELCOME_MESSAGE);
	dlclose(handle);
	return ("OK");
}