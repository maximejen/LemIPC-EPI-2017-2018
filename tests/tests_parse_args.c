/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** test_parse_arg.h
*/

#include <criterion/criterion.h>
#include "lemipc.h"

Test(parse_args, no_arg)
{
	args_t args = {NULL, -1, NULL, 0};
	int ac = 1;
	char *av[2];

	av[0] = "test";
	av[1] = NULL;
	cr_assert_eq(84, parse_args(ac, av, &args));
}