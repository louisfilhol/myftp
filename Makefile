##
## EPITECH PROJECT, 2025
## B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -I./includes
LDFLAGS =

SRC = 	src/main.c \
		src/server.c \
		src/authentification.c \
		src/commands.c \
		src/file_commands.c \
		src/client_handler.c \
		src/socket_setup.c \
		src/client_management.c \

OBJ = $(SRC:.c=.o)
NAME = myftp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
