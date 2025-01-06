NAME = philo

SRC = main.c parse.c routine.c threads.c utils.c
OBJ = $(SRC:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(SRC)
		@$(CC) $(OBJ) -o $(NAME)
	@echo "Philosophers successfully compiled!"
clean:
	@$(RM) $(OBJ)
	@echo "Philosophers successfully cleaned!"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean art re
