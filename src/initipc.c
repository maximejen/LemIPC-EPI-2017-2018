/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** initipc.c
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <memory.h>
#include <stdio.h>
#include "../include/lemipc.h"

static const int IPC_FLAGS = IPC_CREAT | SHM_W | SHM_R | IPC_EXCL;

/*
** Description:
** This function create the shared memory if it does not exists.
** otherwise, just add the shared memory to the lem struct.
*/
void init_shared_memory(lemipc_t *lem)
{
	size_t s = sizeof(sh_mem_t);

	lem->shm_id = shmget(lem->key, s, SHM_R | SHM_W);
	if (lem->shm_id == -1) {
		lem->is_first = 1;
		lem->shm_id = shmget(lem->key, s, IPC_CREAT | SHM_R | SHM_W);
		lem->mem = shmat(lem->shm_id, NULL, SHM_R | SHM_W);
		if (lem->mem) {
			memset(lem->mem, 0, s);
			lem->mem->width = WIDTH;
			lem->mem->height = HEIGHT;
		}
	} else
		lem->mem = shmat(lem->shm_id, NULL, SHM_R | SHM_W);
	if (should_i_be_commander(lem))
		lem->is_commander = 1;
}

/*
** Description:
** This function create the semaphore if it does not exists.
** otherwise, fill the lemipc struct.
*/
void init_semaphores(lemipc_t *lem)
{
	lem->sem_id = semget(lem->key, 2, SHM_R | SHM_W);
	if (lem->sem_id == -1) {
		lem->sem_id = semget(lem->key, 1, IPC_CREAT | SHM_R | SHM_W);
		if (lem->sem_id != -1) {
			semctl(lem->sem_id, 0, SETVAL, 1);
		}
	}
}

void init_message_queue(lemipc_t *lem)
{
	lem->msg_id = msgget(lem->key, SHM_W | SHM_R | IPC_EXCL);
	if (lem->msg_id == -1) {
		lem->msg_id = msgget(lem->key, IPC_FLAGS);
	}
}