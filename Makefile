##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## lemipc
##

CC	=	gcc

RM	=	rm -f

NAME	=	lemipc

SRC	=	main.c				\
		lemipc.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I include -W -Wall -Wextra

LDFLAGS	=

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
