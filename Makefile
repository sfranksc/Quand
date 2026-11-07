SRC = quand.c
OBJ = $(SRC:%.c=%.o)

NAME = Quand

C_FLAGS = -Wall -Wextra -Werror -pedantic -std=c99

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(C_FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
