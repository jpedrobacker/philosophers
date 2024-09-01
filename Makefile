NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -I ./inc
THREADS = -pthread
SRC_DIR = src/obj
FIND = $(shell find $(SRC_DIR))
SRC = $(filter %.c, $(FIND))
OBJ = ${SRC:.c=.o}

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar -rcs philo.a $(OBJ)
		$(CC) $(CFLAGS) src/main.c philo.a -o $(NAME)
		make clean
		clear

git:
	@git add -A
	@git commit -m "checkpoint at $$(date '+%Y-%m-%dT%H:%M:%S%z')"
	@git push
	@echo Checkpoint created and pushed to remote

clean:
		rm -rf $(OBJ)
		clear

fclean: clean
		rm -rf philo.a
		rm -rf $(NAME)
		clear

re: fclean all

debug:	CFLAGS += -ggdb3
debug:	fclean ${NAME}
