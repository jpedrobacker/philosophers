NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
SRC_DIR = src/
FIND = $(shell find $(SRC_DIR))
SRC = $(filter %.c, $(FIND))

all: $(NAME)

$(NAME): $(SRC)
		$(CC) $(SRC) -o $(NAME)

git:
	@git add -A
	@git commit -m "checkpoint at $$(date '+%Y-%m-%dT%H:%M:%S%z')"
	@git push
	@echo Checkpoint created and pushed to remote

clean:
		rm -rf $(NAME)

fclean: clean
		rm -rf $(NAME)

re: fclean all
