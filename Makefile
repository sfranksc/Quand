SRC = $(wildcard src/*.c)
HEADER = $(wildcard include/quand.h)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

NAME = bin/Quand

C_FLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

build/%.o: src/%.c $(HEADER)
	$(CC) $(C_FLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
