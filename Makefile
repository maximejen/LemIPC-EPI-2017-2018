##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## lemipc
##

CC	=	gcc

RM	=	rm -f

NAME	=	lemipc

SRC	=	src/main.c					\
		src/lemipc.c            			\
		src/initipc.c					\
		src/render/text/render.c			\
		src/render/graphical/render.c			\
		src/render/graphical/graph_functions.c		\
		src/render/color/handle_color_list.c		\
		src/render/color/color_generator.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I include -W -Wall -Wextra -g

LDFLAGS	=	-lpthread -lc_graph_prog

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
