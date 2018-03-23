/*
** EPITECH PROJECT, 2018
** lemIPC
** File description:
** my_str_to_wordtab.c
*/

#include <string.h>
#include <stdlib.h>

static size_t count_char(const char *str, char c)
{
	size_t count = 0;

	for (int i = 0 ; str[i] ; i++) {
		if (str[i] == c)
			count++;
	}
	return (count + 1);
}

static char *get_element(const char *str, int *i, char c)
{
	size_t count = 0;
	char *ret;

	while (str[(*i) + count] != 0 && str[(*i) + count] != c)
		count++;
	ret = strndup(str + (*i), count);
	(*i) += count;
	return (ret);
}

char **my_str_to_wordtab(const char *str, char c)
{
	size_t size = count_char(str, c);
	char **tab = malloc(sizeof(char *) * (size + 1));
	int y = 0;
	int i = 0;

	if (!tab)
		return (NULL);
	while (str[i]) {
		if (str[i] != c) {
			tab[y++] = get_element(str, &i, c);
		}
		if (str[i])
			i++;
	}
	tab[size] = NULL;
	return (tab);
}