NAME=test_thread_pool
CC=gcc
SRC=	main.c \
		thread.c \
		task.c \
		thread_pool.c
CFLAGS=-W -Wall -Werror -Wextra -std=c99
OBJ=$(SRC:%.c=%.o)

all:$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -lpthread

clean:
	rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all